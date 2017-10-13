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
		//  ����ʵ���û���Ϣ
		int addFirmUserInfo(const FirmUserInfoPtr& userInfo);
		//  ɾ��ʵ���û���Ϣ
		int deleteFirmUserInfo(int firmID);
		//  �޸Ľ����û���Ϣ
		int updateFirmUserInfo(FirmUserInfoPtr& userInfo);
		//  ���ʵ���û���Ϣ
		int getFirmUserInfoByFirmID(int firmID, FirmUserInfoPtr& userInfo);
	};
}


