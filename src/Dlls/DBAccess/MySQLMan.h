#pragma once
#include <list>
#include "time.h" 

#define CONNECTION_NUM 10		//同时打开的连接数
#define CONNECTION_NUM_INIT 10	//初始同时打开的连接数
#define CHECK_ALLOC_CONN 3600	//检查空闲连接的时间间隔(秒)

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
	Description:    获取CMySQLMan的单一实例
	Input:
	Output:
	Return:			CMySQLMan的指针
	*************************************************/
	static CMySQLMan *Instance();

	/*************************************************
	Function:       ConnectDB()
	Description:    连接数据库
	Input:
	     const char *host：网址（主机IP）
	     const char *user：用户名
		 const char *password：密码
		 const char *db ：数据库名
		 unsigned int port：端口号
		 char *charSet = "gbk" ：字符集
	Output:
	Return:			返回连接成功与否
	*************************************************/
	bool ConnectDB(const char *host, const char *user, const char *password, const char *db, unsigned int port, char *charSet = "gbk");  

	/*************************************************
	Function:       CloseConnect()
	Description:    关闭所有连接
	Input:
	Output:
	Return:			
	*************************************************/
	void CloseConnect();

	/*************************************************
	Function:       IsTimeForTrim()
	Description:    一段时间后判断修整连接链表
	Input:         
	     time_t &lastTime：上次批量连接时间，
	     time_t &curTime：现在时间
	Output:
	Return:
	*************************************************/
	bool IsTimeForTrim(time_t &lastTime, time_t &curTime);

	/*************************************************
	Function:       TrimConn()
	Description:    修整连接链表
	Input:
	Output:
	Return:
	*************************************************/
	void TrimConn();

	/*************************************************
	Function:       GetAnIdleConn()
	Description:    返回一个空闲连接
	Input:
	Output:
	Return:         CMySQLMan的指针
	*************************************************/
	CMySQLConn *GetAnIdleConn();

	/*************************************************
	Function:       SetAConnToAdle()
	Description:    将一个连接设成空闲状态
	Input:
	     CMySQLConn *pConn ：一个连接对象
	Output:
	Return:
	*************************************************/
	void SetAConnToAdle(CMySQLConn *pConn);

public:
	char m_host[40];       //主机
	char m_user[40];       //用户名
	char m_password[40];   //密码
	char m_db[40];         //数据库名
	char m_charSet[40];    //字符集
	unsigned int m_port;   //端口
private:
	int AllocConnection(int num);
private:
	CRITICAL_SECTION m_csList;
	CONN_LIST m_ConnList;          //未使用的连接
	time_t m_last_alloc_time;     //上次批量连接时间
	int m_iNumUsed;               //正在使用的连接数
};

