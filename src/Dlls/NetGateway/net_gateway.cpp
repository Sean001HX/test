/*************************************************
Copyright (C), 2016, HX Tech Co., Ltd.
Description: 定义网络通信类的外部导出函数
Author:	Arven				Date:2016-04-20
Others:
Function List:
1、int SetNetCallback(NetGateway::Server::CNetCallback *netCallback);
2、NetGateway::Server::CNetHandler *GetNetHandler();
3、NetGateway::Client::CClientHandler *CreateClientHandler();
4、void DestroyClientHandler(NetGateway::Client::CClientHandler *clientHandler);

*************************************************/

#include "stdafx.h"
#include "include/NetGateway/net_gateway.h"
#include "ace/Init_ACE.h"
#include "ace/Recursive_Thread_Mutex.h"
#include "GlobaData.h"
#include "NetHandlerImp.h"
#include "ClientHandlerImp.h"
#include "NetListenThread.h"
#include "NetObjectMgr.h"
#include "ClientObjectMgr.h"
#include "ClientThread.h"
#include "NetHeartBeatThread.h"
#include "ClientHeartBeatThread.h"
#include "c:/ng_tools/ng_header_for_log4cxx/ng_header_for_log4cxx.hpp"
#include "C:/ng_tools/ng_header_for_log4cxx/ng_header_for_log4cxx_log_var.hpp"

NG_LOGGER(logger, "NetGateway::");

void *g_client_CNetHeartBeatThread = 0;
void *g_client_CClientThread = 0;

namespace NetGateway
{
	////////////////////////////////////////////////////////////////////////////
	static int count = 0;
	static ACE_Recursive_Thread_Mutex count_mutex;
	namespace Server
	{
		int gListport = 0;
	}
	//////////////////////////////////////////////////////////////////////////////
	int InitServer(int listen_port)
	{
		LOG4CXX_INFO(logger, "InitServer()"LOG_VAR(listen_port));
		Server::gListport = listen_port;
		count_mutex.acquire();
		if (count == 0)
		{
			ACE::init();
		}
		count++;
		count_mutex.release();
		return 0;
	}
	///////////////////////////////////////////////////////////////////////////////
	int FiniServer()
	{
		LOG4CXX_INFO(logger, "FiniServer()");
		count_mutex.acquire();
		if (count == 1)
		{
			Server::CNetHeartBeatThread::Insatnce()->Stop();
			Server::CNetListenThread::Instance()->Stop();
			ACE::fini();
		}
		if (count >= 1)
		{
			count--;
		}
		count_mutex.release();
		return 0;
	}
	////////////////////////////////////////////////////////////////////////////////////
	int InitClient()

	{
		LOG4CXX_INFO(logger, "InitClient()");
		count_mutex.acquire();
		if (count == 0)
		{
			ACE::init();
			Client::CClientObjectMgr::Instance();
		}
		count++;
		count_mutex.release();
		return 0;
	}
	////////////////////////////////////////////////////////////////////////////////////
	int FiniClient()
	{
		LOG4CXX_INFO(logger, "FiniClient()");
		count_mutex.acquire();
		if (count == 1)
		{
			if (g_client_CNetHeartBeatThread)
			{
				Client::CClientHeartBeatThread::Instance()->Stop();
				g_client_CNetHeartBeatThread = 0;
			}
				
			if (g_client_CClientThread)
			{
				Client::CClientThread::Instance()->Stop();
				g_client_CClientThread = 0;
			}
				
			ACE::fini();
		}
		if (count >= 1)
		{
			count--;
		}
		count_mutex.release();
		return 0;
	}


	////////////////////////////////////////////////////////
	namespace Server
	{
		
		////////////////////////////////////////////////////////////////////////////////////
		int SetNetCallback(CNetCallback *netCallback)
		{
			CGlobaData::Instance()->SetNetCallback(netCallback);
			return 0;
		}
		/////////////////////////////////////////////////////////////////////////////////////
		CNetHandler * GetNetHandler()
		{
			return CNetHandlerImp::Instance();
		}

		int BeginListening()
		{
			return CNetHandlerImp::Instance()->BeginListening();
		}

	}

	namespace Client
	{
		
		CClientHandler * CreateClientHandler()
		{
			NG_LOG4CXX_TRACE(logger, "Client::CreateClientHandler()");
			// for test
			return CClientObjectMgr::Instance()->Alloc();
		}

		void DestroyClientHandler(CClientHandler *clientHandler)
		{
			NG_LOG4CXX_TRACE(logger, "Client::DestroyClientHandler()"
				LOG_VAR(clientHandler)
				);
			CClientObjectMgr::Instance()->Free(clientHandler);
		}

	}


}