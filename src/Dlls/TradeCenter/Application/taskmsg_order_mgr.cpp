#include <assert.h>
#include "taskmsg_order_mgr.h"
#include "taskmsg.h"
#include "handler_taskmsg.h"
#include "define/struct_base.h"
#include "GlobalDataManager.h"
#include "../Handler/orderhandler.h"
#include "../Handler/orderlistmanager.h"
#include "../SimulateTrade/SimulateOrder.h"
#include "../SyncTrade/SyncOrder.h"
#include "servermgrbase.h"
#include "utility/utility_fun.h"

#include "C:/ng_tools/ng_header_for_log4cxx/ng_header_for_log4cxx.hpp"
#include "C:/ng_tools/ng_header_for_log4cxx/ng_header_for_log4cxx_log_var.hpp"
NG_LOGGER(logger, "NPTradeCenter");

using namespace AllTrade::NPMgrCenter;

namespace AllTrade{
    namespace NPTradeCenter {

        TaskMsgOrderManager::OrderInsertCbk     TaskMsgOrderManager::m_order_insert_cbk = nullptr;
        TaskMsgOrderManager::CancelOrderCbk     TaskMsgOrderManager::m_order_cancel_cbk = nullptr;
        TaskMsgOrderManager::OrderChangeCbk     TaskMsgOrderManager::m_order_change_cbk = nullptr;
        TaskMsgOrderManager::TradeCbk           TaskMsgOrderManager::m_trade_cbk = nullptr;
        TaskMsgOrderManager::PositionCbk        TaskMsgOrderManager::m_position_cbk = nullptr;
        TaskMsgOrderManager::RiskControlCbk     TaskMsgOrderManager::m_rc_cbk = nullptr;

        TaskMsgOrderManager::TaskMsgOrderManager()
            : m_front_recv(this)
            , m_async_recv(this)
            , m_work_queue_user(3)
            , m_work_queue_trans(6)
        {

        }

        TaskMsgOrderManager::~TaskMsgOrderManager()
        {

        }

        void TaskMsgOrderManager::handlePlaceOrder(const OrderInfoPtr& order_ptr, const UserIDType use_id, const NPMgrCenter::SOnlineAccountPtr& user_online, bool needRecode)
        {
            strncpy_s(order_ptr->shadow_order_id_, GlobalDataManager::instance()->getCurShadowOrderID_c().c_str(), sizeof(order_ptr->shadow_order_id_) - 1);
            LOG4CXX_INFO(logger, "收到委托下单请求,委托合约" LOG_NOVAR(order_ptr->contract_id_)
                ",委托影子ID" LOG_NOVAR(order_ptr->shadow_order_id_)
                ",委托商品类型" LOG_NOVAR((int)order_ptr->commodity_type_)
                ",委托方向" LOG_NOVAR((int)order_ptr->direct_type_)
                ",委托手数" LOG_NOVAR(order_ptr->order_vol_)
                ",委托类型" LOG_NOVAR((int)order_ptr->order_type_)
                ",委托价格" LOG_NOVAR(order_ptr->order_price_)
                ",委托用户" LOG_NOVAR(use_id)
                ",委托下单来源" LOG_NOVAR((int)order_ptr->op_type_));

            UserOperator::HandlerOrderTaskMsg order_msg(OrderListManager::instance()->createOrderHr(order_ptr, use_id, user_online), needRecode);
            m_work_queue_user.add_task(order_msg);
        }

        void TaskMsgOrderManager::handleCancelOrder(const UserIDType use_id, const OrderStreamType order_stream, bool needRecode, bool forceClose)
        {
            if (forceClose)
            {
                LOG4CXX_INFO(logger, "收到强制撤销委托请求,委托流号" LOG_NOVAR(order_stream));
            }
            else
            {
                LOG4CXX_INFO(logger, "收到撤销委托请求,委托流号" LOG_NOVAR(order_stream));
            }

            UserOperator::HandlerCancelOrderTaskMsg cancel_order_msg(OrderListManager::instance()->getOrderHrPtrByUserID(use_id, order_stream), needRecode, forceClose);
            m_work_queue_user.add_task(cancel_order_msg);
        }

        void TaskMsgOrderManager::handleOrderInsertCbk(const OrderInfoPtr& order_ptr, const UserIDType use_id, const NPMgrCenter::SOnlineAccountPtr& user_online /*= nullptr*/)
        {
            LOG4CXX_INFO(logger, "收到委托下单请求回调,委托合约" LOG_NOVAR(order_ptr->contract_id_)
                ",委托流号" LOG_NOVAR(order_ptr->order_stream_)
                ",委托状态" LOG_NOVAR((int)order_ptr->order_state_)
                ",委托ID" LOG_NOVAR(order_ptr->order_id_)
                ",委托影子ID" LOG_NOVAR(order_ptr->shadow_order_id_)
                ",委托Ref" LOG_NOVAR(order_ptr->order_ref_)
                ",系统流号" LOG_NOVAR(order_ptr->system_order_id_)
                ",委托商品类型" LOG_NOVAR((int)order_ptr->commodity_type_)
                ",委托方向" LOG_NOVAR((int)order_ptr->direct_type_)
                ",委托手数" LOG_NOVAR(order_ptr->order_vol_)
                ",委托类型" LOG_NOVAR((int)order_ptr->order_type_)
                ",委托价格" LOG_NOVAR(order_ptr->order_price_)
                ",委托用户" LOG_NOVAR(use_id));

            TransactionOperator::HandlerOrderInsertCbkTaskMsg order_insert_msg(order_ptr, use_id, user_online);
            m_work_queue_trans.add_task(order_insert_msg);
        }

        void TaskMsgOrderManager::handleOrderChangeCbk(const OrderInfoPtr& order_ptr, const UserIDType use_id)
        {
            LOG4CXX_INFO(logger, "收到委托状态改变回调,委托合约" LOG_NOVAR(order_ptr->contract_id_)
                ",委托流号" LOG_NOVAR(order_ptr->order_stream_)
                ",委托状态" LOG_NOVAR((int)order_ptr->order_state_)
                ",委托ID" LOG_NOVAR(order_ptr->order_id_)
                ",委托影子ID" LOG_NOVAR(order_ptr->shadow_order_id_)
                ",委托Ref" LOG_NOVAR(order_ptr->order_ref_)
                ",系统流号" LOG_NOVAR(order_ptr->system_order_id_)
                ",委托商品类型" LOG_NOVAR((int)order_ptr->commodity_type_)
                ",委托方向" LOG_NOVAR((int)order_ptr->direct_type_)
                ",委托手数" LOG_NOVAR(order_ptr->order_vol_)
                ",委托成交手数" LOG_NOVAR(order_ptr->trade_vol_)
                ",委托生效手数" LOG_NOVAR(order_ptr->effected_vol_)
                ",委托类型" LOG_NOVAR((int)order_ptr->order_type_)
                ",委托价格" LOG_NOVAR(order_ptr->order_price_)
                ",委托成交均价" LOG_NOVAR(order_ptr->order_trade_price_)
                ",委托用户" LOG_NOVAR(use_id));

            TransactionOperator::HandlerOrderChangeCbkTaskMsg order_change_msg(order_ptr, use_id);
            m_work_queue_trans.add_task(order_change_msg);
        }

        void TaskMsgOrderManager::handleCancelOrderCbk(const OrderInfoPtr& order_ptr, const UserIDType use_id, const NPMgrCenter::SOnlineAccountPtr& user_online /*= nullptr*/)
        {
            LOG4CXX_INFO(logger, "收到委托撤单回调,委托合约" LOG_NOVAR(order_ptr->contract_id_)
                ",委托流号" LOG_NOVAR(order_ptr->order_stream_)
                ",委托状态" LOG_NOVAR((int)order_ptr->order_state_)
                ",委托ID" LOG_NOVAR(order_ptr->order_id_)
                ",委托影子ID" LOG_NOVAR(order_ptr->shadow_order_id_)
                ",委托Ref" LOG_NOVAR(order_ptr->order_ref_)
                ",系统委托ID" LOG_NOVAR(order_ptr->system_order_id_)
                ",委托商品类型" LOG_NOVAR((int)order_ptr->commodity_type_)
                ",委托方向" LOG_NOVAR((int)order_ptr->direct_type_)
                ",委托手数" LOG_NOVAR(order_ptr->order_vol_)
                ",委托成交手数" LOG_NOVAR(order_ptr->trade_vol_)
                ",委托生效手数" LOG_NOVAR(order_ptr->effected_vol_)
                ",委托类型" LOG_NOVAR((int)order_ptr->order_type_)
                ",委托价格" LOG_NOVAR(order_ptr->order_price_)
                ",委托成交均价" LOG_NOVAR(order_ptr->order_trade_price_)
                ",委托用户" LOG_NOVAR(use_id));

            TransactionOperator::HandlerCancelOrderCbkTaskMsg cancel_order_msg(order_ptr, use_id, user_online);
            m_work_queue_trans.add_task(cancel_order_msg);
        }

        void TaskMsgOrderManager::handleTradeCbk(const TradeInfoPtr& trade_info_ptr, const UserIDType use_id)
        {
            LOG4CXX_INFO(logger, "收到成交消息,委托合约" LOG_NOVAR(trade_info_ptr->contract_id_)
                ",商品类型" LOG_NOVAR((int)trade_info_ptr->commodity_type_)
                ",方向" LOG_NOVAR((int)trade_info_ptr->direct_type_)
                ",手数" LOG_NOVAR(trade_info_ptr->volume_)
                ",成交价" LOG_NOVAR(trade_info_ptr->trade_price_)
                ",用户" LOG_NOVAR(use_id));
            TransactionOperator::HandlerTradeCbkTaskMsg trade_msg(trade_info_ptr, use_id);
            m_work_queue_trans.add_task(trade_msg);
        }

        void TaskMsgOrderManager::handlePositionCbk(const UserIDType user_id, const PositionInfoPtr& position_ptr, const TradeInfoPtr& trade_info_ptr)
        {
            TransactionOperator::HandlerPositionCbkTaskMsg position_msg(user_id, position_ptr, trade_info_ptr);
            m_work_queue_trans.add_task(position_msg);
        }

        void TaskMsgOrderManager::sendMsgToFront(const TaskCommMsgPtr& msg_ptr)
        {
            msg_ptr->Accept(m_front_recv);
        }

        void TaskMsgOrderManager::sendMsgToServer(const TaskCommMsgPtr& msg_ptr)
        {
            msg_ptr->Accept(m_async_recv);
        }

        //////////////////////////////////////////////////////////////////////////
        // 前置机消息处理
        void TaskMsgOrderManager::FrontRecvMsgVisitor::Visit(UserOperator::OrderTaskMsg& order_msg)
        {
            OrderHrPtr order_ptr = order_msg.getOrderHrPtr();
            if (m_order_insert_cbk)
            {
                m_order_insert_cbk(order_msg.getErrorCode(), order_ptr->getUserID().c_str(), order_ptr->getOrderInfoCopy(), order_ptr->getOpUserLoginInfo());
            }
        }

        void TaskMsgOrderManager::FrontRecvMsgVisitor::Visit(UserOperator::CancelOrderTaskMsg& order_msg)
        {
            OrderHrPtr order_ptr = order_msg.getOrderHrPtr();
            if (m_order_cancel_cbk)
                m_order_cancel_cbk(order_msg.getErrorCode(), order_ptr->getUserID().c_str(), order_ptr->getOrderInfoCopy(), order_ptr->getOpUserLoginInfo());
        }

        void TaskMsgOrderManager::FrontRecvMsgVisitor::Visit(TransactionOperator::OrderInsertCbkTaskMsg& order_insert_msg)
        {
            if (m_order_insert_cbk)
                m_order_insert_cbk(order_insert_msg.getErrorCode(), order_insert_msg.getUserID().c_str(), order_insert_msg.getOrderInfoPtr(), order_insert_msg.getOpUserLoginInfo());
        }

        void TaskMsgOrderManager::FrontRecvMsgVisitor::Visit(TransactionOperator::OrderChangeCbkTaskMsg& order_change_msg)
        {
            if (m_order_change_cbk)
                m_order_change_cbk(order_change_msg.getErrorCode(), order_change_msg.getUserID().c_str(), order_change_msg.getOrderInfoPtr());
        }

        void TaskMsgOrderManager::FrontRecvMsgVisitor::Visit(TransactionOperator::CancelOrderCbkTaskMsg& cancel_order_msg)
        {
            if (m_order_cancel_cbk)
            {
                if (cancel_order_msg.getOrderInfoPtr())
                {
                    m_order_change_cbk(cancel_order_msg.getErrorCode(), cancel_order_msg.getUserID().c_str(), cancel_order_msg.getOrderInfoPtr());
                    m_order_cancel_cbk(cancel_order_msg.getErrorCode(), cancel_order_msg.getUserID().c_str(), cancel_order_msg.getOrderInfoPtr(), cancel_order_msg.getOpUserLoginInfo());
                }
                else
                {
                    assert(0);
                    LOG4CXX_ERROR(logger, "撤销委托时失败!无法找到对应委托信息,错误码" LOG_NOVAR(cancel_order_msg.getErrorCode()));
                }
            }
        }


        void TaskMsgOrderManager::FrontRecvMsgVisitor::Visit(TransactionOperator::TradeMatchCbkTaskMsg& match_msg)
        {
            assert(match_msg.getTradeInfoPtr());
            if (m_trade_cbk)
                m_trade_cbk(match_msg.getErrorCode(), match_msg.getUserID().c_str(), match_msg.getTradeInfoPtr());
        }

        void TaskMsgOrderManager::FrontRecvMsgVisitor::Visit(ServerOperator::PositionTaskMsg& pos_msg)
        {
            PositionInfoPtr pos_ptr = pos_msg.getPositionInfoPtr();
            if (m_position_cbk)
                m_position_cbk(pos_msg.getErrorCode(), pos_msg.getUserID().c_str(), pos_ptr);
        }

        void TaskMsgOrderManager::FrontRecvMsgVisitor::Visit(ServerOperator::RiskTaskMsg& rc_msg)
        {
            if (m_rc_cbk)
                m_rc_cbk(rc_msg.getUserID().c_str(), rc_msg.getDateTime().c_str(), rc_msg.getRiskControlType(), rc_msg.getRemarkText().c_str());
        }

        //////////////////////////////////////////////////////////////////////////
        // 交易模块消息处理
        void TaskMsgOrderManager::ASyncRecvMsgVisitor::Visit(UserOperator::OrderTaskMsg& order_insert_msg)
        {
            OrderHrPtr order_hr_ptr = order_insert_msg.getOrderHrPtr();
            assert(order_hr_ptr);

            LOG4CXX_DEBUG(logger, "接收到委托提交消息"LOG_NOVAR(order_hr_ptr->getOrderStream())
                ",委托手数"LOG_NOVAR(order_hr_ptr->getOrderVol())
                ",委托价格"LOG_NOVAR(order_hr_ptr->getOrderPrice())
                ",委托类型"LOG_NOVAR((int)order_hr_ptr->getOrderType())
                ",委托状态"LOG_NOVAR((int)order_hr_ptr->getOrderState()));

            assert(order_hr_ptr->getOrderState() == OrderStateType::ORDER_STATE_SUPPENDED);

            if (order_hr_ptr && order_hr_ptr->getOrderState() == OrderStateType::ORDER_STATE_SUPPENDED)
            {
                order_hr_ptr->setOrderID(UtilityFun::createGUID().c_str());
                order_hr_ptr->setOrderRef(UtilityFun::createGUID().c_str());
                order_hr_ptr->setOrderState(OrderStateType::ORDER_STATE_ACCEPT);
                OrderListManager::instance()->addToList(order_hr_ptr);

                switch (order_hr_ptr->getOrderTradeMode())
                {
                case OrderTradeModeType::ORDERTRADE_MODE_SYNC:
                    SyncOrder::instance()->createOrder(order_hr_ptr);
                    break;
                case OrderTradeModeType::ORDERTRADE_MODE_SIMULATE:
                    SimulateOrder::instance()->createOrder(order_hr_ptr);
                    break;
                default:
                    assert(0);
                    break;
                }
            }
            else
            {
                LOG4CXX_ERROR(logger, "委托提交时状态有误!"LOG_NOVAR((int)order_hr_ptr->getOrderState()));
            }
        }

        void TaskMsgOrderManager::ASyncRecvMsgVisitor::Visit(UserOperator::CancelOrderTaskMsg& cancel_order_msg)
        {
            OrderHrPtr cancel_order_ptr = cancel_order_msg.getOrderHrPtr();
            assert(cancel_order_ptr);

            LOG4CXX_DEBUG(logger, "接收到撤单提交消息"LOG_NOVAR(cancel_order_ptr->getOrderStream())
                ",委托手数"LOG_NOVAR(cancel_order_ptr->getOrderVol())
                ",已成交手数"LOG_NOVAR(cancel_order_ptr->getTradeVol())
                ",委托生效手数"LOG_NOVAR(cancel_order_ptr->getEffectVol()));

            assert(cancel_order_ptr->getOrderState() == OrderStateType::ORDER_STATE_DELETEING);

            if (cancel_order_ptr->getOrderState() == OrderStateType::ORDER_STATE_DELETEING)
            {
                switch (cancel_order_ptr->getOrderTradeMode())
                {
                case OrderTradeModeType::ORDERTRADE_MODE_SYNC:
                    SyncOrder::instance()->cancelOrder(cancel_order_ptr);
                    break;
                case OrderTradeModeType::ORDERTRADE_MODE_SIMULATE:
                    SimulateOrder::instance()->cancelOrder(cancel_order_ptr);
                    break;
                default:
                    assert(0);
                    break;
                }
            }
            else
            {
                LOG4CXX_ERROR(logger, "提交撤单时状态有误!"LOG_NOVAR((int)cancel_order_ptr->getOrderState()));
                // 异常情况处理
            }
        }

        void TaskMsgOrderManager::ASyncRecvMsgVisitor::Visit(TransactionOperator::OrderInsertCbkTaskMsg& order_insert_msg)
        {
            OrderInfoPtr order_ptr = order_insert_msg.getOrderInfoPtr();
            assert(order_ptr && (order_ptr->order_state_ == OrderStateType::ORDER_STATE_FAIL || order_ptr->order_state_ == OrderStateType::ORDER_STATE_QUEUED));

            if (!order_ptr)
            {
                LOG4CXX_ERROR(logger, "接收到委托提交回调时,委托对象为空!");
                return;
            }

            OrderHrPtr order_hr_ptr = OrderListManager::instance()->getOrderHrPtrByUserID(order_insert_msg.getUserID().c_str(), order_ptr->order_stream_);
            if (!order_hr_ptr)
            {
                LOG4CXX_ERROR(logger, "接收到委托提交回调时,无法找到委托!");
                return;
            }

            switch (order_ptr->order_state_)
            {
            case AllTrade::OrderStateType::ORDER_STATE_FAIL:
                order_hr_ptr->setOrderState(order_ptr->order_state_);
                order_hr_ptr->checkOrderTradeStatus();
                break;
            case AllTrade::OrderStateType::ORDER_STATE_QUEUED:
                if (order_hr_ptr->getOrderState() != OrderStateType::ORDER_STATE_FAIL
                    && order_hr_ptr->getOrderState() <= OrderStateType::ORDER_STATE_QUEUED)
                {
                    order_hr_ptr->setOrderState(order_ptr->order_state_);
                }
                else
                {
                    LOG4CXX_TRACE(logger, "接收到委托提交回调时,无需修改委托状态!"
                        LOG_NOVAR((int)order_ptr->order_state_)
                        LOG_NOVAR((int)order_hr_ptr->getOrderState()));
                }
                break;
            default:
                LOG4CXX_ERROR(logger, "接收到委托提交回调时,委托状态有误!"LOG_NOVAR((int)order_ptr->order_state_));
                break;
            }
        }

        void TaskMsgOrderManager::ASyncRecvMsgVisitor::Visit(TransactionOperator::OrderChangeCbkTaskMsg& order_change_msg)
        {
            OrderInfoPtr order_ptr = order_change_msg.getOrderInfoPtr();
            assert(order_ptr);
            if (!order_ptr)
            {
                LOG4CXX_ERROR(logger, "接收到委托改变回调时,委托对象为空!");
                return;
            }

            OrderHrPtr order_hr_ptr = OrderListManager::instance()->getOrderHrPtrByUserID(order_change_msg.getUserID().c_str(), order_ptr->order_stream_);
            if (!order_hr_ptr)
            {
                LOG4CXX_ERROR(logger, "接收到委托改变回调时,无法找到委托!");
                return;
            }

            switch (order_ptr->order_state_)
            {
            case AllTrade::OrderStateType::ORDER_STATE_FAIL:
                order_hr_ptr->setOrderState(order_ptr->order_state_);
                order_hr_ptr->checkOrderTradeStatus();
                break;
            default:
                order_hr_ptr->setSystemOrderID(order_ptr->system_order_id_);
                if (order_hr_ptr->getOrderState() < order_ptr->order_state_)
                {
                    order_hr_ptr->setOrderState(order_ptr->order_state_);
                    order_hr_ptr->checkOrderTradeStatus();
                }
                else
                {
                    LOG4CXX_DEBUG(logger, "接收到委托改变回调时,无需修改委托状态!"
                        LOG_NOVAR((int)order_ptr->order_state_)
                        LOG_NOVAR((int)order_hr_ptr->getOrderState()));
                }
                break;
            }
        }

        void TaskMsgOrderManager::ASyncRecvMsgVisitor::Visit(TransactionOperator::CancelOrderCbkTaskMsg& cancel_order_ptr)
        {
            OrderInfoPtr order_ptr = cancel_order_ptr.getOrderInfoPtr();
            assert(order_ptr && (order_ptr->order_state_ == OrderStateType::ORDER_STATE_PARTDELETED
                                || order_ptr->order_state_ == OrderStateType::ORDER_STATE_DELETED));

            if (!order_ptr)
            {
                LOG4CXX_ERROR(logger, "接收到委托提交回调时,委托对象为空!");
                return;
            }

            OrderHrPtr order_hr_ptr = OrderListManager::instance()->getOrderHrPtrByUserID(cancel_order_ptr.getUserID().c_str(), order_ptr->order_stream_);
            if (!order_hr_ptr)
            {
                LOG4CXX_ERROR(logger, "接收到委托提交回调时,无法找到委托!");
                return;
            }

            if (order_hr_ptr->getOrderState() != OrderStateType::ORDER_STATE_FAIL
                && order_hr_ptr->getOrderState() < order_ptr->order_state_)
            {
                order_hr_ptr->setOrderState(order_ptr->order_state_);
                order_hr_ptr->checkOrderTradeStatus();
            }
            else
            {
                LOG4CXX_TRACE(logger, "接收到撤单委托回调时,无需修改委托状态!"
                    LOG_NOVAR((int)order_ptr->order_state_)
                    LOG_NOVAR((int)order_hr_ptr->getOrderState()));
            }
        }

        void TaskMsgOrderManager::ASyncRecvMsgVisitor::Visit(TransactionOperator::TradeMatchCbkTaskMsg& match_msg)
        {
            TradeInfoPtr trade_ptr = match_msg.getTradeInfoPtr();
            assert(trade_ptr);
            if (!trade_ptr)
            {
                LOG4CXX_ERROR(logger, "接收到成交回调时,成交对象为空!");
                return;
            }

            TradeManagerPtr trade_svrmgr_ptr = ServerMgrBase::getTradeManagerPtr(match_msg.getCommodityType());
            if (trade_svrmgr_ptr)
                trade_svrmgr_ptr->dealTradeMsg(trade_ptr, match_msg.getUserID().c_str());
        }

    }
}