/*************************************************
Copyright (C), 2017, HX Tech Co., Ltd.
File name:      struct_extern.h
Author:			XuYC
Version:
Date:
Description:    �ṩ����Ľṹ�嶨��,�ӿ�����ٶ�
*************************************************/

#ifndef __STRUCT_EXTERN_H__
#define __STRUCT_EXTERN_H__

#include <memory>
#include "struct_base.h"

namespace AllTrade {
    namespace NPMgrCenter {
#pragma region �˻�
        //////////////////////////////////////////////////////////////////////////
        // ���˻�
        struct RootAccount : public SAccountBase
        {
            int                 allow_max_level_;   // ������������㼶
            int                 allow_max_num_;     // ���������������
            
            RootAccount();
        };

        // �����˻�
        struct AgencyAccount : public SAccountBase
        {
            UserIDType          fund_user_id_;    // �ʽ��˻�ID

            E_AGENCY_PROP       agency_prop_;          // �����˻�����(������/����)
            int                 allow_max_level_;   // ������������㼶
            int                 allow_max_num_;     // ���������������

            AgencyAccount();
        };

        // ����˻�
        struct RiskAccount : public SAccountBase
        {
            RiskAccount();
        };

        // �����˻�
        struct ManagerAccount : public SAccountBase
        {
            ManagerAccount();
        };

        // �����˻�
        struct TradeAccount : public SAccountBase
        {
            TradeAccount();

            UserIDType  fund_user_id_;  // ʵ���˻�����
        };

        // �ʽ��˻�
        struct FunderAccount : public SAccountBase
        {
            FunderAccount();

            FundCompanyType fund_company_;  // ʵ���˻���Ӧ��˾����
        };

#pragma endregion

#pragma region ������
        struct SStockContract : public SContractBase
        {
            Feest           close_yestoday_fee_;    // ƽ��������

            ContractPYCodeType      contract_py_code_;
            DisplayPropType         display_prop_;
            DisplayPropTypeType     display_prop_type_;
            PlatePropType           plate_prop_;
            StockAreaType           stock_area_;
            StockStatusType         stock_status_;
            StockPlateAreaType      stock_plate_area_;
            YDouble                 total_shares_;  // �ܹɱ�

            SStockContract();
        };

        struct SForeignFutureContract : public SContractBase
        {
            ProductIDType           product_id_;	    // ����Ʒ��ID, ��ʽ��GUID; ��Ʒ�ֵ��������ھ���Ψһ��

            SForeignFutureContract();
        };
#pragma endregion
    }

    namespace NPTradeCenter {
#pragma region ί��
        //////////////////////////////////////////////////////////////////////////
        // ��Ʊ�µ�ί����Ϣ
        struct StockOrderInfo : public OrderInfoBase
        {
            StockAreaType   stock_area_;

            YDouble         cur_trade_fee_;     // ��ǰ����Ӷ��������
            YDouble         cur_stamp_fee_;     // ��ǰƽ��ӡ��˰��
            YDouble         cur_transfer_fee_;  // ��ǰ������
            YDouble         cur_infomatch_fee_; // ��ǰ��Ϣ��Ϸ�

            StockOrderInfo();
        };

        // �����ڻ��µ�ί����Ϣ
        struct ForeignFutureOrderInfo : public OrderInfoBase
        {
            ProductIDType   product_id_;    // Ʒ��ID

            ForeignFutureOrderInfo();
        };

        // �����ڻ��µ�ί����Ϣ
        struct ChinaFutureOrderInfo : public OrderInfoBase
        {
            ProductIDType   product_id_;    // Ʒ��ID
            OffsetType      offset_type_;   // ��ƽ����

            ChinaFutureOrderInfo();
        };
#pragma endregion

#pragma region �ɽ�
        //////////////////////////////////////////////////////////////////////////
        // ��Ʊ�ɽ���Ϣ
        struct StockTradeInfo : public TradeInfoBase
        {            
            StockAreaType   stock_area_;
            YDouble         trade_fee_;     // ����Ӷ��������
            YDouble         stamp_fee_;     // ƽ��ӡ��˰
            YDouble         transfer_fee_;  // ������
            YDouble         infomatch_fee_; // ��Ϣ��Ϸ�

            StockTradeInfo();
        };

        // �����ڻ��ɽ���Ϣ
        struct ForeignFutureTradeInfo : public TradeInfoBase
        {
            ProductIDType   product_id_;    // Ʒ��ID

            ForeignFutureTradeInfo();
        };

        // �����ڻ��ɽ���Ϣ
        struct ChinaFutureTradeInfo : public TradeInfoBase
        {
            ProductIDType   product_id_;    // Ʒ��ID
            OffsetType      offset_type_;   // ��ƽ����

            ChinaFutureTradeInfo();
        };
#pragma endregion

#pragma region �ֲ�
        //////////////////////////////////////////////////////////////////////////
        // ��Ʊ�ֲ���Ϣ
        struct StockPositionInfo : public PositionInfoBase
        {
            StockAreaType   stock_area_;

            StockPositionInfo();
        };

        // �����ڻ��ֲ���Ϣ
        struct ForeignFuturePositionInfo : public PositionInfoBase
        {
            ProductIDType   product_id_;    // Ʒ��ID

            ForeignFuturePositionInfo();
        };

        // �����ڻ��ֲ���Ϣ
        struct ChinaFuturePositionInfo : public PositionInfoBase
        {
            ProductIDType   product_id_;    // Ʒ��ID
            OffsetType      offset_type_;   // ��ƽ����

            ChinaFuturePositionInfo();
        };
#pragma endregion

#pragma region ��ȯ
		// ��ȯ�ֲ�
		struct MarginPositionInfo : public PositionInfoBase
		{
			UserIDType			user_id_;				// �û�ID
			// DateTimeType        datetime_;				// ����ʱ��
			StockAreaType		stock_area_;

			MarginPositionInfo();;
		};

		// ��ȯ�ɽ�
		struct MarginTradeInfo :public TradeInfoBase
		{
			StockAreaType   stock_area_;
			YDouble         trade_fee_;     // ����Ӷ��������
			YDouble         stamp_fee_;     // ƽ��ӡ��˰
			YDouble         transfer_fee_;  // ������
			YDouble         infomatch_fee_; // ��Ϣ��Ϸ�
			UserIDType			user_id_;				// �û�ID

			YDouble         day_interset_;  // ����Ϣ
			YDouble         interset_fund_; // ��Ϣ�ʽ�

			MarginTradeInfo();;
		};

		// ��ȯί��
		struct MarginOrderInfo : public OrderInfoBase
		{
			UserIDType			user_id_;				// �û�ID
			StockAreaType   stock_area_;

			YDouble         cur_trade_fee_;     // ��ǰ����Ӷ��������
			YDouble         cur_stamp_fee_;     // ��ǰƽ��ӡ��˰��
			YDouble         cur_transfer_fee_;  // ��ǰ������
			YDouble         cur_infomatch_fee_; // ��ǰ��Ϣ��Ϸ�

			MarginOrderInfo();;
		};

		
#pragma endregion

    }
}

#endif