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
#pragma region 用户与交易所管理相关操作
        // 获取根账户
        bool getRootAccount(AllTrade::NPMgrCenter::RootAccountPtr& root_ptr);
        // 获取指定账户下所有的子账户(不包含越级账户)
        bool getAllDirectChildren(std::vector<AllTrade::NPMgrCenter::SAccountPtr>& children, const AllTrade::NPMgrCenter::SAccountPtr& account_ptr);
        // 获取指定账户下的管理层账户(包含根账户/机构账户/管理账户/风控账户)
        bool getMonitChildren(std::vector<AllTrade::NPMgrCenter::SAccountPtr>& children, const AllTrade::NPMgrCenter::SAccountPtr& account_ptr);
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
        std::vector<AllTrade::NPMgrCenter::SMoneyDetailInfoPtr> getFundSerial(const UserIDType user_id, const DateType start_day, const DateType end_day);

        // 序列化登入登出
        void serializeLoginInUser(const AllTrade::NPMgrCenter::SOnlineAccountPtr& online_acc_ptr);
        void serializeLoginOutUser(const AllTrade::NPMgrCenter::SOnlineAccountPtr& online_acc_ptr);

        std::string getNewAgentLink();

        // 新增机构佣金信息
        void agencyMoneyChange(const AllTrade::NPMgrCenter::SAgencyMoneyDetailInfoPtr agy_detail);
        // 查询佣金信息
        bool qryAgencyCommissInfo(const AllTrade::UserIDType user_id, const AllTrade::DateType start_day, const AllTrade::DateType end_day, YDouble& infomatch, YDouble& tradefee, YDouble& comm_all);
        // 查询佣金明细信息
        std::vector<AllTrade::NPMgrCenter::SAgencyMoneyDetailInfoPtr> qryAgencyCommissDtlInfo(const AllTrade::UserIDType user_id, const AllTrade::DateType start_day, const AllTrade::DateType end_day);
        // 查询分成信息
        bool qryAgencyProfitInfo(const AllTrade::UserIDType user_id, const AllTrade::DateType start_day, const AllTrade::DateType end_day, YDouble& profit);
        // 查询分成明细信息
        std::vector<AllTrade::NPMgrCenter::SAgencyMoneyDetailInfoPtr> qryAgencyProfitDtlInfo(const AllTrade::UserIDType user_id, const AllTrade::DateType start_day, const AllTrade::DateType end_day);

#pragma endregion

#pragma region 权限相关操作        
        // 获取角色
		ErrorCodeType getRolesUserInfo(const UserIDType userid, std::vector<AllTrade::AuthorityRolesPtr> &vecRolesInfo);
		// 增加角色操作
		ErrorCodeType addRolesUserInfo(AllTrade::AuthorityRolesPtr& rolesInfo);
		// 修改角色操作
		ErrorCodeType updateRolesUserInfo(const AllTrade::AuthorityRolesPtr& rolesInfo);
		// 删除角色操作：通过角色Id删除
		ErrorCodeType deleteRolesUser(int rolesID);
		// 判断是否已有该角色名
        ErrorCodeType isHaveRoleName(const AllTrade::LoginNameType roleName);

		/////////////////////////// 判断某用户是否具有某功能权限 ////////////////////////////////////
        ErrorCodeType isHaveAuthority(const AllTrade::LoginNameType loginName, int nFunctionId)const;

		////////////////////////// 用户和角色 //////////////////////////////////////////
		// 获取用户和角色之间关系
        ErrorCodeType getAuthorityRoleUsers(const AllTrade::LoginNameType loginName, std::vector<AllTrade::AuthorityRoleUsersPtr>& vecAuthority);
		// 增加用户和角色之间关系
		ErrorCodeType addAuthorityRoleUsers(const std::vector<AllTrade::AuthorityRoleUsersPtr>& vecAuthority);
		// 删除用户和角色之间关系
		ErrorCodeType deleteAuthorityRoleUsers(const std::vector<AllTrade::AuthorityRoleUsersPtr>& vecAuthority);

		// 判断角色是否存在和用户之间关系
		ErrorCodeType judgeRoleUsersRelation(int roleId);
		// 判断某个角色和某个用户是否存在关系
        ErrorCodeType judgeRoleUsersRelation(const AllTrade::LoginNameType loginName, int nRoleId);
		// 找到和某角色有关系的所有代理商
		int getAllAgentHaveRelation(std::set<int>& setInfo, int nRoleId);
		// 判断该用户是否绑定角色
		ErrorCodeType judgeRoleUsersRelation(const AllTrade::LoginNameType loginName);

		// 修改用户和角色之间关系
		ErrorCodeType changeAuthorityRoleUsers(const AllTrade::AuthorityRoleUsersPtr& ptr);

		/////////////////////////// 角色 / 功能 //////////////////////////////////////////
		// 增加 角色/功能 之间关系
		ErrorCodeType addAuthorityRoleFunctions(int roleId, const std::vector<AllTrade::AuthorityRoleFunctionsPtr>& vecAuthority);
		// 删除 角色/功能 之间关系
		ErrorCodeType deleteAuthorityRoleFunctions(const std::vector<AllTrade::AuthorityRoleFunctionsPtr>& vecAuthority);
		// 获取 角色/功能 之间关系
		ErrorCodeType getAuthorityRoleFunctionsByRoleId(int roleId, std::vector<AllTrade::AuthorityRoleFunctionsPtr>& vecAuthority);
		// 判断角色和功能是否有关系
		ErrorCodeType judgeRoleAndFunctionsRelationOne(int nRoleId);
		// 判断某个角色和某个功能是否存在关系
		int judgeRoleAndFunctionsRelationTwo(int nFunctionID, int nRoleId);
		// 获取所有角色 / 功能关系
		int getAllAuthorityRoleFunctions(std::vector<AllTrade::AuthorityRoleFunctionsPtr>& vecAuthority);

		// 获取所有代理商信息
		int GetAllAgentInfo(std::map<int, std::set<int>>& mapInfo);

		// 查询自身的功能
		ErrorCodeType getSelfFunctionsByLoginName(const LoginNameType loginName, std::vector<AuthorityFunctionsUserIdPtr> &vecAuthorityFunctions);

		// 查询所有业务
		ErrorCodeType getAllBussness(std::vector<AuthorityBussnessesPtr>& vec);
#pragma endregion

#pragma region 交易相关操作
        // 更新股票委托信息
        bool updateOrderInfo(const AllTrade::NPTradeCenter::OrderInfoPtr& order_ptr, const AllTrade::UserIDType user_id);
		// 获取股票委托信息
        bool getStockOrderInfo(std::map<AllTrade::PUserIDType, std::vector<AllTrade::NPTradeCenter::StockOrderPtr>>& stockOrder);
        // 获取股票历史委托
        std::vector<AllTrade::NPTradeCenter::OrderInfoPtr> getStockOrderHistory(const AllTrade::UserIDType user_id, const AllTrade::DateType start_time, const AllTrade::DateType end_time);
        // 获取股票历史成交
        std::vector<AllTrade::NPTradeCenter::TradeInfoPtr> getStockTradeHistory(const AllTrade::UserIDType user_id, const AllTrade::DateType start_time, const AllTrade::DateType end_time);

        // 新增成交记录
        bool addTradeRecord(const AllTrade::NPTradeCenter::TradeInfoPtr& trade_ptr, const AllTrade::UserIDType user_id);
		// 获取股票成交记录
		bool getStockTradeRecord(std::map<AllTrade::PUserIDType, AllTrade::NPTradeCenter::StockTradePtr>& tradeOrder);

        // 更新持仓信息
        bool updatePositionInfo(const AllTrade::NPTradeCenter::PositionInfoPtr& position_ptr, const AllTrade::UserIDType user_id);
        bool deletePositionInfo(const AllTrade::NPTradeCenter::PositionInfoPtr& position_ptr, const AllTrade::UserIDType user_id);
		// 获取股票持仓信息
        bool getStockPositionInfo(std::map<AllTrade::PUserIDType, std::vector<AllTrade::NPTradeCenter::StockPositionPtr>>& posiOrder);

        // 创建/更新费用信息
        bool updateTradeFee(const AllTrade::NPTradeCenter::TradeFeePtr& trade_fee);
        bool getTradeFee(AllTrade::NPTradeCenter::TradeFeePtr& trade_fee);

        // 是否可以结算
        bool canSettle(const AllTrade::DateTimeType settle_datetime, const AllTrade::DateTimeType cur_datetime);
        // 结算
        bool updateSettle(const AllTrade::DateTimeType settle_datetime);
        // 影子编号数据管理
        AllTrade::NPTradeCenter::GlobalDataPtr getCurrentGlobalData();
        bool updateCurGlobalData(const AllTrade::NPTradeCenter::GlobalDataPtr global_data);

        // 风控记录
        void updateRiskRecord(const AllTrade::NPTradeCenter::ImmRiskControlPtr risk_cont_st);
        AllTrade::NPTradeCenter::ImmRiskControlPtr getRiskRecord(const AllTrade::UserIDType user_id, AllTrade::RiskControlType rc_type);


		// 风控记录记录到风控历史记录表
		bool selectHistoryRiskRecord(const AllTrade::UserIDType user_id, const AllTrade::DateType start_day, const AllTrade::DateType end_day, std::vector<AllTrade::NPTradeCenter::ImmRiskControlPtr>& vecSt);
		// 风控实时记录查询
		bool getRiskRecord(const AllTrade::UserIDType user_id,std::vector<AllTrade::NPTradeCenter::ImmRiskControlPtr>& vecSt);
#pragma endregion

        // 黑白名单相关
        void addStockBlackWhite(const ContractIDType contract_id);
        bool updateStockBlackWhiteStatus(const ContractIDType contract_id, bool isBlack);
        std::map<PContractIDType, bool> getAllStockBlackWhiteStatus();
        bool isBlackStock(const ContractIDType contract_id);

        // 禁止交易相关
        std::vector<AllTrade::NPTradeCenter::SForbidTradePtr> getAllForbidTradeStatus();
        bool updateForbidTradeStatus(const AllTrade::NPTradeCenter::SForbidTradePtr& ptr);

        // 持仓比例相关
        std::vector<AllTrade::NPTradeCenter::SPositionRatePtr> getPositionRateStatus();
        bool updatePositionRateStatus(const AllTrade::NPTradeCenter::SPositionRatePtr& ptr);

        // 自选股相关
        bool addCustomStock(const AllTrade::UserIDType user_id, const AllTrade::ContractIDType contract_id);
        bool removeCustomStock(const AllTrade::UserIDType user_id, const AllTrade::ContractIDType contract_id);
        std::vector<AllTrade::PContractIDType> getAllCustomStock(const AllTrade::UserIDType user_id);
        std::map<AllTrade::PUserIDType, std::vector<AllTrade::PContractIDType>> getAllCustomStock();

#pragma region 融券相关操作
		// 创建融券委托表
		// bool updateMarginPositionTable(const AllTrade::NPTradeCenter::MarginPositionInfoPtr& ptr);
		// 查看融券委托表
		bool getMarginPositionInfo(std::map<AllTrade::PUserIDType, std::vector<AllTrade::NPTradeCenter::MarginPositionInfoPtr>>& posiOrder);

		// 创建融券委托表
//		bool updateMarginTradeTable(const AllTrade::NPTradeCenter::MarginTradeInfoPtr& ptr);
		// 获取融券成交记录
		bool getMarginTradeRecord(std::map<AllTrade::PUserIDType, AllTrade::NPTradeCenter::MarginTradeInfoPtr>& tradeOrder);
		// 获取融券历史成交
		std::vector<AllTrade::NPTradeCenter::MarginTradeInfoPtr> getMarginTradeHistory(const AllTrade::UserIDType user_id, const AllTrade::DateType start_time, const AllTrade::DateType end_time);


		// 创建融券委托表
//		bool updateMarginOrderTable(const AllTrade::NPTradeCenter::MarginOrderInfoPtr& ptr);
		// 获取融券委托信息
		bool getMarginOrderInfo(std::map<AllTrade::PUserIDType, std::vector<AllTrade::NPTradeCenter::MarginOrderInfoPtr>>& marginOrder);
		// 查看历史融券委托信息
		std::vector<AllTrade::NPTradeCenter::MarginOrderInfoPtr> getAllMarginOrderHistory(const AllTrade::UserIDType user_id, const AllTrade::DateType start_time, const AllTrade::DateType end_time);

		// 更新融券信息表
		bool updateMarginInfoTable(const AllTrade::NPTradeCenter::MarginInfoPtr& ptr);
		// 查看融券信息表
		bool getAllMarginInfo(const AllTrade::NPTradeCenter::MarginInfoPtr& ptr);
	

		// 更新融券剩余数量信息
		bool updateMarginLeftTable(const AllTrade::NPTradeCenter::MarginLeftInfoPtr& ptr);
		// 查询融券剩余数量信息
		bool getMarginLeftTable(const AllTrade::NPTradeCenter::MarginLeftInfoPtr& ptr);


		// 查询利息累计信息
		bool getInterestStatisticsTable(const AllTrade::UserIDType user_id, AllTrade::NPMgrCenter::InterestStatisticsPtr& rstInfo);
		bool updateInterestStatisticsTable(AllTrade::NPMgrCenter::InterestStatisticsPtr& ptrInfo);
		// 查询利息明细
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