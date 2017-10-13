#ifndef __GLOBAL_LOCK__
#define __GLOBAL_LOCK__

#include "utility/instance_shared_from_this.h"
#include "./Application/trade_handler_declare.h"
#include "define/params_declare.h"
#include <mutex>
#include <map>


namespace AllTrade {
	class CGlobalLock : public CommonTools::instance_shared_from_this<CGlobalLock>
	{
	public:
		CGlobalLock();
		~CGlobalLock();

	public:
		void lock(const AllTrade::PUserIDType& user_id_);
		void unlock(const AllTrade::PUserIDType& user_id_);

	private:
		std::map<AllTrade::PUserIDType, std::mutex >	m_userid_mtx_;
	};
}

#endif
