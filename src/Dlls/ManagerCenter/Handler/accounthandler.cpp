#include <assert.h>
#include "accounthandler.h"
#include "define/struct_base.h"
#include "define/struct_declare.h"
#include "define/protocol_error.h"
#include "define/struct_extern.h"
#include "include/OperationManager/OperationManager.h"
#include "MoneyHandler.h"
#include "utility/utility_fun.h"

#include "C:/ng_tools/ng_header_for_log4cxx/ng_header_for_log4cxx.hpp"
#include "C:/ng_tools/ng_header_for_log4cxx/ng_header_for_log4cxx_log_var.hpp"
NG_LOGGER(logger, "AccountHandler");

namespace AllTrade {
    namespace NPMgrCenter {

#pragma region 账户句柄基类

        CAccountBaseHandler::CAccountBaseHandler()
            : m_is_modify(true)
            , m_is_child_modify(true)
            , m_money_hr(nullptr)
            , m_trigger_warning(false)
            , m_trigger_force(false)
            , m_trigger_limit(false)
        {
            m_risk_st_obj = std::make_shared<SRiskInfo>();
        }

        CAccountBaseHandler::CAccountBaseHandler(const SAccountPtr& account_st, const SMoneyInfoPtr& money, const SRiskInfoPtr& risk)
            : m_is_modify(true)
            , m_is_child_modify(true)
            , m_trigger_warning(false)
            , m_trigger_force(false)
            , m_trigger_limit(false)
        {
            assert(account_st);
            m_account_st_obj = account_st;
            if (money)
                m_money_hr = std::make_shared<CMoneyHandler>(money);
            m_risk_st_obj = risk;
        }

        CAccountBaseHandler::~CAccountBaseHandler()
        {
        }

        E_ACCOUNT_PROP CAccountBaseHandler::getAccountProp() const
        {
            return m_account_st_obj->prop_;
        }

        E_ACCOUNT_TYPE CAccountBaseHandler::getAccountType() const
        {
            return m_account_st_obj->type_;
        }

        E_ACCOUNT_STATUS CAccountBaseHandler::getAccountStatus() const
        {
            readLock lock(m_mtx_sp);
            return m_account_st_obj->status_;
        }

		void CAccountBaseHandler::setAccountStatus(E_ACCOUNT_STATUS status, const LoginNameType auditor_name)
        {
            {
                writeLock lock(m_mtx_sp);
                m_account_st_obj->status_ = status;
                strncpy_s(m_account_st_obj->update_datetime_, UtilityFun::getCurrentDateTime().c_str(), sizeof(m_account_st_obj->update_datetime_) - 1);
				strncpy_s(m_account_st_obj->auditor_datetime_, UtilityFun::getCurrentDateTime().c_str(), sizeof(m_account_st_obj->auditor_datetime_) - 1);
				if (strcmp(auditor_name, ""))
				{
					strncpy_s(m_account_st_obj->auditor_name_, auditor_name, sizeof(m_account_st_obj->auditor_name_) - 1);
				}
                m_is_modify = true;
            }
            serialize();
        }

        PUserIDType CAccountBaseHandler::getParentID() const
        {
            return m_account_st_obj->parent_id_;
        }

        PUserIDType CAccountBaseHandler::getAccountID() const
        {
            return m_account_st_obj->user_id_;
        }

        PLoginNameType CAccountBaseHandler::getAccountLoginName() const
        {
            return m_account_st_obj->login_name_;
        }

        AllTrade::PAccountNameType CAccountBaseHandler::getAccountName() const
        {
            return m_account_st_obj->account_name_;
        }

        AllTrade::PLoginPasswordType CAccountBaseHandler::getAccountPsw() const
        {
            return m_account_st_obj->password_;
        }

        PNickNameType CAccountBaseHandler::getAccountNickName() const
        {
            return m_account_st_obj->nick_name_;
        }

        PDateTimeType CAccountBaseHandler::getRegeditTime() const
        {
            return m_account_st_obj->regist_datetime_;
        }

        int CAccountBaseHandler::getAccountLevel() const
        {
            return m_account_st_obj->level_;
        }

        bool CAccountBaseHandler::isValid() const
        {
            return false;
        }

        AllTrade::PPopularizeLinkType CAccountBaseHandler::getPopularizeLink() const
        {
            return m_account_st_obj->agent_link_;
        }

		void CAccountBaseHandler::triggerUserRiskControl(const PRemarkTextType text, RiskControlType rc_type, bool bTrigger)
        {
            {
                writeLock w1(m_mtx_sp);

                switch (rc_type)
                {
                case AllTrade::RCT_WarningLine:
                    if (m_trigger_warning == bTrigger)
                        return;
                    m_trigger_warning = bTrigger;
                    break;
                case AllTrade::RCT_ForceLine:
                    if (m_trigger_force == bTrigger)
                        return;
                    m_trigger_force = bTrigger;
                    break;
                case AllTrade::RCT_LimitLine:
                    if (m_trigger_limit == bTrigger)
                        return;
                    m_trigger_limit = bTrigger;
                    break;
                default:
                    assert(0);
                    break;
                }
            }

            AllTrade::NPTradeCenter::ImmRiskControlPtr risk_cont_st = std::make_shared<AllTrade::NPTradeCenter::ImmRiskControlSt>();
            strncpy_s(risk_cont_st->user_id_, m_account_st_obj->user_id_, sizeof(risk_cont_st->user_id_) - 1);
            risk_cont_st->rc_type_ = rc_type;
            risk_cont_st->bTrigger_ = bTrigger;
            strncpy_s(risk_cont_st->date_time_, UtilityFun::getCurrentDateTime().c_str(), sizeof(risk_cont_st->date_time_) - 1);
			strncpy_s(risk_cont_st->trigger_text_, text.c_str(), sizeof(risk_cont_st->trigger_text_) - 1);

            OperationManager::COperationManager::instance()->updateRiskRecord(risk_cont_st);

            LOG4CXX_TRACE(logger, "账户更新风控信息"LOG_NOVAR(risk_cont_st->user_id_)LOG_NOVAR(risk_cont_st->rc_type_)LOG_NOVAR(risk_cont_st->bTrigger_));
        }

        bool CAccountBaseHandler::getUserIsInRiskControl(RiskControlType rc_type) const
        {
            writeLock w1(m_mtx_sp);            
            switch (rc_type)
            {
            case AllTrade::RCT_WarningLine:
                return m_trigger_warning;
                break;
            case AllTrade::RCT_ForceLine:
                return m_trigger_force;
                break;
            case AllTrade::RCT_LimitLine:
                return m_trigger_limit;
                break;
            default:
                assert(0);
                break;
            }
            return false;
        }

        void CAccountBaseHandler::setParentHandler(const AccountHrPtr& parent)
        {
            writeLock w1(m_mtx_sp);
            m_parent = parent;
        }

        void CAccountBaseHandler::setAccountStruct(SAccountPtr ppb, const AccountHrPtr& parent)
        {
            assert(parent);
            {
                writeLock w1(m_mtx_sp);
                m_parent = parent;
                m_account_st_obj = ppb;
                if (m_money_hr)
                    m_money_hr->setParent(shared_from_this());
                strncpy_s(m_account_st_obj->update_datetime_, UtilityFun::getCurrentDateTime().c_str(), sizeof(m_account_st_obj->update_datetime_) - 1);
                m_is_modify = true;
            }
            serialize();
        }

        AllTrade::ErrorCodeType CAccountBaseHandler::moneyChange(Money_Change_Type money_change, YDouble money, const RemarkTextType remark)
        {
            if (m_money_hr)
                return m_money_hr->moneyChange(money_change, money, remark);

            return Err_Unknown;
        }

        AllTrade::ErrorCodeType CAccountBaseHandler::canOrder(YDouble highest_price)
        {
            ErrorCodeType rslt = canTrade(highest_price);
            if (rslt != Err_Succeed)
                return rslt;

            if (m_money_hr->getCanUse() < highest_price)
                return Err_Money_NotEnough;

            return Err_Succeed;
        }

        AllTrade::ErrorCodeType CAccountBaseHandler::canTrade(YDouble highest_price)
        {
            readLock w1(m_mtx_sp);

            if (m_trigger_force || m_trigger_limit)
            {
                if (m_trigger_force)
                {
                    LOG4CXX_INFO(logger, LOG_NOVAR(m_account_st_obj->user_id_)"账户处于强平状态");
                    return Error_User_NoOpen_Force;
                }
                else
                {
                    LOG4CXX_INFO(logger, LOG_NOVAR(m_account_st_obj->user_id_)"账户处于限仓状态");
                    return Error_User_NoOpen_Limit;
                }
            }

            if (m_account_st_obj->prop_ != E_ACCOUNT_PROP::EAP_Funder && m_account_st_obj->prop_ != E_ACCOUNT_PROP::EAP_Trader)
                return Err_Client_NoTrade;

            if (m_account_st_obj->status_ != EAS_Using)
                return Err_Client_NoTrade;

            return Err_Succeed;
        }

        AllTrade::ErrorCodeType CAccountBaseHandler::changePassword(const LoginPasswordType old_pass, const LoginPasswordType new_pass)
        {
            {
                writeLock w1(m_mtx_sp);
                if (strcmp(m_account_st_obj->password_, old_pass) != 0)
                    return Err_Login_Password;
                strncpy_s(m_account_st_obj->password_, new_pass, sizeof(m_account_st_obj->password_) - 1);
                m_is_modify = true;
            }
           
            ErrorCodeType rslt = serialize();
            if (rslt != Err_Succeed)
                strncpy_s(m_account_st_obj->password_, old_pass, sizeof(m_account_st_obj->password_) - 1);

            return rslt;
        }

        void CAccountBaseHandler::setLoginName(const LoginNameType name)
        {

        }

        void CAccountBaseHandler::setType(E_ACCOUNT_TYPE pst)
        {

        }

        void CAccountBaseHandler::setRegeditTime(const DateTimeType time_st)
        {

        }

        bool CAccountBaseHandler::checkUserData()
        {
            return false;
        }

        void CAccountBaseHandler::setCurNodeModiFlag(bool flag /*= true*/)
        {
            m_is_modify = flag;
        }

        void CAccountBaseHandler::setChildrenModiFlag(bool flag /*= true*/)
        {
            m_is_child_modify = flag;
        }

        ErrorCodeType CAccountBaseHandler::serialize()
        {
            writeLock lock(m_mtx_sp);
            if (m_money_hr)
            {
                m_money_hr->setParent(shared_from_this());
                m_money_hr->serialize();
            }

            // 无修改则无需重复序列化
            if (!m_is_modify)
                return Err_Succeed;

            if (!OperationManager::COperationManager::instance()->updateUserInfo(m_account_st_obj))
                return Err_Database;

            m_is_modify = false;
            return Err_Succeed;
        }

        AllTrade::ErrorCodeType CAccountBaseHandler::unserialize()
        {
            writeLock lock(m_mtx_sp);
            m_money_hr->setParent(shared_from_this());
            m_money_hr->unserialize();

            auto warn_ptr = OperationManager::COperationManager::instance()->getRiskRecord(m_account_st_obj->user_id_, RiskControlType::RCT_WarningLine);
            if (warn_ptr)
                m_trigger_warning = warn_ptr->bTrigger_;
            auto limit_ptr = OperationManager::COperationManager::instance()->getRiskRecord(m_account_st_obj->user_id_, RiskControlType::RCT_LimitLine);
            if (limit_ptr)
                m_trigger_limit = limit_ptr->bTrigger_;
            auto force_ptr = OperationManager::COperationManager::instance()->getRiskRecord(m_account_st_obj->user_id_, RiskControlType::RCT_ForceLine);
            if (force_ptr)
                m_trigger_force = force_ptr->bTrigger_;

            std::vector<SAccountPtr> children;
            if (!OperationManager::COperationManager::instance()->getAllDirectChildren(children, m_account_st_obj))
                return Err_Database;

            for (auto item : children)
            {
                AccountHrPtr new_acc_hr(nullptr);
                SMoneyInfoPtr money;
                OperationManager::COperationManager::instance()->getUserMoneyInfo(item->user_id_, money);
                SRiskInfoPtr risk;
                OperationManager::COperationManager::instance()->getUserRiskInfo(item->user_id_, risk);
                ErrorCodeType err_code = addAccount(new_acc_hr, item, money, risk);
                assert(err_code == Err_Succeed);
                new_acc_hr->unserialize();
            }

            m_is_modify= false;
            m_is_child_modify = false;
            return Err_Succeed;
        }

        AllTrade::ErrorCodeType CAccountBaseHandler::changePositionCost(YDouble cost_money, int vol, DirectType direct)
        {
            return m_money_hr->changePositionCost(cost_money, vol, direct);
        }

        AllTrade::NPMgrCenter::SMoneyInfoPtr CAccountBaseHandler::getMoneyCopy() const
        {
            return m_money_hr->getMoneyPtrCopy();
        }

        AllTrade::NPMgrCenter::SRiskInfoPtr CAccountBaseHandler::getRiskCopy() const
        {
            return std::make_shared<SRiskInfo>(*m_risk_st_obj.get());
        }

        AllTrade::ErrorCodeType CAccountBaseHandler::addAccount(AccountHrPtr& new_acc_hr, const SAccountPtr& acc_ptr, const SMoneyInfoPtr& money, const SRiskInfoPtr& risk)
        {
            strncpy_s(acc_ptr->parent_id_, m_account_st_obj->user_id_, sizeof(acc_ptr->parent_id_) - 1);
            acc_ptr->permission_ = m_account_st_obj->permission_;
            acc_ptr->level_ = m_account_st_obj->level_ + 1;
            return onAddAccount(new_acc_hr, acc_ptr, money, risk);
        }

        AllTrade::ErrorCodeType CAccountBaseHandler::updateRisk(SRiskInfoPtr sacc)
        {
            return Err_Unknown;
        }

#pragma endregion

#pragma region 根账户
        //////////////////////////////////////////////////////////////////////////
        CRootAccountHandler::CRootAccountHandler()
            : CAccountBaseHandler()
        {
            m_account_st_obj = std::make_shared<RootAccount>();
        }

        CRootAccountHandler::CRootAccountHandler(const SAccountPtr& account_st, const SMoneyInfoPtr& money, const SRiskInfoPtr& risk)
            : CAccountBaseHandler(account_st, money, risk)
        {
        }

        CRootAccountHandler::~CRootAccountHandler()
        {

        }

        AllTrade::NPMgrCenter::SAccountPtr CRootAccountHandler::getAccountCopy() const
        {
            readLock lock(m_mtx_sp);
            return std::make_shared<RootAccount>(*std::dynamic_pointer_cast<RootAccount>(m_account_st_obj).get());
        }

        std::vector<AccountHrPtr> CRootAccountHandler::getChildHrs(E_ACCOUNT_PROP acc_prop) const
        {
            return getAccountHrs(acc_prop);
        }

        std::vector<AccountHrPtr> CRootAccountHandler::getAccountHrs(E_ACCOUNT_PROP acc_prop) const
        {
            readLock lock(m_mtx_child);
            auto iter = m_children.find(acc_prop);
            if (iter != m_children.end())
                return iter->second.getAllAccountHrs();

            return std::vector<AccountHrPtr>();
        }

        int CRootAccountHandler::getAccountAllowMaxLevel() const
        {
            readLock lock(m_mtx_child);
            auto ptr = std::dynamic_pointer_cast<RootAccount>(m_account_st_obj);
            return ptr->allow_max_level_;
        }

        void CRootAccountHandler::setAccountAllowMaxLevel(int level) const
        {
            writeLock lock(m_mtx_child);
            auto ptr = std::dynamic_pointer_cast<RootAccount>(m_account_st_obj);
            ptr->allow_max_level_ = level;
        }

        int CRootAccountHandler::getAccountAllowMaxNum() const
        {
            readLock lock(m_mtx_child);
            auto ptr = std::dynamic_pointer_cast<RootAccount>(m_account_st_obj);
            return ptr->allow_max_num_;
        }

        void CRootAccountHandler::setAccountAllowMaxNum(int num) const
        {
            writeLock lock(m_mtx_child);
            auto ptr = std::dynamic_pointer_cast<RootAccount>(m_account_st_obj);
            ptr->allow_max_num_ = num;
        }

        size_t CRootAccountHandler::getAccountHrsCounnt() const
        {
            size_t rslt(0);
            for (auto item : m_children)
                rslt += item.second.getCount();
            return rslt;
        }

        AllTrade::ErrorCodeType CRootAccountHandler::onAddAccount(AccountHrPtr& acc_hr_ptr, const SAccountPtr& acc_ptr, const SMoneyInfoPtr& money, const SRiskInfoPtr& risk)
        {
            switch (acc_ptr->prop_)
            {
            case AllTrade::EAP_Agency:
                acc_hr_ptr = std::make_shared<CAgencyAccountHandler>(acc_ptr, money, risk);
                acc_hr_ptr->setAccountAllowMaxLevel(std::dynamic_pointer_cast<RootAccount>(m_account_st_obj)->allow_max_level_ - 1);
                break;
            case AllTrade::EAP_Risker:
                acc_hr_ptr = std::make_shared<CRiskAccountHandler>(acc_ptr, money, risk);
                break;
            case AllTrade::EAP_Manager:
                acc_hr_ptr = std::make_shared<CManagerAccountHandler>(acc_ptr, money, risk);
                break;
            case AllTrade::EAP_Trader:
                acc_hr_ptr = std::make_shared<CTradeAccountHandler>(acc_ptr, money, risk);
                break;
            case AllTrade::EAP_Funder:
                acc_hr_ptr = std::make_shared<CFunderAccountHandler>(acc_ptr, money, risk);
                break;
            default:
                return Error_No_SuchRights;
                break;
            }

            writeLock lock(m_mtx_child);
            AccountIndex& tmp = m_children[acc_hr_ptr->getAccountProp()];

            if (tmp.getAccountHrPtrByUserID(acc_hr_ptr->getAccountID().c_str())
                || tmp.getAccountHrPtrByLoginName(acc_hr_ptr->getAccountLoginName().c_str())
                || tmp.getAccountHrPtrByAccountName(acc_hr_ptr->getAccountName().c_str()))
                return Error_User_Exist;

            acc_hr_ptr->setParentHandler(shared_from_this());
            tmp.addToList(acc_hr_ptr);

            return Err_Succeed;
        }

#pragma endregion

#pragma region 管理账户
        //////////////////////////////////////////////////////////////////////////
        CManagerAccountHandler::CManagerAccountHandler()
            : CAccountBaseHandler()
        {

        }

        CManagerAccountHandler::CManagerAccountHandler(const SAccountPtr& account_st, const SMoneyInfoPtr& money, const SRiskInfoPtr& risk)
            : CAccountBaseHandler(account_st, money, risk)
        {

        }

        CManagerAccountHandler::~CManagerAccountHandler()
        {

        }

        AllTrade::NPMgrCenter::SAccountPtr CManagerAccountHandler::getAccountCopy() const
        {
            readLock lock(m_mtx_sp);
            return std::make_shared<ManagerAccount>(*std::dynamic_pointer_cast<ManagerAccount>(m_account_st_obj).get());
        }

        std::vector<AccountHrPtr> CManagerAccountHandler::getChildHrs(E_ACCOUNT_PROP acc_prop) const
        {
            return std::vector<AccountHrPtr>();
        }

        std::vector<AccountHrPtr> CManagerAccountHandler::getAccountHrs(E_ACCOUNT_PROP acc_prop) const
        {
            AccountHrPtr parent_ptr = getParentHandler();
            return parent_ptr->getAccountHrs(acc_prop);
        }

        int CManagerAccountHandler::getAccountAllowMaxLevel() const
        {
            AccountHrPtr parent_ptr = getParentHandler();
            return parent_ptr->getAccountAllowMaxLevel();
        }

        int CManagerAccountHandler::getAccountAllowMaxNum() const
        {
            AccountHrPtr parent_ptr = getParentHandler();
            return parent_ptr->getAccountAllowMaxNum();
        }

        size_t CManagerAccountHandler::getAccountHrsCounnt() const
        {
            AccountHrPtr parent_ptr = getParentHandler();
            return parent_ptr->getAccountHrsCounnt();
        }

        AllTrade::ErrorCodeType CManagerAccountHandler::onAddAccount(AccountHrPtr& new_acc_hr, const SAccountPtr& acc_ptr, const SMoneyInfoPtr& money, const SRiskInfoPtr& risk)
        {
            AccountHrPtr parent_ptr = getParentHandler();
            return parent_ptr->addAccount(new_acc_hr, acc_ptr, money, risk);
        }

#pragma endregion

#pragma region 机构账户
        //////////////////////////////////////////////////////////////////////////
        CAgencyAccountHandler::CAgencyAccountHandler()
            : CAccountBaseHandler()
        {

        }

        CAgencyAccountHandler::CAgencyAccountHandler(const SAccountPtr& account_st, const SMoneyInfoPtr& money, const SRiskInfoPtr& risk)
            : CAccountBaseHandler(account_st, money, risk)
        {

        }

        CAgencyAccountHandler::~CAgencyAccountHandler()
        {
        }

        AllTrade::NPMgrCenter::SAccountPtr CAgencyAccountHandler::getAccountCopy() const
        {
            readLock lock(m_mtx_sp);
            return std::make_shared<AgencyAccount>(*std::dynamic_pointer_cast<AgencyAccount>(m_account_st_obj).get());
        }

        std::vector<AccountHrPtr> CAgencyAccountHandler::getChildHrs(E_ACCOUNT_PROP acc_prop) const
        {
            return getAccountHrs(acc_prop);
        }

        std::vector<AccountHrPtr> CAgencyAccountHandler::getAccountHrs(E_ACCOUNT_PROP acc_prop) const
        {
            readLock lock(m_mtx_child);
            auto iter = m_children.find(acc_prop);
            if (iter != m_children.end())
                return iter->second.getAllAccountHrs();

            return std::vector<AccountHrPtr>();
        }

        int CAgencyAccountHandler::getAccountAllowMaxLevel() const
        {
            readLock lock(m_mtx_child);
            auto ptr = std::dynamic_pointer_cast<AgencyAccount>(m_account_st_obj);
            return ptr->allow_max_level_;
        }

        void CAgencyAccountHandler::setAccountAllowMaxLevel(int level) const
        {
            writeLock lock(m_mtx_child);
            auto ptr = std::dynamic_pointer_cast<AgencyAccount>(m_account_st_obj);
            ptr->allow_max_level_ = level;
        }

        int CAgencyAccountHandler::getAccountAllowMaxNum() const
        {
            readLock lock(m_mtx_child);
            auto ptr = std::dynamic_pointer_cast<AgencyAccount>(m_account_st_obj);
            return ptr->allow_max_num_;
        }

        void CAgencyAccountHandler::setAccountAllowMaxNum(int num) const
        {
            writeLock lock(m_mtx_child);
            auto ptr = std::dynamic_pointer_cast<AgencyAccount>(m_account_st_obj);
            ptr->allow_max_num_ = num;
        }

        size_t CAgencyAccountHandler::getAccountHrsCounnt() const
        {
            size_t rslt(0);
            for (auto item : m_children)
                rslt += item.second.getCount();
            return rslt;
        }

        AllTrade::ErrorCodeType CAgencyAccountHandler::updateRisk(SRiskInfoPtr sacc)
        {
            if (!OperationManager::COperationManager::instance()->updateUserRiskInfo(m_account_st_obj->user_id_, sacc))
                return Err_Database;

            m_risk_st_obj = sacc;
            return Err_Succeed;
        }

        AllTrade::ErrorCodeType CAgencyAccountHandler::onAddAccount(AccountHrPtr& acc_hr_ptr, const SAccountPtr& acc_ptr, const SMoneyInfoPtr& money, const SRiskInfoPtr& risk)
        {
            switch (acc_ptr->prop_)
            {
            case AllTrade::EAP_Agency:
                acc_hr_ptr = std::make_shared<CAgencyAccountHandler>(acc_ptr, money, risk);
                acc_hr_ptr->setAccountAllowMaxLevel(std::dynamic_pointer_cast<AgencyAccount>(m_account_st_obj)->allow_max_level_ - 1);
                break;
            case AllTrade::EAP_Risker:
                acc_hr_ptr = std::make_shared<CRiskAccountHandler>(acc_ptr, money, risk);
                break;
            case AllTrade::EAP_Manager:
                acc_hr_ptr = std::make_shared<CManagerAccountHandler>(acc_ptr, money, risk);
                break;
            case AllTrade::EAP_Trader:
                acc_hr_ptr = std::make_shared<CTradeAccountHandler>(acc_ptr, money, risk);
                break;
            default:
                return Error_No_SuchRights;
                break;
            }

            writeLock lock(m_mtx_child);
            AccountIndex& tmp = m_children[acc_hr_ptr->getAccountProp()];

            if (tmp.getAccountHrPtrByUserID(acc_hr_ptr->getAccountID().c_str())
                || tmp.getAccountHrPtrByLoginName(acc_hr_ptr->getAccountLoginName().c_str())
                || tmp.getAccountHrPtrByAccountName(acc_hr_ptr->getAccountName().c_str()))
                return Error_User_Exist;

            acc_hr_ptr->setParentHandler(shared_from_this());
            tmp.addToList(acc_hr_ptr);

            return Err_Succeed;
        }

#pragma endregion

#pragma region 风控账户
        //////////////////////////////////////////////////////////////////////////
        CRiskAccountHandler::CRiskAccountHandler()
            : CAccountBaseHandler()
        {

        }

        CRiskAccountHandler::CRiskAccountHandler(const SAccountPtr& account_st, const SMoneyInfoPtr& money, const SRiskInfoPtr& risk)
            : CAccountBaseHandler(account_st, money, risk)
        {

        }

        CRiskAccountHandler::~CRiskAccountHandler()
        {
        }

        AllTrade::NPMgrCenter::SAccountPtr CRiskAccountHandler::getAccountCopy() const
        {
            readLock lock(m_mtx_sp);
            return std::make_shared<RiskAccount>(*std::dynamic_pointer_cast<RiskAccount>(m_account_st_obj).get());
        }

        std::vector<AccountHrPtr> CRiskAccountHandler::getChildHrs(E_ACCOUNT_PROP acc_prop) const
        {
            return std::vector<AccountHrPtr>();
        }

        std::vector<AccountHrPtr> CRiskAccountHandler::getAccountHrs(E_ACCOUNT_PROP acc_prop) const
        {
            return std::vector<AccountHrPtr>();
        }

        AllTrade::ErrorCodeType CRiskAccountHandler::onAddAccount(AccountHrPtr& new_acc_hr, const SAccountPtr& acc_ptr, const SMoneyInfoPtr& money, const SRiskInfoPtr& risk)
        {
            return Error_No_SuchRights;
        }

#pragma endregion

#pragma region 交易账户
        //////////////////////////////////////////////////////////////////////////
        CTradeAccountHandler::CTradeAccountHandler()
            : CAccountBaseHandler()
        {

        }

        CTradeAccountHandler::CTradeAccountHandler(const SAccountPtr& account_st, const SMoneyInfoPtr& money, const SRiskInfoPtr& risk)
            : CAccountBaseHandler(account_st, money, risk)
        {

        }

        CTradeAccountHandler::~CTradeAccountHandler()
        {

        }

        AllTrade::NPMgrCenter::SAccountPtr CTradeAccountHandler::getAccountCopy() const
        {
            readLock lock(m_mtx_sp);
            return std::make_shared<TradeAccount>(*std::dynamic_pointer_cast<TradeAccount>(m_account_st_obj).get());
        }

        std::vector<AccountHrPtr> CTradeAccountHandler::getChildHrs(E_ACCOUNT_PROP acc_prop) const
        {
            return std::vector<AccountHrPtr>();
        }

        std::vector<AccountHrPtr> CTradeAccountHandler::getAccountHrs(E_ACCOUNT_PROP acc_prop) const
        {
            return std::vector<AccountHrPtr>();
        }

        AllTrade::ErrorCodeType CTradeAccountHandler::onAddAccount(AccountHrPtr& new_acc_hr, const SAccountPtr& acc_ptr, const SMoneyInfoPtr& money, const SRiskInfoPtr& risk)
        {
            return Error_No_SuchRights;
        }

        AllTrade::ErrorCodeType CTradeAccountHandler::updateRisk(SRiskInfoPtr sacc)
        {
            if (!OperationManager::COperationManager::instance()->updateUserRiskInfo(m_account_st_obj->user_id_, sacc))
                return Err_Database;

            m_risk_st_obj = sacc;
            return Err_Succeed;
        }

#pragma endregion

#pragma region 实盘账户
        CFunderAccountHandler::CFunderAccountHandler()
            : CAccountBaseHandler()
        {

        }

        CFunderAccountHandler::CFunderAccountHandler(const SAccountPtr& account_st, const SMoneyInfoPtr& money, const SRiskInfoPtr& risk)
            : CAccountBaseHandler(account_st, money, risk)
        {

        }

        CFunderAccountHandler::~CFunderAccountHandler()
        {

        }

        AllTrade::NPMgrCenter::SAccountPtr CFunderAccountHandler::getAccountCopy() const
        {
            readLock lock(m_mtx_sp);
            return std::make_shared<FunderAccount>(*std::dynamic_pointer_cast<FunderAccount>(m_account_st_obj).get());
        }

        std::vector<AccountHrPtr> CFunderAccountHandler::getChildHrs(E_ACCOUNT_PROP acc_prop) const
        {
            return std::vector<AccountHrPtr>();
        }

        std::vector<AccountHrPtr> CFunderAccountHandler::getAccountHrs(E_ACCOUNT_PROP acc_prop) const
        {
            return std::vector<AccountHrPtr>();
        }

        AllTrade::ErrorCodeType CFunderAccountHandler::onAddAccount(AccountHrPtr& new_acc_hr, const SAccountPtr& acc_ptr, const SMoneyInfoPtr& money, const SRiskInfoPtr& risk)
        {
            return Error_No_SuchRights;
        }

#pragma endregion

    }
}
