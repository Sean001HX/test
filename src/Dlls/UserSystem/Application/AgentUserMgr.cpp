#include "AgentUserMgr.h"
#include "include/OperationManager/OperationManager.h"

using namespace OperationManager;

namespace AllTrade
{
	AgentUserMgr::AgentUserMgr()
	{

	}

	AgentUserMgr::~AgentUserMgr()
	{

	}

	int AgentUserMgr::addAgentUserInfo(const AgentstPtr& userInfo)
	{
		return -1;
	}

	int AgentUserMgr::deleteAgentUserInfo(int agentID)
	{
		return -1;
	}


	int AgentUserMgr::updateAgentUserInfo(AgentstPtr& userInfo)
	{
		return -1;
	}

	int AgentUserMgr::getAgentInfoByAgentID(int levelID, AgentstPtr& userInfo)
	{
		return -1;
	}

	int AgentUserMgr::getAllLowerAgentInfoByAgentID(int agentID, std::vector<AgentstPtr>& vecUserInfo)
	{
		return -1;
	}

	int AgentUserMgr::getAllTradeUserInfoByAgentID(int agentID, std::vector<TradeUserInfoPtr>& vecUserInfo)
	{
		return -1;
	}

}
