/*************************************************
Copyright (C), 2017, HX Tech Co., Ltd.
File name:      SimulateOrder.h
Author:			XuYC
Version:
Date:
Description:    仿真交易模块 - 委托处理,由行情驱动,不做撮合交易
*************************************************/

#ifndef __SIMULATE_ORDER_H__
#define __SIMULATE_ORDER_H__

#include <map>
#include <set>
#include <vector>
#include <atomic>
#include <boost/noncopyable.hpp>
#include "utility/instance_shared_from_this.h"
#include "../Application/trade_handler_declare.h"
#include "utility/thread_core.h"
#include "utility/rwmutex.h"
#include "define/params_declare.h"
#include "define/struct_declare.h"

namespace AllTrade{
    namespace NPTradeCenter {
        // 仿真交易模块 - 委托处理
        class SimulateOrder
            : public CommonTools::instance_shared_from_this<SimulateOrder>
            , public boost::noncopyable
        {
        public:
            SimulateOrder();
            ~SimulateOrder();

            // 接收下单委托信息,将其放入仿真委托队列
            // 注: 此时委托信息必须为有效信息
            void createOrder(const OrderHrPtr& order_hr_ptr);

            // 接收撤单委托信息,将其放入仿真委托队列
            // 注: 此时委托信息必须为有效信息
            void cancelOrder(const OrderHrPtr& order_hr_ptr);

        private:
            // 行情变化后触发的计算线程,注意内部不能含有任何阻塞
            long thread_quote_calculate(void* param);

            // 清理当前所有委托
            void clear();

            // 根据行情计算并修改所有委托,此函数在计算线程内,不可阻塞
            void calculateAll();

            // 撮合成交,写入数据库,并通知TradeManager模块发送委托状态变化和成交信息至前置机
            // 注: 优先发送委托状态改变信息,之后发送成交信息
            void matchOrder(const OrderHrPtr& order_hr_ptr, QuoteHrPtr quote_ptr = nullptr);

        private:
            CommonTools::thread_core<SimulateOrder>     m_thread_call;  // 计算线程

            CommonTools::event                          m_quote_event;  // 行情更新事件
            CommonTools::event                          m_close_event;  // 关闭事件
        };
    }
}

#endif