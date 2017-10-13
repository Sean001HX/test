#pragma once

// 机构设置
enum  InstitutionManagerColumn : int
{
	IMC_InstitutionManager			= 1,		// 机构管理
	IMC_InstitutionSet				= 101,		// 机构设置
	IMC_InstitutionSetQuery			= 10101,	// 机构设置查询
	IMC_InstitutionSetAdd			= 10102,	// 机构设置增加
	IMC_InstitutionSetModify		= 10103,	// 机构设置修改
	IMC_InstitutionSetDek			= 10104,	// 机构设置删除

	IMC_InstitutionApproval			= 102,		// 机构审核
	IMC_InstitutionApprovalQuery	= 10201,	// 修改审核查询
	IMC_InstitutionApprovalYes		= 10202,	// 机构审核通过
	IMC_InstitutionApprovalNo		= 10203,	// 机构审核拒绝

	IMC_InstitutionLink				= 103,		// 机构推广
	IMC_InstitutionLinkQuery		= 10301,	// 机构推开查询
	IMC_InstitutionLinkLook			= 10302,	// 查看网址
	IMC_InstitutionLinkCopy			= 10303,	// 复制网址
	IMC_InstitutionLinkPro			= 10304,	// 生成二维码
	IMC_InstitutionLinkSave			= 10305,	// 保存二维码


	IMC_InstitutionAuthority		= 104,		// 机构权限管理
	IMC_InstitutionAuthorityQuery	= 10401,	// 机构权限查询
	IMC_InstitutionAuthorityAdd		= 10402,	// 机构权限增加
	IMC_InstitutionAuthorityMod		= 10403,	// 机构权限修改
	IMC_InstitutionAuthorityDel		= 10404,	// 机构权限删除
	IMC_InstitutionAuthorityBind	= 10405,	// 指派机构角色功能关系
	IMC_InstitutionFunctionQuery	= 10406,	// 角色查询对应功能

	IMC_InstitutionRole				= 105,		// 机构角色管理
	IMC_InstitutionRoleQuery		= 10501,	// 机构角色查询
	IMC_InstitutionRoleAdd			= 10502,	// 机构角色增加
	IMC_InstitutionRoleMod			= 10503,	// 机构角色修改
	IMC_InstitutionRoleDel			= 10504,	// 机构角色删除


	IMC_InstitutionCommission		= 106,		// 佣金管理
	IMC_InstitutionCommissionQuery	= 10601,	// 佣金统计查询
	IMC_InstitutionCommissionDetail = 10602,	// 佣金明细查询

	IMC_InstitutionDivide			= 106,		// 分成管理
	IMC_InstitutionDivideQuery		= 10601,	// 分成统计查询
	IMC_InstitutionDivideDetail		= 10602,	// 分成明细查询
};

// 机构拓扑树
enum JuniorTopoTree :int
{
	JTT_TopoTree		= 02,		//机构拓扑树
	JTT_TopoTreeShowQry = 20101,   // 查询系统拓扑树
};

// 账户管理
enum AccountMangerColumn : int
{
	AMC_AccountManger		= 3,		// 账户管理

	AMC_ChildList			= 301,		// 子账户列表
	AMC_ChildQuery			= 30101,	// 子账户查询
	AMC_ChildAdd			= 30102,	// 子账户增加
	AMC_ChildUpdate			= 30103,	// 子账户修改
	AMC_ChildDel			= 30104,	// 子账户删除
	AMC_ChildFundInfo		= 30105,	// 子账户资金信息
	AMC_ChildOutInMoney		= 30106,	// 出入金管理
	AMC_ChildPosiInfo		= 30107,	// 子帐户持仓
	AMC_ChildposiClose		= 30108,	// 子帐户持仓平仓
	AMC_ChildPosiAllClose	= 30109,	// 子帐户一键全平
	AMC_ChildTrade			= 30110,	// 子帐户成交记录

	AMC_ChildApprovalList	= 302,		// 子账户审核列表
	AMC_ChildApprovalQuery	= 30201,	// 子账户审核查询
	AMC_ChildApprovalYes	= 30202,	// 子账户审核通过
	AMC_ChildApprovalNo		= 30203,	// 子账户审核拒绝

	
	AMC_FundUserList		= 303,		// 资金账户列表
	AMC_FundUserQuery		= 30301,	// 资金账户查询
	AMC_FundUserAdd			= 30302,	// 资金账户增加
	AMC_FundUserUpdate		= 30303,	// 资金账户修改
	AMC_FundUserDel			= 30304,	// 资金账户删除
	
	AMC_OnlineList			= 304,		// 在线用户列表
	AMC_OnlineQuery			= 30401,	// 在线用户查询

	AMC_ManagerUserList		= 305,		// 管理员账户列表
	AMC_ManagerUserQuery	= 30501,	// 管理员账户查询
	AMC_ManagerUserAdd		= 30502,	// 管理员账户增加
	AMC_ManagerUserUpdate	= 30503,	// 管理员账户修改
	AMC_ManagerUserDel		= 30504,	// 管理员账户删除
};

// 费用管理
enum FeeManagerColumn : int
{
	FMC_FeeManagerList		= 4,		// 费用管理
	FMC_FeeManagerQry		= 40101,	// 查询
	FMC_FeeManagerSet		= 40102,	// 费用管理设置

};

// 风控管理
enum RiskControlListColumn : int
{
	RCC_RiskControl			= 5,		// 风控管理
	RCC_StockBlackUserSetL	= 501,		// 股票黑名单设置
	RCC_StockBlackUserQuery = 50101,	// 股票黑名单查询
	RCC_StockBlackUserSet	= 50102,	// 股票黑名单设置

	RCC_ForBidBuySellSetList= 502,		// 禁止买卖设置
	RCC_ForBidBuySellQuery	= 50201,	// 禁止买卖查询
	RCC_ForBidBuySellSet	= 50202,	// 禁止买卖设置

	RCC_PositionRateSetList = 503,		// 持仓比例设置
	RCC_PositionRateQuery	= 50301,	// 持仓比例查询
	RCC_PositionRateSet		= 50302,	// 持仓比例设置
};

// 安全管理
enum  SafeManagerColumn :int
{
	SMC_SafeManager			= 6,		// 安全管理
	SMC_BusinessRole		= 6001,		// 业务角色
	SMC_RoleQuery			= 60101,	// 角色查询
	SMC_RoleAdd				= 60102,	// 角色增加
	SMC_RoleModify			= 60103,	// 角色修改
	SMC_RoleDelete			= 60104,	// 角色删除
	SMC_RoleFunctional		= 60105,	// 保存<角色-功能>关系
	SMC_RoleFunctionalQuery = 60106,	// 角色查询功能

	SMC_UserManagerRelation = 602,		// 用户角色管理
	SMC_QueryUserRelation	= 60201,	// 查看用户角色关系
	SMC_RoleUserRelationAdd	= 60202,	// 指派角色用户关系
	SMC_RoleUserRelationMod	= 60203,	// 修改用户角色关系
	SMC_DelRoleUserRelation = 60204,	// 删除角色用户关系

};


// 报表管理
enum ReportManagerColumn :int
{
	RMC_ReportManager		= 7,		// 报表管理
	RMC_PositionInfo		= 701,		// 持仓查询
	RMC_PositionInfoQuery	= 70101,	// 查询
	RMC_PositionInfoExport	= 70102,	// 导出


	RMC_EntrustInfo			= 702,		// 委托信息
	RMC_EntrustInfoQuery	= 70201,	// 查询
	RMC_EntrustInfoExport	= 70202,	// 导出

	RMC_TradeInfo			= 703,		// 成交信息
	RMC_TradeInfoQuery		= 70301,	// 查询
	RMC_TradeInfoExport		= 70302,	// 导出

	RMC_FundInfo			= 704,		// 资金信息
	RMC_FundInfoQuery		= 70401,	// 查询
	RMC_FundInfoExport		= 70402,	// 导出

	RMC_OutInMoneyInfo		= 705,		// 资金流水列表
	RMC_OutInMoneyQuery		= 70501,	// 资金流水查询
	RMC_OutInMoneyExport	= 70502,	// 资金流水导出

	RMC_DeliveryInfo		= 706,		// 交割列表 ======> 暂时不用
	RMC_DeliveryInfoQuery	= 70601,	// 查询
	RMC_DeliveryInfoExport	= 70602,	// 导出

};

// 资产监控
enum  MoneyMonitorColumn :int
{
	MMC_MoneyMonitor		= 8,		// 资产监控

	MMC_TimeMoneyMonitor	= 801,		// 实时资产监控
	MMC_ChildMoneyMonitor	= 80101,	// 实时资产监控查询
	

	MMC_ChildTradeInfo		= 802,		// 子账户实时成交记录
	MMC_QueryTradeInfo		= 80201,	// 查询（显示）

	MMC_SumPositionInfo		= 803,		// 系统总持仓统计
	MMC_QuerySumPosiInfo	= 80301,	// 查询（查询）

	MMC_TimeWarnInfo		= 804,		// 实时预警通知
	MMC_QueryWarnInfo		= 80401,	// 查询（显示）
};


// 融资审核
enum OutInMoneyApproval :int
{
	OIMA_OutInMoneyApproval		= 9,		// 资金审核
	OIMA_InMoneyApprovalList	= 901,		// 子账户融资审核	======> 暂时不用
	OIMA_InMoneyApprovalQuery	= 90101,	// 查询
	OIMA_InMoneyApprovalYes		= 90102,	// 审核通过
	OIMA_InMoneyApprovalNo		= 90103,	// 审核拒绝

	OIMA_OutMoneyApprovalList	= 902,		// 入金资金审核		======> 暂时不用
	OIMA_OutMoneyApprovalQuery	= 90201,	// 查询
	OIMA_OutMoneyApprovalYes	= 90202,	// 审核通过
	OIMA_OutMoneyApprovalNo		= 90203,	// 审核拒绝

	OIMA_FinaceApprovalList		= 903,		// 出金资金审核
	OIMA_FinaceApprovalQuery	= 90301,	// 查询
	OIMA_FinaceApprovalYes		= 90302,	// 审核通过
	OIMA_FinaceApprovalNo		= 90303,	// 审核拒绝
};

// 系统管理
enum SystemManager :int
{
	SM_SystemManager			= 10,		// 系统管理
	SM_PasswordChange			= 100101,	// 密码修改
};