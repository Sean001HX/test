/*************************************************
Copyright (C), 2017, HX Tech Co., Ltd.
File name:      taskmsg.h
Author:			XuYC
Version:
Date:
Description:    �ṩ�߳�������Ϣ���ʴ��ݽӿ�,Ϊ������չԤ��λ��
                ��ģ��ɸ�Ϊֱ������ӿ�,ֱ�ӽ���/����json; Ҳ�ɽ�������ʱ��ת
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


            // ��ȡ��Ʒ����
            virtual CommodityTypeType getCommodityType() const = 0;

            // ��ȡ������
            ErrorCodeType getErrorCode() const;
            // ���ô�����
            void setErrorCode(ErrorCodeType errcode);

        private:
            ErrorCodeType m_errcode;
        };


        // �û�����������
        namespace UserOperator{

            class UserTaskCommMsg : public TaskCommMsg, public std::enable_shared_from_this<UserTaskCommMsg>
            {
            protected:
                UserTaskCommMsg();

            public:
                // �����ύί����Ϣ
                static UserTaskCommMsgPtr createOrderMsg(const OrderHrPtr& order_hr_ptr);
                // ����������Ϣ
                static UserTaskCommMsgPtr createCancelOrderMsg(const OrderHrPtr& order_hr_ptr);
            };

            // �ύί����Ϣ
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

            // ������Ϣ
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

        // ����ϵͳ�ص�������
        namespace TransactionOperator {

            class TransTaskCommMsg : public TaskCommMsg, public std::enable_shared_from_this<TransTaskCommMsg>
            {
            protected:
                TransTaskCommMsg();
            public:

                // �����ύί�лص���Ϣ
                static TransTaskCommMsgPtr createOrderMsg(const OrderInfoPtr& order_ptr, const UserIDType use_id, NPMgrCenter::SOnlineAccountPtr user_online = nullptr);
                // ����ί��״̬�ı�ص���Ϣ
                static TransTaskCommMsgPtr createOrderChangeMsg(const OrderInfoPtr& order_ptr, const UserIDType use_id);
                // ��������ί�лص���Ϣ
                static TransTaskCommMsgPtr createCancelOrderMsg(const OrderInfoPtr& order_ptr, const UserIDType use_id, NPMgrCenter::SOnlineAccountPtr user_online = nullptr);
                // �����ɽ��ص���Ϣ
                static TransTaskCommMsgPtr createTradeMsg(const TradeInfoPtr& trade_info_ptr, const UserIDType use_id);
            };

            // ί���ύ�ص���Ϣ
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

            // ί��״̬�ı�ص���Ϣ
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

            // ����ί�лص�
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

            // �ɽ���Ϣ
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

        // ������������
        namespace ServerOperator
        {
            class ServerTaskCommMsg : public TaskCommMsg, public std::enable_shared_from_this<ServerTaskCommMsg>
            {
            protected:
                ServerTaskCommMsg();

            public:
                // �����ֲָı���Ϣ
                static ServerTaskCommMsgPtr createPositionMsg(const UserIDType user_id, const PositionInfoPtr& position_ptr);
                // ���������Ϣ
                static ServerTaskCommMsgPtr createRiskMsg(CommodityTypeType commod_type, const UserIDType user_id, const DateTimeType date_time, RiskControlType rc_type, const RemarkTextType remark_text);
            };

            // �ֲָı���Ϣ
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

            // �����Ϣ
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