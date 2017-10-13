#include <assert.h>
#include "quotehandler.h"
#include "utility/utility_fun.h"
#include "define/struct_base.h"
#include "define/protocol_error.h"
#include "define/struct_extern.h"
#include "orderhandler.h"
#include "orderlistmanager.h"
#include "include/OperationManager/OperationManager.h"

using namespace AllTrade::NPMgrCenter;

namespace AllTrade {
    namespace NPTradeCenter {

        QuoteBaseHandler::QuoteBaseHandler(const QuoteInfoPtr& quote_ptr, const NPMgrCenter::SExchangeCPtr& exchange_ptr, const NPMgrCenter::SContractCPtr& contract_ptr)
            : m_quote_ptr(quote_ptr)
            , m_exchange_ptr(exchange_ptr)
            , m_contract_ptr(contract_ptr)
        {
        }

        AllTrade::PExchangeIDType QuoteBaseHandler::getExchangeID() const
        {
            return m_exchange_ptr->exchange_id_;
        }

        AllTrade::PExchangeNameType QuoteBaseHandler::getExchangeName() const
        {
            return m_exchange_ptr->exchange_name_;
        }

        AllTrade::PExchangeCodeType QuoteBaseHandler::getExchangeCode() const
        {
            return m_exchange_ptr->exchange_code_;
        }

        AllTrade::PContractIDType QuoteBaseHandler::getContractID() const
        {
            return m_contract_ptr->contract_id_;
        }

        AllTrade::PContractNameType QuoteBaseHandler::getContractName() const
        {
            return m_contract_ptr->contract_name_;
        }

        AllTrade::PContractCodeType QuoteBaseHandler::getContractCode() const
        {
            return m_contract_ptr->contract_code_;
        }

        int QuoteBaseHandler::getMultiplier() const
        {
            return m_contract_ptr->contract_multiplier_;
        }

        YDouble QuoteBaseHandler::getLastPrice() const
        {
            return m_quote_ptr->last_price_;
        }

        YDouble QuoteBaseHandler::getRisePrice() const
        {
//             if (m_quote_ptr->highest_price_ != 0.0)
//                 return m_quote_ptr->highest_price_;

            YDouble rslt(0);
            int highest = m_quote_ptr->yclose_price_ * 1000 * 1.1;
            if (highest % 10 != 0)
                rslt = UtilityFun::Round((double)highest / 1000.0 - 0.005, 0.01);
            else
                rslt = UtilityFun::Round((double)highest / 1000.0, 0.01);

            return rslt;
        }

        YDouble QuoteBaseHandler::getFallPrice() const
        {
//             if (m_quote_ptr->lowest_price_ != 0.0)
//                 return m_quote_ptr->lowest_price_;

            YDouble rslt(0);
            int highest = m_quote_ptr->yclose_price_ * 1000 * 0.9;
            if (highest % 10 != 0)
                rslt = UtilityFun::Round((double)highest / 1000.0 + 0.005, 0.01);
            else
                rslt = UtilityFun::Round((double)highest / 1000.0, 0.01);

            return rslt;
        }

        YDouble QuoteBaseHandler::getOpenPrice() const
        {
            return m_quote_ptr->open_price_;
        }

        YDouble QuoteBaseHandler::getYClosePrice() const
        {
            return m_quote_ptr->yclose_price_;
        }

        YDouble QuoteBaseHandler::getYSettlePrice() const
        {
            return m_quote_ptr->ysettle_price_;
        }

        std::vector<YDouble> QuoteBaseHandler::getAskPrice() const
        {
            std::vector<YDouble> rslt;
            int count = sizeof(m_quote_ptr->ask_price_) / sizeof(YDouble);
            for (int i = 0; i < count; i++)
                rslt.push_back(m_quote_ptr->ask_price_[i]);
            return rslt;
        }

        std::vector<int> QuoteBaseHandler::getAskVolume() const
        {
            std::vector<int> rslt;
            int count = sizeof(m_quote_ptr->ask_volume_) / sizeof(int);
            for (int i = 0; i < count; i++)
                rslt.push_back(m_quote_ptr->ask_volume_[i]);
            return rslt;
        }

        std::vector<YDouble> QuoteBaseHandler::getBidPrice() const
        {
            std::vector<YDouble> rslt;
            int count = sizeof(m_quote_ptr->bid_price_) / sizeof(YDouble);
            for (int i = 0; i < count; i++)
                rslt.push_back(m_quote_ptr->bid_price_[i]);
            return rslt;
        }

        std::vector<int> QuoteBaseHandler::getBidVolume() const
        {
            std::vector<int> rslt;
            int count = sizeof(m_quote_ptr->bid_volume_) / sizeof(int);
            for (int i = 0; i < count; i++)
                rslt.push_back(m_quote_ptr->bid_volume_[i]);
            return rslt;
        }

        AllTrade::NPTradeCenter::QuoteInfoPtr QuoteBaseHandler::getQuoteInfoCopy() const
        {
            return std::make_shared<QuoteInfoBase>(*m_quote_ptr.get());
        }

        bool QuoteBaseHandler::isRiseStop() const
        {
            return m_quote_ptr->last_price_ >= getRisePrice();
        }

        bool QuoteBaseHandler::isFallStop() const
        {
            return m_quote_ptr->last_price_ <= getFallPrice();
        }

        bool QuoteBaseHandler::canTrade() const
        {
            return m_quote_ptr->quote_status_ == QuoteStatusType::QUOTESTATUS_Normal;
        }

    }
}
