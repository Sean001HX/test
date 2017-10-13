#pragma once

#include "mysql.h"
#include "dbErr.h"
#include "DBAccess\db_access_interface_def.h"

class CMySQLMan;


class CMySQLConn :public DBAccess::CDBHandler
{
public:
	CMySQLConn(CMySQLMan *pManager);
	~CMySQLConn();


	/*************************************************
	Function:       InsertWithLastID()
	Description:    增加记录到数据库，并返回记录的ID
	Input:
		const char *sql ： SQL语句
		long long &lastID ： 记录的ID
	Output:
	Return:			返回错误码
	*************************************************/
	virtual int InsertWithLastID(const char *sql, long long &lastID);

	/*************************************************
	Function:       ExecSql()
	Description:    执行SQL语句，用于数据库的删、改操作
	（同时在不返回记录ID的情形下，数据库增加记录的操作）
	Input:          const char *sql ： SQL语句
	Output:
	Return:			返回错误码
	*************************************************/
	virtual int ExecSql(const char *sql);

	/*************************************************
	Function:       QuerySql()
	Description:    执行SQL语句，用于数据库的查询操作
	Input:
		const char *sql ： SQL语句
		MYSQL_RES *&sqlResult ：执行SQL语句查询的结果
	bool quick_mode:在调用ReleaseRecords前，不再使用SQL操作的情况下，可以使用quick_mode，能有效提高速度，特别在数据量大的时候。
	Output:
	Return:			返回错误码
	*************************************************/
	virtual int QuerySql(const char *sql, HxSqlRes &sqlResult, bool quick_mode = false);

	/*************************************************
	Function:       LockTable()
	Description:    对特定表加锁
	Input:
		const char *TableName:表名
		const char *Priority:优先级,有read,write
	Output:
	Return:			返回错误码
	*************************************************/
	virtual int LockTable(const char *TableName, const char *Priority = "write");

	/*************************************************
	Function:       UnlockTable()
	Description:    对所有表解锁
	Input:
	Output:
	Return:			返回错误码
	*************************************************/
	virtual int UnlockTable() ;  

	/*************************************************
	Function:       BeginTransaction()
	Description:    开始事务处理
	Input:
	Output:
	Return:			返回错误码
	*************************************************/
	virtual int BeginTransaction();

	/*************************************************
	Function:       CancelTransaction()
	Description:    取消事务处理
	Input:
	Output:
	Return:			返回错误码
	*************************************************/
	virtual int CancelTransaction();

	/*************************************************
	Function:       CommitTransaction()
	Description:    提交事务处理
	Input:
	Output:
	Return:			返回错误码
	*************************************************/
	virtual int CommitTransaction();

	/*************************************************
	Function:       FetchRow()
	Description:    提取记录集中的一行
	Input:
		HxSqlRe pRecords：查询所得记录集
	Output:
	Return:			返回行。若为NULL表示已无行可取
	*************************************************/
	virtual HxResRow FetchRow(HxSqlRes pRecords) ;


	/*************************************************
	Function:       FetchField()
	Description:    提取行中某字段
	Input:
		HxResRow &row：某行
		int fieldId：字段ID
	Output:
	Return:			返回字段。
	*************************************************/
	virtual HxResField FetchField(HxResRow &row, int fieldId) ;

	/*************************************************
	Function:       ReleaseRecords()
	Description:    释放某记录集
	Input:
		HxSqlRes pRecords：记录集
	Output:
	Return:
	*************************************************/
	virtual void ReleaseRecords(HxSqlRes pRecords) ;

public:
	/*************************************************
	Function:       ConncectMySQL()
	Description:    连接数据库
	Input:
	      char *host： 网址（主机IP）
		  int port；   端口号
		  char *DbName：数据库名
		  char *user： 用户名
		  char *pswd： 密码
		  char *charset： 字符集
	Output:
	Return:  返回错误码。
	*************************************************/
	int ConncectMySQL(char *host, int port, char *DbName, char *user, char *pswd, char *charset);

	/*************************************************
	Function:       DisConnect()
	Description:    断开连接
	Input:
	Output:
	Return:
	*************************************************/
	int DisConnect();

	/*************************************************
	Function:       ReConnMySQL()
	Description:    重连数据库
	Input:
	Output:
	Return:
	*************************************************/
	int ReConnMySQL();

public:
	//连接使用状态
	bool m_bInUse;
private:
	MYSQL m_connMysql;
	CMySQLMan *m_manager;//数据库管理类指针
};
