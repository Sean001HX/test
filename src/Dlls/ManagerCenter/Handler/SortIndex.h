/*************************************************
Copyright (C), 2017, HX Tech Co., Ltd.
File name:      SortIndex.h
Author:			XuYC
Version:
Date:
Description:    提供账户排序索引,合约排序索引,品种排序索引,交易所排序索引
*************************************************/

#ifndef __SORT_INDEX_H__
#define __SORT_INDEX_H__

#include <vector>
#include <boost\multi_index_container.hpp>
#include <boost\multi_index\mem_fun.hpp>
#include <boost\multi_index\ordered_index.hpp>
#include <boost\multi_index\global_fun.hpp>

#include "utility/rwmutex.h"
#include "define/params_declare.h"
#include "../Application/user_class_declare.h"

namespace AllTrade {
    namespace NPMgrCenter {

#pragma region 账户多索引分类
        // 用于多索引容器的全局函数
        const PUserIDType index_get_user_id(const AccountHrPtr& acc_hr_ptr);
        const PLoginNameType index_get_login_name(const AccountHrPtr& acc_hr_ptr);
        const PAccountNameType index_get_acc_name(const AccountHrPtr& acc_hr_ptr);

        class AccountIndex
        {
        public:
            AccountIndex() {}
            ~AccountIndex() {}

            AccountIndex(const AccountIndex&);
            AccountIndex& operator=(const AccountIndex&);

            void addToList(const AccountHrPtr& acc_hr_ptr);
            void removefromList(const AccountHrPtr& acc_hr_ptr);
            void removefromList(const UserIDType user_id);
            size_t getCount() const;

            // 根据UserID获取对应账户
            AccountHrPtr getAccountHrPtrByUserID(const UserIDType user_id) const;
            // 根据LoginName获取对应账户
            AccountHrPtr getAccountHrPtrByLoginName(const LoginNameType login_name) const;
            // 根据AccountName获取对应账户
            AccountHrPtr getAccountHrPtrByAccountName(const AccountNameType acc_name) const;

            // 获取所有合约信息
            std::vector<AccountHrPtr> getAllAccountHrs() const;

        private:
            template<typename Tag, typename ParamType>
            AccountHrPtr getAccountHrPtr(const ParamType param) const
            {
                readLock    rl(m_mtx_users);      
                auto& indexoftag = m_users.get<Tag>();
                auto fit = indexoftag.find(param);
                if (fit != indexoftag.end())
                    return *fit;

                return AccountHrPtr();
            }

        private:
            ///////////////////////////////////////////////
            struct UserIDTag{};
            struct LoginNameTag {};
            struct AccountNameTag{};
            typedef boost::multi_index::multi_index_container <
                AccountHrPtr,
                boost::multi_index::indexed_by<
                boost::multi_index::ordered_unique<boost::multi_index::tag<UserIDTag>, boost::multi_index::global_fun<const AccountHrPtr&, const PUserIDType, index_get_user_id> >,
                boost::multi_index::ordered_unique<boost::multi_index::tag<LoginNameTag>, boost::multi_index::global_fun<const AccountHrPtr&, const PLoginNameType, index_get_login_name> >,
                boost::multi_index::ordered_unique<boost::multi_index::tag<AccountNameTag>, boost::multi_index::global_fun<const AccountHrPtr&, const PAccountNameType, index_get_acc_name> >
                >
            > AccountSet;

        private:
            AccountSet             m_users;
            mutable rwMutex        m_mtx_users;
        };
#pragma endregion

#pragma region 合约多索引分类
        // 用于多索引容器的全局函数
        const PContractNameType index_get_contract_name(const ContractHrPtr& contract_hr_ptr);
        const PContractIDType index_get_contract_guid(const ContractHrPtr& contract_hr_ptr);
        const PContractCodeType index_get_contract_code(const ContractHrPtr& contract_hr_ptr);
        StockPlateAreaType index_get_contract_area(const ContractHrPtr& contract_hr_ptr);

        // 合约多索引分类排序, 外界已加锁,此处无需加锁
        class ContractIndex
        {
        public:
            ContractIndex() {}
            ~ContractIndex() {}

            ContractIndex(const ContractIndex&);
            ContractIndex& operator=(const ContractIndex&);

            void addToList(const ContractHrPtr& contract_ptr);
            void removefromList(const ContractHrPtr& contract_ptr);
            void removefromList(const ContractIDType contract_id);

            // 根据ContractID获取对应合约
            ContractHrPtr getContractHrPtrByContractID(const ContractIDType contract_id) const;
            // 根据ContractName获取对应合约
            ContractHrPtr getContractHrPtrByContractName(const ContractNameType contract_name) const;
            // 根据ContractCode获取对应合约
            ContractHrPtr getContractHrPtrByContractCode(const ContractCodeType contract_code) const;
            // 根据板块区域获取对应合约
            std::vector<ContractHrPtr> getContractHrPtrByPlateArea(StockPlateAreaType platearea) const;

            // 获取所有合约信息
            std::vector<ContractHrPtr> getAllContractHrs() const;

        private:
            template<typename Tag, typename ParamType>
            ContractHrPtr getContractHrPtr(const ParamType param) const
            {
                readLock    rl(m_mtx_contracts);
                auto& indexoftag = m_contracts.get<Tag>();
                auto fit = indexoftag.find(param);
                if (fit != indexoftag.end())
                    return *fit;

                return ContractHrPtr();
            }

        private:
            ///////////////////////////////////////////////
            struct ContractNameTag{};
            struct ContractIDTag{};
            struct ContractCodeTag {};
            struct PlateAreaTag {};
            typedef boost::multi_index::multi_index_container <
                ContractHrPtr,
                boost::multi_index::indexed_by<
                boost::multi_index::ordered_unique<boost::multi_index::tag<ContractNameTag>, boost::multi_index::global_fun<const ContractHrPtr&, const PContractNameType, index_get_contract_name> >,
                boost::multi_index::ordered_unique<boost::multi_index::tag<ContractIDTag>, boost::multi_index::global_fun<const ContractHrPtr&, const PContractIDType, index_get_contract_guid> >,
                boost::multi_index::ordered_unique<boost::multi_index::tag<ContractCodeTag>, boost::multi_index::global_fun<const ContractHrPtr&, const PContractCodeType, index_get_contract_code> >,
                boost::multi_index::ordered_non_unique<boost::multi_index::tag<PlateAreaTag>, boost::multi_index::global_fun<const ContractHrPtr&, StockPlateAreaType, index_get_contract_area> >
                >
            > ContractSet;

        private:
            ContractSet             m_contracts;
            mutable rwMutex         m_mtx_contracts;
        };
#pragma endregion

#pragma region 交易所多索引分类
        // 用于多索引容器的全局函数
        const PExchangeIDType index_get_exchange_id(const ExchangeHrPtr& ex_hr_ptr);
        const PExchangeNameType index_get_exchange_name(const ExchangeHrPtr& ex_hr_ptr);
        const PExchangeCodeType index_get_exchange_code(const ExchangeHrPtr& ex_hr_ptr);

        // 合约多索引分类排序, 外界已加锁,此处无需加锁
        class ExchangeIndex
        {
        public:
            ExchangeIndex() {}
            ~ExchangeIndex() {}

            ExchangeIndex(const ExchangeIndex&);
            ExchangeIndex& operator=(const ExchangeIndex&);

            void addToList(const ExchangeHrPtr& exchange_ptr);
            void removefromList(const ExchangeHrPtr& exchange_ptr);
            void removefromList(const ExchangeIDType exchange_ptr);

            // 根据ExchangeID获取对应合约
            ExchangeHrPtr getExchangeHrPtrByExchangeID(const ExchangeIDType exchange_id) const;
            // 根据ExchangeName获取对应合约
            ExchangeHrPtr getExchangeHrPtrByExchangeName(const ExchangeNameType exchange_name) const;
            // 根据ExchangeCode获取对应合约
            ExchangeHrPtr getExchangeHrPtrByExchangeCode(const ExchangeCodeType exchange_code) const;

            // 获取所有交易所信息
            std::vector<ExchangeHrPtr> getAllExchangeHrs() const;

        private:
            template<typename Tag, typename ParamType>
            ExchangeHrPtr getExchangeHr(const ParamType param) const
            {
                readLock    rl(m_mtx_exchanges);
                auto& indexoftag = m_exchanges.get<Tag>();
                auto fit = indexoftag.find(param);
                if (fit != indexoftag.end())
                    return *fit;

                return ExchangeHrPtr();
            }

        private:
            ///////////////////////////////////////////////
            struct ExchangeIDTag {};
            struct ExchangeNameTag {};
            struct ExchangeCodeTag {};
            typedef boost::multi_index::multi_index_container <
                ExchangeHrPtr,
                boost::multi_index::indexed_by<
                boost::multi_index::ordered_unique<boost::multi_index::tag<ExchangeIDTag>, boost::multi_index::global_fun<const ExchangeHrPtr&, const PExchangeIDType, index_get_exchange_id> >,
                boost::multi_index::ordered_unique<boost::multi_index::tag<ExchangeNameTag>, boost::multi_index::global_fun<const ExchangeHrPtr&, const PExchangeNameType, index_get_exchange_name> >,
                boost::multi_index::ordered_non_unique<boost::multi_index::tag<ExchangeCodeTag>, boost::multi_index::global_fun<const ExchangeHrPtr&, const PExchangeCodeType, index_get_exchange_code> >
                >
            > ExchangeHrSet;

        private:
            ExchangeHrSet           m_exchanges;
            mutable rwMutex         m_mtx_exchanges;
        };
#pragma endregion

    }
}
#endif