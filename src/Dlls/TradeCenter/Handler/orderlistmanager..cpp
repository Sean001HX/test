#include <assert.h>
#include "orderlistmanager.h"
#include "define/struct_extern.h"
#include "orderhandler.h"
#include "include/OperationManager/OperationManager.h"
#include "define/protocol_error.h"
#include "../Application/taskmsg_order_mgr.h"

#include "C:/ng_tools/ng_header_for_log4cxx/ng_header_for_log4cxx.hpp"
#include "C:/ng_tools/ng_header_for_log4cxx/ng_header_for_log4cxx_log_var.hpp"
NG_LOGGER(logger, "OrderListManager");

namespace AllTrade {
    namespace NPTradeCenter {

#pragma region 按合约进行的多索引排序
        void OrderListManager::OrderContractIndex::addToList(const OrderHrPtr& order_ptr)
        {
            switch (order_ptr->getDirect())
            {
            case AllTrade::DirectType::DIRECT_BUY:
            {
                writeLock lock(mtx_buy_order);
                auto& indexoftag = m_buy_orders.get<OrderStreamTag>();
                auto iter = indexoftag.find(order_ptr->getOrderStream());
                if (iter == indexoftag.end())
                    indexoftag.insert(order_ptr);
                else
                    indexoftag.replace(iter, order_ptr);// 注意modify在替换失败时会导致删除,但效率较高
            }
            break;
            case AllTrade::DirectType::DIRECT_SELL:
            {
                writeLock lock(mtx_sell_order);
                auto& indexoftag = m_sell_orders.get<OrderStreamTag>();
                auto iter = indexoftag.find(order_ptr->getOrderStream());
                if (iter == indexoftag.end())
                    indexoftag.insert(order_ptr);
                else
                    indexoftag.replace(iter, order_ptr);// 注意modify在替换失败时会导致删除,但效率较高
            }
            break;
            default:
                assert(0);
                break;
            }
        }

        void OrderListManager::OrderContractIndex::removefromList(const OrderHrPtr& order_ptr)
        {
            switch (order_ptr->getDirect())
            {
            case AllTrade::DirectType::DIRECT_BUY:
            {
                writeLock lock(mtx_buy_order);
                auto& indexoftag = m_buy_orders.get<OrderStreamTag>();
                auto iter = indexoftag.find(order_ptr->getOrderStream());
                if (iter != indexoftag.end())
                    indexoftag.erase(iter);
            }
            break;
            case AllTrade::DirectType::DIRECT_SELL:
            {
                writeLock lock(mtx_sell_order);
                auto& indexoftag = m_sell_orders.get<OrderStreamTag>();
                auto iter = indexoftag.find(order_ptr->getOrderStream());
                if (iter != indexoftag.end())
                    indexoftag.erase(iter);
            }
            break;
            default:
                assert(0);
                break;
            }
        }

        OrderHrPtr OrderListManager::OrderContractIndex::getOrderHrPtrByOrderStream(const OrderStreamType order_stream) const
        {
            OrderHrPtr rslt = getBuyOrderHrPtr<OrderStreamTag>(order_stream);
            if (!rslt)
                rslt = getSellOrderHrPtr<OrderStreamTag>(order_stream);

            return rslt;
        }

        AllTrade::NPTradeCenter::OrderHrPtr OrderListManager::OrderContractIndex::getOrderHrPtrByOrderRef(const OrderRefType order_ref) const
        {
            OrderHrPtr rslt = getBuyOrderHrPtr<OrderRefTag>(order_ref);
            if (!rslt)
                rslt = getSellOrderHrPtr<OrderRefTag>(order_ref);

            return rslt;
        }

        std::vector<OrderHrPtr> OrderListManager::OrderContractIndex::getOrderHrPtrByDirect(DirectType direct) const
        {
            std::vector<OrderHrPtr> rslt;
            switch (direct)
            {
            case AllTrade::DirectType::DIRECT_BUY:
            {
                readLock lock(mtx_buy_order);

                auto& indexoftag = m_buy_orders.get<OrdePriceTag>();
                for (auto item : indexoftag)
                    rslt.push_back(item);
            }
            break;
            case AllTrade::DirectType::DIRECT_SELL:
            {
                readLock lock(mtx_sell_order);

                auto& indexoftag = m_sell_orders.get<OrdePriceTag>();
                for (auto item : indexoftag)
                    rslt.push_back(item);
            }
            break;
            default:
                assert(0);
                break;
            }

            return rslt;
        }

        std::vector<OrderHrPtr> OrderListManager::OrderContractIndex::getOrderHrPtrByDirect() const
        {
            std::vector<OrderHrPtr> rslt(getOrderHrPtrByDirect(DirectType::DIRECT_BUY));
            std::vector<OrderHrPtr> sell_vec = getOrderHrPtrByDirect(DirectType::DIRECT_SELL);
            rslt.insert(rslt.end(), sell_vec.begin(), sell_vec.end());
            return rslt;
        }
#pragma endregion

#pragma region 按合约对持有用户的多索引排序
        void OrderListManager::OrderContractUserIndex::addToList(const OrderHrPtr& order_ptr)
        {
            writeLock lock(mtx_user_mtx);
            auto iter = m_users.find(order_ptr->getUserID());
            if (iter == m_users.end())
                m_users[order_ptr->getUserID()] = 1;
            else
                iter->second++;
        }

        void OrderListManager::OrderContractUserIndex::removefromList(const OrderHrPtr& order_ptr)
        {
            writeLock lock(mtx_user_mtx);
            auto iter = m_users.find(order_ptr->getUserID());
            if (iter != m_users.end())
            {
                iter->second--;
                if (iter->second == 0)
                    m_users.erase(iter);
            }
        }

        std::vector<AllTrade::PUserIDType> OrderListManager::OrderContractUserIndex::getAllUsers() const
        {
            std::vector<PUserIDType> rslt;
            readLock lock(mtx_user_mtx);

            for (auto& item : m_users)
            {
                assert(item.second != 0);
                rslt.push_back(item.first);
            }

            return rslt;
        }

#pragma endregion

#pragma region 按用户进行的多索引排序
        void OrderListManager::OrderUserIndex::addToList(const OrderHrPtr& order_ptr)
        {
            writeLock lock(mtx_order);
            auto& indexoftag = m_orders.get<OrderStreamTag>();
            auto iter = indexoftag.find(order_ptr->getOrderStream());
            if (iter == indexoftag.end())
                indexoftag.insert(order_ptr);
            else
                indexoftag.replace(iter, order_ptr);// 注意modify在替换失败时会导致删除,但效率较高
        }

        void OrderListManager::OrderUserIndex::removefromList(const OrderHrPtr& order_ptr)
        {
            writeLock lock(mtx_order);
            auto& indexoftag = m_orders.get<OrderStreamTag>();
            auto iter = indexoftag.find(order_ptr->getOrderStream());
            if (iter != indexoftag.end())
                indexoftag.erase(iter);
        }

        OrderHrPtr OrderListManager::OrderUserIndex::getOrderHrPtrByOrderStream(const OrderStreamType order_stream) const
        {
            return getOrderHrPtr<OrderStreamTag>(order_stream);
        }

        std::vector<OrderHrPtr> OrderListManager::OrderUserIndex::getOrderHrPtrByCreateTime() const
        {
            std::vector<OrderHrPtr> rslt;
            readLock lock(mtx_order);

            auto& indexoftag = m_orders.get<OrderCreateTimeTag>();
			for (auto item : indexoftag)
			{
				/*	if (item->getCommodityType() == AllTrade::CommodityTypeType::COMMODITY_TYPE_MARGIN)
					{

					}*/
				rslt.push_back(item);

			}
              
            return rslt;
        }
#pragma endregion

        const POrderStreamType get_order_stream(const OrderHrPtr& order_hr_ptr)
        {
            return order_hr_ptr->getOrderStream();
        }

        const AllTrade::POrderRefType get_order_ref(const OrderHrPtr& order_hr_ptr)
        {
            return order_hr_ptr->getOrderRef();
        }

        DirectType get_order_direct(const OrderHrPtr& order_hr_ptr)
        {
            return order_hr_ptr->getDirect();
        }

        YDouble get_order_price(const OrderHrPtr& order_hr_ptr)
        {
            return order_hr_ptr->getOrderPrice();
        }

        const PDateTimeType get_order_createtime(const OrderHrPtr& order_hr_ptr)
        {
            return order_hr_ptr->getGenerateDatetime();
        }

        const PUserIDType get_order_user_id(const OrderHrPtr& order_hr_ptr)
        {
            return order_hr_ptr->getUserID();
        }

        //////////////////////////////////////////////////////////////////////////
        OrderListManager::OrderListManager()
        {
            std::map<PUserIDType, std::vector<StockOrderPtr>> stockOrder;
            if (OperationManager::COperationManager::instance()->getStockOrderInfo(stockOrder))
            {
                for (auto& item : stockOrder)
                    for (auto& stock_order : item.second)
                        addToList(createOrderHr(stock_order, item.first.c_str(), NPMgrCenter::SOnlineAccountPtr()));
            }

		//	getMarginOrderInfo();
        }


        OrderListManager::~OrderListManager()
        {

        }

        OrderHrPtr OrderListManager::createOrderHr(const OrderInfoPtr& order_ptr, const UserIDType use_id, const NPMgrCenter::SOnlineAccountPtr& user_online)
        {
            OrderHrPtr new_hr(nullptr);
            switch (order_ptr->commodity_type_)
            {
            case AllTrade::CommodityTypeType::COMMODITY_TYPE_STOCK:
                new_hr = std::make_shared<StockOrderHandler>(std::dynamic_pointer_cast<StockOrderInfo>(order_ptr), use_id, user_online);
                break;
            case AllTrade::CommodityTypeType::COMMODITY_TYPE_FUTURE_F:
                new_hr = std::make_shared<ForeignFutureOrderHandler>(std::dynamic_pointer_cast<ForeignFutureOrderInfo>(order_ptr), use_id, user_online);
                break;
            case AllTrade::CommodityTypeType::COMMODITY_TYPE_FUTURE_C:
                new_hr = std::make_shared<ChinaFutureOrderHandler>(std::dynamic_pointer_cast<ChinaFutureOrderInfo>(order_ptr), use_id, user_online);
                break;

			case AllTrade::CommodityTypeType::COMMODITY_TYPE_MARGIN:
				new_hr = std::make_shared<MarginOrderHandler>(std::dynamic_pointer_cast<MarginOrderInfo>(order_ptr), use_id, user_online);
				break;
            default:
                assert(0);
                break;
            }

            if (new_hr)
            {
                assert(!getOrderHrPtrByUserID(use_id, order_ptr->order_stream_));
            }
            return new_hr;
        }

        AllTrade::NPTradeCenter::OrderHrPtr OrderListManager::getOrderHrPtrByContractID(const ContractIDType contract_id, const OrderStreamType order_stream) const
        {
            readLock lock(m_mtx_order);
            auto iter = m_contract_orders.find(contract_id);
            if (iter != m_contract_orders.end())
                return iter->second.getOrderHrPtrByOrderStream(order_stream);

            assert(0);
            return OrderHrPtr();
        }

        AllTrade::NPTradeCenter::OrderHrPtr OrderListManager::getOrderHrPtrByContractIDAndRef(const ContractIDType contract_id, const OrderRefType order_ref) const
        {
            readLock lock(m_mtx_order);
            auto iter = m_contract_orders.find(contract_id);
            if (iter != m_contract_orders.end())
                return iter->second.getOrderHrPtrByOrderRef(order_ref);

            assert(0);
            return OrderHrPtr();
        }

        AllTrade::NPTradeCenter::OrderHrPtr OrderListManager::getOrderHrPtrByUserID(const UserIDType use_id, const OrderStreamType order_stream) const
        {
            readLock lock(m_mtx_order);
            auto iter = m_user_orders.find(use_id);
            if (iter != m_user_orders.end())
                return iter->second.getOrderHrPtrByOrderStream(order_stream);

            return OrderHrPtr();
        }

        std::vector<OrderHrPtr> OrderListManager::getOrderHrListByContractID(const ContractIDType contract_id, DirectType direct) const
        {
            readLock lock(m_mtx_order);
            auto iter = m_contract_orders.find(contract_id);
            if (iter != m_contract_orders.end())
                return iter->second.getOrderHrPtrByDirect(direct);

            return std::vector<OrderHrPtr>();
        }

        std::vector<OrderHrPtr> OrderListManager::getOrderHrListByContractID(const ContractIDType contract_id) const
        {
            readLock lock(m_mtx_order);
            auto iter = m_contract_orders.find(contract_id);
            if (iter != m_contract_orders.end())
                return iter->second.getOrderHrPtrByDirect();

            return std::vector<OrderHrPtr>();
        }

        std::vector<OrderHrPtr> OrderListManager::getOrderHrListByUserID(const UserIDType user_id) const
        {
            readLock lock(m_mtx_order);
            auto iter = m_user_orders.find(user_id);
            if (iter != m_user_orders.end())
                return iter->second.getOrderHrPtrByCreateTime();

            return std::vector<OrderHrPtr>();
        }

        std::vector<AllTrade::PUserIDType> OrderListManager::getUserListByContractID(const ContractIDType contract_id) const
        {
            readLock lock(m_mtx_order);
            auto iter = m_order_users.find(contract_id);
            if (iter != m_order_users.end())
                return iter->second.getAllUsers();

            return std::vector<PUserIDType>();
        }

        void OrderListManager::closeAllOrders(CommodityTypeType commod_type, const UserIDType user_id) const
        {
            std::vector<OrderHrPtr> rslt = getOrderHrListByUserID(user_id);
            for (auto& item : rslt)
            {
                if (item->canCancelOrder() != Err_Succeed)
                    continue;

                TaskMsgOrderManager::instance()->handleCancelOrder(user_id, item->getOrderStream().c_str(), false, false);
            }
        }

        void OrderListManager::addToList(const OrderHrPtr& order_ptr)
        {
            LOG4CXX_DEBUG(logger, "创建委托至委托队列中"LOG_NOVAR(order_ptr->getOrderStream())
                ",委托手数"LOG_NOVAR(order_ptr->getOrderVol())
                ",委托生效手数"LOG_NOVAR(order_ptr->getEffectVol())
                ",持仓成本"LOG_NOVAR(order_ptr->getPoitionCost())
                ",委托合约"LOG_NOVAR(order_ptr->getContractID())
                ",委托价格"LOG_NOVAR(order_ptr->getOrderPrice())
                ",委托类型"LOG_NOVAR((int)order_ptr->getOrderType()));

            assert(order_ptr);
            writeLock lock(m_mtx_order);
            m_contract_orders[order_ptr->getContractID()].addToList(order_ptr);
            m_user_orders[order_ptr->getUserID()].addToList(order_ptr);
            m_order_users[order_ptr->getContractID()].addToList(order_ptr);
        }

        void OrderListManager::removefromList(const OrderHrPtr& order_ptr)
        {
            LOG4CXX_DEBUG(logger, "从委托队列中删除委托"LOG_NOVAR(order_ptr->getOrderStream())
                ",委托手数"LOG_NOVAR(order_ptr->getOrderVol())
                ",委托生效手数"LOG_NOVAR(order_ptr->getEffectVol())
                ",持仓成本"LOG_NOVAR(order_ptr->getPoitionCost())
                ",委托合约"LOG_NOVAR(order_ptr->getContractID())
                ",委托价格"LOG_NOVAR(order_ptr->getOrderPrice())
                ",委托类型"LOG_NOVAR((int)order_ptr->getOrderType()));

            assert(order_ptr);
            writeLock lock(m_mtx_order);
            auto iter_contract = m_contract_orders.find(order_ptr->getContractID());
            if (iter_contract != m_contract_orders.end())
                iter_contract->second.removefromList(order_ptr);

            auto iter_user = m_user_orders.find(order_ptr->getUserID());
            if (iter_user != m_user_orders.end())
                iter_user->second.removefromList(order_ptr);

            auto iter_order_user = m_order_users.find(order_ptr->getContractID());
            if (iter_order_user != m_order_users.end())
                iter_order_user->second.removefromList(order_ptr);
        }

		void OrderListManager::getMarginOrderInfo()
		{
			std::vector<AllTrade::NPTradeCenter::MarginOrderInfoPtr> vecPtr;// = OperationManager::COperationManager::instance()->getAllMarginOrder();

			for (auto& item : vecPtr)
			{
				item->commodity_type_ = CommodityTypeType::COMMODITY_TYPE_MARGIN;
				addToList(createOrderHr(item, item->user_id_, NPMgrCenter::SOnlineAccountPtr()));
			}
		}

    }

}