#include "OnlineUserManager.h"
#include "define/struct_base.h"
#include "include/OperationManager/OperationManager.h"

using namespace OperationManager;
using namespace AllTrade::NPMgrCenter;

namespace AllTrade {

        OnlineUserManager::OnlineUserManager()
        {

        }

        OnlineUserManager::~OnlineUserManager()
        {

        }

        void OnlineUserManager::addLoginUser(const SOnlineAccountPtr& ptr)
        {
            if (!ptr)
                return;

            {
                writeLock lock(m_mtx);
                m_sess_user[ptr->session_id_] = ptr;
            }

            COperationManager::instance()->serializeLoginInUser(ptr);
        }

        void OnlineUserManager::removeLoginUser(int session_id)
        {
            SOnlineAccountPtr ptr(nullptr);
            {
                writeLock lock(m_mtx);

                auto iter = m_sess_user.find(session_id);
                if (iter == m_sess_user.end())
                    return;

                ptr = iter->second;
                m_sess_user.erase(iter);
                if (!ptr) return;
            }
            COperationManager::instance()->serializeLoginOutUser(ptr);
        }

        SOnlineAccountPtr OnlineUserManager::getLoginInfo(int sess_id) const
        {
            readLock lock(m_mtx);
            auto iter_id = m_sess_user.find(sess_id);
            if (iter_id != m_sess_user.end())
                return iter_id->second;

            return SOnlineAccountPtr();
        }

}