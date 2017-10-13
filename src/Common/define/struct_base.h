/*************************************************
Copyright (C), 2017, HX Tech Co., Ltd.
File name:      struct_base.h
Author:			XuYC
Version:
Date:
Description:    提供统一的基础结构体定义,每个结构体的指针定义放在struct_declare.h中
*************************************************/

#ifndef __STRUCT_BASE_H__
#define __STRUCT_BASE_H__

#include <memory>
#include <vector>
#include "params_declare.h"
#include "ystruct_define.h"

//////////////////////////////////////////////////////////////////////////
// 交易相关
namespace AllTrade {
    namespace NPMgrCenter {
#pragma region 账户
        ///////////////////////////////////////////// 账户管理体系 //////////////////////////////////////
        //用户信息基类
        struct SAccountBase
        {
            UserIDType          user_id_;           // 账户ID
            UserIDType          create_id_;         // 创建者账户ID
            UserIDType          parent_id_;         // 所属父级ID
            int                 level_;             // 层级, supermgr为0
            LoginNameType       login_name_;        // 登录名 
            NickNameType        nick_name_;         // 昵称 
            LoginPasswordType   password_;          // 密码
            AccountNameType     account_name_;      // 账户名 
            E_ACCOUNT_PROP      prop_;              // 账户属性,管理/交易
            E_ACCOUNT_TYPE      type_;              // 账户类型,实盘/模拟
            E_ACCOUNT_STATUS    status_;            // 账户状态
            E_PERMISSION_TYPE   permission_;        // 账户权限授权方式,自动/手动
            PopularizeLinkType  agent_link_;        // 推广连接
            RealNameType        real_name_;         // 真实姓名
            PhoneNumberType     phone_number_;      // 手机号
            IdentityIDType      identity_;          // 身份证号
            DateTimeType        regist_datetime_;   // 开户时间
            DateTimeType        update_datetime_;   // 更新时间
            DateTimeType        vaild_datetime_;    // 有效期时间

			UserIDType          auditor_name_;         // 审核账户
			DateTimeType        auditor_datetime_;    // 审核时间
            SAccountBase();
            virtual ~SAccountBase() {}
        };

        // 在线帐户
        struct SOnlineAccount
        {
            UserIDType          user_id_;           // 账户ID
            int                 session_id_;        // 连接ID
            DateTimeType        login_datetime_;    // 登录时间
            OperatorTradeType   op_type_;           // 登陆端口类型
            LoginIpType         login_ip_;          // 登录ip
            MachineInfoType     mac_info_;          // mac编码

            SOnlineAccount();
        };

#pragma endregion

#pragma region 资金信息
        // 资金信息基类
        struct SMoneyInfo
        {
            YDouble     position_cost_price_;   // 持仓总价(累计)
            int         position_all_vol_;      // 持仓总手数
            YDouble     trading_fee_;           // 交易所手续费(累计,含过户,印花...)
            YDouble     customize_fee_;         // 自定义手续费(累计,信息撮合费)

            YDouble     logic_can_extract_;     // 逻辑可提取金额(总)
            YDouble     logic_wait_thaw_;       // 逻辑待解冻金额(T+0时为0)
            YDouble     order_freeze_;          // 提交委托时的占用资金(含手续费)

            YDouble     user_deposit_;          // 用户保证金(配资为首次开户充值金额),资金帐户中为可配资资金金额
            YDouble     priority_fund_;         // 配资/优先资金

            YDouble getAllTradeFee() const;          // 获取交易总手续费(总)

            YDouble getAllCanExtract() const;   // 获取实际可提取金额(总)
            YDouble getCanExtract() const;      // 获取实际可提取金额(用户)
            YDouble getCanUse() const;          // 获取实际可用金额(总)

            void addDeposit(YDouble money);       // 增加用户保证金
            void addEquipment(YDouble money);     // 增加配资

            void orderFreeze(YDouble money);      // 委托提交时冻结资金
            void cancelOrderThaw(YDouble money);  // 委托撤销时解冻资金
            void moneySettle();                   // 结算

            SMoneyInfo();

        private:
        };

        // 资金明细基类
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

        // 风控信息
        struct SRiskInfo
        {
            YDouble     warningline_;   // 警告线, 亏损（用户当前总资产 - 优先 - 劣后）/ 劣后资金
            YDouble     forceline_;     // 强平线 = 警告线
            YDouble     limitline_;     // 限仓线, （持仓市值+冻结资金）/总资产
            YDouble     lever_rate_;    // 杠杆比例
            YDouble     commissionrate_;// 交易所佣金比例(千分之)
            YDouble     custom_commissionrate_;// 撮合费佣金比例(千分之)
            YDouble     procommrate_;   // 分成比例(千分之)

            SRiskInfo();
        };

        // 申请资金信息基类
        struct SApplyMoneyInfo
        {
            ApplyMoneyIDType        apply_money_id_;
            E_APPLY_MONEY_STATUS    apply_status_;
            UserIDType              approval_user_id_;  // 审核者用户ID
            UserIDType              user_id_;           // 申请者ID
            YDouble                 apply_money_;       // 申请资金
            DateTimeType            apply_date_time_;   // 申请日期
            DateTimeType            approval_date_time_;// 审核日期
            OIMM_Change_Type        money_type_;        // 申请资金类型

            RealNameType            real_name_;         // 真实姓名
            BankNameType            bank_name_;         // 银行名
            BankCardNoType          bank_card_;         // 银行卡号

            SApplyMoneyInfo();
        };

        // 机构佣金/分成资金明细基类
        struct SAgencyMoneyDetailInfo
        {
//             MoneyStreamType     stream_;
            UserIDType          user_id_;
            UserIDType          source_user_id_;// 佣金费用来源
            YDouble             total_before_;  // 未启用
            YDouble             total_after_;   // 未启用
            YDouble             change_money_;
            Agency_Money_Change_Type   change_type_;
            RemarkTextType      remark_;
            DateTimeType        date_time_;
            DateType            date_;
            YDouble             commission_rate_;   // 当前佣金比例,千分之

            SAgencyMoneyDetailInfo();
        };

#pragma endregion

#pragma region 交易所
        //////////////////////////////////////////////////////////////////////////
        // 手续费/交易保证金结构体
        struct Feest
        {
            YDouble	        fee_;	// 手续费/交易保证金
            bool            bFix_;	// 是否采用固定值,true为采用固定值,false为百分比
            Feest();
        };

        // 时间段结构体,如可交易时间段
        struct TimePeriod
        {
            TimeType     start_time_;    // eg: hh:mm:ss
            TimeType     end_time_;      // eg: hh:mm:ss

            TimePeriod();
        };

        //////////////////////////////////////////////////////////////////////////
        // 交易所信息
        struct SExchange
        {
            ExchangeIDType          exchange_id_;	    // 交易所ID, 格式：GUID; 在交易所的生存期内具有唯一性
            ExchangeNameType        exchange_name_;	    // 交易所名称
            ExchangeCodeType        exchange_code_;	    // 交易所代码
            TimePeriod              orderable_time_;    // 可提交委托时间段
            std::vector<TimePeriod> tradable_time_;		// 可交易时间段
            CommodityTypeType       commodity_type_;    // 商品类型(股票/期货/...)
            YDouble                 open_margin_;       // 开户保证金

            SExchange();
        };

        //////////////////////////////////////////////////////////////////////////
        // 品种信息
        struct SProductInfo
        {
            ExchangeIDType          exchange_id_;	        // 所属交易所ID, 格式：GUID; 在交易所的生存期内具有唯一性
            ProductIDType           product_id_;	        // 品种ID, 格式：GUID; 在品种的生存期内具有唯一性
            ProductNameType         product_name_;	        // 品种名
            ProductCodeType         product_code_;	        // 品种代码
            CommodityTypeType       commodity_type_;        // 商品类型(内盘期货/外盘期货/...)
            CurrencyIDType          currency_id_;	        // 品种所用汇率单位
            std::vector<TimePeriod> tradable_time_;		    // 可交易时间段

            YDouble                 min_price_change_;      // 最小变动单位
            int                     contract_multiplier_;   // 合约乘数
            Feest                   open_fee_;              // 开仓手续费
            Feest                   close_yestoday_fee_;    // 平昨手续费
            Feest                   close_today_fee_;       // 平今手续费
            Feest                   margin_fee_;            // 保证金

            SProductInfo();
        };

        //////////////////////////////////////////////////////////////////////////
        // 合约信息
        struct SContractBase
        {
            ExchangeIDType          exchange_id_;	    // 所属交易所ID, 格式：GUID; 在交易所的生存期内具有唯一性
            ContractIDType          contract_id_;	    // 合约ID, 格式：GUID; 在合约的生存期内具有唯一性
            ContractNameType        contract_name_;	    // 合约名称	
            ContractCodeType        contract_code_;	    // 合约代码
            CommodityTypeType       commodity_type_;    // 商品类型(股票/期货/...)
            CurrencyIDType          currency_id_;	    // 合约所用汇率单位
            ContractLastDays        last_days_;         // 合约到期日天数(合约还有几天到期), -1表示无限时间
            DateType                open_datetime_;     // 创建时间, eg:yyyy-MM-dd
            DateTimeType            delivery_datetime_; // 交割日时间, eg:yyyy-MM-dd hh:mm:ss
            DateTimeType            trade_datetime_;    // 最后可开仓时间, eg:yyyy-MM-dd hh:mm:ss

            YDouble                 min_price_change_;      // 最小变动单位
            int                     contract_multiplier_;   // 合约乘数
            Feest                   open_fee_;              // 开仓手续费
//             Feest                   close_today_fee_;       // 平今手续费
            Feest                   margin_fee_;            // 保证金

            SContractBase();
            virtual ~SContractBase(){}
        };

        //////////////////////////////////////////////////////////////////////////
        // 币种信息
        struct SCurrencyInfo
        {
            CurrencyIDType      currency_id_;	    // 币种id,GUID
            CurrencyNameType    currency_name_;	    // 币种名
            CurrencyCodeType    currency_code_;	    // 币种代码
            bool                isBaseCurrency_;    // 是否为基币
            YDouble             rate_for_base_;     // 对应基币汇率
            YDouble             rate_for_rmb_;      // 对应人民币汇率

            SCurrencyInfo();
        };
#pragma endregion

        // 客户自定义费用产生的佣金信息
        struct CustomCommInfo
        {
            UserIDType          user_id_;           // 账户ID
            YDouble             change_money_;      // 改变金额

            UserIDType          trade_user_id_;     // 交易终端账户ID,产生该佣金的交易账户
            DateTimeType        date_time_;         // 产生时间
      
            CustomCommInfo();
        };

		// 利息统计
		struct InterestStatistics{
			UserIDType          user_id_;
			YDouble				sum_interest_;		// 累计利息

			InterestStatistics();
		};
		// 利息明细
		struct InterestDetail{
			UserIDType          user_id_;	
			double				sum_interest_;		// 累计利息
			DateTimeType        date_time_;			// 变动时间
			Agency_Money_Change_Type   change_type_;// 变动类型
			UserIDType          source_user_id_;	// 来源
			YDouble             interest_rate_;		// 利息比例

			InterestDetail();
		};

    }

    namespace NPTradeCenter{
#pragma region 委托
        // 下单委托信息基类
        struct OrderInfoBase
        {
            OrderStreamType         order_stream_;          // 下单委托流号(全局唯一)
            OrderIDType             order_id_;              // 下单委托ID
            ContractIDType          contract_id_;           // 合约ID
            OrderStateType          order_state_;           // 委托状态类型(已挂起/...)
            OrderStateExplainType   orser_state_explain_;   // 委托状态说明
            OrderRefType            order_localtmp_ref_;    // 本地提交的临时编号,仅用于客户端自我识别
            OrderRefType            order_ref_;             // 下单委托提交编号
            ShadowOrderIDType       shadow_order_id_;       // 影子订单编号
            DateTimeType            generate_datetime_;     // 委托创建日期时间
            DateTimeType            update_datetime_;       // 委托状态最后更新日期时间
            DirectType              direct_type_;           // 买卖方向
            YDouble                 currency_rate_;         // 与当前基币汇率
            CurrencyIDType          currency_id_;           // 币种ID
            YDouble                 order_price_;           // 委托价格,市价为0
            int                     order_vol_;             // 委托手数
            int                     effected_vol_;          // 已生效手数,已计入本地数据库信息手数
            int                     trade_vol_;             // 已成交手数,实际已成交,但不一定计入数据库前的手数,实时数据
            OrderTypeType           order_type_;            // 下单委托类型(限价/市价/...)
            OrderTradeModeType      order_trade_mode_;      // 委托交易模式,是否需要同步真实交易所
            YDouble                 order_trade_price_;     // 委托成交价
            SystemIDType            system_order_id_;       // 实盘委托编号
            ExchangeIDType          exchange_id_;           // 交易所ID
            ApiTypeType             api_type_;              // 接口类型(CTP/ESUNNY/...)
            CommodityTypeType       commodity_type_;        // 商品类型(股票/期货/...)
            OperatorTradeType       op_type_;               // 操作员类型(PC/MC/...)
            OrderModeType           order_mode_;            // 下单委托模式(FAK/...)
            DateTimeType	        valid_datetime_;		// 有效日期(GTD情况下使用)

            YDouble                 freeze_money_;          // 冻结资金
            YDouble                 position_cost_;         // 持仓成本

            bool                    b_freeze_money_;        // 是否有冻结资金
            bool                    b_freeze_position_;     // 是否有冻结持仓

            OrderInfoBase();
            virtual ~OrderInfoBase(){}
        };

        // 撤单委托信息,用于消息传输,不在TC内部使用
        struct CancelOrderInfo
        {
            OrderStreamType     order_stream_;        // 下单委托流号
            CommodityTypeType   commodity_type_;      // 商品类型(股票/期货/...)

            CancelOrderInfo();
            virtual ~CancelOrderInfo(){}
        };
#pragma endregion

#pragma region 成交
        // 成交信息基类
        struct TradeInfoBase
        {
            TradeIDType         trade_id_;              // 成交ID
            ShadowTradeIDType   shadow_trade_id_;       // 影子成交编号
            OrderStreamType     order_stream_;          // 下单委托流号
            PositionIDType      position_id_;           // 持仓ID
            ContractIDType      contract_id_;           // 合约ID
            int                 volume_;                // 成交手数
            DirectType          direct_type_;           // 买卖方向
            YDouble             currency_rate_;         // 与当前基币汇率
            CurrencyIDType      currency_id_;           // 币种ID
            YDouble             trade_price_;           // 成交价格
            DateTimeType        generate_datetime_;     // 成交日期时间
            ShadowOrderIDType   shadow_order_id_;       // 影子订单编号
            SystemIDType        system_order_id_;       // 实盘委托编号
            SystemIDType        system_trade_id_;       // 实盘成交编号
            ExchangeIDType      exchange_id_;           // 交易所ID
            ApiTypeType         api_type_;              // 接口类型(CTP/ESUNNY/...)
            CommodityTypeType   commodity_type_;        // 商品类型(股票/期货/...)
            OperatorTradeType   op_type_;               // 操作员类型(PC/MC/...)

            YDouble             close_profit_;          // 平仓盈亏

            TradeInfoBase();
            virtual ~TradeInfoBase(){}
        };
#pragma endregion

#pragma region 持仓
        // 持仓信息基类
        struct PositionInfoBase
        {
            PositionIDType      position_id_;           // 持仓ID
            ContractIDType      contract_id_;           // 合约ID
            int                 volume_;                // 持仓手数
            int                 T_volume_;              // 因为T+1导致的冻结手数
            DirectType          direct_type_;           // 买卖方向
            CurrencyIDType      currency_id_;           // 币种ID
            YDouble             trade_ave_price_;       // 成交均价
            YDouble             cost_price_;            // 持仓成本
            ExchangeIDType      exchange_id_;           // 交易所ID
            CommodityTypeType   commodity_type_;        // 商品类型(股票/期货/...)
            int                 freeze_order_vol_;      // 提交平仓委托时的冻结手数

            PositionInfoBase();
            virtual ~PositionInfoBase(){}
        };
#pragma endregion

		
        // 行情信息数据基类
        struct QuoteInfoBase
        {
            ContractIDType      contract_id_;       // 合约ID
            CurrencyIDType      currency_id_;       // 币种ID
            YDouble             last_price_;        // 合约最新价
            YDouble             yclose_price_;      // 昨收盘,通联数据:昨收盘*1.1=涨停价,余数进位;昨收盘*0.9=跌停价,余数进位
            YDouble             ysettle_price_;     // 昨结算价
            YDouble             open_price_;        // 今开盘价
            YDouble             ask_price_[5];      // 五档卖行情, 卖一 至 卖五价
            int                 ask_volume_[5];     // 五档卖行情, 卖一 至 卖五量
            YDouble             bid_price_[5];      // 五档买行情，买一 至 买五价
            int                 bid_volume_[5];     // 五档买行情，买一 至 买五量
            QuoteStatusType     quote_status_;      // 行情所处状态

            YDouble             highest_price_;     // 涨停价
            YDouble             lowest_price_;      // 跌停价

            QuoteInfoBase();
            ~QuoteInfoBase(){}
        };

        // 费用信息数据
        struct TradeFee
        {
            YDouble trade_commission_;      // 交易所佣金(‰)
            YDouble min_trade_commission_;  // 最小交易所佣金(元)
            YDouble stamp_duty_;            // 印花税(‰)(平仓时收取)
            YDouble transfer_;              // 过户费(‰)
            YDouble info_match_;            // 撮合费(‰)
            YDouble user_profit_rate_;      // 交易员分成比例(‰)

            TradeFee();
        };

        // 风控信息
        struct ImmRiskControlSt
        {
            AllTrade::UserIDType        user_id_;   // 交易账户ID
            AllTrade::RiskControlType   rc_type_;   // 风控类型
            bool                        bTrigger_;  // 是否处于触发状态
            DateTimeType                date_time_; // 最近一次触发时间
			RemarkTextType				trigger_text_; // 触发内容

            ImmRiskControlSt();
        };

        // 禁止交易风控规则结构体
        struct SForbidTradeInfo
        {
            ForbidTradeType         forbid_trade_type_;     // 禁止交易规则类型
            ForbidTradeOperatorType forbid_trade_op_type_;  // 禁止交易操作类型
            bool                    bstart_;                // 是否开启

            SForbidTradeInfo();
        };

        // 持仓比例风控规则结构体
        struct SPositionRateInfo
        {
            PositionRateType        position_rate_type_;    // 持仓比例类型
            int                     position_rate_;         // 持仓比例,30%则设置为30
            bool                    bstart_;                // 是否开启

            SPositionRateInfo();
        };

        // 全局数据信息
        struct GlobalData
        {
            int     shadow_order_id_;      // 影子订单ID
            int     shadow_trade_id_;      // 影子成交ID

            GlobalData();
        };

		
		// 融券信息
		struct MarginInfo
		{
			int					sum_Margin_Qty_;		// 融券总数量
			double				Interest_;				// 融券利息

			MarginInfo();
		};


		// 融券剩余信息
		struct MarginLeftInfo
		{
			ContractIDType      contract_id_;           // 合约ID
			int					left_Margin_Qty_;		// 融券剩余数量

			MarginLeftInfo();
		};
    }
#pragma region 权限控制
    ///////////////////////////////////////////// 权限控制 //////////////////////////////////////
    // 权限业务
    struct AuthorityBussnesses
    {
        int					bussnessID;								// 业务ID
        BussnessName		bussnessName;							// 业务名称
        int					bussnessType;							// 业务类型 1、菜单2、功能
        int					bussnessAddr;							// 业务地址
        int					parentBussnessID;						// 父业务ID
        IsHide				isHide;									// 是否隐藏 IsHide_Hide 隐藏 IsHide_NoIsHide隐藏

        AuthorityBussnesses(){ memset(this, 0 ,sizeof(*this)); }
        ~AuthorityBussnesses(){}

    };
    // 日志记录
    struct AuthorityChangeLog
    {
		LoginNameType		login_name_;						// 创建该角色的用户
        int					changeDate;							// 角色创建日期
        int					changeTime;							// 角色创建时间
        LogContent			content;							// 内容

        AuthorityChangeLog(){ memset(this, 0, sizeof(*this)); }
        ~AuthorityChangeLog(){}

    };

    // 权限功能
    struct AuthorityFunctions
    {
        int					functionID;							// 功能ID
        int					bussnessID;							// 业务ID
        FunctionName		functionName;						// 功能名称
        IsSort				issort;								// 排序  IsSort_NoSort不排序 IsSort_Sort排序

        AuthorityFunctions(){ memset(this, 0, sizeof(*this)); }
        ~AuthorityFunctions(){}

    };

    // 账户权限功能
    struct AuthorityFunctionsUserId
    {
		LoginNameType		login_name_;						// 创建该角色的用户
        int					functionID;							// 功能ID
        int					bussnessID;							// 业务ID
		int					NavigationID;						// 导航ID
        FunctionName		functionName;						// 功能名称
        IsSort				issort;								// 排序  IsSort_NoSort不排序 IsSort_Sort排序

        AuthorityFunctionsUserId(){ memset(this, 0, sizeof(*this)); }
        ~AuthorityFunctionsUserId(){}
    };

    // 权限角色功能
    struct AuthorityRoleFunctions
    {
        int					id;									// id
        int					roleID;								// 角色ID
        int					functionID;							// 功能ID

        AuthorityRoleFunctions(){ memset(this, 0, sizeof(*this)); }
		~AuthorityRoleFunctions(){}

    };

    // 权限角色用户
    struct AuthorityRoleUsers
    {
        int					id;									// id
		LoginNameType		login_name_;						// 创建该角色的用户
        int					rolesID;							// 角色ID

        AuthorityRoleUsers(){ memset(this, 0, sizeof(*this)); }
		~AuthorityRoleUsers(){}

    };

    // 权限角色
    struct AuthorityRoles
    {
        int					rolesID;							// 角色ID
        RolesName			rolesName;							// 角色名称
		LoginNameType		login_name_;						// 创建该角色的用户
        int					createDate;							// 角色创建日期 
        int					createTime;							// 角色创建时间
		E_RolesType		    rolesType;							// 角色类型( 机构 / 管理员)
		E_OperationType		operationType;						// 操作类型( 操作0 / 不可操作1)


        AuthorityRoles(){ memset(this, 0, sizeof(*this)); }
        ~AuthorityRoles(){}
    };
#pragma endregion
}

#endif