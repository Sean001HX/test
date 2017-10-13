#include "SortIndex.h"
#include "ContractHandler.h"
#include "ExchangeHandler.h"
#include "accounthandler.h"

namespace AllTrade {
    namespace NPMgrCenter {

#pragma region 账户多索引分类
        //////////////////////////////////////////////////////////////////////////
        const PUserIDType index_get_user_id(const AccountHrPtr& acc_hr_ptr)
        {
            return acc_hr_ptr->getAccountID();
        }

        const PLoginNameType index_get_login_name(const AccountHrPtr& acc_hr_ptr)
        {
            return acc_hr_ptr->getAccountLoginName();
        }

        const PAccountNameType index_get_acc_name(const AccountHrPtr& acc_hr_ptr)
        {
            return acc_hr_ptr->getAccountName();
        }

        //////////////////////////////////////////////////////////////////////////
        AccountIndex::AccountIndex(const AccountIndex& rhs)
            : m_users(rhs.m_users)
        {

        }

        AccountIndex& AccountIndex::operator=(const AccountIndex& rhs)
        {
            if (&rhs != this)
                m_users = rhs.m_users;

            return *this;
        }
        
        void AccountIndex::addToList(const AccountHrPtr& acc_hr_ptr)
        {
            writeLock lock(m_mtx_users);
            auto& indexoftag = m_users.get<UserIDTag>();
            auto iter = indexoftag.find(acc_hr_ptr->getAccountID());
            if (iter == indexoftag.end())
                indexoftag.insert(acc_hr_ptr);
            else
                indexoftag.replace(iter, acc_hr_ptr);// 注意modify在替换失败时会导致删除,但效率较高
        }

        void AccountIndex::removefromList(const AccountHrPtr& acc_hr_ptr)
        {
            writeLock lock(m_mtx_users);
            auto& indexoftag = m_users.get<UserIDTag>();
            auto iter = indexoftag.find(acc_hr_ptr->getAccountID());
            if (iter != indexoftag.end())
                indexoftag.erase(iter);
        }

        void AccountIndex::removefromList(const UserIDType user_id)
        {
            writeLock lock(m_mtx_users);
            auto& indexoftag = m_users.get<UserIDTag>();
            auto iter = indexoftag.find(user_id);
            if (iter != indexoftag.end())
                indexoftag.erase(iter);
        }

        size_t AccountIndex::getCount() const
        {
            readLock lock(m_mtx_users);
            return m_users.size();
        }

        AllTrade::NPMgrCenter::AccountHrPtr AccountIndex::getAccountHrPtrByUserID(const UserIDType user_id) const
        {
            return getAccountHrPtr<UserIDTag>(user_id);
        }

        AllTrade::NPMgrCenter::AccountHrPtr AccountIndex::getAccountHrPtrByLoginName(const LoginNameType login_name) const
        {
            return getAccountHrPtr<LoginNameTag>(login_name);
        }

        AllTrade::NPMgrCenter::AccountHrPtr AccountIndex::getAccountHrPtrByAccountName(const AccountNameType acc_name) const
        {
            return getAccountHrPtr<AccountNameTag>(acc_name);
        }

        std::vector<AccountHrPtr> AccountIndex::getAllAccountHrs() const
        {
            readLock lock(m_mtx_users);
            std::vector<AccountHrPtr> rslt;
            auto& indexoftag = m_users.get<UserIDTag>();
            for (auto item : indexoftag)
                rslt.push_back(item);
            return rslt;
        }

#pragma endregion

#pragma region 合约多索引分类
        //////////////////////////////////////////////////////////////////////////
        // 用于多索引容器的全局函数
        const PContractNameType index_get_contract_name(const ContractHrPtr& contract_hr_ptr)
        {
            return contract_hr_ptr->getContractName();
        }

        const PContractIDType index_get_contract_guid(const ContractHrPtr& contract_hr_ptr)
        {
            return contract_hr_ptr->getContractID();
        }

        const PContractCodeType index_get_contract_code(const ContractHrPtr& contract_hr_ptr)
        {
            return contract_hr_ptr->getContractCode();
        }

        AllTrade::StockPlateAreaType index_get_contract_area(const ContractHrPtr& contract_hr_ptr)
        {
            return contract_hr_ptr->getContractPlateArea();
        }

        //////////////////////////////////////////////////////////////////////////
        ContractIndex::ContractIndex(const ContractIndex& rhs)
            : m_contracts(rhs.m_contracts)
        {

        }

        ContractIndex& ContractIndex::operator=(const ContractIndex& rhs)
        {
            if (&rhs != this)
                m_contracts = rhs.m_contracts;

            return *this;
        }

        void ContractIndex::addToList(const ContractHrPtr& contract_ptr)
        {
            writeLock lock(m_mtx_contracts);
            auto& indexoftag = m_contracts.get<ContractIDTag>();
            auto iter = indexoftag.find(contract_ptr->getContractID());
            if (iter == indexoftag.end())
                indexoftag.insert(contract_ptr);
            else
                indexoftag.replace(iter, contract_ptr);// 注意modify在替换失败时会导致删除,但效率较高
        }

        void ContractIndex::removefromList(const ContractHrPtr& contract_ptr)
        {
            writeLock lock(m_mtx_contracts);
            auto& indexoftag = m_contracts.get<ContractIDTag>();
            auto iter = indexoftag.find(contract_ptr->getContractID());
            if (iter != indexoftag.end())
                indexoftag.erase(iter);
        }

        void ContractIndex::removefromList(const ContractIDType contract_id)
        {
            writeLock lock(m_mtx_contracts);
            auto& indexoftag = m_contracts.get<ContractIDTag>();
            auto iter = indexoftag.find(contract_id);
            if (iter != indexoftag.end())
                indexoftag.erase(iter);
        }

        AllTrade::NPMgrCenter::ContractHrPtr ContractIndex::getContractHrPtrByContractID(const ContractIDType contract_id) const
        {
            return getContractHrPtr<ContractIDTag>(contract_id);
        }

        AllTrade::NPMgrCenter::ContractHrPtr ContractIndex::getContractHrPtrByContractName(const ContractNameType contract_name) const
        {
            return getContractHrPtr<ContractNameTag>(contract_name);
        }

        AllTrade::NPMgrCenter::ContractHrPtr ContractIndex::getContractHrPtrByContractCode(const ContractCodeType contract_code) const
        {
            return getContractHrPtr<ContractCodeTag>(contract_code);
        }

        std::vector<AllTrade::NPMgrCenter::ContractHrPtr> ContractIndex::getContractHrPtrByPlateArea(StockPlateAreaType platearea) const
        {
            std::vector<ContractHrPtr> rslt;
            readLock    rl(m_mtx_contracts);

            auto& indexoftag = m_contracts.get<PlateAreaTag>();
            auto fit_begin = indexoftag.lower_bound(platearea);
            auto fit_end = indexoftag.upper_bound(platearea);
            while (fit_begin != fit_end)
            {
                rslt.push_back(*fit_begin);
                ++fit_begin;
            }

            return rslt;
        }

        std::vector<ContractHrPtr> ContractIndex::getAllContractHrs() const
        {
            readLock lock(m_mtx_contracts);
            std::vector<ContractHrPtr> rslt;
            auto& indexoftag = m_contracts.get<ContractIDTag>();
            for (auto item : indexoftag)
                rslt.push_back(item);
            return rslt;
        }

#pragma endregion

#pragma region 交易所多索引分类
        const PExchangeIDType index_get_exchange_id(const ExchangeHrPtr& ex_hr_ptr)
        {
            return ex_hr_ptr->getExchangeID();
        }

        const PExchangeNameType index_get_exchange_name(const ExchangeHrPtr& ex_hr_ptr)
        {
            return ex_hr_ptr->getExchangeName();
        }

        const PExchangeCodeType index_get_exchange_code(const ExchangeHrPtr& ex_hr_ptr)
        {
            return ex_hr_ptr->getExchangeCode();
        }

        //////////////////////////////////////////////////////////////////////////
        ExchangeIndex::ExchangeIndex(const ExchangeIndex& rhs)
            : m_exchanges(rhs.m_exchanges)
        {

        }

        ExchangeIndex& ExchangeIndex::operator=(const ExchangeIndex& rhs)
        {
            if (&rhs != this)
                m_exchanges = rhs.m_exchanges;

            return *this;
        }
        void ExchangeIndex::addToList(const ExchangeHrPtr& exchange_ptr)
        {
            writeLock lock(m_mtx_exchanges);
            auto& indexoftag = m_exchanges.get<ExchangeIDTag>();
            auto iter = indexoftag.find(exchange_ptr->getExchangeID());
            if (iter == indexoftag.end())
                indexoftag.insert(exchange_ptr);
            else
                indexoftag.replace(iter, exchange_ptr);// 注意modify在替换失败时会导致删除,但效率较高
        }

        void ExchangeIndex::removefromList(const ExchangeHrPtr& exchange_ptr)
        {
            writeLock lock(m_mtx_exchanges);
            auto& indexoftag = m_exchanges.get<ExchangeIDTag>();
            auto iter = indexoftag.find(exchange_ptr->getExchangeID());
            if (iter != indexoftag.end())
                indexoftag.erase(iter);
        }

        void ExchangeIndex::removefromList(const ExchangeIDType exchange_id)
        {
            writeLock lock(m_mtx_exchanges);
            auto& indexoftag = m_exchanges.get<ExchangeIDTag>();
            auto iter = indexoftag.find(exchange_id);
            if (iter != indexoftag.end())
                indexoftag.erase(iter);
        }

        ExchangeHrPtr ExchangeIndex::getExchangeHrPtrByExchangeID(const ExchangeIDType exchange_id) const
        {
            return getExchangeHr<ExchangeIDTag>(exchange_id);
        }

        ExchangeHrPtr ExchangeIndex::getExchangeHrPtrByExchangeName(const ExchangeNameType exchange_name) const
        {
            return getExchangeHr<ExchangeNameTag>(exchange_name);
        }

        ExchangeHrPtr ExchangeIndex::getExchangeHrPtrByExchangeCode(const ExchangeCodeType exchange_code) const
        {
            return getExchangeHr<ExchangeCodeTag>(exchange_code);
        }

        std::vector<ExchangeHrPtr> ExchangeIndex::getAllExchangeHrs() const
        {
            std::vector<ExchangeHrPtr> rslt;
            readLock lock(m_mtx_exchanges);
            auto& indexoftag = m_exchanges.get<ExchangeIDTag>();
            for (auto item : indexoftag)
                rslt.push_back(item);
            return rslt;
        }

#pragma endregion
    }
}