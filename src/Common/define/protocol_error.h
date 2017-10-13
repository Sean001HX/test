#ifndef __PROTOCOL_ERROR_H__
#define __PROTOCOL_ERROR_H__

#include "params_declare.h"

namespace AllTrade {
    ///////////////////////////////////////////////////////////////////////////
    //�����ύ�ɹ�
    const ErrorCodeType Err_Pending                             = -2;
    //δ֪����
    const ErrorCodeType Err_Unknown								= -1;
    //�ɹ�
    const ErrorCodeType Err_Succeed								= 0;

    ///////////////////////////////////////////////////////////////////////////
    //��¼�汾������
    const ErrorCodeType Err_Login_Version						= 1;
    //��¼���Ͳ�����
    const ErrorCodeType Err_Login_Type							= 2;
    //CA��¼��ʽ����
    const ErrorCodeType Err_Login_Ca							= 3;
    //���޸������¼
    const ErrorCodeType Err_Login_ForcePwd						= 4;
    //��¼��ݲ�����
    const ErrorCodeType Err_Login_Identity						= 5;
    //��¼��������
    const ErrorCodeType Err_Login_LoginNo						= 6;
    //��¼�����
    const ErrorCodeType Err_Login_Password						= 7;
    //��ֹ��¼
    const ErrorCodeType Err_Login_Forbidden						= 8;
    //��½������
    const ErrorCodeType Err_Login_Count							= 9;
    //��������֤ʧ��
    const ErrorCodeType Err_Otp									= 10;
    //δ���ӻ����������
    const ErrorCodeType Err_Network_Disconnected				= 11;
    //Ӧ���в�������Ч����
    const ErrorCodeType Err_No_Valid_Data   					= 12;
    //δ��½�ɹ���û�в���Ȩ��
    const ErrorCodeType Err_Not_Login   					    = 13;
    //û��Ȩ�޲������û�
    const ErrorCodeType Err_No_Such_Client_Rights		        = 14;
    //û�б�������Ȩ��
    const ErrorCodeType Err_No_Oper_Rights		                = 15;
    //��ʼ�����ݳ���1
    const ErrorCodeType Err_Init_FAIL1		                    = 16;
    //��ʼ�����ݳ���2
    const ErrorCodeType Err_Init_FAIL2		                    = 17;
    //��ʼ�����ݳ���3
    const ErrorCodeType Err_Init_FAIL3		                    = 18;
    //δ�ɹ���ʼ��
    const ErrorCodeType Err_Init_Unsuccess	                    = 19;
    //��֤���ѹ���
    const ErrorCodeType Err_Cert_Expired	                    = 20;
    //�û��Ѿ���¼����Ͽ����ٵ�½
    const ErrorCodeType Err_User_Has_Logged                     = 21;
    //����Ƶ�ʹ��ߣ����Ժ�����
    const ErrorCodeType Err_Req_Too_Much                        = 22;
    //���ݲ�ѯ�����������Ժ�����
    const ErrorCodeType Err_Qry_Incomplete                      = 23;
	//Ӧ�ó���ID����֤�벻��
	const ErrorCodeType Err_Cert_APPID						    = 24;
	//��ǿ���˳���
	const ErrorCodeType Err_Force_Logout					    = 25;
	//��¼��̫��
	const ErrorCodeType Err_LoginName_TooShort                  = 26;
	//����Ĳ�������
	const ErrorCodeType Err_Req_Parameter                       = 27;
	//


    ///////////////////////////////////////////////////////////////////////////
    //��ѯ��Լʧ�� �޴�Ʒ��
    const ErrorCodeType Err_Contract_Qry						= 101;
	//��ѯ�ֲ�û�з��ؽ������޷�������һ�β�ѯ
	const ErrorCodeType Err_Hold_QryNoEnd						= 102;
	//��ѯ�������û�з��ؽ������޷�������һ�β�ѯ
	const ErrorCodeType Err_CountRent_QryNoEnd					= 103;

    ///////////////////////////////////////////////////////////////////////////
    //�µ��޴˺�Լ
    const ErrorCodeType Err_Order_Contract						= 201;
    //���ֲ�����
    const ErrorCodeType Err_Order_Upper							= 202;
    //��״̬���ܳ���
    const ErrorCodeType Err_Order_State							= 203;
    //��Լ��ֹ����
    const ErrorCodeType Err_Contract_NoTrade					= 204;
    //��Լ���ڽ���ʱ���
    const ErrorCodeType Err_Contract_ErrTime                    = 205;
    //��Լ��ֹ����
    const ErrorCodeType Err_Contract_NoOpen						= 206;
    //ί�г�������µ���
    const ErrorCodeType Err_MaxOrderVol							= 207;
    //�ֲֳ����������
    const ErrorCodeType Err_MaxHoldVol							= 208;
    //�ͻ���ֹ����
    const ErrorCodeType Err_Client_NoTrade						= 209;
    //�ͻ���ֹ����
    const ErrorCodeType Err_Client_NoOpen						= 210;
    //�µ��ʽ���
    const ErrorCodeType Err_Money_NotEnough						= 211;
    //LMEδ׼������
    const ErrorCodeType Err_LME_Check							= 212;
    //��ɾ����������ת��
    const ErrorCodeType Err_CanNotMove_DeletedOrder				= 213;
    //ǿƽ�����ܳ���
    const ErrorCodeType Err_CanNotDelete_RiskOrder				= 214;
    //�ͻ��Ų�����
    const ErrorCodeType Err_Order_ClientNoExist					= 215;
    //�����Ų���ȷ
    const ErrorCodeType Err_OrderID_InCorrect                   = 216;
	//¼��ɽ��������Ϸ�
	const ErrorCodeType Error_MatchInput_Vol					= 217;
	//¼��ɽ��Ҳ���ί��
	const ErrorCodeType Error_Order_NoExist						= 218;
	//ǿƽ�������޸�
	const ErrorCodeType Error_CanNotModify_RiskOrder			= 219;
	//ƽ�ַ�ʽ����
	const ErrorCodeType Error_CoverMode							= 220;
    //�µ����ڽ���ʱ��
    const ErrorCodeType Err_Order_Trade_Time                    = 221;
    //�µ�ί�в�������
    const ErrorCodeType Err_Order_Param_Error                   = 222;
    //����ί�в�������
    const ErrorCodeType Err_CancelOrder_Param_Error             = 223;
    //����ί���Ŷӳ�ʱ
    const ErrorCodeType Err_CancelOrder_TimeOut                 = 224;
    //����ί�ж������޷�����״̬
    const ErrorCodeType Err_CancelOrder_Cannot_Cancel           = 225;
    //ί��״̬������ɽ�
    const ErrorCodeType Err_OrderStatus_Cannot_Trade            = 226;
    //ί���������ڿ�ƽ������
    const ErrorCodeType Err_MaxCanCloseVol                      = 227;
    //�޷���ȡ������Ϣ
    const ErrorCodeType Err_No_QuoteInfo                        = 228;

    ///////////////////////////////////////////////////////////////////////////
    //���ݿ��������
    const ErrorCodeType Err_Database							= 301;


    //-----���������������
    //��¼ʱ�������汾����
    const ErrorCodeType	Err_Login_VersionErr				    = 401;		
    //��¼ʱ���ֺŴ���                                            
    const ErrorCodeType	Err_Login_UpNOErr					    = 402;		
    //��¼ʱ���ֿͻ��Ŵ���			                              
    const ErrorCodeType	Err_Login_UpUserErr					    = 403;			
    //�������ݰ�ת������                                          
    const ErrorCodeType	Err_Trade_Trans						    = 404;		
    //�������ݰ����ʹ���                                          
    const ErrorCodeType	Err_Trade_Send						    = 405;	
    //��������δ����                                              
    const ErrorCodeType	Err_Trade_APINoReady				    = 406;		
    //�������س���ʧ��                                            
    const ErrorCodeType	Err_Trade_APIFail					    = 407;		
    //ϵͳ���ڽ���ǿ�Ƴ�ʼ��                                      
    const ErrorCodeType	Err_Trade_Initing					    = 408;		
    //�����־ܾ�                                                  
    const ErrorCodeType	Err_Trade_RejectByUpper				    = 409;	
    //�г���Ʒ�ֲ�����                                          
    const ErrorCodeType	Err_Trade_TransWNOFind				    = 410;		
    //�������Ͳ���֧��                                            
    const ErrorCodeType	Err_Trade_InvalidOrderType			    = 411;		
    //�۸����                                                    
    const ErrorCodeType	Err_Trade_PriceErr					    = 412;		
    //�������ʹ���                                                
    const ErrorCodeType	Err_Trade_UnknownOrderType			    = 413;		
    //��Լ����                                                    
    const ErrorCodeType	Err_Trade_UnknownContract			    = 414;		
    //������δ����                                                
    const ErrorCodeType	Err_Trade_ServerUnConnect			    = 415;		
    //����������
    const ErrorCodeType	Err_Trade_UnknownOrder				    = 416;		
    //����״̬������                                              
    const ErrorCodeType	Err_Trade_InvalidState				    = 417;		
    //��������֧�ָĵ�                                            
    const ErrorCodeType	Err_Trade_AmendDisabled				    = 418;		
    //�������Ϸ�                                                  
    const ErrorCodeType	Err_Trade_InvalidVolume				    = 419;		
    //�����Ͳ����޸�                                              
    const ErrorCodeType	Err_Trade_InvalidAmendOrderType		    = 420;		
    //�˻����û���ƥ��                                            
    const ErrorCodeType	Err_Trade_UnknownAccount			    = 421;		
    //����ķ�����������                                        
    const ErrorCodeType	Err_Trade_ErrDirect					    = 422;		
    //��֧�ֵ���Ʒ����                                            
    const ErrorCodeType	Err_Trade_InvalidCommodityType		    = 423;		
    //�Ƿ��ı���ģʽ                                              
    const ErrorCodeType	Err_Trade_InvalidMode				    = 424;
	//	�۽��������������ʹ���.
	const ErrorCodeType	Err_Trade_InvalidOperType				= 425;

    //ǰ�û����صĴ�����
    //�汾�Ų�����ǰ�û�Ҫ��
    const ErrorCodeType    Err_Frnt_Version                     = 501;
    //��ݴ���, ǰ�ò�����ǰ�õ�¼
    const ErrorCodeType    Err_Frnt_Identity                    = 502;
    //���͸�������ʧ��
    const ErrorCodeType    Err_Frnt_SendServer                  = 503;
    //����֧�ֵ�����
    const ErrorCodeType    Err_Frnt_CMDNotAllow                 = 504;
    //�ͻ�û��Ȩ��
    const ErrorCodeType  Err_Frnt_NORight                       = 505;
    //ϵͳ�Ŵ���
    const ErrorCodeType    Err_Frnt_SysNOErr                    = 506;
    //δ��¼��Ȩ��
    const ErrorCodeType  Err_Frnt_NOLogin                       = 508;
    //ǰ�õ�¼�ͻ�������
    const ErrorCodeType  Err_Frnt_ClientFull                    = 509;
    //ǰ�ò���������Ϳͻ���½
    const ErrorCodeType  Err_Frnt_IsNotClient                   = 510;
    //ǰ��û��׼����
    const ErrorCodeType  Err_Frnt_NoReady                       = 511;
	//ǰ��û��������
	const ErrorCodeType  Err_Frnt_NoData				        = 512;
	//�ͻ�Ӧ��û����Ȩ
	const ErrorCodeType  Err_Frnt_APPNotAllow			        = 513;

    //��֤������Ϣ
    //��֤�����
    const ErrorCodeType  Err_Cert_Incorrect                     = 600;
    //��־�ļ���ʼ��ʧ��
    const ErrorCodeType  Err_Open_Log_Init_Failed               = 601;
    //��־�ļ���ʧ��
    const ErrorCodeType  Err_Open_Log_Failed                    = 602;
	//�û��޴�Ȩ��
	const ErrorCodeType  Error_No_SuchRights			        = 603;
	//ί�з�ʽ����
	const ErrorCodeType  Error_No_SuchOrderWay			        = 604;
	//��ƽ��־����
	const ErrorCodeType  Error_No_SuchOffset			        = 605;


	///////////////////////////////////////////////////////////////////////////
	//��̬����ʱ��ͬ��ʧ��
	const ErrorCodeType Error_Otp_SyncTime				        = 700;


	//////////////////////////////////////////////////////////////////////////
	//����������������
	const ErrorCodeType Error_CashOper_Value			        = 800;
	//�������������кŴ���
	const ErrorCodeType Error_CashCheck_SerialID		        = 810;
	//�������������ʽ���Ϣ
	const ErrorCodeType Error_CashCheck_NoMoneyInfo	            = 811;
	//�����������ʽ���
	const ErrorCodeType Error_CashCheck_MoneyNotEnough	        = 812;

    //////////////////////////////////////////////////////////////////////////
    // �û��Ѵ���
    const ErrorCodeType Error_User_Exist                        = 900;
    // �û�������
    const ErrorCodeType Error_User_Unexist                      = 901;
    // �û�����������
    const ErrorCodeType Error_User_Parent_Unexist               = 902;
    // �û������߲�����
    const ErrorCodeType Error_User_Creator_Unexist              = 903;
    // �û��ʽ��ʻ��߲�����
    const ErrorCodeType Error_User_Funder_Unexist               = 904;
    // ������������
    const ErrorCodeType Error_Exchange_Unexist                  = 905;
    // �������Ѵ���
    const ErrorCodeType Error_Exchange_Exist                    = 906;
	// ��ɫ�Ѵ���
	const ErrorCodeType Error_Role_Exist						= 907;
	// �˻��Ѿ��󶨽�ɫ��ϵ
	const ErrorCodeType Error_RoleUser_Exist					= 908;
	// ��ɫ��ҵ���ܴ��ڹ�ϵ
	const ErrorCodeType Error_RoleFunctions_Exist				= 909;
    // ������˶��󲻴���
    const ErrorCodeType Error_ApplyMoney_Unexist                = 910;
	// �˻��͹��ܴ��ڹ�ϵ
	const ErrorCodeType Error_UserAndFunction_Exist				= 911;
    // �����˻������˻�������������㼶
    const ErrorCodeType Error_MaxAllowLevel_Over                = 912;
    // �����˻������˻����������������
    const ErrorCodeType Error_MaxAllowNum_Over                  = 913;
    // �û���ǰ״̬������ò���
    const ErrorCodeType Error_User_Status_Unallow               = 914;
    // ���˻����гֲ�
    const ErrorCodeType Error_User_HasPosition                  = 915;
    // �û����������˿ڵ�¼
    const ErrorCodeType Error_User_Other_Login                  = 916;
    // �û����Գ���Ȩ��
    const ErrorCodeType Error_User_Over_PropRights              = 917;
    // ɾ���ʻ����а󶨶���
    const ErrorCodeType Error_User_Delete_HasBind               = 918;
    // �����˻����ò���ȷ
    const ErrorCodeType Error_User_Parent_Reset                 = 919;
    // ���˻������ʽ�
    const ErrorCodeType Error_User_HasMoney                     = 920;


    // �˻�����ǿƽ,��ֹ����
    const ErrorCodeType Error_User_NoOpen_Force                 = 1001;
    // �˻������޲�,��ֹ����
    const ErrorCodeType Error_User_NoOpen_Limit                 = 1002;
    // ����ͬһ��Ʊ�ֱֲ����޶�,��ֹ����
    const ErrorCodeType Error_User_NoOpen_SameStock             = 1003;
    // ������ҵ��ֱֲ����޶�,��ֹ����
    const ErrorCodeType Error_User_NoOpen_Second_Board          = 1004;
    // ��ֹ���������ҵ��
    const ErrorCodeType Error_User_NoOpen_LossCorp_Buy          = 1005;
    // ��ֹ����������ҵ��
    const ErrorCodeType Error_User_NoOpen_LossCorp_Sell         = 1006;
    // ��ֹ���׿�����ҵ��
    const ErrorCodeType Error_User_NoOpen_LossCorp_Trade        = 1007;
    // ��ֹ������ͣ��
    const ErrorCodeType Error_User_NoOpen_RiseStop_Buy          = 1008;
    // ��ֹ������ͣ��
    const ErrorCodeType Error_User_NoOpen_RiseStop_Sell         = 1009;
    // ��ֹ������ͣ��
    const ErrorCodeType Error_User_NoOpen_RiseStop_Trade        = 1010;
    // ��ֹ�����ͣ��
    const ErrorCodeType Error_User_NoOpen_FallStop_Buy          = 1011;
    // ��ֹ������ͣ��
    const ErrorCodeType Error_User_NoOpen_FallStop_Sell         = 1012;
    // ��ֹ���׵�ͣ��
    const ErrorCodeType Error_User_NoOpen_FallStop_Trade        = 1013;
    // ��ֹ�����¹�
    const ErrorCodeType Error_User_NoOpen_New_Buy               = 1014;
    // ��ֹ�����¹�
    const ErrorCodeType Error_User_NoOpen_New_Sell              = 1015;
    // ��ֹ�����¹�
    const ErrorCodeType Error_User_NoOpen_New_Trade             = 1016;
    // ��ͣ���޷�����
    const ErrorCodeType Error_User_NoOpen_RiseStop              = 1017;
    // ��ͣ���޷����
    const ErrorCodeType Error_User_NoClose_FallStop             = 1018;
    // ��ί�лᵼ�½���ǿƽ��,��ֹ����
    const ErrorCodeType Error_User_Will_NoOpen_Force            = 1019;
    // ��ί�лᵼ�½����޲���,��ֹ����
    const ErrorCodeType Error_User_Will_NoOpen_Limit            = 1020;
}

#endif
