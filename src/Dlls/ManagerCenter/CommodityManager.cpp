#include <assert.h>
#include "CommodityManager.h"
#include "define/struct_extern.h"
#include "define/protocol_error.h"
#include "Handler/ContractHandler.h"
#include "Handler/ExchangeHandler.h"
#include "include/OperationManager/OperationManager.h"

namespace AllTrade{
    namespace NPMgrCenter {

        CommodityManager::CommodityManager()
        {
            std::vector<SExchangePtr> all_exchanges;
            bool bl = OperationManager::COperationManager::instance()->getAllExchange(all_exchanges);
            for (auto item : all_exchanges)
            {
                ExchangeHrPtr ex_hr_ptr = createExchangeHr(item);
                ErrorCodeType err_code = ex_hr_ptr->unserialize();
                if (err_code == Err_Succeed)
                    m_exchanges[item->commodity_type_].addToList(ex_hr_ptr);
            }
        }

        CommodityManager::~CommodityManager()
        {

        }

        std::vector<SExchangePtr> CommodityManager::getExchanges(CommodityTypeType commodity_type) const
        {
            std::vector<SExchangePtr> rslt;
            readLock lock(m_mtx_exchange);
            auto iter = m_exchanges.find(commodity_type);
            if (iter != m_exchanges.end())
            {
                for (auto item : iter->second.getAllExchangeHrs())
                    rslt.push_back(item->getCopyExchange());
            }
            return rslt;
        }

        AllTrade::NPMgrCenter::SExchangePtr CommodityManager::getExchangeByID(CommodityTypeType commodity_type, const ExchangeIDType exchange_id) const
        {
            readLock lock(m_mtx_exchange);
            auto iter = m_exchanges.find(commodity_type);
            if (iter != m_exchanges.end())
            {
                auto ex_hr_ptr = iter->second.getExchangeHrPtrByExchangeID(exchange_id);
                if (ex_hr_ptr)
                    return ex_hr_ptr->getCopyExchange();
            }
            return SExchangePtr();
        }

        AllTrade::NPMgrCenter::SExchangePtr CommodityManager::getExchangeByCode(CommodityTypeType commodity_type, const ExchangeCodeType exchange_code) const
        {
            readLock lock(m_mtx_exchange);
            auto iter = m_exchanges.find(commodity_type);
            if (iter != m_exchanges.end())
            {
                auto ex_hr_ptr = iter->second.getExchangeHrPtrByExchangeCode(exchange_code);
                if (ex_hr_ptr)
                    return ex_hr_ptr->getCopyExchange();
            }
            return SExchangePtr();
        }

        AllTrade::ErrorCodeType CommodityManager::addExchange(const SExchangePtr& ex)
        {
            ExchangeHrPtr ex_hr_ptr = createExchangeHr(ex);

            writeLock lock(m_mtx_exchange);
            ExchangeIndex& tmp = m_exchanges[ex->commodity_type_];

            if (tmp.getExchangeHrPtrByExchangeID(ex->exchange_id_))
                return Error_Exchange_Exist;

            ErrorCodeType err_code = ex_hr_ptr->serialize();
            if (err_code == Err_Succeed)
                tmp.addToList(ex_hr_ptr);

            return err_code;
        }

        AllTrade::NPMgrCenter::SContractPtr CommodityManager::getStockContractByID(StockAreaType stock_area, const ContractIDType contract_id) const
        {
            readLock lock(m_mtx_exchange);
            auto iter = m_exchanges.find(CommodityTypeType::COMMODITY_TYPE_STOCK);
            if (iter != m_exchanges.end())
            {
                for(auto item : iter->second.getAllExchangeHrs())
                {
                    StockExchangeHrPtr ex_hr_ptr = std::dynamic_pointer_cast<StockExchangeHandler>(item);
                    SContractPtr rslt = ex_hr_ptr->getStockContractByID(stock_area, contract_id);
                    if (rslt)
                        return rslt;
                }
            }
            return SContractPtr();
        }

        AllTrade::NPMgrCenter::SContractPtr CommodityManager::getStockContractByCode(StockAreaType stock_area, const ContractCodeType contract_code) const
        {
            readLock lock(m_mtx_exchange);
            auto iter = m_exchanges.find(CommodityTypeType::COMMODITY_TYPE_STOCK);
            if (iter != m_exchanges.end())
            {
                for (auto item : iter->second.getAllExchangeHrs())
                {
                    StockExchangeHrPtr ex_hr_ptr = std::dynamic_pointer_cast<StockExchangeHandler>(item);
                    SContractPtr rslt = ex_hr_ptr->getStockContractByCode(stock_area, contract_code);
                    if (rslt)
                        return rslt;
                }
            }
            return SContractPtr();
        }

        std::vector<SContractPtr> CommodityManager::getContracts(const SExchangePtr& ex) const
        {
            return getContracts(ex->commodity_type_, ex->exchange_id_);
        }

        std::vector<SContractPtr> CommodityManager::getContracts(CommodityTypeType commodity_type, const ExchangeIDType exchange_id) const
        {
            std::vector<SContractPtr> rslt;
            readLock lock(m_mtx_exchange);
            auto iter = m_exchanges.find(commodity_type);
            if (iter != m_exchanges.end())
            {
                ExchangeHrPtr ex_hr_ptr = iter->second.getExchangeHrPtrByExchangeID(exchange_id);
                if (ex_hr_ptr)
                {
                    for (auto item : ex_hr_ptr->getContractHrs())
                        rslt.push_back(item->getCopyContract());
                }
            }
            return rslt;
        }

        AllTrade::ErrorCodeType CommodityManager::addContract(const SContractPtr& contract)
        {
            writeLock lock(m_mtx_exchange);
            ExchangeHrPtr ex_hr_ptr = m_exchanges[contract->commodity_type_].getExchangeHrPtrByExchangeID(contract->exchange_id_);
            if (ex_hr_ptr)
                return ex_hr_ptr->addContract(contract);

            return Err_Unknown;
        }

        bool CommodityManager::curCanOrder(CommodityTypeType commodity_type, const ExchangeIDType exchange_id, const ContractIDType contract_id) const
        {
            readLock lock(m_mtx_exchange);
            auto iter = m_exchanges.find(commodity_type);
            if (iter != m_exchanges.end())
            {
                ExchangeHrPtr ex_hr_ptr = iter->second.getExchangeHrPtrByExchangeID(exchange_id);
                if (ex_hr_ptr)
                    return ex_hr_ptr->curCanOrder();
            }
            return false;
        }

        bool CommodityManager::curCanTrade(CommodityTypeType commodity_type, const ExchangeIDType exchange_id, const ContractIDType contract_id) const
        {
            readLock lock(m_mtx_exchange);
            auto iter = m_exchanges.find(commodity_type);
            if (iter != m_exchanges.end())
            {
                ExchangeHrPtr ex_hr_ptr = iter->second.getExchangeHrPtrByExchangeID(exchange_id);
                if (ex_hr_ptr)
                    return ex_hr_ptr->curCanTrade();
            }
            return false;
        }

        ExchangeHrPtr CommodityManager::createExchangeHr(const SExchangePtr& ex)
        {
            switch (ex->commodity_type_)
            {
            case AllTrade::CommodityTypeType::COMMODITY_TYPE_STOCK:
                return std::make_shared<StockExchangeHandler>(ex);
                break;
			case AllTrade::CommodityTypeType::COMMODITY_TYPE_MARGIN:
				return std::make_shared<StockExchangeHandler>(ex);
				break;
//             case AllTrade::CommodityTypeType::COMMODITY_TYPE_FUTURE_F:
//                 break;
//             case AllTrade::CommodityTypeType::COMMODITY_TYPE_FUTURE_C:
//                 break;
//             case AllTrade::CommodityTypeType::COMMODITY_TYPE_OPTION:
//                 break;
//             case AllTrade::CommodityTypeType::COMMODITY_TYPE_GOODS:
//                 break;
            default:
                assert(0);
                break;
            }
            return ExchangeHrPtr();
        }

    }
}