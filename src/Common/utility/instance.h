/*
* Purpose: 单实例公共基类,供给基类中含有enable_shared_from_this的继承使用
*/
#ifndef __INSTANCE_H__
#define __INSTANCE_H__

#include <memory>
#include <mutex>

namespace CommonTools
{
	// TEMPLATE CLASS instance_shared_from_this
	template<class _Ty>
	class instance_unshared
	{    // provide member functions that create shared_ptr to this
	public:
		static std::shared_ptr<_Ty> instance()
		{    // return shared_ptr
		    if ( !_pInstance )
		    {
		        // RAII,Resource Acquisition Is Initialization, lock in the constructor, the unlock action in the destructor apparatus
		        std::lock_guard<std::recursive_mutex> lock(_mtx_pres_);
		        if( !_pInstance )
		        {
		            _pInstance = std::make_shared<_Ty>();
		        }
		    }
		 
		    return _pInstance;
		}

		static void unInstance()
		{
			if (_pInstance)
			{
				std::lock_guard<std::recursive_mutex> lock(_mtx_pres_);
				if (_pInstance)
				{
					_pInstance.reset();
				}
			}
		}

	protected:
        instance_unshared() _NOEXCEPT
        {    // construct (do nothing)
        }


        ~instance_unshared() _NOEXCEPT
		{    // destroy (do nothing)
		}

	private:
		static std::shared_ptr<_Ty>  _pInstance; // Instance
		static std::recursive_mutex  _mtx_pres_; // Instance Lock, Achieve thread-safety

	};

	template<class _Ty>
    std::shared_ptr<_Ty> instance_unshared<_Ty>::_pInstance = nullptr;

	template<class _Ty>
    std::recursive_mutex	instance_unshared<_Ty>::_mtx_pres_;

}

#endif