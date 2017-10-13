/*************************************************
Copyright (C), 2017, HX Tech Co., Ltd.
File name:      SyncOrder.h
Author:			XuYC
Version:
Date:
Description:    实盘交易模块
*************************************************/

#ifndef __SYNC_ORDER_H__
#define __SYNC_ORDER_H__

#include <boost/noncopyable.hpp>
#include "utility/instance_shared_from_this.h"
#include "../Application/trade_handler_declare.h"

namespace AllTrade{
    namespace NPTradeCenter {

        class TcpCallBack;

        // 实盘交易模块
        class SyncOrder
            : public CommonTools::instance_shared_from_this<SyncOrder>
            , public boost::noncopyable
        {
        public:
            SyncOrder();
            ~SyncOrder();

            // 接收下单委托信息,将其放入仿真委托队列
            // 注: 此时委托信息必须为有效信息
            void createOrder(const OrderHrPtr& order_hr_ptr);

            // 接收撤单委托信息,将其放入仿真委托队列
            // 注: 此时委托信息必须为有效信息
            void cancelOrder(const OrderHrPtr& order_hr_ptr);
 
        private:
            TcpCallBack*            m_tcp_cbk;
        };

    }
}

#endif