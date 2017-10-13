#include "handler_taskmsg.h"
#include "taskmsg.h"
#include "define/protocol_error.h"
#include "utility/scopeguard.h"
#include "taskmsg_order_mgr.h"
#include "../Handler/orderhandler.h"
#include "define/struct_base.h"

#include "C:/ng_tools/ng_header_for_log4cxx/ng_header_for_log4cxx.hpp"
#include "C:/ng_tools/ng_header_for_log4cxx/ng_header_for_log4cxx_log_var.hpp"
NG_LOGGER(logger, "HandlerMsgWorkQueue");

using namespace CommonTools;

namespace AllTrade{
    namespace NPTradeCenter {

        namespace UserOperator{

            //////////////////////////////////////////////////////////////////////////
            HandlerOrderTaskMsg::HandlerOrderTaskMsg(const OrderHrPtr& order_hr_ptr, bool needRecode)
                : m_order_hr_ptr(order_hr_ptr)
                , m_needRecode(needRecode)
            {

            }

            void HandlerOrderTaskMsg::operator()()
            {
                try
                {
                    // ����ί����Ϣ
                    UserTaskCommMsgPtr trade_msg_ptr = UserTaskCommMsg::createOrderMsg(m_order_hr_ptr);
                    ErrorCodeType err_code = trade_msg_ptr->getErrorCode();

                    // ȷ���쳣��������ɷ���
                    ScopeGuard ext([&]{
                        LOG4CXX_INFO(logger, "�ύί��"LOG_NOVAR(m_order_hr_ptr->getOrderStream())"���" LOG_NOVAR(err_code));
                        // 4. д�����ݿ�
                        if (err_code != Err_Succeed)
                            m_order_hr_ptr->setOrderState(OrderStateType::ORDER_STATE_FAIL);

                        if (trade_msg_ptr)
                            trade_msg_ptr->setErrorCode(err_code);

                        // ���д��󷵻���ǰ�û�,�޴����������ύ������ģ��
                        if (err_code != Err_Succeed)
                            TaskMsgOrderManager::instance()->sendMsgToFront(trade_msg_ptr);
                        else
                            TaskMsgOrderManager::instance()->sendMsgToServer(trade_msg_ptr);
                    });

                    // ����ί����Ϣʧ��
                    if (err_code != Err_Succeed)
                        return;

                    // 1.�û�����ί���Ƿ���Ч
                    err_code = m_order_hr_ptr->isOrderValid();
                    if (err_code != Err_Succeed)
                        return;

                    // �����븴λ
                    err_code = Err_Unknown;

                    // 2.�Ƿ���ʱ��
                    if (!m_order_hr_ptr->isOrderTime())
                    {
                        err_code = Err_Order_Trade_Time;
                        return;
                    }

                    // 3. �Ƿ���ύί��
                    err_code = m_order_hr_ptr->canOrder();
                    if (err_code != Err_Succeed)
                        return;

                    // �����븴λ
                    err_code = Err_Unknown;

                    err_code = m_order_hr_ptr->freezeMoney();
                    if (err_code != Err_Succeed)
                        return;

                    err_code = m_order_hr_ptr->freezePosition();
                    if (err_code != Err_Succeed)
                        return;
                }
                catch (...)
                {
                    assert(0);
                    // ȷ��������������,���ڲ�������쳣���Ʋ���
                }
            }

            //////////////////////////////////////////////////////////////////////////
            HandlerCancelOrderTaskMsg::HandlerCancelOrderTaskMsg(const OrderHrPtr& order_hr_ptr, bool needRecode, bool forceClose)
                : m_order_hr_ptr(order_hr_ptr)
                , m_needRecode(needRecode)
                , m_forceClose(forceClose)
            {

            }

            void HandlerCancelOrderTaskMsg::operator()()
            {
                try
                {
                    // ����ί����Ϣ
                    UserTaskCommMsgPtr trade_msg_ptr = UserTaskCommMsg::createCancelOrderMsg(m_order_hr_ptr);
                    ErrorCodeType err_code = trade_msg_ptr->getErrorCode();

                    // ȷ���쳣��������ɷ���
                    ScopeGuard ext([&]{
                        if (trade_msg_ptr)
                            trade_msg_ptr->setErrorCode(err_code);

                        if (err_code != Err_Succeed)
                            TaskMsgOrderManager::instance()->sendMsgToFront(trade_msg_ptr);
                        else
                        {
                            if (!m_forceClose)
                                TaskMsgOrderManager::instance()->sendMsgToServer(trade_msg_ptr);
                            else
                            {
                                auto tmp_order_info = m_order_hr_ptr->getOrderInfoCopy();
                                tmp_order_info->order_state_ = OrderStateType::ORDER_STATE_DELETED;
                                TaskMsgOrderManager::instance()->handleOrderChangeCbk(tmp_order_info, m_order_hr_ptr->getUserID().c_str());
                                TaskMsgOrderManager::instance()->handleCancelOrderCbk(tmp_order_info, m_order_hr_ptr->getUserID().c_str());
                            }
                        }
                    });

                    // ����ί����Ϣʧ��
                    if (err_code != Err_Succeed)
                        return;

                    if (m_forceClose)
                        return;

                    // �����븴λ
                    err_code = Err_Unknown;

                    // 2.�Ƿ���ʱ��
                    if (!m_order_hr_ptr->isTradeTime())
                    {
                        err_code = Err_Order_Trade_Time;
                        return;
                    }

                    // 3. �Ƿ�ɳ���
                    err_code = m_order_hr_ptr->canCancelOrder();
                    if (err_code != Err_Succeed)
                        return;

                    // �����븴λ
                    err_code = Err_Unknown;

                    m_order_hr_ptr->setOrderState(OrderStateType::ORDER_STATE_DELETEING);

                    // 4. д�����ݿ�
                    err_code = m_order_hr_ptr->serialize();
                }
                catch (...)
                {
                    assert(0);
                    // ȷ��������������,���ڲ�������쳣���Ʋ���
                }

            }
        }

        namespace TransactionOperator{

            //////////////////////////////////////////////////////////////////////////
            HandlerOrderInsertCbkTaskMsg::HandlerOrderInsertCbkTaskMsg(const OrderInfoPtr& order_ptr, const UserIDType use_id, NPMgrCenter::SOnlineAccountPtr user_online/* = nullptr*/)
                : m_order_ptr(order_ptr)
                , m_user_online(user_online)
            {
                strncpy_s(m_use_id, use_id, sizeof(m_use_id) - 1);
            }

            void HandlerOrderInsertCbkTaskMsg::operator()()
            {
                // ����ί����Ϣ
                TransTaskCommMsgPtr trade_msg_ptr = TransTaskCommMsg::createOrderMsg(m_order_ptr, m_use_id, m_user_online);
                ErrorCodeType err_code = trade_msg_ptr->getErrorCode();

                // ������Ϣ��ǰ�û�
                TaskMsgOrderManager::instance()->sendMsgToFront(trade_msg_ptr);
                // ������Ϣ������ģ��
                TaskMsgOrderManager::instance()->sendMsgToServer(trade_msg_ptr);
            }

            //////////////////////////////////////////////////////////////////////////
            HandlerOrderChangeCbkTaskMsg::HandlerOrderChangeCbkTaskMsg(const OrderInfoPtr& order_ptr, const UserIDType use_id, NPMgrCenter::SOnlineAccountPtr user_online/* = nullptr*/)
                : m_order_ptr(order_ptr)
                , m_user_online(user_online)
            {
                strncpy_s(m_use_id, use_id, sizeof(m_use_id) - 1);
            }

            void HandlerOrderChangeCbkTaskMsg::operator()()
            {
                // ����ί���޸���Ϣ
                TransTaskCommMsgPtr trade_msg_ptr = TransTaskCommMsg::createOrderChangeMsg(m_order_ptr, m_use_id);
                ErrorCodeType err_code = trade_msg_ptr->getErrorCode();

                // ������Ϣ��ǰ�û�
                TaskMsgOrderManager::instance()->sendMsgToFront(trade_msg_ptr);
                // ������Ϣ������ģ��
                TaskMsgOrderManager::instance()->sendMsgToServer(trade_msg_ptr);
            }

            //////////////////////////////////////////////////////////////////////////
            HandlerCancelOrderCbkTaskMsg::HandlerCancelOrderCbkTaskMsg(const OrderInfoPtr& order_ptr, const UserIDType use_id, NPMgrCenter::SOnlineAccountPtr user_online/* = nullptr*/)
                : m_order_ptr(order_ptr)
                , m_user_online(user_online)
            {
                strncpy_s(m_use_id, use_id, sizeof(m_use_id) - 1);
            }

            void HandlerCancelOrderCbkTaskMsg::operator()()
            {
                // ����ί����Ϣ
                TransTaskCommMsgPtr trade_msg_ptr = TransTaskCommMsg::createCancelOrderMsg(m_order_ptr, m_use_id, m_user_online);
                ErrorCodeType err_code = trade_msg_ptr->getErrorCode();

                // ������Ϣ��ǰ�û�
                TaskMsgOrderManager::instance()->sendMsgToFront(trade_msg_ptr);
                // ������Ϣ������ģ��
                TaskMsgOrderManager::instance()->sendMsgToServer(trade_msg_ptr);
            }

            //////////////////////////////////////////////////////////////////////////
            HandlerTradeCbkTaskMsg::HandlerTradeCbkTaskMsg(const TradeInfoPtr& trade_info_ptr, const UserIDType use_id)
                : m_trade_info_ptr(trade_info_ptr)
            {
                strncpy_s(m_use_id, use_id, sizeof(m_use_id) - 1);
            }

            void HandlerTradeCbkTaskMsg::operator()()
            {
                try
                {
                    // �����ɽ���Ϣ
                    TransTaskCommMsgPtr trade_msg_ptr = TransTaskCommMsg::createTradeMsg(m_trade_info_ptr, m_use_id);
                    ErrorCodeType err_code = trade_msg_ptr->getErrorCode();

                    // ������Ϣ��ǰ�û�
//                     TaskMsgOrderManager::instance()->sendMsgToFront(trade_msg_ptr);
                    // ������Ϣ������ģ��
                    TaskMsgOrderManager::instance()->sendMsgToServer(trade_msg_ptr);
                }
                catch (...)
                {
                    assert(0);
                    // ȷ��������������,���ڲ�������쳣���Ʋ���
                }
            }

            //////////////////////////////////////////////////////////////////////////
            HandlerPositionCbkTaskMsg::HandlerPositionCbkTaskMsg(const UserIDType use_id, const PositionInfoPtr& position_info_ptr, const TradeInfoPtr& trade_info_ptr)
                : m_position_info_ptr(position_info_ptr)
                , m_trde_info_ptr(trade_info_ptr)
            {
                strncpy_s(m_use_id, use_id, sizeof(m_use_id) - 1);
            }

            void HandlerPositionCbkTaskMsg::operator()()
            {
                // �����ɽ���Ϣ
                TransactionOperator::TransTaskCommMsgPtr trade_msg_ptr = TransactionOperator::TransTaskCommMsg::createTradeMsg(m_trde_info_ptr, m_use_id);
                ErrorCodeType err_code = trade_msg_ptr->getErrorCode();

                // ������Ϣ��ǰ�û�
                TaskMsgOrderManager::instance()->sendMsgToFront(trade_msg_ptr);

                // �����ֲ���Ϣ
                ServerOperator::ServerTaskCommMsgPtr pos_msg_ptr = ServerOperator::ServerTaskCommMsg::createPositionMsg(m_use_id, m_position_info_ptr);
                err_code = pos_msg_ptr->getErrorCode();

                // ������Ϣ��ǰ�û�
                TaskMsgOrderManager::instance()->sendMsgToFront(pos_msg_ptr);
            }

        }
    }
}