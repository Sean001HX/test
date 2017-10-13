#include "stdafx.h"
#include "NetListenThread.h"
#include "TcpAsynchAcceptor.h"
#include <assert.h>
#include "ace/INET_Addr.h"
#include "ace/Proactor.h"
#include <iostream>
#include "c:/ng_tools/ng_header_for_log4cxx/ng_header_for_log4cxx.hpp"
#include "C:/ng_tools/ng_header_for_log4cxx/ng_header_for_log4cxx_log_var.hpp"

NG_LOGGER(logger, "NetGateway::Server::CNetListenThread");

namespace NetGateway
{
	namespace Server
	{


		CNetListenThread::CNetListenThread() : num_threads_(2), port_(0)
		{

		}

		CNetListenThread * CNetListenThread::Instance()
		{
			static CNetListenThread _inst;
			return &_inst; 
		}

		CNetListenThread::~CNetListenThread()
		{

		}


		void CNetListenThread::Stop()
		{
			ACE_Proactor::instance()->proactor_end_event_loop();
			this->wait();
			m_bFlag = false;
		}

		int CNetListenThread::open(void *args /*= 0*/)
		{
			ACE_INET_Addr listen_addr(port_);
			if (CTcpAsynchAcceptor::Instance()->open(listen_addr, 0, 1, ACE_DEFAULT_ASYNCH_BACKLOG, 1, 0, 1))
			{
				LOG4CXX_FATAL(logger, "启动异步侦听失败"
					LOG_VAR(port_)
					);
				return -1;
			}

			std::cerr << "开始侦听端口: " << port_ << std::endl;

			LOG4CXX_INFO(logger, "开始侦听端口:"
				LOG_VAR(port_)
				);
			
			return this->activate(THR_NEW_LWP | THR_JOINABLE | THR_INHERIT_SCHED,
				num_threads_,
				1);
		}

		int CNetListenThread::close(u_long flags /*= 0*/)
		{
			return 0;
		}

		int CNetListenThread::svc(void)
		{
// 			try
// 			{
				m_bFlag = true;
				srand(time(0));
				int threadID = ::GetCurrentThreadId();
				LOG4CXX_DEBUG(logger, "svc()"
					LOG_VAR(threadID)
					);
				int ret = ACE_Proactor::instance()->proactor_run_event_loop();

				LOG4CXX_DEBUG(logger, "svc()"
					LOG_VAR(ret)
					);
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

		void CNetListenThread::Init(int threads_num, int listen_port)
		{
			assert(threads_num >= 1);
			//assert(listen_port > 0 && listen_port <= 65535);
			num_threads_ = threads_num;
			port_ = listen_port;
		}

	}  // Server
}