#include <assert.h>
#include "BlackWhiteManager.h"
#include "define/struct_extern.h"
#include "define/protocol_error.h"
#include "include/OperationManager/OperationManager.h"
#include "utility/utility_fun.h"

using namespace OperationManager;

#include "C:/ng_tools/ng_header_for_log4cxx/ng_header_for_log4cxx.hpp"
#include "C:/ng_tools/ng_header_for_log4cxx/ng_header_for_log4cxx_log_var.hpp"
NG_LOGGER(logger, "BlackWhiteManager");

namespace AllTrade{
    namespace NPMgrCenter {

        BlackWhiteManager::BlackWhiteManager()
        {

        }

        BlackWhiteManager::~BlackWhiteManager()
        {

        }

        void BlackWhiteManager::addStockBlackWhite(const AllTrade::ContractIDType contract_id)
        {
            COperationManager::instance()->addStockBlackWhite(contract_id);
        }

        AllTrade::ErrorCodeType BlackWhiteManager::updateStockBlackWhiteStatus(const ContractIDType contract_id, bool isBlack)
        {
            if (!COperationManager::instance()->updateStockBlackWhiteStatus(contract_id, isBlack))
                return Err_Database;

            return Err_Succeed;
        }

        std::map<AllTrade::PContractIDType, bool> BlackWhiteManager::getAllStockBlackWhiteStatus()
        {
            return COperationManager::instance()->getAllStockBlackWhiteStatus();
        }

        AllTrade::ErrorCodeType BlackWhiteManager::canTradeContract(CommodityTypeType commodity_type, const ExchangeIDType exchange_id, const ContractIDType contract_id) const
        {
            if (COperationManager::instance()->isBlackStock(contract_id))
            {
                LOG4CXX_INFO(logger, "合约为黑名单合约!"LOG_NOVAR(contract_id));
                return Err_Contract_NoTrade;
            }

            return Err_Succeed;
        }

    }
}