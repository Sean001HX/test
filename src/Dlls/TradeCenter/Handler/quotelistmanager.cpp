#include <assert.h>
#include "quotelistmanager.h"
#include "define/struct_extern.h"
#include "quotehandler.h"
#include "../Application/RiskControlManager.h"

namespace AllTrade {
    namespace NPTradeCenter {

        QuoteListManager::QuoteListManager()
            : m_quote_event(nullptr)
            , m_cur_quote_status(false)
        {
        }

        QuoteListManager::~QuoteListManager()
        {

        }

        void QuoteListManager::updateQuote(const QuoteInfoPtr& quote_ptr, const NPMgrCenter::SExchangeCPtr& exchange_ptr, const NPMgrCenter::SContractCPtr& contract_ptr)
        {
            assert(quote_ptr && exchange_ptr && contract_ptr);
            auto item_ptr = std::make_shared<QuoteBaseHandler>(quote_ptr, exchange_ptr, contract_ptr);
            {
                writeLock lock(m_mutex);
                m_quote_code_hr[contract_ptr->contract_code_] = item_ptr;
                m_quote_id_hr[contract_ptr->contract_id_] = item_ptr;

                m_change_quotes.insert(contract_ptr->contract_id_);
            }
            if (m_quote_event)
                m_quote_event->set();

            RiskControlManager::instance()->updateQuoteForRisk(item_ptr);
        }

        AllTrade::NPTradeCenter::QuoteHrPtr QuoteListManager::getQuoteHrByCode(const ContractCodeType contract_code) const
        {
            readLock lock(m_mutex);
            auto iter = m_quote_code_hr.find(contract_code);
            if (iter != m_quote_code_hr.end())
                return iter->second;

            return QuoteHrPtr();
        }

        AllTrade::NPTradeCenter::QuoteHrPtr QuoteListManager::getQuoteHrByID(const ContractIDType contract_id) const
        {
            readLock lock(m_mutex);
            auto iter = m_quote_id_hr.find(contract_id);
            if (iter != m_quote_id_hr.end())
                return iter->second;

            return QuoteHrPtr();
        }

        void QuoteListManager::changeQuoteStatus(bool bl)
        {
            writeLock lock(m_mutex);
            m_cur_quote_status = bl;
        }

        bool QuoteListManager::getCurQuoteStatus() const
        {
            readLock lock(m_mutex);
            return m_cur_quote_status;
        }

    }
}