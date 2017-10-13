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

#ifndef NET_GATEWAY_H
#define NET_GATEWAY_H

#ifdef NET_GATEWAY_STATIC_LIB
#   define NET_GATEWAY_API
#else

#ifdef NET_GATEWAY_EXPORTS
#define NET_GATEWAY_API __declspec(dllexport)
#else
#define NET_GATEWAY_API __declspec(dllimport)
#endif

#endif  // NET_GATEWAY_STATIC_LIB

#include "net_gateway_interface_def.h"
#include "net_gateway_client_interface_def.h"

#ifdef __cplusplus
extern "C" {
#endif

namespace NetGateway
{
	/*************************************************
	Function:       InitServer()
	Description:    网络通信类初始化函数 : 服务器端
	Input:
	Output:
	Return:			表示错误码
	*************************************************/
	NET_GATEWAY_API int InitServer(int listen_port = 0);

	/*************************************************
	Function:       FiniServer()
	Description:    网络通信类释放函数 : 服务器端
	Input:
	Output:
	Return:			表示错误码
	*************************************************/
	NET_GATEWAY_API int FiniServer();

	/*************************************************
	Function:       InitClient()
	Description:    网络通信类初始化函数 : 客户端
	Input:
	Output:
	Return:			表示错误码
	*************************************************/
	NET_GATEWAY_API int InitClient();

	/*************************************************
	Function:       FiniClient()
	Description:    网络通信类释放函数 : 客户端
	Input:
	Output:
	Return:			表示错误码
	*************************************************/
	NET_GATEWAY_API int FiniClient();

	namespace Server
	{
		//  第一步调用 SetNetCallback() 和 GetNetHandler ()
		//  第二步调用 Init() 初始化模块
		//  程序结束时才会调用 Fini() 释放模块
		//  设置回调

		/*************************************************
		Function:       SetNetCallback()
		Description:    设置sever端网络通信回调接口类
		Input:         
		     NetGateway::Server::CNetCallback *netCallback ： 接口类的具体实现
		Output:
		Return:			表示错误码
		*************************************************/
		NET_GATEWAY_API int SetNetCallback(NetGateway::Server::CNetCallback *netCallback);
		
		/*************************************************
		Function:       GetNetHandler()
		Description:    获取sever端网络通信handler
		Input:          
		Output:
		Return:			网络通信handler的指针
		*************************************************/
		NET_GATEWAY_API NetGateway::Server::CNetHandler *GetNetHandler();

		/*************************************************
		Function:       BeginListening()
		Description:    服务器开始侦听
		Input:
		Output:
		Return:			表示错误码
		*************************************************/
		NET_GATEWAY_API int BeginListening();
	}

	namespace Client
	{
		/*************************************************
		Function:       CreateClientHandler()
		Description:    创建client端网络通信handler
		Input:
		Output:
		Return:			网络通信handler的指针
		*************************************************/
		NET_GATEWAY_API NetGateway::Client::CClientHandler *CreateClientHandler();
		
		/*************************************************
		Function:       DestroyClientHandler()
		Description:    释放client端网络通信handler
		Input:			
		     NetGateway::Client::CClientHandler *clientHandler ：需要释放的网络通信handler
		Output:
		Return:			
		*************************************************/
		NET_GATEWAY_API void DestroyClientHandler(NetGateway::Client::CClientHandler *clientHandler);
	}
}
		
#ifdef __cplusplus
}
#endif


#endif // NET_GATEWAY_H