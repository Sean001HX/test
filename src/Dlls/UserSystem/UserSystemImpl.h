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
		////////////////////////////// 基本用户相关函数
		// 增加用户信息
		// 返回：错误返回-1
		int addUserInfo(AccountTypeType type,const UserInfoPtr & userInfo);
		// 删除用户信息
		// userId：账户ID
		// 返回：错误返回-1
		int deleteUserInfo(AccountTypeType type, int userID);
		// 修改用户信息
		// 返回：错误返回-1
		int updateUserInfo(AccountTypeType type, UserInfoPtr & userInfo);
		// 查询用户信息
		// userId：账户ID
		// 返回：错误返回-1
		int getUserInfoByUserID(int userID, AccountTypeType type, UserInfoPtr &userInfo);
		// 修改用户密码
		// userId：账户ID
		// 返回：错误返回-1
		int updateUserPassword(int userID, AccountTypeType type, const AllTrade::ChangeUserPswSt& psw);
		// 修改用户昵称
		// userId：账户ID
		// 返回：错误返回-1
		int updateUserNickName(int userID, const AllTrade::ChangeUserNickSt& nickName);
		//// 查询用户名称
		//// userId：账户ID
		//// 返回：错误返回-1
		//int getUserLevelNameByUserID(int userID, AccountTypeType type, LevelInfoPtr&  levelName);

		////////////////////////////// 用户查询相关函数
		//查询某个机构ID下的所有用户
		// userId：机构ID
		// 返回：错误返回-1
		int queryUserInfoByInstitutionID(int userID, std::vector<TradeUserInfoPtr>& vecInfo);
		// 查询某个代理商ID下的所有用户
		// userId：代理商ID
		// 返回：错误返回-1
		int queryUserInfoByAgentID(int userID, std::vector<TradeUserInfoPtr>& vecInfo);
		// 查询某个普通用户下的所有推广用户
		// userId：账户ID
		// 返回：错误返回-1
		int queryPopularizeUserInfoByUserID(int userID, std::vector<TradeUserInfoPtr>& vecInfo);

		// 查询某用户属于哪个机构
		// userId：账户ID
		// 返回：错误返回-1
		int queryInsititutionInfo(int userID, InsititutionStPtr& userInfo);
		// 查询某用户属于哪个代理商
		// userId：账户ID
		// 返回：错误返回-1
		int queryAgentInfo(int userID, AgentstPtr& userInfo);
		// 查询某用户属于哪个推广用户
		// userId：账户ID
		// 返回：错误返回-1
		int queryPopularizeUserInfo(int userID, TradeUserInfoPtr& userInfo);


		//////////////////////////////// 机构相关函数
		// 创建机构
		// 返回：错误返回-1
		int addUserTypeInfo(const InsititutionStPtr& userTypeInfo);
		//  删除机构
		// institutionID：机构ID
		// 返回：错误返回-1
		int deleteInsititutionUserInfo(int InsititutionID);
		//  修改机构信息
		//  返回：错误返回-1
		int updateInsititutionUserInfo(InsititutionStPtr& userInfo);
		//  获取某机构信息
		//  institutionID：机构ID
		//  返回：错误返回-1
		int getInstitutionInfolByInsitionID(int InsititutionID, InsititutionStPtr& userInfo);
		//  获取某个机构的所有实盘账户
		//  institutionID：机构ID
		//  返回：错误返回-1
		int getAllFillUserInfoByInsitutionID(int insititutionID, std::vector<FirmUserInfoPtr>& vecInfo);
		//// 获取某机构名称
		//// institutionID：机构ID
		//// 返回：错误返回-1
		//int getInstitutionNameByUserID(int institutionID, char* institutionName);
		//// 获取某机构层级
		//// institutionID：机构ID
		//// 返回：错误返回-1
		//int getInstitutionLevelByUserID(int levelID, int* level);
		//// 获取某机构信息
		//// institutionID：机构ID
		//// 返回：错误返回-1
		//int getInstitutionInfoByUserID(int institutionID, InsititutionStPtr& insitutionInfo);
		// 查询某个机构下的代理商
		// institutionID：机构ID
		// 返回：错误返回-1
		int getAgentInfoByUserID(int institutionID, std::vector<AgentstPtr>& vecInfo);


		////////////////////////////// 代理商相关函数
		////创建代理商
		////返回：错误返回-1
		//int addAgentInfo(const AgentstPtr& insititutionInfo);
		//// 获取某代理商名称
		//// agentID：代理商ID
		//// 返回：错误返回-1
		//int getAgentNameByUserID(int agentID, char* agentName);
		// 获取某代理商层级
		// agentID：代理商ID
		// 返回：错误返回-1
		int getAgentLevelByUserID(int agentID, int*  level);
		//// 获取某代理商信息
		//// agentID：代理商ID
		//// 返回：错误返回-1
		//int getAgentInfoByUserID(int agentID, AgentstPtr& agentInfo);


		////////////////////////////// 管理员相关函数
		////创建管理员
		////返回：错误返回-1
		//int  addManagerInfo(const UserInfoPtr& managerInfo);
		// 获取某个机构的所有管理员
		// agentID：机构ID
		// 返回：错误返回-1
		int  getAllManagerInfoByInsitutionID(int insititutionID, std::vector<ManagerUserInfoPtr>& vecInfo);


		////////////////////////////// 系统设置相关函数
		// 获取允许的机构深度
		// agentID：机构ID
		// 返回：错误返回-1
		int  getLevelByInsititutionID(int insititutionID, int * level);
		// 获取允许的代理商深度
		// agentID：代理商ID
		// 返回：错误返回-1
		int  getLevelByAgentID(int agentID, int * level);
	};
}


