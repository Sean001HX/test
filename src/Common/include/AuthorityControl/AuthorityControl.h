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
// #	pragma warning(disable: 4275) // 非 DLL 接口类键“identifier”作为 DLL 接口类键“identifier”的基使用
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
		// 判断用户是否具有在线用户查询的功能权限
		// loginName:登录名
		// 返回:true为存在,false不存在
        bool isHaveOnLineUserAuthority(const AllTrade::LoginNameType loginName) const;
	public:
		////////////////////////////// 角色相关函数
		// 获取角色信息
		// nUserId：账户ID
		// 返回：错误返回非0
		ErrorCodeType getRolesUserInfo(const UserIDType userid, std::vector<AllTrade::AuthorityRolesPtr>& vecRolesInfo);
		// 增加角色
		// 返回：错误返回非0
		ErrorCodeType addRolesUserInfo(AllTrade::AuthorityRolesPtr& rolesInfo);
		// 删除角色
		// nRoleId：角色ID
		// 返回：错误返回非0
		ErrorCodeType deleteRolesUser(int nRoleId);
		// 修改角色
		// 返回：错误返回非0
		ErrorCodeType updateRolesUserInfo(const AllTrade::AuthorityRolesPtr& rolesInfo);

		// 判断是否已有该角色名
        ErrorCodeType isHaveRoleName(const AllTrade::LoginNameType roleName);


		/////////////////////////// 判断用户是否具有此功能权限
		// 返回值：Error_UserAndFunction_Exist ===> 该账户存在此功能 / 其他不存在
        ErrorCodeType isHaveAuthority(const AllTrade::LoginNameType loginName, int nFunctionId) const;


		/////////////////////////// 角色 / 用户（机构）
		// 
		// 返回：错误返回非0
        ErrorCodeType getAuthorityRoleUsers(const AllTrade::LoginNameType roleName, std::vector<AllTrade::AuthorityRoleUsersPtr>& vecAuthority);
		// 返回：错误返回非0
		ErrorCodeType addAuthorityRoleUsers(const std::vector<AllTrade::AuthorityRoleUsersPtr>& vecAuthority);
		// 返回：错误返回非0
		ErrorCodeType deleteAuthorityRoleUsers(const std::vector<AllTrade::AuthorityRoleUsersPtr>& vecAuthority);
		// 判断该角色是否被用户绑定关系
		// 返回：错误返回非0
		ErrorCodeType judgeRoleUsersRelation(int roleId);
		// 判断某个角色和某个用户是否存在关系
		// 返回：错误返回非0
        ErrorCodeType judgeRoleUsersRelation(const AllTrade::LoginNameType loginName, int nRoleId);
		// 判断该用户是否绑定角色
		// 返回值：Error_RoleUser_Exist ===> 该账户存在绑定关系 / Err_Database 数据库操作失败 / Err_Succeed 不存在绑定关系
		ErrorCodeType judgeRoleUsersRelation(const AllTrade::LoginNameType loginName);
		// 修改用户和角色之间关系
		ErrorCodeType changeAuthorityRoleUsers(const AllTrade::AuthorityRoleUsersPtr& ptr);

		/////////////////////////// 角色 / 功能
		// 返回：错误返回非0
		ErrorCodeType addAuthorityRoleFunctions(int roleId, const std::vector<AllTrade::AuthorityRoleFunctionsPtr>& vecAuthority);
		// 返回：错误返回非0
		ErrorCodeType deleteAuthorityRoleFunctions(const std::vector<AllTrade::AuthorityRoleFunctionsPtr>& vecAuthority);
		// 返回：错误返回非0
		// 获取该角色对应的所有功能
		ErrorCodeType getAuthorityRoleFunctionsByRoleId(int roleId, std::vector<AllTrade::AuthorityRoleFunctionsPtr>& vecAuthority);
		// 判断角色是否被功能 绑定关系
		// 返回：错误返回非0
		ErrorCodeType judgeRoleAndFunctionsRelationOne(int nRoleId);
		// 判断某个角色和某个功能是否存在关系
		// 返回：错误返回非0
		int judgeRoleAndFunctionsRelationTwo(int nFunctionID, int nRoleId);

		// 删除角色 / 功能关系的处理
		// 说明：vecAuthority传入的；lowAuthority为获取的
		// 返回：错误返回false
		bool handleDelAuthorityRoleFunctions(const std::vector<AllTrade::AuthorityRoleFunctionsPtr>& vecAuthority, std::vector<AllTrade::AuthorityRoleFunctionsPtr>& lowAuthority);

		// 查询自身的功能
		ErrorCodeType getSelfFunctionsByLoginName(const LoginNameType loginName, std::vector<AuthorityFunctionsUserIdPtr> &vecAuthorityFunctions);

		// 查询所有业务
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