#include <assert.h>
#include "taskmsg.h"
#include "define/protocol_error.h"
#include "../Handler/orderhandler.h"
#include "../Handler/tradehandler.h"
#include "handler_taskmsg.h"
#include "define/struct_extern.h"

namespace AllTrade{
    namespace NPTradeCenter {

        //////////////////////////////////////////////////////////////////////////
        TaskCommMsg::TaskCommMsg()
            : m_errcode(Err_Unknown)
        {

        }

        AllTrade::ErrorCodeType TaskCommMsg::getErrorCode() const
        {
            return m_errcode;
        }

        void TaskCommMsg::setErrorCode(ErrorCodeType errcode)
        {
            m_errcode = errcode;
        }

        namespace UserOperator{
            //////////////////////////////////////////////////////////////////////////
            UserTaskCommMsg::UserTaskCommMsg()
                : TaskCommMsg()
            {

            }

            UserTaskCommMsgPtr UserTaskCommMsg::createOrderMsg(const OrderHrPtr& order_hr_ptr)
            {
                UserTaskCommMsgPtr rslt_ptr = std::make_shared<OrderTaskMsg>(order_hr_ptr);
                if (rslt_ptr)
                    rslt_ptr->setErrorCode(Err_Succeed);

                return rslt_ptr;
            }

            UserTaskCommMsgPtr UserTaskCommMsg::createCancelOrderMsg(const OrderHrPtr& order_hr_ptr)
            {
                UserTaskCommMsgPtr rslt_ptr = std::make_shared<CancelOrderTaskMsg>(order_hr_ptr);
                if (rslt_ptr)
                    rslt_ptr->setErrorCode(Err_Succeed);

                return rslt_ptr;
            }

            //////////////////////////////////////////////////////////////////////////
            OrderTaskMsg::OrderTaskMsg()
                :UserTaskCommMsg()
            {

            }

            OrderTaskMsg::OrderTaskMsg(const OrderHrPtr& order_hr_ptr)
                : UserTaskCommMsg()
                , m_order_hr_ptr(order_hr_ptr)
            {

            }

            AllTrade::CommodityTypeType OrderTaskMsg::getCommodityType() const
            {
                return m_order_hr_ptr->getCommodityType();
            }

            //////////////////////////////////////////////////////////////////////////
            CancelOrderTaskMsg::CancelOrderTaskMsg()
                :UserTaskCommMsg()
            {

            }

            CancelOrderTaskMsg::CancelOrderTaskMsg(const OrderHrPtr& order_hr_ptr)
                : UserTaskCommMsg()
                , m_order_hr_ptr(order_hr_ptr)
            {

            }

            AllTrade::CommodityTypeType CancelOrderTaskMsg::getCommodityType() const
            {
                return m_order_hr_ptr->getCommodityType();
            }

        }

        namespace TransactionOperator{
            //////////////////////////////////////////////////////////////////////////
            TransTaskCommMsg::TransTaskCommMsg()
                : TaskCommMsg()
            {

            }

            TransTaskCommMsgPtr TransTaskCommMsg::createOrderMsg(const OrderInfoPtr& order_ptr, const UserIDType use_id, NPMgrCenter::SOnlineAccountPtr user_online/* = nullptr*/)
            {
                TransTaskCommMsgPtr rslt_ptr = std::make_shared<OrderInsertCbkTaskMsg>(order_ptr, use_id, user_online);
                if (rslt_ptr)
                    rslt_ptr->setErrorCode(Err_Succeed);

                return rslt_ptr;
            }

            TransTaskCommMsgPtr TransTaskCommMsg::createOrderChangeMsg(const OrderInfoPtr& order_ptr, const UserIDType use_id)
            {
                TransTaskCommMsgPtr rslt_ptr = std::make_shared<OrderChangeCbkTaskMsg>(order_ptr, use_id);
                if (rslt_ptr)
                    rslt_ptr->setErrorCode(Err_Succeed);

                return rslt_ptr;
            }

            AllTrade::NPTradeCenter::TransactionOperator::TransTaskCommMsgPtr TransTaskCommMsg::createCancelOrderMsg(const OrderInfoPtr& order_ptr, const UserIDType use_id, NPMgrCenter::SOnlineAccountPtr user_online /*= nullptr*/)
            {
                TransTaskCommMsgPtr rslt_ptr = std::make_shared<CancelOrderCbkTaskMsg>(order_ptr, use_id, user_online);
                if (rslt_ptr)
                    rslt_ptr->setErrorCode(Err_Succeed);

                return rslt_ptr;
            }

            TransTaskCommMsgPtr TransTaskCommMsg::createTradeMsg(const TradeInfoPtr& trade_info_ptr, const UserIDType use_id)
            {
                TransTaskCommMsgPtr rslt_ptr = std::make_shared<TradeMatchCbkTaskMsg>(trade_info_ptr, use_id);
                if (rslt_ptr)
                    rslt_ptr->setErrorCode(Err_Succeed);

                return rslt_ptr;
            }

            //////////////////////////////////////////////////////////////////////////
            OrderInsertCbkTaskMsg::OrderInsertCbkTaskMsg()
                : TransTaskCommMsg()
            {

            }

            OrderInsertCbkTaskMsg::OrderInsertCbkTaskMsg(const OrderInfoPtr& order_ptr, const UserIDType use_id, NPMgrCenter::SOnlineAccountPtr user_online/* = nullptr*/)
                : TransTaskCommMsg()
                , m_order_ptr(order_ptr)
                , m_user_online(user_online)
            {
                strncpy_s(m_use_id, use_id, sizeof(m_use_id) - 1);
            }

            AllTrade::CommodityTypeType OrderInsertCbkTaskMsg::getCommodityType() const
            {
                return m_order_ptr->commodity_type_;
            }

            //////////////////////////////////////////////////////////////////////////
            OrderChangeCbkTaskMsg::OrderChangeCbkTaskMsg()
                : TransTaskCommMsg()
            {

            }

            OrderChangeCbkTaskMsg::OrderChangeCbkTaskMsg(const OrderInfoPtr& order_ptr, const UserIDType use_id)
                : TransTaskCommMsg()
                , m_order_ptr(order_ptr)
            {
                strncpy_s(m_use_id, use_id, sizeof(m_use_id) - 1);
            }

            AllTrade::CommodityTypeType OrderChangeCbkTaskMsg::getCommodityType() const
            {
                return m_order_ptr->commodity_type_;
            }

            //////////////////////////////////////////////////////////////////////////
            CancelOrderCbkTaskMsg::CancelOrderCbkTaskMsg()
                : TransTaskCommMsg()
            {

            }

            CancelOrderCbkTaskMsg::CancelOrderCbkTaskMsg(const OrderInfoPtr& order_ptr, const UserIDType use_id, NPMgrCenter::SOnlineAccountPtr user_online /*= nullptr*/)
                : TransTaskCommMsg()
                , m_order_ptr(order_ptr)
                , m_user_online(user_online)
            {
                strncpy_s(m_use_id, use_id, sizeof(m_use_id) - 1);
            }

            AllTrade::CommodityTypeType CancelOrderCbkTaskMsg::getCommodityType() const
            {
                return m_order_ptr->commodity_type_;
            }

            //////////////////////////////////////////////////////////////////////////
            TradeMatchCbkTaskMsg::TradeMatchCbkTaskMsg()
                : TransTaskCommMsg()
            {

            }

            TradeMatchCbkTaskMsg::TradeMatchCbkTaskMsg(const TradeInfoPtr& trade_info_ptr, const UserIDType use_id)
                : TransTaskCommMsg()
                , m_trade_info_ptr(trade_info_ptr)
            {
                strncpy_s(m_use_id, use_id, sizeof(m_use_id) - 1);
            }


            AllTrade::CommodityTypeType TradeMatchCbkTaskMsg::getCommodityType() const
            {
                return m_trade_info_ptr->commodity_type_;
            }

        }

        namespace ServerOperator {
            //////////////////////////////////////////////////////////////////////////
            ServerTaskCommMsg::ServerTaskCommMsg()
                : TaskCommMsg()
            {

            }

            ServerTaskCommMsgPtr ServerTaskCommMsg::createPositionMsg(const UserIDType user_id, const PositionInfoPtr& position_ptr)
            {
                ServerTaskCommMsgPtr rslt_ptr = std::make_shared<PositionTaskMsg>(user_id, position_ptr);
                if (rslt_ptr)
                    rslt_ptr->setErrorCode(Err_Succeed);

                return rslt_ptr;
            }

            ServerTaskCommMsgPtr ServerTaskCommMsg::createRiskMsg(CommodityTypeType commod_type, const UserIDType user_id, const DateTimeType date_time, RiskControlType rc_type, const RemarkTextType remark_text)            {
                ServerTaskCommMsgPtr rslt_ptr = std::make_shared<RiskTaskMsg>(commod_type, user_id, date_time, rc_type, remark_text);
                if (rslt_ptr)
                    rslt_ptr->setErrorCode(Err_Succeed);

                return rslt_ptr;
            }

            //////////////////////////////////////////////////////////////////////////
            PositionTaskMsg::PositionTaskMsg(const UserIDType user_id, const PositionInfoPtr& position_ptr)
                : ServerTaskCommMsg()
                , m_position_ptr(position_ptr)
            {
                strncpy_s(m_user_id, user_id, sizeof(m_user_id) - 1);
            }


            AllTrade::CommodityTypeType PositionTaskMsg::getCommodityType() const
            {
                return m_position_ptr->commodity_type_;
            }

            //////////////////////////////////////////////////////////////////////////
            RiskTaskMsg::RiskTaskMsg(CommodityTypeType commod_type, const UserIDType user_id, const DateTimeType date_time, RiskControlType rc_type, const RemarkTextType remark_text)
                : ServerTaskCommMsg()
                , m_rc_type(rc_type)
                , m_commod_type(commod_type)
            {
                strncpy_s(m_user_id, user_id, sizeof(m_user_id) - 1);
                strncpy_s(m_date_time, date_time, sizeof(m_date_time) - 1);
                strncpy_s(m_remark_text, remark_text, sizeof(m_remark_text) - 1);
            }

            AllTrade::CommodityTypeType RiskTaskMsg::getCommodityType() const
            {
                return m_commod_type;
            }

        }

    }
}
