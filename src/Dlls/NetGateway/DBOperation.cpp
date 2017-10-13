#include "stdafx.h"
#include "DBOperation.h"
#include "db_access/db_access.h"

using namespace DBAccess;

int CDBOperation::GetAllUsers(std::list<UserInfo> &usersInfo)
{
	CDBHandler *phandler = AllocDBHandler();
	if (!phandler)
	{
		return -1;
	}


	HxSqlRes res = NULL;

	int errCode;
	int recNum = 0;

	errCode = phandler->QuerySql("select userID,userType,loginName,accountName,password,registerDate,registerTime,phoneNumber,residentAddress from users", res, true);
}
