/*************************************************
Copyright (C), 2017, HX Tech Co., Ltd.
File name:      struct_declare.h
Author:			XuYC
Version:
Date:
Description:    提供统一的结构体指针声明,防止结构体文件相互包含以及重复定义,加快编译速度
*************************************************/

#ifndef __STRUCT_DECLARE_H__
#define __STRUCT_DECLARE_H__

#ifndef _WIN32_WINNT		// 允许使用特定于 Windows XP 或更高版本的功能。
# define _WIN32_WINNT 0x0501	// 将此值更改为相应的值，以适用于 Windows 的其他版本。
#endif						

#include <memory>
#include "ystruct_define.h"


namespace AllTrade {
    namespace NPMgrCenter {
#pragma region 账户
        // 账户
        struct SAccountBase;
        typedef std::shared_ptr<SAccountBase>   SAccountPtr;
        // 根账户
        struct RootAccount;
        typedef std::shared_ptr<RootAccount>    RootAccountPtr;
        // 机构账户
        struct AgencyAccount;
        typedef std::shared_ptr<AgencyAccount>  AgencyAccountPtr;
        // 风控账户
        struct RiskAccount;
        typedef std::shared_ptr<RiskAccount>    RiskAccountPtr;
        // 管理账户
        struct ManagerAccount;
        typedef std::shared_ptr<ManagerAccount> ManagerAccountPtr;
        // 交易账户
        struct TradeAccount;
        typedef std::shared_ptr<TradeAccount>   TradeAccountPtr;
        // 资金账户
        struct FunderAccount;
        typedef std::shared_ptr<FunderAccount>  FunderAccountPtr;
        
#pragma endregion

        // 在线账户
        struct SOnlineAccount;
        typedef std::shared_ptr<SOnlineAccount>     SOnlineAccountPtr;

#pragma region 资金信息
        // 账户
        struct SMoneyInfo;
        typedef std::shared_ptr<SMoneyInfo>         SMoneyInfoPtr;
        struct SMoneyDetailInfo;
        typedef std::shared_ptr<SMoneyDetailInfo>   SMoneyDetailInfoPtr;
        struct SRiskInfo;
        typedef std::shared_ptr<SRiskInfo>          SRiskInfoPtr;
        struct SApplyMoneyInfo;
        typedef std::shared_ptr<SApplyMoneyInfo>    SApplyMoneyPtr;
        struct SAgencyMoneyDetailInfo;
        typedef std::shared_ptr<SAgencyMoneyDetailInfo>   SAgencyMoneyDetailInfoPtr;

#pragma endregion

#pragma region 交易所
        // 交易所信息
        struct SExchange;
        typedef std::shared_ptr<SExchange>          SExchangePtr;
        typedef std::shared_ptr<const SExchange>    SExchangeCPtr;
        // 品种信息
        struct SProductInfo;
        typedef std::shared_ptr<SProductInfo>       SProductPtr;
        // 合约信息
        struct SContractBase;
        typedef std::shared_ptr<SContractBase>      SContractPtr;
        typedef std::shared_ptr<const SContractBase>  SContractCPtr;
        struct SStockContract;
        typedef std::shared_ptr<SStockContract>     SStockContractPtr;
        // 币种信息
        struct SCurrencyInfo;
        typedef std::shared_ptr<SCurrencyInfo>      SCurrencyPtr;
#pragma endregion

        // 客户自定义佣金
        struct CustomCommInfo;
        typedef std::shared_ptr<CustomCommInfo>     CustomCommInfoPtr;

		// 利息统计
		struct InterestStatistics;
		typedef std::shared_ptr<InterestStatistics>		InterestStatisticsPtr;

		// 利息明细
		struct InterestDetail;
		typedef std::shared_ptr<InterestDetail>			InterestDetailPtr;

    }

    namespace NPTradeCenter {
#pragma region 委托
        //////////////////////////////////////////////////////////////////////////
        // 下单委托信息基类
        struct OrderInfoBase;
        typedef std::shared_ptr<OrderInfoBase>      OrderInfoPtr;

        // 股票下单委托信息
        struct StockOrderInfo;
        typedef std::shared_ptr<StockOrderInfo>     StockOrderPtr;

        // 外盘期货下单委托信息
        struct ForeignFutureOrderInfo;
        typedef std::shared_ptr<ForeignFutureOrderInfo> ForeignFutureOrderPtr;

        // 内盘期货下单委托信息
        struct ChinaFutureOrderInfo;
        typedef std::shared_ptr<ChinaFutureOrderInfo>   ChinaFutureOrderPtr;

        //////////////////////////////////////////////////////////////////////////
        // 撤单委托信息
        struct CancelOrderInfo;
        typedef std::shared_ptr<CancelOrderInfo>        CancelOrderPtr;
#pragma endregion

#pragma region 成交
        //////////////////////////////////////////////////////////////////////////
        // 成交信息
        struct TradeInfoBase;
        typedef std::shared_ptr<TradeInfoBase>          TradeInfoPtr;

        // 股票成交信息
        struct StockTradeInfo;
        typedef std::shared_ptr<StockTradeInfo>         StockTradePtr;

        // 外盘期货成交信息
        struct ForeignFutureTradeInfo;
        typedef std::shared_ptr<ForeignFutureTradeInfo> ForeignFutureTradePtr;

        // 内盘期货成交信息
        struct ChinaFutureTradeInfo;
        typedef std::shared_ptr<ChinaFutureTradeInfo>   ChinaFutureTradePtr;
#pragma endregion

#pragma region 持仓
        //////////////////////////////////////////////////////////////////////////
        // 持仓信息
        struct PositionInfoBase;
        typedef std::shared_ptr<PositionInfoBase>          PositionInfoPtr;

        // 股票持仓信息
        struct StockPositionInfo;
        typedef std::shared_ptr<StockPositionInfo>         StockPositionPtr;

        // 外盘期货持仓信息
        struct ForeignFuturePositionInfo;
        typedef std::shared_ptr<ForeignFuturePositionInfo> ForeignFuturePositionPtr;

        // 内盘期货持仓信息
        struct ChinaFuturePositionInfo;
        typedef std::shared_ptr<ChinaFuturePositionInfo>   ChinaFuturePositionPtr;
#pragma endregion

        //////////////////////////////////////////////////////////////////////////
        // 行情信息数据基类
        struct QuoteInfoBase;
        typedef std::shared_ptr<QuoteInfoBase>          QuoteInfoPtr;

        struct TradeFee;
        typedef std::shared_ptr<TradeFee>               TradeFeePtr;

        struct ImmRiskControlSt;
        typedef std::shared_ptr<ImmRiskControlSt>       ImmRiskControlPtr;

        struct GlobalData;
        typedef std::shared_ptr<GlobalData>             GlobalDataPtr;

        // 账户
        struct SForbidTradeInfo;
        typedef std::shared_ptr<SForbidTradeInfo>       SForbidTradePtr;

        // 账户
        struct SPositionRateInfo;
        typedef std::shared_ptr<SPositionRateInfo>      SPositionRatePtr;


#pragma region 融券
		// 融券持仓
		struct MarginPositionInfo;
		typedef std::shared_ptr<MarginPositionInfo>		MarginPositionInfoPtr;

		// 融券成交
		struct MarginTradeInfo;
		typedef std::shared_ptr<MarginTradeInfo>		MarginTradeInfoPtr;

		// 融券委托
		struct MarginOrderInfo;
		typedef std::shared_ptr<MarginOrderInfo>		MarginOrderInfoPtr;

		// 融券信息
		struct MarginInfo;
		typedef std::shared_ptr<MarginInfo>				MarginInfoPtr;

		// 融券剩余信息
		struct MarginLeftInfo;
		typedef std::shared_ptr<MarginLeftInfo>			MarginLeftInfoPtr;

		
#pragma endregion

    }

#pragma region 权限控制
    // 权限业务
    struct AuthorityBussnesses;
    typedef std::shared_ptr<AuthorityBussnesses>    AuthorityBussnessesPtr;

    // 日志记录
    struct AuthorityChangeLog;
    typedef std::shared_ptr<AuthorityChangeLog>     AuthorityChangeLogPtr;

    // 权限功能
    struct AuthorityFunctions;
    typedef std::shared_ptr<AuthorityFunctions>     AuthorityFunctionsPtr;

    // 账户权限功能
    struct AuthorityFunctionsUserId;
    typedef std::shared_ptr<AuthorityFunctionsUserId>  AuthorityFunctionsUserIdPtr;

    // 权限角色功能
    struct AuthorityRoleFunctions;
    typedef std::shared_ptr<AuthorityRoleFunctions>  AuthorityRoleFunctionsPtr;

    // 权限角色用户
    struct AuthorityRoleUsers;
    typedef std::shared_ptr<AuthorityRoleUsers>     AuthorityRoleUsersPtr;

    // 权限角色
    struct AuthorityRoles;
    typedef std::shared_ptr<AuthorityRoles>         AuthorityRolesPtr;
#pragma endregion



}

#endif