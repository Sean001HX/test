#pragma once
#include "define/struct_declare.h"
#include "define/struct_extern.h"
#include <map>
#include <set>
#include <vector>
#include <mutex>
#include <memory>
#include <string>

using namespace AllTrade;
namespace AuthorityControl
{
	class CAuthorityControlImpl
	{
	public:
		CAuthorityControlImpl();
		~CAuthorityControlImpl();

	public:
		////////////////////////////// ��ɫ��غ���
		// ��ȡ��ɫ��Ϣ
		// nUserId���˻�ID
		// ���أ����󷵻�false
		ErrorCodeType getRolesUserInfo(const UserIDType userid, std::vector<AllTrade::AuthorityRolesPtr>& vecRolesInfo);
		// ���ӽ�ɫ
		// ���أ����󷵻�false
		ErrorCodeType addRolesUserInfo(AllTrade::AuthorityRolesPtr& rolesInfo);
		// ɾ����ɫ
		// nRoleId����ɫID
		// ���أ����󷵻�false
		ErrorCodeType deleteRolesUser(int nRoleId);
		// �޸Ľ�ɫ
		// ���أ����󷵻�false
		ErrorCodeType updateRolesUserInfo(const AllTrade::AuthorityRolesPtr& rolesInfo);

		// �ж��Ƿ����иý�ɫ��
		ErrorCodeType isHaveRoleName(const AllTrade::LoginNameType roleName);

		// ͨ����ɫId��ȡ�û�ID
		// nUserId���û�ID
		void getRolesIdByUserId(int nUserId, std::set<int>& rolesId);

		/////////////////////////// �ж��û��Ƿ���д˹���Ȩ��
		// nUserId: �û�ID
		// nFunctionId������ID
		// nCount: �Ƿ���ڹ�ϵ��־��0�������� / >0 ����
		// ����ֵ��false�޴�Ȩ��
		ErrorCodeType isHaveAuthority(const AllTrade::LoginNameType loginName, int nFunctionId) const;


		/////////////////////////// ��ɫ / �û�
		ErrorCodeType getAuthorityRoleUsers(const AllTrade::LoginNameType loginName, std::vector<AllTrade::AuthorityRoleUsersPtr>& vecAuthority);
		ErrorCodeType addAuthorityRoleUsers(const std::vector<AllTrade::AuthorityRoleUsersPtr>& vecAuthority);
		ErrorCodeType deleteAuthorityRoleUsers(const std::vector<AllTrade::AuthorityRoleUsersPtr>& vecAuthority);
		// �жϽ�ɫ���û��Ƿ��й�ϵ
		ErrorCodeType judgeRoleUsersRelation(int roleId);
		// �ж�ĳ����ɫ��ĳ���û��Ƿ���ڹ�ϵ
		ErrorCodeType judgeRoleUsersRelation(const AllTrade::LoginNameType loginName, int nRoleId);
		// �ҵ���ĳ��ɫ�й�ϵ�����д�����
		bool getAllAgentHaveRelation(std::set<int>& setInfo, int roleId);
		// �жϸ��û��Ƿ�󶨽�ɫ
		ErrorCodeType judgeRoleUsersRelation(const AllTrade::LoginNameType loginName);
		// �޸��û��ͽ�ɫ֮���ϵ
		ErrorCodeType changeAuthorityRoleUsers(const AllTrade::AuthorityRoleUsersPtr& ptr);

		/////////////////////////// ��ɫ / ����
		ErrorCodeType getAllAuthorityRoleFunctions(std::vector<AllTrade::AuthorityRoleFunctionsPtr>& vecAuthority);
		ErrorCodeType addAuthorityRoleFunctions(int roleId, const std::vector<AllTrade::AuthorityRoleFunctionsPtr>& vecAuthority);
		ErrorCodeType deleteAuthorityRoleFunctions(const std::vector<AllTrade::AuthorityRoleFunctionsPtr>& vecAuthority);
		// ��ȡ��ɫ�����еĹ���
		int getAuthorityRoleFunctionsByRoleId(int roleId, std::vector<AllTrade::AuthorityRoleFunctionsPtr>& vecAuthority);
		// �жϽ�ɫ�͹����Ƿ��й�ϵ
		ErrorCodeType judgeRoleAndFunctionsRelationOne(int nRoleId);
		// �ж�ĳ����ɫ��ĳ�������Ƿ���ڹ�ϵ
		int judgeRoleAndFunctionsRelationTwo(int nFunctionID, int nRoleId);
		

		// ɾ����ɫ / ���ܹ�ϵ�Ĵ���
		// ˵����vecAuthority����ģ�lowAuthorityΪ��ȡ��
		bool handleDelAuthorityRoleFunctions(const std::vector<AllTrade::AuthorityRoleFunctionsPtr>& vecAuthority, std::vector<AllTrade::AuthorityRoleFunctionsPtr>& lowAuthority);
		// �ݹ���
		// userId ���û�ID
		void  checkLowerUsers(int userId);
		// ���������¼������̵ĸ�ɾ��Ȩ��
		// ˵����nRoleId ��ɫID�� vecAuthority����ģ�lowAuthorityΪ��ȡ��
		// ����ֵ�� falseʧ�ܣ�true�ɹ�
		bool getLowerAuthoryFunctions(int nRoleId, const std::vector<AllTrade::AuthorityRoleFunctionsPtr>& vecAuthority, std::vector<AllTrade::AuthorityRoleFunctionsPtr>& lowAuthority);
		// ��ȡ���еĹ���Ա�������̣���Ϣ
		bool getAllAgentInfo();

		// ��ѯ����Ĺ���
		ErrorCodeType getSelfFunctionsByLoginName(const LoginNameType loginName, std::vector<AuthorityFunctionsUserIdPtr> &vecAuthorityFunctions);

		// ��ѯ����ҵ��
		ErrorCodeType getAllBussness(std::vector<AuthorityBussnessesPtr>& vec);

		private:
		std::map<int, std::set<int>> m_mapInfo; //  parentid / userid 
		std::set<int> m_setUserId;    // ���������¼�������
	};
}
