/*************************************************
Copyright (C), 2017, HX Tech Co., Ltd.
File name:      positionhandler.h
Author:			XuYC
Version:
Date:
Description:    �ṩ�ֲֲ���,���������������
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

        // �ֲ���Ϣ��������
        class PositionBaseHandler
        {
        protected:
            PositionBaseHandler(const PositionInfoPtr& position_ptr, const UserIDType user_id);
            PositionBaseHandler(const TradeHrPtr& trade_hr);
        public:
            virtual ~PositionBaseHandler(){}

            // �������ݲ�����صĲ���
        public:
            // ��ȡ�ֲ�ID
            const PPositionIDType getPositionID() const;
            // ��ȡ�µ��û�ID
            const PUserIDType getUserID() const;
            // ��ȡ������ID
            const PExchangeIDType getExchangeID() const;
            // ��ȡ��ԼID
            const PContractIDType getContractID() const;
            // ��ȡ�ֲ�����
            int getPositionAllVol() const;
            // ��ȡ�ֲ�����
            int getPositionVol() const;
            // ��ȡT+1�ֲ�����
            int getPositionVol_T() const;
            // ��ȡ��ƽ������
            int getCanCloseVol() const;
            // ���Ӷ����ƽ������
            bool addFreezeVol(int vol);
            // ��ȡ��������
            DirectType getDirect() const;
            // ��ȡ����ID
            const PCurrencyIDType getCurrencyID() const;
            // ��ȡ�ɽ�����
            YDouble getTradeAvePrice() const;
            // ��ȡ�ֲֳɱ�
            YDouble getPositionCost() const;
            // ��ȡ��Ʒ����
            CommodityTypeType getCommodityType() const;
            // ��ȡ�ֲ���ֵ
            YDouble getLastPrice() const;
            // ��ȡ�ֲ�ӯ��
            YDouble getProfit() const;

            // �ж��Ƿ���Ч
            bool isValid() const;

            // �����������¼�
            void updateQuoteLastPrice(YDouble last_quote);

            // ���л�
            // ע: ��ʱ���л���Ϊ�ȳ���ʷ����,�ұ���ȷ��д��ɹ�
            virtual ErrorCodeType serialize();

            virtual void addTradeInfo(const TradeHrPtr& trade_hr_ptr) = 0;

            // ���ֲ�״̬,�Ƿ���Ҫ�Ӷ�����ɾ��;������ɾ��������Ӷ�����ɾ��
            virtual void checkPositionStatus() = 0;

            // ��ȡ�ֲֿ���
            virtual PositionInfoPtr getPositionCopy() const = 0;

            // ����ֲ�
            void settlePosition();

        protected:
            virtual void createByTradeHr(const TradeHrPtr& trade_hr);

        protected:
            mutable rwMutex             m_mtx_quote;        // �������ݶ�д��
            YDouble                     m_last_quote;       // �ֲ��������¼�

            UserIDType                  m_user_id;          // �û�ID
            PositionInfoPtr             m_position_ptr;     // �ֲ���Ϣָ��
            mutable rwMutex             m_mtx;              // ���ݶ�д��
            bool                        m_is_modify;        // �Ƿ��޸�
        };

        // ��Ʊ�ֲ���Ϣ����
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

            // ���ֲ�״̬,�Ƿ���Ҫ�Ӷ�����ɾ��;������ɾ��������Ӷ�����ɾ��
            void checkPositionStatus() override;

            PositionInfoPtr getPositionCopy() const override;

        private:
            void createByTradeHr(const TradeHrPtr& trade_hr) override;
        };

        // �����ڻ��ֲ���Ϣ����
        class ForeignFuturePositionHandler
            : public PositionBaseHandler
            , public std::enable_shared_from_this<ForeignFuturePositionHandler>
            , public boost::noncopyable
        {
        public:
            ForeignFuturePositionHandler(const TradeHrPtr& trade_hr);
            ~ForeignFuturePositionHandler(){}

            void addTradeInfo(const TradeHrPtr& trade_hr_ptr) override;

            // ���ֲ�״̬,�Ƿ���Ҫ�Ӷ�����ɾ��;������ɾ��������Ӷ�����ɾ��
            void checkPositionStatus() override {}

            // ��ȡƷ��ID
            const PProductIDType getProductID() const;

            PositionInfoPtr getPositionCopy() const override;
        };

        // �����ڻ��ֲ���Ϣ����
        class ChinaFuturePositionHandler
            : public PositionBaseHandler
            , public std::enable_shared_from_this<ChinaFuturePositionHandler>
            , public boost::noncopyable
        {
        public:
            ChinaFuturePositionHandler(const TradeHrPtr& trade_hr);
            ~ChinaFuturePositionHandler(){}

            void addTradeInfo(const TradeHrPtr& trade_hr_ptr) override;

            // ���ֲ�״̬,�Ƿ���Ҫ�Ӷ�����ɾ��;������ɾ��������Ӷ�����ɾ��
            void checkPositionStatus() override {}

            // ��ȡƷ��ID
            const PProductIDType getProductID() const;
            // ��ȡ��ƽ��־
            const OffsetType getOffsetType() const;

            PositionInfoPtr getPositionCopy() const override;
        };


		// ��ȯ��Ϣ����
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

			// ���ֲ�״̬,�Ƿ���Ҫ�Ӷ�����ɾ��;������ɾ��������Ӷ�����ɾ��
			void checkPositionStatus() override;

			PositionInfoPtr getPositionCopy() const override;

		private:
			void createByTradeHr(const TradeHrPtr& trade_hr) override;
		};
    }
}

#endif