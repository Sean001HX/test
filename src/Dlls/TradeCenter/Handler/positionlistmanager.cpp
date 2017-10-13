#include <sstream>
#include <assert.h>
#include "include/ManagerCenter/ManagerCenter.h"
#include "positionlistmanager.h"
#include "define/struct_extern.h"
#include "define/protocol_error.h"
#include "tradehandler.h"
#include "positionhandler.h"
#include "utility/utility_fun.h"
#include "include/OperationManager/OperationManager.h"
// #include <windows.h>
// #include "../Application/stockservermgr.h"
// #include "../Application/foreignfutureservermgr.h"
// #include "../Application/chinafutureservermgr.h"
#include "../Application/taskmsg_order_mgr.h"

#include "C:/ng_tools/ng_header_for_log4cxx/ng_header_for_log4cxx.hpp"
#include "C:/ng_tools/ng_header_for_log4cxx/ng_header_for_log4cxx_log_var.hpp"
NG_LOGGER(logger, "PositionListManager");

namespace AllTrade {
    namespace NPTradeCenter {

        PositionListManager::PositionKey::PositionKey(const TradeHrPtr& trade_hr_ptr)
        {
            strncpy_s(user_id_, trade_hr_ptr->getUserID().c_str(), sizeof(user_id_) - 1);
            strncpy_s(contract_id_, trade_hr_ptr->getContractID().c_str(), sizeof(contract_id_) - 1);
            direct_ = trade_hr_ptr->getDirect();
        }

        PositionListManager::PositionKey::PositionKey(const UserIDType user_id, const ContractIDType contract_id, DirectType direct)
        {
            strncpy_s(user_id_, user_id, sizeof(user_id_) - 1);
            strncpy_s(contract_id_, contract_id, sizeof(contract_id_) - 1);
            direct_ = direct;
        }

        //////////////////////////////////////////////////////////////////////////
        PositionListManager::PositionListManager()
        {
            std::map<PUserIDType, std::vector<StockPositionPtr>> posiOrders;
            if (OperationManager::COperationManager::instance()->getStockPositionInfo(posiOrders))
            {
                for (auto userposiOrders : posiOrders)
                {
                    for (auto userposiOrde : userposiOrders.second)
                    {
                        PositionKey map_key(userposiOrders.first.c_str(), userposiOrde->contract_id_, userposiOrde->direct_type_);
                        m_position_map[map_key] = std::make_shared<StockPositionHandler>(userposiOrde, userposiOrders.first.c_str());
                    }
                }
            }

			// 融资持仓查询操作
			handleGetMarginPosition();
        }
        
        PositionHrPtr PositionListManager::changePosition(const TradeHrPtr& trade_hr_ptr)
        {
            PositionKey map_key(trade_hr_ptr);
            PositionHrPtr pos_hr_ptr(nullptr);
            if (map_key.direct_ == DirectType::DIRECT_SELL)
            {
                map_key.direct_ = DirectType::DIRECT_BUY;
                writeLock lock(m_mtx_position);
                pos_hr_ptr = m_position_map[map_key];
                assert(pos_hr_ptr);
                pos_hr_ptr->addTradeInfo(trade_hr_ptr);
            }
            else
            {
                writeLock lock(m_mtx_position);
                pos_hr_ptr = m_position_map[map_key];
                if (!pos_hr_ptr)
                {
                    pos_hr_ptr = createPositionHr(trade_hr_ptr);
                    m_position_map[map_key] = pos_hr_ptr;
                }
                else
                    pos_hr_ptr->addTradeInfo(trade_hr_ptr);
            }

            pos_hr_ptr->checkPositionStatus();
            pos_hr_ptr->serialize();


            return pos_hr_ptr;
        }


        const PositionHrPtr PositionListManager::getReversePosition(const UserIDType user_id, const ContractIDType contract_id, DirectType direct)const
        {
            PositionKey map_key(user_id, contract_id, direct);
            return getReversePosition(map_key);
        }

        const PositionHrPtr PositionListManager::getReversePosition(PositionKey pos_key) const
        {
            switch (pos_key.direct_)
            {
            case AllTrade::DirectType::DIRECT_BUY:
                pos_key.direct_ = DirectType::DIRECT_SELL;
                break;
            case AllTrade::DirectType::DIRECT_SELL:
                pos_key.direct_ = DirectType::DIRECT_BUY;
                break;
            default:
                assert(0);
                break;
            }

            readLock lock(m_mtx_position);
            auto iter = m_position_map.find(pos_key);
            if (iter != m_position_map.end())
                return iter->second;

            return PositionHrPtr();
        }

        const AllTrade::NPTradeCenter::PositionHrPtr PositionListManager::getPosition(const UserIDType user_id, const ContractIDType contract_id, DirectType direct) const
        {
            PositionKey pos_key(user_id, contract_id, direct);
            readLock lock(m_mtx_position);
            auto iter = m_position_map.find(pos_key);
            if (iter != m_position_map.end())
                return iter->second;

            return PositionHrPtr();
        }

        void PositionListManager::removePositionItem(const PositionHrPtr& pos_item)
        {
            PositionKey pos_key(pos_item->getUserID().c_str(), pos_item->getContractID().c_str(), pos_item->getDirect());
            writeLock lock(m_mtx_position);
            auto iter = m_position_map.find(pos_key);
            if (iter == m_position_map.end())
                return;

            m_position_map.erase(iter);
        }

        std::vector<AllTrade::NPTradeCenter::PositionHrPtr> PositionListManager::getPositionHrsByContractIDs(const std::set<PContractIDType>& contract_ids) const
        {
            std::vector<AllTrade::NPTradeCenter::PositionHrPtr> rslt;
            readLock lock(m_mtx_position);
            for (auto& item : m_position_map)
            {
                if (contract_ids.find(item.first.contract_id_) != contract_ids.end())
                    rslt.push_back(item.second);
            }
            return rslt;
        }

        std::vector<AllTrade::NPTradeCenter::PositionHrPtr> PositionListManager::updatePositionQuoteByContractIDs(const std::map<PContractIDType, YDouble>& contract_id_last_quotes) const
        {
            std::vector<AllTrade::NPTradeCenter::PositionHrPtr> rslt;
            readLock lock(m_mtx_position);
            for (auto& item : m_position_map)
            {
                auto iter = contract_id_last_quotes.find(item.first.contract_id_);
                if (iter != contract_id_last_quotes.end())
                {
                    item.second->updateQuoteLastPrice(iter->second);
                    rslt.push_back(item.second);
                }
            }
            return rslt;
        }

        std::vector<AllTrade::NPTradeCenter::PositionHrPtr> PositionListManager::getPositionHrsByUserID(const UserIDType user_id) const
        {
            std::vector<AllTrade::NPTradeCenter::PositionHrPtr> rslt;

            std::set<std::string> contract_id_set;

            readLock lock(m_mtx_position);
            for (auto& item : m_position_map)
            {
                if (strcmp(item.first.user_id_, user_id) == 0)
                {
                    rslt.push_back(item.second);
                    assert(contract_id_set.find(item.second->getContractID()) == contract_id_set.end());
                    contract_id_set.insert(item.second->getContractID());
                }
            }
            return rslt;
        }

        std::vector<AllTrade::NPTradeCenter::PositionHrPtr> PositionListManager::getPositionHrsInSecondBoard(const UserIDType user_id) const
        {
            std::vector<AllTrade::NPTradeCenter::PositionHrPtr> rslt;
            readLock lock(m_mtx_position);
            for (auto& item : m_position_map)
            {
                if (strcmp(item.first.user_id_, user_id) == 0)
                {
                    auto con_ptr = AllTrade::NPMgrCenter::IManagerCenter::instance()->getStockContractByID(StockAreaType::STOCKAREA_TYPE_A, item.first.contract_id_);
                    auto stock_con_ptr = std::dynamic_pointer_cast<AllTrade::NPMgrCenter::SStockContract>(con_ptr);
                    if (stock_con_ptr&& stock_con_ptr->stock_plate_area_ == StockPlateAreaType::SPAT_Second_Board)
                        rslt.push_back(item.second);
                }
            }
            return rslt;
        }

        void PositionListManager::closeAllYestodayPosition(CommodityTypeType commod_type, const UserIDType user_id) const
        {
            std::vector<AllTrade::NPTradeCenter::PositionHrPtr> rslt = getPositionHrsByUserID(user_id);
            for (auto& item : rslt)
            {
                if (item->getCanCloseVol() <= 0)
                {
                    LOG4CXX_TRACE(logger, "强平时账户"LOG_NOVAR(user_id)"可平仓数为0"LOG_NOVAR(item->getContractID())LOG_NOVAR(item->getPositionVol())LOG_NOVAR(item->getPositionVol_T())LOG_NOVAR(item->getCanCloseVol()));
                    continue;
                }
                StockOrderPtr order_ptr = std::make_shared<StockOrderInfo>();
                order_ptr->order_vol_ = item->getCanCloseVol();
                order_ptr->op_type_ = OperatorTradeType::OPERATOR_TRADE_SYSTEM;
                order_ptr->commodity_type_ = commod_type;
                order_ptr->direct_type_ = item->getDirect() == DirectType::DIRECT_BUY ? DirectType::DIRECT_SELL : DirectType::DIRECT_BUY;
                order_ptr->order_price_ = 0.0;
                order_ptr->order_type_ = OrderTypeType::ORDER_TYPE_MARKET;
                order_ptr->order_mode_ = OrderModeType::ORDER_MODE_GFD;
                order_ptr->stock_area_ = StockAreaType::STOCKAREA_TYPE_A;
                strncpy_s(order_ptr->order_localtmp_ref_, "", sizeof(order_ptr->order_localtmp_ref_) - 1);
                strncpy_s(order_ptr->contract_id_, item->getContractID().c_str(), sizeof(order_ptr->contract_id_) - 1);
                strncpy_s(order_ptr->exchange_id_, item->getExchangeID().c_str(), sizeof(order_ptr->exchange_id_) - 1);
                strncpy_s(order_ptr->currency_id_, item->getCurrencyID().c_str(), sizeof(order_ptr->currency_id_) - 1);
                order_ptr->currency_rate_ = 1;
                order_ptr->order_trade_mode_ = OrderTradeModeType::ORDERTRADE_MODE_SIMULATE;

                std::string new_order_stream = user_id;
                new_order_stream += "&" + UtilityFun::createGUID();
                strncpy_s(order_ptr->order_stream_, new_order_stream.c_str(), sizeof(order_ptr->order_stream_) - 1);
                order_ptr->order_state_ = OrderStateType::ORDER_STATE_SUPPENDED;
                order_ptr->orser_state_explain_ = OSET_Err_No;
                strncpy_s(order_ptr->generate_datetime_, UtilityFun::getCurrentDateTime().c_str(), sizeof(order_ptr->generate_datetime_) - 1);

                TaskMsgOrderManager::instance()->handlePlaceOrder(order_ptr, user_id, nullptr, false);
            }
        }

        PositionHrPtr PositionListManager::createPositionHr(const TradeHrPtr& trade_hr_ptr)
        {
            PositionHrPtr pos_hr_ptr(nullptr);
            switch (trade_hr_ptr->getCommodityType())
            {
            case AllTrade::CommodityTypeType::COMMODITY_TYPE_STOCK:
            {
                if (trade_hr_ptr->getDirect() == DirectType::DIRECT_SELL)
                {
                    pos_hr_ptr = m_position_map[PositionKey(trade_hr_ptr->getUserID().c_str(), trade_hr_ptr->getContractID().c_str(), DirectType::DIRECT_BUY)];
                    if (pos_hr_ptr)
                        pos_hr_ptr->addTradeInfo(trade_hr_ptr);
                    else
                        assert(0);
                }
                else
                    pos_hr_ptr = std::make_shared<StockPositionHandler>(trade_hr_ptr);
            }
                break;
            case AllTrade::CommodityTypeType::COMMODITY_TYPE_FUTURE_F:
            {
                pos_hr_ptr = std::make_shared<ForeignFuturePositionHandler>(trade_hr_ptr);
            }
                break;
            case AllTrade::CommodityTypeType::COMMODITY_TYPE_FUTURE_C:
            {
                pos_hr_ptr = std::make_shared<ChinaFuturePositionHandler>(trade_hr_ptr);
            }
                break;
            default:
                assert(0);
                break;
            }
            if (trade_hr_ptr && pos_hr_ptr)
            {
                trade_hr_ptr->setPositionID(pos_hr_ptr->getPositionID().c_str());
            }
            else
                assert(0);

            return pos_hr_ptr;
        }

		void PositionListManager::handleGetMarginPosition()
		{
			std::vector<AllTrade::NPTradeCenter::MarginPositionInfoPtr> rslt; //= OperationManager::COperationManager::instance()->getAllMarginPosition();
			for (auto& item : rslt)
			{
				PositionKey map_key(item->user_id_, item->contract_id_, item->direct_type_);
				m_position_map[map_key] = std::make_shared<MarginPositionHandler>(item, item->user_id_);
			}
		}

    }
}