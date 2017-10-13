/*************************************************
Copyright (C), 2017, HX Tech Co., Ltd.
File name:      SettleManagerThread.h
Author:			XuYC
Version:
Date:
Description:    提供成交费用模块具体实现
*************************************************/

#ifndef _SETTLEMANAGERTHREAD_H_
#define _SETTLEMANAGERTHREAD_H_

#include <boost/noncopyable.hpp>
#include "utility/instance_shared_from_this.h"
#include "define/params_declare.h"
#include "utility/timer_queue.h"

namespace AllTrade {
    namespace NPTradeCenter {
        class SettleManagerThread
            : public CommonTools::instance_shared_from_this<SettleManagerThread>
            , public boost::noncopyable
        {
            typedef CommonTools::TimerQueue<std::chrono::high_resolution_clock>		    TimerQueues;

        public:
            SettleManagerThread();
            ~SettleManagerThread();

            // 注意,析构前必须调用反初始化函数
            void unInitialize();

            // 新增结算时间,可多次结算,可分商品类型结算
            void start();

        private:
            void settle();
            void settle_thread(bool is_erased);

            // 获取下次结算时间
            std::tm getNextSettleTime(TimeType settle_time);

        private:
            TimerQueues                                         m_timerQueue;       // 定时器队列,定时触发结算线程
            CommonTools::AsioServicePool                        m_servicePool;      // 高精度网络定时器线程池,后期可维持多个结算线程

            TimeType   m_settle_time;

        };
    }
}

#endif