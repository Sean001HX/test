#include "stdafx.h"
#include "ClientObjectMgr.h"
#include "ClientThread.h"
#include "windows.h"
#include "ClientHeartBeatThread.h"
#include "c:/ng_tools/ng_header_for_log4cxx/ng_header_for_log4cxx.hpp"
#include "C:/ng_tools/ng_header_for_log4cxx/ng_header_for_log4cxx_log_var.hpp"

NG_LOGGER(logger, "NetGateway::Client::CClientObjectMgr");

extern void *g_client_CNetHeartBeatThread;
extern void *g_client_CClientThread;



namespace NetGateway
{
	namespace Client
	{


		CClientObjectMgr::CClientObjectMgr()
		{
			NGTrace trace(logger,  "CClientObjectMgr()");
// 			for (int i = 0; i < sizeof(client_objects_) / sizeof(client_objects_[0]); ++i)
// 			{
// 				client_objects_[i].Init();
// 			}

			int num_threads = ::GetPrivateProfileIntA("CLIENT", "THREADS", 5, "./net_gateway.hxc");
			//  初始化客户模式线程
			CClientThread::Instance()->Init(num_threads);
			if (CClientThread::Instance()->open() < 0)
			{
				LOG4CXX_FATAL(logger, "CClientThread::Instance()->open() < 0"
					LOG_VAR(num_threads)
					);
			}
			else
			{
				g_client_CClientThread = this;
			}

			if (CClientHeartBeatThread::Instance()->open() < 0)
			{
				LOG4CXX_FATAL(logger, "if (CClientHeartBeatThread::Instance()->open() < 0)");
			}
			else
			{
				g_client_CNetHeartBeatThread = this;
			}
		}

		CClientObjectMgr * CClientObjectMgr::Instance()
		{
			static CClientObjectMgr _inst;
			return &_inst;
		}

		CClientObjectMgr::~CClientObjectMgr()
		{

		}

		CClientObject * CClientObjectMgr::Alloc()
		{
			NGTrace trace(logger,  "Alloc()");

			int i = 0;
			for ( ; i < sizeof(client_objects_) / sizeof(client_objects_[0]); ++i)
			{
				if (client_objects_[i].Occupy())
					return &client_objects_[i];
			}

			return 0;
		}

		void CClientObjectMgr::Free(CClientHandler *client_handler)
		{
			NGTrace trace(logger,  "Free()");
			for (int i = 0; i < sizeof(client_objects_) / sizeof(client_objects_[0]); ++i)
			{
				if (client_handler == (client_objects_ + i))
				{
					client_objects_[i].Free();
					return;
				}
			}

			int size_of_client_object = sizeof(client_objects_[0]);
			LOG4CXX_ERROR(logger, "Free()无效参数"
				LOG_VAR(client_handler)
				LOG_VAR(client_objects_)
				LOG_VAR(size_of_client_object)
				);
		}

		void CClientObjectMgr::SendHeartBeat()
		{
			NGTrace trace(logger,  "SendHeartBeat()");
			for (int i = 0; i < sizeof(client_objects_) / sizeof(client_objects_[0]);  ++i)
			{
				client_objects_[i].SendHeartBeat();
			}
		}

	} // Client
}  //  NetGateway