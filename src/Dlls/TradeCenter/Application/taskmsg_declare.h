/*************************************************
Copyright (C), 2017, HX Tech Co., Ltd.
File name:      trade_msg_declare.h
Author:			XuYC
Version:
Date:
Description:    �ṩ��Ϣ����
*************************************************/
#ifndef __TRADE_MSG_DECLARE_H__
#define __TRADE_MSG_DECLARE_H__

#include <loki/Visitor.h>		// ʹ����Loki�е�cyclic visitorģ��
#include <loki/TypelistMacros.h>
#include <loki/Functor.h>
#include <loki/AssocVector.h>


namespace AllTrade {
    namespace NPTradeCenter {

        class TaskCommMsg;
        typedef std::shared_ptr<TaskCommMsg>                TaskCommMsgPtr;

        // �û�����������
        namespace UserOperator {

            class UserTaskCommMsg;
            typedef std::shared_ptr<UserTaskCommMsg>        UserTaskCommMsgPtr;

            class OrderTaskMsg;
            class CancelOrderTaskMsg;

        }

        // ����ϵͳ�ص�������
        namespace TransactionOperator {

            class TransTaskCommMsg;
            typedef std::shared_ptr<TransTaskCommMsg>        TransTaskCommMsgPtr;

            class OrderInsertCbkTaskMsg;
            class OrderChangeCbkTaskMsg;
            class CancelOrderCbkTaskMsg;
            class TradeMatchCbkTaskMsg;
        }

        // ������������
        namespace ServerOperator {

            class ServerTaskCommMsg;
            typedef std::shared_ptr<ServerTaskCommMsg>        ServerTaskCommMsgPtr;

            class PositionTaskMsg;
            class RiskTaskMsg;
        }


        typedef Loki::CyclicVisitor
            <
            void,
            LOKI_TYPELIST_9(TaskCommMsg, UserOperator::OrderTaskMsg, UserOperator::CancelOrderTaskMsg, TransactionOperator::OrderInsertCbkTaskMsg, TransactionOperator::OrderChangeCbkTaskMsg
                          , TransactionOperator::CancelOrderCbkTaskMsg, TransactionOperator::TradeMatchCbkTaskMsg, ServerOperator::PositionTaskMsg, ServerOperator::RiskTaskMsg)
            >
            TaskMsgVisitor;

        //////////////////////////////////////////////////////////////////////////
        // Task message nop visitor 
        class NopTaskMsgVisitor : public TaskMsgVisitor
        {
        public:
            virtual void Visit(TaskCommMsg&) { assert(0); }
            virtual void Visit(UserOperator::OrderTaskMsg&) { assert(0); }
            virtual void Visit(UserOperator::CancelOrderTaskMsg&) { assert(0); }
            virtual void Visit(TransactionOperator::OrderInsertCbkTaskMsg&) { assert(0); }
            virtual void Visit(TransactionOperator::OrderChangeCbkTaskMsg&) { assert(0); }
            virtual void Visit(TransactionOperator::CancelOrderCbkTaskMsg&) { assert(0); }
            virtual void Visit(TransactionOperator::TradeMatchCbkTaskMsg&) { assert(0); }
            virtual void Visit(ServerOperator::PositionTaskMsg&) { assert(0); }
            virtual void Visit(ServerOperator::RiskTaskMsg&) { assert(0); }
        };

    }
}
#endif