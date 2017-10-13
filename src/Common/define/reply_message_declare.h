/*
* Purpose: 通讯回应消息基类、派生类定义；
*/

#ifndef  __PCA_REPLY_MSG_DECLARE_H__
#define  __PCA_REPLY_MSG_DECLARE_H__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif

#include <memory>

class TCPImpl;

namespace xyc_communication
{
	class ReplyMsg;
    class ReplyLoginMsg;
    class ReplyAgencyQryMsg;
    class ReplyAgencyPreApprovalQryMsg;
    class ReplyAgencyLinkQryMsg;
    class ReplyRolesQryMsg;
    class ReplyAgencyRolesQryMsg;
    class ReplyCommissQryMsg;
    class ReplyCommissDtlQryMsg;
    class ReplyProfitCommisslQryMsg;
    class ReplyProfitCommissDtlQryMsg;
    class ReplyToplogicalTreeQryMsg;
    class ReplyChildAccQryMsg;
    class ReplyChildApprovalQryMsg;
    class ReplyFundAccQryMsg;
    class ReplyOnlineAccQryMsg;
    class ReplyStockContractQryMsg;
    class ReplyStockBlackQryMsg;
    class ReplyForbidBuySellQryMsg;
    class ReplyPosiRateQryMsg;
    class ReplyPosiQryMsg;
    class ReplyCurrentyEntrustQryMsg;
    class ReplyTodayEntrustQryMsg;
    class ReplyHistoryEntrustQryMsg;
    class ReplyTradeQryMsg;
    class ReplyHistoryTradeQryMsg;
    class ReplyFundQryMsg;
    class ReplyFundSerialQryMsg;
    class ReplyDeliveryQryMsg;
    class ReplyFundMonitQryMsg;
    class ReplyTimeTradeQryMsg;
    class ReplySumPosiQryMsg;
    class ReplyTimeWarnQryMsg;
    class ReplyEquipmentMoneyQryMsg;
    class ReplyAutoOutMoneyQryMsg;
    class ReplyFeeSetQryMsg;
    class ReplyManagerQryMsg;
    class ReplyAgencyAddMsg;
    class ReplyAgencyChangeMsg;
    class ReplyAgencyApprovalMsg;
    class ReplyRolesAddMsg;
    class ReplyRolesChangeMsg;
    class ReplyBindRelationMsg;
    class ReplyUserRoleAddRelationMsg;
    class ReplyChildAccAutoAddMsg;
    class ReplyChildAccAddMsg;
    class ReplyChildAccChangeMsg;
    class ReplyChildAccInmoneyMsg;
    class ReplyChildAccApprovalMsg;
    class ReplyFundAccAddMsg;
    class ReplyFundAccChangeMsg;
    class ReplyFeeSetMsg;
    class ReplyStockBlackSetMsg;
    class ReplyForbidBuySellSetMsg;
    class ReplyPosiRateSetMsg;
    class ReplyChildInmoneyApprovalMsg;
    class ReplyChildOutmoneyApprovalMsg;
    class ReplyPswChangeMsg;
    class ReplyManagerAddMsg;
    class ReplyManagerChangeMsg;
    class ReplyOpenCloseMsg;
    class ReplyCancelOrderMsg;
    class PushOrderMsg;
    class PushTradeMsg;
    class PushPositionMsg;
    class PushMoneyMsg;
    class PushRiskControlMsg;
	class ReplySelfFunctionMsg;
	class ReplyRoleFunctionMsg;
	class ReplyDelRoleMsg;
	class ReplyDelRoleUserMsg;
	class ReplyGetAllBussnessMsg;
    class ReplyApplyEquipMoneyMsg;
    class ReplyApprovalApplyEquipMoneyMsg;

    class ReplyAgencyDeleteMsg;
    class ReplyChildDeleteMsg;
    class ReplyFunderDeleteMsg;
    class ReplyManagerDeleteMsg;

    class ReplyGetCustomStockMsg;
    class ReplyAddCustomStockMsg;
    class ReplyDelCustomStockMsg;
	class ReplyChangeRoleUserMsg;

    class ReplyAutoInMoneyQryMsg;
    class ReplyAutoInMoneyMsg;
    class ReplyAutoInMoneyApprovalMsg;
    class ReplyAutoOutMoneyMsg;
    class ReplyAutoOutMoneyApprovalMsg;

	class ReplyRiskHistoryMsg;
	class ReplySetMarginMsg;
	class ReplyMarginLeftQtyMsg;
	class ReplyMarginManagerQtyMsg;
	class ReplyMarginLiabilitiesQtyMsg;

	class ReplyInterestStatisticsMsg;
	class ReplyInterestDetailMsg;
	class ReplyCurrentMarginEntrustMsg;
	class ReplyCurrentMarginTradeQryMsg;

    typedef std::shared_ptr<ReplyMsg>			            ReplyMsgPtr;
    typedef std::shared_ptr<ReplyLoginMsg>	                ReplyLoginMsgPtr;
    typedef std::shared_ptr<ReplyAgencyQryMsg>	            ReplyAgencyQryMsgPtr;
    typedef std::shared_ptr<ReplyAgencyPreApprovalQryMsg>   ReplyAgencyPreApprovalQryMsgPtr;
    typedef std::shared_ptr<ReplyAgencyLinkQryMsg>	        ReplyAgencyLinkQryMsgPtr;
    typedef std::shared_ptr<ReplyRolesQryMsg>	            ReplyRolesQryMsgPtr;
    typedef std::shared_ptr<ReplyAgencyRolesQryMsg>	        ReplyAgencyRolesQryMsgPtr;
    typedef std::shared_ptr<ReplyCommissQryMsg>	            ReplyCommissQryMsgPtr;
    typedef std::shared_ptr<ReplyCommissDtlQryMsg>	        ReplyCommissDtlQryMsgPtr;
    typedef std::shared_ptr<ReplyProfitCommisslQryMsg>	    ReplyProfitCommisslQryMsgPtr;
    typedef std::shared_ptr<ReplyProfitCommissDtlQryMsg>    ReplyProfitCommissDtlQryMsgPtr;
    typedef std::shared_ptr<ReplyToplogicalTreeQryMsg>	    ReplyToplogicalTreeQryMsgPtr;
    typedef std::shared_ptr<ReplyChildAccQryMsg>	        ReplyChildAccQryMsgPtr;
    typedef std::shared_ptr<ReplyChildApprovalQryMsg>	    ReplyChildApprovalQryMsgPtr;
    typedef std::shared_ptr<ReplyFundAccQryMsg>	            ReplyFundAccQryMsgPtr;
    typedef std::shared_ptr<ReplyOnlineAccQryMsg>	        ReplyOnlineAccQryMsgPtr;
    typedef std::shared_ptr<ReplyStockContractQryMsg>	    ReplyStockContractQryMsgPtr;
    typedef std::shared_ptr<ReplyStockBlackQryMsg>	        ReplyStockBlackQryMsgPtr;
    typedef std::shared_ptr<ReplyForbidBuySellQryMsg>	    ReplyForbidBuySellQryMsgPtr;
    typedef std::shared_ptr<ReplyPosiRateQryMsg>	        ReplyPosiRateQryMsgPtr;
    typedef std::shared_ptr<ReplyPosiQryMsg>	            ReplyPosiQryMsgPtr;
    typedef std::shared_ptr<ReplyCurrentyEntrustQryMsg>	    ReplyCurrentyEntrustQryMsgPtr;
    typedef std::shared_ptr<ReplyTodayEntrustQryMsg>	    ReplyTodayEntrustQryMsgPtr;
    typedef std::shared_ptr<ReplyHistoryEntrustQryMsg>	    ReplyHistoryEntrustQryMsgPtr;
    typedef std::shared_ptr<ReplyTradeQryMsg>	            ReplyTradeQryMsgPtr;
    typedef std::shared_ptr<ReplyHistoryTradeQryMsg>	    ReplyHistoryTradeQryMsgPtr;
    typedef std::shared_ptr<ReplyFundQryMsg>	            ReplyFundQryMsgPtr;
    typedef std::shared_ptr<ReplyFundSerialQryMsg>	        ReplyFundSerialQryMsgPtr;
    typedef std::shared_ptr<ReplyDeliveryQryMsg>	        ReplyDeliveryQryMsgPtr;
    typedef std::shared_ptr<ReplyFundMonitQryMsg>	        ReplyFundMonitQryMsgPtr;
    typedef std::shared_ptr<ReplyTimeTradeQryMsg>	        ReplyTimeTradeQryMsgPtr;
    typedef std::shared_ptr<ReplySumPosiQryMsg>	            ReplySumPosiQryMsgPtr;
    typedef std::shared_ptr<ReplyTimeWarnQryMsg>	        ReplyTimeWarnQryMsgPtr;
    typedef std::shared_ptr<ReplyEquipmentMoneyQryMsg>	    ReplyEquipmentMoneyQryMsgPtr;
    typedef std::shared_ptr<ReplyAutoOutMoneyQryMsg>	    ReplyAutoOutMoneyQryMsgPtr;
    typedef std::shared_ptr<ReplyFeeSetQryMsg>	            ReplyFeeSetQryMsgPtr;
    typedef std::shared_ptr<ReplyManagerQryMsg>	            ReplyManagerQryMsgPtr;
    typedef std::shared_ptr<ReplyAgencyAddMsg>	            ReplyAgencyAddMsgPtr;
    typedef std::shared_ptr<ReplyAgencyChangeMsg>	        ReplyAgencyChangeMsgPtr;
    typedef std::shared_ptr<ReplyAgencyApprovalMsg>	        ReplyAgencyApprovalMsgPtr;
    typedef std::shared_ptr<ReplyRolesAddMsg>	            ReplyRolesAddMsgPtr;
    typedef std::shared_ptr<ReplyRolesChangeMsg>	        ReplyRolesChangeMsgPtr;
    typedef std::shared_ptr<ReplyBindRelationMsg>	        ReplyBindRelationMsgPtr;
    typedef std::shared_ptr<ReplyUserRoleAddRelationMsg>    ReplyUserRoleAddRelationMsgPtr;
    typedef std::shared_ptr<ReplyChildAccAutoAddMsg>	    ReplyChildAccAutoAddMsgPtr;
    typedef std::shared_ptr<ReplyChildAccAddMsg>	        ReplyChildAccAddMsgPtr;
    typedef std::shared_ptr<ReplyChildAccChangeMsg>	        ReplyChildAccChangeMsgPtr;
    typedef std::shared_ptr<ReplyChildAccInmoneyMsg>	    ReplyChildAccInmoneyMsgPtr;
    typedef std::shared_ptr<ReplyChildAccApprovalMsg>	    ReplyChildAccApprovalMsgPtr;
    typedef std::shared_ptr<ReplyFundAccAddMsg>	            ReplyFundAccAddMsgPtr;
    typedef std::shared_ptr<ReplyFundAccChangeMsg>	        ReplyFundAccChangeMsgPtr;
    typedef std::shared_ptr<ReplyFeeSetMsg>	                ReplyFeeSetMsgPtr;
    typedef std::shared_ptr<ReplyStockBlackSetMsg>	        ReplyStockBlackSetMsgPtr;
    typedef std::shared_ptr<ReplyForbidBuySellSetMsg>	    ReplyForbidBuySellSetMsgPtr;
    typedef std::shared_ptr<ReplyPosiRateSetMsg>	        ReplyPosiRateSetMsgPtr;
    typedef std::shared_ptr<ReplyChildInmoneyApprovalMsg>	ReplyChildInmoneyApprovalMsgPtr;
    typedef std::shared_ptr<ReplyChildOutmoneyApprovalMsg>	ReplyChildOutmoneyApprovalMsgPtr;
    typedef std::shared_ptr<ReplyPswChangeMsg>	            ReplyPswChangeMsgPtr;
    typedef std::shared_ptr<ReplyManagerAddMsg>	            ReplyManagerAddMsgPtr;
    typedef std::shared_ptr<ReplyManagerChangeMsg>	        ReplyManagerChangeMsgPtr;
    typedef std::shared_ptr<ReplyOpenCloseMsg>	            ReplyOpenCloseMsgPtr;
    typedef std::shared_ptr<ReplyCancelOrderMsg>	        ReplyCancelOrderMsgPtr;

    typedef std::shared_ptr<PushOrderMsg>	                PushOrderMsgPtr;
    typedef std::shared_ptr<PushTradeMsg>	                PushTradeMsgPtr;
    typedef std::shared_ptr<PushPositionMsg>	            PushPositionMsgPtr;
    typedef std::shared_ptr<PushMoneyMsg>	                PushMoneyMsgPtr;
    typedef std::shared_ptr<PushRiskControlMsg>	            PushRiskControlMsgPtr;
	typedef std::shared_ptr<ReplySelfFunctionMsg>	        ReplySelfFunctionMsgPtr;
	typedef std::shared_ptr<ReplyRoleFunctionMsg>	        ReplyRoleFunctionMsgPtr;
	typedef std::shared_ptr<ReplyDelRoleMsg>				ReplyDelRoleMsgPtr;
	typedef std::shared_ptr<ReplyDelRoleUserMsg>			ReplyDelRoleUserMsgPtr;
	typedef std::shared_ptr<ReplyGetAllBussnessMsg>			ReplyGetAllBussnessMsgPtr;
    typedef std::shared_ptr<ReplyApplyEquipMoneyMsg>			    ReplyApplyEquipMoneyMsgPtr;
    typedef std::shared_ptr<ReplyApprovalApplyEquipMoneyMsg>		ReplyApprovalApplyEquipMoneyMsgPtr;

    typedef std::shared_ptr<ReplyAgencyDeleteMsg>		    ReplyAgencyDeleteMsgPtr;
    typedef std::shared_ptr<ReplyChildDeleteMsg>		    ReplyChildDeleteMsgPtr;
    typedef std::shared_ptr<ReplyFunderDeleteMsg>		    ReplyFunderDeleteMsgPtr;
    typedef std::shared_ptr<ReplyManagerDeleteMsg>		    ReplyManagerDeleteMsgPtr;

    typedef std::shared_ptr<ReplyGetCustomStockMsg>		    ReplyGetCustomStockMsgPtr;
    typedef std::shared_ptr<ReplyAddCustomStockMsg>		    ReplyAddCustomStockMsgPtr;
    typedef std::shared_ptr<ReplyDelCustomStockMsg>		    ReplyDelCustomStockMsgPtr;

	typedef std::shared_ptr<ReplyChangeRoleUserMsg>			ReplyChangeRoleUserMsgPtr;

    typedef std::shared_ptr<ReplyAutoInMoneyQryMsg>			ReplyAutoInMoneyQryMsgPtr;
    typedef std::shared_ptr<ReplyAutoInMoneyMsg>			ReplyAutoInMoneyMsgPtr;
    typedef std::shared_ptr<ReplyAutoInMoneyApprovalMsg>	ReplyAutoInMoneyApprovalMsgPtr;
    typedef std::shared_ptr<ReplyAutoOutMoneyMsg>			ReplyAutoOutMoneyMsgPtr;
    typedef std::shared_ptr<ReplyAutoOutMoneyApprovalMsg>	ReplyAutoOutMoneyApprovalMsgPtr;
	typedef std::shared_ptr<ReplyRiskHistoryMsg>			ReplyRiskHistoryMsgPtr;

	typedef std::shared_ptr<ReplySetMarginMsg>				ReplySetMarginMsgPtr;
	typedef std::shared_ptr<ReplyMarginLeftQtyMsg>			ReplyMarginLeftQtyMsgPtr; 
	typedef std::shared_ptr<ReplyMarginManagerQtyMsg>		ReplyMarginManagerQtyMsgPtr;
	typedef std::shared_ptr<ReplyMarginLiabilitiesQtyMsg>	ReplyMarginLiabilitiesQtyMsgPtr;
	typedef std::shared_ptr<ReplyInterestStatisticsMsg>		ReplyInterestStatisticsMsgPtr;

	typedef std::shared_ptr<ReplyInterestDetailMsg>			ReplyInterestDetailMsgPtr;
	typedef std::shared_ptr<ReplyCurrentMarginEntrustMsg>	ReplyCurrentMarginEntrustMsgPtr;
	typedef std::shared_ptr<ReplyCurrentMarginTradeQryMsg>	ReplyCurrentMarginTradeQryMsgPtr;
	
} // namespace xyc_communication

#endif // __PCA_REPLY_MSG_H__
