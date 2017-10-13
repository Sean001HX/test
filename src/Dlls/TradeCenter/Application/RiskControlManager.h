/*************************************************
Copyright (C), 2017, HX Tech Co., Ltd.
File name:      RiskControlManager.h
Author:			XuYC
Version:
Date:
Description:    �ṩ�ɽ�����ģ�����ʵ��
*************************************************/
#ifndef __RISKCONTROLMANAGER_H__
#define __RISKCONTROLMANAGER_H__

#include <vector>
#include <map>
#include <boost/noncopyable.hpp>

#include "utility/instance_shared_from_this.h"
#include "define/struct_base.h"
#include "define/params_declare.h"
#include "utility/rwmutex.h"
#include "utility/thread_core.h"
#include "trade_handler_declare.h"


namespace AllTrade {
    namespace NPTradeCenter {
        class RiskControlManager : public CommonTools::instance_shared_from_this<RiskControlManager>, public boost::noncopyable
        {
        public:
            RiskControlManager();
            ~RiskControlManager();

            void updateQuoteForRisk(const QuoteHrPtr& quote_hr);
            void re_calculate(const ContractIDType contract_id, YDouble last_price);

            ErrorCodeType init_calculate(CommodityTypeType commod_type, const AllTrade::UserIDType user_id, bool needTigger, bool needlog, YDouble frrmoney = 0.0);

        private:
            // ����仯�󴥷��ļ����߳�,ע���ڲ����ܺ����κ�����
            long thread_risk_calculate(void* param);
            // ����������㲢�޸�����ί��,�˺����ڼ����߳���,��������
            void calculateAll();
            // ������
            void risk_calculate(const PositionHrPtr& position_hr);

            void triggerUserRiskControl(CommodityTypeType commod_type, const UserIDType user_id, RiskControlType rc_type, bool bTrigger);

        private:
            mutable rwMutex                                 m_mtx;          // ���ݶ�д��
            CommonTools::thread_core<RiskControlManager>    m_thread_call;  // �����߳�

            CommonTools::event                              m_quote_event;  // ��������¼�
            CommonTools::event                              m_close_event;  // �ر��¼�
            std::map<PContractIDType, YDouble>              m_change_quotes;
        };
    }
}
#endif