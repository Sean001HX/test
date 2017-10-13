/*************************************************
Copyright (C), 2017, HX Tech Co., Ltd.
File name:      ctrade.h
Author:			XuYC
Version:
Date:
Description:    提供交易模块具体实现接口
*************************************************/
#ifndef __CTRADE_H__
#define __CTRADE_H__

#include <functional>
#include <vector>
#include "define/struct_declare.h"
#include "define/params_declare.h"

namespace AllTrade{
    namespace NPTradeCenter {
        class CTradeCenter
        {
            typedef std::function<void(ErrorCodeType errcode, const UserIDType user_id, const OrderInfoPtr& order_ptr, const NPMgrCenter::SOnlineAccountPtr& user_online)>  OrderInsertCbk;
            typedef std::function<void(ErrorCodeType errcode, const UserIDType user_id, const OrderInfoPtr& order_ptr, const NPMgrCenter::SOnlineAccountPtr& user_online)>  CancelOrderCbk;
            typedef std::function<void(ErrorCodeType errcode, const UserIDType user_id, const OrderInfoPtr& order_ptr)>  OrderChangeCbk;
            typedef std::function<void(ErrorCodeType errcode, const UserIDType user_id, const TradeInfoPtr& trade_ptr)>  TradeCbk;
            typedef std::function<void(ErrorCodeType errcode, const UserIDType user_id, const PositionInfoPtr& position_ptr)>  PositionCbk;
            typedef std::function<void(const UserIDType user_id, const DateTimeType date_time, RiskControlType rc_type, const RemarkTextType remark_text)>  RiskControlCbk;
        
        public:
            CTradeCenter();
            ~CTradeCenter();

            /*
            * @brief: 处理下单委托信息
            * order_ptr: 委托指针
            * use_id: 账户ID
            */
            void handlePlaceOrder(const OrderInfoPtr& order_ptr, const UserIDType use_id, const NPMgrCenter::SOnlineAccountPtr& user_online, bool needRecode);

            /*
            * @brief: 处理撤单委托信息
            * cancel_order_info_ptr: 撤销委托指针
            * use_id: 账户ID
            */
            void handleCancelOrder(CommodityTypeType commodity_type, const UserIDType use_id, const OrderStreamType order_stream, bool needRecode);

            // 更新行情状态
            void changeQuoteStatus(bool bl);

            // 更新行情
            void updateQuote(const QuoteInfoPtr& quote_ptr, const NPMgrCenter::SExchangeCPtr& exchange_ptr, const NPMgrCenter::SContractCPtr& contract_ptr);

            // 获取指定用户当前委托信息
            std::vector<AllTrade::NPTradeCenter::OrderInfoPtr> getCurrentOrderList(const UserIDType user_id);
            // 获取指定用户当日委托信息
            std::vector<AllTrade::NPTradeCenter::OrderInfoPtr> getTodayOrderList(const UserIDType user_id);
            // 获取指定用户历史委托信息
            std::vector<AllTrade::NPTradeCenter::OrderInfoPtr> getHistoryOrderList(const UserIDType user_id, const DateType start_time, const DateType end_time);
            // 获取指定用户成交信息
            std::vector<AllTrade::NPTradeCenter::TradeInfoPtr> getTradeList(const UserIDType user_id);
            // 获取指定用户历史成交信息
            std::vector<AllTrade::NPTradeCenter::TradeInfoPtr> getHistoryTradeList(const UserIDType user_id, const DateType start_time, const DateType end_time);
            // 获取指定用户持仓信息
            std::vector<AllTrade::NPTradeCenter::PositionInfoPtr> getPositionList(const UserIDType user_id);

            // 获取费用设置信息
            AllTrade::NPTradeCenter::TradeFeePtr getFeeSetPtr();
            // 设置费用设置信息
            AllTrade::ErrorCodeType setFeeSetPtr(const AllTrade::NPTradeCenter::TradeFeePtr& ptr);

            // 委托是否有效
            bool canCancelOrder(const UserIDType use_id, const OrderStreamType order_stream);

            // 禁止交易相关
            std::vector<AllTrade::NPTradeCenter::SForbidTradePtr> getAllForbidTradeStatus();
            ErrorCodeType updateForbidTradeStatus(const AllTrade::NPTradeCenter::SForbidTradePtr& ptr);

            // 持仓比例相关
            std::vector<AllTrade::NPTradeCenter::SPositionRatePtr> getAllPositionRateStatus();
            ErrorCodeType updatePositionRateStatus(const AllTrade::NPTradeCenter::SPositionRatePtr& ptr);

            // 重置风控信息
            void recalculate_risk(CommodityTypeType commod_type, const UserIDType user_id);

        public:
            // 注册委托提交通知
            void setOrderInsertCbk(const OrderInsertCbk& fun);
            // 注册撤单回调通知
            void setOrderCancelCbk(const CancelOrderCbk& fun);
            // 注册委托改变通知
            void setOrderChangeCbk(const OrderChangeCbk& fun);
            // 注册成交回调通知
            void setTradeCbk(const TradeCbk& fun);
            // 注册持仓回调通知
            void setPositionCbk(const PositionCbk& fun);
            // 注册风控回调通知
            void setRiskControlCbk(const RiskControlCbk& fun);
        };
    }
}
#endif