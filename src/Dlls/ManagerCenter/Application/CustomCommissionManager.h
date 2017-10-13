/*************************************************
Copyright (C), 2017, HX Tech Co., Ltd.
File name:      CustomCommissionManager.h
Author:			XuYC
Version:
Date:
Description:    �ṩ�û��Զ���Ӷ����ȡ����ӿ�
*************************************************/
#ifndef __CUSTOMCOMMISSIONMANAGER_H__
#define __CUSTOMCOMMISSIONMANAGER_H__

#include "utility/instance_shared_from_this.h"
#include "define/params_declare.h"
#include "define/struct_declare.h"

namespace AllTrade {
    namespace NPMgrCenter {

        class CustomCommissionManager : public CommonTools::instance_shared_from_this<CustomCommissionManager>
        {
        public: 
            CustomCommissionManager();
            ~CustomCommissionManager();

            ErrorCodeType addTradeInfo(const NPTradeCenter::TradeInfoPtr& trade_ptr);

            
        };

    }
}
#endif