/*************************************************
Copyright (C), 2017, HX Tech Co., Ltd.
File name:      orderhandler.h
Author:			XuYC
Version:
Date:
Description:    提供下单委托操作,将数据与操作分离
                委托操作是整个交易的核心,故撤单/成交消息中存储的也是委托操作
*************************************************/

#ifndef __ORDER_HANDLER_H__
#define __ORDER_HANDLER_H__

#include <string>
#include <memory>
#include <mutex>
#include <atomic>
#include <boost/noncopyable.hpp>
#include "define/struct_declare.h"
#include "utility/rwmutex.h"
#include "define/params_declare.h"
#include "../Application/trade_handler_declare.h"
#include "define/protocol_error.h"

namespace AllTrade {
    namespace NPTradeCenter {

        // 下单委托操作基类
        class OrderBaseHandler : public std::enable_shared_from_this<OrderBaseHandler>
        {
        public:
            OrderBaseHandler(const OrderInfoPtr& order_ptr, const UserIDType use_id, const NPMgrCenter::SOnlineAccountPtr& user_online);
            virtual ~OrderBaseHandler();

            // 基础数据操作相关的操作
        public:
            // 设置/获取下单委托ID
            const POrderIDType getOrderID() const;
            void setOrderID(const OrderIDType order_id);
            // 获取系统委托ID
            PSystemIDType getSystemOrderID();
            void setSystemOrderID(const SystemIDType sys_order_id);
            // 获取下单委托本地委托编号类型
            const POrderRefType getOrderRef() const;
            void setOrderRef(const OrderRefType order_ref);
            // 获取下单用户ID
            const PUserIDType getUserID() const;
            // 获取合约ID
            const PContractIDType getContractID() const;
            // 设置/获取委托状态
            OrderStateType getOrderState() const;
            void setOrderState(OrderStateType order_state);
            // 获取委托状态说明
            OrderStateExplainType getOrderStateExplain() const;
            // 获取下单委托提交编号,创建委托操作时生成,不得修改
            const POrderStreamType getOrderStream() const;
            // 设置/获取影子订单编号
            const PShadowOrderIDType getShadowOrderID() const;
            void setShadowOrderID(const ShadowOrderIDType shadoworder_id);
            // 委托创建日期时间
            const PDateTimeType getGenerateDatetime() const;
            // 委托状态最后更新日期时间
            const PDateTimeType getUpdateDatetime() const;
            // 获取汇率
            YDouble getCurrencyRate() const;
            // 获取委托币种ID
            const PCurrencyIDType getCurrencyID() const;
            // 获取委托价格
            YDouble getOrderPrice(const CurrencyIDType currency_id) const;
            YDouble getOrderPrice() const;
            void setOrderPrice(YDouble order_price);
            // 获取买卖方向
            DirectType getDirect() const;
            // 获取委托手数
            int getOrderVol() const;
            // 获取已成交手数
            int getTradeVol() const;
            // 新增已成交手数,返回新增结果
            bool addTradeVol(int vol);
            void setTradeVol(int vol);
            // 获取已生效手数
            int getEffectVol() const;
            // 新增有效手数,返回新增结果
//             bool addEffectVol(int vol);
            // 获取下单委托类型(限价/市价/...),后续添加改单功能时,需要添加读锁
            OrderTypeType getOrderType() const;
            void setOrderType(OrderTypeType type);
            // 获取委托交易模式,是否需要同步真实交易所
            OrderTradeModeType getOrderTradeMode() const;
            // 获取委托成交价
            YDouble getOrderTradePrice(const CurrencyIDType currency_id) const;
            YDouble getOrderTradePrice() const;
            // 获取持仓成本
            YDouble getPoitionCost() const;
            // 获取冻结资金
            YDouble getFreezeMoney() const;
            // 获取实盘对应委托ID
            const PSystemIDType getSystemID() const;
            // 获取交易所ID
            const PExchangeIDType getExchangeID() const;
            // 获取接口类型(CTP/ESUNNY/...)
            ApiTypeType getApiType() const;
            // 获取商品类型
            CommodityTypeType getCommodityType() const;
            // 获取操作员类型
            OperatorTradeType getOperatorType() const;
            // 获取下单委托模式(FAK/...)
            OrderModeType getOrderMode() const;
            // 获取有效日期(GTD情况下使用)
            const PDateTimeType getValidDatetime() const;

            // 获取下单用户登录信息
            const NPMgrCenter::SOnlineAccountPtr& getOpUserLoginInfo() const{
                return m_user_online;
            }
            //////////////////////////////////////////////////////////////////////////
            // 有效数据判断

            // 获取委托是否有效
            virtual ErrorCodeType isOrderValid() const;
            // 是否委托时间
            virtual bool isOrderTime() const;
            // 是否交易时间
            virtual bool isTradeTime() const;
            // 是否可提交该交易
            virtual ErrorCodeType canOrder() const;
            // 委托是否可执行该交易(白名单/只允许平仓则可以平仓/风控等所有判断)
            virtual ErrorCodeType canTrade() const;
            // 获取委托提交时的冻结费用
            YDouble getOrderFreezeFee(const QuoteHrPtr& quote_ptr) const;
            // 委托是否可撤销
            virtual ErrorCodeType canCancelOrder() const;

            //////////////////////////////////////////////////////////////////////////
            // 资金与持仓

            // 冻结账户资金
            virtual ErrorCodeType freezeMoney() { return Err_Unknown; }
            // 冻结账户持仓
            virtual ErrorCodeType freezePosition() { return Err_Unknown; }
            // 解冻账户资金
            virtual ErrorCodeType thawMoney() { return Err_Unknown; }
            // 解冻账户持仓
            virtual ErrorCodeType thawPosition() { return Err_Unknown; }

            // 序列化
            virtual ErrorCodeType serialize();

            //////////////////////////////////////////////////////////////////////////
            // 成交与撤单

            // 模拟成交, 返回是否需要继续处理,若不需要继续处理则返回false
            bool simulateTrade(const QuoteHrPtr& quote_ptr);

            // 模拟撤销委托
            void simulateCancelOrder();

            // 检查委托成交状态,是否需要从队列中删除;若满足删除条件则从队列中删除
            void checkOrderTradeStatus();

            // 获取委托拷贝信息
            virtual OrderInfoPtr getOrderInfoCopy() const = 0;

            // 实盘成交
            virtual void realTrade(const TradeInfoPtr& trade_ptr);

            // 根据成交基础数值与当前委托状态修改成交手续费等参数
            virtual void generateTradeFeeVarious(const TradeInfoPtr& trade_ptr){ assert(0); }

       protected:
            //通过委托与行情生成成交信息
            virtual TradeInfoPtr createTradeByQuote(const QuoteInfoPtr& quote_info_ptr, int trade_vol, TradeInfoPtr trade_ptr_self = nullptr) const;

       private:
            // 根据最新行情,判断委托是否成交
            virtual bool matchQuote(const QuoteInfoPtr& quote_ptr) const;
            bool isSerializing();

         protected:
             // 获取开仓总手续费
            YDouble getUserOpenFee(DirectType direct, YDouble all_money, int vol) const;
            // 获取开仓交易佣金
            YDouble getUserTradeCommissionFee(YDouble all_money) const;

        protected:
            UserIDType          m_user_id;              // 用户ID
            OrderInfoPtr        m_order_ptr;            // 委托信息指针

            NPMgrCenter::SOnlineAccountPtr   m_user_online;      // 下单用户登录信息,非系统下单错误时需要返回提示

            mutable rwMutex     m_mtx;          // 数据读写锁
            std::mutex          m_status_mtx;   // 委托状态数据锁(用于成交与撤单同步)

            bool                m_is_modify;    // 是否被修改
        };

        // 股票下单委托操作
        class StockOrderHandler
            : public OrderBaseHandler
            , public boost::noncopyable
        {
        public:
            StockOrderHandler(const StockOrderPtr& order_ptr, const UserIDType use_id, const NPMgrCenter::SOnlineAccountPtr& user_online);
            ~StockOrderHandler(){}

            StockAreaType getStockAreaType() const;

            // 获取委托是否有效
            virtual ErrorCodeType isOrderValid() const override;

            // 冻结账户资金
            virtual ErrorCodeType freezeMoney() override;
            // 冻结账户持仓
            virtual ErrorCodeType freezePosition() override;
            // 解冻账户资金
            virtual ErrorCodeType thawMoney() override;
            // 解冻账户持仓
            virtual ErrorCodeType thawPosition() override;

            // 获取委托拷贝信息
            OrderInfoPtr getOrderInfoCopy() const override;

            // 实盘成交
            void realTrade(const TradeInfoPtr& trade_ptr) override;

            // 根据成交基础数值与当前委托状态修改成交手续费等参数
            void generateTradeFeeVarious(const TradeInfoPtr& trade_ptr) override;

        protected:
            //通过委托与行情生成成交信息
            TradeInfoPtr createTradeByQuote(const QuoteInfoPtr& quote_info_ptr, int trade_vol, TradeInfoPtr trade_ptr_self = nullptr) const override;

            // 获取委托信息
            StockOrderInfo getOrderInfo() const;

        };

        // 外盘期货下单委托操作
        class ForeignFutureOrderHandler
            : public OrderBaseHandler
            , public boost::noncopyable
        {
        public:
            ForeignFutureOrderHandler(const ForeignFutureOrderPtr& order_ptr, const UserIDType use_id, const NPMgrCenter::SOnlineAccountPtr& user_online);
            ~ForeignFutureOrderHandler(){}

            // 获取委托是否有效
            virtual ErrorCodeType isOrderValid() const override;
            // 获取委托拷贝信息
            OrderInfoPtr getOrderInfoCopy() const override;
            // 获取品种ID
            const PProductIDType getProductID() const;
            // 获取委托信息
            ForeignFutureOrderInfo getOrderInfo() const;

        protected:
            //通过委托与行情生成成交信息
            TradeInfoPtr createTradeByQuote(const QuoteInfoPtr& quote_info_ptr, int trade_vol, TradeInfoPtr trade_ptr_self = nullptr) const override;


        };

        // 内盘期货下单委托操作
        class ChinaFutureOrderHandler
            : public OrderBaseHandler
            , public boost::noncopyable
        {
        public:
            ChinaFutureOrderHandler(const ChinaFutureOrderPtr& order_ptr, const UserIDType use_id, const NPMgrCenter::SOnlineAccountPtr& user_online);
            ~ChinaFutureOrderHandler(){}

            // 获取委托是否有效
            virtual ErrorCodeType isOrderValid() const override;
            // 获取委托拷贝信息
            OrderInfoPtr getOrderInfoCopy() const override;
            // 获取品种ID
            const PProductIDType getProductID() const;
            // 获取开平类型
            OffsetType getOffsetType() const;
            // 获取委托信息
            ChinaFutureOrderInfo getOrderInfo() const;

        protected:
            //通过委托与行情生成成交信息
            TradeInfoPtr createTradeByQuote(const QuoteInfoPtr& quote_info_ptr, int trade_vol, TradeInfoPtr trade_ptr_self = nullptr) const override;


        };


		// 下单委托操作
		class MarginOrderHandler
			: public OrderBaseHandler
			, public boost::noncopyable
		{
		public:
			MarginOrderHandler(const MarginOrderInfoPtr& order_ptr, const UserIDType use_id, const NPMgrCenter::SOnlineAccountPtr& user_online);
			~MarginOrderHandler(){}

			// 获取委托是否有效
			virtual ErrorCodeType isOrderValid() const override;
			// 获取委托拷贝信息
			OrderInfoPtr getOrderInfoCopy() const override;
			// 获取委托信息
			MarginOrderInfo getOrderInfo() const;

		protected:
			//通过委托与行情生成成交信息
			TradeInfoPtr createTradeByQuote(const QuoteInfoPtr& quote_info_ptr, int trade_vol, TradeInfoPtr trade_ptr_self = nullptr) const override;

		};


    }
}

#endif