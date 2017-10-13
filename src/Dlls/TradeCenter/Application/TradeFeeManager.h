/*************************************************
Copyright (C), 2017, HX Tech Co., Ltd.
File name:      TradeFeeManager.h
Author:			XuYC
Version:
Date:
Description:    �ṩ�ɽ�����ģ�����ʵ��
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

            // ��ȡ������������
            YDouble getOpenFee(YDouble money, int vol, bool isXSHG);
            // ��ȡָ��Ӷ������Ŀ�����������
            YDouble getSpecifyOpenFee(YDouble comm_rate, YDouble money, int vol, bool isXSHG);
            // ��ȡƽ����������
            YDouble getCloseFee(YDouble money, int vol, bool isXSHG);
            // ��ȡָ��Ӷ�������ƽ����������
            YDouble getSpecifyCloseFee(YDouble comm_rate, YDouble money, int vol, bool isXSHG);

            // ��ȡָ��Ӷ������Ľ���Ӷ��
            YDouble getSpecifyTradeCommissionFee(YDouble comm_rate, YDouble money) const;

            // ����/��ȡӶ��
            YDouble getTradeCommissionFee(YDouble money) const;
            YDouble getTradeCommissionValue() const;
            void setTradeCommissionValue(YDouble money);
            // ����/��ȡ��СӶ��
            YDouble getMinTradeCommissionValue() const;
            void setMinTradeCommissionValue(YDouble money);
            // ����/��ȡӡ��˰
            YDouble getStampDutyFee(YDouble money) const;
            YDouble getStampDutyValue() const;
            void setStampDutyValue(YDouble money);
            // ����/��ȡ������
            YDouble getTransferFee(int vol) const;
            YDouble getTransferValue() const;
            void setTransferValue(YDouble money);
            // ����/��ȡ��Ϣ��Ϸ�
            YDouble getInfoMatchFee(YDouble money) const;
            YDouble getInfoMatchValue() const;
            void setInfoMatchValue(YDouble money);

            // ����/��ȡ����Ա�ֳɱ���
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
            TradeFeePtr         m_TradeFee;       // ������Ϣ����

            bool	            m_is_modify;		// ��ǰ���޸�
        };
    }
}
#endif