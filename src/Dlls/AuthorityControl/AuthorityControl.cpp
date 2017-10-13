#include "AuthorityControl/AuthorityControl.h"
#include "AuthorityControlImpl.h"
#include "define/protocol_error.h"

namespace AuthorityControl
{
	CAuthorityControl::CAuthorityControl()
		: m_authorityImpl(new CAuthorityControlImpl)
	{
	}

	CAuthorityControl::~CAuthorityControl()
	{
		if (m_authorityImpl)
		{
			delete m_authorityImpl;
			m_authorityImpl = nullptr;
		}
	}

	bool CAuthorityControl::isHaveOnLineUserAuthority(const AllTrade::LoginNameType loginName) const
	{
		bool bExitFlag(false);

		if (isHaveAuthority(loginName, AccountMangerColumn::AMC_OnlineQuery) == Error_UserAndFunction_Exist)
			bExitFlag = true;
		
		return bExitFlag;
	}



	ErrorCodeType CAuthorityControl::getRolesUserInfo(const UserIDType userid, std::vector<AllTrade::AuthorityRolesPtr>& vecRolesInfo)
	{
		std::lock_guard<std::recursive_mutex> lock(mtx_roles);
		if (m_authorityImpl)
			return m_authorityImpl->getRolesUserInfo(userid, vecRolesInfo);

		return -1;
	}

	ErrorCodeType CAuthorityControl::addRolesUserInfo(AllTrade::AuthorityRolesPtr& rolesInfo)
	{
		std::lock_guard<std::recursive_mutex> lock(mtx_roles);

		if (m_authorityImpl)
			return m_authorityImpl->addRolesUserInfo(rolesInfo);

		return -1;
	}

	ErrorCodeType CAuthorityControl::deleteRolesUser(int nRoleId)
	{
		std::lock_guard<std::recursive_mutex> lock(mtx_roles);
		if (m_authorityImpl)
			return m_authorityImpl->deleteRolesUser(nRoleId);

		return -1;
	}

	ErrorCodeType CAuthorityControl::updateRolesUserInfo(const AllTrade::AuthorityRolesPtr& rolesInfo)
	{
		std::lock_guard<std::recursive_mutex> lock(mtx_roles);
		if (m_authorityImpl)
			return m_authorityImpl->updateRolesUserInfo(rolesInfo);
		return -1;
	}



	ErrorCodeType CAuthorityControl::isHaveAuthority(const AllTrade::LoginNameType loginName, int nFunctionId) const
	{
		if (m_authorityImpl)
			return m_authorityImpl->isHaveAuthority(loginName, nFunctionId);

		return -1;
	}

	ErrorCodeType CAuthorityControl::getAuthorityRoleUsers(const AllTrade::LoginNameType loginName, std::vector<AllTrade::AuthorityRoleUsersPtr>& vecAuthority)
	{
		std::lock_guard<std::recursive_mutex> lock(mtx_roles);
		if (m_authorityImpl)
			return m_authorityImpl->getAuthorityRoleUsers(loginName, vecAuthority);
		return -1;
	}

	ErrorCodeType CAuthorityControl::addAuthorityRoleUsers(const std::vector<AllTrade::AuthorityRoleUsersPtr>& vecAuthority)
	{
		std::lock_guard<std::recursive_mutex> lock(mtx_roles);

		if (m_authorityImpl)
			return m_authorityImpl->addAuthorityRoleUsers(vecAuthority);

		return -1;
	}

	ErrorCodeType CAuthorityControl::deleteAuthorityRoleUsers(const std::vector<AllTrade::AuthorityRoleUsersPtr>& vecAuthority)
	{
		std::lock_guard<std::recursive_mutex> lock(mtx_roles);
		if (m_authorityImpl)
			return m_authorityImpl->deleteAuthorityRoleUsers(vecAuthority);

		return -1;
	}

	ErrorCodeType CAuthorityControl::judgeRoleUsersRelation(int roleId)
	{
		std::lock_guard<std::recursive_mutex> lock(mtx_roles);
		if (m_authorityImpl)
			return m_authorityImpl->judgeRoleUsersRelation(roleId);

		return -1;
	}

	ErrorCodeType CAuthorityControl::judgeRoleUsersRelation(const AllTrade::LoginNameType loginName, int nRoleId)
	{
		std::lock_guard<std::recursive_mutex> lock(mtx_roles);
		if (m_authorityImpl)
			return m_authorityImpl->judgeRoleUsersRelation(loginName, nRoleId);

		return -1;
	}

	AllTrade::ErrorCodeType CAuthorityControl::judgeRoleUsersRelation(const AllTrade::LoginNameType loginName)
	{
		std::lock_guard<std::recursive_mutex> lock(mtx_roles);
		if (m_authorityImpl)
			return m_authorityImpl->judgeRoleUsersRelation(loginName);

		return -1;
	}


	AllTrade::ErrorCodeType CAuthorityControl::changeAuthorityRoleUsers(const AllTrade::AuthorityRoleUsersPtr& ptr)
	{
		std::lock_guard<std::recursive_mutex> lock(mtx_roles);
		if (m_authorityImpl)
			return m_authorityImpl->changeAuthorityRoleUsers(ptr);

		return -1;
	}


	// ½ÇÉ« / ¹¦ÄÜ
	
	ErrorCodeType CAuthorityControl::addAuthorityRoleFunctions(int roleId, const std::vector<AllTrade::AuthorityRoleFunctionsPtr>& vecAuthority)
	{
		std::lock_guard<std::recursive_mutex> lock(mtx_roles);

		if (m_authorityImpl)
			return m_authorityImpl->addAuthorityRoleFunctions(roleId,vecAuthority);

		return -1;
	}
	ErrorCodeType CAuthorityControl::deleteAuthorityRoleFunctions(const std::vector<AllTrade::AuthorityRoleFunctionsPtr>& vecAuthority)
	{
		std::lock_guard<std::recursive_mutex> lock(mtx_roles);
		if (m_authorityImpl)
			return m_authorityImpl->deleteAuthorityRoleFunctions(vecAuthority);

		return -1;
	}
	ErrorCodeType CAuthorityControl::getAuthorityRoleFunctionsByRoleId(int roleId, std::vector<AllTrade::AuthorityRoleFunctionsPtr>& vecAuthority)
	{
		std::lock_guard<std::recursive_mutex> lock(mtx_roles);

		if (m_authorityImpl)
			return m_authorityImpl->getAuthorityRoleFunctionsByRoleId(roleId,vecAuthority);

		return -1;
	}
	int CAuthorityControl::judgeRoleAndFunctionsRelationOne(int nRoleId)
	{
		std::lock_guard<std::recursive_mutex> lock(mtx_roles);

		if (m_authorityImpl)
			return m_authorityImpl->judgeRoleAndFunctionsRelationOne(nRoleId);
		return -1;
	}
	ErrorCodeType CAuthorityControl::judgeRoleAndFunctionsRelationTwo(int nFunctionID, int nRoleId)
	{
		std::lock_guard<std::recursive_mutex> lock(mtx_roles);
		if (m_authorityImpl)
			return m_authorityImpl->judgeRoleAndFunctionsRelationTwo(nFunctionID, nRoleId);

		return -1;
	}

	bool CAuthorityControl::handleDelAuthorityRoleFunctions(const std::vector<AllTrade::AuthorityRoleFunctionsPtr>& vecAuthority, std::vector<AllTrade::AuthorityRoleFunctionsPtr>& lowAuthority)
	{
		if (m_authorityImpl)
			return m_authorityImpl->handleDelAuthorityRoleFunctions(vecAuthority, lowAuthority);

		return false;
	}

	AllTrade::ErrorCodeType CAuthorityControl::getSelfFunctionsByLoginName(const LoginNameType loginName, std::vector<AuthorityFunctionsUserIdPtr> &vecAuthorityFunctions)
	{
		if (m_authorityImpl)
			return m_authorityImpl->getSelfFunctionsByLoginName(loginName, vecAuthorityFunctions);

		return AllTrade::Err_Unknown;
	}

	AllTrade::ErrorCodeType CAuthorityControl::isHaveRoleName(const AllTrade::LoginNameType roleName)
	{
		if (m_authorityImpl)
			return m_authorityImpl->isHaveRoleName(roleName);

		return AllTrade::Err_Unknown;
	}

	AllTrade::ErrorCodeType CAuthorityControl::getAllBussness(std::vector<AuthorityBussnessesPtr>& vec)
	{
		if (m_authorityImpl)
			return m_authorityImpl->getAllBussness(vec);

		return AllTrade::Err_Unknown;
	}

}
