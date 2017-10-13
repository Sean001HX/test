#include <assert.h>
#include <tbb/tbb.h>
#include <tbb/blocked_range.h>
#include <tbb/parallel_for.h>
#include "RiskControlManager.h"
#include "define/struct_extern.h"
#include "define/protocol_error.h"
#include "include/OperationManager/OperationManager.h"
#include "include/ManagerCenter/ManagerCenter.h"
#include "utility/utility_fun.h"
#include "../Handler/orderlistmanager.h"
#include "../Handler/positionhandler.h"
#include "../Handler/positionlistmanager.h"
#include "../Handler/quotehandler.h"
// #include "servermgrbase.h"
#include "taskmsg.h"
#include "taskmsg_order_mgr.h"

#include "C:/ng_tools/ng_header_for_log4cxx/ng_header_for_log4cxx.hpp"
#include "C:/ng_tools/ng_header_for_log4cxx/ng_header_for_log4cxx_log_var.hpp"
NG_LOGGER(logger, "RiskControlManager");


using namespace AllTrade::NPMgrCenter;

namespace AllTrade{
    namespace NPTradeCenter {

        RiskControlManager::RiskControlManager()
            : m_thread_call(this, &RiskControlManager::thread_risk_calculate)
        {
            m_thread_call.set_priority(THREAD_PRIORITY_ABOVE_NORMAL);// ��׼+1
            m_thread_call.start(this);
        }

        RiskControlManager::~RiskControlManager()
        {

        }

        void RiskControlManager::updateQuoteForRisk(const QuoteHrPtr& quote_hr)
        {
            writeLock lock(m_mtx);
            m_change_quotes[quote_hr->getContractID()] = quote_hr->getLastPrice();
            m_quote_event.set();
        }

        void RiskControlManager::re_calculate(const ContractIDType contract_id, YDouble pos_price)
        {
            writeLock lock(m_mtx);
            m_change_quotes[contract_id] = pos_price;
            m_quote_event.set();
        }

        long RiskControlManager::thread_risk_calculate(void* param)
        {
            try
            {
                const int handlerCnt = 2;
                CommonTools::handler handlerTable[] = { m_quote_event, m_close_event };

                while (true)
                {
                    int index = CommonTools::wait_for_multiple_events(handlerTable, handlerCnt);
                    if (index == -1)
                    {
                        // �쳣�ȴ��¼�
                        break;
                    }
                    else if (handlerTable[index] == m_close_event)// �ر��¼�
                    {
                        break;
                    }

                    calculateAll();
                }
                return 0;
            }
            catch (...)
            {
                assert(0);
                // �����߳��쳣����
                return -1;
            }
        }

        void RiskControlManager::calculateAll()
        {
            // ���ݺ�ԼID���ȡ�Ŷ�ί��
            std::vector<PositionHrPtr> position_hr_ptrs;
            std::map<PContractIDType, YDouble> contract_id_last_quote;

            {
                writeLock lock(m_mtx);
                contract_id_last_quote.swap(m_change_quotes);
            }
            position_hr_ptrs = PositionListManager::instance()->updatePositionQuoteByContractIDs(contract_id_last_quote);

            // ���۳ɽ�,����tbb����
            typedef std::vector<PositionHrPtr>::iterator PositionHrVecIter;
            tbb::parallel_for(tbb::blocked_range<PositionHrVecIter>(position_hr_ptrs.begin(), position_hr_ptrs.end())
                , [&](const tbb::blocked_range<PositionHrVecIter>& range){
                for (auto i = range.begin(); i != range.end(); i++)
                {
                    risk_calculate(*i);
                }
            });
        }

        void RiskControlManager::risk_calculate(const PositionHrPtr& position_hr)
        {
            init_calculate(position_hr->getCommodityType(), position_hr->getUserID().c_str(), true, false);
        }

        void RiskControlManager::triggerUserRiskControl(CommodityTypeType commod_type, const UserIDType user_id, RiskControlType rc_type, bool bTrigger)
        {
			PRemarkTextType remark_text, remark_text1, remark_text2;
            switch (rc_type)
            {
            case AllTrade::RCT_WarningLine:
                remark_text1 = "������ؾ�����";
                remark_text2 = "�ѽ��������";
                break;
            case AllTrade::RCT_ForceLine:
                remark_text1 = "�������ǿƽ��";
                remark_text2 = "�ѽ��ǿƽ���";
                break;
            case AllTrade::RCT_LimitLine:
                remark_text1 = "��������޲���";
                remark_text2 = "�ѽ���޲ַ��";
                break;
            default:
                break;
            }

            if (bTrigger && !IManagerCenter::instance()->getUserIsInRiskControl(user_id, rc_type))
            {
                // �ﵽ���
				remark_text = remark_text1;
                ServerOperator::ServerTaskCommMsgPtr pos_msg_ptr = ServerOperator::ServerTaskCommMsg::createRiskMsg(commod_type, user_id, UtilityFun::getCurrentDateTime().c_str(), rc_type, remark_text.c_str());
                TaskMsgOrderManager::instance()->sendMsgToFront(pos_msg_ptr);
            }
            else if (!bTrigger && IManagerCenter::instance()->getUserIsInRiskControl(user_id, rc_type))
            {
                // ������
                remark_text = remark_text2;
                ServerOperator::ServerTaskCommMsgPtr pos_msg_ptr = ServerOperator::ServerTaskCommMsg::createRiskMsg(commod_type, user_id, UtilityFun::getCurrentDateTime().c_str(), rc_type, remark_text.c_str());
                TaskMsgOrderManager::instance()->sendMsgToFront(pos_msg_ptr);
            }

			IManagerCenter::instance()->triggerUserRiskControl(remark_text, user_id, rc_type, bTrigger);
        }

        ErrorCodeType RiskControlManager::init_calculate(CommodityTypeType commod_type, const UserIDType user_id, bool needTigger, bool needlog, YDouble frrmoney)
        {
            SAccountPtr acc_ptr = IManagerCenter::instance()->getAccountByID(user_id);
            if (!acc_ptr) return Error_User_Unexist;

            SRiskInfoPtr risk_ptr = IManagerCenter::instance()->getRiskInfoByLoginName(acc_ptr->login_name_);
            if (!risk_ptr) return Error_User_Unexist;

            SMoneyInfoPtr money_ptr = IManagerCenter::instance()->getMoneyInfoByLoginName(acc_ptr->login_name_);
            if (!money_ptr) return Error_User_Unexist;

            if (needTigger)
            {
                if (risk_ptr->warningline_ == 0.0)
                {
                    triggerUserRiskControl(commod_type, user_id, RiskControlType::RCT_WarningLine, false);
                }
                if (risk_ptr->forceline_ == 0.0)
                {
                    triggerUserRiskControl(commod_type, user_id, RiskControlType::RCT_ForceLine, false);
                }
                if (risk_ptr->limitline_ == 0.0)
                {
                    triggerUserRiskControl(commod_type, user_id, RiskControlType::RCT_LimitLine, false);
                }
            }

            if (risk_ptr->warningline_ == 0.0
                && risk_ptr->forceline_ == 0.0
                && risk_ptr->limitline_ == 0.0)
            {
                if (needTigger || needlog)
                {
                    LOG4CXX_TRACE(logger, "�˻�"LOG_NOVAR(user_id)"���ֵ��Ϊ0");
                }
                return Err_Succeed;
            }

            // �û���ǰ���ʲ�
            YDouble all_money = money_ptr->logic_can_extract_ + money_ptr->logic_wait_thaw_;

            std::vector<PositionHrPtr> tmp = PositionListManager::instance()->getPositionHrsByUserID(acc_ptr->user_id_);
//             if (!needTigger && tmp.empty()) return Err_Succeed;

            // ����ֵ
            std::string contract_price;
            YDouble all_price(0);
            for (auto& item : tmp)
            {
                if (item->getLastPrice() == 0.0)
                    all_price += item->getTradeAvePrice() * item->getPositionAllVol();
                else
                    all_price += item->getLastPrice();

                contract_price += item->getContractID() + "�ֲ���ֵ:" + std::to_string(item->getLastPrice()) + ",�ɽ�����:" + std::to_string(item->getTradeAvePrice()) + ",�ֲ�������:" + std::to_string(item->getPositionAllVol()) + ";";
            }

            all_money += all_price;

            YDouble riskValue = -(all_money - money_ptr->priority_fund_ - money_ptr->user_deposit_) * 100.0 / money_ptr->user_deposit_;
//             if (riskValue <= 0.0)
//                 return Err_Succeed;

            if (risk_ptr->warningline_ != 0.0)
            {
                if (needTigger)
                {
                    triggerUserRiskControl(commod_type, user_id, RiskControlType::RCT_WarningLine, risk_ptr->warningline_ <= riskValue);
                }
            }

            if (needTigger || needlog)
            {
                LOG4CXX_TRACE(logger, "�˻�"LOG_NOVAR(user_id)"������"
                    LOG_VAR(risk_ptr->warningline_)LOG_VAR(riskValue)LOG_VAR(all_money)LOG_VAR(money_ptr->priority_fund_)LOG_VAR(money_ptr->user_deposit_)
                    LOG_NOVAR(contract_price));
            }

            if (risk_ptr->forceline_ != 0.0)
            {
                if (needTigger)
                {

                    triggerUserRiskControl(commod_type, user_id, RiskControlType::RCT_ForceLine, risk_ptr->forceline_ <= riskValue);

                    // ƽ���
                    if (risk_ptr->forceline_ <= riskValue)
                    {

                        LOG4CXX_INFO(logger, "�˻�"LOG_NOVAR(user_id)
                            "����ǿƽ, ��ʱ���ʲ�"LOG_NOVAR(all_money)
                            ",���ն�"LOG_NOVAR(riskValue)",ǿƽ��"LOG_NOVAR(risk_ptr->forceline_)
                            ",�߼���ȡ"LOG_NOVAR(money_ptr->logic_can_extract_)
                            ",�߼����ⶳ"LOG_NOVAR(money_ptr->logic_wait_thaw_)
                            ",�����ʽ�"LOG_NOVAR(money_ptr->priority_fund_)
                            ",�Ӻ��ʽ�"LOG_NOVAR(money_ptr->user_deposit_)
                            ",�ֲ����:"LOG_NOVAR(contract_price));

                        OrderListManager::instance()->closeAllOrders(commod_type, user_id);
                        PositionListManager::instance()->closeAllYestodayPosition(commod_type, user_id);
                    }
                }

            }

            if (needTigger || needlog)
            {
                LOG4CXX_TRACE(logger, "�˻�"LOG_NOVAR(user_id)"ǿƽ��"
                    LOG_VAR(risk_ptr->forceline_)LOG_VAR(riskValue)LOG_VAR(all_money)LOG_VAR(money_ptr->priority_fund_)LOG_VAR(money_ptr->user_deposit_)
                    LOG_NOVAR(contract_price));
            }

            YDouble limitValue = (all_price + money_ptr->order_freeze_ + frrmoney) * 100.0 / all_money;
            if (risk_ptr->limitline_ != 0.0)
            {
                if (needTigger)
                {
                    triggerUserRiskControl(commod_type, user_id, RiskControlType::RCT_LimitLine, risk_ptr->limitline_ <= limitValue);
                }
                else if (risk_ptr->limitline_ <= limitValue)
                {
                    return Error_User_Will_NoOpen_Limit;
                }
            }

            if (needTigger || needlog)
            {
                LOG4CXX_TRACE(logger, "�˻�"LOG_NOVAR(user_id)"�޲���"
                    LOG_VAR(risk_ptr->limitline_)LOG_VAR(limitValue)LOG_VAR(all_price)LOG_VAR(money_ptr->order_freeze_)LOG_VAR(all_money)
                    LOG_NOVAR(contract_price));
            }

            return Err_Succeed;
        }

    }
}