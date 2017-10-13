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


//   ����ģ��ȫ�����ݻ���


#ifndef GLOBAL_DATA_H
#define GLOBAL_DATA_H

#include "include/NetGateway/net_gateway_interface_def.h"

namespace NetGateway
{
	namespace Server
	{
		class CGlobaData
		{
		public:
			/*************************************************
			Function:       Instance()
			Description:    ��ȡCGlobaData�ĵ�һʵ��
			Input:
			Output:
			Return:			CGlobaData��ָ��
			*************************************************/
			static CGlobaData *Instance();

			/*************************************************
			Function:       SetNetCallback()
			Description:    ��������ص�
			Input:          CNetCallback *netCallback :�ص��ӿ���ľ���ʵ��
			Output:
			Return:			
			*************************************************/
			void SetNetCallback(CNetCallback *netCallback);

			/*************************************************
			Function:       Callback()
			Description:    ��ȡ����ص�
			Input:          
			Output:
			Return:			�ص��ӿ���ľ���ʵ�ֵ�ָ��
			*************************************************/
			CNetCallback *Callback();

		private:
			CGlobaData();

			//�ص��ӿ���ľ���ʵ��
			CNetCallback *netCallback_;
		};
	}
	
}


#endif  // GLOBAL_DATA_H
