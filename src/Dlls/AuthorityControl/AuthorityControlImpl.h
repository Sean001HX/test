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
		////////////////////////////// 角色相关函数
		// 获取角色信息
		// nUserId：账户ID
		// 返回：错误返回false
		ErrorCodeType getRolesUserInfo(const UserIDType userid, std::vector<AllTrade::AuthorityRolesPtr>& vecRolesInfo);
		// 增加角色
		// 返回：错误返回false
		ErrorCodeType addRolesUserInfo(AllTrade::AuthorityRolesPtr& rolesInfo);
		// 删除角色
		// nRoleId：角色ID
		// 返回：错误返回false
		ErrorCodeType deleteRolesUser(int nRoleId);
		// 修改角色
		// 返回：错误返回false
		ErrorCodeType updateRolesUserInfo(const AllTrade::AuthorityRolesPtr& rolesInfo);

		// 判断是否已有该角色名
		ErrorCodeType isHaveRoleName(const AllTrade::LoginNameType roleName);

		// 通过角色Id获取用户ID
		// nUserId：用户ID
		void getRolesIdByUserId(int nUserId, std::set<int>& rolesId);

		/////////////////////////// 判断用户是否具有此功能权限
		// nUserId: 用户ID
		// nFunctionId：功能ID
		// nCount: 是否存在关系标志；0：不存在 / >0 存在
		// 返回值：false无此权限
		ErrorCodeType isHaveAuthority(const AllTrade::LoginNameType loginName, int nFunctionId) const;


		/////////////////////////// 角色 / 用户
		ErrorCodeType getAuthorityRoleUsers(const AllTrade::LoginNameType loginName, std::vector<AllTrade::AuthorityRoleUsersPtr>& vecAuthority);
		ErrorCodeType addAuthorityRoleUsers(const std::vector<AllTrade::AuthorityRoleUsersPtr>& vecAuthority);
		ErrorCodeType deleteAuthorityRoleUsers(const std::vector<AllTrade::AuthorityRoleUsersPtr>& vecAuthority);
		// 判断角色和用户是否有关系
		ErrorCodeType judgeRoleUsersRelation(int roleId);
		// 判断某个角色和某个用户是否存在关系
		ErrorCodeType judgeRoleUsersRelation(const AllTrade::LoginNameType loginName, int nRoleId);
		// 找到和某角色有关系的所有代理商
		bool getAllAgentHaveRelation(std::set<int>& setInfo, int roleId);
		// 判断该用户是否绑定角色
		ErrorCodeType judgeRoleUsersRelation(const AllTrade::LoginNameType loginName);
		// 修改用户和角色之间关系
		ErrorCodeType changeAuthorityRoleUsers(const AllTrade::AuthorityRoleUsersPtr& ptr);

		/////////////////////////// 角色 / 功能
		ErrorCodeType getAllAuthorityRoleFunctions(std::vector<AllTrade::AuthorityRoleFunctionsPtr>& vecAuthority);
		ErrorCodeType addAuthorityRoleFunctions(int roleId, const std::vector<AllTrade::AuthorityRoleFunctionsPtr>& vecAuthority);
		ErrorCodeType deleteAuthorityRoleFunctions(const std::vector<AllTrade::AuthorityRoleFunctionsPtr>& vecAuthority);
		// 获取角色下所有的功能
		int getAuthorityRoleFunctionsByRoleId(int roleId, std::vector<AllTrade::AuthorityRoleFunctionsPtr>& vecAuthority);
		// 判断角色和功能是否有关系
		ErrorCodeType judgeRoleAndFunctionsRelationOne(int nRoleId);
		// 判断某个角色和某个功能是否存在关系
		int judgeRoleAndFunctionsRelationTwo(int nFunctionID, int nRoleId);
		

		// 删除角色 / 功能关系的处理
		// 说明：vecAuthority传入的；lowAuthority为获取的
		bool handleDelAuthorityRoleFunctions(const std::vector<AllTrade::AuthorityRoleFunctionsPtr>& vecAuthority, std::vector<AllTrade::AuthorityRoleFunctionsPtr>& lowAuthority);
		// 递归检查
		// userId ：用户ID
		void  checkLowerUsers(int userId);
		// 查找所有下级代理商的该删除权限
		// 说明：nRoleId 角色ID； vecAuthority传入的；lowAuthority为获取的
		// 返回值： false失败，true成功
		bool getLowerAuthoryFunctions(int nRoleId, const std::vector<AllTrade::AuthorityRoleFunctionsPtr>& vecAuthority, std::vector<AllTrade::AuthorityRoleFunctionsPtr>& lowAuthority);
		// 获取所有的管理员（代理商）信息
		bool getAllAgentInfo();

		// 查询自身的功能
		ErrorCodeType getSelfFunctionsByLoginName(const LoginNameType loginName, std::vector<AuthorityFunctionsUserIdPtr> &vecAuthorityFunctions);

		// 查询所有业务
		ErrorCodeType getAllBussness(std::vector<AuthorityBussnessesPtr>& vec);

		private:
		std::map<int, std::set<int>> m_mapInfo; //  parentid / userid 
		std::set<int> m_setUserId;    // 保存所有下级代理商
	};
}
