/*************************************************
Copyright (C), 2017, HX Tech Co., Ltd.
File name:      TradeCenter.h
Author:			XuYC
Version:
Date:
Description:    �ṩ����ģ��ͳһ�ӿ�
*************************************************/

#ifndef __ITRADE_H__
#define __ITRADE_H__

#include <vector>
#include "utility/instance_shared_from_this.h"
#include "define/struct_declare.h"
#include "define/params_declare.h"

#ifdef HX_ITRADE_API_EXPORTS
#define HX_ITRADE_API_API __declspec(dllexport)
#else
#define HX_ITRADE_API_API __declspec(dllimport)
#endif

#ifdef _MSC_VER
#	pragma warning(push)
#   pragma warning(disable: 4251) 
// #	pragma warning(disable: 4275) // �� DLL �ӿ������identifier����Ϊ DLL �ӿ������identifier���Ļ�ʹ��
#endif

namespace AllTrade{
    namespace NPTradeCenter {
        class CTradeCenter;

        class HX_ITRADE_API_API ITradeCenter : public CommonTools::instance_shared_from_this<ITradeCenter>
        {
            typedef std::function<void(ErrorCodeType errcode, const UserIDType user_id, const OrderInfoPtr& order_ptr, const NPMgrCenter::SOnlineAccountPtr& user_online)>  OrderInsertCbk;
            typedef std::function<void(ErrorCodeType errcode, const UserIDType user_id, const OrderInfoPtr& order_ptr, const NPMgrCenter::SOnlineAccountPtr& user_online)>  CancelOrderCbk;
            typedef std::function<void(ErrorCodeType errcode, const UserIDType user_id, const OrderInfoPtr& order_ptr)>  OrderChangeCbk;
            typedef std::function<void(ErrorCodeType errcode, const UserIDType user_id, const TradeInfoPtr& trade_ptr)>  TradeCbk;
            typedef std::function<void(ErrorCodeType errcode, const UserIDType user_id, const PositionInfoPtr& position_ptr)>  PositionCbk;
            typedef std::function<void(const UserIDType user_id, const DateTimeType date_time, RiskControlType rc_type, const RemarkTextType remark_text)>  RiskControlCbk;
        
        public:
            ITradeCenter();
            ~ITradeCenter();

            /*
            * @brief: �����µ�ί����Ϣ
            * order_ptr: ί����Ϣָ��
            * use_id: �˻�ID
            */
            void handlePlaceOrder(const OrderInfoPtr& order_ptr, const UserIDType use_id, const NPMgrCenter::SOnlineAccountPtr& user_online);

            /*
            * @brief: ������ί����Ϣ
            * cancel_order_info_ptr: ����ί����Ϣָ��
            * use_id: �˻�ID
            */
            void handleCancelOrder(CommodityTypeType commodity_type, const UserIDType use_id, const OrderStreamType order_stream);

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
            // ע��ί���ύ֪ͨ�ص�֪ͨ
            void setOrderInsertCbk(const OrderInsertCbk& fun);
            // ע�᳷���ص�֪ͨ�ص�֪ͨ
            void setOrderCancelCbk(const CancelOrderCbk& fun);
            // ע��ί�иı�֪ͨ�ص�֪ͨ
            void setOrderChangeCbk(const OrderChangeCbk& fun);
            // ע��ɽ��ص�֪ͨ�ص�֪ͨ
            void setTradeCbk(const TradeCbk& fun);
            // ע��ֲֻص�֪ͨ�ص�֪ͨ
            void setPositionCbk(const PositionCbk& fun);
            // ע���ػص�֪ͨ
            void setRiskControlCbk(const RiskControlCbk& fun);

        private:
            CTradeCenter* m_trade;
        };
    }
}
#if defined(_MSC_VER)
#	pragma warning(pop)
#endif

#endif