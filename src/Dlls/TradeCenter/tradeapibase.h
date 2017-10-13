/*************************************************
Copyright (C), 2017, HX Tech Co., Ltd.
File name:      tradeapibase.h
Author:			XuYC
Version:
Date:
Description:    交易api基类,C++11支持虚函数动态指针
*************************************************/

#ifndef __TRADE_API_BASE_H__
#define __TRADE_API_BASE_H__

#if defined(_MSC_VER) && (_MSC_VER < 1700)
#error "编译器版本必须是VS2012或以上!"
#endif

#include <vector>
#include <string>
#include "define/trade_params_declare.h"
#include "define/trade_struct_declare.h"

namespace AllTrade {

    // 交易Api基类
    class CTradeApiBase
    {
    public:
        CTradeApiBase(CommodityTypeType type);
        virtual ~CTradeApiBase(){}

    public:
        // 退出
        virtual void quit() = 0;
        // 登录交易
        virtual void login() = 0;
        // 下单
        virtual void placeOrder(const OrderInfoPtr& order_info_ptr) = 0;
        // 撤单
        virtual void cancelOrder(const CancelOrderInfoPtr& cancel_order_info_ptr) = 0;
        // 查询资金状况
        virtual void queryMoney() const = 0;
        // 获取委托记录
        virtual void getOrderRecord() const = 0;
        // 获取成交记录
        virtual void getTradeRecord() const = 0;
        // 获取持仓记录
        virtual void getPositionRecord() const = 0;

    protected:
        CommodityTypeType currentType() const;

    private:
        CommodityTypeType m_type;
    };

    // 股票交易系统
    class StockTradeApi : public CTradeApiBase
    {
    public:
        StockTradeApi();
        virtual ~StockTradeApi(){}

    public:
        // 退出
        void quit() override;
        // 登录交易
        void login() override;
        // 下单
        void placeOrder(const OrderInfoPtr& order_info_ptr) override;
        // 撤单
        void cancelOrder(const CancelOrderInfoPtr& cancel_order_info_ptr) override;
        // 查询资金状况
        void queryMoney() const override;
        // 获取委托记录
        void getOrderRecord() const override;
        // 获取成交记录
        void getTradeRecord() const override;
        // 获取持仓记录
        void getPositionRecord() const override;

    };
}

#endif