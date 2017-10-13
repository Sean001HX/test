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
			Description:    发送数据
			Input: 
			     CProtoHead &proto_head:报文头
				 const void *send_buf:  发送数据缓冲区字节
				 int bytes_to_send: 缓冲区字节长度
			Output:
			Return:			0 表示成功,非0 表示失败
			*************************************************/
			virtual int Write(CProtoHead &proto_head, const void *send_buf, int bytes_to_send) = 0;
	
			/*************************************************
			Function:       CloseConnection()
			Description:   关闭通信连接
			Input:
			Output:
			Return:			
			*************************************************/
			virtual int CloseConnection() = 0;
		};
	}
}



#endif  //  NET_COMM_HANDLE_H