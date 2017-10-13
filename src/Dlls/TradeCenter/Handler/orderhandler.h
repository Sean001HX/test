/*************************************************
Copyright (C), 2017, HX Tech Co., Ltd.
File name:      orderhandler.h
Author:			XuYC
Version:
Date:
Description:    �ṩ�µ�ί�в���,���������������
                ί�в������������׵ĺ���,�ʳ���/�ɽ���Ϣ�д洢��Ҳ��ί�в���
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

        // �µ�ί�в�������
        class OrderBaseHandler : public std::enable_shared_from_this<OrderBaseHandler>
        {
        public:
            OrderBaseHandler(const OrderInfoPtr& order_ptr, const UserIDType use_id, const NPMgrCenter::SOnlineAccountPtr& user_online);
            virtual ~OrderBaseHandler();

            // �������ݲ�����صĲ���
        public:
            // ����/��ȡ�µ�ί��ID
            const POrderIDType getOrderID() const;
            void setOrderID(const OrderIDType order_id);
            // ��ȡϵͳί��ID
            PSystemIDType getSystemOrderID();
            void setSystemOrderID(const SystemIDType sys_order_id);
            // ��ȡ�µ�ί�б���ί�б������
            const POrderRefType getOrderRef() const;
            void setOrderRef(const OrderRefType order_ref);
            // ��ȡ�µ��û�ID
            const PUserIDType getUserID() const;
            // ��ȡ��ԼID
            const PContractIDType getContractID() const;
            // ����/��ȡί��״̬
            OrderStateType getOrderState() const;
            void setOrderState(OrderStateType order_state);
            // ��ȡί��״̬˵��
            OrderStateExplainType getOrderStateExplain() const;
            // ��ȡ�µ�ί���ύ���,����ί�в���ʱ����,�����޸�
            const POrderStreamType getOrderStream() const;
            // ����/��ȡӰ�Ӷ������
            const PShadowOrderIDType getShadowOrderID() const;
            void setShadowOrderID(const ShadowOrderIDType shadoworder_id);
            // ί�д�������ʱ��
            const PDateTimeType getGenerateDatetime() const;
            // ί��״̬����������ʱ��
            const PDateTimeType getUpdateDatetime() const;
            // ��ȡ����
            YDouble getCurrencyRate() const;
            // ��ȡί�б���ID
            const PCurrencyIDType getCurrencyID() const;
            // ��ȡί�м۸�
            YDouble getOrderPrice(const CurrencyIDType currency_id) const;
            YDouble getOrderPrice() const;
            void setOrderPrice(YDouble order_price);
            // ��ȡ��������
            DirectType getDirect() const;
            // ��ȡί������
            int getOrderVol() const;
            // ��ȡ�ѳɽ�����
            int getTradeVol() const;
            // �����ѳɽ�����,�����������
            bool addTradeVol(int vol);
            void setTradeVol(int vol);
            // ��ȡ����Ч����
            int getEffectVol() const;
            // ������Ч����,�����������
//             bool addEffectVol(int vol);
            // ��ȡ�µ�ί������(�޼�/�м�/...),������Ӹĵ�����ʱ,��Ҫ��Ӷ���
            OrderTypeType getOrderType() const;
            void setOrderType(OrderTypeType type);
            // ��ȡί�н���ģʽ,�Ƿ���Ҫͬ����ʵ������
            OrderTradeModeType getOrderTradeMode() const;
            // ��ȡί�гɽ���
            YDouble getOrderTradePrice(const CurrencyIDType currency_id) const;
            YDouble getOrderTradePrice() const;
            // ��ȡ�ֲֳɱ�
            YDouble getPoitionCost() const;
            // ��ȡ�����ʽ�
            YDouble getFreezeMoney() const;
            // ��ȡʵ�̶�Ӧί��ID
            const PSystemIDType getSystemID() const;
            // ��ȡ������ID
            const PExchangeIDType getExchangeID() const;
            // ��ȡ�ӿ�����(CTP/ESUNNY/...)
            ApiTypeType getApiType() const;
            // ��ȡ��Ʒ����
            CommodityTypeType getCommodityType() const;
            // ��ȡ����Ա����
            OperatorTradeType getOperatorType() const;
            // ��ȡ�µ�ί��ģʽ(FAK/...)
            OrderModeType getOrderMode() const;
            // ��ȡ��Ч����(GTD�����ʹ��)
            const PDateTimeType getValidDatetime() const;

            // ��ȡ�µ��û���¼��Ϣ
            const NPMgrCenter::SOnlineAccountPtr& getOpUserLoginInfo() const{
                return m_user_online;
            }
            //////////////////////////////////////////////////////////////////////////
            // ��Ч�����ж�

            // ��ȡί���Ƿ���Ч
            virtual ErrorCodeType isOrderValid() const;
            // �Ƿ�ί��ʱ��
            virtual bool isOrderTime() const;
            // �Ƿ���ʱ��
            virtual bool isTradeTime() const;
            // �Ƿ���ύ�ý���
            virtual ErrorCodeType canOrder() const;
            // ί���Ƿ��ִ�иý���(������/ֻ����ƽ�������ƽ��/��ص������ж�)
            virtual ErrorCodeType canTrade() const;
            // ��ȡί���ύʱ�Ķ������
            YDouble getOrderFreezeFee(const QuoteHrPtr& quote_ptr) const;
            // ί���Ƿ�ɳ���
            virtual ErrorCodeType canCancelOrder() const;

            //////////////////////////////////////////////////////////////////////////
            // �ʽ���ֲ�

            // �����˻��ʽ�
            virtual ErrorCodeType freezeMoney() { return Err_Unknown; }
            // �����˻��ֲ�
            virtual ErrorCodeType freezePosition() { return Err_Unknown; }
            // �ⶳ�˻��ʽ�
            virtual ErrorCodeType thawMoney() { return Err_Unknown; }
            // �ⶳ�˻��ֲ�
            virtual ErrorCodeType thawPosition() { return Err_Unknown; }

            // ���л�
            virtual ErrorCodeType serialize();

            //////////////////////////////////////////////////////////////////////////
            // �ɽ��볷��

            // ģ��ɽ�, �����Ƿ���Ҫ��������,������Ҫ���������򷵻�false
            bool simulateTrade(const QuoteHrPtr& quote_ptr);

            // ģ�⳷��ί��
            void simulateCancelOrder();

            // ���ί�гɽ�״̬,�Ƿ���Ҫ�Ӷ�����ɾ��;������ɾ��������Ӷ�����ɾ��
            void checkOrderTradeStatus();

            // ��ȡί�п�����Ϣ
            virtual OrderInfoPtr getOrderInfoCopy() const = 0;

            // ʵ�̳ɽ�
            virtual void realTrade(const TradeInfoPtr& trade_ptr);

            // ���ݳɽ�������ֵ�뵱ǰί��״̬�޸ĳɽ������ѵȲ���
            virtual void generateTradeFeeVarious(const TradeInfoPtr& trade_ptr){ assert(0); }

       protected:
            //ͨ��ί�����������ɳɽ���Ϣ
            virtual TradeInfoPtr createTradeByQuote(const QuoteInfoPtr& quote_info_ptr, int trade_vol, TradeInfoPtr trade_ptr_self = nullptr) const;

       private:
            // ������������,�ж�ί���Ƿ�ɽ�
            virtual bool matchQuote(const QuoteInfoPtr& quote_ptr) const;
            bool isSerializing();

         protected:
             // ��ȡ������������
            YDouble getUserOpenFee(DirectType direct, YDouble all_money, int vol) const;
            // ��ȡ���ֽ���Ӷ��
            YDouble getUserTradeCommissionFee(YDouble all_money) const;

        protected:
            UserIDType          m_user_id;              // �û�ID
            OrderInfoPtr        m_order_ptr;            // ί����Ϣָ��

            NPMgrCenter::SOnlineAccountPtr   m_user_online;      // �µ��û���¼��Ϣ,��ϵͳ�µ�����ʱ��Ҫ������ʾ

            mutable rwMutex     m_mtx;          // ���ݶ�д��
            std::mutex          m_status_mtx;   // ί��״̬������(���ڳɽ��볷��ͬ��)

            bool                m_is_modify;    // �Ƿ��޸�
        };

        // ��Ʊ�µ�ί�в���
        class StockOrderHandler
            : public OrderBaseHandler
            , public boost::noncopyable
        {
        public:
            StockOrderHandler(const StockOrderPtr& order_ptr, const UserIDType use_id, const NPMgrCenter::SOnlineAccountPtr& user_online);
            ~StockOrderHandler(){}

            StockAreaType getStockAreaType() const;

            // ��ȡί���Ƿ���Ч
            virtual ErrorCodeType isOrderValid() const override;

            // �����˻��ʽ�
            virtual ErrorCodeType freezeMoney() override;
            // �����˻��ֲ�
            virtual ErrorCodeType freezePosition() override;
            // �ⶳ�˻��ʽ�
            virtual ErrorCodeType thawMoney() override;
            // �ⶳ�˻��ֲ�
            virtual ErrorCodeType thawPosition() override;

            // ��ȡί�п�����Ϣ
            OrderInfoPtr getOrderInfoCopy() const override;

            // ʵ�̳ɽ�
            void realTrade(const TradeInfoPtr& trade_ptr) override;

            // ���ݳɽ�������ֵ�뵱ǰί��״̬�޸ĳɽ������ѵȲ���
            void generateTradeFeeVarious(const TradeInfoPtr& trade_ptr) override;

        protected:
            //ͨ��ί�����������ɳɽ���Ϣ
            TradeInfoPtr createTradeByQuote(const QuoteInfoPtr& quote_info_ptr, int trade_vol, TradeInfoPtr trade_ptr_self = nullptr) const override;

            // ��ȡί����Ϣ
            StockOrderInfo getOrderInfo() const;

        };

        // �����ڻ��µ�ί�в���
        class ForeignFutureOrderHandler
            : public OrderBaseHandler
            , public boost::noncopyable
        {
        public:
            ForeignFutureOrderHandler(const ForeignFutureOrderPtr& order_ptr, const UserIDType use_id, const NPMgrCenter::SOnlineAccountPtr& user_online);
            ~ForeignFutureOrderHandler(){}

            // ��ȡί���Ƿ���Ч
            virtual ErrorCodeType isOrderValid() const override;
            // ��ȡί�п�����Ϣ
            OrderInfoPtr getOrderInfoCopy() const override;
            // ��ȡƷ��ID
            const PProductIDType getProductID() const;
            // ��ȡί����Ϣ
            ForeignFutureOrderInfo getOrderInfo() const;

        protected:
            //ͨ��ί�����������ɳɽ���Ϣ
            TradeInfoPtr createTradeByQuote(const QuoteInfoPtr& quote_info_ptr, int trade_vol, TradeInfoPtr trade_ptr_self = nullptr) const override;


        };

        // �����ڻ��µ�ί�в���
        class ChinaFutureOrderHandler
            : public OrderBaseHandler
            , public boost::noncopyable
        {
        public:
            ChinaFutureOrderHandler(const ChinaFutureOrderPtr& order_ptr, const UserIDType use_id, const NPMgrCenter::SOnlineAccountPtr& user_online);
            ~ChinaFutureOrderHandler(){}

            // ��ȡί���Ƿ���Ч
            virtual ErrorCodeType isOrderValid() const override;
            // ��ȡί�п�����Ϣ
            OrderInfoPtr getOrderInfoCopy() const override;
            // ��ȡƷ��ID
            const PProductIDType getProductID() const;
            // ��ȡ��ƽ����
            OffsetType getOffsetType() const;
            // ��ȡί����Ϣ
            ChinaFutureOrderInfo getOrderInfo() const;

        protected:
            //ͨ��ί�����������ɳɽ���Ϣ
            TradeInfoPtr createTradeByQuote(const QuoteInfoPtr& quote_info_ptr, int trade_vol, TradeInfoPtr trade_ptr_self = nullptr) const override;


        };


		// �µ�ί�в���
		class MarginOrderHandler
			: public OrderBaseHandler
			, public boost::noncopyable
		{
		public:
			MarginOrderHandler(const MarginOrderInfoPtr& order_ptr, const UserIDType use_id, const NPMgrCenter::SOnlineAccountPtr& user_online);
			~MarginOrderHandler(){}

			// ��ȡί���Ƿ���Ч
			virtual ErrorCodeType isOrderValid() const override;
			// ��ȡί�п�����Ϣ
			OrderInfoPtr getOrderInfoCopy() const override;
			// ��ȡί����Ϣ
			MarginOrderInfo getOrderInfo() const;

		protected:
			//ͨ��ί�����������ɳɽ���Ϣ
			TradeInfoPtr createTradeByQuote(const QuoteInfoPtr& quote_info_ptr, int trade_vol, TradeInfoPtr trade_ptr_self = nullptr) const override;

		};


    }
}

#endif