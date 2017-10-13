/*************************************************
Copyright (C), 2017, HX Tech Co., Ltd.
File name:      DBOpManagerCenter.h
Author:			XuYC
Version:
Date:
Description:    ���ݿ����- ����������ز���
*************************************************/

#include <string>
#include <map>
#include <vector>
#include "define/struct_declare.h"
#include "define/params_declare.h"

#define VERSION "1.0.0.0"

namespace OperationManager{

    class DBOpManagerCenter
    {
    public:
        DBOpManagerCenter();
        ~DBOpManagerCenter();

        // ��ʼ�����ݿ��
        bool initAllTable();

    public:
        // ��ȡ���˻�
        bool getRootAccount(AllTrade::NPMgrCenter::RootAccountPtr& root_ptr);
        // ��ȡָ���˻������е����˻�(������Խ���˻�)
        bool getAllDirectChildren(std::vector<AllTrade::NPMgrCenter::SAccountPtr>& children, const AllTrade::NPMgrCenter::SAccountPtr& account_ptr);
        // ��ȡָ���˻��µļ�ܲ��˻�(�������˻�/�����˻�/����˻�)(������Խ���˻�)
        bool getMonitChildren(std::vector<AllTrade::NPMgrCenter::SAccountPtr>& children, const AllTrade::NPMgrCenter::SAccountPtr& account_ptr);
        // ��ȡָ���˻��µĻ����˻�(������Խ���˻�)
        bool getAgencyChildren(std::vector<AllTrade::NPMgrCenter::SAccountPtr>& children, const AllTrade::NPMgrCenter::SAccountPtr& account_ptr);
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
        std::vector<AllTrade::NPMgrCenter::SMoneyDetailInfoPtr> getFundSerial(const AllTrade::UserIDType user_id, const AllTrade::DateType start_day, const AllTrade::DateType end_day);

        // ���л�����ǳ�
        void serializeLoginInUser(const AllTrade::NPMgrCenter::SOnlineAccountPtr& online_acc_ptr);
        void serializeLoginOutUser(const AllTrade::NPMgrCenter::SOnlineAccountPtr& online_acc_ptr);

        std::string getNewAgentLink();

        // ��ѡ�����
        bool addCustomStock(const AllTrade::UserIDType user_id, const AllTrade::ContractIDType contract_id);
        bool removeCustomStock(const AllTrade::UserIDType user_id, const AllTrade::ContractIDType contract_id);
        std::vector<AllTrade::PContractIDType> getAllCustomStock(const AllTrade::UserIDType user_id);
        std::map<AllTrade::PUserIDType, std::vector<AllTrade::PContractIDType>> getAllCustomStock();

        // ��������Ӷ����Ϣ
        void initCommissChange(const AllTrade::UserIDType user_id);
        void initProfitChange(const AllTrade::UserIDType user_id);
        void agencyMoneyChange(const AllTrade::NPMgrCenter::SAgencyMoneyDetailInfoPtr agy_detail);
        // ��ѯӶ����Ϣ
        bool qryAgencyCommissInfo(const AllTrade::UserIDType user_id, const AllTrade::DateType start_day, const AllTrade::DateType end_day, YDouble& infomatch, YDouble& tradefee, YDouble& comm_all);
        // ��ѯӶ����ϸ��Ϣ
        std::vector<AllTrade::NPMgrCenter::SAgencyMoneyDetailInfoPtr> qryAgencyCommissDtlInfo(const AllTrade::UserIDType user_id, const AllTrade::DateType start_day, const AllTrade::DateType end_day);
        // ��ѯ�ֳ���Ϣ
        bool qryAgencyProfitInfo(const AllTrade::UserIDType user_id, const AllTrade::DateType start_day, const AllTrade::DateType end_day, YDouble& profit);
        // ��ѯ�ֳ���ϸ��Ϣ
        std::vector<AllTrade::NPMgrCenter::SAgencyMoneyDetailInfoPtr> qryAgencyProfitDtlInfo(const AllTrade::UserIDType user_id, const AllTrade::DateType start_day, const AllTrade::DateType end_day);

		// ��ѯ��Ϣ�ۼ���Ϣ
		bool getInterestStatisticsTable(const AllTrade::UserIDType user_id, AllTrade::NPMgrCenter::InterestStatisticsPtr& rstInfo);
		bool updateInterestStatisticsTable( AllTrade::NPMgrCenter::InterestStatisticsPtr& ptrInfo);
		// ��ѯ��Ϣ��ϸ
		bool getInterestDetailTable(const AllTrade::UserIDType user_id, std::vector<AllTrade::NPMgrCenter::InterestDetailPtr>& rstInfo);
		bool updateInterestDetailTable( AllTrade::NPMgrCenter::InterestDetailPtr& ptrInfo);
    private:
        bool createManagerUsers();
        bool createAgencyUsers();
        bool createTraderUsers();
        bool createFunderUsers();

        bool updateSuperMgrUserInfo(const AllTrade::NPMgrCenter::RootAccountPtr& account_ptr);
        bool updateAgencyUserInfo(const AllTrade::NPMgrCenter::AgencyAccountPtr& account_ptr);
        bool updateRiskerUserInfo(const AllTrade::NPMgrCenter::RiskAccountPtr& account_ptr);
        bool updateMonitorUserInfo(const AllTrade::NPMgrCenter::ManagerAccountPtr& account_ptr);
        bool updateTraderUserInfo(const AllTrade::NPMgrCenter::TradeAccountPtr& account_ptr);
        bool updateFunderUserInfo(const AllTrade::NPMgrCenter::FunderAccountPtr& account_ptr);

        bool updateStockContractInfo(const AllTrade::NPMgrCenter::SStockContractPtr& contract_ptr);

        bool createExchanges();

        bool createStockContract();

        bool createStockMoneyDetail();
        bool createStockMoney();

        bool createStockRisk();

        bool createApplyMoney();

		bool createVersionTable();
		bool InsertVersionTable();

        bool createLoginInOutInfo();

        bool createCustomStock();

        bool createAccountGlobalData();

        // ��������Ӷ���
        bool createAgencyCommiss();
        bool createAgencyProfit();

        // ����Ӷ��/�ֳ�
        void agencyCommissChange(const AllTrade::NPMgrCenter::SAgencyMoneyDetailInfoPtr agy_detail);
        void agencyProfitChange(const AllTrade::NPMgrCenter::SAgencyMoneyDetailInfoPtr agy_detail);

		// ������Ϣͳ��
		bool createInterestStatisticsTable();
		// ������Ϣ��ϸ
		bool createInterestDetailTable();
    };

}
