#pragma once

#ifndef CLIENT_OBJECT_MGR_H
#define CLIENT_OBJECT_MGR_H

#include "ClientObject.h"
#include "net_gateway_macros.h"

namespace NetGateway
{
	namespace Client
	{
		class CClientObjectMgr
		{
		private:
			CClientObjectMgr();

		public:
			~CClientObjectMgr();

			/*************************************************
			Function:       Instance()
			Description:    获取CClientObjectMgr的单一实例
			Input:
			Output:
			Return:			CClientObjectMgr的指针
			*************************************************/
			static CClientObjectMgr *Instance();
			
			/*************************************************
			Function:       Alloc()
			Description:   分配一个未使用的对象
			Input:
			Output:
			Return:			CClientObject的指针
			*************************************************/
			CClientObject *Alloc();

			/*************************************************
			Function:       Free()
			Description:    释放此对象
			Input:
			Output:
			Return:
			*************************************************/
			void Free(CClientHandler *client_handler);

			void SendHeartBeat();
		private:
			CClientObject client_objects_[NET_CLIENT_OBJECTS_LIMIT];
		};
	}
}

#endif // CLIENT_OBJECT_MGR_H