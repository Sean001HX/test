/*************************************************
Copyright (C), 2017, HX Tech Co., Ltd.
File name:      struct_extern.h
Author:			XuYC
Version:
Date:
Description:    提供具体的结构体定义,加快编译速度
*************************************************/

#ifndef __STRUCT_EXTERN_H__
#define __STRUCT_EXTERN_H__

#include <memory>
#include "struct_base.h"

namespace AllTrade {
    namespace NPMgrCenter {
#pragma region 账户
        //////////////////////////////////////////////////////////////////////////
        // 根账户
        struct RootAccount : public SAccountBase
        {
            int                 allow_max_level_;   // 允许下设的最大层级
            int                 allow_max_num_;     // 允许下设的最大个数
            
            RootAccount();
        };

        // 机构账户
        struct AgencyAccount : public SAccountBase
        {
            UserIDType          fund_user_id_;    // 资金账户ID

            E_AGENCY_PROP       agency_prop_;          // 机构账户属性(代理商/机构)
            int                 allow_max_level_;   // 允许下设的最大层级
            int                 allow_max_num_;     // 允许下设的最大个数

            AgencyAccount();
        };

        // 风控账户
        struct RiskAccount : public SAccountBase
        {
            RiskAccount();
        };

        // 管理账户
        struct ManagerAccount : public SAccountBase
        {
            ManagerAccount();
        };

        // 交易账户
        struct TradeAccount : public SAccountBase
        {
            TradeAccount();

            UserIDType  fund_user_id_;  // 实盘账户名称
        };

        // 资金账户
        struct FunderAccount : public SAccountBase
        {
            FunderAccount();

            FundCompanyType fund_company_;  // 实盘账户对应公司名称
        };

#pragma endregion

#pragma region 交易所
        struct SStockContract : public SContractBase
        {
            Feest           close_yestoday_fee_;    // 平昨手续费

            ContractPYCodeType      contract_py_code_;
            DisplayPropType         display_prop_;
            DisplayPropTypeType     display_prop_type_;
            PlatePropType           plate_prop_;
            StockAreaType           stock_area_;
            StockStatusType         stock_status_;
            StockPlateAreaType      stock_plate_area_;
            YDouble                 total_shares_;  // 总股本

            SStockContract();
        };

        struct SForeignFutureContract : public SContractBase
        {
            ProductIDType           product_id_;	    // 所属品种ID, 格式：GUID; 在品种的生存期内具有唯一性

            SForeignFutureContract();
        };
#pragma endregion
    }

    namespace NPTradeCenter {
#pragma region 委托
        //////////////////////////////////////////////////////////////////////////
        // 股票下单委托信息
        struct StockOrderInfo : public OrderInfoBase
        {
            StockAreaType   stock_area_;

            YDouble         cur_trade_fee_;     // 当前交易佣金手续费
            YDouble         cur_stamp_fee_;     // 当前平仓印花税费
            YDouble         cur_transfer_fee_;  // 当前过户费
            YDouble         cur_infomatch_fee_; // 当前信息撮合费

            StockOrderInfo();
        };

        // 外盘期货下单委托信息
        struct ForeignFutureOrderInfo : public OrderInfoBase
        {
            ProductIDType   product_id_;    // 品种ID

            ForeignFutureOrderInfo();
        };

        // 内盘期货下单委托信息
        struct ChinaFutureOrderInfo : public OrderInfoBase
        {
            ProductIDType   product_id_;    // 品种ID
            OffsetType      offset_type_;   // 开平类型

            ChinaFutureOrderInfo();
        };
#pragma endregion

#pragma region 成交
        //////////////////////////////////////////////////////////////////////////
        // 股票成交信息
        struct StockTradeInfo : public TradeInfoBase
        {            
            StockAreaType   stock_area_;
            YDouble         trade_fee_;     // 交易佣金手续费
            YDouble         stamp_fee_;     // 平仓印花税
            YDouble         transfer_fee_;  // 过户费
            YDouble         infomatch_fee_; // 信息撮合费

            StockTradeInfo();
        };

        // 外盘期货成交信息
        struct ForeignFutureTradeInfo : public TradeInfoBase
        {
            ProductIDType   product_id_;    // 品种ID

            ForeignFutureTradeInfo();
        };

        // 内盘期货成交信息
        struct ChinaFutureTradeInfo : public TradeInfoBase
        {
            ProductIDType   product_id_;    // 品种ID
            OffsetType      offset_type_;   // 开平类型

            ChinaFutureTradeInfo();
        };
#pragma endregion

#pragma region 持仓
        //////////////////////////////////////////////////////////////////////////
        // 股票持仓信息
        struct StockPositionInfo : public PositionInfoBase
        {
            StockAreaType   stock_area_;

            StockPositionInfo();
        };

        // 外盘期货持仓信息
        struct ForeignFuturePositionInfo : public PositionInfoBase
        {
            ProductIDType   product_id_;    // 品种ID

            ForeignFuturePositionInfo();
        };

        // 内盘期货持仓信息
        struct ChinaFuturePositionInfo : public PositionInfoBase
        {
            ProductIDType   product_id_;    // 品种ID
            OffsetType      offset_type_;   // 开平类型

            ChinaFuturePositionInfo();
        };
#pragma endregion

#pragma region 融券
		// 融券持仓
		struct MarginPositionInfo : public PositionInfoBase
		{
			UserIDType			user_id_;				// 用户ID
			// DateTimeType        datetime_;				// 日期时间
			StockAreaType		stock_area_;

			MarginPositionInfo();;
		};

		// 融券成交
		struct MarginTradeInfo :public TradeInfoBase
		{
			StockAreaType   stock_area_;
			YDouble         trade_fee_;     // 交易佣金手续费
			YDouble         stamp_fee_;     // 平仓印花税
			YDouble         transfer_fee_;  // 过户费
			YDouble         infomatch_fee_; // 信息撮合费
			UserIDType			user_id_;				// 用户ID

			YDouble         day_interset_;  // 日利息
			YDouble         interset_fund_; // 利息资金

			MarginTradeInfo();;
		};

		// 融券委托
		struct MarginOrderInfo : public OrderInfoBase
		{
			UserIDType			user_id_;				// 用户ID
			StockAreaType   stock_area_;

			YDouble         cur_trade_fee_;     // 当前交易佣金手续费
			YDouble         cur_stamp_fee_;     // 当前平仓印花税费
			YDouble         cur_transfer_fee_;  // 当前过户费
			YDouble         cur_infomatch_fee_; // 当前信息撮合费

			MarginOrderInfo();;
		};

		
#pragma endregion

    }
}

#endif