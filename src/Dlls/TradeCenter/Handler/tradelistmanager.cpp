#include "tradelistmanager.h"
#include "define/struct_extern.h"
#include "orderhandler.h"
#include "tradehandler.h"
#include "utility/utility_fun.h"
#include "../Application/stockservermgr.h"
#include "../Application/foreignfutureservermgr.h"
#include "../Application/chinafutureservermgr.h"
#include "../Application/taskmsg_order_mgr.h"

namespace AllTrade {
    namespace NPTradeCenter {

        TradeListManager::TradeListManager()
        {

        }

        TradeListManager::~TradeListManager()
        {

        }

        AllTrade::NPTradeCenter::TradeHrPtr TradeListManager::createTradeHr(const TradeInfoPtr& trade_ptr, const OrderInfoPtr& order_ptr, const UserIDType use_id)
        {
            assert(trade_ptr);
            TradeHrPtr trade_hr_ptr(nullptr);
//             switch (trade_ptr->commodity_type_)
//             {
//             case AllTrade::CommodityTypeType::COMMODITY_TYPE_STOCK:
//                 trade_hr_ptr = std::make_shared<StockTradeHandler>(std::dynamic_pointer_cast<StockTradeInfo>(trade_ptr), use_id);
//                 TaskMsgOrderManager::instance()->handleTradeCbk(trade_hr_ptr, order_ptr);
//                 break;
//             case AllTrade::CommodityTypeType::COMMODITY_TYPE_FUTURE_F:
//                 trade_hr_ptr = std::make_shared<ForeignFutureTradeHandler>(std::dynamic_pointer_cast<ForeignFutureTradeInfo>(trade_ptr), use_id);
//                 TaskMsgOrderManager::instance()->handleTradeCbk(trade_hr_ptr, order_ptr);
//                 break;
//             case AllTrade::CommodityTypeType::COMMODITY_TYPE_FUTURE_C:
//                 trade_hr_ptr = std::make_shared<ChinaFutureTradeHandler>(std::dynamic_pointer_cast<ChinaFutureTradeInfo>(trade_ptr), use_id);
//                 TaskMsgOrderManager::instance()->handleTradeCbk(trade_hr_ptr, order_ptr);
//                 break;
//             default:
//                 assert(0);
//                 break;
//             }
            return trade_hr_ptr;
        }

    }
}