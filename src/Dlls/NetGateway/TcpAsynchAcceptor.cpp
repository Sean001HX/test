#include "stdafx.h"
#include "TcpAsynchAcceptor.h"


namespace NetGateway
{
	namespace Server
	{


		CTcpAsynchAcceptor::CTcpAsynchAcceptor()
		{

		}

		CTcpAsynchAcceptor::~CTcpAsynchAcceptor()
		{

		}

		void CTcpAsynchAcceptor::handle_accept(const ACE_Asynch_Accept::Result &result)
		{
			ACE_Asynch_Acceptor<CServerTcpService>::handle_accept(result);
		}

		int CTcpAsynchAcceptor::validate_connection(const ACE_Asynch_Accept::Result& result, const ACE_INET_Addr &remote, const ACE_INET_Addr& local)
		{
			return ACE_Asynch_Acceptor<CServerTcpService>::validate_connection(result, remote, local);
		}

		CTcpAsynchAcceptor * CTcpAsynchAcceptor::Instance()
		{
			static CTcpAsynchAcceptor _inst;
			return &_inst;
		}

	}  //  Server
}  //  NetGateway