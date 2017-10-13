/*************************************************
Copyright (C), 2017, HX Tech Co., Ltd.
File name:      quotehandler.h
Author:			XuYC
Version:
Date:
Description:    �ṩ�������,���������������
*************************************************/

#ifndef __QUOTE_HANDLER_H__
#define __QUOTE_HANDLER_H__

#include <memory>
#include <vector>
#include <boost/noncopyable.hpp>
#include "define/struct_declare.h"
#include "utility/rwmutex.h"
#include "define/params_declare.h"
#include "../Application/trade_handler_declare.h"

namespace AllTrade {
    namespace NPTradeCenter {
        // ������Ϣ��������
        class QuoteBaseHandler : public std::enable_shared_from_this<QuoteBaseHandler>, public boost::noncopyable
        {
        public:
            QuoteBaseHandler(const QuoteInfoPtr& quote_ptr, const NPMgrCenter::SExchangeCPtr& exchange_ptr, const NPMgrCenter::SContractCPtr& contract_ptr);
            virtual ~QuoteBaseHandler(){}

            // ���������
            PExchangeIDType getExchangeID() const;
            PExchangeNameType getExchangeName() const;
            PExchangeCodeType getExchangeCode() const;

            // ��Լ���
            PContractIDType getContractID() const;
            PContractNameType getContractName() const;
            PContractCodeType getContractCode() const;
            int getMultiplier() const;

            // �������
            YDouble getLastPrice() const;
            YDouble getRisePrice() const;
            YDouble getFallPrice() const;
            YDouble getOpenPrice() const;
            YDouble getYClosePrice() const;
            YDouble getYSettlePrice() const;
            std::vector<YDouble> getAskPrice() const;
            std::vector<int> getAskVolume() const;
            std::vector<YDouble> getBidPrice() const;
            std::vector<int> getBidVolume() const;

            // ��ȡ���鿽����Ϣ
            virtual QuoteInfoPtr getQuoteInfoCopy() const;

            // �Ƿ��ǵ�ͣ
            virtual bool isRiseStop() const;
            virtual bool isFallStop() const;

            // �Ƿ�ɽ�����
            virtual bool canTrade() const;

        protected:
            QuoteInfoPtr                    m_quote_ptr;        // ������Ϣָ��
            NPMgrCenter::SExchangeCPtr      m_exchange_ptr;     // ����������ָ��
            NPMgrCenter::SContractCPtr      m_contract_ptr;     // ��Լ��Ϣָ��
            mutable rwMutex                 m_mtx;              // ���ݶ�д��
        };
    }
}

#endif