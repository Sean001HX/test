/*************************************************
Copyright (C), 2017, HX Tech Co., Ltd.
File name:      accounthandler.h
Author:			XuYC
Version:
Date:
Description:    提供用户操作,将数据与操作分离
*************************************************/

#ifndef __USER_HANDLER_H__
#define __USER_HANDLER_H__

#include <memory>
#include <vector>
#include <map>
#include <atomic>
#include <boost/noncopyable.hpp>
#include "define/struct_declare.h"
#include "utility/rwmutex.h"
#include "define/params_declare.h"
#include "../Application/user_class_declare.h"
#include "SortIndex.h"

namespace AllTrade{

    namespace NPMgrCenter {
        // 账户操作统一基类
        class CAccountBaseHandler
            : public std::enable_shared_from_this<CAccountBaseHandler>
        {
            friend class CRootAccountHandler;
            friend class CManagerAccountHandler;
            friend class CAgencyAccountHandler;
            friend class CRiskAccountHandler;
            friend class CTradeAccountHandler;

        public:
            CAccountBaseHandler();
            CAccountBaseHandler(const SAccountPtr& account_st, const SMoneyInfoPtr& money, const SRiskInfoPtr& risk);
            virtual ~CAccountBaseHandler();

        public:
            // 获取内部指针的深拷贝对象
            virtual SAccountPtr getAccountCopy() const = 0;
            SMoneyInfoPtr getMoneyCopy() const;
            SRiskInfoPtr getRiskCopy() const;
            // 获取所包含的子节点
            // 注: 与getAccountHrs的区别为:本函数下的风控账户/管理账户是没有子节点的,而getAccountHrs获取的是可操作的账户
            virtual std::vector<AccountHrPtr> getChildHrs(E_ACCOUNT_PROP acc_prop) const = 0;
            // 获取所有指定账户属性的子节点,不包含越级子节点
            virtual std::vector<AccountHrPtr> getAccountHrs(E_ACCOUNT_PROP acc_prop) const = 0;
            // new_acc_hr: 创建后的账户操作指针,若数据错误则不做修改
            ErrorCodeType addAccount(AccountHrPtr& new_acc_hr, const SAccountPtr& acc_ptr, const SMoneyInfoPtr& money, const SRiskInfoPtr& risk);

            // 获取所有子账户个数,不包含越级子节点
            virtual size_t getAccountHrsCounnt() const{ return 0; }

            // 更新风控信息
            virtual ErrorCodeType updateRisk(SRiskInfoPtr sacc);

        private:
            virtual ErrorCodeType onAddAccount(AccountHrPtr& new_acc_hr, const SAccountPtr& account_st, const SMoneyInfoPtr& money, const SRiskInfoPtr& risk) = 0;

            // 结构(SAccountBase)相关的操作
        public:
            // 获取账户属性
            E_ACCOUNT_PROP getAccountProp() const;
            // 获取账户类型
            E_ACCOUNT_TYPE getAccountType() const;
            // 获取账户状态
            E_ACCOUNT_STATUS getAccountStatus() const;
            // 获取所属账户的ID
            PUserIDType getParentID() const;
            // 获取账户ID
            PUserIDType getAccountID() const;
            // 获取账户登录名
            PLoginNameType getAccountLoginName() const;
            // 获取账户账户名
            PAccountNameType getAccountName() const;
            // 获取账户密码
            PLoginPasswordType getAccountPsw() const;
            // 获取账户昵称
            PNickNameType getAccountNickName() const;
            // 账户开户时间；格式: yyyy-mm-dd hh:mm:ss
            PDateTimeType getRegeditTime() const;
            // 获取账户层级
            int getAccountLevel() const;
            // 设置/获取账户允许下设最大层级
            virtual int getAccountAllowMaxLevel() const { return 0; }
            virtual void setAccountAllowMaxLevel(int) const { return; }
            // 设置/获取账户允许下设的最大个数
            virtual int getAccountAllowMaxNum() const { return 0; }
            virtual void setAccountAllowMaxNum(int) const { return ; }
            // 是否为有效账户
            bool isValid() const;
            // 获取推广码
            PPopularizeLinkType getPopularizeLink() const;
            // 设置风控标志
			void triggerUserRiskControl(const PRemarkTextType text, RiskControlType rc_type, bool bTrigger);
            bool getUserIsInRiskControl(RiskControlType rc_type) const;

            void setAccountStruct(SAccountPtr ppb, const AccountHrPtr& parent);

            // 严禁更换作用域
        protected:
            void setParentHandler(const AccountHrPtr& parent);

            // 其他操作
        public:
            //返回所属账户对象
            AccountHrPtr getParentHandler() const { return m_parent.lock(); }

            // 序列化
            ErrorCodeType serialize();
            // 反序列化,为每个指针提供父指针及子节点
            ErrorCodeType unserialize();

            // 持仓成本变化
            ErrorCodeType changePositionCost(YDouble ave_money, int vol, DirectType direct);
            // 资金变动
            ErrorCodeType moneyChange(Money_Change_Type money_change, YDouble money, const RemarkTextType remark);
            // 判断是否可以下单
            ErrorCodeType canOrder(YDouble highest_price);
            ErrorCodeType canTrade(YDouble highest_price);
            // 修改密码
            ErrorCodeType changePassword(const LoginPasswordType old_pass, const LoginPasswordType new_pass);

        public:
            void setLoginName(const LoginNameType name);
            void setType(E_ACCOUNT_TYPE pst);
            void setRegeditTime(const DateTimeType time_st);		// 设置开户时间
			void setAccountStatus(E_ACCOUNT_STATUS status, const LoginNameType auditor_name = "");

        protected:
            // 检查账户信息是否完备：在保存账户数据到数据库、或本地XML文档中时；
            virtual bool checkUserData();

        protected:
            // 设置修改标记位
            void setCurNodeModiFlag(bool flag = true);
            void setChildrenModiFlag(bool flag = true);

        protected:
            SAccountPtr		    m_account_st_obj;	// 账户对应的数据结构
            MoneyHrPtr          m_money_hr;         // 资金信息对应结构体
            SRiskInfoPtr        m_risk_st_obj;      // 风控信息对应结构体

            bool                m_trigger_warning;  // 处于警告状态中
            bool                m_trigger_force;    // 处于强平状态中
            bool                m_trigger_limit;    // 处于限仓状态中

            mutable rwMutex		m_mtx_sp;

            AccountHrWPtr		m_parent;	// 所属账户操作对象（弱）指针

//             std::vector<ProductHrPtr>		m_white_product;	// 品种白名单
            std::vector<AccountHrPtr>		m_FollowAccounts;	// 跟单账户列表

            std::atomic<bool>	m_is_modify;		// 当前账户有修改
            std::atomic<bool>	m_is_child_modify;	// 子账户有修改

            mutable rwMutex		                    m_mtx_child;
            std::map<E_ACCOUNT_PROP, AccountIndex>  m_children;

        };

        // 根账户
        class CRootAccountHandler
            : public CAccountBaseHandler
            , public boost::noncopyable
        {
            friend class UserManager;

        public:
            CRootAccountHandler();
            CRootAccountHandler(const SAccountPtr& account_st, const SMoneyInfoPtr& money, const SRiskInfoPtr& risk);
            ~CRootAccountHandler();

        public:
            SAccountPtr getAccountCopy() const override;
            std::vector<AccountHrPtr> getChildHrs(E_ACCOUNT_PROP acc_prop) const override;
            std::vector<AccountHrPtr> getAccountHrs(E_ACCOUNT_PROP acc_prop) const override;

            // 获取账户允许下设最大层级
            virtual int getAccountAllowMaxLevel() const override;
            // 设置账户允许下设最大层级
            virtual void setAccountAllowMaxLevel(int) const override;
            // 获取账户允许下设的最大个数
            virtual int getAccountAllowMaxNum() const override;
            // 设置账户允许下设最大个数
            virtual void setAccountAllowMaxNum(int) const override;
            // 获取账户子账户个数,不含越级
            virtual size_t getAccountHrsCounnt() const override;

        private:
            ErrorCodeType onAddAccount(AccountHrPtr& new_acc_hr, const SAccountPtr& acc_ptr, const SMoneyInfoPtr& money, const SRiskInfoPtr& risk) override;
        };

        // 管理账户,自身没有子节点,获取所属机构下的相关节点
        class CManagerAccountHandler
            : public CAccountBaseHandler
            , public boost::noncopyable
        {
        public:
            CManagerAccountHandler();
            CManagerAccountHandler(const SAccountPtr& account_st, const SMoneyInfoPtr& money, const SRiskInfoPtr& risk);
            ~CManagerAccountHandler();

        public:
            SAccountPtr getAccountCopy() const override;
            std::vector<AccountHrPtr> getChildHrs(E_ACCOUNT_PROP acc_prop) const override;
            std::vector<AccountHrPtr> getAccountHrs(E_ACCOUNT_PROP acc_prop) const override;

            // 获取账户允许下设最大层级
            virtual int getAccountAllowMaxLevel() const override;
            // 获取账户允许下设的最大个数
            virtual int getAccountAllowMaxNum() const override;
            // 获取账户子账户个数,不含越级
            virtual size_t getAccountHrsCounnt() const override;

        private:
            ErrorCodeType onAddAccount(AccountHrPtr& new_acc_hr, const SAccountPtr& acc_ptr, const SMoneyInfoPtr& money, const SRiskInfoPtr& risk) override;
        };

        // 机构账户
        class CAgencyAccountHandler
            : public CAccountBaseHandler
            , public boost::noncopyable
        {
        public:
            CAgencyAccountHandler();
            CAgencyAccountHandler(const SAccountPtr& account_st, const SMoneyInfoPtr& money, const SRiskInfoPtr& risk);
            ~CAgencyAccountHandler();

        public:
            SAccountPtr getAccountCopy() const override;
            std::vector<AccountHrPtr> getChildHrs(E_ACCOUNT_PROP acc_prop) const override;
            std::vector<AccountHrPtr> getAccountHrs(E_ACCOUNT_PROP acc_prop) const override;

            // 获取账户允许下设最大层级
            virtual int getAccountAllowMaxLevel() const override;
            // 设置账户允许下设最大层级
            virtual void setAccountAllowMaxLevel(int) const override;
            // 获取账户允许下设的最大个数
            virtual int getAccountAllowMaxNum() const override;
            // 设置账户允许下设最大个数
            virtual void setAccountAllowMaxNum(int) const override;
            // 获取账户子账户个数,不含越级
            virtual size_t getAccountHrsCounnt() const override;

            // 更新风控信息
            ErrorCodeType updateRisk(SRiskInfoPtr sacc) override;

        private:
            ErrorCodeType onAddAccount(AccountHrPtr& new_acc_hr, const SAccountPtr& acc_ptr, const SMoneyInfoPtr& money, const SRiskInfoPtr& risk) override;
        };

        // 风控账户
        class CRiskAccountHandler
            : public CAccountBaseHandler
            , public boost::noncopyable
        {
        public:
            CRiskAccountHandler();
            CRiskAccountHandler(const SAccountPtr& account_st, const SMoneyInfoPtr& money, const SRiskInfoPtr& risk);
            ~CRiskAccountHandler();

        public:
            SAccountPtr getAccountCopy() const override;
            std::vector<AccountHrPtr> getChildHrs(E_ACCOUNT_PROP acc_prop) const override;
            std::vector<AccountHrPtr> getAccountHrs(E_ACCOUNT_PROP acc_prop) const override;

        private:
            ErrorCodeType onAddAccount(AccountHrPtr& new_acc_hr, const SAccountPtr& acc_ptr, const SMoneyInfoPtr& money, const SRiskInfoPtr& risk) override;
        };

        // 交易账户
        class CTradeAccountHandler
            : public CAccountBaseHandler
            , public boost::noncopyable
        {
        public:
            CTradeAccountHandler();
            CTradeAccountHandler(const SAccountPtr& account_st, const SMoneyInfoPtr& money, const SRiskInfoPtr& risk);
            ~CTradeAccountHandler();

        public:
            SAccountPtr getAccountCopy() const override;
            std::vector<AccountHrPtr> getChildHrs(E_ACCOUNT_PROP acc_prop) const override;
            std::vector<AccountHrPtr> getAccountHrs(E_ACCOUNT_PROP acc_prop) const override;

            // 更新风控信息
            ErrorCodeType updateRisk(SRiskInfoPtr sacc) override;

        private:
            ErrorCodeType onAddAccount(AccountHrPtr& new_acc_hr, const SAccountPtr& acc_ptr, const SMoneyInfoPtr& money, const SRiskInfoPtr& risk) override;
        };

        // 实盘账户
        class CFunderAccountHandler
            : public CAccountBaseHandler
            , public boost::noncopyable
        {
        public:
            CFunderAccountHandler();
            CFunderAccountHandler(const SAccountPtr& account_st, const SMoneyInfoPtr& money, const SRiskInfoPtr& risk);
            ~CFunderAccountHandler();

        public:
            SAccountPtr getAccountCopy() const override;
            std::vector<AccountHrPtr> getChildHrs(E_ACCOUNT_PROP acc_prop) const override;
            std::vector<AccountHrPtr> getAccountHrs(E_ACCOUNT_PROP acc_prop) const override;

        private:
            ErrorCodeType onAddAccount(AccountHrPtr& new_acc_hr, const SAccountPtr& acc_ptr, const SMoneyInfoPtr& money, const SRiskInfoPtr& risk) override;
        };

    }
}
#endif