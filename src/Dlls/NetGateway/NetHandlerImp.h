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
			Description:    ��ȡCNetHandlerImp�ĵ�һʵ��
			Input:
			Output:
			Return:			CNetHandlerImp��ָ��
			*************************************************/
			static CNetHandlerImp *Instance();

			//  ��ʼ�����˿�
			int BeginListening();
		private:
			CNetHandlerImp();

			/*************************************************
			Function:       InitNewConnect()
			Description:    ��ʼ�������Ӷ���
			Input:          
				 int connectionID ���������Ӷ����ID
			     NetCommHandle netObject ���������Ӷ����Handle
			Output:
			Return:
			*************************************************/
			virtual void InitNewConnect(int connectionID, NetCommHandle *netObject);

			/*************************************************
			Function:       CloseConnection()
			Description:    �����Ͽ�����
			Input:
			     int connectionID ���������Ӷ����ID
			     NetCommHandle netObject ���������Ӷ����Handle
			Output:
			Return:
			*************************************************/
			virtual void CloseConnection(int connectionID, NetCommHandle *netObject);

			/*************************************************
			Function:       Send()
			Description:    ��������
			Input:
			     int connectionID ���������Ӷ����ID
			     NetCommHandle netObject ���������Ӷ����Handle
				 short netCommand : �������ӵĹ�����
				 const void *buf : �������ݻ������ֽ�
				 int bufLen :   �������ֽڳ���
			Output:
			Return:  ��ʾ������
			*************************************************/
			virtual int Send(int connectionID, NetCommHandle *netObject, short netCommand, const void *buf, int bufLen);

			/*************************************************
			Function:       SetConnectionStatus()
			Description:    ��������״̬
			Input:
			     int connectionID ���������Ӷ����ID
			     NetCommHandle netObject ���������Ӷ����Handle
			     int option  ��״̬ѡ��
				 void *args  ��ѡ�������
			Output:
			Return:  ��ʾ������
			*************************************************/
			virtual int SetConnectionStatus(int connectionID, NetCommHandle *netObject, int option, void *args);

			/*************************************************
			Function:       SetLoginStatus()
			Description:    ���õ�¼״̬
			Input:
			     int connectionID ���������Ӷ����ID
			     NetCommHandle netObject ���������Ӷ����Handle
			     int userID ����¼�û���ID
			Output:
			Return:  ��ʾ������
			*************************************************/
			virtual int SetLoginStatus(int connectionID, NetCommHandle *netObject, int userID = 0);
			// ��ȡ�Է�IP
			virtual void GetPeerAddress(int connectionID, NetCommHandle *netObject, char *addressBuf, int bufLen);

		private:
			//  �����˿�
			int listen_port_;
			//  ��������־
			bool started_flag_;
		};
	}
	
}


#endif  // NET_HANDLER_IMP_H

