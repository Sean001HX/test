#pragma once
#include <QStringList>
#include "params_declare.h"

extern QString getUserStatusInfo(int errCode);

extern QString getAccountTypeInfo(int errCode);
extern QString getOrdrStatusInfo(int type);

extern QString getDerctionType(int type);
extern QString getOrderType(int type);

////////////////////////begin///////////////////////////
extern const QStringList gszApplyMoneyStatusType;

extern QString getApplyMoneyStatusType(int type);

extern AllTrade::E_APPLY_MONEY_STATUS getApplyMoneyStatusType(const QString& str);
/////////////////////////end /////////////////////

extern QString getRiskControlType(int type);

///////////////////////////////begin////////////////////////////////////////
extern const QStringList gszMoneyChangeType;

extern QString getMoneyChangeType(int type);

extern AllTrade::Money_Change_Type getMoneyChangeType(const QString& str);
///////////////////////////////////end////////////////////////////////////


///////////////////////////////begin////////////////////////////////////////
extern const QStringList gszForbidTradeTypeStatus;

extern const QStringList gszForbidTradeType;

extern QString getForbidTradeType(int type);

extern AllTrade::ForbidTradeType getForbidTradeType(const QString& str);
///////////////////////////////////end////////////////////////////////////


/////////////////////////////////////begin//////////////////////////////////
extern const QStringList gszForbidTradeOperatorType;

extern QString getForbidTradeOperatorType(int type);

extern AllTrade::ForbidTradeOperatorType getForbidTradeOperatorType(const QString& str);
//////////////////////////////////////end/////////////////////////////////



//////////////////////////////////////begin/////////////////////////////////
extern const QStringList gszPosiyionRateTypeStatus;
extern const QStringList gszPosiyionRateType;

extern QString getPosiyiomRateType(int type);

extern AllTrade::PositionRateType getPosiyiomRateType(const QString& str);
////////////////////////////////////////end ///////////////////////////////


extern const QStringList gszAgencyMoneyChangeType;
extern QString getAgencyMoneyChangeType(int type);