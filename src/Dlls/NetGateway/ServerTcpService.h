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

			//��д NetCommHandle ���麯��

			/*************************************************
			Function:       open()
			Description:    ���пͻ�������,���ӽ����ɹ���Proactor��ܻ�����������
			Input:
			     ACE_HANDLE new_handle:
				 ACE_Message_Block &message_block:
			Output:
			Return:		
			*************************************************/
			virtual void open(ACE_HANDLE new_handle, ACE_Message_Block &message_block);

			/*************************************************
			Function:       handle_read_stream()
			Description:    ������������Ҫ��ȡʱ,Proactor��ܻ���ø÷���
			Input:
			     const ACE_Asynch_Read_Stream::Result &result:�����ӵĶ���
			Output:
			Return:
			*************************************************/
			virtual void handle_read_stream(const ACE_Asynch_Read_Stream::Result &result);

			/*************************************************
			Function:       handle_write_stream()
			Description:    ���û������ѷ���,Proactor��ܻ���ø÷���
			Input:
			    const ACE_Asynch_Write_Stream::Result &result:�����ӵ�д��
			Output:
			Return:
			*************************************************/
			virtual void handle_write_stream(const ACE_Asynch_Write_Stream::Result &result);

			/*************************************************
			Function:       addresses()
			Description:    ���û����ӳɹ�Proactor��ܻ��ȡ�ͻ��˵�ַ,��ȡ�ɹ������ø÷���
			Input:
			     const ACE_INET_Addr &remote_address: �Զ˵ĵ�ַ��Զ�̣�
				 const ACE_INET_Addr &local_address:  �Զ˵ĵ�ַ�����أ�
			Output:
			Return:
			*************************************************/
			virtual void addresses(const ACE_INET_Addr &remote_address, const ACE_INET_Addr &local_address);

		private:
			/*************************************************
			Function:       Write()
			Description:    ��������
			Input:
			     CProtoHead &proto_head: ����ͷ
				 const void *send_buf:  Ҫ���͵��ֽ���
				 int bytes_to_send:     ʵ�ʷ����ֽ���
			Output:
			Return: 0 ��ʾ�ɹ�,��0 ��ʾʧ��
			*************************************************/
			virtual int Write(CProtoHead &proto_head, const void *send_buf, int bytes_to_send);
	
			/*************************************************
			Function:       CloseConnection()
			Description:    �ر�ͨ������
			Input:
			Output:
			Return: 
			*************************************************/
			virtual int CloseConnection();

			/*************************************************
			Function:       initiate_read_stream()
			Description:    ��ʼ���첽����
			Input:
			Output:
			Return:
			*************************************************/
			int initiate_read_stream();

		private:

			// ���ڸ����ӵĶ���
			ACE_Asynch_Read_Stream  m_rs;

			// ���ڸ����ӵ�д��
			ACE_Asynch_Write_Stream m_ws;

			// �Զ˵ĵ�ַ
			ACE_INET_Addr	peer_addr_;

			char szAddr_peer_[NET_ADDR_BUF_LEN];
			//  �������ʵ��
			CNetObject *net_object_;
		};
	}
}

#endif  //  SERVER_TCP_SERVICE_H