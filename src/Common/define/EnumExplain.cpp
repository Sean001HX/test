#include "EnumExplain.h"

#define SimulatedAccount	"ģ���˻�"
#define	RealAccount			"ʵ���˻�"
#define	RealOrSimulated		"ģ��/ʵ���˻�"

using namespace AllTrade;

QString getUserStatusInfo(int errCode)
{
	switch (static_cast<E_ACCOUNT_STATUS>(errCode))
	{
	case EAS_Check_Create:
		return QStringLiteral("�����");
	case EAS_Check_Unpass:
		return QStringLiteral("��˾ܾ�");
	case EAS_OverTime:
		return QStringLiteral("�ѹ���");
	case EAS_Check_Delete:
		return QStringLiteral("ɾ�����������");

	case EAS_Deleted:
		return QStringLiteral(" �˻���ɾ��");
	case EAS_Using:
		return QStringLiteral("ͨ�����");
	case EAS_Warning:
		return QStringLiteral("�쳣����");

	case EAS_StopOpen:
		return QStringLiteral("��ֹ����");
	case EAS_Freezing:
		return QStringLiteral("������");

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
		return QStringLiteral("ָ��ʧ��");
	case OrderStateType::ORDER_STATE_SUPPENDING:
		return QStringLiteral("�ύ��");
	case OrderStateType::ORDER_STATE_SUPPENDED:
		return QStringLiteral("�ѹ���");
	case OrderStateType::ORDER_STATE_QUEUED:
		return QStringLiteral("���Ŷ�");
	case OrderStateType::ORDER_STATE_ACCEPT:
		return QStringLiteral("������");
	case OrderStateType::ORDER_STATE_DELETEING:
		return QStringLiteral("������");
	case OrderStateType::ORDER_STATE_PARTDELETED:
		return QStringLiteral("���ֳ���");
	case OrderStateType::ORDER_STATE_DELETED:
		return QStringLiteral("��ȫ����");
	case OrderStateType::ORDER_STATE_PARTFINISHED:
		return QStringLiteral("���ֳɽ�");
	case OrderStateType::ORDER_STATE_FINISHED:
		return QStringLiteral("��ȫ�ɽ�");
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
		return QStringLiteral("����");
	case DirectType::DIRECT_SELL:
		return QStringLiteral("����");
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
		return QStringLiteral("�޼�");
	case OrderTypeType::ORDER_TYPE_MARKET:
		return QStringLiteral("�м�");
	case OrderTypeType::ORDER_TYPE_STOP_LIMIT:
		return QStringLiteral("�޼�ֹ��");
	case OrderTypeType::ORDER_TYPE_STOP_MARKET:
		return QStringLiteral("�м�ֹ��");
	default:
		break;
	}
	return QStringLiteral("");
}

const QStringList gszApplyMoneyStatusType = {
	QStringLiteral("δ���"),
	QStringLiteral("�ܾ����"),
	QStringLiteral("�����"),
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
		return QStringLiteral("������");
	case RiskControlType::RCT_ForceLine:
		return QStringLiteral("ǿƽ��");
	case RiskControlType::RCT_LimitLine:
		return QStringLiteral("�޲���");

	default:
		break;
	}
	return QStringLiteral("");
}

const QStringList gszMoneyChangeType = {
	QStringLiteral("���Ӻ��ʽ�"),
	QStringLiteral("�������ʽ�"),
	QStringLiteral("�ʽ�����"),
	QStringLiteral("���Ӻ��ʽ�"),

	QStringLiteral("�������ʽ�"),
	QStringLiteral("�ʽ���"),
	QStringLiteral("����ί�ж����ʽ�,�����ʽ����"),
	QStringLiteral("����,�����ʽ𷵻�"),

	QStringLiteral("���ֳɽ�"),
	QStringLiteral("���ֳɽ�����Ӷ��������"),
	QStringLiteral("���ֳɽ�������"),
	QStringLiteral("���ֳɽ���Ϣ��Ϸ�"),

	QStringLiteral("����ȫ���ɽ�"),
	QStringLiteral("ƽ�ֳɽ��ʽ𷵻�"),
	QStringLiteral("ƽ�ֳɽ�����Ӷ��������"),
	QStringLiteral("ƽ�ֳɽ�������"),

	QStringLiteral("ƽ�ֳɽ���Ϣ��Ϸ�"),
	QStringLiteral("ƽ�ֳɽ�ӡ��˰"),
	QStringLiteral("ϵͳ��Ӷ"),
	QStringLiteral("ϵͳ�ʽ����"),
	QStringLiteral("ϵͳ�ֳ�"),
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
	QStringLiteral("��ֹ���׹�Ʊ�����д�S��ST�Ĺ�Ʊ"),
	QStringLiteral("��ֹ���׵�ǰ��ͣ��Ʊ"),
	QStringLiteral("��ֹ���׵�ǰ��ͣ��Ʊ"),
	QStringLiteral("��ֹ��������20���ڵ��¹�"),
};
const QStringList gszForbidTradeType = {
	QStringLiteral("������ҵ��Ʊ"),
	QStringLiteral("��ǰ��ͣ��Ʊ"),
	QStringLiteral("��ǰ��ͣ��Ʊ"),
	QStringLiteral("�¹�(����20��)"),
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
	QStringLiteral("��������"),
	QStringLiteral("ֻ������"),
	QStringLiteral("ֻ������"),
	QStringLiteral("��ֹ����"),
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
	QStringLiteral("ͬһ��Ʊ�ֲ���ֵ���������ʲ��ı���"),
	QStringLiteral("��ҵ��ֲ���ֵ���������ʲ��ı���"),
};

const QStringList gszPosiyionRateType =
{
	QStringLiteral("ͬһ��Ʊ�ֲ���ֵ���������ʲ��ı���"),
	QStringLiteral("��ҵ��ֲ���ֵ���������ʲ��ı���"),
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
	 QStringLiteral("��Ϣ��Ϸ�Ӷ��"),
	 QStringLiteral("������Ӷ��"),
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
