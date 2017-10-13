/*
* һ��ͨ�õġ�����RAII˼�����Դ�����࣬�Լ���صĺ궨�壻Ҳ������rollbackģʽ��
* Դ�ڣ�"http://blog.csdn.net/pongba/article/details/7911997"��
*/
#pragma once

#include <functional>

#if defined(_MSC_VER) && (_MSC_VER < 1700)
#error "�������汾������VS2012������!"
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

	//! ͨ��ԭ��CAS������Compare-And-Swap��
	//! CASԭ�︺��Ƚ�ĳ���ڴ��ַ����������һ������ֵ������Ƚϳɹ��򽫸��ڴ��ַ���������滻Ϊһ����ֵ��������������ԭ�ӵġ�	 
	//! ��Դ�ڣ������޹ص�(Lock-Free)���ݽṹ�����ڱ���������ͬʱȷ���̼߳�����
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
