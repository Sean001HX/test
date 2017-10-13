/*
*
* Purpose: 定义一个使用boost:asio作为基础的定时器队列类，时间精度最高为毫秒极；
* Note:    1.经不完全测试，每次定时误差(延迟)在2－3毫秒；所以，每次加入定时事件时，可将触发时间点减去3毫秒；
*		   2.线程安全，回调调用使用的是队列对象自身的线程动力，用户在回调函数中不得阻塞，应尽快返回；
*		   3.当定时器无效后，将自动被从队列中删除；
*		   4.要修改定时触发时间时，将旧定时器删除，再加入一个新定时器；
*		   5.如定时触发回调函数绑定的是成员函数，则绑定时所带入的对象指针，一定要用"shared_ptr"包装!!!
*		   6.在作循环定时用时，误差累积未考虑，慎用！
*/
#ifndef  __TIMER_QUEUE_H__
#define  __TIMER_QUEUE_H__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif

#if defined(_MSC_VER) && (_MSC_VER < 1700)
	#error "编译器版本必须是VS2012或以上!"
#endif

#include <boost\noncopyable.hpp>
#include <boost\function.hpp>
#include <boost\asio.hpp>
#include <boost\bind.hpp>
#include <chrono>
#include <ctime>
#include <memory>
#include <map>
#include <mutex>
#include <atomic>
#include <exception>
#include "asioservice.h"

//! 64 bit unsigned variable.
/** This is a typedef for 64bit uint, it ensures portability of the engine. */
#if defined(_MSC_VER) || ((__BORLANDC__ >= 0x530) && !defined(__STRICT_ANSI__))
typedef unsigned __int64			UInt64;
#elif __GNUC__
#if __WORDSIZE == 64
typedef unsigned long int 			UInt64;
#else
__extension__ typedef unsigned long long	UInt64;
#endif
#else
typedef unsigned long long			UInt64;
#endif


namespace CommonTools
{
	typedef UInt64 TimerId;
#define INVALID_TID     0       // 无效的定时器标识号

	/////////////////////////////////////////////////////////////////////////////
	//! class message queue
	template <typename Clock = std::chrono::high_resolution_clock>
	class TimerQueue : boost::noncopyable
	{
	public:
		typedef boost::function<void (bool)> Action;
		typedef typename Clock::time_point	TimePoint;

	private:
		typedef boost::asio::basic_waitable_timer<Clock> my_high_resolution_timer;
		typedef std::shared_ptr<my_high_resolution_timer> TimerPtr;

		struct TimerItem : public std::enable_shared_from_this<TimerItem>, private boost::noncopyable
		{
			TimerQueue<Clock>* queue_; //TimerQueue<Clock>& queue_;
			TimePoint           tp_;	// 第一次定时触发时间点
			TimerId             id_;	// 定时器标识，队列内唯一
			Action              act_;	// 定时触发回调函数
			unsigned int        nIntervalMS_;  // 循环定时间隔，0表示一次循环，非0表示定时循环；
			TimerPtr            pTimer_;	   // asio的定时器
            int                 loopCnt_;      //循环次数，默认为1,表示一次循环，-1表示无限循环
            std::atomic<int>    loopIndex_;    //循环计数器

			TimerItem(TimerQueue<Clock>* queue, const TimePoint& tp, TimerId id, const Action& act, unsigned int nInMS, int loopCount)
				: queue_(queue)
				, tp_(tp)
				, id_(id)
				, act_(act)
				, nIntervalMS_(nInMS)
				, pTimer_()
                , loopCnt_(loopCount)
                , loopIndex_(loopCount)
			{
				pTimer_ = std::make_shared<my_high_resolution_timer>(queue_->service_.get_io_service() );//queue_->service_.get_cpu_count() 
				//if ( !pTimer_ )
					//throw std::bad_alloc("TimerItem::TimerItem(...): can't malloc timer!");//编译时报出错误	error C2248: “std::bad_alloc::bad_alloc”: 
				if (!pTimer_)
					throw std::exception("TimerItem::TimerItem(...):can't malloc timer");

				// 移动到TimerItem::init()
				//auto self( shared_from_this() ); //仅在构造函数调用之后才能用,改用为thi
				//pTimer_->expires_at( tp_ );
				//pTimer_->async_wait( boost::bind(&TimerItem::handler, /*self*/this, boost::asio::placeholders::error ));
			}

			void init()
			{
				auto self( shared_from_this() );
				pTimer_->expires_at( tp_ );
				pTimer_->async_wait( boost::bind(&TimerItem::handler, self, boost::asio::placeholders::error ));
			}

		private:
			void handler(const boost::system::error_code& error)
			{
				try {
					if ( !error )
					{
                        if (loopCnt_ != -1)
                            loopIndex_--;

						auto self( shared_from_this() );
                        //	if ( nIntervalMS_ != 0 ) // 循环定时
						if (( loopCnt_ == -1 || (loopCnt_ != -1 && loopIndex_ != 0)) && nIntervalMS_ != 0) // 循环定时
						{
							pTimer_->expires_from_now( std::chrono::milliseconds(nIntervalMS_) );
							pTimer_->async_wait( boost::bind(&TimerItem::handler, self, boost::asio::placeholders::error ));
						}

                        bool is_erased = (loopIndex_ <= 0 && loopCnt_ != -1);
						if ( !act_.empty() )
							act_( is_erased );

                       /*if (loopCnt_ != -1)
                         loopIndex_--;*/

                        //if ( nIntervalMS_ == 0 ) 
					    if ( is_erased )	//不再需要定时，将之从队列中清除
                            queue_->erase( id_ );
					}
					else  // 有错：1.被"cancel"了；2.其他
					{
                        if (error != boost::asio::error::operation_aborted)
                            return;// DBGPrintf("TimerItem::handler() error: %s \n", error.message());该处后期需要进行错误处理
						queue_->erase( id_ );
					}
				}
				catch(...) {}
			}
		};

		typedef std::shared_ptr<TimerItem>	        TimerItemPtr;
        typedef std::pair<TimerId, TimerItemPtr>	TimerItemPair;

	public:
        TimerQueue(CommonTools::AsioServicePool& service)
			: service_(service)
			, nextId_(1) //修改定时器id从1开始
		{
		}
		~TimerQueue()
		{
			try {
				clear();
			}
			catch(...) {}	// erase all exceptions!
		}

		/**
		* @brief	在队列中加入一个定时器,nIntervalMS：定时间隔，loopCount：循环次数，默认为1表示y仅一次循环，
        *           loopCount = -1 表示无限循环
		*/
		TimerId insert(const TimePoint& tp, const Action & act, unsigned int nIntervalMS = 0, int loopCount = 1)
		{
            TimerItemPtr pItem = std::make_shared<TimerItem>(this,tp, getNextID(), act, nIntervalMS, loopCount);
			if ( !pItem )
				return 0;	// 0 is illegal ID!

			pItem->init();
			{
				std::lock_guard<std::recursive_mutex>	lock(mtx_ts_);
				timerSet_.insert( TimerItemPair(pItem->id_, pItem));
			}
			return pItem->id_;
		}
		/**
		* @brief	从队列中删除一个定时器
		*/
		void erase(TimerId id)
		{
			if ( id == 0 )
				return;

			TimerItemPtr pItem;
			{
				std::lock_guard<std::recursive_mutex>	lock(mtx_ts_);

				auto find = timerSet_.find(id);
				if ( find == timerSet_.end() )
					return ;

				pItem = find->second;
				timerSet_.erase( find );
			}

			if ( pItem )
				pItem->pTimer_->cancel();
		}

		/**
		* @brief	清理队列
		*/
		void clear()
		{
			std::lock_guard<std::recursive_mutex>	lock(mtx_ts_);
			if ( timerSet_.empty() )
				return;

			for ( auto tip : timerSet_ )
				tip.second->pTimer_->cancel();

			timerSet_.clear();
		}

		/**
		* @brief	辅助函数，通过日期时间创建一个"time_point"对象
		*/
		TimePoint makeTimePoint(
			int year,
			int month,
			int day,
			int hour = 0,
			int minute = 0,
			int second = 0,
			int millisecond = 0,
			int microsecond = 0	)
		{
			struct std::tm t;
			t.tm_sec = second;		// second of minute (0 .. 59 and 60 for leap seconds)
			t.tm_min = minute;		// minute of hour (0 .. 59)
			t.tm_hour = hour;		// hour of day (0 .. 23)
			t.tm_mday = day;		// day of month (1 .. 31)
			t.tm_mon = month-1;		// month of year (0 .. 11)
			t.tm_year = year-1900;	// year since 1900
			t.tm_isdst = -1;		// determine whether daylight saving time

            return makeTimePoint(t, millisecond, microsecond);
		}//makeTimePoint(year, month, day, hour, minute, second, millisecond, microsecond)
		
        TimePoint makeTimePoint(
            std::tm t,
            int millisecond = 0,
            int microsecond = 0 )
        {
            std::time_t tt = std::mktime(&t);
            if (tt == -1)
                throw std::domain_error("Invalid time, time_point cannot be made");
            if (millisecond < 0 || millisecond > 999 ||
                microsecond < 0 || microsecond > 999)
                //			nanosecond < 0 || nanosecond > 999)
                throw std::domain_error("Invalid time, time_point cannot be made");

            typename Clock::time_point ret_tp = Clock::from_time_t(tt);
            std::chrono::milliseconds milli(millisecond);
            std::chrono::microseconds micro(microsecond);
            //	std::chrono::nanoseconds nano(nanosecond);
            ret_tp += milli;
            ret_tp += micro;
            //	ret_tp += nano;

            return ret_tp;
        }//makeTimePoint(year, month, day, hour, minute, second, millisecond, microsecond)

		// 辅助函数，通过当前时间 + nMS毫秒，创建一个"time_point"对象
		TimePoint makeNowTimePoint(unsigned int nMS)
		{
			std::chrono::milliseconds milli(nMS);
			typename Clock::time_point ret_tp = Clock::now();
			ret_tp += milli;
			return ret_tp;
		}

	private:
		TimerQueue();
		TimerId getNextID()
		{
			TimerId id = nextId_ ++;
			if ( id == INVALID_TID )
				id = nextId_ ++;
			return id;
		}

	private:
        CommonTools::AsioServicePool&	service_;
		TimerId		                    nextId_;
		std::map<TimerId, TimerItemPtr>	timerSet_;
		std::recursive_mutex	mtx_ts_;
	};

} // namespace CommonTools

#endif // __TIMER_QUEUE_H__
