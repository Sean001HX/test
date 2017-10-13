#include "tradeapibase.h"

namespace AllTrade {

    CTradeApiBase::CTradeApiBase(CommodityTypeType type)
        : m_type(type)
    {
    }

    CommodityTypeType CTradeApiBase::currentType() const
    {
        return m_type;
    }

    //////////////////////////////////////////////////////////////////////////
    StockTradeApi::StockTradeApi()
        : CTradeApiBase(CommodityTypeType::COMMODITY_TYPE_STOCK)
    {

    }

    void StockTradeApi::quit()
    {

    }

    void StockTradeApi::login()
    {

    }

    void StockTradeApi::placeOrder(const OrderInfoPtr& order_info_ptr)
    {

    }

    void StockTradeApi::cancelOrder(const CancelOrderInfoPtr& cancel_order_info_ptr)
    {

    }

    void StockTradeApi::queryMoney() const
    {

    }

    void StockTradeApi::getOrderRecord() const
    {

    }

    void StockTradeApi::getTradeRecord() const
    {

    }

    void StockTradeApi::getPositionRecord() const
    {

    }

}