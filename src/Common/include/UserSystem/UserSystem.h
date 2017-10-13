#pragma once
#ifdef USERSYSTEM_EXPORTS
#define USERSYSTEM_API __declspec(dllexport)
#else
#define USERSYSTEM_API __declspec(dllimport)
#endif

#include<memory>
#include<mutex>
#include<vector>
#include "define/struct_extern.h"
#include"define/struct_declare.h"
#include "utility/instance.h"
#include"define/params_declare.h"
#ifdef _MSC_VER
#	pragma warning(push)
#   pragma warning(disable: 4251) 
// #	pragma warning(disable: 4275) // �� DLL �ӿ������identifier����Ϊ DLL �ӿ������identifier���Ļ�ʹ��
#endif
namespace AllTrade
{
	class UserSystemImpl;
	class USERSYSTEM_API  UserSystem
		:public  CommonTools::instance_unshared<UserSystem>
	{

	public:
		UserSystem();
		~UserSystem();
	public:
		////////////////////////////// �����û���غ���
		// �����û���Ϣ
		// ���أ����󷵻�-1
		int addUserInfo(AccountTypeType type,const SAccountPtr & userInfo);
		// ɾ���û���Ϣ
		// userId���˻�ID
		// ���أ����󷵻�-1
		int deleteUserInfo(AccountTypeType type, int userID);
		// �޸��û���Ϣ
		// ���أ����󷵻�-1
		int updateUserInfo(AccountTypeType type, SAccountPtr & userInfo);
		// ��ѯ�û���Ϣ
		// userId���˻�ID
		// ���أ����󷵻�-1
		int getUserInfoByUserID(int userID, AccountTypeType type, SAccountPtr &userInfo);
		// �޸��û�����
		// userId���˻�ID
		// ���أ����󷵻�-1
		int updateUserPassword(int userID, AccountTypeType type, const AllTrade::ChangeUserPswSt& psw);
		// �޸��û��ǳ�
		// userId���˻�ID
		// ���أ����󷵻�-1
		int updateUserNickName(int userID, const AllTrade::ChangeUserNickSt& nickName);
		// ��ѯ�û��㼶����
		// userId���˻�ID
		// ���أ����󷵻�-1
		int getUserLevelNameByUserID(int userID, AccountTypeType type, LevelInfoPtr&  levelName );
		// ������е��û���Ϣ
		// ���أ����󷵻�-1
		int getAllUserInfo(AccountTypeType type, std::vector<UserInfoPtr> & vecUserInfo);

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
		//// ��������
		//// ���أ����󷵻�-1
		//int addUserTypeInfo(const SAccountPtr& userTypeInfo);
		//// ��ȡĳ��������
		//// institutionID������ID
		//// ���أ����󷵻�-1
		//int getInstitutionNameByUserID(int institutionID, char* institutionName);
		// ��ȡĳ�����㼶
		// institutionID������ID
		// ���أ����󷵻�-1
		int getInstitutionLevelByUserID(int levelID, int* level);
		//// ��ȡĳ������Ϣ
		//// institutionID������ID
		//// ���أ����󷵻�-1
		//int getInstitutionInfoByUserID(int institutionID, InsititutionStPtr& insitutionInfo);
		// ��ѯĳ�������µĴ�����
		// institutionID������ID
		// ���أ����󷵻�-1
		int getAgentInfoByUserID(int institutionID, std::vector<AgentstPtr>& vecInfo);
		//  ��ȡĳ������������ʵ���˻�
		//  institutionID������ID
		//  ���أ����󷵻�-1
		int getAllFillUserInfoByInsitutionID(int insititutionID, std::vector<FirmUserInfoPtr>& vecInfo);


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
		int getAgentLevelByUserID(int agentID, int* level);
		//// ��ȡĳ��������Ϣ
		//// agentID��������ID
		//// ���أ����󷵻�-1
		//int getAgentInfoByUserID(int agentID, AgentstPtr& agentInfo);


		////////////////////////////// ����Ա��غ���
		////��������Ա
		////���أ����󷵻�-1
		//int  addManagerInfo(const SAccountPtr& managerInfo);
		// ��ȡĳ�����������й���Ա
		// agentID������ID
		// ���أ����󷵻�-1
		int  getAllManagerInfoByInsitutionID(int insititutionID, std::vector<ManagerUserInfoPtr>& vecInfo);


		////////////////////////////// ϵͳ������غ���
		// ��ȡ����Ļ������
		// agentID������ID
		// ���أ����󷵻�-1
		int  getLevelByInsititutionID(int insititutionID, int* level);
		// ��ȡ����Ĵ��������
		// agentID��������ID
		// ���أ����󷵻�-1
		int  getLevelByAgentID(int agentID, int* level);
	private:
		std::recursive_mutex             m_userInfoMutex;
		std::recursive_mutex             m_insititutionInfoMutex;
		std::recursive_mutex             m_agentInfoMutex;
	private:
		static std::recursive_mutex   _mutex;
		UserSystemImpl*  m_userSystemImpl;
	};

}
#if defined(_MSC_VER)
#	pragma warning(pop)
#endif