#include "stdafx.h"

#include "MySQLMan.h"
#include "MySQLConn.h"

#define   CR_SERVER_LOST         2013    //  Message: Lost connection to MySQL server during query
#define   CR_SERVER_GONE_ERROR   2006    //  Message: MySQL server has gone away


CMySQLConn::CMySQLConn(CMySQLMan *pManager)
{
	m_bInUse = false;
	m_manager = pManager;
}


CMySQLConn::~CMySQLConn()
{
	DisConnect();
}

int CMySQLConn::InsertWithLastID(const char *sql, long long &lastID)
{
	lastID = 0;
	int err = ExecSql(sql);
	if (err != ERR_DB_NOERR)
		return err;

	HxSqlRes sqlResult = NULL;//MYSQL_RES
	err = QuerySql("select @@identity;", sqlResult);
	if (err != ERR_DB_NOERR)
		return err;

	MYSQL_ROW row = NULL;
	while (row = mysql_fetch_row((MYSQL_RES *)sqlResult))
	{
		lastID = (long long)(atoi(row[0]));
	}
	// 释放结果集
	mysql_free_result((MYSQL_RES *)sqlResult);

// 	if (row == NULL)    //  while (row = mysql_fetch_row((MYSQL_RES *)sqlResult)) 
// 		return ERR_DB_QUERYEMPTY;
	if (!lastID)
		return ERR_DB_QUERYEMPTY;

	return ERR_DB_NOERR;
}

int CMySQLConn::ExecSql(const char *sql)
{
	int ret = 0;
	if ((ret = mysql_query(&m_connMysql, sql)) != 0)
	{
		ret = mysql_errno(&m_connMysql);

		if (ret == CR_SERVER_LOST || ret == CR_SERVER_GONE_ERROR)
		{

			mysql_close(&m_connMysql);
			ret = ReConnMySQL();

			if (ret == ERR_DB_NOERR)
			{
				if ((ret = mysql_query(&m_connMysql, sql)) != 0)
				{
					return ERR_DB_EXECUTESQL;
				}
			}
			else
			{
				return ret;
			}
		}
		else
		{
			return ERR_DB_EXECUTESQL;
		}

	}

	return ERR_DB_NOERR;
}

int CMySQLConn::QuerySql(const char *sql, HxSqlRes &sqlResult, bool quick_mode)
{
	int ret = 0;
	if ((ret = mysql_query(&m_connMysql, sql)) != 0)
	{

		ret = mysql_errno(&m_connMysql);

		if (ret == CR_SERVER_LOST || ret == CR_SERVER_GONE_ERROR)
		{
			mysql_close(&m_connMysql);
			ret = ReConnMySQL();

			if (ret == ERR_DB_NOERR)
			{
				if ((ret = mysql_query(&m_connMysql, sql)) != 0)
				{
					return ERR_DB_EXECUTESQL;
				}
			}
			else
			{
				return ret;
			}
		}
		else
		{
			return ERR_DB_EXECUTESQL;
		}
	}

	if (quick_mode)
		sqlResult = (HxSqlRes)mysql_use_result((&m_connMysql));
	else
		sqlResult = (HxSqlRes) mysql_store_result(&m_connMysql);

	if (NULL == sqlResult)
	{
		return ERR_DB_QUERYEMPTY;
	}

	return ERR_DB_NOERR;
}

int CMySQLConn::BeginTransaction()
{
	if (mysql_query(&m_connMysql, "START TRANSACTION") != 0)
	{
		return ERR_DB_STARTTRANFAIL;
	}
	return ERR_DB_NOERR;
}

int CMySQLConn::CancelTransaction()
{
	if (mysql_query(&m_connMysql, "ROLLBACK") != 0)
	{
		return ERR_DB_CANCELTRANFAIL;
	}
	return ERR_DB_NOERR;
}

int CMySQLConn::CommitTransaction()
{
	if (mysql_query(&m_connMysql, "COMMIT") != 0)
	{
		return ERR_DB_COMMITTRANFAIL;
	}
	return ERR_DB_NOERR;
}

int CMySQLConn::ConncectMySQL(char *host, int port, char *DbName, char *user, char *pswd, char *charset)
{
	if (mysql_init(&m_connMysql) == NULL)//mysql_init((MYSQL*)NULL) == NULL
	{
		return ERR_DB_INITCONNFAIL;
	}

	if (mysql_real_connect(&m_connMysql, host, user, pswd, DbName, port, NULL, 0) == NULL)
	{
		return ERR_DB_CREATECONNFAIL;
	}

	if (mysql_set_character_set(&m_connMysql, charset) != 0)
	{
		return ERR_DB_SETCHASETFAIL;
	}

	return ERR_DB_NOERR;
}

int CMySQLConn::ReConnMySQL()
{

	if (mysql_init(&m_connMysql) == NULL)
	{
		return ERR_DB_INITCONNFAIL;
	}

	if (mysql_real_connect(&m_connMysql, m_manager->m_host, m_manager->m_user, m_manager->m_password, m_manager->m_db, m_manager->m_port, NULL, 0) == NULL)
	{
		return ERR_DB_CREATECONNFAIL;
	}

	if (mysql_set_character_set(&m_connMysql, m_manager->m_charSet) != 0)
	{
		return ERR_DB_SETCHASETFAIL;
	}

	return ERR_DB_NOERR;

}

int CMySQLConn::DisConnect()
{
	mysql_close(&m_connMysql);
	return ERR_DB_NOERR;
}

int CMySQLConn::LockTable(const char *TableName, const char *Priority)
{
	int errCode = ERR_DB_NOERR;
	char szSql[50];
	sprintf_s(szSql, "LOCK TABLES %s %s", TableName, Priority);
	errCode=ExecSql(szSql);

	return errCode;
}

int CMySQLConn::UnlockTable()
{
	int errCode = ERR_DB_NOERR;
	char szSql[30] = "UNLOCK TABLES";
	errCode = ExecSql(szSql);

	return errCode;
}

inline HxResRow CMySQLConn::FetchRow(HxSqlRes pRecords)
{
	return ((HxResRow)mysql_fetch_row((MYSQL_RES *)pRecords));
}

inline HxResField CMySQLConn::FetchField(HxResRow &row, int fieldId)
{
	return ((MYSQL_ROW)row)[fieldId];
}

inline void CMySQLConn::ReleaseRecords(HxSqlRes pRecords)
{
	mysql_free_result((MYSQL_RES *)pRecords);
}
