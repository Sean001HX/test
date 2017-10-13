/*************************************************
Copyright (C), 2017, HX Tech Co., Ltd.
File name:      SimulateOrder.h
Author:			XuYC
Version:
Date:
Description:    ���潻��ģ�� - ί�д���,����������,������Ͻ���
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
        // ���潻��ģ�� - ί�д���
        class SimulateOrder
            : public CommonTools::instance_shared_from_this<SimulateOrder>
            , public boost::noncopyable
        {
        public:
            SimulateOrder();
            ~SimulateOrder();

            // �����µ�ί����Ϣ,����������ί�ж���
            // ע: ��ʱί����Ϣ����Ϊ��Ч��Ϣ
            void createOrder(const OrderHrPtr& order_hr_ptr);

            // ���ճ���ί����Ϣ,����������ί�ж���
            // ע: ��ʱί����Ϣ����Ϊ��Ч��Ϣ
            void cancelOrder(const OrderHrPtr& order_hr_ptr);

        private:
            // ����仯�󴥷��ļ����߳�,ע���ڲ����ܺ����κ�����
            long thread_quote_calculate(void* param);

            // ����ǰ����ί��
            void clear();

            // ����������㲢�޸�����ί��,�˺����ڼ����߳���,��������
            void calculateAll();

            // ��ϳɽ�,д�����ݿ�,��֪ͨTradeManagerģ�鷢��ί��״̬�仯�ͳɽ���Ϣ��ǰ�û�
            // ע: ���ȷ���ί��״̬�ı���Ϣ,֮���ͳɽ���Ϣ
            void matchOrder(const OrderHrPtr& order_hr_ptr, QuoteHrPtr quote_ptr = nullptr);

        private:
            CommonTools::thread_core<SimulateOrder>     m_thread_call;  // �����߳�

            CommonTools::event                          m_quote_event;  // ��������¼�
            CommonTools::event                          m_close_event;  // �ر��¼�
        };
    }
}

#endif