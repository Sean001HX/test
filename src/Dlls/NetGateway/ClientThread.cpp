#include "stdafx.h"
#include "ClientThread.h"
#include "ace/Proactor.h"

#include "c:/ng_tools/ng_header_for_log4cxx/ng_header_for_log4cxx.hpp"
#include "C:/ng_tools/ng_header_for_log4cxx/ng_header_for_log4cxx_log_var.hpp"

NG_LOGGER(logger, "NetGateway::Client::CClientThread");

namespace NetGateway
{
	namespace Client
	{


		CClientThread::CClientThread() : num_threads_(5), init_flag(false)
		{

		}

		CClientThread * CClientThread::Instance()
		{
			static CClientThread _inst;
			return &_inst;
		}

		CClientThread::~CClientThread()
		{

		}

		void CClientThread::Stop()
		{
			if (init_flag)
			{
				ACE_Proactor::instance()->proactor_end_event_loop();
				this->wait();
			}	
		}

		int CClientThread::open(void *args /*= 0*/)
		{
			return this->activate(THR_NEW_LWP | THR_JOINABLE | THR_INHERIT_SCHED,
				num_threads_,
				1);
		}

		int CClientThread::close(u_long flags /*= 0*/)
		{
			return 0;
		}

		int CClientThread::svc(void)
		{
// 			try
// 			{
				init_flag = true;
				srand(time(0));
                OutputDebugString(TEXT("CClientThread::svc()"));
//                 LOG4CXX_INFO(logger, "svc()"
// 					);
				int ret = ACE_Proactor::instance()->proactor_run_event_loop();

//                 LOG4CXX_ERROR(logger, "svc()"
// 					LOG_VAR(ret)
// 					);
				return ret;
// 			}
// 			catch (...)
// 			{
// 				int threadID = ::GetCurrentThreadId();
// 				LOG4CXX_FATAL(logger, "svc() throw a exception"
// 					LOG_VAR(threadID)
// 					);
// 			}
			return 0;
		}

		void CClientThread::Init(int num_threads /*= 5*/)
		{
			if (num_threads > 0)
				num_threads_ = num_threads;
		}

	}  //  Client
}  //  NetGateway