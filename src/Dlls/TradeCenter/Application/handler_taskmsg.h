/*************************************************
Copyright (C), 2017, HX Tech Co., Ltd.
File name:      handler_taskmsg.h
Author:			XuYC
Version:
Date:
Description:    提供账户下单撤单线程任务消息处理,以及服务器实盘/模拟交易线程任务消息处理
*************************************************/
#ifndef __TRADE_TASK_H__
#define __TRADE_TASK_H__

#include "define/struct_declare.h"
#include "trade_handler_declare.h"
#include "define/params_declare.h"

namespace AllTrade{
    namespace NPTradeCenter {

        // 用户操作任务类
        namespace UserOperator{
            // 处理下单委托消息任务类
            class HandlerOrderTaskMsg
            {
            public:
                HandlerOrderTaskMsg(const OrderHrPtr& order_hr_ptr, bool needRecode);
                void operator()();

            private:
                OrderHrPtr         m_order_hr_ptr;
                bool               m_needRecode;
            };

            // 处理撤单委托消息任务类
            class HandlerCancelOrderTaskMsg
            {
            public:
                HandlerCancelOrderTaskMsg(const OrderHrPtr& order_hr_ptr, bool needRecode, bool forceClose);
                void operator()();

            private:
                OrderHrPtr          m_order_hr_ptr;
                bool                m_needRecode;
                bool                m_forceClose;
            };
        }

        // 交易系统回调任务类
        namespace TransactionOperator{

            // 处理委托提交消息任务类
            class HandlerOrderInsertCbkTaskMsg
            {
            public:
                HandlerOrderInsertCbkTaskMsg(const OrderInfoPtr& order_ptr, const UserIDType use_id, NPMgrCenter::SOnlineAccountPtr user_online = nullptr);
                void operator()();

            private:
                OrderInfoPtr                    m_order_ptr;
                UserIDType                      m_use_id;
                NPMgrCenter::SOnlineAccountPtr  m_user_online;
            };

            // 处理状态改变消息任务类
            class HandlerOrderChangeCbkTaskMsg
            {
            public:
                HandlerOrderChangeCbkTaskMsg(const OrderInfoPtr& order_ptr, const UserIDType use_id, NPMgrCenter::SOnlineAccountPtr user_online = nullptr);
                void operator()();

            private:
                OrderInfoPtr                    m_order_ptr;
                UserIDType                      m_use_id;
                NPMgrCenter::SOnlineAccountPtr  m_user_online;
            };

            // 处理撤销委托消息任务类
            class HandlerCancelOrderCbkTaskMsg
            {
            public:
                HandlerCancelOrderCbkTaskMsg(const OrderInfoPtr& order_ptr, const UserIDType use_id, NPMgrCenter::SOnlineAccountPtr user_online = nullptr);
                void operator()();

            private:
                OrderInfoPtr                    m_order_ptr;
                UserIDType                      m_use_id;
                NPMgrCenter::SOnlineAccountPtr  m_user_online;
            };

            // 处理成交消息任务类
            class HandlerTradeCbkTaskMsg
            {
            public:
                HandlerTradeCbkTaskMsg(const TradeInfoPtr& trade_info_ptr, const UserIDType use_id);
                void operator()();

            private:
                TradeInfoPtr    m_trade_info_ptr;
                UserIDType      m_use_id;
            };

            // 处理持仓消息任务类
            class HandlerPositionCbkTaskMsg
            {
            public:
                HandlerPositionCbkTaskMsg(const UserIDType use_id, const PositionInfoPtr& position_info_ptr, const TradeInfoPtr& trade_info_ptr);
                void operator()();

            private:
                PositionInfoPtr     m_position_info_ptr;
                UserIDType          m_use_id;
                TradeInfoPtr        m_trde_info_ptr;
            };
        }
    }
}
#endif