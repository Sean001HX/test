/*
* 一个通用的、采用RAII思想的资源管理类，以及相关的宏定义；也可用于rollback模式；
* 源于："http://blog.csdn.net/pongba/article/details/7911997"。
*/
#pragma once

#include <functional>

#if defined(_MSC_VER) && (_MSC_VER < 1700)
#error "编译器版本必须是VS2012或以上!"
#endif

namespace CommonTools
{
	class ScopeGuard
	{
	public:
		explicit ScopeGuard(std::function<void()> onExitScope) 
			: onExitScope_(onExitScope), dismissed_(false)
		{ }
		
		~ScopeGuard()
		{
			if(!dismissed_)
			{
				onExitScope_();
			}
		}
		
		void Dismiss()
		{
			dismissed_ = true;
		}
		
	private:
		std::function<void()> onExitScope_;
		bool dismissed_;
		
	private: // noncopyable
		ScopeGuard(ScopeGuard const&);
		ScopeGuard& operator=(ScopeGuard const&);
	};

#define SCOPEGUARD_LINENAME_CAT(name, line) name##line
#define SCOPEGUARD_LINENAME(name, line) SCOPEGUARD_LINENAME_CAT(name, line)

#define ON_SCOPE_EXIT(callback) ScopeGuard SCOPEGUARD_LINENAME(EXIT, __LINE__)(callback)

	//! 通用原语CAS操作（Compare-And-Swap）
	//! CAS原语负责比较某个内存地址处的内容与一个期望值，如果比较成功则将该内存地址处的内容替换为一个新值。这整个操作是原子的。	 
	//! 来源于：“锁无关的(Lock-Free)数据结构——在避免死锁的同时确保线程继续”
	template <class T>
	bool CAS(T* addr, T expected, T value) 
	{
		if (*addr == expected) 
		{
			*addr = value;
			return true;
		}
		return false;
	}  

} // namespace CommonTools
