#include <assert.h>
#include "foreignfutureservermgr.h"
#include "define/struct_extern.h"
#include "../Handler/orderhandler.h"
// #include "../Handler/cancelorderhandler.h"

namespace AllTrade{
    namespace NPTradeCenter {
        ForeignFutureServerMgr::ForeignFutureServerMgr()
            : ServerMgrBase(CommodityTypeType::COMMODITY_TYPE_FUTURE_F)
        {

        }

        ForeignFutureServerMgr::~ForeignFutureServerMgr()
        {

        }
    }
}