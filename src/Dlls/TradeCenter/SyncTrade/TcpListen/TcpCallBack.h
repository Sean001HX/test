/*************************************************
Copyright (C), 2017, HX Tech Co., Ltd.
File name:      TcpCallBack.h
Author:			XuYC
Version:
Date:
Description:    ʵ�̽��׼��ص��ӿ�
*************************************************/

#ifndef __TCP_CALL_BACK_H__
#define __TCP_CALL_BACK_H__

#include "include/StockApiManager/StockApiManager.h"
#include "../../Application/trade_handler_declare.h"

namespace AllTrade{
    namespace NPTradeCenter {
        // ʵ�̽���ģ��
        class TcpCallBack
            : public StockApiManager::StockApiServerCallBack
        {
        public:
            TcpCallBack();
            ~TcpCallBack();
 
        public:
            //  �µ�����
            bool ReqOrderInsert(const char *fundreal_name, const ContractCodeType& cont_code, const OrderHrPtr& order_hr_ptr, bool isXSHG);
            //  ��������
            bool ReqCancelOrder(const char *fundreal_name, const ContractCodeType& cont_code, const OrderHrPtr& order_hr_ptr, bool isXSHG);

        protected:
            // ��¼����ص�
            void OnRealAccountTradeLogin(const char *real_name, bool ok) override;
            //  �µ�����
            void OnOrderInsert(const char *real_name, const ContractCodeType contract_code, const StockOrderPtr& orderInfo) override;
            //  ��������
            void OnOrderCancel(const char *real_name, const ContractCodeType contract_code, const OrderInfoPtr& order_ptr) override;
            //  ί��״̬���·���
            void OnOrderStatusUpdate(const char *real_name, const ContractCodeType contract_code, const StockOrderPtr& orderInfo) override;
            //  �ɽ���Ϣ����
            void OnTradeInfo(const char *real_name, const ContractCodeType contract_code, const StockTradePtr& tradeInfo) override;

        private:
            StockApiManager::StockApiServerInterface* m_api_interface;

        };

    }
}

#endif