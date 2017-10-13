/*************************************************
Copyright (C), 2017, HX Tech Co., Ltd.
File name:      struct_declare.h
Author:			XuYC
Version:
Date:
Description:    �ṩͳһ�Ľṹ��ָ������,��ֹ�ṹ���ļ��໥�����Լ��ظ�����,�ӿ�����ٶ�
*************************************************/

#ifndef __STRUCT_DECLARE_H__
#define __STRUCT_DECLARE_H__

#ifndef _WIN32_WINNT		// ����ʹ���ض��� Windows XP ����߰汾�Ĺ��ܡ�
# define _WIN32_WINNT 0x0501	// ����ֵ����Ϊ��Ӧ��ֵ���������� Windows �������汾��
#endif						

#include <memory>
#include "ystruct_define.h"


namespace AllTrade {
    namespace NPMgrCenter {
#pragma region �˻�
        // �˻�
        struct SAccountBase;
        typedef std::shared_ptr<SAccountBase>   SAccountPtr;
        // ���˻�
        struct RootAccount;
        typedef std::shared_ptr<RootAccount>    RootAccountPtr;
        // �����˻�
        struct AgencyAccount;
        typedef std::shared_ptr<AgencyAccount>  AgencyAccountPtr;
        // ����˻�
        struct RiskAccount;
        typedef std::shared_ptr<RiskAccount>    RiskAccountPtr;
        // �����˻�
        struct ManagerAccount;
        typedef std::shared_ptr<ManagerAccount> ManagerAccountPtr;
        // �����˻�
        struct TradeAccount;
        typedef std::shared_ptr<TradeAccount>   TradeAccountPtr;
        // �ʽ��˻�
        struct FunderAccount;
        typedef std::shared_ptr<FunderAccount>  FunderAccountPtr;
        
#pragma endregion

        // �����˻�
        struct SOnlineAccount;
        typedef std::shared_ptr<SOnlineAccount>     SOnlineAccountPtr;

#pragma region �ʽ���Ϣ
        // �˻�
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

#pragma region ������
        // ��������Ϣ
        struct SExchange;
        typedef std::shared_ptr<SExchange>          SExchangePtr;
        typedef std::shared_ptr<const SExchange>    SExchangeCPtr;
        // Ʒ����Ϣ
        struct SProductInfo;
        typedef std::shared_ptr<SProductInfo>       SProductPtr;
        // ��Լ��Ϣ
        struct SContractBase;
        typedef std::shared_ptr<SContractBase>      SContractPtr;
        typedef std::shared_ptr<const SContractBase>  SContractCPtr;
        struct SStockContract;
        typedef std::shared_ptr<SStockContract>     SStockContractPtr;
        // ������Ϣ
        struct SCurrencyInfo;
        typedef std::shared_ptr<SCurrencyInfo>      SCurrencyPtr;
#pragma endregion

        // �ͻ��Զ���Ӷ��
        struct CustomCommInfo;
        typedef std::shared_ptr<CustomCommInfo>     CustomCommInfoPtr;

		// ��Ϣͳ��
		struct InterestStatistics;
		typedef std::shared_ptr<InterestStatistics>		InterestStatisticsPtr;

		// ��Ϣ��ϸ
		struct InterestDetail;
		typedef std::shared_ptr<InterestDetail>			InterestDetailPtr;

    }

    namespace NPTradeCenter {
#pragma region ί��
        //////////////////////////////////////////////////////////////////////////
        // �µ�ί����Ϣ����
        struct OrderInfoBase;
        typedef std::shared_ptr<OrderInfoBase>      OrderInfoPtr;

        // ��Ʊ�µ�ί����Ϣ
        struct StockOrderInfo;
        typedef std::shared_ptr<StockOrderInfo>     StockOrderPtr;

        // �����ڻ��µ�ί����Ϣ
        struct ForeignFutureOrderInfo;
        typedef std::shared_ptr<ForeignFutureOrderInfo> ForeignFutureOrderPtr;

        // �����ڻ��µ�ί����Ϣ
        struct ChinaFutureOrderInfo;
        typedef std::shared_ptr<ChinaFutureOrderInfo>   ChinaFutureOrderPtr;

        //////////////////////////////////////////////////////////////////////////
        // ����ί����Ϣ
        struct CancelOrderInfo;
        typedef std::shared_ptr<CancelOrderInfo>        CancelOrderPtr;
#pragma endregion

#pragma region �ɽ�
        //////////////////////////////////////////////////////////////////////////
        // �ɽ���Ϣ
        struct TradeInfoBase;
        typedef std::shared_ptr<TradeInfoBase>          TradeInfoPtr;

        // ��Ʊ�ɽ���Ϣ
        struct StockTradeInfo;
        typedef std::shared_ptr<StockTradeInfo>         StockTradePtr;

        // �����ڻ��ɽ���Ϣ
        struct ForeignFutureTradeInfo;
        typedef std::shared_ptr<ForeignFutureTradeInfo> ForeignFutureTradePtr;

        // �����ڻ��ɽ���Ϣ
        struct ChinaFutureTradeInfo;
        typedef std::shared_ptr<ChinaFutureTradeInfo>   ChinaFutureTradePtr;
#pragma endregion

#pragma region �ֲ�
        //////////////////////////////////////////////////////////////////////////
        // �ֲ���Ϣ
        struct PositionInfoBase;
        typedef std::shared_ptr<PositionInfoBase>          PositionInfoPtr;

        // ��Ʊ�ֲ���Ϣ
        struct StockPositionInfo;
        typedef std::shared_ptr<StockPositionInfo>         StockPositionPtr;

        // �����ڻ��ֲ���Ϣ
        struct ForeignFuturePositionInfo;
        typedef std::shared_ptr<ForeignFuturePositionInfo> ForeignFuturePositionPtr;

        // �����ڻ��ֲ���Ϣ
        struct ChinaFuturePositionInfo;
        typedef std::shared_ptr<ChinaFuturePositionInfo>   ChinaFuturePositionPtr;
#pragma endregion

        //////////////////////////////////////////////////////////////////////////
        // ������Ϣ���ݻ���
        struct QuoteInfoBase;
        typedef std::shared_ptr<QuoteInfoBase>          QuoteInfoPtr;

        struct TradeFee;
        typedef std::shared_ptr<TradeFee>               TradeFeePtr;

        struct ImmRiskControlSt;
        typedef std::shared_ptr<ImmRiskControlSt>       ImmRiskControlPtr;

        struct GlobalData;
        typedef std::shared_ptr<GlobalData>             GlobalDataPtr;

        // �˻�
        struct SForbidTradeInfo;
        typedef std::shared_ptr<SForbidTradeInfo>       SForbidTradePtr;

        // �˻�
        struct SPositionRateInfo;
        typedef std::shared_ptr<SPositionRateInfo>      SPositionRatePtr;


#pragma region ��ȯ
		// ��ȯ�ֲ�
		struct MarginPositionInfo;
		typedef std::shared_ptr<MarginPositionInfo>		MarginPositionInfoPtr;

		// ��ȯ�ɽ�
		struct MarginTradeInfo;
		typedef std::shared_ptr<MarginTradeInfo>		MarginTradeInfoPtr;

		// ��ȯί��
		struct MarginOrderInfo;
		typedef std::shared_ptr<MarginOrderInfo>		MarginOrderInfoPtr;

		// ��ȯ��Ϣ
		struct MarginInfo;
		typedef std::shared_ptr<MarginInfo>				MarginInfoPtr;

		// ��ȯʣ����Ϣ
		struct MarginLeftInfo;
		typedef std::shared_ptr<MarginLeftInfo>			MarginLeftInfoPtr;

		
#pragma endregion

    }

#pragma region Ȩ�޿���
    // Ȩ��ҵ��
    struct AuthorityBussnesses;
    typedef std::shared_ptr<AuthorityBussnesses>    AuthorityBussnessesPtr;

    // ��־��¼
    struct AuthorityChangeLog;
    typedef std::shared_ptr<AuthorityChangeLog>     AuthorityChangeLogPtr;

    // Ȩ�޹���
    struct AuthorityFunctions;
    typedef std::shared_ptr<AuthorityFunctions>     AuthorityFunctionsPtr;

    // �˻�Ȩ�޹���
    struct AuthorityFunctionsUserId;
    typedef std::shared_ptr<AuthorityFunctionsUserId>  AuthorityFunctionsUserIdPtr;

    // Ȩ�޽�ɫ����
    struct AuthorityRoleFunctions;
    typedef std::shared_ptr<AuthorityRoleFunctions>  AuthorityRoleFunctionsPtr;

    // Ȩ�޽�ɫ�û�
    struct AuthorityRoleUsers;
    typedef std::shared_ptr<AuthorityRoleUsers>     AuthorityRoleUsersPtr;

    // Ȩ�޽�ɫ
    struct AuthorityRoles;
    typedef std::shared_ptr<AuthorityRoles>         AuthorityRolesPtr;
#pragma endregion



}

#endif