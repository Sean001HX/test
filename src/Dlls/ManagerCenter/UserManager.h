/*************************************************
Copyright (C), 2017, HX Tech Co., Ltd.
File name:      UserManager.h
Author:			XuYC
Version:
Date:
Description:    �ṩ�û�ģ�����ʵ�ֽӿ�
*************************************************/
#ifndef __CUSER_H__
#define __CUSER_H__

#include <boost/noncopyable.hpp>
#include <boost\multi_index_container.hpp>
#include <boost\multi_index\mem_fun.hpp>
#include <boost\multi_index\ordered_index.hpp>
#include <boost\multi_index\global_fun.hpp>
#include <vector>

#include "define/struct_declare.h"
#include "define/params_declare.h"
#include "utility/rwmutex.h"
#include "Application/user_class_declare.h"
#include "define/communition_struct_define.h"

namespace AllTrade {
    namespace NPMgrCenter {

        const PUserIDType get_user_id(const AccountHrPtr& acc_hr_ptr);
        const PLoginNameType get_user_loginname(const AccountHrPtr& acc_hr_ptr);
        const PAccountNameType get_user_accname(const AccountHrPtr& acc_hr_ptr);
        const PUserIDType get_parent_id(const AccountHrPtr& acc_hr_ptr);
        E_ACCOUNT_PROP get_acc_prop(const AccountHrPtr& acc_hr_ptr);
        E_ACCOUNT_TYPE get_acc_type(const AccountHrPtr& acc_hr_ptr);

        class UserManager : public boost::noncopyable
        {
            typedef std::function<void(const AllTrade::UserIDType user_id, const NPMgrCenter::SMoneyInfoPtr& money_ptr)>  MoneyCbk;
        public:
            UserManager();
            ~UserManager();

            // ע���ʽ�ص�֪ͨ
            void setMoneyCbk(const MoneyCbk& fun) {
                m_money_cbk = fun;
            }

            // �Ƿ��ܵ�¼
            ErrorCodeType canLogin(const LoginNameType loginname, const std::string& password);
            // ����/��ȡ���˻�
//             void setRootAccount(const RootAccountPtr& root_ptr);
            // ����ID��ȡ�˻�
            RootAccountPtr getRootAccount() const;
            AllTrade::NPMgrCenter::SAccountPtr getAccountByID(const UserIDType user_id);
            AllTrade::NPMgrCenter::SAccountPtr getAccountByLoginName(const LoginNameType loginname);
            // �����ƹ����ҵ��˻�
            AllTrade::NPMgrCenter::SAccountPtr getAccountByPopLink(const PopularizeLinkType poplink);

            // ����ID��ȡ���и�����ܲ��˻�(��Խ��)
            std::vector<AllTrade::NPMgrCenter::SAccountPtr> getAllParentsByID(const UserIDType user_id);

            // ��ȡָ���ʻ��µ�����ֱ���˻�
            std::vector<AllTrade::NPMgrCenter::SAccountPtr> getAllDirectChildren(const UserIDType parent_id);
            // ��ȡָ���ʻ��µ�����ֱ�������˻�
            std::vector<AllTrade::NPMgrCenter::SAccountPtr> getAllDirectAgencys(const UserIDType parent_id);
            // ��ȡָ���ʻ��µ�����ֱ����ܲ��˻�
            std::vector<AllTrade::NPMgrCenter::SAccountPtr> getAllDirectMonits(const UserIDType parent_id);
            // ��ȡָ���ʻ��µ�����ֱ�������˻�
            std::vector<AllTrade::NPMgrCenter::SAccountPtr> getAllDirectManager(const UserIDType parent_id);
            // ��ȡָ���ʻ��µ�����ֱ�������˻�
            std::vector<AllTrade::NPMgrCenter::SAccountPtr> getAllDirectTrades(const UserIDType parent_id);
            // ��ȡָ���˻��µ�����ֱ��ʵ���˻�
            std::vector<AllTrade::NPMgrCenter::SAccountPtr> getAllDirectFunders(const UserIDType parent_id);

            // ��ȡָ���ʻ��µ������˻�(��Խ��)
            std::vector<AllTrade::NPMgrCenter::SAccountPtr> getAllChildren(const UserIDType parent_id);
            std::vector<AllTrade::NPMgrCenter::SAccountPtr> getAllTrade(const UserIDType parent_id);
            std::vector<AllTrade::NPMgrCenter::SAccountPtr> getAllTradeAccByLoginName(const LoginNameType parent_loginname);
            std::vector<AllTrade::NPMgrCenter::SAccountPtr> getAllUsingTradeAccByLoginName(const LoginNameType parent_loginname);
            std::vector<AllTrade::NPMgrCenter::SAccountPtr> getAllCheckingTradeAccByLoginName(const LoginNameType parent_loginname);
            // ��ȡָ���ʻ��µ����л����˻�(��Խ��)
            std::vector<AllTrade::NPMgrCenter::SAccountPtr> getAllAgencys(const UserIDType parent_id);
            std::vector<AllTrade::NPMgrCenter::SAccountPtr> getAllAgencysByLoginName(const LoginNameType parent_loginname);
            std::vector<AllTrade::NPMgrCenter::SAccountPtr> getAllUsingAgencysByLoginName(const LoginNameType parent_loginname);
            std::vector<AllTrade::NPMgrCenter::SAccountPtr> getAllCheckingAgencysByLoginName(const LoginNameType parent_loginname);
            // ��ȡָ���ʻ��µ����м�ܲ��˻�(��Խ��)
            std::vector<AllTrade::NPMgrCenter::SAccountPtr> getAllMonits(const UserIDType parent_id);
            // ��ȡָ���ʻ��µ����н����˻�(��Խ��)
            std::vector<AllTrade::NPMgrCenter::SAccountPtr> getAllTrades(const UserIDType parent_id);
            // ��ȡָ���˻��µ�����ʵ���˻�(��Խ��)
            std::vector<AllTrade::NPMgrCenter::SAccountPtr> getAllFunderAccByLoginName(const LoginNameType loginname);
            // ��ȡָ���ʻ��µ����й����˻�(!!!����Խ��)
            std::vector<AllTrade::NPMgrCenter::ManagerAccountPtr> getManagersByLoginName(const LoginNameType loginname);
			// ��ȡָ���ʻ��µ����л����˻�(!!!����Խ��)
			AllTrade::NPMgrCenter::AgencyAccountPtr getAgencyByLoginName(const LoginNameType loginname);

            // �����˻�
            ErrorCodeType addAccount(SAccountPtr child, SMoneyInfoPtr money, SRiskInfoPtr risk);
            // �����˻�
            ErrorCodeType updateAccount(const SAccountPtr& sacc);
            // ����˻�
			ErrorCodeType checkAccount(const UserIDType user_id, E_ACCOUNT_STATUS bcheck, const LoginNameType auditor_name = "");
            // ���·����Ϣ
            ErrorCodeType updateRisk(const UserIDType user_id, SRiskInfoPtr sacc);

            // ���ݵ�¼����ȡ�ʽ���Ϣ
            AllTrade::NPMgrCenter::SMoneyInfoPtr getMoneyInfoByLoginName(const LoginNameType loginname);
            AllTrade::NPMgrCenter::SRiskInfoPtr getRiskInfoByLoginName(const LoginNameType loginname);
            AllTrade::NPMgrCenter::SRiskInfoPtr getRiskInfoByUserID(const UserIDType user_id);

            // �ֲֳɱ��仯
            ErrorCodeType changePositionCost(const UserIDType user_id, YDouble cost_money, int vol, DirectType direct);
            // �ʽ�䶯
            ErrorCodeType moneyChange(const UserIDType user_id, Money_Change_Type money_change, YDouble money, const RemarkTextType remark);
            // ���������ʽ�
            ErrorCodeType applyMoney(const UserIDType user_id, YDouble money, AllTrade::OIMM_Change_Type money_type, SApplyMoneyPtr ptr = nullptr);
            // ����������ʽ��
            ErrorCodeType approvalApplyMoney(const AllTrade::UserIDType approval_user_id, const AllTrade::UserIDType apply_user_id, const ApplyMoneyIDType apply_money_id, E_APPLY_MONEY_STATUS apply_status, AllTrade::OIMM_Change_Type money_type);
            // ��ѯ�����ʽ�
            std::vector<AllTrade::NPMgrCenter::SApplyMoneyPtr> getApplyMoney(const UserIDType user_id, const DateType start_day, const DateType end_day, AllTrade::OIMM_Change_Type money_type);
            AllTrade::NPMgrCenter::SApplyMoneyPtr getApplyMoneyPtr(const AllTrade::ApplyMoneyIDType apply_money_id, AllTrade::OIMM_Change_Type type);

            // �ж��Ƿ�����µ�(�ʽ����)
            ErrorCodeType canOrder(const UserIDType user_id, YDouble highest_price);
            ErrorCodeType canTrade(const UserIDType user_id, YDouble highest_price);
            // ���÷�ر�־
			void triggerUserRiskControl(const PRemarkTextType text, const UserIDType user_id, RiskControlType rc_type, bool bTrigger);
            bool getUserIsInRiskControl(const UserIDType user_id, RiskControlType rc_type);

            // �����ʽ���ˮ
            std::vector<AllTrade::NPMgrCenter::SMoneyDetailInfoPtr> getFundSerial(const UserIDType user_id, const DateType start_day, const DateType end_day);

            // �޸�����
            ErrorCodeType changePassword(const UserIDType user_id, const LoginPasswordType old_pass, const LoginPasswordType new_pass);

            // ɾ���˻�
            ErrorCodeType deleteAccount(const UserIDType user_id);

        private:
            // �������˻�
            SAccountPtr createNewRootAccount();
            // �����˻��������
            AccountHrPtr createAccountHr(const SAccountPtr& sacc, const SMoneyInfoPtr& money, const SRiskInfoPtr& risk);
            // ��ʼ���ķ����л�,ע����ڳ�ʼ����ʹ��,���������л�����ͬһ������
            void unserialize(const AccountHrPtr& acc_hr);

        private:
            template<typename Tag, typename ParamType>
            AccountHrPtr getAccountHr(const ParamType param) const
            {
                readLock    rl(m_mtx_user);

                auto& indexoftag = m_user_hrs.get<Tag>();
                auto fit = indexoftag.find(param);
                if (fit != indexoftag.end())
                    return *fit;

                return AccountHrPtr();
            }
        private:
            ///////////////////////////////////////////////
            struct UserIDTag {};
            struct LoginNameTag {};
            struct AccountNameTag {};
            struct ParentIDTag {};
            struct PropTag {};
            struct TypeTag {};
            typedef boost::multi_index::multi_index_container <
                AccountHrPtr,
                boost::multi_index::indexed_by<
                boost::multi_index::ordered_unique<boost::multi_index::tag<UserIDTag>, boost::multi_index::global_fun<const AccountHrPtr&, const PUserIDType, get_user_id> >,
                boost::multi_index::ordered_unique<boost::multi_index::tag<LoginNameTag>, boost::multi_index::global_fun<const AccountHrPtr&, const PLoginNameType, get_user_loginname> >,
                boost::multi_index::ordered_unique<boost::multi_index::tag<AccountNameTag>, boost::multi_index::global_fun<const AccountHrPtr&, const PAccountNameType, get_user_accname> >,
                boost::multi_index::ordered_non_unique<boost::multi_index::tag<ParentIDTag>, boost::multi_index::global_fun<const AccountHrPtr&, const PUserIDType, get_parent_id> >,
                boost::multi_index::ordered_non_unique<boost::multi_index::tag<PropTag>, boost::multi_index::global_fun<const AccountHrPtr&, E_ACCOUNT_PROP, get_acc_prop> >,
                boost::multi_index::ordered_non_unique<boost::multi_index::tag<TypeTag>, boost::multi_index::global_fun<const AccountHrPtr&, E_ACCOUNT_TYPE, get_acc_type> >
                >
            > AccountHrSet;

            RootAccountHrPtr        m_root_acc_hr;
            AccountHrSet            m_user_hrs;
            mutable rwMutex         m_mtx_user;

            MoneyCbk                m_money_cbk;
        };
    }
}
#endif