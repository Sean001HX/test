#include "GlobalData.h"
#include"TradeUserMgr.h"
#include"define/protocol_error.h"
namespace AllTrade
{
	static CHxMutex tradeMutex;
	GlobalData::GlobalData()
	{

	}


	GlobalData::~GlobalData()
	{

	}

	bool GlobalData::Checkparams(UserInfoPtr& userInfo)
	{
		if (!userInfo)
			return false;
		InsititutionStPtr insitutionInfo = std::make_shared<InsititutionSt>();
		TradeUserMgr::instance()->queryInsititutionInfo(userInfo->userID, insitutionInfo);
		if (!insitutionInfo)
			return  false;
		RtnInfoWithoutSendFlag<UserInfoPtr> rtnReqInfo;
		rtnReqInfo.errCode = 0;
		rtnReqInfo.data = userInfo;
		if (insitutionInfo->attrType < (int)AccountTypeType::Account_Type_Agent)
		{
			rtnReqInfo.errCode = Err_Not_Login;

			return false;
		}
		 {
			 CHxMutexGuard mutex(&tradeMutex);
			 UserInfoPtr pUserInfo = rtnReqInfo.data;

			 if (pUserInfo->attrType >= (int)AccountTypeType::Account_Type_Insitution)
			 {
				 rtnReqInfo.errCode = Err_Init_FAIL1;

				 return false;
			 }
			 if (pUserInfo->attrType == (int)AccountTypeType::Account_Type_Trade)
			 {
				 TradeUserInfoPtr tradeInfo = std::dynamic_pointer_cast<TradeUserInfo>(pUserInfo);
				 if (tradeInfo->hedgeFlag == AccountSynchroType::Account_Synchro_Enable)
				 {

				 }
				 else if (tradeInfo->hedgeFlag == AccountSynchroType::Account_Synchro_Disable)
				 {

				 }
			 }
			  
			 //验证新账户信息是否有效
			 if (strlen(pUserInfo->loginName) < 16)
			 {
				 //rtnReqInfo.errCode=
			 }
		 }
		 return false;
	}

}
