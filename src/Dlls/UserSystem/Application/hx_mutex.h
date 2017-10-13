#ifndef HX_MUTEX_HPP
#define HX_MUTEX_HPP

#include "windows.h"

namespace AllTrade
{
	class CHxMutex
	{
	public:
		CHxMutex();
		~CHxMutex();
		//  º”À¯
		void Lock();
		//   Õ∑≈À¯
		void Unlock();
		//  ≥¢ ‘º”À¯
		bool TryLock();
	private:
		CRITICAL_SECTION critical_section_;
	};


	class CHxMutexGuard
	{
	public:
		CHxMutexGuard(CHxMutex *mutex = 0);
		~CHxMutexGuard();
	private:
		CHxMutex *mutex_;
	};
}

#endif  //  HX_MUTEX_HPP