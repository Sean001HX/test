/***************************************************************************/
/*                                                                         */
/* Copyright (c) 2016  HX Tech Co.,Ltd.             　   　                */
/*                      恒希科技            版权所有 2016                   */
/*                                                                        */
/* PROPRIETARY RIGHTS of HX Tech Co.,Ltd. are involved in the  subject    */
/* matter of this material.  All manufacturing, reproduction, use, and    */
/* sales rights pertaining to this subject matter are governed by the     */
/* license agreement.  The recipient of this software implicitly accepts  */
/* the terms of the license.                                              */
/* 本软件文档资料是恒希科技公司的资产,任何人士阅读和使用本资料必须获得          */
/* 相应的书面授权,承担保密责任和接受相应的法律约束.                           */
/*                                                                        */
/***************************************************************************/


#ifndef NET_HANDLER_IMP_H
#define NET_HANDLER_IMP_H

#include "include/NetGateway/net_gateway_interface_def.h"

namespace NetGateway
{
	namespace Server
	{
		class CNetHandlerImp : public CNetHandler
		{
		public:
			/*************************************************
			Function:       Instance()
			Description:    获取CNetHandlerImp的单一实例
			Input:
			Output:
			Return:			CNetHandlerImp的指针
			*************************************************/
			static CNetHandlerImp *Instance();

			//  开始侦听端口
			int BeginListening();
		private:
			CNetHandlerImp();

			/*************************************************
			Function:       InitNewConnect()
			Description:    初始化新连接对象
			Input:          
				 int connectionID ：网络连接对象的ID
			     NetCommHandle netObject ：网络连接对象的Handle
			Output:
			Return:
			*************************************************/
			virtual void InitNewConnect(int connectionID, NetCommHandle *netObject);

			/*************************************************
			Function:       CloseConnection()
			Description:    主动断开连接
			Input:
			     int connectionID ：网络连接对象的ID
			     NetCommHandle netObject ：网络连接对象的Handle
			Output:
			Return:
			*************************************************/
			virtual void CloseConnection(int connectionID, NetCommHandle *netObject);

			/*************************************************
			Function:       Send()
			Description:    发送数据
			Input:
			     int connectionID ：网络连接对象的ID
			     NetCommHandle netObject ：网络连接对象的Handle
				 short netCommand : 网络连接的功能码
				 const void *buf : 发送数据缓冲区字节
				 int bufLen :   缓冲区字节长度
			Output:
			Return:  表示错误码
			*************************************************/
			virtual int Send(int connectionID, NetCommHandle *netObject, short netCommand, const void *buf, int bufLen);

			/*************************************************
			Function:       SetConnectionStatus()
			Description:    设置连接状态
			Input:
			     int connectionID ：网络连接对象的ID
			     NetCommHandle netObject ：网络连接对象的Handle
			     int option  ：状态选项
				 void *args  ：选项附带参数
			Output:
			Return:  表示错误码
			*************************************************/
			virtual int SetConnectionStatus(int connectionID, NetCommHandle *netObject, int option, void *args);

			/*************************************************
			Function:       SetLoginStatus()
			Description:    设置登录状态
			Input:
			     int connectionID ：网络连接对象的ID
			     NetCommHandle netObject ：网络连接对象的Handle
			     int userID ：登录用户的ID
			Output:
			Return:  表示错误码
			*************************************************/
			virtual int SetLoginStatus(int connectionID, NetCommHandle *netObject, int userID = 0);
			// 获取对方IP
			virtual void GetPeerAddress(int connectionID, NetCommHandle *netObject, char *addressBuf, int bufLen);

		private:
			//  侦听端口
			int listen_port_;
			//  已启动标志
			bool started_flag_;
		};
	}
	
}


#endif  // NET_HANDLER_IMP_H

