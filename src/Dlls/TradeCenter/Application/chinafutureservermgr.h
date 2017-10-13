/*************************************************
Copyright (C), 2017, HX Tech Co., Ltd.
File name:      chinafutureservermgr.h
Author:			XuYC
Version:
Date:
Description:    提供内盘期货交易操作接口
*************************************************/
#ifndef __CHINA_FUTURE_TRADE_MGR_H__
#define __CHINA_FUTURE_TRADE_MGR_H__

#include "utility/instance_shared_from_this.h"
#include "servermgrbase.h"
#include <assert.h>

namespace AllTrade{
    namespace NPTradeCenter {
        class ChinaFutureServerMgr
            : public CommonTools::instance_shared_from_this<ChinaFutureServerMgr>
            , public ServerMgrBase
        {
        public:
            ChinaFutureServerMgr();
            ~ChinaFutureServerMgr();
            void updateQuote(const QuoteInfoPtr& quote_ptr, const NPMgrCenter::SExchangeCPtr& exchange_ptr, const NPMgrCenter::SContractCPtr& contract_ptr) override { assert(0); }
            void dealTradeMsg(const TradeInfoPtr& trade_info_ptr, const UserIDType use_id) override { assert(0); }
        private:

        };
    }
}
#endif