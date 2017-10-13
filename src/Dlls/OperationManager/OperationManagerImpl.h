#ifndef COPERATION_MANAGER_IMPL_
#define COPERATION_MANAGER_IMPL_

#include <vector>
#include <set>
#include <map>
#include "define/struct_declare.h"
#include "define/params_declare.h"
using namespace AllTrade;

namespace OperationManager
{
    class DBOpManagerCenter;
    class CAuthorityControl;
    class DBOpTradeCenter;

	class COperationManagerImpl
	{
	public:
		COperationManagerImpl();
		~COperationManagerImpl();
	
    public:
        bool initialize();

	public:
#pragma region �û��뽻����������ز���
        // ��ȡ���˻�
        bool getRootAccount(AllTrade::NPMgrCenter::RootAccountPtr& root_ptr);
        // ��ȡָ���˻������е����˻�(������Խ���˻�)
        bool getAllDirectChildren(std::vector<AllTrade::NPMgrCenter::SAccountPtr>& children, const AllTrade::NPMgrCenter::SAccountPtr& account_ptr);
        // ��ȡָ���˻��µĹ�����˻�(�������˻�/�����˻�/�����˻�/����˻�)
        bool getMonitChildren(std::vector<AllTrade::NPMgrCenter::SAccountPtr>& children, const AllTrade::NPMgrCenter::SAccountPtr& account_ptr);
        // ��ȡָ���˻��µĽ����˻�
        bool getTradeChildren(std::vector<AllTrade::NPMgrCenter::SAccountPtr>& children, const AllTrade::NPMgrCenter::SAccountPtr& account_ptr);
        // ��ȡָ���˻��µ�ʵ���˻�
        bool getFunderChildren(std::vector<AllTrade::NPMgrCenter::SAccountPtr>& children, const AllTrade::NPMgrCenter::SAccountPtr& account_ptr);
        // ��ȡ�û��ʽ���Ϣ
        bool getUserMoneyInfo(const AllTrade::UserIDType user_id, AllTrade::NPMgrCenter::SMoneyInfoPtr& money_info);
        // ��ȡ�û������Ϣ
        bool getUserRiskInfo(const AllTrade::UserIDType user_id, AllTrade::NPMgrCenter::SRiskInfoPtr& risk_info);

        // ��ȡ���н�������Ϣ
        bool getAllExchange(std::vector<AllTrade::NPMgrCenter::SExchangePtr>& exchanges);
        // ��ȡ���н�������Ϣ
        bool getStockAllContract(std::vector<AllTrade::NPMgrCenter::SStockContractPtr>& contract_vec, const AllTrade::ExchangeIDType exchange_id);

        // ����/�����û���Ϣ
        bool updateUserInfo(const AllTrade::NPMgrCenter::SAccountPtr& account_ptr);
        // ����/���½�������Ϣ
        bool updateExchangeInfo(const AllTrade::NPMgrCenter::SExchangePtr& exchange_ptr);
        // ����/���º�Լ��Ϣ
        bool updateContractInfo(const AllTrade::NPMgrCenter::SContractPtr& contract_ptr);
        // ����/�����û��ʽ���Ϣ
        bool updateUserMoneyDetailInfo(const AllTrade::UserIDType user_id, const AllTrade::NPMgrCenter::SMoneyDetailInfoPtr& money_info);
        bool updateUserMoneyInfo(const AllTrade::UserIDType user_id, const AllTrade::NPMgrCenter::SMoneyInfoPtr& money_info);
        // ����/�����û������Ϣ
        bool updateUserRiskInfo(const AllTrade::UserIDType user_id, const AllTrade::NPMgrCenter::SRiskInfoPtr& risk_info);

        // ����/�������˻�������
        bool qryApplyMoney(std::vector<AllTrade::NPMgrCenter::SApplyMoneyPtr>& apply_infos, const AllTrade::UserIDType user_id, const AllTrade::DateType start_day, const AllTrade::DateType end_day, AllTrade::OIMM_Change_Type money_type);
        AllTrade::NPMgrCenter::SApplyMoneyPtr getApplyMoneyPtr(const AllTrade::ApplyMoneyIDType apply_money_id, AllTrade::OIMM_Change_Type type);
        bool applyMoney(const AllTrade::NPMgrCenter::SApplyMoneyPtr& apply_info);
        bool approvalApplyMoney(const AllTrade::UserIDType approval_user_id, const AllTrade::ApplyMoneyIDType apply_money_id, AllTrade::E_APPLY_MONEY_STATUS apply_status, const AllTrade::DateTimeType cur_dt, AllTrade::OIMM_Change_Type money_type);

        // ��ȡ�ʽ���ˮ
        std::vector<AllTrade::NPMgrCenter::SMoneyDetailInfoPtr> getFundSerial(const UserIDType user_id, const DateType start_day, const DateType end_day);

        // ���л�����ǳ�
        void serializeLoginInUser(const AllTrade::NPMgrCenter::SOnlineAccountPtr& online_acc_ptr);
        void serializeLoginOutUser(const AllTrade::NPMgrCenter::SOnlineAccountPtr& online_acc_ptr);

        std::string getNewAgentLink();

        // ��������Ӷ����Ϣ
        void agencyMoneyChange(const AllTrade::NPMgrCenter::SAgencyMoneyDetailInfoPtr agy_detail);
        // ��ѯӶ����Ϣ
        bool qryAgencyCommissInfo(const AllTrade::UserIDType user_id, const AllTrade::DateType start_day, const AllTrade::DateType end_day, YDouble& infomatch, YDouble& tradefee, YDouble& comm_all);
        // ��ѯӶ����ϸ��Ϣ
        std::vector<AllTrade::NPMgrCenter::SAgencyMoneyDetailInfoPtr> qryAgencyCommissDtlInfo(const AllTrade::UserIDType user_id, const AllTrade::DateType start_day, const AllTrade::DateType end_day);
        // ��ѯ�ֳ���Ϣ
        bool qryAgencyProfitInfo(const AllTrade::UserIDType user_id, const AllTrade::DateType start_day, const AllTrade::DateType end_day, YDouble& profit);
        // ��ѯ�ֳ���ϸ��Ϣ
        std::vector<AllTrade::NPMgrCenter::SAgencyMoneyDetailInfoPtr> qryAgencyProfitDtlInfo(const AllTrade::UserIDType user_id, const AllTrade::DateType start_day, const AllTrade::DateType end_day);

#pragma endregion

#pragma region Ȩ����ز���        
        // ��ȡ��ɫ
		ErrorCodeType getRolesUserInfo(const UserIDType userid, std::vector<AllTrade::AuthorityRolesPtr> &vecRolesInfo);
		// ���ӽ�ɫ����
		ErrorCodeType addRolesUserInfo(AllTrade::AuthorityRolesPtr& rolesInfo);
		// �޸Ľ�ɫ����
		ErrorCodeType updateRolesUserInfo(const AllTrade::AuthorityRolesPtr& rolesInfo);
		// ɾ����ɫ������ͨ����ɫIdɾ��
		ErrorCodeType deleteRolesUser(int rolesID);
		// �ж��Ƿ����иý�ɫ��
        ErrorCodeType isHaveRoleName(const AllTrade::LoginNameType roleName);

		/////////////////////////// �ж�ĳ�û��Ƿ����ĳ����Ȩ�� ////////////////////////////////////
        ErrorCodeType isHaveAuthority(const AllTrade::LoginNameType loginName, int nFunctionId)const;

		////////////////////////// �û��ͽ�ɫ //////////////////////////////////////////
		// ��ȡ�û��ͽ�ɫ֮���ϵ
        ErrorCodeType getAuthorityRoleUsers(const AllTrade::LoginNameType loginName, std::vector<AllTrade::AuthorityRoleUsersPtr>& vecAuthority);
		// �����û��ͽ�ɫ֮���ϵ
		ErrorCodeType addAuthorityRoleUsers(const std::vector<AllTrade::AuthorityRoleUsersPtr>& vecAuthority);
		// ɾ���û��ͽ�ɫ֮���ϵ
		ErrorCodeType deleteAuthorityRoleUsers(const std::vector<AllTrade::AuthorityRoleUsersPtr>& vecAuthority);

		// �жϽ�ɫ�Ƿ���ں��û�֮���ϵ
		ErrorCodeType judgeRoleUsersRelation(int roleId);
		// �ж�ĳ����ɫ��ĳ���û��Ƿ���ڹ�ϵ
        ErrorCodeType judgeRoleUsersRelation(const AllTrade::LoginNameType loginName, int nRoleId);
		// �ҵ���ĳ��ɫ�й�ϵ�����д�����
		int getAllAgentHaveRelation(std::set<int>& setInfo, int nRoleId);
		// �жϸ��û��Ƿ�󶨽�ɫ
		ErrorCodeType judgeRoleUsersRelation(const AllTrade::LoginNameType loginName);

		// �޸��û��ͽ�ɫ֮���ϵ
		ErrorCodeType changeAuthorityRoleUsers(const AllTrade::AuthorityRoleUsersPtr& ptr);

		/////////////////////////// ��ɫ / ���� //////////////////////////////////////////
		// ���� ��ɫ/���� ֮���ϵ
		ErrorCodeType addAuthorityRoleFunctions(int roleId, const std::vector<AllTrade::AuthorityRoleFunctionsPtr>& vecAuthority);
		// ɾ�� ��ɫ/���� ֮���ϵ
		ErrorCodeType deleteAuthorityRoleFunctions(const std::vector<AllTrade::AuthorityRoleFunctionsPtr>& vecAuthority);
		// ��ȡ ��ɫ/���� ֮���ϵ
		ErrorCodeType getAuthorityRoleFunctionsByRoleId(int roleId, std::vector<AllTrade::AuthorityRoleFunctionsPtr>& vecAuthority);
		// �жϽ�ɫ�͹����Ƿ��й�ϵ
		ErrorCodeType judgeRoleAndFunctionsRelationOne(int nRoleId);
		// �ж�ĳ����ɫ��ĳ�������Ƿ���ڹ�ϵ
		int judgeRoleAndFunctionsRelationTwo(int nFunctionID, int nRoleId);
		// ��ȡ���н�ɫ / ���ܹ�ϵ
		int getAllAuthorityRoleFunctions(std::vector<AllTrade::AuthorityRoleFunctionsPtr>& vecAuthority);

		// ��ȡ���д�������Ϣ
		int GetAllAgentInfo(std::map<int, std::set<int>>& mapInfo);

		// ��ѯ����Ĺ���
		ErrorCodeType getSelfFunctionsByLoginName(const LoginNameType loginName, std::vector<AuthorityFunctionsUserIdPtr> &vecAuthorityFunctions);

		// ��ѯ����ҵ��
		ErrorCodeType getAllBussness(std::vector<AuthorityBussnessesPtr>& vec);
#pragma endregion

#pragma region ������ز���
        // ���¹�Ʊί����Ϣ
        bool updateOrderInfo(const AllTrade::NPTradeCenter::OrderInfoPtr& order_ptr, const AllTrade::UserIDType user_id);
		// ��ȡ��Ʊί����Ϣ
        bool getStockOrderInfo(std::map<AllTrade::PUserIDType, std::vector<AllTrade::NPTradeCenter::StockOrderPtr>>& stockOrder);
        // ��ȡ��Ʊ��ʷί��
        std::vector<AllTrade::NPTradeCenter::OrderInfoPtr> getStockOrderHistory(const AllTrade::UserIDType user_id, const AllTrade::DateType start_time, const AllTrade::DateType end_time);
        // ��ȡ��Ʊ��ʷ�ɽ�
        std::vector<AllTrade::NPTradeCenter::TradeInfoPtr> getStockTradeHistory(const AllTrade::UserIDType user_id, const AllTrade::DateType start_time, const AllTrade::DateType end_time);

        // �����ɽ���¼
        bool addTradeRecord(const AllTrade::NPTradeCenter::TradeInfoPtr& trade_ptr, const AllTrade::UserIDType user_id);
		// ��ȡ��Ʊ�ɽ���¼
		bool getStockTradeRecord(std::map<AllTrade::PUserIDType, AllTrade::NPTradeCenter::StockTradePtr>& tradeOrder);

        // ���³ֲ���Ϣ
        bool updatePositionInfo(const AllTrade::NPTradeCenter::PositionInfoPtr& position_ptr, const AllTrade::UserIDType user_id);
        bool deletePositionInfo(const AllTrade::NPTradeCenter::PositionInfoPtr& position_ptr, const AllTrade::UserIDType user_id);
		// ��ȡ��Ʊ�ֲ���Ϣ
        bool getStockPositionInfo(std::map<AllTrade::PUserIDType, std::vector<AllTrade::NPTradeCenter::StockPositionPtr>>& posiOrder);

        // ����/���·�����Ϣ
        bool updateTradeFee(const AllTrade::NPTradeCenter::TradeFeePtr& trade_fee);
        bool getTradeFee(AllTrade::NPTradeCenter::TradeFeePtr& trade_fee);

        // �Ƿ���Խ���
        bool canSettle(const AllTrade::DateTimeType settle_datetime, const AllTrade::DateTimeType cur_datetime);
        // ����
        bool updateSettle(const AllTrade::DateTimeType settle_datetime);
        // Ӱ�ӱ�����ݹ���
        AllTrade::NPTradeCenter::GlobalDataPtr getCurrentGlobalData();
        bool updateCurGlobalData(const AllTrade::NPTradeCenter::GlobalDataPtr global_data);

        // ��ؼ�¼
        void updateRiskRecord(const AllTrade::NPTradeCenter::ImmRiskControlPtr risk_cont_st);
        AllTrade::NPTradeCenter::ImmRiskControlPtr getRiskRecord(const AllTrade::UserIDType user_id, AllTrade::RiskControlType rc_type);


		// ��ؼ�¼��¼�������ʷ��¼��
		bool selectHistoryRiskRecord(const AllTrade::UserIDType user_id, const AllTrade::DateType start_day, const AllTrade::DateType end_day, std::vector<AllTrade::NPTradeCenter::ImmRiskControlPtr>& vecSt);
		// ���ʵʱ��¼��ѯ
		bool getRiskRecord(const AllTrade::UserIDType user_id,std::vector<AllTrade::NPTradeCenter::ImmRiskControlPtr>& vecSt);
#pragma endregion

        // �ڰ��������
        void addStockBlackWhite(const ContractIDType contract_id);
        bool updateStockBlackWhiteStatus(const ContractIDType contract_id, bool isBlack);
        std::map<PContractIDType, bool> getAllStockBlackWhiteStatus();
        bool isBlackStock(const ContractIDType contract_id);

        // ��ֹ�������
        std::vector<AllTrade::NPTradeCenter::SForbidTradePtr> getAllForbidTradeStatus();
        bool updateForbidTradeStatus(const AllTrade::NPTradeCenter::SForbidTradePtr& ptr);

        // �ֱֲ������
        std::vector<AllTrade::NPTradeCenter::SPositionRatePtr> getPositionRateStatus();
        bool updatePositionRateStatus(const AllTrade::NPTradeCenter::SPositionRatePtr& ptr);

        // ��ѡ�����
        bool addCustomStock(const AllTrade::UserIDType user_id, const AllTrade::ContractIDType contract_id);
        bool removeCustomStock(const AllTrade::UserIDType user_id, const AllTrade::ContractIDType contract_id);
        std::vector<AllTrade::PContractIDType> getAllCustomStock(const AllTrade::UserIDType user_id);
        std::map<AllTrade::PUserIDType, std::vector<AllTrade::PContractIDType>> getAllCustomStock();

#pragma region ��ȯ��ز���
		// ������ȯί�б�
		// bool updateMarginPositionTable(const AllTrade::NPTradeCenter::MarginPositionInfoPtr& ptr);
		// �鿴��ȯί�б�
		bool getMarginPositionInfo(std::map<AllTrade::PUserIDType, std::vector<AllTrade::NPTradeCenter::MarginPositionInfoPtr>>& posiOrder);

		// ������ȯί�б�
//		bool updateMarginTradeTable(const AllTrade::NPTradeCenter::MarginTradeInfoPtr& ptr);
		// ��ȡ��ȯ�ɽ���¼
		bool getMarginTradeRecord(std::map<AllTrade::PUserIDType, AllTrade::NPTradeCenter::MarginTradeInfoPtr>& tradeOrder);
		// ��ȡ��ȯ��ʷ�ɽ�
		std::vector<AllTrade::NPTradeCenter::MarginTradeInfoPtr> getMarginTradeHistory(const AllTrade::UserIDType user_id, const AllTrade::DateType start_time, const AllTrade::DateType end_time);


		// ������ȯί�б�
//		bool updateMarginOrderTable(const AllTrade::NPTradeCenter::MarginOrderInfoPtr& ptr);
		// ��ȡ��ȯί����Ϣ
		bool getMarginOrderInfo(std::map<AllTrade::PUserIDType, std::vector<AllTrade::NPTradeCenter::MarginOrderInfoPtr>>& marginOrder);
		// �鿴��ʷ��ȯί����Ϣ
		std::vector<AllTrade::NPTradeCenter::MarginOrderInfoPtr> getAllMarginOrderHistory(const AllTrade::UserIDType user_id, const AllTrade::DateType start_time, const AllTrade::DateType end_time);

		// ������ȯ��Ϣ��
		bool updateMarginInfoTable(const AllTrade::NPTradeCenter::MarginInfoPtr& ptr);
		// �鿴��ȯ��Ϣ��
		bool getAllMarginInfo(const AllTrade::NPTradeCenter::MarginInfoPtr& ptr);
	

		// ������ȯʣ��������Ϣ
		bool updateMarginLeftTable(const AllTrade::NPTradeCenter::MarginLeftInfoPtr& ptr);
		// ��ѯ��ȯʣ��������Ϣ
		bool getMarginLeftTable(const AllTrade::NPTradeCenter::MarginLeftInfoPtr& ptr);


		// ��ѯ��Ϣ�ۼ���Ϣ
		bool getInterestStatisticsTable(const AllTrade::UserIDType user_id, AllTrade::NPMgrCenter::InterestStatisticsPtr& rstInfo);
		bool updateInterestStatisticsTable(AllTrade::NPMgrCenter::InterestStatisticsPtr& ptrInfo);
		// ��ѯ��Ϣ��ϸ
		bool getInterestDetailTable(const AllTrade::UserIDType user_id, std::vector<AllTrade::NPMgrCenter::InterestDetailPtr>& rstInfo);
		bool updateInterestDetailTable(AllTrade::NPMgrCenter::InterestDetailPtr& ptrInfo);
#pragma endregion


	private:
        DBOpManagerCenter*  m_mgr_center;
		CAuthorityControl*  m_authorityControl;
        DBOpTradeCenter*    m_trade_center;
	};

}
#endif