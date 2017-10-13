/*************************************************
Copyright (C), 2017, HX Tech Co., Ltd.
File name:      struct_quotation_declare.h
Author:			arven
Version:
Date:
Description:    �������ݽṹ����
*************************************************/

#ifndef STRUCT_QUOTATION_DECLARE_H
#define STRUCT_QUOTATION_DECLARE_H


#include "define/params_declare.h"
#include <stdint.h>

namespace AllQuotation
{

#pragma pack(push, 1)

	//  ������Ϣ

#define  QUOTATION_LEVEL   5                           //  ���鵵��
#define  DATE_MULTIFIERS   1000000000                  //  
#define  TIME_MULTIFIERS   1000                  

	//  ����ע����Ϣ
	struct QuotationRegister
	{
		AllTrade::ContractCodeType			quotationCode;                           //  �����ʶ�� ֤ȯ���롢�ڻ���Լ����Ȩ��Լ��
		bool								beUsed;                                  //  ���ñ�־
	};


	//  ���鹫����Ϣ
	struct QuotationCommon
	{
		uint64_t							 updataTime;                              //  ����ʱ��   ��ʽ yyyymmddHHMMSSsss  �� 20100102030405678 ��ʾ 2010-01-02 03:04:05.678
		uint64_t                             tradingDay;                              //  ������     ��ʽ yyyymmdd   �� 20100102 ��ʾ 2010-01-02
		double								 open;                                    //  ���̼�
		double								 preClose;                                //  �����̼�
		double								 close;                                   //  �����̼�
		double                               preSettle;                               //  �����
		double								 high;                                    //  ��߼�
		double								 low;                                     //  ��ͼ�
		double								 lastPrice;                               //  ���¼�
		uint64_t							 lastVolume;                              //  ������
		uint64_t                             openInterest;                            //  �ֲ���
		double                               turnOverAmount;                          //  ���ճɽ����
		uint64_t                             turnOverVolume;                          //  ���ճɽ���
		double								 bidPrice[QUOTATION_LEVEL];               //  �൵���
		double								 askPrice[QUOTATION_LEVEL];               //  �൵����
		uint64_t							 bidVolume[QUOTATION_LEVEL];              //  �൵����
		uint64_t							 askVolume[QUOTATION_LEVEL];              //  �൵����
		//////////////////////
		AllTrade::ContractCodeType           quotationCode;                           //  �����ʶ�� ֤ȯ���롢�ڻ���Լ����Ȩ��Լ��
		AllTrade::ProductTypeType            type;                                    //  �������
	};

	//  �ڻ�����
	struct QuotationOfFuture : public QuotationCommon
	{

	};

#pragma pack(pop)

}  //  namespace AllQuotation

#endif  // STRUCT_QUOTATION_DECLARE_H