#pragma once

//  网络连接对象管理
#ifndef NET_OBJECT_MGR_H
#define NET_OBJECT_MGR_H

#include "net_gateway_macros.h"
#include "NetObject.h"
#include "NetCommHandle.h"

//  编译之前修改 MAX_NET_OBJECT_LIMIT 的值 可改变网络模块允许连接数的上限

namespace NetGateway
{
	namespace Server
	{
		class CNetObjectMgr
		{
		public:
			/*************************************************
			Function:       Instance()
			Description:    获取CNetObjectMgr的单一实例
			Input:
			Output:
			Return:			CNetObjectMgr的指针
			*************************************************/
			static CNetObjectMgr *Instance();

			/*************************************************
			Function:       AllocNetObject()
			Description:   分配一个可用的网络对象
			Input:
			    NetCommHandle *net_comm_handle： 通信访问的句柄
			    const char *peer_addrs：         对端ip地址 "xxx.xxx.xxx.xxx"
			Output:
			Return:		失败返回 NULL， 成功返回实例指针
			*************************************************/
			CNetObject *AllocNetObject(NetCommHandle *net_comm_handle, const char *peer_addr);

			/*************************************************
			Function:       CloseConnection()
			Description:    关闭连接
			Input:
			     int connectionID：        网络连接对象的ID
			     NetCommHandle *netObject：网络连接对象的Handle
			Output:
			Return:
			*************************************************/
			void CloseConnection(int connectionID, NetCommHandle *netObject);
			
			/*************************************************
			Function:       Send()
			Description:    发送数据
			Input:
			    int connectionID：          网络连接对象的ID
			    NetCommHandle *netObject ： 网络连接对象的Handle
			    short netCommand :          网络连接的功能码
			    const void *buf :           发送数据缓冲区字节
			    int bufLen :                缓冲区字节长度
			Output:
			Return:
			*************************************************/
			int Send(int connectionID, NetCommHandle *netObject, short netCommand, const void *buf, int bufLen);

			// 获取对方IP
			virtual void GetPeerAddress(int connectionID, NetCommHandle *netObject, char *addressBuf, int bufLen);

			void CheckHeartBeat(unsigned nowTime);
		private:
			CNetObjectMgr();
			//  网络对象静态缓存
			CNetObject net_objects_[MAX_NET_OBJECT_LIMIT];

		private:
			long long Hash(NetCommHandle *net_comm_handle);
		};
	}
}



#endif  // NET_OBJECT_MGR_H

