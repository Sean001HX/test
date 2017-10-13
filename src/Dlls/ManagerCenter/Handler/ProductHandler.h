#ifndef VARTYHANDLER_H
#define VARTYHANDLER_H

#include <mutex>
#include <atomic>
#include <boost\noncopyable.hpp>
#include <boost\multi_index_container.hpp>
#include <boost\multi_index\mem_fun.hpp>
#include <boost\multi_index\ordered_index.hpp>
#include <boost\multi_index\global_fun.hpp>

#include "define/struct_base.h"
#include "define/struct_declare.h"
#include "define/params_declare.h"
#include "../Application/user_class_declare.h"
#include "utility/rwmutex.h"

namespace AllTrade {
    namespace NPMgrCenter
    {
        //////////////////////////////////////////////////////////////////////////
        // 用于多索引容器的全局函数
        const PContractNameType get_contract_name(const ContractHrPtr& pContract);
        const PContractIDType get_contract_guid(const ContractHrPtr& pContract);
        const PContractCodeType get_contract_code(const ContractHrPtr& pContract);

        class CProductHandler
            : public std::enable_shared_from_this<CProductHandler>
            , public boost::noncopyable
        {
            friend class ExchangeHandler;

        public:
            CProductHandler();
            CProductHandler(const SProductInfo& product_st);
            CProductHandler(const SProductInfo& product_st, const ExchangeHrPtr& parent);
            ~CProductHandler();

            // 结构(SProductInfo)相关的操作
        public:
            // 返回所属交易所的ID
            const PExchangeIDType getBelongExID() const;
            // 返回品种ID
            const PProductIDType getProductID() const;
            // 获取品种的名称
            std::string getProductName() const;
            // 获取品种的代码
            std::string getProductCode() const;
            // 当前时间是否可交易
            bool curCanTrade() const;
            // 指定时间是否可交易
            bool canTrade(const std::string& time) const;
            // 获取品种的默认开仓手续费
            const Feest& getProductOpenFee() const;
            // 获取品种的默认平昨手续费
            const Feest& getProductCloseYestodayFee() const;
            // 获取品种的默认平今手续费
            const Feest& getProductCloseTodayFee() const;
            // 获取品种的默认交易保证金
            const Feest& getProductMargin() const;
            // 获取品种的默认合约乘数
            int getProductMultiple() const;
            // 获取品种的默认最小变动单位
            int getProductMinChUnit() const;

            // 严禁更换作用域
        protected:
            void setExchangeHandler(const ExchangeHrPtr& parent);
            void setBelongExID(ExchangeIDType belong_id);
            void setProductID(ProductIDType product_id);

            SProductPtr getProductStruct() const;
            void setProductStruct(SProductPtr pvp);

        public:
            void setProductName(const std::string& name);

            // 品种中合约的操作
        public:
            // 是否为空品种;
            bool isEmpty();
            // 获取品种中合约的总数
            int getContractCount() const;

            // 异步
            // 创建一个合约对象
            // name: 新建合约的名称，不可为空
            ContractHrPtr createContractHr(const ContractNameType name);

            // 获取指定序号(ID)的合约操作对象；name: 合约的名称
            ContractHrPtr getContractHr(const ContractNameType name) const;
            ContractHrPtr getContractHrByID(const ContractIDType id) const;

            // 异步
            // 删除一个合约对象；返回true, 删除成功
            bool deleteContractHr(const ContractNameType name);
            bool deteteContractHrByID(ContractIDType did);

            // 其他操作
        public:
            //返回所属账户对象
            ExchangeHrPtr getParentExHandler()
            {
                return m_parent.lock();
            }

        protected:
            // 将品种信息从数据库中删除
            void remove(unsigned int db_ver);
            // 从当前品种对象复制出一个新的品种对象，
            // 返回值： 新复制成功的品种对象。
            ProductHrPtr copy();

            void onAddContractHr(ContractHrPtr pvh);
            bool onDelContractHr(ContractHrPtr pvh);

            template<typename Tag, typename ParamType>
            ContractHrPtr getContractHr(const ParamType& param) const
            {
                readLock	rl(mtx_contract);

                auto& indexoftag = m_contracts.get<Tag>();
                auto fit = indexoftag.find(param);
                if (fit != indexoftag.end())
                    return *fit;

                return ContractHrPtr();
            }

        protected:
            // 品种是否被修改
            bool isModified() const;

            // 设置修改标记位
            void setCurPdModiFlag(bool flag = true);
            void setContractModiFlag(bool flag = true);
            // 获取修改标记位
            bool getCurPdModiFlag();
            bool getContractModiFlag();


        private:
            ///////////////////////////////////////////////
            struct ContractNameTag{};
            struct ContractCodeTag {};
            struct ContractIDTag{};
            typedef boost::multi_index::multi_index_container <
                ContractHrPtr,
                boost::multi_index::indexed_by<
                boost::multi_index::ordered_unique<boost::multi_index::tag<ContractNameTag>, boost::multi_index::global_fun<const ContractHrPtr&, const ContractNameType, get_contract_name> >,
                boost::multi_index::ordered_unique<boost::multi_index::tag<ContractCodeTag>, boost::multi_index::global_fun<const ContractHrPtr&, const ContractCodeType, get_contract_code> >,
                boost::multi_index::ordered_unique<boost::multi_index::tag<ContractIDTag>, boost::multi_index::global_fun<const ContractHrPtr&, const ContractIDType, get_contract_guid> >
                >
            > ContractSet;

            ContractSet         m_contracts;		// 品种所含合约		
            mutable rwMutex     mtx_contract;

            SProductPtr         m_product_st_obj;	// 账户对应的数据结构
            mutable rwMutex     m_mtx_sp;

            std::atomic<bool>   modified_cur_;		// 当前品种有修改
            std::atomic<bool>   modified_contract_;	// 所含合约有修改

            ExchangeHrWPtr m_parent;			// 所属交易所操作对象（弱）指针
        };
    }	//! NPMgrCenter
}
#endif	// VARTYHANDLER_H

