/*************************************************
Copyright (C), 2017, HX Tech Co., Ltd.
File name:      CommodityManager.h
Author:			XuYC
Version:
Date:
Description:    提供用户模块具体实现接口
*************************************************/
#ifndef __CCONTRACT_H__
#define __CCONTRACT_H__

#include <map>
#include <vector>
#include <boost/noncopyable.hpp>

#include "define/struct_declare.h"
#include "define/params_declare.h"
#include "utility/rwmutex.h"
#include "Handler/SortIndex.h"

namespace AllTrade {
    namespace NPMgrCenter {

        class CommodityManager : public boost::noncopyable
        {
        public:
            CommodityManager();
            ~CommodityManager();

            // 获取交易所列表
            std::vector<SExchangePtr> getExchanges(CommodityTypeType commodity_type) const;
            SExchangePtr getExchangeByID(CommodityTypeType commodity_type, const ExchangeIDType exchange_id) const;
            // 上海 XSHG, 深圳 XSHE
            SExchangePtr getExchangeByCode(CommodityTypeType commodity_type, const ExchangeCodeType exchange_code) const;
            // 新增/更新交易所
            ErrorCodeType addExchange(const SExchangePtr& ex);

            // 获取交易所合约列表
            SContractPtr getStockContractByID(StockAreaType stock_area, const ContractIDType contract_id) const;
            SContractPtr getStockContractByCode(StockAreaType stock_area, const ContractCodeType contract_code) const;
            std::vector<SContractPtr> getContracts(const SExchangePtr& ex) const;
            std::vector<SContractPtr> getContracts(CommodityTypeType commodity_type, const ExchangeIDType exchange_id) const;
            // 新增/更新交易所合约
            ErrorCodeType addContract(const SContractPtr& contract);

            // 当前时间是否可提交委托
            bool curCanOrder(CommodityTypeType commodity_type, const ExchangeIDType exchange_id, const ContractIDType contract_id) const;
            // 当前时间是否可交易
            bool curCanTrade(CommodityTypeType commodity_type, const ExchangeIDType exchange_id, const ContractIDType contract_id) const;

        private:
            // 创建账户操作句柄
            ExchangeHrPtr createExchangeHr(const SExchangePtr& ex);

        private:
            std::map<CommodityTypeType, ExchangeIndex>  m_exchanges;
            mutable rwMutex                             m_mtx_exchange;
        };
    }
}
#endif