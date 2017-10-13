/*************************************************
Copyright (C), 2017, HX Tech Co., Ltd.
File name:      accounthandler.h
Author:			XuYC
Version:
Date:
Description:    �ṩ�û�����,���������������
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
        // �˻�����ͳһ����
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
            // ��ȡ�ڲ�ָ����������
            virtual SAccountPtr getAccountCopy() const = 0;
            SMoneyInfoPtr getMoneyCopy() const;
            SRiskInfoPtr getRiskCopy() const;
            // ��ȡ���������ӽڵ�
            // ע: ��getAccountHrs������Ϊ:�������µķ���˻�/�����˻���û���ӽڵ��,��getAccountHrs��ȡ���ǿɲ������˻�
            virtual std::vector<AccountHrPtr> getChildHrs(E_ACCOUNT_PROP acc_prop) const = 0;
            // ��ȡ����ָ���˻����Ե��ӽڵ�,������Խ���ӽڵ�
            virtual std::vector<AccountHrPtr> getAccountHrs(E_ACCOUNT_PROP acc_prop) const = 0;
            // new_acc_hr: ��������˻�����ָ��,�����ݴ��������޸�
            ErrorCodeType addAccount(AccountHrPtr& new_acc_hr, const SAccountPtr& acc_ptr, const SMoneyInfoPtr& money, const SRiskInfoPtr& risk);

            // ��ȡ�������˻�����,������Խ���ӽڵ�
            virtual size_t getAccountHrsCounnt() const{ return 0; }

            // ���·����Ϣ
            virtual ErrorCodeType updateRisk(SRiskInfoPtr sacc);

        private:
            virtual ErrorCodeType onAddAccount(AccountHrPtr& new_acc_hr, const SAccountPtr& account_st, const SMoneyInfoPtr& money, const SRiskInfoPtr& risk) = 0;

            // �ṹ(SAccountBase)��صĲ���
        public:
            // ��ȡ�˻�����
            E_ACCOUNT_PROP getAccountProp() const;
            // ��ȡ�˻�����
            E_ACCOUNT_TYPE getAccountType() const;
            // ��ȡ�˻�״̬
            E_ACCOUNT_STATUS getAccountStatus() const;
            // ��ȡ�����˻���ID
            PUserIDType getParentID() const;
            // ��ȡ�˻�ID
            PUserIDType getAccountID() const;
            // ��ȡ�˻���¼��
            PLoginNameType getAccountLoginName() const;
            // ��ȡ�˻��˻���
            PAccountNameType getAccountName() const;
            // ��ȡ�˻�����
            PLoginPasswordType getAccountPsw() const;
            // ��ȡ�˻��ǳ�
            PNickNameType getAccountNickName() const;
            // �˻�����ʱ�䣻��ʽ: yyyy-mm-dd hh:mm:ss
            PDateTimeType getRegeditTime() const;
            // ��ȡ�˻��㼶
            int getAccountLevel() const;
            // ����/��ȡ�˻������������㼶
            virtual int getAccountAllowMaxLevel() const { return 0; }
            virtual void setAccountAllowMaxLevel(int) const { return; }
            // ����/��ȡ�˻����������������
            virtual int getAccountAllowMaxNum() const { return 0; }
            virtual void setAccountAllowMaxNum(int) const { return ; }
            // �Ƿ�Ϊ��Ч�˻�
            bool isValid() const;
            // ��ȡ�ƹ���
            PPopularizeLinkType getPopularizeLink() const;
            // ���÷�ر�־
			void triggerUserRiskControl(const PRemarkTextType text, RiskControlType rc_type, bool bTrigger);
            bool getUserIsInRiskControl(RiskControlType rc_type) const;

            void setAccountStruct(SAccountPtr ppb, const AccountHrPtr& parent);

            // �Ͻ�����������
        protected:
            void setParentHandler(const AccountHrPtr& parent);

            // ��������
        public:
            //���������˻�����
            AccountHrPtr getParentHandler() const { return m_parent.lock(); }

            // ���л�
            ErrorCodeType serialize();
            // �����л�,Ϊÿ��ָ���ṩ��ָ�뼰�ӽڵ�
            ErrorCodeType unserialize();

            // �ֲֳɱ��仯
            ErrorCodeType changePositionCost(YDouble ave_money, int vol, DirectType direct);
            // �ʽ�䶯
            ErrorCodeType moneyChange(Money_Change_Type money_change, YDouble money, const RemarkTextType remark);
            // �ж��Ƿ�����µ�
            ErrorCodeType canOrder(YDouble highest_price);
            ErrorCodeType canTrade(YDouble highest_price);
            // �޸�����
            ErrorCodeType changePassword(const LoginPasswordType old_pass, const LoginPasswordType new_pass);

        public:
            void setLoginName(const LoginNameType name);
            void setType(E_ACCOUNT_TYPE pst);
            void setRegeditTime(const DateTimeType time_st);		// ���ÿ���ʱ��
			void setAccountStatus(E_ACCOUNT_STATUS status, const LoginNameType auditor_name = "");

        protected:
            // ����˻���Ϣ�Ƿ��걸���ڱ����˻����ݵ����ݿ⡢�򱾵�XML�ĵ���ʱ��
            virtual bool checkUserData();

        protected:
            // �����޸ı��λ
            void setCurNodeModiFlag(bool flag = true);
            void setChildrenModiFlag(bool flag = true);

        protected:
            SAccountPtr		    m_account_st_obj;	// �˻���Ӧ�����ݽṹ
            MoneyHrPtr          m_money_hr;         // �ʽ���Ϣ��Ӧ�ṹ��
            SRiskInfoPtr        m_risk_st_obj;      // �����Ϣ��Ӧ�ṹ��

            bool                m_trigger_warning;  // ���ھ���״̬��
            bool                m_trigger_force;    // ����ǿƽ״̬��
            bool                m_trigger_limit;    // �����޲�״̬��

            mutable rwMutex		m_mtx_sp;

            AccountHrWPtr		m_parent;	// �����˻�������������ָ��

//             std::vector<ProductHrPtr>		m_white_product;	// Ʒ�ְ�����
            std::vector<AccountHrPtr>		m_FollowAccounts;	// �����˻��б�

            std::atomic<bool>	m_is_modify;		// ��ǰ�˻����޸�
            std::atomic<bool>	m_is_child_modify;	// ���˻����޸�

            mutable rwMutex		                    m_mtx_child;
            std::map<E_ACCOUNT_PROP, AccountIndex>  m_children;

        };

        // ���˻�
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

            // ��ȡ�˻������������㼶
            virtual int getAccountAllowMaxLevel() const override;
            // �����˻������������㼶
            virtual void setAccountAllowMaxLevel(int) const override;
            // ��ȡ�˻����������������
            virtual int getAccountAllowMaxNum() const override;
            // �����˻���������������
            virtual void setAccountAllowMaxNum(int) const override;
            // ��ȡ�˻����˻�����,����Խ��
            virtual size_t getAccountHrsCounnt() const override;

        private:
            ErrorCodeType onAddAccount(AccountHrPtr& new_acc_hr, const SAccountPtr& acc_ptr, const SMoneyInfoPtr& money, const SRiskInfoPtr& risk) override;
        };

        // �����˻�,����û���ӽڵ�,��ȡ���������µ���ؽڵ�
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

            // ��ȡ�˻������������㼶
            virtual int getAccountAllowMaxLevel() const override;
            // ��ȡ�˻����������������
            virtual int getAccountAllowMaxNum() const override;
            // ��ȡ�˻����˻�����,����Խ��
            virtual size_t getAccountHrsCounnt() const override;

        private:
            ErrorCodeType onAddAccount(AccountHrPtr& new_acc_hr, const SAccountPtr& acc_ptr, const SMoneyInfoPtr& money, const SRiskInfoPtr& risk) override;
        };

        // �����˻�
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

            // ��ȡ�˻������������㼶
            virtual int getAccountAllowMaxLevel() const override;
            // �����˻������������㼶
            virtual void setAccountAllowMaxLevel(int) const override;
            // ��ȡ�˻����������������
            virtual int getAccountAllowMaxNum() const override;
            // �����˻���������������
            virtual void setAccountAllowMaxNum(int) const override;
            // ��ȡ�˻����˻�����,����Խ��
            virtual size_t getAccountHrsCounnt() const override;

            // ���·����Ϣ
            ErrorCodeType updateRisk(SRiskInfoPtr sacc) override;

        private:
            ErrorCodeType onAddAccount(AccountHrPtr& new_acc_hr, const SAccountPtr& acc_ptr, const SMoneyInfoPtr& money, const SRiskInfoPtr& risk) override;
        };

        // ����˻�
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

        // �����˻�
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

            // ���·����Ϣ
            ErrorCodeType updateRisk(SRiskInfoPtr sacc) override;

        private:
            ErrorCodeType onAddAccount(AccountHrPtr& new_acc_hr, const SAccountPtr& acc_ptr, const SMoneyInfoPtr& money, const SRiskInfoPtr& risk) override;
        };

        // ʵ���˻�
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