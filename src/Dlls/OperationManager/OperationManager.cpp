// OperationManager.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include "include/OperationManager/OperationManager.h"
#include "OperationManagerImpl.h"
#include "define/protocol_error.h"

namespace OperationManager
{
	COperationManager::COperationManager() :m_impl(NULL)
	{
		m_impl = new COperationManagerImpl();
	}

	COperationManager::~COperationManager()
	{
		if (m_impl)
		{
			delete m_impl;
			m_impl = NULL;
		}
	}

    bool COperationManager::initialize()
    {
        if (m_impl)
            return m_impl->initialize();

        return false;
    }

#pragma region 用户与交易所管理相关操作

    bool COperationManager::getRootAccount(AllTrade::NPMgrCenter::RootAccountPtr& root_ptr)
    {
        if (m_impl)
            return m_impl->getRootAccount(root_ptr);

        return false;
    }

    bool COperationManager::getAllDirectChildren(std::vector<AllTrade::NPMgrCenter::SAccountPtr>& children, const AllTrade::NPMgrCenter::SAccountPtr& account_ptr)
    {
        if (m_impl)
            return m_impl->getAllDirectChildren(children, account_ptr);

        return false;
    }

    bool COperationManager::getMonitChildren(std::vector<AllTrade::NPMgrCenter::SAccountPtr>& children, const AllTrade::NPMgrCenter::SAccountPtr& account_ptr)
    {
        if (m_impl)
            return m_impl->getMonitChildren(children, account_ptr);

        return false;
    }

    bool COperationManager::getTradeChildren(std::vector<AllTrade::NPMgrCenter::SAccountPtr>& children, const AllTrade::NPMgrCenter::SAccountPtr& account_ptr)
    {
        if (m_impl)
            return m_impl->getTradeChildren(children, account_ptr);

        return false;
    }

    bool COperationManager::getFunderChildren(std::vector<AllTrade::NPMgrCenter::SAccountPtr>& children, const AllTrade::NPMgrCenter::SAccountPtr& account_ptr)
    {
        if (m_impl)
            return m_impl->getFunderChildren(children, account_ptr);

        return false;
    }

    bool COperationManager::getUserMoneyInfo(const UserIDType user_id, AllTrade::NPMgrCenter::SMoneyInfoPtr& money_info)
    {
        if (m_impl)
            return m_impl->getUserMoneyInfo(user_id, money_info);

        return false;
    }

    bool COperationManager::getUserRiskInfo(const UserIDType user_id, AllTrade::NPMgrCenter::SRiskInfoPtr& risk_info)
    {
        if (m_impl)
            return m_impl->getUserRiskInfo(user_id, risk_info);

        return false;
    }

    bool COperationManager::getAllExchange(std::vector<AllTrade::NPMgrCenter::SExchangePtr>& exchanges)
    {
        if (m_impl)
            return m_impl->getAllExchange(exchanges);

        return false;
    }

    bool COperationManager::getStockAllContract(std::vector<AllTrade::NPMgrCenter::SStockContractPtr>& contract_vec, const ExchangeIDType exchange_id)
    {
        if (m_impl)
            return m_impl->getStockAllContract(contract_vec, exchange_id);

        return false;
    }

    bool COperationManager::updateUserInfo(const AllTrade::NPMgrCenter::SAccountPtr& account_ptr)
    {
        if (m_impl)
            return m_impl->updateUserInfo(account_ptr);

        return false;
    }

    bool COperationManager::updateExchangeInfo(const AllTrade::NPMgrCenter::SExchangePtr& exchange_ptr)
    {
        if (m_impl)
            return m_impl->updateExchangeInfo(exchange_ptr);

        return false;
    }

    bool COperationManager::updateContractInfo(const AllTrade::NPMgrCenter::SContractPtr& contract_ptr)
    {
        if (m_impl)
            return m_impl->updateContractInfo(contract_ptr);

        return false;
    }

    bool COperationManager::updateUserMoneyDetailInfo(const AllTrade::UserIDType user_id, const AllTrade::NPMgrCenter::SMoneyDetailInfoPtr& money_info)
    {
        if (m_impl)
            return m_impl->updateUserMoneyDetailInfo(user_id, money_info);

        return false;
    }

    bool COperationManager::updateUserMoneyInfo(const UserIDType user_id, const AllTrade::NPMgrCenter::SMoneyInfoPtr& money_info)
    {
        if (m_impl)
            return m_impl->updateUserMoneyInfo(user_id, money_info);

        return false;
    }

    bool COperationManager::updateUserRiskInfo(const UserIDType user_id, const AllTrade::NPMgrCenter::SRiskInfoPtr& risk_info)
    {
        if (m_impl)
            return m_impl->updateUserRiskInfo(user_id, risk_info);

        return false;
    }

    bool COperationManager::qryApplyMoney(std::vector<AllTrade::NPMgrCenter::SApplyMoneyPtr>& apply_infos, const AllTrade::UserIDType user_id, const DateType start_day, const DateType end_day, AllTrade::OIMM_Change_Type money_type)
    {
        if (m_impl)
            return m_impl->qryApplyMoney(apply_infos, user_id, start_day, end_day, money_type);

        return false;
    }

    AllTrade::NPMgrCenter::SApplyMoneyPtr COperationManager::getApplyMoneyPtr(const AllTrade::ApplyMoneyIDType apply_money_id, AllTrade::OIMM_Change_Type type)
    {
        if (m_impl)
            return m_impl->getApplyMoneyPtr(apply_money_id, type);

        return AllTrade::NPMgrCenter::SApplyMoneyPtr();
    }

    bool COperationManager::applyMoney(const AllTrade::NPMgrCenter::SApplyMoneyPtr& apply_info)
    {
        if (m_impl)
            return m_impl->applyMoney(apply_info);

        return false;
    }

    bool COperationManager::approvalApplyMoney(const UserIDType approval_user_id, const AllTrade::ApplyMoneyIDType apply_money_id, AllTrade::E_APPLY_MONEY_STATUS apply_status, const AllTrade::DateTimeType cur_dt, AllTrade::OIMM_Change_Type money_type)
    {
        if (m_impl)
            return m_impl->approvalApplyMoney(approval_user_id, apply_money_id, apply_status, cur_dt, money_type);

        return false;
    }

    std::vector<AllTrade::NPMgrCenter::SMoneyDetailInfoPtr> COperationManager::getFundSerial(const UserIDType user_id, const DateType start_day, const DateType end_day)
    {
        if (m_impl)
            return m_impl->getFundSerial(user_id, start_day, end_day);

        return std::vector<AllTrade::NPMgrCenter::SMoneyDetailInfoPtr>();
    }

    void COperationManager::serializeLoginInUser(const AllTrade::NPMgrCenter::SOnlineAccountPtr& online_acc_ptr)
    {
        if (m_impl)
            m_impl->serializeLoginInUser(online_acc_ptr);
    }

    void COperationManager::serializeLoginOutUser(const AllTrade::NPMgrCenter::SOnlineAccountPtr& online_acc_ptr)
    {
        if (m_impl)
            m_impl->serializeLoginOutUser(online_acc_ptr);
    }

    std::string COperationManager::getNewAgentLink()
    {
        if (m_impl)
            return m_impl->getNewAgentLink();
        return "";
    }

    void COperationManager::agencyMoneyChange(const AllTrade::NPMgrCenter::SAgencyMoneyDetailInfoPtr agy_detail)
    {
        if (m_impl)
            return m_impl->agencyMoneyChange(agy_detail);
    }

    bool COperationManager::qryAgencyCommissInfo(const AllTrade::UserIDType user_id, const AllTrade::DateType start_day, const AllTrade::DateType end_day, YDouble& infomatch, YDouble& tradefee, YDouble& comm_all)
    {
        if (m_impl)
            return m_impl->qryAgencyCommissInfo(user_id, start_day, end_day, infomatch, tradefee, comm_all);

        return false;
    }
    
    std::vector<AllTrade::NPMgrCenter::SAgencyMoneyDetailInfoPtr> COperationManager::qryAgencyCommissDtlInfo(const AllTrade::UserIDType user_id, const AllTrade::DateType start_day, const AllTrade::DateType end_day)
    {
        if (m_impl)
            return m_impl->qryAgencyCommissDtlInfo(user_id, start_day, end_day);

        return std::vector<AllTrade::NPMgrCenter::SAgencyMoneyDetailInfoPtr>();
    }

    bool COperationManager::qryAgencyProfitInfo(const AllTrade::UserIDType user_id, const AllTrade::DateType start_day, const AllTrade::DateType end_day, YDouble& profit)
    {
        if (m_impl)
            return m_impl->qryAgencyProfitInfo(user_id, start_day, end_day, profit);

        return false;
    }

    std::vector<AllTrade::NPMgrCenter::SAgencyMoneyDetailInfoPtr> COperationManager::qryAgencyProfitDtlInfo(const AllTrade::UserIDType user_id, const AllTrade::DateType start_day, const AllTrade::DateType end_day)
    {
        if (m_impl)
            return m_impl->qryAgencyProfitDtlInfo(user_id, start_day, end_day);

        return std::vector<AllTrade::NPMgrCenter::SAgencyMoneyDetailInfoPtr>();
    }

#pragma endregion


#pragma region 权限相关操作
ErrorCodeType COperationManager::getRolesUserInfo(const UserIDType userid, std::vector<AuthorityRolesPtr> &vecRolesInfo)
	{
		if (m_impl)
			return m_impl->getRolesUserInfo(userid, vecRolesInfo);

		return -1;
	}

	ErrorCodeType COperationManager::addRolesUserInfo(AuthorityRolesPtr& rolesInfo)
	{
		if (m_impl)
			return m_impl->addRolesUserInfo(rolesInfo);

		return -1;
	}

	ErrorCodeType COperationManager::updateRolesUserInfo(const AuthorityRolesPtr& rolesInfo)
	{
		if (m_impl)
			return m_impl->updateRolesUserInfo(rolesInfo);

		return -1;
	}

	ErrorCodeType COperationManager::deleteRolesUser(int rolesID)
	{
		if (m_impl)
			return m_impl->deleteRolesUser(rolesID);

		return -1;
	}

    ErrorCodeType COperationManager::isHaveAuthority(const AllTrade::LoginNameType loginName, int nFunctionId) const
	{
		if (m_impl)
			return m_impl->isHaveAuthority(loginName, nFunctionId);

		return -1;
	}

    ErrorCodeType COperationManager::getAuthorityRoleUsers(const AllTrade::LoginNameType loginName, std::vector<AllTrade::AuthorityRoleUsersPtr>& vecAuthority)
	{
		if (m_impl)
			return m_impl->getAuthorityRoleUsers(loginName, vecAuthority);

		return -1;
	}

	ErrorCodeType COperationManager::addAuthorityRoleUsers(const std::vector<AllTrade::AuthorityRoleUsersPtr>& vecAuthority)
	{
		if (m_impl)
			return m_impl->addAuthorityRoleUsers(vecAuthority);

		return -1;
	}

	ErrorCodeType COperationManager::deleteAuthorityRoleUsers(const std::vector<AllTrade::AuthorityRoleUsersPtr>& vecAuthority)
	{
		if (m_impl)
			return m_impl->deleteAuthorityRoleUsers(vecAuthority);

		return -1;
	}

	ErrorCodeType COperationManager::judgeRoleUsersRelation(int roleId)
	{
		if (m_impl)
			return m_impl->judgeRoleUsersRelation(roleId);

		return AllTrade::Err_Unknown;
	}

    ErrorCodeType COperationManager::judgeRoleUsersRelation(const AllTrade::LoginNameType loginName, int nRoleId)
	{
		if (m_impl)
			return m_impl->judgeRoleUsersRelation(loginName, nRoleId);

		return -1;

	}

	AllTrade::ErrorCodeType COperationManager::judgeRoleUsersRelation(const AllTrade::LoginNameType loginName)
	{
		if (m_impl)
			return m_impl->judgeRoleUsersRelation(loginName);

		return -1;
	}

	AllTrade::ErrorCodeType COperationManager::changeAuthorityRoleUsers(const AllTrade::AuthorityRoleUsersPtr& ptr)
	{
		if (m_impl)
			return m_impl->changeAuthorityRoleUsers(ptr);

		return -1;
	}


	int COperationManager::getAllAgentHaveRelation(std::set<int>& setInfo, int nRoleId)
	{
		if (m_impl)
			return m_impl->getAllAgentHaveRelation(setInfo, nRoleId);

		return -1;
	}

	ErrorCodeType COperationManager::addAuthorityRoleFunctions(int roleId, const std::vector<AllTrade::AuthorityRoleFunctionsPtr>& vecAuthority)
	{
		if (m_impl)
			return m_impl->addAuthorityRoleFunctions(roleId,vecAuthority);

		return -1;
	}

	ErrorCodeType COperationManager::deleteAuthorityRoleFunctions(const std::vector<AllTrade::AuthorityRoleFunctionsPtr>& vecAuthority)
	{
		if (m_impl)
			return m_impl->deleteAuthorityRoleFunctions(vecAuthority);

		return -1;
	}

	ErrorCodeType COperationManager::getAuthorityRoleFunctionsByRoleId(int roleId, std::vector<AllTrade::AuthorityRoleFunctionsPtr>& vecAuthority)
	{
		if (m_impl)
			return m_impl->getAuthorityRoleFunctionsByRoleId(roleId, vecAuthority);

		return -1;
	}

	ErrorCodeType COperationManager::judgeRoleAndFunctionsRelationOne(int nRoleId)
	{
		if (m_impl)
			return m_impl->judgeRoleAndFunctionsRelationOne(nRoleId);

		return -1;
	}

	int COperationManager::judgeRoleAndFunctionsRelationTwo(int nFunctionID, int nRoleId)
	{
		if (m_impl)
			return m_impl->judgeRoleAndFunctionsRelationTwo(nFunctionID, nRoleId);

		return -1;

	}

	int COperationManager::GetAllAgentInfo(std::map<int, std::set<int>>& mapInfo)
	{
		if (m_impl)
			return m_impl->GetAllAgentInfo(mapInfo);

		return -1;
	}

	int COperationManager::getAllAuthorityRoleFunctions(std::vector<AllTrade::AuthorityRoleFunctionsPtr>& vecAuthority)
	{
		if (m_impl)
			return m_impl->getAllAuthorityRoleFunctions(vecAuthority);

		return -1;
	}
#pragma endregion

#pragma region 交易相关操作
    bool COperationManager::updateOrderInfo(const AllTrade::NPTradeCenter::OrderInfoPtr& order_ptr, const AllTrade::UserIDType user_id)
    {
        if (m_impl)
            return m_impl->updateOrderInfo(order_ptr, user_id);

        return false;
    }


    bool COperationManager::getStockOrderInfo(std::map<AllTrade::PUserIDType, std::vector<AllTrade::NPTradeCenter::StockOrderPtr>>& stockOrder)
	{
		if (m_impl)
			return m_impl->getStockOrderInfo(stockOrder);

		return false;
	}


    std::vector<AllTrade::NPTradeCenter::OrderInfoPtr> COperationManager::getStockOrderHistory(const AllTrade::UserIDType user_id, const AllTrade::DateType start_time, const AllTrade::DateType end_time)
    {
        if (m_impl)
            return m_impl->getStockOrderHistory(user_id, start_time, end_time);

        return std::vector<AllTrade::NPTradeCenter::OrderInfoPtr>();
    }

    std::vector<AllTrade::NPTradeCenter::TradeInfoPtr> COperationManager::getStockTradeHistory(const AllTrade::UserIDType user_id, const AllTrade::DateType start_time, const AllTrade::DateType end_time)
    {
        if (m_impl)
            return m_impl->getStockTradeHistory(user_id, start_time, end_time);

        return std::vector<AllTrade::NPTradeCenter::TradeInfoPtr>();
    }

    bool COperationManager::addTradeRecord(const AllTrade::NPTradeCenter::TradeInfoPtr& trade_ptr, const AllTrade::UserIDType user_id)
    {
        if (m_impl)
            return m_impl->addTradeRecord(trade_ptr, user_id);

        return false;
    }

	bool COperationManager::getStockTradeRecord(std::map<AllTrade::PUserIDType, AllTrade::NPTradeCenter::StockTradePtr>& tradeOrder)
	{
		if (m_impl)
			return m_impl->getStockTradeRecord(tradeOrder);

		return false;
	}

    bool COperationManager::updatePositionInfo(const AllTrade::NPTradeCenter::PositionInfoPtr& position_ptr, const AllTrade::UserIDType user_id)
    {
        if (m_impl)
            return m_impl->updatePositionInfo(position_ptr, user_id);

        return false;
    }

    bool COperationManager::deletePositionInfo(const AllTrade::NPTradeCenter::PositionInfoPtr& position_ptr, const AllTrade::UserIDType user_id)
    {
        if (m_impl)
            return m_impl->deletePositionInfo(position_ptr, user_id);

        return false;
    }

    bool COperationManager::getStockPositionInfo(std::map<AllTrade::PUserIDType, std::vector<AllTrade::NPTradeCenter::StockPositionPtr>>& posiOrder)
	{
		if (m_impl)
			return m_impl->getStockPositionInfo(posiOrder);

		return false;
	}

    bool COperationManager::updateTradeFee(const AllTrade::NPTradeCenter::TradeFeePtr& trade_fee)
    {
        if (m_impl)
            return m_impl->updateTradeFee(trade_fee);

        return false;
    }

    bool COperationManager::getTradeFee(AllTrade::NPTradeCenter::TradeFeePtr& trade_fee)
    {
        if (m_impl)
            return m_impl->getTradeFee(trade_fee);

        return false;
    }

    bool COperationManager::canSettle(const AllTrade::DateTimeType settle_datetime, const AllTrade::DateTimeType cur_datetime)
    {
        if (m_impl)
            return m_impl->canSettle(settle_datetime, cur_datetime);

        return false;
    }

    bool COperationManager::updateSettle(const AllTrade::DateTimeType settle_datetime)
    {
        if (m_impl)
            return m_impl->updateSettle(settle_datetime);

        return false;
    }

    AllTrade::NPTradeCenter::GlobalDataPtr COperationManager::getCurrentGlobalData()
    {
        if (m_impl)
            return m_impl->getCurrentGlobalData();

        return AllTrade::NPTradeCenter::GlobalDataPtr();
    }

    bool COperationManager::updateCurGlobalData(const AllTrade::NPTradeCenter::GlobalDataPtr global_data)
    {
        if (m_impl)
            return m_impl->updateCurGlobalData(global_data);

        return false;
    }

    void COperationManager::updateRiskRecord(const AllTrade::NPTradeCenter::ImmRiskControlPtr risk_cont_st)
    {
        if (m_impl)
            return m_impl->updateRiskRecord(risk_cont_st);
    }

    AllTrade::NPTradeCenter::ImmRiskControlPtr COperationManager::getRiskRecord(const UserIDType user_id, RiskControlType rc_type)
    {
        if (m_impl)
            return m_impl->getRiskRecord(user_id, rc_type);

        return AllTrade::NPTradeCenter::ImmRiskControlPtr();
    }

	bool COperationManager::getRiskRecord(const AllTrade::UserIDType user_id, std::vector<AllTrade::NPTradeCenter::ImmRiskControlPtr>& vecSt)
	{
		if (m_impl)
			return m_impl->getRiskRecord(user_id, vecSt);
		return false;
	}

	bool COperationManager::selectHistoryRiskRecord(const AllTrade::UserIDType user_id, const AllTrade::DateType start_day, const AllTrade::DateType end_day, std::vector<AllTrade::NPTradeCenter::ImmRiskControlPtr>& vecSt)
	{
		if (m_impl)
			return m_impl->selectHistoryRiskRecord(user_id, start_day, end_day, vecSt);
		return false;
	}


    AllTrade::ErrorCodeType COperationManager::getSelfFunctionsByLoginName(const LoginNameType loginName, std::vector<AuthorityFunctionsUserIdPtr> &vecAuthorityFunctions)
	{
		if (m_impl)
			return m_impl->getSelfFunctionsByLoginName(loginName,vecAuthorityFunctions);

		return AllTrade::Err_Unknown;
	}

    ErrorCodeType COperationManager::isHaveRoleName(const AllTrade::LoginNameType roleName)
	{
		if (m_impl)
			return m_impl->isHaveRoleName(roleName);

		return AllTrade::Err_Unknown;;
	}


	AllTrade::ErrorCodeType COperationManager::getAllBussness(std::vector<AuthorityBussnessesPtr>& vec)
	{
		if (m_impl)
			return m_impl->getAllBussness(vec);

		return AllTrade::Err_Unknown;;
	}

#pragma endregion

    void COperationManager::addStockBlackWhite(const ContractIDType code)
    {
        if (m_impl)
            m_impl->addStockBlackWhite(code);
    }

    bool COperationManager::updateStockBlackWhiteStatus(const ContractIDType contract_id, bool isBlack)
    {
        if (m_impl)
            return m_impl->updateStockBlackWhiteStatus(contract_id, isBlack);

        return false;
    }

    std::map<AllTrade::PContractIDType, bool> COperationManager::getAllStockBlackWhiteStatus()
    {
        if (m_impl)
            return m_impl->getAllStockBlackWhiteStatus();

        return std::map<AllTrade::PContractIDType, bool>();
    }

    bool COperationManager::isBlackStock(const ContractIDType contract_id)
    {
        if (m_impl)
            return m_impl->isBlackStock(contract_id);

        return false;
    }

    std::vector<AllTrade::NPTradeCenter::SForbidTradePtr> COperationManager::getAllForbidTradeStatus()
    {
        if (m_impl)
            return m_impl->getAllForbidTradeStatus();

        return std::vector<AllTrade::NPTradeCenter::SForbidTradePtr>();
    }

    bool COperationManager::updateForbidTradeStatus(const AllTrade::NPTradeCenter::SForbidTradePtr& ptr)
    {
        if (m_impl)
            return m_impl->updateForbidTradeStatus(ptr);

        return false;
    }

    std::vector<AllTrade::NPTradeCenter::SPositionRatePtr> COperationManager::getPositionRateStatus()
    {
        if (m_impl)
            return m_impl->getPositionRateStatus();

        return std::vector<AllTrade::NPTradeCenter::SPositionRatePtr>();
    }

    bool COperationManager::updatePositionRateStatus(const AllTrade::NPTradeCenter::SPositionRatePtr& ptr)
    {
        if (m_impl)
            return m_impl->updatePositionRateStatus(ptr);

        return false;
    }

    bool COperationManager::addCustomStock(const AllTrade::UserIDType user_id, const AllTrade::ContractIDType contract_id)
    {
        if (m_impl)
            return m_impl->addCustomStock(user_id, contract_id);

        return false;
    }

    bool COperationManager::removeCustomStock(const AllTrade::UserIDType user_id, const AllTrade::ContractIDType contract_id)
    {
        if (m_impl)
            return m_impl->removeCustomStock(user_id, contract_id);

        return false;
    }

    std::map<AllTrade::PUserIDType, std::vector<AllTrade::PContractIDType>> COperationManager::getAllCustomStock()
    {
        if (m_impl)
            return m_impl->getAllCustomStock();

        return std::map<AllTrade::PUserIDType, std::vector<AllTrade::PContractIDType>>();
    }

    std::vector<AllTrade::PContractIDType> COperationManager::getAllCustomStock(const AllTrade::UserIDType user_id)
    {
        if (m_impl)
            return m_impl->getAllCustomStock(user_id);

        return std::vector<AllTrade::PContractIDType>();
    }


	bool COperationManager::getMarginPositionInfo(std::map<AllTrade::PUserIDType, std::vector<AllTrade::NPTradeCenter::MarginPositionInfoPtr>>& posiOrder)
	{
		if (m_impl)
			return m_impl->getMarginPositionInfo(posiOrder);

		return false;
	}

	//bool COperationManager::updateMarginTradeTable(const AllTrade::NPTradeCenter::MarginTradeInfoPtr& ptr)
	//{
	//	if (m_impl)
	//		return m_impl->updateMarginTradeTable(ptr);

	//	return false;
	//}

	bool COperationManager::getMarginTradeRecord(std::map<AllTrade::PUserIDType, AllTrade::NPTradeCenter::MarginTradeInfoPtr>& tradeOrder)
	{
		if (m_impl)
			return m_impl->getMarginTradeRecord(tradeOrder);

		return false;
	}

	std::vector<AllTrade::NPTradeCenter::MarginTradeInfoPtr> COperationManager::getMarginTradeHistory(const AllTrade::UserIDType user_id, const AllTrade::DateType start_time, const AllTrade::DateType end_time)
	{
		if (m_impl)
			return m_impl->getMarginTradeHistory(user_id, start_time, end_time);

		return std::vector<AllTrade::NPTradeCenter::MarginTradeInfoPtr>();
	}

// 	bool COperationManager::updateMarginOrderTable(const AllTrade::NPTradeCenter::MarginOrderInfoPtr& ptr)
// 	{
// 		if (m_impl)
// 			return m_impl->updateMarginOrderTable(ptr);
// 
// 		return false;
// 	}

	bool COperationManager::getMarginOrderInfo(std::map<AllTrade::PUserIDType, std::vector<AllTrade::NPTradeCenter::MarginOrderInfoPtr>>& marginOrder)
	{
		if (m_impl)
			return m_impl->getMarginOrderInfo(marginOrder);

		return false;
	}

	std::vector<AllTrade::NPTradeCenter::MarginOrderInfoPtr> COperationManager::getAllMarginOrderHistory(const AllTrade::UserIDType user_id, const AllTrade::DateType start_time, const AllTrade::DateType end_time)
	{
		if (m_impl)
			return m_impl->getAllMarginOrderHistory(user_id, start_time, end_time);

		return std::vector<AllTrade::NPTradeCenter::MarginOrderInfoPtr>();
	}


	bool COperationManager::updateMarginInfoTable(const AllTrade::NPTradeCenter::MarginInfoPtr& ptr)
	{
		if (m_impl)
			return m_impl->updateMarginInfoTable(ptr);

		return false;
	}

	bool COperationManager::getAllMarginInfo(const AllTrade::NPTradeCenter::MarginInfoPtr& ptr)
	{
		if (m_impl)
			return m_impl->getAllMarginInfo(ptr);

		return false;
	}

	bool COperationManager::updateMarginLeftTable(const AllTrade::NPTradeCenter::MarginLeftInfoPtr& ptr)
	{
		if (m_impl)
			return m_impl->updateMarginLeftTable(ptr);

		return false;
	}

	bool COperationManager::getMarginLeftTable(const AllTrade::NPTradeCenter::MarginLeftInfoPtr& ptr)
	{
		if (m_impl)
			return m_impl->getMarginLeftTable(ptr);

		return false;
	}

	bool COperationManager::getInterestStatisticsTable(const AllTrade::UserIDType user_id, AllTrade::NPMgrCenter::InterestStatisticsPtr& rstInfo)
	{
		if (m_impl)
			return m_impl->getInterestStatisticsTable(user_id, rstInfo);

		return false;
	}

	bool COperationManager::updateInterestStatisticsTable(AllTrade::NPMgrCenter::InterestStatisticsPtr& ptrInfo)
	{
		if (m_impl)
			return m_impl->updateInterestStatisticsTable(ptrInfo);

		return false;
	}

	bool COperationManager::getInterestDetailTable(const AllTrade::UserIDType user_id, std::vector<AllTrade::NPMgrCenter::InterestDetailPtr>& rstInfo)
	{
		if (m_impl)
			return m_impl->getInterestDetailTable(user_id, rstInfo);

		return false;
	}

	bool COperationManager::updateInterestDetailTable(AllTrade::NPMgrCenter::InterestDetailPtr& ptrInfo)
	{
		if (m_impl)
			return m_impl->updateInterestDetailTable(ptrInfo);

		return false;
	}

}