/*************************************************
Copyright (C), 2017, HX Tech Co., Ltd.
File name:      taskmsg_order_mgr.h
Author:			XuYC
Version:
Date:
Description:    �ṩί�й�����Ƚӿ�
                1. �ṩ�����˻��µ��̳߳ع���;
                2. �ṩ����ϵͳ�µ��ص��̳߳ع���;
*************************************************/
#ifndef __TASKMSG_ORDER_MGR_H__
#define __TASKMSG_ORDER_MGR_H__

#include <functional>
#include "utility/instance_shared_from_this.h"
#include "utility/workqueue.h"
#include <vector>
#include "define/struct_declare.h"
#include "define/params_declare.h"
#include "taskmsg_declare.h"

namespace AllTrade{
    namespace NPTradeCenter {

        class TaskMsgOrderManager : public CommonTools::instance_shared_from_this<TaskMsgOrderManager>
        {
        public:
            typedef std::function<void(ErrorCodeType errcode, const UserIDType user_id, const OrderInfoPtr& order_ptr, const NPMgrCenter::SOnlineAccountPtr& user_online)>  OrderInsertCbk;
            typedef std::function<void(ErrorCodeType errcode, const UserIDType user_id, const OrderInfoPtr& order_ptr, const NPMgrCenter::SOnlineAccountPtr& user_online)>  CancelOrderCbk;
            typedef std::function<void(ErrorCodeType errcode, const UserIDType user_id, const OrderInfoPtr& order_ptr)>  OrderChangeCbk;
            typedef std::function<void(ErrorCodeType errcode, const UserIDType user_id, const TradeInfoPtr& trade_ptr)>  TradeCbk;
            typedef std::function<void(ErrorCodeType errcode, const UserIDType user_id, const PositionInfoPtr& position_ptr)>  PositionCbk;
            typedef std::function<void(const UserIDType user_id, const DateTimeType date_time, RiskControlType rc_type, const RemarkTextType remark_text)>  RiskControlCbk;

        public:
            TaskMsgOrderManager();
            ~TaskMsgOrderManager();

        public:
            // �����µ�ί����Ϣ, needRecode:ʧ��ʱ�Ƿ���Ҫ�������ݿ�
            void handlePlaceOrder(const OrderInfoPtr& order_ptr, const UserIDType use_id, const NPMgrCenter::SOnlineAccountPtr& user_online, bool needRecode);
            // ������ί����Ϣ
            void handleCancelOrder(const UserIDType use_id, const OrderStreamType order_stream, bool needRecode, bool forceClose);

            // ����ί���ύ�ص���Ϣ
            void handleOrderInsertCbk(const OrderInfoPtr& order_ptr, const UserIDType use_id, const NPMgrCenter::SOnlineAccountPtr& user_online = nullptr);
            // ����ί��״̬�ı�ص���Ϣ
            void handleOrderChangeCbk(const OrderInfoPtr& order_ptr, const UserIDType use_id);
            // ����ί�г����ص���Ϣ
            void handleCancelOrderCbk(const OrderInfoPtr& order_ptr, const UserIDType use_id, const NPMgrCenter::SOnlineAccountPtr& user_online = nullptr);
            // ����ɽ��ص���Ϣ
            void handleTradeCbk(const TradeInfoPtr& trade_info_ptr, const UserIDType use_id);

            // ����ֲָı���Ϣ()Ŀǰ����������ʾ
            void handlePositionCbk(const UserIDType user_id, const PositionInfoPtr& position_ptr, const TradeInfoPtr& trade_info_ptr);

        public:
            // ע��ί���ύ֪ͨ�ص�֪ͨ
            void setOrderInsertCbk(const OrderInsertCbk& fun){
                m_order_insert_cbk = fun;
            }
            // ע�᳷���ص�֪ͨ�ص�֪ͨ
            void setOrderCancelCbk(const CancelOrderCbk& fun){
                m_order_cancel_cbk = fun;
            }
            // ע��ί�иı�֪ͨ�ص�֪ͨ
            void setOrderChangeCbk(const OrderChangeCbk& fun){
                m_order_change_cbk = fun;
            }
            // ע��ɽ��ص�֪ͨ�ص�֪ͨ
            void setTradeCbk(const TradeCbk& fun){
                m_trade_cbk = fun;
            }
            // ע��ֲֻص�֪ͨ�ص�֪ͨ
            void setPositionCbk(const PositionCbk& fun){
                m_position_cbk = fun;
            }
            // ע���ػص�֪ͨ
            void setRiskControlCbk(const RiskControlCbk& fun){
                m_rc_cbk = fun;
            }

            // ����ǰ�û���Ϣ
            void sendMsgToFront(const TaskCommMsgPtr& msg_ptr);
            // �����ź�������ģ��
            void sendMsgToServer(const TaskCommMsgPtr& msg_ptr);

        protected:
            // ǰ�û��Խ��յ�����Ϣ���д���
            class FrontRecvMsgVisitor : public NopTaskMsgVisitor
            {
            public:
                FrontRecvMsgVisitor(TaskMsgOrderManager* pParent) : m_pParent(pParent){}
                ~FrontRecvMsgVisitor() {}

                // �ύδͨ�������жϷ���֪ͨ,ͨ������������践��
                virtual void Visit(UserOperator::OrderTaskMsg& msg);
                // �ύδͨ�������жϷ���֪ͨ,ͨ������������践��
                virtual void Visit(UserOperator::CancelOrderTaskMsg& msg);
                virtual void Visit(TransactionOperator::OrderInsertCbkTaskMsg& msg);
                virtual void Visit(TransactionOperator::OrderChangeCbkTaskMsg& msg);
                virtual void Visit(TransactionOperator::CancelOrderCbkTaskMsg& msg);
                virtual void Visit(TransactionOperator::TradeMatchCbkTaskMsg& msg);
                virtual void Visit(ServerOperator::PositionTaskMsg& msg);
                virtual void Visit(ServerOperator::RiskTaskMsg& msg);

            protected:
                TaskMsgOrderManager*	m_pParent;
            };
            friend class FrontRecvMsgVisitor;
            FrontRecvMsgVisitor      m_front_recv;

            // ����ģ��Խ��յ�����Ϣ���д���
            class ASyncRecvMsgVisitor : public NopTaskMsgVisitor
            {
            public:
                ASyncRecvMsgVisitor(TaskMsgOrderManager* pParent) : m_pParent(pParent){}
                ~ASyncRecvMsgVisitor() {}

                virtual void Visit(UserOperator::OrderTaskMsg& msg);
                virtual void Visit(UserOperator::CancelOrderTaskMsg& msg);
                virtual void Visit(TransactionOperator::OrderInsertCbkTaskMsg& msg);
                virtual void Visit(TransactionOperator::OrderChangeCbkTaskMsg& msg);
                virtual void Visit(TransactionOperator::CancelOrderCbkTaskMsg& msg);
                virtual void Visit(TransactionOperator::TradeMatchCbkTaskMsg& msg);

            protected:
                TaskMsgOrderManager*	m_pParent;
            };
            friend class ASyncRecvMsgVisitor;
            ASyncRecvMsgVisitor     m_async_recv;

        private:
            WorkQueue           m_work_queue_user;  // �û������̳߳�
            WorkQueue           m_work_queue_trans; // ��̨�����̳߳�

            static OrderInsertCbk      m_order_insert_cbk;
            static CancelOrderCbk      m_order_cancel_cbk;
            static OrderChangeCbk      m_order_change_cbk;
            static TradeCbk            m_trade_cbk;
            static PositionCbk         m_position_cbk;
            static RiskControlCbk      m_rc_cbk;

        };
    }
}
#endif