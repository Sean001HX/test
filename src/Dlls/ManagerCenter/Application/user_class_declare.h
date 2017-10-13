/*************************************************
Copyright (C), 2017, HX Tech Co., Ltd.
File name:      user_struct_declare.h
Author:			XuYC
Version:
Date:
Description:    提供交易中心统一的结构体指针声明,防止结构体文件相互包含以及重复定义,加快编译速度
*************************************************/

#ifndef __TRADE_CLASS_DECLARE_H__
#define __TRADE_CLASS_DECLARE_H__

#include <memory>

namespace AllTrade {

    namespace NPMgrCenter {
        // 账户操作统一基类
        class CAccountBaseHandler;
        typedef std::shared_ptr<CAccountBaseHandler>        AccountHrPtr;
        typedef std::weak_ptr<CAccountBaseHandler>          AccountHrWPtr;

        // 根账户
        class CRootAccountHandler;
        typedef std::shared_ptr<CRootAccountHandler>        RootAccountHrPtr;
        // 机构账户
        class CAgencyAccountHandler;
        typedef std::shared_ptr<CAgencyAccountHandler>      AgencyAccountHrPtr;
        // 管理账户(保留)
        class CManagerAccountHandler;
        typedef std::shared_ptr<CManagerAccountHandler>     ManagerAccountHrPtr;
        // 风控账户
        class CRiskAccountHandler;
        typedef std::shared_ptr<CRiskAccountHandler>        RiskAccountHrPtr;
        // 交易账户
        class CTradeAccountHandler;
        typedef std::shared_ptr<CTradeAccountHandler>       TradeAccountHrPtr;

        // 资金信息操作
        class CMoneyHandler;
        typedef std::shared_ptr<CMoneyHandler>              MoneyHrPtr;
        typedef std::weak_ptr<CMoneyHandler>                MoneyHrWPtr;


        // 交易所操作
        class ExchangeBaseHandler;
        typedef std::shared_ptr<ExchangeBaseHandler>        ExchangeHrPtr;
        typedef std::weak_ptr<ExchangeBaseHandler>          ExchangeHrWPtr;

        class StockExchangeHandler;
        typedef std::shared_ptr<StockExchangeHandler>       StockExchangeHrPtr;
        typedef std::weak_ptr<StockExchangeHandler>         StockExchangeHrWPtr;

        // 品种操作
        class CProductHandler;
        typedef std::shared_ptr<CProductHandler>            ProductHrPtr;
        typedef std::weak_ptr<CProductHandler>              ProductHrWPtr;

        // 合约操作
        class ContractBaseHandler;
        typedef std::shared_ptr<ContractBaseHandler>        ContractHrPtr;
        typedef std::weak_ptr<ContractBaseHandler>          ContractHrWPtr;
 
        class StockContractHandler;
        typedef std::shared_ptr<StockContractHandler>       StockContractHrPtr;
        typedef std::weak_ptr<StockContractHandler>         StockContractHrWPtr;
    }
}

#endif