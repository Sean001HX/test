/*************************************************
Copyright (C), 2017, HX Tech Co., Ltd.
File name:      tradelistmanager.h
Author:			XuYC
Version:
Date:
Description:    提供成交操作管理池, 统一成交指针管理
*************************************************/

#ifndef __TRADELISTMANAGER_H__
#define __TRADELISTMANAGER_H__

#include <boost\noncopyable.hpp>
#include <vector>
#include <mutex>
#include <atomic>
#include <boost\multi_index_container.hpp>
#include <boost\multi_index\mem_fun.hpp>
#include <boost\multi_index\ordered_index.hpp>
#include <boost\multi_index\global_fun.hpp>

#include "utility/rwmutex.h"
#include "utility/instance_shared_from_this.h"
#include "../Application/trade_handler_declare.h"
#include "define/params_declare.h"
#include "define/struct_declare.h"

namespace AllTrade {
    namespace NPTradeCenter {

        class TradeListManager
            : public CommonTools::instance_shared_from_this<TradeListManager>
        {
        public:
            TradeListManager();
            ~TradeListManager();

            // 创建成交信息操作
            TradeHrPtr createTradeHr(const TradeInfoPtr& trade_ptr, const OrderInfoPtr& order_ptr, const UserIDType use_id);
        };

    }
}

#endif