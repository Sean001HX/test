/*************************************************
Copyright (C), 2016, HX Tech Co., Ltd.
Description: 定义数据库访问类的外部导出函数
Author:	Arven				Date:2016-04-20
Others:
Function List:  
1、int Init()
2、int Fint()
3、CDBHandler * AllocDBHandler()
4、void FreeDBHandler(CDBHandler *handler)

*************************************************/

#include "stdafx.h"
#include "DBAccess\db_access.h"
#include "MySQLMan.h"
#include "MySQLConn.h"
#include <stdlib.h>
#include <windows.h>
#include "c:/ng_tools/ng_header_for_log4cxx/ng_header_for_log4cxx.hpp"
#include "C:/ng_tools/ng_header_for_log4cxx/ng_header_for_log4cxx_log_var.hpp"

NG_LOGGER(Logger, "DBAccess");

namespace DBAccess
{

	int InitDB()
	{
        char m_dbHost[100] = { 0 }; // "127.0.0.1";
        int  m_dbPort = 3306;
        char m_dbName[100] = { 0 };  // "test";
        char m_dbLgnName[100] = { 0 };  // "root";
        char m_dbLgnPsw[100] = { 0 };

        GetPrivateProfileStringA("DB", "host", "127.0.0.1", m_dbHost, sizeof(m_dbHost), "./db_access.hxc");
        GetPrivateProfileStringA("DB", "db_name", "", m_dbName, sizeof(m_dbName), "./db_access.hxc");
        GetPrivateProfileStringA("DB", "login_name", "", m_dbLgnName, sizeof(m_dbHost), "./db_access.hxc");
        GetPrivateProfileStringA("DB", "password", "", m_dbLgnPsw, sizeof(m_dbHost), "./db_access.hxc");
        m_dbPort = GetPrivateProfileIntA("DB", "port", 3306, "./db_access.hxc");

        bool ok = CMySQLMan::Instance()->ConnectDB(m_dbHost, m_dbLgnName, m_dbLgnPsw, m_dbName, m_dbPort);
        if (!ok)
        {
            LOG4CXX_FATAL(Logger, "Init()"
                LOG_VAR(m_dbHost)
                LOG_VAR(m_dbPort)
                LOG_VAR(m_dbName)
                LOG_VAR(m_dbLgnName)
                );
            return -1;
        }
        return 0;
	}

	int FintDB()
	{
		CMySQLMan::Instance()->CloseConnect();
		return 0;
	}

	CDBHandler * AllocDBHandler()
	{
		return(dynamic_cast<CDBHandler *>(CMySQLMan::Instance()->GetAnIdleConn()));
	}

	void FreeDBHandler(CDBHandler *handler)
	{
		CMySQLMan::Instance()->SetAConnToAdle(dynamic_cast<CMySQLConn *>(handler));
		
	}

}