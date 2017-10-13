#include "AuthorityControlImpl.h"
#include "include/OperationManager/OperationManager.h"

using namespace OperationManager;

namespace AuthorityControl
{
	CAuthorityControlImpl::CAuthorityControlImpl()
	{
	
	}


	CAuthorityControlImpl::~CAuthorityControlImpl()
	{
	}

	ErrorCodeType CAuthorityControlImpl::getRolesUserInfo(const UserIDType userid, std::vector<AllTrade::AuthorityRolesPtr>& vecRolesInfo)
	{
		return COperationManager::instance()->getRolesUserInfo(userid, vecRolesInfo);
	}

	ErrorCodeType CAuthorityControlImpl::addRolesUserInfo(AllTrade::AuthorityRolesPtr& rolesInfo)
	{
		
		return COperationManager::instance()->addRolesUserInfo(rolesInfo);
	}

	ErrorCodeType CAuthorityControlImpl::deleteRolesUser(int nRoleId)
	{
		return COperationManager::instance()->deleteRolesUser(nRoleId);
	}

	ErrorCodeType CAuthorityControlImpl::updateRolesUserInfo(const AllTrade::AuthorityRolesPtr& rolesInfo)
	{
		return COperationManager::instance()->updateRolesUserInfo(rolesInfo);

	}

	AllTrade::ErrorCodeType CAuthorityControlImpl::isHaveRoleName(const AllTrade::LoginNameType roleName)
	{
		return COperationManager::instance()->isHaveRoleName(roleName);
	}

	void CAuthorityControlImpl::getRolesIdByUserId(int nUserId, std::set<int>& rolesId)
	{
	/*	std::vector<AllTrade::AuthorityRolesPtr> vecRolesInfo;
		if (!getRolesUserInfo(nUserId, vecRolesInfo))
		{
			for (auto &item : vecRolesInfo)
			{
				rolesId.insert(item->rolesID);
			}
		}*/
	}

	ErrorCodeType CAuthorityControlImpl::isHaveAuthority(const AllTrade::LoginNameType loginName, int nFunctionId) const
	{
		return COperationManager::instance()->isHaveAuthority(loginName, nFunctionId);
	
	}

	ErrorCodeType CAuthorityControlImpl::getAuthorityRoleUsers(const AllTrade::LoginNameType loginName, std::vector<AllTrade::AuthorityRoleUsersPtr>& vecAuthority)
	{
		return COperationManager::instance()->getAuthorityRoleUsers(loginName, vecAuthority);
	}

	ErrorCodeType CAuthorityControlImpl::addAuthorityRoleUsers(const std::vector<AllTrade::AuthorityRoleUsersPtr>& vecAuthority)
	{
		return COperationManager::instance()->addAuthorityRoleUsers(vecAuthority);
	}

	ErrorCodeType CAuthorityControlImpl::deleteAuthorityRoleUsers(const std::vector<AllTrade::AuthorityRoleUsersPtr>& vecAuthority)
	{
		return COperationManager::instance()->deleteAuthorityRoleUsers(vecAuthority);
	}

	ErrorCodeType CAuthorityControlImpl::judgeRoleUsersRelation(int roleId)
	{
		return COperationManager::instance()->judgeRoleUsersRelation(roleId);
	}

	ErrorCodeType CAuthorityControlImpl::judgeRoleUsersRelation(const AllTrade::LoginNameType loginName, int nRoleId)
	{
		return COperationManager::instance()->judgeRoleUsersRelation(loginName, nRoleId);
	}

	AllTrade::ErrorCodeType CAuthorityControlImpl::judgeRoleUsersRelation(const AllTrade::LoginNameType loginName)
	{
		return COperationManager::instance()->judgeRoleUsersRelation(loginName);
	}

	AllTrade::ErrorCodeType CAuthorityControlImpl::changeAuthorityRoleUsers(const AllTrade::AuthorityRoleUsersPtr& ptr)
	{
		return COperationManager::instance()->changeAuthorityRoleUsers(ptr);
	}


	bool CAuthorityControlImpl::getAllAgentHaveRelation(std::set<int>& setInfo, int roleId)
	{
		if (!COperationManager::instance()->getAllAgentHaveRelation(setInfo, roleId))
			return true;

		return false;
	}

	ErrorCodeType CAuthorityControlImpl::getAllAuthorityRoleFunctions(std::vector<AllTrade::AuthorityRoleFunctionsPtr>& vecAuthority)
	{
		return COperationManager::instance()->getAllAuthorityRoleFunctions(vecAuthority);
	}

	ErrorCodeType CAuthorityControlImpl::addAuthorityRoleFunctions(int roleId, const std::vector<AllTrade::AuthorityRoleFunctionsPtr>& vecAuthority)
	{
		return COperationManager::instance()->addAuthorityRoleFunctions(roleId,vecAuthority);
	}

	ErrorCodeType CAuthorityControlImpl::deleteAuthorityRoleFunctions(const std::vector<AllTrade::AuthorityRoleFunctionsPtr>& vecAuthority)
	{
		return COperationManager::instance()->deleteAuthorityRoleFunctions(vecAuthority);
	}

	int CAuthorityControlImpl::getAuthorityRoleFunctionsByRoleId(int roleId, std::vector<AllTrade::AuthorityRoleFunctionsPtr>& vecAuthority)
	{
		return COperationManager::instance()->getAuthorityRoleFunctionsByRoleId(roleId, vecAuthority);
	}

	ErrorCodeType CAuthorityControlImpl::judgeRoleAndFunctionsRelationOne(int nRoleId)
	{
		return COperationManager::instance()->judgeRoleAndFunctionsRelationOne(nRoleId);
		
	}

	int CAuthorityControlImpl::judgeRoleAndFunctionsRelationTwo(int nFunctionID, int nRoleId)
	{
		return COperationManager::instance()->judgeRoleAndFunctionsRelationTwo(nFunctionID, nRoleId);
			
	}

	

	bool CAuthorityControlImpl::handleDelAuthorityRoleFunctions(const std::vector<AllTrade::AuthorityRoleFunctionsPtr>& vecAuthority, std::vector<AllTrade::AuthorityRoleFunctionsPtr>& lowAuthority)
	{
		if (vecAuthority.size() == 0)
			return false;


		// 1、获取有关系的代理商
		std::set<int> setHaveRelationId;
		if (!getAllAgentHaveRelation(setHaveRelationId, vecAuthority.at(0)->roleID))
			return false;

		if (!setHaveRelationId.size())
			return false;

		// 2、保存有关系的代理商的所有下级代理商
		m_setUserId.clear();
		if (!getAllAgentInfo())
			return false;

		for (auto& iterId : setHaveRelationId)
		{
			m_setUserId.insert(iterId);

			checkLowerUsers(iterId);
		}

		// 3、查找所有下级代理商开的角色
		std::set<int> setRolesId;
		// setRolesId.insert(vecAuthority.at(0).roleID); // 自身的
		for (auto& item : m_setUserId)
		{
			getRolesIdByUserId(item, setRolesId);
		}

		// 4、对角色进行功能限制
		for (auto& item : setRolesId)
		{
			if (!getLowerAuthoryFunctions(item, vecAuthority, lowAuthority))
				return false;
		}

		return true;
	}

	void CAuthorityControlImpl::checkLowerUsers(int userId)
	{
		auto iter = m_mapInfo.find(userId);
		if (iter != m_mapInfo.end())
		{
			for (auto &item : iter->second)
			{
				m_setUserId.insert(item);
				checkLowerUsers(item);
			}
		}
		else
		{
			m_setUserId.insert(userId);
		}
	}

	bool CAuthorityControlImpl::getLowerAuthoryFunctions(int nRoleId, const std::vector<AllTrade::AuthorityRoleFunctionsPtr>& vecAuthority, std::vector<AllTrade::AuthorityRoleFunctionsPtr>& lowAuthority)
	{
		std::vector<AllTrade::AuthorityRoleFunctionsPtr> vecInfo;
		if (COperationManager::instance()->getAllAuthorityRoleFunctions(vecInfo))
			return false;

		for (auto& item : vecInfo)
		{
			if (nRoleId == item->roleID)
			{
				for (auto& itemParam : vecAuthority)
				{
					if (itemParam->functionID == item->functionID)
					{
						lowAuthority.emplace_back(item);

						break;
					}

				}

			}
		}
		
		return true;
	}

	bool CAuthorityControlImpl::getAllAgentInfo()
	{
		m_mapInfo.clear();
		// 
		if (!COperationManager::instance()->GetAllAgentInfo(m_mapInfo))
			return true;

		return false;
	}

	AllTrade::ErrorCodeType CAuthorityControlImpl::getSelfFunctionsByLoginName(const LoginNameType loginName, std::vector<AuthorityFunctionsUserIdPtr> &vecAuthorityFunctions)
	{
		return COperationManager::instance()->getSelfFunctionsByLoginName(loginName, vecAuthorityFunctions);
	}

	AllTrade::ErrorCodeType CAuthorityControlImpl::getAllBussness(std::vector<AuthorityBussnessesPtr>& vec)
	{
		return COperationManager::instance()->getAllBussness(vec);
	}

}
