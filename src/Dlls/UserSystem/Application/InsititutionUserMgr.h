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
		  // ��������
		int addInsititutionUserInfo(const InsititutionStPtr& userInfo);
		 //  ɾ������
		int deleteInsititutionUserInfo(int InsititutionID);
		//  �޸Ļ�����Ϣ
		int updateInsititutionUserInfo(InsititutionStPtr& userInfo);
		 // ��ȡĳ������Ϣ
		int getInstitutionInfolByInsitionID(int InsititutionID, InsititutionStPtr& userInfo);
		 // ��ѯĳ�������µĴ�����
		int getAgentInfoByInsitionID(int insititutionID, std::vector<AgentstPtr>& vecInfo);
		//  ��ȡĳ�����������й���Ա
		int getAllManagerInfoByInsitutionID(int insititutionID, std::vector<ManagerUserInfoPtr>& vecInfo);
		//  ��ȡĳ������������ʵ���˻�
		int getAllFillUserInfoByInsitutionID(int insititutionID, std::vector<FirmUserInfoPtr>& vecInfo);




		// // ��ȡĳ�����㼶
		//int getInstitutionLevelByInsitionID(int  insititutionID, int* level);
		//// ��ȡĳ�����㼶����
		//int getInsititutionUserLevelNameByInsitionID(int levelID, LevelInfoPtr& userLevelName);
	};

}

