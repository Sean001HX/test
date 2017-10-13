/*************************************************
Copyright (C), 2017, HX Tech Co., Ltd.
File name:      handler_taskmsg.h
Author:			XuYC
Version:
Date:
Description:    �ṩ�˻��µ������߳�������Ϣ����,�Լ�������ʵ��/ģ�⽻���߳�������Ϣ����
*************************************************/
#ifndef __TRADE_TASK_H__
#define __TRADE_TASK_H__

#include "define/struct_declare.h"
#include "trade_handler_declare.h"
#include "define/params_declare.h"

namespace AllTrade{
    namespace NPTradeCenter {

        // �û�����������
        namespace UserOperator{
            // �����µ�ί����Ϣ������
            class HandlerOrderTaskMsg
            {
            public:
                HandlerOrderTaskMsg(const OrderHrPtr& order_hr_ptr, bool needRecode);
                void operator()();

            private:
                OrderHrPtr         m_order_hr_ptr;
                bool               m_needRecode;
            };

            // ������ί����Ϣ������
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

        // ����ϵͳ�ص�������
        namespace TransactionOperator{

            // ����ί���ύ��Ϣ������
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

            // ����״̬�ı���Ϣ������
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

            // ������ί����Ϣ������
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

            // ����ɽ���Ϣ������
            class HandlerTradeCbkTaskMsg
            {
            public:
                HandlerTradeCbkTaskMsg(const TradeInfoPtr& trade_info_ptr, const UserIDType use_id);
                void operator()();

            private:
                TradeInfoPtr    m_trade_info_ptr;
                UserIDType      m_use_id;
            };

            // ����ֲ���Ϣ������
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