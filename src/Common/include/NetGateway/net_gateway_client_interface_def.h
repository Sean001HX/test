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




#ifndef NET_GATEWAY_CLIENT_INTERFACE_DEF_H
#define NET_GATEWAY_CLIENT_INTERFACE_DEF_H


namespace NetGateway
{
	namespace Client
	{
		enum
		{
			NetCommandBase = 1024 /*���繦������ʼ��*/
		};

		class CClientCallback
		{
		public:

			virtual ~CClientCallback() {};
			
			/*************************************************
			Function:       OnConnected()
			Description:    �������ӻص�
			Input:
			Output:			isOk �� ���ӳɹ����
			Return:			
			*************************************************/
			virtual void OnConnected(bool isOk) {};
			
			/*************************************************
			Function:       OnSend()
			Description:    ���緢�ͻص�
			Input:
			Output:
			Return:
			*************************************************/
			virtual void OnSend() {};
			
			/*************************************************
			Function:       OnRecv()
			Description:    ������ջص�
			Input:
			Output:
				  short netCommand : ����Э�鹦����
				  char *buf �� ���յ����ݻ�����
				  int bufLen �� ���յ����ݳ���
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
			Description:    ע������ص�����
			Input:
				CClientCallback *callback �� ����ص���
			Output:
			Return:
			*************************************************/
			virtual void RegisterCallback(CClientCallback *callback) {};
			
			/*************************************************
			Function:       Connect()
			Description:    ��������
			Input:
				const char *host �� ��ַ
				int port �� �˿ں�
			Output:
			Return:			������
			*************************************************/
			virtual int Connect(const char *host, int port) = 0;
			
			/*************************************************
			Function:       Send()
			Description:    ��������
			Input:
				short netCommand : ����Э�鹦����
				char *buf �� ���յ����ݻ�����
				int bufLen �� ���յ����ݳ���
			Output:
			Return:			������: 0 = �ɹ��� ��0 = ������
			*************************************************/
			virtual int Send(short netCommand, const void *buf, int bufLen) = 0;
			
			/*************************************************
			Function:       CloseConnection()
			Description:    �����ر���������
			Input:
			Output:
			Return:			
			*************************************************/
			virtual void CloseConnection() = 0;
		};
	}
}


#endif // NET_GATEWAY_CLIENT_INTERFACE_DEF_H