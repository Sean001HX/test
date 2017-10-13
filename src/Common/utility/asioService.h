/*
* Purpose: ����ʹ��"boost::asio"��Ϊ����ͨѶ�ײ���ʱ���¼���������.
* Note:    1.ʹ���̳߳أ�2.ʹ��"io_service pool"�������ؾ���û�ܺÿ��ǣ�3.ÿ��"io_service"�����Ӧһ���߳�!��
*
* ��Դ�ڣ�"http://www.boost.org/doc/libs/1_55_0/doc/html/boost_asio/example/cpp03/http/server2/io_service_pool.hpp"
*
* Modified: ����ȡ������CPU��Ŀ�ĺ���Ǩ�Ƶ�"utilities_nv.h"�ļ��С�
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
    // io_service�Ķ����
    class AsioServicePool : private boost::noncopyable
    {
    public:
        explicit AsioServicePool();
        ~AsioServicePool();

        // ����������ʹ�ñ����ʱ��Ҫ����һ��"AsioServicePool"���󣬲�"start"��Ȼ����ܽ�������һ������ͨѶ�������!
        // ��ο�������֮��������
        // service_num ȱʡʱ,����������ǻ�����cpu��
        void  start(size_t service_num = 0);

        // ֹͣ�����ڵ��ô˺���ǰ��һ��Ҫ����˶�����ص�����"connection"��"acceptor"��/��"connector"ȫ���رգ�������ܳ����쳣!!!
        void  stop();

        // ʹ��ѭ��������ѡ����һ��io_service��ʹ��
        boost::asio::io_service& get_io_service();

    private:
        void init();

        typedef std::shared_ptr<boost::asio::io_service>			io_service_ptr;
        typedef std::shared_ptr<boost::asio::io_service::work>	    work_ptr;
        typedef std::shared_ptr<std::thread>			            thread_ptr;

        // io_service�Ķ����
        std::vector<io_service_ptr> io_services_;
        // ����io_services���������
        std::vector<work_ptr>       works_;
        // ���ӵ���һ��io_service
        std::size_t                 next_io_service_;
        // �̳߳�
        std::vector<thread_ptr>     threads_;
        // �Ƿ��ѿ���
        std::atomic<bool>           bstart_;
    };

    typedef std::shared_ptr<AsioServicePool>	AsioServicePoolPtr;

} // namespace CommonTools

#endif // #ifndef _ASIO_SERVICE_H_
