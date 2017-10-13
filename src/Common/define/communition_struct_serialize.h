
#ifndef TABLESTRUCT_SERIZLIZE_H
#define TABLESTRUCT_SERIZLIZE_H

#include "communition_struct_define.h"
#include "params_declare.h"
#include "define/struct_declare.h"
#include "define/reply_message_declare.h"

//////////////////////////////////////////////////////////////////////////
extern std::string toJson(AllTrade::ErrorCodeType result, const std::string& cmd_code);

//////////////////////////////////////////////////////////////////////////
extern void fromJson(xyc_communication::ReplyLoginMsg* msg_info, const std::string& json);
extern std::string toJson(xyc_communication::ReplyLoginMsgPtr msg_info);

//////////////////////////////////////////////////////////////////////////
// extern void fromJson(xyc_communication::ReplyAgencyQryMsg* msg_info, const std::string& json);
extern std::string toJson(xyc_communication::ReplyAgencyQryMsgPtr msg_info);

//////////////////////////////////////////////////////////////////////////
// extern void fromJson(xyc_communication::ReplyAgencyPreApprovalQryMsg* msg_info, const std::string& json);
extern std::string toJson(xyc_communication::ReplyAgencyPreApprovalQryMsgPtr msg_info);

/////////////////////////////// ��ɫ��ѯ ///////////////////////////////////////////
// extern void fromJson(xyc_communication::ReplyRolesQryMsg* msg_info, const std::string& json);
extern std::string toJson(xyc_communication::ReplyRolesQryMsgPtr msg_info);

//////////////////////////////////////////////////////////////////////////
// extern void fromJson(xyc_communication::ReplyChildAccQryMsg* msg_info, const std::string& json);
extern std::string toJson(xyc_communication::ReplyChildAccQryMsgPtr msg_info);

//////////////////////////////////////////////////////////////////////////
// extern void fromJson(xyc_communication::ReplyChildApprovalQryMsg* msg_info, const std::string& json);
extern std::string toJson(xyc_communication::ReplyChildApprovalQryMsgPtr msg_info);

//////////////////////////////////////////////////////////////////////////
extern void fromJson(xyc_communication::ReplyAgencyAddMsg* msg_info, const std::string& json);
extern std::string toJson(xyc_communication::ReplyAgencyAddMsgPtr msg_info);

//////////////////////////////////////////////////////////////////////////
extern void fromJson(xyc_communication::ReplyAgencyChangeMsg* msg_info, const std::string& json);
extern std::string toJson(xyc_communication::ReplyAgencyChangeMsgPtr msg_info);

//////////////////////////////////////////////////////////////////////////
extern void fromJson(xyc_communication::ReplyAgencyApprovalMsg* msg_info, const std::string& json);
extern std::string toJson(xyc_communication::ReplyAgencyApprovalMsgPtr msg_info);

//////////////////////////////////////////////////////////////////////////
extern void fromJson(xyc_communication::ReplyChildAccAddMsg* msg_info, const std::string& json);
extern std::string toJson(xyc_communication::ReplyChildAccAddMsgPtr msg_info);

//////////////////////////////////////////////////////////////////////////
extern void fromJson(xyc_communication::ReplyChildAccChangeMsg* msg_info, const std::string& json);
extern std::string toJson(xyc_communication::ReplyChildAccChangeMsgPtr msg_info);

//////////////////////////////////////////////////////////////////////////
extern void fromJson(xyc_communication::ReplyChildAccApprovalMsg* msg_info, const std::string& json);
extern std::string toJson(xyc_communication::ReplyChildAccApprovalMsgPtr msg_info);

//////////////////////////////////////////////////////////////////////////
extern void fromJson(xyc_communication::ReplyChildAccInmoneyMsg* msg_info, const std::string& json);
extern std::string toJson(xyc_communication::ReplyChildAccInmoneyMsgPtr msg_info);

//////////////////////////////////////////////////////////////////////////
// extern void fromJson(xyc_communication::ReplyFundAccQryMsg* msg_info, const std::string& json);
extern std::string toJson(xyc_communication::ReplyFundAccQryMsgPtr msg_info);

//////////////////////////////////////////////////////////////////////////
extern void fromJson(xyc_communication::ReplyStockContractQryMsg* msg_info, const std::string& json);
extern std::string toJson(xyc_communication::ReplyStockContractQryMsgPtr msg_info);

//////////////////////////////////////////////////////////////////////////
extern void fromJson(xyc_communication::ReplyFundAccAddMsg* msg_info, const std::string& json);
extern std::string toJson(xyc_communication::ReplyFundAccAddMsgPtr msg_info);

//////////////////////////////////////////////////////////////////////////
extern void fromJson(xyc_communication::ReplyFundAccChangeMsg* msg_info, const std::string& json);
extern std::string toJson(xyc_communication::ReplyFundAccChangeMsgPtr msg_info);

//////////////////////////////////////////////////////////////////////////
extern void fromJson(xyc_communication::ReplyFeeSetMsg* msg_info, const std::string& json);
extern std::string toJson(xyc_communication::ReplyFeeSetMsgPtr msg_info);

///////////////////////////////////////////////// ���ӽ�ɫ /////////////////////////
extern void fromJson(xyc_communication::ReplyRolesAddMsg* msg_info, const std::string& json);
extern std::string toJson(xyc_communication::ReplyRolesAddMsgPtr msg_info);

/////////////////////////////// ���ӽ�ɫ�͹���֮���ϵ ///////////////////////////////////////////
extern void fromJson(xyc_communication::ReplyBindRelationMsg* msg_info, const std::string& json);
extern std::string toJson(xyc_communication::ReplyBindRelationMsgPtr msg_info);

/////////////////////////////// �޸Ľ�ɫ ///////////////////////////////////////////
extern void fromJson(xyc_communication::ReplyRolesChangeMsg* msg_info, const std::string& json);
extern std::string toJson(xyc_communication::ReplyRolesChangeMsgPtr msg_info);

//////////////////////////////////////////////////////////////////////////
extern void fromJson(xyc_communication::ReplyOpenCloseMsg* msg_info, const std::string& json);
extern std::string toJson(xyc_communication::ReplyOpenCloseMsgPtr msg_info);

//////////////////////////////////////////////////////////////////////////
extern void fromJson(xyc_communication::ReplyCancelOrderMsg* msg_info, const std::string& json);
extern std::string toJson(xyc_communication::ReplyCancelOrderMsgPtr msg_info);

//////////////////////////////////////////////////////////////////////////
extern void fromJson(xyc_communication::ReplyFundQryMsg* msg_info, const std::string& json);
extern std::string toJson(xyc_communication::ReplyFundQryMsgPtr msg_info);

//////////////////////////////////////////////////////////////////////////
extern void fromJson(xyc_communication::ReplyFundSerialQryMsg* msg_info, const std::string& json);
extern std::string toJson(xyc_communication::ReplyFundSerialQryMsgPtr msg_info);

//////////////////////////////////////////////////////////////////////////
extern void fromJson(xyc_communication::ReplyPosiQryMsg* msg_info, const std::string& json);
extern std::string toJson(xyc_communication::ReplyPosiQryMsgPtr msg_info);

//////////////////////////////////////////////////////////////////////////
extern void fromJson(xyc_communication::ReplyCurrentyEntrustQryMsg* msg_info, const std::string& json);
extern std::string toJson(xyc_communication::ReplyCurrentyEntrustQryMsgPtr msg_info);
//////////////////////////////////////////////////////////////////////////
extern void fromJson(xyc_communication::ReplyTodayEntrustQryMsg* msg_info, const std::string& json);
extern std::string toJson(xyc_communication::ReplyTodayEntrustQryMsgPtr msg_info);
//////////////////////////////////////////////////////////////////////////
extern void fromJson(xyc_communication::ReplyHistoryEntrustQryMsg* msg_info, const std::string& json);
extern std::string toJson(xyc_communication::ReplyHistoryEntrustQryMsgPtr msg_info);
//////////////////////////////////////////////////////////////////////////
extern void fromJson(xyc_communication::ReplyTradeQryMsg* msg_info, const std::string& json);
extern std::string toJson(xyc_communication::ReplyTradeQryMsgPtr msg_info);
//////////////////////////////////////////////////////////////////////////
extern void fromJson(xyc_communication::ReplyHistoryTradeQryMsg* msg_info, const std::string& json);
extern std::string toJson(xyc_communication::ReplyHistoryTradeQryMsgPtr msg_info);

//////////////////////////////////////////////////////////////////////////
extern void fromJson(xyc_communication::ReplyPswChangeMsg* msg_info, const std::string& json);
extern std::string toJson(xyc_communication::ReplyPswChangeMsgPtr msg_info);

//////////////////////////////////////////////////////////////////////////
extern void fromJson(xyc_communication::ReplyManagerAddMsg* msg_info, const std::string& json);
extern std::string toJson(xyc_communication::ReplyManagerAddMsgPtr msg_info);

//////////////////////////////////////////////////////////////////////////
extern void fromJson(xyc_communication::ReplyManagerChangeMsg* msg_info, const std::string& json);
extern std::string toJson(xyc_communication::ReplyManagerChangeMsgPtr msg_info);

//////////////////////////////////////////////////////////////////////////
extern void fromJson(xyc_communication::ReplyEquipmentMoneyQryMsg* msg_info, const std::string& json); 
extern std::string toJson(xyc_communication::ReplyEquipmentMoneyQryMsgPtr msg_info);

//////////////////////////////////////////////////////////////////////////
extern std::string toJson(xyc_communication::ReplyFeeSetQryMsgPtr msg_info);

//////////////////////////////////////////////////////////////////////////
extern std::string toJson(xyc_communication::ReplyManagerQryMsgPtr msg_info);

//////////////////////////////////////////////////////////////////////////
extern std::string toJson(xyc_communication::PushOrderMsgPtr msg_info);
//////////////////////////////////////////////////////////////////////////
extern std::string toJson(xyc_communication::PushTradeMsgPtr msg_info);
//////////////////////////////////////////////////////////////////////////
extern std::string toJson(xyc_communication::PushPositionMsgPtr msg_info);
//////////////////////////////////////////////////////////////////////////
extern std::string toJson(xyc_communication::PushMoneyMsgPtr msg_info);
//////////////////////////////////////////////////////////////////////////
extern std::string toJson(xyc_communication::PushRiskControlMsgPtr msg_info);


/////////////////////////////// ��½�������ܲ�ѯ ///////////////////////////////////////////
// extern void fromJson(xyc_communication::ReplySelfFunctionMsg* msg_info, const std::string& json);
extern std::string toJson(xyc_communication::ReplySelfFunctionMsgPtr msg_info);

/////////////////////////////// ��ɫ���ܲ�ѯ ///////////////////////////////////////////
extern void fromJson(xyc_communication::ReplyRoleFunctionMsg* msg_info, const std::string& json);
extern std::string toJson(xyc_communication::ReplyRoleFunctionMsgPtr msg_info);

/////////////////////////////// ɾ����ɫ ///////////////////////////////////////////
extern void fromJson(xyc_communication::ReplyDelRoleMsg* msg_info, const std::string& json);
extern std::string toJson(xyc_communication::ReplyDelRoleMsgPtr msg_info);

/////////////////////////////// ��ɫ/�û���ѯ ///////////////////////////////////////////
// extern void fromJson(xyc_communication::ReplyAgencyRolesQryMsg* msg_info, const std::string& json);
extern std::string toJson(xyc_communication::ReplyAgencyRolesQryMsgPtr msg_info);

/////////////////////////////// ��ɫ/�û����� ///////////////////////////////////////////
extern void fromJson(xyc_communication::ReplyUserRoleAddRelationMsg* msg_info, const std::string& json);
extern std::string toJson(xyc_communication::ReplyUserRoleAddRelationMsgPtr msg_info);

/////////////////////////////// ɾ����ɫ/�û� ///////////////////////////////////////////
extern void fromJson(xyc_communication::ReplyDelRoleUserMsg* msg_info, const std::string& json);
extern std::string toJson(xyc_communication::ReplyDelRoleUserMsgPtr msg_info);

/////////////////////////////// ��ѯ����ҵ�� ///////////////////////////////////////////
// extern void fromJson(xyc_communication::ReplyGetAllBussnessMsg* msg_info, const std::string& json);
extern std::string toJson(xyc_communication::ReplyGetAllBussnessMsgPtr msg_info);

/////////////////////////////// ��ѯ�������˻� ///////////////////////////////////////////
extern std::string toJson(xyc_communication::ReplyOnlineAccQryMsgPtr msg_info);

/////////////////////////////// ������� ///////////////////////////////////////////
extern void fromJson(xyc_communication::ReplyApplyEquipMoneyMsg* msg_info, const std::string& json);
extern std::string toJson(xyc_communication::ReplyApplyEquipMoneyMsgPtr msg_info);

/////////////////////////////// ���������� ///////////////////////////////////////////
extern void fromJson(xyc_communication::ReplyApprovalApplyEquipMoneyMsg* msg_info, const std::string& json);
extern std::string toJson(xyc_communication::ReplyApprovalApplyEquipMoneyMsgPtr msg_info);

/////////////////////////////// ɾ������ ///////////////////////////////////////////
extern void fromJson(xyc_communication::ReplyAgencyDeleteMsg* msg_info, const std::string& json);
extern std::string toJson(xyc_communication::ReplyAgencyDeleteMsgPtr msg_info);

/////////////////////////////// ɾ�����˻� ///////////////////////////////////////////
extern void fromJson(xyc_communication::ReplyChildDeleteMsg* msg_info, const std::string& json);
extern std::string toJson(xyc_communication::ReplyChildDeleteMsgPtr msg_info);

/////////////////////////////// ɾ���ʽ��˻� ///////////////////////////////////////////
extern void fromJson(xyc_communication::ReplyFunderDeleteMsg* msg_info, const std::string& json);
extern std::string toJson(xyc_communication::ReplyFunderDeleteMsgPtr msg_info);

/////////////////////////////// ɾ������Ա ///////////////////////////////////////////
extern void fromJson(xyc_communication::ReplyManagerDeleteMsg* msg_info, const std::string& json);
extern std::string toJson(xyc_communication::ReplyManagerDeleteMsgPtr msg_info);

//////////////////////////////////////////////////////////////////////////
extern std::string toJson(xyc_communication::ReplyStockBlackQryMsgPtr msg_info);

//////////////////////////////////////////////////////////////////////////
extern void fromJson(xyc_communication::ReplyStockBlackSetMsg* msg_info, const std::string& json);
extern std::string toJson(xyc_communication::ReplyStockBlackSetMsgPtr msg_info);

//////////////////////////////////////////////////////////////////////////
extern std::string toJson(xyc_communication::ReplyForbidBuySellQryMsgPtr msg_info);

//////////////////////////////////////////////////////////////////////////
extern void fromJson(xyc_communication::ReplyForbidBuySellSetMsg* msg_info, const std::string& json);
extern std::string toJson(xyc_communication::ReplyForbidBuySellSetMsgPtr msg_info);

//////////////////////////////////////////////////////////////////////////
extern std::string toJson(xyc_communication::ReplyPosiRateQryMsgPtr msg_info);

//////////////////////////////////////////////////////////////////////////
extern void fromJson(xyc_communication::ReplyPosiRateSetMsg* msg_info, const std::string& json);
extern std::string toJson(xyc_communication::ReplyPosiRateSetMsgPtr msg_info);

//////////////////////////////////////////////////////////////////////////
extern std::string toJson(xyc_communication::ReplyGetCustomStockMsgPtr msg_info);

//////////////////////////////////////////////////////////////////////////
extern void fromJson(xyc_communication::ReplyAddCustomStockMsg* msg_info, const std::string& json);
extern std::string toJson(xyc_communication::ReplyAddCustomStockMsgPtr msg_info);

//////////////////////////////////////////////////////////////////////////
extern void fromJson(xyc_communication::ReplyDelCustomStockMsg* msg_info, const std::string& json);
extern std::string toJson(xyc_communication::ReplyDelCustomStockMsgPtr msg_info);

/////////////////////////////// �޸Ľ�ɫ/�û� ///////////////////////////////////////////
extern void fromJson(xyc_communication::ReplyChangeRoleUserMsg* msg_info, const std::string& json);
extern std::string toJson(xyc_communication::ReplyChangeRoleUserMsgPtr msg_info);

///////////////////////////// �Զ����� //////////////////////////////////
extern void fromJson(xyc_communication::ReplyChildAccAutoAddMsg* msg_info, const std::string& json);
extern std::string toJson(xyc_communication::ReplyChildAccAutoAddMsgPtr msg_info);

///////////////////////////// �Զ���� //////////////////////////////////
extern void fromJson(xyc_communication::ReplyAutoInMoneyMsg* msg_info, const std::string& json);
extern std::string toJson(xyc_communication::ReplyAutoInMoneyMsgPtr msg_info);

///////////////////////////// �Զ������� //////////////////////////////
extern void fromJson(xyc_communication::ReplyAutoInMoneyApprovalMsg* msg_info, const std::string& json);
extern std::string toJson(xyc_communication::ReplyAutoInMoneyApprovalMsgPtr msg_info);

/////////////////// ���˻��Զ������˲�ѯ //////////////////////////////
extern void fromJson(xyc_communication::ReplyAutoInMoneyQryMsg* msg_info, const std::string& json);
extern std::string toJson(xyc_communication::ReplyAutoInMoneyQryMsgPtr msg_info);

///////////////////////////// �Զ����� //////////////////////////////////
extern void fromJson(xyc_communication::ReplyAutoOutMoneyMsg* msg_info, const std::string& json);
extern std::string toJson(xyc_communication::ReplyAutoOutMoneyMsgPtr msg_info);

///////////////////////////// �Զ�������� //////////////////////////////
extern void fromJson(xyc_communication::ReplyAutoOutMoneyApprovalMsg* msg_info, const std::string& json);
extern std::string toJson(xyc_communication::ReplyAutoOutMoneyApprovalMsgPtr msg_info);

/////////////////// ���˻��Զ�������˲�ѯ //////////////////////////////
extern void fromJson(xyc_communication::ReplyAutoOutMoneyQryMsg* msg_info, const std::string& json);
extern std::string toJson(xyc_communication::ReplyAutoOutMoneyQryMsgPtr msg_info);

/////////////////// ����Ӷ���ѯ //////////////////////////////
extern void fromJson(xyc_communication::ReplyCommissQryMsg* msg_info, const std::string& json);
extern std::string toJson(xyc_communication::ReplyCommissQryMsgPtr msg_info);

/////////////////// ����Ӷ����ϸ��ѯ //////////////////////////////
extern void fromJson(xyc_communication::ReplyCommissDtlQryMsg* msg_info, const std::string& json);
extern std::string toJson(xyc_communication::ReplyCommissDtlQryMsgPtr msg_info);

/////////////////// �����ֳɲ�ѯ //////////////////////////////
extern void fromJson(xyc_communication::ReplyProfitCommisslQryMsg* msg_info, const std::string& json);
extern std::string toJson(xyc_communication::ReplyProfitCommisslQryMsgPtr msg_info);

/////////////////// �����ֳ���ϸ��ѯ //////////////////////////////
extern void fromJson(xyc_communication::ReplyProfitCommissDtlQryMsg* msg_info, const std::string& json);
extern std::string toJson(xyc_communication::ReplyProfitCommissDtlQryMsgPtr msg_info);

/////////////////// �����ʷ��ѯ���� //////////////////////////////
extern void fromJson(xyc_communication::ReplyRiskHistoryMsg* msg_info, const std::string& json);
extern std::string toJson(xyc_communication::ReplyRiskHistoryMsgPtr msg_info);

/////////////////// ��ز�ѯ���� //////////////////////////////
extern void fromJson(xyc_communication::ReplyTimeWarnQryMsg* msg_info, const std::string& json);
extern std::string toJson(xyc_communication::ReplyTimeWarnQryMsgPtr msg_info);

/////////////////// ������ȯ���� //////////////////////////////
extern void fromJson(xyc_communication::ReplySetMarginMsg* msg_info, const std::string& json);
extern std::string toJson(xyc_communication::ReplySetMarginMsgPtr msg_info);

/////////////////// ��ȯʣ������ //////////////////////////////
extern void fromJson(xyc_communication::ReplyMarginLeftQtyMsg* msg_info, const std::string& json);
extern std::string toJson(xyc_communication::ReplyMarginLeftQtyMsgPtr msg_info);

/////////////////// ��ȯ�����ѯ���� //////////////////////////////
extern void fromJson(xyc_communication::ReplyMarginManagerQtyMsg* msg_info, const std::string& json);
extern std::string toJson(xyc_communication::ReplyMarginManagerQtyMsgPtr msg_info);

/////////////////// ��ȯ��ծ��ѯ���� //////////////////////////////
extern void fromJson(xyc_communication::ReplyMarginLiabilitiesQtyMsg* msg_info, const std::string& json);
extern std::string toJson(xyc_communication::ReplyMarginLiabilitiesQtyMsgPtr msg_info);

/////////////////// ��Ϣͳ�Ʋ�ѯ���� //////////////////////////////
extern void fromJson(xyc_communication::ReplyInterestStatisticsMsg* msg_info, const std::string& json);
extern std::string toJson(xyc_communication::ReplyInterestStatisticsMsgPtr msg_info);

/////////////////// ��Ϣ��ϸ��ѯ���� //////////////////////////////
extern void fromJson(xyc_communication::ReplyInterestDetailMsg* msg_info, const std::string& json);
extern std::string toJson(xyc_communication::ReplyInterestDetailMsgPtr msg_info);

/////////////////// ��ȯ��ǰί�в�ѯ���� //////////////////////////////
extern void fromJson(xyc_communication::ReplyCurrentMarginEntrustMsg* msg_info, const std::string& json);
extern std::string toJson(xyc_communication::ReplyCurrentMarginEntrustMsgPtr msg_info);

/////////////////// ��ȯ��ǰ�ɽ���ѯ���� //////////////////////////////
extern void fromJson(xyc_communication::ReplyCurrentMarginTradeQryMsg* msg_info, const std::string& json);
extern std::string toJson(xyc_communication::ReplyCurrentMarginTradeQryMsgPtr msg_info);
#endif