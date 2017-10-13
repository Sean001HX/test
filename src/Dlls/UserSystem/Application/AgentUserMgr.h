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
		 //  ����������
		int  addAgentUserInfo(const AgentstPtr& userInfo);
		 //  ɾ��������
		 int deleteAgentUserInfo(int agentID);
		 //  �޸Ĵ�������Ϣ
		 int updateAgentUserInfo(AgentstPtr& userInfo);
		 //  ��ȡĳ��������Ϣ
		 int getAgentInfoByAgentID(int agentID, AgentstPtr& userInfo);

		 //  ��ȡ�¼����д�����
		 int getAllLowerAgentInfoByAgentID(int agentID, std::vector<AgentstPtr>& vecUserInfo);
		 //  ��ȡĳ�������¼����еĽ����˻�
		 int getAllTradeUserInfoByAgentID(int agentID, std::vector<TradeUserInfoPtr>& vecUserInfo);
		 
	};

	
}


