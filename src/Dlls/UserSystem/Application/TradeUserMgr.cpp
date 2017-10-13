#include "TradeUserMgr.h"

namespace AllTrade
{
	TradeUserMgr::TradeUserMgr()
	{

	}

	TradeUserMgr::~TradeUserMgr()
	{

	}

	int TradeUserMgr::addTradeUserInfo(const TradeUserInfoPtr& userInfo)
	{
		return -1;
	}

	int TradeUserMgr::deleteTradeUserInfo(int userID)
	{
		return -1;
	}

	int TradeUserMgr::updateTradeUserInfo(TradeUserInfoPtr& userInfo)
	{
		return -1;
	}

	int TradeUserMgr::getTradeUserNameByUserID(int userID, char* userLevelName)
	{
		return -1;
	}

	int TradeUserMgr::getTradeUserInfoByUserID(int userID, TradeUserInfoPtr& userInfo)
	{
		return -1;
	}

	int TradeUserMgr::queryTradeUserInfoByInstitutionID(int userID, std::vector<TradeUserInfoPtr>& vecInfo)
	{
		return -1;
	}

	int TradeUserMgr::queryTradeUserInfoByAgentID(int userID, std::vector<TradeUserInfoPtr>& vecInfo)
	{
		return -1;
	}

	int TradeUserMgr::queryPopularizeUserInfoByUserID(int userID, std::vector<TradeUserInfoPtr>& vecInfo)
	{
		return -1;
	}

	int TradeUserMgr::queryInsititutionInfo(int userID, InsititutionStPtr& userInfo)
	{
		return -1;
	}

	int TradeUserMgr::queryAgentInfo(int userID, AgentstPtr& userInfo)
	{
		return -1;
	}

	int TradeUserMgr::queryPopularizeUserInfo(int userID, TradeUserInfoPtr& userInfo)
	{
		return -1;
	}

	int TradeUserMgr::updateTradeUserPassword(int userID, const AllTrade::ChangeUserPswSt& psw)
	{
		return -1;
	}

	int TradeUserMgr::updateTradeUserNickName(int userID, const AllTrade::ChangeUserNickSt& nickName)
	{
		return -1;
	}

	int TradeUserMgr::getAllTradeUserInfo(std::vector<TradeUserInfoPtr>& vecUserInfo)
	{
		return -1;
	}

}
