/*************************************************
Copyright (C), 2017, HX Tech Co., Ltd.
File name:      positionhandler.h
Author:			XuYC
Version:
Date:
Description:    提供持仓操作,将数据与操作分离
*************************************************/

#ifndef __POSITION_HANDLER_H__
#define __POSITION_HANDLER_H__

#include <memory>
#include <boost/noncopyable.hpp>
#include "define/struct_declare.h"
#include "utility/rwmutex.h"
#include "define/params_declare.h"
#include "../Application/trade_handler_declare.h"

namespace AllTrade {
    namespace NPTradeCenter {

        // 持仓信息操作基类
        class PositionBaseHandler
        {
        protected:
            PositionBaseHandler(const PositionInfoPtr& position_ptr, const UserIDType user_id);
            PositionBaseHandler(const TradeHrPtr& trade_hr);
        public:
            virtual ~PositionBaseHandler(){}

            // 基础数据操作相关的操作
        public:
            // 获取持仓ID
            const PPositionIDType getPositionID() const;
            // 获取下单用户ID
            const PUserIDType getUserID() const;
            // 获取交易所ID
            const PExchangeIDType getExchangeID() const;
            // 获取合约ID
            const PContractIDType getContractID() const;
            // 获取持仓手数
            int getPositionAllVol() const;
            // 获取持仓手数
            int getPositionVol() const;
            // 获取T+1持仓手数
            int getPositionVol_T() const;
            // 获取可平仓手数
            int getCanCloseVol() const;
            // 增加冻结可平仓手数
            bool addFreezeVol(int vol);
            // 获取买卖方向
            DirectType getDirect() const;
            // 获取币种ID
            const PCurrencyIDType getCurrencyID() const;
            // 获取成交均价
            YDouble getTradeAvePrice() const;
            // 获取持仓成本
            YDouble getPositionCost() const;
            // 获取商品类型
            CommodityTypeType getCommodityType() const;
            // 获取持仓市值
            YDouble getLastPrice() const;
            // 获取持仓盈亏
            YDouble getProfit() const;

            // 判断是否有效
            bool isValid() const;

            // 更新行情最新价
            void updateQuoteLastPrice(YDouble last_quote);

            // 序列化
            // 注: 此时序列化的为既成历史内容,且必须确保写入成功
            virtual ErrorCodeType serialize();

            virtual void addTradeInfo(const TradeHrPtr& trade_hr_ptr) = 0;

            // 检查持仓状态,是否需要从队列中删除;若满足删除条件则从队列中删除
            virtual void checkPositionStatus() = 0;

            // 获取持仓拷贝
            virtual PositionInfoPtr getPositionCopy() const = 0;

            // 结算持仓
            void settlePosition();

        protected:
            virtual void createByTradeHr(const TradeHrPtr& trade_hr);

        protected:
            mutable rwMutex             m_mtx_quote;        // 行情数据读写锁
            YDouble                     m_last_quote;       // 持仓行情最新价

            UserIDType                  m_user_id;          // 用户ID
            PositionInfoPtr             m_position_ptr;     // 持仓信息指针
            mutable rwMutex             m_mtx;              // 数据读写锁
            bool                        m_is_modify;        // 是否被修改
        };

        // 股票持仓信息操作
        class StockPositionHandler
            : public PositionBaseHandler
            , public std::enable_shared_from_this<StockPositionHandler>
            , public boost::noncopyable
        {
        public:
            StockPositionHandler(const StockPositionPtr& position_ptr, const UserIDType user_id);
            StockPositionHandler(const TradeHrPtr& trade_hr);
            ~StockPositionHandler(){}

            void addTradeInfo(const TradeHrPtr& trade_hr_ptr) override;

            // 检查持仓状态,是否需要从队列中删除;若满足删除条件则从队列中删除
            void checkPositionStatus() override;

            PositionInfoPtr getPositionCopy() const override;

        private:
            void createByTradeHr(const TradeHrPtr& trade_hr) override;
        };

        // 外盘期货持仓信息操作
        class ForeignFuturePositionHandler
            : public PositionBaseHandler
            , public std::enable_shared_from_this<ForeignFuturePositionHandler>
            , public boost::noncopyable
        {
        public:
            ForeignFuturePositionHandler(const TradeHrPtr& trade_hr);
            ~ForeignFuturePositionHandler(){}

            void addTradeInfo(const TradeHrPtr& trade_hr_ptr) override;

            // 检查持仓状态,是否需要从队列中删除;若满足删除条件则从队列中删除
            void checkPositionStatus() override {}

            // 获取品种ID
            const PProductIDType getProductID() const;

            PositionInfoPtr getPositionCopy() const override;
        };

        // 内盘期货持仓信息操作
        class ChinaFuturePositionHandler
            : public PositionBaseHandler
            , public std::enable_shared_from_this<ChinaFuturePositionHandler>
            , public boost::noncopyable
        {
        public:
            ChinaFuturePositionHandler(const TradeHrPtr& trade_hr);
            ~ChinaFuturePositionHandler(){}

            void addTradeInfo(const TradeHrPtr& trade_hr_ptr) override;

            // 检查持仓状态,是否需要从队列中删除;若满足删除条件则从队列中删除
            void checkPositionStatus() override {}

            // 获取品种ID
            const PProductIDType getProductID() const;
            // 获取开平标志
            const OffsetType getOffsetType() const;

            PositionInfoPtr getPositionCopy() const override;
        };


		// 融券信息操作
		class MarginPositionHandler
			: public PositionBaseHandler
			, public std::enable_shared_from_this<MarginPositionHandler>
			, public boost::noncopyable
		{
		public:
			MarginPositionHandler(const MarginPositionInfoPtr& position_ptr, const UserIDType user_id);
			MarginPositionHandler(const TradeHrPtr& trade_hr);
			~MarginPositionHandler(){}

			void addTradeInfo(const TradeHrPtr& trade_hr_ptr) override;

			// 检查持仓状态,是否需要从队列中删除;若满足删除条件则从队列中删除
			void checkPositionStatus() override;

			PositionInfoPtr getPositionCopy() const override;

		private:
			void createByTradeHr(const TradeHrPtr& trade_hr) override;
		};
    }
}

#endif