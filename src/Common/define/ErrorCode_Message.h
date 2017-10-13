#ifndef ERRORCOD_EMESSAGE_H
#define ERRORCOD_EMESSAGE_H

#include<QString>
#include "../../Common/define/protocol_error.h"
using namespace AllTrade;

QString getRtnErrorInfo(int errCode)
{
	switch (static_cast<ErrorCodeType>(errCode))
	{
	case Err_Pending:
		return QStringLiteral("�ѹ���");
	case Err_Unknown:
		return QStringLiteral("δ֪����");
	case Err_Succeed:
		return QStringLiteral("�ɹ�");

///////////////////////////////////////////////////////////////////////////
	case Err_Login_Version:
		return QStringLiteral("��¼�汾������");
	case Err_Login_Type:
		return QStringLiteral("��¼���Ͳ�����");
	case Err_Login_Ca:
		return QStringLiteral("CA��¼��ʽ����");
	case Err_Login_ForcePwd:
		return QStringLiteral("���޸������¼");
	case Err_Login_Identity:
		return QStringLiteral("��¼��ݲ�����");
	case Err_Login_LoginNo:
		return QStringLiteral("��¼��������");
	case Err_Login_Password:
		return QStringLiteral("��¼�����");
	case Err_Login_Forbidden:
		return QStringLiteral("��ֹ��¼");
	case Err_Login_Count:
		return QStringLiteral("��½������");
	case Err_Otp:
		return QStringLiteral("��������֤ʧ��");
	case Err_Network_Disconnected:
		return QStringLiteral("δ���ӻ����������");
	case Err_No_Valid_Data:
		return QStringLiteral("Ӧ���в�������Ч����");
	case Err_Not_Login:
		return QStringLiteral("δ��½�ɹ���û�в���Ȩ��");
	case Err_No_Such_Client_Rights:
		return QStringLiteral("û��Ȩ�޲������û�");
	case Err_No_Oper_Rights:
		return QStringLiteral("û�б�������Ȩ��");
	case Err_Init_FAIL1:
		return QStringLiteral("��ʼ�����ݳ���1");
	case Err_Init_FAIL2:
		return QStringLiteral("��ʼ�����ݳ���2");
	case Err_Init_FAIL3:
		return QStringLiteral("��ʼ�����ݳ���3");
	case Err_Init_Unsuccess:
		return QStringLiteral("δ�ɹ���ʼ��");
	case Err_Cert_Expired:
		return QStringLiteral("��֤���ѹ���");
	case Err_User_Has_Logged:
		return QStringLiteral("�û��Ѿ���¼����Ͽ����ٵ�½");
	case Err_Req_Too_Much:
		return QStringLiteral("����Ƶ�ʹ��ߣ����Ժ�����");
	case Err_Qry_Incomplete:
		return QStringLiteral("���ݲ�ѯ�����������Ժ�����");
	case Err_Cert_APPID:
		return QStringLiteral("Ӧ�ó���ID����֤�벻��");
	case Err_Force_Logout:
		return QStringLiteral("��ǿ���˳�");
	case Err_LoginName_TooShort:
		return QStringLiteral("��¼��̫��");
	case Err_Req_Parameter:
		return QStringLiteral("����Ĳ�������");

///////////////////////////////////////////////////////////////////////////
	case Err_Contract_Qry:
		return QStringLiteral("��ѯ��Լʧ�� �޴�Ʒ��");
	case Err_Hold_QryNoEnd:
		return QStringLiteral("��ѯ�ֲ�û�з��ؽ������޷�������һ�β�ѯ");
	case Err_CountRent_QryNoEnd:
		return QStringLiteral("��ѯ�������û�з��ؽ������޷�������һ�β�ѯ");

///////////////////////////////////////////////////////////////////////////
	case Err_Order_Contract:
		return QStringLiteral("�µ��޴˺�Լ");
	case Err_Order_Upper:
		return QStringLiteral("���ֲ�����");
	case Err_Order_State:
		return QStringLiteral("��״̬���ܳ���");
	case Err_Contract_NoTrade:
		return QStringLiteral("��Լ��ֹ����");
	case Err_Contract_ErrTime:
		return QStringLiteral("��Լ���ڽ���ʱ���");
	case Err_Contract_NoOpen:
		return QStringLiteral("��Լ��ֹ����");
	case Err_MaxOrderVol:
		return QStringLiteral("ί�г�������µ���");
	case Err_MaxHoldVol:
		return QStringLiteral("�ֲֳ����������");
	case Err_Client_NoTrade:
		return QStringLiteral("�ͻ���ֹ����");
	case Err_Client_NoOpen:
		return QStringLiteral("�ͻ���ֹ����");
	case Err_Money_NotEnough:
		return QStringLiteral("�µ��ʽ���");
	case Err_LME_Check:
		return QStringLiteral("LMEδ׼������");
	case Err_CanNotMove_DeletedOrder:
		return QStringLiteral("��ɾ����������ת��");
	case Err_CanNotDelete_RiskOrder:
		return QStringLiteral("ǿƽ�����ܳ���");
	case Err_Order_ClientNoExist:
		return QStringLiteral("�ͻ��Ų�����");
	case Err_OrderID_InCorrect:
		return QStringLiteral("�����Ų���ȷ");
	case Error_MatchInput_Vol:
		return QStringLiteral("¼��ɽ��������Ϸ�");
	case Error_Order_NoExist:
		return QStringLiteral("¼��ɽ��Ҳ���ί��");
	case Error_CanNotModify_RiskOrder:
		return QStringLiteral("ǿƽ�������޸�");
	case Error_CoverMode:
		return QStringLiteral("ƽ�ַ�ʽ����");
	case Err_Order_Trade_Time:
		return QStringLiteral("�µ����ڽ���ʱ��");
	case Err_Order_Param_Error:
		return QStringLiteral("�µ�ί�в�������");
	case Err_CancelOrder_Param_Error:
		return QStringLiteral("����ί�в�������");
	case Err_CancelOrder_TimeOut:
		return QStringLiteral("����ί���Ŷӳ�ʱ");
	case Err_CancelOrder_Cannot_Cancel:
		return QStringLiteral("����ί�ж������޷�����״̬");
	case Err_MaxCanCloseVol:
		return QStringLiteral("ί���������ڿ�ƽ������");
	case Err_No_QuoteInfo:
		return QStringLiteral("�޷���ȡ������Ϣ");

//////////////////////////////////////////////////////////////////////////

	case Err_Database:
		return QStringLiteral("���ݿ��������");


	case Err_Login_VersionErr:
		return QStringLiteral("��¼ʱ�������汾����");
	case Err_Login_UpNOErr:
		return QStringLiteral("��¼ʱ���ֺŴ���");
	case Err_Login_UpUserErr:
		return QStringLiteral("��¼ʱ���ֿͻ��Ŵ���");
	case Err_Trade_Trans:
		return QStringLiteral("�������ݰ�ת������");
	case Err_Trade_Send:
		return QStringLiteral("�������ݰ����ʹ���");
	case Err_Trade_APINoReady:
		return QStringLiteral("��������δ����");
	case Err_Trade_APIFail:
		return QStringLiteral("�������س���ʧ��");
	case Err_Trade_Initing:
		return QStringLiteral("ϵͳ���ڽ���ǿ�Ƴ�ʼ��");
	case Err_Trade_RejectByUpper:
		return QStringLiteral("�����־ܾ�");
	case Err_Trade_TransWNOFind:
		return QStringLiteral("�г���Ʒ�ֲ�����");
	case Err_Trade_InvalidOrderType:
		return QStringLiteral("�������Ͳ���֧��");
	case Err_Trade_PriceErr:
		return QStringLiteral("�۸����");
	case Err_Trade_UnknownOrderType:
		return QStringLiteral("�������ʹ���");
	case Err_Trade_UnknownContract:
		return QStringLiteral("��Լ����");
	case Err_Trade_ServerUnConnect:
		return QStringLiteral("������δ����");
	case Err_Trade_UnknownOrder:
		return QStringLiteral("����������");
	case Err_Trade_InvalidState:
		return QStringLiteral("����״̬������");
	case Err_Trade_AmendDisabled:
		return QStringLiteral("��������֧�ָĵ�");
	case Err_Trade_InvalidVolume:
		return QStringLiteral("�������Ϸ�");
	case Err_Trade_InvalidAmendOrderType:
		return QStringLiteral("�����Ͳ����޸�");
	case Err_Trade_UnknownAccount:
		return QStringLiteral("�˻����û���ƥ��");
	case Err_Trade_ErrDirect:
		return QStringLiteral("����ķ�����������");
	case Err_Trade_InvalidCommodityType:
		return QStringLiteral("��֧�ֵ���Ʒ����");
	case Err_Trade_InvalidMode:
		return QStringLiteral("�Ƿ��ı���ģʽ");
	case Err_Trade_InvalidOperType:
		return QStringLiteral("�۽��������������ʹ���");

//////////////////////////////////////////////////////////////////////////
	case Err_Frnt_Version:
		return QStringLiteral("�汾�Ų�����ǰ�û�Ҫ��");
	case Err_Frnt_Identity:
		return QStringLiteral("��ݴ���, ǰ�ò�����ǰ�õ�¼");
	case Err_Frnt_SendServer:
		return QStringLiteral("���͸�������ʧ��");
	case Err_Frnt_CMDNotAllow:
		return QStringLiteral("����֧�ֵ�����");
	case Err_Frnt_NORight:
		return QStringLiteral("�ͻ�û��Ȩ��");
	case Err_Frnt_SysNOErr:
		return QStringLiteral("ϵͳ�Ŵ���");
	case Err_Frnt_NOLogin:
		return QStringLiteral("δ��¼��Ȩ��");
	case Err_Frnt_ClientFull:
		return QStringLiteral("ǰ�õ�¼�ͻ�������");
	case Err_Frnt_IsNotClient:
		return QStringLiteral("ǰ�ò���������Ϳͻ���½");
	case Err_Frnt_NoReady:
		return QStringLiteral("ǰ��û��׼����");
	case Err_Frnt_NoData:
		return QStringLiteral("ǰ��û��������");
	case Err_Frnt_APPNotAllow:
		return QStringLiteral("�ͻ�Ӧ��û����Ȩ");
//////////////////////////////////////////////////////////////////////////
	case Err_Cert_Incorrect:
		return QStringLiteral("��֤�����");
	case Err_Open_Log_Init_Failed:
		return QStringLiteral("��־�ļ���ʼ��ʧ��");
	case Err_Open_Log_Failed:
		return QStringLiteral("��־�ļ���ʧ��");
	case Error_No_SuchRights:
		return QStringLiteral("�û��޴�Ȩ��");
	case Error_No_SuchOrderWay:
		return QStringLiteral("ί�з�ʽ����");
	case Error_No_SuchOffset:
		return QStringLiteral("��ƽ��־����");
/////////////////////////////////////////////////////////////////////////

	case Error_Otp_SyncTime:
		return QStringLiteral("��̬����ʱ��ͬ��ʧ��");
/////////////////////////////////////////////////////////////////////////
	case Error_CashOper_Value:
		return QStringLiteral("����������������");
	case Error_CashCheck_SerialID:
		return QStringLiteral("�������������кŴ���");
	case Error_CashCheck_NoMoneyInfo:
		return QStringLiteral("�������������ʽ���Ϣ");
	case Error_CashCheck_MoneyNotEnough:
		return QStringLiteral("�����������ʽ���");
/////////////////////////////////////////////////////////////////////////
	case Error_User_Exist:
		return QStringLiteral("�û��Ѵ���");
	case Error_User_Unexist:
		return QStringLiteral("�û�������");
	case Error_User_Parent_Unexist:
		return QStringLiteral("�û�����������");
	case Error_User_Creator_Unexist:
		return QStringLiteral("�û������߲�����");
	case Error_User_Funder_Unexist:
		return QStringLiteral("�û��ʽ��ʻ��߲�����");
	case Error_Exchange_Unexist:
		return QStringLiteral("������������");
	case Error_Exchange_Exist:
		return QStringLiteral("�������Ѵ���");
	case Error_Role_Exist:
		return QStringLiteral("��ɫ�Ѵ���");
	case Error_RoleUser_Exist:
		return QStringLiteral("��ɫ���˻����ڹ�ϵ");
	case Error_RoleFunctions_Exist:
		return QStringLiteral("��ɫ��ҵ���ܴ��ڹ�ϵ");
	case Error_ApplyMoney_Unexist:
		return QStringLiteral("������˶��󲻴���");
	case Error_UserAndFunction_Exist:
		return QStringLiteral("�˻��͹��ܴ��ڹ�ϵ");
	case Error_MaxAllowLevel_Over:
		return QStringLiteral("�����˻������˻�������������㼶");
	case Error_MaxAllowNum_Over:
		return QStringLiteral("�����˻������˻����������������");
	case Error_User_Status_Unallow:
		return QStringLiteral("�û���ǰ״̬������ò���");
	case Error_User_HasPosition:
		return QStringLiteral("���˻����гֲ�");
	case Error_User_Other_Login:
		return QStringLiteral("�û����������˿ڵ�¼");

	case Error_User_Over_PropRights:
		return QStringLiteral("�û����Գ���Ȩ��");
	case Error_User_Delete_HasBind:
		return QStringLiteral("ɾ���ʻ����а󶨶���");
	case Error_User_Parent_Reset:
		return QStringLiteral("�����˻����ò���ȷ");
	case Error_User_HasMoney:
		return QStringLiteral("���˻������ʽ�");

/////////////////////////////////////////////////////////////////////////////
	case Error_User_NoOpen_Force:
		return QStringLiteral("�˻�����ǿƽ,��ֹ����");
	case Error_User_NoOpen_Limit:
		return QStringLiteral("�˻������޲�,��ֹ����");
	case  Error_User_NoOpen_SameStock:
		return QStringLiteral("����ͬһ��Ʊ�ֱֲ����޶�,��ֹ����");

	case Error_User_NoOpen_Second_Board:
		return QStringLiteral("������ҵ������޶�,��ֹ����");
	case Error_User_NoOpen_LossCorp_Buy:
		return QStringLiteral("��ֹ���������ҵ��");
	case  Error_User_NoOpen_LossCorp_Sell:
		return QStringLiteral(" ��ֹ����������ҵ��");

	case Error_User_NoOpen_LossCorp_Trade:
		return QStringLiteral("��ֹ���׿�����ҵ��");
	case Error_User_NoOpen_RiseStop_Buy:
		return QStringLiteral("��ֹ������ͣ��");

	case Error_User_NoOpen_RiseStop_Sell:
		return QStringLiteral("��ֹ������ͣ��");
	case Error_User_NoOpen_RiseStop_Trade:
		return QStringLiteral("��ֹ������ͣ��");
	case  Error_User_NoOpen_FallStop_Buy:
		return QStringLiteral("��ֹ�����ͣ��");

	case Error_User_NoOpen_FallStop_Sell:
		return QStringLiteral("��ֹ������ͣ��");
	case Error_User_NoOpen_FallStop_Trade:
		return QStringLiteral("��ֹ���׵�ͣ��");
	case  Error_User_NoOpen_New_Buy:
		return QStringLiteral(" ��ֹ�����¹�");
	case Error_User_NoOpen_New_Sell:
		return QStringLiteral("��ֹ�����¹�");
	case  Error_User_NoOpen_New_Trade:
		return QStringLiteral("��ֹ�����¹�");
	case Error_User_NoOpen_RiseStop:
		return QStringLiteral("��ͣ���޷�����");
	case Error_User_NoClose_FallStop:
		return QStringLiteral("��ͣ���޷����");
	case Error_User_Will_NoOpen_Force:
		return QStringLiteral("�û��ʽ�ﵽǿƽ��,��ֹ����");
	case Error_User_Will_NoOpen_Limit:
		return QStringLiteral("�û��ʽ�ﵽ�޲���,��ֹ����");
	default:
		break;
	}
	return QStringLiteral("");
}


#endif