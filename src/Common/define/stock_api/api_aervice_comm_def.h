/*
brief : api service 公用信息
author :
created date : 2016-05-11
*/


#ifndef API_SERVICE_COMM_DEF_H
#define API_SERVICE_COMM_DEF_H


//  接口类型定义

#define API_SERVICE_TYPE_CTP              1             //  CTP
#define API_SERVICE_TYPE_SP               2             //  SP
#define API_SERVICE_TYPE_ESUNNY           3             //  esunny 易盛
#define API_SERVICE_TYPE_IB               4             //  IB 盈透


//  CTP 接口功能编号

enum ApiServiceOfCTP
{
	//   交易回调方法
	TradeRspBegin   =   0,
	OnRspUserLogin,                                         ///  登录请求响应
	OnRspUserLogout,                                        ///  登出请求响应
	OnRspOrderInsert,                                       ///  报单录入请求响应
	OnRspSettlementInfoConfirm,                             ///  投资者结算结果确认响应
	OnRspQryOrder,                                          ///  请求查询报单响应
	OnRspQryTrade,                                          ///  请求查询成交响应
	OnRspQryInvestorPosition,                               ///  请求查询投资者持仓响应
	OnRspQryTradingAccount,                                 ///  请求查询资金账户响应
	OnRspQryExchange,                                       ///  请求查询交易所响应
	OnRspQryProduct,                                        ///  请求查询产品响应
	OnRspQryInstrument,                                     ///  请求查询合约响应
	OnRspQryDepthMarketData,                                ///  请求查询行情响应
	OnRspQrySettlementInfo,                                 ///  请求查询投资者结算结果响应
	OnRspQryInvestorPositionDetail,                         ///  请求查询投资者持仓明细响应
	OnRspQrySettlementInfoConfirm,                          ///  请求查询结算信息确认响应

	// ********************************************************************************* //
	//   交易请求方法
	TradeReqBegin   =   0x800,
	ReqUserLogin,                                        	///  用户登录请求  
	ReqUserLogout,                                          ///  登出请求
	ReqOrderInsert,                                         ///  报单录入请求
	ReqQueryMaxOrderVolume,                                 ///  查询最大报单数量请求
	ReqSettlementInfoConfirm,                               ///  投资者结算结果确认
	ReqQryOrder,                                            ///  请求查询报单
	ReqQryTrade,                                            ///  请求查询成交
	ReqQryInvestorPosition,                                 ///  请求查询投资者持仓
	ReqQryTradingAccount,                                   ///  请求查询资金账户
	ReqQryTradingCode,                                      ///  请求查询交易编码
	ReqQryInstrumentMarginRate,                             ///  请求查询合约保证金率
	ReqQryInstrumentCommissionRate,                         ///  请求查询合约手续费率
	ReqQryExchange,                                         ///  请求查询交易所
	ReqQryProduct,                                          ///  请求查询产品
	ReqQryInstrument,                                       ///  请求查询合约
	ReqQryDepthMarketData,                                  ///  请求查询行情
	ReqQryInvestorPositionDetail,                           ///  请求查询投资者持仓明细
	ReqQryExchangeRate,                                     ///  请求查询汇率

	//  ********************************************************************************  //
	//  行情回调
	QuotationRspBegin =  0xa00,
	OnRspSubMarketData,                                    ///  订阅行情应答
	OnRspUnSubMarketData,                                  ///  取消订阅行情应答    
	OnRtnDepthMarketData,                                  ///  深度行情通知

	//  ********************************************************************************  //
	//  行情请求
	QuotationReqBegin =  0xb00,
	SubscribeMarketData,                                   ///  订阅行情
	UnSubscribeMarketData,                                 ///  退订行情
};


struct ApiServiceProtoHead                                ///  api service 协议头
{
	short       apiType;                                  ///  接口类型
	short       apiServiceProtoCode;                      ///  对应接口的协议功能编号
	int         dataLen;                                  ///  协议数据长度

	ApiServiceProtoHead()
	{
		apiType = 0;
		apiServiceProtoCode = 0;
		dataLen = 0;
	}
};

#endif  // API_SERVICE_COMM_DEF_H