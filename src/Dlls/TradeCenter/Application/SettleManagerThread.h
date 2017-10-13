/*************************************************
Copyright (C), 2017, HX Tech Co., Ltd.
File name:      SettleManagerThread.h
Author:			XuYC
Version:
Date:
Description:    �ṩ�ɽ�����ģ�����ʵ��
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

            // ע��,����ǰ������÷���ʼ������
            void unInitialize();

            // ��������ʱ��,�ɶ�ν���,�ɷ���Ʒ���ͽ���
            void start();

        private:
            void settle();
            void settle_thread(bool is_erased);

            // ��ȡ�´ν���ʱ��
            std::tm getNextSettleTime(TimeType settle_time);

        private:
            TimerQueues                                         m_timerQueue;       // ��ʱ������,��ʱ���������߳�
            CommonTools::AsioServicePool                        m_servicePool;      // �߾������綨ʱ���̳߳�,���ڿ�ά�ֶ�������߳�

            TimeType   m_settle_time;

        };
    }
}

#endif