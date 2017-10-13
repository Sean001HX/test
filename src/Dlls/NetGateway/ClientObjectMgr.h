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
			Description:    ��ȡCClientObjectMgr�ĵ�һʵ��
			Input:
			Output:
			Return:			CClientObjectMgr��ָ��
			*************************************************/
			static CClientObjectMgr *Instance();
			
			/*************************************************
			Function:       Alloc()
			Description:   ����һ��δʹ�õĶ���
			Input:
			Output:
			Return:			CClientObject��ָ��
			*************************************************/
			CClientObject *Alloc();

			/*************************************************
			Function:       Free()
			Description:    �ͷŴ˶���
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