#include "struct_extern.h"

namespace AllTrade {
    namespace NPMgrCenter {
#pragma region 账户
        RootAccount::RootAccount()
            : SAccountBase()
        {
            strncpy_s(login_name_, "super", sizeof(login_name_) - 1);
            strncpy_s(nick_name_, "super", sizeof(nick_name_) - 1);
            strncpy_s(password_, "super", sizeof(password_) - 1);
            strncpy_s(account_name_, "super", sizeof(account_name_) - 1);

            prop_ = E_ACCOUNT_PROP::EAP_Root;
            type_ = E_ACCOUNT_TYPE::EAT_SimuReal;
            permission_ = E_PERMISSION_TYPE::EPT_AUTO;
            status_ = E_ACCOUNT_STATUS::EAS_Using;

            allow_max_level_ = 4;
            allow_max_num_ = 0;
        }

        AgencyAccount::AgencyAccount()
            : SAccountBase()
        {
            memset(fund_user_id_, 0, sizeof(fund_user_id_));
            prop_ = E_ACCOUNT_PROP::EAP_Agency;
            agency_prop_ = E_AGENCY_PROP::EAP_COMMON;

            allow_max_level_ = 0;
            allow_max_num_ = 0;
        }

        RiskAccount::RiskAccount()
            : SAccountBase()
        {
            prop_ = E_ACCOUNT_PROP::EAP_Risker;
        }

        ManagerAccount::ManagerAccount()
            : SAccountBase()
        {
            prop_ = E_ACCOUNT_PROP::EAP_Manager;
            status_ = E_ACCOUNT_STATUS::EAS_Using;
        }

        TradeAccount::TradeAccount()
            : SAccountBase()
        {
            prop_ = E_ACCOUNT_PROP::EAP_Trader;
            type_ = E_ACCOUNT_TYPE::EAT_Invalid;
            permission_ = E_PERMISSION_TYPE::EPT_Invalid;
            status_ = E_ACCOUNT_STATUS::EAS_Check_Create;

            memset(fund_user_id_, 0, sizeof(fund_user_id_));
        }

        FunderAccount::FunderAccount()
            : SAccountBase()
        {
            prop_ = E_ACCOUNT_PROP::EAP_Funder;
            type_ = E_ACCOUNT_TYPE::EAT_Real;
            status_ = E_ACCOUNT_STATUS::EAS_Using;
        }

#pragma endregion

#pragma region 交易所

        //////////////////////////////////////////////////////////////////////////
        SStockContract::SStockContract()
            : SContractBase()
        {
            memset(display_prop_, 0, sizeof(display_prop_));
            memset(plate_prop_, 0, sizeof(plate_prop_));
            stock_area_ = StockAreaType::STOCKAREA_TYPE_Invalid;
            display_prop_type_ = DisplayPropTypeType::DPTT_Invalid;
            stock_plate_area_ = StockPlateAreaType::SPAT_Invalid;
            total_shares_ = 0;
        }

        SForeignFutureContract::SForeignFutureContract()
            : SContractBase()
        {
            strncpy_s(product_id_, 0, sizeof(product_id_) - 1);
        }

#pragma endregion
}

    namespace NPTradeCenter {
#pragma region 委托
        //////////////////////////////////////////////////////////////////////////
        StockOrderInfo::StockOrderInfo()
            : OrderInfoBase()
        {
            stock_area_ = StockAreaType::STOCKAREA_TYPE_Invalid;
        }

        //////////////////////////////////////////////////////////////////////////
        ForeignFutureOrderInfo::ForeignFutureOrderInfo()
            : OrderInfoBase()
        {
            memset(product_id_, 0, sizeof(product_id_));
        }

        //////////////////////////////////////////////////////////////////////////
        ChinaFutureOrderInfo::ChinaFutureOrderInfo()
            : OrderInfoBase()
            , offset_type_(OffsetType::OFFSET_Invalid)
        {
            memset(product_id_, 0, sizeof(product_id_));
        }
#pragma endregion

#pragma region 成交
        //////////////////////////////////////////////////////////////////////////
        StockTradeInfo::StockTradeInfo()
            : TradeInfoBase()
        {
            stock_area_ = StockAreaType::STOCKAREA_TYPE_Invalid;
        }

        ForeignFutureTradeInfo::ForeignFutureTradeInfo()
            : TradeInfoBase()
        {
            memset(product_id_, 0, sizeof(product_id_));
        }

        ChinaFutureTradeInfo::ChinaFutureTradeInfo()
            : TradeInfoBase()
            , offset_type_(OffsetType::OFFSET_Invalid)
        {
            memset(product_id_, 0, sizeof(product_id_));
        }

#pragma endregion

#pragma region 持仓
        //////////////////////////////////////////////////////////////////////////
        StockPositionInfo::StockPositionInfo()
            : PositionInfoBase()
        {
            stock_area_ = StockAreaType::STOCKAREA_TYPE_Invalid;
        }

        ForeignFuturePositionInfo::ForeignFuturePositionInfo()
            : PositionInfoBase()
        {
            memset(product_id_, 0, sizeof(product_id_));
        }

        ChinaFuturePositionInfo::ChinaFuturePositionInfo()
            : PositionInfoBase()
            , offset_type_(OffsetType::OFFSET_Invalid)
        {
            memset(product_id_, 0, sizeof(product_id_));
        }

#pragma endregion

		MarginPositionInfo::MarginPositionInfo()
			: PositionInfoBase()
		{
			memset(this, 0, sizeof(*this));
		}

		MarginTradeInfo::MarginTradeInfo()
		{
			stock_area_ = StockAreaType::STOCKAREA_TYPE_Invalid;
		}

		MarginOrderInfo::MarginOrderInfo()
		{
			stock_area_ = StockAreaType::STOCKAREA_TYPE_Invalid;
		}

	}
}
