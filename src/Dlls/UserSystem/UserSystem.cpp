#include "include/UserSystem/UserSystem.h"
#include"UserSystemImpl.h"
namespace AllTrade
{

	std::recursive_mutex UserSystem::_mutex;
	UserSystem::UserSystem() :m_userSystemImpl(new UserSystemImpl)
	{

	}

	UserSystem::~UserSystem()
	{
		if (m_userSystemImpl)
		{
			delete m_userSystemImpl;
			m_userSystemImpl = nullptr;
		}
	}


	int UserSystem::addUserInfo(AccountTypeType type, const UserInfoPtr & userInfo)
	{
		std::lock_guard<std::recursive_mutex> lock(m_userInfoMutex);
		if (m_userSystemImpl)
		{
			return m_userSystemImpl->addUserInfo(type,userInfo);
		}
		return -1;
	}

	int UserSystem::deleteUserInfo(AccountTypeType type, int userID)
	{
		std::lock_guard<std::recursive_mutex> lock(m_userInfoMutex);
		if (m_userSystemImpl)
		{
			return m_userSystemImpl->deleteUserInfo(type,userID);
		}
		return -1;
	}

	int UserSystem::updateUserInfo(AccountTypeType type, UserInfoPtr & userInfo)
	{
		std::lock_guard<std::recursive_mutex> lock(m_userInfoMutex);
		if (m_userSystemImpl)
		{
			return m_userSystemImpl->updateUserInfo(type,userInfo);
		}
		return -1;
	}

	int UserSystem::getUserInfoByUserID(int userID, AccountTypeType type, UserInfoPtr &userInfo)
	{
		std::lock_guard<std::recursive_mutex> lock(m_userInfoMutex);
		if (m_userSystemImpl)
		{
			return m_userSystemImpl->getUserInfoByUserID(userID,type, userInfo);
		}
		return -1;
	}

	int UserSystem::updateUserPassword(int userID, AccountTypeType type,  const AllTrade::ChangeUserPswSt& psw)
	{

		std::lock_guard<std::recursive_mutex> lock(m_userInfoMutex);
		if (m_userSystemImpl)
		{
			return m_userSystemImpl->updateUserPassword(userID,type, psw);
		}
		return -1;
	}

	int UserSystem::updateUserNickName(int userID, const AllTrade::ChangeUserNickSt& nickName)
	{
		std::lock_guard<std::recursive_mutex> lock(m_userInfoMutex);
		if (m_userSystemImpl)
		{
			return m_userSystemImpl->updateUserNickName(userID, nickName);
		}
		return -1;
	}


	int UserSystem::queryUserInfoByInstitutionID(int userID, std::vector<TradeUserInfoPtr>& vecInfo)
	{
		std::lock_guard<std::recursive_mutex> lock(m_userInfoMutex);
		if (m_userSystemImpl)
		{
			return m_userSystemImpl->queryUserInfoByInstitutionID(userID, vecInfo);
		}
		return -1;
	}

	int UserSystem::queryUserInfoByAgentID(int userID, std::vector<TradeUserInfoPtr>& vecInfo)
	{
		std::lock_guard<std::recursive_mutex> lock(m_userInfoMutex);
		if (m_userSystemImpl)
		{
			return m_userSystemImpl->queryUserInfoByAgentID(userID, vecInfo);
		}
		return -1;
	}


	int UserSystem::queryPopularizeUserInfoByUserID(int userID, std::vector<TradeUserInfoPtr>& vecInfo)
	{
		std::lock_guard<std::recursive_mutex> lock(m_userInfoMutex);
		if (m_userSystemImpl)
		{
			return m_userSystemImpl->queryPopularizeUserInfoByUserID(userID, vecInfo);
		}
		return -1;
	}

	int UserSystem::queryInsititutionInfo(int userID, InsititutionStPtr& userInfo)
	{
		std::lock_guard<std::recursive_mutex> lock(m_userInfoMutex);
		if (m_userSystemImpl)
		{
			return m_userSystemImpl->queryInsititutionInfo(userID, userInfo);
		}
		return -1;
	}

	int UserSystem::queryAgentInfo(int userID, AgentstPtr& userInfo)
	{
		std::lock_guard<std::recursive_mutex> lock(m_userInfoMutex);
		if (m_userSystemImpl)
		{
			return m_userSystemImpl->queryAgentInfo(userID, userInfo);
		}
		return -1;
	}

	int UserSystem::queryPopularizeUserInfo(int userID, TradeUserInfoPtr& userInfo)
	{
		std::lock_guard<std::recursive_mutex> lock(m_insititutionInfoMutex);
		if (m_userSystemImpl)
		{
			return m_userSystemImpl->queryPopularizeUserInfo(userID, userInfo);
		}
		return -1;
	}

	int UserSystem::addUserTypeInfo(const InsititutionStPtr& userTypeInfo)
	{
		std::lock_guard<std::recursive_mutex> lock(m_insititutionInfoMutex);
		if (m_userSystemImpl)
		{
			return m_userSystemImpl->addUserTypeInfo(userTypeInfo);
		}
		return -1;
	}

	int UserSystem::deleteInsititutionUserInfo(int InsititutionID)
	{
		std::lock_guard<std::recursive_mutex> lock(m_insititutionInfoMutex);
		if (m_userSystemImpl)
		{
			return m_userSystemImpl->deleteInsititutionUserInfo(InsititutionID);
		}
		return -1;
	}

	int UserSystem::updateInsititutionUserInfo(InsititutionStPtr& userInfo)
	{
		std::lock_guard<std::recursive_mutex> lock(m_insititutionInfoMutex);
		if (m_userSystemImpl)
		{
			return m_userSystemImpl->updateInsititutionUserInfo(userInfo);
		}
		return -1;
	}

	int UserSystem::getInstitutionInfolByInsitionID(int InsititutionID, InsititutionStPtr& userInfo)
	{
		std::lock_guard<std::recursive_mutex> lock(m_insititutionInfoMutex);
		if (m_userSystemImpl)
		{
			return m_userSystemImpl->getInstitutionInfolByInsitionID(InsititutionID,userInfo);
		}
		return -1;
	}


	int UserSystem::getAgentInfoByUserID(int institutionID, std::vector<AgentstPtr>& vecInfo)
	{
		std::lock_guard<std::recursive_mutex> lock(m_insititutionInfoMutex);
		if (m_userSystemImpl)
		{
			return m_userSystemImpl->getAgentInfoByUserID(institutionID, vecInfo);
		}
		return -1;
	}

	
	int UserSystem::getAllFillUserInfoByInsitutionID(int insititutionID, std::vector<FirmUserInfoPtr>& vecInfo)
	{
		std::lock_guard<std::recursive_mutex> lock(m_insititutionInfoMutex);
		if (m_userSystemImpl)
		{
			return m_userSystemImpl->getAllFillUserInfoByInsitutionID(insititutionID, vecInfo);
		}
		return -1;
	}

	
	int UserSystem::getAllManagerInfoByInsitutionID(int insititutionID, std::vector<ManagerUserInfoPtr>& vecInfo)
	{
		std::lock_guard<std::recursive_mutex> lock(m_userInfoMutex);
		if (m_userSystemImpl)
		{
			return m_userSystemImpl->getAllManagerInfoByInsitutionID(insititutionID, vecInfo);
		}
		return -1;
	}

	int UserSystem::getLevelByInsititutionID(int insititutionID, int * level)
	{
		std::lock_guard<std::recursive_mutex> lock(m_userInfoMutex);
		if (m_userSystemImpl)
		{
			return m_userSystemImpl->getLevelByInsititutionID(insititutionID, level);
		}
		return -1;
	}

	int UserSystem::getLevelByAgentID(int agentID, int* level)
	{
		std::lock_guard<std::recursive_mutex> lock(m_userInfoMutex);
		if (m_userSystemImpl)
		{
			return m_userSystemImpl->getLevelByAgentID(agentID, level);
		}
		return -1;
	}

}


