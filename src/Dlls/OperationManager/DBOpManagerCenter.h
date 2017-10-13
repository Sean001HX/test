/*************************************************
Copyright (C), 2017, HX Tech Co., Ltd.
File name:      DBOpManagerCenter.h
Author:			XuYC
Version:
Date:
Description:    数据库操作- 管理中心相关部分
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

        // 初始化数据库表
        bool initAllTable();

    public:
        // 获取根账户
        bool getRootAccount(AllTrade::NPMgrCenter::RootAccountPtr& root_ptr);
        // 获取指定账户下所有的子账户(不包含越级账户)
        bool getAllDirectChildren(std::vector<AllTrade::NPMgrCenter::SAccountPtr>& children, const AllTrade::NPMgrCenter::SAccountPtr& account_ptr);
        // 获取指定账户下的监管层账户(包含根账户/管理账户/风控账户)(不包含越级账户)
        bool getMonitChildren(std::vector<AllTrade::NPMgrCenter::SAccountPtr>& children, const AllTrade::NPMgrCenter::SAccountPtr& account_ptr);
        // 获取指定账户下的机构账户(不包含越级账户)
        bool getAgencyChildren(std::vector<AllTrade::NPMgrCenter::SAccountPtr>& children, const AllTrade::NPMgrCenter::SAccountPtr& account_ptr);
        // 获取指定账户下的交易账户
        bool getTradeChildren(std::vector<AllTrade::NPMgrCenter::SAccountPtr>& children, const AllTrade::NPMgrCenter::SAccountPtr& account_ptr);
        // 获取指定账户下的实盘账户
        bool getFunderChildren(std::vector<AllTrade::NPMgrCenter::SAccountPtr>& children, const AllTrade::NPMgrCenter::SAccountPtr& account_ptr);
        // 获取用户资金信息
        bool getUserMoneyInfo(const AllTrade::UserIDType user_id, AllTrade::NPMgrCenter::SMoneyInfoPtr& money_info);
        // 获取用户风控信息
        bool getUserRiskInfo(const AllTrade::UserIDType user_id, AllTrade::NPMgrCenter::SRiskInfoPtr& risk_info);

        // 获取所有交易所信息
        bool getAllExchange(std::vector<AllTrade::NPMgrCenter::SExchangePtr>& exchanges);
        // 获取所有交易所信息
        bool getStockAllContract(std::vector<AllTrade::NPMgrCenter::SStockContractPtr>& contract_vec, const AllTrade::ExchangeIDType exchange_id);

        // 创建/更新用户信息
        bool updateUserInfo(const AllTrade::NPMgrCenter::SAccountPtr& account_ptr);
        // 创建/更新交易所信息
        bool updateExchangeInfo(const AllTrade::NPMgrCenter::SExchangePtr& exchange_ptr);
        // 创建/更新合约信息
        bool updateContractInfo(const AllTrade::NPMgrCenter::SContractPtr& contract_ptr);
        // 创建/更新用户资金信息
        bool updateUserMoneyDetailInfo(const AllTrade::UserIDType user_id, const AllTrade::NPMgrCenter::SMoneyDetailInfoPtr& money_info);
        bool updateUserMoneyInfo(const AllTrade::UserIDType user_id, const AllTrade::NPMgrCenter::SMoneyInfoPtr& money_info);
        // 创建/更新用户风控信息
        bool updateUserRiskInfo(const AllTrade::UserIDType user_id, const AllTrade::NPMgrCenter::SRiskInfoPtr& risk_info);

        // 创建/更新子账户入金审核
        bool qryApplyMoney(std::vector<AllTrade::NPMgrCenter::SApplyMoneyPtr>& apply_infos, const AllTrade::UserIDType user_id, const AllTrade::DateType start_day, const AllTrade::DateType end_day, AllTrade::OIMM_Change_Type money_type);
        AllTrade::NPMgrCenter::SApplyMoneyPtr getApplyMoneyPtr(const AllTrade::ApplyMoneyIDType apply_money_id, AllTrade::OIMM_Change_Type type);
        bool applyMoney(const AllTrade::NPMgrCenter::SApplyMoneyPtr& apply_info);
        bool approvalApplyMoney(const AllTrade::UserIDType approval_user_id, const AllTrade::ApplyMoneyIDType apply_money_id, AllTrade::E_APPLY_MONEY_STATUS apply_status, const AllTrade::DateTimeType cur_dt, AllTrade::OIMM_Change_Type money_type);

        // 获取资金流水
        std::vector<AllTrade::NPMgrCenter::SMoneyDetailInfoPtr> getFundSerial(const AllTrade::UserIDType user_id, const AllTrade::DateType start_day, const AllTrade::DateType end_day);

        // 序列化登入登出
        void serializeLoginInUser(const AllTrade::NPMgrCenter::SOnlineAccountPtr& online_acc_ptr);
        void serializeLoginOutUser(const AllTrade::NPMgrCenter::SOnlineAccountPtr& online_acc_ptr);

        std::string getNewAgentLink();

        // 自选股相关
        bool addCustomStock(const AllTrade::UserIDType user_id, const AllTrade::ContractIDType contract_id);
        bool removeCustomStock(const AllTrade::UserIDType user_id, const AllTrade::ContractIDType contract_id);
        std::vector<AllTrade::PContractIDType> getAllCustomStock(const AllTrade::UserIDType user_id);
        std::map<AllTrade::PUserIDType, std::vector<AllTrade::PContractIDType>> getAllCustomStock();

        // 新增机构佣金信息
        void initCommissChange(const AllTrade::UserIDType user_id);
        void initProfitChange(const AllTrade::UserIDType user_id);
        void agencyMoneyChange(const AllTrade::NPMgrCenter::SAgencyMoneyDetailInfoPtr agy_detail);
        // 查询佣金信息
        bool qryAgencyCommissInfo(const AllTrade::UserIDType user_id, const AllTrade::DateType start_day, const AllTrade::DateType end_day, YDouble& infomatch, YDouble& tradefee, YDouble& comm_all);
        // 查询佣金明细信息
        std::vector<AllTrade::NPMgrCenter::SAgencyMoneyDetailInfoPtr> qryAgencyCommissDtlInfo(const AllTrade::UserIDType user_id, const AllTrade::DateType start_day, const AllTrade::DateType end_day);
        // 查询分成信息
        bool qryAgencyProfitInfo(const AllTrade::UserIDType user_id, const AllTrade::DateType start_day, const AllTrade::DateType end_day, YDouble& profit);
        // 查询分成明细信息
        std::vector<AllTrade::NPMgrCenter::SAgencyMoneyDetailInfoPtr> qryAgencyProfitDtlInfo(const AllTrade::UserIDType user_id, const AllTrade::DateType start_day, const AllTrade::DateType end_day);

		// 查询利息累计信息
		bool getInterestStatisticsTable(const AllTrade::UserIDType user_id, AllTrade::NPMgrCenter::InterestStatisticsPtr& rstInfo);
		bool updateInterestStatisticsTable( AllTrade::NPMgrCenter::InterestStatisticsPtr& ptrInfo);
		// 查询利息明细
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

        // 创建机构佣金表
        bool createAgencyCommiss();
        bool createAgencyProfit();

        // 更新佣金/分成
        void agencyCommissChange(const AllTrade::NPMgrCenter::SAgencyMoneyDetailInfoPtr agy_detail);
        void agencyProfitChange(const AllTrade::NPMgrCenter::SAgencyMoneyDetailInfoPtr agy_detail);

		// 创建利息统计
		bool createInterestStatisticsTable();
		// 创建利息明细
		bool createInterestDetailTable();
    };

}
