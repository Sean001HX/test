#pragma once

#include "define/stock_api/tcas_def.h"
#include "define/stock_api/StockDllStruct.h"
#include <vector>

namespace TcasMedia
{
	//回调类
	class CTcasMediaCallBack
	{
	public:
		virtual ~CTcasMediaCallBack(){};

		virtual void OnConnect(bool bConnect) { ; }// 为界面层

		virtual void OnLogin(int errCode) = 0;
		virtual void OnPlaceOrder(StockDLL::OrderInfo) = 0;
		virtual void OnCancelOrder(StockDLL::CancelOrderInfo) = 0;
		virtual void OnQueryOrder() {};
		virtual void OnQueryQuotation() {} ;
		virtual void OnQueryPostion() {};
	};
}