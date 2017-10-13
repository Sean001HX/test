/*************************************************
Copyright (C), 2017, HX Tech Co., Ltd.
File name:      BlackWhiteManager.h
Author:			XuYC
Version:
Date:
Description:    提供黑白名单管理接口
*************************************************/
#ifndef __BLACKWHITEMANAGER_H__
#define __BLACKWHITEMANAGER_H__

#include <map>

#include "utility/instance_shared_from_this.h"
#include "define/params_declare.h"

namespace AllTrade {
    namespace NPMgrCenter {

        class BlackWhiteManager :public CommonTools::instance_shared_from_this<BlackWhiteManager>
        {
        public:
            BlackWhiteManager();
            ~BlackWhiteManager();

            void addStockBlackWhite(const AllTrade::ContractIDType contract_id);
            ErrorCodeType updateStockBlackWhiteStatus(const AllTrade::ContractIDType contract_id, bool isBlack);
            std::map<PContractIDType, bool> getAllStockBlackWhiteStatus();

            ErrorCodeType canTradeContract(AllTrade::CommodityTypeType commodity_type, const AllTrade::ExchangeIDType exchange_id, const AllTrade::ContractIDType contract_id) const;
        };

    }
}
#endif