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




#ifndef NET_GATEWAY_CLIENT_INTERFACE_DEF_H
#define NET_GATEWAY_CLIENT_INTERFACE_DEF_H


namespace NetGateway
{
	namespace Client
	{
		enum
		{
			NetCommandBase = 1024 /*网络功能码起始点*/
		};

		class CClientCallback
		{
		public:

			virtual ~CClientCallback() {};
			
			/*************************************************
			Function:       OnConnected()
			Description:    网络连接回调
			Input:
			Output:			isOk ： 连接成功与否
			Return:			
			*************************************************/
			virtual void OnConnected(bool isOk) {};
			
			/*************************************************
			Function:       OnSend()
			Description:    网络发送回调
			Input:
			Output:
			Return:
			*************************************************/
			virtual void OnSend() {};
			
			/*************************************************
			Function:       OnRecv()
			Description:    网络接收回调
			Input:
			Output:
				  short netCommand : 网络协议功能码
				  char *buf ： 接收的数据缓存区
				  int bufLen ： 接收的数据长度
			Return:
			*************************************************/
			virtual void OnRecv(short netCommand, char *buf, int bufLen) {};
		};

		class CClientHandler
		{
		public:

			virtual ~CClientHandler() {};
			
			/*************************************************
			Function:       RegisterCallback()
			Description:    注册网络回调函数
			Input:
				CClientCallback *callback ： 网络回调类
			Output:
			Return:
			*************************************************/
			virtual void RegisterCallback(CClientCallback *callback) {};
			
			/*************************************************
			Function:       Connect()
			Description:    连接网络
			Input:
				const char *host ： 网址
				int port ： 端口号
			Output:
			Return:			错误码
			*************************************************/
			virtual int Connect(const char *host, int port) = 0;
			
			/*************************************************
			Function:       Send()
			Description:    发送数据
			Input:
				short netCommand : 网络协议功能码
				char *buf ： 接收的数据缓存区
				int bufLen ： 接收的数据长度
			Output:
			Return:			错误码: 0 = 成功， 非0 = 错误码
			*************************************************/
			virtual int Send(short netCommand, const void *buf, int bufLen) = 0;
			
			/*************************************************
			Function:       CloseConnection()
			Description:    主动关闭网络连接
			Input:
			Output:
			Return:			
			*************************************************/
			virtual void CloseConnection() = 0;
		};
	}
}


#endif // NET_GATEWAY_CLIENT_INTERFACE_DEF_H