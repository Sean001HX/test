/*************************************************
Copyright (C), 2017, HX Tech Co., Ltd.
File name:      struct_base.h
Author:			XuYC
Version:
Date:
Description:    �ṩͳһ�Ļ����ṹ�嶨��,ÿ���ṹ���ָ�붨�����struct_declare.h��
*************************************************/

#ifndef __STRUCT_BASE_H__
#define __STRUCT_BASE_H__

#include <memory>
#include <vector>
#include "params_declare.h"
#include "ystruct_define.h"

//////////////////////////////////////////////////////////////////////////
// �������
namespace AllTrade {
    namespace NPMgrCenter {
#pragma region �˻�
        ///////////////////////////////////////////// �˻�������ϵ //////////////////////////////////////
        //�û���Ϣ����
        struct SAccountBase
        {
            UserIDType          user_id_;           // �˻�ID
            UserIDType          create_id_;         // �������˻�ID
            UserIDType          parent_id_;         // ��������ID
            int                 level_;             // �㼶, supermgrΪ0
            LoginNameType       login_name_;        // ��¼�� 
            NickNameType        nick_name_;         // �ǳ� 
            LoginPasswordType   password_;          // ����
            AccountNameType     account_name_;      // �˻��� 
            E_ACCOUNT_PROP      prop_;              // �˻�����,����/����
            E_ACCOUNT_TYPE      type_;              // �˻�����,ʵ��/ģ��
            E_ACCOUNT_STATUS    status_;            // �˻�״̬
            E_PERMISSION_TYPE   permission_;        // �˻�Ȩ����Ȩ��ʽ,�Զ�/�ֶ�
            PopularizeLinkType  agent_link_;        // �ƹ�����
            RealNameType        real_name_;         // ��ʵ����
            PhoneNumberType     phone_number_;      // �ֻ���
            IdentityIDType      identity_;          // ���֤��
            DateTimeType        regist_datetime_;   // ����ʱ��
            DateTimeType        update_datetime_;   // ����ʱ��
            DateTimeType        vaild_datetime_;    // ��Ч��ʱ��

			UserIDType          auditor_name_;         // ����˻�
			DateTimeType        auditor_datetime_;    // ���ʱ��
            SAccountBase();
            virtual ~SAccountBase() {}
        };

        // �����ʻ�
        struct SOnlineAccount
        {
            UserIDType          user_id_;           // �˻�ID
            int                 session_id_;        // ����ID
            DateTimeType        login_datetime_;    // ��¼ʱ��
            OperatorTradeType   op_type_;           // ��½�˿�����
            LoginIpType         login_ip_;          // ��¼ip
            MachineInfoType     mac_info_;          // mac����

            SOnlineAccount();
        };

#pragma endregion

#pragma region �ʽ���Ϣ
        // �ʽ���Ϣ����
        struct SMoneyInfo
        {
            YDouble     position_cost_price_;   // �ֲ��ܼ�(�ۼ�)
            int         position_all_vol_;      // �ֲ�������
            YDouble     trading_fee_;           // ������������(�ۼ�,������,ӡ��...)
            YDouble     customize_fee_;         // �Զ���������(�ۼ�,��Ϣ��Ϸ�)

            YDouble     logic_can_extract_;     // �߼�����ȡ���(��)
            YDouble     logic_wait_thaw_;       // �߼����ⶳ���(T+0ʱΪ0)
            YDouble     order_freeze_;          // �ύί��ʱ��ռ���ʽ�(��������)

            YDouble     user_deposit_;          // �û���֤��(����Ϊ�״ο�����ֵ���),�ʽ��ʻ���Ϊ�������ʽ���
            YDouble     priority_fund_;         // ����/�����ʽ�

            YDouble getAllTradeFee() const;          // ��ȡ������������(��)

            YDouble getAllCanExtract() const;   // ��ȡʵ�ʿ���ȡ���(��)
            YDouble getCanExtract() const;      // ��ȡʵ�ʿ���ȡ���(�û�)
            YDouble getCanUse() const;          // ��ȡʵ�ʿ��ý��(��)

            void addDeposit(YDouble money);       // �����û���֤��
            void addEquipment(YDouble money);     // ��������

            void orderFreeze(YDouble money);      // ί���ύʱ�����ʽ�
            void cancelOrderThaw(YDouble money);  // ί�г���ʱ�ⶳ�ʽ�
            void moneySettle();                   // ����

            SMoneyInfo();

        private:
        };

        // �ʽ���ϸ����
        struct SMoneyDetailInfo
        {
            MoneyStreamType     stream_;
            YDouble             total_before_;
            SMoneyInfo          money_before_;
            YDouble             total_after_;
            SMoneyInfo          money_after_;
            YDouble             change_money_;
            Money_Change_Type   change_type_;
            RemarkTextType      remark_;
            DateTimeType        date_time_;

            SMoneyDetailInfo();
        };

        // �����Ϣ
        struct SRiskInfo
        {
            YDouble     warningline_;   // ������, �����û���ǰ���ʲ� - ���� - �Ӻ�/ �Ӻ��ʽ�
            YDouble     forceline_;     // ǿƽ�� = ������
            YDouble     limitline_;     // �޲���, ���ֲ���ֵ+�����ʽ�/���ʲ�
            YDouble     lever_rate_;    // �ܸ˱���
            YDouble     commissionrate_;// ������Ӷ�����(ǧ��֮)
            YDouble     custom_commissionrate_;// ��Ϸ�Ӷ�����(ǧ��֮)
            YDouble     procommrate_;   // �ֳɱ���(ǧ��֮)

            SRiskInfo();
        };

        // �����ʽ���Ϣ����
        struct SApplyMoneyInfo
        {
            ApplyMoneyIDType        apply_money_id_;
            E_APPLY_MONEY_STATUS    apply_status_;
            UserIDType              approval_user_id_;  // ������û�ID
            UserIDType              user_id_;           // ������ID
            YDouble                 apply_money_;       // �����ʽ�
            DateTimeType            apply_date_time_;   // ��������
            DateTimeType            approval_date_time_;// �������
            OIMM_Change_Type        money_type_;        // �����ʽ�����

            RealNameType            real_name_;         // ��ʵ����
            BankNameType            bank_name_;         // ������
            BankCardNoType          bank_card_;         // ���п���

            SApplyMoneyInfo();
        };

        // ����Ӷ��/�ֳ��ʽ���ϸ����
        struct SAgencyMoneyDetailInfo
        {
//             MoneyStreamType     stream_;
            UserIDType          user_id_;
            UserIDType          source_user_id_;// Ӷ�������Դ
            YDouble             total_before_;  // δ����
            YDouble             total_after_;   // δ����
            YDouble             change_money_;
            Agency_Money_Change_Type   change_type_;
            RemarkTextType      remark_;
            DateTimeType        date_time_;
            DateType            date_;
            YDouble             commission_rate_;   // ��ǰӶ�����,ǧ��֮

            SAgencyMoneyDetailInfo();
        };

#pragma endregion

#pragma region ������
        //////////////////////////////////////////////////////////////////////////
        // ������/���ױ�֤��ṹ��
        struct Feest
        {
            YDouble	        fee_;	// ������/���ױ�֤��
            bool            bFix_;	// �Ƿ���ù̶�ֵ,trueΪ���ù̶�ֵ,falseΪ�ٷֱ�
            Feest();
        };

        // ʱ��νṹ��,��ɽ���ʱ���
        struct TimePeriod
        {
            TimeType     start_time_;    // eg: hh:mm:ss
            TimeType     end_time_;      // eg: hh:mm:ss

            TimePeriod();
        };

        //////////////////////////////////////////////////////////////////////////
        // ��������Ϣ
        struct SExchange
        {
            ExchangeIDType          exchange_id_;	    // ������ID, ��ʽ��GUID; �ڽ��������������ھ���Ψһ��
            ExchangeNameType        exchange_name_;	    // ����������
            ExchangeCodeType        exchange_code_;	    // ����������
            TimePeriod              orderable_time_;    // ���ύί��ʱ���
            std::vector<TimePeriod> tradable_time_;		// �ɽ���ʱ���
            CommodityTypeType       commodity_type_;    // ��Ʒ����(��Ʊ/�ڻ�/...)
            YDouble                 open_margin_;       // ������֤��

            SExchange();
        };

        //////////////////////////////////////////////////////////////////////////
        // Ʒ����Ϣ
        struct SProductInfo
        {
            ExchangeIDType          exchange_id_;	        // ����������ID, ��ʽ��GUID; �ڽ��������������ھ���Ψһ��
            ProductIDType           product_id_;	        // Ʒ��ID, ��ʽ��GUID; ��Ʒ�ֵ��������ھ���Ψһ��
            ProductNameType         product_name_;	        // Ʒ����
            ProductCodeType         product_code_;	        // Ʒ�ִ���
            CommodityTypeType       commodity_type_;        // ��Ʒ����(�����ڻ�/�����ڻ�/...)
            CurrencyIDType          currency_id_;	        // Ʒ�����û��ʵ�λ
            std::vector<TimePeriod> tradable_time_;		    // �ɽ���ʱ���

            YDouble                 min_price_change_;      // ��С�䶯��λ
            int                     contract_multiplier_;   // ��Լ����
            Feest                   open_fee_;              // ����������
            Feest                   close_yestoday_fee_;    // ƽ��������
            Feest                   close_today_fee_;       // ƽ��������
            Feest                   margin_fee_;            // ��֤��

            SProductInfo();
        };

        //////////////////////////////////////////////////////////////////////////
        // ��Լ��Ϣ
        struct SContractBase
        {
            ExchangeIDType          exchange_id_;	    // ����������ID, ��ʽ��GUID; �ڽ��������������ھ���Ψһ��
            ContractIDType          contract_id_;	    // ��ԼID, ��ʽ��GUID; �ں�Լ���������ھ���Ψһ��
            ContractNameType        contract_name_;	    // ��Լ����	
            ContractCodeType        contract_code_;	    // ��Լ����
            CommodityTypeType       commodity_type_;    // ��Ʒ����(��Ʊ/�ڻ�/...)
            CurrencyIDType          currency_id_;	    // ��Լ���û��ʵ�λ
            ContractLastDays        last_days_;         // ��Լ����������(��Լ���м��쵽��), -1��ʾ����ʱ��
            DateType                open_datetime_;     // ����ʱ��, eg:yyyy-MM-dd
            DateTimeType            delivery_datetime_; // ������ʱ��, eg:yyyy-MM-dd hh:mm:ss
            DateTimeType            trade_datetime_;    // ���ɿ���ʱ��, eg:yyyy-MM-dd hh:mm:ss

            YDouble                 min_price_change_;      // ��С�䶯��λ
            int                     contract_multiplier_;   // ��Լ����
            Feest                   open_fee_;              // ����������
//             Feest                   close_today_fee_;       // ƽ��������
            Feest                   margin_fee_;            // ��֤��

            SContractBase();
            virtual ~SContractBase(){}
        };

        //////////////////////////////////////////////////////////////////////////
        // ������Ϣ
        struct SCurrencyInfo
        {
            CurrencyIDType      currency_id_;	    // ����id,GUID
            CurrencyNameType    currency_name_;	    // ������
            CurrencyCodeType    currency_code_;	    // ���ִ���
            bool                isBaseCurrency_;    // �Ƿ�Ϊ����
            YDouble             rate_for_base_;     // ��Ӧ���һ���
            YDouble             rate_for_rmb_;      // ��Ӧ����һ���

            SCurrencyInfo();
        };
#pragma endregion

        // �ͻ��Զ�����ò�����Ӷ����Ϣ
        struct CustomCommInfo
        {
            UserIDType          user_id_;           // �˻�ID
            YDouble             change_money_;      // �ı���

            UserIDType          trade_user_id_;     // �����ն��˻�ID,������Ӷ��Ľ����˻�
            DateTimeType        date_time_;         // ����ʱ��
      
            CustomCommInfo();
        };

		// ��Ϣͳ��
		struct InterestStatistics{
			UserIDType          user_id_;
			YDouble				sum_interest_;		// �ۼ���Ϣ

			InterestStatistics();
		};
		// ��Ϣ��ϸ
		struct InterestDetail{
			UserIDType          user_id_;	
			double				sum_interest_;		// �ۼ���Ϣ
			DateTimeType        date_time_;			// �䶯ʱ��
			Agency_Money_Change_Type   change_type_;// �䶯����
			UserIDType          source_user_id_;	// ��Դ
			YDouble             interest_rate_;		// ��Ϣ����

			InterestDetail();
		};

    }

    namespace NPTradeCenter{
#pragma region ί��
        // �µ�ί����Ϣ����
        struct OrderInfoBase
        {
            OrderStreamType         order_stream_;          // �µ�ί������(ȫ��Ψһ)
            OrderIDType             order_id_;              // �µ�ί��ID
            ContractIDType          contract_id_;           // ��ԼID
            OrderStateType          order_state_;           // ί��״̬����(�ѹ���/...)
            OrderStateExplainType   orser_state_explain_;   // ί��״̬˵��
            OrderRefType            order_localtmp_ref_;    // �����ύ����ʱ���,�����ڿͻ�������ʶ��
            OrderRefType            order_ref_;             // �µ�ί���ύ���
            ShadowOrderIDType       shadow_order_id_;       // Ӱ�Ӷ������
            DateTimeType            generate_datetime_;     // ί�д�������ʱ��
            DateTimeType            update_datetime_;       // ί��״̬����������ʱ��
            DirectType              direct_type_;           // ��������
            YDouble                 currency_rate_;         // �뵱ǰ���һ���
            CurrencyIDType          currency_id_;           // ����ID
            YDouble                 order_price_;           // ί�м۸�,�м�Ϊ0
            int                     order_vol_;             // ί������
            int                     effected_vol_;          // ����Ч����,�Ѽ��뱾�����ݿ���Ϣ����
            int                     trade_vol_;             // �ѳɽ�����,ʵ���ѳɽ�,����һ���������ݿ�ǰ������,ʵʱ����
            OrderTypeType           order_type_;            // �µ�ί������(�޼�/�м�/...)
            OrderTradeModeType      order_trade_mode_;      // ί�н���ģʽ,�Ƿ���Ҫͬ����ʵ������
            YDouble                 order_trade_price_;     // ί�гɽ���
            SystemIDType            system_order_id_;       // ʵ��ί�б��
            ExchangeIDType          exchange_id_;           // ������ID
            ApiTypeType             api_type_;              // �ӿ�����(CTP/ESUNNY/...)
            CommodityTypeType       commodity_type_;        // ��Ʒ����(��Ʊ/�ڻ�/...)
            OperatorTradeType       op_type_;               // ����Ա����(PC/MC/...)
            OrderModeType           order_mode_;            // �µ�ί��ģʽ(FAK/...)
            DateTimeType	        valid_datetime_;		// ��Ч����(GTD�����ʹ��)

            YDouble                 freeze_money_;          // �����ʽ�
            YDouble                 position_cost_;         // �ֲֳɱ�

            bool                    b_freeze_money_;        // �Ƿ��ж����ʽ�
            bool                    b_freeze_position_;     // �Ƿ��ж���ֲ�

            OrderInfoBase();
            virtual ~OrderInfoBase(){}
        };

        // ����ί����Ϣ,������Ϣ����,����TC�ڲ�ʹ��
        struct CancelOrderInfo
        {
            OrderStreamType     order_stream_;        // �µ�ί������
            CommodityTypeType   commodity_type_;      // ��Ʒ����(��Ʊ/�ڻ�/...)

            CancelOrderInfo();
            virtual ~CancelOrderInfo(){}
        };
#pragma endregion

#pragma region �ɽ�
        // �ɽ���Ϣ����
        struct TradeInfoBase
        {
            TradeIDType         trade_id_;              // �ɽ�ID
            ShadowTradeIDType   shadow_trade_id_;       // Ӱ�ӳɽ����
            OrderStreamType     order_stream_;          // �µ�ί������
            PositionIDType      position_id_;           // �ֲ�ID
            ContractIDType      contract_id_;           // ��ԼID
            int                 volume_;                // �ɽ�����
            DirectType          direct_type_;           // ��������
            YDouble             currency_rate_;         // �뵱ǰ���һ���
            CurrencyIDType      currency_id_;           // ����ID
            YDouble             trade_price_;           // �ɽ��۸�
            DateTimeType        generate_datetime_;     // �ɽ�����ʱ��
            ShadowOrderIDType   shadow_order_id_;       // Ӱ�Ӷ������
            SystemIDType        system_order_id_;       // ʵ��ί�б��
            SystemIDType        system_trade_id_;       // ʵ�̳ɽ����
            ExchangeIDType      exchange_id_;           // ������ID
            ApiTypeType         api_type_;              // �ӿ�����(CTP/ESUNNY/...)
            CommodityTypeType   commodity_type_;        // ��Ʒ����(��Ʊ/�ڻ�/...)
            OperatorTradeType   op_type_;               // ����Ա����(PC/MC/...)

            YDouble             close_profit_;          // ƽ��ӯ��

            TradeInfoBase();
            virtual ~TradeInfoBase(){}
        };
#pragma endregion

#pragma region �ֲ�
        // �ֲ���Ϣ����
        struct PositionInfoBase
        {
            PositionIDType      position_id_;           // �ֲ�ID
            ContractIDType      contract_id_;           // ��ԼID
            int                 volume_;                // �ֲ�����
            int                 T_volume_;              // ��ΪT+1���µĶ�������
            DirectType          direct_type_;           // ��������
            CurrencyIDType      currency_id_;           // ����ID
            YDouble             trade_ave_price_;       // �ɽ�����
            YDouble             cost_price_;            // �ֲֳɱ�
            ExchangeIDType      exchange_id_;           // ������ID
            CommodityTypeType   commodity_type_;        // ��Ʒ����(��Ʊ/�ڻ�/...)
            int                 freeze_order_vol_;      // �ύƽ��ί��ʱ�Ķ�������

            PositionInfoBase();
            virtual ~PositionInfoBase(){}
        };
#pragma endregion

		
        // ������Ϣ���ݻ���
        struct QuoteInfoBase
        {
            ContractIDType      contract_id_;       // ��ԼID
            CurrencyIDType      currency_id_;       // ����ID
            YDouble             last_price_;        // ��Լ���¼�
            YDouble             yclose_price_;      // ������,ͨ������:������*1.1=��ͣ��,������λ;������*0.9=��ͣ��,������λ
            YDouble             ysettle_price_;     // ������
            YDouble             open_price_;        // ���̼�
            YDouble             ask_price_[5];      // �嵵������, ��һ �� �����
            int                 ask_volume_[5];     // �嵵������, ��һ �� ������
            YDouble             bid_price_[5];      // �嵵�����飬��һ �� �����
            int                 bid_volume_[5];     // �嵵�����飬��һ �� ������
            QuoteStatusType     quote_status_;      // ��������״̬

            YDouble             highest_price_;     // ��ͣ��
            YDouble             lowest_price_;      // ��ͣ��

            QuoteInfoBase();
            ~QuoteInfoBase(){}
        };

        // ������Ϣ����
        struct TradeFee
        {
            YDouble trade_commission_;      // ������Ӷ��(��)
            YDouble min_trade_commission_;  // ��С������Ӷ��(Ԫ)
            YDouble stamp_duty_;            // ӡ��˰(��)(ƽ��ʱ��ȡ)
            YDouble transfer_;              // ������(��)
            YDouble info_match_;            // ��Ϸ�(��)
            YDouble user_profit_rate_;      // ����Ա�ֳɱ���(��)

            TradeFee();
        };

        // �����Ϣ
        struct ImmRiskControlSt
        {
            AllTrade::UserIDType        user_id_;   // �����˻�ID
            AllTrade::RiskControlType   rc_type_;   // �������
            bool                        bTrigger_;  // �Ƿ��ڴ���״̬
            DateTimeType                date_time_; // ���һ�δ���ʱ��
			RemarkTextType				trigger_text_; // ��������

            ImmRiskControlSt();
        };

        // ��ֹ���׷�ع���ṹ��
        struct SForbidTradeInfo
        {
            ForbidTradeType         forbid_trade_type_;     // ��ֹ���׹�������
            ForbidTradeOperatorType forbid_trade_op_type_;  // ��ֹ���ײ�������
            bool                    bstart_;                // �Ƿ���

            SForbidTradeInfo();
        };

        // �ֱֲ�����ع���ṹ��
        struct SPositionRateInfo
        {
            PositionRateType        position_rate_type_;    // �ֱֲ�������
            int                     position_rate_;         // �ֱֲ���,30%������Ϊ30
            bool                    bstart_;                // �Ƿ���

            SPositionRateInfo();
        };

        // ȫ��������Ϣ
        struct GlobalData
        {
            int     shadow_order_id_;      // Ӱ�Ӷ���ID
            int     shadow_trade_id_;      // Ӱ�ӳɽ�ID

            GlobalData();
        };

		
		// ��ȯ��Ϣ
		struct MarginInfo
		{
			int					sum_Margin_Qty_;		// ��ȯ������
			double				Interest_;				// ��ȯ��Ϣ

			MarginInfo();
		};


		// ��ȯʣ����Ϣ
		struct MarginLeftInfo
		{
			ContractIDType      contract_id_;           // ��ԼID
			int					left_Margin_Qty_;		// ��ȯʣ������

			MarginLeftInfo();
		};
    }
#pragma region Ȩ�޿���
    ///////////////////////////////////////////// Ȩ�޿��� //////////////////////////////////////
    // Ȩ��ҵ��
    struct AuthorityBussnesses
    {
        int					bussnessID;								// ҵ��ID
        BussnessName		bussnessName;							// ҵ������
        int					bussnessType;							// ҵ������ 1���˵�2������
        int					bussnessAddr;							// ҵ���ַ
        int					parentBussnessID;						// ��ҵ��ID
        IsHide				isHide;									// �Ƿ����� IsHide_Hide ���� IsHide_NoIsHide����

        AuthorityBussnesses(){ memset(this, 0 ,sizeof(*this)); }
        ~AuthorityBussnesses(){}

    };
    // ��־��¼
    struct AuthorityChangeLog
    {
		LoginNameType		login_name_;						// �����ý�ɫ���û�
        int					changeDate;							// ��ɫ��������
        int					changeTime;							// ��ɫ����ʱ��
        LogContent			content;							// ����

        AuthorityChangeLog(){ memset(this, 0, sizeof(*this)); }
        ~AuthorityChangeLog(){}

    };

    // Ȩ�޹���
    struct AuthorityFunctions
    {
        int					functionID;							// ����ID
        int					bussnessID;							// ҵ��ID
        FunctionName		functionName;						// ��������
        IsSort				issort;								// ����  IsSort_NoSort������ IsSort_Sort����

        AuthorityFunctions(){ memset(this, 0, sizeof(*this)); }
        ~AuthorityFunctions(){}

    };

    // �˻�Ȩ�޹���
    struct AuthorityFunctionsUserId
    {
		LoginNameType		login_name_;						// �����ý�ɫ���û�
        int					functionID;							// ����ID
        int					bussnessID;							// ҵ��ID
		int					NavigationID;						// ����ID
        FunctionName		functionName;						// ��������
        IsSort				issort;								// ����  IsSort_NoSort������ IsSort_Sort����

        AuthorityFunctionsUserId(){ memset(this, 0, sizeof(*this)); }
        ~AuthorityFunctionsUserId(){}
    };

    // Ȩ�޽�ɫ����
    struct AuthorityRoleFunctions
    {
        int					id;									// id
        int					roleID;								// ��ɫID
        int					functionID;							// ����ID

        AuthorityRoleFunctions(){ memset(this, 0, sizeof(*this)); }
		~AuthorityRoleFunctions(){}

    };

    // Ȩ�޽�ɫ�û�
    struct AuthorityRoleUsers
    {
        int					id;									// id
		LoginNameType		login_name_;						// �����ý�ɫ���û�
        int					rolesID;							// ��ɫID

        AuthorityRoleUsers(){ memset(this, 0, sizeof(*this)); }
		~AuthorityRoleUsers(){}

    };

    // Ȩ�޽�ɫ
    struct AuthorityRoles
    {
        int					rolesID;							// ��ɫID
        RolesName			rolesName;							// ��ɫ����
		LoginNameType		login_name_;						// �����ý�ɫ���û�
        int					createDate;							// ��ɫ�������� 
        int					createTime;							// ��ɫ����ʱ��
		E_RolesType		    rolesType;							// ��ɫ����( ���� / ����Ա)
		E_OperationType		operationType;						// ��������( ����0 / ���ɲ���1)


        AuthorityRoles(){ memset(this, 0, sizeof(*this)); }
        ~AuthorityRoles(){}
    };
#pragma endregion
}

#endif