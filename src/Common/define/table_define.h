/*************************************************
Copyright (C), 2017, HX Tech Co., Ltd.
File name:      table_define.h
Author:			XuYC
Version:
Date:
Description:    提供具体的结构体定义,加快编译速度
                注:现阶段各表间不要建立关联,便于后期移植非关系型数据库,部分关键数据后期统一修改为关系型数据库的关联结构
*************************************************/

#ifndef __TABLE_DEFINE_H__
#define __TABLE_DEFINE_H__

namespace OperationManager {

#pragma region 用户信息表
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
        "varchar(64) COLLATE utf8_bin NOT NULL DEFAULT '' COMMENT '账户标识(用户ID)，系统内部使用' primary key",
        "varchar(64) COLLATE utf8_bin DEFAULT '' COMMENT '创建者账户标识，系统内部使用'",
        "varchar(64) COLLATE utf8_bin DEFAULT '' COMMENT '从属账户标识(用户ID)，系统内部使用'",
        "varchar(50) COLLATE utf8_bin NOT NULL DEFAULT '' COMMENT '登录名'",
        "varchar(50) COLLATE utf8_bin DEFAULT '' COMMENT '昵称'",
        "varchar(24) COLLATE utf8_bin NOT NULL DEFAULT '' COMMENT '密码'",
        "varchar(50) COLLATE utf8_bin NOT NULL DEFAULT '' COMMENT '账户名'",
        "varchar(64) COLLATE utf8_bin DEFAULT '' COMMENT '对应资金账户标识(用户ID)，系统内部使用'",
        "int NOT NULL DEFAULT '-1' COMMENT '层级'",
        "int(2) NOT NULL DEFAULT '-1' COMMENT '账户类型'",
        "int(2) NOT NULL DEFAULT '-1' COMMENT '账户状态'",
        "int(2) NOT NULL DEFAULT '-1' COMMENT '账户权限控制模式'",
        "varchar(1024) COLLATE utf8_bin DEFAULT '' COMMENT '推广链接'",
        "varchar(50) COLLATE utf8_bin DEFAULT '' COMMENT '真实姓名'",
        "varchar(18) COLLATE utf8_bin DEFAULT '' COMMENT '手机号'",
        "varchar(20) COLLATE utf8_bin DEFAULT '' COMMENT '身份证号'",
        "DATETIME COMMENT '开户时间'",
        "DATETIME COMMENT '更新时间'",
        "DATETIME COMMENT '有效期时间'",
        "int(2) NOT NULL DEFAULT '-1' COMMENT '管理账户属性'",
        "int NOT NULL DEFAULT '-1' COMMENT '允许下设的最大层级'",
        "int NOT NULL DEFAULT '-1' COMMENT '允许下设的最大个数'",
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
        "varchar(64) COLLATE utf8_bin NOT NULL DEFAULT '' COMMENT '账户标识(用户ID)，系统内部使用' primary key",
        "varchar(64) COLLATE utf8_bin NOT NULL DEFAULT '' COMMENT '创建者账户标识，系统内部使用'",
        "varchar(64) COLLATE utf8_bin NOT NULL DEFAULT '' COMMENT '从属账户标识(用户ID)，系统内部使用'",
        "varchar(50) COLLATE utf8_bin NOT NULL DEFAULT '' COMMENT '登录名'",
        "varchar(50) COLLATE utf8_bin NOT NULL DEFAULT '' COMMENT '昵称'",
        "varchar(24) COLLATE utf8_bin NOT NULL DEFAULT '' COMMENT '密码'",
        "varchar(50) COLLATE utf8_bin NOT NULL DEFAULT '' COMMENT '账户名'",
        "varchar(64) COLLATE utf8_bin DEFAULT '' COMMENT '对应资金账户标识(用户ID)，系统内部使用'",
        "int NOT NULL DEFAULT '-1' COMMENT '层级'",
        "int(2) NOT NULL DEFAULT '-1' COMMENT '账户属性'",
        "int(2) NOT NULL DEFAULT '-1' COMMENT '账户类型'",
        "int(2) NOT NULL DEFAULT '-1' COMMENT '账户状态'",
        "int(2) NOT NULL DEFAULT '-1' COMMENT '账户权限控制模式'",
        "varchar(1024) COLLATE utf8_bin NOT NULL DEFAULT '' COMMENT '推广链接'",
        "varchar(50) COLLATE utf8_bin DEFAULT '' COMMENT '真实姓名'",
        "varchar(18) COLLATE utf8_bin DEFAULT '' COMMENT '手机号'",
        "varchar(20) COLLATE utf8_bin DEFAULT '' COMMENT '身份证号'",
        "DATETIME COMMENT '开户时间'",
        "DATETIME COMMENT '更新时间'",
        "DATETIME COMMENT '有效期时间'",
		"varchar(64) COLLATE utf8_bin NOT NULL DEFAULT '' COMMENT '审核者，系统内部使用'",
		"DATETIME COMMENT '审核时间'",
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
        "varchar(64) COLLATE utf8_bin NOT NULL DEFAULT '' COMMENT '账户标识(用户ID)，系统内部使用' primary key",
        "varchar(64) COLLATE utf8_bin DEFAULT '' COMMENT '创建者账户标识，系统内部使用'",
        "varchar(64) COLLATE utf8_bin DEFAULT '' COMMENT '从属账户标识(用户ID)，系统内部使用'",
        "varchar(50) COLLATE utf8_bin NOT NULL DEFAULT '' COMMENT '登录名'",
        "varchar(50) COLLATE utf8_bin DEFAULT '' COMMENT '昵称'",
        "varchar(24) COLLATE utf8_bin NOT NULL DEFAULT '' COMMENT '密码'",
        "varchar(50) COLLATE utf8_bin NOT NULL DEFAULT '' COMMENT '账户名'",
        "int NOT NULL DEFAULT '-1' COMMENT '层级'",
        "int(2) NOT NULL DEFAULT '-1' COMMENT '账户属性'",
        "int(2) NOT NULL DEFAULT '-1' COMMENT '账户类型'",
        "int(2) NOT NULL DEFAULT '-1' COMMENT '账户状态'",
        "int(2) NOT NULL DEFAULT '-1' COMMENT '账户权限控制模式'",
        "varchar(1024) COLLATE utf8_bin DEFAULT '' COMMENT '推广链接'",
        "varchar(50) COLLATE utf8_bin DEFAULT '' COMMENT '真实姓名'",
        "varchar(18) COLLATE utf8_bin DEFAULT '' COMMENT '手机号'",
        "varchar(20) COLLATE utf8_bin DEFAULT '' COMMENT '身份证号'",
        "DATETIME COMMENT '开户时间'",
        "DATETIME COMMENT '更新时间'",
        "DATETIME COMMENT '有效期时间'",
        "int NOT NULL DEFAULT '-1' COMMENT '允许下设的最大层级'",
        "int NOT NULL DEFAULT '-1' COMMENT '允许下设的最大个数'",
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
        "varchar(64) COLLATE utf8_bin NOT NULL DEFAULT '' COMMENT '账户标识(用户ID)，系统内部使用' primary key",
        "varchar(64) COLLATE utf8_bin NOT NULL DEFAULT '' COMMENT '创建者账户标识，系统内部使用'",
        "varchar(64) COLLATE utf8_bin NOT NULL DEFAULT '' COMMENT '从属账户标识(用户ID)，系统内部使用'",
        "varchar(50) COLLATE utf8_bin NOT NULL DEFAULT '' COMMENT '登录名'",
        "varchar(50) COLLATE utf8_bin NOT NULL DEFAULT '' COMMENT '昵称'",
        "varchar(24) COLLATE utf8_bin NOT NULL DEFAULT '' COMMENT '密码'",
        "varchar(50) COLLATE utf8_bin NOT NULL DEFAULT '' COMMENT '账户名'",
        "int NOT NULL DEFAULT '-1' COMMENT '层级'",
        "int(2) NOT NULL DEFAULT '-1' COMMENT '账户属性'",
        "int(2) NOT NULL DEFAULT '-1' COMMENT '账户类型'",
        "int(2) NOT NULL DEFAULT '-1' COMMENT '账户状态'",
        "int(2) NOT NULL DEFAULT '-1' COMMENT '账户权限控制模式'",
        "varchar(1024) COLLATE utf8_bin NOT NULL DEFAULT '' COMMENT '推广链接'",
        "varchar(50) COLLATE utf8_bin DEFAULT '' COMMENT '真实姓名'",
        "varchar(18) COLLATE utf8_bin DEFAULT '' COMMENT '手机号'",
        "varchar(20) COLLATE utf8_bin DEFAULT '' COMMENT '身份证号'",
        "varchar(50) COLLATE utf8_bin DEFAULT '' COMMENT '对应交易实盘公司名'",
        "DATETIME COMMENT '开户时间'",
        "DATETIME COMMENT '更新时间'",
        "DATETIME COMMENT '有效期时间'",
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
        "varchar(64) COLLATE utf8_bin NOT NULL DEFAULT '' COMMENT '账户标识(用户ID)，系统内部使用'",
        "int(2) NOT NULL DEFAULT '-1' COMMENT '登入登出'",
        "DATETIME COMMENT '时间'",
        "int(2) NOT NULL DEFAULT '-1' COMMENT '操作类型'",
        "varchar(40) COLLATE utf8_bin DEFAULT '' COMMENT '登录IP'",
        "varchar(200) COLLATE utf8_bin DEFAULT '' COMMENT '登录MAC'",
    };

#pragma endregion

#pragma region 账户全局数据管理表
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
        "int(2) NOT NULL DEFAULT '-1' COMMENT '商品类型' primary key",
        "int(5) NOT NULL COMMENT '累计订单编号'",
    };
#pragma endregion

#pragma region 资金信息及风控信息表
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
        "varchar(64) COLLATE utf8_bin NOT NULL DEFAULT '' COMMENT '流水单号' primary key",
        "varchar(64) COLLATE utf8_bin NOT NULL DEFAULT '' COMMENT '用户ID'",
        "double(32,8) NOT NULL DEFAULT '0.00000000' COMMENT '变化前总资金'",
        "double(32,8) NOT NULL DEFAULT '0.00000000' COMMENT '变化后总资金'",
        "double(32,8) NOT NULL DEFAULT '0.00000000' COMMENT '变动资金'",
        "int(2) NOT NULL DEFAULT '-1' COMMENT '变动类型'",
        "varchar(1024) COLLATE utf8_bin DEFAULT '' COMMENT '备注信息'",
        "DATETIME COMMENT '创建日期时间'",
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
        "varchar(64) COLLATE utf8_bin DEFAULT '' COMMENT '用户ID' primary key",
        "double(32,8) NOT NULL DEFAULT '0.00000000' COMMENT '持仓总价'",
        "int NOT NULL DEFAULT '0' COMMENT '持仓手数'",
        "double(32,8) NOT NULL DEFAULT '0.00000000' COMMENT '交易所手续费'",
        "double(32,8) NOT NULL DEFAULT '0.00000000' COMMENT '自定义手续费'",
        "double(32,8) NOT NULL DEFAULT '0.00000000' COMMENT '逻辑可提取金额(总)'",
        "double(32,8) NOT NULL DEFAULT '0.00000000' COMMENT '逻辑待解冻金额(总)'",
        "double(32,8) NOT NULL DEFAULT '0.00000000' COMMENT '提交委托时的占用资金(含手续费)'",
        "double(32,8) NOT NULL DEFAULT '0.00000000' COMMENT '用户保证金'",
        "double(32,8) NOT NULL DEFAULT '0.00000000' COMMENT '配资资金'",
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
        "varchar(64) COLLATE utf8_bin DEFAULT '' COMMENT '用户ID' primary key",
        "double(32,8) NOT NULL DEFAULT '0.00000000' COMMENT '警告线'",
        "double(32,8) NOT NULL DEFAULT '0.00000000' COMMENT '强平线'",
        "double(32,8) NOT NULL DEFAULT '0.00000000' COMMENT '限仓线'",
        "double(32,8) NOT NULL DEFAULT '0.00000000' COMMENT '杠杆比例'",
        "double(32,8) NOT NULL DEFAULT '0.00000000' COMMENT '交易所佣金比例(千分之)'",
        "double(32,8) NOT NULL DEFAULT '0.00000000' COMMENT '客户自定义佣金比例(千分之)'",
        "double(32,8) NOT NULL DEFAULT '0.00000000' COMMENT '分成比例(千分之)'",
    };

#pragma endregion

#pragma region 交易所信息表
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
        "varchar(64) COLLATE utf8_bin DEFAULT '' COMMENT '交易所ID' primary key",
        "varchar(64) COLLATE utf8_bin DEFAULT '' COMMENT '交易所名'",
        "varchar(64) COLLATE utf8_bin DEFAULT '' COMMENT '交易所代码'",
        "varchar(64) COLLATE utf8_bin DEFAULT '' COMMENT '交易时间段'",
        "varchar(64) COLLATE utf8_bin DEFAULT '' COMMENT '委托提交时间段'",
        "int(2) NOT NULL DEFAULT '-1' COMMENT '商品类型'",
    };

#pragma endregion

#pragma region 股票合约信息表
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
        "varchar(64) COLLATE utf8_bin DEFAULT '' COMMENT '合约ID' primary key",
        "varchar(64) COLLATE utf8_bin DEFAULT '' COMMENT '交易所ID'",
        "varchar(20) COLLATE utf8_bin DEFAULT '' COMMENT '合约名'",
        "varchar(20) COLLATE utf8_bin DEFAULT '' COMMENT '合约代码'",
        "int(2) NOT NULL DEFAULT '-1' COMMENT '商品类型'",
        "varchar(64) COLLATE utf8_bin DEFAULT '' COMMENT '汇率单位ID'",
        "int NOT NULL DEFAULT '-1' COMMENT '到期日天数'",
        "DATETIME COMMENT '创建时间'",
        "DATETIME COMMENT '交割日时间'",
        "DATETIME COMMENT '最后可开仓时间'",
        "double(32,8) NOT NULL DEFAULT '0.00000000' COMMENT '最小变动单位'",
        "int NOT NULL DEFAULT '-1' COMMENT '合约乘数'",
        "tinyint(1) NOT NULL DEFAULT '1' COMMENT '开仓手续费是否采用固定值'",
        "double(32,8) NOT NULL DEFAULT '0.00000000' COMMENT '开仓手续费'",
        "tinyint(1) NOT NULL DEFAULT '1' COMMENT '平昨手续费是否采用固定值'",
        "double(32,8) NOT NULL DEFAULT '0.00000000' COMMENT '平昨手续费'",
        "tinyint(1) NOT NULL DEFAULT '1' COMMENT '保证金是否采用固定值'",
        "double(32,8) NOT NULL DEFAULT '0.00000000' COMMENT '保证金'",
        "varchar(20) COLLATE utf8_bin DEFAULT '' COMMENT '显示(业绩)属性类型'",
        "int(2) NOT NULL DEFAULT '-1' COMMENT '显示(业绩)属性类型'",
        "varchar(20) COLLATE utf8_bin DEFAULT '' COMMENT '板块属性类型(航空/建筑...)'",
        "int(2) NOT NULL DEFAULT '-1' COMMENT '所属股票类型'",
        "int(2) NOT NULL DEFAULT '-1' COMMENT '所属股票板块属性(沪深板/新三板...)'",
        "double(32,8) NOT NULL DEFAULT '0.00000000' COMMENT '总股本'",
    };
#pragma endregion

#pragma region 股票委托
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
        "varchar(128) COLLATE utf8_bin NOT NULL DEFAULT '' COMMENT '系统内流号,用户ID+&+GUID' primary key",
        "varchar(64) COLLATE utf8_bin DEFAULT '' COMMENT '委托ID'",
        "varchar(64) COLLATE utf8_bin NOT NULL DEFAULT '' COMMENT '帐户标识(用户ID)，系统内部使用'",
        "varchar(64) COLLATE utf8_bin NOT NULL DEFAULT '' COMMENT '合约ID'",
        "int(2) NOT NULL DEFAULT '-1' COMMENT '委托状态'",
        "int(2) NOT NULL DEFAULT '-1' COMMENT '委托状态说明'",
        "varchar(64) COLLATE utf8_bin DEFAULT '' COMMENT '当委托未生效时,本地需要唯一标示该委托,本地生成一个唯一编码,使用该编码进行标识'",
        "varchar(64) COLLATE utf8_bin DEFAULT '' COMMENT '客户端提交的委托编号'",
        "varchar(64) COLLATE utf8_bin DEFAULT '' COMMENT '影子订单编号， 客户端显示使用'",
        "DATETIME COMMENT '委托创建日期时间'",
        "DATETIME COMMENT ' 委托状态最后更新日期时间'",
        "double(32,8) NOT NULL DEFAULT '0.00000000' COMMENT '当前对应基币汇率'",
        "varchar(64) NOT NULL DEFAULT ''COMMENT '币种ID'",
        "double(32,8) NOT NULL DEFAULT '0.00000000' COMMENT '委托价格'",
        "tinyint(1) NOT NULL DEFAULT '1' COMMENT '买卖方向,同时也是开平标志,买表示开仓,卖表示平仓'",
        "int(10) NOT NULL DEFAULT '0' COMMENT '委托手数'",
        "int(10) NOT NULL DEFAULT '0' COMMENT '已生效手数'",
        "int(10) NOT NULL DEFAULT '0' COMMENT '成交手数'",
        "tinyint(1) NOT NULL DEFAULT '0' COMMENT '是否有冻结持仓'",
        "double(32,8) NOT NULL DEFAULT '0.00000000' COMMENT '委托冻结总资金'",
        "tinyint(1) NOT NULL DEFAULT '0' COMMENT '是否有冻结资金'",
        "int(2) NOT NULL DEFAULT '-1' COMMENT '下单委托类型'",
        "int(2) NOT NULL DEFAULT '-1' COMMENT '委托交易模式'",
        "double(32,8) NOT NULL DEFAULT '0.00000000' COMMENT '委托成交价'",
        "double(32,8) NOT NULL DEFAULT '0.00000000' COMMENT '持仓成本'",
        "varchar(64) COLLATE utf8_bin NOT NULL DEFAULT '' COMMENT '交易所委托编号'",
        "varchar(255) COLLATE utf8_bin NOT NULL DEFAULT '' COMMENT '交易所ID'",
        "int(2) NOT NULL DEFAULT '-1' COMMENT '接口类型'",
        "int(2) NOT NULL DEFAULT '-1' COMMENT '操作员类型'",
        "int(2) NOT NULL DEFAULT '-1' COMMENT '下单委托模式'",
        "DATETIME COMMENT '有效日期'",
        "int(2) NOT NULL DEFAULT '-1' COMMENT '所属股票类型'",
        "double(32,8) NOT NULL DEFAULT '0.00000000' COMMENT '当前交易佣金手续费'",
        "double(32,8) NOT NULL DEFAULT '0.00000000' COMMENT '当前平仓印花税费'",
        "double(32,8) NOT NULL DEFAULT '0.00000000' COMMENT '当前过户费'",
        "double(32,8) NOT NULL DEFAULT '0.00000000' COMMENT '当前信息撮合费'",
    };
#pragma endregion

#pragma region 外盘委托
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
        "varchar(128) COLLATE utf8_bin DEFAULT '' COMMENT '系统内流号,用户ID+&+GUID' primary key",
        "varchar(64) COLLATE utf8_bin NOT NULL DEFAULT '' COMMENT '委托ID'",
        "varchar(64) COLLATE utf8_bin NOT NULL DEFAULT '' COMMENT '帐户标识(用户ID)，系统内部使用'",
        "varchar(64) COLLATE utf8_bin NOT NULL DEFAULT '' COMMENT '合约ID'",
        "int(2) NOT NULL DEFAULT '-1' COMMENT '委托状态'",
        "int(2) NOT NULL DEFAULT '-1' COMMENT '委托状态说明'",
        "varchar(64) COLLATE utf8_bin NOT NULL DEFAULT '' COMMENT '当委托未生效时,本地需要唯一标示该委托,本地生成一个唯一编码,使用该编码进行标识'",
        "varchar(64) COLLATE utf8_bin NOT NULL DEFAULT '' COMMENT '客户端提交的委托编号'",
        "varchar(64) COLLATE utf8_bin NOT NULL DEFAULT '' COMMENT '影子订单编号， 客户端显示使用'",
        "DATETIME COMMENT '委托创建日期时间'",
        "DATETIME COMMENT ' 委托状态最后更新日期时间'",
        "double(32,8) NOT NULL DEFAULT '0.00000000' COMMENT '当前对应基币汇率'",
        "varchar(64) NOT NULL DEFAULT ''COMMENT '币种ID'",
        "double(32,8) NOT NULL DEFAULT '0.00000000' COMMENT '委托价格'",
        "int(2) NOT NULL DEFAULT '-1' COMMENT '买卖方向'",
        "int(10) NOT NULL DEFAULT '0' COMMENT '委托手数'",
        "int(10) NOT NULL DEFAULT '0' COMMENT '已生效手数'",
        "int(2) NOT NULL DEFAULT '-1' COMMENT '下单委托类型'",
        "int(2) NOT NULL DEFAULT '-1' COMMENT '委托交易模式'",
        "double(32,8) NOT NULL DEFAULT '0.00000000' COMMENT '委托成交价'",
        "double(32,8) NOT NULL DEFAULT '0.00000000' COMMENT '持仓成本'",
        "varchar(64) COLLATE utf8_bin NOT NULL DEFAULT '' COMMENT '交易所委托编号'",
        "varchar(255) COLLATE utf8_bin NOT NULL DEFAULT '' COMMENT '交易所ID'",
        "int(2) NOT NULL DEFAULT '-1' COMMENT '接口类型'",
        "int(2) NOT NULL DEFAULT '-1' COMMENT '操作员类型'",
        "int(2) NOT NULL DEFAULT '-1' COMMENT '下单委托模式'",
        "DATETIME COMMENT '有效日期'",
        "int(10) NOT NULL DEFAULT '-1' COMMENT '品种ID'",
    };
#pragma endregion

#pragma region 内盘委托
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
        "varchar(128) COLLATE utf8_bin DEFAULT '' COMMENT '系统内流号,用户ID+&+GUID' primary key",
        "varchar(64) COLLATE utf8_bin NOT NULL DEFAULT '' COMMENT '委托ID'",
        "varchar(64) COLLATE utf8_bin NOT NULL DEFAULT '' COMMENT '帐户标识(用户ID)，系统内部使用'",
        "varchar(64) COLLATE utf8_bin NOT NULL DEFAULT '' COMMENT '合约ID'",
        "int(2) NOT NULL DEFAULT '-1' COMMENT '委托状态'",
        "int(2) NOT NULL DEFAULT '-1' COMMENT '委托状态说明'",
        "varchar(64) COLLATE utf8_bin NOT NULL DEFAULT '' COMMENT '当委托未生效时,本地需要唯一标示该委托,本地生成一个唯一编码,使用该编码进行标识'",
        "varchar(64) COLLATE utf8_bin NOT NULL DEFAULT '' COMMENT '客户端提交的委托编号'",
        "varchar(64) COLLATE utf8_bin NOT NULL DEFAULT '' COMMENT '影子订单编号， 客户端显示使用'",
        "DATETIME COMMENT '委托创建日期时间'",
        "DATETIME COMMENT ' 委托状态最后更新日期时间'",
        "double(32,8) NOT NULL DEFAULT '0.00000000' COMMENT '当前对应基币汇率'",
        "varchar(64) NOT NULL DEFAULT ''COMMENT '币种ID'",
        "double(32,8) NOT NULL DEFAULT '0.00000000' COMMENT '委托价格'",
        "int(2) NOT NULL DEFAULT '-1' COMMENT '买卖方向'",
        "int(10) NOT NULL DEFAULT '0' COMMENT '委托手数'",
        "int(10) NOT NULL DEFAULT '0' COMMENT '已生效手数'",
        "int(2) NOT NULL DEFAULT '-1' COMMENT '下单委托类型'",
        "int(2) NOT NULL DEFAULT '-1' COMMENT '委托交易模式'",
        "double(32,8) NOT NULL DEFAULT '0.00000000' COMMENT '委托成交价'",
        "double(32,8) NOT NULL DEFAULT '0.00000000' COMMENT '持仓成本'",
        "varchar(64) COLLATE utf8_bin NOT NULL DEFAULT '' COMMENT '交易所委托编号'",
        "varchar(255) COLLATE utf8_bin NOT NULL DEFAULT '' COMMENT '交易所ID'",
        "int(2) NOT NULL DEFAULT '-1' COMMENT '接口类型'",
        "int(2) NOT NULL DEFAULT '-1' COMMENT '操作员类型'",
        "int(2) NOT NULL DEFAULT '-1' COMMENT '下单委托模式'",
        "DATETIME COMMENT '有效日期'",
        "int(10) NOT NULL DEFAULT '-1' COMMENT '品种ID'",
        "tinyint(1) NOT NULL DEFAULT '1' COMMENT '开平标志'",
    };
#pragma endregion

#pragma region 股票成交
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
        "varchar(64) COLLATE utf8_bin DEFAULT '' COMMENT '系统内成交流号' primary key",
        "varchar(64) COLLATE utf8_bin DEFAULT '' COMMENT '影子订单编号'",
        "varchar(128) COLLATE utf8_bin DEFAULT '' COMMENT '委托流号'",
        "varchar(64) COLLATE utf8_bin DEFAULT '' COMMENT '持仓ID'",
        "varchar(64) COLLATE utf8_bin NOT NULL DEFAULT '' COMMENT '帐户标识(用户ID)，系统内部使用'",
        "varchar(255) COLLATE utf8_bin NOT NULL DEFAULT '' COMMENT '交易所ID'",
        "varchar(64) COLLATE utf8_bin NOT NULL DEFAULT '' COMMENT '合约ID'",
        "DATETIME COMMENT '成交日期时间'",
        "tinyint(1) NOT NULL DEFAULT '1' COMMENT '买卖方向,同时也是开平标志,买表示开仓,卖表示平仓'",
        "int(10) NOT NULL DEFAULT '0' COMMENT '成交手数'",
        "double(32,8) NOT NULL DEFAULT '0.00000000' COMMENT '当前对应基币汇率'",
        "varchar(64) COLLATE utf8_bin NOT NULL DEFAULT '' COMMENT '币种ID'",
        "double(32,8) NOT NULL DEFAULT '0.00000000' COMMENT '成交均价'",
        "double(32,8) NOT NULL DEFAULT '0.00000000' COMMENT '平仓盈亏'",
        "int(2) NOT NULL DEFAULT '-1' COMMENT '操作员类型'",
        "int(2) NOT NULL DEFAULT '-1' COMMENT '所属股票类型'",
        "double(32,8) NOT NULL DEFAULT '0.00000000' COMMENT '交易佣金手续费'",
        "double(32,8) NOT NULL DEFAULT '0.00000000' COMMENT '平仓印花税费'",
        "double(32,8) NOT NULL DEFAULT '0.00000000' COMMENT '过户费'",
        "double(32,8) NOT NULL DEFAULT '0.00000000' COMMENT '信息撮合费'",
    };
#pragma endregion

#pragma region 外盘成交
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
        "varchar(64) COLLATE utf8_bin DEFAULT '' COMMENT '系统内成交流号' primary key",
        "varchar(128) COLLATE utf8_bin DEFAULT '' COMMENT '委托流号'",
        "varchar(64) COLLATE utf8_bin DEFAULT '' COMMENT '持仓ID'",
        "varchar(64) COLLATE utf8_bin NOT NULL DEFAULT '' COMMENT '帐户标识(用户ID)，系统内部使用'",
        "varchar(255) COLLATE utf8_bin NOT NULL DEFAULT '' COMMENT '交易所ID'",
        "varchar(64) COLLATE utf8_bin NOT NULL DEFAULT '' COMMENT '品种ID'",
        "varchar(64) COLLATE utf8_bin NOT NULL DEFAULT '' COMMENT '合约ID'",
        "DATETIME COMMENT '成交日期时间'",
        "int(2) NOT NULL DEFAULT '-1' COMMENT '买卖方向'",
        "int(10) NOT NULL DEFAULT '0' COMMENT '成交手数'",
        "double(32,8) NOT NULL DEFAULT '0.00000000' COMMENT '当前对应基币汇率'",
        "varchar(64) COLLATE utf8_bin NOT NULL DEFAULT '' COMMENT '币种ID'",
        "double(32,8) NOT NULL DEFAULT '0.00000000' COMMENT '成交均价'",
        "double(32,8) NOT NULL DEFAULT '0.00000000' COMMENT '平仓盈亏'",
        "int(2) NOT NULL DEFAULT '-1' COMMENT '操作员类型'",
    };

#pragma endregion

#pragma region 内盘成交
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
        "varchar(64) COLLATE utf8_bin DEFAULT '' COMMENT '系统内成交流号' primary key",
        "varchar(128) COLLATE utf8_bin DEFAULT '' COMMENT '委托流号'",
        "varchar(64) COLLATE utf8_bin DEFAULT '' COMMENT '持仓ID'",
        "varchar(64) COLLATE utf8_bin NOT NULL DEFAULT '' COMMENT '帐户标识(用户ID)，系统内部使用'",
        "varchar(255) COLLATE utf8_bin NOT NULL DEFAULT '' COMMENT '交易所ID'",
        "varchar(64) COLLATE utf8_bin NOT NULL DEFAULT '' COMMENT '品种ID'",
        "varchar(64) COLLATE utf8_bin NOT NULL DEFAULT '' COMMENT '合约ID'",
        "DATETIME COMMENT '成交日期时间'",
        "int(2) NOT NULL DEFAULT '-1' COMMENT '买卖方向'",
        "int(2) NOT NULL DEFAULT '-1' COMMENT '开平标志'",
        "int(10) NOT NULL DEFAULT '0' COMMENT '成交手数'",
        "double(32,8) NOT NULL DEFAULT '0.00000000' COMMENT '当前对应基币汇率'",
        "varchar(64) COLLATE utf8_bin NOT NULL DEFAULT '' COMMENT '币种ID'",
        "double(32,8) NOT NULL DEFAULT '0.00000000' COMMENT '成交均价'",
        "double(32,8) NOT NULL DEFAULT '0.00000000' COMMENT '平仓盈亏'",
        "int(2) NOT NULL DEFAULT '-1' COMMENT '操作员类型'",
    };

#pragma endregion

#pragma region 股票持仓
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
        "varchar(64) COLLATE utf8_bin DEFAULT '' COMMENT '持仓ID' primary key",
        "varchar(64) COLLATE utf8_bin NOT NULL DEFAULT '' COMMENT '帐户标识(用户ID)，系统内部使用'",
        "varchar(255) COLLATE utf8_bin NOT NULL DEFAULT '' COMMENT '交易所ID'",
        "varchar(64) COLLATE utf8_bin NOT NULL DEFAULT '' COMMENT '合约ID'",
        "tinyint(1) NOT NULL DEFAULT '1' COMMENT '买卖方向,同时也是开平标志,买表示开仓,卖表示平仓'",
        "int(10) NOT NULL DEFAULT '0' COMMENT '持仓手数'",
        "int(10) NOT NULL DEFAULT '0' COMMENT 'T+1持仓手数'",
        "varchar(64) COLLATE utf8_bin NOT NULL DEFAULT '' COMMENT '币种ID'",
        "double(32,8) NOT NULL DEFAULT '0.00000000' COMMENT '持仓总价'",
        "double(32,8) NOT NULL DEFAULT '0.00000000' COMMENT '成交均价'",
        "int(2) NOT NULL DEFAULT '-1' COMMENT '所属股票类型'",
        "int(10) NOT NULL DEFAULT '0' COMMENT '平仓委托冻结持仓手数'",
    };
#pragma endregion

#pragma region 外盘持仓
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
        "varchar(64) COLLATE utf8_bin DEFAULT '' COMMENT '持仓ID' primary key",
        "varchar(64) COLLATE utf8_bin NOT NULL DEFAULT '' COMMENT '帐户标识(用户ID)，系统内部使用'",
        "varchar(255) COLLATE utf8_bin NOT NULL DEFAULT '' COMMENT '交易所ID'",
        "varchar(64) COLLATE utf8_bin NOT NULL DEFAULT '' COMMENT '合约ID'",
        "int(2) NOT NULL DEFAULT '-1' COMMENT '买卖方向'",
        "int(10) NOT NULL DEFAULT '0' COMMENT '持仓手数'",
        "varchar(64) COLLATE utf8_bin NOT NULL DEFAULT '' COMMENT '币种ID'",
        "double(32,8) NOT NULL DEFAULT '0.00000000' COMMENT '持仓总价'",
    };
#pragma endregion

#pragma region 内盘持仓
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
        "varchar(64) COLLATE utf8_bin DEFAULT '' COMMENT '持仓ID' primary key",
        "varchar(64) COLLATE utf8_bin NOT NULL DEFAULT '' COMMENT '帐户标识(用户ID)，系统内部使用'",
        "varchar(255) COLLATE utf8_bin NOT NULL DEFAULT '' COMMENT '交易所ID'",
        "varchar(64) COLLATE utf8_bin NOT NULL DEFAULT '' COMMENT '合约ID'",
        "int(2) NOT NULL DEFAULT '-1' COMMENT '买卖方向'",
        "tinyint(1) NOT NULL DEFAULT '1' COMMENT '开平标志'",
        "int(10) NOT NULL DEFAULT '0' COMMENT '持仓手数'",
        "varchar(64) COLLATE utf8_bin NOT NULL DEFAULT '' COMMENT '币种ID'",
        "double(32,8) NOT NULL DEFAULT '0.00000000' COMMENT '持仓总价'",
    };
#pragma endregion

#pragma region 费用管理表

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
        "double(32,8) NOT NULL DEFAULT '0.00000000' COMMENT '交易佣金(千分之)'",
        "double(32,8) NOT NULL DEFAULT '0.00000000' COMMENT '最小交易佣金(元)'",
        "double(32,8) NOT NULL DEFAULT '0.00000000' COMMENT '印花税(千分之)'",
        "double(32,8) NOT NULL DEFAULT '0.00000000' COMMENT '过户费(千分之)'",
        "double(32,8) NOT NULL DEFAULT '0.00000000' COMMENT '撮合费(千分之)'",
        "double(32,8) NOT NULL DEFAULT '0.00000000' COMMENT '交易账户分成比例(千分之)'",
    };
#pragma endregion

#pragma region 结算管理表

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
//         "varchar(64) COLLATE utf8_bin DEFAULT '' COMMENT '交易所ID' primary key",
        "int(2) NOT NULL DEFAULT '-1' COMMENT '商品类型' primary key",
        "DATETIME COMMENT '结算时间'",
    };
#pragma endregion

#pragma region 全局数据管理表
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
        "int(2) NOT NULL DEFAULT '-1' COMMENT '商品类型' primary key",
        "int(5) NOT NULL DEFAULT '-1' COMMENT '累计订单编号'",
        "int(5) NOT NULL DEFAULT '-1' COMMENT '累计成交编号'",
    };
#pragma endregion

#pragma region 风控记录表
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
		"varchar(64) CHARACTER SET utf8 NOT NULL COMMENT '用户ID'",
        "int(2) NOT NULL DEFAULT '-1' COMMENT '风控类型'",
        "tinyint(2) NOT NULL COMMENT '是否处于触发状态 0不触发 1触发'",
        "DATETIME COMMENT '触发时间'",
		"varchar(1024) CHARACTER SET utf8 NOT NULL COMMENT '提示内容'",
    };
#pragma endregion

#pragma region 风控历史记录表
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
		"varchar(64) CHARACTER SET utf8 NOT NULL COMMENT '用户ID'",
		"int(2) NOT NULL DEFAULT '-1' COMMENT '风控类型'",
		"tinyint(2) NOT NULL COMMENT '是否处于触发状态 0不触发 1触发'",
		"DATETIME COMMENT '触发时间'",
		"varchar(1024) CHARACTER SET utf8 NOT NULL COMMENT '提示内容'",
	};
#pragma endregion

#pragma region 权限业务表
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
		"int(10) unsigned NOT NULL AUTO_INCREMENT COMMENT '业务ID' primary key",
		"varchar(64) CHARACTER SET utf8 NOT NULL COMMENT '业务名称'",
		"tinyint(2) NOT NULL COMMENT '业务类型 1、菜单2、功能'",
		"varchar(20) CHARACTER SET utf8 NOT NULL COMMENT '业务地址'",
		"int(10) NOT NULL COMMENT '父业务ID'",
		"tinyint(2) NOT NULL COMMENT '是否隐藏 0不隐藏 1隐藏'",
	};
#pragma endregion

#pragma region 权限日志表
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
		"int(10) NOT NULL COMMENT '操作者编号'",
		"int(20) NOT NULL COMMENT '操作日期'",
		"int(10) NOT NULL COMMENT '操作时间'",
		"varchar(200) CHARACTER SET utf8 NOT NULL COMMENT '操作内容'",
	};
#pragma endregion

#pragma region 权限功能表
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
		"int(10) unsigned NOT NULL AUTO_INCREMENT COMMENT '功能ID' primary key",
		"int(10) NOT NULL COMMENT '业务ID'",
		"int(10) NOT NULL COMMENT '导航ID'",
		"varchar(64) CHARACTER SET utf8 NOT NULL COMMENT '功能名称'",
		"tinyint(2) NOT NULL COMMENT '排序 0不排序 1排序'",
	};
#pragma endregion

#pragma region 权限角色功能表
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
		"int(10) NOT NULL COMMENT '角色ID'",
		"int(10) NOT NULL COMMENT '功能ID'",
	};
#pragma endregion

#pragma region 权限角色用户表
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
		"varchar(64) CHARACTER SET utf8 NOT NULL COMMENT '用户登录名'",
		"int(10) NOT NULL COMMENT '角色ID'",
	};
#pragma endregion

#pragma region 权限角色表
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
		"int(10) unsigned NOT NULL AUTO_INCREMENT COMMENT '角色ID' primary key",
		"varchar(24) CHARACTER SET utf8 NOT NULL COMMENT '角色名称'",
		"varchar(64) CHARACTER SET utf8 NOT NULL COMMENT '创建该角色的用户登录名'",
		"int(20) NOT NULL COMMENT '角色创建日期'",
		"int(10) NOT NULL COMMENT '角色创建时间'",
		"tinyint(2) NOT NULL COMMENT '角色类型(0机构 1管理员)'",
		"tinyint(2) NOT NULL COMMENT '操作类型(0可操作 1不可操作)'",
	};
#pragma endregion

#pragma region 融资资金审核表
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
        "int(25) NOT NULL AUTO_INCREMENT COMMENT '流水ID' primary key",
        "varchar(64) COLLATE utf8_bin DEFAULT '' COMMENT '审核者用户ID'",
        "varchar(64) COLLATE utf8_bin DEFAULT '' COMMENT '申请者用户ID'",
        "double(32,8) NOT NULL DEFAULT '0.00000000' COMMENT '申请资金'",
        "DATETIME COMMENT '申请日期时间'",
        "DATETIME COMMENT '审核日期时间'",
        "int(2) NOT NULL DEFAULT '-1' COMMENT '审核状态'",
    };
#pragma endregion

#pragma region 入金资金审核表
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
        "int(25) NOT NULL AUTO_INCREMENT COMMENT '流水ID' primary key",
        "varchar(64) COLLATE utf8_bin DEFAULT '' COMMENT '审核者用户ID'",
        "varchar(64) NOT NULL COLLATE utf8_bin DEFAULT '' COMMENT '申请者用户ID'",
        "int(11)",
        "double(18,3) NOT NULL DEFAULT '0.000' COMMENT '申请资金'",
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

#pragma region 出金资金审核表
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
        "int(25) NOT NULL AUTO_INCREMENT COMMENT '流水ID' primary key",
        "varchar(64) COLLATE utf8_bin DEFAULT '' COMMENT '审核者用户ID'",
        "varchar(64) NOT NULL COLLATE utf8_bin DEFAULT '' COMMENT '申请者用户ID'",
        "varchar(50) NOT NULL COLLATE utf8_bin",
        "varchar(50) NOT NULL COLLATE utf8_bin",
        "varchar(100) NOT NULL COLLATE utf8_bin",
        "double(18,3) NOT NULL DEFAULT '0.000' COMMENT '申请资金'",
        "DATETIME NOT NULL COMMENT '申请日期时间'",
        "tinyint(4) NOT NULL",
        "DATETIME COMMENT '审核日期时间'",
    };
#pragma endregion

#pragma region 黑白名单管理表
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
        "varchar(64) COLLATE utf8_bin DEFAULT '' COMMENT '合约ID' primary key",
        "tinyint(2) NOT NULL COMMENT '是否黑名单'",
    };
#pragma endregion

#pragma region 禁止交易规则管理表
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
        "int(2) NOT NULL DEFAULT '0' COMMENT '风控项目' primary key",
        "int(2) NOT NULL DEFAULT '0' COMMENT '操作类型'",
        "tinyint(2) NOT NULL COMMENT '是否开启'",
    };
#pragma endregion

#pragma region 持仓比例规则管理表
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
        "int(2) NOT NULL DEFAULT '0' COMMENT '项目' primary key",
        "int(3) NOT NULL DEFAULT '0' COMMENT '持仓比例'",
        "tinyint(2) NOT NULL COMMENT '是否开启'",
    };
#pragma endregion

#pragma region 自选股管理表
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
        "varchar(64) COLLATE utf8_bin DEFAULT '' COMMENT '账户ID'",
        "varchar(64) COLLATE utf8_bin DEFAULT '' COMMENT '合约ID'",
    };
#pragma endregion

#pragma region 机构佣金表
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
        "int(10) unsigned NOT NULL AUTO_INCREMENT COMMENT '业务ID' primary key",
        "varchar(64) COLLATE utf8_bin NOT NULL DEFAULT '' COMMENT '用户ID'",
        "varchar(64) COLLATE utf8_bin NOT NULL DEFAULT '' COMMENT '佣金来源用户ID'",
        "double(32,8) NOT NULL DEFAULT '0.00000000' COMMENT '变化前总资金, 暂未启用'",
        "double(32,8) NOT NULL DEFAULT '0.00000000' COMMENT '变化后总资金, 暂未启用'",
        "double(32,8) NOT NULL DEFAULT '0.00000000' COMMENT '当前费用收取比例'",
        "double(32,8) NOT NULL DEFAULT '0.00000000' COMMENT '变动资金'",
        "int(2) NOT NULL DEFAULT '-1' COMMENT '变动类型'",
        "varchar(1024) COLLATE utf8_bin DEFAULT '' COMMENT '备注信息'",
        "DATETIME COMMENT '创建日期时间'",
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
        "varchar(64) COLLATE utf8_bin DEFAULT '' COMMENT '用户ID' primary key",
        "double(32,8) NOT NULL DEFAULT '0.00000000' COMMENT '累计信息撮合费'",
        "double(32,8) NOT NULL DEFAULT '0.00000000' COMMENT '累计交易所手续费'",
        "double(32,8) NOT NULL DEFAULT '0.00000000' COMMENT '累计佣金'",
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
        "varchar(64) COLLATE utf8_bin DEFAULT '' COMMENT '用户ID'",
        "DATE COMMENT '快照日期'",
        "double(32,8) NOT NULL DEFAULT '0.00000000' COMMENT '累计信息撮合费'",
        "double(32,8) NOT NULL DEFAULT '0.00000000' COMMENT '累计交易所手续费'",
        "double(32,8) NOT NULL DEFAULT '0.00000000' COMMENT '累计佣金'",
    };

#pragma endregion

#pragma region 机构分成表
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
        "int(10) unsigned NOT NULL AUTO_INCREMENT COMMENT '业务ID' primary key",
        "varchar(64) COLLATE utf8_bin NOT NULL DEFAULT '' COMMENT '用户ID'",
        "varchar(64) COLLATE utf8_bin NOT NULL DEFAULT '' COMMENT '佣金来源用户ID'",
        "double(32,8) NOT NULL DEFAULT '0.00000000' COMMENT '变化前总资金, 暂未启用'",
        "double(32,8) NOT NULL DEFAULT '0.00000000' COMMENT '变化后总资金, 暂未启用'",
        "double(32,8) NOT NULL DEFAULT '0.00000000' COMMENT '当前费用收取比例'",
        "double(32,8) NOT NULL DEFAULT '0.00000000' COMMENT '变动资金'",
        "int(2) NOT NULL DEFAULT '-1' COMMENT '变动类型'",
        "varchar(1024) COLLATE utf8_bin DEFAULT '' COMMENT '备注信息'",
        "DATETIME COMMENT '创建日期时间'",
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
        "varchar(64) COLLATE utf8_bin DEFAULT '' COMMENT '用户ID' primary key",
        "double(32,8) NOT NULL DEFAULT '0.00000000' COMMENT '累计分成'",
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
        "varchar(64) COLLATE utf8_bin DEFAULT '' COMMENT '用户ID'",
        "DATE COMMENT '快照日期'",
        "double(32,8) NOT NULL DEFAULT '0.00000000' COMMENT '累计分成'",
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
		"varchar(32) COLLATE utf8_bin DEFAULT '' COMMENT '版本名称' primary key",
	};

#pragma region 融券持仓
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
		"varchar(64) COLLATE utf8_bin DEFAULT '' COMMENT '持仓ID' primary key",
		"varchar(64) COLLATE utf8_bin NOT NULL DEFAULT '' COMMENT '帐户标识(用户ID)，系统内部使用'",
		"varchar(255) COLLATE utf8_bin NOT NULL DEFAULT '' COMMENT '交易所ID'",
		"varchar(64) COLLATE utf8_bin NOT NULL DEFAULT '' COMMENT '合约ID'",
		"tinyint(1) NOT NULL DEFAULT '1' COMMENT '买卖方向,同时也是开平标志,买表示开仓,卖表示平仓'",
		"int(10) NOT NULL DEFAULT '0' COMMENT '持仓手数'",
		"int(10) NOT NULL DEFAULT '0' COMMENT 'T+1持仓手数'",
		"varchar(64) COLLATE utf8_bin NOT NULL DEFAULT '' COMMENT '币种ID'",
		"double(32,8) NOT NULL DEFAULT '0.00000000' COMMENT '持仓总价'",
		"double(32,8) NOT NULL DEFAULT '0.00000000' COMMENT '成交均价'",
		"int(2) NOT NULL DEFAULT '-1' COMMENT '所属股票类型'",
		"int(10) NOT NULL DEFAULT '0' COMMENT '平仓委托冻结持仓手数'",
	};
#pragma endregion

#pragma region 融券成交
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
		"varchar(64) COLLATE utf8_bin DEFAULT '' COMMENT '系统内成交流号' primary key",
		"varchar(64) COLLATE utf8_bin DEFAULT '' COMMENT '影子订单编号'",
		"varchar(128) COLLATE utf8_bin DEFAULT '' COMMENT '委托流号'",
		"varchar(64) COLLATE utf8_bin DEFAULT '' COMMENT '持仓ID'",
		"varchar(64) COLLATE utf8_bin NOT NULL DEFAULT '' COMMENT '帐户标识(用户ID)，系统内部使用'",
		"varchar(255) COLLATE utf8_bin NOT NULL DEFAULT '' COMMENT '交易所ID'",
		"varchar(64) COLLATE utf8_bin NOT NULL DEFAULT '' COMMENT '合约ID'",
		"DATETIME COMMENT '成交日期时间'",
		"tinyint(1) NOT NULL DEFAULT '1' COMMENT '买卖方向,同时也是开平标志,买表示开仓,卖表示平仓'",
		"int(10) NOT NULL DEFAULT '0' COMMENT '成交手数'",
		"double(32,8) NOT NULL DEFAULT '0.00000000' COMMENT '当前对应基币汇率'",
		"varchar(64) COLLATE utf8_bin NOT NULL DEFAULT '' COMMENT '币种ID'",
		"double(32,8) NOT NULL DEFAULT '0.00000000' COMMENT '成交均价'",
		"double(32,8) NOT NULL DEFAULT '0.00000000' COMMENT '平仓盈亏'",
		"int(2) NOT NULL DEFAULT '-1' COMMENT '操作员类型'",
		"int(2) NOT NULL DEFAULT '-1' COMMENT '所属股票类型'",
		"double(32,8) NOT NULL DEFAULT '0.00000000' COMMENT '交易佣金手续费'",
		"double(32,8) NOT NULL DEFAULT '0.00000000' COMMENT '平仓印花税费'",
		"double(32,8) NOT NULL DEFAULT '0.00000000' COMMENT '过户费'",
		"double(32,8) NOT NULL DEFAULT '0.00000000' COMMENT '信息撮合费'",
		"double(32,8) NOT NULL DEFAULT '0.00000000' COMMENT '日利息'",
		"double(32,8) NOT NULL DEFAULT '0.00000000' COMMENT '利息资金'",
	};
#pragma endregion

#pragma region 融券委托
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
		"varchar(128) COLLATE utf8_bin NOT NULL DEFAULT '' COMMENT '系统内流号,用户ID+&+GUID' primary key",
		"varchar(64) COLLATE utf8_bin DEFAULT '' COMMENT '委托ID'",
		"varchar(64) COLLATE utf8_bin NOT NULL DEFAULT '' COMMENT '帐户标识(用户ID)，系统内部使用'",
		"varchar(64) COLLATE utf8_bin NOT NULL DEFAULT '' COMMENT '合约ID'",
		"int(2) NOT NULL DEFAULT '-1' COMMENT '委托状态'",
		"int(2) NOT NULL DEFAULT '-1' COMMENT '委托状态说明'",
		"varchar(64) COLLATE utf8_bin DEFAULT '' COMMENT '当委托未生效时,本地需要唯一标示该委托,本地生成一个唯一编码,使用该编码进行标识'",
		"varchar(64) COLLATE utf8_bin DEFAULT '' COMMENT '客户端提交的委托编号'",
		"varchar(64) COLLATE utf8_bin DEFAULT '' COMMENT '影子订单编号， 客户端显示使用'",
		"DATETIME COMMENT '委托创建日期时间'",
		"DATETIME COMMENT ' 委托状态最后更新日期时间'",
		"double(32,8) NOT NULL DEFAULT '0.00000000' COMMENT '当前对应基币汇率'",
		"varchar(64) NOT NULL DEFAULT ''COMMENT '币种ID'",
		"double(32,8) NOT NULL DEFAULT '0.00000000' COMMENT '委托价格'",
		"tinyint(1) NOT NULL DEFAULT '1' COMMENT '买卖方向,同时也是开平标志,买表示开仓,卖表示平仓'",
		"int(10) NOT NULL DEFAULT '0' COMMENT '委托手数'",
		"int(10) NOT NULL DEFAULT '0' COMMENT '已生效手数'",
		"int(10) NOT NULL DEFAULT '0' COMMENT '成交手数'",
		"tinyint(1) NOT NULL DEFAULT '0' COMMENT '是否有冻结持仓'",
		"double(32,8) NOT NULL DEFAULT '0.00000000' COMMENT '委托冻结总资金'",
		"tinyint(1) NOT NULL DEFAULT '0' COMMENT '是否有冻结资金'",
		"int(2) NOT NULL DEFAULT '-1' COMMENT '下单委托类型'",
		"int(2) NOT NULL DEFAULT '-1' COMMENT '委托交易模式'",
		"double(32,8) NOT NULL DEFAULT '0.00000000' COMMENT '委托成交价'",
		"double(32,8) NOT NULL DEFAULT '0.00000000' COMMENT '持仓成本'",
		"varchar(64) COLLATE utf8_bin NOT NULL DEFAULT '' COMMENT '交易所委托编号'",
		"varchar(255) COLLATE utf8_bin NOT NULL DEFAULT '' COMMENT '交易所ID'",
		"int(2) NOT NULL DEFAULT '-1' COMMENT '接口类型'",
		"int(2) NOT NULL DEFAULT '-1' COMMENT '操作员类型'",
		"int(2) NOT NULL DEFAULT '-1' COMMENT '下单委托模式'",
		"DATETIME COMMENT '有效日期'",
		"int(2) NOT NULL DEFAULT '-1' COMMENT '所属股票类型'",
		"double(32,8) NOT NULL DEFAULT '0.00000000' COMMENT '当前交易佣金手续费'",
		"double(32,8) NOT NULL DEFAULT '0.00000000' COMMENT '当前平仓印花税费'",
		"double(32,8) NOT NULL DEFAULT '0.00000000' COMMENT '当前过户费'",
		"double(32,8) NOT NULL DEFAULT '0.00000000' COMMENT '当前信息撮合费'",
	};
#pragma endregion

#pragma region 融券信息
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
		"int(10) NOT NULL DEFAULT '0' COMMENT '融资总手数'",
		"double(32,8) NOT NULL DEFAULT '0.00000000' COMMENT '融券利息'",
	};
#pragma endregion

#pragma region 融券剩余数量信息
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
		"varchar(64) COLLATE utf8_bin DEFAULT '' COMMENT '合约ID' primary key",
		"int(10) NOT NULL DEFAULT '0' COMMENT '融资剩余手数'",
	};
#pragma endregion


#pragma region 利息管理
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
		"varchar(64) CHARACTER SET utf8 NOT NULL COMMENT '用户id'  primary key",
		"double(32,8) NOT NULL DEFAULT '0.00000000' COMMENT '累计利息'",
		"DATE COMMENT '快照日期'",
	};
	// 利息明细
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
		"int(10) unsigned NOT NULL AUTO_INCREMENT COMMENT '业务ID' primary key",
		"varchar(64) CHARACTER SET utf8 NOT NULL COMMENT '用户id'",
		"double(32,8) NOT NULL DEFAULT '0.00000000' COMMENT '利息变动'",
		"DATETIME COMMENT '变动时间'",
		"int(2) NOT NULL DEFAULT '-1' COMMENT '变动类型'",
		"varchar(64) CHARACTER SET utf8 NOT NULL COMMENT '变动来源'",
		"double(32,8) NOT NULL DEFAULT '0.00000000' COMMENT '利息比例'",
	}; 
#pragma endregion
}

#endif