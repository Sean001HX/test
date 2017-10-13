#include <assert.h>
#include <boost\format.hpp>
#include <boost\algorithm\string.hpp>
#include <functional>
#include <sstream>
#include "DBOpTradeCenter.h"
#include "define/struct_extern.h"
#include "include/DBAccess/db_access.h"
#include "define/table_define.h"
#include <string>
#include "C:/ng_tools/ng_header_for_log4cxx/ng_header_for_log4cxx.hpp"
#include "C:/ng_tools/ng_header_for_log4cxx/ng_header_for_log4cxx_log_var.hpp"
NG_LOGGER(logger, "DBOpManagerCenter");

using namespace AllTrade;
using namespace AllTrade::NPTradeCenter;
using namespace AllTrade::NPMgrCenter;
using namespace DBAccess;


namespace OperationManager{

    DBOpTradeCenter::DBOpTradeCenter()
    {

    }

    DBOpTradeCenter::~DBOpTradeCenter()
    {

    }

    bool DBOpTradeCenter::initAllTable()
    {

        return createStockOrderInfo()
//             && createForeignFutureOrderInfo()
//             && createChinaFutureOrderInfo()
            && createStockTradeInfo()
//             && createForeignFutureTradeInfo()
//             && createChinaFutureTradeInfo()
            && createStockPositionInfo()
//             && createForeignFuturePositionInfo()
//             && createChinaFuturePositionInfo()
            && createTradeFee()
            && createSettle()
            && createGlobalData()
            && createStockBlackWhite()
            && createForbidTrade()
            && createPositionRate()
            && createRiskRecord()
			&& createHistoryRiskRecord()
			
			&& createMarginPositionTable()
			&& createMarginTradeTable()
			&& createMarginOrderTable()
			&& createMarginInfoTable()
			&& createMarginLeftTable();
    }

    bool DBOpTradeCenter::updateOrderInfo(const AllTrade::NPTradeCenter::OrderInfoPtr& order_ptr, const AllTrade::UserIDType user_id)
    {
        switch (order_ptr->commodity_type_)
        {
        case AllTrade::CommodityTypeType::COMMODITY_TYPE_STOCK:
            return updateStockOrderInfo(std::dynamic_pointer_cast<StockOrderInfo>(order_ptr), user_id);
            break;
        case AllTrade::CommodityTypeType::COMMODITY_TYPE_FUTURE_F:
            return updateForeignFutureOrderInfo(std::dynamic_pointer_cast<ForeignFutureOrderInfo>(order_ptr), user_id);
            break;
        case AllTrade::CommodityTypeType::COMMODITY_TYPE_FUTURE_C:
            return updateChinaFutureOrderInfo(std::dynamic_pointer_cast<ChinaFutureOrderInfo>(order_ptr), user_id);
            break;
        case AllTrade::CommodityTypeType::COMMODITY_TYPE_OPTION:
            break;
        case AllTrade::CommodityTypeType::COMMODITY_TYPE_GOODS:
            break;

		case AllTrade::CommodityTypeType::COMMODITY_TYPE_MARGIN:
			return updateMarginOrderTable(std::dynamic_pointer_cast<MarginOrderInfo>(order_ptr), user_id);
			break;
			
        default:
            assert(0);
            break;
        }
        return false;
    }

    bool DBOpTradeCenter::addTradeRecord(const AllTrade::NPTradeCenter::TradeInfoPtr& trade_ptr, const AllTrade::UserIDType user_id)
    {
        switch (trade_ptr->commodity_type_)
        {
        case AllTrade::CommodityTypeType::COMMODITY_TYPE_STOCK:
            return addStockTradeRecord(std::dynamic_pointer_cast<StockTradeInfo>(trade_ptr), user_id);
            break;
        case AllTrade::CommodityTypeType::COMMODITY_TYPE_FUTURE_F:
            return addForeignFutureTradeRecord(std::dynamic_pointer_cast<ForeignFutureTradeInfo>(trade_ptr), user_id);
            break;
        case AllTrade::CommodityTypeType::COMMODITY_TYPE_FUTURE_C:
            return addChinaFutureTradeRecord(std::dynamic_pointer_cast<ChinaFutureTradeInfo>(trade_ptr), user_id);
            break;
        case AllTrade::CommodityTypeType::COMMODITY_TYPE_OPTION:
            break;
        case AllTrade::CommodityTypeType::COMMODITY_TYPE_GOODS:
            break;

		case AllTrade::CommodityTypeType::COMMODITY_TYPE_MARGIN:
			return updateMarginTradeTable(std::dynamic_pointer_cast<MarginTradeInfo>(trade_ptr), user_id);
			
			break;
        default:
            assert(0);
            break;
        }
        return false;
    }

    bool DBOpTradeCenter::updatePositionInfo(const AllTrade::NPTradeCenter::PositionInfoPtr& position_ptr, const AllTrade::UserIDType user_id)
    {
        switch (position_ptr->commodity_type_)
        {
        case AllTrade::CommodityTypeType::COMMODITY_TYPE_STOCK:
            return updateStockPositionInfo(std::dynamic_pointer_cast<StockPositionInfo>(position_ptr), user_id);
            break;
        case AllTrade::CommodityTypeType::COMMODITY_TYPE_FUTURE_F:
            return updateForeignFuturePositionInfo(std::dynamic_pointer_cast<ForeignFuturePositionInfo>(position_ptr), user_id);
            break;
        case AllTrade::CommodityTypeType::COMMODITY_TYPE_FUTURE_C:
            return updateChinaFuturePositionInfo(std::dynamic_pointer_cast<ChinaFuturePositionInfo>(position_ptr), user_id);
            break;
        case AllTrade::CommodityTypeType::COMMODITY_TYPE_OPTION:
            break;
        case AllTrade::CommodityTypeType::COMMODITY_TYPE_GOODS:
            break;

		case AllTrade::CommodityTypeType::COMMODITY_TYPE_MARGIN:
			return updateMarginPositionTable(std::dynamic_pointer_cast<MarginPositionInfo>(position_ptr), user_id);
			break;
        default:
            assert(0);
            break;
        }
        return false;
    }

    bool DBOpTradeCenter::deletePositionInfo(const AllTrade::NPTradeCenter::PositionInfoPtr& position_ptr, const AllTrade::UserIDType user_id)
    {
        switch (position_ptr->commodity_type_)
        {
        case AllTrade::CommodityTypeType::COMMODITY_TYPE_STOCK:
            return deleteStockPositionInfo(std::dynamic_pointer_cast<StockPositionInfo>(position_ptr), user_id);
            break;

		case AllTrade::CommodityTypeType::COMMODITY_TYPE_MARGIN:
			return deleteMarginPositionInfo(std::dynamic_pointer_cast<MarginPositionInfo>(position_ptr), user_id);
			break;
//         case AllTrade::CommodityTypeType::COMMODITY_TYPE_FUTURE_F:
//             return deleteForeignFuturePositionInfo(std::dynamic_pointer_cast<ForeignFuturePositionInfo>(position_ptr), user_id);
//             break;
//         case AllTrade::CommodityTypeType::COMMODITY_TYPE_FUTURE_C:
//             return deleteChinaFuturePositionInfo(std::dynamic_pointer_cast<ChinaFuturePositionInfo>(position_ptr), user_id);
//             break;
//         case AllTrade::CommodityTypeType::COMMODITY_TYPE_OPTION:
//             break;
//         case AllTrade::CommodityTypeType::COMMODITY_TYPE_GOODS:
//             break;
        default:
            assert(0);
            break;
        }
        return false;

    }

    bool DBOpTradeCenter::getStockOrderInfo(std::map<AllTrade::PUserIDType, std::vector<AllTrade::NPTradeCenter::StockOrderPtr>>& stockOrder)
	{
		CDBHandler *phandler = AllocDBHandler();
		if (!phandler)
			return false;

		HxSqlRes res = NULL;
		int errCode = 0;
		int recNum = 0;

		std::stringstream sstr;
		sstr << "SELECT * FROM " << gszStockOrderTableName<< " where "
			<< gszStockOrderColName[SOT_OrderState] << " != " << (int)AllTrade::OrderStateType::ORDER_STATE_FAIL << " and "
			<< gszStockOrderColName[SOT_OrderState] << " != " << (int)AllTrade::OrderStateType::ORDER_STATE_DELETED << " and "
			<< gszStockOrderColName[SOT_OrderState] << " != " << (int)AllTrade::OrderStateType::ORDER_STATE_FINISHED;

		errCode = phandler->QuerySql(sstr.str().c_str(), res, true);
        
        if (errCode == 0 && res)
		{
			HxResRow row = NULL;
			AllTrade::GUIDType userId;

			while (row = phandler->FetchRow(res))
			{
				AllTrade::NPTradeCenter::StockOrderPtr ptr= std::make_shared<StockOrderInfo>();
				char *pchar;
				strncpy_s(ptr->order_stream_, phandler->FetchField(row, SOT_OrderStream), sizeof(ptr->order_stream_) - 1);
                strncpy_s(ptr->order_id_, phandler->FetchField(row, SOT_OrderID), sizeof(ptr->order_id_) - 1);

                strncpy_s(userId, phandler->FetchField(row, SOT_UserID), sizeof(AllTrade::GUIDType) - 1);

                strncpy_s(ptr->contract_id_, phandler->FetchField(row, SOT_ContractID), sizeof(ptr->contract_id_) - 1);
				pchar = phandler->FetchField(row, SOT_OrderState);
				ptr->order_state_ = (OrderStateType)(atoi(pchar));

				pchar = phandler->FetchField(row, SOT_OrderStateExplain);
				ptr->orser_state_explain_ = (OrderStateExplainType)(atoi(pchar));
                strncpy_s(ptr->order_ref_, phandler->FetchField(row, SOT_OrderRef), sizeof(ptr->order_ref_) - 1);

                strncpy_s(ptr->order_localtmp_ref_, phandler->FetchField(row, SOT_LoclaTmp_OrderRef), sizeof(ptr->order_localtmp_ref_) - 1);

                strncpy_s(ptr->shadow_order_id_, phandler->FetchField(row, SOT_ShadowOrderID), sizeof(ptr->shadow_order_id_) - 1);
                strncpy_s(ptr->generate_datetime_, phandler->FetchField(row, SOT_GenerateDateTime), sizeof(ptr->generate_datetime_) - 1);
                strncpy_s(ptr->update_datetime_, phandler->FetchField(row, SOT_UpdateDateTime), sizeof(ptr->update_datetime_) - 1);
				pchar = phandler->FetchField(row, SOT_Direct);
				ptr->direct_type_ = (DirectType)(atoi(pchar));

				pchar = phandler->FetchField(row, SOT_CurrencyRate);
				ptr->currency_rate_ = atof(pchar);
                strncpy_s(ptr->currency_id_, phandler->FetchField(row, SOT_CurrencyID), sizeof(ptr->currency_id_) - 1);
			
				pchar = phandler->FetchField(row, SOT_OrderPrice);
				ptr->order_price_ = atof(pchar);
				pchar = phandler->FetchField(row, SOT_OrderVol);
				ptr->order_vol_ = atoi(pchar);
				pchar = phandler->FetchField(row, SOT_EffectedVol);
				ptr->effected_vol_ = atoi(pchar);
                pchar = phandler->FetchField(row, SOT_TradeVol);
                ptr->trade_vol_ = atoi(pchar);
                pchar = phandler->FetchField(row, SOT_BFreezePosition);
                ptr->b_freeze_position_ = atoi(pchar) == 1;
                pchar = phandler->FetchField(row, SOT_FreezeMoney);
                ptr->freeze_money_ = atof(pchar);
                pchar = phandler->FetchField(row, SOT_BFreezeMoney);
                ptr->b_freeze_money_ = atoi(pchar) == 1;
				pchar = phandler->FetchField(row, SOT_OrderType);
				ptr->order_type_ = (OrderTypeType)(atoi(pchar));
				pchar = phandler->FetchField(row, SOT_OrderTradeMode);
				ptr->order_trade_mode_ = (OrderTradeModeType)(atoi(pchar));

                pchar = phandler->FetchField(row, SOT_OrderTradePrice);
                ptr->order_trade_price_ = atof(pchar);
                pchar = phandler->FetchField(row, SOT_OrderPositionCost);
                ptr->position_cost_ = atof(pchar);

                strncpy_s(ptr->system_order_id_, phandler->FetchField(row, SOT_SystemOrderID), sizeof(ptr->system_order_id_) - 1);
                strncpy_s(ptr->exchange_id_, phandler->FetchField(row, SOT_ExchangeID), sizeof(ptr->exchange_id_) - 1);

				pchar = phandler->FetchField(row, SOT_ApiType);
				ptr->api_type_ = (ApiTypeType)(atoi(pchar));
				pchar = phandler->FetchField(row, SOT_OperatorType);
				ptr->op_type_ = (OperatorTradeType)(atoi(pchar));
				pchar = phandler->FetchField(row, SOT_OrderMode);
				ptr->order_mode_ = (OrderModeType)(atoi(pchar));
                pchar = phandler->FetchField(row, SOT_StockArea);
                ptr->stock_area_ = (StockAreaType)(atoi(pchar));
//                 strncpy_s(ptr->valid_datetime_, phandler->FetchField(row, SOT_ValidDateTime), sizeof(ptr->valid_datetime_) - 1);
                ptr->commodity_type_ = CommodityTypeType::COMMODITY_TYPE_STOCK;

                stockOrder[userId].push_back(ptr);
			}
		}

		phandler->ReleaseRecords(res);
		DBAccess::FreeDBHandler(phandler);
		return errCode == 0;
		
	}

    std::vector<AllTrade::NPTradeCenter::OrderInfoPtr> DBOpTradeCenter::getStockOrderHistory(const AllTrade::UserIDType user_id, const AllTrade::DateType start_time, const AllTrade::DateType end_time)
    {
        std::vector<AllTrade::NPTradeCenter::OrderInfoPtr> rslt;
        CDBHandler *phandler = AllocDBHandler();
        if (!phandler)
            return rslt;

        HxSqlRes res = NULL;
        int errCode = 0;
        int recNum = 0;

        std::stringstream sstr;
        sstr << "SELECT * FROM " << gszStockOrderTableName
            << " where " << gszStockOrderColName[SOT_UserID] << " = '" << user_id << "'"
            << " and " << gszStockOrderColName[SOT_GenerateDateTime] << " >= '" << start_time << "'"
            << " and " << gszStockOrderColName[SOT_GenerateDateTime] << " <= '" << end_time << "'";

        std::string tmp = sstr.str();
        errCode = phandler->QuerySql(sstr.str().c_str(), res, true);

        if (errCode == 0 && res)
        {
            HxResRow row = NULL;
            AllTrade::GUIDType userId;

            while (row = phandler->FetchRow(res))
            {
                AllTrade::NPTradeCenter::StockOrderPtr ptr = std::make_shared<StockOrderInfo>();
                char *pchar;
                strncpy_s(ptr->order_stream_, phandler->FetchField(row, SOT_OrderStream), sizeof(ptr->order_stream_) - 1);
                strncpy_s(ptr->order_id_, phandler->FetchField(row, SOT_OrderID), sizeof(ptr->order_id_) - 1);

                strncpy_s(userId, phandler->FetchField(row, SOT_UserID), sizeof(AllTrade::GUIDType) - 1);

                strncpy_s(ptr->contract_id_, phandler->FetchField(row, SOT_ContractID), sizeof(ptr->contract_id_) - 1);
                pchar = phandler->FetchField(row, SOT_OrderState);
                ptr->order_state_ = (OrderStateType)(atoi(pchar));

                pchar = phandler->FetchField(row, SOT_OrderStateExplain);
                ptr->orser_state_explain_ = (OrderStateExplainType)(atoi(pchar));
                strncpy_s(ptr->order_ref_, phandler->FetchField(row, SOT_OrderRef), sizeof(ptr->order_ref_) - 1);

                strncpy_s(ptr->order_localtmp_ref_, phandler->FetchField(row, SOT_LoclaTmp_OrderRef), sizeof(ptr->order_localtmp_ref_) - 1);

                strncpy_s(ptr->shadow_order_id_, phandler->FetchField(row, SOT_ShadowOrderID), sizeof(ptr->shadow_order_id_) - 1);
                strncpy_s(ptr->generate_datetime_, phandler->FetchField(row, SOT_GenerateDateTime), sizeof(ptr->generate_datetime_) - 1);
                strncpy_s(ptr->update_datetime_, phandler->FetchField(row, SOT_UpdateDateTime), sizeof(ptr->update_datetime_) - 1);
                pchar = phandler->FetchField(row, SOT_Direct);
                ptr->direct_type_ = (DirectType)(atoi(pchar));

                pchar = phandler->FetchField(row, SOT_CurrencyRate);
                ptr->currency_rate_ = atof(pchar);
                strncpy_s(ptr->currency_id_, phandler->FetchField(row, SOT_CurrencyID), sizeof(ptr->currency_id_) - 1);

                pchar = phandler->FetchField(row, SOT_OrderPrice);
                ptr->order_price_ = atof(pchar);
                pchar = phandler->FetchField(row, SOT_OrderVol);
                ptr->order_vol_ = atoi(pchar);
                pchar = phandler->FetchField(row, SOT_EffectedVol);
                ptr->effected_vol_ = atoi(pchar);
                pchar = phandler->FetchField(row, SOT_TradeVol);
                ptr->trade_vol_ = atoi(pchar);
                pchar = phandler->FetchField(row, SOT_BFreezePosition);
                ptr->b_freeze_position_ = atoi(pchar) == 1;
                pchar = phandler->FetchField(row, SOT_FreezeMoney);
                ptr->freeze_money_ = atof(pchar);
                pchar = phandler->FetchField(row, SOT_BFreezeMoney);
                ptr->b_freeze_position_ = atoi(pchar) == 1;
                pchar = phandler->FetchField(row, SOT_OrderType);
                ptr->order_type_ = (OrderTypeType)(atoi(pchar));
                pchar = phandler->FetchField(row, SOT_OrderTradeMode);
                ptr->order_trade_mode_ = (OrderTradeModeType)(atoi(pchar));

                pchar = phandler->FetchField(row, SOT_OrderTradePrice);
                ptr->order_trade_price_ = atof(pchar);
                pchar = phandler->FetchField(row, SOT_OrderPositionCost);
                ptr->position_cost_ = atof(pchar);

                strncpy_s(ptr->system_order_id_, phandler->FetchField(row, SOT_SystemOrderID), sizeof(ptr->system_order_id_) - 1);
                strncpy_s(ptr->exchange_id_, phandler->FetchField(row, SOT_ExchangeID), sizeof(ptr->exchange_id_) - 1);

                pchar = phandler->FetchField(row, SOT_ApiType);
                ptr->api_type_ = (ApiTypeType)(atoi(pchar));
                pchar = phandler->FetchField(row, SOT_OperatorType);
                ptr->op_type_ = (OperatorTradeType)(atoi(pchar));
                pchar = phandler->FetchField(row, SOT_OrderMode);
                ptr->order_mode_ = (OrderModeType)(atoi(pchar));
                pchar = phandler->FetchField(row, SOT_StockArea);
                ptr->stock_area_ = (StockAreaType)(atoi(pchar));
//                 strncpy_s(ptr->valid_datetime_, phandler->FetchField(row, SOT_ValidDateTime), sizeof(ptr->valid_datetime_) - 1);
                ptr->commodity_type_ = CommodityTypeType::COMMODITY_TYPE_STOCK;

                rslt.push_back(ptr);
            }
        }

        phandler->ReleaseRecords(res);
        DBAccess::FreeDBHandler(phandler);
        return rslt;
    }

    bool DBOpTradeCenter::getStockTradeRecord(std::map<AllTrade::PUserIDType, AllTrade::NPTradeCenter::StockTradePtr>& tradeOrder)
	{
		CDBHandler *phandler = AllocDBHandler();
		if (!phandler)
			return false;

		HxSqlRes res = NULL;
		int errCode = 0;
		int recNum = 0;

		std::stringstream sstr;
		sstr << "SELECT * FROM " << gszStockTradeTableName;

		errCode = phandler->QuerySql(sstr.str().c_str(), res, true);

		if (errCode == 0 && res)
		{
			HxResRow row = NULL;
			AllTrade::GUIDType userId;

			while (row = phandler->FetchRow(res))
			{
				AllTrade::NPTradeCenter::StockTradePtr ptr = std::make_shared<StockTradeInfo>();
				char *pchar;

                strncpy_s(ptr->trade_id_, phandler->FetchField(row, STT_TradeID), sizeof(ptr->trade_id_) - 1);
                strncpy_s(ptr->shadow_trade_id_, phandler->FetchField(row, STT_ShadowTradeID), sizeof(ptr->shadow_trade_id_) - 1);
                strncpy_s(ptr->order_stream_, phandler->FetchField(row, STT_OrderStream), sizeof(ptr->order_stream_) - 1);

                strncpy_s(ptr->position_id_, phandler->FetchField(row, STT_PositionID), sizeof(ptr->position_id_) - 1);
                strncpy_s(userId, phandler->FetchField(row, STT_UserID), sizeof(userId) - 1);

                strncpy_s(ptr->exchange_id_, phandler->FetchField(row, STT_ExchangeID), sizeof(ptr->exchange_id_) - 1);
                strncpy_s(ptr->contract_id_, phandler->FetchField(row, STT_ContractID), sizeof(ptr->contract_id_) - 1);
                strncpy_s(ptr->generate_datetime_, phandler->FetchField(row, STT_GenerateDateTime), sizeof(ptr->generate_datetime_) - 1);

				pchar = phandler->FetchField(row, STT_Direct);
				ptr->direct_type_ = (DirectType)(atoi(pchar));
				pchar = phandler->FetchField(row, STT_TradeVol);
				ptr->volume_ = atoi(pchar);

				pchar = phandler->FetchField(row, STT_CurrencyRate);
				ptr->currency_rate_ = atof(pchar);
                strncpy_s(ptr->currency_id_, phandler->FetchField(row, STT_CurrencyID), sizeof(ptr->currency_id_) - 1);
				pchar = phandler->FetchField(row, STT_TradeAvePrice);
				ptr->trade_price_ = atof(pchar);
				pchar = phandler->FetchField(row, STT_CloseProfit);
				ptr->close_profit_ = atof(pchar);
				pchar = phandler->FetchField(row, STT_OperatorType);
				ptr->op_type_ = (OperatorTradeType)(atoi(pchar));
                ptr->commodity_type_ = CommodityTypeType::COMMODITY_TYPE_STOCK;
                pchar = phandler->FetchField(row, STT_StockArea);
                ptr->stock_area_ = (StockAreaType)atoi(pchar);

                pchar = phandler->FetchField(row, STT_TradeFee);
                ptr->trade_fee_ = atof(pchar);
                pchar = phandler->FetchField(row, STT_StampFee);
                ptr->stamp_fee_ = atof(pchar);
                pchar = phandler->FetchField(row, STT_TransferFee);
                ptr->transfer_fee_ = atof(pchar);
                pchar = phandler->FetchField(row, STT_InfomatchFee);
                ptr->infomatch_fee_ = atof(pchar);

				tradeOrder[userId] = ptr;
			}
		}

		phandler->ReleaseRecords(res);
		DBAccess::FreeDBHandler(phandler);
		return errCode == 0;
	}

    std::vector<AllTrade::NPTradeCenter::TradeInfoPtr> DBOpTradeCenter::getStockTradeHistory(const AllTrade::UserIDType user_id, const AllTrade::DateType start_time, const AllTrade::DateType end_time)
    {
        std::vector<AllTrade::NPTradeCenter::TradeInfoPtr> rslt;
        CDBHandler *phandler = AllocDBHandler();
        if (!phandler)
            return rslt;

        HxSqlRes res = NULL;
        int errCode = 0;
        int recNum = 0;

        std::stringstream sstr;
        sstr << "SELECT * FROM " << gszStockTradeTableName 
            << " where " << gszStockTradeColName[STT_UserID] << " = '" << user_id << "'"
            << " and " << gszStockTradeColName[STT_GenerateDateTime] << " >= '" << start_time << "'"
            << " and " << gszStockTradeColName[STT_GenerateDateTime] << " <= '" << end_time << "'";

        errCode = phandler->QuerySql(sstr.str().c_str(), res, true);

        if (errCode == 0 && res)
        {
            HxResRow row = NULL;
            AllTrade::GUIDType userId;

            while (row = phandler->FetchRow(res))
            {
                AllTrade::NPTradeCenter::StockTradePtr ptr = std::make_shared<StockTradeInfo>();
                char *pchar;

                strncpy_s(ptr->trade_id_, phandler->FetchField(row, STT_TradeID), sizeof(ptr->trade_id_) - 1);
                strncpy_s(ptr->shadow_trade_id_, phandler->FetchField(row, STT_ShadowTradeID), sizeof(ptr->shadow_trade_id_) - 1);
                strncpy_s(ptr->order_stream_, phandler->FetchField(row, STT_OrderStream), sizeof(ptr->order_stream_) - 1);

                strncpy_s(ptr->position_id_, phandler->FetchField(row, STT_PositionID), sizeof(ptr->position_id_) - 1);
                strncpy_s(userId, phandler->FetchField(row, STT_UserID), sizeof(userId) - 1);

                strncpy_s(ptr->exchange_id_, phandler->FetchField(row, STT_ExchangeID), sizeof(ptr->exchange_id_) - 1);
                strncpy_s(ptr->contract_id_, phandler->FetchField(row, STT_ContractID), sizeof(ptr->contract_id_) - 1);
                strncpy_s(ptr->generate_datetime_, phandler->FetchField(row, STT_GenerateDateTime), sizeof(ptr->generate_datetime_) - 1);

                pchar = phandler->FetchField(row, STT_Direct);
                ptr->direct_type_ = (DirectType)(atoi(pchar));
                pchar = phandler->FetchField(row, STT_TradeVol);
                ptr->volume_ = atoi(pchar);

                pchar = phandler->FetchField(row, STT_CurrencyRate);
                ptr->currency_rate_ = atof(pchar);
                strncpy_s(ptr->currency_id_, phandler->FetchField(row, STT_CurrencyID), sizeof(ptr->currency_id_) - 1);
                pchar = phandler->FetchField(row, STT_TradeAvePrice);
                ptr->trade_price_ = atof(pchar);
                pchar = phandler->FetchField(row, STT_CloseProfit);
                ptr->close_profit_ = atof(pchar);
                pchar = phandler->FetchField(row, STT_OperatorType);
                ptr->op_type_ = (OperatorTradeType)(atoi(pchar));
                ptr->commodity_type_ = CommodityTypeType::COMMODITY_TYPE_STOCK;
                pchar = phandler->FetchField(row, STT_StockArea);
                ptr->stock_area_ = (StockAreaType)atoi(pchar);

                pchar = phandler->FetchField(row, STT_TradeFee);
                ptr->trade_fee_ = atof(pchar);
                pchar = phandler->FetchField(row, STT_StampFee);
                ptr->stamp_fee_ = atof(pchar);
                pchar = phandler->FetchField(row, STT_TransferFee);
                ptr->transfer_fee_ = atof(pchar);
                pchar = phandler->FetchField(row, STT_InfomatchFee);
                ptr->infomatch_fee_ = atof(pchar);

                rslt.push_back(ptr);
            }
        }

        phandler->ReleaseRecords(res);
        DBAccess::FreeDBHandler(phandler);
        return rslt;
    }

    bool DBOpTradeCenter::getStockPositionInfo(std::map<AllTrade::PUserIDType, std::vector<AllTrade::NPTradeCenter::StockPositionPtr>>& posiOrder)
	{
		CDBHandler *phandler = AllocDBHandler();
		if (!phandler)
			return false;

		HxSqlRes res = NULL;
		int errCode = 0;
		int recNum = 0;

		std::stringstream sstr;
		sstr << "SELECT * FROM " << gszStockPositionTableName;

		errCode = phandler->QuerySql(sstr.str().c_str(), res, true);

		if (errCode == 0 && res)
		{
			HxResRow row = NULL;
			AllTrade::GUIDType userId;

			while (row = phandler->FetchRow(res))
			{
				AllTrade::NPTradeCenter::StockPositionPtr ptr = std::make_shared<StockPositionInfo>();
				char *pchar;

                strncpy_s(ptr->position_id_, phandler->FetchField(row, SPT_PositionID), sizeof(ptr->position_id_) - 1);
                strncpy_s(userId, phandler->FetchField(row, SPT_UserID), sizeof(userId) - 1);

                strncpy_s(ptr->exchange_id_, phandler->FetchField(row, SPT_ExchangeID), sizeof(ptr->exchange_id_) - 1);
                strncpy_s(ptr->contract_id_, phandler->FetchField(row, SPT_ContractID), sizeof(ptr->contract_id_) - 1);
				
				pchar = phandler->FetchField(row, SPT_Direct);
				ptr->direct_type_ = (DirectType)(atoi(pchar));
				pchar = phandler->FetchField(row, SPT_PositionVol);
				ptr->volume_ = atoi(pchar);
                pchar = phandler->FetchField(row, SPT_PositionTVol);
                ptr->T_volume_ = atoi(pchar);
                strncpy_s(ptr->currency_id_, phandler->FetchField(row, SPT_CurrencyID), sizeof(ptr->currency_id_) - 1);

				pchar = phandler->FetchField(row, SPT_PositionCostPrice);
				ptr->cost_price_ = atof(pchar);

                pchar = phandler->FetchField(row, SPT_TradeAvePrice);
                ptr->trade_ave_price_ = atof(pchar);
                ptr->commodity_type_ = CommodityTypeType::COMMODITY_TYPE_STOCK;

                pchar = phandler->FetchField(row, SPT_StockArea);
                ptr->stock_area_ = (StockAreaType)atoi(pchar);

                pchar = phandler->FetchField(row, SPT_PositionFreezeVol);
                ptr->freeze_order_vol_ = atoi(pchar);

                posiOrder[userId].push_back(ptr);
			}
		}

		phandler->ReleaseRecords(res);
		DBAccess::FreeDBHandler(phandler);
		return errCode == 0;
	}

    bool DBOpTradeCenter::updateTradeFee(const AllTrade::NPTradeCenter::TradeFeePtr& trade_fee)
    {
        CDBHandler *phandler = AllocDBHandler();
        if (!phandler)
            return false;

        int errCode = 0;

        std::stringstream sstr;
        sstr << "REPLACE INTO " << gszTradeFeeTableName << " set "
            << gszTradeFeeColName[TFT_ID] << " = " << 1 << ", "
            << gszTradeFeeColName[TFT_Trade_Commission] << " = " << trade_fee->trade_commission_ << ", "
            << gszTradeFeeColName[TFT_Min_Trade_Commission] << " = " << trade_fee->min_trade_commission_ << ", "
            << gszTradeFeeColName[TFT_Stamp_Duty] << " = " << trade_fee->stamp_duty_ << ", "
            << gszTradeFeeColName[TFT_Transfer] << " = " << trade_fee->transfer_ << ", "
            << gszTradeFeeColName[TFT_Info_Match] << " = " << trade_fee->info_match_ << ", "
            << gszTradeFeeColName[TFT_Profit_Rate] << " = " << trade_fee->user_profit_rate_ << "; ";

        errCode = phandler->ExecSql(sstr.str().c_str());
        if (errCode != 0)
            LOG4CXX_ERROR(logger, "更新费用信息失败!"LOG_NOVAR(sstr.str().c_str()));

        DBAccess::FreeDBHandler(phandler);
        return errCode == 0;
    }

    bool DBOpTradeCenter::getTradeFee(AllTrade::NPTradeCenter::TradeFeePtr& trade_fee)
    {
        CDBHandler *phandler = AllocDBHandler();
        if (!phandler)
            return false;

        bool bFind(false);

        HxSqlRes res = NULL;
        int errCode = 0;
        int recNum = 0;

        std::stringstream sstr;
        sstr << "SELECT * FROM " << gszTradeFeeTableName;

        errCode = phandler->QuerySql(sstr.str().c_str(), res, true);

        if (errCode == 0 && res)
        {
            HxResRow row = NULL;

            if (row = phandler->FetchRow(res))
            {
                char *pchar;
                
                trade_fee = std::make_shared<TradeFee>();

                pchar = phandler->FetchField(row, TFT_Trade_Commission);
                trade_fee->trade_commission_ = atof(pchar);

                pchar = phandler->FetchField(row, TFT_Min_Trade_Commission);
                trade_fee->min_trade_commission_ = atof(pchar);
  
                pchar = phandler->FetchField(row, TFT_Stamp_Duty);
                trade_fee->stamp_duty_ = atof(pchar);
     
                pchar = phandler->FetchField(row, TFT_Transfer);
                trade_fee->transfer_ = atof(pchar);
  
                pchar = phandler->FetchField(row, TFT_Info_Match);
                trade_fee->info_match_ = atof(pchar);

                pchar = phandler->FetchField(row, TFT_Profit_Rate);
                trade_fee->user_profit_rate_ = atof(pchar);

                bFind = true;
            }
        }

        phandler->ReleaseRecords(res);
        DBAccess::FreeDBHandler(phandler);
        return errCode == 0 && bFind;
    }

    bool DBOpTradeCenter::canSettle(const AllTrade::DateTimeType settle_datetime, const AllTrade::DateTimeType cur_datetime)
    {
        CDBHandler *phandler = AllocDBHandler();
        if (!phandler)
            return false;

        bool bCan(true);

        HxSqlRes res = NULL;
        int errCode = 0;
        int recNum = 0;

        std::stringstream sstr;
        sstr << "SELECT * FROM " << gszSettleTableName
            << " WHERE " << gszSettleColName[Settle_CommodityType] << " = " << (int)CommodityTypeType::COMMODITY_TYPE_STOCK;

        errCode = phandler->QuerySql(sstr.str().c_str(), res, true);

        if (errCode == 0 && res)
        {
            HxResRow row = NULL;

            if (row = phandler->FetchRow(res))
            {
                char *pchar;
                pchar = phandler->FetchField(row, Settle_DateTime);
                DateTimeType last_settle_datetime = { 0 };
                strncpy_s(last_settle_datetime, phandler->FetchField(row, Settle_DateTime), sizeof(last_settle_datetime) - 1);

                // 获取时间差,以秒数返回
                // 返回值date1-date2的时间差
                auto getSpaceSec = [](const AllTrade::DateTimeType date1, const AllTrade::DateTimeType date2)->int{

                    auto getTm_t = [](const AllTrade::DateTimeType date)->time_t{
                        std::vector<std::string>	vec_date;
                        boost::split(vec_date, date, boost::is_any_of("- :"));
                        assert(vec_date.size() == 6);

                        tm tm_1;
                        tm_1.tm_year = std::stoi(vec_date[0]) - 1900;
                        tm_1.tm_mon = std::stoi(vec_date[1]) - 1;
                        tm_1.tm_mday = std::stoi(vec_date[2]);
                        tm_1.tm_hour = std::stoi(vec_date[3]);
                        tm_1.tm_min = std::stoi(vec_date[4]);
                        tm_1.tm_sec = std::stoi(vec_date[5]);
                        tm_1.tm_isdst = -1;
                        return mktime(&tm_1); //将tm时间转换为秒时间
                    };

                    time_t t1 = getTm_t(date1);
                    time_t t2 = getTm_t(date2);
                    return t1 - t2;
                };

                // 比较日期, date1 > date2
                auto compDate = [](const AllTrade::DateTimeType date1, const AllTrade::DateTimeType date2)->bool{

                    auto getTm = [](const AllTrade::DateTimeType date)->tm{
                        std::vector<std::string>	vec_date;
                        boost::split(vec_date, date, boost::is_any_of("- :"));
                        assert(vec_date.size() == 6);

                        tm tm_1;
                        tm_1.tm_year = std::stoi(vec_date[0]) - 1900;
                        tm_1.tm_mon = std::stoi(vec_date[1]) - 1;
                        tm_1.tm_mday = std::stoi(vec_date[2]);
                        tm_1.tm_hour = std::stoi(vec_date[3]);
                        tm_1.tm_min = std::stoi(vec_date[4]);
                        tm_1.tm_sec = std::stoi(vec_date[5]);
                        tm_1.tm_isdst = -1;
                        return tm_1;
                    };

                    tm t1 = getTm(date1);
                    tm t2 = getTm(date2);
                    return t1.tm_year >t2.tm_year
                        || (t1.tm_year == t2.tm_year&&t1.tm_mon >t2.tm_mon)
                        || (t1.tm_year == t2.tm_year&&t1.tm_mon == t2.tm_mon&&t1.tm_mday > t2.tm_mday);
                };

                // 1. 上次结算时间 >= 本次结算时间                           => 无需结算
                if (strcmp(last_settle_datetime, settle_datetime) >= 0)
                    bCan = false;
                // 2. 本次结算时间 - 上次结算时间(去除休息日) >= 24h         => 需要结算
                else if (getSpaceSec(settle_datetime, last_settle_datetime) > 24 * 60 * 60)
                    bCan = true;
                // 3. 本次结算时间 - 上次结算时间(去除休息日) < 24h
                else
                {
                    // 3.1  当前时间 >= 本次结算时间                             => 需要结算
                    if (strcmp(cur_datetime, settle_datetime) >= 0)
                        bCan = true;
                    // 3.2  当前时间 < 本次结算时间                              => 无需结算
                    else
                        bCan = false;
                }

//                 if (strcmp(cur_datetime, settle_datetime) < 0)
//                 {
//                     if (getSpaceSec(settle_datetime, last_settle_datetime) < 24 * 60 * 60 - 20)
//                         bCan = false;
//                 }
//                 else
//                 {
//                     if (!compDate(cur_datetime, last_settle_datetime))
//                         bCan = false;
//                 }

            }
        }

        phandler->ReleaseRecords(res);
        DBAccess::FreeDBHandler(phandler);
        if (errCode != 0)
            return false;

        return bCan;
    }

    bool DBOpTradeCenter::updateSettle(const AllTrade::DateTimeType settle_datetime)
    {
        LOG4CXX_TRACE(logger, "更新结算时间"LOG_NOVAR(settle_datetime));

        CDBHandler *phandler = AllocDBHandler();
        if (!phandler)
            return false;

        int errCode = 0;

        std::stringstream sstr;
        sstr << "REPLACE INTO " << gszSettleTableName << " set "
            << gszSettleColName[Settle_CommodityType] << " = " << (int)CommodityTypeType::COMMODITY_TYPE_STOCK << ", "
            << gszSettleColName[Settle_DateTime] << " = '" << settle_datetime << "'; ";

        errCode = phandler->ExecSql(sstr.str().c_str());
        if (errCode != 0)
            LOG4CXX_ERROR(logger, "更新结算信息失败!"LOG_NOVAR(sstr.str().c_str()));

        DBAccess::FreeDBHandler(phandler);
        return errCode == 0;
    }

    bool DBOpTradeCenter::createSettle()
    {
        CDBHandler *phandler = AllocDBHandler();
        if (!phandler)
            return false;

        int errCode = 0;

        std::stringstream sstr;
        sstr << "CREATE TABLE IF NOT EXISTS " << gszSettleTableName << " (";

        for (int i = 0; i < Settle_Max; i++)
        {
            sstr << gszSettleColName[i] << " " << gszSettleCreateColType[i];
            if (i < Settle_Max - 1)
                sstr << ",";
        }
        sstr << ");";

        errCode = phandler->ExecSql(sstr.str().c_str());

        DBAccess::FreeDBHandler(phandler);
        return errCode == 0;
    }

    AllTrade::NPTradeCenter::GlobalDataPtr DBOpTradeCenter::getCurrentGlobalData()
    {
        GlobalDataPtr rslt = std::make_shared<GlobalData>();

        CDBHandler *phandler = AllocDBHandler();
        if (!phandler)
            return false;

        HxSqlRes res = NULL;
        int errCode = 0;
        int recNum = 0;

        std::stringstream sstr;
        sstr << "SELECT * FROM " << gszGlobalDataTableName 
            << " WHERE " << gszGlobalDataColName[GD_CommodityType] << " = " << (int)CommodityTypeType::COMMODITY_TYPE_STOCK;

        errCode = phandler->QuerySql(sstr.str().c_str(), res, true);

        if (errCode == 0 && res)
        {
            HxResRow row = NULL;

            if (row = phandler->FetchRow(res))
            {
                char *pchar;
                pchar = phandler->FetchField(row, GD_CurShadowOrderID);
                rslt->shadow_order_id_ = atoi(pchar);
                pchar = phandler->FetchField(row, GD_CurShadowTradeID);
                rslt->shadow_trade_id_ = atoi(pchar);
            }
        }

        phandler->ReleaseRecords(res);
        DBAccess::FreeDBHandler(phandler);
        return rslt;
    }

    bool DBOpTradeCenter::updateCurGlobalData(const AllTrade::NPTradeCenter::GlobalDataPtr global_data)
    {
        CDBHandler *phandler = AllocDBHandler();
        if (!phandler)
            return false;

        int errCode = 0;

        std::stringstream sstr;
        sstr << "REPLACE INTO " << gszGlobalDataTableName << " set "
            << gszGlobalDataColName[GD_CommodityType] << " = " << (int)CommodityTypeType::COMMODITY_TYPE_STOCK << ", "
            << gszGlobalDataColName[GD_CurShadowOrderID] << " = " << global_data->shadow_order_id_ << ", "
            << gszGlobalDataColName[GD_CurShadowTradeID] << " = " << global_data->shadow_trade_id_ << "; ";

        errCode = phandler->ExecSql(sstr.str().c_str());
        if (errCode != 0)
            LOG4CXX_ERROR(logger, "更新全局信息失败!"LOG_NOVAR(sstr.str().c_str()));

        DBAccess::FreeDBHandler(phandler);
        return errCode == 0;
    }

    bool DBOpTradeCenter::createGlobalData()
    {
        CDBHandler *phandler = AllocDBHandler();
        if (!phandler)
            return false;

        int errCode = 0;

        std::stringstream sstr;
        sstr << "CREATE TABLE IF NOT EXISTS " << gszGlobalDataTableName << " (";

        for (int i = 0; i < GD_Max; i++)
        {
            sstr << gszGlobalDataColName[i] << " " << gszGlobalDataCreateColType[i];
            if (i < GD_Max - 1)
                sstr << ",";
        }
        sstr << ");";

        errCode = phandler->ExecSql(sstr.str().c_str());

        DBAccess::FreeDBHandler(phandler);
        return errCode == 0;
    }

    void DBOpTradeCenter::updateRiskRecord(const AllTrade::NPTradeCenter::ImmRiskControlPtr risk_cont_st)
    {
        CDBHandler *phandler = AllocDBHandler();
        if (!phandler)
            return;

        int errCode = 0;

        std::stringstream sstr;
		sstr << "REPLACE INTO " << gszRiskControlRecordTableName << " set "
			<< gszRiskControlRecordColName[RCRT_UserID] << " = '" << risk_cont_st->user_id_ << "', "
			<< gszRiskControlRecordColName[RCRT_RiskType] << " = " << (int)risk_cont_st->rc_type_ << ", "
			<< gszRiskControlRecordColName[RCRT_BTrigger] << " = " << (risk_cont_st->bTrigger_ ? 1 : 0) << ", "
			<< gszRiskControlRecordColName[RCRT_DateTime] << " = '" << risk_cont_st->date_time_ << "', "
			<< gszRiskControlRecordColName[RCRT_TriggerText] << " = '" << risk_cont_st->trigger_text_ << "'; ";

		errCode = phandler->ExecSql(sstr.str().c_str());

		if (errCode != 0)
			LOG4CXX_ERROR(logger, "更新风控记录信息失败!"LOG_NOVAR(sstr.str().c_str()));

		sstr.str("");

		// 插入历史记录表
		sstr << "INSERT INTO " << gszRiskControlHistoryRecordTableName << " set "
			<< gszRiskControlHistoryRecordColName[RCHRT_UserID] << " = '" << risk_cont_st->user_id_ << "', "
			<< gszRiskControlHistoryRecordColName[RCHRT_RiskType] << " = " << (int)risk_cont_st->rc_type_ << ", "
			<< gszRiskControlHistoryRecordColName[RCHRT_BTrigger] << " = " << (risk_cont_st->bTrigger_ ? 1 : 0) << ", "
			<< gszRiskControlHistoryRecordColName[RCHRT_DateTime] << " = '" << risk_cont_st->date_time_ << "', "
			<< gszRiskControlHistoryRecordColName[RCHRT_TriggerText] << " = '" << risk_cont_st->trigger_text_ << "'; ";

		errCode = phandler->ExecSql(sstr.str().c_str());

		if (errCode!= 0)
			LOG4CXX_ERROR(logger, "更新风控历史记录信息失败!"LOG_NOVAR(sstr.str().c_str()));
        

        DBAccess::FreeDBHandler(phandler);
        return;
    }

    AllTrade::NPTradeCenter::ImmRiskControlPtr DBOpTradeCenter::getRiskRecord(const UserIDType user_id, RiskControlType rc_type)
    {
        ImmRiskControlPtr rslt(nullptr);

        CDBHandler *phandler = AllocDBHandler();
        if (!phandler)
            return false;

        HxSqlRes res = NULL;
        int errCode = 0;
        int recNum = 0;

        std::stringstream sstr;
        sstr << "SELECT * FROM " << gszRiskControlRecordTableName
            << " WHERE " << gszRiskControlRecordColName[RCRT_UserID] << " = '" << user_id << "' "
            << " AND " << gszRiskControlRecordColName[RCRT_RiskType] << " = " << (int)rc_type << ";";

        errCode = phandler->QuerySql(sstr.str().c_str(), res, true);

        if (errCode == 0 && res)
        {
            HxResRow row = NULL;

            if (row = phandler->FetchRow(res))
            {
                rslt = std::make_shared<ImmRiskControlSt>();

                char *pchar;
                pchar = phandler->FetchField(row, RCRT_UserID);
                strncpy_s(rslt->user_id_, user_id, sizeof(rslt->user_id_) - 1);
                pchar = phandler->FetchField(row, RCRT_RiskType);
                rslt->rc_type_ = (RiskControlType)atoi(pchar);
                pchar = phandler->FetchField(row, RCRT_BTrigger);
                rslt->bTrigger_ = atoi(pchar) == 1;
                strncpy_s(rslt->date_time_, phandler->FetchField(row, RCRT_DateTime), sizeof(rslt->date_time_) - 1);
            }
        }

        phandler->ReleaseRecords(res);
        DBAccess::FreeDBHandler(phandler);
        return rslt;
    }

	bool DBOpTradeCenter::getRiskRecord(const AllTrade::UserIDType user_id, std::vector<AllTrade::NPTradeCenter::ImmRiskControlPtr>& vecSt)
	{
		CDBHandler *phandler = AllocDBHandler();
		if (!phandler)
			return false;

		HxSqlRes res = NULL;
		int errCode = 0;

		std::stringstream sstr;
		sstr << "SELECT * FROM " << gszRiskControlRecordTableName
			<< " WHERE " << gszRiskControlRecordColName[RCRT_UserID] << " = '" << user_id << "'; ";

		errCode = phandler->QuerySql(sstr.str().c_str(), res, true);

		if (errCode == 0 && res)
		{
			HxResRow row = NULL;

			while (row = phandler->FetchRow(res))
			{
				AllTrade::NPTradeCenter::ImmRiskControlPtr rslt = std::make_shared<ImmRiskControlSt>();

				char *pchar;
				pchar = phandler->FetchField(row, RCRT_UserID);
				strncpy_s(rslt->user_id_, user_id, sizeof(rslt->user_id_) - 1);
				pchar = phandler->FetchField(row, RCRT_RiskType);
				rslt->rc_type_ = (RiskControlType)atoi(pchar);
				pchar = phandler->FetchField(row, RCRT_BTrigger);
				rslt->bTrigger_ = atoi(pchar) == 1;
				strncpy_s(rslt->date_time_, phandler->FetchField(row, RCRT_DateTime), sizeof(rslt->date_time_) - 1);
                if (pchar = phandler->FetchField(row, RCRT_TriggerText))
                    strncpy_s(rslt->trigger_text_, pchar, sizeof(rslt->trigger_text_) - 1);

				vecSt.emplace_back(rslt);
			}
		}

		phandler->ReleaseRecords(res);
		DBAccess::FreeDBHandler(phandler);

		return errCode == 0;
	}

	bool DBOpTradeCenter::createRiskRecord()
    {
        CDBHandler *phandler = AllocDBHandler();
        if (!phandler)
            return false;

        int errCode = 0;

        std::stringstream sstr;
        sstr << "CREATE TABLE IF NOT EXISTS " << gszRiskControlRecordTableName << " (";

        for (int i = 0; i < RCRT_Max; i++)
        {
            sstr << gszRiskControlRecordColName[i] << " " << gszRiskControlRecordCreateColType[i]
                 << ",";
        }
        sstr << "PRIMARY KEY (" << gszRiskControlRecordColName[RCRT_UserID] << "," << gszRiskControlRecordColName[RCRT_RiskType] << ") );";

        errCode = phandler->ExecSql(sstr.str().c_str());
        if (errCode != 0)
            LOG4CXX_ERROR(logger, "创建风控记录表失败!"LOG_NOVAR(sstr.str().c_str()));

        DBAccess::FreeDBHandler(phandler);
        return errCode == 0;
    }

#pragma region 委托
    bool DBOpTradeCenter::createStockOrderInfo()
    {
        CDBHandler *phandler = AllocDBHandler();
        if (!phandler)
            return false;

        int errCode = 0;

        std::stringstream sstr;
        sstr << "CREATE TABLE IF NOT EXISTS " << gszStockOrderTableName << " (";

        for (int i = 0; i < SOT_Max; i++)
        {
            sstr << gszStockOrderColName[i] << " " << gszStockOrderCreateColType[i];
            if (i < SOT_Max - 1)
                sstr << ",";
        }
        sstr << ");";

        errCode = phandler->ExecSql(sstr.str().c_str());
        if (errCode != 0)
            LOG4CXX_ERROR(logger, "创建股票委托表失败!"LOG_NOVAR(sstr.str().c_str()));

        DBAccess::FreeDBHandler(phandler);
        return errCode == 0;
    }

    bool DBOpTradeCenter::createForeignFutureOrderInfo()
    {
        CDBHandler *phandler = AllocDBHandler();
        if (!phandler)
            return false;

        int errCode = 0;

        std::stringstream sstr;
        sstr << "CREATE TABLE IF NOT EXISTS " << gszForeignFutureOrderTableName << " (";

        for (int i = 0; i < FFOT_Max; i++)
        {
            sstr << gszForeignFutureOrderColName[i] << " " << gszForeignFutureOrderCreateColType[i];
            if (i < FFOT_Max - 1)
                sstr << ",";
        }
        sstr << ");";

        errCode = phandler->ExecSql(sstr.str().c_str());
        if (errCode != 0)
            LOG4CXX_ERROR(logger, "创建外盘委托表失败!"LOG_NOVAR(sstr.str().c_str()));

        DBAccess::FreeDBHandler(phandler);
        return errCode == 0;
    }

    bool DBOpTradeCenter::createChinaFutureOrderInfo()
    {
        CDBHandler *phandler = AllocDBHandler();
        if (!phandler)
            return false;

        int errCode = 0;

        std::stringstream sstr;
        sstr << "CREATE TABLE IF NOT EXISTS " << gszChinaFutureOrderTableName << " (";

        for (int i = 0; i < CFOT_Max; i++)
        {
            sstr << gszChinaFutureOrderColName[i] << " " << gszChinaFutureOrderCreateColType[i];
            if (i < CFOT_Max - 1)
                sstr << ",";
        }
        sstr << ");";

        errCode = phandler->ExecSql(sstr.str().c_str());
        if (errCode != 0)
            LOG4CXX_ERROR(logger, "创建内盘委托表失败!"LOG_NOVAR(sstr.str().c_str()));

        DBAccess::FreeDBHandler(phandler);
        return errCode == 0;
    }

    bool DBOpTradeCenter::createTradeFee()
    {
        CDBHandler *phandler = AllocDBHandler();
        if (!phandler)
            return false;

        int errCode = 0;

        std::stringstream sstr;
        sstr << "CREATE TABLE IF NOT EXISTS " << gszTradeFeeTableName << " (";

        for (int i = 0; i < TFT_Max; i++)
        {
            sstr << gszTradeFeeColName[i] << " " << gszTradeFeeCreateColType[i];
            if (i < TFT_Max - 1)
                sstr << ",";
        }
        sstr << ");";

        errCode = phandler->ExecSql(sstr.str().c_str());
        if (errCode != 0)
            LOG4CXX_ERROR(logger, "创建交易费用表失败!"LOG_NOVAR(sstr.str().c_str()));

        DBAccess::FreeDBHandler(phandler);
        return errCode == 0;
    }

    bool DBOpTradeCenter::updateStockOrderInfo(const AllTrade::NPTradeCenter::StockOrderPtr& order_ptr, const AllTrade::UserIDType user_id)
    {
        CDBHandler *phandler = AllocDBHandler();
        if (!phandler)
            return false;

        int errCode = 0;
        std::stringstream sstr;
        sstr << "REPLACE INTO " << gszStockOrderTableName << " set "
            << gszStockOrderColName[SOT_OrderStream] << " = '" << order_ptr->order_stream_ << "', "
            << gszStockOrderColName[SOT_OrderID] << " = '" << order_ptr->order_id_ << "', "
            << gszStockOrderColName[SOT_UserID] << " = '" << user_id << "', "
            << gszStockOrderColName[SOT_ContractID] << " = '" << order_ptr->contract_id_ << "', "
            << gszStockOrderColName[SOT_OrderState] << " = " << (int)order_ptr->order_state_ << ", "
            << gszStockOrderColName[SOT_OrderStateExplain] << " = " << order_ptr->orser_state_explain_ << ", "
            << gszStockOrderColName[SOT_OrderRef] << " = '" << order_ptr->order_ref_ << "', "
            << gszStockOrderColName[SOT_LoclaTmp_OrderRef] << " = '" << order_ptr->order_localtmp_ref_ << "', "
            << gszStockOrderColName[SOT_ShadowOrderID] << " = '" << order_ptr->shadow_order_id_ << "', "
            << gszStockOrderColName[SOT_GenerateDateTime] << " = '" << order_ptr->generate_datetime_ << "', "
            << gszStockOrderColName[SOT_UpdateDateTime] << " = '" << order_ptr->update_datetime_ << "', "
            << gszStockOrderColName[SOT_CurrencyRate] << " = '" << order_ptr->currency_rate_ << "', "
            << gszStockOrderColName[SOT_CurrencyID] << " = '" << order_ptr->currency_id_ << "', "
            << gszStockOrderColName[SOT_OrderPrice] << " = " << order_ptr->order_price_ << ", "
            << gszStockOrderColName[SOT_Direct] << " = " << (int)order_ptr->direct_type_ << ", "
            << gszStockOrderColName[SOT_OrderVol] << " = " << order_ptr->order_vol_ << ", "
            << gszStockOrderColName[SOT_EffectedVol] << " = " << order_ptr->effected_vol_ << ", "
            << gszStockOrderColName[SOT_TradeVol] << " = " << order_ptr->trade_vol_ << ", "
            << gszStockOrderColName[SOT_BFreezePosition] << " = " << (order_ptr->b_freeze_position_ ? 1 : 0) << ", "
            << gszStockOrderColName[SOT_FreezeMoney] << " = " << order_ptr->freeze_money_ << ", "
            << gszStockOrderColName[SOT_BFreezeMoney] << " = " << (order_ptr->b_freeze_money_ ? 1 : 0) << ", "
            << gszStockOrderColName[SOT_OrderType] << " = " << (int)order_ptr->order_type_ << ", "
            << gszStockOrderColName[SOT_OrderTradeMode] << " = " << (int)order_ptr->order_trade_mode_ << ", "
            << gszStockOrderColName[SOT_OrderTradePrice] << " = " << order_ptr->order_trade_price_ << ", "
            << gszStockOrderColName[SOT_OrderPositionCost] << " = " << order_ptr->position_cost_ << ", "
            << gszStockOrderColName[SOT_SystemOrderID] << " = '" << order_ptr->system_order_id_ << "', "
            << gszStockOrderColName[SOT_ExchangeID] << " = '" << order_ptr->exchange_id_ << "', "
            << gszStockOrderColName[SOT_ApiType] << " = " << (int)order_ptr->api_type_ << ", "
            << gszStockOrderColName[SOT_OperatorType] << " = " << (int)order_ptr->op_type_ << ", "
            << gszStockOrderColName[SOT_OrderMode] << " = " << (int)order_ptr->order_mode_ << ", "
//             << gszStockOrderColName[SOT_ValidDateTime] << " = '" << order_ptr->valid_datetime_ << "', "
            << gszStockOrderColName[SOT_StockArea] << " = " << (int)order_ptr->stock_area_ << ", "
            << gszStockOrderColName[SOT_CurTradeFee] << " = " << order_ptr->cur_trade_fee_ << ", "
            << gszStockOrderColName[SOT_CurStampFee] << " = " << order_ptr->cur_stamp_fee_ << ", "
            << gszStockOrderColName[SOT_CurTransferFee] << " = " << order_ptr->cur_transfer_fee_ << ", "
            << gszStockOrderColName[SOT_CurInfomatchFee] << " = " << order_ptr->cur_infomatch_fee_ << "; ";

        errCode = phandler->ExecSql(sstr.str().c_str());
        if (errCode != 0)
            LOG4CXX_ERROR(logger, "更新股票委托信息失败!"LOG_NOVAR(sstr.str().c_str()));

        DBAccess::FreeDBHandler(phandler);
        return errCode == 0;
    }

    bool DBOpTradeCenter::updateForeignFutureOrderInfo(const AllTrade::NPTradeCenter::ForeignFutureOrderPtr& order_ptr, const AllTrade::UserIDType user_id)
    {
        CDBHandler *phandler = AllocDBHandler();
        if (!phandler)
            return false;

        int errCode = 0;

        std::stringstream sstr;
        sstr << "REPLACE INTO " << gszForeignFutureOrderTableName << " set "
            << gszForeignFutureOrderColName[FFOT_OrderStream] << " = '" << order_ptr->order_stream_ << "', "
            << gszForeignFutureOrderColName[FFOT_OrderID] << " = '" << order_ptr->order_id_ << "', "
            << gszForeignFutureOrderColName[FFOT_UserID] << " = '" << user_id << "', "
            << gszForeignFutureOrderColName[FFOT_ContractID] << " = '" << order_ptr->contract_id_ << "', "
            << gszForeignFutureOrderColName[FFOT_OrderState] << " = " << (int)order_ptr->order_state_ << ", "
            << gszForeignFutureOrderColName[FFOT_OrderStateExplain] << " = " << order_ptr->orser_state_explain_ << ", "
            << gszForeignFutureOrderColName[FFOT_OrderRef] << " = '" << order_ptr->order_ref_ << "', "
            << gszForeignFutureOrderColName[FFOT_LoclaTmp_OrderRef] << " = '" << order_ptr->order_localtmp_ref_ << "', "
            << gszForeignFutureOrderColName[FFOT_ShadowOrderID] << " = '" << order_ptr->shadow_order_id_ << "', "
            << gszForeignFutureOrderColName[FFOT_GenerateDateTime] << " = '" << order_ptr->generate_datetime_ << "', "
            << gszForeignFutureOrderColName[FFOT_UpdateDateTime] << " = '" << order_ptr->update_datetime_ << "', "
            << gszForeignFutureOrderColName[FFOT_CurrencyRate] << " = '" << order_ptr->currency_rate_ << "', "
            << gszForeignFutureOrderColName[FFOT_CurrencyID] << " = '" << order_ptr->currency_id_ << "', "
            << gszForeignFutureOrderColName[FFOT_OrderPrice] << " = " << order_ptr->order_price_ << ", "
            << gszForeignFutureOrderColName[FFOT_Direct] << " = " << (int)order_ptr->direct_type_ << ", "
            << gszForeignFutureOrderColName[FFOT_OrderVol] << " = " << order_ptr->order_vol_ << ", "
            << gszForeignFutureOrderColName[FFOT_EffectedVol] << " = " << order_ptr->effected_vol_ << ", "
            << gszForeignFutureOrderColName[FFOT_OrderType] << " = " << (int)order_ptr->order_type_ << ", "
            << gszForeignFutureOrderColName[FFOT_OrderTradeMode] << " = " << (int)order_ptr->order_trade_mode_ << ", "
            << gszForeignFutureOrderColName[FFOT_OrderTradePrice] << " = " << order_ptr->order_trade_price_ << ", "
            << gszForeignFutureOrderColName[FFOT_OrderPositionCost] << " = " << order_ptr->position_cost_ << ", "
            << gszForeignFutureOrderColName[FFOT_SystemOrderID] << " = '" << order_ptr->system_order_id_ << "', "
            << gszForeignFutureOrderColName[FFOT_ExchangeID] << " = '" << order_ptr->exchange_id_ << "', "
            << gszForeignFutureOrderColName[FFOT_ApiType] << " = " << (int)order_ptr->api_type_ << ", "
            << gszForeignFutureOrderColName[FFOT_OperatorType] << " = " << (int)order_ptr->op_type_ << ", "
            << gszForeignFutureOrderColName[FFOT_OrderMode] << " = " << (int)order_ptr->order_mode_ << ", "
            << gszForeignFutureOrderColName[FFOT_ValidDateTime] << " = '" << order_ptr->valid_datetime_ << "', "
            << gszForeignFutureOrderColName[FFOT_ProductID] << " = '" << order_ptr->product_id_ << "'; ";

        errCode = phandler->ExecSql(sstr.str().c_str());

        DBAccess::FreeDBHandler(phandler);
        return errCode == 0;
    }

    bool DBOpTradeCenter::updateChinaFutureOrderInfo(const AllTrade::NPTradeCenter::ChinaFutureOrderPtr& order_ptr, const AllTrade::UserIDType user_id)
    {
        CDBHandler *phandler = AllocDBHandler();
        if (!phandler)
            return false;

        int errCode = 0;

        std::stringstream sstr;
        sstr << "REPLACE INTO " << gszChinaFutureOrderTableName << " set "
            << gszChinaFutureOrderColName[CFOT_OrderStream] << " = '" << order_ptr->order_stream_ << "', "
            << gszChinaFutureOrderColName[CFOT_OrderID] << " = '" << order_ptr->order_id_ << "', "
            << gszChinaFutureOrderColName[CFOT_UserID] << " = '" << user_id << "', "
            << gszChinaFutureOrderColName[CFOT_ContractID] << " = '" << order_ptr->contract_id_ << "', "
            << gszChinaFutureOrderColName[CFOT_OrderState] << " = " << (int)order_ptr->order_state_ << ", "
            << gszChinaFutureOrderColName[CFOT_OrderStateExplain] << " = " << order_ptr->orser_state_explain_ << ", "
            << gszChinaFutureOrderColName[CFOT_OrderRef] << " = '" << order_ptr->order_ref_ << "', "
            << gszChinaFutureOrderColName[CFOT_LoclaTmp_OrderRef] << " = '" << order_ptr->order_localtmp_ref_ << "', "
            << gszChinaFutureOrderColName[CFOT_ShadowOrderID] << " = '" << order_ptr->shadow_order_id_ << "', "
            << gszChinaFutureOrderColName[CFOT_GenerateDateTime] << " = '" << order_ptr->generate_datetime_ << "', "
            << gszChinaFutureOrderColName[CFOT_UpdateDateTime] << " = '" << order_ptr->update_datetime_ << "', "
            << gszChinaFutureOrderColName[CFOT_CurrencyRate] << " = '" << order_ptr->currency_rate_ << "', "
            << gszChinaFutureOrderColName[CFOT_CurrencyID] << " = '" << order_ptr->currency_id_ << "', "
            << gszChinaFutureOrderColName[CFOT_OrderPrice] << " = " << order_ptr->order_price_ << ", "
            << gszChinaFutureOrderColName[CFOT_Direct] << " = " << (int)order_ptr->direct_type_ << ", "
            << gszChinaFutureOrderColName[CFOT_OrderVol] << " = " << order_ptr->order_vol_ << ", "
            << gszChinaFutureOrderColName[CFOT_EffectedVol] << " = " << order_ptr->effected_vol_ << ", "
            << gszChinaFutureOrderColName[CFOT_OrderType] << " = " << (int)order_ptr->order_type_ << ", "
            << gszChinaFutureOrderColName[CFOT_OrderTradeMode] << " = " << (int)order_ptr->order_trade_mode_ << ", "
            << gszChinaFutureOrderColName[CFOT_OrderTradePrice] << " = " << order_ptr->order_trade_price_ << ", "
            << gszChinaFutureOrderColName[CFOT_OrderPositionCost] << " = " << order_ptr->position_cost_ << ", "
            << gszChinaFutureOrderColName[CFOT_SystemOrderID] << " = '" << order_ptr->system_order_id_ << "', "
            << gszChinaFutureOrderColName[CFOT_ExchangeID] << " = '" << order_ptr->exchange_id_ << "', "
            << gszChinaFutureOrderColName[CFOT_ApiType] << " = " << (int)order_ptr->api_type_ << ", "
            << gszChinaFutureOrderColName[CFOT_OperatorType] << " = " << (int)order_ptr->op_type_ << ", "
            << gszChinaFutureOrderColName[CFOT_OrderMode] << " = " << (int)order_ptr->order_mode_ << ", "
            << gszChinaFutureOrderColName[CFOT_ValidDateTime] << " = '" << order_ptr->valid_datetime_ << "', "
            << gszChinaFutureOrderColName[CFOT_ProductID] << " = '" << order_ptr->product_id_ << "', "
            << gszChinaFutureOrderColName[CFOT_OffsetType] << " = " << (int)order_ptr->offset_type_ << ";";

        errCode = phandler->ExecSql(sstr.str().c_str());

        DBAccess::FreeDBHandler(phandler);
        return errCode == 0;
    }

	

#pragma endregion

#pragma region 成交
    bool DBOpTradeCenter::createStockTradeInfo()
    {
        CDBHandler *phandler = AllocDBHandler();
        if (!phandler)
            return false;

        int errCode = 0;

        std::stringstream sstr;
        sstr << "CREATE TABLE IF NOT EXISTS " << gszStockTradeTableName << " (";

        for (int i = 0; i < STT_Max; i++)
        {
            sstr << gszStockTradeColName[i] << " " << gszStockTradeCreateColType[i];
            if (i < STT_Max - 1)
                sstr << ",";
        }
        sstr << ");";

        errCode = phandler->ExecSql(sstr.str().c_str());
        if (errCode != 0)
            LOG4CXX_ERROR(logger, "创建股票成交表失败!"LOG_NOVAR(sstr.str().c_str()));

        DBAccess::FreeDBHandler(phandler);
        return errCode == 0;
    }

    bool DBOpTradeCenter::createForeignFutureTradeInfo()
    {
        CDBHandler *phandler = AllocDBHandler();
        if (!phandler)
            return false;

        int errCode = 0;

        std::stringstream sstr;
        sstr << "CREATE TABLE IF NOT EXISTS " << gszForeignFutureTradeTableName << " (";

        for (int i = 0; i < FFTT_Max; i++)
        {
            sstr << gszForeignFutureTradeColName[i] << " " << gszForeignFutureTradeCreateColType[i];
            if (i < FFTT_Max - 1)
                sstr << ",";
        }
        sstr << ");";

        errCode = phandler->ExecSql(sstr.str().c_str());

        DBAccess::FreeDBHandler(phandler);
        return errCode == 0;
    }

    bool DBOpTradeCenter::createChinaFutureTradeInfo()
    {
        CDBHandler *phandler = AllocDBHandler();
        if (!phandler)
            return false;

        int errCode = 0;

        std::stringstream sstr;
        sstr << "CREATE TABLE IF NOT EXISTS " << gszChinaFutureTradeTableName << " (";

        for (int i = 0; i < CFTT_Max; i++)
        {
            sstr << gszChinaFutureTradeColName[i] << " " << gszChinaFutureTradeCreateColType[i];
            if (i < CFTT_Max - 1)
                sstr << ",";
        }
        sstr << ");";

        errCode = phandler->ExecSql(sstr.str().c_str());

        DBAccess::FreeDBHandler(phandler);
        return errCode == 0;
    }

    bool DBOpTradeCenter::addStockTradeRecord(const AllTrade::NPTradeCenter::StockTradePtr& trade_ptr, const AllTrade::UserIDType user_id)
    {
        CDBHandler *phandler = AllocDBHandler();
        if (!phandler)
            return false;

        int errCode = 0;

        std::stringstream sstr;
        sstr << "REPLACE INTO " << gszStockTradeTableName << " SET "
            << gszStockTradeColName[STT_TradeID] << " = '" << trade_ptr->trade_id_ << "', "
            << gszStockTradeColName[STT_ShadowTradeID] << " = '" << trade_ptr->shadow_trade_id_ << "', "
            << gszStockTradeColName[STT_OrderStream] << " = '" << trade_ptr->order_stream_ << "', "
            << gszStockTradeColName[STT_PositionID] << " = '" << trade_ptr->position_id_ << "', "
            << gszStockTradeColName[STT_UserID] << " = '" << user_id << "', "
            << gszStockTradeColName[STT_ExchangeID] << " = '" << trade_ptr->exchange_id_ << "', "
            << gszStockTradeColName[STT_ContractID] << " = '" << trade_ptr->contract_id_ << "', "
            << gszStockTradeColName[STT_GenerateDateTime] << " = '" << trade_ptr->generate_datetime_ << "', "
            << gszStockTradeColName[STT_Direct] << " = " << (int)trade_ptr->direct_type_ << ", "
            << gszStockTradeColName[STT_TradeVol] << " = " << trade_ptr->volume_ << ", "
            << gszStockTradeColName[STT_CurrencyRate] << " = " << trade_ptr->currency_rate_ << ", "
            << gszStockTradeColName[STT_CurrencyID] << " = '" << trade_ptr->currency_id_ << "', "
            << gszStockTradeColName[STT_TradeAvePrice] << " = " << trade_ptr->trade_price_ << ", "
            << gszStockTradeColName[STT_CloseProfit] << " = " << trade_ptr->close_profit_ << ", "
            << gszStockTradeColName[STT_OperatorType] << " = " << (int)trade_ptr->op_type_ << ", "
            << gszStockTradeColName[STT_StockArea] << " = " << (int)trade_ptr->stock_area_ << ", "
            << gszStockTradeColName[STT_TradeFee] << " = " << trade_ptr->trade_fee_ << ", "
            << gszStockTradeColName[STT_StampFee] << " = " << trade_ptr->stamp_fee_ << ", "
            << gszStockTradeColName[STT_TransferFee] << " = " << trade_ptr->transfer_fee_ << ", "
            << gszStockTradeColName[STT_InfomatchFee] << " = " << trade_ptr->infomatch_fee_ << "; ";

        errCode = phandler->ExecSql(sstr.str().c_str());
        if (errCode != 0)
            LOG4CXX_ERROR(logger, "更新股票成交信息失败!"LOG_NOVAR(sstr.str().c_str()));

        DBAccess::FreeDBHandler(phandler);
        return errCode == 0;
    }

    bool DBOpTradeCenter::addForeignFutureTradeRecord(const AllTrade::NPTradeCenter::ForeignFutureTradePtr& trade_ptr, const AllTrade::UserIDType user_id)
    {
        CDBHandler *phandler = AllocDBHandler();
        if (!phandler)
            return false;

        int errCode = 0;

        std::stringstream sstr;
        sstr << "INSERT INTO " << gszForeignFutureTradeTableName << " SET "
            << gszForeignFutureTradeColName[FFTT_TradeID] << " = '" << trade_ptr->trade_id_ << "', "
            << gszForeignFutureTradeColName[FFTT_OrderStream] << " = '" << trade_ptr->order_stream_ << "', "
            << gszForeignFutureTradeColName[FFTT_PositionID] << " = '" << trade_ptr->position_id_ << "', "
            << gszForeignFutureTradeColName[FFTT_UserID] << " = '" << user_id << "', "
            << gszForeignFutureTradeColName[FFTT_ExchangeID] << " = '" << trade_ptr->exchange_id_ << "', "
            << gszForeignFutureTradeColName[FFTT_ProductID] << " = '" << trade_ptr->product_id_ << "', "
            << gszForeignFutureTradeColName[FFTT_ContractID] << " = '" << trade_ptr->contract_id_ << "', "
            << gszForeignFutureTradeColName[FFTT_GenerateDateTime] << " = '" << trade_ptr->generate_datetime_ << "', "
            << gszForeignFutureTradeColName[FFTT_Direct] << " = " << (int)trade_ptr->direct_type_ << ", "
            << gszForeignFutureTradeColName[FFTT_TradeVol] << " = " << trade_ptr->volume_ << ", "
            << gszForeignFutureTradeColName[FFTT_CurrencyRate] << " = " << trade_ptr->currency_rate_ << ", "
            << gszForeignFutureTradeColName[FFTT_CurrencyID] << " = '" << trade_ptr->currency_id_ << "', "
            << gszForeignFutureTradeColName[FFTT_TradeAvePrice] << " = " << trade_ptr->trade_price_ << ", "
            << gszForeignFutureTradeColName[FFTT_CloseProfit] << " = " << trade_ptr->close_profit_<< ", "
            << gszForeignFutureTradeColName[FFTT_OperatorType] << " = " << (int)trade_ptr->op_type_ << "; ";

        errCode = phandler->ExecSql(sstr.str().c_str());

        DBAccess::FreeDBHandler(phandler);
        return errCode == 0;
    }

    bool DBOpTradeCenter::addChinaFutureTradeRecord(const AllTrade::NPTradeCenter::ChinaFutureTradePtr& trade_ptr, const AllTrade::UserIDType user_id)
    {
        CDBHandler *phandler = AllocDBHandler();
        if (!phandler)
            return false;

        int errCode = 0;

        std::stringstream sstr;
        sstr << "INSERT INTO " << gszChinaFutureTradeTableName << " SET "
            << gszChinaFutureTradeColName[CFTT_TradeID] << " = '" << trade_ptr->trade_id_ << "', "
            << gszChinaFutureTradeColName[CFTT_OrderStream] << " = '" << trade_ptr->order_stream_ << "', "
            << gszChinaFutureTradeColName[CFTT_PositionID] << " = '" << trade_ptr->position_id_ << "', "
            << gszChinaFutureTradeColName[CFTT_UserID] << " = '" << user_id << "', "
            << gszChinaFutureTradeColName[CFTT_ExchangeID] << " = '" << trade_ptr->exchange_id_ << "', "
            << gszChinaFutureTradeColName[CFTT_ProductID] << " = '" << trade_ptr->product_id_ << "', "
            << gszChinaFutureTradeColName[CFTT_ContractID] << " = '" << trade_ptr->contract_id_ << "', "
            << gszChinaFutureTradeColName[CFTT_GenerateDateTime] << " = '" << trade_ptr->generate_datetime_ << "', "
            << gszChinaFutureTradeColName[CFTT_Direct] << " = " << (int)trade_ptr->direct_type_ << ", "
            << gszChinaFutureTradeColName[CFTT_Offset] << " = " << (int)trade_ptr->offset_type_ << ", "
            << gszChinaFutureTradeColName[CFTT_TradeVol] << " = " << trade_ptr->volume_ << ", "
            << gszChinaFutureTradeColName[CFTT_CurrencyRate] << " = " << trade_ptr->currency_rate_ << ", "
            << gszChinaFutureTradeColName[CFTT_CurrencyID] << " = '" << trade_ptr->currency_id_ << "', "
            << gszChinaFutureTradeColName[CFTT_TradeAvePrice] << " = " << trade_ptr->trade_price_ << ", "
            << gszChinaFutureTradeColName[CFTT_CloseProfit] << " = " << trade_ptr->close_profit_ << ", "
            << gszChinaFutureTradeColName[CFTT_OperatorType] << " = " << (int)trade_ptr->op_type_ << "; ";

        errCode = phandler->ExecSql(sstr.str().c_str());

        DBAccess::FreeDBHandler(phandler);
        return errCode == 0;
    }
#pragma endregion

#pragma region 持仓
    bool DBOpTradeCenter::createStockPositionInfo()
    {
        CDBHandler *phandler = AllocDBHandler();
        if (!phandler)
            return false;

        int errCode = 0;

        std::stringstream sstr;
        sstr << "CREATE TABLE IF NOT EXISTS " << gszStockPositionTableName << " (";

        for (int i = 0; i < SPT_Max; i++)
        {
            sstr << gszStockPositionColName[i] << " " << gszStockPositionCreateColType[i];
            if (i < SPT_Max - 1)
                sstr << ",";
        }
        sstr << ");";

        errCode = phandler->ExecSql(sstr.str().c_str());
        if (errCode != 0)
            LOG4CXX_ERROR(logger, "创建股票持仓表失败!"LOG_NOVAR(sstr.str().c_str()));

        DBAccess::FreeDBHandler(phandler);
        return errCode == 0;
    }

    bool DBOpTradeCenter::createForeignFuturePositionInfo()
    {
        CDBHandler *phandler = AllocDBHandler();
        if (!phandler)
            return false;

        int errCode = 0;

        std::stringstream sstr;
        sstr << "CREATE TABLE IF NOT EXISTS " << gszForeignFuturePositionTableName << " (";

        for (int i = 0; i < FFPT_Max; i++)
        {
            sstr << gszForeignFuturePositionColName[i] << " " << gszForeignFuturePositionCreateColType[i];
            if (i < FFPT_Max - 1)
                sstr << ",";
        }
        sstr << ");";

        errCode = phandler->ExecSql(sstr.str().c_str());

        DBAccess::FreeDBHandler(phandler);
        return errCode == 0;
    }

    bool DBOpTradeCenter::createChinaFuturePositionInfo()
    {
        CDBHandler *phandler = AllocDBHandler();
        if (!phandler)
            return false;

        int errCode = 0;

        std::stringstream sstr;
        sstr << "CREATE TABLE IF NOT EXISTS " << gszChinaFuturePositionTableName << " (";

        for (int i = 0; i < CFPT_Max; i++)
        {
            sstr << gszChinaFuturePositionColName[i] << " " << gszChinaFuturePositionCreateColType[i];
            if (i < CFPT_Max - 1)
                sstr << ",";
        }
        sstr << ");";

        errCode = phandler->ExecSql(sstr.str().c_str());

        DBAccess::FreeDBHandler(phandler);
        return errCode == 0;
    }

    bool DBOpTradeCenter::updateStockPositionInfo(const AllTrade::NPTradeCenter::StockPositionPtr& position_ptr, const AllTrade::UserIDType user_id)
    {
        CDBHandler *phandler = AllocDBHandler();
        if (!phandler)
            return false;

        int errCode = 0;

        std::stringstream sstr;
        sstr << "REPLACE INTO " << gszStockPositionTableName << " set "
            << gszStockPositionColName[SPT_PositionID] << " = '" << position_ptr->position_id_ << "', "
            << gszStockPositionColName[SPT_UserID] << " = '" << user_id << "', "
            << gszStockPositionColName[SPT_ExchangeID] << " = '" << position_ptr->exchange_id_ << "', "
            << gszStockPositionColName[SPT_ContractID] << " = '" << position_ptr->contract_id_ << "', "
            << gszStockPositionColName[SPT_Direct] << " = " << (int)position_ptr->direct_type_ << ", "
            << gszStockPositionColName[SPT_PositionVol] << " = " << position_ptr->volume_ << ", "
            << gszStockPositionColName[SPT_PositionTVol] << " = " << position_ptr->T_volume_ << ", "
            << gszStockPositionColName[SPT_CurrencyID] << " = '" << position_ptr->currency_id_ << "', "
            << gszStockPositionColName[SPT_PositionCostPrice] << " = " << position_ptr->cost_price_ << ", "
            << gszStockPositionColName[SPT_TradeAvePrice] << " = " << position_ptr->trade_ave_price_ << ", "
            << gszStockPositionColName[SPT_StockArea] << " = " << (int)position_ptr->stock_area_ << ", "
            << gszStockPositionColName[SPT_PositionFreezeVol] << " = " << position_ptr->freeze_order_vol_ << "; ";

        errCode = phandler->ExecSql(sstr.str().c_str());
        if (errCode != 0)
            LOG4CXX_ERROR(logger, "更新股票持仓信息失败!"LOG_NOVAR(sstr.str().c_str()));

        DBAccess::FreeDBHandler(phandler);
        return errCode == 0;
    }

    bool DBOpTradeCenter::deleteStockPositionInfo(const AllTrade::NPTradeCenter::StockPositionPtr& position_ptr, const AllTrade::UserIDType user_id)
    {
        CDBHandler *phandler = AllocDBHandler();
        if (!phandler)
            return false;

        int errCode = 0;

        std::stringstream sstr;
        sstr << "DELETE FROM " << gszStockPositionTableName << " WHERE "
            << gszStockPositionColName[SPT_PositionID] << " = '" << position_ptr->position_id_ << "' "
            << " AND " << gszStockPositionColName[SPT_UserID] << " = '" << user_id << "' "
            << " AND " << gszStockPositionColName[SPT_ExchangeID] << " = '" << position_ptr->exchange_id_ << "' "
            << " AND " << gszStockPositionColName[SPT_ContractID] << " = '" << position_ptr->contract_id_ << "' "
            << " AND " << gszStockPositionColName[SPT_Direct] << " = " << (int)position_ptr->direct_type_ << " "
            << " AND " << gszStockPositionColName[SPT_StockArea] << " = " << (int)position_ptr->stock_area_ << " ";

        errCode = phandler->ExecSql(sstr.str().c_str());
        if (errCode != 0)
            LOG4CXX_ERROR(logger, "删除股票持仓信息失败!"LOG_NOVAR(sstr.str().c_str()));

        DBAccess::FreeDBHandler(phandler);
        return errCode == 0;
    }

    bool DBOpTradeCenter::updateForeignFuturePositionInfo(const AllTrade::NPTradeCenter::ForeignFuturePositionPtr& position_ptr, const AllTrade::UserIDType user_id)
    {
        CDBHandler *phandler = AllocDBHandler();
        if (!phandler)
            return false;

        int errCode = 0;

        std::stringstream sstr;
        sstr << "REPLACE INTO " << gszForeignFuturePositionTableName << " set "
            << gszForeignFuturePositionColName[FFPT_PositionID] << " = '" << position_ptr->position_id_ << "', "
            << gszForeignFuturePositionColName[FFPT_UserID] << " = '" << user_id << "', "
            << gszForeignFuturePositionColName[FFPT_ExchangeID] << " = '" << position_ptr->exchange_id_ << "', "
            << gszForeignFuturePositionColName[FFPT_ContractID] << " = '" << position_ptr->contract_id_ << "', "
            << gszForeignFuturePositionColName[FFPT_Direct] << " = " << (int)position_ptr->direct_type_ << ", "
            << gszForeignFuturePositionColName[FFPT_PositionVol] << " = " << position_ptr->volume_ << ", "
            << gszForeignFuturePositionColName[FFPT_CurrencyID] << " = '" << position_ptr->currency_id_ << "', "
            << gszForeignFuturePositionColName[FFPT_PositionCostPrice] << " = " << position_ptr->cost_price_ << "; ";

        errCode = phandler->ExecSql(sstr.str().c_str());

        DBAccess::FreeDBHandler(phandler);
        return errCode == 0;
    }

    bool DBOpTradeCenter::updateChinaFuturePositionInfo(const AllTrade::NPTradeCenter::ChinaFuturePositionPtr& position_ptr, const AllTrade::UserIDType user_id)
    {
        CDBHandler *phandler = AllocDBHandler();
        if (!phandler)
            return false;

        int errCode = 0;

        std::stringstream sstr;
        sstr << "REPLACE INTO " << gszChinaFuturePositionTableName << " set "
            << gszChinaFuturePositionColName[CFPT_PositionID] << " = '" << position_ptr->position_id_ << "', "
            << gszChinaFuturePositionColName[CFPT_UserID] << " = '" << user_id << "', "
            << gszChinaFuturePositionColName[CFPT_ExchangeID] << " = '" << position_ptr->exchange_id_ << "', "
            << gszChinaFuturePositionColName[CFPT_ContractID] << " = '" << position_ptr->contract_id_ << "', "
            << gszChinaFuturePositionColName[CFOT_OffsetType] << " = " << (int)position_ptr->offset_type_ << ", "
            << gszChinaFuturePositionColName[CFPT_Direct] << " = " << (int)position_ptr->direct_type_ << ", "
            << gszChinaFuturePositionColName[CFPT_PositionVol] << " = " << position_ptr->volume_ << ", "
            << gszChinaFuturePositionColName[CFPT_CurrencyID] << " = '" << position_ptr->currency_id_ << "', "
            << gszChinaFuturePositionColName[CFPT_PositionCostPrice] << " = " << position_ptr->cost_price_ << "; ";

        errCode = phandler->ExecSql(sstr.str().c_str());

        DBAccess::FreeDBHandler(phandler);
        return errCode == 0;
    }

#pragma endregion

    void DBOpTradeCenter::addStockBlackWhite(const ContractIDType contract_id)
    {
        CDBHandler *phandler = AllocDBHandler();
        if (!phandler)
            return;

        int errCode = 0;

        std::stringstream sstr;
        sstr << "INSERT INTO " << gszStockBlackWhiteTableName << " ( "
            << gszStockBlackWhiteColName[SBWT_ContractID] << ", "
            << gszStockBlackWhiteColName[SBWT_IsBlack] << ") "
            << " SELECT '" << contract_id << "', " << " 0 "
            << " FROM DUAL WHERE NOT EXISTS( SELECT " << gszStockBlackWhiteColName[SBWT_ContractID]
                << " FROM " << gszStockBlackWhiteTableName
                << " WHERE " << gszStockBlackWhiteColName[SBWT_ContractID] << " = '" << contract_id << "') "
            << " LIMIT 1";

        errCode = phandler->ExecSql(sstr.str().c_str());
        if (errCode != 0)
            LOG4CXX_ERROR(logger, "新增股票黑白名单合约信息失败!"LOG_NOVAR(sstr.str().c_str()));

        DBAccess::FreeDBHandler(phandler);
        return ;
    }

    bool DBOpTradeCenter::updateStockBlackWhiteStatus(const ContractIDType contract_id, bool isBlack)
    {
        CDBHandler *phandler = AllocDBHandler();
        if (!phandler)
            return false;

        int errCode = 0;

        std::stringstream sstr;
        sstr << "REPLACE INTO " << gszStockBlackWhiteTableName << " set "
            << gszStockBlackWhiteColName[SBWT_ContractID] << " = '" << contract_id << "', "
            << gszStockBlackWhiteColName[SBWT_IsBlack] << " = " << (isBlack ? 1 : 0) << "; ";

        errCode = phandler->ExecSql(sstr.str().c_str());

        DBAccess::FreeDBHandler(phandler);
        return errCode == 0;
    }

    std::map<AllTrade::PContractIDType, bool> DBOpTradeCenter::getAllStockBlackWhiteStatus()
    {
        std::map<AllTrade::PContractIDType, bool> rslt;
        CDBHandler *phandler = AllocDBHandler();
        if (!phandler)
            return rslt;

        HxSqlRes res = NULL;
        int errCode = 0;
        int recNum = 0;

        std::stringstream sstr;
        sstr << "SELECT * FROM " << gszStockBlackWhiteTableName;

        errCode = phandler->QuerySql(sstr.str().c_str(), res, true);

        if (errCode == 0 && res)
        {
            HxResRow row = NULL;

            while (row = phandler->FetchRow(res))
            {
                char *pchar;
                pchar = phandler->FetchField(row, SBWT_ContractID);
                PContractIDType contract_id = pchar;
                pchar = phandler->FetchField(row, SBWT_IsBlack);
                rslt[contract_id] = atoi(pchar) == 1;
            }
        }

        phandler->ReleaseRecords(res);
        DBAccess::FreeDBHandler(phandler);
        return rslt;
    }

    bool DBOpTradeCenter::isBlackStock(const ContractIDType contract_id)
    {
        bool rslt(false);
        CDBHandler *phandler = AllocDBHandler();
        if (!phandler)
            return false;

        HxSqlRes res = NULL;
        int errCode = 0;
        int recNum = 0;

        std::stringstream sstr;
        sstr << "SELECT * FROM " << gszStockBlackWhiteTableName
             << " WHERE " << gszStockBlackWhiteColName[SBWT_ContractID] << "='" << contract_id << "';";

        errCode = phandler->QuerySql(sstr.str().c_str(), res, true);

        if (errCode == 0 && res)
        {
            HxResRow row = NULL;

            if (row = phandler->FetchRow(res))
            {
                char *pchar;
                pchar = phandler->FetchField(row, SBWT_IsBlack);
                rslt = atoi(pchar) == 1;
            }
        }

        phandler->ReleaseRecords(res);
        DBAccess::FreeDBHandler(phandler);
        return rslt;
    }

    bool DBOpTradeCenter::createStockBlackWhite()
    {
        CDBHandler *phandler = AllocDBHandler();
        if (!phandler)
            return false;

        int errCode = 0;

        std::stringstream sstr;
        sstr << "CREATE TABLE IF NOT EXISTS " << gszStockBlackWhiteTableName << " (";

        for (int i = 0; i < SBWT_Max; i++)
        {
            sstr << gszStockBlackWhiteColName[i] << " " << gszStockBlackWhiteCreateColType[i];
            if (i < SBWT_Max - 1)
                sstr << ",";
        }
        sstr << ");";

        errCode = phandler->ExecSql(sstr.str().c_str());

        DBAccess::FreeDBHandler(phandler);
        return errCode == 0;
    }

    void DBOpTradeCenter::addStockBlackWhite(AllTrade::ForbidTradeType type)
    {
        CDBHandler *phandler = AllocDBHandler();
        if (!phandler)
            return;

        int errCode = 0;

        std::stringstream sstr;
        sstr << "INSERT INTO " << gszForbidTradeTableName << " ( "
            << gszForbidTradeColName[FTT_ID] << ", "
            << gszForbidTradeColName[FTT_OpType] << ", "
            << gszForbidTradeColName[FTT_BOpen] << ") "
            << " SELECT " << type << ", 0 , 0"
            << " FROM DUAL WHERE NOT EXISTS( SELECT " << gszForbidTradeColName[FTT_ID]
            << " FROM " << gszForbidTradeTableName
            << " WHERE " << gszForbidTradeColName[FTT_ID] << " = '" << type << "') "
            << " LIMIT 1";

        errCode = phandler->ExecSql(sstr.str().c_str());
        if (errCode != 0)
            LOG4CXX_ERROR(logger, "新增禁止交易风控信息失败!"LOG_NOVAR(sstr.str().c_str()));

        DBAccess::FreeDBHandler(phandler);
        return;
    }

    std::vector<AllTrade::NPTradeCenter::SForbidTradePtr> DBOpTradeCenter::getAllForbidTradeStatus()
    {
        std::vector<SForbidTradePtr> rslt;
        CDBHandler *phandler = AllocDBHandler();
        if (!phandler)
            return rslt;

        HxSqlRes res = NULL;
        int errCode = 0;
        int recNum = 0;

        std::stringstream sstr;
        sstr << "SELECT * FROM " << gszForbidTradeTableName;

        errCode = phandler->QuerySql(sstr.str().c_str(), res, true);

        if (errCode == 0 && res)
        {
            HxResRow row = NULL;

            while (row = phandler->FetchRow(res))
            {
                SForbidTradePtr ptr = std::make_shared<SForbidTradeInfo>();
                char *pchar;
                pchar = phandler->FetchField(row, FTT_ID);
                ptr->forbid_trade_type_ = (ForbidTradeType)atoi(pchar);
                pchar = phandler->FetchField(row, FTT_OpType);
                ptr->forbid_trade_op_type_ = (ForbidTradeOperatorType)atoi(pchar);
                pchar = phandler->FetchField(row, FTT_BOpen);
                ptr->bstart_ = atoi(pchar) != 0;
                rslt.push_back(ptr);
            }
        }

        phandler->ReleaseRecords(res);
        DBAccess::FreeDBHandler(phandler);
        return rslt;
    }

    bool DBOpTradeCenter::updateForbidTradeStatus(const AllTrade::NPTradeCenter::SForbidTradePtr& ptr)
    {
        CDBHandler *phandler = AllocDBHandler();
        if (!phandler)
            return false;

        int errCode = 0;

        std::stringstream sstr;
        sstr << "REPLACE INTO " << gszForbidTradeTableName << " set "
            << gszForbidTradeColName[FTT_ID] << " = " << ptr->forbid_trade_type_ << ", "
            << gszForbidTradeColName[FTT_OpType] << " = " << ptr->forbid_trade_op_type_ << ", "
            << gszForbidTradeColName[FTT_BOpen] << " = " << (ptr->bstart_ ? 1 : 0) << "; ";

        errCode = phandler->ExecSql(sstr.str().c_str());
        if (errCode != 0)
            LOG4CXX_ERROR(logger, "更新禁止交易风控信息失败!"LOG_NOVAR(sstr.str().c_str()));

        DBAccess::FreeDBHandler(phandler);
        return errCode == 0;
    }

    bool DBOpTradeCenter::createForbidTrade()
    {
        CDBHandler *phandler = AllocDBHandler();
        if (!phandler)
            return false;

        int errCode = 0;

        std::stringstream sstr;
        sstr << "CREATE TABLE IF NOT EXISTS " << gszForbidTradeTableName << " (";

        for (int i = 0; i < FTT_Max; i++)
        {
            sstr << gszForbidTradeColName[i] << " " << gszForbidTradeCreateColType[i];
            if (i < FTT_Max - 1)
                sstr << ",";
        }
        sstr << ");";

        errCode = phandler->ExecSql(sstr.str().c_str());

        DBAccess::FreeDBHandler(phandler);

        if (errCode == 0)
        {
            addStockBlackWhite(ForbidTradeType::FTT_LossCorporateStock);
            addStockBlackWhite(ForbidTradeType::FTT_RiseStopStock);
            addStockBlackWhite(ForbidTradeType::FTT_FallStopStock);
            addStockBlackWhite(ForbidTradeType::FTT_NewStock);
        }
        return errCode == 0;
    }

    void DBOpTradeCenter::addPositionRateStatus(AllTrade::PositionRateType type)
    {
        CDBHandler *phandler = AllocDBHandler();
        if (!phandler)
            return;

        int errCode = 0;

        std::stringstream sstr;
        sstr << "INSERT INTO " << gszPositionRateTableName << " ( "
            << gszPositionRateColName[PRT_ID] << ", "
            << gszPositionRateColName[PRT_Rate] << ", "
            << gszPositionRateColName[PRT_BOpen] << ") "
            << " SELECT " << type << ", 0 , 0"
            << " FROM DUAL WHERE NOT EXISTS( SELECT " << gszPositionRateColName[PRT_ID]
            << " FROM " << gszPositionRateTableName
            << " WHERE " << gszPositionRateColName[PRT_ID] << " = '" << type << "') "
            << " LIMIT 1";

        errCode = phandler->ExecSql(sstr.str().c_str());
        if (errCode != 0)
            LOG4CXX_ERROR(logger, "新增持仓比例风控信息失败!"LOG_NOVAR(sstr.str().c_str()));

        DBAccess::FreeDBHandler(phandler);
        return;
    }

    std::vector<AllTrade::NPTradeCenter::SPositionRatePtr> DBOpTradeCenter::getPositionRateStatus()
    {
        std::vector<SPositionRatePtr> rslt;
        CDBHandler *phandler = AllocDBHandler();
        if (!phandler)
            return rslt;

        HxSqlRes res = NULL;
        int errCode = 0;
        int recNum = 0;

        std::stringstream sstr;
        sstr << "SELECT * FROM " << gszPositionRateTableName;

        errCode = phandler->QuerySql(sstr.str().c_str(), res, true);

        if (errCode == 0 && res)
        {
            HxResRow row = NULL;

            while (row = phandler->FetchRow(res))
            {
                SPositionRatePtr ptr = std::make_shared<SPositionRateInfo>();
                char *pchar;
                pchar = phandler->FetchField(row, PRT_ID);
                ptr->position_rate_type_ = (PositionRateType)atoi(pchar);
                pchar = phandler->FetchField(row, PRT_Rate);
                ptr->position_rate_ = atoi(pchar);
                pchar = phandler->FetchField(row, PRT_BOpen);
                ptr->bstart_ = atoi(pchar) != 0;
                rslt.push_back(ptr);
            }
        }

        phandler->ReleaseRecords(res);
        DBAccess::FreeDBHandler(phandler);
        return rslt;
    }

    bool DBOpTradeCenter::updatePositionRateStatus(const AllTrade::NPTradeCenter::SPositionRatePtr& ptr)
    {
        CDBHandler *phandler = AllocDBHandler();
        if (!phandler)
            return false;

        int errCode = 0;

        std::stringstream sstr;
        sstr << "REPLACE INTO " << gszPositionRateTableName << " set "
            << gszPositionRateColName[PRT_ID] << " = " << ptr->position_rate_type_ << ", "
            << gszPositionRateColName[PRT_Rate] << " = " << ptr->position_rate_ << ", "
            << gszPositionRateColName[PRT_BOpen] << " = " << (ptr->bstart_ ? 1 : 0) << "; ";

        errCode = phandler->ExecSql(sstr.str().c_str());
        if (errCode != 0)
            LOG4CXX_ERROR(logger, "更新持仓比例风控信息失败!"LOG_NOVAR(sstr.str().c_str()));

        DBAccess::FreeDBHandler(phandler);
        return errCode == 0;
    }

	bool DBOpTradeCenter::selectHistoryRiskRecord(const AllTrade::UserIDType user_id, const AllTrade::DateType start_day, const AllTrade::DateType end_day, std::vector<AllTrade::NPTradeCenter::ImmRiskControlPtr>& vecSt)
	{
		CDBHandler *phandler = AllocDBHandler();
		if (!phandler)
			return false;

		HxSqlRes res = NULL;
		int errCode = 0;

		std::stringstream sstr;
		sstr << "SELECT * FROM " << gszRiskControlHistoryRecordTableName
			<< " WHERE " << gszRiskControlHistoryRecordColName[RCHRT_UserID] << " = '" << user_id << "' "
			<< " AND " << gszRiskControlHistoryRecordColName[RCHRT_DateTime] << " <= '" << end_day << "'"
			<< " AND " << gszRiskControlHistoryRecordColName[RCHRT_DateTime] << " >= '" << start_day << "'; ";

		errCode = phandler->QuerySql(sstr.str().c_str(), res, true);
		
		if (errCode == 0 && res)
		{
			HxResRow row = NULL;

			while (row = phandler->FetchRow(res))
			{
				AllTrade::NPTradeCenter::ImmRiskControlPtr rslt = std::make_shared<ImmRiskControlSt>();

				char *pchar;
				pchar = phandler->FetchField(row, RCHRT_UserID);
				strncpy_s(rslt->user_id_, user_id, sizeof(rslt->user_id_) - 1);
				pchar = phandler->FetchField(row, RCHRT_RiskType);
				rslt->rc_type_ = (RiskControlType)atoi(pchar);
				pchar = phandler->FetchField(row, RCHRT_BTrigger);
				rslt->bTrigger_ = atoi(pchar) == 1;
				strncpy_s(rslt->date_time_, phandler->FetchField(row, RCHRT_DateTime), sizeof(rslt->date_time_) - 1);
                if (pchar = phandler->FetchField(row, RCHRT_TriggerText))
                    strncpy_s(rslt->trigger_text_, pchar, sizeof(rslt->trigger_text_) - 1);

				vecSt.emplace_back(rslt);
			}
		}

		phandler->ReleaseRecords(res);
		DBAccess::FreeDBHandler(phandler);

		return errCode == 0;
	}


    bool DBOpTradeCenter::createPositionRate()
    {
        CDBHandler *phandler = AllocDBHandler();
        if (!phandler)
            return false;

        int errCode = 0;

        std::stringstream sstr;
        sstr << "CREATE TABLE IF NOT EXISTS " << gszPositionRateTableName << " (";

        for (int i = 0; i < PRT_Max; i++)
        {
            sstr << gszPositionRateColName[i] << " " << gszPositionRateCreateColType[i];
            if (i < PRT_Max - 1)
                sstr << ",";
        }
        sstr << ");";

        errCode = phandler->ExecSql(sstr.str().c_str());

        DBAccess::FreeDBHandler(phandler);

        if (errCode == 0)
        {
            addPositionRateStatus(PositionRateType::PRT_SameStock);
            addPositionRateStatus(PositionRateType::PRT_Second_Board);
        }

        return errCode == 0;
    }

	bool DBOpTradeCenter::createHistoryRiskRecord()
	{
		CDBHandler *phandler = AllocDBHandler();
		if (!phandler)
			return false;

		int errCode = 0;

		std::stringstream sstr;
		sstr << "CREATE TABLE IF NOT EXISTS " << gszRiskControlHistoryRecordTableName << " (";

		for (int i = 0; i < RCHRT_Max; i++)
		{
			sstr << gszRiskControlHistoryRecordColName[i] << " " << gszRiskControlHistoryRecordCreateColType[i];
			if (i < RCHRT_Max-1)
				sstr << ",";
		}

	//	sstr << "KEY `index_Id` (`" << gszRiskControlHistoryRecordColName[0] << "`)";
		sstr << ");";

		errCode = phandler->ExecSql(sstr.str().c_str());
		if (errCode != 0)
			LOG4CXX_ERROR(logger, "创建风控历史记录表失败!"LOG_NOVAR(sstr.str().c_str()));

		DBAccess::FreeDBHandler(phandler);
		return errCode == 0;
	}

	
	bool DBOpTradeCenter::createMarginPositionTable()
	{
		CDBHandler *phandler = AllocDBHandler();
		if (!phandler)
			return false;

		int errCode = 0;

		std::stringstream sstr;
		sstr << "CREATE TABLE IF NOT EXISTS " << gszMarginPositionTableName << " (";

		for (int i = 0; i < MPT_Max; i++)
		{
			sstr << gszMarginPositionColName[i] << " " << gszMarginPositionCreateColType[i];
			if (i < MPT_Max - 1)
				sstr << ",";
		}
		sstr << ");";

		errCode = phandler->ExecSql(sstr.str().c_str());
		if (errCode != 0)
			LOG4CXX_ERROR(logger, "创建融券持仓失败!"LOG_NOVAR(sstr.str().c_str()));

		DBAccess::FreeDBHandler(phandler);
		return errCode == 0;

	}

	bool DBOpTradeCenter::updateMarginPositionTable(const AllTrade::NPTradeCenter::MarginPositionInfoPtr& position_ptr, const AllTrade::UserIDType user_id)
	{
		CDBHandler *phandler = AllocDBHandler();
		if (!phandler)
			return false;

		int errCode = 0;

		std::stringstream sstr;
		sstr << "REPLACE INTO " << gszMarginPositionTableName << " set "
			<< gszMarginPositionColName[MPT_PositionID] << " = '" << position_ptr->position_id_ << "', "
			<< gszMarginPositionColName[MPT_UserID] << " = '" << user_id << "', "
			<< gszMarginPositionColName[MPT_ExchangeID] << " = '" << position_ptr->exchange_id_ << "', "
			<< gszMarginPositionColName[MPT_ContractID] << " = '" << position_ptr->contract_id_ << "', "
			<< gszMarginPositionColName[MPT_Direct] << " = " << (int)position_ptr->direct_type_ << ", "
			<< gszMarginPositionColName[MPT_PositionVol] << " = " << position_ptr->volume_ << ", "
			<< gszMarginPositionColName[MPT_PositionTVol] << " = " << position_ptr->T_volume_ << ", "
			<< gszMarginPositionColName[MPT_CurrencyID] << " = '" << position_ptr->currency_id_ << "', "
			<< gszMarginPositionColName[MPT_PositionCostPrice] << " = " << position_ptr->cost_price_ << ", "
			<< gszMarginPositionColName[MPT_TradeAvePrice] << " = " << position_ptr->trade_ave_price_ << ", "
			<< gszMarginPositionColName[MPT_StockArea] << " = " << (int)position_ptr->stock_area_ << ", "
			<< gszMarginPositionColName[MPT_PositionFreezeVol] << " = " << position_ptr->freeze_order_vol_ << "; ";

		errCode = phandler->ExecSql(sstr.str().c_str());
		if (errCode != 0)
			LOG4CXX_ERROR(logger, "更新融资持仓信息失败!"LOG_NOVAR(sstr.str().c_str()));

		DBAccess::FreeDBHandler(phandler);
		return errCode == 0;
	}

	bool DBOpTradeCenter::deleteMarginPositionInfo(const AllTrade::NPTradeCenter::MarginPositionInfoPtr& position_ptr, const AllTrade::UserIDType user_id)
	{
		CDBHandler *phandler = AllocDBHandler();
		if (!phandler)
			return false;

		int errCode = 0;

		std::stringstream sstr;
		sstr << "DELETE FROM " << gszMarginPositionTableName << " WHERE "
			<< gszMarginPositionColName[MPT_PositionID] << " = '" << position_ptr->position_id_ << "' "
			<< " AND " << gszMarginPositionColName[MPT_UserID] << " = '" << user_id << "' "
			<< " AND " << gszMarginPositionColName[MPT_ExchangeID] << " = '" << position_ptr->exchange_id_ << "' "
			<< " AND " << gszMarginPositionColName[MPT_ContractID] << " = '" << position_ptr->contract_id_ << "' "
			<< " AND " << gszMarginPositionColName[MPT_Direct] << " = " << (int)position_ptr->direct_type_ << " "
			<< " AND " << gszMarginPositionColName[MPT_StockArea] << " = " << (int)position_ptr->stock_area_ << " ";

		errCode = phandler->ExecSql(sstr.str().c_str());
		if (errCode != 0)
			LOG4CXX_ERROR(logger, "删除融资持仓信息失败!"LOG_NOVAR(sstr.str().c_str()));

		DBAccess::FreeDBHandler(phandler);
		return errCode == 0;
	}

	bool DBOpTradeCenter::getMarginPositionInfo(std::map<AllTrade::PUserIDType, std::vector<AllTrade::NPTradeCenter::MarginPositionInfoPtr>>& posiOrder)
	{
		CDBHandler *phandler = AllocDBHandler();
		if (!phandler)
			return false;

		HxSqlRes res = NULL;
		int errCode = 0;
		int recNum = 0;

		std::stringstream sstr;
		sstr << "SELECT * FROM " << gszMarginPositionTableName;

		errCode = phandler->QuerySql(sstr.str().c_str(), res, true);

		if (errCode == 0 && res)
		{
			HxResRow row = NULL;
			AllTrade::GUIDType userId;

			while (row = phandler->FetchRow(res))
			{
				AllTrade::NPTradeCenter::MarginPositionInfoPtr ptr = std::make_shared<MarginPositionInfo>();
				char *pchar;

				strncpy_s(ptr->position_id_, phandler->FetchField(row, MPT_PositionID), sizeof(ptr->position_id_) - 1);
				strncpy_s(userId, phandler->FetchField(row, MPT_UserID), sizeof(userId) - 1);

				strncpy_s(ptr->exchange_id_, phandler->FetchField(row, MPT_ExchangeID), sizeof(ptr->exchange_id_) - 1);
				strncpy_s(ptr->contract_id_, phandler->FetchField(row, MPT_ContractID), sizeof(ptr->contract_id_) - 1);

				pchar = phandler->FetchField(row, MPT_Direct);
				ptr->direct_type_ = (DirectType)(atoi(pchar));
				pchar = phandler->FetchField(row, MPT_PositionVol);
				ptr->volume_ = atoi(pchar);
				pchar = phandler->FetchField(row, MPT_PositionTVol);
				ptr->T_volume_ = atoi(pchar);
				strncpy_s(ptr->currency_id_, phandler->FetchField(row, MPT_CurrencyID), sizeof(ptr->currency_id_) - 1);

				pchar = phandler->FetchField(row, MPT_PositionCostPrice);
				ptr->cost_price_ = atof(pchar);

				pchar = phandler->FetchField(row, MPT_TradeAvePrice);
				ptr->trade_ave_price_ = atof(pchar);
				ptr->commodity_type_ = CommodityTypeType::COMMODITY_TYPE_STOCK;

				pchar = phandler->FetchField(row, MPT_StockArea);
				ptr->stock_area_ = (StockAreaType)atoi(pchar);

				pchar = phandler->FetchField(row, MPT_PositionFreezeVol);
				ptr->freeze_order_vol_ = atoi(pchar);

				posiOrder[userId].push_back(ptr);
			}
		}

		phandler->ReleaseRecords(res);
		DBAccess::FreeDBHandler(phandler);
		return errCode == 0;
	}

	bool DBOpTradeCenter::createMarginTradeTable()
	{
		CDBHandler *phandler = AllocDBHandler();
		if (!phandler)
			return false;

		int errCode = 0;

		std::stringstream sstr;
		sstr << "CREATE TABLE IF NOT EXISTS " << gszMarginTradeTableName << " (";

		for (int i = 0; i < MTT_Max; i++)
		{
			sstr << gszMarginTradeColName[i] << " " << gszMarginTradeCreateColType[i];
			if (i < MTT_Max - 1)
				sstr << ",";
		}
		sstr << ");";

		errCode = phandler->ExecSql(sstr.str().c_str());
		if (errCode != 0)
			LOG4CXX_ERROR(logger, "创建融券成交表失败!"LOG_NOVAR(sstr.str().c_str()));

		DBAccess::FreeDBHandler(phandler);
		return errCode == 0;
	}

	bool DBOpTradeCenter::updateMarginTradeTable(const AllTrade::NPTradeCenter::MarginTradeInfoPtr& trade_ptr, const AllTrade::UserIDType user_id)
	{
		CDBHandler *phandler = AllocDBHandler();
		if (!phandler)
			return false;

		int errCode = 0;

		std::stringstream sstr;
		sstr << "REPLACE INTO " << gszMarginTradeTableName << " SET "
			<< gszStockTradeColName[MTT_TradeID] << " = '" << trade_ptr->trade_id_ << "', "
			<< gszStockTradeColName[MTT_ShadowTradeID] << " = '" << trade_ptr->shadow_trade_id_ << "', "
			<< gszStockTradeColName[MTT_OrderStream] << " = '" << trade_ptr->order_stream_ << "', "
			<< gszStockTradeColName[MTT_PositionID] << " = '" << trade_ptr->position_id_ << "', "
			<< gszStockTradeColName[MTT_UserID] << " = '" << user_id << "', "
			<< gszStockTradeColName[MTT_ExchangeID] << " = '" << trade_ptr->exchange_id_ << "', "
			<< gszStockTradeColName[MTT_ContractID] << " = '" << trade_ptr->contract_id_ << "', "
			<< gszStockTradeColName[MTT_GenerateDateTime] << " = '" << trade_ptr->generate_datetime_ << "', "
			<< gszStockTradeColName[MTT_Direct] << " = " << (int)trade_ptr->direct_type_ << ", "
			<< gszStockTradeColName[MTT_TradeVol] << " = " << trade_ptr->volume_ << ", "
			<< gszStockTradeColName[MTT_CurrencyRate] << " = " << trade_ptr->currency_rate_ << ", "
			<< gszStockTradeColName[MTT_CurrencyID] << " = '" << trade_ptr->currency_id_ << "', "
			<< gszStockTradeColName[MTT_TradeAvePrice] << " = " << trade_ptr->trade_price_ << ", "
			<< gszStockTradeColName[MTT_CloseProfit] << " = " << trade_ptr->close_profit_ << ", "
			<< gszStockTradeColName[MTT_OperatorType] << " = " << (int)trade_ptr->op_type_ << ", "
			<< gszStockTradeColName[MTT_StockArea] << " = " << (int)trade_ptr->stock_area_ << ", "
			<< gszStockTradeColName[MTT_TradeFee] << " = " << trade_ptr->trade_fee_ << ", "
			<< gszStockTradeColName[MTT_StampFee] << " = " << trade_ptr->stamp_fee_ << ", "
			<< gszStockTradeColName[MTT_TransferFee] << " = " << trade_ptr->transfer_fee_ << ", "
			<< gszStockTradeColName[MTT_InfomatchFee] << " = " << trade_ptr->infomatch_fee_ << ", "
			<< gszStockTradeColName[MTT_DayInterset] << " = " << trade_ptr->day_interset_ << ", "
			<< gszStockTradeColName[MTT_IntersetFund] << " = " << trade_ptr->interset_fund_ << "; ";

		errCode = phandler->ExecSql(sstr.str().c_str());
		if (errCode != 0)
			LOG4CXX_ERROR(logger, "更新融资成交信息失败!"LOG_NOVAR(sstr.str().c_str()));

		DBAccess::FreeDBHandler(phandler);
		return errCode == 0;
	}


	bool DBOpTradeCenter::getMarginTradeRecord(std::map<AllTrade::PUserIDType, AllTrade::NPTradeCenter::MarginTradeInfoPtr>& tradeOrder)
	{

		CDBHandler *phandler = AllocDBHandler();
		if (!phandler)
			return false;

		HxSqlRes res = NULL;
		int errCode = 0;
		int recNum = 0;

		std::stringstream sstr;
		sstr << "SELECT * FROM " << gszMarginTradeTableName;

		errCode = phandler->QuerySql(sstr.str().c_str(), res, true);

		if (errCode == 0 && res)
		{
			HxResRow row = NULL;
			AllTrade::GUIDType userId;

			while (row = phandler->FetchRow(res))
			{
				AllTrade::NPTradeCenter::MarginTradeInfoPtr ptr = std::make_shared<MarginTradeInfo>();
				char *pchar;

				strncpy_s(ptr->trade_id_, phandler->FetchField(row, MTT_TradeID), sizeof(ptr->trade_id_) - 1);
				strncpy_s(ptr->shadow_trade_id_, phandler->FetchField(row, MTT_ShadowTradeID), sizeof(ptr->shadow_trade_id_) - 1);
				strncpy_s(ptr->order_stream_, phandler->FetchField(row, MTT_OrderStream), sizeof(ptr->order_stream_) - 1);

				strncpy_s(ptr->position_id_, phandler->FetchField(row, MTT_PositionID), sizeof(ptr->position_id_) - 1);
				strncpy_s(userId, phandler->FetchField(row, MTT_UserID), sizeof(userId) - 1);

				strncpy_s(ptr->exchange_id_, phandler->FetchField(row, MTT_ExchangeID), sizeof(ptr->exchange_id_) - 1);
				strncpy_s(ptr->contract_id_, phandler->FetchField(row, MTT_ContractID), sizeof(ptr->contract_id_) - 1);
				strncpy_s(ptr->generate_datetime_, phandler->FetchField(row, MTT_GenerateDateTime), sizeof(ptr->generate_datetime_) - 1);

				pchar = phandler->FetchField(row, MTT_Direct);
				ptr->direct_type_ = (DirectType)(atoi(pchar));
				pchar = phandler->FetchField(row, MTT_TradeVol);
				ptr->volume_ = atoi(pchar);

				pchar = phandler->FetchField(row, MTT_CurrencyRate);
				ptr->currency_rate_ = atof(pchar);
				strncpy_s(ptr->currency_id_, phandler->FetchField(row, MTT_CurrencyID), sizeof(ptr->currency_id_) - 1);
				pchar = phandler->FetchField(row, MTT_TradeAvePrice);
				ptr->trade_price_ = atof(pchar);
				pchar = phandler->FetchField(row, MTT_CloseProfit);
				ptr->close_profit_ = atof(pchar);
				pchar = phandler->FetchField(row, MTT_OperatorType);
				ptr->op_type_ = (OperatorTradeType)(atoi(pchar));
				ptr->commodity_type_ = CommodityTypeType::COMMODITY_TYPE_STOCK;
				pchar = phandler->FetchField(row, MTT_StockArea);
				ptr->stock_area_ = (StockAreaType)atoi(pchar);

				pchar = phandler->FetchField(row, MTT_TradeFee);
				ptr->trade_fee_ = atof(pchar);
				pchar = phandler->FetchField(row, MTT_StampFee);
				ptr->stamp_fee_ = atof(pchar);
				pchar = phandler->FetchField(row, MTT_TransferFee);
				ptr->transfer_fee_ = atof(pchar);
				pchar = phandler->FetchField(row, MTT_InfomatchFee);
				ptr->infomatch_fee_ = atof(pchar);

				pchar = phandler->FetchField(row, MTT_DayInterset);
				ptr->day_interset_ = atof(pchar);
				pchar = phandler->FetchField(row, MTT_IntersetFund);
				ptr->interset_fund_ = atof(pchar);

				tradeOrder[userId] = ptr;
			}
		}

		phandler->ReleaseRecords(res);
		DBAccess::FreeDBHandler(phandler);
		return errCode == 0;
	}

	std::vector<AllTrade::NPTradeCenter::MarginTradeInfoPtr> DBOpTradeCenter::getMarginTradeHistory(const AllTrade::UserIDType user_id, const AllTrade::DateType start_time, const AllTrade::DateType end_time)
	{
		std::vector<AllTrade::NPTradeCenter::MarginTradeInfoPtr> rslt;
		CDBHandler *phandler = AllocDBHandler();
		if (!phandler)
			return rslt;

		HxSqlRes res = NULL;
		int errCode = 0;
		int recNum = 0;

		std::stringstream sstr;
		sstr << "SELECT * FROM " << gszMarginTradeTableName
			<< " where " << gszMarginTradeColName[MTT_UserID] << " = '" << user_id << "'"
			<< " and " << gszMarginTradeColName[MTT_GenerateDateTime] << " >= '" << start_time << "'"
			<< " and " << gszMarginTradeColName[MTT_GenerateDateTime] << " <= '" << end_time << "'";

		errCode = phandler->QuerySql(sstr.str().c_str(), res, true);

		if (errCode == 0 && res)
		{
			HxResRow row = NULL;
			AllTrade::GUIDType userId;

			while (row = phandler->FetchRow(res))
			{
				AllTrade::NPTradeCenter::MarginTradeInfoPtr ptr = std::make_shared<MarginTradeInfo>();
				char *pchar;

				strncpy_s(ptr->trade_id_, phandler->FetchField(row, MTT_TradeID), sizeof(ptr->trade_id_) - 1);
				strncpy_s(ptr->shadow_trade_id_, phandler->FetchField(row, MTT_ShadowTradeID), sizeof(ptr->shadow_trade_id_) - 1);
				strncpy_s(ptr->order_stream_, phandler->FetchField(row, MTT_OrderStream), sizeof(ptr->order_stream_) - 1);

				strncpy_s(ptr->position_id_, phandler->FetchField(row, MTT_PositionID), sizeof(ptr->position_id_) - 1);
				strncpy_s(userId, phandler->FetchField(row, MTT_UserID), sizeof(userId) - 1);

				strncpy_s(ptr->exchange_id_, phandler->FetchField(row, MTT_ExchangeID), sizeof(ptr->exchange_id_) - 1);
				strncpy_s(ptr->contract_id_, phandler->FetchField(row, MTT_ContractID), sizeof(ptr->contract_id_) - 1);
				strncpy_s(ptr->generate_datetime_, phandler->FetchField(row, MTT_GenerateDateTime), sizeof(ptr->generate_datetime_) - 1);

				pchar = phandler->FetchField(row, MTT_Direct);
				ptr->direct_type_ = (DirectType)(atoi(pchar));
				pchar = phandler->FetchField(row, MTT_TradeVol);
				ptr->volume_ = atoi(pchar);

				pchar = phandler->FetchField(row, MTT_CurrencyRate);
				ptr->currency_rate_ = atof(pchar);
				strncpy_s(ptr->currency_id_, phandler->FetchField(row, MTT_CurrencyID), sizeof(ptr->currency_id_) - 1);
				pchar = phandler->FetchField(row, MTT_TradeAvePrice);
				ptr->trade_price_ = atof(pchar);
				pchar = phandler->FetchField(row, MTT_CloseProfit);
				ptr->close_profit_ = atof(pchar);
				pchar = phandler->FetchField(row, MTT_OperatorType);
				ptr->op_type_ = (OperatorTradeType)(atoi(pchar));
				ptr->commodity_type_ = CommodityTypeType::COMMODITY_TYPE_STOCK;
				pchar = phandler->FetchField(row, MTT_StockArea);
				ptr->stock_area_ = (StockAreaType)atoi(pchar);

				pchar = phandler->FetchField(row, MTT_TradeFee);
				ptr->trade_fee_ = atof(pchar);
				pchar = phandler->FetchField(row, MTT_StampFee);
				ptr->stamp_fee_ = atof(pchar);
				pchar = phandler->FetchField(row, MTT_TransferFee);
				ptr->transfer_fee_ = atof(pchar);
				pchar = phandler->FetchField(row, MTT_InfomatchFee);
				ptr->infomatch_fee_ = atof(pchar);

				rslt.push_back(ptr);
			}
		}

		phandler->ReleaseRecords(res);
		DBAccess::FreeDBHandler(phandler);
		return rslt;
	}

	bool DBOpTradeCenter::createMarginOrderTable()
	{
		CDBHandler *phandler = AllocDBHandler();
		if (!phandler)
			return false;

		int errCode = 0;

		std::stringstream sstr;
		sstr << "CREATE TABLE IF NOT EXISTS " << gszMarginOrderTableName << " (";

		for (int i = 0; i < MOT_Max; i++)
		{
			sstr << gszMarginOrderTableColName[i] << " " << gszMarginOrderTableColType[i];
			if (i < MOT_Max - 1)
				sstr << ",";
		}
		sstr << ");";

		errCode = phandler->ExecSql(sstr.str().c_str());
		if (errCode != 0)
			LOG4CXX_ERROR(logger, "创建融券委托表失败!"LOG_NOVAR(sstr.str().c_str()));

		DBAccess::FreeDBHandler(phandler);
		return errCode == 0;
	}

	
	bool DBOpTradeCenter::updateMarginOrderTable(const AllTrade::NPTradeCenter::MarginOrderInfoPtr& order_ptr, const AllTrade::UserIDType user_id)
	{
		CDBHandler *phandler = AllocDBHandler();
		if (!phandler)
			return false;

		int errCode = 0;
		std::stringstream sstr;
		sstr << "REPLACE INTO " << gszMarginOrderTableName << " set "
			<< gszMarginOrderTableColName[MOT_OrderStream] << " = '" << order_ptr->order_stream_ << "', "
			<< gszMarginOrderTableColName[MOT_OrderID] << " = '" << order_ptr->order_id_ << "', "
			<< gszMarginOrderTableColName[MOT_UserID] << " = '" << user_id << "', "
			<< gszMarginOrderTableColName[MOT_ContractID] << " = '" << order_ptr->contract_id_ << "', "
			<< gszMarginOrderTableColName[MOT_OrderState] << " = " << (int)order_ptr->order_state_ << ", "
			<< gszMarginOrderTableColName[MOT_OrderStateExplain] << " = " << order_ptr->orser_state_explain_ << ", "
			<< gszMarginOrderTableColName[MOT_OrderRef] << " = '" << order_ptr->order_ref_ << "', "
			<< gszMarginOrderTableColName[MOT_LoclaTmp_OrderRef] << " = '" << order_ptr->order_localtmp_ref_ << "', "
			<< gszMarginOrderTableColName[MOT_ShadowOrderID] << " = '" << order_ptr->shadow_order_id_ << "', "
			<< gszMarginOrderTableColName[MOT_GenerateDateTime] << " = '" << order_ptr->generate_datetime_ << "', "
			<< gszMarginOrderTableColName[MOT_UpdateDateTime] << " = '" << order_ptr->update_datetime_ << "', "
			<< gszMarginOrderTableColName[MOT_CurrencyRate] << " = '" << order_ptr->currency_rate_ << "', "
			<< gszMarginOrderTableColName[MOT_CurrencyID] << " = '" << order_ptr->currency_id_ << "', "
			<< gszMarginOrderTableColName[MOT_OrderPrice] << " = " << order_ptr->order_price_ << ", "
			<< gszMarginOrderTableColName[MOT_Direct] << " = " << (int)order_ptr->direct_type_ << ", "
			<< gszMarginOrderTableColName[MOT_OrderVol] << " = " << order_ptr->order_vol_ << ", "
			<< gszMarginOrderTableColName[MOT_EffectedVol] << " = " << order_ptr->effected_vol_ << ", "
			<< gszMarginOrderTableColName[MOT_TradeVol] << " = " << order_ptr->trade_vol_ << ", "
			<< gszMarginOrderTableColName[MOT_BFreezePosition] << " = " << (order_ptr->b_freeze_position_ ? 1 : 0) << ", "
			<< gszMarginOrderTableColName[MOT_FreezeMoney] << " = " << order_ptr->freeze_money_ << ", "
			<< gszMarginOrderTableColName[MOT_BFreezeMoney] << " = " << (order_ptr->b_freeze_money_ ? 1 : 0) << ", "
			<< gszMarginOrderTableColName[MOT_OrderType] << " = " << (int)order_ptr->order_type_ << ", "
			<< gszMarginOrderTableColName[MOT_OrderTradeMode] << " = " << (int)order_ptr->order_trade_mode_ << ", "
			<< gszMarginOrderTableColName[MOT_OrderTradePrice] << " = " << order_ptr->order_trade_price_ << ", "
			<< gszMarginOrderTableColName[MOT_OrderPositionCost] << " = " << order_ptr->position_cost_ << ", "
			<< gszMarginOrderTableColName[MOT_SystemOrderID] << " = '" << order_ptr->system_order_id_ << "', "
			<< gszMarginOrderTableColName[MOT_ExchangeID] << " = '" << order_ptr->exchange_id_ << "', "
			<< gszMarginOrderTableColName[MOT_ApiType] << " = " << (int)order_ptr->api_type_ << ", "
			<< gszMarginOrderTableColName[MOT_OperatorType] << " = " << (int)order_ptr->op_type_ << ", "
			<< gszMarginOrderTableColName[MOT_OrderMode] << " = " << (int)order_ptr->order_mode_ << ", "
			//             << gszMarginOrderTableColName[MOT_ValidDateTime] << " = '" << order_ptr->valid_datetime_ << "', "
			<< gszMarginOrderTableColName[MOT_StockArea] << " = " << (int)order_ptr->stock_area_ << ", "
			<< gszMarginOrderTableColName[MOT_CurTradeFee] << " = " << order_ptr->cur_trade_fee_ << ", "
			<< gszMarginOrderTableColName[MOT_CurStampFee] << " = " << order_ptr->cur_stamp_fee_ << ", "
			<< gszMarginOrderTableColName[MOT_CurTransferFee] << " = " << order_ptr->cur_transfer_fee_ << ", "
			<< gszMarginOrderTableColName[MOT_CurInfomatchFee] << " = " << order_ptr->cur_infomatch_fee_ << "; ";

		errCode = phandler->ExecSql(sstr.str().c_str());
		if (errCode != 0)
			LOG4CXX_ERROR(logger, "更新融资委托信息失败!"LOG_NOVAR(sstr.str().c_str()));

		DBAccess::FreeDBHandler(phandler);
		return errCode == 0;


	}

	bool DBOpTradeCenter::getMarginOrderInfo(std::map<AllTrade::PUserIDType, std::vector<AllTrade::NPTradeCenter::MarginOrderInfoPtr>>& marginOrder)
	{
		CDBHandler *phandler = AllocDBHandler();
		if (!phandler)
			return false;

		HxSqlRes res = NULL;
		int errCode = 0;
		int recNum = 0;

		std::stringstream sstr;
		sstr << "SELECT * FROM " << gszMarginOrderTableName << " where "
			<< gszMarginOrderTableColName[MOT_OrderState] << " != " << (int)AllTrade::OrderStateType::ORDER_STATE_FAIL << " and "
			<< gszMarginOrderTableColName[MOT_OrderState] << " != " << (int)AllTrade::OrderStateType::ORDER_STATE_DELETED << " and "
			<< gszMarginOrderTableColName[MOT_OrderState] << " != " << (int)AllTrade::OrderStateType::ORDER_STATE_FINISHED;

		errCode = phandler->QuerySql(sstr.str().c_str(), res, true);

		if (errCode == 0 && res)
		{
			HxResRow row = NULL;
			AllTrade::GUIDType userId;

			while (row = phandler->FetchRow(res))
			{
				AllTrade::NPTradeCenter::MarginOrderInfoPtr ptr = std::make_shared<MarginOrderInfo>();
				char *pchar;
				strncpy_s(ptr->order_stream_, phandler->FetchField(row, MOT_OrderStream), sizeof(ptr->order_stream_) - 1);
				strncpy_s(ptr->order_id_, phandler->FetchField(row, MOT_OrderID), sizeof(ptr->order_id_) - 1);

				strncpy_s(userId, phandler->FetchField(row, MOT_UserID), sizeof(AllTrade::GUIDType) - 1);

				strncpy_s(ptr->contract_id_, phandler->FetchField(row, MOT_ContractID), sizeof(ptr->contract_id_) - 1);
				pchar = phandler->FetchField(row, MOT_OrderState);
				ptr->order_state_ = (OrderStateType)(atoi(pchar));

				pchar = phandler->FetchField(row, MOT_OrderStateExplain);
				ptr->orser_state_explain_ = (OrderStateExplainType)(atoi(pchar));
				strncpy_s(ptr->order_ref_, phandler->FetchField(row, MOT_OrderRef), sizeof(ptr->order_ref_) - 1);

				strncpy_s(ptr->order_localtmp_ref_, phandler->FetchField(row, MOT_LoclaTmp_OrderRef), sizeof(ptr->order_localtmp_ref_) - 1);

				strncpy_s(ptr->shadow_order_id_, phandler->FetchField(row, MOT_ShadowOrderID), sizeof(ptr->shadow_order_id_) - 1);
				strncpy_s(ptr->generate_datetime_, phandler->FetchField(row, MOT_GenerateDateTime), sizeof(ptr->generate_datetime_) - 1);
				strncpy_s(ptr->update_datetime_, phandler->FetchField(row, MOT_UpdateDateTime), sizeof(ptr->update_datetime_) - 1);
				pchar = phandler->FetchField(row, MOT_Direct);
				ptr->direct_type_ = (DirectType)(atoi(pchar));

				pchar = phandler->FetchField(row, MOT_CurrencyRate);
				ptr->currency_rate_ = atof(pchar);
				strncpy_s(ptr->currency_id_, phandler->FetchField(row, MOT_CurrencyID), sizeof(ptr->currency_id_) - 1);

				pchar = phandler->FetchField(row, MOT_OrderPrice);
				ptr->order_price_ = atof(pchar);
				pchar = phandler->FetchField(row, MOT_OrderVol);
				ptr->order_vol_ = atoi(pchar);
				pchar = phandler->FetchField(row, MOT_EffectedVol);
				ptr->effected_vol_ = atoi(pchar);
				pchar = phandler->FetchField(row, MOT_TradeVol);
				ptr->trade_vol_ = atoi(pchar);
				pchar = phandler->FetchField(row, MOT_BFreezePosition);
				ptr->b_freeze_position_ = atoi(pchar) == 1;
				pchar = phandler->FetchField(row, MOT_FreezeMoney);
				ptr->freeze_money_ = atof(pchar);
				pchar = phandler->FetchField(row, MOT_BFreezeMoney);
				ptr->b_freeze_money_ = atoi(pchar) == 1;
				pchar = phandler->FetchField(row, MOT_OrderType);
				ptr->order_type_ = (OrderTypeType)(atoi(pchar));
				pchar = phandler->FetchField(row, MOT_OrderTradeMode);
				ptr->order_trade_mode_ = (OrderTradeModeType)(atoi(pchar));

				pchar = phandler->FetchField(row, MOT_OrderTradePrice);
				ptr->order_trade_price_ = atof(pchar);
				pchar = phandler->FetchField(row, MOT_OrderPositionCost);
				ptr->position_cost_ = atof(pchar);

				strncpy_s(ptr->system_order_id_, phandler->FetchField(row, MOT_SystemOrderID), sizeof(ptr->system_order_id_) - 1);
				strncpy_s(ptr->exchange_id_, phandler->FetchField(row, MOT_ExchangeID), sizeof(ptr->exchange_id_) - 1);

				pchar = phandler->FetchField(row, MOT_ApiType);
				ptr->api_type_ = (ApiTypeType)(atoi(pchar));
				pchar = phandler->FetchField(row, MOT_OperatorType);
				ptr->op_type_ = (OperatorTradeType)(atoi(pchar));
				pchar = phandler->FetchField(row, MOT_OrderMode);
				ptr->order_mode_ = (OrderModeType)(atoi(pchar));
				pchar = phandler->FetchField(row, MOT_StockArea);
				ptr->stock_area_ = (StockAreaType)(atoi(pchar));
				//                 strncpy_s(ptr->valid_datetime_, phandler->FetchField(row, MOT_ValidDateTime), sizeof(ptr->valid_datetime_) - 1);
				ptr->commodity_type_ = CommodityTypeType::COMMODITY_TYPE_STOCK;

				marginOrder[userId].push_back(ptr);
			}
		}

		phandler->ReleaseRecords(res);
		DBAccess::FreeDBHandler(phandler);
		return errCode == 0;
	}

	std::vector<AllTrade::NPTradeCenter::MarginOrderInfoPtr> DBOpTradeCenter::getAllMarginOrderHistory(const AllTrade::UserIDType user_id, const AllTrade::DateType start_time, const AllTrade::DateType end_time)
	{
		std::vector<AllTrade::NPTradeCenter::MarginOrderInfoPtr> rslt;
		CDBHandler *phandler = AllocDBHandler();
		if (!phandler)
			return rslt;

		HxSqlRes res = NULL;
		int errCode = 0;
		int recNum = 0;

		std::stringstream sstr;
		sstr << "SELECT * FROM " << gszMarginOrderTableName
			<< " where " << gszMarginOrderTableColName[MOT_UserID] << " = '" << user_id << "'"
			<< " and " << gszMarginOrderTableColName[MOT_GenerateDateTime] << " >= '" << start_time << "'"
			<< " and " << gszMarginOrderTableColName[MOT_GenerateDateTime] << " <= '" << end_time << "'";

		std::string tmp = sstr.str();
		errCode = phandler->QuerySql(sstr.str().c_str(), res, true);

		if (errCode == 0 && res)
		{
			HxResRow row = NULL;
			AllTrade::GUIDType userId;

			while (row = phandler->FetchRow(res))
			{
				AllTrade::NPTradeCenter::MarginOrderInfoPtr ptr = std::make_shared<MarginOrderInfo>();
				char *pchar;
				strncpy_s(ptr->order_stream_, phandler->FetchField(row, MOT_OrderStream), sizeof(ptr->order_stream_) - 1);
				strncpy_s(ptr->order_id_, phandler->FetchField(row, MOT_OrderID), sizeof(ptr->order_id_) - 1);

				strncpy_s(userId, phandler->FetchField(row, MOT_UserID), sizeof(AllTrade::GUIDType) - 1);

				strncpy_s(ptr->contract_id_, phandler->FetchField(row, MOT_ContractID), sizeof(ptr->contract_id_) - 1);
				pchar = phandler->FetchField(row, MOT_OrderState);
				ptr->order_state_ = (OrderStateType)(atoi(pchar));

				pchar = phandler->FetchField(row, MOT_OrderStateExplain);
				ptr->orser_state_explain_ = (OrderStateExplainType)(atoi(pchar));
				strncpy_s(ptr->order_ref_, phandler->FetchField(row, MOT_OrderRef), sizeof(ptr->order_ref_) - 1);

				strncpy_s(ptr->order_localtmp_ref_, phandler->FetchField(row, MOT_LoclaTmp_OrderRef), sizeof(ptr->order_localtmp_ref_) - 1);

				strncpy_s(ptr->shadow_order_id_, phandler->FetchField(row, MOT_ShadowOrderID), sizeof(ptr->shadow_order_id_) - 1);
				strncpy_s(ptr->generate_datetime_, phandler->FetchField(row, MOT_GenerateDateTime), sizeof(ptr->generate_datetime_) - 1);
				strncpy_s(ptr->update_datetime_, phandler->FetchField(row, MOT_UpdateDateTime), sizeof(ptr->update_datetime_) - 1);
				pchar = phandler->FetchField(row, MOT_Direct);
				ptr->direct_type_ = (DirectType)(atoi(pchar));

				pchar = phandler->FetchField(row, MOT_CurrencyRate);
				ptr->currency_rate_ = atof(pchar);
				strncpy_s(ptr->currency_id_, phandler->FetchField(row, MOT_CurrencyID), sizeof(ptr->currency_id_) - 1);

				pchar = phandler->FetchField(row, MOT_OrderPrice);
				ptr->order_price_ = atof(pchar);
				pchar = phandler->FetchField(row, MOT_OrderVol);
				ptr->order_vol_ = atoi(pchar);
				pchar = phandler->FetchField(row, MOT_EffectedVol);
				ptr->effected_vol_ = atoi(pchar);
				pchar = phandler->FetchField(row, MOT_TradeVol);
				ptr->trade_vol_ = atoi(pchar);
				pchar = phandler->FetchField(row, MOT_BFreezePosition);
				ptr->b_freeze_position_ = atoi(pchar) == 1;
				pchar = phandler->FetchField(row, MOT_FreezeMoney);
				ptr->freeze_money_ = atof(pchar);
				pchar = phandler->FetchField(row, MOT_BFreezeMoney);
				ptr->b_freeze_position_ = atoi(pchar) == 1;
				pchar = phandler->FetchField(row, MOT_OrderType);
				ptr->order_type_ = (OrderTypeType)(atoi(pchar));
				pchar = phandler->FetchField(row, MOT_OrderTradeMode);
				ptr->order_trade_mode_ = (OrderTradeModeType)(atoi(pchar));

				pchar = phandler->FetchField(row, MOT_OrderTradePrice);
				ptr->order_trade_price_ = atof(pchar);
				pchar = phandler->FetchField(row, MOT_OrderPositionCost);
				ptr->position_cost_ = atof(pchar);

				strncpy_s(ptr->system_order_id_, phandler->FetchField(row, MOT_SystemOrderID), sizeof(ptr->system_order_id_) - 1);
				strncpy_s(ptr->exchange_id_, phandler->FetchField(row, MOT_ExchangeID), sizeof(ptr->exchange_id_) - 1);

				pchar = phandler->FetchField(row, MOT_ApiType);
				ptr->api_type_ = (ApiTypeType)(atoi(pchar));
				pchar = phandler->FetchField(row, MOT_OperatorType);
				ptr->op_type_ = (OperatorTradeType)(atoi(pchar));
				pchar = phandler->FetchField(row, MOT_OrderMode);
				ptr->order_mode_ = (OrderModeType)(atoi(pchar));
				pchar = phandler->FetchField(row, MOT_StockArea);
				ptr->stock_area_ = (StockAreaType)(atoi(pchar));
				//                 strncpy_s(ptr->valid_datetime_, phandler->FetchField(row, MOT_ValidDateTime), sizeof(ptr->valid_datetime_) - 1);
				ptr->commodity_type_ = CommodityTypeType::COMMODITY_TYPE_STOCK;

				rslt.push_back(ptr);
			}
		}

		phandler->ReleaseRecords(res);
		DBAccess::FreeDBHandler(phandler);
		return rslt;
	}

	bool DBOpTradeCenter::createMarginInfoTable()
	{
		CDBHandler *phandler = AllocDBHandler();
		if (!phandler)
			return false;

		int errCode = 0;

		std::stringstream sstr;
		sstr << "CREATE TABLE IF NOT EXISTS " << gszMarginInfoTableName << " (";

		for (int i = 0; i < MIT_Max; i++)
		{
			sstr << gszMarginInfoTableColName[i] << " " << gszMarginInfoTableColType[i];
			if (i < MIT_Max - 1)
				sstr << ",";
		}
		sstr << ");";

		errCode = phandler->ExecSql(sstr.str().c_str());
		if (errCode != 0)
			LOG4CXX_ERROR(logger, "创建融券信息表失败!"LOG_NOVAR(sstr.str().c_str()));

		DBAccess::FreeDBHandler(phandler);
		return errCode == 0;
	}

	bool DBOpTradeCenter::updateMarginInfoTable(const AllTrade::NPTradeCenter::MarginInfoPtr& ptr)
	{
		CDBHandler *phandler = AllocDBHandler();
		if (!phandler)
			return false;

		int errCode = 0;

		std::stringstream sstr;


		sstr << "REPLACE INTO " << gszMarginInfoTableName << " SET "
			<< gszMarginInfoTableColName[MIT_SumQty] << " = '" << ptr->sum_Margin_Qty_ << "', "
			<< gszMarginInfoTableColName[MIT_Interest] << " = '" << ptr->Interest_ << "', ";

	
		errCode = phandler->ExecSql(sstr.str().c_str());

		DBAccess::FreeDBHandler(phandler);
		return errCode == 0;
	}

	bool DBOpTradeCenter::getAllMarginInfo(const AllTrade::NPTradeCenter::MarginInfoPtr& ptr)
	{
		
		CDBHandler *phandler = AllocDBHandler();
		if (!phandler)
			return false;

		HxSqlRes res = NULL;
		int errCode = 0;
		int recNum = 0;

		std::stringstream sstr;
		sstr << "SELECT * FROM " << gszMarginInfoTableName;

		errCode = phandler->QuerySql(sstr.str().c_str(), res, true);

		if (errCode == 0 && res)
		{
			HxResRow row = NULL;

			while (row = phandler->FetchRow(res))
			{
				char *pchar;
				pchar = phandler->FetchField(row, MIT_SumQty);
				ptr->sum_Margin_Qty_ = atoi(pchar);
				pchar = phandler->FetchField(row, MIT_Interest);
				ptr->Interest_ = atoi(pchar);
			}
		}

		phandler->ReleaseRecords(res);
		DBAccess::FreeDBHandler(phandler);
		return errCode==0;
	}

	

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	bool DBOpTradeCenter::createMarginLeftTable()
	{
		CDBHandler *phandler = AllocDBHandler();
		if (!phandler)
			return false;

		int errCode = 0;

		std::stringstream sstr;
		sstr << "CREATE TABLE IF NOT EXISTS " << gszMarginLeftQtyTableName << " (";

		for (int i = 0; i < MLQT_Max; i++)
		{
			sstr << gszMarginLeftQtyTableColName[i] << " " << gszMarginLeftQtyTableColType[i];
			if (i < MLQT_Max - 1)
				sstr << ",";
		}
		sstr << ");";

		errCode = phandler->ExecSql(sstr.str().c_str());
		if (errCode != 0)
			LOG4CXX_ERROR(logger, "创建融券剩余数量信息表失败!"LOG_NOVAR(sstr.str().c_str()));

		DBAccess::FreeDBHandler(phandler);
		return errCode == 0;
	}

	bool DBOpTradeCenter::updateMarginLeftTable(const AllTrade::NPTradeCenter::MarginLeftInfoPtr& ptr)
	{
		CDBHandler *phandler = AllocDBHandler();
		if (!phandler)
			return false;

		int errCode = 0;

		std::stringstream sstr;


		sstr << "REPLACE INTO " << gszMarginLeftQtyTableName << " SET "
			<< gszMarginLeftQtyTableColName[MLQT_ContractID] << " = '" << ptr->contract_id_ << "', "
			<< gszMarginLeftQtyTableColName[MLQT_LeftQty] << " = '" << ptr->left_Margin_Qty_ << "'; ";


		errCode = phandler->ExecSql(sstr.str().c_str());

		DBAccess::FreeDBHandler(phandler);
		return errCode == 0;
	}

	bool DBOpTradeCenter::getMarginLeftTable(const AllTrade::NPTradeCenter::MarginLeftInfoPtr& ptr)
	{
		CDBHandler *phandler = AllocDBHandler();
		if (!phandler)
			return false;

		HxSqlRes res = NULL;
		int errCode = 0;
		int recNum = 0;

		std::stringstream sstr;
		sstr << "SELECT * FROM " << gszMarginLeftQtyTableName << " WHERE " << gszMarginLeftQtyTableColName[MLQT_ContractID] 
			<< " =' " << ptr->contract_id_ << "'; ";;

		errCode = phandler->QuerySql(sstr.str().c_str(), res, true);

		if (errCode == 0 && res)
		{
			HxResRow row = NULL;

			while (row = phandler->FetchRow(res))
			{
				char *pchar;

				strncpy_s(ptr->contract_id_, phandler->FetchField(row, MLQT_ContractID), sizeof(ptr->contract_id_) - 1);
				
				pchar = phandler->FetchField(row, MLQT_LeftQty);
				ptr->left_Margin_Qty_ = atoi(pchar);
				
			}
		}

		phandler->ReleaseRecords(res);
		DBAccess::FreeDBHandler(phandler);
		return errCode == 0;
	}

}