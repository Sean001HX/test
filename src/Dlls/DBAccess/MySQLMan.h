#pragma once
#include <list>
#include "time.h" 

#define CONNECTION_NUM 10		//ͬʱ�򿪵�������
#define CONNECTION_NUM_INIT 10	//��ʼͬʱ�򿪵�������
#define CHECK_ALLOC_CONN 3600	//���������ӵ�ʱ����(��)

class CMySQLConn;

typedef std::list<CMySQLConn *> CONN_LIST;
typedef std::list<CMySQLConn *>::iterator ITER_CONN_LIST;


class CMySQLMan
{
public:
	CMySQLMan();
	~CMySQLMan();
public:

	/*************************************************
	Function:       Instance()
	Description:    ��ȡCMySQLMan�ĵ�һʵ��
	Input:
	Output:
	Return:			CMySQLMan��ָ��
	*************************************************/
	static CMySQLMan *Instance();

	/*************************************************
	Function:       ConnectDB()
	Description:    �������ݿ�
	Input:
	     const char *host����ַ������IP��
	     const char *user���û���
		 const char *password������
		 const char *db �����ݿ���
		 unsigned int port���˿ں�
		 char *charSet = "gbk" ���ַ���
	Output:
	Return:			�������ӳɹ����
	*************************************************/
	bool ConnectDB(const char *host, const char *user, const char *password, const char *db, unsigned int port, char *charSet = "gbk");  

	/*************************************************
	Function:       CloseConnect()
	Description:    �ر���������
	Input:
	Output:
	Return:			
	*************************************************/
	void CloseConnect();

	/*************************************************
	Function:       IsTimeForTrim()
	Description:    һ��ʱ����ж�������������
	Input:         
	     time_t &lastTime���ϴ���������ʱ�䣬
	     time_t &curTime������ʱ��
	Output:
	Return:
	*************************************************/
	bool IsTimeForTrim(time_t &lastTime, time_t &curTime);

	/*************************************************
	Function:       TrimConn()
	Description:    ������������
	Input:
	Output:
	Return:
	*************************************************/
	void TrimConn();

	/*************************************************
	Function:       GetAnIdleConn()
	Description:    ����һ����������
	Input:
	Output:
	Return:         CMySQLMan��ָ��
	*************************************************/
	CMySQLConn *GetAnIdleConn();

	/*************************************************
	Function:       SetAConnToAdle()
	Description:    ��һ��������ɿ���״̬
	Input:
	     CMySQLConn *pConn ��һ�����Ӷ���
	Output:
	Return:
	*************************************************/
	void SetAConnToAdle(CMySQLConn *pConn);

public:
	char m_host[40];       //����
	char m_user[40];       //�û���
	char m_password[40];   //����
	char m_db[40];         //���ݿ���
	char m_charSet[40];    //�ַ���
	unsigned int m_port;   //�˿�
private:
	int AllocConnection(int num);
private:
	CRITICAL_SECTION m_csList;
	CONN_LIST m_ConnList;          //δʹ�õ�����
	time_t m_last_alloc_time;     //�ϴ���������ʱ��
	int m_iNumUsed;               //����ʹ�õ�������
};

