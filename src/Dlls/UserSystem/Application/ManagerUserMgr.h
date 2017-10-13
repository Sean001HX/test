#pragma once
#include<vector>
#include "utility/instance.h"
#include "define/struct_declare.h"
namespace AllTrade
{
	class ManagerUserMgr
		: public CommonTools::instance_unshared<ManagerUserMgr>
	{
	public:
		ManagerUserMgr();
		~ManagerUserMgr();
	public:
		//  创建管理员
		int addManagerUserInfo(const ManagerUserInfoPtr & userInfo);
		//  删除管理员
		int deleteManagerUserInfo(int ManagerID);
		//  修改管理员信息
		int updateManagerUserInfo(ManagerUserInfoPtr& userInfo);
		//  获取管理员信息
		int getManagerUserInfoByManagerID(int ManagerID, ManagerUserInfoPtr& userInfo);
		
	};
}
