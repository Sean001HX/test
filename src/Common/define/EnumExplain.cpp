#include "EnumExplain.h"

#define SimulatedAccount	"模拟账户"
#define	RealAccount			"实盘账户"
#define	RealOrSimulated		"模拟/实盘账户"

using namespace AllTrade;

QString getUserStatusInfo(int errCode)
{
	switch (static_cast<E_ACCOUNT_STATUS>(errCode))
	{
	case EAS_Check_Create:
		return QStringLiteral("审核中");
	case EAS_Check_Unpass:
		return QStringLiteral("审核拒绝");
	case EAS_OverTime:
		return QStringLiteral("已过期");
	case EAS_Check_Delete:
		return QStringLiteral("删除申请审核中");

	case EAS_Deleted:
		return QStringLiteral(" 账户已删除");
	case EAS_Using:
		return QStringLiteral("通过审核");
	case EAS_Warning:
		return QStringLiteral("异常警告");

	case EAS_StopOpen:
		return QStringLiteral("禁止开仓");
	case EAS_Freezing:
		return QStringLiteral("冻结中");

	default:
		break;
	}

	return QStringLiteral("");
}

QString getAccountTypeInfo(int errCode)
{
	switch (static_cast<E_ACCOUNT_TYPE>(errCode))
	{
	case EAT_Simulation:
		return QStringLiteral(SimulatedAccount);
	case EAT_Real:
		return QStringLiteral(RealAccount);
	case EAT_SimuReal:
		return QStringLiteral(RealOrSimulated);

	default:
		break;
	}

	return QStringLiteral("");
}

QString getOrdrStatusInfo(int type)
{
	switch (static_cast<OrderStateType>(type))
	{
	case OrderStateType::ORDER_STATE_FAIL:
		return QStringLiteral("指令失败");
	case OrderStateType::ORDER_STATE_SUPPENDING:
		return QStringLiteral("提交中");
	case OrderStateType::ORDER_STATE_SUPPENDED:
		return QStringLiteral("已挂起");
	case OrderStateType::ORDER_STATE_QUEUED:
		return QStringLiteral("已排队");
	case OrderStateType::ORDER_STATE_ACCEPT:
		return QStringLiteral("已受理");
	case OrderStateType::ORDER_STATE_DELETEING:
		return QStringLiteral("待撤消");
	case OrderStateType::ORDER_STATE_PARTDELETED:
		return QStringLiteral("部分撤单");
	case OrderStateType::ORDER_STATE_DELETED:
		return QStringLiteral("完全撤单");
	case OrderStateType::ORDER_STATE_PARTFINISHED:
		return QStringLiteral("部分成交");
	case OrderStateType::ORDER_STATE_FINISHED:
		return QStringLiteral("完全成交");
	default:
		break;
	}

	return QStringLiteral("");
}

QString getDerctionType(int type)
{
	switch (static_cast<DirectType>(type))
	{
	case DirectType::DIRECT_BUY:
		return QStringLiteral("买入");
	case DirectType::DIRECT_SELL:
		return QStringLiteral("卖出");
	default:
		break;
	}
	return QStringLiteral("");
}

QString getOrderType(int type)
{
	switch (static_cast<OrderTypeType>(type))
	{
	case OrderTypeType::ORDER_TYPE_LIMIT:
		return QStringLiteral("限价");
	case OrderTypeType::ORDER_TYPE_MARKET:
		return QStringLiteral("市价");
	case OrderTypeType::ORDER_TYPE_STOP_LIMIT:
		return QStringLiteral("限价止损");
	case OrderTypeType::ORDER_TYPE_STOP_MARKET:
		return QStringLiteral("市价止损");
	default:
		break;
	}
	return QStringLiteral("");
}

const QStringList gszApplyMoneyStatusType = {
	QStringLiteral("未审核"),
	QStringLiteral("拒绝审核"),
	QStringLiteral("已审核"),
};

QString getApplyMoneyStatusType(int type)
{
	switch (static_cast<E_APPLY_MONEY_STATUS>(type))
	{
	case E_APPLY_MONEY_STATUS::EAMS_Check_Create:
		return gszApplyMoneyStatusType[EAMS_Check_Create];
	case E_APPLY_MONEY_STATUS::EAMS_Check_Unpass:
		return gszApplyMoneyStatusType[EAMS_Check_Unpass];
	case E_APPLY_MONEY_STATUS::EAMS_Using:
		return gszApplyMoneyStatusType[EAMS_Using];

	default:
		break;
	}
	return QStringLiteral("");
}

AllTrade::E_APPLY_MONEY_STATUS getApplyMoneyStatusType(const QString& str)
{
	E_APPLY_MONEY_STATUS type_;

	if (str == gszApplyMoneyStatusType[EAMS_Check_Create])
		type_ = E_APPLY_MONEY_STATUS::EAMS_Check_Create;
	else if (str == gszApplyMoneyStatusType[EAMS_Check_Unpass])
		type_ = E_APPLY_MONEY_STATUS::EAMS_Check_Unpass;
	else if (str == gszApplyMoneyStatusType[EAMS_Using])
		type_ = E_APPLY_MONEY_STATUS::EAMS_Using;

	return type_;
}

QString getRiskControlType(int type)
{
	switch (static_cast<RiskControlType>(type))
	{
	case RiskControlType::RCT_WarningLine:
		return QStringLiteral("警告线");
	case RiskControlType::RCT_ForceLine:
		return QStringLiteral("强平线");
	case RiskControlType::RCT_LimitLine:
		return QStringLiteral("限仓线");

	default:
		break;
	}
	return QStringLiteral("");
}

const QStringList gszMoneyChangeType = {
	QStringLiteral("加劣后资金"),
	QStringLiteral("加优先资金"),
	QStringLiteral("资金蓝补"),
	QStringLiteral("扣劣后资金"),

	QStringLiteral("扣优先资金"),
	QStringLiteral("资金红冲"),
	QStringLiteral("开仓委托冻结资金,可用资金减少"),
	QStringLiteral("撤单,冻结资金返还"),

	QStringLiteral("开仓成交"),
	QStringLiteral("开仓成交交易佣金手续费"),
	QStringLiteral("开仓成交过户费"),
	QStringLiteral("开仓成交信息撮合费"),

	QStringLiteral("开仓全部成交"),
	QStringLiteral("平仓成交资金返还"),
	QStringLiteral("平仓成交交易佣金手续费"),
	QStringLiteral("平仓成交过户费"),

	QStringLiteral("平仓成交信息撮合费"),
	QStringLiteral("平仓成交印花税"),
	QStringLiteral("系统返佣"),
	QStringLiteral("系统资金结算"),
	QStringLiteral("系统分成"),
};

QString getMoneyChangeType(int type)
{
	switch (static_cast<Money_Change_Type>(type))
	{
	case Money_Change_Type::MC_In_Deposit:
		return gszMoneyChangeType[MC_In_Deposit];
	case Money_Change_Type::MC_In_Equipment:
		return gszMoneyChangeType[MC_In_Equipment];
	case Money_Change_Type::MC_In_BlueAdd:
		return gszMoneyChangeType[MC_In_BlueAdd];

	case Money_Change_Type::MC_Out_Deposit:
		return gszMoneyChangeType[MC_Out_Deposit];
	case Money_Change_Type::MC_Out_Equipment:
		return gszMoneyChangeType[MC_Out_Equipment];
	case Money_Change_Type::MC_Out_RedSub:
		return gszMoneyChangeType[MC_Out_RedSub];

	case Money_Change_Type::MC_Order_Freeze:
		return gszMoneyChangeType[MC_Order_Freeze];
	case Money_Change_Type::MC_Order_Cancel:
		return gszMoneyChangeType[MC_Order_Cancel];
	case Money_Change_Type::MC_Trade_Open:
		return gszMoneyChangeType[MC_Trade_Open];

	case Money_Change_Type::MC_Trade_Open_Fee:
		return gszMoneyChangeType[MC_Trade_Open_Fee];
	case Money_Change_Type::MC_Trade_Open_TransferFee:
		return gszMoneyChangeType[MC_Trade_Open_TransferFee];
	case Money_Change_Type::MC_Trade_Open_InfoMatchFee:
		return gszMoneyChangeType[MC_Trade_Open_InfoMatchFee];

	case Money_Change_Type::MC_Trade_Thaw:
		return gszMoneyChangeType[MC_Trade_Thaw];
	case Money_Change_Type::MC_Trade_Close:
		return gszMoneyChangeType[MC_Trade_Close];
	case Money_Change_Type::MC_Trade_Close_Fee:
		return gszMoneyChangeType[MC_Trade_Close_Fee];

	case Money_Change_Type::MC_Trade_Close_TransferFee:
		return gszMoneyChangeType[MC_Trade_Close_TransferFee];
	case Money_Change_Type::MC_Trade_Close_InfoMatchFee:
		return gszMoneyChangeType[MC_Trade_Close_InfoMatchFee];
	case Money_Change_Type::MC_Trade_Close_StampFee:
		return gszMoneyChangeType[MC_Trade_Close_StampFee];

	case Money_Change_Type::MC_Commission:
		return gszMoneyChangeType[MC_Commission];
	case Money_Change_Type::MC_Money_Settle:
		return gszMoneyChangeType[MC_Money_Settle]; 
	case Money_Change_Type::MC_Profit:
		return gszMoneyChangeType[MC_Profit];

	default:
		break;
	}
	return QStringLiteral("");
}

extern AllTrade::Money_Change_Type getMoneyChangeType(const QString& str)
{
	Money_Change_Type type_;
	if (str == gszMoneyChangeType[MC_In_Deposit])
		type_ = MC_In_Deposit;
	else if (str == gszMoneyChangeType[MC_In_Equipment])
		type_ = MC_In_Equipment;
	else if (str == gszMoneyChangeType[MC_In_BlueAdd])
		type_ = MC_In_BlueAdd;
	else if (str == gszMoneyChangeType[MC_Out_Deposit])
		type_ = MC_Out_Deposit;
	else if (str == gszMoneyChangeType[MC_Out_Equipment])
		type_ = MC_Out_Equipment;

	else if (str == gszMoneyChangeType[MC_Out_RedSub])
		type_ = MC_Out_RedSub;
	else if (str == gszMoneyChangeType[MC_Order_Freeze])
		type_ = MC_Order_Freeze;
	else if (str == gszMoneyChangeType[MC_Order_Cancel])
		type_ = MC_Order_Cancel;
	else if (str == gszMoneyChangeType[MC_Trade_Open])
		type_ = MC_Trade_Open;

	else if (str == gszMoneyChangeType[MC_Trade_Open_Fee])
		type_ = MC_Trade_Open_Fee;
	else if (str == gszMoneyChangeType[MC_Trade_Open_TransferFee])
		type_ = MC_Trade_Open_TransferFee;
	else if (str == gszMoneyChangeType[MC_Trade_Open_InfoMatchFee])
		type_ = MC_Trade_Open_InfoMatchFee;
	else if (str == gszMoneyChangeType[MC_Trade_Thaw])
		type_ = MC_Trade_Thaw;

	else if (str == gszMoneyChangeType[MC_Trade_Close])
		type_ = MC_Trade_Close;
	else if (str == gszMoneyChangeType[MC_Trade_Close_Fee])
		type_ = MC_Trade_Close_Fee;
	else if (str == gszMoneyChangeType[MC_Trade_Close_TransferFee])
		type_ = MC_Trade_Close_TransferFee;
	else if (str == gszMoneyChangeType[MC_Trade_Close_InfoMatchFee])
		type_ = MC_Trade_Close_InfoMatchFee;

	else if (str == gszMoneyChangeType[MC_Trade_Close_StampFee])
		type_ = MC_Trade_Close_StampFee;
	else if (str == gszMoneyChangeType[MC_Commission])
		type_ = MC_Commission;
	else if (str == gszMoneyChangeType[MC_Money_Settle])
		type_ = MC_Money_Settle;
	else if (str == gszMoneyChangeType[MC_Profit])
		type_ = MC_Profit;

	return type_;
}


const QStringList gszForbidTradeTypeStatus
{
	QStringLiteral("禁止交易股票名称中带S或ST的股票"),
	QStringLiteral("禁止交易当前涨停股票"),
	QStringLiteral("禁止交易当前跌停股票"),
	QStringLiteral("禁止交易上市20天内的新股"),
};
const QStringList gszForbidTradeType = {
	QStringLiteral("亏损企业股票"),
	QStringLiteral("当前涨停股票"),
	QStringLiteral("当前跌停股票"),
	QStringLiteral("新股(上市20天)"),
};

QString getForbidTradeType(int type)
{
	switch (static_cast<ForbidTradeType>(type))
	{
	case ForbidTradeType::FTT_LossCorporateStock:
		return gszForbidTradeType[ForbidTradeType::FTT_LossCorporateStock];
	case ForbidTradeType::FTT_RiseStopStock:
		return gszForbidTradeType[ForbidTradeType::FTT_RiseStopStock];
	case ForbidTradeType::FTT_FallStopStock:
		return gszForbidTradeType[ForbidTradeType::FTT_FallStopStock];
	case ForbidTradeType::FTT_NewStock:
		return gszForbidTradeType[ForbidTradeType::FTT_NewStock];

	default:
		break;
	}
	return QStringLiteral("");
}

AllTrade::ForbidTradeType getForbidTradeType(const QString& str)
{
	ForbidTradeType type_;
	if (str == gszForbidTradeType[ForbidTradeType::FTT_LossCorporateStock])
	{
		type_ = ForbidTradeType::FTT_LossCorporateStock;
	}
	else if (str == gszForbidTradeType[ForbidTradeType::FTT_RiseStopStock])
	{
		type_ = ForbidTradeType::FTT_RiseStopStock;
	}
	else if (str == gszForbidTradeType[ForbidTradeType::FTT_FallStopStock])
	{
		type_ = ForbidTradeType::FTT_FallStopStock;
	}
	else if (str == gszForbidTradeType[ForbidTradeType::FTT_NewStock])
	{
		type_ = ForbidTradeType::FTT_NewStock;
	}

	return type_;
}

const QStringList gszForbidTradeOperatorType = {
	QStringLiteral("允许买卖"),
	QStringLiteral("只许买入"),
	QStringLiteral("只许卖出"),
	QStringLiteral("禁止买卖"),
};

QString getForbidTradeOperatorType(int type)
{
	switch (static_cast<ForbidTradeOperatorType>(type))
	{
	case ForbidTradeOperatorType::FTOT_AllowTrade:
		return gszForbidTradeOperatorType[(int)ForbidTradeOperatorType::FTOT_AllowTrade];
	case ForbidTradeOperatorType::FTOT_AllowBuy:
		return gszForbidTradeOperatorType[(int)ForbidTradeOperatorType::FTOT_AllowBuy];
	case ForbidTradeOperatorType::FTOT_AllowSell:
		return gszForbidTradeOperatorType[(int)ForbidTradeOperatorType::FTOT_AllowSell];
	case ForbidTradeOperatorType::FTOT_ForbidTrade:
		return gszForbidTradeOperatorType[(int)ForbidTradeOperatorType::FTOT_ForbidTrade];

	default:
		break;
	}
	return QStringLiteral("");
}

AllTrade::ForbidTradeOperatorType getForbidTradeOperatorType(const QString& str)
{
	ForbidTradeOperatorType type_;
	if (str == gszForbidTradeOperatorType[(int)ForbidTradeOperatorType::FTOT_AllowTrade])
	{
		type_ = ForbidTradeOperatorType::FTOT_AllowTrade;
	}
	else if (str == gszForbidTradeOperatorType[(int)ForbidTradeOperatorType::FTOT_AllowBuy])
	{
		type_ = ForbidTradeOperatorType::FTOT_AllowBuy;
	}
	else if (str == gszForbidTradeOperatorType[(int)ForbidTradeOperatorType::FTOT_AllowSell])
	{
		type_ = ForbidTradeOperatorType::FTOT_AllowSell;
	}
	else if (str == gszForbidTradeOperatorType[(int)ForbidTradeOperatorType::FTOT_ForbidTrade])
	{
		type_ = ForbidTradeOperatorType::FTOT_ForbidTrade;
	}

	return type_;
}

const QStringList gszPosiyionRateTypeStatus =
{
	QStringLiteral("同一股票持仓市值不超过总资产的比例"),
	QStringLiteral("创业板持仓市值不超过总资产的比例"),
};

const QStringList gszPosiyionRateType =
{
	QStringLiteral("同一股票持仓市值不超过总资产的比例"),
	QStringLiteral("创业板持仓市值不超过总资产的比例"),
};

 QString getPosiyiomRateType(int type)
{
	switch (static_cast<PositionRateType>(type))
	{
	case PositionRateType::PRT_SameStock:
		return gszPosiyionRateType[(int)PositionRateType::PRT_SameStock];
	case PositionRateType::PRT_Second_Board:
		return gszPosiyionRateType[(int)PositionRateType::PRT_Second_Board];
	
	default:
		break;
	}
	return QStringLiteral("");
}

 AllTrade::PositionRateType getPosiyiomRateType(const QString& str)
{
	PositionRateType type_;
	if (str == gszPosiyionRateType[(int)PositionRateType::PRT_SameStock])
	{
		type_ = PositionRateType::PRT_SameStock;
	}

	if (str == gszPosiyionRateType[(int)PositionRateType::PRT_Second_Board])
	{
		type_ = PositionRateType::PRT_Second_Board;
	}
	
	return type_;
}


 const QStringList gszAgencyMoneyChangeType =
 {
	 QStringLiteral("信息撮合费佣金"),
	 QStringLiteral("手续费佣金"),
 };

 QString getAgencyMoneyChangeType(int type)
 {
	 switch (static_cast<Agency_Money_Change_Type>(type))
	 {
	 case Agency_Money_Change_Type::AMCT_InfoMatch_Commission:
		 return gszAgencyMoneyChangeType[(int)Agency_Money_Change_Type::AMCT_InfoMatch_Commission];
	 case Agency_Money_Change_Type::AMCT_Exchange_Commission:
		 return gszAgencyMoneyChangeType[(int)Agency_Money_Change_Type::AMCT_Exchange_Commission];

	 default:
		 break;
	 }
	 return QStringLiteral("");
 }
