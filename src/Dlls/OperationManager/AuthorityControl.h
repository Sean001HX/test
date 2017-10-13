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


		// 初始化数据库表
		bool initAllTable();

		// 权限业务表
		bool createAuthorityBussnesses();
		// 权限日志表
		bool createAuthorityLog();
		// 权限功能表
		bool createAuthorityFunctions();
		// 权限角色功能表
		bool createAuthorityRoleFunctions();
		// 权限角色用户表
		bool createAuthorityRoleUsers();
		// 权限角色表
		bool createAuthorityRoles();

		// 根据loginname查询userid（管理者）
		std::string getUserIdByLoginName(const LoginNameType loginName);
		// 查询所有管理者(含机构) parentid / userid 
		int getAllManager(std::map<std::string, std::set<std::string>>& mapManager);

		// 递归检查
		void  checkLowerUsers(std::string userId);
		///////////////////////////////////////////// 角色相关操作 ////////////////////////////////////
		// 查询角色操作：通过userId查找角色
		ErrorCodeType getRolesUserInfo(const UserIDType userid, std::vector<AuthorityRolesPtr> &vecRolesInfo);
		// 查询角色操作：通过userId查找角色
		int handleGetRolesUserInfo(const LoginNameType loginName, std::vector<AuthorityRolesPtr> &vecRolesInfo);
		
		// 增加角色操作
		ErrorCodeType addRolesUserInfo(AuthorityRolesPtr& rolesInfo);
		// 修改角色操作
		ErrorCodeType updateRolesUserInfo(const AuthorityRolesPtr& rolesInfo);
		// 删除角色操作：通过角色Id删除
		ErrorCodeType deleteRolesUser(int rolesID);
		// 判断是否已有该角色名
        ErrorCodeType isHaveRoleName(const AllTrade::LoginNameType roleName);

		/////////////////////////// 判断某用户是否具有某功能权限 ////////////////////////////////////
        ErrorCodeType isHaveAuthority(const AllTrade::LoginNameType loginName, int nFunctionId)const;

		////////////////////////// 用户和角色 //////////////////////////////////////////
		// 获取用户和角色之间关系
        ErrorCodeType getAuthorityRoleUsers(const AllTrade::LoginNameType loginName, std::vector<AllTrade::AuthorityRoleUsersPtr>& vecAuthority);
		// 获取用户和角色之间关系
        ErrorCodeType handleGetAuthorityRoleUsers(const AllTrade::LoginNameType loginName, std::vector<AllTrade::AuthorityRoleUsersPtr>& vecAuthority);

		// 增加用户和角色之间关系
		ErrorCodeType addAuthorityRoleUsers(const std::vector<AllTrade::AuthorityRoleUsersPtr>& vecAuthority);
		// 删除用户和角色之间关系
		ErrorCodeType deleteAuthorityRoleUsers(const std::vector<AllTrade::AuthorityRoleUsersPtr>& vecAuthority);

		// 判断角色是否存在和用户之间关系
		ErrorCodeType judgeRoleUsersRelation(int roleId);
		// 判断某个角色和某个用户是否存在关系
        ErrorCodeType judgeRoleUsersRelation(const AllTrade::LoginNameType loginName, int nRoleId);
		// 找到和某角色有关系的所有代理商
		int getAllAgentHaveRelation(std::set<int>& setInfo, int nRoleId);
		// 判断该用户是否绑定角色
		ErrorCodeType judgeRoleUsersRelation(const AllTrade::LoginNameType loginName);

		// 修改用户和角色之间关系
		ErrorCodeType changeAuthorityRoleUsers(const AllTrade::AuthorityRoleUsersPtr& ptr);

		/////////////////////////// 角色 / 功能
		// 添加所有角色 / 功能关系
		ErrorCodeType addAuthorityRoleFunctions(int roleId, const std::vector<AllTrade::AuthorityRoleFunctionsPtr>& vecAuthority);
		// 删除所有角色 / 功能关系
		ErrorCodeType deleteAuthorityRoleFunctions(const std::vector<AllTrade::AuthorityRoleFunctionsPtr>& vecAuthority);
		// 获取所有角色 / 功能关系
		ErrorCodeType getAuthorityRoleFunctionsByRoleId(int roleId, std::vector<AllTrade::AuthorityRoleFunctionsPtr>& vecAuthority);
		// 判断角色和功能是否有关系
		ErrorCodeType judgeRoleAndFunctionsRelationOne(int roleId);
		// 判断某个角色和某个功能是否存在关系
		int judgeRoleAndFunctionsRelationTwo(int nFunctionID, int nRoleId, int* nCount);
		// 获取所有角色 / 功能关系
		int getAllAuthorityRoleFunctions(std::vector<AllTrade::AuthorityRoleFunctionsPtr>& vecAuthority);

		// 获取所有代理商信息
		int GetAllAgentInfo(std::map<int, std::set<int>>& mapInfo);

		// 查询自身的功能
		ErrorCodeType getSelfFunctionsByLoginName(const LoginNameType loginName, std::vector<AuthorityFunctionsUserIdPtr> &vecAuthorityFunctions);

		// 查询所有业务
		ErrorCodeType getAllBussness(std::vector<AuthorityBussnessesPtr>& vec);

	private:
		std::map<std::string, std::set<std::string>> m_mapManager; // 保存所有的管理者<parentid/userid>
		std::set<std::string> m_setUserId;    // 保存所有下级代理商
		std::map<std::string, std::string> m_mapManagerInfo; // <id / login>
	};

}
#endif