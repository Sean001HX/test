#pragma once
#include "utility/instance.h"
#include "define/struct_declare.h"
#include <vector>

namespace AllTrade
{
	class AgentUserMgr 
		: public CommonTools::instance_unshared<AgentUserMgr>
	{
	public:
		AgentUserMgr();
		~AgentUserMgr();

	public:
		 //  创建代理商
		int  addAgentUserInfo(const AgentstPtr& userInfo);
		 //  删除代理商
		 int deleteAgentUserInfo(int agentID);
		 //  修改代理商信息
		 int updateAgentUserInfo(AgentstPtr& userInfo);
		 //  获取某代理商信息
		 int getAgentInfoByAgentID(int agentID, AgentstPtr& userInfo);

		 //  获取下级所有代理商
		 int getAllLowerAgentInfoByAgentID(int agentID, std::vector<AgentstPtr>& vecUserInfo);
		 //  获取某代理商下级所有的交易账户
		 int getAllTradeUserInfoByAgentID(int agentID, std::vector<TradeUserInfoPtr>& vecUserInfo);
		 
	};

	
}


