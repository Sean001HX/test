#include <codecvt>
#include <assert.h>
#include "CommMessage.h"
#include "define/CommMsgDefine.h"
#include "commmsg_declare.h"
#include "define/net_illustrate.h"

using namespace xyc_communication;
using namespace AllTrade;

// static member of CommMsgBase
TypeToMsgMap				        CommMsgBase::_sTypeToMsg;		// 消息类型到消息创建函数的映射
CmdTypeMap					        CommMsgBase::_sCmdTypeMap;	    // 命令码<-->命令类型

//////////////////////////////////////////////////////////////////////////
// CommMsgBase class
CommMsgBase::CommMsgBase()
    : request_(nullptr)
    , type_(EMPT_Init_Null)
{
}

CommMsgBase::CommMsgBase(E_COMM_MSG_TYPE type)
    : request_(nullptr)
    , type_(type)
{

}

CommMsgBase::CommMsgBase(RequestPtr request)
    : request_(request)
{
    assert(request);
    type_ = CommMsgBase::getTypeFromCmd(request->command_);
    assert(type_ > EMPT_Init_Null && type_ < EMPT_Max_Count);
}

CommMsgBase::CommMsgBase(E_COMM_MSG_TYPE type, RequestPtr request)
    : request_(request)
    , type_(type)
{
    assert( request );
    assert(CommMsgBase::getTypeFromCmd(request->command_) == type);
}

CommMsgBase::~CommMsgBase()
{
    try
    {
        if ( request_ && request_.unique() )
        {
            request_->clear();
        }
    }
    catch(...) {}
}

bool CommMsgBase::initialize()
{
    if (CommMsgBase::_sTypeToMsg.size() != 0)
        return false;

    // 消息类型到消息创建函数的映射
    bool bRet = CommMsgBase::_sTypeToMsg.insert(TTMMValueType(LOGIN_TRADE_REQ, reinterpret_cast<CommMsgLoginPtr(*)(RequestPtr)>(CommMsgLogin::createFromReq))).second != 0;
    bRet &= CommMsgBase::_sTypeToMsg.insert(TTMMValueType(LOGIN_OUT_REQ, reinterpret_cast<CommMsgLogoutPtr(*)(RequestPtr)>(CommMsgLogout::createFromReq))).second != 0;
    bRet &= CommMsgBase::_sTypeToMsg.insert(TTMMValueType(HEART_BEAT_MSG, reinterpret_cast<CommMsgHeartBeatPtr(*)(RequestPtr)>(CommMsgHeartBeat::createFromReq))).second != 0;
    bRet &= CommMsgBase::_sTypeToMsg.insert(TTMMValueType(INSTITUTION_REQ, reinterpret_cast<CommMsgAgencyQryPtr(*)(RequestPtr)>(CommMsgAgencyQry::createFromReq))).second != 0;
    bRet &= CommMsgBase::_sTypeToMsg.insert(TTMMValueType(INSTITUTION_PREAPPROVAL_REQ, reinterpret_cast<CommMsgAgencyPreApprovalQryPtr(*)(RequestPtr)>(CommMsgAgencyPreApprovalQry::createFromReq))).second != 0;
    bRet &= CommMsgBase::_sTypeToMsg.insert(TTMMValueType(INSTITUTION_LINK_REQ, reinterpret_cast<CommMsgAgencyLinkQryPtr(*)(RequestPtr)>(CommMsgAgencyLinkQry::createFromReq))).second != 0;
    bRet &= CommMsgBase::_sTypeToMsg.insert(TTMMValueType(ROLES_QUERY_REQ, reinterpret_cast<CommMsgRolesQryPtr(*)(RequestPtr)>(CommMsgRolesQry::createFromReq))).second != 0;
    bRet &= CommMsgBase::_sTypeToMsg.insert(TTMMValueType(INSTITUTIONUSER_ROLE_RELATION_REQ, reinterpret_cast<CommMsgAgencyRolesQryPtr(*)(RequestPtr)>(CommMsgAgencyRolesQry::createFromReq))).second != 0;
    bRet &= CommMsgBase::_sTypeToMsg.insert(TTMMValueType(COMMISSION_QUERY_REQ, reinterpret_cast<CommMsgCommissQryPtr(*)(RequestPtr)>(CommMsgCommissQry::createFromReq))).second != 0;
    bRet &= CommMsgBase::_sTypeToMsg.insert(TTMMValueType(COMMISSION_DETAIL_REQ, reinterpret_cast<CommMsgCommissDtlQryPtr(*)(RequestPtr)>(CommMsgCommissDtlQry::createFromReq))).second != 0;
    bRet &= CommMsgBase::_sTypeToMsg.insert(TTMMValueType(PROFITCOMMISSION_QUERY_REQ, reinterpret_cast<CommMsgProfitCommisslQryPtr(*)(RequestPtr)>(CommMsgProfitCommisslQry::createFromReq))).second != 0;
    bRet &= CommMsgBase::_sTypeToMsg.insert(TTMMValueType(PROFITCOMMISSION_DETAIL_REQ, reinterpret_cast<CommMsgProfitCommissDtlQryPtr(*)(RequestPtr)>(CommMsgProfitCommissDtlQry::createFromReq))).second != 0;
    bRet &= CommMsgBase::_sTypeToMsg.insert(TTMMValueType(TOPOLOGICAL_TREE_REQ, reinterpret_cast<CommMsgToplogicalTreeQryPtr(*)(RequestPtr)>(CommMsgToplogicalTreeQry::createFromReq))).second != 0;
    bRet &= CommMsgBase::_sTypeToMsg.insert(TTMMValueType(CHILD_QUERY_REQ, reinterpret_cast<CommMsgChildAccQryPtr(*)(RequestPtr)>(CommMsgChildAccQry::createFromReq))).second != 0;
    bRet &= CommMsgBase::_sTypeToMsg.insert(TTMMValueType(CHILD_APPROVAL_REQ, reinterpret_cast<CommMsgChildApprovalQryPtr(*)(RequestPtr)>(CommMsgChildApprovalQry::createFromReq))).second != 0;
    bRet &= CommMsgBase::_sTypeToMsg.insert(TTMMValueType(FUNDACC_QUERY_REQ, reinterpret_cast<CommMsgFundAccQryPtr(*)(RequestPtr)>(CommMsgFundAccQry::createFromReq))).second != 0;
    bRet &= CommMsgBase::_sTypeToMsg.insert(TTMMValueType(ONLINE_USER_REQ, reinterpret_cast<CommMsgOnlineAccQryPtr(*)(RequestPtr)>(CommMsgOnlineAccQry::createFromReq))).second != 0;
    bRet &= CommMsgBase::_sTypeToMsg.insert(TTMMValueType(STOCK_CONTRACT_QUERY_REQ, reinterpret_cast<CommMsgStockContractQryPtr(*)(RequestPtr)>(CommMsgStockContractQry::createFromReq))).second != 0;
    bRet &= CommMsgBase::_sTypeToMsg.insert(TTMMValueType(STOCK_INSTRUMENT_QUERY_REQ, reinterpret_cast<CommMsgStockBlackQryPtr(*)(RequestPtr)>(CommMsgStockBlackQry::createFromReq))).second != 0;
    bRet &= CommMsgBase::_sTypeToMsg.insert(TTMMValueType(FORBID_BUY_SELL_QUERY_REQ, reinterpret_cast<CommMsgForbidBuySellQryPtr(*)(RequestPtr)>(CommMsgForbidBuySellQry::createFromReq))).second != 0;
    bRet &= CommMsgBase::_sTypeToMsg.insert(TTMMValueType(POSI_RATE_QUERY_REQ, reinterpret_cast<CommMsgPosiRateQryPtr(*)(RequestPtr)>(CommMsgPosiRateQry::createFromReq))).second != 0;
    bRet &= CommMsgBase::_sTypeToMsg.insert(TTMMValueType(POSI_QUERY_REQ, reinterpret_cast<CommMsgPosiQryPtr(*)(RequestPtr)>(CommMsgPosiQry::createFromReq))).second != 0;
    bRet &= CommMsgBase::_sTypeToMsg.insert(TTMMValueType(CURRENTENTRUST_QUERY_REQ, reinterpret_cast<CommMsgCurrentyEntrustQryPtr(*)(RequestPtr)>(CommMsgCurrentyEntrustQry::createFromReq))).second != 0;
    bRet &= CommMsgBase::_sTypeToMsg.insert(TTMMValueType(TODAYENTRUST_QUERY_REQ, reinterpret_cast<CommMsgTodayEntrustQryPtr(*)(RequestPtr)>(CommMsgTodayEntrustQry::createFromReq))).second != 0;
    bRet &= CommMsgBase::_sTypeToMsg.insert(TTMMValueType(HISTORYENTRUST_QUERY_REQ, reinterpret_cast<CommMsgHistoryEntrustQryPtr(*)(RequestPtr)>(CommMsgHistoryEntrustQry::createFromReq))).second != 0;
    bRet &= CommMsgBase::_sTypeToMsg.insert(TTMMValueType(TRADE_QUERY_REQ, reinterpret_cast<CommMsgTradeQryPtr(*)(RequestPtr)>(CommMsgTradeQry::createFromReq))).second != 0;
    bRet &= CommMsgBase::_sTypeToMsg.insert(TTMMValueType(HISTORYTRADE_QUERY_REQ, reinterpret_cast<CommMsgHistoryTradeQryPtr(*)(RequestPtr)>(CommMsgHistoryTradeQry::createFromReq))).second != 0;
    bRet &= CommMsgBase::_sTypeToMsg.insert(TTMMValueType(FUND_QUERY_REQ, reinterpret_cast<CommMsgFundQryPtr(*)(RequestPtr)>(CommMsgFundQry::createFromReq))).second != 0;
    bRet &= CommMsgBase::_sTypeToMsg.insert(TTMMValueType(FUND_SERIAL_QUERY_REQ, reinterpret_cast<CommMsgFundSerialQryPtr(*)(RequestPtr)>(CommMsgFundSerialQry::createFromReq))).second != 0;
    bRet &= CommMsgBase::_sTypeToMsg.insert(TTMMValueType(DELIVERY_QUERY_REQ, reinterpret_cast<CommMsgDeliveryQryPtr(*)(RequestPtr)>(CommMsgDeliveryQry::createFromReq))).second != 0;
    bRet &= CommMsgBase::_sTypeToMsg.insert(TTMMValueType(CHILD_FUNDMONITIOR_QUERY_REQ, reinterpret_cast<CommMsgFundMonitQryPtr(*)(RequestPtr)>(CommMsgFundMonitQry::createFromReq))).second != 0;
//     bRet &= CommMsgBase::_sTypeToMsg.insert(TTMMValueType(CHILD_TIMETRADE_QUERY_REQ, reinterpret_cast<CommMsgTimeTradeQryPtr(*)(RequestPtr)>(CommMsgTimeTradeQry::createFromReq))).second != 0;
    bRet &= CommMsgBase::_sTypeToMsg.insert(TTMMValueType(CHILD_SUMPOSITION_QUERY_REQ, reinterpret_cast<CommMsgSumPosiQryPtr(*)(RequestPtr)>(CommMsgSumPosiQry::createFromReq))).second != 0;
    bRet &= CommMsgBase::_sTypeToMsg.insert(TTMMValueType(CHILD_TIMEWARN_NOTIFY_QUERY_REQ, reinterpret_cast<CommMsgTimeWarnQryPtr(*)(RequestPtr)>(CommMsgTimeWarnQry::createFromReq))).second != 0;
    bRet &= CommMsgBase::_sTypeToMsg.insert(TTMMValueType(CHILD_EQUIPMENTMONEY_QUERY_REQ, reinterpret_cast<CommMsgEquipMoneyQryPtr(*)(RequestPtr)>(CommMsgEquipMoneyQry::createFromReq))).second != 0;
    bRet &= CommMsgBase::_sTypeToMsg.insert(TTMMValueType(CHILD_AUTOOUTMONEY_QUERY_REQ, reinterpret_cast<CommMsgAutoOutMoneyQryPtr(*)(RequestPtr)>(CommMsgAutoOutMoneyQry::createFromReq))).second != 0;
    bRet &= CommMsgBase::_sTypeToMsg.insert(TTMMValueType(FEE_MANAGER_QUERY_REQ, reinterpret_cast<CommMsgFeeSetQryPtr(*)(RequestPtr)>(CommMsgFeeSetQry::createFromReq))).second != 0;
    bRet &= CommMsgBase::_sTypeToMsg.insert(TTMMValueType(MANAGER_QUERY_REQ, reinterpret_cast<CommMsgManagerQryPtr(*)(RequestPtr)>(CommMsgManagerQry::createFromReq))).second != 0;
    bRet &= CommMsgBase::_sTypeToMsg.insert(TTMMValueType(INSTITUTION_ADD_REQ, reinterpret_cast<CommMsgAgencyAddPtr(*)(RequestPtr)>(CommMsgAgencyAdd::createFromReq))).second != 0;
    bRet &= CommMsgBase::_sTypeToMsg.insert(TTMMValueType(INSTITUTION_CHANGE_REQ, reinterpret_cast<CommMsgAgencyChangePtr(*)(RequestPtr)>(CommMsgAgencyChange::createFromReq))).second != 0;
    bRet &= CommMsgBase::_sTypeToMsg.insert(TTMMValueType(INSTITUTION_APPROVAL_REQ, reinterpret_cast<CommMsgAgencyApprovalPtr(*)(RequestPtr)>(CommMsgAgencyApproval::createFromReq))).second != 0;
    bRet &= CommMsgBase::_sTypeToMsg.insert(TTMMValueType(ROLES_ADD_REQ, reinterpret_cast<CommMsgRolesAddPtr(*)(RequestPtr)>(CommMsgRolesAdd::createFromReq))).second != 0;
    bRet &= CommMsgBase::_sTypeToMsg.insert(TTMMValueType(ROLES_CHANGE_REQ, reinterpret_cast<CommMsgRolesChangePtr(*)(RequestPtr)>(CommMsgRolesChange::createFromReq))).second != 0;
    bRet &= CommMsgBase::_sTypeToMsg.insert(TTMMValueType(BIND_FUNCTION_ROLE_RELATIUON_REQ, reinterpret_cast<CommMsgBindRelationPtr(*)(RequestPtr)>(CommMsgBindRelation::createFromReq))).second != 0;
    bRet &= CommMsgBase::_sTypeToMsg.insert(TTMMValueType(USERROLE_ADDRELATION_REQ, reinterpret_cast<CommMsgUserRoleAddRelationPtr(*)(RequestPtr)>(CommMsgUserRoleAddRelation::createFromReq))).second != 0;
    bRet &= CommMsgBase::_sTypeToMsg.insert(TTMMValueType(CHILDUSER_ADD_REQ, reinterpret_cast<CommMsgChildAccAddPtr(*)(RequestPtr)>(CommMsgChildAccAdd::createFromReq))).second != 0;
    bRet &= CommMsgBase::_sTypeToMsg.insert(TTMMValueType(CHILDUSER_CHANGE_REQ, reinterpret_cast<CommMsgChildAccChangePtr(*)(RequestPtr)>(CommMsgChildAccChange::createFromReq))).second != 0;
    bRet &= CommMsgBase::_sTypeToMsg.insert(TTMMValueType(CHILDUSER_INOUTMONEY_REQ, reinterpret_cast<CommMsgChildAccInmoneyPtr(*)(RequestPtr)>(CommMsgChildAccInmoney::createFromReq))).second != 0;
    bRet &= CommMsgBase::_sTypeToMsg.insert(TTMMValueType(CHILDUSER_APPROVAL_REQ, reinterpret_cast<CommMsgChildAccApprovalPtr(*)(RequestPtr)>(CommMsgChildAccApproval::createFromReq))).second != 0;
    bRet &= CommMsgBase::_sTypeToMsg.insert(TTMMValueType(FUNDUSER_ADD_REQ, reinterpret_cast<CommMsgFundAccAddPtr(*)(RequestPtr)>(CommMsgFundAccAdd::createFromReq))).second != 0;
    bRet &= CommMsgBase::_sTypeToMsg.insert(TTMMValueType(FUNDUSER_CHANGE_REQ, reinterpret_cast<CommMsgFundAccChangePtr(*)(RequestPtr)>(CommMsgFundAccChange::createFromReq))).second != 0;
    bRet &= CommMsgBase::_sTypeToMsg.insert(TTMMValueType(FEE_SET_REQ, reinterpret_cast<CommMsgFeeSetPtr(*)(RequestPtr)>(CommMsgFeeSet::createFromReq))).second != 0;
    bRet &= CommMsgBase::_sTypeToMsg.insert(TTMMValueType(STOCK_INSTRUMENTBLACK_SET_REQ, reinterpret_cast<CommMsgStockBlackSetPtr(*)(RequestPtr)>(CommMsgStockBlackSet::createFromReq))).second != 0;
    bRet &= CommMsgBase::_sTypeToMsg.insert(TTMMValueType(FORBID_BUY_SELL_SET_REQ, reinterpret_cast<CommMsgForbidBuySellSetPtr(*)(RequestPtr)>(CommMsgForbidBuySellSet::createFromReq))).second != 0;
    bRet &= CommMsgBase::_sTypeToMsg.insert(TTMMValueType(POSI_RATE_SET_REQ, reinterpret_cast<CommMsgPosiRateSetPtr(*)(RequestPtr)>(CommMsgPosiRateSet::createFromReq))).second != 0;
    bRet &= CommMsgBase::_sTypeToMsg.insert(TTMMValueType(CHILDUSER_AUTOINMONEY_APPROVAL_REQ, reinterpret_cast<CommMsgAutoInMoneyApprovalPtr(*)(RequestPtr)>(CommMsgAutoInMoneyApproval::createFromReq))).second != 0;
    bRet &= CommMsgBase::_sTypeToMsg.insert(TTMMValueType(CHILDUSER_AUTOOUTMONEY_APPROVAL_REQ, reinterpret_cast<CommMsgAutoOutMoneyApprovalPtr(*)(RequestPtr)>(CommMsgAutoOutMoneyApproval::createFromReq))).second != 0;
    bRet &= CommMsgBase::_sTypeToMsg.insert(TTMMValueType(PASSWORD_CHANGE_REQ, reinterpret_cast<CommMsgPswChangePtr(*)(RequestPtr)>(CommMsgPswChange::createFromReq))).second != 0;
    bRet &= CommMsgBase::_sTypeToMsg.insert(TTMMValueType(MANAGER_ADD_REQ, reinterpret_cast<CommMsgManagerAddPtr(*)(RequestPtr)>(CommMsgManagerAdd::createFromReq))).second != 0;
    bRet &= CommMsgBase::_sTypeToMsg.insert(TTMMValueType(MANAGER_CHANGE_REQ, reinterpret_cast<CommMsgManagerChangePtr(*)(RequestPtr)>(CommMsgManagerChange::createFromReq))).second != 0;
    bRet &= CommMsgBase::_sTypeToMsg.insert(TTMMValueType(OPENCLOSE_REQ, reinterpret_cast<CommMsgOpenClosePtr(*)(RequestPtr)>(CommMsgOpenClose::createFromReq))).second != 0;
    bRet &= CommMsgBase::_sTypeToMsg.insert(TTMMValueType(CANCELORDER_REQ, reinterpret_cast<CommMsgCancelOrderPtr(*)(RequestPtr)>(CommMsgCancelOrder::createFromReq))).second != 0;
    bRet &= CommMsgBase::_sTypeToMsg.insert(TTMMValueType(SELFFUNCTION_QUERY_REQ, reinterpret_cast<CommMsgSelfFunctionQryPtr(*)(RequestPtr)>(CommMsgSelfFunctionQry::createFromReq))).second != 0;
    bRet &= CommMsgBase::_sTypeToMsg.insert(TTMMValueType(ROLEFUNCTION_QUERY_REQ, reinterpret_cast<CommMsgRoleFunctionQryPtr(*)(RequestPtr)>(CommMsgRoleFunctionQry::createFromReq))).second != 0;
    bRet &= CommMsgBase::_sTypeToMsg.insert(TTMMValueType(ROLES_DEL_REQ, reinterpret_cast<CommMsgDelRolePtr(*)(RequestPtr)>(CommMsgDelRole::createFromReq))).second != 0;
    bRet &= CommMsgBase::_sTypeToMsg.insert(TTMMValueType(ROLES_USER_DEL_REQ, reinterpret_cast<CommMsgDelRoleUserPtr(*)(RequestPtr)>(CommMsgDelRoleUser::createFromReq))).second != 0;
    bRet &= CommMsgBase::_sTypeToMsg.insert(TTMMValueType(BUSSNESS_QUERY_REQ, reinterpret_cast<CommMsgGetAllBussnessUserPtr(*)(RequestPtr)>(CommMsgGetAllBussnessUser::createFromReq))).second != 0;
    bRet &= CommMsgBase::_sTypeToMsg.insert(TTMMValueType(APPLY_EQUIPMONEY_REQ, reinterpret_cast<CommMsgApplyEquipMoneyPtr(*)(RequestPtr)>(CommMsgApplyEquipMoney::createFromReq))).second != 0;
    bRet &= CommMsgBase::_sTypeToMsg.insert(TTMMValueType(APPLY_EQUIPMONEY_APPROVAL_REQ, reinterpret_cast<CommMsgApprovalApplyEquipMoneyPtr(*)(RequestPtr)>(CommMsgApprovalApplyEquipMoney::createFromReq))).second != 0;
    bRet &= CommMsgBase::_sTypeToMsg.insert(TTMMValueType(INSTITUTION_DEL_REQ, reinterpret_cast<CommMsgAgencyDeletePtr(*)(RequestPtr)>(CommMsgAgencyDelete::createFromReq))).second != 0;
    bRet &= CommMsgBase::_sTypeToMsg.insert(TTMMValueType(CHILDUSER_DEL_REQ, reinterpret_cast<CommMsgChildDeletePtr(*)(RequestPtr)>(CommMsgChildDelete::createFromReq))).second != 0;
    bRet &= CommMsgBase::_sTypeToMsg.insert(TTMMValueType(FUNDUSER_DEL_REQ, reinterpret_cast<CommMsgFunderDeletePtr(*)(RequestPtr)>(CommMsgFunderDelete::createFromReq))).second != 0;
    bRet &= CommMsgBase::_sTypeToMsg.insert(TTMMValueType(MANAGER_DEL_REQ, reinterpret_cast<CommMsgManagerDeletePtr(*)(RequestPtr)>(CommMsgManagerDelete::createFromReq))).second != 0;
    bRet &= CommMsgBase::_sTypeToMsg.insert(TTMMValueType(CUSTOMSTOCK_REQ, reinterpret_cast<CommMsgGetCustomStockPtr(*)(RequestPtr)>(CommMsgGetCustomStock::createFromReq))).second != 0;
    bRet &= CommMsgBase::_sTypeToMsg.insert(TTMMValueType(CUSTOMSTOCK_ADD_REQ, reinterpret_cast<CommMsgAddCustomStockPtr(*)(RequestPtr)>(CommMsgAddCustomStock::createFromReq))).second != 0;
    bRet &= CommMsgBase::_sTypeToMsg.insert(TTMMValueType(CUSTOMSTOCK_DEL_REQ, reinterpret_cast<CommMsgDelCustomStockPtr(*)(RequestPtr)>(CommMsgDelCustomStock::createFromReq))).second != 0;
	bRet &= CommMsgBase::_sTypeToMsg.insert(TTMMValueType(ROLES_USER_CHANGE_REQ, reinterpret_cast<CommMsgChangeRoleUserPtr(*)(RequestPtr)>(CommMsgChangeRoleUser::createFromReq))).second != 0;

    bRet &= CommMsgBase::_sTypeToMsg.insert(TTMMValueType(CHILD_AUTOINTOMONEY_QUERY_REQ, reinterpret_cast<CommMsgAutoInMoneyQryPtr(*)(RequestPtr)>(CommMsgAutoInMoneyQry::createFromReq))).second != 0;
    bRet &= CommMsgBase::_sTypeToMsg.insert(TTMMValueType(CHILDUSER_AUTO_INMONEY_REQ, reinterpret_cast<CommMsgAutoInMoneyPtr(*)(RequestPtr)>(CommMsgAutoInMoney::createFromReq))).second != 0;
    bRet &= CommMsgBase::_sTypeToMsg.insert(TTMMValueType(CHILDUSER_AUTO_OUTMONEY_REQ, reinterpret_cast<CommMsgAutoOutMoneyPtr(*)(RequestPtr)>(CommMsgAutoOutMoney::createFromReq))).second != 0;
    bRet &= CommMsgBase::_sTypeToMsg.insert(TTMMValueType(CHILDUSER_AUTO_ADD_REQ, reinterpret_cast<CommMsgChildAccAutoAddPtr(*)(RequestPtr)>(CommMsgChildAccAutoAdd::createFromReq))).second != 0;
	bRet &= CommMsgBase::_sTypeToMsg.insert(TTMMValueType(RISK_HISTORY_REQ, reinterpret_cast<RiskHistoryQryPtr(*)(RequestPtr)>(RiskHistoryQry::createFromReq))).second != 0;
 
	bRet &= CommMsgBase::_sTypeToMsg.insert(TTMMValueType(MARGIN_SET_REQ, reinterpret_cast<MarginSetQryPtr(*)(RequestPtr)>(MarginSetQry::createFromReq))).second != 0;
	bRet &= CommMsgBase::_sTypeToMsg.insert(TTMMValueType(MARGIN_LEFTQTY_REQ, reinterpret_cast<MarginLeftQryPtr(*)(RequestPtr)>(MarginLeftQry::createFromReq))).second != 0;
	bRet &= CommMsgBase::_sTypeToMsg.insert(TTMMValueType(MARGIN_MANAGER_REQ, reinterpret_cast<MarginManagerQryPtr(*)(RequestPtr)>(MarginManagerQry::createFromReq))).second != 0;

	bRet &= CommMsgBase::_sTypeToMsg.insert(TTMMValueType(MARGIN_LIABILITIES_REQ, reinterpret_cast<MarginLiabilitiesQryPtr(*)(RequestPtr)>(MarginLiabilitiesQry::createFromReq))).second != 0;
	bRet &= CommMsgBase::_sTypeToMsg.insert(TTMMValueType(INTEREST_STATISTICS_REQ, reinterpret_cast<InterestStatisticsQryPtr(*)(RequestPtr)>(InterestStatisticsQry::createFromReq))).second != 0;
	bRet &= CommMsgBase::_sTypeToMsg.insert(TTMMValueType(INTEREST_DETAIL_REQ, reinterpret_cast<InterestDetailQryPtr(*)(RequestPtr)>(InterestDetailQry::createFromReq))).second != 0;
	bRet &= CommMsgBase::_sTypeToMsg.insert(TTMMValueType(CURRENT_MARGINENTRUST_REQ, reinterpret_cast<CommMsgCurrentyMarginEntrustQryPtr(*)(RequestPtr)>(CommMsgCurrentyMarginEntrustQry::createFromReq))).second != 0;
	bRet &= CommMsgBase::_sTypeToMsg.insert(TTMMValueType(CURRENT_MARGINTRADE_REQ, reinterpret_cast<CommMsgCurrentyMarginTradeQryPtr(*)(RequestPtr)>(CommMsgCurrentyMarginTradeQry::createFromReq))).second != 0;

	
	// 命令码<-->命令类型
    for ( int i=0; i<EMPT_Max_Count; i++ )
        CommMsgBase::_sCmdTypeMap.insert( CTMapValue(gszMsgCommandCode[i], i) );

    return bRet;
}

void CommMsgBase::unInitialize()
{
    CommMsgBase::_sTypeToMsg.clear();
    CommMsgBase::_sCmdTypeMap.clear();
}

std::tuple<CommMsgPtr, AllTrade::ErrorCodeType> CommMsgBase::create(RequestPtr request)
{
    assert( request );

    E_COMM_MSG_TYPE type = CommMsgBase::getTypeFromCmd( request->command_ );
    if ( type == EMPT_Init_Null )
    {
        return std::make_tuple(CommMsgPtr(), Err_Req_Parameter);
    }

    TypeToMsgMap::iterator itfind = CommMsgBase::_sTypeToMsg.find(type);
    if (itfind != CommMsgBase::_sTypeToMsg.end())
    {
        CommMsgPtr pCommMsg = (itfind->second)(request);
        return std::make_tuple(pCommMsg, Err_Succeed);
    }

    assert(0);
    return std::make_tuple(CommMsgPtr(), Err_Unknown);
}

E_COMM_MSG_TYPE CommMsgBase::getTypeFromCmd(const std::string& cmd)
{
    CmdTypeMap::iterator itf = CommMsgBase::_sCmdTypeMap.find( cmd );
    if ( itf != CommMsgBase::_sCmdTypeMap.end() )
        return (E_COMM_MSG_TYPE)itf->second;

    assert(0);
    return EMPT_Init_Null;
}

