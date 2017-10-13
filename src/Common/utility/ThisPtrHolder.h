/********************************************************************
	purpose:	BOOST智能指针使用的辅助类
*********************************************************************/
#ifndef  __QNACSDK_THIS_PTR_HOLDER_H__
#define  __QNACSDK_THIS_PTR_HOLDER_H__

#include <boost\smart_ptr.hpp>


namespace CommonTools
{
	
template<class T>
class ThisPtrHolder
{
public:
	ThisPtrHolder() {}

private:
	ThisPtrHolder( const ThisPtrHolder& other );	// not implemented
	ThisPtrHolder& operator = ( const ThisPtrHolder& other ); 	// not implemented

public:
	typedef boost::shared_ptr<T>	PtrType; 
	typedef boost::weak_ptr<T>		WPtrType; 
	
	PtrType getThisPtr() const 
	{
		PtrType pThis = m_pThis.lock();
		assert( pThis );
		return  pThis;
	}

protected:
	void setThisPtr( PtrType pThis ) 
	{ 
		assert( pThis.get() == static_cast<T*>( this ) );
		m_pThis = pThis; 
	}

private:
	WPtrType m_pThis;	
};


} // namespace MDIPSDK

#endif
