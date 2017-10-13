/*************************************************
Copyright (C), 2017, HX Tech Co., Ltd.
File name:      CustomStockManager.h
Author:			XuYC
Version:
Date:
Description:    提供自选股管理接口
*************************************************/
#ifndef __CUSTOMSTOCKMANAGER_H__
#define __CUSTOMSTOCKMANAGER_H__

#include <map>
#include <vector>

#include "utility/instance_shared_from_this.h"
#include "define/params_declare.h"

namespace AllTrade {
    namespace NPMgrCenter {

        class CustomStockManager :public CommonTools::instance_shared_from_this<CustomStockManager>
        {
        public:
            CustomStockManager();
            ~CustomStockManager();

            AllTrade::ErrorCodeType addCustomStock(const AllTrade::UserIDType user_id, const AllTrade::ContractIDType contract_id);
            AllTrade::ErrorCodeType removeCustomStock(const AllTrade::UserIDType user_id, const AllTrade::ContractIDType contract_id);
            std::vector<AllTrade::PContractIDType> getAllCustomStock(const AllTrade::UserIDType user_id);
            std::map<AllTrade::PUserIDType, std::vector<AllTrade::PContractIDType>> getAllCustomStock();
        };

    }
}
#endif