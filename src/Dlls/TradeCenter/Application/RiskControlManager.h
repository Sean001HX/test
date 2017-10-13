/*************************************************
Copyright (C), 2017, HX Tech Co., Ltd.
File name:      RiskControlManager.h
Author:			XuYC
Version:
Date:
Description:    提供成交费用模块具体实现
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
            // 行情变化后触发的计算线程,注意内部不能含有任何阻塞
            long thread_risk_calculate(void* param);
            // 根据行情计算并修改所有委托,此函数在计算线程内,不可阻塞
            void calculateAll();
            // 计算风控
            void risk_calculate(const PositionHrPtr& position_hr);

            void triggerUserRiskControl(CommodityTypeType commod_type, const UserIDType user_id, RiskControlType rc_type, bool bTrigger);

        private:
            mutable rwMutex                                 m_mtx;          // 数据读写锁
            CommonTools::thread_core<RiskControlManager>    m_thread_call;  // 计算线程

            CommonTools::event                              m_quote_event;  // 行情更新事件
            CommonTools::event                              m_close_event;  // 关闭事件
            std::map<PContractIDType, YDouble>              m_change_quotes;
        };
    }
}
#endif