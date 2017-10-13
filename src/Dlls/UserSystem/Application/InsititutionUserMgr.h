#pragma once
#include "define/struct_declare.h"
#include "utility/instance.h"
#include <vector>
namespace AllTrade
{
	class InsititutionUserMgr 
		: public CommonTools::instance_unshared<InsititutionUserMgr>
	{
	public:
		InsititutionUserMgr();
		~InsititutionUserMgr();

	public:
		  // 创建机构
		int addInsititutionUserInfo(const InsititutionStPtr& userInfo);
		 //  删除机构
		int deleteInsititutionUserInfo(int InsititutionID);
		//  修改机构信息
		int updateInsititutionUserInfo(InsititutionStPtr& userInfo);
		 // 获取某机构信息
		int getInstitutionInfolByInsitionID(int InsititutionID, InsititutionStPtr& userInfo);
		 // 查询某个机构下的代理商
		int getAgentInfoByInsitionID(int insititutionID, std::vector<AgentstPtr>& vecInfo);
		//  获取某个机构的所有管理员
		int getAllManagerInfoByInsitutionID(int insititutionID, std::vector<ManagerUserInfoPtr>& vecInfo);
		//  获取某个机构的所有实盘账户
		int getAllFillUserInfoByInsitutionID(int insititutionID, std::vector<FirmUserInfoPtr>& vecInfo);




		// // 获取某机构层级
		//int getInstitutionLevelByInsitionID(int  insititutionID, int* level);
		//// 获取某机构层级名称
		//int getInsititutionUserLevelNameByInsitionID(int levelID, LevelInfoPtr& userLevelName);
	};

}

