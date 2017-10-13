//  侦听线程
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

			// 重写父类函数
		public:
			virtual int open(void *args = 0);

			virtual int close(u_long flags = 0);

			virtual int svc(void);

		public:
			//  运行标志
			bool m_bFlag;
			//  异步处理线程
			int num_threads_;
			//  侦听端口
			int port_;
		};
	}
}


#endif  //  NET_LISTEN_THREAD_H