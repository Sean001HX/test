#pragma once
#include<vector>
#include "utility/instance.h"
#include "define/struct_declare.h"
#include"define/struct_base.h"
namespace AllTrade
{
	class TradeUserMgr
		: public CommonTools::instance_unshared<TradeUserMgr>
	{
	public:
		TradeUserMgr();
		~TradeUserMgr();
	public:
		// ���ӽ����û���Ϣ
		int addTradeUserInfo(const TradeUserInfoPtr& userInfo);
		// ɾ���ý��׻���Ϣ
		int deleteTradeUserInfo(int userID);
		// �޸Ľ����û���Ϣ
		int updateTradeUserInfo(TradeUserInfoPtr& userInfo);
		// ��ѯ�����û�����
		int getTradeUserNameByUserID(int userID, char* userLevelName);
		// ��ѯ�����û���Ϣ
		int getTradeUserInfoByUserID(int userID, TradeUserInfoPtr& userInfo);
		// ��ѯĳ������ID�µ����н����û�
		int queryTradeUserInfoByInstitutionID(int userID, std::vector<TradeUserInfoPtr>& vecInfo);
		// ��ѯĳ��������ID�µ����н����û�
		int queryTradeUserInfoByAgentID(int userID, std::vector<TradeUserInfoPtr>& vecInfo);
		// ��ѯĳ����ͨ�����û��µ������ƹ��û�
		int queryPopularizeUserInfoByUserID(int userID, std::vector<TradeUserInfoPtr>& vecInfo);
		// ��ѯĳ�����û������ĸ�����
		int queryInsititutionInfo(int userID, InsititutionStPtr& userInfo);
		// ��ѯĳ�����û������ĸ�������
		int queryAgentInfo(int userID, AgentstPtr& userInfo);
		// ��ѯĳ�����û������ĸ��ƹ��û�
		int queryPopularizeUserInfo(int userID, TradeUserInfoPtr& userInfo);
		// �޸Ľ����û�����
		int updateTradeUserPassword(int userID, const AllTrade::ChangeUserPswSt& psw);
		// �޸Ľ����û��ǳ�
		int updateTradeUserNickName(int userID, const AllTrade::ChangeUserNickSt& nickName);
		// ��ȡ���еĽ����˻��û�
		int getAllTradeUserInfo(std::vector<TradeUserInfoPtr>& vecUserInfo);
	};
}


