/*************************************************
Copyright (C), 2017, HX Tech Co., Ltd.
File name:      user_struct_declare.h
Author:			XuYC
Version:
Date:
Description:    �ṩ��������ͳһ�Ľṹ��ָ������,��ֹ�ṹ���ļ��໥�����Լ��ظ�����,�ӿ�����ٶ�
*************************************************/

#ifndef __TRADE_CLASS_DECLARE_H__
#define __TRADE_CLASS_DECLARE_H__

#include <memory>

namespace AllTrade {

    namespace NPMgrCenter {
        // �˻�����ͳһ����
        class CAccountBaseHandler;
        typedef std::shared_ptr<CAccountBaseHandler>        AccountHrPtr;
        typedef std::weak_ptr<CAccountBaseHandler>          AccountHrWPtr;

        // ���˻�
        class CRootAccountHandler;
        typedef std::shared_ptr<CRootAccountHandler>        RootAccountHrPtr;
        // �����˻�
        class CAgencyAccountHandler;
        typedef std::shared_ptr<CAgencyAccountHandler>      AgencyAccountHrPtr;
        // �����˻�(����)
        class CManagerAccountHandler;
        typedef std::shared_ptr<CManagerAccountHandler>     ManagerAccountHrPtr;
        // ����˻�
        class CRiskAccountHandler;
        typedef std::shared_ptr<CRiskAccountHandler>        RiskAccountHrPtr;
        // �����˻�
        class CTradeAccountHandler;
        typedef std::shared_ptr<CTradeAccountHandler>       TradeAccountHrPtr;

        // �ʽ���Ϣ����
        class CMoneyHandler;
        typedef std::shared_ptr<CMoneyHandler>              MoneyHrPtr;
        typedef std::weak_ptr<CMoneyHandler>                MoneyHrWPtr;


        // ����������
        class ExchangeBaseHandler;
        typedef std::shared_ptr<ExchangeBaseHandler>        ExchangeHrPtr;
        typedef std::weak_ptr<ExchangeBaseHandler>          ExchangeHrWPtr;

        class StockExchangeHandler;
        typedef std::shared_ptr<StockExchangeHandler>       StockExchangeHrPtr;
        typedef std::weak_ptr<StockExchangeHandler>         StockExchangeHrWPtr;

        // Ʒ�ֲ���
        class CProductHandler;
        typedef std::shared_ptr<CProductHandler>            ProductHrPtr;
        typedef std::weak_ptr<CProductHandler>              ProductHrWPtr;

        // ��Լ����
        class ContractBaseHandler;
        typedef std::shared_ptr<ContractBaseHandler>        ContractHrPtr;
        typedef std::weak_ptr<ContractBaseHandler>          ContractHrWPtr;
 
        class StockContractHandler;
        typedef std::shared_ptr<StockContractHandler>       StockContractHrPtr;
        typedef std::weak_ptr<StockContractHandler>         StockContractHrWPtr;
    }
}

#endif