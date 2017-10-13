/*************************************************
Copyright (C), 2017, HX Tech Co., Ltd.
File name:      table_define.h
Author:			XuYC
Version:
Date:
Description:    �ṩ����Ľṹ�嶨��,�ӿ�����ٶ�
                ע:�ֽ׶θ���䲻Ҫ��������,���ں�����ֲ�ǹ�ϵ�����ݿ�,���ֹؼ����ݺ���ͳһ�޸�Ϊ��ϵ�����ݿ�Ĺ����ṹ
*************************************************/

#ifndef __TABLE_DEFINE_H__
#define __TABLE_DEFINE_H__

namespace OperationManager {

#pragma region �û���Ϣ��
    //////////////////////////////////////////////////////////////////////////
    enum AgencyUserTable : int {
        AgyUT_UserID = 0,
        AgyUT_CreatorID,
        AgyUT_ParentID,
        AgyUT_LoginName,
        AgyUT_NickName,
        AgyUT_Password,
        AgyUT_AccountName,
        AgyUT_FunderID,
        AgyUT_Level,
        AgyUT_AccountType,
        AgyUT_AccountStatus,
        AgyUT_PermissionType,
        AgyUT_PopularizeLink,
        AgyUT_RealName,
        AgyUT_PhoneNumber,
        AgyUT_IdentityID,
        AgyUT_RegistDatetime,
        AgyUT_UpdateDatetime,
        AgyUT_VaildDatetime,
        AgyUT_AgyProp,
        AgyUT_AllowMaxLevel,
        AgyUT_AllowMaxNum,
        AgyUT_Max
    };
    const char* const gszAgencyUserTableName = "agency_users";
    const char* const gszAgencyUserColName[AgyUT_Max] = {
        "user_id",
        "create_id",
        "parent_id",
        "login_name",
        "nick_name",
        "password",
        "account_name",
        "funder_id",
        "level",
        "type",
        "status",
        "permission",
        "agent_link",
        "real_name",
        "phone_number",
        "identity",
        "regist_datetime",
        "update_datetime",
        "vaild_datetime",
        "mgr_prop",
        "allow_max_level",
        "allow_max_num",
    };
    const char* const gszAgencyUserCreateColType[AgyUT_Max] = {
        "varchar(64) COLLATE utf8_bin NOT NULL DEFAULT '' COMMENT '�˻���ʶ(�û�ID)��ϵͳ�ڲ�ʹ��' primary key",
        "varchar(64) COLLATE utf8_bin DEFAULT '' COMMENT '�������˻���ʶ��ϵͳ�ڲ�ʹ��'",
        "varchar(64) COLLATE utf8_bin DEFAULT '' COMMENT '�����˻���ʶ(�û�ID)��ϵͳ�ڲ�ʹ��'",
        "varchar(50) COLLATE utf8_bin NOT NULL DEFAULT '' COMMENT '��¼��'",
        "varchar(50) COLLATE utf8_bin DEFAULT '' COMMENT '�ǳ�'",
        "varchar(24) COLLATE utf8_bin NOT NULL DEFAULT '' COMMENT '����'",
        "varchar(50) COLLATE utf8_bin NOT NULL DEFAULT '' COMMENT '�˻���'",
        "varchar(64) COLLATE utf8_bin DEFAULT '' COMMENT '��Ӧ�ʽ��˻���ʶ(�û�ID)��ϵͳ�ڲ�ʹ��'",
        "int NOT NULL DEFAULT '-1' COMMENT '�㼶'",
        "int(2) NOT NULL DEFAULT '-1' COMMENT '�˻�����'",
        "int(2) NOT NULL DEFAULT '-1' COMMENT '�˻�״̬'",
        "int(2) NOT NULL DEFAULT '-1' COMMENT '�˻�Ȩ�޿���ģʽ'",
        "varchar(1024) COLLATE utf8_bin DEFAULT '' COMMENT '�ƹ�����'",
        "varchar(50) COLLATE utf8_bin DEFAULT '' COMMENT '��ʵ����'",
        "varchar(18) COLLATE utf8_bin DEFAULT '' COMMENT '�ֻ���'",
        "varchar(20) COLLATE utf8_bin DEFAULT '' COMMENT '���֤��'",
        "DATETIME COMMENT '����ʱ��'",
        "DATETIME COMMENT '����ʱ��'",
        "DATETIME COMMENT '��Ч��ʱ��'",
        "int(2) NOT NULL DEFAULT '-1' COMMENT '�����˻�����'",
        "int NOT NULL DEFAULT '-1' COMMENT '������������㼶'",
        "int NOT NULL DEFAULT '-1' COMMENT '���������������'",
    };

    enum TradeUserTable : int {
        TUT_UserID = 0,
        TUT_CreatorID,
        TUT_ParentID,
        TUT_LoginName,
        TUT_NickName,
        TUT_Password,
        TUT_AccountName,
        TUT_FunderID,
        TUT_Level,
        TUT_AccountProp,
        TUT_AccountType,
        TUT_AccountStatus,
        TUT_PermissionType,
        TUT_PopularizeLink,
        TUT_RealName,
        TUT_PhoneNumber,
        TUT_IdentityID,
        TUT_RegistDatetime,
        TUT_UpdateDatetime,
        TUT_VaildDatetime,
		TUT_AuditorName,
		TUT_AuditorDatetime,
        TUT_Max
    };
    const char* const gszTradeUserTableName = "trade_users";
    const char* const gszTradeUserColName[TUT_Max] = {
        "user_id",
        "create_id",
        "parent_id",
        "login_name",
        "nick_name",
        "password",
        "account_name",
        "funder_id",
        "level",
        "prop",
        "type",
        "status",
        "permission",
        "agent_link",
        "real_name",
        "phone_number",
        "identity",
        "regist_datetime",
        "update_datetime",
        "vaild_datetime",
		"auditor_name",
		"auditor_time",
    };
    const char* const gszTradeUserCreateColType[TUT_Max] = {
        "varchar(64) COLLATE utf8_bin NOT NULL DEFAULT '' COMMENT '�˻���ʶ(�û�ID)��ϵͳ�ڲ�ʹ��' primary key",
        "varchar(64) COLLATE utf8_bin NOT NULL DEFAULT '' COMMENT '�������˻���ʶ��ϵͳ�ڲ�ʹ��'",
        "varchar(64) COLLATE utf8_bin NOT NULL DEFAULT '' COMMENT '�����˻���ʶ(�û�ID)��ϵͳ�ڲ�ʹ��'",
        "varchar(50) COLLATE utf8_bin NOT NULL DEFAULT '' COMMENT '��¼��'",
        "varchar(50) COLLATE utf8_bin NOT NULL DEFAULT '' COMMENT '�ǳ�'",
        "varchar(24) COLLATE utf8_bin NOT NULL DEFAULT '' COMMENT '����'",
        "varchar(50) COLLATE utf8_bin NOT NULL DEFAULT '' COMMENT '�˻���'",
        "varchar(64) COLLATE utf8_bin DEFAULT '' COMMENT '��Ӧ�ʽ��˻���ʶ(�û�ID)��ϵͳ�ڲ�ʹ��'",
        "int NOT NULL DEFAULT '-1' COMMENT '�㼶'",
        "int(2) NOT NULL DEFAULT '-1' COMMENT '�˻�����'",
        "int(2) NOT NULL DEFAULT '-1' COMMENT '�˻�����'",
        "int(2) NOT NULL DEFAULT '-1' COMMENT '�˻�״̬'",
        "int(2) NOT NULL DEFAULT '-1' COMMENT '�˻�Ȩ�޿���ģʽ'",
        "varchar(1024) COLLATE utf8_bin NOT NULL DEFAULT '' COMMENT '�ƹ�����'",
        "varchar(50) COLLATE utf8_bin DEFAULT '' COMMENT '��ʵ����'",
        "varchar(18) COLLATE utf8_bin DEFAULT '' COMMENT '�ֻ���'",
        "varchar(20) COLLATE utf8_bin DEFAULT '' COMMENT '���֤��'",
        "DATETIME COMMENT '����ʱ��'",
        "DATETIME COMMENT '����ʱ��'",
        "DATETIME COMMENT '��Ч��ʱ��'",
		"varchar(64) COLLATE utf8_bin NOT NULL DEFAULT '' COMMENT '����ߣ�ϵͳ�ڲ�ʹ��'",
		"DATETIME COMMENT '���ʱ��'",
    };

    //////////////////////////////////////////////////////////////////////////
    enum ManagerUserTable : int {
        MgrUT_UserID = 0,
        MgrUT_CreatorID,
        MgrUT_ParentID,
        MgrUT_LoginName,
        MgrUT_NickName,
        MgrUT_Password,
        MgrUT_AccountName,
        MgrUT_Level,
        MgrUT_AccountProp,
        MgrUT_AccountType,
        MgrUT_AccountStatus,
        MgrUT_PermissionType,
        MgrUT_PopularizeLink,
        MgrUT_RealName,
        MgrUT_PhoneNumber,
        MgrUT_IdentityID,
        MgrUT_RegistDatetime,
        MgrUT_UpdateDatetime,
        MgrUT_VaildDatetime,
        MgrUT_AllowMaxLevel,
        MgrUT_AllowMaxNum,
        MgrUT_Max
    };
    const char* const gszManagerUserTableName = "manager_users";
    const char* const gszManagerUserColName[MgrUT_Max] = {
        "user_id",
        "create_id",
        "parent_id",
        "login_name",
        "nick_name",
        "password",
        "account_name",
        "level",
        "prop",
        "type",
        "status",
        "permission",
        "agent_link",
        "real_name",
        "phone_number",
        "identity",
        "regist_datetime",
        "update_datetime",
        "vaild_datetime",
        "allow_max_level",
        "allow_max_num",
    };
    const char* const gszManagerUserCreateColType[MgrUT_Max] = {
        "varchar(64) COLLATE utf8_bin NOT NULL DEFAULT '' COMMENT '�˻���ʶ(�û�ID)��ϵͳ�ڲ�ʹ��' primary key",
        "varchar(64) COLLATE utf8_bin DEFAULT '' COMMENT '�������˻���ʶ��ϵͳ�ڲ�ʹ��'",
        "varchar(64) COLLATE utf8_bin DEFAULT '' COMMENT '�����˻���ʶ(�û�ID)��ϵͳ�ڲ�ʹ��'",
        "varchar(50) COLLATE utf8_bin NOT NULL DEFAULT '' COMMENT '��¼��'",
        "varchar(50) COLLATE utf8_bin DEFAULT '' COMMENT '�ǳ�'",
        "varchar(24) COLLATE utf8_bin NOT NULL DEFAULT '' COMMENT '����'",
        "varchar(50) COLLATE utf8_bin NOT NULL DEFAULT '' COMMENT '�˻���'",
        "int NOT NULL DEFAULT '-1' COMMENT '�㼶'",
        "int(2) NOT NULL DEFAULT '-1' COMMENT '�˻�����'",
        "int(2) NOT NULL DEFAULT '-1' COMMENT '�˻�����'",
        "int(2) NOT NULL DEFAULT '-1' COMMENT '�˻�״̬'",
        "int(2) NOT NULL DEFAULT '-1' COMMENT '�˻�Ȩ�޿���ģʽ'",
        "varchar(1024) COLLATE utf8_bin DEFAULT '' COMMENT '�ƹ�����'",
        "varchar(50) COLLATE utf8_bin DEFAULT '' COMMENT '��ʵ����'",
        "varchar(18) COLLATE utf8_bin DEFAULT '' COMMENT '�ֻ���'",
        "varchar(20) COLLATE utf8_bin DEFAULT '' COMMENT '���֤��'",
        "DATETIME COMMENT '����ʱ��'",
        "DATETIME COMMENT '����ʱ��'",
        "DATETIME COMMENT '��Ч��ʱ��'",
        "int NOT NULL DEFAULT '-1' COMMENT '������������㼶'",
        "int NOT NULL DEFAULT '-1' COMMENT '���������������'",
    };

    //////////////////////////////////////////////////////////////////////////
    enum FunderUserTable : int {
        FUT_UserID = 0,
        FUT_CreatorID,
        FUT_ParentID,
        FUT_LoginName,
        FUT_NickName,
        FUT_Password,
        FUT_AccountName,
        FUT_Level,
        FUT_AccountProp,
        FUT_AccountType,
        FUT_AccountStatus,
        FUT_PermissionType,
        FUT_PopularizeLink,
        FUT_RealName,
        FUT_PhoneNumber,
        FUT_IdentityID,
        FUT_FunderCompany,
        FUT_RegistDatetime,
        FUT_UpdateDatetime,
        FUT_VaildDatetime,
        FUT_Max
    };
    const char* const gszFunderUserTableName = "funder_users";
    const char* const gszFunderUserColName[FUT_Max] = {
        "user_id",
        "create_id",
        "parent_id",
        "login_name",
        "nick_name",
        "password",
        "account_name",
        "level",
        "prop",
        "type",
        "status",
        "permission",
        "agent_link",
        "real_name",
        "phone_number",
        "identity",
        "funder_company",
        "regist_datetime",
        "update_datetime",
        "vaild_datetime",
    };
    const char* const gszFunderUserCreateColType[FUT_Max] = {
        "varchar(64) COLLATE utf8_bin NOT NULL DEFAULT '' COMMENT '�˻���ʶ(�û�ID)��ϵͳ�ڲ�ʹ��' primary key",
        "varchar(64) COLLATE utf8_bin NOT NULL DEFAULT '' COMMENT '�������˻���ʶ��ϵͳ�ڲ�ʹ��'",
        "varchar(64) COLLATE utf8_bin NOT NULL DEFAULT '' COMMENT '�����˻���ʶ(�û�ID)��ϵͳ�ڲ�ʹ��'",
        "varchar(50) COLLATE utf8_bin NOT NULL DEFAULT '' COMMENT '��¼��'",
        "varchar(50) COLLATE utf8_bin NOT NULL DEFAULT '' COMMENT '�ǳ�'",
        "varchar(24) COLLATE utf8_bin NOT NULL DEFAULT '' COMMENT '����'",
        "varchar(50) COLLATE utf8_bin NOT NULL DEFAULT '' COMMENT '�˻���'",
        "int NOT NULL DEFAULT '-1' COMMENT '�㼶'",
        "int(2) NOT NULL DEFAULT '-1' COMMENT '�˻�����'",
        "int(2) NOT NULL DEFAULT '-1' COMMENT '�˻�����'",
        "int(2) NOT NULL DEFAULT '-1' COMMENT '�˻�״̬'",
        "int(2) NOT NULL DEFAULT '-1' COMMENT '�˻�Ȩ�޿���ģʽ'",
        "varchar(1024) COLLATE utf8_bin NOT NULL DEFAULT '' COMMENT '�ƹ�����'",
        "varchar(50) COLLATE utf8_bin DEFAULT '' COMMENT '��ʵ����'",
        "varchar(18) COLLATE utf8_bin DEFAULT '' COMMENT '�ֻ���'",
        "varchar(20) COLLATE utf8_bin DEFAULT '' COMMENT '���֤��'",
        "varchar(50) COLLATE utf8_bin DEFAULT '' COMMENT '��Ӧ����ʵ�̹�˾��'",
        "DATETIME COMMENT '����ʱ��'",
        "DATETIME COMMENT '����ʱ��'",
        "DATETIME COMMENT '��Ч��ʱ��'",
    };

    //////////////////////////////////////////////////////////////////////////
    enum UserLoginInfoTable : int {
        ULI_UserID = 0,
        ULI_InOut,
        ULI_DateTime,
        ULI_OpType,
        ULI_LoginIp,
        ULI_LoginMac,
        ULI_Max
    };
    const char* const gszUserLoginInfoTableName = "login_info";
    const char* const gszUserLoginInfoColName[ULI_Max] = {
        "user_id",
        "in_out",
        "date_time",
        "optype",
        "login_ip",
        "login_mac",
    };
    const char* const gszUserLoginInfoCreateColType[ULI_Max] = {
        "varchar(64) COLLATE utf8_bin NOT NULL DEFAULT '' COMMENT '�˻���ʶ(�û�ID)��ϵͳ�ڲ�ʹ��'",
        "int(2) NOT NULL DEFAULT '-1' COMMENT '����ǳ�'",
        "DATETIME COMMENT 'ʱ��'",
        "int(2) NOT NULL DEFAULT '-1' COMMENT '��������'",
        "varchar(40) COLLATE utf8_bin DEFAULT '' COMMENT '��¼IP'",
        "varchar(200) COLLATE utf8_bin DEFAULT '' COMMENT '��¼MAC'",
    };

#pragma endregion

#pragma region �˻�ȫ�����ݹ����
    enum AccountGlobalDataTable : int {
        AGD_CommodityType = 0,
        AGD_CurAgencyID,
        AGD_Max
    };
    const char* const gszAccountGlobalDataTableName = "account_global_data";
    const char* const gszAccountGlobalDataColName[AGD_Max] = {
        "commodity",
        "cur_agency_id",
    };
    const char* const gszAccountGlobalDataCreateColType[AGD_Max] = {
        "int(2) NOT NULL DEFAULT '-1' COMMENT '��Ʒ����' primary key",
        "int(5) NOT NULL COMMENT '�ۼƶ������'",
    };
#pragma endregion

#pragma region �ʽ���Ϣ�������Ϣ��
    enum MoneyChangeTable : int {
        MnyCT_Stream = 0,
        MnyCT_UserID,
        MnyCT_Before,
        MnyCT_After,
        MnyCT_ChangeMoney,
        MnyCT_Type,
        MnyCT_Remark,
        MnyCT_Time,
        MnyCT_Max,
    };
    const char* const gszMoneyChangeTableName = "stock_money_detail";
    const char* const gszMoneyChangeColName[MnyCT_Max] = {
        "stream",
        "user_id",
        "before_total",
        "after_total",
        "change_money",
        "type",
        "remark",
        "create_time",
    };
    const char* const gszMoneyChangeCreateColType[MnyCT_Max] = {
        "varchar(64) COLLATE utf8_bin NOT NULL DEFAULT '' COMMENT '��ˮ����' primary key",
        "varchar(64) COLLATE utf8_bin NOT NULL DEFAULT '' COMMENT '�û�ID'",
        "double(32,8) NOT NULL DEFAULT '0.00000000' COMMENT '�仯ǰ���ʽ�'",
        "double(32,8) NOT NULL DEFAULT '0.00000000' COMMENT '�仯�����ʽ�'",
        "double(32,8) NOT NULL DEFAULT '0.00000000' COMMENT '�䶯�ʽ�'",
        "int(2) NOT NULL DEFAULT '-1' COMMENT '�䶯����'",
        "varchar(1024) COLLATE utf8_bin DEFAULT '' COMMENT '��ע��Ϣ'",
        "DATETIME COMMENT '��������ʱ��'",
    };

    enum MoneyTable : int {
        MnyT_UserID = 0,
        MnyT_PositionCostPrice,
        MnyT_PositionVolume,
        MnyT_TradingFee,
        MnyT_CustomizeFee,
        MnyT_LogicCanExtract,
        MnyT_LogicWaitThaw,
        MnyT_OrderFreeze,
        MnyT_UserDeposit,
        MnyT_PriorityFund,
        MnyT_Max,
    };
    const char* const gszMoneyTableName = "stock_money";
    const char* const gszMoneyColName[MnyT_Max] = {
        "user_id",
        "position_cost_price",
        "position_volume",
        "trading_fee",
        "customize_fee",
        "logic_can_extract",
        "logic_wait_thaw",
        "order_thaw",
        "user_deposit",
        "priority_fund",
    };
    const char* const gszMoneyCreateColType[MnyT_Max] = {
        "varchar(64) COLLATE utf8_bin DEFAULT '' COMMENT '�û�ID' primary key",
        "double(32,8) NOT NULL DEFAULT '0.00000000' COMMENT '�ֲ��ܼ�'",
        "int NOT NULL DEFAULT '0' COMMENT '�ֲ�����'",
        "double(32,8) NOT NULL DEFAULT '0.00000000' COMMENT '������������'",
        "double(32,8) NOT NULL DEFAULT '0.00000000' COMMENT '�Զ���������'",
        "double(32,8) NOT NULL DEFAULT '0.00000000' COMMENT '�߼�����ȡ���(��)'",
        "double(32,8) NOT NULL DEFAULT '0.00000000' COMMENT '�߼����ⶳ���(��)'",
        "double(32,8) NOT NULL DEFAULT '0.00000000' COMMENT '�ύί��ʱ��ռ���ʽ�(��������)'",
        "double(32,8) NOT NULL DEFAULT '0.00000000' COMMENT '�û���֤��'",
        "double(32,8) NOT NULL DEFAULT '0.00000000' COMMENT '�����ʽ�'",
    };

    enum RiskTable : int {
        RiskT_UserID = 0,
        RiskT_WarningLine,
        RiskT_ForceLine,
        RiskT_LimitLine,
        RiskT_LeverRate,
        RiskT_CommissionRate,
        RiskT_Custom_Commissionrate,
        RiskT_Procommrate,
        RiskT_Max,
    };
    const char* const gszRiskTableName = "stock_risk";
    const char* const gszRiskColName[RiskT_Max] = {
        "user_id",
        "warningline",
        "forceline",
        "limitline",
        "lever_rate",
        "commissionrate",
        "custom_commissionrate",
        "procommrate",
    };
    const char* const gszRiskCreateColType[RiskT_Max] = {
        "varchar(64) COLLATE utf8_bin DEFAULT '' COMMENT '�û�ID' primary key",
        "double(32,8) NOT NULL DEFAULT '0.00000000' COMMENT '������'",
        "double(32,8) NOT NULL DEFAULT '0.00000000' COMMENT 'ǿƽ��'",
        "double(32,8) NOT NULL DEFAULT '0.00000000' COMMENT '�޲���'",
        "double(32,8) NOT NULL DEFAULT '0.00000000' COMMENT '�ܸ˱���'",
        "double(32,8) NOT NULL DEFAULT '0.00000000' COMMENT '������Ӷ�����(ǧ��֮)'",
        "double(32,8) NOT NULL DEFAULT '0.00000000' COMMENT '�ͻ��Զ���Ӷ�����(ǧ��֮)'",
        "double(32,8) NOT NULL DEFAULT '0.00000000' COMMENT '�ֳɱ���(ǧ��֮)'",
    };

#pragma endregion

#pragma region ��������Ϣ��
    enum ExchangeTable : int {
        ExT_ExchangeID = 0,
        ExT_ExchangeName,
        ExT_ExchangeCode,
        ExT_TradeTime,
        ExT_OrderTime,
        ExT_CommodityType,
        ExT_Max,
    };
    const char* const gszExchangeTableName = "exchanges";
    const char* const gszExchangeColName[ExT_Max] = {
        "exchange_id",
        "exchange_name",
        "exchange_code",
        "trade_time",
        "order_time",
        "commodity_type",
    };
    const char* const gszExchangeCreateColType[ExT_Max] = {
        "varchar(64) COLLATE utf8_bin DEFAULT '' COMMENT '������ID' primary key",
        "varchar(64) COLLATE utf8_bin DEFAULT '' COMMENT '��������'",
        "varchar(64) COLLATE utf8_bin DEFAULT '' COMMENT '����������'",
        "varchar(64) COLLATE utf8_bin DEFAULT '' COMMENT '����ʱ���'",
        "varchar(64) COLLATE utf8_bin DEFAULT '' COMMENT 'ί���ύʱ���'",
        "int(2) NOT NULL DEFAULT '-1' COMMENT '��Ʒ����'",
    };

#pragma endregion

#pragma region ��Ʊ��Լ��Ϣ��
    enum StockContractTable : int {
        SCT_ContractID = 0,
        SCT_ExchangeID,
        SCT_ContractNmae,
        SCT_ContractCode,
        SCT_CommodityType,
        SCT_CurrencyID,
        SCT_LastDays,
        SCT_OpenDateTime,
        SCT_DeliveryDateTime,
        SCT_TradeDateTime,
        SCT_MinPriceChange,
        SCT_Multiplier,
        SCT_OpenFeeFix,
        SCT_OpenFee,
        SCT_CloseYestodayFeeFix,
        SCT_CloseYestodayFee,
        SCT_MarginFix,
        SCT_Margin,
        SCT_DisplayProp,
        SCT_DisplayPropType,
        SCT_PlateProp,
        SCT_StockArea,
        SCT_StockPlateArea,
        SCT_StockTotalShares,
        SCT_Max,
    };
    const char* const gszStockContractTableName = "stock_contract";
    const char* const gszStockContractColName[SCT_Max] = {
        "contract_id",
        "exchange_id",
        "contract_name",
        "contract_code",
        "commodity_type",
        "currency_id",
        "last_days",
        "open_datetime",
        "delivery_datetime",
        "trade_datetime",
        "min_price_change",
        "multiplier",
        "open_fee_fix",
        "open_fee",
        "close_yestoday_fee_fix",
        "close_yestoday_fee",
        "margin_fix",
        "margin",
        "display_prop",
        "display_prop_type",
        "plate_prop",
        "stock_area",
        "stock_platearea",
        "stock_total_shares",
    };
    const char* const gszStockContractCreateColType[SCT_Max] = {
        "varchar(64) COLLATE utf8_bin DEFAULT '' COMMENT '��ԼID' primary key",
        "varchar(64) COLLATE utf8_bin DEFAULT '' COMMENT '������ID'",
        "varchar(20) COLLATE utf8_bin DEFAULT '' COMMENT '��Լ��'",
        "varchar(20) COLLATE utf8_bin DEFAULT '' COMMENT '��Լ����'",
        "int(2) NOT NULL DEFAULT '-1' COMMENT '��Ʒ����'",
        "varchar(64) COLLATE utf8_bin DEFAULT '' COMMENT '���ʵ�λID'",
        "int NOT NULL DEFAULT '-1' COMMENT '����������'",
        "DATETIME COMMENT '����ʱ��'",
        "DATETIME COMMENT '������ʱ��'",
        "DATETIME COMMENT '���ɿ���ʱ��'",
        "double(32,8) NOT NULL DEFAULT '0.00000000' COMMENT '��С�䶯��λ'",
        "int NOT NULL DEFAULT '-1' COMMENT '��Լ����'",
        "tinyint(1) NOT NULL DEFAULT '1' COMMENT '�����������Ƿ���ù̶�ֵ'",
        "double(32,8) NOT NULL DEFAULT '0.00000000' COMMENT '����������'",
        "tinyint(1) NOT NULL DEFAULT '1' COMMENT 'ƽ���������Ƿ���ù̶�ֵ'",
        "double(32,8) NOT NULL DEFAULT '0.00000000' COMMENT 'ƽ��������'",
        "tinyint(1) NOT NULL DEFAULT '1' COMMENT '��֤���Ƿ���ù̶�ֵ'",
        "double(32,8) NOT NULL DEFAULT '0.00000000' COMMENT '��֤��'",
        "varchar(20) COLLATE utf8_bin DEFAULT '' COMMENT '��ʾ(ҵ��)��������'",
        "int(2) NOT NULL DEFAULT '-1' COMMENT '��ʾ(ҵ��)��������'",
        "varchar(20) COLLATE utf8_bin DEFAULT '' COMMENT '�����������(����/����...)'",
        "int(2) NOT NULL DEFAULT '-1' COMMENT '������Ʊ����'",
        "int(2) NOT NULL DEFAULT '-1' COMMENT '������Ʊ�������(�����/������...)'",
        "double(32,8) NOT NULL DEFAULT '0.00000000' COMMENT '�ܹɱ�'",
    };
#pragma endregion

#pragma region ��Ʊί��
    enum StockOrderTable : int {
        SOT_OrderStream = 0,
        SOT_OrderID,
        SOT_UserID,
        SOT_ContractID,
        SOT_OrderState,
        SOT_OrderStateExplain,
        SOT_OrderRef,
        SOT_LoclaTmp_OrderRef,
        SOT_ShadowOrderID,
        SOT_GenerateDateTime,
        SOT_UpdateDateTime,
        SOT_CurrencyRate,
        SOT_CurrencyID,
        SOT_OrderPrice,
        SOT_Direct,
        SOT_OrderVol,
        SOT_EffectedVol,
        SOT_TradeVol,
        SOT_BFreezePosition,
        SOT_FreezeMoney,
        SOT_BFreezeMoney,
        SOT_OrderType,
        SOT_OrderTradeMode,
        SOT_OrderTradePrice,
        SOT_OrderPositionCost,
        SOT_SystemOrderID,
        SOT_ExchangeID,
        SOT_ApiType,
        SOT_OperatorType,
        SOT_OrderMode,
        SOT_ValidDateTime,
        SOT_StockArea,
        SOT_CurTradeFee,
        SOT_CurStampFee,
        SOT_CurTransferFee,
        SOT_CurInfomatchFee,
        SOT_Max
    };
    const char* const gszStockOrderTableName = "stock_order_info";
    const char* const gszStockOrderColName[SOT_Max] = {
        "order_stream",
        "order_id",
        "user_id",
        "contract_id",
        "order_state",
        "orser_state_explain",
        "order_ref",
        "order_loacltmp_ref",
        "shadow_order_id",
        "generate_datetime",
        "update_datetime",
        "currency_rate",
        "currency_id",
        "order_price",
        "direct_type",
        "order_vol",
        "effected_vol",
        "trade_vol",
        "b_freeze_position",
        "freeze_money",
        "b_freeze_money",
        "order_type",
        "order_trade_mode",
        "order_trade_price",
        "order_position_cost",
        "system_order_id",
        "exchange_id",
        "api_type",
        "op_type",
        "order_mode",
        "valid_datetime",
        "stock_area",
        "cur_trade_fee",
        "cur_stamp_fee",
        "cur_transfer_fee",
        "cur_infomatch_fee",
    };
    const char* const gszStockOrderCreateColType[SOT_Max] = {
        "varchar(128) COLLATE utf8_bin NOT NULL DEFAULT '' COMMENT 'ϵͳ������,�û�ID+&+GUID' primary key",
        "varchar(64) COLLATE utf8_bin DEFAULT '' COMMENT 'ί��ID'",
        "varchar(64) COLLATE utf8_bin NOT NULL DEFAULT '' COMMENT '�ʻ���ʶ(�û�ID)��ϵͳ�ڲ�ʹ��'",
        "varchar(64) COLLATE utf8_bin NOT NULL DEFAULT '' COMMENT '��ԼID'",
        "int(2) NOT NULL DEFAULT '-1' COMMENT 'ί��״̬'",
        "int(2) NOT NULL DEFAULT '-1' COMMENT 'ί��״̬˵��'",
        "varchar(64) COLLATE utf8_bin DEFAULT '' COMMENT '��ί��δ��Чʱ,������ҪΨһ��ʾ��ί��,��������һ��Ψһ����,ʹ�øñ�����б�ʶ'",
        "varchar(64) COLLATE utf8_bin DEFAULT '' COMMENT '�ͻ����ύ��ί�б��'",
        "varchar(64) COLLATE utf8_bin DEFAULT '' COMMENT 'Ӱ�Ӷ�����ţ� �ͻ�����ʾʹ��'",
        "DATETIME COMMENT 'ί�д�������ʱ��'",
        "DATETIME COMMENT ' ί��״̬����������ʱ��'",
        "double(32,8) NOT NULL DEFAULT '0.00000000' COMMENT '��ǰ��Ӧ���һ���'",
        "varchar(64) NOT NULL DEFAULT ''COMMENT '����ID'",
        "double(32,8) NOT NULL DEFAULT '0.00000000' COMMENT 'ί�м۸�'",
        "tinyint(1) NOT NULL DEFAULT '1' COMMENT '��������,ͬʱҲ�ǿ�ƽ��־,���ʾ����,����ʾƽ��'",
        "int(10) NOT NULL DEFAULT '0' COMMENT 'ί������'",
        "int(10) NOT NULL DEFAULT '0' COMMENT '����Ч����'",
        "int(10) NOT NULL DEFAULT '0' COMMENT '�ɽ�����'",
        "tinyint(1) NOT NULL DEFAULT '0' COMMENT '�Ƿ��ж���ֲ�'",
        "double(32,8) NOT NULL DEFAULT '0.00000000' COMMENT 'ί�ж������ʽ�'",
        "tinyint(1) NOT NULL DEFAULT '0' COMMENT '�Ƿ��ж����ʽ�'",
        "int(2) NOT NULL DEFAULT '-1' COMMENT '�µ�ί������'",
        "int(2) NOT NULL DEFAULT '-1' COMMENT 'ί�н���ģʽ'",
        "double(32,8) NOT NULL DEFAULT '0.00000000' COMMENT 'ί�гɽ���'",
        "double(32,8) NOT NULL DEFAULT '0.00000000' COMMENT '�ֲֳɱ�'",
        "varchar(64) COLLATE utf8_bin NOT NULL DEFAULT '' COMMENT '������ί�б��'",
        "varchar(255) COLLATE utf8_bin NOT NULL DEFAULT '' COMMENT '������ID'",
        "int(2) NOT NULL DEFAULT '-1' COMMENT '�ӿ�����'",
        "int(2) NOT NULL DEFAULT '-1' COMMENT '����Ա����'",
        "int(2) NOT NULL DEFAULT '-1' COMMENT '�µ�ί��ģʽ'",
        "DATETIME COMMENT '��Ч����'",
        "int(2) NOT NULL DEFAULT '-1' COMMENT '������Ʊ����'",
        "double(32,8) NOT NULL DEFAULT '0.00000000' COMMENT '��ǰ����Ӷ��������'",
        "double(32,8) NOT NULL DEFAULT '0.00000000' COMMENT '��ǰƽ��ӡ��˰��'",
        "double(32,8) NOT NULL DEFAULT '0.00000000' COMMENT '��ǰ������'",
        "double(32,8) NOT NULL DEFAULT '0.00000000' COMMENT '��ǰ��Ϣ��Ϸ�'",
    };
#pragma endregion

#pragma region ����ί��
    enum ForeignFutureOrderTable : int {
        FFOT_OrderStream = 0,
        FFOT_OrderID,
        FFOT_UserID,
        FFOT_ContractID,
        FFOT_OrderState,
        FFOT_OrderStateExplain,
        FFOT_OrderRef,
        FFOT_LoclaTmp_OrderRef,
        FFOT_ShadowOrderID,
        FFOT_GenerateDateTime,
        FFOT_UpdateDateTime,
        FFOT_CurrencyRate,
        FFOT_CurrencyID,
        FFOT_OrderPrice,
        FFOT_Direct,
        FFOT_OrderVol,
        FFOT_EffectedVol,
        FFOT_OrderType,
        FFOT_OrderTradeMode,
        FFOT_OrderTradePrice,
        FFOT_OrderPositionCost,
        FFOT_SystemOrderID,
        FFOT_ExchangeID,
        FFOT_ApiType,
        FFOT_OperatorType,
        FFOT_OrderMode,
        FFOT_ValidDateTime,
        FFOT_ProductID,
        FFOT_Max
    };
    const char* const gszForeignFutureOrderTableName = "foreign_futureorder_info";
    const char* const gszForeignFutureOrderColName[FFOT_Max] = {
        "order_stream",
        "order_id",
        "user_id",
        "contract_id",
        "order_state",
        "orser_state_explain",
        "order_ref",
        "order_loacltmp_ref",
        "shadow_order_id",
        "generate_datetime",
        "update_datetime",
        "currency_rate",
        "currency_id",
        "order_price",
        "direct_type",
        "order_vol",
        "effected_vol",
        "order_type",
        "order_trade_mode",
        "order_trade_price",
        "order_position_cost",
        "system_order_id",
        "exchange_id",
        "api_type",
        "op_type",
        "order_mode",
        "valid_datetime",
        "product_id",
    };
    const char* const gszForeignFutureOrderCreateColType[FFOT_Max] = {
        "varchar(128) COLLATE utf8_bin DEFAULT '' COMMENT 'ϵͳ������,�û�ID+&+GUID' primary key",
        "varchar(64) COLLATE utf8_bin NOT NULL DEFAULT '' COMMENT 'ί��ID'",
        "varchar(64) COLLATE utf8_bin NOT NULL DEFAULT '' COMMENT '�ʻ���ʶ(�û�ID)��ϵͳ�ڲ�ʹ��'",
        "varchar(64) COLLATE utf8_bin NOT NULL DEFAULT '' COMMENT '��ԼID'",
        "int(2) NOT NULL DEFAULT '-1' COMMENT 'ί��״̬'",
        "int(2) NOT NULL DEFAULT '-1' COMMENT 'ί��״̬˵��'",
        "varchar(64) COLLATE utf8_bin NOT NULL DEFAULT '' COMMENT '��ί��δ��Чʱ,������ҪΨһ��ʾ��ί��,��������һ��Ψһ����,ʹ�øñ�����б�ʶ'",
        "varchar(64) COLLATE utf8_bin NOT NULL DEFAULT '' COMMENT '�ͻ����ύ��ί�б��'",
        "varchar(64) COLLATE utf8_bin NOT NULL DEFAULT '' COMMENT 'Ӱ�Ӷ�����ţ� �ͻ�����ʾʹ��'",
        "DATETIME COMMENT 'ί�д�������ʱ��'",
        "DATETIME COMMENT ' ί��״̬����������ʱ��'",
        "double(32,8) NOT NULL DEFAULT '0.00000000' COMMENT '��ǰ��Ӧ���һ���'",
        "varchar(64) NOT NULL DEFAULT ''COMMENT '����ID'",
        "double(32,8) NOT NULL DEFAULT '0.00000000' COMMENT 'ί�м۸�'",
        "int(2) NOT NULL DEFAULT '-1' COMMENT '��������'",
        "int(10) NOT NULL DEFAULT '0' COMMENT 'ί������'",
        "int(10) NOT NULL DEFAULT '0' COMMENT '����Ч����'",
        "int(2) NOT NULL DEFAULT '-1' COMMENT '�µ�ί������'",
        "int(2) NOT NULL DEFAULT '-1' COMMENT 'ί�н���ģʽ'",
        "double(32,8) NOT NULL DEFAULT '0.00000000' COMMENT 'ί�гɽ���'",
        "double(32,8) NOT NULL DEFAULT '0.00000000' COMMENT '�ֲֳɱ�'",
        "varchar(64) COLLATE utf8_bin NOT NULL DEFAULT '' COMMENT '������ί�б��'",
        "varchar(255) COLLATE utf8_bin NOT NULL DEFAULT '' COMMENT '������ID'",
        "int(2) NOT NULL DEFAULT '-1' COMMENT '�ӿ�����'",
        "int(2) NOT NULL DEFAULT '-1' COMMENT '����Ա����'",
        "int(2) NOT NULL DEFAULT '-1' COMMENT '�µ�ί��ģʽ'",
        "DATETIME COMMENT '��Ч����'",
        "int(10) NOT NULL DEFAULT '-1' COMMENT 'Ʒ��ID'",
    };
#pragma endregion

#pragma region ����ί��
    enum ChinaFutureOrderTable : int {
        CFOT_OrderStream = 0,
        CFOT_OrderID,
        CFOT_UserID,
        CFOT_ContractID,
        CFOT_OrderState,
        CFOT_OrderStateExplain,
        CFOT_OrderRef,
        CFOT_LoclaTmp_OrderRef,
        CFOT_ShadowOrderID,
        CFOT_GenerateDateTime,
        CFOT_UpdateDateTime,
        CFOT_CurrencyRate,
        CFOT_CurrencyID,
        CFOT_OrderPrice,
        CFOT_Direct,
        CFOT_OrderVol,
        CFOT_EffectedVol,
        CFOT_OrderType,
        CFOT_OrderTradeMode,
        CFOT_OrderTradePrice,
        CFOT_OrderPositionCost,
        CFOT_SystemOrderID,
        CFOT_ExchangeID,
        CFOT_ApiType,
        CFOT_OperatorType,
        CFOT_OrderMode,
        CFOT_ValidDateTime,
        CFOT_ProductID,
        CFOT_OffsetType,
        CFOT_Max
    };
    const char* const gszChinaFutureOrderTableName = "china_futureorder_info";
    const char* const gszChinaFutureOrderColName[CFOT_Max] = {
        "order_stream",
        "order_id",
        "user_id",
        "contract_id",
        "order_state",
        "orser_state_explain",
        "order_ref",
        "order_loacltmp_ref",
        "shadow_order_id",
        "generate_datetime",
        "update_datetime",
        "currency_rate",
        "currency_id",
        "order_price",
        "direct_type",
        "order_vol",
        "effected_vol",
        "order_type",
        "order_trade_mode",
        "order_trade_price",
        "order_position_cost",
        "system_order_id",
        "exchange_id",
        "api_type",
        "op_type",
        "order_mode",
        "valid_datetime",
        "product_id",
        "offset_type",
    };
    const char* const gszChinaFutureOrderCreateColType[CFOT_Max] = {
        "varchar(128) COLLATE utf8_bin DEFAULT '' COMMENT 'ϵͳ������,�û�ID+&+GUID' primary key",
        "varchar(64) COLLATE utf8_bin NOT NULL DEFAULT '' COMMENT 'ί��ID'",
        "varchar(64) COLLATE utf8_bin NOT NULL DEFAULT '' COMMENT '�ʻ���ʶ(�û�ID)��ϵͳ�ڲ�ʹ��'",
        "varchar(64) COLLATE utf8_bin NOT NULL DEFAULT '' COMMENT '��ԼID'",
        "int(2) NOT NULL DEFAULT '-1' COMMENT 'ί��״̬'",
        "int(2) NOT NULL DEFAULT '-1' COMMENT 'ί��״̬˵��'",
        "varchar(64) COLLATE utf8_bin NOT NULL DEFAULT '' COMMENT '��ί��δ��Чʱ,������ҪΨһ��ʾ��ί��,��������һ��Ψһ����,ʹ�øñ�����б�ʶ'",
        "varchar(64) COLLATE utf8_bin NOT NULL DEFAULT '' COMMENT '�ͻ����ύ��ί�б��'",
        "varchar(64) COLLATE utf8_bin NOT NULL DEFAULT '' COMMENT 'Ӱ�Ӷ�����ţ� �ͻ�����ʾʹ��'",
        "DATETIME COMMENT 'ί�д�������ʱ��'",
        "DATETIME COMMENT ' ί��״̬����������ʱ��'",
        "double(32,8) NOT NULL DEFAULT '0.00000000' COMMENT '��ǰ��Ӧ���һ���'",
        "varchar(64) NOT NULL DEFAULT ''COMMENT '����ID'",
        "double(32,8) NOT NULL DEFAULT '0.00000000' COMMENT 'ί�м۸�'",
        "int(2) NOT NULL DEFAULT '-1' COMMENT '��������'",
        "int(10) NOT NULL DEFAULT '0' COMMENT 'ί������'",
        "int(10) NOT NULL DEFAULT '0' COMMENT '����Ч����'",
        "int(2) NOT NULL DEFAULT '-1' COMMENT '�µ�ί������'",
        "int(2) NOT NULL DEFAULT '-1' COMMENT 'ί�н���ģʽ'",
        "double(32,8) NOT NULL DEFAULT '0.00000000' COMMENT 'ί�гɽ���'",
        "double(32,8) NOT NULL DEFAULT '0.00000000' COMMENT '�ֲֳɱ�'",
        "varchar(64) COLLATE utf8_bin NOT NULL DEFAULT '' COMMENT '������ί�б��'",
        "varchar(255) COLLATE utf8_bin NOT NULL DEFAULT '' COMMENT '������ID'",
        "int(2) NOT NULL DEFAULT '-1' COMMENT '�ӿ�����'",
        "int(2) NOT NULL DEFAULT '-1' COMMENT '����Ա����'",
        "int(2) NOT NULL DEFAULT '-1' COMMENT '�µ�ί��ģʽ'",
        "DATETIME COMMENT '��Ч����'",
        "int(10) NOT NULL DEFAULT '-1' COMMENT 'Ʒ��ID'",
        "tinyint(1) NOT NULL DEFAULT '1' COMMENT '��ƽ��־'",
    };
#pragma endregion

#pragma region ��Ʊ�ɽ�
    enum StockTradeTable : int {
        STT_TradeID = 0,
        STT_ShadowTradeID,
        STT_OrderStream,
        STT_PositionID,
        STT_UserID,
        STT_ExchangeID,
        STT_ContractID,
        STT_GenerateDateTime,
        STT_Direct,
        STT_TradeVol,
        STT_CurrencyRate,
        STT_CurrencyID,
        STT_TradeAvePrice,
        STT_CloseProfit,
        STT_OperatorType,
        STT_StockArea,
        STT_TradeFee,
        STT_StampFee,
        STT_TransferFee,
        STT_InfomatchFee,
        STT_Max
    };
    const char* const gszStockTradeTableName = "stock_trade_info";
    const char* const gszStockTradeColName[STT_Max] = {
        "trade_id",
        "shadow_trade_id",
        "order_stream",
        "position_id",
        "user_id",
        "exchange_id",
        "contract_id",
        "generate_datetime",
        "direct_type",
        "trade_vol",
        "currency_rate",
        "currency_id",
        "trade_ave_price",
        "close_profit",
        "op_type",
        "stock_area",
        "trade_fee",
        "stamp_fee",
        "transfer_fee",
        "infomatch_fee",
    };
    const char* const gszStockTradeCreateColType[STT_Max] = {
        "varchar(64) COLLATE utf8_bin DEFAULT '' COMMENT 'ϵͳ�ڳɽ�����' primary key",
        "varchar(64) COLLATE utf8_bin DEFAULT '' COMMENT 'Ӱ�Ӷ������'",
        "varchar(128) COLLATE utf8_bin DEFAULT '' COMMENT 'ί������'",
        "varchar(64) COLLATE utf8_bin DEFAULT '' COMMENT '�ֲ�ID'",
        "varchar(64) COLLATE utf8_bin NOT NULL DEFAULT '' COMMENT '�ʻ���ʶ(�û�ID)��ϵͳ�ڲ�ʹ��'",
        "varchar(255) COLLATE utf8_bin NOT NULL DEFAULT '' COMMENT '������ID'",
        "varchar(64) COLLATE utf8_bin NOT NULL DEFAULT '' COMMENT '��ԼID'",
        "DATETIME COMMENT '�ɽ�����ʱ��'",
        "tinyint(1) NOT NULL DEFAULT '1' COMMENT '��������,ͬʱҲ�ǿ�ƽ��־,���ʾ����,����ʾƽ��'",
        "int(10) NOT NULL DEFAULT '0' COMMENT '�ɽ�����'",
        "double(32,8) NOT NULL DEFAULT '0.00000000' COMMENT '��ǰ��Ӧ���һ���'",
        "varchar(64) COLLATE utf8_bin NOT NULL DEFAULT '' COMMENT '����ID'",
        "double(32,8) NOT NULL DEFAULT '0.00000000' COMMENT '�ɽ�����'",
        "double(32,8) NOT NULL DEFAULT '0.00000000' COMMENT 'ƽ��ӯ��'",
        "int(2) NOT NULL DEFAULT '-1' COMMENT '����Ա����'",
        "int(2) NOT NULL DEFAULT '-1' COMMENT '������Ʊ����'",
        "double(32,8) NOT NULL DEFAULT '0.00000000' COMMENT '����Ӷ��������'",
        "double(32,8) NOT NULL DEFAULT '0.00000000' COMMENT 'ƽ��ӡ��˰��'",
        "double(32,8) NOT NULL DEFAULT '0.00000000' COMMENT '������'",
        "double(32,8) NOT NULL DEFAULT '0.00000000' COMMENT '��Ϣ��Ϸ�'",
    };
#pragma endregion

#pragma region ���̳ɽ�
    enum ForeignFutureTradeTable : int {
        FFTT_TradeID = 0,
        FFTT_OrderStream,
        FFTT_PositionID,
        FFTT_UserID,
        FFTT_ExchangeID,
        FFTT_ProductID,
        FFTT_ContractID,
        FFTT_GenerateDateTime,
        FFTT_Direct,
        FFTT_TradeVol,
        FFTT_CurrencyRate,
        FFTT_CurrencyID,
        FFTT_TradeAvePrice,
        FFTT_CloseProfit,
        FFTT_OperatorType,
        FFTT_Max
    };
    const char* const gszForeignFutureTradeTableName = "foreignfuture_trade_info";
    const char* const gszForeignFutureTradeColName[FFTT_Max] = {
        "trade_id",
        "order_stream",
        "position_id",
        "user_id",
        "exchange_id",
        "product_id",
        "contract_id",
        "generate_datetime",
        "direct",
        "trade_vol",
        "currency_rate",
        "currency_id",
        "trade_ave_price",
        "close_profit",
        "op_type",
    };
    const char* const gszForeignFutureTradeCreateColType[FFTT_Max] = {
        "varchar(64) COLLATE utf8_bin DEFAULT '' COMMENT 'ϵͳ�ڳɽ�����' primary key",
        "varchar(128) COLLATE utf8_bin DEFAULT '' COMMENT 'ί������'",
        "varchar(64) COLLATE utf8_bin DEFAULT '' COMMENT '�ֲ�ID'",
        "varchar(64) COLLATE utf8_bin NOT NULL DEFAULT '' COMMENT '�ʻ���ʶ(�û�ID)��ϵͳ�ڲ�ʹ��'",
        "varchar(255) COLLATE utf8_bin NOT NULL DEFAULT '' COMMENT '������ID'",
        "varchar(64) COLLATE utf8_bin NOT NULL DEFAULT '' COMMENT 'Ʒ��ID'",
        "varchar(64) COLLATE utf8_bin NOT NULL DEFAULT '' COMMENT '��ԼID'",
        "DATETIME COMMENT '�ɽ�����ʱ��'",
        "int(2) NOT NULL DEFAULT '-1' COMMENT '��������'",
        "int(10) NOT NULL DEFAULT '0' COMMENT '�ɽ�����'",
        "double(32,8) NOT NULL DEFAULT '0.00000000' COMMENT '��ǰ��Ӧ���һ���'",
        "varchar(64) COLLATE utf8_bin NOT NULL DEFAULT '' COMMENT '����ID'",
        "double(32,8) NOT NULL DEFAULT '0.00000000' COMMENT '�ɽ�����'",
        "double(32,8) NOT NULL DEFAULT '0.00000000' COMMENT 'ƽ��ӯ��'",
        "int(2) NOT NULL DEFAULT '-1' COMMENT '����Ա����'",
    };

#pragma endregion

#pragma region ���̳ɽ�
    enum ChinaFutureTradeTable : int {
        CFTT_TradeID = 0,
        CFTT_OrderStream,
        CFTT_PositionID,
        CFTT_UserID,
        CFTT_ExchangeID,
        CFTT_ProductID,
        CFTT_ContractID,
        CFTT_GenerateDateTime,
        CFTT_Direct,
        CFTT_Offset,
        CFTT_TradeVol,
        CFTT_CurrencyRate,
        CFTT_CurrencyID,
        CFTT_TradeAvePrice,
        CFTT_CloseProfit,
        CFTT_OperatorType,
        CFTT_Max
    };
    const char* const gszChinaFutureTradeTableName = "chinafuture_trade_info";
    const char* const gszChinaFutureTradeColName[CFTT_Max] = {
        "trade_id",
        "order_stream",
        "position_id",
        "user_id",
        "exchange_id",
        "product_id",
        "contract_id",
        "generate_datetime",
        "direct",
        "offset",
        "trade_vol",
        "currency_rate",
        "currency_id",
        "trade_ave_price",
        "close_profit",
        "op_type",
    };
    const char* const gszChinaFutureTradeCreateColType[CFTT_Max] = {
        "varchar(64) COLLATE utf8_bin DEFAULT '' COMMENT 'ϵͳ�ڳɽ�����' primary key",
        "varchar(128) COLLATE utf8_bin DEFAULT '' COMMENT 'ί������'",
        "varchar(64) COLLATE utf8_bin DEFAULT '' COMMENT '�ֲ�ID'",
        "varchar(64) COLLATE utf8_bin NOT NULL DEFAULT '' COMMENT '�ʻ���ʶ(�û�ID)��ϵͳ�ڲ�ʹ��'",
        "varchar(255) COLLATE utf8_bin NOT NULL DEFAULT '' COMMENT '������ID'",
        "varchar(64) COLLATE utf8_bin NOT NULL DEFAULT '' COMMENT 'Ʒ��ID'",
        "varchar(64) COLLATE utf8_bin NOT NULL DEFAULT '' COMMENT '��ԼID'",
        "DATETIME COMMENT '�ɽ�����ʱ��'",
        "int(2) NOT NULL DEFAULT '-1' COMMENT '��������'",
        "int(2) NOT NULL DEFAULT '-1' COMMENT '��ƽ��־'",
        "int(10) NOT NULL DEFAULT '0' COMMENT '�ɽ�����'",
        "double(32,8) NOT NULL DEFAULT '0.00000000' COMMENT '��ǰ��Ӧ���һ���'",
        "varchar(64) COLLATE utf8_bin NOT NULL DEFAULT '' COMMENT '����ID'",
        "double(32,8) NOT NULL DEFAULT '0.00000000' COMMENT '�ɽ�����'",
        "double(32,8) NOT NULL DEFAULT '0.00000000' COMMENT 'ƽ��ӯ��'",
        "int(2) NOT NULL DEFAULT '-1' COMMENT '����Ա����'",
    };

#pragma endregion

#pragma region ��Ʊ�ֲ�
    enum StockPositionTable : int {
        SPT_PositionID = 0,
        SPT_UserID,
        SPT_ExchangeID,
        SPT_ContractID,
        SPT_Direct,
        SPT_PositionVol,
        SPT_PositionTVol,
        SPT_CurrencyID,
        SPT_PositionCostPrice,
        SPT_TradeAvePrice,
        SPT_StockArea,
        SPT_PositionFreezeVol,
        SPT_Max
    };
    const char* const gszStockPositionTableName = "stock_position_info";
    const char* const gszStockPositionColName[SPT_Max] = {
        "position_id",
        "user_id",
        "exchange_id",
        "contract_id",
        "direct_type",
        "position_vol",
        "position_T_vol",
        "currency_id",
        "position_cost_price",
        "trade_ave_price",
        "stock_area",
        "position_freeze_vol",
    };
    const char* const gszStockPositionCreateColType[SPT_Max] = {
        "varchar(64) COLLATE utf8_bin DEFAULT '' COMMENT '�ֲ�ID' primary key",
        "varchar(64) COLLATE utf8_bin NOT NULL DEFAULT '' COMMENT '�ʻ���ʶ(�û�ID)��ϵͳ�ڲ�ʹ��'",
        "varchar(255) COLLATE utf8_bin NOT NULL DEFAULT '' COMMENT '������ID'",
        "varchar(64) COLLATE utf8_bin NOT NULL DEFAULT '' COMMENT '��ԼID'",
        "tinyint(1) NOT NULL DEFAULT '1' COMMENT '��������,ͬʱҲ�ǿ�ƽ��־,���ʾ����,����ʾƽ��'",
        "int(10) NOT NULL DEFAULT '0' COMMENT '�ֲ�����'",
        "int(10) NOT NULL DEFAULT '0' COMMENT 'T+1�ֲ�����'",
        "varchar(64) COLLATE utf8_bin NOT NULL DEFAULT '' COMMENT '����ID'",
        "double(32,8) NOT NULL DEFAULT '0.00000000' COMMENT '�ֲ��ܼ�'",
        "double(32,8) NOT NULL DEFAULT '0.00000000' COMMENT '�ɽ�����'",
        "int(2) NOT NULL DEFAULT '-1' COMMENT '������Ʊ����'",
        "int(10) NOT NULL DEFAULT '0' COMMENT 'ƽ��ί�ж���ֲ�����'",
    };
#pragma endregion

#pragma region ���ֲ̳�
    enum ForeignFuturePositionTable : int {
        FFPT_PositionID = 0,
        FFPT_UserID,
        FFPT_ExchangeID,
        FFPT_ContractID,
        FFPT_Direct,
        FFPT_PositionVol,
        FFPT_CurrencyID,
        FFPT_PositionCostPrice,
        FFPT_Max
    };
    const char* const gszForeignFuturePositionTableName = "foreignfuture_position_info";
    const char* const gszForeignFuturePositionColName[FFPT_Max] = {
        "position_id",
        "user_id",
        "exchange_id",
        "contract_id",
        "direct",
        "position_vol",
        "currency_id",
        "position_cost_price",
    };
    const char* const gszForeignFuturePositionCreateColType[FFPT_Max] = {
        "varchar(64) COLLATE utf8_bin DEFAULT '' COMMENT '�ֲ�ID' primary key",
        "varchar(64) COLLATE utf8_bin NOT NULL DEFAULT '' COMMENT '�ʻ���ʶ(�û�ID)��ϵͳ�ڲ�ʹ��'",
        "varchar(255) COLLATE utf8_bin NOT NULL DEFAULT '' COMMENT '������ID'",
        "varchar(64) COLLATE utf8_bin NOT NULL DEFAULT '' COMMENT '��ԼID'",
        "int(2) NOT NULL DEFAULT '-1' COMMENT '��������'",
        "int(10) NOT NULL DEFAULT '0' COMMENT '�ֲ�����'",
        "varchar(64) COLLATE utf8_bin NOT NULL DEFAULT '' COMMENT '����ID'",
        "double(32,8) NOT NULL DEFAULT '0.00000000' COMMENT '�ֲ��ܼ�'",
    };
#pragma endregion

#pragma region ���ֲ̳�
    enum ChinaFuturePositionTable : int {
        CFPT_PositionID = 0,
        CFPT_UserID,
        CFPT_ExchangeID,
        CFPT_ContractID,
        CFPT_Direct,
        CFPT_Offset,
        CFPT_PositionVol,
        CFPT_CurrencyID,
        CFPT_PositionCostPrice,
        CFPT_Max
    };
    const char* const gszChinaFuturePositionTableName = "chinafuture_position_info";
    const char* const gszChinaFuturePositionColName[CFPT_Max] = {
        "position_id",
        "user_id",
        "exchange_id",
        "contract_id",
        "direct",
        "offset_type",
        "position_vol",
        "currency_id",
        "position_cost_price",
    };
    const char* const gszChinaFuturePositionCreateColType[CFPT_Max] = {
        "varchar(64) COLLATE utf8_bin DEFAULT '' COMMENT '�ֲ�ID' primary key",
        "varchar(64) COLLATE utf8_bin NOT NULL DEFAULT '' COMMENT '�ʻ���ʶ(�û�ID)��ϵͳ�ڲ�ʹ��'",
        "varchar(255) COLLATE utf8_bin NOT NULL DEFAULT '' COMMENT '������ID'",
        "varchar(64) COLLATE utf8_bin NOT NULL DEFAULT '' COMMENT '��ԼID'",
        "int(2) NOT NULL DEFAULT '-1' COMMENT '��������'",
        "tinyint(1) NOT NULL DEFAULT '1' COMMENT '��ƽ��־'",
        "int(10) NOT NULL DEFAULT '0' COMMENT '�ֲ�����'",
        "varchar(64) COLLATE utf8_bin NOT NULL DEFAULT '' COMMENT '����ID'",
        "double(32,8) NOT NULL DEFAULT '0.00000000' COMMENT '�ֲ��ܼ�'",
    };
#pragma endregion

#pragma region ���ù����

    enum TradeFeeTable : int {
        TFT_ID = 0,
        TFT_Trade_Commission,
        TFT_Min_Trade_Commission,
        TFT_Stamp_Duty,
        TFT_Transfer,
        TFT_Info_Match,
        TFT_Profit_Rate,
        TFT_Max
    };
    const char* const gszTradeFeeTableName = "trade_fee";
    const char* const gszTradeFeeColName[TFT_Max] = {
        "ID",
        "trade_commission",
        "min_trade_commission",
        "stamp_duty",
        "transfer",
        "info_match",
        "profit_rate",
    };
    const char* const gszTradeFeeCreateColType[TFT_Max] = {
        "int(10) unsigned NOT NULL AUTO_INCREMENT COMMENT 'ID' primary key",
        "double(32,8) NOT NULL DEFAULT '0.00000000' COMMENT '����Ӷ��(ǧ��֮)'",
        "double(32,8) NOT NULL DEFAULT '0.00000000' COMMENT '��С����Ӷ��(Ԫ)'",
        "double(32,8) NOT NULL DEFAULT '0.00000000' COMMENT 'ӡ��˰(ǧ��֮)'",
        "double(32,8) NOT NULL DEFAULT '0.00000000' COMMENT '������(ǧ��֮)'",
        "double(32,8) NOT NULL DEFAULT '0.00000000' COMMENT '��Ϸ�(ǧ��֮)'",
        "double(32,8) NOT NULL DEFAULT '0.00000000' COMMENT '�����˻��ֳɱ���(ǧ��֮)'",
    };
#pragma endregion

#pragma region ��������

    enum SettleTable : int {
//         Settle_ExchangeID = 0,
        Settle_CommodityType = 0,
        Settle_DateTime,
        Settle_Max
    };
    const char* const gszSettleTableName = "settle_recode";
    const char* const gszSettleColName[Settle_Max] = {
//         "exchange_id",
        "settle_commodity",
        "settle_datetime",
    };
    const char* const gszSettleCreateColType[Settle_Max] = {
//         "varchar(64) COLLATE utf8_bin DEFAULT '' COMMENT '������ID' primary key",
        "int(2) NOT NULL DEFAULT '-1' COMMENT '��Ʒ����' primary key",
        "DATETIME COMMENT '����ʱ��'",
    };
#pragma endregion

#pragma region ȫ�����ݹ����
    enum GlobalDataTable : int {
        GD_CommodityType = 0,
        GD_CurShadowOrderID,
        GD_CurShadowTradeID,
        GD_Max
    };
    const char* const gszGlobalDataTableName = "global_data";
    const char* const gszGlobalDataColName[GD_Max] = {
        "commodity",
        "cur_shadow_order_id",
        "cur_shadow_trade_id",
    };
    const char* const gszGlobalDataCreateColType[GD_Max] = {
        "int(2) NOT NULL DEFAULT '-1' COMMENT '��Ʒ����' primary key",
        "int(5) NOT NULL DEFAULT '-1' COMMENT '�ۼƶ������'",
        "int(5) NOT NULL DEFAULT '-1' COMMENT '�ۼƳɽ����'",
    };
#pragma endregion

#pragma region ��ؼ�¼��
    enum RiskControlRecordTable : int {
        RCRT_UserID = 0,
        RCRT_RiskType,
        RCRT_BTrigger,
        RCRT_DateTime,
		RCRT_TriggerText,
        RCRT_Max
    };
    const char* const gszRiskControlRecordTableName = "risk_control_record";
    const char* const gszRiskControlRecordColName[RCRT_Max] = {
		"user_id",
        "risk_type",
        "bTrigger",
        "tri_datetime",
		"tri_triggertext",
    };
    const char* const gszRiskControlRecordCreateColType[RCRT_Max] = {
		"varchar(64) CHARACTER SET utf8 NOT NULL COMMENT '�û�ID'",
        "int(2) NOT NULL DEFAULT '-1' COMMENT '�������'",
        "tinyint(2) NOT NULL COMMENT '�Ƿ��ڴ���״̬ 0������ 1����'",
        "DATETIME COMMENT '����ʱ��'",
		"varchar(1024) CHARACTER SET utf8 NOT NULL COMMENT '��ʾ����'",
    };
#pragma endregion

#pragma region �����ʷ��¼��
	enum RiskControlHistoryRecordTable : int {
		RCHRT_Stream = 0,
		RCHRT_UserID,
		RCHRT_RiskType,
		RCHRT_BTrigger,
		RCHRT_DateTime,
		RCHRT_TriggerText,
		RCHRT_Max
	};
	const char* const gszRiskControlHistoryRecordTableName = "risk_control_history_record";
	const char* const gszRiskControlHistoryRecordColName[RCHRT_Max] = {
		"stream",
		"user_id",
		"risk_type",
		"bTrigger",
		"tri_datetime",
		"tri_triggertext",
	};
	const char* const gszRiskControlHistoryRecordCreateColType[RCHRT_Max] = {
		"int(10) unsigned NOT NULL AUTO_INCREMENT COMMENT 'ID' primary key",
		"varchar(64) CHARACTER SET utf8 NOT NULL COMMENT '�û�ID'",
		"int(2) NOT NULL DEFAULT '-1' COMMENT '�������'",
		"tinyint(2) NOT NULL COMMENT '�Ƿ��ڴ���״̬ 0������ 1����'",
		"DATETIME COMMENT '����ʱ��'",
		"varchar(1024) CHARACTER SET utf8 NOT NULL COMMENT '��ʾ����'",
	};
#pragma endregion

#pragma region Ȩ��ҵ���
	enum AuthorityBussnessesTable : int {
		ABT_BussnessId = 0,
		ABT_BussnessName,
		ABT_BussnessType,
		ABT_BussnessAddr,
		ABT_ParentBussnessId,
		ABT_IsHide,
		ABT_Max
	};
	const char* const gszAuthorityBussnessesTableName = "authority_bussnesses";
	const char* const gszAuthorityBussnessesColName[ABT_Max] = {
		"bussnessID",
		"bussnessName",
		"bussnessType",
		"bussnessAddr",
		"parentBussnessID",
		"isHide",
	};
	const char* const gszAuthorityBussnessesCreateColType[ABT_Max] = {
		"int(10) unsigned NOT NULL AUTO_INCREMENT COMMENT 'ҵ��ID' primary key",
		"varchar(64) CHARACTER SET utf8 NOT NULL COMMENT 'ҵ������'",
		"tinyint(2) NOT NULL COMMENT 'ҵ������ 1���˵�2������'",
		"varchar(20) CHARACTER SET utf8 NOT NULL COMMENT 'ҵ���ַ'",
		"int(10) NOT NULL COMMENT '��ҵ��ID'",
		"tinyint(2) NOT NULL COMMENT '�Ƿ����� 0������ 1����'",
	};
#pragma endregion

#pragma region Ȩ����־��
	enum AuthorityChangeLogTable : int {
		ACLT_Id = 0,
		ACLT_UserId,
		ACLT_ChangeDate,
		ACLT_ChangeTime,
		ACLT_Content,
		ACLT_Max
	};
	const char* const gszAuthorityChangeLogTableName = "authority_change_log";
	const char* const gszAuthorityChangeLogColName[ACLT_Max] = {
		"id",
		"userID",
		"changeDate",
		"changeTime",
		"content",
	};
	const char* const gszAuthorityChangeLogCreateColType[ACLT_Max] = {
		"int(10) unsigned NOT NULL AUTO_INCREMENT COMMENT 'id' primary key",
		"int(10) NOT NULL COMMENT '�����߱��'",
		"int(20) NOT NULL COMMENT '��������'",
		"int(10) NOT NULL COMMENT '����ʱ��'",
		"varchar(200) CHARACTER SET utf8 NOT NULL COMMENT '��������'",
	};
#pragma endregion

#pragma region Ȩ�޹��ܱ�
	enum AuthorityFunctionsTable : int {
		AFT_FunctionId = 0,
		AFT_BussnessId,
		AFT_NavigationId,
		AFT_FunctionName,
		AFT_Issort,
		AFT_Max
	};
	const char* const gszAuthorityFunctionsTableName = "authority_functions";
	const char* const gszAuthorityFunctionsColName[AFT_Max] = {
		"functionID",
		"bussnessID",
		"NavigationID",
		"functionName",
		"issort",
	};
	const char* const gszAuthorityFunctionsCreateColType[AFT_Max] = {
		"int(10) unsigned NOT NULL AUTO_INCREMENT COMMENT '����ID' primary key",
		"int(10) NOT NULL COMMENT 'ҵ��ID'",
		"int(10) NOT NULL COMMENT '����ID'",
		"varchar(64) CHARACTER SET utf8 NOT NULL COMMENT '��������'",
		"tinyint(2) NOT NULL COMMENT '���� 0������ 1����'",
	};
#pragma endregion

#pragma region Ȩ�޽�ɫ���ܱ�
	enum AuthorityRoleFunctionsTable : int {
		ARFT_Id = 0,
		ARFT_RoleId,
		ARFT_FunctionId,
		ARFT_Max
	};
	const char* const gszAuthorityRoleFunctionsTableName = "authority_role_functions";
	const char* const gszAuthorityRoleFunctionsColName[ARFT_Max] = {
		"id",
		"roleID",
		"functionID",
	};
	const char* const gszAuthorityRoleFunctionsCreateColType[ARFT_Max] = {
		"int(10) unsigned NOT NULL AUTO_INCREMENT COMMENT 'id' primary key",
		"int(10) NOT NULL COMMENT '��ɫID'",
		"int(10) NOT NULL COMMENT '����ID'",
	};
#pragma endregion

#pragma region Ȩ�޽�ɫ�û���
	enum AuthorityRoleUsersTable : int {
		ARUT_Id = 0,
		ARUT_LoginName,
		ARUT_RolesId,
		ARUT_Max
	};
	const char* const gszAuthorityRoleUsersTableName = "authority_role_users";
	const char* const gszAuthorityRoleUsersColName[ARUT_Max] = {
		"id",
		"loginName",
		"rolesID",
	};
	const char* const gszAuthorityRoleUsersCreateColType[ARUT_Max] = {
		"int(10) unsigned NOT NULL AUTO_INCREMENT primary key",
		"varchar(64) CHARACTER SET utf8 NOT NULL COMMENT '�û���¼��'",
		"int(10) NOT NULL COMMENT '��ɫID'",
	};
#pragma endregion

#pragma region Ȩ�޽�ɫ��
	enum AuthorityRolesTable : int {
		ART_RolesId = 0,
		ART_RolesName,
		ART_LoginName,
		ART_CreateDate,
		ART_CreateTime,
		ART_RolesType,
		ART_OperationType,
		ART_Max
	};
	const char* const gszAuthorityRolesTableName = "authority_roles";
	const char* const gszAuthorityRolesColName[ART_Max] = {
		"rolesID",
		"rolesName",
		"LoginName",
		"createDate",
		"createTime",
		"rolesType",
		"operationType",
	};
	const char* const gszAuthorityRolesCreateColType[ART_Max] = {
		"int(10) unsigned NOT NULL AUTO_INCREMENT COMMENT '��ɫID' primary key",
		"varchar(24) CHARACTER SET utf8 NOT NULL COMMENT '��ɫ����'",
		"varchar(64) CHARACTER SET utf8 NOT NULL COMMENT '�����ý�ɫ���û���¼��'",
		"int(20) NOT NULL COMMENT '��ɫ��������'",
		"int(10) NOT NULL COMMENT '��ɫ����ʱ��'",
		"tinyint(2) NOT NULL COMMENT '��ɫ����(0���� 1����Ա)'",
		"tinyint(2) NOT NULL COMMENT '��������(0�ɲ��� 1���ɲ���)'",
	};
#pragma endregion

#pragma region �����ʽ���˱�
    enum ApplyMoneyTable : int {
        ApplyMoney_ID = 0,
        ApplyMoney_Approval_UserID,
        ApplyMoney_UserID,
        ApplyMoney_Money,
        ApplyMoney_DateTime,
        ApplyMoney_Approval_DateTime,
        ApplyMoney_Status,
        ApplyMoney_Max,
    };
    const char* const gszApplyMoneyTableName = "apply_money_table";
    const char* const gszApplyMoneyColName[ApplyMoney_Max] = {
        "apply_id",
        "approval_userid",
        "apply_userid",
        "apply_money",
        "apply_dt",
        "approval_dt",
        "apply_status",
    };
    const char* const gszApplyMoneyCreateColType[ApplyMoney_Max] = {
        "int(25) NOT NULL AUTO_INCREMENT COMMENT '��ˮID' primary key",
        "varchar(64) COLLATE utf8_bin DEFAULT '' COMMENT '������û�ID'",
        "varchar(64) COLLATE utf8_bin DEFAULT '' COMMENT '�������û�ID'",
        "double(32,8) NOT NULL DEFAULT '0.00000000' COMMENT '�����ʽ�'",
        "DATETIME COMMENT '��������ʱ��'",
        "DATETIME COMMENT '�������ʱ��'",
        "int(2) NOT NULL DEFAULT '-1' COMMENT '���״̬'",
    };
#pragma endregion

#pragma region ����ʽ���˱�
    enum ApplyInMoneyTable : int {
        AIMT_SerialNumber = 0,
        AIMT_Approval_Userid,
        AIMT_AccountID,
        AIMT_BusinessID,
        AIMT_Amount,
        AIMT_Description,
        AIMT_BankName,
        AIMT_BankCard,
        AIMT_PostTime,
        AIMT_UpdateTime,
        AIMT_StateID,
        AIMT_OrderNumber,
        AIMT_RechargeType,
        AIMT_FeeType,
        AIMT_CardNo,
        AIMT_ResultCode,
        AIMT_ResultMessage,
        AIMT_LoadNo,
        AIMT_IsApproval,
        AIMT_ApprovalTime,
        AIMT_Max
    };
    const char* const gszApplyInMoneyTableName = "apply_in_money";
    const char* const gszApplyInMoneyColName[AIMT_Max] = {
        "SerialNumber",
        "approval_userid",
        "AccountID",
        "BusinessID",
        "Amount",
        "Description",
        "BankName",
        "BankCard",
        "PostTime",
        "UpdateTime",
        "StateID",
        "OrderNumber",
        "RechargeType",
        "FeeType",
        "CardNo",
        "ResultCode",
        "ResultMessage",
        "LoadNo",
        "IsApproval",
        "ApprovalTime",
    };
    const char* const gszApplyInMoneyCreateColType[AIMT_Max] = {
        "int(25) NOT NULL AUTO_INCREMENT COMMENT '��ˮID' primary key",
        "varchar(64) COLLATE utf8_bin DEFAULT '' COMMENT '������û�ID'",
        "varchar(64) NOT NULL COLLATE utf8_bin DEFAULT '' COMMENT '�������û�ID'",
        "int(11)",
        "double(18,3) NOT NULL DEFAULT '0.000' COMMENT '�����ʽ�'",
        "varchar(200) COLLATE utf8_bin",
        "varchar(100) COLLATE utf8_bin",
        "varchar(50) COLLATE utf8_bin",
        "DATETIME",
        "DATETIME",
        "smallint(6)",
        "varchar(50) COLLATE utf8_bin",
        "tinyint(4)",
        "tinyint(4)",
        "varchar(50) COLLATE utf8_bin",
        "varchar(50) COLLATE utf8_bin",
        "varchar(200) COLLATE utf8_bin",
        "varchar(50) COLLATE utf8_bin",
        "tinyint(4)",
        "DATETIME",
    };
#pragma endregion

#pragma region �����ʽ���˱�
    enum ApplyOutMoneyTable : int {
        AOMT_SerialNumber = 0,
        AOMT_Approval_Userid,
        AOMT_UserID,
        AOMT_IdentityCardNo,
        AOMT_BankCard,
        AOMT_BankName,
        AOMT_OutAmount,
        AOMT_PostTime,
        AOMT_IsApproval,
        AOMT_ApprovalTime,
        AOMT_Max
    };
    const char* const gszApplyOutMoneyTableName = "apply_out_money";
    const char* const gszApplyOutMoneyColName[AOMT_Max] = {
        "SerialNumber",
        "approval_userid",
        "UserID",
        "IdentityCardNo",
        "BankCard",
        "BankName",
        "OutAmount",
        "PostTime",
        "IsApproval",
        "ApprovalTime",
    };
    const char* const gszApplyOutMoneyCreateColType[AOMT_Max] = {
        "int(25) NOT NULL AUTO_INCREMENT COMMENT '��ˮID' primary key",
        "varchar(64) COLLATE utf8_bin DEFAULT '' COMMENT '������û�ID'",
        "varchar(64) NOT NULL COLLATE utf8_bin DEFAULT '' COMMENT '�������û�ID'",
        "varchar(50) NOT NULL COLLATE utf8_bin",
        "varchar(50) NOT NULL COLLATE utf8_bin",
        "varchar(100) NOT NULL COLLATE utf8_bin",
        "double(18,3) NOT NULL DEFAULT '0.000' COMMENT '�����ʽ�'",
        "DATETIME NOT NULL COMMENT '��������ʱ��'",
        "tinyint(4) NOT NULL",
        "DATETIME COMMENT '�������ʱ��'",
    };
#pragma endregion

#pragma region �ڰ����������
    enum StockBlackWhiteTable : int {
        SBWT_ContractID = 0,
        SBWT_IsBlack,
        SBWT_Max
    };
    const char* const gszStockBlackWhiteTableName = "stock_blackwhite";
    const char* const gszStockBlackWhiteColName[SBWT_Max] = {
        "contract_id",
        "is_black",
    };
    const char* const gszStockBlackWhiteCreateColType[SBWT_Max] = {
        "varchar(64) COLLATE utf8_bin DEFAULT '' COMMENT '��ԼID' primary key",
        "tinyint(2) NOT NULL COMMENT '�Ƿ������'",
    };
#pragma endregion

#pragma region ��ֹ���׹�������
    enum ForbidTradeTable : int {
        FTT_ID = 0,
        FTT_OpType,
        FTT_BOpen,
        FTT_Max
    };
    const char* const gszForbidTradeTableName = "forbid_trade";
    const char* const gszForbidTradeColName[FTT_Max] = {
        "risk_id",
        "risk_op",
        "is_open",
    };
    const char* const gszForbidTradeCreateColType[FTT_Max] = {
        "int(2) NOT NULL DEFAULT '0' COMMENT '�����Ŀ' primary key",
        "int(2) NOT NULL DEFAULT '0' COMMENT '��������'",
        "tinyint(2) NOT NULL COMMENT '�Ƿ���'",
    };
#pragma endregion

#pragma region �ֱֲ�����������
    enum PositionRateTable : int {
        PRT_ID = 0,
        PRT_Rate,
        PRT_BOpen,
        PRT_Max
    };
    const char* const gszPositionRateTableName = "position_rate";
    const char* const gszPositionRateColName[PRT_Max] = {
        "pos_rate_id",
        "pos_rate",
        "is_open",
    };
    const char* const gszPositionRateCreateColType[PRT_Max] = {
        "int(2) NOT NULL DEFAULT '0' COMMENT '��Ŀ' primary key",
        "int(3) NOT NULL DEFAULT '0' COMMENT '�ֱֲ���'",
        "tinyint(2) NOT NULL COMMENT '�Ƿ���'",
    };
#pragma endregion

#pragma region ��ѡ�ɹ����
    enum CustomStockTable : int {
        CST_UserID = 0,
        CST_ContractID,
        CST_Max
    };
    const char* const gszCustomStockTableName = "custom_stock";
    const char* const gszCustomStockColName[CST_Max] = {
        "user_id",
        "contract_id",
    };
    const char* const gszCustomStockCreateColType[SBWT_Max] = {
        "varchar(64) COLLATE utf8_bin DEFAULT '' COMMENT '�˻�ID'",
        "varchar(64) COLLATE utf8_bin DEFAULT '' COMMENT '��ԼID'",
    };
#pragma endregion

#pragma region ����Ӷ���
    enum AgencyCommissionChangeTable : int {
        AgyCCT_Stream = 0,
        AgyCCT_UserID,
        AgyCCT_SourceUserID,
        AgyCCT_Before,
        AgyCCT_After,
        AgyCCT_CommissionRate,
        AgyCCT_ChangeMoney,
        AgyCCT_Type,
        AgyCCT_Remark,
        AgyCCT_Time,
        AgyCCT_Max,
    };
    const char* const gszAgencyCommissionChangeTableName = "agency_commission_detail";
    const char* const gszAgencyCommissionChangeColName[AgyCCT_Max] = {
        "stream",
        "user_id",
        "source_user_id",
        "before_total",
        "after_total",
        "commission_rate",
        "change_money",
        "type",
        "remark",
        "create_time",
    };
    const char* const gszAgencyCommissionChangeCreateColType[AgyCCT_Max] = {
        "int(10) unsigned NOT NULL AUTO_INCREMENT COMMENT 'ҵ��ID' primary key",
        "varchar(64) COLLATE utf8_bin NOT NULL DEFAULT '' COMMENT '�û�ID'",
        "varchar(64) COLLATE utf8_bin NOT NULL DEFAULT '' COMMENT 'Ӷ����Դ�û�ID'",
        "double(32,8) NOT NULL DEFAULT '0.00000000' COMMENT '�仯ǰ���ʽ�, ��δ����'",
        "double(32,8) NOT NULL DEFAULT '0.00000000' COMMENT '�仯�����ʽ�, ��δ����'",
        "double(32,8) NOT NULL DEFAULT '0.00000000' COMMENT '��ǰ������ȡ����'",
        "double(32,8) NOT NULL DEFAULT '0.00000000' COMMENT '�䶯�ʽ�'",
        "int(2) NOT NULL DEFAULT '-1' COMMENT '�䶯����'",
        "varchar(1024) COLLATE utf8_bin DEFAULT '' COMMENT '��ע��Ϣ'",
        "DATETIME COMMENT '��������ʱ��'",
    };

    enum AgencyCommissionTable : int {
        AgyCT_UserID = 0,
        AgyCT_InfoMatchTotal,
        AgyCT_TradeFeeTotal,
        AgyCT_CommissionTotal,
        AgyCT_Max,
    };
    const char* const gszAgencyCommissionTableName = "agency_commission";
    const char* const gszAgencyCommissionColName[AgyCT_Max] = {
        "user_id",
        "infomatch",
        "trade_fee",
        "commission",
    };
    const char* const gszAgencyCommissionCreateColType[AgyCT_Max] = {
        "varchar(64) COLLATE utf8_bin DEFAULT '' COMMENT '�û�ID' primary key",
        "double(32,8) NOT NULL DEFAULT '0.00000000' COMMENT '�ۼ���Ϣ��Ϸ�'",
        "double(32,8) NOT NULL DEFAULT '0.00000000' COMMENT '�ۼƽ�����������'",
        "double(32,8) NOT NULL DEFAULT '0.00000000' COMMENT '�ۼ�Ӷ��'",
    };

    enum AgencyCommissRecodeTable : int {
        AgyCRT_UserID = 0,
        AgyCRT_Date,
        AgyCRT_InfoMatchTotal,
        AgyCRT_TradeFeeTotal,
        AgyCRT_CommissionTotal,
        AgyCRT_Max,
    };
    const char* const gszAgencyCommissRecodeTableName = "agency_commission_recode";
    const char* const gszAgencyCommissRecodeColName[AgyCRT_Max] = {
        "user_id",
        "recode_date",
        "infomatch",
        "trade_fee",
        "commission",
    };
    const char* const gszAgencyCommissRecodeCreateColType[AgyCRT_Max] = {
        "varchar(64) COLLATE utf8_bin DEFAULT '' COMMENT '�û�ID'",
        "DATE COMMENT '��������'",
        "double(32,8) NOT NULL DEFAULT '0.00000000' COMMENT '�ۼ���Ϣ��Ϸ�'",
        "double(32,8) NOT NULL DEFAULT '0.00000000' COMMENT '�ۼƽ�����������'",
        "double(32,8) NOT NULL DEFAULT '0.00000000' COMMENT '�ۼ�Ӷ��'",
    };

#pragma endregion

#pragma region �����ֳɱ�
    enum AgencyProfitChangeTable : int {
        AgyPCT_Stream = 0,
        AgyPCT_UserID,
        AgyPCT_SourceUserID,
        AgyPCT_Before,
        AgyPCT_After,
        AgyPCT_CommissionRate,
        AgyPCT_ChangeMoney,
        AgyPCT_Type,
        AgyPCT_Remark,
        AgyPCT_Time,
        AgyPCT_Max,
    };
    const char* const gszAgencyProfitChangeTableName = "agency_profit_detail";
    const char* const gszAgencyProfitChangeColName[AgyPCT_Max] = {
        "stream",
        "user_id",
        "source_user_id",
        "before_total",
        "after_total",
        "commission_rate",
        "change_money",
        "type",
        "remark",
        "create_time",
    };
    const char* const gszAgencyProfitChangeCreateColType[AgyPCT_Max] = {
        "int(10) unsigned NOT NULL AUTO_INCREMENT COMMENT 'ҵ��ID' primary key",
        "varchar(64) COLLATE utf8_bin NOT NULL DEFAULT '' COMMENT '�û�ID'",
        "varchar(64) COLLATE utf8_bin NOT NULL DEFAULT '' COMMENT 'Ӷ����Դ�û�ID'",
        "double(32,8) NOT NULL DEFAULT '0.00000000' COMMENT '�仯ǰ���ʽ�, ��δ����'",
        "double(32,8) NOT NULL DEFAULT '0.00000000' COMMENT '�仯�����ʽ�, ��δ����'",
        "double(32,8) NOT NULL DEFAULT '0.00000000' COMMENT '��ǰ������ȡ����'",
        "double(32,8) NOT NULL DEFAULT '0.00000000' COMMENT '�䶯�ʽ�'",
        "int(2) NOT NULL DEFAULT '-1' COMMENT '�䶯����'",
        "varchar(1024) COLLATE utf8_bin DEFAULT '' COMMENT '��ע��Ϣ'",
        "DATETIME COMMENT '��������ʱ��'",
    };

    enum AgencyProfitTable : int {
        AgyPT_UserID = 0,
        AgyPT_ProfitTotal,
        AgyPT_Max,
    };
    const char* const gszAgencyProfitTableName = "agency_profit";
    const char* const gszAgencyProfitColName[AgyPT_Max] = {
        "user_id",
        "profit",
    };
    const char* const gszAgencyProfitCreateColType[AgyPT_Max] = {
        "varchar(64) COLLATE utf8_bin DEFAULT '' COMMENT '�û�ID' primary key",
        "double(32,8) NOT NULL DEFAULT '0.00000000' COMMENT '�ۼƷֳ�'",
    };

    enum AgencyProfitRecodeTable : int {
        AgyPRT_UserID = 0,
        AgyPRT_Date,
        AgyPRT_ProfitTotal,
        AgyPRT_Max,
    };
    const char* const gszAgencyProfitRecodeTableName = "agency_profit_recode";
    const char* const gszAgencyProfitRecodeColName[AgyPRT_Max] = {
        "user_id",
        "recode_date",
        "profit",
    };
    const char* const gszAgencyProfitRecodeCreateColType[AgyPRT_Max] = {
        "varchar(64) COLLATE utf8_bin DEFAULT '' COMMENT '�û�ID'",
        "DATE COMMENT '��������'",
        "double(32,8) NOT NULL DEFAULT '0.00000000' COMMENT '�ۼƷֳ�'",
    };

#pragma endregion

	enum VersionTable : int {
		Version_Name = 0,
		Version_Max,
	};
	const char* const gszVersionTableName = "version_table";
	const char* const gszVersionColName[RiskT_Max] = {
		"version_name",
	};
	const char* const gszVersionCreateColType[RiskT_Max] = {
		"varchar(32) COLLATE utf8_bin DEFAULT '' COMMENT '�汾����' primary key",
	};

#pragma region ��ȯ�ֲ�
	enum MarginPositionTable : int {
		MPT_PositionID = 0,
		MPT_UserID,
		MPT_ExchangeID,
		MPT_ContractID,
		MPT_Direct,
		MPT_PositionVol,
		MPT_PositionTVol,
		MPT_CurrencyID,
		MPT_PositionCostPrice,
		MPT_TradeAvePrice,
		MPT_StockArea,
		MPT_PositionFreezeVol,
		MPT_Max
	};
	const char* const gszMarginPositionTableName = "margin_position_info";
	const char* const gszMarginPositionColName[MPT_Max] = {
		"position_id",
		"user_id",
		"exchange_id",
		"contract_id",
		"direct_type",
		"position_vol",
		"position_T_vol",
		"currency_id",
		"position_cost_price",
		"trade_ave_price",
		"stock_area",
		"position_freeze_vol",
	};
	const char* const gszMarginPositionCreateColType[MPT_Max] = {
		"varchar(64) COLLATE utf8_bin DEFAULT '' COMMENT '�ֲ�ID' primary key",
		"varchar(64) COLLATE utf8_bin NOT NULL DEFAULT '' COMMENT '�ʻ���ʶ(�û�ID)��ϵͳ�ڲ�ʹ��'",
		"varchar(255) COLLATE utf8_bin NOT NULL DEFAULT '' COMMENT '������ID'",
		"varchar(64) COLLATE utf8_bin NOT NULL DEFAULT '' COMMENT '��ԼID'",
		"tinyint(1) NOT NULL DEFAULT '1' COMMENT '��������,ͬʱҲ�ǿ�ƽ��־,���ʾ����,����ʾƽ��'",
		"int(10) NOT NULL DEFAULT '0' COMMENT '�ֲ�����'",
		"int(10) NOT NULL DEFAULT '0' COMMENT 'T+1�ֲ�����'",
		"varchar(64) COLLATE utf8_bin NOT NULL DEFAULT '' COMMENT '����ID'",
		"double(32,8) NOT NULL DEFAULT '0.00000000' COMMENT '�ֲ��ܼ�'",
		"double(32,8) NOT NULL DEFAULT '0.00000000' COMMENT '�ɽ�����'",
		"int(2) NOT NULL DEFAULT '-1' COMMENT '������Ʊ����'",
		"int(10) NOT NULL DEFAULT '0' COMMENT 'ƽ��ί�ж���ֲ�����'",
	};
#pragma endregion

#pragma region ��ȯ�ɽ�
	enum MarginTradeTable : int {
		MTT_TradeID = 0,
		MTT_ShadowTradeID,
		MTT_OrderStream,
		MTT_PositionID,
		MTT_UserID,
		MTT_ExchangeID,
		MTT_ContractID,
		MTT_GenerateDateTime,
		MTT_Direct,
		MTT_TradeVol,
		MTT_CurrencyRate,
		MTT_CurrencyID,
		MTT_TradeAvePrice,
		MTT_CloseProfit,
		MTT_OperatorType,
		MTT_StockArea,
		MTT_TradeFee,
		MTT_StampFee,
		MTT_TransferFee,
		MTT_InfomatchFee,
		MTT_DayInterset,
		MTT_IntersetFund,
		MTT_Max
	};
	const char* const gszMarginTradeTableName = "margin_trade_info";
	const char* const gszMarginTradeColName[MTT_Max] = {
		"trade_id",
		"shadow_trade_id",
		"order_stream",
		"position_id",
		"user_id",
		"exchange_id",
		"contract_id",
		"generate_datetime",
		"direct_type",
		"trade_vol",
		"currency_rate",
		"currency_id",
		"trade_ave_price",
		"close_profit",
		"op_type",
		"stock_area",
		"trade_fee",
		"stamp_fee",
		"transfer_fee",
		"infomatch_fee",
		"day_interset",
		"interset_fund",
	};
	const char* const gszMarginTradeCreateColType[MTT_Max] = {
		"varchar(64) COLLATE utf8_bin DEFAULT '' COMMENT 'ϵͳ�ڳɽ�����' primary key",
		"varchar(64) COLLATE utf8_bin DEFAULT '' COMMENT 'Ӱ�Ӷ������'",
		"varchar(128) COLLATE utf8_bin DEFAULT '' COMMENT 'ί������'",
		"varchar(64) COLLATE utf8_bin DEFAULT '' COMMENT '�ֲ�ID'",
		"varchar(64) COLLATE utf8_bin NOT NULL DEFAULT '' COMMENT '�ʻ���ʶ(�û�ID)��ϵͳ�ڲ�ʹ��'",
		"varchar(255) COLLATE utf8_bin NOT NULL DEFAULT '' COMMENT '������ID'",
		"varchar(64) COLLATE utf8_bin NOT NULL DEFAULT '' COMMENT '��ԼID'",
		"DATETIME COMMENT '�ɽ�����ʱ��'",
		"tinyint(1) NOT NULL DEFAULT '1' COMMENT '��������,ͬʱҲ�ǿ�ƽ��־,���ʾ����,����ʾƽ��'",
		"int(10) NOT NULL DEFAULT '0' COMMENT '�ɽ�����'",
		"double(32,8) NOT NULL DEFAULT '0.00000000' COMMENT '��ǰ��Ӧ���һ���'",
		"varchar(64) COLLATE utf8_bin NOT NULL DEFAULT '' COMMENT '����ID'",
		"double(32,8) NOT NULL DEFAULT '0.00000000' COMMENT '�ɽ�����'",
		"double(32,8) NOT NULL DEFAULT '0.00000000' COMMENT 'ƽ��ӯ��'",
		"int(2) NOT NULL DEFAULT '-1' COMMENT '����Ա����'",
		"int(2) NOT NULL DEFAULT '-1' COMMENT '������Ʊ����'",
		"double(32,8) NOT NULL DEFAULT '0.00000000' COMMENT '����Ӷ��������'",
		"double(32,8) NOT NULL DEFAULT '0.00000000' COMMENT 'ƽ��ӡ��˰��'",
		"double(32,8) NOT NULL DEFAULT '0.00000000' COMMENT '������'",
		"double(32,8) NOT NULL DEFAULT '0.00000000' COMMENT '��Ϣ��Ϸ�'",
		"double(32,8) NOT NULL DEFAULT '0.00000000' COMMENT '����Ϣ'",
		"double(32,8) NOT NULL DEFAULT '0.00000000' COMMENT '��Ϣ�ʽ�'",
	};
#pragma endregion

#pragma region ��ȯί��
	enum MarginOrderTable : int {
		MOT_OrderStream = 0,
		MOT_OrderID,
		MOT_UserID,
		MOT_ContractID,
		MOT_OrderState,
		MOT_OrderStateExplain,
		MOT_OrderRef,
		MOT_LoclaTmp_OrderRef,
		MOT_ShadowOrderID,
		MOT_GenerateDateTime,
		MOT_UpdateDateTime,
		MOT_CurrencyRate,
		MOT_CurrencyID,
		MOT_OrderPrice,
		MOT_Direct,
		MOT_OrderVol,
		MOT_EffectedVol,
		MOT_TradeVol,
		MOT_BFreezePosition,
		MOT_FreezeMoney,
		MOT_BFreezeMoney,
		MOT_OrderType,
		MOT_OrderTradeMode,
		MOT_OrderTradePrice,
		MOT_OrderPositionCost,
		MOT_SystemOrderID,
		MOT_ExchangeID,
		MOT_ApiType,
		MOT_OperatorType,
		MOT_OrderMode,
		MOT_ValidDateTime,
		MOT_StockArea,
		MOT_CurTradeFee,
		MOT_CurStampFee,
		MOT_CurTransferFee,
		MOT_CurInfomatchFee,
		MOT_Max
	};
	const char* const gszMarginOrderTableName = "margin_order_table";
	const char* const gszMarginOrderTableColName[MOT_Max] = {
		"order_stream",
		"order_id",
		"user_id",
		"contract_id",
		"order_state",
		"orser_state_explain",
		"order_ref",
		"order_loacltmp_ref",
		"shadow_order_id",
		"generate_datetime",
		"update_datetime",
		"currency_rate",
		"currency_id",
		"order_price",
		"direct_type",
		"order_vol",
		"effected_vol",
		"trade_vol",
		"b_freeze_position",
		"freeze_money",
		"b_freeze_money",
		"order_type",
		"order_trade_mode",
		"order_trade_price",
		"order_position_cost",
		"system_order_id",
		"exchange_id",
		"api_type",
		"op_type",
		"order_mode",
		"valid_datetime",
		"stock_area",
		"cur_trade_fee",
		"cur_stamp_fee",
		"cur_transfer_fee",
		"cur_infomatch_fee",
	};
	const char* const gszMarginOrderTableColType[MOT_Max] = {
		"varchar(128) COLLATE utf8_bin NOT NULL DEFAULT '' COMMENT 'ϵͳ������,�û�ID+&+GUID' primary key",
		"varchar(64) COLLATE utf8_bin DEFAULT '' COMMENT 'ί��ID'",
		"varchar(64) COLLATE utf8_bin NOT NULL DEFAULT '' COMMENT '�ʻ���ʶ(�û�ID)��ϵͳ�ڲ�ʹ��'",
		"varchar(64) COLLATE utf8_bin NOT NULL DEFAULT '' COMMENT '��ԼID'",
		"int(2) NOT NULL DEFAULT '-1' COMMENT 'ί��״̬'",
		"int(2) NOT NULL DEFAULT '-1' COMMENT 'ί��״̬˵��'",
		"varchar(64) COLLATE utf8_bin DEFAULT '' COMMENT '��ί��δ��Чʱ,������ҪΨһ��ʾ��ί��,��������һ��Ψһ����,ʹ�øñ�����б�ʶ'",
		"varchar(64) COLLATE utf8_bin DEFAULT '' COMMENT '�ͻ����ύ��ί�б��'",
		"varchar(64) COLLATE utf8_bin DEFAULT '' COMMENT 'Ӱ�Ӷ�����ţ� �ͻ�����ʾʹ��'",
		"DATETIME COMMENT 'ί�д�������ʱ��'",
		"DATETIME COMMENT ' ί��״̬����������ʱ��'",
		"double(32,8) NOT NULL DEFAULT '0.00000000' COMMENT '��ǰ��Ӧ���һ���'",
		"varchar(64) NOT NULL DEFAULT ''COMMENT '����ID'",
		"double(32,8) NOT NULL DEFAULT '0.00000000' COMMENT 'ί�м۸�'",
		"tinyint(1) NOT NULL DEFAULT '1' COMMENT '��������,ͬʱҲ�ǿ�ƽ��־,���ʾ����,����ʾƽ��'",
		"int(10) NOT NULL DEFAULT '0' COMMENT 'ί������'",
		"int(10) NOT NULL DEFAULT '0' COMMENT '����Ч����'",
		"int(10) NOT NULL DEFAULT '0' COMMENT '�ɽ�����'",
		"tinyint(1) NOT NULL DEFAULT '0' COMMENT '�Ƿ��ж���ֲ�'",
		"double(32,8) NOT NULL DEFAULT '0.00000000' COMMENT 'ί�ж������ʽ�'",
		"tinyint(1) NOT NULL DEFAULT '0' COMMENT '�Ƿ��ж����ʽ�'",
		"int(2) NOT NULL DEFAULT '-1' COMMENT '�µ�ί������'",
		"int(2) NOT NULL DEFAULT '-1' COMMENT 'ί�н���ģʽ'",
		"double(32,8) NOT NULL DEFAULT '0.00000000' COMMENT 'ί�гɽ���'",
		"double(32,8) NOT NULL DEFAULT '0.00000000' COMMENT '�ֲֳɱ�'",
		"varchar(64) COLLATE utf8_bin NOT NULL DEFAULT '' COMMENT '������ί�б��'",
		"varchar(255) COLLATE utf8_bin NOT NULL DEFAULT '' COMMENT '������ID'",
		"int(2) NOT NULL DEFAULT '-1' COMMENT '�ӿ�����'",
		"int(2) NOT NULL DEFAULT '-1' COMMENT '����Ա����'",
		"int(2) NOT NULL DEFAULT '-1' COMMENT '�µ�ί��ģʽ'",
		"DATETIME COMMENT '��Ч����'",
		"int(2) NOT NULL DEFAULT '-1' COMMENT '������Ʊ����'",
		"double(32,8) NOT NULL DEFAULT '0.00000000' COMMENT '��ǰ����Ӷ��������'",
		"double(32,8) NOT NULL DEFAULT '0.00000000' COMMENT '��ǰƽ��ӡ��˰��'",
		"double(32,8) NOT NULL DEFAULT '0.00000000' COMMENT '��ǰ������'",
		"double(32,8) NOT NULL DEFAULT '0.00000000' COMMENT '��ǰ��Ϣ��Ϸ�'",
	};
#pragma endregion

#pragma region ��ȯ��Ϣ
	enum MarginInfoTable : int {
		MIT_SumQty = 0,
		MIT_Interest,
		MIT_Max
	};
	const char* const gszMarginInfoTableName = "margin_Info_table";
	const char* const gszMarginInfoTableColName[MIT_Max] = {
		"sum_qty",
		"Interest",
	};
	const char* const gszMarginInfoTableColType[MIT_Max] = {
		"int(10) NOT NULL DEFAULT '0' COMMENT '����������'",
		"double(32,8) NOT NULL DEFAULT '0.00000000' COMMENT '��ȯ��Ϣ'",
	};
#pragma endregion

#pragma region ��ȯʣ��������Ϣ
	enum MarginLeftQtyTable : int {
		MLQT_ContractID = 0,
		MLQT_LeftQty,
		MLQT_Max
	};
	const char* const gszMarginLeftQtyTableName = "margin_left_table";
	const char* const gszMarginLeftQtyTableColName[MLQT_Max] = {
		"contract_id",
		"left_qty",
	};
	const char* const gszMarginLeftQtyTableColType[MLQT_Max] = {
		"varchar(64) COLLATE utf8_bin DEFAULT '' COMMENT '��ԼID' primary key",
		"int(10) NOT NULL DEFAULT '0' COMMENT '����ʣ������'",
	};
#pragma endregion


#pragma region ��Ϣ����
	enum SumInterestTable : int {
		SIT_UserId = 0,
		SIT_SumInterest,
		SIT_DateTime,
		SIT_Max
	};
	const char* const gszSumInterestTableName = "interest_statistics_table";
	const char* const gszSumInterestTableColName[SIT_Max] = {
		"user_id",
		"sum_interest",
		"date_time",
	};
	const char* const gszSumInterestTableColType[SIT_Max] = {
		"varchar(64) CHARACTER SET utf8 NOT NULL COMMENT '�û�id'  primary key",
		"double(32,8) NOT NULL DEFAULT '0.00000000' COMMENT '�ۼ���Ϣ'",
		"DATE COMMENT '��������'",
	};
	// ��Ϣ��ϸ
	enum InterestDetailTable : int {
		InDT_Stream = 0,
		InDT_UserId,
		InDT_InterestChange,
		InDT_ChanegTime,
		InDT_ChangeType,
		InDT_InterestSource,
		InDT_InterestRate,
		InDT_Max,
	};
	const char* const gszInterestDetailTableName = "interest_detail_table";
	const char* const gszInterestDetailTableColName[InDT_Max] = {
		"stream",
		"user_id",
		"interest_change",
		"change_time",
		"change_type",
		"interest_source",
		"interest_rate",
	};
	const char* const gszInterestDetailTableColType[InDT_Max] = {
		"int(10) unsigned NOT NULL AUTO_INCREMENT COMMENT 'ҵ��ID' primary key",
		"varchar(64) CHARACTER SET utf8 NOT NULL COMMENT '�û�id'",
		"double(32,8) NOT NULL DEFAULT '0.00000000' COMMENT '��Ϣ�䶯'",
		"DATETIME COMMENT '�䶯ʱ��'",
		"int(2) NOT NULL DEFAULT '-1' COMMENT '�䶯����'",
		"varchar(64) CHARACTER SET utf8 NOT NULL COMMENT '�䶯��Դ'",
		"double(32,8) NOT NULL DEFAULT '0.00000000' COMMENT '��Ϣ����'",
	}; 
#pragma endregion
}

#endif