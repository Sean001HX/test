/*************************************************
Copyright (C), 2017, HX Tech Co., Ltd.
File name:      TradeFeeManager.h
Author:			XuYC
Version:
Date:
Description:    提供成交费用模块具体实现
*************************************************/
#ifndef __TRADEFEEMANAGER_H__
#define __TRADEFEEMANAGER_H__

#include <vector>

#include "utility/instance_shared_from_this.h"
#include "define/params_declare.h"
#include "utility/rwmutex.h"
#include "define/ystruct_define.h"
#include "define/struct_declare.h"

namespace AllTrade {
    namespace NPTradeCenter {
        class TradeFeeManager : public CommonTools::instance_shared_from_this<TradeFeeManager>
        {
        public:
            TradeFeeManager();
            ~TradeFeeManager();

            // 获取开仓总手续费
            YDouble getOpenFee(YDouble money, int vol, bool isXSHG);
            // 获取指定佣金比例的开仓总手续费
            YDouble getSpecifyOpenFee(YDouble comm_rate, YDouble money, int vol, bool isXSHG);
            // 获取平仓总手续费
            YDouble getCloseFee(YDouble money, int vol, bool isXSHG);
            // 获取指定佣金比例的平仓总手续费
            YDouble getSpecifyCloseFee(YDouble comm_rate, YDouble money, int vol, bool isXSHG);

            // 获取指定佣金比例的交易佣金
            YDouble getSpecifyTradeCommissionFee(YDouble comm_rate, YDouble money) const;

            // 设置/获取佣金
            YDouble getTradeCommissionFee(YDouble money) const;
            YDouble getTradeCommissionValue() const;
            void setTradeCommissionValue(YDouble money);
            // 设置/获取最小佣金
            YDouble getMinTradeCommissionValue() const;
            void setMinTradeCommissionValue(YDouble money);
            // 设置/获取印花税
            YDouble getStampDutyFee(YDouble money) const;
            YDouble getStampDutyValue() const;
            void setStampDutyValue(YDouble money);
            // 设置/获取过户费
            YDouble getTransferFee(int vol) const;
            YDouble getTransferValue() const;
            void setTransferValue(YDouble money);
            // 设置/获取信息撮合费
            YDouble getInfoMatchFee(YDouble money) const;
            YDouble getInfoMatchValue() const;
            void setInfoMatchValue(YDouble money);

            // 设置/获取交易员分成比例
            YDouble getProfitRate() const;
            YDouble getProfitValue() const;
            void setProfitRate(YDouble rate);

            TradeFeePtr getFeeSetPtrCopy() const;
            AllTrade::ErrorCodeType setFeeSetPtr(const AllTrade::NPTradeCenter::TradeFeePtr& ptr);

        private:
            ErrorCodeType serialize();
            ErrorCodeType unserialize();

        private:
            mutable rwMutex     m_mtx;
            TradeFeePtr         m_TradeFee;       // 费用信息数据

            bool	            m_is_modify;		// 当前有修改
        };
    }
}
#endif