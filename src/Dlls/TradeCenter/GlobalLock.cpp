#include "GlobalLock.h"

namespace AllTrade 
{
	CGlobalLock::CGlobalLock()
	{
	}


	CGlobalLock::~CGlobalLock()
	{
	}

	void CGlobalLock::lock(const AllTrade::PUserIDType& user_id_)
	{
		m_userid_mtx_[user_id_].lock();
	}

	void CGlobalLock::unlock(const AllTrade::PUserIDType& user_id_)
	{
		m_userid_mtx_[user_id_].unlock();
	}

}
