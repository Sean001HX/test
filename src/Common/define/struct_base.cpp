#include "struct_base.h"
#include "params_declare.h"

namespace AllTrade {
    namespace NPMgrCenter {
#pragma region 账户
        SAccountBase::SAccountBase()
        {
            memset(this, 0, sizeof(*this));
            prop_ = E_ACCOUNT_PROP::EAP_Invalid;
            type_ = E_ACCOUNT_TYPE::EAT_Invalid;
            permission_ = E_PERMISSION_TYPE::EPT_Invalid;

            status_ = E_ACCOUNT_STATUS::EAS_Check_Create;
        }

        SOnlineAccount::SOnlineAccount()
        {
            memset(this, 0, sizeof(*this));
        }

#pragma endregion

#pragma region 资金信息
        SMoneyInfo::SMoneyInfo()
        {
            memset(this, 0, sizeof(*this));
        }

        YDouble SMoneyInfo::getAllTradeFee() const
        {
            return trading_fee_ + customize_fee_;
        }

        YDouble SMoneyInfo::getAllCanExtract() const
        {
            if (getCanUse() - logic_wait_thaw_ < 0.0)
                return 0;
            return getCanUse() - logic_wait_thaw_;
        }

        YDouble SMoneyInfo::getCanExtract() const
        {
            if (getAllCanExtract() - priority_fund_ < 0.0)
                return 0;
            return getAllCanExtract() - priority_fund_;
        }

        YDouble SMoneyInfo::getCanUse() const
        {
            return logic_can_extract_ + logic_wait_thaw_ - order_freeze_;
        }

        void SMoneyInfo::addDeposit(YDouble money)
        {
            logic_can_extract_ += money;
            user_deposit_ += money;
        }

        void SMoneyInfo::addEquipment(YDouble money)
        {
            logic_can_extract_ += money;
            priority_fund_ += money;
        }

        void SMoneyInfo::orderFreeze(YDouble money)
        {
            order_freeze_ += money;
        }

        void SMoneyInfo::cancelOrderThaw(YDouble money)
        {
            order_freeze_ -= money;
        }

        void SMoneyInfo::moneySettle()
        {
            logic_can_extract_ += logic_wait_thaw_;
            logic_wait_thaw_ = 0;
        }

        //////////////////////////////////////////////////////////////////////////
        SMoneyDetailInfo::SMoneyDetailInfo()
        {
            memset(this, 0, sizeof(*this));
        }

        SRiskInfo::SRiskInfo()
        {
            memset(this, 0, sizeof(*this));
        }

#pragma endregion

#pragma region 交易所
        Feest::Feest()
            : fee_(0)
            , bFix_(false)
        {

        }

        TimePeriod::TimePeriod()
        {
            memset(this, 0, sizeof(*this));
        }

        SExchange::SExchange()
        {
            memset(this, 0, sizeof(*this));
        }

        SProductInfo::SProductInfo()
        {
            memset(this, 0, sizeof(*this));
            contract_multiplier_ = 1;
        }

        SContractBase::SContractBase()
        {
            memset(this, 0, sizeof(*this));
        }

        SCurrencyInfo::SCurrencyInfo()
            : isBaseCurrency_(false)
        {
            memset(this, 0, sizeof(*this));
        }


        SApplyMoneyInfo::SApplyMoneyInfo()
        {
            memset(this, 0, sizeof(*this));
            apply_status_ = E_APPLY_MONEY_STATUS::EAMS_Invalid;
        }

        SAgencyMoneyDetailInfo::SAgencyMoneyDetailInfo()
        {
            memset(this, 0, sizeof(*this));
            change_type_ = Agency_Money_Change_Type::AMCT_Invalid;
        }

#pragma endregion

		InterestStatistics::InterestStatistics()
		{
			memset(this, 0, sizeof(*this));
		}

		InterestDetail::InterestDetail()
		{
			memset(this, 0, sizeof(*this));
			change_type_ = Agency_Money_Change_Type::AMCT_Invalid;
		}

		}

    namespace NPTradeCenter {
#pragma region 委托
        //////////////////////////////////////////////////////////////////////////
        OrderInfoBase::OrderInfoBase()
        {
            memset(this, 0, sizeof(*this));
            direct_type_ = DirectType::DIRECT_Invalid;
            order_state_ = OrderStateType::ORDER_STATE_Invalid;
            orser_state_explain_ = Invalid_OrderState_Explain;
            order_type_ = OrderTypeType::ORDER_TYPE_Invalid;
            order_trade_mode_ = OrderTradeModeType::ORDERTRADE_MODE_Invalid;
            op_type_ = OperatorTradeType::OPERATOR_TRADE_Invalid;
            order_mode_ = OrderModeType::ORDER_MODE_Invalid;
            api_type_ = ApiTypeType::APIType_TYPE_Invalid;
            commodity_type_ = CommodityTypeType::COMMODITY_TYPE_Invalid;

            b_freeze_money_ = false;
            b_freeze_position_ = false;
        }

        //////////////////////////////////////////////////////////////////////////
        CancelOrderInfo::CancelOrderInfo()
        {
            memset(this, 0, sizeof(*this));
            commodity_type_ = CommodityTypeType::COMMODITY_TYPE_Invalid;
        }
#pragma endregion

#pragma region 成交
        //////////////////////////////////////////////////////////////////////////
        TradeInfoBase::TradeInfoBase()
        {
            memset(this, 0, sizeof(*this));
            direct_type_ = DirectType::DIRECT_Invalid;
            api_type_ = ApiTypeType::APIType_TYPE_Invalid;
            api_type_ = ApiTypeType::APIType_TYPE_Invalid;
            commodity_type_ = CommodityTypeType::COMMODITY_TYPE_Invalid;
            op_type_ = OperatorTradeType::OPERATOR_TRADE_Invalid;
        }

#pragma endregion

#pragma region 持仓
        //////////////////////////////////////////////////////////////////////////
        PositionInfoBase::PositionInfoBase()
        {
            memset(this, 0, sizeof(*this));
            direct_type_ = DirectType::DIRECT_Invalid;
            commodity_type_ = CommodityTypeType::COMMODITY_TYPE_Invalid;
        }

#pragma endregion

        //////////////////////////////////////////////////////////////////////////
        QuoteInfoBase::QuoteInfoBase()
        {
            memset(this, 0, sizeof(*this));
            quote_status_ =  QuoteStatusType::QUOTESTATUS_Invalid;
        }

        TradeFee::TradeFee()
        {
            memset(this, 0, sizeof(*this));
        }

        ImmRiskControlSt::ImmRiskControlSt()
        {
            memset(this, 0, sizeof(*this));
        }

        //////////////////////////////////////////////////////////////////////////
        GlobalData::GlobalData()
        {
            memset(this, 0, sizeof(*this));
        }

        //////////////////////////////////////////////////////////////////////////
        SForbidTradeInfo::SForbidTradeInfo()
        {
            memset(this, 0, sizeof(*this));
            bstart_ = false;
        }

        //////////////////////////////////////////////////////////////////////////
        SPositionRateInfo::SPositionRateInfo()
        {
            memset(this, 0, sizeof(*this));
            bstart_ = false;
        }

		MarginInfo::MarginInfo()
		{
			memset(this, 0, sizeof(*this));
		}

		MarginLeftInfo::MarginLeftInfo()
		{
			memset(this, 0, sizeof(*this));
		}

	}
}