/*************************************************
Copyright (C), 2017, HX Tech Co., Ltd.
File name:      TcpCallBack.h
Author:			XuYC
Version:
Date:
Description:    实盘交易及回调接口
*************************************************/

#ifndef __TCP_CALL_BACK_H__
#define __TCP_CALL_BACK_H__

#include "include/StockApiManager/StockApiManager.h"
#include "../../Application/trade_handler_declare.h"

namespace AllTrade{
    namespace NPTradeCenter {
        // 实盘交易模块
        class TcpCallBack
            : public StockApiManager::StockApiServerCallBack
        {
        public:
            TcpCallBack();
            ~TcpCallBack();
 
        public:
            //  下单请求
            bool ReqOrderInsert(const char *fundreal_name, const ContractCodeType& cont_code, const OrderHrPtr& order_hr_ptr, bool isXSHG);
            //  撤单请求
            bool ReqCancelOrder(const char *fundreal_name, const ContractCodeType& cont_code, const OrderHrPtr& order_hr_ptr, bool isXSHG);

        protected:
            // 登录请求回调
            void OnRealAccountTradeLogin(const char *real_name, bool ok) override;
            //  下单返回
            void OnOrderInsert(const char *real_name, const ContractCodeType contract_code, const StockOrderPtr& orderInfo) override;
            //  撤单返回
            void OnOrderCancel(const char *real_name, const ContractCodeType contract_code, const OrderInfoPtr& order_ptr) override;
            //  委托状态更新返回
            void OnOrderStatusUpdate(const char *real_name, const ContractCodeType contract_code, const StockOrderPtr& orderInfo) override;
            //  成交信息返回
            void OnTradeInfo(const char *real_name, const ContractCodeType contract_code, const StockTradePtr& tradeInfo) override;

        private:
            StockApiManager::StockApiServerInterface* m_api_interface;

        };

    }
}

#endif