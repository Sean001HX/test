#pragma once
#include<mutex>
#include<memory>
#include<vector>
#include "define/struct_extern.h"
#include"define/struct_declare.h"
namespace AllTrade
{
	class UserSystemImpl
	{
	public:
		UserSystemImpl();
		~UserSystemImpl();
	public:
		////////////////////////////// �����û���غ���
		// �����û���Ϣ
		// ���أ����󷵻�-1
		int addUserInfo(AccountTypeType type,const UserInfoPtr & userInfo);
		// ɾ���û���Ϣ
		// userId���˻�ID
		// ���أ����󷵻�-1
		int deleteUserInfo(AccountTypeType type, int userID);
		// �޸��û���Ϣ
		// ���أ����󷵻�-1
		int updateUserInfo(AccountTypeType type, UserInfoPtr & userInfo);
		// ��ѯ�û���Ϣ
		// userId���˻�ID
		// ���أ����󷵻�-1
		int getUserInfoByUserID(int userID, AccountTypeType type, UserInfoPtr &userInfo);
		// �޸��û�����
		// userId���˻�ID
		// ���أ����󷵻�-1
		int updateUserPassword(int userID, AccountTypeType type, const AllTrade::ChangeUserPswSt& psw);
		// �޸��û��ǳ�
		// userId���˻�ID
		// ���أ����󷵻�-1
		int updateUserNickName(int userID, const AllTrade::ChangeUserNickSt& nickName);
		//// ��ѯ�û�����
		//// userId���˻�ID
		//// ���أ����󷵻�-1
		//int getUserLevelNameByUserID(int userID, AccountTypeType type, LevelInfoPtr&  levelName);

		////////////////////////////// �û���ѯ��غ���
		//��ѯĳ������ID�µ������û�
		// userId������ID
		// ���أ����󷵻�-1
		int queryUserInfoByInstitutionID(int userID, std::vector<TradeUserInfoPtr>& vecInfo);
		// ��ѯĳ��������ID�µ������û�
		// userId��������ID
		// ���أ����󷵻�-1
		int queryUserInfoByAgentID(int userID, std::vector<TradeUserInfoPtr>& vecInfo);
		// ��ѯĳ����ͨ�û��µ������ƹ��û�
		// userId���˻�ID
		// ���أ����󷵻�-1
		int queryPopularizeUserInfoByUserID(int userID, std::vector<TradeUserInfoPtr>& vecInfo);

		// ��ѯĳ�û������ĸ�����
		// userId���˻�ID
		// ���أ����󷵻�-1
		int queryInsititutionInfo(int userID, InsititutionStPtr& userInfo);
		// ��ѯĳ�û������ĸ�������
		// userId���˻�ID
		// ���أ����󷵻�-1
		int queryAgentInfo(int userID, AgentstPtr& userInfo);
		// ��ѯĳ�û������ĸ��ƹ��û�
		// userId���˻�ID
		// ���أ����󷵻�-1
		int queryPopularizeUserInfo(int userID, TradeUserInfoPtr& userInfo);


		//////////////////////////////// ������غ���
		// ��������
		// ���أ����󷵻�-1
		int addUserTypeInfo(const InsititutionStPtr& userTypeInfo);
		//  ɾ������
		// institutionID������ID
		// ���أ����󷵻�-1
		int deleteInsititutionUserInfo(int InsititutionID);
		//  �޸Ļ�����Ϣ
		//  ���أ����󷵻�-1
		int updateInsititutionUserInfo(InsititutionStPtr& userInfo);
		//  ��ȡĳ������Ϣ
		//  institutionID������ID
		//  ���أ����󷵻�-1
		int getInstitutionInfolByInsitionID(int InsititutionID, InsititutionStPtr& userInfo);
		//  ��ȡĳ������������ʵ���˻�
		//  institutionID������ID
		//  ���أ����󷵻�-1
		int getAllFillUserInfoByInsitutionID(int insititutionID, std::vector<FirmUserInfoPtr>& vecInfo);
		//// ��ȡĳ��������
		//// institutionID������ID
		//// ���أ����󷵻�-1
		//int getInstitutionNameByUserID(int institutionID, char* institutionName);
		//// ��ȡĳ�����㼶
		//// institutionID������ID
		//// ���أ����󷵻�-1
		//int getInstitutionLevelByUserID(int levelID, int* level);
		//// ��ȡĳ������Ϣ
		//// institutionID������ID
		//// ���أ����󷵻�-1
		//int getInstitutionInfoByUserID(int institutionID, InsititutionStPtr& insitutionInfo);
		// ��ѯĳ�������µĴ�����
		// institutionID������ID
		// ���أ����󷵻�-1
		int getAgentInfoByUserID(int institutionID, std::vector<AgentstPtr>& vecInfo);


		////////////////////////////// ��������غ���
		////����������
		////���أ����󷵻�-1
		//int addAgentInfo(const AgentstPtr& insititutionInfo);
		//// ��ȡĳ����������
		//// agentID��������ID
		//// ���أ����󷵻�-1
		//int getAgentNameByUserID(int agentID, char* agentName);
		// ��ȡĳ�����̲㼶
		// agentID��������ID
		// ���أ����󷵻�-1
		int getAgentLevelByUserID(int agentID, int*  level);
		//// ��ȡĳ��������Ϣ
		//// agentID��������ID
		//// ���أ����󷵻�-1
		//int getAgentInfoByUserID(int agentID, AgentstPtr& agentInfo);


		////////////////////////////// ����Ա��غ���
		////��������Ա
		////���أ����󷵻�-1
		//int  addManagerInfo(const UserInfoPtr& managerInfo);
		// ��ȡĳ�����������й���Ա
		// agentID������ID
		// ���أ����󷵻�-1
		int  getAllManagerInfoByInsitutionID(int insititutionID, std::vector<ManagerUserInfoPtr>& vecInfo);


		////////////////////////////// ϵͳ������غ���
		// ��ȡ����Ļ������
		// agentID������ID
		// ���أ����󷵻�-1
		int  getLevelByInsititutionID(int insititutionID, int * level);
		// ��ȡ����Ĵ��������
		// agentID��������ID
		// ���أ����󷵻�-1
		int  getLevelByAgentID(int agentID, int * level);
	};
}


