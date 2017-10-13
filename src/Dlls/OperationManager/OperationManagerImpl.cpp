#include "stdafx.h"
#include "OperationManagerImpl.h"
#include "include/DBAccess/db_access.h"
#include "DBOpManagerCenter.h"
#include "AuthorityControl.h"
#include "DBOpTradeCenter.h"
#include "define/protocol_error.h"

using namespace AllTrade;
using namespace AllTrade::NPTradeCenter;
using namespace AllTrade::NPMgrCenter;

namespace OperationManager
{
	COperationManagerImpl::COperationManagerImpl()
        : m_mgr_center(NULL)
		, m_authorityControl(nullptr)
	{
        m_mgr_center = new DBOpManagerCenter;
		m_authorityControl = new CAuthorityControl;
        m_trade_center = new DBOpTradeCenter;
	}


	COperationManagerImpl::~COperationManagerImpl()
	{
        if (m_mgr_center)
		{
            delete m_mgr_center;
            m_mgr_center = nullptr;
		}

		if (m_authorityControl)
		{
			delete m_authorityControl;
			m_authorityControl = nullptr;
		}

        if (m_trade_center)
        {
            delete m_trade_center;
            m_trade_center = nullptr;
        }
    }

    bool COperationManagerImpl::initialize()
    {
        if (0 != DBAccess::InitDB())
            return false;

        bool bTradeCenter(false), bAuthority(false), bMgrCenter(false);
 
        if (m_trade_center)
            bTradeCenter = m_trade_center->initAllTable();

		if (m_authorityControl)
			bAuthority = m_authorityControl->initAllTable();

        if (m_mgr_center)
            bMgrCenter = m_mgr_center->initAllTable();

        return bTradeCenter && bAuthority && bMgrCenter;
    }

#pragma region 用户与交易所管理相关操作

    bool COperationManagerImpl::getRootAccount(AllTrade::NPMgrCenter::RootAccountPtr& root_ptr)
    {
        if (m_mgr_center)
            return m_mgr_center->getRootAccount(root_ptr);

        return false;
    }

    bool COperationManagerImpl::getAllDirectChildren(std::vector<AllTrade::NPMgrCenter::SAccountPtr>& children, const AllTrade::NPMgrCenter::SAccountPtr& account_ptr)
    {
        if (m_mgr_center)
            return m_mgr_center->getAllDirectChildren(children, account_ptr);

        return false;
    }

    bool COperationManagerImpl::getMonitChildren(std::vector<AllTrade::NPMgrCenter::SAccountPtr>& children, const AllTrade::NPMgrCenter::SAccountPtr& account_ptr)
    {
        if (m_mgr_center)
            return m_mgr_center->getMonitChildren(children, account_ptr);

        return false;
    }

    bool COperationManagerImpl::getTradeChildren(std::vector<AllTrade::NPMgrCenter::SAccountPtr>& children, const AllTrade::NPMgrCenter::SAccountPtr& account_ptr)
    {
        if (m_mgr_center)
            return m_mgr_center->getTradeChildren(children, account_ptr);

        return false;
    }

    bool COperationManagerImpl::getFunderChildren(std::vector<AllTrade::NPMgrCenter::SAccountPtr>& children, const AllTrade::NPMgrCenter::SAccountPtr& account_ptr)
    {
        if (m_mgr_center)
            return m_mgr_center->getFunderChildren(children, account_ptr);

        return false;
    }

    bool COperationManagerImpl::getUserMoneyInfo(const AllTrade::UserIDType user_id, AllTrade::NPMgrCenter::SMoneyInfoPtr& money_info)
    {
        if (m_mgr_center)
            return m_mgr_center->getUserMoneyInfo(user_id, money_info);

        return false;
    }

    bool COperationManagerImpl::getUserRiskInfo(const UserIDType user_id, AllTrade::NPMgrCenter::SRiskInfoPtr& risk_info)
    {
        if (m_mgr_center)
            return m_mgr_center->getUserRiskInfo(user_id, risk_info);

        return false;
    }

    bool COperationManagerImpl::getAllExchange(std::vector<AllTrade::NPMgrCenter::SExchangePtr>& exchanges)
    {
        if (m_mgr_center)
            return m_mgr_center->getAllExchange(exchanges);

        return false;
    }

    bool COperationManagerImpl::getStockAllContract(std::vector<AllTrade::NPMgrCenter::SStockContractPtr>& contract_vec, const ExchangeIDType exchange_id)
    {
        if (m_mgr_center)
            return m_mgr_center->getStockAllContract(contract_vec, exchange_id);

        return false;
    }

    bool COperationManagerImpl::updateUserInfo(const AllTrade::NPMgrCenter::SAccountPtr& account_ptr)
    {
        if (m_mgr_center)
            return m_mgr_center->updateUserInfo(account_ptr);

        return false;
    }

    bool COperationManagerImpl::updateExchangeInfo(const AllTrade::NPMgrCenter::SExchangePtr& exchange_ptr)
    {
        if (m_mgr_center)
            return m_mgr_center->updateExchangeInfo(exchange_ptr);

        return false;
    }

    bool COperationManagerImpl::updateContractInfo(const AllTrade::NPMgrCenter::SContractPtr& contract_ptr)
    {
        if (m_mgr_center)
            return m_mgr_center->updateContractInfo(contract_ptr);
 
        return false;
    }

    bool COperationManagerImpl::updateUserMoneyDetailInfo(const AllTrade::UserIDType user_id, const AllTrade::NPMgrCenter::SMoneyDetailInfoPtr& money_info)
    {
        if (m_mgr_center)
            return m_mgr_center->updateUserMoneyDetailInfo(user_id, money_info);

        return false;
    }

    bool COperationManagerImpl::updateUserMoneyInfo(const AllTrade::UserIDType user_id, const AllTrade::NPMgrCenter::SMoneyInfoPtr& money_info)
    {
        if (m_mgr_center)
            return m_mgr_center->updateUserMoneyInfo(user_id, money_info);

        return false;
    }

    bool COperationManagerImpl::updateUserRiskInfo(const UserIDType user_id, const AllTrade::NPMgrCenter::SRiskInfoPtr& risk_info)
    {
        if (m_mgr_center)
            return m_mgr_center->updateUserRiskInfo(user_id, risk_info);

        return false;
    }

    bool COperationManagerImpl::qryApplyMoney(std::vector<SApplyMoneyPtr>& apply_infos, const UserIDType user_id, const DateType start_day, const DateType end_day, AllTrade::OIMM_Change_Type money_type)
    {
        if (m_mgr_center)
            return m_mgr_center->qryApplyMoney(apply_infos, user_id, start_day, end_day, money_type);

        return false;
    }

    AllTrade::NPMgrCenter::SApplyMoneyPtr COperationManagerImpl::getApplyMoneyPtr(const AllTrade::ApplyMoneyIDType apply_money_id, AllTrade::OIMM_Change_Type type)
    {
        if (m_mgr_center)
            return m_mgr_center->getApplyMoneyPtr(apply_money_id, type);

        return SApplyMoneyPtr();
    }

    bool COperationManagerImpl::applyMoney(const SApplyMoneyPtr& apply_info)
    {
        if (m_mgr_center)
            return m_mgr_center->applyMoney(apply_info);

        return false;
    }

    bool COperationManagerImpl::approvalApplyMoney(const AllTrade::UserIDType approval_user_id, const AllTrade::ApplyMoneyIDType apply_money_id, AllTrade::E_APPLY_MONEY_STATUS apply_status, const AllTrade::DateTimeType cur_dt, AllTrade::OIMM_Change_Type money_type)
    {
        if (m_mgr_center)
            return m_mgr_center->approvalApplyMoney(approval_user_id, apply_money_id, apply_status, cur_dt, money_type);

        return false;
    }

    std::vector<AllTrade::NPMgrCenter::SMoneyDetailInfoPtr> COperationManagerImpl::getFundSerial(const UserIDType user_id, const DateType start_day, const DateType end_day)
    {
        if (m_mgr_center)
            return m_mgr_center->getFundSerial(user_id, start_day, end_day);

        return std::vector<AllTrade::NPMgrCenter::SMoneyDetailInfoPtr>();
    }

    void COperationManagerImpl::serializeLoginInUser(const AllTrade::NPMgrCenter::SOnlineAccountPtr& online_acc_ptr)
    {
        if (m_mgr_center)
            m_mgr_center->serializeLoginInUser(online_acc_ptr);
    }

    void COperationManagerImpl::serializeLoginOutUser(const AllTrade::NPMgrCenter::SOnlineAccountPtr& online_acc_ptr)
    {
        if (m_mgr_center)
            m_mgr_center->serializeLoginOutUser(online_acc_ptr);
    }

    std::string COperationManagerImpl::getNewAgentLink()
    {
        if (m_mgr_center)
            return m_mgr_center->getNewAgentLink();
        return "";
    }

    void COperationManagerImpl::agencyMoneyChange(const AllTrade::NPMgrCenter::SAgencyMoneyDetailInfoPtr agy_detail)
    {
        if (m_mgr_center)
            return m_mgr_center->agencyMoneyChange(agy_detail);
    }

    bool COperationManagerImpl::qryAgencyCommissInfo(const AllTrade::UserIDType user_id, const AllTrade::DateType start_day, const AllTrade::DateType end_day, YDouble& infomatch, YDouble& tradefee, YDouble& comm_all)
    {
        if (m_mgr_center)
            return m_mgr_center->qryAgencyCommissInfo(user_id, start_day, end_day, infomatch, tradefee, comm_all);

        return false;
    }

    std::vector<AllTrade::NPMgrCenter::SAgencyMoneyDetailInfoPtr> COperationManagerImpl::qryAgencyCommissDtlInfo(const AllTrade::UserIDType user_id, const AllTrade::DateType start_day, const AllTrade::DateType end_day)
    {
        if (m_mgr_center)
            return m_mgr_center->qryAgencyCommissDtlInfo(user_id, start_day, end_day);

        return std::vector<AllTrade::NPMgrCenter::SAgencyMoneyDetailInfoPtr>();
    }

    bool COperationManagerImpl::qryAgencyProfitInfo(const AllTrade::UserIDType user_id, const AllTrade::DateType start_day, const AllTrade::DateType end_day, YDouble& profit)
    {
        if (m_mgr_center)
            return m_mgr_center->qryAgencyProfitInfo(user_id, start_day, end_day, profit);

        return false;
    }

    std::vector<AllTrade::NPMgrCenter::SAgencyMoneyDetailInfoPtr> COperationManagerImpl::qryAgencyProfitDtlInfo(const AllTrade::UserIDType user_id, const AllTrade::DateType start_day, const AllTrade::DateType end_day)
    {
        if (m_mgr_center)
            return m_mgr_center->qryAgencyProfitDtlInfo(user_id, start_day, end_day);

        return std::vector<AllTrade::NPMgrCenter::SAgencyMoneyDetailInfoPtr>();
    }

#pragma endregion

#pragma region 权限相关操作        
ErrorCodeType COperationManagerImpl::getRolesUserInfo(const UserIDType userid, std::vector<AuthorityRolesPtr> &vecRolesInfo)
	{
		if (m_authorityControl)
			return m_authorityControl->getRolesUserInfo(userid, vecRolesInfo);
		
		return -1;
	}

	ErrorCodeType COperationManagerImpl::addRolesUserInfo(AuthorityRolesPtr& rolesInfo)
	{
		if (m_authorityControl)
			return m_authorityControl->addRolesUserInfo(rolesInfo);

		return -1;
	}

	ErrorCodeType COperationManagerImpl::updateRolesUserInfo(const AuthorityRolesPtr& rolesInfo)
	{
		if (m_authorityControl)
			return m_authorityControl->updateRolesUserInfo(rolesInfo);

		return -1;
	}

	ErrorCodeType COperationManagerImpl::deleteRolesUser(int rolesID)
	{
		if (m_authorityControl)
			return m_authorityControl->deleteRolesUser(rolesID);

		return AllTrade::Err_Unknown;
	}

    ErrorCodeType COperationManagerImpl::isHaveRoleName(const AllTrade::LoginNameType roleName)
	{
		if (m_authorityControl)
			return m_authorityControl->isHaveRoleName(roleName);

		return -1;
	}

    ErrorCodeType COperationManagerImpl::isHaveAuthority(const AllTrade::LoginNameType loginName, int nFunctionId) const
	{
		if (m_authorityControl)
			return m_authorityControl->isHaveAuthority(loginName, nFunctionId);

		return -1;
	}

    ErrorCodeType COperationManagerImpl::getAuthorityRoleUsers(const AllTrade::LoginNameType loginName, std::vector<AllTrade::AuthorityRoleUsersPtr>& vecAuthority)
	{
		if (m_authorityControl)
			return m_authorityControl->getAuthorityRoleUsers(loginName, vecAuthority);

		return -1;
	}

	ErrorCodeType COperationManagerImpl::addAuthorityRoleUsers(const std::vector<AllTrade::AuthorityRoleUsersPtr>& vecAuthority)
	{
		if (m_authorityControl)
			return m_authorityControl->addAuthorityRoleUsers(vecAuthority);

		return -1;
	}

	ErrorCodeType COperationManagerImpl::deleteAuthorityRoleUsers(const std::vector<AllTrade::AuthorityRoleUsersPtr>& vecAuthority)
	{
		if (m_authorityControl)
			return m_authorityControl->deleteAuthorityRoleUsers(vecAuthority);

		return -1;
	}

	ErrorCodeType COperationManagerImpl::judgeRoleUsersRelation(int roleId)
	{
		if (m_authorityControl)
			return  m_authorityControl->judgeRoleUsersRelation(roleId);

		return AllTrade::Err_Unknown;
	}

    ErrorCodeType COperationManagerImpl::judgeRoleUsersRelation(const AllTrade::LoginNameType loginName, int nRoleId)
	{
		if (m_authorityControl)
			return m_authorityControl->judgeRoleUsersRelation(loginName, nRoleId);

		return -1;
	}

	AllTrade::ErrorCodeType COperationManagerImpl::judgeRoleUsersRelation(const AllTrade::LoginNameType loginName)
	{
		if (m_authorityControl)
			return m_authorityControl->judgeRoleUsersRelation(loginName);

		return -1;
	}

	AllTrade::ErrorCodeType COperationManagerImpl::changeAuthorityRoleUsers(const AllTrade::AuthorityRoleUsersPtr& ptr)
	{
		if (m_authorityControl)
			return m_authorityControl->changeAuthorityRoleUsers(ptr);

		return -1;
	}

	int COperationManagerImpl::getAllAgentHaveRelation(std::set<int>& setInfo, int nRoleId)
	{
		if (m_authorityControl)
			return m_authorityControl->getAllAgentHaveRelation(setInfo, nRoleId);

		return -1;
	}

	ErrorCodeType COperationManagerImpl::addAuthorityRoleFunctions(int roleId, const std::vector<AllTrade::AuthorityRoleFunctionsPtr>& vecAuthority)
	{
		if (m_authorityControl)
			return m_authorityControl->addAuthorityRoleFunctions(roleId,vecAuthority);

		return -1;
	}

	ErrorCodeType COperationManagerImpl::deleteAuthorityRoleFunctions(const std::vector<AllTrade::AuthorityRoleFunctionsPtr>& vecAuthority)
	{
		if (m_authorityControl)
			return m_authorityControl->deleteAuthorityRoleFunctions(vecAuthority);

		return -1;
	}

	ErrorCodeType COperationManagerImpl::getAuthorityRoleFunctionsByRoleId(int roleId, std::vector<AllTrade::AuthorityRoleFunctionsPtr>& vecAuthority)
	{
		if (m_authorityControl)
			return m_authorityControl->getAuthorityRoleFunctionsByRoleId(roleId,vecAuthority);

		return -1;
	}

	ErrorCodeType COperationManagerImpl::judgeRoleAndFunctionsRelationOne(int nRoleId)
	{
		if (m_authorityControl)
			return m_authorityControl->judgeRoleAndFunctionsRelationOne( nRoleId);

		
		return -1;
	}

	int COperationManagerImpl::judgeRoleAndFunctionsRelationTwo(int nFunctionID, int nRoleId)
	{
		int nCount(0);
		int errorDb(0);
		if (m_authorityControl)
			errorDb = m_authorityControl->judgeRoleAndFunctionsRelationTwo(nFunctionID, nRoleId, &nCount);

		if (errorDb)
			return errorDb;
		if (nCount)
			return 0;

		return -1;
	}

	int COperationManagerImpl::getAllAuthorityRoleFunctions(std::vector<AllTrade::AuthorityRoleFunctionsPtr>& vecAuthority)
	{
		if (m_authorityControl)
			return m_authorityControl->getAllAuthorityRoleFunctions(vecAuthority);

		return -1;
	}

	int COperationManagerImpl::GetAllAgentInfo(std::map<int, std::set<int>>& mapInfo)
	{
		if (m_authorityControl)
			return m_authorityControl->GetAllAgentInfo(mapInfo);

		return -1;
	}

	AllTrade::ErrorCodeType COperationManagerImpl::getSelfFunctionsByLoginName(const LoginNameType loginName, std::vector<AuthorityFunctionsUserIdPtr> &vecAuthorityFunctions)
	{
		if (m_authorityControl)
			return m_authorityControl->getSelfFunctionsByLoginName(loginName,vecAuthorityFunctions);

		return -1;
	}

	AllTrade::ErrorCodeType COperationManagerImpl::getAllBussness(std::vector<AuthorityBussnessesPtr>& vec)
	{
		if (m_authorityControl)
			return m_authorityControl->getAllBussness(vec);

		return -1;
	}

#pragma endregion

#pragma region 交易相关操作
    bool COperationManagerImpl::updateOrderInfo(const AllTrade::NPTradeCenter::OrderInfoPtr& order_ptr, const AllTrade::UserIDType user_id)
    {
        if (m_trade_center)
            return m_trade_center->updateOrderInfo(order_ptr, user_id);

        return false;
    }

    bool COperationManagerImpl::getStockOrderInfo(std::map<AllTrade::PUserIDType, std::vector<AllTrade::NPTradeCenter::StockOrderPtr>>& stockOrder)
	{
		if (m_trade_center)
			return m_trade_center->getStockOrderInfo(stockOrder);

		return false;
	}

    std::vector<AllTrade::NPTradeCenter::OrderInfoPtr> COperationManagerImpl::getStockOrderHistory(const AllTrade::UserIDType user_id, const AllTrade::DateType start_time, const AllTrade::DateType end_time)
    {
        if (m_trade_center)
            return m_trade_center->getStockOrderHistory(user_id, start_time, end_time);

        return std::vector<AllTrade::NPTradeCenter::OrderInfoPtr>();
    }

    std::vector<AllTrade::NPTradeCenter::TradeInfoPtr> COperationManagerImpl::getStockTradeHistory(const AllTrade::UserIDType user_id, const AllTrade::DateType start_time, const AllTrade::DateType end_time)
    {
        if (m_trade_center)
            return m_trade_center->getStockTradeHistory(user_id, start_time, end_time);

        return std::vector<AllTrade::NPTradeCenter::TradeInfoPtr>();
    }

    bool COperationManagerImpl::addTradeRecord(const AllTrade::NPTradeCenter::TradeInfoPtr& trade_ptr, const AllTrade::UserIDType user_id)
    {
        if (m_trade_center)
            return m_trade_center->addTradeRecord(trade_ptr, user_id);

        return false;
    }

	bool COperationManagerImpl::getStockTradeRecord(std::map<AllTrade::PUserIDType, AllTrade::NPTradeCenter::StockTradePtr>& tradeOrder)
	{
		if (m_trade_center)
			return m_trade_center->getStockTradeRecord(tradeOrder);

		return false;
	}

    bool COperationManagerImpl::updatePositionInfo(const AllTrade::NPTradeCenter::PositionInfoPtr& position_ptr, const AllTrade::UserIDType user_id)
    {
        if (m_trade_center)
            return m_trade_center->updatePositionInfo(position_ptr, user_id);

        return false;
    }

    bool COperationManagerImpl::deletePositionInfo(const AllTrade::NPTradeCenter::PositionInfoPtr& position_ptr, const AllTrade::UserIDType user_id)
    {
        if (m_trade_center)
            return m_trade_center->deletePositionInfo(position_ptr, user_id);

        return false;
    }

    bool COperationManagerImpl::getStockPositionInfo(std::map<AllTrade::PUserIDType, std::vector<AllTrade::NPTradeCenter::StockPositionPtr>>& posiOrder)
	{
		if (m_trade_center)
			return m_trade_center->getStockPositionInfo(posiOrder);

		return false;
	}

    bool COperationManagerImpl::updateTradeFee(const AllTrade::NPTradeCenter::TradeFeePtr& trade_fee)
    {
        if (m_trade_center)
            return m_trade_center->updateTradeFee(trade_fee);

        return false;
    }

    bool COperationManagerImpl::getTradeFee(AllTrade::NPTradeCenter::TradeFeePtr& trade_fee)
    {
        if (m_trade_center)
            return m_trade_center->getTradeFee(trade_fee);

        return false;
    }

    bool COperationManagerImpl::canSettle(const AllTrade::DateTimeType settle_datetime, const AllTrade::DateTimeType cur_datetime)
    {
        if (m_trade_center)
            return m_trade_center->canSettle(settle_datetime, cur_datetime);

        return false;

    }

    bool COperationManagerImpl::updateSettle(const AllTrade::DateTimeType settle_datetime)
    {
        if (m_trade_center)
            return m_trade_center->updateSettle(settle_datetime);

        return false;
    }

    AllTrade::NPTradeCenter::GlobalDataPtr COperationManagerImpl::getCurrentGlobalData()
    {
        if (m_trade_center)
            return m_trade_center->getCurrentGlobalData();

        return AllTrade::NPTradeCenter::GlobalDataPtr();
    }

    bool COperationManagerImpl::updateCurGlobalData(const AllTrade::NPTradeCenter::GlobalDataPtr global_data)
    {
        if (m_trade_center)
            return m_trade_center->updateCurGlobalData(global_data);

        return false;
    }

    void COperationManagerImpl::updateRiskRecord(const AllTrade::NPTradeCenter::ImmRiskControlPtr risk_cont_st)
    {
        if (m_trade_center)
            return m_trade_center->updateRiskRecord(risk_cont_st);
    }

    AllTrade::NPTradeCenter::ImmRiskControlPtr COperationManagerImpl::getRiskRecord(const UserIDType user_id, RiskControlType rc_type)
    {
        if (m_trade_center)
            return m_trade_center->getRiskRecord(user_id, rc_type);

        return AllTrade::NPTradeCenter::ImmRiskControlPtr();
    }

	bool COperationManagerImpl::getRiskRecord(const AllTrade::UserIDType user_id, std::vector<AllTrade::NPTradeCenter::ImmRiskControlPtr>& vecSt)
	{
		if (m_trade_center)
			return m_trade_center->getRiskRecord(user_id, vecSt);

		return false;
	}

	bool COperationManagerImpl::selectHistoryRiskRecord(const AllTrade::UserIDType user_id, const AllTrade::DateType start_day, const AllTrade::DateType end_day, std::vector<AllTrade::NPTradeCenter::ImmRiskControlPtr>& vecSt)
	{
		if (m_trade_center)
			return m_trade_center->selectHistoryRiskRecord(user_id, start_day, end_day, vecSt);

		return false;
	}

#pragma endregion

    void COperationManagerImpl::addStockBlackWhite(const ContractIDType contract_id)
    {
        if (m_trade_center)
            m_trade_center->addStockBlackWhite(contract_id);
    }

    bool COperationManagerImpl::updateStockBlackWhiteStatus(const ContractIDType contract_id, bool isBlack)
    {
        if (m_trade_center)
            return m_trade_center->updateStockBlackWhiteStatus(contract_id, isBlack);

        return false;
    }

    std::map<AllTrade::PContractIDType, bool> COperationManagerImpl::getAllStockBlackWhiteStatus()
    {
        if (m_trade_center)
            return m_trade_center->getAllStockBlackWhiteStatus();

        return std::map<AllTrade::PContractIDType, bool>();
    }

    bool COperationManagerImpl::isBlackStock(const ContractIDType contract_id)
    {
        if (m_trade_center)
            return m_trade_center->isBlackStock(contract_id);

        return false;
    }

    std::vector<AllTrade::NPTradeCenter::SForbidTradePtr> COperationManagerImpl::getAllForbidTradeStatus()
    {
        if (m_trade_center)
            return m_trade_center->getAllForbidTradeStatus();

        return std::vector<AllTrade::NPTradeCenter::SForbidTradePtr>();
    }

    bool COperationManagerImpl::updateForbidTradeStatus(const AllTrade::NPTradeCenter::SForbidTradePtr& ptr)
    {
        if (m_trade_center)
            return m_trade_center->updateForbidTradeStatus(ptr);

        return false;
    }

    std::vector<AllTrade::NPTradeCenter::SPositionRatePtr> COperationManagerImpl::getPositionRateStatus()
    {
        if (m_trade_center)
            return m_trade_center->getPositionRateStatus();

        return std::vector<AllTrade::NPTradeCenter::SPositionRatePtr>();
    }

    bool COperationManagerImpl::updatePositionRateStatus(const AllTrade::NPTradeCenter::SPositionRatePtr& ptr)
    {
        if (m_trade_center)
            return m_trade_center->updatePositionRateStatus(ptr);

        return false;
    }

    bool COperationManagerImpl::addCustomStock(const AllTrade::UserIDType user_id, const AllTrade::ContractIDType contract_id)
    {
        if (m_mgr_center)
            return m_mgr_center->addCustomStock(user_id, contract_id);

        return false;
    }

    bool COperationManagerImpl::removeCustomStock(const AllTrade::UserIDType user_id, const AllTrade::ContractIDType contract_id)
    {
        if (m_mgr_center)
            return m_mgr_center->removeCustomStock(user_id, contract_id);

        return false;
    }

    std::map<AllTrade::PUserIDType, std::vector<AllTrade::PContractIDType>> COperationManagerImpl::getAllCustomStock()
    {
        if (m_mgr_center)
            return m_mgr_center->getAllCustomStock();

        return std::map<AllTrade::PUserIDType, std::vector<AllTrade::PContractIDType>>();
    }

    std::vector<AllTrade::PContractIDType> COperationManagerImpl::getAllCustomStock(const AllTrade::UserIDType user_id)
    {
        if (m_mgr_center)
            return m_mgr_center->getAllCustomStock(user_id);

        return std::vector<AllTrade::PContractIDType>();
    }

	/*bool COperationManagerImpl::updateMarginPositionTable(const AllTrade::NPTradeCenter::MarginPositionInfoPtr& ptr)
	{
		if (m_trade_center)
			return m_trade_center->updateMarginPositionTable(ptr);

		return false;
	}*/

	bool COperationManagerImpl::getMarginPositionInfo(std::map<AllTrade::PUserIDType, std::vector<AllTrade::NPTradeCenter::MarginPositionInfoPtr>>& posiOrder)
	{
		if (m_trade_center)
			return m_trade_center->getMarginPositionInfo(posiOrder);

		return false;
	}

	/*bool COperationManagerImpl::updateMarginTradeTable(const AllTrade::NPTradeCenter::MarginTradeInfoPtr& ptr)
	{
		if (m_trade_center)
			return m_trade_center->updateMarginTradeTable(ptr);

		return false;
	}*/

	bool COperationManagerImpl::getMarginTradeRecord(std::map<AllTrade::PUserIDType, AllTrade::NPTradeCenter::MarginTradeInfoPtr>& tradeOrder)
	{
		if (m_trade_center)
			return m_trade_center->getMarginTradeRecord(tradeOrder);

		return false;
	}

	std::vector<AllTrade::NPTradeCenter::MarginTradeInfoPtr> COperationManagerImpl::getMarginTradeHistory(const AllTrade::UserIDType user_id, const AllTrade::DateType start_time, const AllTrade::DateType end_time)
	{

		if (m_trade_center)
			return m_trade_center->getMarginTradeHistory(user_id, start_time, end_time);

		return std::vector<AllTrade::NPTradeCenter::MarginTradeInfoPtr>();
	}

// 	bool COperationManagerImpl::updateMarginOrderTable(const AllTrade::NPTradeCenter::MarginOrderInfoPtr& ptr)
// 	{
// 		if (m_trade_center)
// 			return m_trade_center->updateMarginOrderTable(ptr);
// 
// 		return false;
// 	}


	bool COperationManagerImpl::getMarginOrderInfo(std::map<AllTrade::PUserIDType, std::vector<AllTrade::NPTradeCenter::MarginOrderInfoPtr>>& marginOrder)
	{
		if (m_trade_center)
			return m_trade_center->getMarginOrderInfo(marginOrder);

		return false;

	}

	std::vector<AllTrade::NPTradeCenter::MarginOrderInfoPtr> COperationManagerImpl::getAllMarginOrderHistory(const AllTrade::UserIDType user_id, const AllTrade::DateType start_time, const AllTrade::DateType end_time)
	{
		if (m_trade_center)
			return m_trade_center->getAllMarginOrderHistory(user_id, start_time,end_time);

		return std::vector<AllTrade::NPTradeCenter::MarginOrderInfoPtr>();
	}

	bool COperationManagerImpl::updateMarginInfoTable(const AllTrade::NPTradeCenter::MarginInfoPtr& ptr)
	{
		if (m_trade_center)
			return m_trade_center->updateMarginInfoTable(ptr);

		return false;
	}

	bool COperationManagerImpl::getAllMarginInfo(const AllTrade::NPTradeCenter::MarginInfoPtr& ptr)
	{
		if (m_trade_center)
			return m_trade_center->getAllMarginInfo(ptr);

		return false;
	}

	bool COperationManagerImpl::updateMarginLeftTable(const AllTrade::NPTradeCenter::MarginLeftInfoPtr& ptr)
	{

		if (m_trade_center)
			return m_trade_center->updateMarginLeftTable(ptr);

		return false;
	}

	bool COperationManagerImpl::getMarginLeftTable(const AllTrade::NPTradeCenter::MarginLeftInfoPtr& ptr)
	{
		if (m_trade_center)
			return m_trade_center->getMarginLeftTable(ptr);

		return false;
	}

	bool COperationManagerImpl::getInterestStatisticsTable(const AllTrade::UserIDType user_id, AllTrade::NPMgrCenter::InterestStatisticsPtr& rstInfo)
	{
		if (m_trade_center)
			return m_mgr_center->getInterestStatisticsTable(user_id, rstInfo);

		return false;
	}

	bool COperationManagerImpl::updateInterestStatisticsTable(AllTrade::NPMgrCenter::InterestStatisticsPtr& ptrInfo)
	{
		if (m_trade_center)
			return m_mgr_center->updateInterestStatisticsTable(ptrInfo);

		return false;
	}

	bool COperationManagerImpl::getInterestDetailTable(const AllTrade::UserIDType user_id, std::vector<AllTrade::NPMgrCenter::InterestDetailPtr>& rstInfo)
	{
		if (m_trade_center)
			return m_mgr_center->getInterestDetailTable(user_id, rstInfo);

		return false;
	}

	bool COperationManagerImpl::updateInterestDetailTable(AllTrade::NPMgrCenter::InterestDetailPtr& ptrInfo)
	{
		if (m_trade_center)
			return m_mgr_center->updateInterestDetailTable(ptrInfo);

		return false;
	}

}