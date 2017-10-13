/*************************************************
Copyright (C), 2017, HX Tech Co., Ltd.
File name:      taskmsg.h
Author:			XuYC
Version:
Date:
Description:    提供线程任务消息访问传递接口,为后期扩展预留位置
                该模块可改为直接面向接口,直接解析/发送json; 也可仅用做临时中转
*************************************************/
#ifndef __TRADE_MSG_H__
#define __TRADE_MSG_H__

#include "define/struct_declare.h"
#include "define/params_declare.h"
#include "trade_handler_declare.h"
#include "taskmsg_declare.h"

namespace AllTrade{
    namespace NPTradeCenter {

        class TaskCommMsg
        {
        public:
            TaskCommMsg();

            virtual void Accept(NopTaskMsgVisitor&) { assert(0); }


            // 获取商品类型
            virtual CommodityTypeType getCommodityType() const = 0;

            // 获取错误码
            ErrorCodeType getErrorCode() const;
            // 设置错误码
            void setErrorCode(ErrorCodeType errcode);

        private:
            ErrorCodeType m_errcode;
        };


        // 用户操作任务类
        namespace UserOperator{

            class UserTaskCommMsg : public TaskCommMsg, public std::enable_shared_from_this<UserTaskCommMsg>
            {
            protected:
                UserTaskCommMsg();

            public:
                // 创建提交委托消息
                static UserTaskCommMsgPtr createOrderMsg(const OrderHrPtr& order_hr_ptr);
                // 创建撤单消息
                static UserTaskCommMsgPtr createCancelOrderMsg(const OrderHrPtr& order_hr_ptr);
            };

            // 提交委托消息
            class OrderTaskMsg : public UserTaskCommMsg
            {
            public:
                OrderTaskMsg();
                OrderTaskMsg(const OrderHrPtr& order_hr_ptr);

                OrderHrPtr getOrderHrPtr() const{
                    return m_order_hr_ptr;
                }

                CommodityTypeType getCommodityType() const override;

                LOKI_DEFINE_CYCLIC_VISITABLE(NopTaskMsgVisitor)

            private:
                OrderHrPtr      m_order_hr_ptr;
            };

            // 撤单消息
            class CancelOrderTaskMsg : public UserTaskCommMsg
            {
            public:
                CancelOrderTaskMsg();
                CancelOrderTaskMsg(const OrderHrPtr& order_hr_ptr);

                OrderHrPtr getOrderHrPtr() const{
                    return m_order_hr_ptr;
                }

                CommodityTypeType getCommodityType() const override;

                LOKI_DEFINE_CYCLIC_VISITABLE(NopTaskMsgVisitor)

            private:
                OrderHrPtr      m_order_hr_ptr;
            };

        }

        // 交易系统回调任务类
        namespace TransactionOperator {

            class TransTaskCommMsg : public TaskCommMsg, public std::enable_shared_from_this<TransTaskCommMsg>
            {
            protected:
                TransTaskCommMsg();
            public:

                // 创建提交委托回调消息
                static TransTaskCommMsgPtr createOrderMsg(const OrderInfoPtr& order_ptr, const UserIDType use_id, NPMgrCenter::SOnlineAccountPtr user_online = nullptr);
                // 创建委托状态改变回调消息
                static TransTaskCommMsgPtr createOrderChangeMsg(const OrderInfoPtr& order_ptr, const UserIDType use_id);
                // 创建撤销委托回调消息
                static TransTaskCommMsgPtr createCancelOrderMsg(const OrderInfoPtr& order_ptr, const UserIDType use_id, NPMgrCenter::SOnlineAccountPtr user_online = nullptr);
                // 创建成交回调消息
                static TransTaskCommMsgPtr createTradeMsg(const TradeInfoPtr& trade_info_ptr, const UserIDType use_id);
            };

            // 委托提交回调消息
            class OrderInsertCbkTaskMsg : public TransTaskCommMsg
            {
            public:
                OrderInsertCbkTaskMsg();
                OrderInsertCbkTaskMsg(const OrderInfoPtr& order_ptr, const UserIDType use_id, NPMgrCenter::SOnlineAccountPtr user_online = nullptr);

                OrderInfoPtr getOrderInfoPtr() const{
                    return m_order_ptr;
                }

                PUserIDType getUserID() const{
                    return m_use_id;
                }

                NPMgrCenter::SOnlineAccountPtr getOpUserLoginInfo() const{
                    return m_user_online;
                }

                CommodityTypeType getCommodityType() const override;

                LOKI_DEFINE_CYCLIC_VISITABLE(NopTaskMsgVisitor)

            private:
                OrderInfoPtr                    m_order_ptr;
                UserIDType                      m_use_id;
                NPMgrCenter::SOnlineAccountPtr  m_user_online;
            };

            // 委托状态改变回调消息
            class OrderChangeCbkTaskMsg : public TransTaskCommMsg
            {
            public:
                OrderChangeCbkTaskMsg();
                OrderChangeCbkTaskMsg(const OrderInfoPtr& order_ptr, const UserIDType use_id);

                OrderInfoPtr getOrderInfoPtr() const{
                    return m_order_ptr;
                }

                PUserIDType getUserID() const{
                    return m_use_id;
                }

                CommodityTypeType getCommodityType() const override;

                LOKI_DEFINE_CYCLIC_VISITABLE(NopTaskMsgVisitor)

            private:
                OrderInfoPtr        m_order_ptr;
                UserIDType          m_use_id;
            };

            // 撤单委托回调
            class CancelOrderCbkTaskMsg : public TransTaskCommMsg
            {
            public:
                CancelOrderCbkTaskMsg();
                CancelOrderCbkTaskMsg(const OrderInfoPtr& order_ptr, const UserIDType use_id, NPMgrCenter::SOnlineAccountPtr user_online = nullptr);

                OrderInfoPtr getOrderInfoPtr() const{
                    return m_order_ptr;
                }

                PUserIDType getUserID() const{
                    return m_use_id;
                }

                NPMgrCenter::SOnlineAccountPtr getOpUserLoginInfo() const{
                    return m_user_online;
                }

                CommodityTypeType getCommodityType() const override;

                LOKI_DEFINE_CYCLIC_VISITABLE(NopTaskMsgVisitor)

            private:
                OrderInfoPtr                    m_order_ptr;
                UserIDType                      m_use_id;
                NPMgrCenter::SOnlineAccountPtr  m_user_online;
            };

            // 成交消息
            class TradeMatchCbkTaskMsg : public TransTaskCommMsg
            {
            public:
                TradeMatchCbkTaskMsg();
                TradeMatchCbkTaskMsg(const TradeInfoPtr& trade_info_ptr, const UserIDType use_id);

                CommodityTypeType getCommodityType() const override;

                TradeInfoPtr getTradeInfoPtr() const{
                    return m_trade_info_ptr;
                }

                PUserIDType getUserID() const{
                    return m_use_id;
                }

                LOKI_DEFINE_CYCLIC_VISITABLE(NopTaskMsgVisitor)

            private:
                TradeInfoPtr        m_trade_info_ptr;
                UserIDType          m_use_id;
            };
        }

        // 服务器任务类
        namespace ServerOperator
        {
            class ServerTaskCommMsg : public TaskCommMsg, public std::enable_shared_from_this<ServerTaskCommMsg>
            {
            protected:
                ServerTaskCommMsg();

            public:
                // 创建持仓改变消息
                static ServerTaskCommMsgPtr createPositionMsg(const UserIDType user_id, const PositionInfoPtr& position_ptr);
                // 创建风控消息
                static ServerTaskCommMsgPtr createRiskMsg(CommodityTypeType commod_type, const UserIDType user_id, const DateTimeType date_time, RiskControlType rc_type, const RemarkTextType remark_text);
            };

            // 持仓改变消息
            class PositionTaskMsg : public ServerTaskCommMsg
            {
            public:
                PositionTaskMsg(const UserIDType user_id, const PositionInfoPtr& position_ptr);

                CommodityTypeType getCommodityType() const override;

                const PUserIDType getUserID() const{
                    return m_user_id;
                }
                PositionInfoPtr getPositionInfoPtr() const{
                    return m_position_ptr;
                }

                LOKI_DEFINE_CYCLIC_VISITABLE(NopTaskMsgVisitor)

            private:
                UserIDType          m_user_id;
                PositionInfoPtr     m_position_ptr;
            };

            // 风控消息
            class RiskTaskMsg : public ServerTaskCommMsg
            {
            public:
                RiskTaskMsg(CommodityTypeType commod_type, const UserIDType user_id, const DateTimeType date_time, RiskControlType rc_type, const RemarkTextType remark_text);

                CommodityTypeType getCommodityType() const override;

                const PUserIDType getUserID() const{
                    return m_user_id;
                }
                const PDateTimeType getDateTime() const{
                    return m_date_time;
                }
                RiskControlType getRiskControlType() const{
                    return m_rc_type;
                }
                const PRemarkTextType getRemarkText() const{
                    return m_remark_text;
                }


                LOKI_DEFINE_CYCLIC_VISITABLE(NopTaskMsgVisitor)

            private:
                CommodityTypeType   m_commod_type;
                UserIDType          m_user_id;
                DateTimeType        m_date_time;
                RiskControlType     m_rc_type;
                RemarkTextType      m_remark_text;
            };
        }
    }
}
#endif