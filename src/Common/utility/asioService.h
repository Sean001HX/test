/*
* Purpose: 定义使用"boost::asio"作为网络通讯底层框架时的事件调度中心.
* Note:    1.使用线程池；2.使用"io_service pool"，但负载均衡没很好考虑；3.每个"io_service"对象对应一个线程!。
*
* 来源于："http://www.boost.org/doc/libs/1_55_0/doc/html/boost_asio/example/cpp03/http/server2/io_service_pool.hpp"
*
* Modified: 将获取本机中CPU数目的函数迁移到"utilities_nv.h"文件中。
*/

#ifndef _ASIO_SERVICE_H_
#define _ASIO_SERVICE_H_

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif

#include <boost/noncopyable.hpp>
#include <thread>
#include <memory>
#include <vector>
#include <atomic>

namespace CommonTools
{
    // io_service的对象池
    class AsioServicePool : private boost::noncopyable
    {
    public:
        explicit AsioServicePool();
        ~AsioServicePool();

        // 启动服务；在使用本框架时，要生成一个"AsioServicePool"对象，并"start"，然后才能进行其他一切网络通讯相关事务!
        // 多次开启会在之后进行添加
        // service_num 缺省时,服务对象数是机器里cpu数
        void  start(size_t service_num = 0);

        // 停止服务；在调用此函数前，一定要将与此对象相关的所有"connection"、"acceptor"和/或"connector"全部关闭，否则可能出现异常!!!
        void  stop();

        // 使用循环方案来选择下一个io_service的使用
        boost::asio::io_service& get_io_service();

    private:
        void init();

        typedef std::shared_ptr<boost::asio::io_service>			io_service_ptr;
        typedef std::shared_ptr<boost::asio::io_service::work>	    work_ptr;
        typedef std::shared_ptr<std::thread>			            thread_ptr;

        // io_service的对象池
        std::vector<io_service_ptr> io_services_;
        // 保持io_services对象池运行
        std::vector<work_ptr>       works_;
        // 连接的下一个io_service
        std::size_t                 next_io_service_;
        // 线程池
        std::vector<thread_ptr>     threads_;
        // 是否已开启
        std::atomic<bool>           bstart_;
    };

    typedef std::shared_ptr<AsioServicePool>	AsioServicePoolPtr;

} // namespace CommonTools

#endif // #ifndef _ASIO_SERVICE_H_
