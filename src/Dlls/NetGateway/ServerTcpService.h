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

#pragma once

#ifndef SERVER_TCP_SERVICE_H
#define SERVER_TCP_SERVICE_H

#include "net_gateway_macros.h"
#include "include/NetGateway/net_gateway_interface_def.h"
#include "ace/Asynch_IO.h"
#include "ace/INET_Addr.h"
#include "ace/Recursive_Thread_Mutex.h"
#include "NetCommHandle.h"
#include "proto_head.hpp"

namespace NetGateway
{
	namespace Server
	{
		class CServerTcpService : public ACE_Service_Handler, public NetCommHandle
		{
		public:
			CServerTcpService();
			~CServerTcpService();

			//重写 NetCommHandle 的虚函数

			/*************************************************
			Function:       open()
			Description:    当有客户端连接,连接建立成功后Proactor框架会调用这个方法
			Input:
			     ACE_HANDLE new_handle:
				 ACE_Message_Block &message_block:
			Output:
			Return:		
			*************************************************/
			virtual void open(ACE_HANDLE new_handle, ACE_Message_Block &message_block);

			/*************************************************
			Function:       handle_read_stream()
			Description:    当网卡有数据要读取时,Proactor框架会调用该方法
			Input:
			     const ACE_Asynch_Read_Stream::Result &result:该链接的读流
			Output:
			Return:
			*************************************************/
			virtual void handle_read_stream(const ACE_Asynch_Read_Stream::Result &result);

			/*************************************************
			Function:       handle_write_stream()
			Description:    当用户数据已发送,Proactor框架会调用该方法
			Input:
			    const ACE_Asynch_Write_Stream::Result &result:该链接的写流
			Output:
			Return:
			*************************************************/
			virtual void handle_write_stream(const ACE_Asynch_Write_Stream::Result &result);

			/*************************************************
			Function:       addresses()
			Description:    当用户连接成功Proactor框架会获取客户端地址,获取成功后会调用该方法
			Input:
			     const ACE_INET_Addr &remote_address: 对端的地址（远程）
				 const ACE_INET_Addr &local_address:  对端的地址（本地）
			Output:
			Return:
			*************************************************/
			virtual void addresses(const ACE_INET_Addr &remote_address, const ACE_INET_Addr &local_address);

		private:
			/*************************************************
			Function:       Write()
			Description:    发送数据
			Input:
			     CProtoHead &proto_head: 报文头
				 const void *send_buf:  要发送的字节数
				 int bytes_to_send:     实际发送字节数
			Output:
			Return: 0 表示成功,非0 表示失败
			*************************************************/
			virtual int Write(CProtoHead &proto_head, const void *send_buf, int bytes_to_send);
	
			/*************************************************
			Function:       CloseConnection()
			Description:    关闭通信连接
			Input:
			Output:
			Return: 
			*************************************************/
			virtual int CloseConnection();

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

			// 对端的地址
			ACE_INET_Addr	peer_addr_;

			char szAddr_peer_[NET_ADDR_BUF_LEN];
			//  网络对象实例
			CNetObject *net_object_;
		};
	}
}

#endif  //  SERVER_TCP_SERVICE_H