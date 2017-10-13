/*************************************************
Copyright (C), 2017, HX Tech Co., Ltd.
File name:      tradeapibase.h
Author:			XuYC
Version:
Date:
Description:    ����api����,C++11֧���麯����ָ̬��
*************************************************/

#ifndef __TRADE_API_BASE_H__
#define __TRADE_API_BASE_H__

#if defined(_MSC_VER) && (_MSC_VER < 1700)
#error "�������汾������VS2012������!"
#endif

#include <vector>
#include <string>
#include "define/trade_params_declare.h"
#include "define/trade_struct_declare.h"

namespace AllTrade {

    // ����Api����
    class CTradeApiBase
    {
    public:
        CTradeApiBase(CommodityTypeType type);
        virtual ~CTradeApiBase(){}

    public:
        // �˳�
        virtual void quit() = 0;
        // ��¼����
        virtual void login() = 0;
        // �µ�
        virtual void placeOrder(const OrderInfoPtr& order_info_ptr) = 0;
        // ����
        virtual void cancelOrder(const CancelOrderInfoPtr& cancel_order_info_ptr) = 0;
        // ��ѯ�ʽ�״��
        virtual void queryMoney() const = 0;
        // ��ȡί�м�¼
        virtual void getOrderRecord() const = 0;
        // ��ȡ�ɽ���¼
        virtual void getTradeRecord() const = 0;
        // ��ȡ�ֲּ�¼
        virtual void getPositionRecord() const = 0;

    protected:
        CommodityTypeType currentType() const;

    private:
        CommodityTypeType m_type;
    };

    // ��Ʊ����ϵͳ
    class StockTradeApi : public CTradeApiBase
    {
    public:
        StockTradeApi();
        virtual ~StockTradeApi(){}

    public:
        // �˳�
        void quit() override;
        // ��¼����
        void login() override;
        // �µ�
        void placeOrder(const OrderInfoPtr& order_info_ptr) override;
        // ����
        void cancelOrder(const CancelOrderInfoPtr& cancel_order_info_ptr) override;
        // ��ѯ�ʽ�״��
        void queryMoney() const override;
        // ��ȡί�м�¼
        void getOrderRecord() const override;
        // ��ȡ�ɽ���¼
        void getTradeRecord() const override;
        // ��ȡ�ֲּ�¼
        void getPositionRecord() const override;

    };
}

#endif