#pragma once
#include "utility/instance_shared_from_this.h"
#include "Network/reply_message.h"
#include "utility/command.h"
#include "utility/dispatcher_core.h"

namespace xyc_communication{

    class AsyncQryService
        : public CommonTools::instance_shared_from_this<AsyncQryService>
        , public CommonTools::dispatcher_callback<CommonTools::CommandPtr>
    {
    public:
        AsyncQryService();
        ~AsyncQryService();

    public:
        // 机构账户
        void qryUsingAgencys(const ReplyAgencyQryMsgPtr& msg_ptr);
        void qryCheckingAgencys(const ReplyAgencyPreApprovalQryMsgPtr& msg_ptr);

        void addAgencyAcc(const ReplyAgencyAddMsgPtr& msg_ptr);
        void changeAgencyAcc(const ReplyAgencyChangeMsgPtr& msg_ptr);
        void checkAgencyAcc(const ReplyAgencyApprovalMsgPtr& msg_ptr);

        // 交易账户
        void autoCreateTradeUser(const ReplyChildAccAutoAddMsgPtr& msg_ptr);
        void addTradeAcc(const ReplyChildAccAddMsgPtr& msg_ptr);
        void changeTradeAcc(const ReplyChildAccChangeMsgPtr& msg_ptr);
        void checkTradeAcc(const ReplyChildAccApprovalMsgPtr& msg_ptr);
        void qryUsingTradeAcc(const ReplyChildAccQryMsgPtr& msg_ptr);
        void qryCheckingTradeAcc(const ReplyChildApprovalQryMsgPtr& msg_ptr);

        // 管理账户
        void addManagerAcc(const ReplyManagerAddMsgPtr& msg_ptr);
        void changeManagerAcc(const ReplyManagerChangeMsgPtr& msg_ptr);
        void qryManagerAcc(const ReplyManagerQryMsgPtr& msg_ptr);
        void qryUsingManagerAcc(const ReplyManagerQryMsgPtr& msg_ptr);
        
        // 资金帐户
        void qryFunderAcc(const ReplyFundAccQryMsgPtr& msg_ptr);
        void qryUsingFunderAcc(const ReplyFundAccQryMsgPtr& msg_ptr);
        void addFunderAcc(const ReplyFundAccAddMsgPtr& msg_ptr);
        void changeFunderAcc(const ReplyFundAccChangeMsgPtr& msg_ptr);

        // 修改密码
        void changePassword(const ReplyPswChangeMsgPtr& msg_ptr);

        // 出入金
        void outInMoney(const ReplyChildAccInmoneyMsgPtr& msg_ptr);

        // 申请融资金额
        void applyEquipMoney(const ReplyApplyEquipMoneyMsgPtr& msg_ptr);
        // 申请自动入金
        void applyAutoInMoney(const ReplyAutoInMoneyMsgPtr& msg_ptr);
        // 申请自动出金
        void applyAutoOutMoney(const ReplyAutoOutMoneyMsgPtr& msg_ptr);

        // 审核融资申请
        void approvalApplyEquipMoney(const ReplyApprovalApplyEquipMoneyMsgPtr& msg_ptr);
        // 审核自动入金申请
        void approvalApplyAutoInMoney(const ReplyAutoInMoneyApprovalMsgPtr& msg_ptr);
        // 审核自动出金申请
        void approvalApplyAutoOutMoney(const ReplyAutoOutMoneyApprovalMsgPtr& msg_ptr);

        // 查询融资申请
        void qryEquipMoneyInfos(const ReplyEquipmentMoneyQryMsgPtr& msg_ptr);
        // 查询自动入金申请
        void qryAutoInMoneyInfos(const ReplyAutoInMoneyQryMsgPtr& msg_ptr);
        // 查询自动出金申请
        void qryAutoOutMoneyInfos(const ReplyAutoOutMoneyQryMsgPtr& msg_ptr);

		// 权限相关
		void addRole(const ReplyRolesAddMsgPtr& msg_ptr);						// 增加角色
		void qryRoleInfo(const ReplyRolesQryMsgPtr& msg_ptr);					// 查询角色
		void bindRoleFunctionRelation(const ReplyBindRelationMsgPtr& msg_ptr);	// 绑定角色功能关系
		void qrySelfFunctionsInfo(const ReplySelfFunctionMsgPtr& msg_ptr);		// 登陆者查询自身功能
		void qryRoleFunctionsInfo(const ReplyRoleFunctionMsgPtr& msg_ptr);		// 角色功能查询
		void changeRole(const ReplyRolesChangeMsgPtr& msg_ptr);					// 修改角色
		void deleteRole(const ReplyDelRoleMsgPtr& msg_ptr);						// 删除角色

		void getRoleUserInfo(const ReplyAgencyRolesQryMsgPtr& msg_ptr);			// 查询角色/用户信息
		void addRoleUserInfo(const ReplyUserRoleAddRelationMsgPtr& msg_ptr);	// 增加角色/用户信息
        void deleteRoleUserInfo(const ReplyDelRoleUserMsgPtr& msg_ptr);	// 删除角色/用户信息
		void getAllBussnessInfo(const ReplyGetAllBussnessMsgPtr& msg_ptr);	// 删除角色/用户信息

        // 查询在线子账户
        void getOnlineChildren(bool& bFind, std::vector<AllTrade::NPMgrCenter::SAccountPtr>& rslt, const ReplyOnlineAccQryMsgPtr& msg_ptr);

        // 费用设置
        void qryFeeSet(const ReplyFeeSetQryMsgPtr& msg_ptr);
        void changeFeeSet(const ReplyFeeSetMsgPtr& msg_ptr);

		// 委托
        void handlePlaceOrder(const ReplyOpenCloseMsgPtr& msg_ptr, const AllTrade::NPMgrCenter::SOnlineAccountPtr& user_online);
        void handleCancelOrder(const ReplyCancelOrderMsgPtr& msg_ptr);

        // 查询股票合约
        void qryStockContract(const ReplyStockContractQryMsgPtr& msg_ptr);

        // 查询资金信息
        void qryAccountFund(const ReplyFundQryMsgPtr& msg_ptr);
        // 查询资金流水
        void qryHistoryFundSerial(const ReplyFundSerialQryMsgPtr& msg_ptr);
        // 查询持仓
        void qryPosition(const ReplyPosiQryMsgPtr& msg_ptr);
        // 查询当前委托
        void qryCurrentyEntrust(const ReplyCurrentyEntrustQryMsgPtr& msg_ptr);
        // 查询当日委托
        void qryTodayEntrust(const ReplyTodayEntrustQryMsgPtr& msg_ptr);
        // 查询历史委托
        void qryHistoryEntrust(const ReplyHistoryEntrustQryMsgPtr& msg_ptr);
        // 查询成交信息
        void qryTrade(const ReplyTradeQryMsgPtr& msg_ptr);
        // 查询历史委托
        void qryHistoryTrade(const ReplyHistoryTradeQryMsgPtr& msg_ptr);

        // 查询/设置股票黑名单信息
        void qryStockBlackWhiteStatus(const ReplyStockBlackQryMsgPtr& msg_ptr);
        void setStockBlackWhiteStatus(const ReplyStockBlackSetMsgPtr& msg_ptr);

        // 查询/设置禁止交易信息
        void qryForbidTradeStatus(const ReplyForbidBuySellQryMsgPtr& msg_ptr);
        void setForbidTradeStatus(const ReplyForbidBuySellSetMsgPtr& msg_ptr);

        // 查询/设置持仓比例信息
        void qryPosiRateStatus(const ReplyPosiRateQryMsgPtr& msg_ptr);
        void setPosiRateStatus(const ReplyPosiRateSetMsgPtr& msg_ptr);

        // 删除机构
        void deleteAgency(const ReplyAgencyDeleteMsgPtr& msg_ptr);
        // 删除子账户
        void deleteChild(const ReplyChildDeleteMsgPtr& msg_ptr);
        // 删除资金帐户
        void deleteFunder(const ReplyFunderDeleteMsgPtr& msg_ptr);
        // 删除管理员
        void deleteManager(const ReplyManagerDeleteMsgPtr& msg_ptr);

        void qryCustomStock(const ReplyGetCustomStockMsgPtr& msg_ptr);
        void addCustomStock(const ReplyAddCustomStockMsgPtr& msg_ptr);
        void deleteCustomStock(const ReplyDelCustomStockMsgPtr& msg_ptr);

		void changeRoleUserInfo(const ReplyChangeRoleUserMsgPtr& msg_ptr);	// 修改角色/用户信息

        // 查询佣金信息
        void qryAgencyCommissInfo(const ReplyCommissQryMsgPtr& msg_ptr);
        // 查询佣金明细信息
        void qryAgencyCommissDtlInfo(const ReplyCommissDtlQryMsgPtr& msg_ptr);
        // 查询分成信息
        void qryAgencyProfitInfo(const ReplyProfitCommisslQryMsgPtr& msg_ptr);
        // 查询分成明细信息
        void qryAgencyProfitDtlInfo(const ReplyProfitCommissDtlQryMsgPtr& msg_ptr);

		// 风控历史查询请求
		void qryRiskHistoryInfos(const ReplyRiskHistoryMsgPtr& msg_ptr);
		// 查询风控实时监控
		void qryRiskTimerInfos(const ReplyTimeWarnQryMsgPtr& msg_ptr);

		// 设置融券信息请求
		void setMarginInfo(const ReplySetMarginMsgPtr& msg_ptr);

		// 查询融券剩余数量
		void getMarginLeftInfo(const ReplyMarginLeftQtyMsgPtr& msg_ptr);
		// 查询融券管理信息请求
		void getMarginManagerInfo(const ReplyMarginManagerQtyMsgPtr& msg_ptr);
		// 查询融券负债信息请求
		void getMarginLiabilitiesInfo(const ReplyMarginLiabilitiesQtyMsgPtr& msg_ptr);
		// 查询利息统计查询请求
		void getInterestStatisticsInfo(const ReplyInterestStatisticsMsgPtr& msg_ptr);
		// 查询利息明细查询请求
		void getInterestDetailInfo(const ReplyInterestDetailMsgPtr& msg_ptr);
		// 当前融券委托查询请求
		void getCurrentMarginEntrustInfo(const ReplyCurrentMarginEntrustMsgPtr& msg_ptr);
		// 查询融券成交信息
		void qryCurrentMarginTrade(const ReplyCurrentMarginTradeQryMsgPtr& msg_ptr);
    protected:
        // dispatcher_callback functions
        long on_threadstart(void* param);
        long on_threadstop(void* param);
        long on_message(CommonTools::CommandPtr msg, bool cleanup);
        long on_event(CommonTools::handler evt);
        bool postDispMsg(CommonTools::CommandPtr pCmd) {
            if (!pCmd)
                return false;
            return m_dispatcher.post_message(pCmd);
        }
    private:
        CommonTools::dispatcher<CommonTools::CommandPtr>	m_dispatcher;

    };

}