/*************************************************
Copyright (C), 2017, HX Tech Co., Ltd.
File name:      workqueue.h
Author:			XuYC
Version:
Date:
Purpose: 定义用"boost::asio"中"Asio"，"Thread"为基础的任务队列类
Note:    1.使用线程池；2.使用"io_service pool"，但负载均衡没很好考虑；3.每个"io_service"对象对应一个线程!。
*************************************************/

#ifndef __WORK_QUEUE_H__
#define __WORK_QUEUE_H__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif

#if defined(_MSC_VER) && (_MSC_VER < 1700)
#error "编译器版本必须是VS2012或以上!"
#endif

#include <boost/asio.hpp>
#include <boost/thread.hpp>
#include <type_traits>

namespace AllTrade{

    class WorkQueue
    {
    public:
        // 虽然可以8核/16核，这么多线程动力，但是需要注意防范其它资源不够(比如访问数据库句柄)
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
