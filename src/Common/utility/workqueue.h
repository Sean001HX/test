/*************************************************
Copyright (C), 2017, HX Tech Co., Ltd.
File name:      workqueue.h
Author:			XuYC
Version:
Date:
Purpose: ������"boost::asio"��"Asio"��"Thread"Ϊ���������������
Note:    1.ʹ���̳߳أ�2.ʹ��"io_service pool"�������ؾ���û�ܺÿ��ǣ�3.ÿ��"io_service"�����Ӧһ���߳�!��
*************************************************/

#ifndef __WORK_QUEUE_H__
#define __WORK_QUEUE_H__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif

#if defined(_MSC_VER) && (_MSC_VER < 1700)
#error "�������汾������VS2012������!"
#endif

#include <boost/asio.hpp>
#include <boost/thread.hpp>
#include <type_traits>

namespace AllTrade{

    class WorkQueue
    {
    public:
        // ��Ȼ����8��/16�ˣ���ô���̶߳�����������Ҫע�����������Դ����(����������ݿ���)
        WorkQueue(int workers = 3)
            : m_io_service(new boost::asio::io_service)
            , m_work(new boost::asio::io_service::work(*m_io_service))
        {
            for (size_t i = 0; i < workers; ++i) {
                threads_.create_thread(
                    boost::bind(&boost::asio::io_service::run, m_io_service));
            }
        }

        virtual ~WorkQueue()
        {
            m_io_service->stop();
            m_io_service.reset();
//             threads_.join_all();
            m_work.reset();
        }

        template <typename TTask>
        void add_task(TTask& task)
        {
            m_io_service->post(std::move(task));
        }

    private:
        boost::thread_group threads_;

        typedef boost::shared_ptr<boost::asio::io_service> io_service_ptr;
        typedef boost::shared_ptr<boost::asio::io_service::work> work_ptr;

        io_service_ptr  m_io_service;
        work_ptr        m_work;
    };

}
#endif // #ifndef __WORK_QUEUE_H__
