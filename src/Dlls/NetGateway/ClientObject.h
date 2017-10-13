#pragma once

#ifndef CLIENT_OBJECT_H
#define CLIENT_OBJECT_H

#include "net_gateway_macros.h"
#include "ace/Recursive_Thread_Mutex.h"
#include <time.h>
#include "include/NetGateway/net_gateway_errors.h"
#include "include/NetGateway/net_gateway_client_interface_def.h"
#include "proto_head.hpp"
#include "ace/Message_Block.h"

namespace NetGateway
{
	namespace Client
	{
		class CClientConnector;

		class CClientObject : public CClientHandler
		{
			friend class CClientConnector;
			friend class CClientObjectMgr;
			friend class CClientTcpService;

		public:
			CClientObject();
			~CClientObject();
			/*************************************************
			Function:       RegisterCallback()
			Description:    注册Client端网络通讯的回调类
			Input:          CClientCallback *callback : 回调接口类的具体实现
			Output:
			Return:
			*************************************************/
			virtual void RegisterCallback(CClientCallback *callback);

			/*************************************************
			Function:       Connect()
			Description:    网络连接
			Input:
			      const char *host ： 网址（主机IP）
			      int port ：  端口号
			Output:
			Return:			返回错误码
			*************************************************/
			virtual int Connect(const char *host, int port);

			/*************************************************
			Function:       Send()
			Description:    发送数据
			Input:
			     short netCommand : 网络协议功能码
			     const void *buf ：发送数据缓冲区字节
			     int bufLen ： 缓冲区字节长度
			Output:
			Return:          返回错误码
			*************************************************/
			virtual int Send(short netCommand, const void *buf, int bufLen);

			/*************************************************
			Function:       CloseConnection()
			Description:    主动关闭网络连接
			Input:
			Output:
			Return:
			*************************************************/
			virtual void CloseConnection();

			/*************************************************
			Function:       OnConnected()
			Description:    返回连接状态
			Input: 
			     bool is_ok:
				 CClientHandler *client_handler:
			Output:
			Return:
			*************************************************/
			void OnConnected(bool is_ok, CClientHandler *client_handler, CClientConnector *connector);

			/*************************************************
			Function:       OnRead()
			Description:    收到数据回调
			Input:
			     CClientHandler *client_handler:
				 const char *read_buf:
				 int bytes_received:
			Output:
			Return:
			*************************************************/
			void OnRead(CClientHandler *client_handler, const char *read_buf, int bytes_received);

			/*************************************************
			Function:       Occupy()
			Description:    占有此对象
			Input:
			Output:
			Return:     true = 占有成功， false = 占有失败
			*************************************************/
			bool Occupy();
		
			/*************************************************
			Function:       Free()
			Description:    释放此对象
			Input:
			Output:
			Return:     
			*************************************************/
			void Free();

		private:
			void SendHeartBeat();
			/*************************************************
			Function:       Reset()
			Description:  
			Input:
			Output:
			Return:
			*************************************************/
			void Reset();

			/*************************************************
			Function:       Init()
			Description:    初始化对象
			Input:
			Output:
			Return:
			*************************************************/
			void Init();

			/*************************************************
			Function:       PackData()
			Description:    打包
			Input:        
			     CProtoHead &proto_head：报文头
				 const char *buf； 数据缓冲区字节
				 int bufLen；  缓冲区字节长度
				 ACE_Message_Block &mb：
			Output:
			Return:     
			*************************************************/
			bool PackData(CProtoHead &proto_head, const char *buf, int bufLen, ACE_Message_Block &mb);

			/*************************************************
			Function:       DispatchPacket()
			Description:    分发数据包
			Input:
			      unsigned short netCommand：网络命令码
				  void *buf：数据缓冲区字节
				  int bufLen：缓冲区字节长度
			Output:
			Return:
			*************************************************/
			void DispatchPacket(unsigned short netCommand, void *buf, int bufLen);

		private:
			//  占用标志
			bool flag_in_use_;
			//  回调对象
			CClientCallback *callback_;
			//  对端地址
			char peer_addr_[NET_ADDR_BUF_LEN];

			//  通信种子
			unsigned short seed_;
			//  接收缓冲区
			char *recv_buf_;
			//  缓冲区中未解析的字节数
			int  unparsed_data_len_;
			//  发起连接时的连接对象
			CClientConnector *connector_;
			//  
			CClientHandler *client_handler_;
			//  CNetObject读写操作访问锁
			ACE_Recursive_Thread_Mutex  mutex_client_object_;
		};
	}
}

#endif  // CLIENT_OBJECT_H