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
		// 增加交易用户信息
		int addTradeUserInfo(const TradeUserInfoPtr& userInfo);
		// 删除用交易户信息
		int deleteTradeUserInfo(int userID);
		// 修改交易用户信息
		int updateTradeUserInfo(TradeUserInfoPtr& userInfo);
		// 查询交易用户名称
		int getTradeUserNameByUserID(int userID, char* userLevelName);
		// 查询交易用户信息
		int getTradeUserInfoByUserID(int userID, TradeUserInfoPtr& userInfo);
		// 查询某个机构ID下的所有交易用户
		int queryTradeUserInfoByInstitutionID(int userID, std::vector<TradeUserInfoPtr>& vecInfo);
		// 查询某个代理商ID下的所有交易用户
		int queryTradeUserInfoByAgentID(int userID, std::vector<TradeUserInfoPtr>& vecInfo);
		// 查询某个普通交易用户下的所有推广用户
		int queryPopularizeUserInfoByUserID(int userID, std::vector<TradeUserInfoPtr>& vecInfo);
		// 查询某交易用户属于哪个机构
		int queryInsititutionInfo(int userID, InsititutionStPtr& userInfo);
		// 查询某交易用户属于哪个代理商
		int queryAgentInfo(int userID, AgentstPtr& userInfo);
		// 查询某交易用户属于哪个推广用户
		int queryPopularizeUserInfo(int userID, TradeUserInfoPtr& userInfo);
		// 修改交易用户密码
		int updateTradeUserPassword(int userID, const AllTrade::ChangeUserPswSt& psw);
		// 修改交易用户昵称
		int updateTradeUserNickName(int userID, const AllTrade::ChangeUserNickSt& nickName);
		// 获取所有的交易账户用户
		int getAllTradeUserInfo(std::vector<TradeUserInfoPtr>& vecUserInfo);
	};
}


