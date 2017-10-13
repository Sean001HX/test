/*************************************************
Copyright (C), 2017, HX Tech Co., Ltd.
File name:      UserManager.h
Author:			XuYC
Version:
Date:
Description:    提供用户模块具体实现接口
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

            // 注册资金回调通知
            void setMoneyCbk(const MoneyCbk& fun) {
                m_money_cbk = fun;
            }

            // 是否能登录
            ErrorCodeType canLogin(const LoginNameType loginname, const std::string& password);
            // 设置/获取根账户
//             void setRootAccount(const RootAccountPtr& root_ptr);
            // 根据ID获取账户
            RootAccountPtr getRootAccount() const;
            AllTrade::NPMgrCenter::SAccountPtr getAccountByID(const UserIDType user_id);
            AllTrade::NPMgrCenter::SAccountPtr getAccountByLoginName(const LoginNameType loginname);
            // 根据推广码找到账户
            AllTrade::NPMgrCenter::SAccountPtr getAccountByPopLink(const PopularizeLinkType poplink);

            // 根据ID获取所有父级监管层账户(含越级)
            std::vector<AllTrade::NPMgrCenter::SAccountPtr> getAllParentsByID(const UserIDType user_id);

            // 获取指定帐户下的所有直属账户
            std::vector<AllTrade::NPMgrCenter::SAccountPtr> getAllDirectChildren(const UserIDType parent_id);
            // 获取指定帐户下的所有直属机构账户
            std::vector<AllTrade::NPMgrCenter::SAccountPtr> getAllDirectAgencys(const UserIDType parent_id);
            // 获取指定帐户下的所有直属监管层账户
            std::vector<AllTrade::NPMgrCenter::SAccountPtr> getAllDirectMonits(const UserIDType parent_id);
            // 获取指定帐户下的所有直属管理账户
            std::vector<AllTrade::NPMgrCenter::SAccountPtr> getAllDirectManager(const UserIDType parent_id);
            // 获取指定帐户下的所有直属交易账户
            std::vector<AllTrade::NPMgrCenter::SAccountPtr> getAllDirectTrades(const UserIDType parent_id);
            // 获取指定账户下的所有直属实盘账户
            std::vector<AllTrade::NPMgrCenter::SAccountPtr> getAllDirectFunders(const UserIDType parent_id);

            // 获取指定帐户下的所有账户(含越级)
            std::vector<AllTrade::NPMgrCenter::SAccountPtr> getAllChildren(const UserIDType parent_id);
            std::vector<AllTrade::NPMgrCenter::SAccountPtr> getAllTrade(const UserIDType parent_id);
            std::vector<AllTrade::NPMgrCenter::SAccountPtr> getAllTradeAccByLoginName(const LoginNameType parent_loginname);
            std::vector<AllTrade::NPMgrCenter::SAccountPtr> getAllUsingTradeAccByLoginName(const LoginNameType parent_loginname);
            std::vector<AllTrade::NPMgrCenter::SAccountPtr> getAllCheckingTradeAccByLoginName(const LoginNameType parent_loginname);
            // 获取指定帐户下的所有机构账户(含越级)
            std::vector<AllTrade::NPMgrCenter::SAccountPtr> getAllAgencys(const UserIDType parent_id);
            std::vector<AllTrade::NPMgrCenter::SAccountPtr> getAllAgencysByLoginName(const LoginNameType parent_loginname);
            std::vector<AllTrade::NPMgrCenter::SAccountPtr> getAllUsingAgencysByLoginName(const LoginNameType parent_loginname);
            std::vector<AllTrade::NPMgrCenter::SAccountPtr> getAllCheckingAgencysByLoginName(const LoginNameType parent_loginname);
            // 获取指定帐户下的所有监管层账户(含越级)
            std::vector<AllTrade::NPMgrCenter::SAccountPtr> getAllMonits(const UserIDType parent_id);
            // 获取指定帐户下的所有交易账户(含越级)
            std::vector<AllTrade::NPMgrCenter::SAccountPtr> getAllTrades(const UserIDType parent_id);
            // 获取指定账户下的所有实盘账户(含越级)
            std::vector<AllTrade::NPMgrCenter::SAccountPtr> getAllFunderAccByLoginName(const LoginNameType loginname);
            // 获取指定帐户下的所有管理账户(!!!不含越级)
            std::vector<AllTrade::NPMgrCenter::ManagerAccountPtr> getManagersByLoginName(const LoginNameType loginname);
			// 获取指定帐户下的所有机构账户(!!!不含越级)
			AllTrade::NPMgrCenter::AgencyAccountPtr getAgencyByLoginName(const LoginNameType loginname);

            // 新增账户
            ErrorCodeType addAccount(SAccountPtr child, SMoneyInfoPtr money, SRiskInfoPtr risk);
            // 更新账户
            ErrorCodeType updateAccount(const SAccountPtr& sacc);
            // 审核账户
			ErrorCodeType checkAccount(const UserIDType user_id, E_ACCOUNT_STATUS bcheck, const LoginNameType auditor_name = "");
            // 更新风控信息
            ErrorCodeType updateRisk(const UserIDType user_id, SRiskInfoPtr sacc);

            // 根据登录名获取资金信息
            AllTrade::NPMgrCenter::SMoneyInfoPtr getMoneyInfoByLoginName(const LoginNameType loginname);
            AllTrade::NPMgrCenter::SRiskInfoPtr getRiskInfoByLoginName(const LoginNameType loginname);
            AllTrade::NPMgrCenter::SRiskInfoPtr getRiskInfoByUserID(const UserIDType user_id);

            // 持仓成本变化
            ErrorCodeType changePositionCost(const UserIDType user_id, YDouble cost_money, int vol, DirectType direct);
            // 资金变动
            ErrorCodeType moneyChange(const UserIDType user_id, Money_Change_Type money_change, YDouble money, const RemarkTextType remark);
            // 申请融资资金
            ErrorCodeType applyMoney(const UserIDType user_id, YDouble money, AllTrade::OIMM_Change_Type money_type, SApplyMoneyPtr ptr = nullptr);
            // 审核申请融资金额
            ErrorCodeType approvalApplyMoney(const AllTrade::UserIDType approval_user_id, const AllTrade::UserIDType apply_user_id, const ApplyMoneyIDType apply_money_id, E_APPLY_MONEY_STATUS apply_status, AllTrade::OIMM_Change_Type money_type);
            // 查询融资资金
            std::vector<AllTrade::NPMgrCenter::SApplyMoneyPtr> getApplyMoney(const UserIDType user_id, const DateType start_day, const DateType end_day, AllTrade::OIMM_Change_Type money_type);
            AllTrade::NPMgrCenter::SApplyMoneyPtr getApplyMoneyPtr(const AllTrade::ApplyMoneyIDType apply_money_id, AllTrade::OIMM_Change_Type type);

            // 判断是否可以下单(资金相关)
            ErrorCodeType canOrder(const UserIDType user_id, YDouble highest_price);
            ErrorCodeType canTrade(const UserIDType user_id, YDouble highest_price);
            // 设置风控标志
			void triggerUserRiskControl(const PRemarkTextType text, const UserIDType user_id, RiskControlType rc_type, bool bTrigger);
            bool getUserIsInRiskControl(const UserIDType user_id, RiskControlType rc_type);

            // 设置资金流水
            std::vector<AllTrade::NPMgrCenter::SMoneyDetailInfoPtr> getFundSerial(const UserIDType user_id, const DateType start_day, const DateType end_day);

            // 修改密码
            ErrorCodeType changePassword(const UserIDType user_id, const LoginPasswordType old_pass, const LoginPasswordType new_pass);

            // 删除账户
            ErrorCodeType deleteAccount(const UserIDType user_id);

        private:
            // 创建根账户
            SAccountPtr createNewRootAccount();
            // 创建账户操作句柄
            AccountHrPtr createAccountHr(const SAccountPtr& sacc, const SMoneyInfoPtr& money, const SRiskInfoPtr& risk);
            // 初始化的反序列化,注意仅在初始化是使用,与句柄反序列化并非同一个功能
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