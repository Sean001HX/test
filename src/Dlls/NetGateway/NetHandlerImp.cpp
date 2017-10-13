#include "stdafx.h"
#include "NetHandlerImp.h"
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include "windows.h"
#include "NetListenThread.h"
#include "assert.h"
#include "GlobaData.h"
#include "NetObjectMgr.h"
#include "NetHeartBeatThread.h"
#include "c:/ng_tools/ng_header_for_log4cxx/ng_header_for_log4cxx.hpp"
#include "c:/ng_tools/ng_header_for_log4cxx/ng_header_for_log4cxx_log_var.hpp"

NG_LOGGER(logger, "NetGateway::Server::NetHandlerImp");

namespace NetGateway
{
	namespace Server
	{
		extern int gListport;
		//////////////////////////////////////////////////////////
		CNetHandlerImp * CNetHandlerImp::Instance()
		{

			static CNetHandlerImp _inst;
			return &_inst;
		}
		/////////////////////////////////////////////////////////
		CNetHandlerImp::CNetHandlerImp() : started_flag_(false)
		{
			srand(time(0));

			CNetObjectMgr::Instance();

			// ÍøÂçÄ£¿é³õÊ¼»¯
		
			listen_port_ = gListport;
			
		}
		///////////////////////////////////////////////////////////////
		int CNetHandlerImp::BeginListening()
		{
			if (started_flag_)
				return 0;

			started_flag_ = true;

			int threads = GetPrivateProfileIntA("SERVER", "THREADS", 1, "./net_gateway.hxc");
			CNetListenThread::Instance()->Init(threads, gListport);
			if (CNetListenThread::Instance()->open() < 0)
			{
				LOG4CXX_FATAL(logger, "ÍøÂçÄ£¿é³õÊ¼»¯Ê§°Ü"
					LOG_VAR(listen_port_)
					LOG_VAR(threads)
					);

				system("pause");
				assert(false);

				return -1;
			}
			if (CNetHeartBeatThread::Insatnce()->open() < 0)
			{
				LOG4CXX_FATAL(logger, "ÍøÂçÄ£¿é³õÊ¼»¯Ê§°Ü"
					LOG_VAR(listen_port_)
					LOG_VAR(threads)
					);

				system("pause");
				assert(false);

				return -1;
			}

			return 0;
		}
		///////////////////////////////////////////////////////////////
		void CNetHandlerImp::InitNewConnect(int connectionID, NetCommHandle *netObject)
		{
			NG_LOG4CXX_TRACE(logger, "InitNewConnect");
		}

		void CNetHandlerImp::CloseConnection(int connectionID, NetCommHandle *netObject)
		{
			NG_LOG4CXX_TRACE(logger, "CloseConnection");
			CNetObjectMgr::Instance()->CloseConnection(connectionID, netObject);
		}

		int CNetHandlerImp::Send(int connectionID, NetCommHandle *netObject, short netCommand, const void *buf, int bufLen)
		{
// 			NG_LOG4CXX_TRACE(logger, "Send"
// 				LOG_VAR(connectionID)
// 				LOG_VAR(netObject)
// 				LOG_VAR(netCommand));


			return CNetObjectMgr::Instance()->Send(connectionID, netObject, netCommand, buf, bufLen);
			return 0;
		}

		int CNetHandlerImp::SetConnectionStatus(int connectionID, NetCommHandle *netObject, int option, void *args)
		{
			NG_LOG4CXX_TRACE(logger, "SetConnectionStatus");
			return 0;
		}

		int CNetHandlerImp::SetLoginStatus(int connectionID, NetCommHandle *netObject, int userID /*= 0*/)
		{
			NG_LOG4CXX_TRACE(logger, "SetLoginStatus");
			return 0;
		}

		void CNetHandlerImp::GetPeerAddress(int connectionID, NetCommHandle *netObject, char *addressBuf, int bufLen)
		{
			return CNetObjectMgr::Instance()->GetPeerAddress(connectionID, netObject, addressBuf, bufLen);
		}

	}
	
}