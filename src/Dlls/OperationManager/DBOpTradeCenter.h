/*************************************************
Copyright (C), 2017, HX Tech Co., Ltd.
File name:      DBOpTradeCenter.h
Author:			XuYC
Version:
Date:
Description:    ���ݿ����- ����������ز���
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

        // ��ʼ�����ݿ��
        bool initAllTable();

        // ����/����ί����Ϣ
        bool updateOrderInfo(const AllTrade::NPTradeCenter::OrderInfoPtr& order_ptr, const AllTrade::UserIDType user_id);

        // �����ɽ���¼
        bool addTradeRecord(const AllTrade::NPTradeCenter::TradeInfoPtr& trade_ptr, const AllTrade::UserIDType user_id);

        // ����/���³ֲ���Ϣ
        bool updatePositionInfo(const AllTrade::NPTradeCenter::PositionInfoPtr& position_ptr, const AllTrade::UserIDType user_id);
        bool deletePositionInfo(const AllTrade::NPTradeCenter::PositionInfoPtr& position_ptr, const AllTrade::UserIDType user_id);

		// ��ȡ��Ʊί����Ϣ
        bool getStockOrderInfo(std::map<AllTrade::PUserIDType, std::vector<AllTrade::NPTradeCenter::StockOrderPtr>>& stockOrder);
        // ��ȡ��Ʊ��ʷί��
        std::vector<AllTrade::NPTradeCenter::OrderInfoPtr> getStockOrderHistory(const AllTrade::UserIDType user_id, const AllTrade::DateType start_time, const AllTrade::DateType end_time);

		// ��ȡ��Ʊ�ɽ���¼
		bool getStockTradeRecord(std::map<AllTrade::PUserIDType, AllTrade::NPTradeCenter::StockTradePtr>& tradeOrder);
        // ��ȡ��Ʊ��ʷ�ɽ�
        std::vector<AllTrade::NPTradeCenter::TradeInfoPtr> getStockTradeHistory(const AllTrade::UserIDType user_id, const AllTrade::DateType start_time, const AllTrade::DateType end_time);
		
        // ��ȡ��Ʊ�ֲ���Ϣ
        bool getStockPositionInfo(std::map<AllTrade::PUserIDType, std::vector<AllTrade::NPTradeCenter::StockPositionPtr>>& posiOrder);

        // ����/���·�����Ϣ
        bool updateTradeFee(const AllTrade::NPTradeCenter::TradeFeePtr& trade_fee);
        bool getTradeFee(AllTrade::NPTradeCenter::TradeFeePtr& trade_fee);

        // �Ƿ���Խ���
        bool canSettle(const AllTrade::DateTimeType settle_datetime, const AllTrade::DateTimeType cur_datetime);
        // ����
        bool updateSettle(const AllTrade::DateTimeType settle_datetime);

        // Ӱ�ӱ�����ݹ���
        AllTrade::NPTradeCenter::GlobalDataPtr getCurrentGlobalData();
        bool updateCurGlobalData(const AllTrade::NPTradeCenter::GlobalDataPtr global_data);

        // ��ؼ�¼
        void updateRiskRecord(const AllTrade::NPTradeCenter::ImmRiskControlPtr risk_cont_st);
        AllTrade::NPTradeCenter::ImmRiskControlPtr getRiskRecord(const AllTrade::UserIDType user_id, AllTrade::RiskControlType rc_type);

        // �ڰ��������
        void addStockBlackWhite(const AllTrade::ContractIDType contract_id);
        bool updateStockBlackWhiteStatus(const AllTrade::ContractIDType contract_id, bool isBlack);
        std::map<AllTrade::PContractIDType, bool> getAllStockBlackWhiteStatus();
        bool isBlackStock(const AllTrade::ContractIDType contract_id);

        // ��ֹ�������
        void addStockBlackWhite(AllTrade::ForbidTradeType type);
        std::vector<AllTrade::NPTradeCenter::SForbidTradePtr> getAllForbidTradeStatus();
        bool updateForbidTradeStatus(const AllTrade::NPTradeCenter::SForbidTradePtr& ptr);

        // �ֱֲ������
        void addPositionRateStatus(AllTrade::PositionRateType type);
        std::vector<AllTrade::NPTradeCenter::SPositionRatePtr> getPositionRateStatus();
        bool updatePositionRateStatus(const AllTrade::NPTradeCenter::SPositionRatePtr& ptr);

		// ��ؼ�¼��¼�������ʷ��¼��
		bool selectHistoryRiskRecord(const AllTrade::UserIDType user_id, const AllTrade::DateType start_day, const AllTrade::DateType end_day, std::vector<AllTrade::NPTradeCenter::ImmRiskControlPtr>& vecSt);
		// ���ʵʱ��¼��ѯ
		bool getRiskRecord(const AllTrade::UserIDType user_id,  std::vector<AllTrade::NPTradeCenter::ImmRiskControlPtr>& vecSt);
	
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////	
		
		// �鿴��ȯ�ֱֲ�
		bool getMarginPositionInfo(std::map<AllTrade::PUserIDType, std::vector<AllTrade::NPTradeCenter::MarginPositionInfoPtr>>& posiOrder);
		
		// ������ȯ�ɽ���
		bool updateMarginTradeTable(const AllTrade::NPTradeCenter::MarginTradeInfoPtr& trade_ptr, const AllTrade::UserIDType user_id);
		// ��ȡ��ȯ�ɽ���¼
		bool getMarginTradeRecord(std::map<AllTrade::PUserIDType, AllTrade::NPTradeCenter::MarginTradeInfoPtr>& tradeOrder);
		// ��ȡ��ȯ��ʷ�ɽ�
		std::vector<AllTrade::NPTradeCenter::MarginTradeInfoPtr> getMarginTradeHistory(const AllTrade::UserIDType user_id, const AllTrade::DateType start_time, const AllTrade::DateType end_time);


		// ������ȯί�б�
		bool updateMarginOrderTable(const AllTrade::NPTradeCenter::MarginOrderInfoPtr& order_ptr, const AllTrade::UserIDType user_id);
		// ��ȡ��ȯί����Ϣ
		bool getMarginOrderInfo(std::map<AllTrade::PUserIDType, std::vector<AllTrade::NPTradeCenter::MarginOrderInfoPtr>>& marginOrder);
		// �鿴��ʷ��ȯί����Ϣ
		std::vector<AllTrade::NPTradeCenter::MarginOrderInfoPtr> getAllMarginOrderHistory(const AllTrade::UserIDType user_id, const AllTrade::DateType start_time, const AllTrade::DateType end_time);
	

		// ������ȯ��Ϣ��
		bool updateMarginInfoTable(const AllTrade::NPTradeCenter::MarginInfoPtr& ptr);
		// �鿴��ȯ��Ϣ��
		bool getAllMarginInfo(const AllTrade::NPTradeCenter::MarginInfoPtr& ptr);


		// ������ȯʣ��������Ϣ
		bool updateMarginLeftTable(const AllTrade::NPTradeCenter::MarginLeftInfoPtr& ptr);
		// ��ѯ��ȯʣ��������Ϣ
		bool getMarginLeftTable(const AllTrade::NPTradeCenter::MarginLeftInfoPtr& ptr);
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////	
	private:
#pragma region ί��
        // ������Ʊί�б�
        bool createStockOrderInfo();
        // ��������ί�б�
        bool createForeignFutureOrderInfo();
        // ��������ί�б�
        bool createChinaFutureOrderInfo();
        // ����������Ϣ��
        bool createTradeFee();

        // ����/���¹�Ʊί����Ϣ
        bool updateStockOrderInfo(const AllTrade::NPTradeCenter::StockOrderPtr& order_ptr, const AllTrade::UserIDType user_id);
        // ����/��������ί����Ϣ
        bool updateForeignFutureOrderInfo(const AllTrade::NPTradeCenter::ForeignFutureOrderPtr& order_ptr, const AllTrade::UserIDType user_id);
        // ����/��������ί����Ϣ
        bool updateChinaFutureOrderInfo(const AllTrade::NPTradeCenter::ChinaFutureOrderPtr& order_ptr, const AllTrade::UserIDType user_id);

		
#pragma endregion

#pragma region �ɽ�
        // ������Ʊ�ɽ���
        bool createStockTradeInfo();
        // �������̳ɽ���
        bool createForeignFutureTradeInfo();
        // �������̳ɽ���
        bool createChinaFutureTradeInfo();

        // ������Ʊ�ɽ���¼
        bool addStockTradeRecord(const AllTrade::NPTradeCenter::StockTradePtr& trade_ptr, const AllTrade::UserIDType user_id);
        // �������̳ɽ���¼
        bool addForeignFutureTradeRecord(const AllTrade::NPTradeCenter::ForeignFutureTradePtr& trade_ptr, const AllTrade::UserIDType user_id);
        // �������̳ɽ���¼
        bool addChinaFutureTradeRecord(const AllTrade::NPTradeCenter::ChinaFutureTradePtr& trade_ptr, const AllTrade::UserIDType user_id);
#pragma endregion

#pragma region �ֲ�
        // ������Ʊ�ֱֲ�
        bool createStockPositionInfo();
        // �������ֱֲ̳�
        bool createForeignFuturePositionInfo();
        // �������ֱֲ̳�
        bool createChinaFuturePositionInfo();

        // ����/���¹�Ʊί����Ϣ
        bool updateStockPositionInfo(const AllTrade::NPTradeCenter::StockPositionPtr& position_ptr, const AllTrade::UserIDType user_id);
        bool deleteStockPositionInfo(const AllTrade::NPTradeCenter::StockPositionPtr& position_ptr, const AllTrade::UserIDType user_id);
        // ����/��������ί����Ϣ
        bool updateForeignFuturePositionInfo(const AllTrade::NPTradeCenter::ForeignFuturePositionPtr& position_ptr, const AllTrade::UserIDType user_id);
        // ����/��������ί����Ϣ
        bool updateChinaFuturePositionInfo(const AllTrade::NPTradeCenter::ChinaFuturePositionPtr& position_ptr, const AllTrade::UserIDType user_id);
#pragma endregion

        // ���������
        bool createSettle();

        // �������ݹ����
        bool createGlobalData();

        // ������ؼ�¼��
        bool createRiskRecord();

        // �����ڰ�������
        bool createStockBlackWhite();

        // ������ֹ���ױ�
        bool createForbidTrade();

        // �����ֱֲ�����
        bool createPositionRate();

		// ���������ʷ��¼��
		bool createHistoryRiskRecord();

		/////////////////////////////////////////////////
		// ������ȯ�ֱֲ�
		bool createMarginPositionTable();
		// ������ȯ�ֱֲ�
		bool updateMarginPositionTable(const AllTrade::NPTradeCenter::MarginPositionInfoPtr& position_ptr, const AllTrade::UserIDType user_id);
		bool deleteMarginPositionInfo(const AllTrade::NPTradeCenter::MarginPositionInfoPtr& position_ptr, const AllTrade::UserIDType user_id);
		/////////////////////////////////////////////////

		// ������ȯ�ɽ���
		bool createMarginTradeTable();

		// ������ȯί�б�
		bool createMarginOrderTable();

		// ������ȯ��Ϣ��
		bool createMarginInfoTable();

		// ������ȯʣ��������
		bool createMarginLeftTable();
	
 };

}
