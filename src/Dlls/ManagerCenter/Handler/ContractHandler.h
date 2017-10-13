#ifndef CONTRACTHANDLER_H
#define CONTRACTHANDLER_H

#include <mutex>
#include <atomic>
#include <boost\noncopyable.hpp>

#include "define/struct_base.h"
#include "define/struct_declare.h"
#include "utility/rwmutex.h"
#include "define/params_declare.h"
#include "../Application/user_class_declare.h"

namespace AllTrade {
    namespace NPMgrCenter {

        class ContractBaseHandler
            : public std::enable_shared_from_this<ContractBaseHandler>
            , public boost::noncopyable
        {
        public:
            ContractBaseHandler();
            ContractBaseHandler(const SContractPtr& contract_st);
            ~ContractBaseHandler();

            // 结构(SContractInfo)相关的操作
        public:
            // 返回所属交易所的ID
            PExchangeIDType getBelongExID() const;
            // 返回合约ID
            PContractIDType getContractID() const;
            // 获取合约的名称
            PContractNameType getContractName() const;
            // 获取合约的代码
            PContractCodeType getContractCode() const;
            // 当前时间是否可交易
            bool curCanTrade() const;
            // 指定时间是否可交易
            bool canTrade(const TimeType time) const;
            // 获取合约的开仓手续费
            const Feest& getContractOpenFee() const;
            // 获取合约的平昨手续费
//             const Feest& getContractCloseYestodayFee() const;
            // 获取合约的平今手续费
//             const Feest& getContractCloseTodayFee() const;
            // 获取合约的交易保证金
            const Feest& getContractMargin() const;
            // 获取合约的合约乘数
            int getContractMultiple() const;
            // 获取合约的最小变动单位
            YDouble getContractMinChUnit() const;

            // 获取拷贝后的合约指针
            // 注: 该指针并非内部结构体指针,而是内部结构体指针的深拷贝,外界无法直接修改内部参数
            virtual SContractPtr getCopyContract() const = 0;
            
            // 获取股票板块区域,主板/创业板...
            virtual StockPlateAreaType getContractPlateArea() const = 0;
        public:
            // 序列化
            ErrorCodeType serialize();

        protected:
            // 将合约信息从数据库中删除
//             void remove(unsigned int db_ver);
            // 从当前合约对象复制出一个新的合约对象，
            // 返回值： 新复制成功的合约对象。
//             virtual ContractHrPtr copy() = 0;

        protected:
            // 合约是否被修改
            bool isModified() const;

            // 设置修改标记位
            void setCurContractModiFlag(bool flag = true);
            // 获取修改标记位
            bool getCurContractModiFlag();

        protected:
            SContractPtr		m_contract_st_obj;	// 账户对应的数据结构
            mutable rwMutex		m_mtx_sp;

            std::atomic<bool>	m_modified_cur;		// 当前合约有修改
        };

        class StockContractHandler : public ContractBaseHandler
        {
        public:
            StockContractHandler();
            StockContractHandler(const SContractPtr& contract_st);
            ~StockContractHandler();

            // 获取所属类型
            AllTrade::StockAreaType getStockArea();
            // 获取拷贝后的合约指针
            SContractPtr getCopyContract() const override;
            // 获取股票板块区域,主板/创业板...
            StockPlateAreaType getContractPlateArea() const override;

        public:
            //返回所属账户对象
            StockExchangeHrPtr getParentExHandler()
            {
                return m_parent.lock();
            }

        private:
            StockExchangeHrWPtr m_parent;
        };
    }	//! NPMgrCenter
}
#endif	// CONTRACTHANDLER_H

