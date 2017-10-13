/*************************************************
Copyright (C), 2017, HX Tech Co., Ltd.
File name:      params_declare.h
Author:			XuYC
Version:
Date:
Description:    �ṩͳһ�Ľṹ���������,����ά�������ָ��
*************************************************/

#ifndef __PARAMS_DECLARE_H__
#define __PARAMS_DECLARE_H__

#include <string>

namespace AllTrade {

    //GUID����
    typedef char	GUIDType[65];

    //��֤��Ϣ
    typedef char    CertInfoType[401];

    //�汾��Ϣ
    typedef char    VersionType[51];

    //��¼IP��Ϣ
    typedef char    LoginIpType[41];

    //Ӧ�ó���ID
    typedef char    AppIDType[101];

    //��½������Ϣ����Ҫ����mac��ַ
    typedef char    MachineInfoType[201];

    typedef unsigned char  u_char;

    //��������
    typedef unsigned int    SizeType;

    ///////////////////////////////////////////////////////////////////////////
    //���ں�ʱ������(��ʽ yyyy-MM-dd hh:mm:ss)
    typedef char            DateTimeType[21];
    typedef std::string     PDateTimeType;
    //��������(��ʽ yyyy-MM-dd)
    typedef char		    DateType[11];
    typedef std::string     PDateType;
    //ʱ������(��ʽ hh:mm:ss)
    typedef char		    TimeType[11];
    typedef std::string     PTimeType;

    ///////////////////////////////////////////////////////////////////////////
    //���������(0-��ʾ�ɹ�),���protocol_error.h
    typedef int				ErrorCodeType;

    //������Ϣ
    typedef char			ErrorTextType[51];
    typedef std::string     PErrorTextType;

    //��ע��Ϣ
    typedef char			RemarkTextType[1025];
    typedef std::string     PRemarkTextType;

    //////////////////////////////////////////////////////////////////////////
    // �˻�����
    enum E_ACCOUNT_PROP
    {
        EAP_Invalid = -1,
        EAP_Root,	            // ���˻�
        EAP_Agency,             // �����˻�
        EAP_Risker,             // ����˻�
        EAP_Manager,            // �����˻�
        EAP_Trader,             // �����˻�
        EAP_Funder,             // �ʽ��˻�
        EAP_MAX,
    };
    // �˻�����
    enum E_ACCOUNT_TYPE
    {
        EAT_Invalid = -1,
        EAT_Simulation,         // ģ���˻�
        EAT_Real,               // ʵ���˻�
        EAT_SimuReal,           // ģ���ʵ���˻�
        EAT_MaxCount
    };
    // �����˻�Ȩ�޷�ʽ
    enum E_PERMISSION_TYPE
    {
        EPT_Invalid = -1,
        EPT_AUTO,               // �Զ�
        EPT_MANUAL,             // �ֶ�
        EPT_MaxCount
    };
    // �˻�״̬
    enum E_ACCOUNT_STATUS
    {
        EAS_Invalid = -1,
        EAS_Check_Create,       // �������������
        EAS_Check_Unpass,       // ��˾ܾ�
        EAS_OverTime,           // �ѹ���,��ֹ��¼
        EAS_Check_Delete,       // ɾ�����������
        EAS_Deleted,            // �˻���ɾ������������
        EAS_Using,		        // ͨ�����ʹ����
        EAS_Warning,		    // �쳣������(���ڹ���/���/�����˻������쳣��ʾ)
        EAS_StopOpen,           // ���/����,��ֹ����
        EAS_Freezing,           // ������,��ֹ����
        EAS_MaxCount
    };

    //////////////////////////////////////////////////////////////////////////
    // �����˻�����
    enum E_AGENCY_PROP
    {
        EAP_INVALID = -1,
        EAP_PROXY,              // �������˻�
        EAP_COMMON,             // �����˻�
    };

    ///////////////////////////////////////////////////////////////////////////
    // �����ʽ
    enum OIMM_Change_Type
    {
        OIMM_Type_Invalid = -1,
        OIMM_In_Deposit,		// ���Ӻ��ʽ�
        OIMM_In_Equipment,		// �������ʽ�
        OIMM_In_BlueAdd,		// �ʽ�����
        OIMM_Out_Deposit,		// ���Ӻ��ʽ�
        OIMM_Out_Equipment,		// �������ʽ�
        OIMM_Out_RedSub,		// �ʽ���
        OIMM_Type_Num
    };

    //�����ʽ������ˮID����
    typedef long long				ApplyMoneyIDType;
//     typedef std::string				PApplyMoneyIDType;
    // �ʽ����״̬
    enum E_APPLY_MONEY_STATUS
    {
        EAMS_Invalid = -1,
        EAMS_Check_Create,       // �������������
        EAMS_Check_Unpass,       // ��˾ܾ�
        EAMS_Using,		         // ͨ�����
        EAMS_MaxCount
    };

    // �ʽ�䶯��ʽ
    enum Money_Change_Type
    {
        MC_Type_Invalid = -1,
        MC_In_Deposit,		            // ���Ӻ��ʽ�
        MC_In_Equipment,                // �������ʽ�
        MC_In_BlueAdd,		            // �ʽ�����
        MC_Out_Deposit,		            // ���Ӻ��ʽ�
        MC_Out_Equipment,               // �������ʽ�
        MC_Out_RedSub,		            // �ʽ���
        MC_Order_Freeze,                // ����ί�ж����ʽ�,�����ʽ����
        MC_Order_Cancel,                // ����,�����ʽ𷵻�
        MC_Trade_Open,                  // ���ֳɽ�(�ɽ���)
        MC_Trade_Open_Fee,              // ���ֳɽ�����Ӷ��������
        MC_Trade_Open_TransferFee,      // ���ֳɽ�������
        MC_Trade_Open_InfoMatchFee,     // ���ֳɽ���Ϣ��Ϸ�
        MC_Trade_Thaw,                  // ί�ж����ʽ𷵻�
        MC_Trade_Close,                 // ƽ�ֳɽ��ʽ𷵻�(�ɽ���)
        MC_Trade_Close_Fee,             // ƽ�ֳɽ�����Ӷ��������
        MC_Trade_Close_TransferFee,     // ƽ�ֳɽ�������
        MC_Trade_Close_InfoMatchFee,    // ƽ�ֳɽ���Ϣ��Ϸ�
        MC_Trade_Close_StampFee,        // ƽ�ֳɽ�ӡ��˰
        MC_Commission,                  // ϵͳ��Ӷ
        MC_Money_Settle,                // ϵͳ�ʽ����,��Ϊ����ȡ�ʽ�
        MC_Profit,                      // ϵͳ�ֳɳ�ȡ
        MC_Type_Num
    };

    // ������Ӷ/�ֳɵ��ʽ�䶯��ʽ
    enum Agency_Money_Change_Type
    {
        AMCT_Invalid = -1,
        AMCT_InfoMatch_Commission,      // ��Ϣ��Ϸ�Ӷ��
        AMCT_Exchange_Commission,       // ������Ӷ��
        AMCT_Trade_Profit,              // ӯ���ֳ�
    };


    //����ID����
    typedef GUIDType				CurrencyIDType;
    typedef std::string				PCurrencyIDType;
    //���ұ������
    typedef char					CurrencyCodeType[11];
    typedef std::string				PCurrencyCodeType;
    //������������
    typedef char					CurrencyNameType[21];
    typedef std::string				PCurrencyNameType;

    ///////////////////////////////////////////////////////////////////////////
    //����Ա����
    enum class OperatorTradeType : int
    {
        OPERATOR_TRADE_Invalid = -1,
        OPERATOR_TRADE_PC,              // PC�˿ͻ��Է���
        OPERATOR_TRADE_APP,             // APP�˿ͻ��Է���
        OPERATOR_TRADE_MC,              // ��̨��ض˷���
        OPERATOR_TRADE_RC,              // ��̨��ض˷���
        OPERATOR_TRADE_SYSTEM,          // ϵͳ����
    };

    ///////////////////////////////////////////////////////////////////////////
    //ί�н���ģʽ����,�Ƿ�ͬ������ʵ������
    enum class OrderTradeModeType : int
    {
        ORDERTRADE_MODE_Invalid = -1,
        ORDERTRADE_MODE_SYNC,             // ͬ����������
        ORDERTRADE_MODE_SIMULATE,         // ͬ�������潻�׶�
    };

    ///////////////////////////////////////////////////////////////////////////
    //������ID����
    typedef GUIDType				ExchangeIDType;
    typedef std::string				PExchangeIDType;
    //��������������
    typedef char					ExchangeCodeType[11];
    typedef std::string				PExchangeCodeType;
    //��������������
    typedef char					ExchangeNameType[31];
    typedef std::string				PExchangeNameType;

    ///////////////////////////////////////////////////////////////////////////
    //�ӿ���������
    enum class ApiTypeType : int
    {
        APIType_TYPE_Invalid = -1,
        APIType_TYPE_CTP = 0,
        APIType_TYPE_ESUNNY,
        APIType_TYPE_IB,
        APIType_TYPE_SP,
    };

    ///////////////////////////////////////////////////////////////////////////
    //��Ʒ��������
    enum class CommodityTypeType : int
    {
        COMMODITY_TYPE_Invalid = -1,
        COMMODITY_TYPE_STOCK = 0,   // ��Ʊ
        COMMODITY_TYPE_FUTURE_F,    // �����ڻ�
        COMMODITY_TYPE_FUTURE_C,    // �����ڻ�
        COMMODITY_TYPE_OPTION,      // ��Ȩ
        COMMODITY_TYPE_GOODS,       // �ֻ�
		COMMODITY_TYPE_MARGIN,      // ��Ʊ��ȯ
    };

    ///////////////////////////////////////////////////////////////////////////
    //Ʒ��ID����,����û��Ʒ��
    typedef GUIDType				ProductIDType;
    typedef std::string				PProductIDType;
    //Ʒ�ִ�������
    typedef char					ProductCodeType[11];
    typedef std::string				PProductCodeType;
    //Ʒ����������
    typedef char					ProductNameType[21];
    typedef std::string				PProductNameType;

    ///////////////////////////////////////////////////////////////////////////
    //��ԼID����
    typedef GUIDType				ContractIDType;
    typedef std::string				PContractIDType;
    //��Լ��������
    typedef char					ContractCodeType[21];
    typedef std::string				PContractCodeType;
    //��Լ��������
    typedef char					ContractNameType[21];
    typedef std::string				PContractNameType;
    //��Լ����������(��Լ���м��쵽��), -1��ʾ����ʱ��
    typedef int						ContractLastDays;
    //��Ʊ��Լ��ʾ(ҵ��)��������, S/ST/*ST...
    typedef char				    DisplayPropType[21];
    typedef std::string				PDisplayPropType;
    //��Ʊ��Լ�����������, ����/��ͨ...
    typedef char				    PlatePropType[21];
    typedef std::string				PPlatePropType;
    //��Ʊ��Լƴ������
    typedef char				    ContractPYCodeType[21];
    typedef std::string				PContractPYCodeType;
    // ��Ʊ��Լ����״̬
    enum class StockStatusType : int
    {
        STOCKSTATUS_Invalid = -1,
        STOCKSTATUS_L = 0,      // ����
        STOCKSTATUS_S,          // ��ͣ
        STOCKSTATUS_DE,         // ��ֹ����
        STOCKSTATUS_UN,         // δ����
    };
    enum class DisplayPropTypeType :int{
        DPTT_Invalid = -1,
        DPTT_Normal,
        DPTT_S,
        DPTT_ST,
        DPTT_SST,
        DPTT_StarST,
        DPTT_SStarST,
    };
    // ��Ʊ��Լ����״̬
    enum class QuoteStatusType : int
    {
        QUOTESTATUS_Invalid = -1,
        QUOTESTATUS_Normal = 0, // ����
        QUOTESTATUS_Close,      // ����
        QUOTESTATUS_Stop,       // ͣ��
    };

    ///////////////////////////////////////////////////////////////////////////
    //��Ʊ��Լ������Ʊ����, A��/B��...
    enum class StockAreaType : int
    {
        STOCKAREA_TYPE_Invalid = -1,
        STOCKAREA_TYPE_A = 0,
        STOCKAREA_TYPE_B,
        STOCKAREA_TYPE_H,
        STOCKAREA_TYPE_N,
        STOCKAREA_TYPE_S,
    };
    enum class StockPlateAreaType : int
    {
        SPAT_Invalid = -1,
        SPAT_Main_Board = 0,    // �����
        SPAT_Second_Board,      // ��ҵ���
        SPAT_SME_Board,         // ��С��
        SPAT_NEEQ_Board,        // ������
    };

    ///////////////////////////////////////////////////////////////////////////
    //ί�б������(ÿ�����׷�������Ψһ��־,�ɷ���������)
    typedef GUIDType				OrderIDType;
    typedef std::string				POrderIDType;
    //����ί�б������(��������ȫ��Ψһ��־,UserID+GUID)
    typedef char					OrderStreamType[129];
    typedef std::string				POrderStreamType;
    //����ί�б������(ÿ�����׷�������Ψһ��־,�ɷ���������)
    typedef GUIDType				OrderRefType;
    typedef std::string				POrderRefType;
    //Ӱ�Ӷ������(ÿ�����׷�������Ψһ��־,�ɷ���������)
    typedef GUIDType				ShadowOrderIDType;
    typedef std::string				PShadowOrderIDType;
    //Ӱ�ӳɽ����(ÿ�����׷�������Ψһ��־,�ɷ���������)
    typedef GUIDType				ShadowTradeIDType;
    typedef std::string				PShadowTradeIDType;
    //ϵͳ�������(�ϼ�����������Ψһ��־,��ͬ���������ܻ��ظ�)
    typedef GUIDType				SystemIDType;
    typedef std::string				PSystemIDType;
    //�ɽ����(ÿ�����׷�������Ψһ��־,�ɷ���������)
    typedef GUIDType				TradeIDType;
    typedef std::string				PTradeIDType;
    //�ֱֲ��(ÿ�����׷�������Ψһ��־,�ɷ���������)
    typedef GUIDType				PositionIDType;
    typedef std::string				PPositionIDType;

    // ҵ������(ÿ�����׷�������Ψһ��־,�ɷ���������)
    typedef char					BussnessName[64];
    typedef std::string				PBussnessName;
    // ��־����(ÿ�����׷�������Ψһ��־,�ɷ���������)
    typedef char					LogContent[200];
    typedef std::string				PLogContent;
    // ��������(ÿ�����׷�������Ψһ��־,�ɷ���������)
    typedef char					FunctionName[64];
    typedef std::string				PFunctionName;
    // ��ɫ����(ÿ�����׷�������Ψһ��־,�ɷ���������)
    typedef char					RolesName[24];
    typedef std::string				PRolesName;

    // Ȩ��ҵ��(ÿ�����׷�������Ψһ��־,�ɷ���������)
    typedef char					IsHide;
    const IsHide				    IsHide_Hide = 0x00;
    const IsHide				    IsHide_NoIsHide = 0x01;

    // ��ɫ����(ÿ�����׷�������Ψһ��־,�ɷ���������)
    typedef char					IsSort;
    const IsSort				    IsSort_Sort = 0x00;
    const IsSort				    IsSort_NoSort = 0x01;

    // Ȩ�޽�ɫ(ÿ�����׷�������Ψһ��־,�ɷ���������)
    enum E_RolesType
    {
        ERT_Invalid = -1,
        ERT_Institution,            // ����
        ERT_Manager,				// ����Ա
        ERT_MaxCount
    };

	// ��������(ÿ�����׷�������Ψһ��־,�ɷ���������)
	enum E_OperationType
	{
		EOT_Invalid = -1,
		EOT_IsOperation,            // �ɲ���
		EOT_IsNotOperation,			// ���ɲ���
		EOT_MaxCount
	};

    //////////////////////////////////////////////////////////////////
    //�������˻���Ϣ

    ///////////////////////////////////////////////////////////////////////////
    //�û�ID����
    typedef GUIDType				UserIDType;
    typedef std::string				PUserIDType;

    //�˻���¼����
    typedef char                    LoginNameType[51];
    typedef std::string				PLoginNameType;
    //�˻�����
    typedef char                    AccountNameType[51];
    typedef std::string				PAccountNameType;
    //��¼����
    typedef char                    LoginPasswordType[25];
    typedef std::string				PLoginPasswordType;
    //�ǳ�
    typedef char                    NickNameType[51];
    typedef std::string				PNickNameType;
    //��ʵ����
    typedef char                    RealNameType[51];
    typedef std::string				PRealNameType;
    //�ֻ���
    typedef char                    PhoneNumberType[18];
    typedef std::string				PPhoneNumberType;
    //���֤��
    typedef char                    IdentityIDType[20];
    typedef std::string				PIdentityIDType;
    //������
    typedef char                    BankNameType[100];
    typedef std::string				PBankNameType;
    //���п���
    typedef char                    BankCardNoType[50];
    typedef std::string				PBankCardNoType;

    //�ƹ㿪������
    typedef char                    PopularizeLinkType[1025];
    typedef std::string				PPopularizeLinkType;

    //ʵ���˻��ӿ�����
    typedef char                    HedgeApiType[15];
    typedef std::string				PHedgeApiType;

    //�㼶����
    typedef char                    LevelNameType[24];
    typedef std::string				PLevelNameType;

    // ʵ���˻���Ӧ��˾����
    typedef char                    FundCompanyType[51];
    typedef std::string				PFundCompanyType;

    //�ʽ���������
    typedef char					MoneyStreamType[65];
    typedef std::string				PMoneyStreamType;


    ///////////////////////////////////////////////////////////////////////////
    //ί������
    enum class OrderTypeType : int
    {
        ORDER_TYPE_Invalid = -1,
        ORDER_TYPE_LIMIT = 0,   // �޼�
        ORDER_TYPE_MARKET,      // �м�
        ORDER_TYPE_STOP_LIMIT,  // �޼�ֹ��
        ORDER_TYPE_STOP_MARKET, // �м�ֹ��
    };

    ///////////////////////////////////////////////////////////////////////////
    //ί��ģʽ����
    enum class OrderModeType : int
    {
        ORDER_MODE_Invalid = -1,
        ORDER_MODE_FOK = 0,     // ����ȫ���ɽ������Զ�����ָ��(FOKָ��)��ָ���޶���λ�´�ָ������ָ���������걨����δ��ȫ���ɽ�����ָ���������걨�����Զ���ϵͳ������
        ORDER_MODE_FAK,         // �����ɽ�ʣ��ָ���Զ�����ָ��(FAKָ��)��ָ���޶���λ�´�ָ������ָ���²����걨�����ɽ�����ָ����ʣ���걨�����Զ���ϵͳ����
        ORDER_MODE_GFD,         // ������Ч
        ORDER_MODE_GTC,         // ȡ��ǰ��Ч
        ORDER_MODE_GTD,         // ָ������ǰ��Ч
    };

    ///////////////////////////////////////////////////////////////////////////
    //��������
    enum class DirectType : int
    {
        DIRECT_Invalid = -1,
        DIRECT_BUY,         // ����
        DIRECT_SELL,        // ����
		DIRECT_Margin,      // ��ȯ
		DIRECT_BackMargin,  // ��ȯ
    };

    ///////////////////////////////////////////////////////////////////////////
    //��ƽ����
    enum class OffsetType : int
    {
        OFFSET_Invalid = -1,
        OFFSET_OPEN = 0,        // ����
        OFFSET_COVER,           // ƽ��
        OFFSET_COVER_TODAY,     // ƽ��
    };

    ///////////////////////////////////////////////////////////////////////////
    //ί��״̬����
    enum class OrderStateType : int
    {
        ORDER_STATE_Invalid = -1,
        ORDER_STATE_FAIL = 0,       // ָ��ʧ��
        ORDER_STATE_SUPPENDING,     // �ύ��
        ORDER_STATE_SUPPENDED,      // �ѹ���
        ORDER_STATE_ACCEPT,         // ������,����������������
        ORDER_STATE_QUEUED,         // ���Ŷ�,����������/���׶���/�ύ��������
        ORDER_STATE_DELETEING,      // ������
        ORDER_STATE_PARTDELETED,    // ���ֳ���
        ORDER_STATE_DELETED,        // ��ȫ����
        ORDER_STATE_PARTFINISHED,   // ���ֳɽ�
        ORDER_STATE_FINISHED,       // ��ȫ�ɽ�
    };
    ///////////////////////////////////////////////////////////////////////////
    //ί��״̬˵������
    typedef int					    OrderStateExplainType;
    const OrderStateExplainType     Invalid_OrderState_Explain = -1;
    const OrderStateExplainType     OSET_Err_EffectVol = -2;

    const OrderStateExplainType     OSET_Err_No = 0;

    ///////////////////////////////////////////////////////////////////////////
    //���տ���������ʾ����
    enum RiskControlType : int
    {
        RCT_Invalid = 0,
        RCT_WarningLine,    // ������
        RCT_ForceLine,      // ǿƽ��
        RCT_LimitLine,      // �޲���
    };

    //////////////////////////////////////////////////////////////////////////
    // ��ֹ���׷�ع�������
    enum ForbidTradeType : int
    {
        FTT_Invalid = -1,
        FTT_LossCorporateStock,	// ������ҵ��Ʊ
        FTT_RiseStopStock,		// ��ǰ��ͣ��Ʊ
        FTT_FallStopStock,		// ��ǰ��ͣ��Ʊ
        FTT_NewStock,			// �¹�(����20��)
    };
    // ��ֹ���׷�ز�������
    enum ForbidTradeOperatorType : int
    {
        FTOT_Invalid = -1,
        FTOT_AllowTrade,		// ��������
        FTOT_AllowBuy,			// ֻ������
        FTOT_AllowSell,			// ֻ������
        FTOT_ForbidTrade,		// ��ֹ����
    };

    //////////////////////////////////////////////////////////////////////////
    // �ֱֲ�����������
    enum PositionRateType : int
    {
        PRT_Invalid = -1,
        PRT_SameStock,          // ͬһ��Ʊ�ֱֲ������������ʲ��ı���
//         PRT_SamePlateArea,		// ͬһ��ҵ��鲻�������ʲ��ı���
        PRT_Second_Board,		// ��ҵ��ֲֲ������ֱֲܳ���
    };

}

#endif