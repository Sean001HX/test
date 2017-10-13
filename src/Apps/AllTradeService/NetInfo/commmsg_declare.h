#ifndef  __COMM_MESSAGE_DECLARE_H__
#define  __COMM_MESSAGE_DECLARE_H__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif

#if defined(_MSC_VER) && (_MSC_VER < 1700)
#error "编译器版本必须是VS2012或以上!"
#endif

#include <loki/Visitor.h>		// 使用了Loki中的cyclic visitor模板
#include <loki/TypelistMacros.h>
#include <loki/Functor.h>
#include <loki/AssocVector.h>

#include <memory>
#include <map>

namespace xyc_communication
{
	// Forward declaration
	class CommMsgBase;				        // 1
    class CommMsgLogin;				        // 2
    class CommMsgLogout;				    // 3
    class CommMsgHeartBeat;				    // 4
    class CommMsgAgencyQry;                 // 5
    class CommMsgAgencyPreApprovalQry;      // 6
    class CommMsgAgencyLinkQry;             // 7
    class CommMsgRolesQry;                  // 8
    class CommMsgAgencyRolesQry;            // 9
    class CommMsgCommissQry;                // 10
    class CommMsgCommissDtlQry;             // 11
    class CommMsgProfitCommisslQry;         // 12
    class CommMsgProfitCommissDtlQry;       // 13
    class CommMsgToplogicalTreeQry;         // 14
    class CommMsgChildAccQry;               // 15
    class CommMsgChildApprovalQry;          // 16
    class CommMsgFundAccQry;                // 17
    class CommMsgOnlineAccQry;              // 18
    class CommMsgStockContractQry;          // 19
    class CommMsgStockBlackQry;             // 20
    class CommMsgForbidBuySellQry;          // 21
    class CommMsgPosiRateQry;               // 22
    class CommMsgPosiQry;                   // 23
    class CommMsgCurrentyEntrustQry;        // 24
    class CommMsgTodayEntrustQry;           // 25
    class CommMsgHistoryEntrustQry;         // 26
    class CommMsgTradeQry;                  // 27
    class CommMsgHistoryTradeQry;           // 28
    class CommMsgFundQry;                   // 29
    class CommMsgFundSerialQry;             // 30
    class CommMsgDeliveryQry;               // 31
    class CommMsgFundMonitQry;              // 32
//     class CommMsgTimeTradeQry;              // 33
    class CommMsgSumPosiQry;                // 33
    class CommMsgTimeWarnQry;               // 34
    class CommMsgEquipMoneyQry;                // 35
    class CommMsgAutoOutMoneyQry;               // 36
    class CommMsgFeeSetQry;                 // 37
    class CommMsgAgencyAdd;                 // 38
    class CommMsgAgencyChange;              // 39
    class CommMsgAgencyApproval;            // 40
    class CommMsgRolesAdd;                  // 41
    class CommMsgRolesChange;               // 42
    class CommMsgBindRelation;              // 43
    class CommMsgUserRoleAddRelation;       // 44
    class CommMsgChildAccAdd;               // 45
    class CommMsgChildAccChange;            // 46
    class CommMsgChildAccInmoney;           // 47
    class CommMsgChildAccApproval;          // 48
    class CommMsgFundAccAdd;                // 49
    class CommMsgFundAccChange;             // 50
    class CommMsgFeeSet;                    // 51
    class CommMsgStockBlackSet;             // 52
    class CommMsgForbidBuySellSet;          // 53
    class CommMsgPosiRateSet;               // 54
    class CommMsgAutoInMoneyApproval;      // 55
    class CommMsgAutoOutMoneyApproval;     // 56
    class CommMsgPswChange;                 // 57
    class CommMsgOpenClose;                 // 58
    class CommMsgCancelOrder;               // 59
	class CommMsgSelfFunctionQry;           // 60
	class CommMsgRoleFunctionQry;           // 61
	class CommMsgDelRole;					// 62
	class CommMsgDelRoleUser;				// 63
    class CommMsgManagerAdd;				// 64
    class CommMsgManagerChange;				// 65
    class CommMsgManagerQry;                // 66
	class CommMsgGetAllBussnessUser;        // 67
//     class CommMsgGetOnlineChildren;         // 67
    class CommMsgApplyEquipMoney;                // 68
    class CommMsgApprovalApplyEquipMoney;        // 69

    class CommMsgAgencyDelete;              // 70
    class CommMsgChildDelete;               // 71
    class CommMsgFunderDelete;              // 72
    class CommMsgManagerDelete;             // 73

    class CommMsgGetCustomStock;            // 74
    class CommMsgAddCustomStock;            // 75
    class CommMsgDelCustomStock;            // 76
	class CommMsgChangeRoleUser;			// 77
    class CommMsgAutoInMoney;			    // 78
    class CommMsgAutoOutMoney;			    // 79
    class CommMsgChildAccAutoAdd;			// 80
    class CommMsgAutoInMoneyQry;            // 81
	class RiskHistoryQry;					// 82

	class MarginSetQry;						// 83
	class MarginLeftQry;					// 84
	class MarginManagerQry;					// 85
	class MarginLiabilitiesQry;				// 86
	class InterestStatisticsQry;			// 87
	class InterestDetailQry;				// 88
	class CommMsgCurrentyMarginEntrustQry;	// 89
	class CommMsgCurrentyMarginTradeQry;	// 90

    // visitor pattern(from the Loki)!
	typedef Loki::CyclicVisitor
		<
		void,
        LOKI_TYPELIST_90(CommMsgBase, CommMsgLogin, CommMsgLogout,CommMsgHeartBeat, CommMsgAgencyQry
		, CommMsgAgencyPreApprovalQry, CommMsgAgencyLinkQry, CommMsgRolesQry, CommMsgAgencyRolesQry, CommMsgCommissQry
		, CommMsgCommissDtlQry, CommMsgProfitCommisslQry, CommMsgProfitCommissDtlQry, CommMsgToplogicalTreeQry, CommMsgChildAccQry
		, CommMsgChildApprovalQry , CommMsgFundAccQry, CommMsgOnlineAccQry, CommMsgStockContractQry, CommMsgStockBlackQry
		, CommMsgForbidBuySellQry, CommMsgPosiRateQry, CommMsgPosiQry, CommMsgCurrentyEntrustQry, CommMsgTodayEntrustQry
		, CommMsgHistoryEntrustQry, CommMsgTradeQry, CommMsgHistoryTradeQry, CommMsgFundQry, CommMsgFundSerialQry
		, CommMsgDeliveryQry, CommMsgFundMonitQry/*, CommMsgTimeTradeQry*/, CommMsgSumPosiQry, CommMsgTimeWarnQry, CommMsgEquipMoneyQry
		, CommMsgAutoOutMoneyQry , CommMsgFeeSetQry, CommMsgAgencyAdd, CommMsgAgencyChange, CommMsgAgencyApproval
		, CommMsgRolesAdd, CommMsgRolesChange, CommMsgBindRelation, CommMsgUserRoleAddRelation, CommMsgChildAccAdd
		, CommMsgChildAccChange, CommMsgChildAccInmoney, CommMsgChildAccApproval, CommMsgFundAccAdd, CommMsgFundAccChange
		, CommMsgFeeSet, CommMsgStockBlackSet, CommMsgForbidBuySellSet, CommMsgPosiRateSet, CommMsgAutoInMoneyApproval
		, CommMsgAutoOutMoneyApproval , CommMsgPswChange, CommMsgOpenClose, CommMsgCancelOrder, CommMsgSelfFunctionQry
		, CommMsgRoleFunctionQry, CommMsgDelRole, CommMsgDelRoleUser, CommMsgManagerAdd, CommMsgManagerChange
		, CommMsgManagerQry, CommMsgGetAllBussnessUser/*, CommMsgGetOnlineChildren*/, CommMsgApplyEquipMoney, CommMsgApprovalApplyEquipMoney, CommMsgAgencyDelete
		, CommMsgChildDelete, CommMsgFunderDelete, CommMsgManagerDelete, CommMsgGetCustomStock, CommMsgAddCustomStock
		, CommMsgDelCustomStock, CommMsgChangeRoleUser, CommMsgAutoInMoney, CommMsgAutoOutMoney, CommMsgChildAccAutoAdd
		, CommMsgAutoInMoneyQry, RiskHistoryQry, MarginSetQry, MarginLeftQry, MarginManagerQry
		, MarginLiabilitiesQry, InterestStatisticsQry, InterestDetailQry, CommMsgCurrentyMarginEntrustQry, CommMsgCurrentyMarginTradeQry)
		>
		CommVisitor;

	class ReplyMsg;
	typedef std::shared_ptr<ReplyMsg>	    ReplyMsgPtr;

	// 消息对象指针
	typedef std::shared_ptr<CommMsgBase>	                CommMsgPtr;
    typedef std::shared_ptr<CommMsgLogin>	                CommMsgLoginPtr;
    typedef std::shared_ptr<CommMsgLogout>	                CommMsgLogoutPtr;
    typedef std::shared_ptr<CommMsgHeartBeat>	            CommMsgHeartBeatPtr;
    typedef std::shared_ptr<CommMsgAgencyQry>	            CommMsgAgencyQryPtr;
    typedef std::shared_ptr<CommMsgAgencyPreApprovalQry>	CommMsgAgencyPreApprovalQryPtr;
    typedef std::shared_ptr<CommMsgAgencyLinkQry>	        CommMsgAgencyLinkQryPtr;
    typedef std::shared_ptr<CommMsgRolesQry>	            CommMsgRolesQryPtr;
    typedef std::shared_ptr<CommMsgAgencyRolesQry>	        CommMsgAgencyRolesQryPtr;
    typedef std::shared_ptr<CommMsgCommissQry>	            CommMsgCommissQryPtr;
    typedef std::shared_ptr<CommMsgCommissDtlQry>	        CommMsgCommissDtlQryPtr;
    typedef std::shared_ptr<CommMsgProfitCommisslQry>	    CommMsgProfitCommisslQryPtr;
    typedef std::shared_ptr<CommMsgProfitCommissDtlQry>	    CommMsgProfitCommissDtlQryPtr;
    typedef std::shared_ptr<CommMsgToplogicalTreeQry>	    CommMsgToplogicalTreeQryPtr;
    typedef std::shared_ptr<CommMsgChildAccQry>	            CommMsgChildAccQryPtr;
    typedef std::shared_ptr<CommMsgChildApprovalQry>	    CommMsgChildApprovalQryPtr;
    typedef std::shared_ptr<CommMsgFundAccQry>	            CommMsgFundAccQryPtr;
    typedef std::shared_ptr<CommMsgOnlineAccQry>	        CommMsgOnlineAccQryPtr;
    typedef std::shared_ptr<CommMsgStockContractQry>	    CommMsgStockContractQryPtr;
    typedef std::shared_ptr<CommMsgStockBlackQry>	        CommMsgStockBlackQryPtr;
    typedef std::shared_ptr<CommMsgForbidBuySellQry>	    CommMsgForbidBuySellQryPtr;
    typedef std::shared_ptr<CommMsgPosiRateQry>	            CommMsgPosiRateQryPtr;
    typedef std::shared_ptr<CommMsgPosiQry>	                CommMsgPosiQryPtr;
    typedef std::shared_ptr<CommMsgCurrentyEntrustQry>	    CommMsgCurrentyEntrustQryPtr;
    typedef std::shared_ptr<CommMsgTodayEntrustQry>	        CommMsgTodayEntrustQryPtr;
    typedef std::shared_ptr<CommMsgHistoryEntrustQry>	    CommMsgHistoryEntrustQryPtr;
    typedef std::shared_ptr<CommMsgTradeQry>	            CommMsgTradeQryPtr;
    typedef std::shared_ptr<CommMsgHistoryTradeQry>	        CommMsgHistoryTradeQryPtr;
    typedef std::shared_ptr<CommMsgFundQry>	                CommMsgFundQryPtr;
    typedef std::shared_ptr<CommMsgFundSerialQry>	        CommMsgFundSerialQryPtr;
    typedef std::shared_ptr<CommMsgDeliveryQry>	            CommMsgDeliveryQryPtr;
    typedef std::shared_ptr<CommMsgFundMonitQry>	        CommMsgFundMonitQryPtr;
//     typedef std::shared_ptr<CommMsgTimeTradeQry>	        CommMsgTimeTradeQryPtr;
    typedef std::shared_ptr<CommMsgSumPosiQry>	            CommMsgSumPosiQryPtr;
    typedef std::shared_ptr<CommMsgTimeWarnQry>	            CommMsgTimeWarnQryPtr;
    typedef std::shared_ptr<CommMsgEquipMoneyQry>	        CommMsgEquipMoneyQryPtr;
    typedef std::shared_ptr<CommMsgAutoOutMoneyQry>	            CommMsgAutoOutMoneyQryPtr;
    typedef std::shared_ptr<CommMsgFeeSetQry>	            CommMsgFeeSetQryPtr;
    typedef std::shared_ptr<CommMsgManagerQry>	            CommMsgManagerQryPtr;
    typedef std::shared_ptr<CommMsgAgencyAdd>	            CommMsgAgencyAddPtr;
    typedef std::shared_ptr<CommMsgAgencyChange>	        CommMsgAgencyChangePtr;
    typedef std::shared_ptr<CommMsgAgencyApproval>	        CommMsgAgencyApprovalPtr;
    typedef std::shared_ptr<CommMsgRolesAdd>	            CommMsgRolesAddPtr;
    typedef std::shared_ptr<CommMsgRolesChange>	            CommMsgRolesChangePtr;
    typedef std::shared_ptr<CommMsgBindRelation>	        CommMsgBindRelationPtr;
    typedef std::shared_ptr<CommMsgUserRoleAddRelation>	    CommMsgUserRoleAddRelationPtr;
    typedef std::shared_ptr<CommMsgChildAccAdd>	            CommMsgChildAccAddPtr;
    typedef std::shared_ptr<CommMsgChildAccChange>	        CommMsgChildAccChangePtr;
    typedef std::shared_ptr<CommMsgChildAccInmoney>	        CommMsgChildAccInmoneyPtr;
    typedef std::shared_ptr<CommMsgChildAccApproval>	    CommMsgChildAccApprovalPtr;
    typedef std::shared_ptr<CommMsgFundAccAdd>	            CommMsgFundAccAddPtr;
    typedef std::shared_ptr<CommMsgFundAccChange>	        CommMsgFundAccChangePtr;
    typedef std::shared_ptr<CommMsgFeeSet>	                CommMsgFeeSetPtr;
    typedef std::shared_ptr<CommMsgStockBlackSet>	        CommMsgStockBlackSetPtr;
    typedef std::shared_ptr<CommMsgForbidBuySellSet>	    CommMsgForbidBuySellSetPtr;
    typedef std::shared_ptr<CommMsgPosiRateSet>	            CommMsgPosiRateSetPtr;
    typedef std::shared_ptr<CommMsgAutoInMoneyApproval>	CommMsgAutoInMoneyApprovalPtr;
    typedef std::shared_ptr<CommMsgAutoOutMoneyApproval>	CommMsgAutoOutMoneyApprovalPtr;
    typedef std::shared_ptr<CommMsgPswChange>	            CommMsgPswChangePtr;
    typedef std::shared_ptr<CommMsgManagerAdd>	            CommMsgManagerAddPtr;
    typedef std::shared_ptr<CommMsgManagerChange>	        CommMsgManagerChangePtr;
    typedef std::shared_ptr<CommMsgOpenClose>	            CommMsgOpenClosePtr;
    typedef std::shared_ptr<CommMsgCancelOrder>	            CommMsgCancelOrderPtr;
	typedef std::shared_ptr<CommMsgSelfFunctionQry>	        CommMsgSelfFunctionQryPtr;
	typedef std::shared_ptr<CommMsgRoleFunctionQry>	        CommMsgRoleFunctionQryPtr;
	typedef std::shared_ptr<CommMsgDelRole>					CommMsgDelRolePtr;
	typedef std::shared_ptr<CommMsgDelRoleUser>				CommMsgDelRoleUserPtr;
	typedef std::shared_ptr<CommMsgGetAllBussnessUser>		CommMsgGetAllBussnessUserPtr;
//     typedef std::shared_ptr<CommMsgGetOnlineChildren>		CommMsgGetOnlineChildrenPtr;
    typedef std::shared_ptr<CommMsgApplyEquipMoney>		        CommMsgApplyEquipMoneyPtr;
    typedef std::shared_ptr<CommMsgApprovalApplyEquipMoney>		CommMsgApprovalApplyEquipMoneyPtr;

    typedef std::shared_ptr<CommMsgAgencyDelete>		    CommMsgAgencyDeletePtr;
    typedef std::shared_ptr<CommMsgChildDelete>		        CommMsgChildDeletePtr;
    typedef std::shared_ptr<CommMsgFunderDelete>		    CommMsgFunderDeletePtr;
    typedef std::shared_ptr<CommMsgManagerDelete>		    CommMsgManagerDeletePtr;

    typedef std::shared_ptr<CommMsgGetCustomStock>		    CommMsgGetCustomStockPtr;
    typedef std::shared_ptr<CommMsgAddCustomStock>		    CommMsgAddCustomStockPtr;
    typedef std::shared_ptr<CommMsgDelCustomStock>		    CommMsgDelCustomStockPtr;
	typedef std::shared_ptr<CommMsgChangeRoleUser>			CommMsgChangeRoleUserPtr;
    typedef std::shared_ptr<CommMsgAutoInMoneyQry>			CommMsgAutoInMoneyQryPtr;
    typedef std::shared_ptr<CommMsgAutoInMoney>			    CommMsgAutoInMoneyPtr;
    typedef std::shared_ptr<CommMsgAutoOutMoney>			CommMsgAutoOutMoneyPtr;
    typedef std::shared_ptr<CommMsgChildAccAutoAdd>			CommMsgChildAccAutoAddPtr;
	typedef std::shared_ptr<RiskHistoryQry>					RiskHistoryQryPtr;

	typedef std::shared_ptr<MarginSetQry>					MarginSetQryPtr;
	typedef std::shared_ptr<MarginLeftQry>					MarginLeftQryPtr; 
	typedef std::shared_ptr<MarginManagerQry>				MarginManagerQryPtr;
	typedef std::shared_ptr<MarginLiabilitiesQry>			MarginLiabilitiesQryPtr;
	typedef std::shared_ptr<InterestStatisticsQry>			InterestStatisticsQryPtr;
	typedef std::shared_ptr<InterestDetailQry>				InterestDetailQryPtr;
	typedef std::shared_ptr<CommMsgCurrentyMarginEntrustQry> CommMsgCurrentyMarginEntrustQryPtr;
	typedef std::shared_ptr<CommMsgCurrentyMarginTradeQry> CommMsgCurrentyMarginTradeQryPtr;
    
    struct Request;
    typedef std::shared_ptr<Request>		RequestPtr;

    typedef Loki::Functor<CommMsgPtr, LOKI_TYPELIST_1(RequestPtr)>		MsgCreator;
	typedef Loki::AssocVector<int, MsgCreator>							TypeToMsgMap;
	typedef TypeToMsgMap::value_type									TTMMValueType;

	typedef std::map<std::string, int>		CmdTypeMap;     // 命令码<-->命令类型
	typedef CmdTypeMap::value_type			CTMapValue;

} // namespace xyc_communication

#endif // __COMM_MESSAGE_H__
