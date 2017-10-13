#include "stdafx.h"
#include "ClientConnector.h"
#include <assert.h>
#include "ClientObject.h"
#include "c:/ng_tools/ng_header_for_log4cxx/ng_header_for_log4cxx.hpp"
#include "C:/ng_tools/ng_header_for_log4cxx/ng_header_for_log4cxx_log_var.hpp"

NG_LOGGER(logger, "NetGateway::Client::CClientConnector");



namespace NetGateway
{
	namespace Client
	{
		CClientConnector::CClientConnector(CClientObject *client_object /*= 0*/) : client_object_(client_object)
		{
			LOG4CXX_TRACE(logger, "CClientConnector()"
				LOG_VAR(client_object)
				);
			assert(client_object_);
		}

		CClientConnector::~CClientConnector()
		{
			LOG4CXX_TRACE(logger, "~CClientConnector()"
				LOG_VAR(client_object_)
				);
		}

		CClientTcpService * CClientConnector::make_handler(void)
		{
			NGTrace trace(logger,  "make_handler()");

			CClientTcpService *service = ACE_Asynch_Connector<CClientTcpService>::make_handler();
			if (!service)
			{
				LOG4CXX_FATAL(logger, "make_handler()"
					LOG_VAR(this)
					);
				return 0;
			}

			service->Connect(client_object_->peer_addr_, 0);
			service->SetClientObject(client_object_);
			service->SetConnectorInfo(this);

			return service;
		}

		void CClientConnector::handle_connect(const ACE_Asynch_Connect::Result &result)
		{
			NGTrace trace(logger,  "handle_connect()");
			bool success = result.success();
			ACE_Asynch_Connector<CClientTcpService>::handle_connect(result);

			if (!success)
			{
				if (client_object_)
				{
					client_object_->OnConnected(false, 0, this);
				}
				else
				{
					LOG4CXX_ERROR(logger, "handle_connect()"
						LOG_VAR(client_object_)
						);
				}
			}

			delete this;
		}

		int CClientConnector::Connect(const char *host_ip, int port)
		{
			NGTrace trace(logger,  "Connect()");

			int ret = 0;

			ACE_INET_Addr target_addr(port, host_ip);
			ret = this->open();
			if (-1 == ret)
				return ret;

			ret = this->connect(target_addr);

			return ret;
		}

	} // Client
}  //  NetGateway
