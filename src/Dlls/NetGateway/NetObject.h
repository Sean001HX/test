#pragma once

#ifndef NET_OBJECT_H
#define NET_OBJECT_H

#include "net_gateway_macros.h"
#include "ace/Recursive_Thread_Mutex.h"
#include <time.h>

namespace NetGateway
{
	namespace Server
	{

		class NetCommHandle;

		class CNetObject
		{
			friend class CNetObjectMgr;
		public:
			CNetObject();
			~CNetObject();
			/*************************************************
			Function:       OnNewConnection()
			Description:    �����ӻص�
			Input: 
			     NetCommHandle *pHandler��ͨ�ŷ��ʵľ��
				 const char *peer_addrs���Զ�ip��ַ "xxx.xxx.xxx.xxx"
			Output:
			Return:		true ����ɹ�,false:����ɹ�
			*************************************************/
			virtual bool OnNewConnection(NetCommHandle *pHandler, const char *peer_addrs);

			/*************************************************
			Function:       OnWrite()
			Description:    ���ط��ͻص�
			Input:
			    NetCommHandle *handler��ͨ�ŷ��ʵľ��
				int bytes_to_send��Ҫ���͵��ֽ���
				int bytes_sent �� ʵ�ʷ����ֽ���
			Output:
			Return:		
			*************************************************/
			virtual void OnWrite(NetCommHandle *handler, int bytes_to_send, int bytes_sent);

			/*************************************************
			Function:       OnRead()
			Description:    �յ����ݻص�
			Input:
			     NetCommHandle *handler��ͨ�ŷ��ʵľ��
			     const char *read_buf�����յ����ݻ�����
			     int bytes_received �� ���յ����ֽ���
			Output:
			Return:
			*************************************************/
			virtual void OnRead(NetCommHandle *handler, const char *read_buf, int bytes_received);

			/*************************************************
			Function:       OnDisconnected()
			Description:    ���߻ص�
			Input:
			     NetCommHandle *handler��ͨ�ŷ��ʵľ��
			Output:
			Return:
			*************************************************/
			virtual void OnDisconnected(NetCommHandle *handler);

			/*************************************************
			Function:       InitCommSeed()
			Description:    ��ʼ��ͨ������
			Input:
			     NetCommHandle *handler��ͨ�ŷ��ʵľ��
			Output:
			Return:
			*************************************************/
			virtual void InitCommSeed(NetCommHandle *handler);

		public:
			/*************************************************
			Function:       Send()
			Description:    ��������
			Input:
			    NetCommHandle *handler ��   �������Ӷ����Handle
			    unsigned short netCommand : �������ӵĹ�����
			    const void *buf :           �������ݻ������ֽ�
			    int bufLen :                �������ֽڳ���
			Output:
			Return:  
			*************************************************/
			int Send(NetCommHandle *handler, unsigned short netCommand, const void *buf, int bufLen);

			/*************************************************
			Function:       CloseConnection()
			Description:    �ر�����
			Input:
			     NetCommHandle *handler��ͨ�ŷ��ʵľ��
			Output:
			Return:
			*************************************************/
			int CloseConnection(NetCommHandle *handler);

			/*************************************************
			Function:       Handler()
			Description:    
			Input:
			Output:
			Return:
			*************************************************/
			NetCommHandle *Handler() const;

			/*************************************************
			Function:       Reset()
			Description:    ���ô˶���
			Input:
			Output:
			Return:
			*************************************************/
			void Reset();

		private:
			/*************************************************
			Function:       __SendImp()
			Description:    �������
			Input:   
				unsigned short netCommand : ����Э�鹦����
				const void *buf ���������ݻ������ֽ�
				int bufLen �� �������ֽڳ���
			Output:
			Return:
			*************************************************/
			int __SendImp(unsigned short netCommand, const void *buf, int bufLen);

			/*************************************************
			Function:       DispatchPacket()
			Description:    �ַ����ݰ�
			Input:
				unsigned short netCommand : ����Э�鹦����
				const void *buf ���������ݻ������ֽ�
				int bufLen �� �������ֽڳ���
			Output:
			Return:
			*************************************************/
			void DispatchPacket(unsigned short netCommand, void *buf, int bufLen);

			void CheckHeartBeat(unsigned nowTime);

			void HandleHeartBeat();
		private:
			//  �Զ˵�ַ
			char peer_addr_[NET_ADDR_BUF_LEN];
			
			//  CNetObject��д����������
			ACE_Recursive_Thread_Mutex  mutex_net_object_;
			//  ��˶���󶨵�ͨ�ŷ��ʹ����
			NetCommHandle *net_comm_handle_;
			//  ���һ������ʱ��
			time_t last_heart_beat_time_;
			//  ��������ʱ��
			time_t seed_generate_time_;
			//  ͨ������
			unsigned short seed_;
			unsigned short seed_new_;
			//  ���ջ�����
			char *recv_buf_;
			int  unparsed_data_len_;
		public:
			//  �ö���ı��
			int index_;
		};
	}  // Server
}  //  NetGateway


#endif // NET_OBJECT_H



