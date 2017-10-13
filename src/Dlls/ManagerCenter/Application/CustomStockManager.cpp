#include <assert.h>
#include "CustomStockManager.h"
#include "define/struct_extern.h"
#include "define/protocol_error.h"
#include "include/OperationManager/OperationManager.h"
#include "utility/utility_fun.h"

using namespace OperationManager;

namespace AllTrade{
    namespace NPMgrCenter {

        CustomStockManager::CustomStockManager()
        {

        }

        CustomStockManager::~CustomStockManager()
        {

        }

        AllTrade::ErrorCodeType CustomStockManager::addCustomStock(const AllTrade::UserIDType user_id, const AllTrade::ContractIDType contract_id)
        {
            COperationManager::instance()->addCustomStock(user_id, contract_id);
            return Err_Succeed;
        }

        AllTrade::ErrorCodeType CustomStockManager::removeCustomStock(const AllTrade::UserIDType user_id, const AllTrade::ContractIDType contract_id)
        {
            COperationManager::instance()->removeCustomStock(user_id, contract_id);
            return Err_Succeed;
        }

        std::map<AllTrade::PUserIDType, std::vector<AllTrade::PContractIDType>> CustomStockManager::getAllCustomStock()
        {
            return COperationManager::instance()->getAllCustomStock();
        }

        std::vector<AllTrade::PContractIDType> CustomStockManager::getAllCustomStock(const AllTrade::UserIDType user_id)
        {
            return COperationManager::instance()->getAllCustomStock(user_id);
        }

    }
}