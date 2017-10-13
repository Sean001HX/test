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
	Description:    ���Ӽ�¼�����ݿ⣬�����ؼ�¼��ID
	Input:
		const char *sql �� SQL���
		long long &lastID �� ��¼��ID
	Output:
	Return:			���ش�����
	*************************************************/
	virtual int InsertWithLastID(const char *sql, long long &lastID);

	/*************************************************
	Function:       ExecSql()
	Description:    ִ��SQL��䣬�������ݿ��ɾ���Ĳ���
	��ͬʱ�ڲ����ؼ�¼ID�������£����ݿ����Ӽ�¼�Ĳ�����
	Input:          const char *sql �� SQL���
	Output:
	Return:			���ش�����
	*************************************************/
	virtual int ExecSql(const char *sql);

	/*************************************************
	Function:       QuerySql()
	Description:    ִ��SQL��䣬�������ݿ�Ĳ�ѯ����
	Input:
		const char *sql �� SQL���
		MYSQL_RES *&sqlResult ��ִ��SQL����ѯ�Ľ��
	bool quick_mode:�ڵ���ReleaseRecordsǰ������ʹ��SQL����������£�����ʹ��quick_mode������Ч����ٶȣ��ر������������ʱ��
	Output:
	Return:			���ش�����
	*************************************************/
	virtual int QuerySql(const char *sql, HxSqlRes &sqlResult, bool quick_mode = false);

	/*************************************************
	Function:       LockTable()
	Description:    ���ض������
	Input:
		const char *TableName:����
		const char *Priority:���ȼ�,��read,write
	Output:
	Return:			���ش�����
	*************************************************/
	virtual int LockTable(const char *TableName, const char *Priority = "write");

	/*************************************************
	Function:       UnlockTable()
	Description:    �����б����
	Input:
	Output:
	Return:			���ش�����
	*************************************************/
	virtual int UnlockTable() ;  

	/*************************************************
	Function:       BeginTransaction()
	Description:    ��ʼ������
	Input:
	Output:
	Return:			���ش�����
	*************************************************/
	virtual int BeginTransaction();

	/*************************************************
	Function:       CancelTransaction()
	Description:    ȡ��������
	Input:
	Output:
	Return:			���ش�����
	*************************************************/
	virtual int CancelTransaction();

	/*************************************************
	Function:       CommitTransaction()
	Description:    �ύ������
	Input:
	Output:
	Return:			���ش�����
	*************************************************/
	virtual int CommitTransaction();

	/*************************************************
	Function:       FetchRow()
	Description:    ��ȡ��¼���е�һ��
	Input:
		HxSqlRe pRecords����ѯ���ü�¼��
	Output:
	Return:			�����С���ΪNULL��ʾ�����п�ȡ
	*************************************************/
	virtual HxResRow FetchRow(HxSqlRes pRecords) ;


	/*************************************************
	Function:       FetchField()
	Description:    ��ȡ����ĳ�ֶ�
	Input:
		HxResRow &row��ĳ��
		int fieldId���ֶ�ID
	Output:
	Return:			�����ֶΡ�
	*************************************************/
	virtual HxResField FetchField(HxResRow &row, int fieldId) ;

	/*************************************************
	Function:       ReleaseRecords()
	Description:    �ͷ�ĳ��¼��
	Input:
		HxSqlRes pRecords����¼��
	Output:
	Return:
	*************************************************/
	virtual void ReleaseRecords(HxSqlRes pRecords) ;

public:
	/*************************************************
	Function:       ConncectMySQL()
	Description:    �������ݿ�
	Input:
	      char *host�� ��ַ������IP��
		  int port��   �˿ں�
		  char *DbName�����ݿ���
		  char *user�� �û���
		  char *pswd�� ����
		  char *charset�� �ַ���
	Output:
	Return:  ���ش����롣
	*************************************************/
	int ConncectMySQL(char *host, int port, char *DbName, char *user, char *pswd, char *charset);

	/*************************************************
	Function:       DisConnect()
	Description:    �Ͽ�����
	Input:
	Output:
	Return:
	*************************************************/
	int DisConnect();

	/*************************************************
	Function:       ReConnMySQL()
	Description:    �������ݿ�
	Input:
	Output:
	Return:
	*************************************************/
	int ReConnMySQL();

public:
	//����ʹ��״̬
	bool m_bInUse;
private:
	MYSQL m_connMysql;
	CMySQLMan *m_manager;//���ݿ������ָ��
};
