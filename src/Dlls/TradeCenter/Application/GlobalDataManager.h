/*************************************************
Copyright (C), 2017, HX Tech Co., Ltd.
File name:      GlobalDataManager.h
Author:			XuYC
Version:
Date:
Description:    提供全局数据的序列化与反序列化操作接口
*************************************************/

#ifndef _GLOBALDATAMANAGER_H_
#define _GLOBALDATAMANAGER_H_

#include <boost/noncopyable.hpp>
#include "utility/instance_shared_from_this.h"
#include "define/params_declare.h"
#include "define/struct_declare.h"
#include "utility/rwmutex.h"

namespace AllTrade {
    namespace NPTradeCenter {
        class GlobalDataManager
            : public CommonTools::instance_shared_from_this<GlobalDataManager>
            , public boost::noncopyable
        {
        public:
            GlobalDataManager();
            ~GlobalDataManager();

            PShadowOrderIDType getCurShadowOrderID_c();

            PShadowOrderIDType getCurShadowTradeID_c();

            void settle();

        private:
            int getCurShadowTradeID();
            int getCurShadowOrderID();
            void serialize();

        private:
            rwMutex                 m_mtx_order;
            rwMutex                 m_mtx_trade;
            GlobalDataPtr           m_global_data;
        };
    }
}

#endif