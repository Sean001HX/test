/*************************************************
Copyright (C), 2017, HX Tech Co., Ltd.
File name:      tradehandler.h
Author:			XuYC
Version:
Date:
Description:    提供成交操作,将数据与操作分离
                成交依旧为对委托操作,故内部存储的仍为委托对象
*************************************************/

#ifndef __TRADE_HANDLER_H__
#define __TRADE_HANDLER_H__

#include <memory>
#include <boost/noncopyable.hpp>
#include "define/struct_declare.h"
#include "utility/rwmutex.h"
#include "define/params_declare.h"
#include "../Application/trade_handler_declare.h"

namespace AllTrade {
    namespace NPTradeCenter {
        // 成交信息操作基类
        class TradeBaseHandler : public std::enable_shared_from_this<TradeBaseHandler>
        {
        public:
            TradeBaseHandler(const TradeInfoPtr& trade_ptr, const UserIDType use_id);
            virtual ~TradeBaseHandler(){}

            // 基础数据操作相关的操作
        public:
            // 获取成交ID
            const PTradeIDType getTradeID() const;
            // 获取持仓ID
            const PPositionIDType getPositionID() const;
            void setPositionID(const PositionIDType positionID);
            // 获取委托流号
            const POrderIDType getOrderStream() const;
            // 获取委托流号
            const PSystemIDType getOrderSystemID() const;
            // 获取下单用户ID
            const PUserIDType getUserID() const;
            // 获取交易所ID
            const PExchangeIDType getExchangeID() const;
            // 获取合约ID
            const PContractIDType getContractID() const;
            // 获取成交日期时间
            const PDateTimeType getGenerateDatetime() const;
            // 获取成交手数
            int getTradeVol() const;
            // 获取买卖方向
            DirectType getDirect() const;
            // 获取汇率
            YDouble getCurrencyRate() const;
            // 获取币种ID
            const PCurrencyIDType getCurrencyID() const;
            // 获取成交价
            YDouble getTradePrice() const;
            // 获取平仓盈亏
            YDouble getCloseProfit() const;
            // 获取商品类型
            CommodityTypeType getCommodityType() const;
            // 获取操作员类型
            OperatorTradeType getOperatorType() const;
            // 获取持仓成本
            virtual YDouble getPositionCost() const { return 0; };
            // 获取持仓均价
//             YDouble getPositionAvePrice() const;

            bool isValid() const;

            // 序列化
            // 注: 此时序列化的为既成历史内容,且必须确保写入成功
            virtual ErrorCodeType serialize();

            // 获取成交拷贝信息
            virtual TradeInfoPtr getTradeInfoCopy() const = 0;

        protected:
            UserIDType                  m_user_id;          // 用户ID
            TradeInfoPtr                m_trade_ptr;        // 成交信息指针
            mutable rwMutex             m_mtx;              // 数据读写锁
        };

        // 股票成交信息操作
        class StockTradeHandler
            : public TradeBaseHandler
            , public boost::noncopyable
        {
        public:
            StockTradeHandler(const StockTradePtr& stock_trade_ptr, const UserIDType use_id);
            ~StockTradeHandler(){}

            // 获取成交信息结构体
            StockTradeInfo getTradeInfo() const;

            // 获取成交拷贝信息
            TradeInfoPtr getTradeInfoCopy() const override;

            YDouble getPositionCost() const override;

            // 获取交易佣金手续费
            YDouble getTradeCommissionFee() const;
            // 获取平仓印花税
            YDouble getStampFee() const;
            // 获取过户费
            YDouble getTransferFee() const;
            // 获取信息撮合费
            YDouble getInfoMatchFee() const;

        };

        // 外盘期货成交信息操作
        class ForeignFutureTradeHandler
            : public TradeBaseHandler
            , public boost::noncopyable
        {
        public:
            ForeignFutureTradeHandler(const ForeignFutureTradePtr& ffuture_trade_ptr, const UserIDType use_id);
            ~ForeignFutureTradeHandler(){}

            // 获取品种ID
            const PProductIDType getProductID() const;

            // 获取成交信息结构体
            ForeignFutureTradeInfo getTradeInfo() const;

            // 获取成交拷贝信息
            TradeInfoPtr getTradeInfoCopy() const override;

        };

        // 内盘期货成交信息操作
        class ChinaFutureTradeHandler
            : public TradeBaseHandler
            , public boost::noncopyable
        {
        public:
            ChinaFutureTradeHandler(const ChinaFutureTradePtr& cfuture_trade_ptr, const UserIDType use_id);
            ~ChinaFutureTradeHandler(){}

            // 获取品种ID
            const PProductIDType getProductID() const;
            // 获取开平标志
            const OffsetType getOffsetType() const;

            // 获取成交信息结构体
            ChinaFutureTradeInfo getTradeInfo() const;

            // 获取成交拷贝信息
            TradeInfoPtr getTradeInfoCopy() const override;

        };


		// 融资成交信息操作
		class MarginTradeHandler
			: public TradeBaseHandler
			, public boost::noncopyable
		{
		public:
			MarginTradeHandler(const MarginTradeInfoPtr& margin_trade_ptr, const UserIDType use_id);
			~MarginTradeHandler(){}

			// 获取成交信息结构体
			MarginTradeInfo getTradeInfo() const;

			// 获取成交拷贝信息
			TradeInfoPtr getTradeInfoCopy() const override;

		};
    }
}

#endif