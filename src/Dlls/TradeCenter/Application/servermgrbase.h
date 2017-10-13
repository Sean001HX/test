/*************************************************
Copyright (C), 2017, HX Tech Co., Ltd.
File name:      servermgrbase.h
Author:			XuYC
Version:
Date:
Description:    �ṩ���ײ����Ļ���ӿ�,�˴�������Ϊͳһ��������ȡ
                �ṩͳһ���źŴ������,����Ϣ�ַ�
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

            // ������Ʒ���ͻ�ȡ��Ӧָ��
            static TradeManagerPtr getTradeManagerPtr(CommodityTypeType commodity_type);

            // ��������
            virtual void updateQuote(const QuoteInfoPtr& quote_ptr, const NPMgrCenter::SExchangeCPtr& exchange_ptr, const NPMgrCenter::SContractCPtr& contract_ptr) = 0;

            // ����ɽ�
            virtual void dealTradeMsg(const TradeInfoPtr& trade_info_ptr, const UserIDType use_id) = 0;


        protected:
            CommodityTypeType   m_product_type;
      };

    }
}
#endif