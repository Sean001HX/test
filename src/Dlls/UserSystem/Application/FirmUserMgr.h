#pragma once
#include "utility/instance.h"
#include "define/struct_declare.h"
namespace AllTrade
{
	class FirmUserMgr
		: public CommonTools::instance_unshared<FirmUserMgr>
	{
	public:
		FirmUserMgr();
		~FirmUserMgr();
		//  增加实盘用户信息
		int addFirmUserInfo(const FirmUserInfoPtr& userInfo);
		//  删除实盘用户信息
		int deleteFirmUserInfo(int firmID);
		//  修改交易用户信息
		int updateFirmUserInfo(FirmUserInfoPtr& userInfo);
		//  获得实盘用户信息
		int getFirmUserInfoByFirmID(int firmID, FirmUserInfoPtr& userInfo);
	};
}


