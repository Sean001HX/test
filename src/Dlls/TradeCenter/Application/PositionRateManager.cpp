#include <assert.h>
#include "PositionRateManager.h"
#include "define/struct_extern.h"
#include "define/protocol_error.h"
#include "include/OperationManager/OperationManager.h"
#include "utility/utility_fun.h"
#include "include/ManagerCenter/ManagerCenter.h"
#include "../Handler/positionhandler.h"
#include "../Handler/positionlistmanager.h"

#include "C:/ng_tools/ng_header_for_log4cxx/ng_header_for_log4cxx.hpp"
#include "C:/ng_tools/ng_header_for_log4cxx/ng_header_for_log4cxx_log_var.hpp"
NG_LOGGER(logger, "PositionRateManager");

using namespace OperationManager;
using namespace AllTrade::NPMgrCenter;

namespace AllTrade{
    namespace NPTradeCenter {

        PositionRateManager::PositionRateManager()
        {

        }

        PositionRateManager::~PositionRateManager()
        {

        }

        std::vector<AllTrade::NPTradeCenter::SPositionRatePtr> PositionRateManager::getAllPositionRateStatus()
        {
            return COperationManager::instance()->getPositionRateStatus();;
        }

        AllTrade::ErrorCodeType PositionRateManager::updatePositionRateStatus(const AllTrade::NPTradeCenter::SPositionRatePtr& ptr)
        {
            if (!COperationManager::instance()->updatePositionRateStatus(ptr))
                return Err_Database;

            return Err_Succeed;
        }

        AllTrade::ErrorCodeType PositionRateManager::canTrade(const UserIDType user_id, const ContractIDType contract_id, YDouble order_freeze_money)
        {
            SAccountPtr acc_ptr = IManagerCenter::instance()->getAccountByID(user_id);
            if (!acc_ptr) return Error_User_Exist;

            SMoneyInfoPtr money_ptr = IManagerCenter::instance()->getMoneyInfoByLoginName(acc_ptr->login_name_);
            if (!money_ptr) return Err_Unknown;

            YDouble all_money = money_ptr->getCanUse() + money_ptr->order_freeze_;

            if (all_money <= 0.0) return Err_Money_NotEnough;

            // 同一股票持仓,创业板持仓
            YDouble same_stock_pos_money(order_freeze_money), second_all_pos_money(0);
            std::vector<PositionHrPtr> posit_hr_ptrs = PositionListManager::instance()->getPositionHrsByUserID(user_id);
            for (auto& posit_item : posit_hr_ptrs)
            {
                YDouble pos_last_price(posit_item->getLastPrice());// 市值

                if (pos_last_price == 0.0)
                    pos_last_price += posit_item->getTradeAvePrice() * posit_item->getPositionAllVol();

                all_money += pos_last_price;
                if (strcmp(posit_item->getContractID().c_str(), contract_id) == 0)
                    same_stock_pos_money += pos_last_price;
     
                auto con_ptr = AllTrade::NPMgrCenter::IManagerCenter::instance()->getStockContractByID(StockAreaType::STOCKAREA_TYPE_A, posit_item->getContractID().c_str());
                auto stock_con_ptr = std::dynamic_pointer_cast<AllTrade::NPMgrCenter::SStockContract>(con_ptr);
                if (stock_con_ptr && stock_con_ptr->stock_plate_area_ == StockPlateAreaType::SPAT_Second_Board)
                    second_all_pos_money += pos_last_price;
            }
            auto con_ptr = AllTrade::NPMgrCenter::IManagerCenter::instance()->getStockContractByID(StockAreaType::STOCKAREA_TYPE_A, contract_id);
            auto stock_con_ptr = std::dynamic_pointer_cast<AllTrade::NPMgrCenter::SStockContract>(con_ptr);
            if (stock_con_ptr && stock_con_ptr->stock_plate_area_ == StockPlateAreaType::SPAT_Second_Board)
                second_all_pos_money += order_freeze_money;

            std::vector<AllTrade::NPTradeCenter::SPositionRatePtr> pos_rate_vec = getAllPositionRateStatus();
            for (auto& pos_rate_ptr : pos_rate_vec)
            {
                if (!pos_rate_ptr->bstart_)
                    continue;

                switch (pos_rate_ptr->position_rate_type_)
                {
                case AllTrade::PRT_SameStock:
                    if ((same_stock_pos_money * 100) / all_money >= pos_rate_ptr->position_rate_)
                    {
                        LOG4CXX_INFO(logger, "达到同一股票持仓比例风控线!"LOG_NOVAR(user_id)LOG_NOVAR(contract_id)
                            LOG_NOVAR(same_stock_pos_money)
                            LOG_NOVAR(order_freeze_money)
                            LOG_NOVAR(all_money)
                            LOG_NOVAR(pos_rate_ptr->position_rate_));
                        return Error_User_NoOpen_SameStock;
                    }
                    break;
                case  AllTrade::PRT_Second_Board:
                    if (stock_con_ptr->stock_plate_area_ != StockPlateAreaType::SPAT_Second_Board)
                        break;

                    if ((second_all_pos_money * 100) / all_money >= pos_rate_ptr->position_rate_)
                    {
                        LOG4CXX_INFO(logger, "达到创业板持仓比例风控线!"LOG_NOVAR(user_id)LOG_NOVAR(contract_id)
                            LOG_NOVAR(second_all_pos_money)
                            LOG_NOVAR(order_freeze_money)
                            LOG_NOVAR(all_money)
                            LOG_NOVAR(pos_rate_ptr->position_rate_));
                        return Error_User_NoOpen_Second_Board;
                    }
                    break;
                default:
                    assert(0);
                    break;
                }
            }

            return Err_Succeed;
        }

    }
}