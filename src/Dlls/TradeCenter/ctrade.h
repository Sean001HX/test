/*************************************************
Copyright (C), 2017, HX Tech Co., Ltd.
File name:      ctrade.h
Author:			XuYC
Version:
Date:
Description:    �ṩ����ģ�����ʵ�ֽӿ�
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
            * @brief: �����µ�ί����Ϣ
            * order_ptr: ί��ָ��
            * use_id: �˻�ID
            */
            void handlePlaceOrder(const OrderInfoPtr& order_ptr, const UserIDType use_id, const NPMgrCenter::SOnlineAccountPtr& user_online, bool needRecode);

            /*
            * @brief: ������ί����Ϣ
            * cancel_order_info_ptr: ����ί��ָ��
            * use_id: �˻�ID
            */
            void handleCancelOrder(CommodityTypeType commodity_type, const UserIDType use_id, const OrderStreamType order_stream, bool needRecode);

            // ��������״̬
            void changeQuoteStatus(bool bl);

            // ��������
            void updateQuote(const QuoteInfoPtr& quote_ptr, const NPMgrCenter::SExchangeCPtr& exchange_ptr, const NPMgrCenter::SContractCPtr& contract_ptr);

            // ��ȡָ���û���ǰί����Ϣ
            std::vector<AllTrade::NPTradeCenter::OrderInfoPtr> getCurrentOrderList(const UserIDType user_id);
            // ��ȡָ���û�����ί����Ϣ
            std::vector<AllTrade::NPTradeCenter::OrderInfoPtr> getTodayOrderList(const UserIDType user_id);
            // ��ȡָ���û���ʷί����Ϣ
            std::vector<AllTrade::NPTradeCenter::OrderInfoPtr> getHistoryOrderList(const UserIDType user_id, const DateType start_time, const DateType end_time);
            // ��ȡָ���û��ɽ���Ϣ
            std::vector<AllTrade::NPTradeCenter::TradeInfoPtr> getTradeList(const UserIDType user_id);
            // ��ȡָ���û���ʷ�ɽ���Ϣ
            std::vector<AllTrade::NPTradeCenter::TradeInfoPtr> getHistoryTradeList(const UserIDType user_id, const DateType start_time, const DateType end_time);
            // ��ȡָ���û��ֲ���Ϣ
            std::vector<AllTrade::NPTradeCenter::PositionInfoPtr> getPositionList(const UserIDType user_id);

            // ��ȡ����������Ϣ
            AllTrade::NPTradeCenter::TradeFeePtr getFeeSetPtr();
            // ���÷���������Ϣ
            AllTrade::ErrorCodeType setFeeSetPtr(const AllTrade::NPTradeCenter::TradeFeePtr& ptr);

            // ί���Ƿ���Ч
            bool canCancelOrder(const UserIDType use_id, const OrderStreamType order_stream);

            // ��ֹ�������
            std::vector<AllTrade::NPTradeCenter::SForbidTradePtr> getAllForbidTradeStatus();
            ErrorCodeType updateForbidTradeStatus(const AllTrade::NPTradeCenter::SForbidTradePtr& ptr);

            // �ֱֲ������
            std::vector<AllTrade::NPTradeCenter::SPositionRatePtr> getAllPositionRateStatus();
            ErrorCodeType updatePositionRateStatus(const AllTrade::NPTradeCenter::SPositionRatePtr& ptr);

            // ���÷����Ϣ
            void recalculate_risk(CommodityTypeType commod_type, const UserIDType user_id);

        public:
            // ע��ί���ύ֪ͨ
            void setOrderInsertCbk(const OrderInsertCbk& fun);
            // ע�᳷���ص�֪ͨ
            void setOrderCancelCbk(const CancelOrderCbk& fun);
            // ע��ί�иı�֪ͨ
            void setOrderChangeCbk(const OrderChangeCbk& fun);
            // ע��ɽ��ص�֪ͨ
            void setTradeCbk(const TradeCbk& fun);
            // ע��ֲֻص�֪ͨ
            void setPositionCbk(const PositionCbk& fun);
            // ע���ػص�֪ͨ
            void setRiskControlCbk(const RiskControlCbk& fun);
        };
    }
}
#endif