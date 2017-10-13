#ifndef CAUTHORITY_CONTROL_H_
#define CAUTHORITY_CONTROL_H_

#include <vector>
#include <set>
#include <map>
#include "define/struct_extern.h"
#include "define/struct_declare.h"
#include <string>
using namespace AllTrade;

namespace OperationManager
{
	class CAuthorityControl
	{
	public:
		CAuthorityControl();
		~CAuthorityControl();


		// ��ʼ�����ݿ��
		bool initAllTable();

		// Ȩ��ҵ���
		bool createAuthorityBussnesses();
		// Ȩ����־��
		bool createAuthorityLog();
		// Ȩ�޹��ܱ�
		bool createAuthorityFunctions();
		// Ȩ�޽�ɫ���ܱ�
		bool createAuthorityRoleFunctions();
		// Ȩ�޽�ɫ�û���
		bool createAuthorityRoleUsers();
		// Ȩ�޽�ɫ��
		bool createAuthorityRoles();

		// ����loginname��ѯuserid�������ߣ�
		std::string getUserIdByLoginName(const LoginNameType loginName);
		// ��ѯ���й�����(������) parentid / userid 
		int getAllManager(std::map<std::string, std::set<std::string>>& mapManager);

		// �ݹ���
		void  checkLowerUsers(std::string userId);
		///////////////////////////////////////////// ��ɫ��ز��� ////////////////////////////////////
		// ��ѯ��ɫ������ͨ��userId���ҽ�ɫ
		ErrorCodeType getRolesUserInfo(const UserIDType userid, std::vector<AuthorityRolesPtr> &vecRolesInfo);
		// ��ѯ��ɫ������ͨ��userId���ҽ�ɫ
		int handleGetRolesUserInfo(const LoginNameType loginName, std::vector<AuthorityRolesPtr> &vecRolesInfo);
		
		// ���ӽ�ɫ����
		ErrorCodeType addRolesUserInfo(AuthorityRolesPtr& rolesInfo);
		// �޸Ľ�ɫ����
		ErrorCodeType updateRolesUserInfo(const AuthorityRolesPtr& rolesInfo);
		// ɾ����ɫ������ͨ����ɫIdɾ��
		ErrorCodeType deleteRolesUser(int rolesID);
		// �ж��Ƿ����иý�ɫ��
        ErrorCodeType isHaveRoleName(const AllTrade::LoginNameType roleName);

		/////////////////////////// �ж�ĳ�û��Ƿ����ĳ����Ȩ�� ////////////////////////////////////
        ErrorCodeType isHaveAuthority(const AllTrade::LoginNameType loginName, int nFunctionId)const;

		////////////////////////// �û��ͽ�ɫ //////////////////////////////////////////
		// ��ȡ�û��ͽ�ɫ֮���ϵ
        ErrorCodeType getAuthorityRoleUsers(const AllTrade::LoginNameType loginName, std::vector<AllTrade::AuthorityRoleUsersPtr>& vecAuthority);
		// ��ȡ�û��ͽ�ɫ֮���ϵ
        ErrorCodeType handleGetAuthorityRoleUsers(const AllTrade::LoginNameType loginName, std::vector<AllTrade::AuthorityRoleUsersPtr>& vecAuthority);

		// �����û��ͽ�ɫ֮���ϵ
		ErrorCodeType addAuthorityRoleUsers(const std::vector<AllTrade::AuthorityRoleUsersPtr>& vecAuthority);
		// ɾ���û��ͽ�ɫ֮���ϵ
		ErrorCodeType deleteAuthorityRoleUsers(const std::vector<AllTrade::AuthorityRoleUsersPtr>& vecAuthority);

		// �жϽ�ɫ�Ƿ���ں��û�֮���ϵ
		ErrorCodeType judgeRoleUsersRelation(int roleId);
		// �ж�ĳ����ɫ��ĳ���û��Ƿ���ڹ�ϵ
        ErrorCodeType judgeRoleUsersRelation(const AllTrade::LoginNameType loginName, int nRoleId);
		// �ҵ���ĳ��ɫ�й�ϵ�����д�����
		int getAllAgentHaveRelation(std::set<int>& setInfo, int nRoleId);
		// �жϸ��û��Ƿ�󶨽�ɫ
		ErrorCodeType judgeRoleUsersRelation(const AllTrade::LoginNameType loginName);

		// �޸��û��ͽ�ɫ֮���ϵ
		ErrorCodeType changeAuthorityRoleUsers(const AllTrade::AuthorityRoleUsersPtr& ptr);

		/////////////////////////// ��ɫ / ����
		// ������н�ɫ / ���ܹ�ϵ
		ErrorCodeType addAuthorityRoleFunctions(int roleId, const std::vector<AllTrade::AuthorityRoleFunctionsPtr>& vecAuthority);
		// ɾ�����н�ɫ / ���ܹ�ϵ
		ErrorCodeType deleteAuthorityRoleFunctions(const std::vector<AllTrade::AuthorityRoleFunctionsPtr>& vecAuthority);
		// ��ȡ���н�ɫ / ���ܹ�ϵ
		ErrorCodeType getAuthorityRoleFunctionsByRoleId(int roleId, std::vector<AllTrade::AuthorityRoleFunctionsPtr>& vecAuthority);
		// �жϽ�ɫ�͹����Ƿ��й�ϵ
		ErrorCodeType judgeRoleAndFunctionsRelationOne(int roleId);
		// �ж�ĳ����ɫ��ĳ�������Ƿ���ڹ�ϵ
		int judgeRoleAndFunctionsRelationTwo(int nFunctionID, int nRoleId, int* nCount);
		// ��ȡ���н�ɫ / ���ܹ�ϵ
		int getAllAuthorityRoleFunctions(std::vector<AllTrade::AuthorityRoleFunctionsPtr>& vecAuthority);

		// ��ȡ���д�������Ϣ
		int GetAllAgentInfo(std::map<int, std::set<int>>& mapInfo);

		// ��ѯ����Ĺ���
		ErrorCodeType getSelfFunctionsByLoginName(const LoginNameType loginName, std::vector<AuthorityFunctionsUserIdPtr> &vecAuthorityFunctions);

		// ��ѯ����ҵ��
		ErrorCodeType getAllBussness(std::vector<AuthorityBussnessesPtr>& vec);

	private:
		std::map<std::string, std::set<std::string>> m_mapManager; // �������еĹ�����<parentid/userid>
		std::set<std::string> m_setUserId;    // ���������¼�������
		std::map<std::string, std::string> m_mapManagerInfo; // <id / login>
	};

}
#endif