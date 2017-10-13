#pragma once

#ifndef NET_HEART_BEAT_THREAD_H
#define NET_HEART_BEAT_THREAD_H

#include "ace//Task.h"

namespace NetGateway
{
	namespace Server
	{
		class CNetHeartBeatThread : public ACE_Task_Base
		{
		private:
			CNetHeartBeatThread();
		public:
			static CNetHeartBeatThread *Insatnce();

			virtual int open(void *args = 0);
			//  Ïß³Ìº¯Êý
			virtual int svc(void);

			void Stop();

		private:
			bool running_;
		};
	}
}

#endif  // NET_HEART_BEAT_THREAD_H