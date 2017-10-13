#include <assert.h>
#include "chinafutureservermgr.h"
#include "define/struct_extern.h"
#include "../Handler/orderhandler.h"

namespace AllTrade{
    namespace NPTradeCenter {

        ChinaFutureServerMgr::ChinaFutureServerMgr()
            : ServerMgrBase(CommodityTypeType::COMMODITY_TYPE_FUTURE_C)
        {

        }

        ChinaFutureServerMgr::~ChinaFutureServerMgr()
        {

        }
    }
}