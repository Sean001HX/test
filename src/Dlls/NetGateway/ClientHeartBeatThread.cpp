#include "stdafx.h"
#include "ClientHeartBeatThread.h"
#include "ClientObjectMgr.h"
#include "c:/ng_tools/ng_header_for_log4cxx/ng_header_for_log4cxx.hpp"
#include "C:/ng_tools/ng_header_for_log4cxx/ng_header_for_log4cxx_log_var.hpp"

NG_LOGGER(logger, "NetGateway::Client::CClientHeartBeatThread");

namespace NetGateway
{
	namespace Client
	{


		CClientHeartBeatThread::CClientHeartBeatThread() : running_(false)
		{

		}

		CClientHeartBeatThread * CClientHeartBeatThread::Instance()
		{
			static CClientHeartBeatThread _inst;
			return &_inst;
		}

		int CClientHeartBeatThread::svc(void)
		{
			running_ = true;
			srand(time(0));
			int threadID = GetCurrentThreadId();
// 			try
// 			{
				LOG4CXX_INFO(logger, "svc()" LOG_VAR(threadID) LOG_VAR(this));

				while (running_)
				{
					Sleep(10 * 1000);

					CClientObjectMgr::Instance()->SendHeartBeat();
				}
// 			}
// 			catch (...)
// 			{
// 				LOG4CXX_ERROR(logger, "svc() throw an exception" LOG_VAR(threadID) LOG_VAR(this) );
// 			}
			LOG4CXX_ERROR(logger, "svc() ÒÑÍË³ö£¡" LOG_VAR(threadID) LOG_VAR(this));
			return 0;
		}

		void CClientHeartBeatThread::Stop()
		{
			running_ = false;
		}

		int CClientHeartBeatThread::open(void *args /*= 0*/)
		{
			return this->activate(THR_NEW_LWP | THR_JOINABLE | THR_INHERIT_SCHED,
				1,
				1);
		}

	} // Client
}  // NetGateway