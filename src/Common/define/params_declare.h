/*************************************************
Copyright (C), 2017, HX Tech Co., Ltd.
File name:      params_declare.h
Author:			XuYC
Version:
Date:
Description:    提供统一的结构体参数定义,便于维护与参数指定
*************************************************/

#ifndef __PARAMS_DECLARE_H__
#define __PARAMS_DECLARE_H__

#include <string>

namespace AllTrade {

    //GUID类型
    typedef char	GUIDType[65];

    //认证信息
    typedef char    CertInfoType[401];

    //版本信息
    typedef char    VersionType[51];

    //登录IP信息
    typedef char    LoginIpType[41];

    //应用程序ID
    typedef char    AppIDType[101];

    //登陆机器信息，主要包括mac地址
    typedef char    MachineInfoType[201];

    typedef unsigned char  u_char;

    //长度类型
    typedef unsigned int    SizeType;

    ///////////////////////////////////////////////////////////////////////////
    //日期和时间类型(格式 yyyy-MM-dd hh:mm:ss)
    typedef char            DateTimeType[21];
    typedef std::string     PDateTimeType;
    //日期类型(格式 yyyy-MM-dd)
    typedef char		    DateType[11];
    typedef std::string     PDateType;
    //时间类型(格式 hh:mm:ss)
    typedef char		    TimeType[11];
    typedef std::string     PTimeType;

    ///////////////////////////////////////////////////////////////////////////
    //错误号类型(0-表示成功),详见protocol_error.h
    typedef int				ErrorCodeType;

    //错误信息
    typedef char			ErrorTextType[51];
    typedef std::string     PErrorTextType;

    //备注信息
    typedef char			RemarkTextType[1025];
    typedef std::string     PRemarkTextType;

    //////////////////////////////////////////////////////////////////////////
    // 账户属性
    enum E_ACCOUNT_PROP
    {
        EAP_Invalid = -1,
        EAP_Root,	            // 根账户
        EAP_Agency,             // 机构账户
        EAP_Risker,             // 风控账户
        EAP_Manager,            // 管理账户
        EAP_Trader,             // 交易账户
        EAP_Funder,             // 资金账户
        EAP_MAX,
    };
    // 账户类型
    enum E_ACCOUNT_TYPE
    {
        EAT_Invalid = -1,
        EAT_Simulation,         // 模拟账户
        EAT_Real,               // 实盘账户
        EAT_SimuReal,           // 模拟或实盘账户
        EAT_MaxCount
    };
    // 设置账户权限方式
    enum E_PERMISSION_TYPE
    {
        EPT_Invalid = -1,
        EPT_AUTO,               // 自动
        EPT_MANUAL,             // 手动
        EPT_MaxCount
    };
    // 账户状态
    enum E_ACCOUNT_STATUS
    {
        EAS_Invalid = -1,
        EAS_Check_Create,       // 创建申请审核中
        EAS_Check_Unpass,       // 审核拒绝
        EAS_OverTime,           // 已过期,禁止登录
        EAS_Check_Delete,       // 删除申请审核中
        EAS_Deleted,            // 账户已删除但留存数据
        EAS_Using,		        // 通过审核使用中
        EAS_Warning,		    // 异常警告中(仅在管理/风控/管理账户中做异常显示)
        EAS_StopOpen,           // 风控/复审,禁止开仓
        EAS_Freezing,           // 冻结中,禁止交易
        EAS_MaxCount
    };

    //////////////////////////////////////////////////////////////////////////
    // 机构账户属性
    enum E_AGENCY_PROP
    {
        EAP_INVALID = -1,
        EAP_PROXY,              // 代理商账户
        EAP_COMMON,             // 机构账户
    };

    ///////////////////////////////////////////////////////////////////////////
    // 出入金方式
    enum OIMM_Change_Type
    {
        OIMM_Type_Invalid = -1,
        OIMM_In_Deposit,		// 加劣后资金
        OIMM_In_Equipment,		// 加优先资金
        OIMM_In_BlueAdd,		// 资金蓝补
        OIMM_Out_Deposit,		// 扣劣后资金
        OIMM_Out_Equipment,		// 扣优先资金
        OIMM_Out_RedSub,		// 资金红冲
        OIMM_Type_Num
    };

    //融资资金审核流水ID类型
    typedef long long				ApplyMoneyIDType;
//     typedef std::string				PApplyMoneyIDType;
    // 资金审核状态
    enum E_APPLY_MONEY_STATUS
    {
        EAMS_Invalid = -1,
        EAMS_Check_Create,       // 创建申请审核中
        EAMS_Check_Unpass,       // 审核拒绝
        EAMS_Using,		         // 通过审核
        EAMS_MaxCount
    };

    // 资金变动方式
    enum Money_Change_Type
    {
        MC_Type_Invalid = -1,
        MC_In_Deposit,		            // 加劣后资金
        MC_In_Equipment,                // 加优先资金
        MC_In_BlueAdd,		            // 资金蓝补
        MC_Out_Deposit,		            // 扣劣后资金
        MC_Out_Equipment,               // 扣优先资金
        MC_Out_RedSub,		            // 资金红冲
        MC_Order_Freeze,                // 开仓委托冻结资金,可用资金减少
        MC_Order_Cancel,                // 撤单,冻结资金返还
        MC_Trade_Open,                  // 开仓成交(成交价)
        MC_Trade_Open_Fee,              // 开仓成交交易佣金手续费
        MC_Trade_Open_TransferFee,      // 开仓成交过户费
        MC_Trade_Open_InfoMatchFee,     // 开仓成交信息撮合费
        MC_Trade_Thaw,                  // 委托冻结资金返还
        MC_Trade_Close,                 // 平仓成交资金返还(成交价)
        MC_Trade_Close_Fee,             // 平仓成交交易佣金手续费
        MC_Trade_Close_TransferFee,     // 平仓成交过户费
        MC_Trade_Close_InfoMatchFee,    // 平仓成交信息撮合费
        MC_Trade_Close_StampFee,        // 平仓成交印花税
        MC_Commission,                  // 系统返佣
        MC_Money_Settle,                // 系统资金结算,改为可提取资金
        MC_Profit,                      // 系统分成抽取
        MC_Type_Num
    };

    // 机构返佣/分成等资金变动方式
    enum Agency_Money_Change_Type
    {
        AMCT_Invalid = -1,
        AMCT_InfoMatch_Commission,      // 信息撮合费佣金
        AMCT_Exchange_Commission,       // 交易所佣金
        AMCT_Trade_Profit,              // 盈利分成
    };


    //货币ID类型
    typedef GUIDType				CurrencyIDType;
    typedef std::string				PCurrencyIDType;
    //货币编号类型
    typedef char					CurrencyCodeType[11];
    typedef std::string				PCurrencyCodeType;
    //货币名称类型
    typedef char					CurrencyNameType[21];
    typedef std::string				PCurrencyNameType;

    ///////////////////////////////////////////////////////////////////////////
    //操作员类型
    enum class OperatorTradeType : int
    {
        OPERATOR_TRADE_Invalid = -1,
        OPERATOR_TRADE_PC,              // PC端客户自发起
        OPERATOR_TRADE_APP,             // APP端客户自发起
        OPERATOR_TRADE_MC,              // 后台监控端发起
        OPERATOR_TRADE_RC,              // 后台风控端发起
        OPERATOR_TRADE_SYSTEM,          // 系统发起
    };

    ///////////////////////////////////////////////////////////////////////////
    //委托交易模式类型,是否同步至真实交易所
    enum class OrderTradeModeType : int
    {
        ORDERTRADE_MODE_Invalid = -1,
        ORDERTRADE_MODE_SYNC,             // 同步至交易所
        ORDERTRADE_MODE_SIMULATE,         // 同步至仿真交易端
    };

    ///////////////////////////////////////////////////////////////////////////
    //交易所ID类型
    typedef GUIDType				ExchangeIDType;
    typedef std::string				PExchangeIDType;
    //交易所代码类型
    typedef char					ExchangeCodeType[11];
    typedef std::string				PExchangeCodeType;
    //交易所名称类型
    typedef char					ExchangeNameType[31];
    typedef std::string				PExchangeNameType;

    ///////////////////////////////////////////////////////////////////////////
    //接口类型类型
    enum class ApiTypeType : int
    {
        APIType_TYPE_Invalid = -1,
        APIType_TYPE_CTP = 0,
        APIType_TYPE_ESUNNY,
        APIType_TYPE_IB,
        APIType_TYPE_SP,
    };

    ///////////////////////////////////////////////////////////////////////////
    //商品类型类型
    enum class CommodityTypeType : int
    {
        COMMODITY_TYPE_Invalid = -1,
        COMMODITY_TYPE_STOCK = 0,   // 股票
        COMMODITY_TYPE_FUTURE_F,    // 外盘期货
        COMMODITY_TYPE_FUTURE_C,    // 内盘期货
        COMMODITY_TYPE_OPTION,      // 期权
        COMMODITY_TYPE_GOODS,       // 现货
		COMMODITY_TYPE_MARGIN,      // 股票融券
    };

    ///////////////////////////////////////////////////////////////////////////
    //品种ID类型,股市没有品种
    typedef GUIDType				ProductIDType;
    typedef std::string				PProductIDType;
    //品种代码类型
    typedef char					ProductCodeType[11];
    typedef std::string				PProductCodeType;
    //品种名称类型
    typedef char					ProductNameType[21];
    typedef std::string				PProductNameType;

    ///////////////////////////////////////////////////////////////////////////
    //合约ID类型
    typedef GUIDType				ContractIDType;
    typedef std::string				PContractIDType;
    //合约代码类型
    typedef char					ContractCodeType[21];
    typedef std::string				PContractCodeType;
    //合约名称类型
    typedef char					ContractNameType[21];
    typedef std::string				PContractNameType;
    //合约到期日天数(合约还有几天到期), -1表示无限时间
    typedef int						ContractLastDays;
    //股票合约显示(业绩)属性类型, S/ST/*ST...
    typedef char				    DisplayPropType[21];
    typedef std::string				PDisplayPropType;
    //股票合约板块属性类型, 航空/交通...
    typedef char				    PlatePropType[21];
    typedef std::string				PPlatePropType;
    //股票合约拼音代码
    typedef char				    ContractPYCodeType[21];
    typedef std::string				PContractPYCodeType;
    // 股票合约上市状态
    enum class StockStatusType : int
    {
        STOCKSTATUS_Invalid = -1,
        STOCKSTATUS_L = 0,      // 上市
        STOCKSTATUS_S,          // 暂停
        STOCKSTATUS_DE,         // 终止上市
        STOCKSTATUS_UN,         // 未上市
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
    // 股票合约行情状态
    enum class QuoteStatusType : int
    {
        QUOTESTATUS_Invalid = -1,
        QUOTESTATUS_Normal = 0, // 正常
        QUOTESTATUS_Close,      // 闭市
        QUOTESTATUS_Stop,       // 停牌
    };

    ///////////////////////////////////////////////////////////////////////////
    //股票合约所属股票类型, A股/B股...
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
        SPAT_Main_Board = 0,    // 主板块
        SPAT_Second_Board,      // 创业板块
        SPAT_SME_Board,         // 中小板
        SPAT_NEEQ_Board,        // 新三板
    };

    ///////////////////////////////////////////////////////////////////////////
    //委托编号类型(每个交易服务器内唯一标志,由服务器生成)
    typedef GUIDType				OrderIDType;
    typedef std::string				POrderIDType;
    //本地委托编号类型(服务器内全局唯一标志,UserID+GUID)
    typedef char					OrderStreamType[129];
    typedef std::string				POrderStreamType;
    //本地委托编号类型(每个交易服务器内唯一标志,由服务器生成)
    typedef GUIDType				OrderRefType;
    typedef std::string				POrderRefType;
    //影子订单编号(每个交易服务器内唯一标志,由服务器生成)
    typedef GUIDType				ShadowOrderIDType;
    typedef std::string				PShadowOrderIDType;
    //影子成交编号(每个交易服务器内唯一标志,由服务器生成)
    typedef GUIDType				ShadowTradeIDType;
    typedef std::string				PShadowTradeIDType;
    //系统编号类型(上级交易所报单唯一标志,不同交易所可能会重复)
    typedef GUIDType				SystemIDType;
    typedef std::string				PSystemIDType;
    //成交编号(每个交易服务器内唯一标志,由服务器生成)
    typedef GUIDType				TradeIDType;
    typedef std::string				PTradeIDType;
    //持仓编号(每个交易服务器内唯一标志,由服务器生成)
    typedef GUIDType				PositionIDType;
    typedef std::string				PPositionIDType;

    // 业务名称(每个交易服务器内唯一标志,由服务器生成)
    typedef char					BussnessName[64];
    typedef std::string				PBussnessName;
    // 日志内容(每个交易服务器内唯一标志,由服务器生成)
    typedef char					LogContent[200];
    typedef std::string				PLogContent;
    // 功能名称(每个交易服务器内唯一标志,由服务器生成)
    typedef char					FunctionName[64];
    typedef std::string				PFunctionName;
    // 角色名称(每个交易服务器内唯一标志,由服务器生成)
    typedef char					RolesName[24];
    typedef std::string				PRolesName;

    // 权限业务(每个交易服务器内唯一标志,由服务器生成)
    typedef char					IsHide;
    const IsHide				    IsHide_Hide = 0x00;
    const IsHide				    IsHide_NoIsHide = 0x01;

    // 角色名称(每个交易服务器内唯一标志,由服务器生成)
    typedef char					IsSort;
    const IsSort				    IsSort_Sort = 0x00;
    const IsSort				    IsSort_NoSort = 0x01;

    // 权限角色(每个交易服务器内唯一标志,由服务器生成)
    enum E_RolesType
    {
        ERT_Invalid = -1,
        ERT_Institution,            // 机构
        ERT_Manager,				// 管理员
        ERT_MaxCount
    };

	// 操作类型(每个交易服务器内唯一标志,由服务器生成)
	enum E_OperationType
	{
		EOT_Invalid = -1,
		EOT_IsOperation,            // 可操作
		EOT_IsNotOperation,			// 不可操作
		EOT_MaxCount
	};

    //////////////////////////////////////////////////////////////////
    //基本子账户信息

    ///////////////////////////////////////////////////////////////////////////
    //用户ID类型
    typedef GUIDType				UserIDType;
    typedef std::string				PUserIDType;

    //账户登录名称
    typedef char                    LoginNameType[51];
    typedef std::string				PLoginNameType;
    //账户名称
    typedef char                    AccountNameType[51];
    typedef std::string				PAccountNameType;
    //登录密码
    typedef char                    LoginPasswordType[25];
    typedef std::string				PLoginPasswordType;
    //昵称
    typedef char                    NickNameType[51];
    typedef std::string				PNickNameType;
    //真实姓名
    typedef char                    RealNameType[51];
    typedef std::string				PRealNameType;
    //手机号
    typedef char                    PhoneNumberType[18];
    typedef std::string				PPhoneNumberType;
    //身份证号
    typedef char                    IdentityIDType[20];
    typedef std::string				PIdentityIDType;
    //银行名
    typedef char                    BankNameType[100];
    typedef std::string				PBankNameType;
    //银行卡号
    typedef char                    BankCardNoType[50];
    typedef std::string				PBankCardNoType;

    //推广开户链接
    typedef char                    PopularizeLinkType[1025];
    typedef std::string				PPopularizeLinkType;

    //实盘账户接口连接
    typedef char                    HedgeApiType[15];
    typedef std::string				PHedgeApiType;

    //层级名称
    typedef char                    LevelNameType[24];
    typedef std::string				PLevelNameType;

    // 实盘账户对应公司名称
    typedef char                    FundCompanyType[51];
    typedef std::string				PFundCompanyType;

    //资金流号类型
    typedef char					MoneyStreamType[65];
    typedef std::string				PMoneyStreamType;


    ///////////////////////////////////////////////////////////////////////////
    //委托类型
    enum class OrderTypeType : int
    {
        ORDER_TYPE_Invalid = -1,
        ORDER_TYPE_LIMIT = 0,   // 限价
        ORDER_TYPE_MARKET,      // 市价
        ORDER_TYPE_STOP_LIMIT,  // 限价止损
        ORDER_TYPE_STOP_MARKET, // 市价止损
    };

    ///////////////////////////////////////////////////////////////////////////
    //委托模式类型
    enum class OrderModeType : int
    {
        ORDER_MODE_Invalid = -1,
        ORDER_MODE_FOK = 0,     // 立即全部成交否则自动撤销指令(FOK指令)，指在限定价位下达指令，如果该指令下所有申报手数未能全部成交，该指令下所有申报手数自动被系统撤销。
        ORDER_MODE_FAK,         // 立即成交剩余指令自动撤销指令(FAK指令)，指在限定价位下达指令，如果该指令下部分申报手数成交，该指令下剩余申报手数自动被系统撤销
        ORDER_MODE_GFD,         // 当日有效
        ORDER_MODE_GTC,         // 取消前有效
        ORDER_MODE_GTD,         // 指定日期前有效
    };

    ///////////////////////////////////////////////////////////////////////////
    //买卖类型
    enum class DirectType : int
    {
        DIRECT_Invalid = -1,
        DIRECT_BUY,         // 买入
        DIRECT_SELL,        // 卖出
		DIRECT_Margin,      // 融券
		DIRECT_BackMargin,  // 还券
    };

    ///////////////////////////////////////////////////////////////////////////
    //开平类型
    enum class OffsetType : int
    {
        OFFSET_Invalid = -1,
        OFFSET_OPEN = 0,        // 开仓
        OFFSET_COVER,           // 平仓
        OFFSET_COVER_TODAY,     // 平今
    };

    ///////////////////////////////////////////////////////////////////////////
    //委托状态类型
    enum class OrderStateType : int
    {
        ORDER_STATE_Invalid = -1,
        ORDER_STATE_FAIL = 0,       // 指令失败
        ORDER_STATE_SUPPENDING,     // 提交中
        ORDER_STATE_SUPPENDED,      // 已挂起
        ORDER_STATE_ACCEPT,         // 已受理,加入至服务器队列
        ORDER_STATE_QUEUED,         // 已排队,加入至竞价/交易队列/提交至交易所
        ORDER_STATE_DELETEING,      // 待撤消
        ORDER_STATE_PARTDELETED,    // 部分撤单
        ORDER_STATE_DELETED,        // 完全撤单
        ORDER_STATE_PARTFINISHED,   // 部分成交
        ORDER_STATE_FINISHED,       // 完全成交
    };
    ///////////////////////////////////////////////////////////////////////////
    //委托状态说明类型
    typedef int					    OrderStateExplainType;
    const OrderStateExplainType     Invalid_OrderState_Explain = -1;
    const OrderStateExplainType     OSET_Err_EffectVol = -2;

    const OrderStateExplainType     OSET_Err_No = 0;

    ///////////////////////////////////////////////////////////////////////////
    //风险控制推送提示类型
    enum RiskControlType : int
    {
        RCT_Invalid = 0,
        RCT_WarningLine,    // 警告线
        RCT_ForceLine,      // 强平线
        RCT_LimitLine,      // 限仓线
    };

    //////////////////////////////////////////////////////////////////////////
    // 禁止交易风控规则类型
    enum ForbidTradeType : int
    {
        FTT_Invalid = -1,
        FTT_LossCorporateStock,	// 亏损企业股票
        FTT_RiseStopStock,		// 当前涨停股票
        FTT_FallStopStock,		// 当前跌停股票
        FTT_NewStock,			// 新股(上市20天)
    };
    // 禁止交易风控操作类型
    enum ForbidTradeOperatorType : int
    {
        FTOT_Invalid = -1,
        FTOT_AllowTrade,		// 允许买卖
        FTOT_AllowBuy,			// 只许买入
        FTOT_AllowSell,			// 只许卖出
        FTOT_ForbidTrade,		// 禁止买卖
    };

    //////////////////////////////////////////////////////////////////////////
    // 持仓比例规则类型
    enum PositionRateType : int
    {
        PRT_Invalid = -1,
        PRT_SameStock,          // 同一股票持仓比例不超过总资产的比例
//         PRT_SamePlateArea,		// 同一行业板块不超过总资产的比例
        PRT_Second_Board,		// 创业板持仓不超过总持仓比例
    };

}

#endif