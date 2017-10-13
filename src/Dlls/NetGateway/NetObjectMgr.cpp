#include "stdafx.h"
#include "NetObjectMgr.h"
#include "include/NetGateway/net_gateway_errors.h"
#include "c:/ng_tools/ng_header_for_log4cxx/ng_header_for_log4cxx.hpp"
#include "C:/ng_tools/ng_header_for_log4cxx/ng_header_for_log4cxx_log_var.hpp"

NG_LOGGER(logger, "NetGateway::Server::CNetObjectMgr")

namespace NetGateway
{
	namespace Server
	{

		CNetObjectMgr * CNetObjectMgr::Instance()
		{
			static CNetObjectMgr _inst;
			return &_inst;
		}

		CNetObjectMgr::CNetObjectMgr()
		{
			LOG4CXX_TRACE(logger, "CNetObjectMgr()");
			for (int i = 0; i < sizeof(net_objects_) / sizeof(net_objects_[0]); ++i)
			{
				net_objects_[i].Reset();
				net_objects_[i].index_ = i;
			}
		}

		CNetObject * CNetObjectMgr::AllocNetObject(NetCommHandle *net_comm_handle, const char *peer_addr)
		{
			if (!net_comm_handle)
				return 0;

			int first_pos = (int)Hash(net_comm_handle);
			int i = 0;

			for (; i < CONNECT_TRY_TIMES; ++i) 
			{
				if (!(net_objects_[(first_pos + i) % MAX_NET_OBJECT_LIMIT].Handler()) && net_objects_[(first_pos + i) % MAX_NET_OBJECT_LIMIT].OnNewConnection(net_comm_handle, peer_addr))
					break;
			}

			if (i >= CONNECT_TRY_TIMES)
			{
				LOG4CXX_ERROR(logger, "服务器连接数超限, 客户连接被拒绝"
					LOG_VAR(net_comm_handle)
					LOG_VAR(peer_addr)
					);
				return 0;
			}

			return &net_objects_[(first_pos + i) % MAX_NET_OBJECT_LIMIT];
		}

		long long CNetObjectMgr::Hash(NetCommHandle *net_comm_handle)
		{
			long long hash = (long long)net_comm_handle;
			hash >>= 8;

			hash %= MAX_NET_OBJECT_LIMIT;
			if (hash < 0)
			{
				hash += MAX_NET_OBJECT_LIMIT;
			}

			return hash;
		}

		void CNetObjectMgr::CloseConnection(int connectionID, NetCommHandle *netObject)
		{
			LOG4CXX_TRACE(logger, "CloseConnection"
				LOG_VAR(connectionID)
				LOG_VAR(netObject)
				);

			if (connectionID >= 0 && connectionID < MAX_NET_OBJECT_LIMIT)
			{
				net_objects_[connectionID].CloseConnection(netObject);
			}
			else
			{
				LOG4CXX_ERROR(logger, "CloseConnection参数溢出"
					LOG_VAR(connectionID)
					LOG_VAR(netObject)
					);
			}
		}

		int CNetObjectMgr::Send(int connectionID, NetCommHandle *netObject, short netCommand, const void *buf, int bufLen)
		{
// 			LOG4CXX_TRACE(logger, "Send()"
// 				LOG_VAR(connectionID)
// 				LOG_VAR(netObject)
// 				LOG_VAR(netCommand)
// 				LOG_VAR(bufLen)
// 				);
			if (connectionID >= 0 && connectionID < MAX_NET_OBJECT_LIMIT)
			{
				return net_objects_[connectionID].Send(netObject, netCommand, buf, bufLen);
			}
			else
			{
				LOG4CXX_ERROR(logger, "Send()参数溢出"
					LOG_VAR(connectionID)
					LOG_VAR(netObject)
					);

				return InvalidTcpSendParameter;
			}
		}

		void CNetObjectMgr::GetPeerAddress(int connectionID, NetCommHandle *netObject, char *addressBuf, int bufLen)
		{
			if (!addressBuf || bufLen <= 0)
				return;

			if (connectionID < 0 || connectionID >= sizeof(net_objects_) / sizeof(net_objects_[0]))
			{
				addressBuf[0] = 0;
				return;
			}
				
			if (net_objects_[connectionID].net_comm_handle_ != netObject)
			{
				addressBuf[0] = 0;
				return;
			}

			_snprintf_s(addressBuf, bufLen, bufLen - 1, "%s", net_objects_[connectionID].peer_addr_);
		}

		void CNetObjectMgr::CheckHeartBeat(unsigned nowTime)
		{
			for (int  i = 0; i < sizeof(net_objects_) / sizeof(net_objects_[0]); ++i)
			{
				if(net_objects_[i].seed_ && net_objects_[i].net_comm_handle_)
					net_objects_[i].CheckHeartBeat(nowTime);
			}
		}

	}
}