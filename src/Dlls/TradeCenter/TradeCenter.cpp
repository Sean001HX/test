#include "include/TradeCenter/TradeCenter.h"
#include "ctrade.h"

namespace AllTrade{
    namespace NPTradeCenter {
        ITradeCenter::ITradeCenter()
        {
            m_trade = new CTradeCenter;
        }

        ITradeCenter::~ITradeCenter()
        {
            if (m_trade)
            {
                delete m_trade;
                m_trade = nullptr;
            }
        }

        void ITradeCenter::handlePlaceOrder(const OrderInfoPtr& order_ptr, const UserIDType use_id, const NPMgrCenter::SOnlineAccountPtr& user_online)
        {
            if (m_trade)
                m_trade->handlePlaceOrder(order_ptr, use_id, user_online, true);
        }

        void ITradeCenter::handleCancelOrder(CommodityTypeType commodity_type, const UserIDType use_id, const OrderStreamType order_stream)
        {
            if (m_trade)
                m_trade->handleCancelOrder(commodity_type, use_id, order_stream, true);
        }

        void ITradeCenter::changeQuoteStatus(bool bl)
        {
            if (m_trade)
                m_trade->changeQuoteStatus(bl);
        }

        void ITradeCenter::updateQuote(const QuoteInfoPtr& quote_ptr, const NPMgrCenter::SExchangeCPtr& exchange_ptr, const NPMgrCenter::SContractCPtr& contract_ptr)
        {
            if (m_trade)
                m_trade->updateQuote(quote_ptr, exchange_ptr, contract_ptr);
        }

        std::vector<AllTrade::NPTradeCenter::OrderInfoPtr> ITradeCenter::getCurrentOrderList(const UserIDType user_id)
        {
            return m_trade->getCurrentOrderList(user_id);
        }

        std::vector<AllTrade::NPTradeCenter::OrderInfoPtr> ITradeCenter::getTodayOrderList(const UserIDType user_id)
        {
            return m_trade->getTodayOrderList(user_id);
        }

        std::vector<AllTrade::NPTradeCenter::OrderInfoPtr> ITradeCenter::getHistoryOrderList(const UserIDType user_id, const DateType start_time, const DateType end_time)
        {
            return m_trade->getHistoryOrderList(user_id, start_time, end_time);
        }

        std::vector<AllTrade::NPTradeCenter::TradeInfoPtr> ITradeCenter::getTradeList(const UserIDType user_id)
        {
            return m_trade->getTradeList(user_id);
        }

        std::vector<AllTrade::NPTradeCenter::TradeInfoPtr> ITradeCenter::getHistoryTradeList(const UserIDType user_id, const DateType start_time, const DateType end_time)
        {
            return m_trade->getHistoryTradeList(user_id, start_time, end_time);
        }

        std::vector<AllTrade::NPTradeCenter::PositionInfoPtr> ITradeCenter::getPositionList(const UserIDType user_id)
        {
            return m_trade->getPositionList(user_id);
        }

        AllTrade::NPTradeCenter::TradeFeePtr ITradeCenter::getFeeSetPtr()
        {
            return m_trade->getFeeSetPtr();
        }

        AllTrade::ErrorCodeType ITradeCenter::setFeeSetPtr(const AllTrade::NPTradeCenter::TradeFeePtr& ptr)
        {
            return m_trade->setFeeSetPtr(ptr);
        }

        bool ITradeCenter::canCancelOrder(const UserIDType use_id, const OrderStreamType order_stream)
        {
            return m_trade->canCancelOrder(use_id, order_stream);
        }

        std::vector<AllTrade::NPTradeCenter::SForbidTradePtr> ITradeCenter::getAllForbidTradeStatus()
        {
            return m_trade->getAllForbidTradeStatus();
        }

        ErrorCodeType ITradeCenter::updateForbidTradeStatus(const AllTrade::NPTradeCenter::SForbidTradePtr& ptr)
        {
            return m_trade->updateForbidTradeStatus(ptr);
        }

        std::vector<AllTrade::NPTradeCenter::SPositionRatePtr> ITradeCenter::getAllPositionRateStatus()
        {
            return m_trade->getAllPositionRateStatus();
        }

        AllTrade::ErrorCodeType ITradeCenter::updatePositionRateStatus(const AllTrade::NPTradeCenter::SPositionRatePtr& ptr)
        {
            return m_trade->updatePositionRateStatus(ptr);
        }

        void ITradeCenter::recalculate_risk(CommodityTypeType commod_type, const UserIDType user_id)
        {
            return m_trade->recalculate_risk(commod_type, user_id);
        }

        void ITradeCenter::setOrderInsertCbk(const OrderInsertCbk& fun)
        {
            if (m_trade)
                m_trade->setOrderInsertCbk(fun);
        }

        void ITradeCenter::setOrderCancelCbk(const CancelOrderCbk& fun)
        {
            if (m_trade)
                m_trade->setOrderCancelCbk(fun);
        }

        void ITradeCenter::setOrderChangeCbk(const OrderChangeCbk& fun)
        {
            if (m_trade)
                m_trade->setOrderChangeCbk(fun);
        }

        void ITradeCenter::setTradeCbk(const TradeCbk& fun)
        {
            if (m_trade)
                m_trade->setTradeCbk(fun);
        }

        void ITradeCenter::setPositionCbk(const PositionCbk& fun)
        {
            if (m_trade)
                m_trade->setPositionCbk(fun);
        }

        void ITradeCenter::setRiskControlCbk(const RiskControlCbk& fun)
        {
            if (m_trade)
                m_trade->setRiskControlCbk(fun);
        }

    }
}