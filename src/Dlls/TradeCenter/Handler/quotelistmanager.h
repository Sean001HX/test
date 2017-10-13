/*************************************************
Copyright (C), 2017, HX Tech Co., Ltd.
File name:      qoutelistmanager.h
Author:			XuYC
Version:
Date:
Description:    提供成交操作管理池, 统一成交指针管理
*************************************************/

#ifndef __QUOTE_LIST_MANAGER_H__
#define __QUOTE_LIST_MANAGER_H__

#include <boost\noncopyable.hpp>
#include <map>
#include <set>
#include "utility/sync.h"
#include "utility/rwmutex.h"
#include "utility/instance_shared_from_this.h"
#include "../Application/trade_handler_declare.h"
#include "define/params_declare.h"
#include "define/struct_declare.h"

namespace AllTrade {
    namespace NPTradeCenter {

        class QuoteListManager
            : public CommonTools::instance_shared_from_this<QuoteListManager>
            , public boost::noncopyable
        {
        public:
            QuoteListManager();
            ~QuoteListManager();

            // 更新/获取行情状态
            void changeQuoteStatus(bool bl);
            bool getCurQuoteStatus() const;
            // 更新行情
            void updateQuote(const QuoteInfoPtr& quote_ptr, const NPMgrCenter::SExchangeCPtr& exchange_ptr, const NPMgrCenter::SContractCPtr& contract_ptr);

            QuoteHrPtr getQuoteHrByCode(const ContractCodeType contract_code) const;
            QuoteHrPtr getQuoteHrByID(const ContractIDType contract_id) const;

            std::set<PContractIDType> getChangeQuote(){
                std::set<PContractIDType> rslt;
                writeLock lock(m_mutex);
                rslt = std::move(m_change_quotes);
                m_change_quotes.clear();
                return rslt;
            }

            void setQuoteEvent(CommonTools::event* e){
                writeLock lock(m_mutex);
                m_quote_event = e;
            }
        private:
            mutable rwMutex                           m_mutex;
            std::map<PContractCodeType, QuoteHrPtr>   m_quote_code_hr;
            std::map<PContractIDType, QuoteHrPtr>     m_quote_id_hr;
            std::set<PContractIDType>                 m_change_quotes;
            CommonTools::event*                       m_quote_event;
            bool                                      m_cur_quote_status;
        };

    }
}

#endif