//  �첽������

#pragma once

#ifndef TCP_ASYNCH_ACCEPTOR_H
#define TCP_ASYNCH_ACCEPTOR_H

#include <ace/Asynch_Acceptor.h>
#include "ServerTcpService.h"

namespace NetGateway
{
	namespace Server
	{
		class CTcpAsynchAcceptor : public ACE_Asynch_Acceptor<CServerTcpService>
		{
		private:
			CTcpAsynchAcceptor();
		public:
			static CTcpAsynchAcceptor *Instance();

			~CTcpAsynchAcceptor();

		private:
			// This method will be called when an asynchronous accept completes.
			virtual void handle_accept(const ACE_Asynch_Accept::Result &result);
			//  �˴�����ӹ���,
			virtual int validate_connection(const ACE_Asynch_Accept::Result& result,
				const ACE_INET_Addr &remote,
				const ACE_INET_Addr& local);
		};
	}
}

#endif  //  TCP_ASYNCH_ACCEPTOR_H