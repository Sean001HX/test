#include <assert.h>
#include "ForbidTradeManager.h"
#include "define/struct_extern.h"
#include "define/protocol_error.h"
#include "include/OperationManager/OperationManager.h"
#include "utility/utility_fun.h"
#include "../Handler/quotehandler.h"
#include "include/ManagerCenter/ManagerCenter.h"

#include "C:/ng_tools/ng_header_for_log4cxx/ng_header_for_log4cxx.hpp"
#include "C:/ng_tools/ng_header_for_log4cxx/ng_header_for_log4cxx_log_var.hpp"
NG_LOGGER(logger, "PositionRateManager");

using namespace OperationManager;
using namespace AllTrade::NPMgrCenter;

namespace AllTrade{
    namespace NPTradeCenter {

        ForbidTradeManager::ForbidTradeManager()
        {

        }

        ForbidTradeManager::~ForbidTradeManager()
        {

        }

        std::vector<SForbidTradePtr> ForbidTradeManager::getAllForbidTradeStatus()
        {
            return COperationManager::instance()->getAllForbidTradeStatus();
        }

        ErrorCodeType ForbidTradeManager::updateForbidTradeStatus(const SForbidTradePtr& ptr)
        {
            if (!COperationManager::instance()->updateForbidTradeStatus(ptr))
                return Err_Database;

            return Err_Succeed;
        }

        AllTrade::ErrorCodeType ForbidTradeManager::canTrade(const QuoteHrPtr& quote, DirectType dir_type)
        {
            SContractPtr con_ptr = IManagerCenter::instance()->getStockContractByID(StockAreaType::STOCKAREA_TYPE_A, quote->getContractID().c_str());
            SStockContractPtr stock_ptr = std::dynamic_pointer_cast<SStockContract>(con_ptr);
            if (!stock_ptr)
                return Err_Contract_Qry;

            std::vector<SForbidTradePtr> risk_vec = getAllForbidTradeStatus();
            for (auto& risk_item : risk_vec)
            {
                if (!risk_item->bstart_ || risk_item->forbid_trade_op_type_ == FTOT_AllowTrade)
                    continue;

                switch (risk_item->forbid_trade_type_)
                {
                case AllTrade::FTT_LossCorporateStock:
                    if(stock_ptr->display_prop_type_ == DisplayPropTypeType::DPTT_Normal)
                        continue;

                    if ((risk_item->forbid_trade_op_type_ == FTOT_AllowBuy && dir_type == DirectType::DIRECT_BUY)
                        || (risk_item->forbid_trade_op_type_ == FTOT_AllowSell && dir_type == DirectType::DIRECT_SELL))
                        continue;

                    LOG4CXX_INFO(logger, "下单为亏损企业股票!"LOG_NOVAR(risk_item->forbid_trade_op_type_));

                    if (risk_item->forbid_trade_op_type_ == FTOT_AllowSell && dir_type == DirectType::DIRECT_BUY)
                        return Error_User_NoOpen_LossCorp_Buy;
                    else if (risk_item->forbid_trade_op_type_ == FTOT_AllowBuy && dir_type == DirectType::DIRECT_SELL)
                        return Error_User_NoOpen_LossCorp_Sell;
                    else if (risk_item->forbid_trade_op_type_ == FTOT_ForbidTrade)
                        return Error_User_NoOpen_LossCorp_Trade;
                    break;
                case AllTrade::FTT_RiseStopStock:
                    if (!quote->isRiseStop())
                        continue;

                    if ((risk_item->forbid_trade_op_type_ == FTOT_AllowBuy && dir_type == DirectType::DIRECT_BUY)
                        || (risk_item->forbid_trade_op_type_ == FTOT_AllowSell && dir_type == DirectType::DIRECT_SELL))
                        continue;

                    LOG4CXX_INFO(logger, "下单为当前涨停股票!"LOG_NOVAR(quote->getLastPrice())LOG_NOVAR(quote->getRisePrice()));
                    
                    if (risk_item->forbid_trade_op_type_ == FTOT_AllowSell && dir_type == DirectType::DIRECT_BUY)
                        return Error_User_NoOpen_RiseStop_Buy;
                    else if (risk_item->forbid_trade_op_type_ == FTOT_AllowBuy && dir_type == DirectType::DIRECT_SELL)
                        return Error_User_NoOpen_RiseStop_Sell;
                    else if (risk_item->forbid_trade_op_type_ == FTOT_ForbidTrade)
                        return Error_User_NoOpen_RiseStop_Trade;
                    break;
                case AllTrade::FTT_FallStopStock:
                    if (!quote->isFallStop())
                        continue;

                    if ((risk_item->forbid_trade_op_type_ == FTOT_AllowBuy && dir_type == DirectType::DIRECT_BUY)
                        || (risk_item->forbid_trade_op_type_ == FTOT_AllowSell && dir_type == DirectType::DIRECT_SELL))
                        continue;

                    LOG4CXX_INFO(logger, "下单为当前跌停股票!"LOG_NOVAR(quote->getLastPrice())LOG_NOVAR(quote->getFallPrice()));

                    if (risk_item->forbid_trade_op_type_ == FTOT_AllowSell && dir_type == DirectType::DIRECT_BUY)
                        return Error_User_NoOpen_FallStop_Buy;
                    else if (risk_item->forbid_trade_op_type_ == FTOT_AllowBuy && dir_type == DirectType::DIRECT_SELL)
                        return Error_User_NoOpen_FallStop_Sell;
                    else if (risk_item->forbid_trade_op_type_ == FTOT_ForbidTrade)
                        return Error_User_NoOpen_FallStop_Trade;
                    break;
                case AllTrade::FTT_NewStock:
                {
                    int dateSpace = UtilityFun::getDateSpace(stock_ptr->open_datetime_, UtilityFun::getCurrentDate());
                    if (dateSpace > 20)
                        continue;

                    if ((risk_item->forbid_trade_op_type_ == FTOT_AllowBuy && dir_type == DirectType::DIRECT_BUY)
                        || (risk_item->forbid_trade_op_type_ == FTOT_AllowSell && dir_type == DirectType::DIRECT_SELL))
                        continue;

                    LOG4CXX_INFO(logger, "下单为新股!"LOG_NOVAR(stock_ptr->open_datetime_)LOG_NOVAR(dateSpace));

                    if (risk_item->forbid_trade_op_type_ == FTOT_AllowSell && dir_type == DirectType::DIRECT_BUY)
                        return Error_User_NoOpen_New_Buy;
                    else if (risk_item->forbid_trade_op_type_ == FTOT_AllowBuy && dir_type == DirectType::DIRECT_SELL)
                        return Error_User_NoOpen_New_Sell;
                    else if (risk_item->forbid_trade_op_type_ == FTOT_ForbidTrade)
                        return Error_User_NoOpen_New_Trade;
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