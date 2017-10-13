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
		//  ��������Ա
		int addManagerUserInfo(const ManagerUserInfoPtr & userInfo);
		//  ɾ������Ա
		int deleteManagerUserInfo(int ManagerID);
		//  �޸Ĺ���Ա��Ϣ
		int updateManagerUserInfo(ManagerUserInfoPtr& userInfo);
		//  ��ȡ����Ա��Ϣ
		int getManagerUserInfoByManagerID(int ManagerID, ManagerUserInfoPtr& userInfo);
		
	};
}
