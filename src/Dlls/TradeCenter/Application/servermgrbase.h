/*************************************************
Copyright (C), 2017, HX Tech Co., Ltd.
File name:      servermgrbase.h
Author:			XuYC
Version:
Date:
Description:    提供交易操作的基类接口,此处操作均为统一操作的提取
                提供统一的信号处理机制,如消息分发
*************************************************/
#ifndef __TRADE_MANAGER_BASE_H__
#define __TRADE_MANAGER_BASE_H__

#include <assert.h>
#include <memory>
#include "define/struct_declare.h"
#include "define/params_declare.h"
#include "trade_handler_declare.h"
#include "taskmsg_declare.h"

namespace AllTrade{
    namespace NPTradeCenter {
        class ServerMgrBase
        {
        public:
            ServerMgrBase(CommodityTypeType product_type);
            virtual ~ServerMgrBase();

            // 根据商品类型获取对应指针
            static TradeManagerPtr getTradeManagerPtr(CommodityTypeType commodity_type);

            // 更新行情
            virtual void updateQuote(const QuoteInfoPtr& quote_ptr, const NPMgrCenter::SExchangeCPtr& exchange_ptr, const NPMgrCenter::SContractCPtr& contract_ptr) = 0;

            // 处理成交
            virtual void dealTradeMsg(const TradeInfoPtr& trade_info_ptr, const UserIDType use_id) = 0;


        protected:
            CommodityTypeType   m_product_type;
      };

    }
}
#endif