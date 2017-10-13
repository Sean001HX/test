/*************************************************
Copyright (C), 2017, HX Tech Co., Ltd.
File name:      OnlineUserManager.h
Author:			XuYC
Version:
Date:
Description:    提供在线用户管理中心
*************************************************/

#ifndef __ONLINE_USER_MANAGER_H__
#define __ONLINE_USER_MANAGER_H__

#include <map>
#include "utility/instance_shared_from_this.h"
#include "utility/rwmutex.h"
#include "define/struct_declare.h"
#include "define/params_declare.h"

namespace AllTrade {

        class OnlineUserManager : public CommonTools::instance_shared_from_this<OnlineUserManager>
        {
        public:
            OnlineUserManager();
            ~OnlineUserManager();

            void addLoginUser(const NPMgrCenter::SOnlineAccountPtr& ptr);
            void removeLoginUser(int session_id);

            NPMgrCenter::SOnlineAccountPtr getLoginInfo(int sess_id) const;

        private:
            // session_id, ptr
            std::map<int, NPMgrCenter::SOnlineAccountPtr>            m_sess_user;
            mutable rwMutex                                          m_mtx;
        };
}

#endif