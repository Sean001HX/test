/*************************************************
Copyright (C), 2017, HX Tech Co., Ltd.
File name:      struct_quotation_declare.h
Author:			arven
Version:
Date:
Description:    行情数据结构定义
*************************************************/

#ifndef STRUCT_QUOTATION_DECLARE_H
#define STRUCT_QUOTATION_DECLARE_H


#include "define/params_declare.h"
#include <stdint.h>

namespace AllQuotation
{

#pragma pack(push, 1)

	//  行情信息

#define  QUOTATION_LEVEL   5                           //  行情档数
#define  DATE_MULTIFIERS   1000000000                  //  
#define  TIME_MULTIFIERS   1000                  

	//  行情注册信息
	struct QuotationRegister
	{
		AllTrade::ContractCodeType			quotationCode;                           //  行情标识， 证券代码、期货合约、期权合约等
		bool								beUsed;                                  //  启用标志
	};


	//  行情公共信息
	struct QuotationCommon
	{
		uint64_t							 updataTime;                              //  更新时间   格式 yyyymmddHHMMSSsss  如 20100102030405678 表示 2010-01-02 03:04:05.678
		uint64_t                             tradingDay;                              //  交易日     格式 yyyymmdd   如 20100102 表示 2010-01-02
		double								 open;                                    //  开盘价
		double								 preClose;                                //  昨收盘价
		double								 close;                                   //  今收盘价
		double                               preSettle;                               //  昨结算
		double								 high;                                    //  最高价
		double								 low;                                     //  最低价
		double								 lastPrice;                               //  最新价
		uint64_t							 lastVolume;                              //  最新量
		uint64_t                             openInterest;                            //  持仓量
		double                               turnOverAmount;                          //  当日成交金额
		uint64_t                             turnOverVolume;                          //  当日成交量
		double								 bidPrice[QUOTATION_LEVEL];               //  多档买价
		double								 askPrice[QUOTATION_LEVEL];               //  多档卖价
		uint64_t							 bidVolume[QUOTATION_LEVEL];              //  多档买量
		uint64_t							 askVolume[QUOTATION_LEVEL];              //  多档卖量
		//////////////////////
		AllTrade::ContractCodeType           quotationCode;                           //  行情标识， 证券代码、期货合约、期权合约等
		AllTrade::ProductTypeType            type;                                    //  行情类别
	};

	//  期货行情
	struct QuotationOfFuture : public QuotationCommon
	{

	};

#pragma pack(pop)

}  //  namespace AllQuotation

#endif  // STRUCT_QUOTATION_DECLARE_H