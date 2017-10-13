#include "servermgrbase.h"
#include "stockservermgr.h"
#include "foreignfutureservermgr.h"
#include "chinafutureservermgr.h"

#include "C:/ng_tools/ng_header_for_log4cxx/ng_header_for_log4cxx.hpp"
#include "C:/ng_tools/ng_header_for_log4cxx/ng_header_for_log4cxx_log_var.hpp"
NG_LOGGER(logger, "ServerManager");

using namespace AllTrade::NPMgrCenter;

namespace AllTrade {
    namespace NPTradeCenter {
        ServerMgrBase::ServerMgrBase(CommodityTypeType product_type)
            : m_product_type(product_type)
        {
        }

        ServerMgrBase::~ServerMgrBase()
        {
        }

        TradeManagerPtr ServerMgrBase::getTradeManagerPtr(CommodityTypeType commodity_type)
        {
            TradeManagerPtr trade_ptr(nullptr);
            switch (commodity_type)
            {
            case AllTrade::CommodityTypeType::COMMODITY_TYPE_STOCK:
                trade_ptr = StockServerMgr::instance();
                break;
            case AllTrade::CommodityTypeType::COMMODITY_TYPE_FUTURE_F:
                trade_ptr = ForeignFutureServerMgr::instance();
                break;
            case AllTrade::CommodityTypeType::COMMODITY_TYPE_FUTURE_C:
                trade_ptr = ChinaFutureServerMgr::instance();
                break;
            default:
                LOG4CXX_FATAL(logger, "未知商品类型,无法获取对应交易管理指针!");
                assert(0);
                break;
            }
            return trade_ptr;
        }


    }
}