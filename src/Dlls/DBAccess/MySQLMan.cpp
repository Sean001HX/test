#include "stdafx.h"
#include "MySQLMan.h"
#include "MySQLConn.h"
#include "c:/ng_tools/ng_header_for_log4cxx/ng_header_for_log4cxx.hpp"
#include "C:/ng_tools/ng_header_for_log4cxx/ng_header_for_log4cxx_log_var.hpp"

NG_LOGGER(logger, "CMySQLMan");


CMySQLMan::CMySQLMan()
{
	m_iNumUsed = 0;
	InitializeCriticalSection(&m_csList);
}


CMySQLMan::~CMySQLMan()
{
	DeleteCriticalSection(&m_csList);
}

CMySQLMan *CMySQLMan::Instance()
{
	static CMySQLMan _instance;
	return &_instance;
}

bool CMySQLMan::ConnectDB(const char *host, const char *user, const char *password, const char *db, unsigned int port, char *charSet)
{
	strcpy_s(m_host, host);
	strcpy_s(m_user, user);
	strcpy_s(m_password, password);
	strcpy_s(m_db, db);
	strcpy_s(m_charSet, charSet);
	m_port = port;

	time(&m_last_alloc_time);

	if (ERR_DB_NOERR != AllocConnection(CONNECTION_NUM_INIT))
		return false;

	return true;
}

void CMySQLMan::CloseConnect()
{
	ITER_CONN_LIST ite;
	for (ite = m_ConnList.begin(); ite != m_ConnList.end(); ite++)
	{
		(*ite)->DisConnect();
		delete (*ite);
	}
	m_ConnList.clear();
}


bool CMySQLMan::IsTimeForTrim(time_t &lastTime, time_t &curTime)
{
	if ((curTime - lastTime) < CHECK_ALLOC_CONN)
		return false;
	return true;
}

void CMySQLMan::TrimConn()
{
	int needErasedNum = m_ConnList.size() - CONNECTION_NUM_INIT;
	int haveErasedNum = 0;

	m_ConnList.reverse();
	ITER_CONN_LIST ite;
	for (ite = m_ConnList.begin(); (ite != m_ConnList.end()) && (haveErasedNum<needErasedNum);)
	{
		if (!(*ite)->m_bInUse)
		{
			(*ite)->DisConnect();
			delete (*ite);
			ite = m_ConnList.erase(ite);
			haveErasedNum++;
		}
		else
			ite++;
	}
	m_ConnList.reverse();
}

CMySQLConn * CMySQLMan::GetAnIdleConn()
{
	CMySQLConn *result = NULL;
	int conCount = m_ConnList.size();
	if (conCount <= 0)
	{
		LOG4CXX_ERROR(logger, "GetAnIdleConn() if (!result)" LOG_VAR(result) LOG_VAR(m_iNumUsed) LOG_VAR(conCount));
		return NULL;
	}
		
	EnterCriticalSection(&m_csList);

	ITER_CONN_LIST ite;
	for (ite = m_ConnList.begin(); ite != m_ConnList.end(); ite++)
	{
		if (!(*ite)->m_bInUse)
		{
			(*ite)->m_bInUse = true;
			result = (*ite);
			m_iNumUsed++;
			goto LEAVE_GET_CONN;
		}

	}

	ite--;
	if (ERR_DB_NOERR == AllocConnection(CONNECTION_NUM))
	{
		time(&m_last_alloc_time);
		ite++;
		(*ite)->m_bInUse = true;
		result = (*ite);
		m_iNumUsed++;

	}

LEAVE_GET_CONN:
	time_t curTime;
	time(&curTime);
	if (conCount > CONNECTION_NUM_INIT && m_iNumUsed <= CONNECTION_NUM_INIT && IsTimeForTrim(m_last_alloc_time, curTime))
		TrimConn();

	LeaveCriticalSection(&m_csList);

	if (!result)
	{
		LOG4CXX_ERROR(logger, "GetAnIdleConn() if (!result)" LOG_VAR(result) LOG_VAR(m_iNumUsed) LOG_VAR(conCount));
	}

	return result;
}

void CMySQLMan::SetAConnToAdle(CMySQLConn *pConn)
{
	EnterCriticalSection(&m_csList);
	if (pConn)
	{
		pConn->m_bInUse = false;
		m_iNumUsed--;
	}
	LeaveCriticalSection(&m_csList);
}

int CMySQLMan::AllocConnection(int num)
{
	int resErr = ERR_DB_NOERR;
	try
	{
		for (int i = 0; i < num; ++i)
		{
			CMySQLConn *pMySql = new CMySQLConn(this);
			resErr = pMySql->ConncectMySQL(m_host, m_port, m_db, m_user, m_password, m_charSet);
			if (resErr == ERR_DB_NOERR)
			{
				m_ConnList.push_back(pMySql);
			}
			else
			{
				return resErr;
			}
		}
	}
	catch (...)
	{
		return ERR_DB_ALLOCCONNFAIL;
	}


	return ERR_DB_NOERR;
}





