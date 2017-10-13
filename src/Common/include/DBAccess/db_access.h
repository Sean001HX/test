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



#ifndef DB_ACCESS_H
#define DB_ACCESS_H

#ifdef DB_ACCESS_EXPORTS
#define DB_ACCESS_API __declspec(dllexport)
#else
#define DB_ACCESS_API __declspec(dllimport)
#endif

#include "db_access_interface_def.h"

#ifdef __cplusplus
extern "C" {
#endif

	namespace DBAccess
	{
		/*************************************************
		Function:       Init()
		Description:    数据库初始化函数
		Input:
		Output:
		Return:			表示错误码
		*************************************************/
		DB_ACCESS_API int InitDB();
		
		/*************************************************
		Function:       Fint()
		Description:    数据库反初始化函数
		Input:
		Output:
		Return:			表示错误码
		*************************************************/
		DB_ACCESS_API int FintDB();
		
		/*************************************************
		Function:       AllocDBHandler()
		Description:    获取数据库handler
		Input:
		Output:
		Return:			数据库handler指针
		*************************************************/
		DB_ACCESS_API CDBHandler *AllocDBHandler();
		
		/*************************************************
		Function:       FreeDBHandler(CDBHandler *handler)
		Description:    释放数据库handler
		Input:			CDBHandler *handler
		Output:
		Return:			
		*************************************************/
		DB_ACCESS_API void FreeDBHandler(CDBHandler *handler);
	}

#ifdef __cplusplus
}
#endif


#endif  // DB_ACCESS_H