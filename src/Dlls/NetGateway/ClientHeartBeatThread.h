#pragma once

#ifndef CLIENT_HEART_BEAT_THREAD_H
#define CLIENT_HEART_BEAT_THREAD_H

#include "ace//Task.h"

namespace NetGateway
{
	namespace Client
	{
		class CClientHeartBeatThread : public ACE_Task_Base
		{
		private:
			CClientHeartBeatThread();
		public:
			static CClientHeartBeatThread *Instance();

			virtual int open(void *args = 0);
			//  Ïß³Ìº¯Êý
			virtual int svc(void);

			void Stop();

		private:
			bool running_;
		};
	}
}

#endif  // 