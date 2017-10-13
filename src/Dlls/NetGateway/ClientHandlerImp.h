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
/* ������ĵ������Ǻ�ϣ�Ƽ���˾���ʲ�,�κ���ʿ�Ķ���ʹ�ñ����ϱ�����         */
/* ��Ӧ��������Ȩ,�е��������κͽ�����Ӧ�ķ���Լ��.                           */
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
			Description:    ע��Client������ͨѶ�Ļص���
			Input:          CClientCallback *callback : �ص��ӿ���ľ���ʵ��
			Output:
			Return:
			*************************************************/
			virtual void RegisterCallback(CClientCallback *callback);
			
			/*************************************************
			Function:       Connect()
			Description:    ��������
			Input:         
			     const char *host �� ��ַ������IP��
			     int port ��  �˿ں�
			Output:
			Return:			���ش�����
			*************************************************/
			virtual int Connect(const char *host, int port);
			
			/*************************************************
			Function:       Send()
			Description:    ��������
			Input:
				short netCommand : ����Э�鹦����
	             const void *buf ���������ݻ������ֽ�
				 int bufLen �� �������ֽڳ���
			Output:
			Return:          ���ش�����
			*************************************************/
			virtual int Send(short netCommand, const void *buf, int bufLen);
			
			/*************************************************
			Function:       CloseConnection()
			Description:    �����ر���������
			Input:
			Output:
			Return:
			*************************************************/
			virtual void CloseConnection();

		private:
			//�ص��ӿ���ľ���ʵ��
			CClientCallback *callback_;
		};
	}
}



#endif  // CLIENT_HANDLER_IMP_H