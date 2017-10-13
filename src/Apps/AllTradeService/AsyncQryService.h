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
        // �����˻�
        void qryUsingAgencys(const ReplyAgencyQryMsgPtr& msg_ptr);
        void qryCheckingAgencys(const ReplyAgencyPreApprovalQryMsgPtr& msg_ptr);

        void addAgencyAcc(const ReplyAgencyAddMsgPtr& msg_ptr);
        void changeAgencyAcc(const ReplyAgencyChangeMsgPtr& msg_ptr);
        void checkAgencyAcc(const ReplyAgencyApprovalMsgPtr& msg_ptr);

        // �����˻�
        void autoCreateTradeUser(const ReplyChildAccAutoAddMsgPtr& msg_ptr);
        void addTradeAcc(const ReplyChildAccAddMsgPtr& msg_ptr);
        void changeTradeAcc(const ReplyChildAccChangeMsgPtr& msg_ptr);
        void checkTradeAcc(const ReplyChildAccApprovalMsgPtr& msg_ptr);
        void qryUsingTradeAcc(const ReplyChildAccQryMsgPtr& msg_ptr);
        void qryCheckingTradeAcc(const ReplyChildApprovalQryMsgPtr& msg_ptr);

        // �����˻�
        void addManagerAcc(const ReplyManagerAddMsgPtr& msg_ptr);
        void changeManagerAcc(const ReplyManagerChangeMsgPtr& msg_ptr);
        void qryManagerAcc(const ReplyManagerQryMsgPtr& msg_ptr);
        void qryUsingManagerAcc(const ReplyManagerQryMsgPtr& msg_ptr);
        
        // �ʽ��ʻ�
        void qryFunderAcc(const ReplyFundAccQryMsgPtr& msg_ptr);
        void qryUsingFunderAcc(const ReplyFundAccQryMsgPtr& msg_ptr);
        void addFunderAcc(const ReplyFundAccAddMsgPtr& msg_ptr);
        void changeFunderAcc(const ReplyFundAccChangeMsgPtr& msg_ptr);

        // �޸�����
        void changePassword(const ReplyPswChangeMsgPtr& msg_ptr);

        // �����
        void outInMoney(const ReplyChildAccInmoneyMsgPtr& msg_ptr);

        // �������ʽ��
        void applyEquipMoney(const ReplyApplyEquipMoneyMsgPtr& msg_ptr);
        // �����Զ����
        void applyAutoInMoney(const ReplyAutoInMoneyMsgPtr& msg_ptr);
        // �����Զ�����
        void applyAutoOutMoney(const ReplyAutoOutMoneyMsgPtr& msg_ptr);

        // �����������
        void approvalApplyEquipMoney(const ReplyApprovalApplyEquipMoneyMsgPtr& msg_ptr);
        // ����Զ��������
        void approvalApplyAutoInMoney(const ReplyAutoInMoneyApprovalMsgPtr& msg_ptr);
        // ����Զ���������
        void approvalApplyAutoOutMoney(const ReplyAutoOutMoneyApprovalMsgPtr& msg_ptr);

        // ��ѯ��������
        void qryEquipMoneyInfos(const ReplyEquipmentMoneyQryMsgPtr& msg_ptr);
        // ��ѯ�Զ��������
        void qryAutoInMoneyInfos(const ReplyAutoInMoneyQryMsgPtr& msg_ptr);
        // ��ѯ�Զ���������
        void qryAutoOutMoneyInfos(const ReplyAutoOutMoneyQryMsgPtr& msg_ptr);

		// Ȩ�����
		void addRole(const ReplyRolesAddMsgPtr& msg_ptr);						// ���ӽ�ɫ
		void qryRoleInfo(const ReplyRolesQryMsgPtr& msg_ptr);					// ��ѯ��ɫ
		void bindRoleFunctionRelation(const ReplyBindRelationMsgPtr& msg_ptr);	// �󶨽�ɫ���ܹ�ϵ
		void qrySelfFunctionsInfo(const ReplySelfFunctionMsgPtr& msg_ptr);		// ��½�߲�ѯ������
		void qryRoleFunctionsInfo(const ReplyRoleFunctionMsgPtr& msg_ptr);		// ��ɫ���ܲ�ѯ
		void changeRole(const ReplyRolesChangeMsgPtr& msg_ptr);					// �޸Ľ�ɫ
		void deleteRole(const ReplyDelRoleMsgPtr& msg_ptr);						// ɾ����ɫ

		void getRoleUserInfo(const ReplyAgencyRolesQryMsgPtr& msg_ptr);			// ��ѯ��ɫ/�û���Ϣ
		void addRoleUserInfo(const ReplyUserRoleAddRelationMsgPtr& msg_ptr);	// ���ӽ�ɫ/�û���Ϣ
        void deleteRoleUserInfo(const ReplyDelRoleUserMsgPtr& msg_ptr);	// ɾ����ɫ/�û���Ϣ
		void getAllBussnessInfo(const ReplyGetAllBussnessMsgPtr& msg_ptr);	// ɾ����ɫ/�û���Ϣ

        // ��ѯ�������˻�
        void getOnlineChildren(bool& bFind, std::vector<AllTrade::NPMgrCenter::SAccountPtr>& rslt, const ReplyOnlineAccQryMsgPtr& msg_ptr);

        // ��������
        void qryFeeSet(const ReplyFeeSetQryMsgPtr& msg_ptr);
        void changeFeeSet(const ReplyFeeSetMsgPtr& msg_ptr);

		// ί��
        void handlePlaceOrder(const ReplyOpenCloseMsgPtr& msg_ptr, const AllTrade::NPMgrCenter::SOnlineAccountPtr& user_online);
        void handleCancelOrder(const ReplyCancelOrderMsgPtr& msg_ptr);

        // ��ѯ��Ʊ��Լ
        void qryStockContract(const ReplyStockContractQryMsgPtr& msg_ptr);

        // ��ѯ�ʽ���Ϣ
        void qryAccountFund(const ReplyFundQryMsgPtr& msg_ptr);
        // ��ѯ�ʽ���ˮ
        void qryHistoryFundSerial(const ReplyFundSerialQryMsgPtr& msg_ptr);
        // ��ѯ�ֲ�
        void qryPosition(const ReplyPosiQryMsgPtr& msg_ptr);
        // ��ѯ��ǰί��
        void qryCurrentyEntrust(const ReplyCurrentyEntrustQryMsgPtr& msg_ptr);
        // ��ѯ����ί��
        void qryTodayEntrust(const ReplyTodayEntrustQryMsgPtr& msg_ptr);
        // ��ѯ��ʷί��
        void qryHistoryEntrust(const ReplyHistoryEntrustQryMsgPtr& msg_ptr);
        // ��ѯ�ɽ���Ϣ
        void qryTrade(const ReplyTradeQryMsgPtr& msg_ptr);
        // ��ѯ��ʷί��
        void qryHistoryTrade(const ReplyHistoryTradeQryMsgPtr& msg_ptr);

        // ��ѯ/���ù�Ʊ��������Ϣ
        void qryStockBlackWhiteStatus(const ReplyStockBlackQryMsgPtr& msg_ptr);
        void setStockBlackWhiteStatus(const ReplyStockBlackSetMsgPtr& msg_ptr);

        // ��ѯ/���ý�ֹ������Ϣ
        void qryForbidTradeStatus(const ReplyForbidBuySellQryMsgPtr& msg_ptr);
        void setForbidTradeStatus(const ReplyForbidBuySellSetMsgPtr& msg_ptr);

        // ��ѯ/���óֱֲ�����Ϣ
        void qryPosiRateStatus(const ReplyPosiRateQryMsgPtr& msg_ptr);
        void setPosiRateStatus(const ReplyPosiRateSetMsgPtr& msg_ptr);

        // ɾ������
        void deleteAgency(const ReplyAgencyDeleteMsgPtr& msg_ptr);
        // ɾ�����˻�
        void deleteChild(const ReplyChildDeleteMsgPtr& msg_ptr);
        // ɾ���ʽ��ʻ�
        void deleteFunder(const ReplyFunderDeleteMsgPtr& msg_ptr);
        // ɾ������Ա
        void deleteManager(const ReplyManagerDeleteMsgPtr& msg_ptr);

        void qryCustomStock(const ReplyGetCustomStockMsgPtr& msg_ptr);
        void addCustomStock(const ReplyAddCustomStockMsgPtr& msg_ptr);
        void deleteCustomStock(const ReplyDelCustomStockMsgPtr& msg_ptr);

		void changeRoleUserInfo(const ReplyChangeRoleUserMsgPtr& msg_ptr);	// �޸Ľ�ɫ/�û���Ϣ

        // ��ѯӶ����Ϣ
        void qryAgencyCommissInfo(const ReplyCommissQryMsgPtr& msg_ptr);
        // ��ѯӶ����ϸ��Ϣ
        void qryAgencyCommissDtlInfo(const ReplyCommissDtlQryMsgPtr& msg_ptr);
        // ��ѯ�ֳ���Ϣ
        void qryAgencyProfitInfo(const ReplyProfitCommisslQryMsgPtr& msg_ptr);
        // ��ѯ�ֳ���ϸ��Ϣ
        void qryAgencyProfitDtlInfo(const ReplyProfitCommissDtlQryMsgPtr& msg_ptr);

		// �����ʷ��ѯ����
		void qryRiskHistoryInfos(const ReplyRiskHistoryMsgPtr& msg_ptr);
		// ��ѯ���ʵʱ���
		void qryRiskTimerInfos(const ReplyTimeWarnQryMsgPtr& msg_ptr);

		// ������ȯ��Ϣ����
		void setMarginInfo(const ReplySetMarginMsgPtr& msg_ptr);

		// ��ѯ��ȯʣ������
		void getMarginLeftInfo(const ReplyMarginLeftQtyMsgPtr& msg_ptr);
		// ��ѯ��ȯ������Ϣ����
		void getMarginManagerInfo(const ReplyMarginManagerQtyMsgPtr& msg_ptr);
		// ��ѯ��ȯ��ծ��Ϣ����
		void getMarginLiabilitiesInfo(const ReplyMarginLiabilitiesQtyMsgPtr& msg_ptr);
		// ��ѯ��Ϣͳ�Ʋ�ѯ����
		void getInterestStatisticsInfo(const ReplyInterestStatisticsMsgPtr& msg_ptr);
		// ��ѯ��Ϣ��ϸ��ѯ����
		void getInterestDetailInfo(const ReplyInterestDetailMsgPtr& msg_ptr);
		// ��ǰ��ȯί�в�ѯ����
		void getCurrentMarginEntrustInfo(const ReplyCurrentMarginEntrustMsgPtr& msg_ptr);
		// ��ѯ��ȯ�ɽ���Ϣ
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