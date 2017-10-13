/***************************************************************************/
/*                                                                         */
/* Copyright (c) 2016  HX Tech Co.,Ltd.             ��   ��                */
/*                      ��ϣ�Ƽ�            ��Ȩ���� 2016                   */
/*                                                                        */
/* PROPRIETARY RIGHTS of HX Tech Co.,Ltd. are involved in the  subject    */
/* matter of this material.  All manufacturing, reproduction, use, and    */
/* sales rights pertaining to this subject matter are governed by the     */
/* license agreement.  The recipient of this software implicitly accepts  */
/* the terms of the license.                                              */
/* ������ĵ������Ǻ�ϣ�Ƽ���˾���ʲ�,�κ���ʿ�Ķ���ʹ�ñ����ϱ�����          */
/* ��Ӧ��������Ȩ,�е��������κͽ�����Ӧ�ķ���Լ��.                           */
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
	Description:    ����ͨ�����ʼ������ : ��������
	Input:
	Output:
	Return:			��ʾ������
	*************************************************/
	NET_GATEWAY_API int InitServer(int listen_port = 0);

	/*************************************************
	Function:       FiniServer()
	Description:    ����ͨ�����ͷź��� : ��������
	Input:
	Output:
	Return:			��ʾ������
	*************************************************/
	NET_GATEWAY_API int FiniServer();

	/*************************************************
	Function:       InitClient()
	Description:    ����ͨ�����ʼ������ : �ͻ���
	Input:
	Output:
	Return:			��ʾ������
	*************************************************/
	NET_GATEWAY_API int InitClient();

	/*************************************************
	Function:       FiniClient()
	Description:    ����ͨ�����ͷź��� : �ͻ���
	Input:
	Output:
	Return:			��ʾ������
	*************************************************/
	NET_GATEWAY_API int FiniClient();

	namespace Server
	{
		//  ��һ������ SetNetCallback() �� GetNetHandler ()
		//  �ڶ������� Init() ��ʼ��ģ��
		//  �������ʱ�Ż���� Fini() �ͷ�ģ��
		//  ���ûص�

		/*************************************************
		Function:       SetNetCallback()
		Description:    ����sever������ͨ�Żص��ӿ���
		Input:         
		     NetGateway::Server::CNetCallback *netCallback �� �ӿ���ľ���ʵ��
		Output:
		Return:			��ʾ������
		*************************************************/
		NET_GATEWAY_API int SetNetCallback(NetGateway::Server::CNetCallback *netCallback);
		
		/*************************************************
		Function:       GetNetHandler()
		Description:    ��ȡsever������ͨ��handler
		Input:          
		Output:
		Return:			����ͨ��handler��ָ��
		*************************************************/
		NET_GATEWAY_API NetGateway::Server::CNetHandler *GetNetHandler();

		/*************************************************
		Function:       BeginListening()
		Description:    ��������ʼ����
		Input:
		Output:
		Return:			��ʾ������
		*************************************************/
		NET_GATEWAY_API int BeginListening();
	}

	namespace Client
	{
		/*************************************************
		Function:       CreateClientHandler()
		Description:    ����client������ͨ��handler
		Input:
		Output:
		Return:			����ͨ��handler��ָ��
		*************************************************/
		NET_GATEWAY_API NetGateway::Client::CClientHandler *CreateClientHandler();
		
		/*************************************************
		Function:       DestroyClientHandler()
		Description:    �ͷ�client������ͨ��handler
		Input:			
		     NetGateway::Client::CClientHandler *clientHandler ����Ҫ�ͷŵ�����ͨ��handler
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