#include<assert.h>
#include "UserSystemImpl.h"
#include "Application/InsititutionUserMgr.h"
#include"Application/AgentUserMgr.h"
#include"Application/TradeUserMgr.h"
#include"Application/ManagerUserMgr.h"
#include"Application/FirmUserMgr.h"
#include"define/params_declare.h"

namespace AllTrade
{
	UserSystemImpl::UserSystemImpl()
	{
		TradeUserMgr::instance();
		InsititutionUserMgr::instance();
		AgentUserMgr::instance();
		FirmUserMgr::instance();
		ManagerUserMgr::instance();
	}


	UserSystemImpl::~UserSystemImpl()
	{
		TradeUserMgr::unInstance();
		InsititutionUserMgr::unInstance();
		AgentUserMgr::unInstance();
		FirmUserMgr::unInstance();
		ManagerUserMgr::unInstance();
	}

	int UserSystemImpl::addUserInfo(AccountTypeType type, const UserInfoPtr & userInfo)
	{
		switch (type)
		{
		case AccountTypeType::Account_Type_Trade:
			return TradeUserMgr::instance()->addTradeUserInfo(std::dynamic_pointer_cast<TradeUserInfo>(userInfo));
			break;
		case AccountTypeType::Account_Type_Firm:
			return   FirmUserMgr::instance()->addFirmUserInfo(std::dynamic_pointer_cast<FirmUserInfo>(userInfo));
			break;
		case AccountTypeType::Account_Type_Agent:
			return   AgentUserMgr::instance()->addAgentUserInfo(std::dynamic_pointer_cast<AgentSt>(userInfo));
			break;
		case AccountTypeType::Account_Type_Manager:
			return   ManagerUserMgr::instance()->addManagerUserInfo(std::dynamic_pointer_cast<ManagerUserInfo>(userInfo));
			break;
		default:
			assert(0);
			break;
		}
		return -1;
	}

	int UserSystemImpl::deleteUserInfo(AccountTypeType type, int userID)
	{
		switch (type)
		{
		case AccountTypeType::Account_Type_Trade:
			return TradeUserMgr::instance()->deleteTradeUserInfo(userID);
			break;
		case AccountTypeType::Account_Type_Firm:
			return   FirmUserMgr::instance()->deleteFirmUserInfo(userID);
			break;
		case AccountTypeType::Account_Type_Agent:
			return   AgentUserMgr::instance()->deleteAgentUserInfo(userID);
			break;
		case AccountTypeType::Account_Type_Manager:
			return   ManagerUserMgr::instance()->deleteManagerUserInfo(userID);
			break;
		default:
			assert(0);
			break;
		}
		return -1;
	}

	int UserSystemImpl::updateUserInfo(AccountTypeType type, UserInfoPtr & userInfo)
	{
		switch (type)
		{
		case AccountTypeType::Account_Type_Trade:
			return TradeUserMgr::instance()->updateTradeUserInfo(std::dynamic_pointer_cast<TradeUserInfo>(userInfo));
			break;
		case AccountTypeType::Account_Type_Firm:
			return   FirmUserMgr::instance()->updateFirmUserInfo(std::dynamic_pointer_cast<FirmUserInfo>(userInfo));
			break;
		case AccountTypeType::Account_Type_Agent:
			return   AgentUserMgr::instance()->updateAgentUserInfo(std::dynamic_pointer_cast<AgentSt>(userInfo));
			break;
		case AccountTypeType::Account_Type_Manager:
			return   ManagerUserMgr::instance()->updateManagerUserInfo(std::dynamic_pointer_cast<ManagerUserInfo>(userInfo));
			break;
		default:
			assert(0);
			break;
		}
		return -1;
	}

	int UserSystemImpl::getUserInfoByUserID(int userID, AccountTypeType type, UserInfoPtr &userInfo)
	{
		switch (type)
		{
		case AccountTypeType::Account_Type_Trade:
			return TradeUserMgr::instance()->getTradeUserInfoByUserID(userID,std::dynamic_pointer_cast<TradeUserInfo>(userInfo));
			break;
		case AccountTypeType::Account_Type_Firm:
			return   FirmUserMgr::instance()->getFirmUserInfoByFirmID(userID, std::dynamic_pointer_cast<FirmUserInfo>(userInfo));
			break;
		case AccountTypeType::Account_Type_Agent:
			return   AgentUserMgr::instance()->getAgentInfoByAgentID(userID, std::dynamic_pointer_cast<AgentSt>(userInfo));
			break;
		case AccountTypeType::Account_Type_Manager:
			return   ManagerUserMgr::instance()->getManagerUserInfoByManagerID(userID, std::dynamic_pointer_cast<ManagerUserInfo>(userInfo));
			break;
		default:
			assert(0);
			break;
		}
		return -1;
	}

	int UserSystemImpl::updateUserPassword(int userID, AccountTypeType type, const AllTrade::ChangeUserPswSt& psw)
	{
		switch (type)
		{
		case AllTrade::AccountTypeType::Account_Type_Trade:
			return TradeUserMgr::instance()->updateTradeUserPassword(userID, psw);
			break;
		default:
			assert(0);
			break;
		}
		return -1;
	}

	int UserSystemImpl::updateUserNickName(int userID, const AllTrade::ChangeUserNickSt& nickName)
	{
		return  TradeUserMgr::instance()->updateTradeUserNickName(userID, nickName);
	}

	int UserSystemImpl::queryUserInfoByInstitutionID(int userID, std::vector<TradeUserInfoPtr>& vecInfo)
	{
		return TradeUserMgr::instance()->queryTradeUserInfoByInstitutionID(userID, vecInfo);
	}

	int UserSystemImpl::queryUserInfoByAgentID(int userID, std::vector<TradeUserInfoPtr>& vecInfo)
	{
		return  TradeUserMgr::instance()->queryTradeUserInfoByAgentID(userID, vecInfo);
	}

	int UserSystemImpl::queryPopularizeUserInfoByUserID(int userID, std::vector<TradeUserInfoPtr>& vecInfo)
	{
		return TradeUserMgr::instance()->queryPopularizeUserInfoByUserID(userID, vecInfo);
	}

	int UserSystemImpl::queryInsititutionInfo(int userID, InsititutionStPtr& userInfo)
	{
		return TradeUserMgr::instance()->queryInsititutionInfo(userID, userInfo);
	}

	int UserSystemImpl::queryAgentInfo(int userID, AgentstPtr& userInfo)
	{
		return TradeUserMgr::instance()->queryAgentInfo(userID, userInfo);
	}

	int UserSystemImpl::queryPopularizeUserInfo(int userID, TradeUserInfoPtr& userInfo)
	{
		return TradeUserMgr::instance()->queryPopularizeUserInfo(userID, userInfo);
	}

	
	int UserSystemImpl::addUserTypeInfo(const InsititutionStPtr& userTypeInfo)
	{
		return InsititutionUserMgr::instance()->addInsititutionUserInfo(userTypeInfo);
	}

	int UserSystemImpl::deleteInsititutionUserInfo(int InsititutionID)
	{
		return InsititutionUserMgr::instance()->deleteInsititutionUserInfo(InsititutionID);
	}

	int UserSystemImpl::updateInsititutionUserInfo(InsititutionStPtr& userInfo)
	{
		return InsititutionUserMgr::instance()->updateInsititutionUserInfo(userInfo);
	}

	int UserSystemImpl::getInstitutionInfolByInsitionID(int InsititutionID, InsititutionStPtr& userInfo)
	{
		return InsititutionUserMgr::instance()->getInstitutionInfolByInsitionID(InsititutionID, userInfo);
	}

	int UserSystemImpl::getAllFillUserInfoByInsitutionID(int insititutionID, std::vector<FirmUserInfoPtr>& vecInfo)
	{
		return InsititutionUserMgr::instance()->getAllFillUserInfoByInsitutionID(insititutionID, vecInfo);
	}

	int UserSystemImpl::getAgentInfoByUserID(int institutionID, std::vector<AgentstPtr>& vecInfo)
	{
		return InsititutionUserMgr::instance()->getAgentInfoByInsitionID(institutionID, vecInfo);
	}


	int UserSystemImpl::getAllManagerInfoByInsitutionID(int insititutionID, std::vector<ManagerUserInfoPtr>& vecInfo)
	{
		return InsititutionUserMgr::instance()->getAllManagerInfoByInsitutionID(insititutionID, vecInfo);
	}

	int UserSystemImpl::getLevelByInsititutionID(int insititutionID, int * level)
	{
		return -1;

	}

	int UserSystemImpl::getLevelByAgentID(int agentID, int * level)
	{
		return -1;
	}

}
