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

#ifndef  NET_COMM_HANDLE_H
#define  NET_COMM_HANDLE_H



namespace NetGateway
{
	class CProtoHead;

	namespace Server
	{
		class CNetObject;

		class NetCommHandle
		{
		public:
			virtual ~NetCommHandle() {};

			/*************************************************
			Function:       Write()
			Description:    ��������
			Input: 
			     CProtoHead &proto_head:����ͷ
				 const void *send_buf:  �������ݻ������ֽ�
				 int bytes_to_send: �������ֽڳ���
			Output:
			Return:			0 ��ʾ�ɹ�,��0 ��ʾʧ��
			*************************************************/
			virtual int Write(CProtoHead &proto_head, const void *send_buf, int bytes_to_send) = 0;
	
			/*************************************************
			Function:       CloseConnection()
			Description:   �ر�ͨ������
			Input:
			Output:
			Return:			
			*************************************************/
			virtual int CloseConnection() = 0;
		};
	}
}



#endif  //  NET_COMM_HANDLE_H