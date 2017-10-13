/*************************************************
Copyright (C), 2017, HX Tech Co., Ltd.
File name:      taskmsg_order_mgr.h
Author:			XuYC
Version:
Date:
Description:    提供委托管理调度接口
                1. 提供面向账户下单线程池管理;
                2. 提供面向系统下单回调线程池管理;
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
            // 处理下单委托信息, needRecode:失败时是否需要记入数据库
            void handlePlaceOrder(const OrderInfoPtr& order_ptr, const UserIDType use_id, const NPMgrCenter::SOnlineAccountPtr& user_online, bool needRecode);
            // 处理撤单委托信息
            void handleCancelOrder(const UserIDType use_id, const OrderStreamType order_stream, bool needRecode, bool forceClose);

            // 处理委托提交回调消息
            void handleOrderInsertCbk(const OrderInfoPtr& order_ptr, const UserIDType use_id, const NPMgrCenter::SOnlineAccountPtr& user_online = nullptr);
            // 处理委托状态改变回调消息
            void handleOrderChangeCbk(const OrderInfoPtr& order_ptr, const UserIDType use_id);
            // 处理委托撤单回调消息
            void handleCancelOrderCbk(const OrderInfoPtr& order_ptr, const UserIDType use_id, const NPMgrCenter::SOnlineAccountPtr& user_online = nullptr);
            // 处理成交回调消息
            void handleTradeCbk(const TradeInfoPtr& trade_info_ptr, const UserIDType use_id);

            // 处理持仓改变信息()目前仅供界面显示
            void handlePositionCbk(const UserIDType user_id, const PositionInfoPtr& position_ptr, const TradeInfoPtr& trade_info_ptr);

        public:
            // 注册委托提交通知回调通知
            void setOrderInsertCbk(const OrderInsertCbk& fun){
                m_order_insert_cbk = fun;
            }
            // 注册撤单回调通知回调通知
            void setOrderCancelCbk(const CancelOrderCbk& fun){
                m_order_cancel_cbk = fun;
            }
            // 注册委托改变通知回调通知
            void setOrderChangeCbk(const OrderChangeCbk& fun){
                m_order_change_cbk = fun;
            }
            // 注册成交回调通知回调通知
            void setTradeCbk(const TradeCbk& fun){
                m_trade_cbk = fun;
            }
            // 注册持仓回调通知回调通知
            void setPositionCbk(const PositionCbk& fun){
                m_position_cbk = fun;
            }
            // 注册风控回调通知
            void setRiskControlCbk(const RiskControlCbk& fun){
                m_rc_cbk = fun;
            }

            // 返回前置机信息
            void sendMsgToFront(const TaskCommMsgPtr& msg_ptr);
            // 发出信号至交易模块
            void sendMsgToServer(const TaskCommMsgPtr& msg_ptr);

        protected:
            // 前置机对接收到的消息进行处理
            class FrontRecvMsgVisitor : public NopTaskMsgVisitor
            {
            public:
                FrontRecvMsgVisitor(TaskMsgOrderManager* pParent) : m_pParent(pParent){}
                ~FrontRecvMsgVisitor() {}

                // 提交未通过本地判断返回通知,通过的情况下无需返回
                virtual void Visit(UserOperator::OrderTaskMsg& msg);
                // 提交未通过本地判断返回通知,通过的情况下无需返回
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

            // 交易模块对接收到的消息进行处理
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
            WorkQueue           m_work_queue_user;  // 用户交互线程池
            WorkQueue           m_work_queue_trans; // 后台交易线程池

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