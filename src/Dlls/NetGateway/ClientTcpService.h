
#pragma once
#ifndef CLIENT_TCP_SERVICE_H
#define CLIENT_TCP_SERVICE_H

#include "net_gateway_macros.h"
#include "include/NetGateway/net_gateway_client_interface_def.h"
#include "ace/Asynch_IO.h"
#include "ace/INET_Addr.h"
#include "ace/Recursive_Thread_Mutex.h"
#include "proto_head.hpp"

namespace NetGateway
{
	namespace Client
	{
		class CClientObject;
		class CClientConnector;

		class CClientTcpService : public ACE_Service_Handler, public CClientHandler
		{
		public:
			CClientTcpService();
			~CClientTcpService();
			/*************************************************
			Function:       open()
			Description:    重写 NetCommHandle 的虚函数，当有客户端连接,连接建立成功后Proactor框架会调用这个方法
			Input:
			     ACE_HANDLE new_handle： 
			     ACE_Message_Block &message_block： 
			Output:
			Return:		
			*************************************************/
			virtual void open(ACE_HANDLE new_handle, ACE_Message_Block &message_block);

			/*************************************************
			Function:       handle_read_stream()
			Description:    当网卡有数据要读取时,Proactor框架会调用该方法
			Input:
			     const ACE_Asynch_Read_Stream::Result &result：该链接的读流
			Output:
			Return:
			*************************************************/
			virtual void handle_read_stream(const ACE_Asynch_Read_Stream::Result &result);

			/*************************************************
			Function:       handle_write_stream()
			Description:    当用户数据已发送,Proactor框架会调用该方法
			Input:
			     const ACE_Asynch_Write_Stream::Result &result：该链接的写流
			Output:
			Return:
			*************************************************/
			virtual void handle_write_stream(const ACE_Asynch_Write_Stream::Result &result);

		public:
			/*************************************************
			Function:       Connect()
			Description:    网络连接
			Input:
				 const char *host ： 网址（主机IP）
				 int port ：  端口号
			Output:
			Return:			返回错误码
			*************************************************/
			virtual int Connect(const char *host, int port) ;

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
			virtual int Send(short netCommand, const void *buf, int bufLen) ;

			/*************************************************
			Function:       CloseConnection()
			Description:    主动关闭网络连接
			Input:
			Output:
			Return:
			*************************************************/
			virtual void CloseConnection();

			/*************************************************
			Function:       SetClientObject()
			Description:    
			Input:
				 CClientObject *client_object：
			Output:
			Return:
			*************************************************/
			void SetClientObject(CClientObject *client_object);


			void SetConnectorInfo(CClientConnector *connector);

		private:
			/*************************************************
			Function:       initiate_read_stream()
			Description:    初始化异步读流
			Input:
			Output:
			Return:
			*************************************************/
			int initiate_read_stream();

		private:
			// 用于该链接的读流
			ACE_Asynch_Read_Stream  m_rs;

			// 用于该链接的写流
			ACE_Asynch_Write_Stream m_ws;
			//  回调对象
			CClientObject *client_object_;

			CClientConnector *client_connector_;
			//  服务器地址
			char szAddr_peer_[NET_ADDR_BUF_LEN];
		};
	}
}


#endif // CLIENT_TCP_SERVICE_H