#include "stdafx.h"
#include <sstream>
#include "AuthorityControl.h"
#include "include/DBAccess/db_access.h"
#include "define/table_define.h"
#include "define/protocol_error.h"

using namespace DBAccess;

namespace OperationManager
{

	CAuthorityControl::CAuthorityControl()
	{
	}


	CAuthorityControl::~CAuthorityControl()
	{
	}

	bool CAuthorityControl::initAllTable()
	{
		CDBHandler *phandler = AllocDBHandler();
		if (!phandler)
			return false;

		/*std::stringstream sstr;
		sstr << "drop TABLE IF EXISTS " << gszAuthorityBussnessesTableName << ";";
		phandler->ExecSql(sstr.str().c_str());

		sstr.str("");
		sstr << "drop TABLE IF EXISTS " << gszAuthorityChangeLogTableName << ";";
		phandler->ExecSql(sstr.str().c_str());

		sstr.str("");
		sstr << "drop TABLE IF EXISTS " << gszAuthorityFunctionsTableName << ";";
		phandler->ExecSql(sstr.str().c_str());

		sstr.str("");
		sstr << "drop TABLE IF EXISTS " << gszAuthorityRoleFunctionsTableName << ";";
		phandler->ExecSql(sstr.str().c_str());*/

		DBAccess::FreeDBHandler(phandler);

		return createAuthorityBussnesses()
			&& createAuthorityLog()
			&& createAuthorityFunctions()
			&& createAuthorityRoleFunctions()
			&& createAuthorityRoleUsers()
			&& createAuthorityRoles();
	}

	bool CAuthorityControl::createAuthorityBussnesses()
	{
		CDBHandler *phandler = AllocDBHandler();
		if (!phandler)
			return false;

		int errCode = 0;

		std::stringstream sstr;
		sstr << "CREATE TABLE IF NOT EXISTS " << gszAuthorityBussnessesTableName << " (";

		for (int i = 0; i < ABT_Max; i++)
		{
			sstr << gszAuthorityBussnessesColName[i] << " " << gszAuthorityBussnessesCreateColType[i];
			sstr << ",";
		}
		sstr << "KEY `index_bussnessID` (`" << gszAuthorityBussnessesColName[0] << "`)";
		sstr << ")ENGINE=InnoDB AUTO_INCREMENT=1 DEFAULT CHARSET=latin1;";

		errCode = phandler->ExecSql(sstr.str().c_str());

		DBAccess::FreeDBHandler(phandler);
		return errCode == 0;
	}

	bool CAuthorityControl::createAuthorityLog()
	{
		CDBHandler *phandler = AllocDBHandler();
		if (!phandler)
			return false;

		int errCode = 0;

		std::stringstream sstr;
		sstr << "CREATE TABLE IF NOT EXISTS " << gszAuthorityChangeLogTableName << " (";

		for (int i = 0; i < ACLT_Max; i++)
		{
			sstr << gszAuthorityChangeLogColName[i] << " " << gszAuthorityChangeLogCreateColType[i];
			sstr << ",";
		}
		sstr << "KEY `index_userId` (`" << gszAuthorityChangeLogColName[0] << "`)";
		sstr << ")ENGINE=InnoDB AUTO_INCREMENT=1 DEFAULT CHARSET=latin1;";

		errCode = phandler->ExecSql(sstr.str().c_str());

		DBAccess::FreeDBHandler(phandler);
		return errCode == 0;
	}

	bool CAuthorityControl::createAuthorityFunctions()
	{
		CDBHandler *phandler = AllocDBHandler();
		if (!phandler)
			return false;

		int errCode = 0;

		std::stringstream sstr;
		sstr << "CREATE TABLE IF NOT EXISTS " << gszAuthorityFunctionsTableName << " (";

		for (int i = 0; i < AFT_Max; i++)
		{
			sstr << gszAuthorityFunctionsColName[i] << " " << gszAuthorityFunctionsCreateColType[i];
			sstr << ",";
		}
		sstr << "KEY `index_userId` (`" << gszAuthorityFunctionsColName[1] << "`)";
		sstr << ")ENGINE=InnoDB AUTO_INCREMENT=1 DEFAULT CHARSET=latin1;";

		errCode = phandler->ExecSql(sstr.str().c_str());

		DBAccess::FreeDBHandler(phandler);
		return errCode == 0;
	}

	bool CAuthorityControl::createAuthorityRoleFunctions()
	{
		CDBHandler *phandler = AllocDBHandler();
		if (!phandler)
			return false;

		int errCode = 0;

		std::stringstream sstr;
		sstr << "CREATE TABLE IF NOT EXISTS " << gszAuthorityRoleFunctionsTableName << " (";

		for (int i = 0; i < ARFT_Max; i++)
		{
			sstr << gszAuthorityRoleFunctionsColName[i] << " " << gszAuthorityRoleFunctionsCreateColType[i];
			sstr << ",";
		}
		sstr << "UNIQUE KEY `roleID` (`" << gszAuthorityRoleFunctionsColName[1] << "`,`"<<gszAuthorityRoleFunctionsColName [2]<< "`),";
		sstr << "KEY `index_userId` (`" << gszAuthorityFunctionsColName[0] << "`)";
		sstr << ")ENGINE=InnoDB AUTO_INCREMENT=1 DEFAULT CHARSET=latin1;";

		errCode = phandler->ExecSql(sstr.str().c_str());

		DBAccess::FreeDBHandler(phandler);
		return errCode == 0;
	}

	bool CAuthorityControl::createAuthorityRoleUsers()
	{
		CDBHandler *phandler = AllocDBHandler();
		if (!phandler)
			return false;

		int errCode = 0;

		std::stringstream sstr;
		sstr << "CREATE TABLE IF NOT EXISTS " << gszAuthorityRoleUsersTableName << " (";

		for (int i = 0; i < ARUT_Max; i++)
		{
			sstr << gszAuthorityRoleUsersColName[i] << " " << gszAuthorityRoleUsersCreateColType[i];
			sstr << ",";
		}
		sstr << "KEY `userID` (`" << gszAuthorityRoleUsersColName[1] << "`)";
		sstr << ")ENGINE=InnoDB AUTO_INCREMENT=1 DEFAULT CHARSET=latin1;";

		errCode = phandler->ExecSql(sstr.str().c_str());

		DBAccess::FreeDBHandler(phandler);
		return errCode == 0;
	}

	bool CAuthorityControl::createAuthorityRoles()
	{
		CDBHandler *phandler = AllocDBHandler();
		if (!phandler)
			return false;

		int errCode = 0;

		std::stringstream sstr;
		sstr << "CREATE TABLE IF NOT EXISTS " << gszAuthorityRolesTableName << " (";

		for (int i = 0; i < ART_Max; i++)
		{
			sstr << gszAuthorityRolesColName[i] << " " << gszAuthorityRolesCreateColType[i];
			sstr << ",";
		}
		sstr << "KEY `index_rolesId` (`" << gszAuthorityRolesColName[0] << "`)";
		sstr << ")ENGINE=InnoDB AUTO_INCREMENT=1 DEFAULT CHARSET=latin1;";

		errCode = phandler->ExecSql(sstr.str().c_str());

		DBAccess::FreeDBHandler(phandler);
		return errCode == 0;
	}

	std::string CAuthorityControl::getUserIdByLoginName(const LoginNameType loginName)
	{
		CDBHandler *phandler = AllocDBHandler();
		if (!phandler)
			return false;

		HxSqlRes res = NULL;
		int errCode = 0;
		int recNum = 0;
		std::string accountName;

		std::stringstream sstr;
		sstr << "SELECT * FROM " << gszManagerUserTableName << " WHERE " << gszManagerUserColName[MgrUT_LoginName] << " = '" << loginName << "';";

		errCode = phandler->QuerySql(sstr.str().c_str(), res, true);

		if (!errCode && res)
		{
			HxResRow row = NULL;
			while (row = phandler->FetchRow(res))
			{
				NPMgrCenter::SAccountPtr root_ptr = std::make_shared<NPMgrCenter::RootAccount>();			
				strncpy_s(root_ptr->user_id_, phandler->FetchField(row, MgrUT_UserID), sizeof(root_ptr->user_id_) - 1);

				accountName = root_ptr->user_id_;
			}
		}

		phandler->ReleaseRecords(res);
		DBAccess::FreeDBHandler(phandler);

		return accountName;
	}

	int CAuthorityControl::getAllManager(std::map<std::string, std::set<std::string>>& mapManager)
	{

		CDBHandler *phandler = AllocDBHandler();
		if (!phandler)
			return false;

		HxSqlRes res = NULL;
		int errCodeManager = 0;
		int errCodeAg = 0;

		std::stringstream sstr;
		sstr << "SELECT * FROM " << gszManagerUserTableName;

		errCodeManager = phandler->QuerySql(sstr.str().c_str(), res, true);

		if (!errCodeManager && res)
		{
			HxResRow row = NULL;
			while (row = phandler->FetchRow(res))
			{
				NPMgrCenter::SAccountPtr root_ptr = std::make_shared<NPMgrCenter::RootAccount>();
//				char *pchar;
				strncpy_s(root_ptr->user_id_, phandler->FetchField(row, MgrUT_UserID), sizeof(root_ptr->user_id_) - 1);
				strncpy_s(root_ptr->parent_id_, phandler->FetchField(row, MgrUT_ParentID), sizeof(root_ptr->parent_id_) - 1);
				strncpy_s(root_ptr->login_name_, phandler->FetchField(row, MgrUT_LoginName), sizeof(root_ptr->login_name_) - 1);

				mapManager[root_ptr->parent_id_].insert(root_ptr->user_id_);

				m_mapManagerInfo[root_ptr->user_id_] = root_ptr->login_name_;
			}
		}


		std::stringstream sstrag;
		sstrag << "SELECT * FROM " << gszAgencyUserTableName;

		errCodeAg = phandler->QuerySql(sstrag.str().c_str(), res, true);

		if (!errCodeAg && res)
		{
			HxResRow row = NULL;
			while (row = phandler->FetchRow(res))
			{
				NPMgrCenter::SAccountPtr root_ptr = std::make_shared<NPMgrCenter::RootAccount>();
				//				char *pchar;
				strncpy_s(root_ptr->user_id_, phandler->FetchField(row, AgyUT_UserID), sizeof(root_ptr->user_id_) - 1);
				strncpy_s(root_ptr->parent_id_, phandler->FetchField(row, AgyUT_ParentID), sizeof(root_ptr->parent_id_) - 1);
				strncpy_s(root_ptr->login_name_, phandler->FetchField(row, AgyUT_LoginName), sizeof(root_ptr->login_name_) - 1);

				mapManager[root_ptr->parent_id_].insert(root_ptr->user_id_);

				m_mapManagerInfo[root_ptr->user_id_] = root_ptr->login_name_;
			}
		}

		phandler->ReleaseRecords(res);
		DBAccess::FreeDBHandler(phandler);

		return (errCodeAg == 0 && errCodeManager == 0);
	}

	void CAuthorityControl::checkLowerUsers(std::string userId)
	{
		auto iter = m_mapManager.find(userId);
		if (iter != m_mapManager.end())
		{
			for (auto &item : iter->second)
			{
				m_setUserId.insert(item);
				checkLowerUsers(item);
			}
		}
		else
		{
			m_setUserId.insert(userId);
		}
	}

	ErrorCodeType CAuthorityControl::getRolesUserInfo(const UserIDType userid, std::vector<AuthorityRolesPtr> &vecRolesInfo)
	{	
//		std::string userId = getUserIdByLoginName(loginName);	
		m_mapManager.clear();
		m_setUserId.clear();
		int errCode(0);
		getAllManager(m_mapManager);
		checkLowerUsers(userid);
		m_setUserId.insert(userid); // 插入自身

		for (auto item : m_setUserId)
		{
			if (m_mapManagerInfo.find(item) != m_mapManagerInfo.end())
			{
				errCode = handleGetRolesUserInfo(const_cast<char*>(m_mapManagerInfo[item].c_str()), vecRolesInfo);
			}
			
		}
		
		if (errCode)
			return AllTrade::Err_Database;

		return errCode;
	}

	int CAuthorityControl::handleGetRolesUserInfo(const LoginNameType loginName, std::vector<AuthorityRolesPtr> &vecRolesInfo)
	{
		CDBHandler *phandler = AllocDBHandler();
		if (!phandler)
		{
			return -1;
		}

		HxSqlRes res = NULL;
		int errCode = 0;
		//		char sqlBuf[1024];

		std::stringstream sstr;
		sstr << "SELECT * FROM " << gszAuthorityRolesTableName
			<< " WHERE " << gszAuthorityRolesColName[ART_LoginName] << " = '" << loginName << "' ;";

		std::string aa = sstr.str().c_str();
		errCode = phandler->QuerySql(sstr.str().c_str(), res, true);

		if (!errCode && res)
		{
			HxResRow row = NULL;

			while (row = phandler->FetchRow(res))
			{
				AuthorityRolesPtr item = std::make_shared<AuthorityRoles>();
				char *pchar;

				pchar = phandler->FetchField(row, AuthorityRolesTable::ART_RolesId);
				item->rolesID = atoi(pchar);
				strncpy_s(item->rolesName, phandler->FetchField(row, AuthorityRolesTable::ART_RolesName), sizeof(item->rolesName) - 1);
				strncpy_s(item->login_name_, phandler->FetchField(row, AuthorityRolesTable::ART_LoginName), sizeof(item->login_name_) - 1);
				pchar = phandler->FetchField(row, AuthorityRolesTable::ART_CreateDate);
				item->createDate = atoi(pchar);
				pchar = phandler->FetchField(row, AuthorityRolesTable::ART_CreateTime);
				item->createTime = atoi(pchar);
				pchar = phandler->FetchField(row, AuthorityRolesTable::ART_RolesType);
				item->rolesType = (E_RolesType)atoi(pchar);
				pchar = phandler->FetchField(row, AuthorityRolesTable::ART_OperationType);
				item->operationType = (E_OperationType)atoi(pchar);

				vecRolesInfo.push_back(item);
			}
		}

		phandler->ReleaseRecords(res);
		DBAccess::FreeDBHandler(phandler);

		return errCode;
	}

	ErrorCodeType CAuthorityControl::addRolesUserInfo(AuthorityRolesPtr& rolesInfo)
	{

		CDBHandler *phandler = AllocDBHandler();
		if (!phandler)
		{
			return -1;
		}

		int errCode = 0;
		long long lastID = 0;

		std::stringstream sstr;
		sstr << "REPLACE INTO " << gszAuthorityRolesTableName << " set "
			<< gszAuthorityRolesColName[ART_RolesName] << " = '" << rolesInfo->rolesName << "' , "
			<< gszAuthorityRolesColName[ART_LoginName] << " = '" << rolesInfo->login_name_ << "' , "
			<< gszAuthorityRolesColName[ART_CreateDate] << " = '" << rolesInfo->createDate << "' , "
			<< gszAuthorityRolesColName[ART_CreateTime] << " = '" << rolesInfo->createTime << "' , "
			<< gszAuthorityRolesColName[ART_RolesType] << " = '" << rolesInfo->rolesType << "' , "
			<< gszAuthorityRolesColName[ART_OperationType] << " = '" << rolesInfo->operationType << "' ; ";

		errCode = phandler->InsertWithLastID(sstr.str().c_str(), lastID);
		if (!errCode)
		{
			rolesInfo->rolesID = lastID;
		}

		//  结束事务
		if (errCode)
			phandler->CancelTransaction();
		else
			phandler->CommitTransaction();

		DBAccess::FreeDBHandler(phandler);

		if (errCode)
			return AllTrade::Err_Database;
		
		return errCode;
	}

	ErrorCodeType CAuthorityControl::updateRolesUserInfo(const AuthorityRolesPtr& rolesInfo)
	{
		CDBHandler *phandler = AllocDBHandler();
		if (!phandler)
		{
			return -1;
		}

		int errCode = 0;

		std::stringstream sstr;
		sstr << "UPDATE " << gszAuthorityRolesTableName << " set "
			<< gszAuthorityRolesColName[ART_RolesName] << " = '" << rolesInfo->rolesName << "' WHERE "
			<< gszAuthorityRolesColName[ART_RolesId] << " = ' " << rolesInfo->rolesID << " ' ; ";

		
		errCode = phandler->ExecSql(sstr.str().c_str());

		//  结束事务
		if (errCode)
			phandler->CancelTransaction();
		else
			phandler->CommitTransaction();

		DBAccess::FreeDBHandler(phandler);

		if (errCode)
			return AllTrade::Err_Database;

		return errCode;
	}

	ErrorCodeType CAuthorityControl::deleteRolesUser(int rolesID)
	{
		CDBHandler *phandler = AllocDBHandler();
		if (!phandler)
		{
			return -1;
		}

		int errCode = 0;

		std::stringstream sstr;
		sstr << "DELETE FROM " << gszAuthorityRolesTableName <<  " WHERE "
			<< gszAuthorityRolesColName[ART_RolesId] << " = ' " << rolesID << " ' ; ";

		errCode = phandler->ExecSql(sstr.str().c_str());

		//  结束事务
		if (errCode)
			phandler->CancelTransaction();
		else
			phandler->CommitTransaction();

		DBAccess::FreeDBHandler(phandler);


		if (errCode)
			return AllTrade::Err_Database;
		
		return errCode;
	}

    ErrorCodeType CAuthorityControl::isHaveRoleName(const AllTrade::LoginNameType roleName)
	{
		CDBHandler *phandler = AllocDBHandler();
		if (!phandler)
		{
			return -1;
		}

		HxSqlRes res = NULL;
		int errCode = 0;
		char sqlBuf[1024];
		int  nCount(0);

		ErrorCodeType type(Err_Succeed);

		_snprintf_s(sqlBuf, sizeof(sqlBuf) / sizeof(sqlBuf[0]) - 1, "select count(*) from authority_roles where rolesName = '%s';",roleName);
		errCode = phandler->QuerySql(sqlBuf, res, true);

		if (!errCode && res)
		{
			HxResRow row = NULL;
			char *pchar;

			while (row = phandler->FetchRow(res))
			{
				if (pchar = phandler->FetchField(row, 0))
				{
					nCount = atoi(pchar);
				}

			}
		}

		phandler->ReleaseRecords(res);
		DBAccess::FreeDBHandler(phandler);

		if (nCount > 0)
			type = AllTrade::Error_Role_Exist;
		if (errCode)
			type = AllTrade::Err_Database;

		return type;
	}

    ErrorCodeType CAuthorityControl::isHaveAuthority(const AllTrade::LoginNameType loginName, int nFunctionId) const
	{
		CDBHandler *phandler = AllocDBHandler();
		if (!phandler)
		{
			return -1;
		}

		HxSqlRes res = NULL;
		int errCode = 0;
		char sqlBuf[1024];

		ErrorCodeType type(Err_Succeed);
		int nCount(0);

		_snprintf_s(sqlBuf, sizeof(sqlBuf) / sizeof(sqlBuf[0]) - 1, "select count(*) from authority_role_functions a,authority_role_users b where \
													a.roleID = b.rolesID and a.functionID = %d and b.loginName = '%s';", nFunctionId, loginName);
		errCode = phandler->QuerySql(sqlBuf, res, true);
		if (!errCode && res)
		{
			HxResRow row = NULL;
	
			char *pchar;
			while (row = phandler->FetchRow(res))
			{
				int count(0);
				if (pchar = phandler->FetchField(row, 0))
				{
					nCount = atoi(pchar);
				}
			}
			
		}

		phandler->ReleaseRecords(res);
		DBAccess::FreeDBHandler(phandler);

		if (nCount > 0)
			type = AllTrade::Error_UserAndFunction_Exist;
		if (errCode)
			type = AllTrade::Err_Database;

		return type;
	}

    ErrorCodeType CAuthorityControl::getAuthorityRoleUsers(const AllTrade::LoginNameType loginName, std::vector<AllTrade::AuthorityRoleUsersPtr>& vecAuthority)
	{
		std::string userId = getUserIdByLoginName(loginName);
		m_mapManager.clear();
		m_setUserId.clear();
		ErrorCodeType errCode_;

		getAllManager(m_mapManager);
		checkLowerUsers(userId);
		m_setUserId.insert(userId);

		for (auto item : m_setUserId)
		{
			if (m_mapManagerInfo.find(item) != m_mapManagerInfo.end())
			{
				errCode_ = handleGetAuthorityRoleUsers(const_cast<char*>(m_mapManagerInfo[item].c_str()), vecAuthority);
			}
		}

		return errCode_;
	}

    AllTrade::ErrorCodeType CAuthorityControl::handleGetAuthorityRoleUsers(const AllTrade::LoginNameType loginName, std::vector<AllTrade::AuthorityRoleUsersPtr>& vecAuthority)
	{
		CDBHandler *phandler = AllocDBHandler();
		if (!phandler)
		{
			return -1;
		}

		HxSqlRes res = NULL;
		int errCode = 0;
		char sqlBuf[1024];

		_snprintf_s(sqlBuf, sizeof(sqlBuf) / sizeof(sqlBuf[0]) - 1, "select id,loginName,rolesID from authority_role_users where loginName = '%s'; ", loginName);

		errCode = phandler->QuerySql(sqlBuf, res, true);

		if (!errCode && res)
		{
			HxResRow row = NULL;


			while (row = phandler->FetchRow(res))
			{
				AuthorityRoleUsersPtr item = std::make_shared<AuthorityRoleUsers>();
				char *pchar;

				if (pchar = phandler->FetchField(row, 0))
				{
					item->id = atoi(pchar);
				}

				if (pchar = phandler->FetchField(row, 1))
				{
					_snprintf_s(item->login_name_, sizeof(item->login_name_) / sizeof(item->login_name_[0]) - 1, "%s", pchar);
					//	item->userID = atoi(pchar);
				}
				if (pchar = phandler->FetchField(row, 2))
				{
					item->rolesID = atoi(pchar);
				}

				vecAuthority.push_back(item);
			}
		}

		phandler->ReleaseRecords(res);
		DBAccess::FreeDBHandler(phandler);

		return errCode;
	}

	ErrorCodeType CAuthorityControl::addAuthorityRoleUsers(const std::vector<AllTrade::AuthorityRoleUsersPtr>& vecAuthority)
	{
		CDBHandler *phandler = AllocDBHandler();
		if (!phandler)
		{
			return -1;
		}

		int errCode = 0;

		std::string strSql;
		char sqlBuf[1024];
		for (auto& iter : vecAuthority)
		{
			_snprintf_s(sqlBuf, sizeof(sqlBuf) / sizeof(sqlBuf[0]) - 1, "INSERT INTO authority_role_users SET loginName='%s',rolesID=%d;",
				iter->login_name_, iter->rolesID);
			strSql += sqlBuf;
		}
		errCode = phandler->ExecSql(strSql.c_str());
		//  结束事务
		if (errCode)
			phandler->CancelTransaction();
		else
			phandler->CommitTransaction();

		DBAccess::FreeDBHandler(phandler);

		if (errCode)
			return AllTrade::Err_Database;

		return errCode;
	}

	ErrorCodeType CAuthorityControl::deleteAuthorityRoleUsers(const std::vector<AllTrade::AuthorityRoleUsersPtr>& vecAuthority)
	{
		CDBHandler *phandler = AllocDBHandler();
		if (!phandler)
		{
			return -1;
		}

		int errCode = 0;
		std::string strSql;
		char sqlBuf[1024];

		for (auto& iter : vecAuthority)
		{
			_snprintf_s(sqlBuf, sizeof(sqlBuf) / sizeof(sqlBuf[0]) - 1, "delete from authority_role_users where loginName='%s' and rolesID=%d;",
				iter->login_name_, iter-> rolesID);
			strSql += sqlBuf;

		}

		errCode = phandler->ExecSql(strSql.c_str());
		//  结束事务
		if (errCode)
			phandler->CancelTransaction();
		else
			phandler->CommitTransaction();

		DBAccess::FreeDBHandler(phandler);

		if (errCode)
			return AllTrade::Err_Database;

		return errCode;
	}

	ErrorCodeType CAuthorityControl::judgeRoleUsersRelation(int roleId)
	{
		CDBHandler *phandler = AllocDBHandler();
		if (!phandler)
		{
			return -1;
		}

		HxSqlRes res = NULL;
		int errCode = 0;
		char sqlBuf[1024];
		ErrorCodeType type(Err_Succeed);
		int nCount(0);

		_snprintf_s(sqlBuf, sizeof(sqlBuf) / sizeof(sqlBuf[0]) - 1, "select count(*) from authority_role_users where rolesID =%d; ", roleId);
		errCode = phandler->QuerySql(sqlBuf, res, true);

		if (!errCode && res)
		{
			HxResRow row = NULL;
			char *pchar;

			while (row = phandler->FetchRow(res))
			{
				if (pchar = phandler->FetchField(row, 0))
				{
					nCount = atoi(pchar);
				}
			}
			
		}
		
		phandler->ReleaseRecords(res);
		DBAccess::FreeDBHandler(phandler);

		if (nCount > 0)
			type = AllTrade::Error_RoleUser_Exist;
		if (errCode)
			type = AllTrade::Err_Database;

		return type;
	}


    ErrorCodeType CAuthorityControl::judgeRoleUsersRelation(const AllTrade::LoginNameType loginName, int nRoleId)
	{
		CDBHandler *phandler = AllocDBHandler();
		if (!phandler)
		{
			return -1;
		}

		HxSqlRes res = NULL;
		int errCode = 0;
		char sqlBuf[1024];
		int nCount(0);
		ErrorCodeType type(Err_Succeed);

		_snprintf_s(sqlBuf, sizeof(sqlBuf) / sizeof(sqlBuf[0]) - 1, "select count(*) from authority_role_users \
					where rolesID = %d and loginName = '%s'; ", nRoleId, loginName);
		errCode = phandler->QuerySql(sqlBuf, res, true);

		if (!errCode && res)
		{
			HxResRow row = NULL;
			while (row = phandler->FetchRow(res))
			{
				char *pchar;

				if (pchar = phandler->FetchField(row, 0))
				{
					nCount = atoi(pchar);
				}
			}
		}

		phandler->ReleaseRecords(res);
		DBAccess::FreeDBHandler(phandler);

		if (nCount > 0)
			type = AllTrade::Error_RoleUser_Exist;
		if (errCode)
			type = AllTrade::Err_Database;

		return type;
	}

	AllTrade::ErrorCodeType CAuthorityControl::judgeRoleUsersRelation(const AllTrade::LoginNameType loginName)
	{
		CDBHandler *phandler = AllocDBHandler();
		if (!phandler)
		{
			return -1;
		}

		HxSqlRes res = NULL;
		int errCode = 0;
		char sqlBuf[1024];
		int nCount(0);
		ErrorCodeType type(Err_Succeed);

		_snprintf_s(sqlBuf, sizeof(sqlBuf) / sizeof(sqlBuf[0]) - 1, "select count(*) from authority_role_users where loginName = '%s'; ", loginName);
		errCode = phandler->QuerySql(sqlBuf, res, true);

		if (!errCode && res)
		{
			HxResRow row = NULL;
			while (row = phandler->FetchRow(res))
			{
				char *pchar;

				if (pchar = phandler->FetchField(row, 0))
				{
					nCount = atoi(pchar);
				}
			}
		}

		phandler->ReleaseRecords(res);
		DBAccess::FreeDBHandler(phandler);

		if (nCount > 0)
			type = AllTrade::Error_RoleUser_Exist;
		if (errCode)
			type = AllTrade::Err_Database;

		return type;
	}

	AllTrade::ErrorCodeType CAuthorityControl::changeAuthorityRoleUsers(const AllTrade::AuthorityRoleUsersPtr& ptr)
	{
		CDBHandler *phandler = AllocDBHandler();
		if (!phandler)
		{
			return -1;
		}

		int errCode = 0;
		HxSqlRes res = NULL;
		char sqlBuf[1024];
		
		_snprintf_s(sqlBuf, sizeof(sqlBuf) / sizeof(sqlBuf[0]) - 1, "UPDATE authority_role_users SET rolesID=%d where loginName='%s'",
			ptr->rolesID,ptr->login_name_ );

		errCode = phandler->QuerySql(sqlBuf, res, true);
		//  结束事务
		if (errCode)
			phandler->CancelTransaction();
		else
			phandler->CommitTransaction();

		DBAccess::FreeDBHandler(phandler);

		if (errCode)
			return AllTrade::Err_Database;

		return errCode;
	}

	int CAuthorityControl::getAllAgentHaveRelation(std::set<int>& setInfo, int nRoleId)
	{
		CDBHandler *phandler = AllocDBHandler();
		if (!phandler)
		{
			return -1;
		}

		HxSqlRes res = NULL;
		int errCode = 0;
		char sqlBuf[1024];

		_snprintf_s(sqlBuf, sizeof(sqlBuf) / sizeof(sqlBuf[0]) - 1, "select userID from authority_role_users \
																	where rolesID = %d; ", nRoleId);
		errCode = phandler->QuerySql(sqlBuf, res, true);

		if (!errCode && res)
		{
			HxResRow row = NULL;
			
			while (row = phandler->FetchRow(res))
			{
				char *pchar;

				if (pchar = phandler->FetchField(row, 0))
				{
					setInfo.insert(atoi(pchar));
				}				
			}
		}

		phandler->ReleaseRecords(res);
		DBAccess::FreeDBHandler(phandler);

		return errCode;
	}

	ErrorCodeType CAuthorityControl::addAuthorityRoleFunctions(int roleId, const std::vector<AllTrade::AuthorityRoleFunctionsPtr>& vecAuthority)
	{
		CDBHandler *phandler = AllocDBHandler();
		if (!phandler)
		{
			return -1;
		}

		int errCode = 0;
		char sqlBuf[1024];

		_snprintf_s(sqlBuf, sizeof(sqlBuf) / sizeof(sqlBuf[0]) - 1, "DELETE FROM authority_role_functions WHERE roleID=%d", roleId);

		//  开始事务
		phandler->BeginTransaction();

		errCode = phandler->ExecSql(sqlBuf);
		if (!errCode)
		{
			phandler->CommitTransaction();

			for (auto &iter : vecAuthority)
			{
				_snprintf_s(sqlBuf, sizeof(sqlBuf) / sizeof(sqlBuf[0]) - 1, "insert into authority_role_functions set roleID=%d,functionID=%d;",
					iter->roleID, iter->functionID);
			//	 strSql += sqlBuf;

				errCode = phandler->ExecSql(sqlBuf);

				
			}
		}
		//  结束事务
		if (errCode)
			phandler->CancelTransaction();
		else
			phandler->CommitTransaction();
		
		DBAccess::FreeDBHandler(phandler);

		if (errCode)
			return AllTrade::Err_Database;

		return errCode;
	}

	ErrorCodeType CAuthorityControl::deleteAuthorityRoleFunctions(const std::vector<AllTrade::AuthorityRoleFunctionsPtr>& vecAuthority)
	{
		CDBHandler *phandler = AllocDBHandler();
		if (!phandler)
		{
			return -1;
		}

		int errCode = 0;
		char sqlBuf[1024];

		for (auto &iter : vecAuthority)
		{
			_snprintf_s(sqlBuf, sizeof(sqlBuf) / sizeof(sqlBuf[0]) - 1, "delete from authority_role_functions where roleID=%d and functionID=%d;",
				iter->roleID, iter->functionID);

			errCode = phandler->ExecSql(sqlBuf);
		}


		//  结束事务
		if (errCode)
			phandler->CancelTransaction();
		else
			phandler->CommitTransaction();

		DBAccess::FreeDBHandler(phandler);

		return errCode;
	}

	ErrorCodeType CAuthorityControl::getAuthorityRoleFunctionsByRoleId(int roleId, std::vector<AllTrade::AuthorityRoleFunctionsPtr>& vecAuthority)
	{
		CDBHandler *phandler = AllocDBHandler();
		if (!phandler)
		{
			return -1;
		}

		HxSqlRes res = NULL;
		int errCode = 0;
		char sqlBuf[1024];

		_snprintf_s(sqlBuf, sizeof(sqlBuf) / sizeof(sqlBuf[0]) - 1, "select id,roleID,functionID from authority_role_functions\
																	where roleID = %d; ", roleId);
		errCode = phandler->QuerySql(sqlBuf, res, true);

		if (!errCode && res)
		{
			HxResRow row = NULL;
			
			while (row = phandler->FetchRow(res))
			{			
				AuthorityRoleFunctionsPtr item = std::make_shared<AuthorityRoleFunctions>();
				char *pchar;
				if (pchar = phandler->FetchField(row, 0))
				{
					item->id = atoi(pchar);
				}
				if (pchar = phandler->FetchField(row, 1))
				{
					item->roleID = atoi(pchar);
				}
				if (pchar = phandler->FetchField(row, 2))
				{
					item->functionID = atoi(pchar);
				}

				vecAuthority.push_back(item);
			}
		}

		phandler->ReleaseRecords(res);
		DBAccess::FreeDBHandler(phandler);

		return errCode;
	}

	ErrorCodeType CAuthorityControl::judgeRoleAndFunctionsRelationOne(int roleId)
	{
		CDBHandler *phandler = AllocDBHandler();
		if (!phandler)
		{
			return -1;
		}

		HxSqlRes res = NULL;
		int errCode = 0;
		char sqlBuf[1024];

		ErrorCodeType type(Err_Succeed);
		int nCount(0);

		_snprintf_s(sqlBuf, sizeof(sqlBuf) / sizeof(sqlBuf[0]) - 1, "select count(*) from authority_role_functions where roleID = %d; ", roleId);
		errCode = phandler->QuerySql(sqlBuf, res, true);

		if (!errCode && res)
		{
			HxResRow row = NULL;

			while (row = phandler->FetchRow(res))
			{
				char *pchar;

				if (pchar = phandler->FetchField(row, 0))
				{
					nCount = atoi(pchar);
				}
			}
		}

		phandler->ReleaseRecords(res);
		DBAccess::FreeDBHandler(phandler);

		if (nCount > 0)
			type = AllTrade::Error_RoleFunctions_Exist;
		if (errCode)
			type = AllTrade::Err_Database;

		return type;
	}

	int CAuthorityControl::judgeRoleAndFunctionsRelationTwo(int nFunctionID, int nRoleId, int* nCount)
	{
		CDBHandler *phandler = AllocDBHandler();
		if (!phandler)
		{
			return -1;
		}

		HxSqlRes res = NULL;
		int errCode = 0;
		char sqlBuf[1024];

		_snprintf_s(sqlBuf, sizeof(sqlBuf) / sizeof(sqlBuf[0]) - 1, "select count(*) from authority_role_functions \
													where roleID = %d and functionID = %d; ", nRoleId, nFunctionID);
		errCode = phandler->QuerySql(sqlBuf, res, true);

		if (!errCode && res)
		{
			HxResRow row = NULL;

			while (row = phandler->FetchRow(res))
			{
				char *pchar;

				if (pchar = phandler->FetchField(row, 0))
				{
					*nCount = atoi(pchar);
				}
			}
		}

		phandler->ReleaseRecords(res);
		DBAccess::FreeDBHandler(phandler);

		return errCode;

		return 0;
	}

	int CAuthorityControl::getAllAuthorityRoleFunctions(std::vector<AllTrade::AuthorityRoleFunctionsPtr>& vecAuthority)
	{
		CDBHandler *phandler = AllocDBHandler();
		if (!phandler)
		{
			return -1;
		}

		HxSqlRes res = NULL;
		int errCode = 0;
		char sqlBuf[1024];

		_snprintf_s(sqlBuf, sizeof(sqlBuf) / sizeof(sqlBuf[0]) - 1, "select id,roleID,functionID from authority_role_functions;");
		errCode = phandler->QuerySql(sqlBuf, res, true);

		if (!errCode && res)

			errCode = phandler->QuerySql("", res, true);
		if (!errCode && res)
		{
			HxResRow row = NULL;
			while (row = phandler->FetchRow(res))
			{
				AuthorityRoleFunctionsPtr item = std::shared_ptr<AuthorityRoleFunctions>();

				char *pchar;
				if (pchar = phandler->FetchField(row, 0))
				{
					item->id = atoi(pchar);
				}
				if (pchar = phandler->FetchField(row, 1))
				{
					item->roleID = atoi(pchar);
				}
				if (pchar = phandler->FetchField(row, 2))
				{
					item->functionID = atoi(pchar);
				}

				vecAuthority.push_back(item);
			}
		}

		phandler->ReleaseRecords(res);
		DBAccess::FreeDBHandler(phandler);

		return errCode;
	}

	int CAuthorityControl::GetAllAgentInfo(std::map<int, std::set<int>>& mapInfo)
	{
		CDBHandler *phandler = AllocDBHandler();
		if (!phandler)
		{
			return -1;
		}

		HxSqlRes res = NULL;
		int errCode = 0;
		int recNum = 0;

		char sqlBuf[1024];

		_snprintf_s(sqlBuf, sizeof(sqlBuf) / sizeof(sqlBuf[0]) - 1, "select agentID,parentID from agent_basic_info;");


		errCode = phandler->QuerySql(sqlBuf, res, true);

		if (!errCode && res)
		{
			int userid(0), parentId(0);
			HxResRow row = NULL;
			while (row = phandler->FetchRow(res))
			{
				char *pchar;
				if (pchar = phandler->FetchField(row, 0))
				{
					userid = atoi(pchar);
				}
				if (pchar = phandler->FetchField(row, 1))
				{
					parentId = atoi(pchar);
				}

				mapInfo[parentId].insert(userid);
			}
		}

		phandler->ReleaseRecords(res);
		DBAccess::FreeDBHandler(phandler);

		return errCode;
	}

	AllTrade::ErrorCodeType CAuthorityControl::getSelfFunctionsByLoginName(const LoginNameType loginName, std::vector<AuthorityFunctionsUserIdPtr> &vecAuthorityFunctions)
	{
		CDBHandler *phandler = AllocDBHandler();
		if (!phandler)
		{
			return -1;
		}

		HxSqlRes res = NULL;
		int errCode = 0;
		int recNum = 0;

		char sqlBuf[1024];
		
		/*std::stringstream sstr;
		sstr << "SELECT " << gszAuthorityRoleUsersTableName[ARUT_LoginName] << ", a." << gszAuthorityRoleFunctionsTableName[ARFT_FunctionId]
			<< ", " << gszAuthorityFunctionsTableName[AFT_BussnessId] << ", " << gszAuthorityFunctionsTableName[AFT_FunctionName]
			<< ", " << gszAuthorityFunctionsTableName[AFT_Issort] << " FROM " << gszAuthorityRoleFunctionsTableName << " a, "
			<< gszAuthorityRoleUsersTableName << " b, " << gszAuthorityFunctionsTableName  << " c, "
			<< " WHERE a." << gszAuthorityRoleFunctionsColName[ARFT_FunctionId] << " = c." << gszAuthorityFunctionsColName[AFT_FunctionId]
			<< " and a." << gszAuthorityRoleFunctionsColName[ARFT_RoleId] << " = b." << gszAuthorityRoleUsersColName[ARUT_RolesId]
			<< " and b." << gszAuthorityRoleUsersTableName[ARUT_LoginName] << " = " << loginName;

		errCode = phandler->QuerySql(sstr.str().c_str(), res, true);*/

		_snprintf_s(sqlBuf, sizeof(sqlBuf) / sizeof(sqlBuf[0]) - 1,
			"select loginName,a.functionID,bussnessID,NavigationID,functionName,issort from authority_role_functions a ,authority_role_users b, authority_functions c \
						where a.functionID = c.functionID and a.roleID = b.rolesID and b.loginName = '%s';", loginName);
	
		errCode = phandler->QuerySql(sqlBuf, res, true);

		if (!errCode && res)
		{
			HxResRow row = NULL;
			while (row = phandler->FetchRow(res))
			{

				AuthorityFunctionsUserIdPtr item = std::make_shared<AuthorityFunctionsUserId>();
				
				char *pchar;
				if (pchar = phandler->FetchField(row, 0))
				{
					_snprintf_s(item->login_name_, sizeof(item->login_name_) / sizeof(item->login_name_[0]) - 1, "%s", pchar);
				}
				if (pchar = phandler->FetchField(row, 1 ))
				{
					item->functionID = atoi(pchar);
				}
				if (pchar = phandler->FetchField(row, 2))
				{
					item->bussnessID = atoi(pchar);
				}

				if (pchar = phandler->FetchField(row, 3 ))
				{
					item->NavigationID = atoi(pchar);
				}
				if (pchar = phandler->FetchField(row, 4))
				{
					_snprintf_s(item->functionName, sizeof(item->functionName) / sizeof(item->functionName[0]) - 1, "%s", pchar);
				}
				if (pchar = phandler->FetchField(row, 5))
				{
					item->issort = atoi(pchar);
				}

				vecAuthorityFunctions.push_back(item);
			}
		}

		phandler->ReleaseRecords(res);
		DBAccess::FreeDBHandler(phandler);

		return errCode;
	}

	AllTrade::ErrorCodeType CAuthorityControl::getAllBussness(std::vector<AuthorityBussnessesPtr>& vec)
	{
		CDBHandler *phandler = AllocDBHandler();
		if (!phandler)
		{
			return -1;
		}

		HxSqlRes res = NULL;
		int errCode = 0;
		int recNum = 0;

		char sqlBuf[1024];

		_snprintf_s(sqlBuf, sizeof(sqlBuf) / sizeof(sqlBuf[0]) - 1,
			"select bussnessID,bussnessName from authority_bussnesses;");

		errCode = phandler->QuerySql(sqlBuf, res, true);

		if (!errCode && res)
		{
			HxResRow row = NULL;
			while (row = phandler->FetchRow(res))
			{

				AuthorityBussnessesPtr item = std::make_shared<AuthorityBussnesses>();

				char *pchar;
				if (pchar = phandler->FetchField(row, 0))
				{
					item->bussnessID = atoi(pchar);
					
				}
				if (pchar = phandler->FetchField(row, 1))
				{
					_snprintf_s(item->bussnessName, sizeof(item->bussnessName) / sizeof(item->bussnessName[0]) - 1, "%s", pchar);
				}
			
				vec.push_back(item);
			}
		}

		phandler->ReleaseRecords(res);
		DBAccess::FreeDBHandler(phandler);

		return errCode;
	}

}