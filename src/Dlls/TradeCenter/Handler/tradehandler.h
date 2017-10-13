/*************************************************
Copyright (C), 2017, HX Tech Co., Ltd.
File name:      tradehandler.h
Author:			XuYC
Version:
Date:
Description:    �ṩ�ɽ�����,���������������
                �ɽ�����Ϊ��ί�в���,���ڲ��洢����Ϊί�ж���
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
        // �ɽ���Ϣ��������
        class TradeBaseHandler : public std::enable_shared_from_this<TradeBaseHandler>
        {
        public:
            TradeBaseHandler(const TradeInfoPtr& trade_ptr, const UserIDType use_id);
            virtual ~TradeBaseHandler(){}

            // �������ݲ�����صĲ���
        public:
            // ��ȡ�ɽ�ID
            const PTradeIDType getTradeID() const;
            // ��ȡ�ֲ�ID
            const PPositionIDType getPositionID() const;
            void setPositionID(const PositionIDType positionID);
            // ��ȡί������
            const POrderIDType getOrderStream() const;
            // ��ȡί������
            const PSystemIDType getOrderSystemID() const;
            // ��ȡ�µ��û�ID
            const PUserIDType getUserID() const;
            // ��ȡ������ID
            const PExchangeIDType getExchangeID() const;
            // ��ȡ��ԼID
            const PContractIDType getContractID() const;
            // ��ȡ�ɽ�����ʱ��
            const PDateTimeType getGenerateDatetime() const;
            // ��ȡ�ɽ�����
            int getTradeVol() const;
            // ��ȡ��������
            DirectType getDirect() const;
            // ��ȡ����
            YDouble getCurrencyRate() const;
            // ��ȡ����ID
            const PCurrencyIDType getCurrencyID() const;
            // ��ȡ�ɽ���
            YDouble getTradePrice() const;
            // ��ȡƽ��ӯ��
            YDouble getCloseProfit() const;
            // ��ȡ��Ʒ����
            CommodityTypeType getCommodityType() const;
            // ��ȡ����Ա����
            OperatorTradeType getOperatorType() const;
            // ��ȡ�ֲֳɱ�
            virtual YDouble getPositionCost() const { return 0; };
            // ��ȡ�ֲ־���
//             YDouble getPositionAvePrice() const;

            bool isValid() const;

            // ���л�
            // ע: ��ʱ���л���Ϊ�ȳ���ʷ����,�ұ���ȷ��д��ɹ�
            virtual ErrorCodeType serialize();

            // ��ȡ�ɽ�������Ϣ
            virtual TradeInfoPtr getTradeInfoCopy() const = 0;

        protected:
            UserIDType                  m_user_id;          // �û�ID
            TradeInfoPtr                m_trade_ptr;        // �ɽ���Ϣָ��
            mutable rwMutex             m_mtx;              // ���ݶ�д��
        };

        // ��Ʊ�ɽ���Ϣ����
        class StockTradeHandler
            : public TradeBaseHandler
            , public boost::noncopyable
        {
        public:
            StockTradeHandler(const StockTradePtr& stock_trade_ptr, const UserIDType use_id);
            ~StockTradeHandler(){}

            // ��ȡ�ɽ���Ϣ�ṹ��
            StockTradeInfo getTradeInfo() const;

            // ��ȡ�ɽ�������Ϣ
            TradeInfoPtr getTradeInfoCopy() const override;

            YDouble getPositionCost() const override;

            // ��ȡ����Ӷ��������
            YDouble getTradeCommissionFee() const;
            // ��ȡƽ��ӡ��˰
            YDouble getStampFee() const;
            // ��ȡ������
            YDouble getTransferFee() const;
            // ��ȡ��Ϣ��Ϸ�
            YDouble getInfoMatchFee() const;

        };

        // �����ڻ��ɽ���Ϣ����
        class ForeignFutureTradeHandler
            : public TradeBaseHandler
            , public boost::noncopyable
        {
        public:
            ForeignFutureTradeHandler(const ForeignFutureTradePtr& ffuture_trade_ptr, const UserIDType use_id);
            ~ForeignFutureTradeHandler(){}

            // ��ȡƷ��ID
            const PProductIDType getProductID() const;

            // ��ȡ�ɽ���Ϣ�ṹ��
            ForeignFutureTradeInfo getTradeInfo() const;

            // ��ȡ�ɽ�������Ϣ
            TradeInfoPtr getTradeInfoCopy() const override;

        };

        // �����ڻ��ɽ���Ϣ����
        class ChinaFutureTradeHandler
            : public TradeBaseHandler
            , public boost::noncopyable
        {
        public:
            ChinaFutureTradeHandler(const ChinaFutureTradePtr& cfuture_trade_ptr, const UserIDType use_id);
            ~ChinaFutureTradeHandler(){}

            // ��ȡƷ��ID
            const PProductIDType getProductID() const;
            // ��ȡ��ƽ��־
            const OffsetType getOffsetType() const;

            // ��ȡ�ɽ���Ϣ�ṹ��
            ChinaFutureTradeInfo getTradeInfo() const;

            // ��ȡ�ɽ�������Ϣ
            TradeInfoPtr getTradeInfoCopy() const override;

        };


		// ���ʳɽ���Ϣ����
		class MarginTradeHandler
			: public TradeBaseHandler
			, public boost::noncopyable
		{
		public:
			MarginTradeHandler(const MarginTradeInfoPtr& margin_trade_ptr, const UserIDType use_id);
			~MarginTradeHandler(){}

			// ��ȡ�ɽ���Ϣ�ṹ��
			MarginTradeInfo getTradeInfo() const;

			// ��ȡ�ɽ�������Ϣ
			TradeInfoPtr getTradeInfoCopy() const override;

		};
    }
}

#endif