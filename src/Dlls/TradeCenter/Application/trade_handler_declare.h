/*************************************************
Copyright (C), 2017, HX Tech Co., Ltd.
File name:      trade_handler_declare.h
Author:			XuYC
Version:
Date:
Description:    提供交易中心统一的结构体指针声明,防止结构体文件相互包含以及重复定义,加快编译速度
*************************************************/

#ifndef __TRADE_CLASS_DECLARE_H__
#define __TRADE_CLASS_DECLARE_H__

#include <memory>

namespace AllTrade {
    namespace NPTradeCenter {
        class ServerMgrBase;
        typedef std::shared_ptr<ServerMgrBase>       TradeManagerPtr;
    }
}

namespace AllTrade {
    namespace NPTradeCenter {
        // 委托操作
        class OrderBaseHandler;
        typedef std::shared_ptr<OrderBaseHandler>                   OrderHrPtr;
        class StockOrderHandler;
        typedef std::shared_ptr<StockOrderHandler>                  StockOrderHrPtr;
        class ForeignFutureOrderHandler;
        typedef std::shared_ptr<ForeignFutureOrderHandler>          ForeignFutureOrderHrPtr;
        class ChinaFutureOrderHandler;
        typedef std::shared_ptr<ChinaFutureOrderHandler>            ChinaFutureOrderHrPtr;

        // 成交操作
        class TradeBaseHandler;
        typedef std::shared_ptr<TradeBaseHandler>                   TradeHrPtr;
        class StockTradeHandler;
        typedef std::shared_ptr<StockTradeHandler>                  StockTradeHrPtr;
        class ForeignFutureTradeHandler;
        typedef std::shared_ptr<ForeignFutureTradeHandler>          ForeignFutureTradeHrPtr;
        class ChinaFutureTradeHandler;
        typedef std::shared_ptr<ChinaFutureTradeHandler>            ChinaFutureTradeHrPtr;

        // 持仓操作
        class PositionBaseHandler;
        typedef std::shared_ptr<PositionBaseHandler>                PositionHrPtr;
        class StockPositionHandler;
        typedef std::shared_ptr<StockPositionHandler>               StockPositionHrPtr;
        class ForeignFuturePositionHandler;
        typedef std::shared_ptr<ForeignFuturePositionHandler>       ForeignFuturePositionHrPtr;
        class ChinaFuturePositionHandler;
        typedef std::shared_ptr<ChinaFuturePositionHandler>         ChinaFuturePositionHrPtr;

        // 行情操作
        class QuoteBaseHandler;
        typedef std::shared_ptr<QuoteBaseHandler>                   QuoteHrPtr;

    }
}

#endif