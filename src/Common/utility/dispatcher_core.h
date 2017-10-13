/////////////////////////////////////////////////////////////////
/*
* Purpose: 异步调度实现基础
*/

#ifndef __DISPATCHER_H__
#define __DISPATCHER_H__

#ifdef _MSC_VER
// warning C4355: 'this' : used in base member initializer list
#pragma warning(disable : 4355) 
#endif

#include "thread_core.h"
#include <list>
#include <iostream>

namespace CommonTools
{
	template <class Message>
	class dispatcher_callback
	{
	public:
		dispatcher_callback() { }
		virtual ~dispatcher_callback() { }

		virtual long on_threadstart(void* param) = 0;
		virtual long on_threadstop(void* param) = 0;
		virtual long on_message(Message msg, bool cleanup) = 0;
		virtual long on_event(handler evt) = 0;
	};

	enum __dispatcher_param { 
		dispatcher_handler_table_size   = 20 
	};

	enum __dispatcher_error { 
		dispatcher_error_no_error       = 0,
		dispatcher_error_general        = -1,
		dispatcher_error_wait_failed    = -2,
		dispatcher_error_exit_event     = 1
	};

	template<class Message>
	class dispatcher
	{	
	public:
		dispatcher(dispatcher_callback<Message>* callback_ptr)
			: m_thread(this, &dispatcher::thread_func)
		{
			assert(callback_ptr);
			m_callback_ptr = callback_ptr;
			m_handle_count = 0;
			m_message_enabled = false;
		}

		virtual ~dispatcher()
		{
			assert(!m_thread.is_running());
			assert(m_handle_count == 0);
			assert(m_msg_queue.size() == 0);

			m_callback_ptr = NULL;
		}

		bool start(void* param = NULL)
		{
			if(m_thread.is_running())
				return true;

			m_handle_count = 0;
			assert(m_msg_queue.size() == 0);
			m_exit_event.reset();
			m_exitok_event.reset();
			m_continue_event.reset();

			enable_message();
			return m_thread.start(param);
		}

		bool stop()
		{
			if(!m_thread.is_running())
				return true;

			enable_message(false);
			m_exit_event.set();
			//#define SHOW_DEBUG_INFO
			//#ifdef SHOW_DEBUG_INFO
			//		cout << "waiting for exitok event..." << endl;
			//#endif
			m_exitok_event.wait();
			//#ifdef SHOW_DEBUG_INFO
			//		cout << "waited exitok event." << endl;
			//#endif
			//		m_msg_queue.clear();
			return m_thread.stop();
		}

		bool is_running() const
		{
			return m_thread.is_running();
		}

		bool send_message(Message msg)
		{
			int ret = dispatcher_error_general;

			if(m_callback_ptr)
				ret = m_callback_ptr->on_message(msg, false);

			return ret == dispatcher_error_no_error;
		}

		bool post_message(Message msg)
		{
			scoped_lock lock(m_message_queue_lock);
			if(m_message_enabled)
				m_msg_queue.push_back(msg);
			else
				return false;

			m_msg_sem.release();
			return true;
		}

		bool is_empty()
		{
			scoped_lock lock(m_message_queue_lock);
			bool ret = m_msg_queue.empty();
			return ret;
		}

		bool add_handle(handler hdl)
		{
			if(m_handle_count < dispatcher_handler_table_size - 1)
			{
				m_handle_table[m_handle_count] = hdl;
				m_handle_count++;
				m_continue_event.set();
				return true;
			}

			return false;
		}

		bool remove_handle(handler hdl)
		{
			int i;
			for(i=0; i<m_handle_count; i++)
			{
				if(m_handle_table[i] == hdl)
				{
					break;
				}
			}

			if(i<m_handle_count)
			{
				m_handle_count--;
				for(int j=i; j<m_handle_count; j++)
				{
					m_handle_table[j] = m_handle_table[j+1];
				}
				m_continue_event.set();
				return true;
			}

			return false;
		}

		void exit()
		{
			if(!m_thread.is_running())
				return;

			m_exit_event.set();
		}

#ifdef _DEBUG
		void setDebugFlag(std::string& szFlag) {
			m_szName = szFlag;
		}
#endif

	protected:
		void enable_message(bool enable = true)
		{
			scoped_lock lock(m_message_queue_lock);
			m_message_enabled = enable;
		}

		bool get_message(Message* msg_ptr)
		{
			scoped_lock lock(m_message_queue_lock);
			if(m_msg_queue.size() == 0)
			{
				msg_ptr = NULL;
				return false;
			}
			*msg_ptr = m_msg_queue.front();
			m_msg_queue.pop_front();
			return true;
		}

		void  pour_message()
		{
			//#ifdef SHOW_DEBUG_INFO
			//		cout << "dispatcher::pour_message" << endl;
			//#endif
			while(m_msg_sem.trywait())
			{
				//#ifdef SHOW_DEBUG_INFO
				//			cout << "dispatcher::pour_message: waited message" << endl;
				//#endif
				Message msg;
				if(get_message( &msg ) && m_callback_ptr)
					m_callback_ptr->on_message(msg, true);
			}

			assert(m_msg_queue.size() == 0);
		}	

		long thread_func(void* param)
		{
			long ret = 0;
			add_handle( m_exit_event );
			add_handle( m_msg_sem );
			add_handle (m_continue_event);

			enable_message();
			//#ifdef SHOW_DEBUG_INFO
			//		cout << "dispatcher::thread_func: " << endl;
			//#endif
			if(m_callback_ptr)
				ret = m_callback_ptr->on_threadstart(param);
			if(ret != 0)
			{
				enable_message(false);
				pour_message();
				return ret;
			}

			while(true)
			{
				int index = wait_for_multiple_events( m_handle_table, m_handle_count );
				if(index == -1)
				{
					ret = dispatcher_error_wait_failed;
					break;
				}

				if(m_handle_table[index] == m_exit_event)
				{
					ret = dispatcher_error_exit_event;
					break;
				}
				else if( m_handle_table[index] == m_msg_sem )
				{
					Message msg;
					get_message( &msg );
					if(m_callback_ptr)
					{
						ret = m_callback_ptr->on_message(msg, false);
					}
					if(ret != dispatcher_error_no_error)
					{
						break;
					}
				}
				else if ( m_handle_table[index] == m_continue_event )
				{
					continue;
				}
				else
				{
					if(m_callback_ptr)
					{
						ret = m_callback_ptr->on_event( m_handle_table[index] );
					}

					if(ret != dispatcher_error_no_error)
					{
						break;
					}
				}
			}

			// Must before on_thradstop() func!
			pour_message();

			if(m_callback_ptr)
				ret = m_callback_ptr->on_threadstop(param);

			remove_handle( m_exit_event );
			remove_handle( m_msg_sem );
			remove_handle ( m_continue_event );
			m_exitok_event.set();

			return ret;
		}

	private:
		dispatcher_callback<Message>*	m_callback_ptr;
		thread_core<dispatcher>			m_thread;
		std::list<Message>				m_msg_queue;
		handler 						m_handle_table[dispatcher_handler_table_size];
		event							m_exit_event;
		event							m_exitok_event;
		int								m_handle_count;
		bool							m_message_enabled;
		mutex							m_message_queue_lock;
#ifdef _DEBUG
		std::string						m_szName;
#endif
		timedsem						m_msg_sem;
		event							m_continue_event;
	};

} // namespace XYCTOOLS

#endif//__DISPATCHER_H__
