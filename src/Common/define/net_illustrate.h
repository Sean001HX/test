#ifndef __NET_ILLUSTRATE_H__
#define __NET_ILLUSTRATE_H__

enum E_COMM_MSG_TYPE : int
{
    EMPT_Init_Null = -1,                // 无效
	/////////////////// 登陆相关 //////////
	LOGIN_TRADE_REQ	= 0,                // 登录请求	= 1001
    LOGIN_TRADE_RSP,		            // 登录回调	= 1002
    LOGIN_OUT_REQ,		                // 登出请求	= 1003
    LOGIN_QUIT_MSG,		                // 强制下线	= 1004
    HEART_BEAT_MSG,		                // 心跳连接	= 1005

	///////////////// 获取相关 ////////////
	INSTITUTION_REQ,			        // 机构查询请求	= 2001
	INSTITUTION_RSP,			        // 机构查询应答	= 2002
	INSTITUTION_PREAPPROVAL_REQ,        // 待审核机构查询请求 = 2003
    INSTITUTION_PREAPPROVAL_RSP,        // 待审核机构查询应答 = 2004
	INSTITUTION_LINK_REQ,	            // 机构推广查询请求 = 2005
	INSTITUTION_LINK_RSP,	            // 机构推广查询应答 = 2006
	ROLES_QUERY_REQ,			        // 角色查询请求 = 2007
	ROLES_QUERY_RSP,			        // 角色查询应答	= 2008
	INSTITUTIONUSER_ROLE_RELATION_REQ,	// 机构（用户）角色关系查询请求 = 2009
	INSTITUTIONUSER_ROLE_RELATION_RSP,	// 机构（用户）角色关系查询应答 = 2010
	COMMISSION_QUERY_REQ,			    // 佣金查询请求 = 2011
	COMMISSION_QUERY_RSP,			    // 佣金查询应答 = 2012
	COMMISSION_DETAIL_REQ,			    // 佣金明细查询请求 = 2013
	COMMISSION_DETAIL_RSP,			    // 佣金明细查询应答 = 2014
	PROFITCOMMISSION_QUERY_REQ,			// 分成查询请求 = 2015
    PROFITCOMMISSION_QUERY_RSP,			// 分成查询应答 = 2016
    PROFITCOMMISSION_DETAIL_REQ,		// 分成明细查询请求 = 2017
    PROFITCOMMISSION_DETAIL_RSP,		// 分成明细查询应答 = 2018
	TOPOLOGICAL_TREE_REQ,			    // 拓扑树查询请求 = 2019
	TOPOLOGICAL_TREE_RSP,			    // 拓扑树查询应答 = 2020
	CHILD_QUERY_REQ,					// 子账户查询请求 = 2021
	CHILD_QUERY_RSP,					// 子账户查询应答 = 2022
	CHILD_APPROVAL_REQ,				    // 子账户审核查询请求 = 2023
	CHILD_APPROVAL_RSP,				    // 子账户审核查询应答 = 2024
	FUNDACC_QUERY_REQ,					// 资金账户查询请求 = 2025
    FUNDACC_QUERY_RSP,					// 资金账户应答 = 2026
	ONLINE_USER_REQ,					// 在线用户查询请求 = 2027
	ONLINE_USER_RSP,					// 在线用户应答 = 2028

    STOCK_CONTRACT_QUERY_REQ,		    // 股票合约查询请求 = 2029
    STOCK_CONTRACT_QUERY_RSP,		    // 股票合约查询应答 = 2030
    STOCK_INSTRUMENT_QUERY_REQ,		    // 股票黑名单查询请求 = 2031
	STOCK_INSTRUMENT_QUERY_RSP,		    // 股票黑名单查询应答 = 2032
	FORBID_BUY_SELL_QUERY_REQ,		    // 禁止买卖查询请求 = 2033
	FORBID_BUY_SELL_QUERY_RSP,		    // 禁止买卖查询应答 = 2034
	POSI_RATE_QUERY_REQ,				// 持仓比例设置查询请求 = 2035
	POSI_RATE_QUERY_RSP,				// 持仓比例设置查询应答 = 2036
	POSI_QUERY_REQ,					    // 持仓查询请求 = 2037
	POSI_QUERY_RSP,					    // 持仓查询应答 = 2038

	CURRENTENTRUST_QUERY_REQ,			// 当前委托查询请求 = 2039
    CURRENTENTRUST_QUERY_RSP,			// 当前委托查询应答 = 2040
    TODAYENTRUST_QUERY_REQ,				// 当日委托查询请求 = 2041
    TODAYENTRUST_QUERY_RSP,				// 当日委托查询应答 = 2042
    HISTORYENTRUST_QUERY_REQ,			// 历史委托查询请求 = 2043
    HISTORYENTRUST_QUERY_RSP,			// 历史委托查询应答 = 2044
    TRADE_QUERY_REQ,					// 当日成交查询请求 = 2045
	TRADE_QUERY_RSP,					// 当日成交查询应答 = 2046
    HISTORYTRADE_QUERY_REQ,			    // 历史成交查询请求 = 2047
    HISTORYTRADE_QUERY_RSP,			    // 历史成交查询应答 = 2048
    FUND_QUERY_REQ,					    // 资金查询请求 = 2049
	FUND_QUERY_RSP,					    // 资金查询应答 = 2050
	FUND_SERIAL_QUERY_REQ,			    // 资金流水查询请求 = 2051
	FUND_SERIAL_QUERY_RSP,			    // 资金流水查询应答 = 2052
	DELIVERY_QUERY_REQ,				    // 交割查询请求 = 2053
	DELIVERY_QUERY_RSP,				    // 交割查询应答 = 2054
	CHILD_FUNDMONITIOR_QUERY_REQ,	    // 子帐户实时资金监控查询请求 = 2055(不使用)
	CHILD_FUNDMONITIOR_QUERY_RSP,	    // 子帐户实时资金监控查询应答 = 2056(不使用)
	CHILD_SUMPOSITION_QUERY_REQ,		// 系统总持仓查询请求 = 2057(不使用)
	CHILD_SUMPOSITION_QUERY_RSP,		// 系统总持仓查询应答 = 2058(不使用)
	CHILD_TIMEWARN_NOTIFY_QUERY_REQ,	// 实时预警通知查询请求 = 2059
	CHILD_TIMEWARN_NOTIFY_QUERY_RSP,	// 实时预警通知查询应答 = 2060
    CHILD_EQUIPMENTMONEY_QUERY_REQ,		// 子帐户融资审核查询请求 = 2061
    CHILD_EQUIPMENTMONEY_QUERY_RSP,		// 子帐户融资审核查询应答 = 2062
	CHILD_AUTOOUTMONEY_QUERY_REQ,		// 子帐户自动出金审核查询请求 = 2063
	CHILD_AUTOOUTMONEY_QUERY_RSP,		// 子帐户自动出金审核查询应答 = 2064
	FEE_MANAGER_QUERY_REQ,				// 费用管理查询请求 = 2065
	FEE_MANAGER_QUERY_RSP,				// 费用管理查询请求应答 = 2066

	SELFFUNCTION_QUERY_REQ,				// 自身功能查询请求 = 2067
	SELFFUNCTION_QUERY_RSP,				// 自身功能查询请求应答 = 2068
	ROLEFUNCTION_QUERY_REQ,				// 角色功能查询请求 = 2069
	ROLEFUNCTION_QUERY_RSP,				// 角色功能查询请求应答 = 2070
	MANAGER_QUERY_REQ,					// 管理员查询请求 = 2071
	MANAGER_QUERY_RSP,					// 管理员查询请求应答 = 2072
	BUSSNESS_QUERY_REQ,					// 所有业务查询请求 = 2073
	BUSSNESS_QUERY_RSP,					// 所有业务查询请求应答 = 2074

    CUSTOMSTOCK_REQ,			        // 自选股票查询请求	= 2075
    CUSTOMSTOCK_RSP,			        // 自选股票查询应答	= 2076

    CHILD_AUTOINTOMONEY_QUERY_REQ,		// 子帐户自动入金审核查询请求 = 2077
    CHILD_AUTOINTOMONEY_QUERY_RSP,		// 子帐户自动入金审核查询应答 = 2078

	RISK_HISTORY_REQ,					    // 风控历史查询请求 = 2079
	RISK_HISTORY_RSP,					    // 风控历史查询应答 = 2080

	MARGIN_LEFTQTY_REQ,					    // 剩余融券数量查询请求 = 2081
	MARGIN_LEFTQTY_RSP,					    // 剩余融券数量查询应答 = 2082

	MARGIN_MANAGER_REQ,					    // 融券管理查询请求 = 2083
	MARGIN_MANAGER_RSP,					    // 融券管理查询应答 = 2084

	MARGIN_LIABILITIES_REQ,					// 融券负债查询请求 = 2085
	MARGIN_LIABILITIES_RSP,					// 融券负债查询应答 = 2086
	INTEREST_STATISTICS_REQ,				// 利息统计查询请求 = 2087
	INTEREST_STATISTICS_RSP,				// 利息统计查询应答 = 2088
	INTEREST_DETAIL_REQ,					// 利息明细查询请求 = 2089
	INTEREST_DETAIL_RSP,					// 利息明细查询应答 = 2090

	CURRENT_MARGINENTRUST_REQ,					// 当前融券委托请求 = 2091
	CURRENT_MARGINENTRUST_RSP,					// 当前融券委托查询应答 = 2092
	CURRENT_MARGINTRADE_REQ,					// 当前融券成交请求 = 2093
	CURRENT_MARGINTRADE_RSP,					// 当前融券成交查询应答 = 2094
	///////////////////////////////// 增加/更新 相关 ///////////////////
	ABOUT_ADD_CHANGE,				// 增加/更新 相关 = 3000

	INSTITUTION_ADD_REQ,				// 机构增加请求请求 = 3001
	INSTITUTION_ADD_RSP,				// 机构增加请求应答 = 3002
	INSTITUTION_CHANGE_REQ,			    // 机构修改请求 = 3003
	INSTITUTION_CHANGE_RSP,			    // 机构修改应答 = 3004
    INSTITUTION_APPROVAL_REQ,		    // 机构审核请求 = 3005
	INSTITUTION_APPROVAL_RSP,		    // 机构审核应答 = 3006
	ROLES_ADD_REQ,					    // 增加角色请求 = 3007
	ROLES_ADD_RSP,					    // 增加角色应答 = 3008
	ROLES_CHANGE_REQ,				    // 修改角色请求 = 3009
	ROLES_CHANGE_RSP,				    // 修改角色应答 = 3010
	BIND_FUNCTION_ROLE_RELATIUON_REQ,   // 绑定功能角色关系请求  = 3011
	BIND_FUNCTION_ROLE_RELATIUON_RSP,   // 绑定功能角色关系应答 = 3012
	USERROLE_ADDRELATION_REQ,		    // 增加用户(机构)角色关系请求请求 = 3013
	USERROLE_ADDRELATION_RSP,		    // 增加用户(机构)角色关系请求应答 = 3014
	CHILDUSER_ADD_REQ,				    // 子帐户增加请求 = 3015
	CHILDUSER_ADD_RSP,				    // 子帐户增加应答 = 3016
	CHILDUSER_CHANGE_REQ,			    // 子帐户修改请求 = 3017
	CHILDUSER_CHANGE_RSP,			    // 子帐户修改应答 = 3018
	CHILDUSER_INOUTMONEY_REQ,		    // 子帐户出入金请求 = 3019
	CHILDUSER_INOUTMONEY_RSP,		    // 子帐户出入金应答 = 3020
	CHILDUSER_APPROVAL_REQ,			    // 子帐户审核请求 = 3021
	CHILDUSER_APPROVAL_RSP,			    // 子帐户审核应答 = 3022
	FUNDUSER_ADD_REQ,				    // 资金账户增加请求 = 3023
	FUNDUSER_ADD_RSP,				    // 资金账户增加应答 = 3024
	FUNDUSER_CHANGE_REQ,				// 资金账户修改请求 = 3025
	FUNDUSER_CHANGE_RSP,				// 资金账户修改应答 = 3026
	FEE_SET_REQ,						// 费用设置请求 = 3027
	FEE_SET_RSP,						// 费用设置应答 = 3028
	STOCK_INSTRUMENTBLACK_SET_REQ,	    // 股票黑名单设置请求 = 3029
	STOCK_INSTRUMENTBLACK_SET_RSP,	    // 股票黑名单设置应答 = 3030
	FORBID_BUY_SELL_SET_REQ,			// 禁止买卖设置请求	= 3031
	FORBID_BUY_SELL_SET_RSP,			// 禁止买卖设置应答 = 3032
	POSI_RATE_SET_REQ,				    // 持仓比例设置请求 = 3033
	POSI_RATE_SET_RSP,				    // 持仓比例设置应答 = 3034
	CHILDUSER_AUTOINMONEY_APPROVAL_REQ,	// 子账户自动入金审核请求 = 3035
	CHILDUSER_AUTOINMONEY_APPROVAL_RSP,	// 子账户自动入金审核应答 = 3036
	CHILDUSER_AUTOOUTMONEY_APPROVAL_REQ,// 子账户自动出金审核请求 = 3037
	CHILDUSER_AUTOOUTMONEY_APPROVAL_RSP,// 子账户自动出金审核应答 = 3038
	PASSWORD_CHANGE_REQ,				// 密码修改请求 = 3039
	PASSWORD_CHANGE_RSP,				// 密码修改应答 = 3040

	MANAGER_ADD_REQ,					// 管理员增加请求 = 3041
	MANAGER_ADD_RSP,					// 管理员增加请求应答 = 3042
	MANAGER_CHANGE_REQ,					// 管理员修改请求 = 3043
	MANAGER_CHANGE_RSP,					// 管理员修改请求应答 = 3044
	APPLY_EQUIPMONEY_REQ,               // 申请融资资金请求  =3045
	APPLY_EQUIPMONEY_RSP,               // 申请融资资金请求应答 =3046
    APPLY_EQUIPMONEY_APPROVAL_REQ,      // 申请融资资金审核请求  =3047
    APPLY_EQUIPMONEY_APPROVAL_RSP,      // 申请融资资金审核请求应答 =3048

    CUSTOMSTOCK_ADD_REQ,			    // 自选股票新增请求	= 3049
    CUSTOMSTOCK_ADD_RSP,			    // 自选股票新增应答	= 3050

	ROLES_USER_CHANGE_REQ,			    // 修改用户（机构）之间关系	= 3051
	ROLES_USER_CHANGE_RSP,			    // 修改用户（机构）之间关系	= 3052

    CHILDUSER_AUTO_INMONEY_REQ,			// 子账户自动入金请求 = 3053
    CHILDUSER_AUTO_INMONEY_RSP,			// 子账户自动入金应答 = 3054
    CHILDUSER_AUTO_OUTMONEY_REQ,		// 子账户自动出金请求 = 3055
    CHILDUSER_AUTO_OUTMONEYL_RSP,		// 子账户自动出金应答 = 3056

    CHILDUSER_AUTO_ADD_REQ,				// 子帐户自动开户请求 = 3057
    CHILDUSER_AUTO_ADD_RSP,				// 子帐户自动开户应答 = 3058

	MARGIN_SET_REQ,						// 融券信息设置请求 = 3059
	MARGIN_SET_RSP,						// 融券信息设置应答 = 3060

	//////////////////////// 交易相关 ////////////
	ABOUT_TRADE,					    // 交易相关 = 4000
	OPENCLOSE_REQ,					    // 开平仓请求 = 4001
    ORDERINSERT_MSG,					// 委托提交推送 = 4002
    ORDERCHANGE_MSG,					// 委托改变推送 = 4003
	CANCELORDER_REQ,					// 撤单请求 = 4004
    ORDERCANCEL_MSG,					// 委托撤销推送 = 4005
    TRADEOVER_MSG,					    // 成交推送 = 4006
    POSITION_MSG,					    // 持仓推送 = 4007
    MONEYCHANGE_MSG,					// 资金推送 = 4008
    RISKTIGGER_MSG,					    // 风控推送 = 4009

	//////////////////// 删除相关 ////////////////
	ABOUT_DELETE,				// 删除相关 = 5000
	INSTITUTION_DEL_REQ,		// 机构删除请求 = 5001
	INSTITUTION_DEL_RSP,		// 机构删除应答 = 5002
	ROLES_DEL_REQ,			    // 角色删除请求 = 5003
	ROLES_DEL_RSP,			    // 角色删除应答 = 5004
	ROLES_USER_DEL_REQ,		    // 删除用户（机构）之间关系 = 5005
	ROLES_USER_DEL_RSP,		    // 删除用户（机构）之间关系应答 = 5006
	CHILDUSER_DEL_REQ,		    // 子账户删除请求 = 5007
	CHILDUSER_DEL_RSP,		    // 子账户删除应答 = 5008
	FUNDUSER_DEL_REQ,		    // 资金账户删除请求 = 5009
	FUNDUSER_DEL_RSP,		    // 资金账户删除应答,5010
	MANAGER_DEL_REQ,			// 管理员删除请求 = 5011
	MANAGER_DEL_RSP,			// 管理员删除请求应答 = 5012

    CUSTOMSTOCK_DEL_REQ,		// 自选股票删除请求	= 5013
    CUSTOMSTOCK_DEL_RSP,		// 自选股票删除应答	= 5014

    EMPT_Max_Count,
};

// 消息中的command code；注意：命令码存储顺序一定要与枚举“E_COMM_MSG_TYPE”中对应项保持一致!!!
const char* const gszMsgCommandCode[E_COMM_MSG_TYPE::EMPT_Max_Count] = {
    /////////////////// 登陆相关 //////////
    "1001",
    "1002",
    "1003",
    "1004",
    "1005",
    ///////////////// 获取相关 ////////////
    "2001",
    "2002",
    "2003",
    "2004",
    "2005",
    "2006",
    "2007",
    "2008",
    "2009",
    "2010",
    "2011",
    "2012",
    "2013",
    "2014",
    "2015",
    "2016",
    "2017",
    "2018",
    "2019",
    "2020",
    "2021",
    "2022",
    "2023",
    "2024",
    "2025",
    "2026",
    "2027",
    "2028",
    "2029",
    "2030",
    "2031",
    "2032",
    "2033",
    "2034",
    "2035",
    "2036",
    "2037",
    "2038",
    "2039",
    "2040",
    "2041",
    "2042",
    "2043",
    "2044",
    "2045",
    "2046",
    "2047",
    "2048",
    "2049",
    "2050",
    "2051",
    "2052",
    "2053",
    "2054",
    "2055",
    "2056",
    "2057",
    "2058",
	"2059",
	"2060",
	"2061",
	"2062",
	"2063",
	"2064",
	"2065",
	"2066",
	"2067",
	"2068",
    "2069",
    "2070",
    "2071",
    "2072",
    "2073",
    "2074",
    "2075",
    "2076",
    "2077",
    "2078",
	"2079",
	"2080",
	"2081",
	"2082",
	"2083",
	"2084",
	"2085",
	"2086",
	"2087",
	"2088",
	"2089",
	"2090",
	"2091",
	"2092",
	"2093",
	"2094",
    ///////////////////////////////// 增加/更新 相关 ///////////////////
	"3000",
    "3001",
    "3002",
    "3003",
    "3004",
    "3005",
    "3006",
    "3007",
    "3008",
    "3009",
    "3010",
    "3011",
    "3012",
    "3013",
    "3014",
    "3015",
    "3016",
    "3017",
    "3018",
    "3019",
    "3020",
    "3021",
    "3022",
    "3023",
    "3024",
    "3025",
    "3026",
    "3027",
    "3028",
    "3029",
    "3030",
    "3031",
    "3032",
    "3033",
    "3034",
    "3035",
    "3036",
    "3037",
    "3038",
    "3039",
    "3040",
	"3041",
	"3042",
	"3043",
	"3044",
	"3045",
    "3046",
    "3047",
    "3048",
    "3049",
    "3050",
	"3051",
	"3052",
    "3053",
    "3054",
    "3055",
    "3056",
    "3057",
    "3058",
	"3059",
	"3060",

    //////////////////////// 交易相关 ////////////
	"4000",
    "4001",
    "4002",
    "4003",
    "4004",
    "4005",
    "4006",
    "4007",
    "4008",
    "4009",
	
    //////////////////// 删除相关 ////////////////
	"5000",
    "5001",
    "5002",
    "5003",
    "5004",
    "5005",
    "5006",
    "5007",
    "5008",
    "5009",
    "5010",
	"5011",
	"5012",
    "5013",
    "5014",
};

#endif