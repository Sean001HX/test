/*************************************************
Copyright (C), 2017, HX Tech Co., Ltd.
File name:      DBOpTradeCenter.h
Author:			XuYC
Version:
Date:
Description:    数据库操作- 交易中心相关部分
*************************************************/

#include <string>
#include "define/struct_base.h"
#include "define/struct_declare.h"
#include "define/params_declare.h"
#include <map>


namespace OperationManager{

    class DBOpTradeCenter
    {
    public:
        DBOpTradeCenter();
        ~DBOpTradeCenter();

        // 初始化数据库表
        bool initAllTable();

        // 创建/更新委托信息
        bool updateOrderInfo(const AllTrade::NPTradeCenter::OrderInfoPtr& order_ptr, const AllTrade::UserIDType user_id);

        // 新增成交记录
        bool addTradeRecord(const AllTrade::NPTradeCenter::TradeInfoPtr& trade_ptr, const AllTrade::UserIDType user_id);

        // 创建/更新持仓信息
        bool updatePositionInfo(const AllTrade::NPTradeCenter::PositionInfoPtr& position_ptr, const AllTrade::UserIDType user_id);
        bool deletePositionInfo(const AllTrade::NPTradeCenter::PositionInfoPtr& position_ptr, const AllTrade::UserIDType user_id);

		// 获取股票委托信息
        bool getStockOrderInfo(std::map<AllTrade::PUserIDType, std::vector<AllTrade::NPTradeCenter::StockOrderPtr>>& stockOrder);
        // 获取股票历史委托
        std::vector<AllTrade::NPTradeCenter::OrderInfoPtr> getStockOrderHistory(const AllTrade::UserIDType user_id, const AllTrade::DateType start_time, const AllTrade::DateType end_time);

		// 获取股票成交记录
		bool getStockTradeRecord(std::map<AllTrade::PUserIDType, AllTrade::NPTradeCenter::StockTradePtr>& tradeOrder);
        // 获取股票历史成交
        std::vector<AllTrade::NPTradeCenter::TradeInfoPtr> getStockTradeHistory(const AllTrade::UserIDType user_id, const AllTrade::DateType start_time, const AllTrade::DateType end_time);
		
        // 获取股票持仓信息
        bool getStockPositionInfo(std::map<AllTrade::PUserIDType, std::vector<AllTrade::NPTradeCenter::StockPositionPtr>>& posiOrder);

        // 创建/更新费用信息
        bool updateTradeFee(const AllTrade::NPTradeCenter::TradeFeePtr& trade_fee);
        bool getTradeFee(AllTrade::NPTradeCenter::TradeFeePtr& trade_fee);

        // 是否可以结算
        bool canSettle(const AllTrade::DateTimeType settle_datetime, const AllTrade::DateTimeType cur_datetime);
        // 结算
        bool updateSettle(const AllTrade::DateTimeType settle_datetime);

        // 影子编号数据管理
        AllTrade::NPTradeCenter::GlobalDataPtr getCurrentGlobalData();
        bool updateCurGlobalData(const AllTrade::NPTradeCenter::GlobalDataPtr global_data);

        // 风控记录
        void updateRiskRecord(const AllTrade::NPTradeCenter::ImmRiskControlPtr risk_cont_st);
        AllTrade::NPTradeCenter::ImmRiskControlPtr getRiskRecord(const AllTrade::UserIDType user_id, AllTrade::RiskControlType rc_type);

        // 黑白名单相关
        void addStockBlackWhite(const AllTrade::ContractIDType contract_id);
        bool updateStockBlackWhiteStatus(const AllTrade::ContractIDType contract_id, bool isBlack);
        std::map<AllTrade::PContractIDType, bool> getAllStockBlackWhiteStatus();
        bool isBlackStock(const AllTrade::ContractIDType contract_id);

        // 禁止交易相关
        void addStockBlackWhite(AllTrade::ForbidTradeType type);
        std::vector<AllTrade::NPTradeCenter::SForbidTradePtr> getAllForbidTradeStatus();
        bool updateForbidTradeStatus(const AllTrade::NPTradeCenter::SForbidTradePtr& ptr);

        // 持仓比例相关
        void addPositionRateStatus(AllTrade::PositionRateType type);
        std::vector<AllTrade::NPTradeCenter::SPositionRatePtr> getPositionRateStatus();
        bool updatePositionRateStatus(const AllTrade::NPTradeCenter::SPositionRatePtr& ptr);

		// 风控记录记录到风控历史记录表
		bool selectHistoryRiskRecord(const AllTrade::UserIDType user_id, const AllTrade::DateType start_day, const AllTrade::DateType end_day, std::vector<AllTrade::NPTradeCenter::ImmRiskControlPtr>& vecSt);
		// 风控实时记录查询
		bool getRiskRecord(const AllTrade::UserIDType user_id,  std::vector<AllTrade::NPTradeCenter::ImmRiskControlPtr>& vecSt);
	
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////	
		
		// 查看融券持仓表
		bool getMarginPositionInfo(std::map<AllTrade::PUserIDType, std::vector<AllTrade::NPTradeCenter::MarginPositionInfoPtr>>& posiOrder);
		
		// 更新融券成交表
		bool updateMarginTradeTable(const AllTrade::NPTradeCenter::MarginTradeInfoPtr& trade_ptr, const AllTrade::UserIDType user_id);
		// 获取融券成交记录
		bool getMarginTradeRecord(std::map<AllTrade::PUserIDType, AllTrade::NPTradeCenter::MarginTradeInfoPtr>& tradeOrder);
		// 获取融券历史成交
		std::vector<AllTrade::NPTradeCenter::MarginTradeInfoPtr> getMarginTradeHistory(const AllTrade::UserIDType user_id, const AllTrade::DateType start_time, const AllTrade::DateType end_time);


		// 创建融券委托表
		bool updateMarginOrderTable(const AllTrade::NPTradeCenter::MarginOrderInfoPtr& order_ptr, const AllTrade::UserIDType user_id);
		// 获取融券委托信息
		bool getMarginOrderInfo(std::map<AllTrade::PUserIDType, std::vector<AllTrade::NPTradeCenter::MarginOrderInfoPtr>>& marginOrder);
		// 查看历史融券委托信息
		std::vector<AllTrade::NPTradeCenter::MarginOrderInfoPtr> getAllMarginOrderHistory(const AllTrade::UserIDType user_id, const AllTrade::DateType start_time, const AllTrade::DateType end_time);
	

		// 更新融券信息表
		bool updateMarginInfoTable(const AllTrade::NPTradeCenter::MarginInfoPtr& ptr);
		// 查看融券信息表
		bool getAllMarginInfo(const AllTrade::NPTradeCenter::MarginInfoPtr& ptr);


		// 更新融券剩余数量信息
		bool updateMarginLeftTable(const AllTrade::NPTradeCenter::MarginLeftInfoPtr& ptr);
		// 查询融券剩余数量信息
		bool getMarginLeftTable(const AllTrade::NPTradeCenter::MarginLeftInfoPtr& ptr);
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////	
	private:
#pragma region 委托
        // 创建股票委托表
        bool createStockOrderInfo();
        // 创建外盘委托表
        bool createForeignFutureOrderInfo();
        // 创建内盘委托表
        bool createChinaFutureOrderInfo();
        // 创建费用信息表
        bool createTradeFee();

        // 创建/更新股票委托信息
        bool updateStockOrderInfo(const AllTrade::NPTradeCenter::StockOrderPtr& order_ptr, const AllTrade::UserIDType user_id);
        // 创建/更新外盘委托信息
        bool updateForeignFutureOrderInfo(const AllTrade::NPTradeCenter::ForeignFutureOrderPtr& order_ptr, const AllTrade::UserIDType user_id);
        // 创建/更新内盘委托信息
        bool updateChinaFutureOrderInfo(const AllTrade::NPTradeCenter::ChinaFutureOrderPtr& order_ptr, const AllTrade::UserIDType user_id);

		
#pragma endregion

#pragma region 成交
        // 创建股票成交表
        bool createStockTradeInfo();
        // 创建外盘成交表
        bool createForeignFutureTradeInfo();
        // 创建内盘成交表
        bool createChinaFutureTradeInfo();

        // 新增股票成交记录
        bool addStockTradeRecord(const AllTrade::NPTradeCenter::StockTradePtr& trade_ptr, const AllTrade::UserIDType user_id);
        // 新增外盘成交记录
        bool addForeignFutureTradeRecord(const AllTrade::NPTradeCenter::ForeignFutureTradePtr& trade_ptr, const AllTrade::UserIDType user_id);
        // 新增内盘成交记录
        bool addChinaFutureTradeRecord(const AllTrade::NPTradeCenter::ChinaFutureTradePtr& trade_ptr, const AllTrade::UserIDType user_id);
#pragma endregion

#pragma region 持仓
        // 创建股票持仓表
        bool createStockPositionInfo();
        // 创建外盘持仓表
        bool createForeignFuturePositionInfo();
        // 创建内盘持仓表
        bool createChinaFuturePositionInfo();

        // 创建/更新股票委托信息
        bool updateStockPositionInfo(const AllTrade::NPTradeCenter::StockPositionPtr& position_ptr, const AllTrade::UserIDType user_id);
        bool deleteStockPositionInfo(const AllTrade::NPTradeCenter::StockPositionPtr& position_ptr, const AllTrade::UserIDType user_id);
        // 创建/更新外盘委托信息
        bool updateForeignFuturePositionInfo(const AllTrade::NPTradeCenter::ForeignFuturePositionPtr& position_ptr, const AllTrade::UserIDType user_id);
        // 创建/更新内盘委托信息
        bool updateChinaFuturePositionInfo(const AllTrade::NPTradeCenter::ChinaFuturePositionPtr& position_ptr, const AllTrade::UserIDType user_id);
#pragma endregion

        // 创建结算表
        bool createSettle();

        // 创建数据管理表
        bool createGlobalData();

        // 创建风控记录表
        bool createRiskRecord();

        // 创建黑白名单表
        bool createStockBlackWhite();

        // 创建禁止交易表
        bool createForbidTrade();

        // 创建持仓比例表
        bool createPositionRate();

		// 创建风控历史记录表
		bool createHistoryRiskRecord();

		/////////////////////////////////////////////////
		// 创建融券持仓表
		bool createMarginPositionTable();
		// 更新融券持仓表
		bool updateMarginPositionTable(const AllTrade::NPTradeCenter::MarginPositionInfoPtr& position_ptr, const AllTrade::UserIDType user_id);
		bool deleteMarginPositionInfo(const AllTrade::NPTradeCenter::MarginPositionInfoPtr& position_ptr, const AllTrade::UserIDType user_id);
		/////////////////////////////////////////////////

		// 创建融券成交表
		bool createMarginTradeTable();

		// 创建融券委托表
		bool createMarginOrderTable();

		// 创建融券信息表
		bool createMarginInfoTable();

		// 创建融券剩余数量表
		bool createMarginLeftTable();
	
 };

}
