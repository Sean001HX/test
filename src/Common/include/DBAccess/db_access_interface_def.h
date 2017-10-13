/***************************************************************************/
/*                                                                         */
/* Copyright (c) 2016  HX Tech Co.,Ltd.             ��   ��                */
/*                      ��ϣ�Ƽ�            ��Ȩ���� 2016                   */
/*                                                                        */
/* PROPRIETARY RIGHTS of HX Tech Co.,Ltd. are involved in the  subject    */
/* matter of this material.  All manufacturing, reproduction, use, and    */
/* sales rights pertaining to this subject matter are governed by the     */
/* license agreement.  The recipient of this software implicitly accepts  */
/* the terms of the license.                                              */
/* ������ĵ������Ǻ�ϣ�Ƽ���˾���ʲ�,�κ���ʿ�Ķ���ʹ�ñ����ϱ�����          */
/* ��Ӧ��������Ȩ,�е��������κͽ�����Ӧ�ķ���Լ��.                           */
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
	//���ݷ��ʵĴ�����  
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
		Description:    ���Ӽ�¼�����ݿ⣬�����ؼ�¼��ID
		Input:
			 const char *sql �� SQL���
			 long long &lastID �� ��¼��ID
		Output:
		Return:			���ش�����
		*************************************************/
		virtual int InsertWithLastID(const char *sql, long long &lastID) = 0;

		/*************************************************
		Function:       ExecSql()
		Description:    ִ��SQL��䣬�������ݿ��ɾ���Ĳ���
		                ��ͬʱ�ڲ����ؼ�¼ID�������£����ݿ����Ӽ�¼�Ĳ�����
		Input:          const char *sql �� SQL���
		Output:
		Return:			���ش�����
		*************************************************/
		virtual int ExecSql(const char *sql) = 0;
	
		/*************************************************
		Function:       QuerySql()
		Description:    ִ��SQL��䣬�������ݿ�Ĳ�ѯ����
		Input:          
		     const char *sql �� SQL���
			 MYSQL_RES *&sqlResult ��ִ��SQL����ѯ�Ľ��
			 bool quick_mode���ڵ���ReleaseRecordsǰ������ʹ��SQL����������£�����ʹ��quick_mode������Ч����ٶȣ��ر������������ʱ��
		Output:
		Return:			���ش�����
		*************************************************/
		virtual int QuerySql(const char *sql, HxSqlRes &sqlResult, bool quick_mode = false) = 0;

		/*************************************************
		Function:       LockTable()
		Description:    ���ض������
		Input:
			const char *TableName:����
			const char *Priority:���ȼ�,��read,write
		Output:
		Return:			���ش�����
		*************************************************/
		virtual int LockTable(const char *TableName, const char *Priority="write")=0; //

		/*************************************************
		Function:       UnlockTable()
		Description:    �����б����
		Input:
		Output:
		Return:			���ش�����
		*************************************************/
		virtual int UnlockTable() = 0;       //����

		/*************************************************
		Function:       BeginTransaction()
		Description:    ��ʼ������
		Input:
		Output:
		Return:			���ش�����
		*************************************************/
		virtual int BeginTransaction() = 0;

		/*************************************************
		Function:       CancelTransaction()
		Description:    ȡ��������
		Input:
		Output:
		Return:			���ش�����
		*************************************************/
		virtual int CancelTransaction() = 0;

		/*************************************************
		Function:       CommitTransaction()
		Description:    �ύ������
		Input:
		Output:
		Return:			���ش�����
		*************************************************/
		virtual int CommitTransaction() = 0;

		/*************************************************
		Function:       FetchRow()
		Description:    ��ȡ��¼���е�һ��
		Input:	
			HxSqlRe pRecords����ѯ���ü�¼��
		Output:
		Return:			�����С���ΪNULL��ʾ�����п�ȡ
		*************************************************/
		virtual HxResRow FetchRow(HxSqlRes pRecords) = 0;

		/*************************************************
		Function:       FetchField()
		Description:    ��ȡ����ĳ�ֶ�
		Input:
			HxResRow &row��ĳ��
			int fieldId���ֶ�ID
		Output:
		Return:			�����ֶΡ�
		*************************************************/
		virtual HxResField FetchField(HxResRow &row,int fieldId) = 0;

		/*************************************************
		Function:       ReleaseRecords()
		Description:    �ͷ�ĳ��¼��
		Input:
			HxSqlRes pRecords����¼��
		Output:
		Return:			
		*************************************************/
		virtual void ReleaseRecords(HxSqlRes pRecords)=0;
	};
}



#endif  // DB_ACCESS_INTERFACE_DEF_H