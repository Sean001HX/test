#include <assert.h>
#include "ctrade.h"
#include "define/struct_extern.h"
#include "define/protocol_error.h"
#include "Application/stockservermgr.h"
#include "Application/foreignfutureservermgr.h"
#include "Application/chinafutureservermgr.h"
#include "Handler/orderhandler.h"
#include "Handler/orderlistmanager.h"
#include "Handler/tradehandler.h"
#include "Handler/tradelistmanager.h"
#include "Handler/positionhandler.h"
#include "Handler/positionlistmanager.h"
#include "include/OperationManager/OperationManager.h"
#include "utility/utility_fun.h"
#include "Handler/quotelistmanager.h"
#include "SimulateTrade/SimulateOrder.h"
#include "SyncTrade/SyncOrder.h"
#include "Application/TradeFeeManager.h"
#include "Application/RiskControlManager.h"
#include "Application/SettleManagerThread.h"
#include "Application/GlobalDataManager.h"
#include "Application/ForbidTradeManager.h"
#include "Application/PositionRateManager.h"

#include "Application/taskmsg_order_mgr.h"

#include "C:/ng_tools/ng_header_for_log4cxx/ng_header_for_log4cxx.hpp"
#include "C:/ng_tools/ng_header_for_log4cxx/ng_header_for_log4cxx_log_var.hpp"
NG_LOGGER(logger, "CTradeCenter");

namespace AllTrade{
    namespace NPTradeCenter {
        CTradeCenter::CTradeCenter()
        {
            SettleManagerThread::instance()->start();

            StockServerMgr::instance();
            ForeignFutureServerMgr::instance();
            ChinaFutureServerMgr::instance();

            TradeFeeManager::instance();
            QuoteListManager::instance();
            SimulateOrder::instance();
            SyncOrder::instance();

            OrderListManager::instance();
            TradeListManager::instance();
            PositionListManager::instance();

            RiskControlManager::instance();

            GlobalDataManager::instance();

            ForbidTradeManager::instance();
        }

        CTradeCenter::~CTradeCenter()
        {
            SettleManagerThread::instance()->unInitialize();
            SettleManagerThread::unInstance();

            RiskControlManager::unInstance();

            StockServerMgr::unInstance();
            ForeignFutureServerMgr::unInstance();
            ChinaFutureServerMgr::unInstance();

            // Ë³Ðò²»ÄÜµßµ¹
            SimulateOrder::unInstance();
            SyncOrder::unInstance();
            QuoteListManager::unInstance();
            TradeFeeManager::unInstance();

            OrderListManager::unInstance();
            TradeListManager::unInstance();
            PositionListManager::unInstance();
      
            GlobalDataManager::unInstance();

            ForbidTradeManager::unInstance();
        }

        void CTradeCenter::handlePlaceOrder(const OrderInfoPtr& order_ptr, const UserIDType use_id, const NPMgrCenter::SOnlineAccountPtr& user_online, bool needRecode)
        {
            TaskMsgOrderManager::instance()->handlePlaceOrder(order_ptr, use_id, user_online, needRecode);
        }

        void CTradeCenter::handleCancelOrder(CommodityTypeType commodity_type, const UserIDType use_id, const OrderStreamType order_stream, bool needRecode)
        {
            TaskMsgOrderManager::instance()->handleCancelOrder(use_id, order_stream, needRecode, false);
        }

        void CTradeCenter::changeQuoteStatus(bool bl)
        {
            QuoteListManager::instance()->changeQuoteStatus(bl);
        }

        void CTradeCenter::updateQuote(const QuoteInfoPtr& quote_ptr, const NPMgrCenter::SExchangeCPtr& exchange_ptr, const NPMgrCenter::SContractCPtr& contract_ptr)
        {
            switch (contract_ptr->commodity_type_)
            {
            case AllTrade::CommodityTypeType::COMMODITY_TYPE_STOCK:
                StockServerMgr::instance()->updateQuote(quote_ptr, exchange_ptr, contract_ptr);
                break;
            default:
                assert(0);
                break;
            }
        }

        std::vector<AllTrade::NPTradeCenter::OrderInfoPtr> CTradeCenter::getCurrentOrderList(const UserIDType user_id)
        {
            std::vector<OrderHrPtr> vec_order_hr = OrderListManager::instance()->getOrderHrListByUserID(user_id);
            std::vector<OrderInfoPtr> rslt;
            for (auto& item : vec_order_hr)
                rslt.push_back(item->getOrderInfoCopy());

            std::vector<OrderInfoPtr> tmp = getTodayOrderList(user_id);
            rslt.insert(rslt.end(), tmp.begin(), tmp.end());
            return rslt;
        }

        std::vector<AllTrade::NPTradeCenter::OrderInfoPtr> CTradeCenter::getTodayOrderList(const UserIDType user_id)
        {
            return OperationManager::COperationManager::instance()->getStockOrderHistory(user_id, UtilityFun::getCurrentDate().c_str(), UtilityFun::getAddDate(1).c_str());
        }

        std::vector<AllTrade::NPTradeCenter::OrderInfoPtr> CTradeCenter::getHistoryOrderList(const UserIDType user_id, const DateType start_time, const DateType end_time)
        {
            return OperationManager::COperationManager::instance()->getStockOrderHistory(user_id, start_time, end_time);
        }

        std::vector<AllTrade::NPTradeCenter::TradeInfoPtr> CTradeCenter::getTradeList(const UserIDType user_id)
        {
            return OperationManager::COperationManager::instance()->getStockTradeHistory(user_id, UtilityFun::getCurrentDate().c_str(), UtilityFun::getAddDate(1).c_str());
        }

        std::vector<AllTrade::NPTradeCenter::TradeInfoPtr> CTradeCenter::getHistoryTradeList(const UserIDType user_id, const DateType start_time, const DateType end_time)
        {
            return OperationManager::COperationManager::instance()->getStockTradeHistory(user_id, start_time, end_time);
        }

        std::vector<AllTrade::NPTradeCenter::PositionInfoPtr> CTradeCenter::getPositionList(const UserIDType user_id)
        {
            std::vector<PositionHrPtr> vec_order_hr = PositionListManager::instance()->getPositionHrsByUserID(user_id);
            std::vector<PositionInfoPtr> rslt;
            for (auto& item : vec_order_hr)
            {
                auto pos_item = item->getPositionCopy();
                if (pos_item->volume_ == 0 && pos_item->T_volume_ == 0)
                    continue;
                rslt.push_back(pos_item);
            }

            return rslt;
        }

        AllTrade::NPTradeCenter::TradeFeePtr CTradeCenter::getFeeSetPtr()
        {
            return AllTrade::NPTradeCenter::TradeFeeManager::instance()->getFeeSetPtrCopy();
        }

        AllTrade::ErrorCodeType CTradeCenter::setFeeSetPtr(const AllTrade::NPTradeCenter::TradeFeePtr& ptr)
        {
            return AllTrade::NPTradeCenter::TradeFeeManager::instance()->setFeeSetPtr(ptr);
        }

        bool CTradeCenter::canCancelOrder(const UserIDType use_id, const OrderStreamType order_stream)
        {
            auto item = OrderListManager::instance()->getOrderHrPtrByUserID(use_id, order_stream);
            if (item)
                return item->canCancelOrder() == Err_Succeed;

            return false;
        }

        std::vector<AllTrade::NPTradeCenter::SForbidTradePtr> CTradeCenter::getAllForbidTradeStatus()
        {
            return ForbidTradeManager::instance()->getAllForbidTradeStatus();
        }

        ErrorCodeType CTradeCenter::updateForbidTradeStatus(const AllTrade::NPTradeCenter::SForbidTradePtr& ptr)
        {
            return ForbidTradeManager::instance()->updateForbidTradeStatus(ptr);
        }

        std::vector<AllTrade::NPTradeCenter::SPositionRatePtr> CTradeCenter::getAllPositionRateStatus()
        {
            return PositionRateManager::instance()->getAllPositionRateStatus();
        }

        AllTrade::ErrorCodeType CTradeCenter::updatePositionRateStatus(const AllTrade::NPTradeCenter::SPositionRatePtr& ptr)
        {
            return PositionRateManager::instance()->updatePositionRateStatus(ptr);
        }

        void CTradeCenter::recalculate_risk(CommodityTypeType commod_type, const UserIDType user_id)
        {
            RiskControlManager::instance()->init_calculate(commod_type, user_id, true, true);
        }

        void CTradeCenter::setOrderInsertCbk(const OrderInsertCbk& fun)
        {
            TaskMsgOrderManager::instance()->setOrderInsertCbk(fun);
        }

        void CTradeCenter::setOrderCancelCbk(const CancelOrderCbk& fun)
        {
            TaskMsgOrderManager::instance()->setOrderCancelCbk(fun);
        }

        void CTradeCenter::setOrderChangeCbk(const OrderChangeCbk& fun)
        {
            TaskMsgOrderManager::instance()->setOrderChangeCbk(fun);
        }

        void CTradeCenter::setTradeCbk(const TradeCbk& fun)
        {
            TaskMsgOrderManager::instance()->setTradeCbk(fun);
        }

        void CTradeCenter::setPositionCbk(const PositionCbk& fun)
        {
            TaskMsgOrderManager::instance()->setPositionCbk(fun);
        }

        void CTradeCenter::setRiskControlCbk(const RiskControlCbk& fun)
        {
            TaskMsgOrderManager::instance()->setRiskControlCbk(fun);
        }

    }
}