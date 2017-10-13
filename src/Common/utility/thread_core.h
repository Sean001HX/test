// thread_core.hpp

#ifndef __THREAD_CORE_H__
#define __THREAD_CORE_H__

#include "sync.h"

#include <cassert>
//#include <sstream>
#include <iomanip>

#ifdef _MSC_VER
#  include <process.h>
#  if !defined(_MT)
#    error must use multithreaded run-time library by setting /MT option.
#  endif
#elif defined(__GNUC__)
#  include <pthread.h>
#endif

#ifdef _MSC_VER
typedef HANDLE thread_handle;
typedef unsigned int thread_id;
#define INVALID_THREAD_HANDLE NULL
#elif defined(__GNUC__)
typedef pthread_t thread_handle;
typedef pthread_t thread_id;
#define INVALID_THREAD_HANDLE -1
#endif


namespace CommonTools
{
	/*	Example Usage:
	class Foo
	{
	public:
	Foo() : m_Thread( this, ThreadFunc )  // Init Member Function Thread Object 

	void  ThreadFunc( LPVOID lpParam )
	{
	// Thread stuff starts here

	}

	void  Bar()
	{
	LPVOID lpParam;
	...
	m_Thread.Start( lpParam );
	}

	private:
	MemFuncThread<Foo>  m_Thread;
	};
	*/

	template<class T>
	class thread_core
	{
		typedef long (T::*T_MEM_FUNC)(void* param);

	public:
		thread_core(T* obj_ptr, T_MEM_FUNC func_ptr) : m_stop_event(false)
		{
			m_obj_ptr = obj_ptr;
			m_mfunc = func_ptr;
			m_handle = INVALID_THREAD_HANDLE;	
			m_param = NULL;
			m_running = false;
			m_terminating = false;
			m_waiting_stop_thread_cnt = 0;
		}

		~thread_core()
		{
			if( is_running() ) stop();
            //close_handle();
		}
#if 0
		std::string GetObjName() {
			std::stringstream  stream;
			stream << " " << std::hex << std::setw(8) << (void*)this << " ";
			return stream.str();
		}
#endif

		bool start(void* param)
		{
			scoped_lock lock(m_lock);

			if( m_running || m_waiting_stop_thread_cnt != 0 )
			{
				return false;			
			}

			m_param = param;

#ifdef _MSC_VER
			m_handle = (thread_handle)_beginthreadex( NULL, 0, thread_func, this, 0, &m_id );
			m_running = (m_handle != INVALID_THREAD_HANDLE);	

#elif defined(__GNUC__)
			int ret = pthread_create(&m_handle, NULL, thread_func, this);
			m_running = (ret == 0);
			m_id = m_handle;
#endif

			m_terminating = false;
			m_stop_event.reset();
#ifdef SHOW_DEBUG_INFO
			cout << "thread_core: started." << endl;
#endif

			return m_running;
		}

		bool set_priority( int priority )
		{
			bool  result = false;
           
#ifdef _MSC_VER
			scoped_lock lock(m_lock);
			if( m_handle != INVALID_THREAD_HANDLE )
				result = (SetThreadPriority( m_handle, priority ) == TRUE);
			else
				result = false;
#endif

			return result;
		}

		bool stop( /*int timeout = INFINITE */)
		{
			m_lock.lock();
			if( !m_running && (m_handle == INVALID_THREAD_HANDLE) )
			{
				m_lock.unlock();
				return true;			
			}

			if( m_terminating )
			{
				++m_waiting_stop_thread_cnt;
				m_lock.unlock();
                m_stop_event.timedwait(5000);
				//if (m_stop_event.timedwait(5000) == false)
					//assert( !"Wait for thread_core stop event time out in 5s." );将断言去除
// 			    ::MessageBox( NULL, "FATAL ERROR !!!", "FATAL!!!", MB_OK );
// 			    assert( !"WARNING: Try to stop a thread_core while the thread_core is terminating.\n return without waiting." );
				m_lock.lock();
				--m_waiting_stop_thread_cnt;
				m_lock.unlock();
				return true;			
			}

			assert( m_handle != INVALID_THREAD_HANDLE );
			if(m_handle != INVALID_THREAD_HANDLE)
			{
				m_terminating = true;
				m_lock.unlock();

#ifdef _MSC_VER
				if (WaitForSingleObject( m_handle, 5000 ) == WAIT_TIMEOUT)
				{
//     				::MessageBox( NULL, "Wait for thread_core termination time out in 5s.", "WARNING", MB_OK );
					//assert( !"Wait for thread_core termination time out in 5s." );将断言去除
					return false;
				}

				m_lock.lock();
				CloseHandle( m_handle );

#elif defined(__GNUC__)
#ifdef SHOW_DEBUG_INFO
				cout << "thread_core: waiting exit." << endl;
#endif
				pthread_join( m_handle, NULL );

				m_lock.lock();
#endif

				m_handle = INVALID_THREAD_HANDLE;
				m_param = NULL;
				m_running = false;
				m_terminating = false;
				m_stop_event.set();		
			}

			m_lock.unlock();
			return true;
		}

		void close_handle()
		{
			scoped_lock lock(m_lock);

//			assert( m_handle != INVALID_THREAD_HANDLE );
			if(m_handle != INVALID_THREAD_HANDLE)
			{
#ifdef _MSC_VER
				CloseHandle( m_handle );
#elif defined(__GNUC__)
#ifdef SHOW_DEBUG_INFO
				cout << "thread_core: waiting exit." << endl;
#endif
				pthread_join( m_handle, NULL );
#endif

				m_handle = INVALID_THREAD_HANDLE;
				m_param = NULL;
				m_running = false;
				m_terminating = false;
				m_stop_event.set();		
			}
		}

		thread_handle handle()
		{
			scoped_lock lock( m_lock );
			return m_handle;
		}

		bool is_running() const
		{
			scoped_lock lock( m_lock );
			return m_running;
		}

	private:

#ifdef _MSC_VER
		static unsigned int WINAPI thread_func(void* param)
		{
			thread_core<T>* this_ptr = (thread_core<T>*)param;

			if( this_ptr )
			{
				(this_ptr->m_obj_ptr->*(this_ptr->m_mfunc))( this_ptr->m_param );
				this_ptr->m_running = false;
			}

			_endthreadex( 0 );		
			return 0;
		}
#elif defined(__GNUC__)
		static void* thread_func(void* param)
		{
			thread_core<T>* this_ptr = (thread_core<T>*)param;

			if( this_ptr )
			{
#ifdef SHOW_DEBUG_INFO
				cout << "thread_core: thread_func" << endl;
#endif
				(this_ptr->m_obj_ptr->*(this_ptr->m_mfunc))( this_ptr->m_param );
				this_ptr->m_running = false;
			}
#ifdef SHOW_DEBUG_INFO
			cout << "thread_coure::thread_func: exiting..." << endl;	
#endif

			pthread_exit( NULL );
			return NULL;
		}
#endif

	protected:
		T*				m_obj_ptr;
		T_MEM_FUNC		m_mfunc;
		thread_handle	m_handle;
		thread_id		m_id;
		void*			m_param;

		mutable bool	m_running;
		bool			m_terminating;
		int				m_waiting_stop_thread_cnt;

		event			m_stop_event;
		mutable mutex	m_lock;
	};

} // namespace CommonTools

#endif//__THREAD_CORE_H__
