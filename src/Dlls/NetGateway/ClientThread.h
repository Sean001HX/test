//  客户端模式异步处理线程
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
			Description:    获取CClientThread的单一实例
			Input:
			Output:
			Return:			CClientThread的指针
			*************************************************/
			static CClientThread *Instance();

			/*************************************************
			Function:       Init()
			Description:    初始化对象
			Input:
			      int num_threads = 5 :
			Output:
			Return:
			*************************************************/
			void Init(int num_threads = 5);

			/*************************************************
			Function:       Stop()
			Description:    初始化对象
			Input:
			int num_threads = 5 :
			Output:
			Return:
			*************************************************/
			void Stop();

			// 重写父类函数
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