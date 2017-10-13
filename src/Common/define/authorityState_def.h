#pragma once

// ��������
enum  InstitutionManagerColumn : int
{
	IMC_InstitutionManager			= 1,		// ��������
	IMC_InstitutionSet				= 101,		// ��������
	IMC_InstitutionSetQuery			= 10101,	// �������ò�ѯ
	IMC_InstitutionSetAdd			= 10102,	// ������������
	IMC_InstitutionSetModify		= 10103,	// ���������޸�
	IMC_InstitutionSetDek			= 10104,	// ��������ɾ��

	IMC_InstitutionApproval			= 102,		// �������
	IMC_InstitutionApprovalQuery	= 10201,	// �޸���˲�ѯ
	IMC_InstitutionApprovalYes		= 10202,	// �������ͨ��
	IMC_InstitutionApprovalNo		= 10203,	// ������˾ܾ�

	IMC_InstitutionLink				= 103,		// �����ƹ�
	IMC_InstitutionLinkQuery		= 10301,	// �����ƿ���ѯ
	IMC_InstitutionLinkLook			= 10302,	// �鿴��ַ
	IMC_InstitutionLinkCopy			= 10303,	// ������ַ
	IMC_InstitutionLinkPro			= 10304,	// ���ɶ�ά��
	IMC_InstitutionLinkSave			= 10305,	// �����ά��


	IMC_InstitutionAuthority		= 104,		// ����Ȩ�޹���
	IMC_InstitutionAuthorityQuery	= 10401,	// ����Ȩ�޲�ѯ
	IMC_InstitutionAuthorityAdd		= 10402,	// ����Ȩ������
	IMC_InstitutionAuthorityMod		= 10403,	// ����Ȩ���޸�
	IMC_InstitutionAuthorityDel		= 10404,	// ����Ȩ��ɾ��
	IMC_InstitutionAuthorityBind	= 10405,	// ָ�ɻ�����ɫ���ܹ�ϵ
	IMC_InstitutionFunctionQuery	= 10406,	// ��ɫ��ѯ��Ӧ����

	IMC_InstitutionRole				= 105,		// ������ɫ����
	IMC_InstitutionRoleQuery		= 10501,	// ������ɫ��ѯ
	IMC_InstitutionRoleAdd			= 10502,	// ������ɫ����
	IMC_InstitutionRoleMod			= 10503,	// ������ɫ�޸�
	IMC_InstitutionRoleDel			= 10504,	// ������ɫɾ��


	IMC_InstitutionCommission		= 106,		// Ӷ�����
	IMC_InstitutionCommissionQuery	= 10601,	// Ӷ��ͳ�Ʋ�ѯ
	IMC_InstitutionCommissionDetail = 10602,	// Ӷ����ϸ��ѯ

	IMC_InstitutionDivide			= 106,		// �ֳɹ���
	IMC_InstitutionDivideQuery		= 10601,	// �ֳ�ͳ�Ʋ�ѯ
	IMC_InstitutionDivideDetail		= 10602,	// �ֳ���ϸ��ѯ
};

// ����������
enum JuniorTopoTree :int
{
	JTT_TopoTree		= 02,		//����������
	JTT_TopoTreeShowQry = 20101,   // ��ѯϵͳ������
};

// �˻�����
enum AccountMangerColumn : int
{
	AMC_AccountManger		= 3,		// �˻�����

	AMC_ChildList			= 301,		// ���˻��б�
	AMC_ChildQuery			= 30101,	// ���˻���ѯ
	AMC_ChildAdd			= 30102,	// ���˻�����
	AMC_ChildUpdate			= 30103,	// ���˻��޸�
	AMC_ChildDel			= 30104,	// ���˻�ɾ��
	AMC_ChildFundInfo		= 30105,	// ���˻��ʽ���Ϣ
	AMC_ChildOutInMoney		= 30106,	// ��������
	AMC_ChildPosiInfo		= 30107,	// ���ʻ��ֲ�
	AMC_ChildposiClose		= 30108,	// ���ʻ��ֲ�ƽ��
	AMC_ChildPosiAllClose	= 30109,	// ���ʻ�һ��ȫƽ
	AMC_ChildTrade			= 30110,	// ���ʻ��ɽ���¼

	AMC_ChildApprovalList	= 302,		// ���˻�����б�
	AMC_ChildApprovalQuery	= 30201,	// ���˻���˲�ѯ
	AMC_ChildApprovalYes	= 30202,	// ���˻����ͨ��
	AMC_ChildApprovalNo		= 30203,	// ���˻���˾ܾ�

	
	AMC_FundUserList		= 303,		// �ʽ��˻��б�
	AMC_FundUserQuery		= 30301,	// �ʽ��˻���ѯ
	AMC_FundUserAdd			= 30302,	// �ʽ��˻�����
	AMC_FundUserUpdate		= 30303,	// �ʽ��˻��޸�
	AMC_FundUserDel			= 30304,	// �ʽ��˻�ɾ��
	
	AMC_OnlineList			= 304,		// �����û��б�
	AMC_OnlineQuery			= 30401,	// �����û���ѯ

	AMC_ManagerUserList		= 305,		// ����Ա�˻��б�
	AMC_ManagerUserQuery	= 30501,	// ����Ա�˻���ѯ
	AMC_ManagerUserAdd		= 30502,	// ����Ա�˻�����
	AMC_ManagerUserUpdate	= 30503,	// ����Ա�˻��޸�
	AMC_ManagerUserDel		= 30504,	// ����Ա�˻�ɾ��
};

// ���ù���
enum FeeManagerColumn : int
{
	FMC_FeeManagerList		= 4,		// ���ù���
	FMC_FeeManagerQry		= 40101,	// ��ѯ
	FMC_FeeManagerSet		= 40102,	// ���ù�������

};

// ��ع���
enum RiskControlListColumn : int
{
	RCC_RiskControl			= 5,		// ��ع���
	RCC_StockBlackUserSetL	= 501,		// ��Ʊ����������
	RCC_StockBlackUserQuery = 50101,	// ��Ʊ��������ѯ
	RCC_StockBlackUserSet	= 50102,	// ��Ʊ����������

	RCC_ForBidBuySellSetList= 502,		// ��ֹ��������
	RCC_ForBidBuySellQuery	= 50201,	// ��ֹ������ѯ
	RCC_ForBidBuySellSet	= 50202,	// ��ֹ��������

	RCC_PositionRateSetList = 503,		// �ֱֲ�������
	RCC_PositionRateQuery	= 50301,	// �ֱֲ�����ѯ
	RCC_PositionRateSet		= 50302,	// �ֱֲ�������
};

// ��ȫ����
enum  SafeManagerColumn :int
{
	SMC_SafeManager			= 6,		// ��ȫ����
	SMC_BusinessRole		= 6001,		// ҵ���ɫ
	SMC_RoleQuery			= 60101,	// ��ɫ��ѯ
	SMC_RoleAdd				= 60102,	// ��ɫ����
	SMC_RoleModify			= 60103,	// ��ɫ�޸�
	SMC_RoleDelete			= 60104,	// ��ɫɾ��
	SMC_RoleFunctional		= 60105,	// ����<��ɫ-����>��ϵ
	SMC_RoleFunctionalQuery = 60106,	// ��ɫ��ѯ����

	SMC_UserManagerRelation = 602,		// �û���ɫ����
	SMC_QueryUserRelation	= 60201,	// �鿴�û���ɫ��ϵ
	SMC_RoleUserRelationAdd	= 60202,	// ָ�ɽ�ɫ�û���ϵ
	SMC_RoleUserRelationMod	= 60203,	// �޸��û���ɫ��ϵ
	SMC_DelRoleUserRelation = 60204,	// ɾ����ɫ�û���ϵ

};


// �������
enum ReportManagerColumn :int
{
	RMC_ReportManager		= 7,		// �������
	RMC_PositionInfo		= 701,		// �ֲֲ�ѯ
	RMC_PositionInfoQuery	= 70101,	// ��ѯ
	RMC_PositionInfoExport	= 70102,	// ����


	RMC_EntrustInfo			= 702,		// ί����Ϣ
	RMC_EntrustInfoQuery	= 70201,	// ��ѯ
	RMC_EntrustInfoExport	= 70202,	// ����

	RMC_TradeInfo			= 703,		// �ɽ���Ϣ
	RMC_TradeInfoQuery		= 70301,	// ��ѯ
	RMC_TradeInfoExport		= 70302,	// ����

	RMC_FundInfo			= 704,		// �ʽ���Ϣ
	RMC_FundInfoQuery		= 70401,	// ��ѯ
	RMC_FundInfoExport		= 70402,	// ����

	RMC_OutInMoneyInfo		= 705,		// �ʽ���ˮ�б�
	RMC_OutInMoneyQuery		= 70501,	// �ʽ���ˮ��ѯ
	RMC_OutInMoneyExport	= 70502,	// �ʽ���ˮ����

	RMC_DeliveryInfo		= 706,		// �����б� ======> ��ʱ����
	RMC_DeliveryInfoQuery	= 70601,	// ��ѯ
	RMC_DeliveryInfoExport	= 70602,	// ����

};

// �ʲ����
enum  MoneyMonitorColumn :int
{
	MMC_MoneyMonitor		= 8,		// �ʲ����

	MMC_TimeMoneyMonitor	= 801,		// ʵʱ�ʲ����
	MMC_ChildMoneyMonitor	= 80101,	// ʵʱ�ʲ���ز�ѯ
	

	MMC_ChildTradeInfo		= 802,		// ���˻�ʵʱ�ɽ���¼
	MMC_QueryTradeInfo		= 80201,	// ��ѯ����ʾ��

	MMC_SumPositionInfo		= 803,		// ϵͳ�ֲܳ�ͳ��
	MMC_QuerySumPosiInfo	= 80301,	// ��ѯ����ѯ��

	MMC_TimeWarnInfo		= 804,		// ʵʱԤ��֪ͨ
	MMC_QueryWarnInfo		= 80401,	// ��ѯ����ʾ��
};


// �������
enum OutInMoneyApproval :int
{
	OIMA_OutInMoneyApproval		= 9,		// �ʽ����
	OIMA_InMoneyApprovalList	= 901,		// ���˻��������	======> ��ʱ����
	OIMA_InMoneyApprovalQuery	= 90101,	// ��ѯ
	OIMA_InMoneyApprovalYes		= 90102,	// ���ͨ��
	OIMA_InMoneyApprovalNo		= 90103,	// ��˾ܾ�

	OIMA_OutMoneyApprovalList	= 902,		// ����ʽ����		======> ��ʱ����
	OIMA_OutMoneyApprovalQuery	= 90201,	// ��ѯ
	OIMA_OutMoneyApprovalYes	= 90202,	// ���ͨ��
	OIMA_OutMoneyApprovalNo		= 90203,	// ��˾ܾ�

	OIMA_FinaceApprovalList		= 903,		// �����ʽ����
	OIMA_FinaceApprovalQuery	= 90301,	// ��ѯ
	OIMA_FinaceApprovalYes		= 90302,	// ���ͨ��
	OIMA_FinaceApprovalNo		= 90303,	// ��˾ܾ�
};

// ϵͳ����
enum SystemManager :int
{
	SM_SystemManager			= 10,		// ϵͳ����
	SM_PasswordChange			= 100101,	// �����޸�
};