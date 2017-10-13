//  �����߳�
#pragma once

#ifndef NET_LISTEN_THREAD_H
#define NET_LISTEN_THREAD_H

#include "ace//Task.h"

namespace NetGateway
{
	namespace Server
	{
		class CNetListenThread : public ACE_Task_Base
		{
		private:
			CNetListenThread();
		public:
			static CNetListenThread *Instance();
			~CNetListenThread();

			void Init(int threads_num, int listen_port);

			void Stop();

			// ��д���ຯ��
		public:
			virtual int open(void *args = 0);

			virtual int close(u_long flags = 0);

			virtual int svc(void);

		public:
			//  ���б�־
			bool m_bFlag;
			//  �첽�����߳�
			int num_threads_;
			//  �����˿�
			int port_;
		};
	}
}


#endif  //  NET_LISTEN_THREAD_H