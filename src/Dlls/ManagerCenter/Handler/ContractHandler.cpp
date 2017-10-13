#include "ContractHandler.h"
#include "define/struct_extern.h"
#include "define/protocol_error.h"
#include "include/OperationManager/OperationManager.h"

namespace AllTrade {
    namespace NPMgrCenter {

        ContractBaseHandler::ContractBaseHandler()
            : m_modified_cur(true)
        {

        }

        ContractBaseHandler::ContractBaseHandler(const SContractPtr& contract_st)
            : m_contract_st_obj(contract_st)
            , m_modified_cur(true)
        {

        }

        ContractBaseHandler::~ContractBaseHandler()
        {

        }

        AllTrade::PExchangeIDType ContractBaseHandler::getBelongExID() const
        {
            return m_contract_st_obj->exchange_id_;
        }

        AllTrade::PContractIDType ContractBaseHandler::getContractID() const
        {
            return m_contract_st_obj->contract_id_;
        }

        AllTrade::PContractNameType ContractBaseHandler::getContractName() const
        {
            return m_contract_st_obj->contract_name_;
        }

        AllTrade::PContractCodeType ContractBaseHandler::getContractCode() const
        {
            return m_contract_st_obj->contract_code_;
        }

        bool ContractBaseHandler::curCanTrade() const
        {
            return true;
        }

        bool ContractBaseHandler::canTrade(const TimeType time) const
        {
            return true;
        }

        const Feest& ContractBaseHandler::getContractOpenFee() const
        {
            return m_contract_st_obj->open_fee_;
        }

//         const Feest& ContractBaseHandler::getContractCloseYestodayFee() const
//         {
//             return m_contract_st_obj->close_yestoday_fee_;
//         }
// 
//         const Feest& ContractBaseHandler::getContractCloseTodayFee() const
//         {
//             return m_contract_st_obj->close_today_fee_;
//         }

        const Feest& ContractBaseHandler::getContractMargin() const
        {
            return m_contract_st_obj->margin_fee_;
        }

        int ContractBaseHandler::getContractMultiple() const
        {
            return m_contract_st_obj->contract_multiplier_;
        }

        YDouble ContractBaseHandler::getContractMinChUnit() const
        {
            return m_contract_st_obj->min_price_change_;
        }

        ErrorCodeType ContractBaseHandler::serialize()
        {
            writeLock lock(m_mtx_sp);

            // 无修改则无需重复序列化
            if (!m_modified_cur)
                return Err_Succeed;

            if (!OperationManager::COperationManager::instance()->updateContractInfo(m_contract_st_obj))
                return Err_Database;

            m_modified_cur = false;
            return Err_Succeed;
        }

        bool ContractBaseHandler::isModified() const
        {
            return true;
        }

        void ContractBaseHandler::setCurContractModiFlag(bool flag /*= true*/)
        {

        }

        bool ContractBaseHandler::getCurContractModiFlag()
        {
            return true;
        }

        //////////////////////////////////////////////////////////////////////////
        StockContractHandler::StockContractHandler()
            : ContractBaseHandler()
        {

        }

        StockContractHandler::StockContractHandler(const SContractPtr& contract_st)
            : ContractBaseHandler(contract_st)
        {

        }

        StockContractHandler::~StockContractHandler()
        {

        }

        AllTrade::StockAreaType StockContractHandler::getStockArea()
        {
            readLock lock(m_mtx_sp);
            return (std::dynamic_pointer_cast<SStockContract>(m_contract_st_obj))->stock_area_;
        }

        SContractPtr StockContractHandler::getCopyContract() const
        {
            readLock lock(m_mtx_sp);
            SContractPtr new_contract = std::make_shared<SStockContract>(*std::dynamic_pointer_cast<SStockContract>(m_contract_st_obj).get());
            return new_contract;
        }

        AllTrade::StockPlateAreaType StockContractHandler::getContractPlateArea() const
        {
            readLock lock(m_mtx_sp);
            SStockContractPtr new_contract = std::dynamic_pointer_cast<SStockContract>(m_contract_st_obj);
            return new_contract->stock_plate_area_;
        }

    }
}