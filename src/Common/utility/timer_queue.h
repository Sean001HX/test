/*
*
* Purpose: ����һ��ʹ��boost:asio��Ϊ�����Ķ�ʱ�������࣬ʱ�侫�����Ϊ���뼫��
* Note:    1.������ȫ���ԣ�ÿ�ζ�ʱ���(�ӳ�)��2��3���룻���ԣ�ÿ�μ��붨ʱ�¼�ʱ���ɽ�����ʱ����ȥ3���룻
*		   2.�̰߳�ȫ���ص�����ʹ�õ��Ƕ��ж���������̶߳������û��ڻص������в���������Ӧ���췵�أ�
*		   3.����ʱ����Ч�󣬽��Զ����Ӷ�����ɾ����
*		   4.Ҫ�޸Ķ�ʱ����ʱ��ʱ�����ɶ�ʱ��ɾ�����ټ���һ���¶�ʱ����
*		   5.�綨ʱ�����ص������󶨵��ǳ�Ա���������ʱ������Ķ���ָ�룬һ��Ҫ��"shared_ptr"��װ!!!
*		   6.����ѭ����ʱ��ʱ������ۻ�δ���ǣ����ã�
*/
#ifndef  __TIMER_QUEUE_H__
#define  __TIMER_QUEUE_H__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif

#if defined(_MSC_VER) && (_MSC_VER < 1700)
	#error "�������汾������VS2012������!"
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
#define INVALID_TID     0       // ��Ч�Ķ�ʱ����ʶ��

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
			TimePoint           tp_;	// ��һ�ζ�ʱ����ʱ���
			TimerId             id_;	// ��ʱ����ʶ��������Ψһ
			Action              act_;	// ��ʱ�����ص�����
			unsigned int        nIntervalMS_;  // ѭ����ʱ�����0��ʾһ��ѭ������0��ʾ��ʱѭ����
			TimerPtr            pTimer_;	   // asio�Ķ�ʱ��
            int                 loopCnt_;      //ѭ��������Ĭ��Ϊ1,��ʾһ��ѭ����-1��ʾ����ѭ��
            std::atomic<int>    loopIndex_;    //ѭ��������

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
					//throw std::bad_alloc("TimerItem::TimerItem(...): can't malloc timer!");//����ʱ��������	error C2248: ��std::bad_alloc::bad_alloc��: 
				if (!pTimer_)
					throw std::exception("TimerItem::TimerItem(...):can't malloc timer");

				// �ƶ���TimerItem::init()
				//auto self( shared_from_this() ); //���ڹ��캯������֮�������,����Ϊthi
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
                        //	if ( nIntervalMS_ != 0 ) // ѭ����ʱ
						if (( loopCnt_ == -1 || (loopCnt_ != -1 && loopIndex_ != 0)) && nIntervalMS_ != 0) // ѭ����ʱ
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
					    if ( is_erased )	//������Ҫ��ʱ����֮�Ӷ��������
                            queue_->erase( id_ );
					}
					else  // �д�1.��"cancel"�ˣ�2.����
					{
                        if (error != boost::asio::error::operation_aborted)
                            return;// DBGPrintf("TimerItem::handler() error: %s \n", error.message());�ô�������Ҫ���д�����
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
			, nextId_(1) //�޸Ķ�ʱ��id��1��ʼ
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
		* @brief	�ڶ����м���һ����ʱ��,nIntervalMS����ʱ�����loopCount��ѭ��������Ĭ��Ϊ1��ʾy��һ��ѭ����
        *           loopCount = -1 ��ʾ����ѭ��
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
		* @brief	�Ӷ�����ɾ��һ����ʱ��
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
		* @brief	�������
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
		* @brief	����������ͨ������ʱ�䴴��һ��"time_point"����
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

		// ����������ͨ����ǰʱ�� + nMS���룬����һ��"time_point"����
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
