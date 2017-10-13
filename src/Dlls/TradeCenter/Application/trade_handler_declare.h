/*************************************************
Copyright (C), 2017, HX Tech Co., Ltd.
File name:      trade_handler_declare.h
Author:			XuYC
Version:
Date:
Description:    �ṩ��������ͳһ�Ľṹ��ָ������,��ֹ�ṹ���ļ��໥�����Լ��ظ�����,�ӿ�����ٶ�
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
        // ί�в���
        class OrderBaseHandler;
        typedef std::shared_ptr<OrderBaseHandler>                   OrderHrPtr;
        class StockOrderHandler;
        typedef std::shared_ptr<StockOrderHandler>                  StockOrderHrPtr;
        class ForeignFutureOrderHandler;
        typedef std::shared_ptr<ForeignFutureOrderHandler>          ForeignFutureOrderHrPtr;
        class ChinaFutureOrderHandler;
        typedef std::shared_ptr<ChinaFutureOrderHandler>            ChinaFutureOrderHrPtr;

        // �ɽ�����
        class TradeBaseHandler;
        typedef std::shared_ptr<TradeBaseHandler>                   TradeHrPtr;
        class StockTradeHandler;
        typedef std::shared_ptr<StockTradeHandler>                  StockTradeHrPtr;
        class ForeignFutureTradeHandler;
        typedef std::shared_ptr<ForeignFutureTradeHandler>          ForeignFutureTradeHrPtr;
        class ChinaFutureTradeHandler;
        typedef std::shared_ptr<ChinaFutureTradeHandler>            ChinaFutureTradeHrPtr;

        // �ֲֲ���
        class PositionBaseHandler;
        typedef std::shared_ptr<PositionBaseHandler>                PositionHrPtr;
        class StockPositionHandler;
        typedef std::shared_ptr<StockPositionHandler>               StockPositionHrPtr;
        class ForeignFuturePositionHandler;
        typedef std::shared_ptr<ForeignFuturePositionHandler>       ForeignFuturePositionHrPtr;
        class ChinaFuturePositionHandler;
        typedef std::shared_ptr<ChinaFuturePositionHandler>         ChinaFuturePositionHrPtr;

        // �������
        class QuoteBaseHandler;
        typedef std::shared_ptr<QuoteBaseHandler>                   QuoteHrPtr;

    }
}

#endif