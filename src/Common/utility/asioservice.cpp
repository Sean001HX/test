#ifdef _MSC_VER
#define _WIN32_WINNT 0x0501
#endif

#include <boost\bind.hpp>
#include <boost/asio.hpp>
#include "asioservice.h"
#include "utility/utility_fun.h"


namespace CommonTools
{
	//////////////////////////////////////////////////////////////////////////
	// AsioServicePool class
    AsioServicePool::AsioServicePool()
		: next_io_service_(0)
        , bstart_(false)
	{
        init();
	}


    void AsioServicePool::init()
    {
        threads_.clear();
        works_.clear();
        io_services_.clear();		
        next_io_service_ = 0;
    }

	AsioServicePool::~AsioServicePool()
	{
        stop();
	}

	void AsioServicePool::start(size_t service_num)
	{
        bool expected = false;
        if ( !bstart_.compare_exchange_strong(expected, true) )  // 已启动则退出
            return;

        init();

        if ( service_num == 0 )
			service_num = UtilityFun::get_cpu_count() ;

        // 为所有io_service定义work,以确保io_service的run()函数不会终止,直至调用其stop()
		for (std::size_t i = 0; i < service_num; ++i)
		{
            io_service_ptr io_service = std::make_shared<boost::asio::io_service>();
			assert( io_service );
            work_ptr work = std::make_shared<boost::asio::io_service::work>(*io_service);
			assert( work );

			io_services_.push_back(io_service);
			works_.push_back(work);
		}

		for (std::size_t i = 0; i < io_services_.size(); ++i)
		{
            thread_ptr thread(new std::thread(std::bind(static_cast<std::size_t(boost::asio::io_service::*)(void)>(&boost::asio::io_service::run), io_services_[i])));
			threads_.push_back(thread);
		}
	}

	void AsioServicePool::stop()
	{
        bool expected = true;
        if ( !bstart_.compare_exchange_strong(expected, false) )  // 未启动则退出
            return;

        // 明确停止所有io_service对象
		for (std::size_t i = 0; i < io_services_.size(); ++i)
			io_services_[i]->stop();

		// 等待所有线程退出
		for (std::size_t i = 0; i < threads_.size(); ++i)
			if ( threads_[i]->joinable() )
				threads_[i]->join();

	}

    boost::asio::io_service& AsioServicePool::get_io_service()
	{
        assert( next_io_service_ < io_services_.size());

        boost::asio::io_service& io_service = *io_services_[next_io_service_];
		++next_io_service_;
		if (next_io_service_ == io_services_.size())
			next_io_service_ = 0;
		return io_service;
	}

} // namespace CommonTools
