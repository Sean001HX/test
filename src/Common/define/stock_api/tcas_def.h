#ifndef  TCAS_DEF_H
#define  TCAS_DEF_H

enum
{
	////////////////////////////////////////////////////API service相关的网络协议码///////////////////////////////////////////////////////
	NET_AS_BEGIN = 0x1000,

	NET_AS_LOGIN,					//api service向TC登录
	NET_AS_PUSH_QUOTATION,			//api service向TC推送行情
	NET_AS_NET_STATUS,				//api service向TC告知自己的网络状态
	NET_AS_REGISTER_QUOTATION,		//注册行情
	NET_AS_UNREGISTER_QUOTATION,	//反注册行情
	NET_AS_QUERY_QUOTATION,			//查询行情
	NET_AS_START_QUOTATION,			//启动行情
	NET_AS_PLACE_ORDER,				//下单
	NET_AS_PLACE_ORDER_RSP_STATUS,	//单子状态
	NET_AS_PLACE_ORDER_RSP_ORDER,   //单子信息
	NET_AS_PLACE_ORDER_RSP_TRADE,	//成交信息
	NET_AS_CANCEL_ORDER,			//撤单
	NET_AS_QUERY_ORDER,				//查单
	NET_AS_QUERY_POSITION,			//查持仓
	NET_AS_NOTIFY_ASYNC_ORDER_RECORD,      //  查询委托记录
	NET_AS_NOTIFY_ASYNC_TRADE_RECORD,      //  查询成交记录

	NET_AS_END = 0x1F00,
	////////////////////////////////////////////////////API service相关的网络协议码///////////////////////////////////////////////////////
};

#endif
