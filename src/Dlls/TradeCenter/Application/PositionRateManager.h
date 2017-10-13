/*************************************************
Copyright (C), 2017, HX Tech Co., Ltd.
File name:      PositionRateManager.h
Author:			XuYC
Version:
Date:
Description:    提供禁止交易规则管理接口
*************************************************/
#ifndef __POSITIONRATEEMANAGER_H__
#define __POSITIONRATEEMANAGER_H__

#include <vector>

#include "utility/instance_shared_from_this.h"
#include "define/params_declare.h"
#include "define/struct_declare.h"

namespace AllTrade {
    namespace NPTradeCenter {

        class PositionRateManager : public CommonTools::instance_shared_from_this<PositionRateManager>
        {
        public:
            PositionRateManager();
            ~PositionRateManager();

            // 持仓比例相关
            std::vector<AllTrade::NPTradeCenter::SPositionRatePtr> getAllPositionRateStatus();
            ErrorCodeType updatePositionRateStatus(const AllTrade::NPTradeCenter::SPositionRatePtr& ptr);

            ErrorCodeType canTrade(const UserIDType user_id, const ContractIDType contract_id, YDouble order_freeze_money);
        };

    }
}
#endif