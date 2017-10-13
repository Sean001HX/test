/*************************************************
Copyright (C), 2017, HX Tech Co., Ltd.
File name:      ForbidTradeManager.h
Author:			XuYC
Version:
Date:
Description:    提供禁止交易规则管理接口
*************************************************/
#ifndef __FORBIDTRADEMANAGER_H__
#define __FORBIDTRADEMANAGER_H__

#include <vector>

#include "utility/instance_shared_from_this.h"
#include "define/params_declare.h"
#include "define/struct_declare.h"
#include "trade_handler_declare.h"

namespace AllTrade {
    namespace NPTradeCenter {

        class ForbidTradeManager : public CommonTools::instance_shared_from_this<ForbidTradeManager>
        {
        public:
            ForbidTradeManager();
            ~ForbidTradeManager();

            std::vector<SForbidTradePtr> getAllForbidTradeStatus();
            ErrorCodeType updateForbidTradeStatus(const SForbidTradePtr& ptr);

            ErrorCodeType canTrade(const QuoteHrPtr& quote, DirectType dir_type);

        };

    }
}
#endif