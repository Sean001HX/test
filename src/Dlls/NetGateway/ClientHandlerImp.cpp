#include "stdafx.h"
#include "ClientHandlerImp.h"
#include <iostream>
#include "c:/ng_tools/ng_header_for_log4cxx/ng_header_for_log4cxx.hpp"
#include "c:/ng_tools/ng_header_for_log4cxx/ng_header_for_log4cxx_log_var.hpp"

NG_LOGGER(logger, "NetGateway::Client::CClientHandlerImp::");

namespace NetGateway
{
	namespace Client
	{

		CClientHandlerImp::CClientHandlerImp() : callback_(0)
		{

		}

		void CClientHandlerImp::RegisterCallback(CClientCallback *callback)
		{
			callback_ = callback;
		}
		//////////////////////////////////////////////////
		int CClientHandlerImp::Connect(const char *host, int port)
		{
			NG_LOG4CXX_TRACE(logger, "Connect::"
				LOG_VAR(host)
				LOG_VAR(port)
				);
			std::cout << "CClientHandlerImp::Connect\n";
			return 0;
		}
		///////////////////////////////////////////////
		int CClientHandlerImp::Send(short netCommand, const void *buf, int bufLen)
		{
			NG_LOG4CXX_TRACE(logger, "Send::"
				LOG_VAR(bufLen)
				);
			std::cout << "CClientHandlerImp::Send\n";
			return 0;
		}
		/////////////////////////////////////////////////
		void CClientHandlerImp::CloseConnection()
		{
			NG_LOG4CXX_TRACE(logger, "CloseConnection::"
				);
			std::cout << "CClientHandlerImp::CloseConnection\n";
		}

	}
}

