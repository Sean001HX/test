#pragma once

#ifdef AUTHORITY_EXPORTS
#define AUTHORITY_API __declspec(dllexport)
#else
#define AUTHORITY_API __declspec(dllimport)
#endif

#include "utility/instance_shared_from_this.h"
#include <map>
#include <set>
#include <vector>
#include <mutex>
#include <memory>
#include "define/struct_declare.h"
#include "define/params_declare.h"
#include "define/authorityState_def.h"

#ifdef _MSC_VER
#	pragma warning(push)
#   pragma warning(disable: 4251) 
// #	pragma warning(disable: 4275) // �� DLL �ӿ������identifier����Ϊ DLL �ӿ������identifier���Ļ�ʹ��
#endif
using namespace AllTrade;

namespace AuthorityControl
{
	class CAuthorityControlImpl;

	class AUTHORITY_API CAuthorityControl : public CommonTools::instance_shared_from_this<CAuthorityControl>
	{
	public:
		CAuthorityControl();
		~CAuthorityControl();

	public:
		// �ж��û��Ƿ���������û���ѯ�Ĺ���Ȩ��
		// loginName:��¼��
		// ����:trueΪ����,false������
        bool isHaveOnLineUserAuthority(const AllTrade::LoginNameType loginName) const;
	public:
		////////////////////////////// ��ɫ��غ���
		// ��ȡ��ɫ��Ϣ
		// nUserId���˻�ID
		// ���أ����󷵻ط�0
		ErrorCodeType getRolesUserInfo(const UserIDType userid, std::vector<AllTrade::AuthorityRolesPtr>& vecRolesInfo);
		// ���ӽ�ɫ
		// ���أ����󷵻ط�0
		ErrorCodeType addRolesUserInfo(AllTrade::AuthorityRolesPtr& rolesInfo);
		// ɾ����ɫ
		// nRoleId����ɫID
		// ���أ����󷵻ط�0
		ErrorCodeType deleteRolesUser(int nRoleId);
		// �޸Ľ�ɫ
		// ���أ����󷵻ط�0
		ErrorCodeType updateRolesUserInfo(const AllTrade::AuthorityRolesPtr& rolesInfo);

		// �ж��Ƿ����иý�ɫ��
        ErrorCodeType isHaveRoleName(const AllTrade::LoginNameType roleName);


		/////////////////////////// �ж��û��Ƿ���д˹���Ȩ��
		// ����ֵ��Error_UserAndFunction_Exist ===> ���˻����ڴ˹��� / ����������
        ErrorCodeType isHaveAuthority(const AllTrade::LoginNameType loginName, int nFunctionId) const;


		/////////////////////////// ��ɫ / �û���������
		// 
		// ���أ����󷵻ط�0
        ErrorCodeType getAuthorityRoleUsers(const AllTrade::LoginNameType roleName, std::vector<AllTrade::AuthorityRoleUsersPtr>& vecAuthority);
		// ���أ����󷵻ط�0
		ErrorCodeType addAuthorityRoleUsers(const std::vector<AllTrade::AuthorityRoleUsersPtr>& vecAuthority);
		// ���أ����󷵻ط�0
		ErrorCodeType deleteAuthorityRoleUsers(const std::vector<AllTrade::AuthorityRoleUsersPtr>& vecAuthority);
		// �жϸý�ɫ�Ƿ��û��󶨹�ϵ
		// ���أ����󷵻ط�0
		ErrorCodeType judgeRoleUsersRelation(int roleId);
		// �ж�ĳ����ɫ��ĳ���û��Ƿ���ڹ�ϵ
		// ���أ����󷵻ط�0
        ErrorCodeType judgeRoleUsersRelation(const AllTrade::LoginNameType loginName, int nRoleId);
		// �жϸ��û��Ƿ�󶨽�ɫ
		// ����ֵ��Error_RoleUser_Exist ===> ���˻����ڰ󶨹�ϵ / Err_Database ���ݿ����ʧ�� / Err_Succeed �����ڰ󶨹�ϵ
		ErrorCodeType judgeRoleUsersRelation(const AllTrade::LoginNameType loginName);
		// �޸��û��ͽ�ɫ֮���ϵ
		ErrorCodeType changeAuthorityRoleUsers(const AllTrade::AuthorityRoleUsersPtr& ptr);

		/////////////////////////// ��ɫ / ����
		// ���أ����󷵻ط�0
		ErrorCodeType addAuthorityRoleFunctions(int roleId, const std::vector<AllTrade::AuthorityRoleFunctionsPtr>& vecAuthority);
		// ���أ����󷵻ط�0
		ErrorCodeType deleteAuthorityRoleFunctions(const std::vector<AllTrade::AuthorityRoleFunctionsPtr>& vecAuthority);
		// ���أ����󷵻ط�0
		// ��ȡ�ý�ɫ��Ӧ�����й���
		ErrorCodeType getAuthorityRoleFunctionsByRoleId(int roleId, std::vector<AllTrade::AuthorityRoleFunctionsPtr>& vecAuthority);
		// �жϽ�ɫ�Ƿ񱻹��� �󶨹�ϵ
		// ���أ����󷵻ط�0
		ErrorCodeType judgeRoleAndFunctionsRelationOne(int nRoleId);
		// �ж�ĳ����ɫ��ĳ�������Ƿ���ڹ�ϵ
		// ���أ����󷵻ط�0
		int judgeRoleAndFunctionsRelationTwo(int nFunctionID, int nRoleId);

		// ɾ����ɫ / ���ܹ�ϵ�Ĵ���
		// ˵����vecAuthority����ģ�lowAuthorityΪ��ȡ��
		// ���أ����󷵻�false
		bool handleDelAuthorityRoleFunctions(const std::vector<AllTrade::AuthorityRoleFunctionsPtr>& vecAuthority, std::vector<AllTrade::AuthorityRoleFunctionsPtr>& lowAuthority);

		// ��ѯ����Ĺ���
		ErrorCodeType getSelfFunctionsByLoginName(const LoginNameType loginName, std::vector<AuthorityFunctionsUserIdPtr> &vecAuthorityFunctions);

		// ��ѯ����ҵ��
		ErrorCodeType getAllBussness(std::vector<AuthorityBussnessesPtr>& vec);
	private:
		std::recursive_mutex                    mtx_roles;
	
	private:
		CAuthorityControlImpl* m_authorityImpl;
	};
}

#if defined(_MSC_VER)
#	pragma warning(pop)
#endif