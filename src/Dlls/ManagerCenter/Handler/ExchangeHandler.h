#ifndef EXCHANGEHANDLER_H
#define EXCHANGEHANDLER_H

#include <map>
#include <mutex>
#include <atomic>
#include <boost\noncopyable.hpp>

#include "define/struct_extern.h"
#include "define/struct_declare.h"
#include "define/params_declare.h"
#include "../Application/user_class_declare.h"
#include "utility/rwmutex.h"
#include "SortIndex.h"

namespace AllTrade {
    namespace NPMgrCenter {

        class ExchangeBaseHandler
            : public std::enable_shared_from_this<ExchangeBaseHandler>
            , public boost::noncopyable
        {
        public:
            ExchangeBaseHandler();
            ExchangeBaseHandler(const SExchangePtr& exchange_ptr);
            ~ExchangeBaseHandler();

            // 结构(SAccountBase)相关的操作
        public:
            // 返回交易所ID
            const PExchangeIDType getExchangeID() const;
            // 获取交易所的名称
            const PExchangeNameType getExchangeName() const;
            // 获取交易所的代码
            const PExchangeCodeType getExchangeCode() const;
            // 当前时间是否可提交委托
            bool curCanOrder() const;
            // 当前时间是否可交易
            bool curCanTrade() const;
            // 指定时间是否可交易
            bool canTrade(const TimeType time) const;
            // 获取开户保证金
            YDouble getDGCT() const;

            // 获取拷贝后的交易所指针
            // 注: 该指针并非内部结构体指针,而是内部结构体指针的深拷贝,外界无法直接修改内部参数
            virtual SExchangePtr getCopyExchange() const = 0;
            // 获取交易所内所有合约
            virtual std::vector<ContractHrPtr> getContractHrs() const = 0;
            // 新增一个合约
            virtual ErrorCodeType addContract(const SContractPtr& contract_ptr) = 0;

        public:
            // 设置交易所名称
            void setExchangeName(const ExchangeNameType name);
            // 是否为空交易所;
            virtual bool isEmpty() const = 0;

            // 序列化
            virtual ErrorCodeType serialize();
            virtual ErrorCodeType unserialize() = 0;

        protected:
            ContractHrPtr createContractHr(const SContractPtr& contract_ptr);
            // 将交易所信息从数据库中删除
            void remove(unsigned int db_ver);

        protected:
            // 交易所是否被修改
            bool isModified() const;
            // 设置/获取修改标记位
            void resetCurExModiFlag(bool flag = true);
            bool getCurExModiFlag();


        protected:
            SExchangePtr        m_exchange_st_obj;	// 账户对应的数据结构
            mutable rwMutex     m_mtx_sp;

            std::atomic<bool>   m_modified_cur;	    // 当前交易所有修改
        };

        class StockExchangeHandler : public ExchangeBaseHandler
        {
        public:
            StockExchangeHandler();
            StockExchangeHandler(const SExchangePtr& exchange_ptr);
            ~StockExchangeHandler();

            // 获取拷贝后的交易所指针
            // 注: 该指针并非内部结构体指针,而是内部结构体指针的深拷贝,外界无法直接修改内部参数
            SExchangePtr getCopyExchange() const override;
            // 获取交易所内所有合约
            std::vector<ContractHrPtr> getContractHrs() const override;
            // 新增一个合约
            ErrorCodeType addContract(const SContractPtr& contract_ptr) override;
            // 获取合约通过ID
            SContractPtr getStockContractByID(StockAreaType stock_area, const ContractIDType contract_id) const;
            SContractPtr getStockContractByCode(StockAreaType stock_area, const ContractCodeType contract_code) const;

        public:
            // 是否为空
            bool isEmpty() const override;
            // 获取含有合约总数
            int getContractCount() const;
            // 删除一个合约
            ErrorCodeType delContract(StockAreaType stock_area, const ContractIDType contract_id);
            // 反序列化
            ErrorCodeType unserialize() override;

        private:
            std::map<StockAreaType, ContractIndex>  m_contracts;		// 交易所所含合约,按区域分类, A/B...		
            mutable rwMutex		                    m_mtx_contract;

            std::atomic<bool>                       m_modified_contract;  // 所含合约有修改
       };

    }	//! NPMgrCenter
}
#endif	// EXCHANGEHANDLER_H

