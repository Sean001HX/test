#pragma once

#ifndef NET_OBJECT_H
#define NET_OBJECT_H

#include "net_gateway_macros.h"
#include "ace/Recursive_Thread_Mutex.h"
#include <time.h>

namespace NetGateway
{
	namespace Server
	{

		class NetCommHandle;

		class CNetObject
		{
			friend class CNetObjectMgr;
		public:
			CNetObject();
			~CNetObject();
			/*************************************************
			Function:       OnNewConnection()
			Description:    新连接回调
			Input: 
			     NetCommHandle *pHandler：通信访问的句柄
				 const char *peer_addrs：对端ip地址 "xxx.xxx.xxx.xxx"
			Output:
			Return:		true 分配成功,false:分配成功
			*************************************************/
			virtual bool OnNewConnection(NetCommHandle *pHandler, const char *peer_addrs);

			/*************************************************
			Function:       OnWrite()
			Description:    返回发送回调
			Input:
			    NetCommHandle *handler：通信访问的句柄
				int bytes_to_send：要发送的字节数
				int bytes_sent ： 实际发送字节数
			Output:
			Return:		
			*************************************************/
			virtual void OnWrite(NetCommHandle *handler, int bytes_to_send, int bytes_sent);

			/*************************************************
			Function:       OnRead()
			Description:    收到数据回调
			Input:
			     NetCommHandle *handler：通信访问的句柄
			     const char *read_buf：已收到数据缓冲区
			     int bytes_received ： 已收到的字节数
			Output:
			Return:
			*************************************************/
			virtual void OnRead(NetCommHandle *handler, const char *read_buf, int bytes_received);

			/*************************************************
			Function:       OnDisconnected()
			Description:    掉线回调
			Input:
			     NetCommHandle *handler：通信访问的句柄
			Output:
			Return:
			*************************************************/
			virtual void OnDisconnected(NetCommHandle *handler);

			/*************************************************
			Function:       InitCommSeed()
			Description:    初始化通信种子
			Input:
			     NetCommHandle *handler：通信访问的句柄
			Output:
			Return:
			*************************************************/
			virtual void InitCommSeed(NetCommHandle *handler);

		public:
			/*************************************************
			Function:       Send()
			Description:    发送数据
			Input:
			    NetCommHandle *handler ：   网络连接对象的Handle
			    unsigned short netCommand : 网络连接的功能码
			    const void *buf :           发送数据缓冲区字节
			    int bufLen :                缓冲区字节长度
			Output:
			Return:  
			*************************************************/
			int Send(NetCommHandle *handler, unsigned short netCommand, const void *buf, int bufLen);

			/*************************************************
			Function:       CloseConnection()
			Description:    关闭连接
			Input:
			     NetCommHandle *handler：通信访问的句柄
			Output:
			Return:
			*************************************************/
			int CloseConnection(NetCommHandle *handler);

			/*************************************************
			Function:       Handler()
			Description:    
			Input:
			Output:
			Return:
			*************************************************/
			NetCommHandle *Handler() const;

			/*************************************************
			Function:       Reset()
			Description:    重置此对象
			Input:
			Output:
			Return:
			*************************************************/
			void Reset();

		private:
			/*************************************************
			Function:       __SendImp()
			Description:    打包发送
			Input:   
				unsigned short netCommand : 网络协议功能码
				const void *buf ：发送数据缓冲区字节
				int bufLen ： 缓冲区字节长度
			Output:
			Return:
			*************************************************/
			int __SendImp(unsigned short netCommand, const void *buf, int bufLen);

			/*************************************************
			Function:       DispatchPacket()
			Description:    分发数据包
			Input:
				unsigned short netCommand : 网络协议功能码
				const void *buf ：发送数据缓冲区字节
				int bufLen ： 缓冲区字节长度
			Output:
			Return:
			*************************************************/
			void DispatchPacket(unsigned short netCommand, void *buf, int bufLen);

			void CheckHeartBeat(unsigned nowTime);

			void HandleHeartBeat();
		private:
			//  对端地址
			char peer_addr_[NET_ADDR_BUF_LEN];
			
			//  CNetObject读写操作访问锁
			ACE_Recursive_Thread_Mutex  mutex_net_object_;
			//  与此对象绑定的通信访问够句柄
			NetCommHandle *net_comm_handle_;
			//  最后一次心跳时间
			time_t last_heart_beat_time_;
			//  生成种子时间
			time_t seed_generate_time_;
			//  通信种子
			unsigned short seed_;
			unsigned short seed_new_;
			//  接收缓冲区
			char *recv_buf_;
			int  unparsed_data_len_;
		public:
			//  该对象的编号
			int index_;
		};
	}  // Server
}  //  NetGateway


#endif // NET_OBJECT_H



