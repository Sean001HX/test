#include "ExchangeHandler.h"
#include "ContractHandler.h"
#include "define/protocol_error.h"
#include "include/OperationManager/OperationManager.h"
#include "utility/utility_fun.h"


namespace AllTrade {
    namespace NPMgrCenter{

#pragma region 交易所基类
        ExchangeBaseHandler::ExchangeBaseHandler()
            : m_modified_cur(true)
        {

        }

        ExchangeBaseHandler::ExchangeBaseHandler(const SExchangePtr& exchange_ptr)
            : m_exchange_st_obj(exchange_ptr)
            , m_modified_cur(true)
        {

        }

        ExchangeBaseHandler::~ExchangeBaseHandler()
        {

        }

        const PExchangeIDType ExchangeBaseHandler::getExchangeID() const
        {
            return m_exchange_st_obj->exchange_id_;
        }

        const PExchangeNameType ExchangeBaseHandler::getExchangeName() const
        {
            readLock lock(m_mtx_sp);
            return m_exchange_st_obj->exchange_name_;
        }

        const PExchangeCodeType ExchangeBaseHandler::getExchangeCode() const
        {
            return m_exchange_st_obj->exchange_code_;
        }

        bool ExchangeBaseHandler::curCanOrder() const
        {
            PTimeType cur_time = UtilityFun::getCurrentTime();
            bool overTime = (strcmp(cur_time.c_str(), m_exchange_st_obj->orderable_time_.start_time_) < 0
                        || strcmp(cur_time.c_str(), m_exchange_st_obj->orderable_time_.end_time_) > 0);

            if (overTime)
                return curCanTrade();

            return true;
        }

        bool ExchangeBaseHandler::curCanTrade() const
        {
            PTimeType cur_time = UtilityFun::getCurrentTime();
            std::vector<TimePeriod> tmp = m_exchange_st_obj->tradable_time_;
            for (auto allow_time : tmp)
            {
                if (strcmp(cur_time.c_str(), allow_time.start_time_) < 0
                    || strcmp(cur_time.c_str(), allow_time.end_time_) > 0)
                    continue;
                else
                    return true;
            }
            return false;
        }

        bool ExchangeBaseHandler::canTrade(const TimeType time) const
        {
            return true;
        }

        YDouble ExchangeBaseHandler::getDGCT() const
        {
            readLock lock(m_mtx_sp);
            return m_exchange_st_obj->open_margin_;
        }

        void ExchangeBaseHandler::setExchangeName(const ExchangeNameType name)
        {
            writeLock lock(m_mtx_sp);
            strncpy_s(m_exchange_st_obj->exchange_name_, name, sizeof(m_exchange_st_obj->exchange_name_) - 1);
            m_modified_cur = true;
        }

        AllTrade::ErrorCodeType ExchangeBaseHandler::serialize()
        {
            writeLock lock(m_mtx_sp);

            // 无修改则无需重复序列化
            if (!m_modified_cur)
                return Err_Succeed;

            if (!OperationManager::COperationManager::instance()->updateExchangeInfo(m_exchange_st_obj))
                return Err_Database;

            m_modified_cur = false;
            return Err_Succeed;
        }

        void ExchangeBaseHandler::remove(unsigned int db_ver)
        {

        }

        bool ExchangeBaseHandler::isModified() const
        {
            readLock lock(m_mtx_sp);
            return m_modified_cur;
        }

        void ExchangeBaseHandler::resetCurExModiFlag(bool flag /*= true*/)
        {
            writeLock lock(m_mtx_sp);
            m_modified_cur = flag;
        }

        bool ExchangeBaseHandler::getCurExModiFlag()
        {
            readLock lock(m_mtx_sp);
            return m_modified_cur;
        }

        AllTrade::NPMgrCenter::ContractHrPtr ExchangeBaseHandler::createContractHr(const SContractPtr& contract_ptr)
        {
            switch (contract_ptr->commodity_type_)
            {
            case AllTrade::CommodityTypeType::COMMODITY_TYPE_STOCK:
                return std::make_shared<StockContractHandler>(contract_ptr);
                break;
            default:
                assert(0);
                break;
            }
            return ContractHrPtr();
        }

#pragma endregion

#pragma region 股票交易所

        StockExchangeHandler::StockExchangeHandler()
            : ExchangeBaseHandler()
        {

        }
   
        StockExchangeHandler::StockExchangeHandler(const SExchangePtr& exchange_ptr)
            : ExchangeBaseHandler(exchange_ptr)
        {

        }

        StockExchangeHandler::~StockExchangeHandler()
        {

        }

        SExchangePtr StockExchangeHandler::getCopyExchange() const
        {
            readLock lock(m_mtx_sp);
            SExchangePtr new_ex = std::make_shared<SExchange>(*m_exchange_st_obj.get());
            return new_ex;
        }

        std::vector<ContractHrPtr> StockExchangeHandler::getContractHrs() const
        {
            std::vector<ContractHrPtr> rslt;
            readLock lock(m_mtx_contract);
            for (auto item : m_contracts)
            {
                std::vector<ContractHrPtr> tmp = item.second.getAllContractHrs();
                rslt.insert(rslt.end(), tmp.begin(), tmp.end());
            }
            return rslt;
        }

        bool StockExchangeHandler::isEmpty() const
        {
            readLock lock(m_mtx_contract);
            return m_contracts.empty();
        }

        int StockExchangeHandler::getContractCount() const
        {
            readLock lock(m_mtx_contract);
            return (int)m_contracts.size();
        }

        AllTrade::ErrorCodeType StockExchangeHandler::addContract(const SContractPtr& contract_ptr)
        {
            StockContractHrPtr contract_hr_ptr = std::dynamic_pointer_cast<StockContractHandler>(createContractHr(contract_ptr));
            assert(contract_hr_ptr);

            ErrorCodeType err_code = contract_hr_ptr->serialize();
            if (err_code == Err_Succeed)
            {
                writeLock lock(m_mtx_contract);
                m_contracts[contract_hr_ptr->getStockArea()].addToList(contract_hr_ptr);
                m_modified_contract = true;
            }
            return err_code;
        }

        AllTrade::NPMgrCenter::SContractPtr StockExchangeHandler::getStockContractByID(StockAreaType stock_area, const ContractIDType contract_id) const
        {
            readLock lock(m_mtx_contract);
            auto iter = m_contracts.find(stock_area);
            if (iter == m_contracts.end())
                return SContractPtr();

            ContractHrPtr contract_hr_ptr = iter->second.getContractHrPtrByContractID(contract_id);
            if (contract_hr_ptr)
                return contract_hr_ptr->getCopyContract();

            return SContractPtr();
        }

        AllTrade::NPMgrCenter::SContractPtr StockExchangeHandler::getStockContractByCode(StockAreaType stock_area, const ContractCodeType contract_code) const
        {
            readLock lock(m_mtx_contract);
            auto iter = m_contracts.find(stock_area);
            if (iter == m_contracts.end())
                return SContractPtr();

            ContractHrPtr ptr = iter->second.getContractHrPtrByContractCode(contract_code);
            if (ptr)
                return ptr->getCopyContract();

            return SContractPtr();
        }

        AllTrade::ErrorCodeType StockExchangeHandler::delContract(StockAreaType stock_area, const ContractIDType contract_id)
        {
            writeLock lock(m_mtx_contract);
            auto iter = m_contracts.find(stock_area);
            if (iter == m_contracts.end())
                return Err_Unknown;

            iter->second.removefromList(contract_id);
            return Err_Succeed;
        }

        AllTrade::ErrorCodeType StockExchangeHandler::unserialize()
        {
            writeLock lock(m_mtx_sp);

            std::vector<SStockContractPtr> stock_contract_vec;
            if (!OperationManager::COperationManager::instance()->getStockAllContract(stock_contract_vec, m_exchange_st_obj->exchange_id_))
                return Err_Database;

            for (auto item : stock_contract_vec)
                addContract(item);

            m_modified_contract = true;
            return Err_Succeed;
        }
        
#pragma endregion
}

}
