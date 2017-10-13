#include "InsititutionUserMgr.h"
#include "define/struct_base.h"

namespace AllTrade
{
	InsititutionUserMgr::InsititutionUserMgr() 
	{

	}


	InsititutionUserMgr::~InsititutionUserMgr()
	{

	}

	int InsititutionUserMgr::addInsititutionUserInfo(const InsititutionStPtr& userInfo)
	{
		return -1;
	}


	int InsititutionUserMgr::deleteInsititutionUserInfo(int InsititutionID)
	{
		return -1;
	}

	int InsititutionUserMgr::updateInsititutionUserInfo(InsititutionStPtr& userInfo)
	{
		return -1;
	}

	int InsititutionUserMgr::getInstitutionInfolByInsitionID(int InsititutionID, InsititutionStPtr& userInfo)
	{
		return -1;
	}

	int InsititutionUserMgr::getAgentInfoByInsitionID(int insititutionID, std::vector<AgentstPtr>& vecInfo)
	{
		return -1;
	}

	int InsititutionUserMgr::getAllManagerInfoByInsitutionID(int insititutionID, std::vector<ManagerUserInfoPtr>& vecInfo)
	{
		return -1;
	}

	int InsititutionUserMgr::getAllFillUserInfoByInsitutionID(int insititutionID, std::vector<FirmUserInfoPtr>& vecInfo)
	{
		return -1;
	}

}
