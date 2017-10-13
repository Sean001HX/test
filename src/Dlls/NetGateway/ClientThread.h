//  �ͻ���ģʽ�첽�����߳�
#pragma once

#ifndef CLIENT_THREAD_H
#define CLIENT_THREAD_H

#include "ace//Task.h"

namespace NetGateway
{
	namespace Client
	{
		class CClientThread :public ACE_Task_Base
		{
		private:
			CClientThread();

		public:
			~CClientThread();

			/*************************************************
			Function:       Instance()
			Description:    ��ȡCClientThread�ĵ�һʵ��
			Input:
			Output:
			Return:			CClientThread��ָ��
			*************************************************/
			static CClientThread *Instance();

			/*************************************************
			Function:       Init()
			Description:    ��ʼ������
			Input:
			      int num_threads = 5 :
			Output:
			Return:
			*************************************************/
			void Init(int num_threads = 5);

			/*************************************************
			Function:       Stop()
			Description:    ��ʼ������
			Input:
			int num_threads = 5 :
			Output:
			Return:
			*************************************************/
			void Stop();

			// ��д���ຯ��
		public:
			virtual int open(void *args = 0);

			virtual int close(u_long flags = 0);

			virtual int svc(void);

			int num_threads_;

			bool init_flag;
		};
	}
}

#endif  //  CLIENT_THREAD_H