#include "stdafx.h"
#include "NetHeartBeatThread.h"
#include "NetObjectMgr.h"
#include "c:/ng_tools/ng_header_for_log4cxx/ng_header_for_log4cxx.hpp"
#include "C:/ng_tools/ng_header_for_log4cxx/ng_header_for_log4cxx_log_var.hpp"

NG_LOGGER(logger, "NetGateway::Server::CNetHeartBeatThread");

namespace NetGateway
{
	namespace Server
	{


		CNetHeartBeatThread::CNetHeartBeatThread() : running_(false)
		{

		}

		CNetHeartBeatThread * CNetHeartBeatThread::Insatnce()
		{
			static CNetHeartBeatThread _inst;
			return &_inst;
		}

		int CNetHeartBeatThread::svc(void)
		{
			running_ = true;
			srand(time(0));
			int threadID = GetCurrentThreadId();
// 			try
// 			{
				LOG4CXX_INFO(logger, "svc()" LOG_VAR(threadID) LOG_VAR(this));

				while (running_)
				{
					Sleep(30 * 1000);
					unsigned nowTime = time(0);
					CNetObjectMgr::Instance()->CheckHeartBeat(nowTime);
				}
// 			}
// 			catch (...)
// 			{
// 				LOG4CXX_ERROR(logger, "svc() throw an exception" LOG_VAR(threadID) LOG_VAR(this));
// 			}

			return 0;
		}

		void CNetHeartBeatThread::Stop()
		{
			running_ = false;
		}

		int CNetHeartBeatThread::open(void *args /*= 0*/)
		{
			return this->activate(THR_NEW_LWP | THR_JOINABLE | THR_INHERIT_SCHED,
				1,
				1);
		}

	}  //  Server
}  // NetGateway