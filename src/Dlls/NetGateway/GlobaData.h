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


//   网络模块全局数据缓存


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
			Description:    获取CGlobaData的单一实例
			Input:
			Output:
			Return:			CGlobaData的指针
			*************************************************/
			static CGlobaData *Instance();

			/*************************************************
			Function:       SetNetCallback()
			Description:    设置网络回调
			Input:          CNetCallback *netCallback :回调接口类的具体实现
			Output:
			Return:			
			*************************************************/
			void SetNetCallback(CNetCallback *netCallback);

			/*************************************************
			Function:       Callback()
			Description:    获取网络回调
			Input:          
			Output:
			Return:			回调接口类的具体实现的指针
			*************************************************/
			CNetCallback *Callback();

		private:
			CGlobaData();

			//回调接口类的具体实现
			CNetCallback *netCallback_;
		};
	}
	
}


#endif  // GLOBAL_DATA_H
