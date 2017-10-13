#pragma once

#include "StockDllStruct.h"
#include "DataBase.h"

namespace StockDLL{

	class CStockDll
	{
	public:
		CStockDll() {};
		virtual ~CStockDll(){};

		virtual void init() = 0;
		virtual void finit() = 0;

		virtual bool LogOn(LogonInfo logonInfo) = 0;
		virtual bool LogOff() = 0;
		virtual bool QueryMoney() = 0;
		virtual bool QueryPosition() = 0;
		virtual bool QueryTodayOrder() = 0;
		virtual bool QueryTodayTrade() = 0;
		virtual bool OrderInsert(OrderInfo orderInfo) = 0;
		virtual bool OrderCancel(CancelOrderInfo cancelInfo) = 0;

	protected:
		int m_clientId;
		char *Result;
		char *ErrInfo;
		DataBase* m_dataProcess;

		//所有提交成功的委托， <orderNo, orderInfo>
		std::map<std::string, std::shared_ptr<DLLOrderInfo>> m_allSuccessfulOrders;
		//所有收到的成交回报，<orderNo, ...>
		std::map<std::string, std::vector<std::shared_ptr<DLLTradeInfo>>> m_allTradeInfos;
	};

} //namespace StockDLL
