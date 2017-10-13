/******************************************************************************
 * File: synch.cpp
 *
 * Permission to use, copy, modify, distribute and sell this software
 * and its documentation for any purpose is hereby granted without fee,
 * provided that the above copyright notice appear in all copies and
 * that both that copyright notice and this permission notice appear
 * in supporting documentation.  XXXX makes no
 * representations about the suitability of this software for any
 * purpose.  It is provided "as is" without express or implied warranty.
 *
 *****************************************************************************/

#include "sync.h"

namespace CommonTools
{
	///////////////////////////////////////////////////////////////////////////////
	// wait_for_multiple_events
#ifdef _MSC_VER

	int wait_for_multiple_events( handler events[], int count, bool wait_all)
	{
        try {
    		handle test_events[max_handler_array_size];
            for (int i = 0; i < count; ++i)
			    test_events[i] = handle(events[i]);
        } catch (...) {
            return -1;
        }
//    handle* _events = new handle[count];
		assert( count < (int)max_handler_array_size );
		handle _events[max_handler_array_size];
		for(int i=0; i<count; ++i)
			_events[i] = handle(events[i]);
		int ret = (int)WaitForMultipleObjects( count, _events, wait_all?TRUE:FALSE, INFINITE );
//    delete [] _events;
		return ret;
	}

#elif defined(__GNUC__)

	int wait_for_multiple_events( handler events[], int count)
	{
		int index = -1;
		int i;

		fd_set rset;
		FD_ZERO( &rset );
		int max_fd = 0;
		for(int i=0; i<count; i++)
		{
			if( events[i] > max_fd ) max_fd = events[i];
			FD_SET( events[i], &rset );
		}

		//while( 1 )
		{
#ifdef SHOW_DEBUG_INFO
			cout << "waiting for multiple objects..." << endl;
#endif
			int ret = select( max_fd+1, &rset, NULL, NULL, NULL );
			if( ret == -1 )
				return -1;
			else if( ret == 0 )
				return -1; //WAIT_TIMEOUT
			else
			{
				for(int i=0; i<count; i++)
				{
					if( FD_ISSET( events[i], &rset ) )
					{
						events[i].sync();
						return i;
					}
				}
			}

		}

		return -1;
	}
#endif

	///////////////////////////////////////////////////////////////////////////////
	// wait_for_multiple_events_timed
#ifdef _MSC_VER

	int wait_for_multiple_events_timed( handler events[], int count, int timeout, bool wait_all)
	{
		assert( count < (int)max_handler_array_size );
		handle _events[max_handler_array_size];
		for(int i=0; i<count; ++i)
			_events[i] = handle(events[i]);
		DWORD ret =  WaitForMultipleObjects( (DWORD)count, _events, wait_all?TRUE:FALSE, (DWORD)timeout );

		if (ret == WAIT_TIMEOUT)
			return count;
		return (int)ret;
	}

#elif defined(__GNUC__)
#	error implement wait_for_multiple_events_timed(...) function!
#endif

} // namespace CommonTools
