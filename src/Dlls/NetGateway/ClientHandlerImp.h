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
/* 本软件文档资料是恒希科技公司的资产,任何人士阅读和使用本资料必须获得         */
/* 相应的书面授权,承担保密责任和接受相应的法律约束.                           */
/*                                                                        */
/***************************************************************************/


#ifndef CLIENT_HANDLER_IMP_H
#define CLIENT_HANDLER_IMP_H

#include "include/NetGateway/net_gateway_client_interface_def.h"

namespace NetGateway
{
	namespace Client
	{
		class CClientHandlerImp : public CClientHandler
		{
		public:
			CClientHandlerImp();

			/*************************************************
			Function:       RegisterCallback()
			Description:    注册Client端网络通讯的回调类
			Input:          CClientCallback *callback : 回调接口类的具体实现
			Output:
			Return:
			*************************************************/
			virtual void RegisterCallback(CClientCallback *callback);
			
			/*************************************************
			Function:       Connect()
			Description:    网络连接
			Input:         
			     const char *host ： 网址（主机IP）
			     int port ：  端口号
			Output:
			Return:			返回错误码
			*************************************************/
			virtual int Connect(const char *host, int port);
			
			/*************************************************
			Function:       Send()
			Description:    发送数据
			Input:
				short netCommand : 网络协议功能码
	             const void *buf ：发送数据缓冲区字节
				 int bufLen ： 缓冲区字节长度
			Output:
			Return:          返回错误码
			*************************************************/
			virtual int Send(short netCommand, const void *buf, int bufLen);
			
			/*************************************************
			Function:       CloseConnection()
			Description:    主动关闭网络连接
			Input:
			Output:
			Return:
			*************************************************/
			virtual void CloseConnection();

		private:
			//回调接口类的具体实现
			CClientCallback *callback_;
		};
	}
}



#endif  // CLIENT_HANDLER_IMP_H