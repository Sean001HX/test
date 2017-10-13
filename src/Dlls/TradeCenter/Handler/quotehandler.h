/*************************************************
Copyright (C), 2017, HX Tech Co., Ltd.
File name:      quotehandler.h
Author:			XuYC
Version:
Date:
Description:    提供行情操作,将数据与操作分离
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
        // 行情信息操作基类
        class QuoteBaseHandler : public std::enable_shared_from_this<QuoteBaseHandler>, public boost::noncopyable
        {
        public:
            QuoteBaseHandler(const QuoteInfoPtr& quote_ptr, const NPMgrCenter::SExchangeCPtr& exchange_ptr, const NPMgrCenter::SContractCPtr& contract_ptr);
            virtual ~QuoteBaseHandler(){}

            // 交易所相关
            PExchangeIDType getExchangeID() const;
            PExchangeNameType getExchangeName() const;
            PExchangeCodeType getExchangeCode() const;

            // 合约相关
            PContractIDType getContractID() const;
            PContractNameType getContractName() const;
            PContractCodeType getContractCode() const;
            int getMultiplier() const;

            // 行情相关
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

            // 获取行情拷贝信息
            virtual QuoteInfoPtr getQuoteInfoCopy() const;

            // 是否涨跌停
            virtual bool isRiseStop() const;
            virtual bool isFallStop() const;

            // 是否可交易中
            virtual bool canTrade() const;

        protected:
            QuoteInfoPtr                    m_quote_ptr;        // 行情信息指针
            NPMgrCenter::SExchangeCPtr      m_exchange_ptr;     // 所属交易所指针
            NPMgrCenter::SContractCPtr      m_contract_ptr;     // 合约信息指针
            mutable rwMutex                 m_mtx;              // 数据读写锁
        };
    }
}

#endif