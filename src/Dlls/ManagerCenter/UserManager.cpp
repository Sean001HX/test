#include <assert.h>
#include "UserManager.h"
#include "define/struct_extern.h"
#include "Handler/accounthandler.h"
#include "define/protocol_error.h"
#include "include/OperationManager/OperationManager.h"
#include "utility/utility_fun.h"

#include "C:/ng_tools/ng_header_for_log4cxx/ng_header_for_log4cxx.hpp"
#include "C:/ng_tools/ng_header_for_log4cxx/ng_header_for_log4cxx_log_var.hpp"
NG_LOGGER(logger, "UserManager");

namespace AllTrade{
    namespace NPMgrCenter {

        const PUserIDType get_user_id(const AccountHrPtr& acc_hr_ptr)
        {
            return acc_hr_ptr->getAccountID();
        }

        const PLoginNameType get_user_loginname(const AccountHrPtr& acc_hr_ptr)
        {
            return acc_hr_ptr->getAccountLoginName();
        }

        const AllTrade::PAccountNameType get_user_accname(const AccountHrPtr& acc_hr_ptr)
        {
            return acc_hr_ptr->getAccountName();
        }

        const PUserIDType get_parent_id(const AccountHrPtr& acc_hr_ptr)
        {
            return acc_hr_ptr->getParentID();
        }

        AllTrade::E_ACCOUNT_PROP get_acc_prop(const AccountHrPtr& acc_hr_ptr)
        {
            return acc_hr_ptr->getAccountProp();
        }

        AllTrade::E_ACCOUNT_TYPE get_acc_type(const AccountHrPtr& acc_hr_ptr)
        {
            return acc_hr_ptr->getAccountType();
        }

        UserManager::UserManager()
            :m_money_cbk(nullptr)
        {
            RootAccountPtr root_ptr(nullptr);
            bool db_root = OperationManager::COperationManager::instance()->getRootAccount(root_ptr);

            ErrorCodeType err_code(Err_Unknown);
            if (db_root && root_ptr)
            {
                SMoneyInfoPtr money;
                OperationManager::COperationManager::instance()->getUserMoneyInfo(root_ptr->user_id_, money);
                SRiskInfoPtr risk;
                OperationManager::COperationManager::instance()->getUserRiskInfo(root_ptr->user_id_, risk);
                m_root_acc_hr = std::dynamic_pointer_cast<CRootAccountHandler>(createAccountHr(root_ptr, money, risk));
                assert(m_root_acc_hr);
                err_code = m_root_acc_hr->unserialize();
            }
            else
            {
                m_root_acc_hr = std::dynamic_pointer_cast<CRootAccountHandler>(createAccountHr(createNewRootAccount(), std::make_shared<SMoneyInfo>(), std::make_shared<SRiskInfo>()));
                assert(m_root_acc_hr);
                err_code = m_root_acc_hr->serialize();
            }

            if (err_code == Err_Succeed)
            {
                m_user_hrs.insert(m_root_acc_hr);
                unserialize(m_root_acc_hr);
            }
        }

        UserManager::~UserManager()
        {

        }        

        ErrorCodeType UserManager::canLogin(const LoginNameType loginname, const std::string& password)
        {
            AccountHrPtr acc_hr_ptr = getAccountHr<LoginNameTag>(loginname);
            if (!acc_hr_ptr)
                return Err_Login_LoginNo;

            if (acc_hr_ptr->getAccountPsw() != password)
                return Err_Login_Password;

            if (acc_hr_ptr->getAccountStatus() < E_ACCOUNT_STATUS::EAS_Using
                || acc_hr_ptr->getAccountStatus() >= E_ACCOUNT_STATUS::EAS_Freezing)
                return Err_Login_Forbidden;

            return Err_Succeed;
        }

//         void UserManager::setRootAccount(const RootAccountPtr& root_ptr)
//         {
//             writeLock lock(m_mtx_user);
//             m_root_acc_hr = std::dynamic_pointer_cast<CRootAccountHandler>(createAccountHr(root_ptr));
//             assert(m_root_acc_hr);
//             m_user_hrs.insert(m_root_acc_hr);
//         }

        RootAccountPtr UserManager::getRootAccount() const
        {
            return std::dynamic_pointer_cast<RootAccount>(m_root_acc_hr->getAccountCopy());
        }

        AllTrade::NPMgrCenter::SAccountPtr UserManager::getAccountByID(const UserIDType user_id)
        {
            if (strnlen_s(user_id, sizeof(user_id)) != 0)
            {
                AccountHrPtr hr_ptr = getAccountHr<UserIDTag>(user_id);
                if (hr_ptr)
                    return hr_ptr->getAccountCopy();
                else
                    return SAccountPtr();
            }
            else
                return SAccountPtr();
        }
        
        AllTrade::NPMgrCenter::SAccountPtr UserManager::getAccountByLoginName(const LoginNameType loginname)
        {
            if (strnlen_s(loginname, sizeof(loginname)) != 0)
            {
                AccountHrPtr hr_ptr = getAccountHr<LoginNameTag>(loginname);
                if (hr_ptr)
                    return hr_ptr->getAccountCopy();
            }

            return SAccountPtr();
        }

        AllTrade::NPMgrCenter::SAccountPtr UserManager::getAccountByPopLink(const PopularizeLinkType poplink)
        {
            auto allAgency = getAllAgencys(m_root_acc_hr->getAccountID().c_str());
            for (auto item : allAgency)
            {
                if (strcmp(poplink, item->agent_link_) == 0)
                    return item;
            }
            return SAccountPtr();
        }

        std::vector<AllTrade::NPMgrCenter::SAccountPtr> UserManager::getAllParentsByID(const UserIDType user_id)
        {
            std::vector<AllTrade::NPMgrCenter::SAccountPtr> rslt;
            AccountHrPtr hr_ptr = getAccountHr<UserIDTag>(user_id);
            if (!hr_ptr)
                return rslt;

            AccountHrPtr hr_parent_ptr = hr_ptr->getParentHandler();
            if (!hr_parent_ptr)
                return rslt;

            if (hr_parent_ptr->getAccountProp() == E_ACCOUNT_PROP::EAP_Agency
                || hr_parent_ptr->getAccountProp() == E_ACCOUNT_PROP::EAP_Root)
            {
                std::vector<AllTrade::NPMgrCenter::SAccountPtr> tmp = getAllDirectManager(hr_parent_ptr->getAccountID().c_str());
                rslt.insert(rslt.end(), tmp.begin(), tmp.end());
                rslt.push_back(hr_parent_ptr->getAccountCopy());
            }

            std::vector<AllTrade::NPMgrCenter::SAccountPtr> tmp = getAllParentsByID(hr_parent_ptr->getAccountID().c_str());
            rslt.insert(rslt.end(), tmp.begin(), tmp.end());
            rslt.push_back(hr_parent_ptr->getAccountCopy());
            return rslt;
        }

        std::vector<SAccountPtr> UserManager::getAllDirectChildren(const UserIDType parent_id)
        {
            std::vector<SAccountPtr> rslt;
            readLock    rl(m_mtx_user);

            auto& indexoftag = m_user_hrs.get<ParentIDTag>();
            auto fit_begin = indexoftag.lower_bound(parent_id);
            auto fit_end = indexoftag.upper_bound(parent_id);
            while (fit_begin != fit_end)
            {
                AccountHrPtr tmp = (*fit_begin);
                rslt.push_back(tmp->getAccountCopy());
                ++fit_begin;
            }

            return rslt;
        }

        std::vector<SAccountPtr> UserManager::getAllDirectAgencys(const UserIDType parent_id)
        {
            std::vector<SAccountPtr> rslt;
            readLock    rl(m_mtx_user);

            auto& indexoftag = m_user_hrs.get<ParentIDTag>();
            auto fit_begin = indexoftag.lower_bound(parent_id);
            auto fit_end = indexoftag.upper_bound(parent_id);
            while (fit_begin != fit_end)
            {
                if ((*fit_begin)->getAccountProp() == EAP_Agency)
                    rslt.push_back((*fit_begin)->getAccountCopy());
                ++fit_begin;
            }

            return rslt;
        }

        std::vector<SAccountPtr> UserManager::getAllDirectMonits(const UserIDType parent_id)
        {
            std::vector<SAccountPtr> rslt;
            readLock    rl(m_mtx_user);

            auto& indexoftag = m_user_hrs.get<ParentIDTag>();
            auto fit_begin = indexoftag.lower_bound(parent_id);
            auto fit_end = indexoftag.upper_bound(parent_id);
            while (fit_begin != fit_end)
            {
                if ((*fit_begin)->getAccountProp() != EAP_Invalid
                    && (*fit_begin)->getAccountProp() != EAP_Trader)
                    rslt.push_back((*fit_begin)->getAccountCopy());
                ++fit_begin;
            }

            return rslt;
        }

        std::vector<AllTrade::NPMgrCenter::SAccountPtr> UserManager::getAllDirectManager(const UserIDType parent_id)
        {
            std::vector<SAccountPtr> rslt;
            readLock    rl(m_mtx_user);

            auto& indexoftag = m_user_hrs.get<ParentIDTag>();
            auto fit_begin = indexoftag.lower_bound(parent_id);
            auto fit_end = indexoftag.upper_bound(parent_id);
            while (fit_begin != fit_end)
            {
                if ((*fit_begin)->getAccountProp() == EAP_Manager)
                    rslt.push_back((*fit_begin)->getAccountCopy());
                ++fit_begin;
            }

            return rslt;
        }

        std::vector<SAccountPtr> UserManager::getAllDirectTrades(const UserIDType parent_id)
        {
            std::vector<SAccountPtr> rslt;
            readLock    rl(m_mtx_user);

            auto& indexoftag = m_user_hrs.get<ParentIDTag>();
            auto fit_begin = indexoftag.lower_bound(parent_id);
            auto fit_end = indexoftag.upper_bound(parent_id);
            while (fit_begin != fit_end)
            {
                if ((*fit_begin)->getAccountProp() == EAP_Trader)
                    rslt.push_back((*fit_begin)->getAccountCopy());
                ++fit_begin;
            }

            return rslt;
        }

        std::vector<AllTrade::NPMgrCenter::SAccountPtr> UserManager::getAllDirectFunders(const UserIDType parent_id)
        {
            std::vector<SAccountPtr> rslt;
            readLock    rl(m_mtx_user);

            auto& indexoftag = m_user_hrs.get<ParentIDTag>();
            auto fit_begin = indexoftag.lower_bound(parent_id);
            auto fit_end = indexoftag.upper_bound(parent_id);
            while (fit_begin != fit_end)
            {
                E_ACCOUNT_PROP prop_tmp = (*fit_begin)->getAccountProp();
                if ((*fit_begin)->getAccountProp() == E_ACCOUNT_PROP::EAP_Funder)
                    rslt.push_back((*fit_begin)->getAccountCopy());
                ++fit_begin;
            }

            return rslt;
        }

        std::vector<AllTrade::NPMgrCenter::SAccountPtr> UserManager::getAllChildren(const UserIDType parent_id)
        {
            std::vector<SAccountPtr> rslt;
            std::vector<SAccountPtr> dir_agency = getAllDirectChildren(parent_id);
            for (auto& item : dir_agency)
            {
                rslt.push_back(item);
                std::vector<SAccountPtr> tmp = getAllChildren(item->user_id_);
                if (!tmp.empty())
                    rslt.insert(rslt.end(), tmp.begin(), tmp.end());
            }
            return rslt;
        }

        std::vector<AllTrade::NPMgrCenter::SAccountPtr> UserManager::getAllTrade(const UserIDType parent_id)
        {
            std::vector<SAccountPtr> rslt;
            std::vector<SAccountPtr> dir_agency = getAllDirectChildren(parent_id);
            for (auto& item : dir_agency)
            {
                if (item->prop_ == EAP_Trader)
                {
                    rslt.push_back(item);
                }
                else
                {
                    std::vector<SAccountPtr> tmp = getAllTrade(item->user_id_);
                    if (!tmp.empty())
                        rslt.insert(rslt.end(), tmp.begin(), tmp.end());
                }
            }
            return rslt;
        }

        std::vector<AllTrade::NPMgrCenter::SAccountPtr> UserManager::getAllTradeAccByLoginName(const LoginNameType parent_loginname)
        {
            AccountHrPtr tmp = getAccountHr<LoginNameTag>(parent_loginname);
            if (tmp)
            {
                if (tmp->getAccountProp() == EAP_Manager)
                    return getAllTrade(tmp->getParentID().c_str());
                else
                    return getAllTrade(tmp->getAccountID().c_str());
            }

            return std::vector<AllTrade::NPMgrCenter::SAccountPtr>();
        }

        std::vector<AllTrade::NPMgrCenter::SAccountPtr> UserManager::getAllUsingTradeAccByLoginName(const LoginNameType parent_loginname)
        {
            std::vector<AllTrade::NPMgrCenter::SAccountPtr> rslt;
            auto vec = getAllTradeAccByLoginName(parent_loginname);
            for (auto item : vec)
            {
                if (item->status_ == E_ACCOUNT_STATUS::EAS_Using)
                    rslt.push_back(item);
            }
            return rslt;
        }

        std::vector<AllTrade::NPMgrCenter::SAccountPtr> UserManager::getAllCheckingTradeAccByLoginName(const LoginNameType parent_loginname)
        {
            std::vector<AllTrade::NPMgrCenter::SAccountPtr> rslt;
            auto vec = getAllTradeAccByLoginName(parent_loginname);
            for (auto item : vec)
            {
             //   if (item->status_ == E_ACCOUNT_STATUS::EAS_Check_Create)
                    rslt.push_back(item);
            }
            return rslt;
        }

        std::vector<AllTrade::NPMgrCenter::SAccountPtr> UserManager::getAllAgencys(const UserIDType parent_id)
        {
            std::vector<SAccountPtr> rslt;
            std::vector<SAccountPtr> dir_agency = getAllDirectAgencys(parent_id);
            for (auto& item : dir_agency)
            {
                rslt.push_back(item);
                std::vector<SAccountPtr> tmp = getAllAgencys(item->user_id_);
                if (!tmp.empty())
                    rslt.insert(rslt.end(), tmp.begin(), tmp.end());
            }
            return rslt;
        }

        std::vector<AllTrade::NPMgrCenter::SAccountPtr> UserManager::getAllAgencysByLoginName(const LoginNameType parent_loginname)
        {
            AccountHrPtr tmp = getAccountHr<LoginNameTag>(parent_loginname);
            if (tmp)
            {
                if (tmp->getAccountProp() == EAP_Manager)
                    return getAllAgencys(tmp->getParentID().c_str());
                else
                    return getAllAgencys(tmp->getAccountID().c_str());
            }
            return std::vector<AllTrade::NPMgrCenter::SAccountPtr>();
        }

        std::vector<AllTrade::NPMgrCenter::SAccountPtr> UserManager::getAllUsingAgencysByLoginName(const LoginNameType parent_loginname)
        {
            std::vector<AllTrade::NPMgrCenter::SAccountPtr> rslt;
            auto vec = getAllAgencysByLoginName(parent_loginname);
            for (auto item : vec)
            {
                if (item->status_ == E_ACCOUNT_STATUS::EAS_Using)
                    rslt.push_back(item);
            }
            return rslt;
        }

        std::vector<AllTrade::NPMgrCenter::SAccountPtr> UserManager::getAllCheckingAgencysByLoginName(const LoginNameType parent_loginname)
        {
            std::vector<AllTrade::NPMgrCenter::SAccountPtr> rslt;
            auto vec = getAllAgencysByLoginName(parent_loginname);
            for (auto item : vec)
            {
                if (item->status_ == E_ACCOUNT_STATUS::EAS_Check_Create)
                    rslt.push_back(item);
            }
            return rslt;
        }

        std::vector<AllTrade::NPMgrCenter::SAccountPtr> UserManager::getAllMonits(const UserIDType parent_id)
        {
            std::vector<SAccountPtr> rslt;
            std::vector<SAccountPtr> dir_agency = getAllDirectMonits(parent_id);
            for (auto& item : dir_agency)
            {
                rslt.push_back(item);
                std::vector<SAccountPtr> tmp = getAllMonits(item->user_id_);
                if (!tmp.empty())
                    rslt.insert(rslt.end(), tmp.begin(), tmp.end());
            }
            return rslt;
        }

        std::vector<AllTrade::NPMgrCenter::SAccountPtr> UserManager::getAllTrades(const UserIDType parent_id)
        {
            std::vector<SAccountPtr> rslt;
            std::vector<SAccountPtr> dir_agency = getAllDirectMonits(parent_id);
            for (auto& item : dir_agency)
            {
                std::vector<SAccountPtr> tmp_child = getAllTrades(item->user_id_);
                if (!tmp_child.empty())
                    rslt.insert(rslt.end(), tmp_child.begin(), tmp_child.end());
            }
            std::vector<SAccountPtr> tmp = getAllDirectTrades(parent_id);
            if (!tmp.empty())
                rslt.insert(rslt.end(), tmp.begin(), tmp.end());

            return rslt;
        }

        std::vector<AllTrade::NPMgrCenter::SAccountPtr> UserManager::getAllFunderAccByLoginName(const LoginNameType loginname)
        {
            AccountHrPtr tmp = getAccountHr<LoginNameTag>(loginname);
            if (tmp && tmp->getAccountProp() == EAP_Manager)
            {
                AccountHrPtr tmp_parent = getAccountHr<UserIDTag>(tmp->getParentID().c_str());
                if (strcmp(m_root_acc_hr->getAccountLoginName().c_str(), tmp_parent->getAccountLoginName().c_str()) != 0)
                    return std::vector<SAccountPtr>();
            }
            else if (tmp)
            {
                if (strcmp(loginname, m_root_acc_hr->getAccountLoginName().c_str()) != 0)
                    return std::vector<SAccountPtr>();
            }
            else
                return std::vector<SAccountPtr>();

            return getAllDirectFunders(m_root_acc_hr->getAccountID().c_str());
        }

        std::vector<AllTrade::NPMgrCenter::ManagerAccountPtr> UserManager::getManagersByLoginName(const LoginNameType loginname)
        {
            std::vector<AllTrade::NPMgrCenter::ManagerAccountPtr> rslt;
            AccountHrPtr tmp = getAccountHr<LoginNameTag>(loginname);
            if (tmp)
            {
                std::vector<SAccountPtr> dir_agency;
                if (tmp->getAccountProp() == EAP_Manager)
                    dir_agency = getAllDirectMonits(tmp->getParentID().c_str());
                else
                    dir_agency = getAllDirectMonits(tmp->getAccountID().c_str());

                for (auto& item : dir_agency)
                {
                    if (item->prop_ == EAP_Manager && strcmp(item->login_name_, loginname) != 0)
                        rslt.push_back(std::dynamic_pointer_cast<ManagerAccount>(item));
                }
            }
            return rslt;
        }

		AllTrade::NPMgrCenter::AgencyAccountPtr UserManager::getAgencyByLoginName(const LoginNameType loginname)
		{
			AllTrade::NPMgrCenter::AgencyAccountPtr rslt;
			AccountHrPtr tmp = getAccountHr<LoginNameTag>(loginname);
			if (tmp)
			{
				std::vector<SAccountPtr> dir_agency;
				if (tmp->getAccountProp() == EAP_Agency)
					dir_agency = getAllDirectMonits(tmp->getParentID().c_str());
				

				for (auto& item : dir_agency)
				{
					if (item->prop_ == EAP_Agency && strcmp(item->login_name_, loginname) == 0)
					{
						rslt = std::dynamic_pointer_cast<AgencyAccount>(item);
						break;
					}
						
				}
			}
			return rslt;
		}

        ErrorCodeType UserManager::addAccount(SAccountPtr child, SMoneyInfoPtr money, SRiskInfoPtr risk)
        {
            assert(child);
            AccountHrPtr parent_hr = getAccountHr<UserIDTag>(child->parent_id_);
            if (!parent_hr)
                return Error_User_Parent_Unexist;

            if ((child->prop_ == E_ACCOUNT_PROP::EAP_Agency || child->prop_ == E_ACCOUNT_PROP::EAP_Manager) && parent_hr->getAccountAllowMaxLevel() <= 0)
                return Error_MaxAllowLevel_Over;
//             if (parent_hr->getAccountHrsCounnt() >= parent_hr->getAccountAllowMaxNum())
//                 return Error_MaxAllowNum_Over;

            if (getAccountHr<UserIDTag>(child->user_id_) || getAccountHr<LoginNameTag>(child->login_name_) || getAccountHr<AccountNameTag>(child->account_name_))
                return Error_User_Exist;
//             AccountHrPtr create_hr = getAccountHr<UserIDTag>(child->create_id_);
//             if (!create_hr)
//                 return Error_User_Creator_Unexist;

            AccountHrPtr new_acc_hr(nullptr);

            strncpy_s(child->regist_datetime_, UtilityFun::getCurrentDateTime().c_str(), sizeof(child->regist_datetime_) - 1);
            strncpy_s(child->update_datetime_, UtilityFun::getCurrentDateTime().c_str(), sizeof(child->update_datetime_) - 1);
            strncpy_s(child->vaild_datetime_, UtilityFun::getAddDate(10 * 365).c_str(), sizeof(child->vaild_datetime_) - 1);

            ErrorCodeType err_code = parent_hr->addAccount(new_acc_hr, child, money, risk);
            if (err_code != Err_Succeed)
                return err_code;

            err_code = new_acc_hr->serialize();

            if (err_code != Err_Succeed)
                return err_code;

            {
                writeLock lock(m_mtx_user);
                m_user_hrs.insert(new_acc_hr);
            }

            if (err_code == Err_Succeed)
                err_code = updateRisk(child->user_id_, risk);

            return err_code;
        }

        ErrorCodeType UserManager::updateAccount(const SAccountPtr& sacc)
        {
            assert(sacc);
            AccountHrPtr self_hr = getAccountHr<UserIDTag>(sacc->user_id_);
            AccountHrPtr parent_hr = getAccountHr<UserIDTag>(sacc->parent_id_);
            if (!parent_hr || !self_hr /*|| !getAccountHr<UserIDTag>(sacc->create_id_)*/)
                return Error_User_Unexist;

            self_hr->setAccountStruct(sacc, parent_hr);

            {
                writeLock lock(m_mtx_user);
                auto& indexoftag = m_user_hrs.get<UserIDTag>();
                auto iter = indexoftag.find(sacc->user_id_);
                if (iter != indexoftag.end())
                    indexoftag.replace(iter, self_hr);// 注意modify在替换失败时会导致删除,但效率较高
                else
                    return Error_User_Unexist;
            }

            return Err_Succeed;
        }

		AllTrade::ErrorCodeType UserManager::checkAccount(const UserIDType user_id, E_ACCOUNT_STATUS bcheck, const LoginNameType auditor_name)
        {
            AccountHrPtr self_hr = getAccountHr<UserIDTag>(user_id);
            if (!self_hr)
                return Err_Unknown;

			self_hr->setAccountStatus(bcheck, auditor_name);
            return Err_Succeed;
        }

        AllTrade::ErrorCodeType UserManager::updateRisk(const UserIDType user_id, SRiskInfoPtr sacc)
        {
            AccountHrPtr acc_ptr = getAccountHr<UserIDTag>(user_id);
            if (!acc_ptr)
                return Error_User_Unexist;

            acc_ptr->updateRisk(sacc);
            return Err_Succeed;
        }

        AllTrade::NPMgrCenter::SMoneyInfoPtr UserManager::getMoneyInfoByLoginName(const LoginNameType loginname)
        {
            auto item = getAccountHr<LoginNameTag>(loginname);
            if (!item)
                return SMoneyInfoPtr();

            return item->getMoneyCopy();
        }

        AllTrade::NPMgrCenter::SRiskInfoPtr UserManager::getRiskInfoByLoginName(const LoginNameType loginname)
        {
            auto item = getAccountHr<LoginNameTag>(loginname);
            if (!item)
                return SRiskInfoPtr();

            return item->getRiskCopy();
        }

        AllTrade::NPMgrCenter::SRiskInfoPtr UserManager::getRiskInfoByUserID(const UserIDType user_id)
        {
            auto item = getAccountHr<UserIDTag>(user_id);
            if (!item)
                return SRiskInfoPtr();

            return item->getRiskCopy();
        }

        AllTrade::ErrorCodeType UserManager::changePositionCost(const UserIDType user_id, YDouble cost_money, int vol, DirectType direct)
        {
            auto item = getAccountHr<UserIDTag>(user_id);
            if (!item)
                return Error_User_Unexist;

            ErrorCodeType rslt = item->changePositionCost(cost_money, vol, direct);
            if (m_money_cbk && rslt == Err_Succeed)
                m_money_cbk(user_id, item->getMoneyCopy());

            return rslt;
        }

//         AllTrade::ErrorCodeType UserManager::outInMoney(const LoginNameType loginname, OIMM_Change_Type iotype, YDouble money, const RemarkTextType remark)
//         {
//             auto item = getAccountHr<LoginNameTag>(loginname);
//             if (!item)
//                 return Error_User_Unexist;
// 
//             return item->changeMoney(iotype, money, remark);
//         }

        AllTrade::ErrorCodeType UserManager::moneyChange(const UserIDType user_id, Money_Change_Type money_change, YDouble money, const RemarkTextType remark)
        {
            auto item = getAccountHr<UserIDTag>(user_id);
            if (!item)
                return Error_User_Unexist;

            ErrorCodeType rslt = item->moneyChange(money_change, money, remark);
            if (m_money_cbk && rslt == Err_Succeed)
                m_money_cbk(user_id, item->getMoneyCopy());

            return rslt;
        }

        AllTrade::ErrorCodeType UserManager::applyMoney(const UserIDType user_id, YDouble money, AllTrade::OIMM_Change_Type money_type, SApplyMoneyPtr ptr)
        {
            auto item = getAccountHr<UserIDTag>(user_id);
            if (!item)
                return Error_User_Unexist;
            
            if (money_type >= OIMM_Out_Deposit && item->getMoneyCopy()->getCanExtract() < money)
                return Error_CashOper_Value;

            SApplyMoneyPtr new_apply = std::make_shared<SApplyMoneyInfo>();
            strncpy_s(new_apply->user_id_, user_id, sizeof(new_apply->user_id_) - 1);
            strncpy_s(new_apply->apply_date_time_, UtilityFun::getCurrentDateTime().c_str(), sizeof(new_apply->apply_date_time_) - 1);
            strncpy_s(new_apply->approval_date_time_, "0000-00-00", sizeof(new_apply->approval_date_time_) - 1);
            new_apply->apply_money_ = money;
            new_apply->apply_status_ = E_APPLY_MONEY_STATUS::EAMS_Check_Create;
            new_apply->money_type_ = money_type;
            if (ptr)
            {
                strncpy_s(new_apply->real_name_, ptr->real_name_, sizeof(new_apply->real_name_) - 1);
                strncpy_s(new_apply->bank_card_, ptr->bank_card_, sizeof(new_apply->bank_card_) - 1);
                strncpy_s(new_apply->bank_name_, ptr->bank_name_, sizeof(new_apply->bank_name_) - 1);
            }
            if (!OperationManager::COperationManager::instance()->applyMoney(new_apply))
                return Err_Database;

            LOG4CXX_WARN(logger, "账户提交审核资金"LOG_NOVAR(user_id)
                "金额"LOG_NOVAR(money)"出入金流号"LOG_NOVAR(new_apply->apply_money_id_)
                "出入金类型"LOG_NOVAR(money_type));

            return Err_Succeed;
        }

        AllTrade::ErrorCodeType UserManager::approvalApplyMoney(const AllTrade::UserIDType approval_user_id, const AllTrade::UserIDType apply_user_id, const ApplyMoneyIDType apply_money_id, E_APPLY_MONEY_STATUS apply_status, AllTrade::OIMM_Change_Type money_type)
        {
            auto item = getAccountHr<UserIDTag>(apply_user_id);
            if (!item)
                return Error_User_Unexist;

            ErrorCodeType errcode(Err_Succeed);
            if (apply_status == EAMS_Using)
            {
                auto app_money_ptr = OperationManager::COperationManager::instance()->getApplyMoneyPtr(apply_money_id, money_type);
                if (app_money_ptr->apply_money_id_ != 0)
                    errcode = moneyChange(item->getAccountID().c_str(), (Money_Change_Type)money_type, app_money_ptr->apply_money_, "通过申请资金审核");
                else
                    errcode = Error_CashCheck_SerialID;
            }

            if (errcode == Err_Succeed)
            {
                if (!OperationManager::COperationManager::instance()->approvalApplyMoney(approval_user_id, apply_money_id, apply_status, UtilityFun::getCurrentDateTime().c_str(), money_type))
                {
                    errcode = Err_Database;
                    LOG4CXX_ERROR(logger, "审核资金失败!审核账户"LOG_NOVAR(approval_user_id)
                        "申请账户"LOG_NOVAR(apply_user_id)"出入金流号"LOG_NOVAR(apply_money_id)
                        "审核状态"LOG_NOVAR(apply_status)"出入金类型"LOG_NOVAR(money_type));
                }
            }

            return errcode;
        }

        std::vector<AllTrade::NPMgrCenter::SApplyMoneyPtr> UserManager::getApplyMoney(const UserIDType user_id, const DateType start_day, const DateType end_day, AllTrade::OIMM_Change_Type money_type)
        {
            std::vector<AllTrade::NPMgrCenter::SApplyMoneyPtr> rslt;
            auto item = getAccountHr<UserIDTag>(user_id);
            if (!item)
                return rslt;

            OperationManager::COperationManager::instance()->qryApplyMoney(rslt, user_id, start_day, end_day, money_type);
            return rslt;
        }

        AllTrade::NPMgrCenter::SApplyMoneyPtr UserManager::getApplyMoneyPtr(const AllTrade::ApplyMoneyIDType apply_money_id, AllTrade::OIMM_Change_Type type)
        {
            return OperationManager::COperationManager::instance()->getApplyMoneyPtr(apply_money_id, type);
        }

        AllTrade::ErrorCodeType UserManager::canOrder(const UserIDType user_id, YDouble highest_price)
        {
            auto item = getAccountHr<UserIDTag>(user_id);
            if (!item)
                return Error_User_Unexist;

            return item->canOrder(highest_price);
        }

        AllTrade::ErrorCodeType UserManager::canTrade(const UserIDType user_id, YDouble highest_price)
        {
            auto item = getAccountHr<UserIDTag>(user_id);
            if (!item)
                return Error_User_Unexist;

            return item->canTrade(highest_price);
        }

		void UserManager::triggerUserRiskControl(const PRemarkTextType text, const UserIDType user_id, RiskControlType rc_type, bool bTrigger)
        {
            auto item = getAccountHr<UserIDTag>(user_id);
            if (!item)
                return;

			return item->triggerUserRiskControl(text,rc_type, bTrigger);
        }

        bool UserManager::getUserIsInRiskControl(const UserIDType user_id, RiskControlType rc_type)
        {
            auto item = getAccountHr<UserIDTag>(user_id);
            if (!item)
                return false;

            return item->getUserIsInRiskControl(rc_type);
        }

        std::vector<AllTrade::NPMgrCenter::SMoneyDetailInfoPtr> UserManager::getFundSerial(const UserIDType user_id, const DateType start_day, const DateType end_day)
        {
            return OperationManager::COperationManager::instance()->getFundSerial(user_id, start_day, end_day);
        }

        AllTrade::ErrorCodeType UserManager::changePassword(const UserIDType user_id, const LoginPasswordType old_pass, const LoginPasswordType new_pass)
        {
            auto item = getAccountHr<UserIDTag>(user_id);
            if (!item)
                return Error_User_Unexist;

            return item->changePassword(old_pass, new_pass);
        }

        AllTrade::ErrorCodeType UserManager::deleteAccount(const UserIDType user_id)
        {
            auto item = getAccountHr<UserIDTag>(user_id);
            if (!item)
                return Error_User_Unexist;

            if (item->getAccountStatus() != E_ACCOUNT_STATUS::EAS_Using)
                return Error_User_Status_Unallow;

            // 实盘账户判断绑定
            if (item->getAccountProp() == E_ACCOUNT_PROP::EAP_Funder)
            {
                auto trade_items = getAllDirectTrades(m_root_acc_hr->getAccountID().c_str());
                for (auto& acc_item : trade_items)
                {
                    TradeAccountPtr ptr = std::dynamic_pointer_cast<TradeAccount>(acc_item);
                    if (ptr && strcmp(ptr->fund_user_id_, user_id) == 0)
                        return Error_User_Delete_HasBind;
                }
            }

            item->setAccountStatus(E_ACCOUNT_STATUS::EAS_Freezing);

            return Err_Succeed;
        }

        AllTrade::NPMgrCenter::SAccountPtr UserManager::createNewRootAccount()
        {
            RootAccountPtr root_ptr = std::make_shared<RootAccount>();
            strncpy_s(root_ptr->user_id_, UtilityFun::createGUID().c_str(), sizeof(root_ptr->user_id_) - 1);
            strncpy_s(root_ptr->regist_datetime_, UtilityFun::getCurrentDateTime().c_str(), sizeof(root_ptr->regist_datetime_) - 1);
            strncpy_s(root_ptr->update_datetime_, UtilityFun::getCurrentDateTime().c_str(), sizeof(root_ptr->update_datetime_) - 1);
            strncpy_s(root_ptr->vaild_datetime_, UtilityFun::getAddDate(10 * 365).c_str(), sizeof(root_ptr->vaild_datetime_) - 1);

            return root_ptr;
        }

        AccountHrPtr UserManager::createAccountHr(const SAccountPtr& sacc, const SMoneyInfoPtr& money, const SRiskInfoPtr& risk)
        {
            switch (sacc->prop_)
            {
            case AllTrade::EAP_Root:
                return std::make_shared<CRootAccountHandler>(sacc, money, risk);
                break;
            case AllTrade::EAP_Agency:
                return std::make_shared<CAgencyAccountHandler>(sacc, money, risk);
                break;
            case AllTrade::EAP_Risker:
                return std::make_shared<CRiskAccountHandler>(sacc, money, risk);
                break;
            case AllTrade::EAP_Manager:
                return std::make_shared<CManagerAccountHandler>(sacc, money, risk);
                break;
            case AllTrade::EAP_Trader:
                return std::make_shared<CTradeAccountHandler>(sacc, money, risk);
                break;
            case AllTrade::EAP_Funder:
                return std::make_shared<CFunderAccountHandler>(sacc, money, risk);
                break;
            default:
                assert(0);
                break;
            }

            return AccountHrPtr();
        }

        void UserManager::unserialize(const AccountHrPtr& acc_hr)
        {
            for (int i = E_ACCOUNT_PROP::EAP_Agency; i < E_ACCOUNT_PROP::EAP_MAX; i++)
            {
                for (auto item_hr : acc_hr->getChildHrs((E_ACCOUNT_PROP)i))
                {
                    m_user_hrs.insert(item_hr);
                    unserialize(item_hr);
                }
            }
        }

    }
}