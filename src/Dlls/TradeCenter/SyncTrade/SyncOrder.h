/*************************************************
Copyright (C), 2017, HX Tech Co., Ltd.
File name:      SyncOrder.h
Author:			XuYC
Version:
Date:
Description:    ʵ�̽���ģ��
*************************************************/

#ifndef __SYNC_ORDER_H__
#define __SYNC_ORDER_H__

#include <boost/noncopyable.hpp>
#include "utility/instance_shared_from_this.h"
#include "../Application/trade_handler_declare.h"

namespace AllTrade{
    namespace NPTradeCenter {

        class TcpCallBack;

        // ʵ�̽���ģ��
        class SyncOrder
            : public CommonTools::instance_shared_from_this<SyncOrder>
            , public boost::noncopyable
        {
        public:
            SyncOrder();
            ~SyncOrder();

            // �����µ�ί����Ϣ,����������ί�ж���
            // ע: ��ʱί����Ϣ����Ϊ��Ч��Ϣ
            void createOrder(const OrderHrPtr& order_hr_ptr);

            // ���ճ���ί����Ϣ,����������ί�ж���
            // ע: ��ʱί����Ϣ����Ϊ��Ч��Ϣ
            void cancelOrder(const OrderHrPtr& order_hr_ptr);
 
        private:
            TcpCallBack*            m_tcp_cbk;
        };

    }
}

#endif