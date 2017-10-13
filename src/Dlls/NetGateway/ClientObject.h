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
			Description:    ע��Client������ͨѶ�Ļص���
			Input:          CClientCallback *callback : �ص��ӿ���ľ���ʵ��
			Output:
			Return:
			*************************************************/
			virtual void RegisterCallback(CClientCallback *callback);

			/*************************************************
			Function:       Connect()
			Description:    ��������
			Input:
			      const char *host �� ��ַ������IP��
			      int port ��  �˿ں�
			Output:
			Return:			���ش�����
			*************************************************/
			virtual int Connect(const char *host, int port);

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
			virtual int Send(short netCommand, const void *buf, int bufLen);

			/*************************************************
			Function:       CloseConnection()
			Description:    �����ر���������
			Input:
			Output:
			Return:
			*************************************************/
			virtual void CloseConnection();

			/*************************************************
			Function:       OnConnected()
			Description:    ��������״̬
			Input: 
			     bool is_ok:
				 CClientHandler *client_handler:
			Output:
			Return:
			*************************************************/
			void OnConnected(bool is_ok, CClientHandler *client_handler, CClientConnector *connector);

			/*************************************************
			Function:       OnRead()
			Description:    �յ����ݻص�
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
			Description:    ռ�д˶���
			Input:
			Output:
			Return:     true = ռ�гɹ��� false = ռ��ʧ��
			*************************************************/
			bool Occupy();
		
			/*************************************************
			Function:       Free()
			Description:    �ͷŴ˶���
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
			Description:    ��ʼ������
			Input:
			Output:
			Return:
			*************************************************/
			void Init();

			/*************************************************
			Function:       PackData()
			Description:    ���
			Input:        
			     CProtoHead &proto_head������ͷ
				 const char *buf�� ���ݻ������ֽ�
				 int bufLen��  �������ֽڳ���
				 ACE_Message_Block &mb��
			Output:
			Return:     
			*************************************************/
			bool PackData(CProtoHead &proto_head, const char *buf, int bufLen, ACE_Message_Block &mb);

			/*************************************************
			Function:       DispatchPacket()
			Description:    �ַ����ݰ�
			Input:
			      unsigned short netCommand������������
				  void *buf�����ݻ������ֽ�
				  int bufLen���������ֽڳ���
			Output:
			Return:
			*************************************************/
			void DispatchPacket(unsigned short netCommand, void *buf, int bufLen);

		private:
			//  ռ�ñ�־
			bool flag_in_use_;
			//  �ص�����
			CClientCallback *callback_;
			//  �Զ˵�ַ
			char peer_addr_[NET_ADDR_BUF_LEN];

			//  ͨ������
			unsigned short seed_;
			//  ���ջ�����
			char *recv_buf_;
			//  ��������δ�������ֽ���
			int  unparsed_data_len_;
			//  ��������ʱ�����Ӷ���
			CClientConnector *connector_;
			//  
			CClientHandler *client_handler_;
			//  CNetObject��д����������
			ACE_Recursive_Thread_Mutex  mutex_client_object_;
		};
	}
}

#endif  // CLIENT_OBJECT_H