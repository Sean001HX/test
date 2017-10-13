#include <assert.h>
#include "positionhandler.h"
#include "define/struct_base.h"
#include "define/protocol_error.h"
#include "define/struct_extern.h"
#include "tradehandler.h"
#include "include/OperationManager/OperationManager.h"
#include "positionlistmanager.h"
#include "utility/utility_fun.h"
#include "include/ManagerCenter/ManagerCenter.h"

#include "C:/ng_tools/ng_header_for_log4cxx/ng_header_for_log4cxx.hpp"
#include "C:/ng_tools/ng_header_for_log4cxx/ng_header_for_log4cxx_log_var.hpp"
NG_LOGGER(logger, "PositionHandler");

using namespace AllTrade::NPMgrCenter;

namespace AllTrade {
    namespace NPTradeCenter {
        PositionBaseHandler::PositionBaseHandler(const PositionInfoPtr& position_ptr, const UserIDType user_id)
            : m_position_ptr(position_ptr)
            , m_is_modify(false)
        {
            strncpy_s(m_user_id, user_id, sizeof(m_user_id) - 1);
        }

        PositionBaseHandler::PositionBaseHandler(const TradeHrPtr& trade_hr)
            : m_position_ptr(nullptr)
            , m_is_modify(true)
        {
        }

        const PPositionIDType PositionBaseHandler::getPositionID() const
        {
            return m_position_ptr->position_id_;
        }

        const PUserIDType PositionBaseHandler::getUserID() const
        {
            return m_user_id;
        }

        const PExchangeIDType PositionBaseHandler::getExchangeID() const
        {
            return m_position_ptr->exchange_id_;
        }

        const PContractIDType PositionBaseHandler::getContractID() const
        {
            return m_position_ptr->contract_id_;
        }

        int PositionBaseHandler::getPositionAllVol() const
        {
            readLock lock(m_mtx);
            return m_position_ptr->volume_ + m_position_ptr->T_volume_;
        }

        int PositionBaseHandler::getPositionVol() const
        {
            readLock lock(m_mtx);
            return m_position_ptr->volume_;
        }

        int PositionBaseHandler::getPositionVol_T() const
        {
            readLock lock(m_mtx);
            return m_position_ptr->T_volume_;
        }

        int PositionBaseHandler::getCanCloseVol() const
        {
            readLock lock(m_mtx);
            return m_position_ptr->volume_ - m_position_ptr->freeze_order_vol_;
        }

        bool PositionBaseHandler::addFreezeVol(int vol)
        {
            if (vol == 0)
                return true;

            LOG4CXX_DEBUG(logger, LOG_NOVAR(m_position_ptr->position_id_)
                "新增委托冻结持仓手数"LOG_NOVAR(vol)
                ",原委托冻结持仓手数"LOG_NOVAR(m_position_ptr->freeze_order_vol_)
                ",原持仓总手数"LOG_NOVAR(m_position_ptr->volume_));

            {
                writeLock lock(m_mtx);
                if (m_position_ptr->freeze_order_vol_ + vol > m_position_ptr->volume_)
                    return false;

                if (m_position_ptr->freeze_order_vol_ + vol < 0)
                    return false;

                m_position_ptr->freeze_order_vol_ += vol;
                m_is_modify = true;
            }
            if (serialize() != Err_Succeed)
            {
                LOG4CXX_ERROR(logger, LOG_NOVAR(m_position_ptr->position_id_)"新增委托冻结持仓手数时写入数据库失败");
                writeLock lock(m_mtx);
                m_position_ptr->freeze_order_vol_ -= vol;
                m_is_modify = true;
                return false;
            }
            return true;
        }

        DirectType PositionBaseHandler::getDirect() const
        {
            return m_position_ptr->direct_type_;
        }

        const PCurrencyIDType PositionBaseHandler::getCurrencyID() const
        {
            return m_position_ptr->currency_id_;
        }

        YDouble PositionBaseHandler::getTradeAvePrice() const
        {
            readLock lock(m_mtx);
            return m_position_ptr->trade_ave_price_;
        }

        YDouble PositionBaseHandler::getPositionCost() const
        {
            return m_position_ptr->cost_price_;
        }

        bool PositionBaseHandler::isValid() const
        {
            return true;
        }

        void PositionBaseHandler::updateQuoteLastPrice(YDouble last_quote)
        {
            writeLock lock(m_mtx_quote);
            assert(last_quote != 0);
            m_last_quote = last_quote;
        }

        AllTrade::CommodityTypeType PositionBaseHandler::getCommodityType() const
        {
            return m_position_ptr->commodity_type_;
        }

        YDouble PositionBaseHandler::getLastPrice() const
        {
            readLock lock(m_mtx_quote);
            return m_last_quote*(m_position_ptr->volume_ + m_position_ptr->T_volume_);
        }

        YDouble PositionBaseHandler::getProfit() const
        {
            readLock lock(m_mtx_quote);
            return getLastPrice() - getPositionCost();
        }

        AllTrade::ErrorCodeType PositionBaseHandler::serialize()
        {
            writeLock lock(m_mtx);
            if (!m_is_modify)
                return Err_Succeed;

            if (m_position_ptr->volume_ == 0 && m_position_ptr->T_volume_ == 0 && m_position_ptr->freeze_order_vol_ == 0)
            {
                if (!OperationManager::COperationManager::instance()->deletePositionInfo(m_position_ptr, m_user_id))
                    return Err_Database;
            }
            else
            {
                if (!OperationManager::COperationManager::instance()->updatePositionInfo(m_position_ptr, m_user_id))
                    return Err_Database;
            }

            m_is_modify = false;
            return Err_Succeed;
        }

        void PositionBaseHandler::settlePosition()
        {
            LOG4CXX_TRACE(logger, LOG_NOVAR(m_user_id)LOG_NOVAR(m_position_ptr->position_id_)"结算持仓,原T手数"LOG_NOVAR(m_position_ptr->volume_)",原T+1手数"LOG_NOVAR(m_position_ptr->T_volume_));
            {
                writeLock lock(m_mtx);
                m_position_ptr->volume_ += m_position_ptr->T_volume_;
                m_position_ptr->T_volume_ = 0;
                m_is_modify = true;
            }
            LOG4CXX_TRACE(logger, LOG_NOVAR(m_user_id)LOG_NOVAR(m_position_ptr->position_id_)"结算持仓完毕,T手数"LOG_NOVAR(m_position_ptr->volume_)",T+1手数"LOG_NOVAR(m_position_ptr->T_volume_));
            serialize();
        }

        void PositionBaseHandler::createByTradeHr(const TradeHrPtr& trade_hr)
        {
            assert(m_position_ptr);

            strncpy_s(m_user_id, trade_hr->getUserID().c_str(), sizeof(m_user_id) - 1);
            strncpy_s(m_position_ptr->position_id_, UtilityFun::createGUID().c_str(), sizeof(m_position_ptr->position_id_) - 1);
            strncpy_s(m_position_ptr->contract_id_, trade_hr->getContractID().c_str(), sizeof(m_position_ptr->contract_id_) - 1);
            m_position_ptr->direct_type_ = trade_hr->getDirect();
            strncpy_s(m_position_ptr->currency_id_, trade_hr->getCurrencyID().c_str(), sizeof(m_position_ptr->currency_id_) - 1);
            m_position_ptr->trade_ave_price_ = trade_hr->getTradePrice();
            m_position_ptr->cost_price_ = trade_hr->getPositionCost();
            strncpy_s(m_position_ptr->exchange_id_, trade_hr->getExchangeID().c_str(), sizeof(m_position_ptr->exchange_id_) - 1);
            m_position_ptr->commodity_type_ = trade_hr->getCommodityType();
        }

        //////////////////////////////////////////////////////////////////////////
        StockPositionHandler::StockPositionHandler(const TradeHrPtr& trade_hr)
            : PositionBaseHandler(trade_hr)
        {
            createByTradeHr(trade_hr);
        }

        StockPositionHandler::StockPositionHandler(const StockPositionPtr& position_ptr, const UserIDType user_id)
            : PositionBaseHandler(position_ptr, user_id)
        {
        }

        void StockPositionHandler::addTradeInfo(const TradeHrPtr& trade_hr_ptr)
        {
            if (!trade_hr_ptr)
                return;

            LOG4CXX_DEBUG(logger, "成交前"LOG_NOVAR(m_user_id)LOG_NOVAR(m_position_ptr->position_id_)"T持仓手数"LOG_NOVAR(m_position_ptr->volume_)",T+1手数"LOG_NOVAR(m_position_ptr->T_volume_));
            
            if (trade_hr_ptr->getDirect() == AllTrade::DirectType::DIRECT_SELL)
                addFreezeVol(-trade_hr_ptr->getTradeVol());

            writeLock lock(m_mtx);

            assert(strcmp(trade_hr_ptr->getCurrencyID().c_str(), m_position_ptr->currency_id_) == 0);

            switch (trade_hr_ptr->getDirect())
            {
            case AllTrade::DirectType::DIRECT_BUY:
            {
                m_position_ptr->trade_ave_price_ = (m_position_ptr->trade_ave_price_ * (m_position_ptr->volume_ + m_position_ptr->T_volume_) + trade_hr_ptr->getTradePrice() * trade_hr_ptr->getTradeVol()) / (m_position_ptr->volume_ + m_position_ptr->T_volume_ + trade_hr_ptr->getTradeVol());
                m_position_ptr->cost_price_ += trade_hr_ptr->getPositionCost();
                m_position_ptr->T_volume_ += trade_hr_ptr->getTradeVol();
            }
            break;
            case AllTrade::DirectType::DIRECT_SELL:
                if (m_position_ptr->volume_ + m_position_ptr->T_volume_ - trade_hr_ptr->getTradeVol() == 0)
                {
                    IManagerCenter::instance()->changePositionCost(trade_hr_ptr->getUserID().c_str(), -m_position_ptr->cost_price_, trade_hr_ptr->getTradeVol(), trade_hr_ptr->getDirect());
                    m_position_ptr->trade_ave_price_ = 0;
                    m_position_ptr->cost_price_ = 0;
                    m_position_ptr->volume_ -= trade_hr_ptr->getTradeVol();
                }
                else
                {
                    IManagerCenter::instance()->changePositionCost(trade_hr_ptr->getUserID().c_str(), UtilityFun::Round(trade_hr_ptr->getPositionCost() - trade_hr_ptr->getTradePrice()*trade_hr_ptr->getTradeVol() * 2, 0.00001) , trade_hr_ptr->getTradeVol(), trade_hr_ptr->getDirect());
                    m_position_ptr->trade_ave_price_ = (m_position_ptr->trade_ave_price_ * (m_position_ptr->volume_ + m_position_ptr->T_volume_) - trade_hr_ptr->getTradePrice() * trade_hr_ptr->getTradeVol()) / (m_position_ptr->volume_ + m_position_ptr->T_volume_ - trade_hr_ptr->getTradeVol());
                    m_position_ptr->cost_price_ = (m_position_ptr->cost_price_ + trade_hr_ptr->getPositionCost() - trade_hr_ptr->getTradePrice()*trade_hr_ptr->getTradeVol() * 2);
                    m_position_ptr->volume_ -= trade_hr_ptr->getTradeVol();
                }
                break;
            default:
                assert(0);
                break;
            }

            trade_hr_ptr->setPositionID(m_position_ptr->position_id_);
            m_is_modify = true;
            LOG4CXX_DEBUG(logger, "成交后"LOG_NOVAR(m_user_id)LOG_NOVAR(m_position_ptr->position_id_)"T持仓手数"LOG_NOVAR(m_position_ptr->volume_)",T+1手数"LOG_NOVAR(m_position_ptr->T_volume_));

        }

        void StockPositionHandler::checkPositionStatus()
        {
            writeLock lock(m_mtx);
            if (m_position_ptr->volume_ == 0
                && m_position_ptr->T_volume_ == 0
                && m_position_ptr->freeze_order_vol_ == 0
                && m_position_ptr->cost_price_ == 0.0)
                PositionListManager::instance()->removePositionItem(shared_from_this());
        }

        AllTrade::NPTradeCenter::PositionInfoPtr StockPositionHandler::getPositionCopy() const
        {
            return std::make_shared<StockPositionInfo>(*std::dynamic_pointer_cast<StockPositionInfo>(m_position_ptr).get());
        }

        void StockPositionHandler::createByTradeHr(const TradeHrPtr& trade_hr)
        {
            StockPositionPtr position_ptr = std::make_shared<StockPositionInfo>();
            StockTradeHrPtr stock_trade = std::dynamic_pointer_cast<StockTradeHandler>(trade_hr);

            position_ptr->stock_area_ = StockAreaType::STOCKAREA_TYPE_A;
            position_ptr->T_volume_ = trade_hr->getTradeVol();
            position_ptr->volume_ = 0;

            m_position_ptr = position_ptr;

            PositionBaseHandler::createByTradeHr(trade_hr);
        }

        //////////////////////////////////////////////////////////////////////////
        ForeignFuturePositionHandler::ForeignFuturePositionHandler(const TradeHrPtr& trade_hr)
            : PositionBaseHandler(trade_hr)
        {
            createByTradeHr(trade_hr);
        }

        const PProductIDType ForeignFuturePositionHandler::getProductID() const
        {
            ForeignFuturePositionPtr ffuture_position_ptr = std::dynamic_pointer_cast<ForeignFuturePositionInfo>(m_position_ptr);
            assert(ffuture_position_ptr);
            return ffuture_position_ptr->product_id_;
        }

        void ForeignFuturePositionHandler::addTradeInfo(const TradeHrPtr& trade_hr_ptr)
        {

        }

        AllTrade::NPTradeCenter::PositionInfoPtr ForeignFuturePositionHandler::getPositionCopy() const
        {
            return std::make_shared<ForeignFuturePositionInfo>(*std::dynamic_pointer_cast<ForeignFuturePositionInfo>(m_position_ptr).get());
        }

        //////////////////////////////////////////////////////////////////////////
        ChinaFuturePositionHandler::ChinaFuturePositionHandler(const TradeHrPtr& trade_hr)
            : PositionBaseHandler(trade_hr)
        {
            createByTradeHr(trade_hr);
        }

        const PProductIDType ChinaFuturePositionHandler::getProductID() const
        {
            ChinaFuturePositionPtr cfuture_position_ptr = std::dynamic_pointer_cast<ChinaFuturePositionInfo>(m_position_ptr);
            assert(cfuture_position_ptr);
            return cfuture_position_ptr->product_id_;
        }

        const OffsetType ChinaFuturePositionHandler::getOffsetType() const
        {
            ChinaFuturePositionPtr cfuture_position_ptr = std::dynamic_pointer_cast<ChinaFuturePositionInfo>(m_position_ptr);
            assert(cfuture_position_ptr);
            return cfuture_position_ptr->offset_type_;
        }

        void ChinaFuturePositionHandler::addTradeInfo(const TradeHrPtr& trade_hr_ptr)
        {

        }

        AllTrade::NPTradeCenter::PositionInfoPtr ChinaFuturePositionHandler::getPositionCopy() const
        {
            return std::make_shared<ChinaFuturePositionInfo>(*std::dynamic_pointer_cast<ChinaFuturePositionInfo>(m_position_ptr).get());
        }

		//////////////////////////////////////////////////////////////////////////
		MarginPositionHandler::MarginPositionHandler(const MarginPositionInfoPtr& position_ptr, const UserIDType user_id)
			: PositionBaseHandler(position_ptr, user_id)
		{

		}

		MarginPositionHandler::MarginPositionHandler(const TradeHrPtr& trade_hr)
			: PositionBaseHandler(trade_hr)
		{
			createByTradeHr(trade_hr);
		}

		void MarginPositionHandler::addTradeInfo(const TradeHrPtr& trade_hr_ptr)
		{

		}

		void MarginPositionHandler::checkPositionStatus()
		{

		}

		AllTrade::NPTradeCenter::PositionInfoPtr MarginPositionHandler::getPositionCopy() const
		{
			return std::make_shared<MarginPositionInfo>(*std::dynamic_pointer_cast<MarginPositionInfo>(m_position_ptr).get());
		}

		void MarginPositionHandler::createByTradeHr(const TradeHrPtr& trade_hr)
		{

		}

	}
}
