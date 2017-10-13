#pragma once
#ifndef CLIENT_CONNECTOR_H
#define CLIENT_CONNECTOR_H

#include "ace/Asynch_Connector.h"
#include "ClientTcpService.h"

namespace NetGateway
{
	namespace Client
	{
		class CClientObject;

		class CClientConnector : public ACE_Asynch_Connector<CClientTcpService>
		{
		public:
			CClientConnector(CClientObject *client_object = 0);
			~CClientConnector();

			// This method will be called when an asynchronous connect completes.
			virtual void handle_connect(const ACE_Asynch_Connect::Result &result);

			virtual CClientTcpService *make_handler(void);

			//  连接服务器， 方法客户端使用
			int Connect(const char *host_ip, int port);
		private:
			CClientObject *client_object_;
		};
	}
}

#endif  //  CLIENT_CONNECTOR_H