#include "include/StockApiManager/StockApiManager.h"
#include "include/NetGateway/net_gateway.h"
#include "ApiServerMgrImp.h"

namespace AllTrade {
    namespace NPTradeCenter {

        namespace StockApiManager
        {
            int InitApiServerMgr(int listen_port)
            {
                NetGateway::InitServer(listen_port);
                ApiServerMgrImp::Instance();
                return NetGateway::Server::BeginListening();
            }

            int FiniApiServerMgr()
            {
                return NetGateway::FiniServer();
            }

            StockApiServerInterface * GetApiServerMgr()
            {
                return ApiServerMgrImp::Instance();
            }
        }
    }
}  // ApiServerMgr
