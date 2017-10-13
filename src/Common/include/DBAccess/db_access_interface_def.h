/***************************************************************************/
/*                                                                         */
/* Copyright (c) 2016  HX Tech Co.,Ltd.             　   　                */
/*                      恒希科技            版权所有 2016                   */
/*                                                                        */
/* PROPRIETARY RIGHTS of HX Tech Co.,Ltd. are involved in the  subject    */
/* matter of this material.  All manufacturing, reproduction, use, and    */
/* sales rights pertaining to this subject matter are governed by the     */
/* license agreement.  The recipient of this software implicitly accepts  */
/* the terms of the license.                                              */
/* 本软件文档资料是恒希科技公司的资产,任何人士阅读和使用本资料必须获得          */
/* 相应的书面授权,承担保密责任和接受相应的法律约束.                           */
/*                                                                        */
/***************************************************************************/

#ifndef DB_ACCESS_INTERFACE_DEF_H
#define DB_ACCESS_INTERFACE_DEF_H

//typedef struct st_mysql_res MYSQL_RES;
typedef void *  HxSqlRes;
typedef void ** HxResRow;
typedef char *	HxResField;

namespace DBAccess
{
	//数据访问的错误码  
	enum 
	{
		NoError = 0,
		CommenErr

	};

	class CDBHandler
	{
	public:
		virtual ~CDBHandler() {};

		/*************************************************
		Function:       InsertWithLastID()
		Description:    增加记录到数据库，并返回记录的ID
		Input:
			 const char *sql ： SQL语句
			 long long &lastID ： 记录的ID
		Output:
		Return:			返回错误码
		*************************************************/
		virtual int InsertWithLastID(const char *sql, long long &lastID) = 0;

		/*************************************************
		Function:       ExecSql()
		Description:    执行SQL语句，用于数据库的删、改操作
		                （同时在不返回记录ID的情形下，数据库增加记录的操作）
		Input:          const char *sql ： SQL语句
		Output:
		Return:			返回错误码
		*************************************************/
		virtual int ExecSql(const char *sql) = 0;
	
		/*************************************************
		Function:       QuerySql()
		Description:    执行SQL语句，用于数据库的查询操作
		Input:          
		     const char *sql ： SQL语句
			 MYSQL_RES *&sqlResult ：执行SQL语句查询的结果
			 bool quick_mode：在调用ReleaseRecords前，不再使用SQL操作的情况下，可以使用quick_mode，能有效提高速度，特别在数据量大的时候。
		Output:
		Return:			返回错误码
		*************************************************/
		virtual int QuerySql(const char *sql, HxSqlRes &sqlResult, bool quick_mode = false) = 0;

		/*************************************************
		Function:       LockTable()
		Description:    对特定表加锁
		Input:
			const char *TableName:表名
			const char *Priority:优先级,有read,write
		Output:
		Return:			返回错误码
		*************************************************/
		virtual int LockTable(const char *TableName, const char *Priority="write")=0; //

		/*************************************************
		Function:       UnlockTable()
		Description:    对所有表解锁
		Input:
		Output:
		Return:			返回错误码
		*************************************************/
		virtual int UnlockTable() = 0;       //解锁

		/*************************************************
		Function:       BeginTransaction()
		Description:    开始事务处理
		Input:
		Output:
		Return:			返回错误码
		*************************************************/
		virtual int BeginTransaction() = 0;

		/*************************************************
		Function:       CancelTransaction()
		Description:    取消事务处理
		Input:
		Output:
		Return:			返回错误码
		*************************************************/
		virtual int CancelTransaction() = 0;

		/*************************************************
		Function:       CommitTransaction()
		Description:    提交事务处理
		Input:
		Output:
		Return:			返回错误码
		*************************************************/
		virtual int CommitTransaction() = 0;

		/*************************************************
		Function:       FetchRow()
		Description:    提取记录集中的一行
		Input:	
			HxSqlRe pRecords：查询所得记录集
		Output:
		Return:			返回行。若为NULL表示已无行可取
		*************************************************/
		virtual HxResRow FetchRow(HxSqlRes pRecords) = 0;

		/*************************************************
		Function:       FetchField()
		Description:    提取行中某字段
		Input:
			HxResRow &row：某行
			int fieldId：字段ID
		Output:
		Return:			返回字段。
		*************************************************/
		virtual HxResField FetchField(HxResRow &row,int fieldId) = 0;

		/*************************************************
		Function:       ReleaseRecords()
		Description:    释放某记录集
		Input:
			HxSqlRes pRecords：记录集
		Output:
		Return:			
		*************************************************/
		virtual void ReleaseRecords(HxSqlRes pRecords)=0;
	};
}



#endif  // DB_ACCESS_INTERFACE_DEF_H