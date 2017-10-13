/*************************************************
Copyright (C), 2017, HX Tech Co., Ltd.
File name:      CommodityManager.h
Author:			XuYC
Version:
Date:
Description:    �ṩ�û�ģ�����ʵ�ֽӿ�
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

            // ��ȡ�������б�
            std::vector<SExchangePtr> getExchanges(CommodityTypeType commodity_type) const;
            SExchangePtr getExchangeByID(CommodityTypeType commodity_type, const ExchangeIDType exchange_id) const;
            // �Ϻ� XSHG, ���� XSHE
            SExchangePtr getExchangeByCode(CommodityTypeType commodity_type, const ExchangeCodeType exchange_code) const;
            // ����/���½�����
            ErrorCodeType addExchange(const SExchangePtr& ex);

            // ��ȡ��������Լ�б�
            SContractPtr getStockContractByID(StockAreaType stock_area, const ContractIDType contract_id) const;
            SContractPtr getStockContractByCode(StockAreaType stock_area, const ContractCodeType contract_code) const;
            std::vector<SContractPtr> getContracts(const SExchangePtr& ex) const;
            std::vector<SContractPtr> getContracts(CommodityTypeType commodity_type, const ExchangeIDType exchange_id) const;
            // ����/���½�������Լ
            ErrorCodeType addContract(const SContractPtr& contract);

            // ��ǰʱ���Ƿ���ύί��
            bool curCanOrder(CommodityTypeType commodity_type, const ExchangeIDType exchange_id, const ContractIDType contract_id) const;
            // ��ǰʱ���Ƿ�ɽ���
            bool curCanTrade(CommodityTypeType commodity_type, const ExchangeIDType exchange_id, const ContractIDType contract_id) const;

        private:
            // �����˻��������
            ExchangeHrPtr createExchangeHr(const SExchangePtr& ex);

        private:
            std::map<CommodityTypeType, ExchangeIndex>  m_exchanges;
            mutable rwMutex                             m_mtx_exchange;
        };
    }
}
#endif