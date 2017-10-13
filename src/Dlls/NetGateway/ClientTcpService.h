
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
			Description:    ��д NetCommHandle ���麯�������пͻ�������,���ӽ����ɹ���Proactor��ܻ�����������
			Input:
			     ACE_HANDLE new_handle�� 
			     ACE_Message_Block &message_block�� 
			Output:
			Return:		
			*************************************************/
			virtual void open(ACE_HANDLE new_handle, ACE_Message_Block &message_block);

			/*************************************************
			Function:       handle_read_stream()
			Description:    ������������Ҫ��ȡʱ,Proactor��ܻ���ø÷���
			Input:
			     const ACE_Asynch_Read_Stream::Result &result�������ӵĶ���
			Output:
			Return:
			*************************************************/
			virtual void handle_read_stream(const ACE_Asynch_Read_Stream::Result &result);

			/*************************************************
			Function:       handle_write_stream()
			Description:    ���û������ѷ���,Proactor��ܻ���ø÷���
			Input:
			     const ACE_Asynch_Write_Stream::Result &result�������ӵ�д��
			Output:
			Return:
			*************************************************/
			virtual void handle_write_stream(const ACE_Asynch_Write_Stream::Result &result);

		public:
			/*************************************************
			Function:       Connect()
			Description:    ��������
			Input:
				 const char *host �� ��ַ������IP��
				 int port ��  �˿ں�
			Output:
			Return:			���ش�����
			*************************************************/
			virtual int Connect(const char *host, int port) ;

			/*************************************************
			Function:       Send()
			Description:    ��������
			Input:
			     short netCommand : ����Э�鹦����
			     const void *buf ���������ݻ������ֽ�
			     int bufLen �� �������ֽڳ���
			Output:
			Return:          ���ش�����
			*************************************************/
			virtual int Send(short netCommand, const void *buf, int bufLen) ;

			/*************************************************
			Function:       CloseConnection()
			Description:    �����ر���������
			Input:
			Output:
			Return:
			*************************************************/
			virtual void CloseConnection();

			/*************************************************
			Function:       SetClientObject()
			Description:    
			Input:
				 CClientObject *client_object��
			Output:
			Return:
			*************************************************/
			void SetClientObject(CClientObject *client_object);


			void SetConnectorInfo(CClientConnector *connector);

		private:
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
			//  �ص�����
			CClientObject *client_object_;

			CClientConnector *client_connector_;
			//  ��������ַ
			char szAddr_peer_[NET_ADDR_BUF_LEN];
		};
	}
}


#endif // CLIENT_TCP_SERVICE_H