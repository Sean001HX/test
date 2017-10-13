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
		Description:    ���ݿ��ʼ������
		Input:
		Output:
		Return:			��ʾ������
		*************************************************/
		DB_ACCESS_API int InitDB();
		
		/*************************************************
		Function:       Fint()
		Description:    ���ݿⷴ��ʼ������
		Input:
		Output:
		Return:			��ʾ������
		*************************************************/
		DB_ACCESS_API int FintDB();
		
		/*************************************************
		Function:       AllocDBHandler()
		Description:    ��ȡ���ݿ�handler
		Input:
		Output:
		Return:			���ݿ�handlerָ��
		*************************************************/
		DB_ACCESS_API CDBHandler *AllocDBHandler();
		
		/*************************************************
		Function:       FreeDBHandler(CDBHandler *handler)
		Description:    �ͷ����ݿ�handler
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