#include "AsyncQryService.h"
#include "include/ManagerCenter/ManagerCenter.h"
#include "include/TradeCenter/TradeCenter.h"
#include "Network/reply_message.h"
#include "define/struct_extern.h"
#include "Network/TCPImpl.h"
#include "utility/utility_fun.h"
#include "include/AuthorityControl/AuthorityControl.h"
#include "include/OperationManager/OperationManager.h"

#include "C:/ng_tools/ng_header_for_log4cxx/ng_header_for_log4cxx.hpp"
#include "C:/ng_tools/ng_header_for_log4cxx/ng_header_for_log4cxx_log_var.hpp"
NG_LOGGER(logger, "AsyncQryService");

using namespace AllTrade;
using namespace AllTrade::NPMgrCenter;
using namespace AllTrade::NPTradeCenter;

namespace xyc_communication{
    AsyncQryService::AsyncQryService()
        : m_dispatcher(this)
    {
    }

    AsyncQryService::~AsyncQryService()
    {
    }

    void AsyncQryService::qryUsingAgencys(const ReplyAgencyQryMsgPtr& msg_ptr)
    {
        TCPImpl* ptr = msg_ptr->getTCPImpl();
        std::vector<SAccountPtr> vec = AllTrade::NPMgrCenter::IManagerCenter::instance()->getAllUsingAgencysByLoginName(msg_ptr->getLoginName().c_str());
        msg_ptr->setResult(Err_Succeed);
        for (auto item : vec)
        {
            SAccountPtr parent_ptr = AllTrade::NPMgrCenter::IManagerCenter::instance()->getAccountByID(item->parent_id_);
            strncpy_s(msg_ptr->m_rtn_parent_login_name, parent_ptr->login_name_, sizeof(msg_ptr->m_rtn_parent_login_name) - 1);
            msg_ptr->m_rtn_agency = std::dynamic_pointer_cast<AgencyAccount>(item);
            msg_ptr->m_rtn_risk = AllTrade::NPMgrCenter::IManagerCenter::instance()->getRiskInfoByLoginName(item->login_name_);
            if (!msg_ptr->m_rtn_risk)
                msg_ptr->m_rtn_risk = std::make_shared<SRiskInfo>();
            SAccountPtr fund_ptr = AllTrade::NPMgrCenter::IManagerCenter::instance()->getAccountByID(msg_ptr->m_rtn_agency->fund_user_id_);
            if (fund_ptr)
                strncpy_s(msg_ptr->m_fund_login_name, fund_ptr->login_name_, sizeof(msg_ptr->m_fund_login_name) - 1);
            else
                memset(msg_ptr->m_fund_login_name, 0, sizeof(msg_ptr->m_fund_login_name) - 1);

            ptr->sendMessageInter(msg_ptr);
        }
        msg_ptr->m_blast = true;
        ptr->sendMessageInter(msg_ptr);
    }

    void AsyncQryService::qryCheckingAgencys(const ReplyAgencyPreApprovalQryMsgPtr& msg_ptr)
    {
        TCPImpl* ptr = msg_ptr->getTCPImpl();
        std::vector<SAccountPtr> vec = AllTrade::NPMgrCenter::IManagerCenter::instance()->getAllCheckingAgencysByLoginName(msg_ptr->getLoginName().c_str());
        msg_ptr->setResult(Err_Succeed);
        for (auto item : vec)
        {
            SAccountPtr parent_ptr = AllTrade::NPMgrCenter::IManagerCenter::instance()->getAccountByID(item->parent_id_);
            strncpy_s(msg_ptr->m_rtn_parent_login_name, parent_ptr->login_name_, sizeof(msg_ptr->m_rtn_parent_login_name) - 1);
            msg_ptr->m_rtn_agency = std::dynamic_pointer_cast<AgencyAccount>(item);
            msg_ptr->m_rtn_risk = AllTrade::NPMgrCenter::IManagerCenter::instance()->getRiskInfoByLoginName(item->login_name_);
            if (!msg_ptr->m_rtn_risk)
                msg_ptr->m_rtn_risk = std::make_shared<SRiskInfo>();
            SAccountPtr fund_ptr = AllTrade::NPMgrCenter::IManagerCenter::instance()->getAccountByID(msg_ptr->m_rtn_agency->fund_user_id_);
            if (fund_ptr)
                strncpy_s(msg_ptr->m_fund_login_name, fund_ptr->login_name_, sizeof(msg_ptr->m_fund_login_name) - 1);
            else
                memset(msg_ptr->m_fund_login_name, 0, sizeof(msg_ptr->m_fund_login_name) - 1);

            ptr->sendMessageInter(msg_ptr);
        }
        msg_ptr->m_blast = true;
        ptr->sendMessageInter(msg_ptr);
    }

    void AsyncQryService::qryUsingTradeAcc(const ReplyChildAccQryMsgPtr& msg_ptr)
    {
        TCPImpl* ptr = msg_ptr->getTCPImpl();
        std::vector<SAccountPtr> vec = AllTrade::NPMgrCenter::IManagerCenter::instance()->getAllUsingTradeAccByLoginName(msg_ptr->getLoginName().c_str());
        msg_ptr->setResult(Err_Succeed);
        for (auto item : vec)
        {
            msg_ptr->m_rtn_acc = std::dynamic_pointer_cast<TradeAccount>(item);
            SAccountPtr parent_ptr = AllTrade::NPMgrCenter::IManagerCenter::instance()->getAccountByID(msg_ptr->m_rtn_acc->parent_id_);
            SAccountPtr fund_ptr = AllTrade::NPMgrCenter::IManagerCenter::instance()->getAccountByID(msg_ptr->m_rtn_acc->fund_user_id_);
            strncpy_s(msg_ptr->m_rtn_parent_login_name, parent_ptr->login_name_, sizeof(msg_ptr->m_rtn_parent_login_name) - 1);
            if (fund_ptr)
                strncpy_s(msg_ptr->m_rtn_fund_login_name, fund_ptr->login_name_, sizeof(msg_ptr->m_rtn_fund_login_name) - 1);
            else
                memset(msg_ptr->m_rtn_fund_login_name, 0, sizeof(msg_ptr->m_rtn_fund_login_name) - 1);

            msg_ptr->m_rtn_risk = AllTrade::NPMgrCenter::IManagerCenter::instance()->getRiskInfoByLoginName(item->login_name_);
            if (!msg_ptr->m_rtn_risk)
                msg_ptr->m_rtn_risk = std::make_shared<SRiskInfo>();
            
            msg_ptr->m_rtn_money = AllTrade::NPMgrCenter::IManagerCenter::instance()->getMoneyInfoByLoginName(item->login_name_);
            if (!msg_ptr->m_rtn_money)
                msg_ptr->m_rtn_money = std::make_shared<SMoneyInfo>();
            
            ptr->sendMessageInter(msg_ptr);
        }
        msg_ptr->m_blast = true;
        ptr->sendMessageInter(msg_ptr);
    }

    void AsyncQryService::qryCheckingTradeAcc(const ReplyChildApprovalQryMsgPtr& msg_ptr)
    {
        TCPImpl* ptr = msg_ptr->getTCPImpl();
        std::vector<SAccountPtr> vec = AllTrade::NPMgrCenter::IManagerCenter::instance()->getAllCheckingTradeAccByLoginName(msg_ptr->getLoginName().c_str());
        msg_ptr->setResult(Err_Succeed);
        for (auto item : vec)
        {
            msg_ptr->m_rtn_acc = std::dynamic_pointer_cast<TradeAccount>(item);
            SAccountPtr parent_ptr = AllTrade::NPMgrCenter::IManagerCenter::instance()->getAccountByID(msg_ptr->m_rtn_acc->parent_id_);
            SAccountPtr fund_ptr = AllTrade::NPMgrCenter::IManagerCenter::instance()->getAccountByID(msg_ptr->m_rtn_acc->fund_user_id_);
            strncpy_s(msg_ptr->m_rtn_parent_login_name, parent_ptr->login_name_, sizeof(msg_ptr->m_rtn_parent_login_name) - 1);
            if (fund_ptr)
                strncpy_s(msg_ptr->m_rtn_fund_login_name, fund_ptr->login_name_, sizeof(msg_ptr->m_rtn_fund_login_name) - 1);
            else
                memset(msg_ptr->m_rtn_fund_login_name, 0, sizeof(msg_ptr->m_rtn_fund_login_name) - 1);

            msg_ptr->m_rtn_risk = AllTrade::NPMgrCenter::IManagerCenter::instance()->getRiskInfoByLoginName(item->login_name_);
            if (!msg_ptr->m_rtn_risk)
                msg_ptr->m_rtn_risk = std::make_shared<SRiskInfo>();

            msg_ptr->m_rtn_money = AllTrade::NPMgrCenter::IManagerCenter::instance()->getMoneyInfoByLoginName(item->login_name_);
            if (!msg_ptr->m_rtn_money)
                msg_ptr->m_rtn_money = std::make_shared<SMoneyInfo>();

			auto& createorPtr = AllTrade::NPMgrCenter::IManagerCenter::instance()->getAccountByID(item->create_id_);
			if (createorPtr)
				strncpy_s(msg_ptr->m_crLoginName, createorPtr->login_name_, sizeof(msg_ptr->m_crLoginName) - 1);

            ptr->sendMessageInter(msg_ptr);
        }
        msg_ptr->m_blast = true;
        ptr->sendMessageInter(msg_ptr);
    }

    void AsyncQryService::addManagerAcc(const ReplyManagerAddMsgPtr& msg_ptr)
    {
        TCPImpl* ptr = msg_ptr->getTCPImpl();
        SAccountPtr olditem_ptr = AllTrade::NPMgrCenter::IManagerCenter::instance()->getAccountByLoginName(msg_ptr->m_rtn_acc->login_name_);
        if (olditem_ptr)
        {
            ptr->sendMessageInter(ReplyMsg::getReply(Error_User_Exist, msg_ptr->getSocketID(), msg_ptr->getCmdCode()));
            return;
        }
        SAccountPtr create_ptr = AllTrade::NPMgrCenter::IManagerCenter::instance()->getAccountByLoginName(msg_ptr->getLoginName().c_str());
        if (!create_ptr)
        {
            ptr->sendMessageInter(ReplyMsg::getReply(Error_User_Creator_Unexist, msg_ptr->getSocketID(), msg_ptr->getCmdCode()));
            return;
        }

        ManagerAccountPtr item_ptr = msg_ptr->m_rtn_acc;
        strncpy_s(item_ptr->user_id_, UtilityFun::createGUID().c_str(), sizeof(item_ptr->user_id_) - 1);
        strncpy_s(item_ptr->create_id_, create_ptr->user_id_, sizeof(item_ptr->create_id_) - 1);
        strncpy_s(item_ptr->parent_id_, create_ptr->user_id_, sizeof(item_ptr->parent_id_) - 1);
        item_ptr->type_ = create_ptr->type_;

        ErrorCodeType errcode = AllTrade::NPMgrCenter::IManagerCenter::instance()->addAccount(item_ptr, SMoneyInfoPtr(), SRiskInfoPtr());
        msg_ptr->setResult(errcode);

        if (errcode == Err_Succeed)
            ptr->sendMessageToAllInter(create_ptr->user_id_, create_ptr->login_name_, msg_ptr);
        else
            ptr->sendMessageInter(msg_ptr);
    }

    void AsyncQryService::changeManagerAcc(const ReplyManagerChangeMsgPtr& msg_ptr)
    {
        TCPImpl* ptr = msg_ptr->getTCPImpl();
        SAccountPtr olditem_ptr = AllTrade::NPMgrCenter::IManagerCenter::instance()->getAccountByLoginName(msg_ptr->m_rtn_acc->login_name_);
        if (!olditem_ptr)
        {
            ptr->sendMessageInter(ReplyMsg::getReply(Error_User_Unexist, msg_ptr->getSocketID(), msg_ptr->getCmdCode()));
            return;
        }
        SAccountPtr create_ptr = AllTrade::NPMgrCenter::IManagerCenter::instance()->getAccountByLoginName(msg_ptr->getLoginName().c_str());
        if (!create_ptr)
        {
            ptr->sendMessageInter(ReplyMsg::getReply(Error_User_Creator_Unexist, msg_ptr->getSocketID(), msg_ptr->getCmdCode()));
            return;
        }
        ManagerAccountPtr item_ptr = std::dynamic_pointer_cast<ManagerAccount>(olditem_ptr);
        strncpy_s(item_ptr->account_name_, msg_ptr->m_rtn_acc->account_name_, sizeof(item_ptr->account_name_) - 1);
        strncpy_s(item_ptr->password_, msg_ptr->m_rtn_acc->password_, sizeof(item_ptr->password_) - 1);

        ErrorCodeType errcode = AllTrade::NPMgrCenter::IManagerCenter::instance()->updateAccount(item_ptr);
        msg_ptr->setResult(errcode);

        if (errcode == Err_Succeed)
            ptr->sendMessageToAllInter(create_ptr->user_id_, create_ptr->login_name_, msg_ptr);
        else
            ptr->sendMessageInter(msg_ptr);
    }

    void AsyncQryService::qryManagerAcc(const ReplyManagerQryMsgPtr& msg_ptr)
    {
        TCPImpl* ptr = msg_ptr->getTCPImpl();
        std::vector<ManagerAccountPtr> vec = AllTrade::NPMgrCenter::IManagerCenter::instance()->getManagersByLoginName(msg_ptr->getLoginName().c_str());
        msg_ptr->setResult(Err_Succeed);
        for (auto item : vec)
        {
            msg_ptr->m_rtn_acc = item;
            SAccountPtr parent_ptr = AllTrade::NPMgrCenter::IManagerCenter::instance()->getAccountByID(item->parent_id_);
            if (parent_ptr)
                strncpy_s(msg_ptr->m_parent_login_name, parent_ptr->login_name_, sizeof(msg_ptr->m_parent_login_name) - 1);
            ptr->sendMessageInter(msg_ptr);
        }
        msg_ptr->m_blast = true;
        ptr->sendMessageInter(msg_ptr);
    }

    void AsyncQryService::qryUsingManagerAcc(const ReplyManagerQryMsgPtr& msg_ptr)
    {
        TCPImpl* ptr = msg_ptr->getTCPImpl();
        std::vector<ManagerAccountPtr> vec = AllTrade::NPMgrCenter::IManagerCenter::instance()->getManagersByLoginName(msg_ptr->getLoginName().c_str());
        msg_ptr->setResult(Err_Succeed);
        for (auto& item : vec)
        {
            if (item->status_ == E_ACCOUNT_STATUS::EAS_Using)
            {
                msg_ptr->m_rtn_acc = item;
                SAccountPtr parent_ptr = AllTrade::NPMgrCenter::IManagerCenter::instance()->getAccountByID(item->parent_id_);
                if (parent_ptr)
                    strncpy_s(msg_ptr->m_parent_login_name, parent_ptr->login_name_, sizeof(msg_ptr->m_parent_login_name) - 1);

                ptr->sendMessageInter(msg_ptr);
            }
        }
        msg_ptr->m_blast = true;
        ptr->sendMessageInter(msg_ptr);
    }

    void AsyncQryService::addAgencyAcc(const ReplyAgencyAddMsgPtr& msg_ptr)
    {
        TCPImpl* ptr = msg_ptr->getTCPImpl();
        SAccountPtr olditem_ptr = AllTrade::NPMgrCenter::IManagerCenter::instance()->getAccountByLoginName(msg_ptr->m_rtn_acc->login_name_);
        if (olditem_ptr)
        {
            ptr->sendMessageInter(ReplyMsg::getReply(Error_User_Exist, msg_ptr->getSocketID(), msg_ptr->getCmdCode()));
            return;
        }

        SAccountPtr parent_ptr = AllTrade::NPMgrCenter::IManagerCenter::instance()->getAccountByLoginName(msg_ptr->m_parent_login_name);
        if (!parent_ptr)
        {
            ptr->sendMessageInter(ReplyMsg::getReply(Error_User_Parent_Unexist, msg_ptr->getSocketID(), msg_ptr->getCmdCode()));
            return;
        }
        strncpy_s(msg_ptr->m_parent_login_name, parent_ptr->login_name_, sizeof(msg_ptr->m_parent_login_name) - 1);
        if (parent_ptr->type_ != E_ACCOUNT_TYPE::EAT_SimuReal && msg_ptr->m_rtn_acc->type_ != parent_ptr->type_)
        {
            ptr->sendMessageInter(ReplyMsg::getReply(Error_User_Over_PropRights, msg_ptr->getSocketID(), msg_ptr->getCmdCode()));
            return;
        }

        SAccountPtr create_ptr = AllTrade::NPMgrCenter::IManagerCenter::instance()->getAccountByLoginName(msg_ptr->getLoginName().c_str());
        if (!create_ptr)
        {
            ptr->sendMessageInter(ReplyMsg::getReply(Error_User_Creator_Unexist, msg_ptr->getSocketID(), msg_ptr->getCmdCode()));
            return;
        }

        AgencyAccountPtr item_ptr = msg_ptr->m_rtn_acc;

        // 资金帐户
        if (item_ptr->type_ == E_ACCOUNT_TYPE::EAT_SimuReal
            || item_ptr->type_ == E_ACCOUNT_TYPE::EAT_Real)
        {
            SAccountPtr funder_ptr = AllTrade::NPMgrCenter::IManagerCenter::instance()->getAccountByLoginName(msg_ptr->m_fund_login_name);
            if (!funder_ptr)
            {

                AgencyAccountPtr agy_parent_ptr(nullptr);
                if (parent_ptr->prop_ == E_ACCOUNT_PROP::EAP_Manager)
                {
                    SAccountPtr acc_parent_ptr = AllTrade::NPMgrCenter::IManagerCenter::instance()->getAccountByID(parent_ptr->parent_id_);
                    if (acc_parent_ptr->prop_ == E_ACCOUNT_PROP::EAP_Agency)
                        agy_parent_ptr = std::dynamic_pointer_cast<AgencyAccount>(acc_parent_ptr);
                }
                else if (parent_ptr->prop_ == E_ACCOUNT_PROP::EAP_Agency)
                {
                    agy_parent_ptr = std::dynamic_pointer_cast<AgencyAccount>(parent_ptr);
                }
                if (agy_parent_ptr)
                    funder_ptr = AllTrade::NPMgrCenter::IManagerCenter::instance()->getAccountByID(agy_parent_ptr->fund_user_id_);

                if (!funder_ptr)
                {
                    ptr->sendMessageInter(ReplyMsg::getReply(Error_User_Funder_Unexist, msg_ptr->getSocketID(), msg_ptr->getCmdCode()));
                    return;
                }
            }
            strncpy_s(item_ptr->fund_user_id_, funder_ptr->user_id_, sizeof(item_ptr->fund_user_id_) - 1);
            strncpy_s(msg_ptr->m_fund_login_name, funder_ptr->login_name_, sizeof(msg_ptr->m_fund_login_name) - 1);
        }
        strncpy_s(item_ptr->user_id_, UtilityFun::createGUID().c_str(), sizeof(item_ptr->user_id_) - 1);

        // 推广码
        strncpy_s(item_ptr->agent_link_, OperationManager::COperationManager::instance()->getNewAgentLink().c_str(), sizeof(item_ptr->agent_link_) - 1);

        strncpy_s(item_ptr->create_id_, create_ptr->user_id_, sizeof(item_ptr->create_id_) - 1);
        strncpy_s(item_ptr->parent_id_, parent_ptr->user_id_, sizeof(item_ptr->parent_id_) - 1);

        ErrorCodeType errcode = AllTrade::NPMgrCenter::IManagerCenter::instance()->addAccount(item_ptr, msg_ptr->m_rtn_money, msg_ptr->m_rtn_risk);
        msg_ptr->setResult(errcode);

        ptr->sendMessageInter(msg_ptr);
        if (errcode == Err_Succeed)
            ptr->sendMessageToAllInter(parent_ptr->user_id_, parent_ptr->login_name_, msg_ptr);
    }

    void AsyncQryService::changeAgencyAcc(const ReplyAgencyChangeMsgPtr& msg_ptr)
    {
        TCPImpl* ptr = msg_ptr->getTCPImpl();
        SAccountPtr olditem_ptr = AllTrade::NPMgrCenter::IManagerCenter::instance()->getAccountByLoginName(msg_ptr->m_rtn_acc->login_name_);
        if (!olditem_ptr)
        {
            ptr->sendMessageInter(ReplyMsg::getReply(Error_User_Unexist, msg_ptr->getSocketID(), msg_ptr->getCmdCode()));
            return;
        }
        SAccountPtr parent_ptr = AllTrade::NPMgrCenter::IManagerCenter::instance()->getAccountByLoginName(msg_ptr->m_parent_login_name);
        if (!parent_ptr)
        {
            ptr->sendMessageInter(ReplyMsg::getReply(Error_User_Parent_Unexist, msg_ptr->getSocketID(), msg_ptr->getCmdCode()));
            return;
        }
        
        if (parent_ptr->type_ != E_ACCOUNT_TYPE::EAT_SimuReal && msg_ptr->m_rtn_acc->type_ != parent_ptr->type_)
        {
            ptr->sendMessageInter(ReplyMsg::getReply(Error_User_Over_PropRights, msg_ptr->getSocketID(), msg_ptr->getCmdCode()));
            return;
        }

        SAccountPtr create_ptr = AllTrade::NPMgrCenter::IManagerCenter::instance()->getAccountByLoginName(msg_ptr->getLoginName().c_str());
        if (!create_ptr)
        {
            ptr->sendMessageInter(ReplyMsg::getReply(Error_User_Creator_Unexist, msg_ptr->getSocketID(), msg_ptr->getCmdCode()));
            return;
        }

		// 获取被修改者账户
		auto& curPtr = AllTrade::NPMgrCenter::IManagerCenter::instance()->getAgencyByLoginName(olditem_ptr->login_name_);
		SAccountPtr curFund_ptr(nullptr);
		if (curPtr)
			curFund_ptr = AllTrade::NPMgrCenter::IManagerCenter::instance()->getAccountByID(curPtr->fund_user_id_);

        auto agy_children = AllTrade::NPMgrCenter::IManagerCenter::instance()->getAllChildren(olditem_ptr->user_id_);
        bool bChangeType(msg_ptr->m_rtn_acc->type_ != olditem_ptr->type_);

		if (curFund_ptr)
		{
			if (curFund_ptr->login_name_ != msg_ptr->m_fund_login_name && msg_ptr->m_rtn_acc->type_ != E_ACCOUNT_TYPE::EAT_Simulation) /// 修改了资金账户
				bChangeType = true;
		}

        for (auto item : agy_children)
        {
            if (item->prop_ == E_ACCOUNT_PROP::EAP_Trader)
            {
                if (bChangeType && !AllTrade::NPTradeCenter::ITradeCenter::instance()->getPositionList(item->user_id_).empty())
                {
                    ptr->sendMessageInter(ReplyMsg::getReply(Error_User_HasPosition, msg_ptr->getSocketID(), msg_ptr->getCmdCode()));
                    return;
                }
            }
            else if (item->prop_ == E_ACCOUNT_PROP::EAP_Agency)
            {
                if (strcmp(item->user_id_, parent_ptr->user_id_) == 0)
                {
                    ptr->sendMessageInter(ReplyMsg::getReply(Error_User_Parent_Reset, msg_ptr->getSocketID(), msg_ptr->getCmdCode()));
                    return;
                }
            }
        }

        AgencyAccountPtr item_ptr = std::dynamic_pointer_cast<AgencyAccount>(olditem_ptr);
        // 资金帐户
        if (msg_ptr->m_rtn_acc->type_ == E_ACCOUNT_TYPE::EAT_SimuReal
            || msg_ptr->m_rtn_acc->type_ == E_ACCOUNT_TYPE::EAT_Real)
        {
            SAccountPtr funder_ptr = AllTrade::NPMgrCenter::IManagerCenter::instance()->getAccountByLoginName(msg_ptr->m_fund_login_name);
            if (!funder_ptr)
            {
                AgencyAccountPtr agy_parent_ptr(nullptr);
                if (parent_ptr->prop_ == E_ACCOUNT_PROP::EAP_Manager)
                {
                    SAccountPtr acc_parent_ptr = AllTrade::NPMgrCenter::IManagerCenter::instance()->getAccountByID(parent_ptr->parent_id_);
                    if (acc_parent_ptr->prop_ == E_ACCOUNT_PROP::EAP_Agency)
                        agy_parent_ptr = std::dynamic_pointer_cast<AgencyAccount>(acc_parent_ptr);
                }
                else if (parent_ptr->prop_ == E_ACCOUNT_PROP::EAP_Agency)
                {
                    agy_parent_ptr = std::dynamic_pointer_cast<AgencyAccount>(parent_ptr);
                }
                if (agy_parent_ptr)
                    funder_ptr = AllTrade::NPMgrCenter::IManagerCenter::instance()->getAccountByID(agy_parent_ptr->fund_user_id_);

                if (!funder_ptr)
                {
                    ptr->sendMessageInter(ReplyMsg::getReply(Error_User_Funder_Unexist, msg_ptr->getSocketID(), msg_ptr->getCmdCode()));
                    return;
                }
            }
            strncpy_s(item_ptr->fund_user_id_, funder_ptr->user_id_, sizeof(item_ptr->fund_user_id_) - 1);
            strncpy_s(msg_ptr->m_fund_login_name, funder_ptr->login_name_, sizeof(msg_ptr->m_fund_login_name) - 1);
        }
        else
        {
            memset(item_ptr->fund_user_id_, 0, sizeof(item_ptr->fund_user_id_));
            memset(msg_ptr->m_fund_login_name, 0, sizeof(msg_ptr->m_fund_login_name));
        }

        strncpy_s(item_ptr->parent_id_, parent_ptr->user_id_, sizeof(item_ptr->parent_id_) - 1);
        strncpy_s(item_ptr->account_name_, msg_ptr->m_rtn_acc->account_name_, sizeof(item_ptr->account_name_) - 1);
        strncpy_s(item_ptr->password_, msg_ptr->m_rtn_acc->password_, sizeof(item_ptr->password_) - 1);
//         strncpy_s(item_ptr->agent_link_, msg_ptr->m_rtn_acc->agent_link_, sizeof(item_ptr->agent_link_) - 1);
//         item_ptr->allow_max_level_ = msg_ptr->m_rtn_acc->allow_max_level_;
//         item_ptr->allow_max_num_ = msg_ptr->m_rtn_acc->allow_max_num_;
//         item_ptr->status_ = msg_ptr->m_rtn_acc->status_;
        item_ptr->type_ = msg_ptr->m_rtn_acc->type_;
        strncpy_s(item_ptr->identity_, msg_ptr->m_rtn_acc->identity_, sizeof(item_ptr->identity_) - 1);
        strncpy_s(item_ptr->real_name_, msg_ptr->m_rtn_acc->real_name_, sizeof(item_ptr->real_name_) - 1);
        strncpy_s(item_ptr->phone_number_, msg_ptr->m_rtn_acc->phone_number_, sizeof(item_ptr->phone_number_) - 1);

        ErrorCodeType errcode = AllTrade::NPMgrCenter::IManagerCenter::instance()->updateAccount(item_ptr);
        msg_ptr->m_rtn_acc = item_ptr;
        if (errcode == Err_Succeed)
            errcode = AllTrade::NPMgrCenter::IManagerCenter::instance()->updateRisk(item_ptr->user_id_, msg_ptr->m_rtn_risk);
        msg_ptr->setResult(errcode);

        ptr->sendMessageInter(msg_ptr);
        if (errcode == Err_Succeed)
        {
            ptr->sendMessageToAllInter(parent_ptr->user_id_, parent_ptr->login_name_, msg_ptr);
            if (bChangeType && item_ptr->type_ != E_ACCOUNT_TYPE::EAT_SimuReal)
            {
                for (auto& child_item : agy_children)
                {
                    ReplyMsgPtr msg_ptr_push = nullptr;
                    child_item->type_ = item_ptr->type_;
                    switch (child_item->prop_)
                    {
                    case AllTrade::EAP_Agency:
                    {
                        AgencyAccountPtr agy_ptr = std::dynamic_pointer_cast<AgencyAccount>(child_item);
                        strncpy_s(agy_ptr->fund_user_id_, item_ptr->fund_user_id_, sizeof(agy_ptr->fund_user_id_) - 1);

                        ReplyAgencyChangeMsgPtr msg_ptr_push_tmp = std::make_shared<ReplyAgencyChangeMsg>();
                        msg_ptr_push_tmp->m_rtn_acc = agy_ptr;
                        msg_ptr_push_tmp->m_rtn_money = AllTrade::NPMgrCenter::IManagerCenter::instance()->getMoneyInfoByLoginName(agy_ptr->login_name_);
                        msg_ptr_push_tmp->m_rtn_risk = AllTrade::NPMgrCenter::IManagerCenter::instance()->getRiskInfoByLoginName(agy_ptr->login_name_);
                        strncpy_s(msg_ptr_push_tmp->m_fund_login_name, msg_ptr->m_fund_login_name, sizeof(msg_ptr_push_tmp->m_fund_login_name) - 1);
                        SAccountPtr parent_tmp = AllTrade::NPMgrCenter::IManagerCenter::instance()->getAccountByID(agy_ptr->parent_id_);
                        if (parent_tmp)
                            strncpy_s(msg_ptr_push_tmp->m_parent_login_name, parent_tmp->login_name_, sizeof(msg_ptr_push_tmp->m_parent_login_name) - 1);
                        msg_ptr_push = msg_ptr_push_tmp;
                    }
                        break;
                    case AllTrade::EAP_Trader:
                    {
                        TradeAccountPtr acc_ptr = std::dynamic_pointer_cast<TradeAccount>(child_item);
                        strncpy_s(acc_ptr->fund_user_id_, item_ptr->fund_user_id_, sizeof(acc_ptr->fund_user_id_) - 1);
                
                        ReplyChildAccChangeMsgPtr msg_ptr_push_tmp = std::make_shared<ReplyChildAccChangeMsg>();
                        msg_ptr_push_tmp->m_rtn_acc = acc_ptr;
                        msg_ptr_push_tmp->m_rtn_money = AllTrade::NPMgrCenter::IManagerCenter::instance()->getMoneyInfoByLoginName(acc_ptr->login_name_);
                        msg_ptr_push_tmp->m_rtn_risk = AllTrade::NPMgrCenter::IManagerCenter::instance()->getRiskInfoByLoginName(acc_ptr->login_name_);
                        strncpy_s(msg_ptr_push_tmp->m_fund_login_name, msg_ptr->m_fund_login_name, sizeof(msg_ptr_push_tmp->m_fund_login_name) - 1);
                        SAccountPtr parent_tmp = AllTrade::NPMgrCenter::IManagerCenter::instance()->getAccountByID(acc_ptr->parent_id_);
                        if (parent_tmp)
                            strncpy_s(msg_ptr_push_tmp->m_parent_login_name, parent_tmp->login_name_, sizeof(msg_ptr_push_tmp->m_parent_login_name) - 1);
                        msg_ptr_push = msg_ptr_push_tmp;
                    }
                        break;
                    default:
                        break;
                    }

                    if (msg_ptr_push)
                    {
                        ErrorCodeType errcode = AllTrade::NPMgrCenter::IManagerCenter::instance()->updateAccount(child_item);
                        SAccountPtr child_parent_ptr = AllTrade::NPMgrCenter::IManagerCenter::instance()->getAccountByID(child_item->parent_id_);

                        msg_ptr_push->setResult(errcode);
                        ptr->sendMessageToAllInter(child_parent_ptr->user_id_, child_parent_ptr->login_name_, msg_ptr_push);
                    }
                }
            }
        }
    }

    void AsyncQryService::checkAgencyAcc(const ReplyAgencyApprovalMsgPtr& msg_ptr)
    {
        TCPImpl* ptr = msg_ptr->getTCPImpl();
        AgencyAccountPtr item_ptr = std::dynamic_pointer_cast<AgencyAccount>(AllTrade::NPMgrCenter::IManagerCenter::instance()->getAccountByLoginName(msg_ptr->m_acc_login_name));
        if (!item_ptr)
        {
            ptr->sendMessageInter(ReplyMsg::getReply(Error_User_Unexist, msg_ptr->getSocketID(), msg_ptr->getCmdCode()));
            return;
        }
        if (item_ptr->type_ == E_ACCOUNT_TYPE::EAT_SimuReal
            || item_ptr->type_ == E_ACCOUNT_TYPE::EAT_Real)
        {
            SAccountPtr funder_ptr = AllTrade::NPMgrCenter::IManagerCenter::instance()->getAccountByID(item_ptr->fund_user_id_);
            if (!funder_ptr || funder_ptr->status_ != E_ACCOUNT_STATUS::EAS_Using)
            {
                ptr->sendMessageInter(ReplyMsg::getReply(Error_User_Funder_Unexist, msg_ptr->getSocketID(), msg_ptr->getCmdCode()));
                return;
            }
            strncpy_s(msg_ptr->m_fund_login_name, funder_ptr->login_name_, sizeof(msg_ptr->m_fund_login_name) - 1);
        }

        SAccountPtr parent_ptr = AllTrade::NPMgrCenter::IManagerCenter::instance()->getAccountByID(item_ptr->parent_id_);
        if (!parent_ptr)
        {
            ptr->sendMessageInter(ReplyMsg::getReply(Error_User_Parent_Unexist, msg_ptr->getSocketID(), msg_ptr->getCmdCode()));
            return;
        }
        strncpy_s(msg_ptr->m_parent_login_name, parent_ptr->login_name_, sizeof(msg_ptr->m_parent_login_name) - 1);

        item_ptr->status_ = msg_ptr->m_bApproval;

        ErrorCodeType errcode = AllTrade::NPMgrCenter::IManagerCenter::instance()->checkAccount(item_ptr->user_id_, item_ptr->status_);
        msg_ptr->setResult(errcode);

        msg_ptr->m_rtn_acc = item_ptr;
        msg_ptr->m_rtn_money = AllTrade::NPMgrCenter::IManagerCenter::instance()->getMoneyInfoByLoginName(item_ptr->login_name_);
        msg_ptr->m_rtn_risk = AllTrade::NPMgrCenter::IManagerCenter::instance()->getRiskInfoByLoginName(item_ptr->login_name_);

        ptr->sendMessageInter(msg_ptr);
        if (errcode == Err_Succeed)
            ptr->sendMessageToAllInter(parent_ptr->user_id_, parent_ptr->login_name_, msg_ptr);
    }

    void AsyncQryService::autoCreateTradeUser(const ReplyChildAccAutoAddMsgPtr& msg_ptr)
    {
        TCPImpl* ptr = msg_ptr->getTCPImpl();
        // 是否已存在
        SAccountPtr olditem_ptr = AllTrade::NPMgrCenter::IManagerCenter::instance()->getAccountByLoginName(msg_ptr->m_rtn_acc->login_name_);
        if (olditem_ptr)
        {
            ptr->sendMessageInter(ReplyMsg::getReply(Error_User_Exist, msg_ptr->getSocketID(), msg_ptr->getCmdCode()));
            return;
        }

        // 根据推广码找到父级
        SAccountPtr parent_ptr = AllTrade::NPMgrCenter::IManagerCenter::instance()->getAccountByPopLink(msg_ptr->m_pop_link);
        if (!parent_ptr)
        {
            ptr->sendMessageInter(ReplyMsg::getReply(Error_User_Parent_Unexist, msg_ptr->getSocketID(), msg_ptr->getCmdCode()));
            return;
        }
        strncpy_s(msg_ptr->m_parent_login_name, parent_ptr->login_name_, sizeof(msg_ptr->m_parent_login_name) - 1);
        // 父级为实盘/模拟盘则新增子账户也为实盘/模拟盘
        if (parent_ptr->type_ != E_ACCOUNT_TYPE::EAT_SimuReal && msg_ptr->m_rtn_acc->type_ != parent_ptr->type_)
        {
            ptr->sendMessageInter(ReplyMsg::getReply(Error_User_Over_PropRights, msg_ptr->getSocketID(), msg_ptr->getCmdCode()));
            return;
        }

        // 若为实盘账户则需要绑定实盘账号
        if (msg_ptr->m_rtn_acc->type_ == E_ACCOUNT_TYPE::EAT_Real)
        {
            SAccountPtr fund_ptr(nullptr);
            // 若为根账户或根账户的管理员,则直接获取资金账户
            if (parent_ptr->prop_ == E_ACCOUNT_PROP::EAP_Root
                || (parent_ptr->prop_ == E_ACCOUNT_PROP::EAP_Manager && parent_ptr->level_ == 1)
                )
            {
                fund_ptr = AllTrade::NPMgrCenter::IManagerCenter::instance()->getAccountByLoginName(msg_ptr->m_fund_login_name);
            }
            // 若为机构或非根账户管理员,则需要获取其父级资金帐户
            else if (parent_ptr->prop_ == E_ACCOUNT_PROP::EAP_Agency || parent_ptr->prop_ == E_ACCOUNT_PROP::EAP_Manager)
            {
                AgencyAccountPtr agy_parent_ptr(nullptr);
                if (parent_ptr->prop_ == E_ACCOUNT_PROP::EAP_Manager)
                {
                    SAccountPtr acc_parent_ptr = AllTrade::NPMgrCenter::IManagerCenter::instance()->getAccountByID(parent_ptr->parent_id_);
                    if (acc_parent_ptr->prop_ == E_ACCOUNT_PROP::EAP_Agency)
                        agy_parent_ptr = std::dynamic_pointer_cast<AgencyAccount>(acc_parent_ptr);
                }
                else if (parent_ptr->prop_ == E_ACCOUNT_PROP::EAP_Agency)
                {
                    agy_parent_ptr = std::dynamic_pointer_cast<AgencyAccount>(parent_ptr);
                }
                if (agy_parent_ptr)
                    fund_ptr = AllTrade::NPMgrCenter::IManagerCenter::instance()->getAccountByID(agy_parent_ptr->fund_user_id_);

            }

            // 获取父账户资金帐户对象
            if (!fund_ptr)
            {
                ptr->sendMessageInter(ReplyMsg::getReply(Error_User_Funder_Unexist, msg_ptr->getSocketID(), msg_ptr->getCmdCode()));
                return;
            }

            strncpy_s(msg_ptr->m_fund_login_name, fund_ptr->login_name_, sizeof(msg_ptr->m_fund_login_name) - 1);
            strncpy_s(msg_ptr->m_rtn_acc->fund_user_id_, fund_ptr->user_id_, sizeof(msg_ptr->m_rtn_acc->fund_user_id_) - 1);
        }

        TradeAccountPtr item_ptr = msg_ptr->m_rtn_acc;
        strncpy_s(item_ptr->user_id_, UtilityFun::createGUID().c_str(), sizeof(item_ptr->user_id_) - 1);
        strncpy_s(item_ptr->create_id_, "", sizeof(item_ptr->create_id_) - 1);
        strncpy_s(item_ptr->parent_id_, parent_ptr->user_id_, sizeof(item_ptr->parent_id_) - 1);

        ErrorCodeType errcode = AllTrade::NPMgrCenter::IManagerCenter::instance()->addAccount(item_ptr, std::make_shared<SMoneyInfo>(), msg_ptr->m_rtn_risk);

        msg_ptr->setResult(errcode);

        ptr->sendMessageInter(msg_ptr);
        if (errcode == Err_Succeed)
            ptr->sendMessageToAllInter(parent_ptr->user_id_, parent_ptr->login_name_, msg_ptr);
    }

    void AsyncQryService::addTradeAcc(const ReplyChildAccAddMsgPtr& msg_ptr)
    {
        TCPImpl* ptr = msg_ptr->getTCPImpl();
        // 是否已存在
        SAccountPtr olditem_ptr = AllTrade::NPMgrCenter::IManagerCenter::instance()->getAccountByLoginName(msg_ptr->m_rtn_acc->login_name_);
        if (olditem_ptr)
        {
            ptr->sendMessageInter(ReplyMsg::getReply(Error_User_Exist, msg_ptr->getSocketID(), msg_ptr->getCmdCode()));
            return;
        }
        // 父级账户是否存在
        SAccountPtr parent_ptr = AllTrade::NPMgrCenter::IManagerCenter::instance()->getAccountByLoginName(msg_ptr->m_parent_login_name);
        if (!parent_ptr)
        {
            ptr->sendMessageInter(ReplyMsg::getReply(Error_User_Parent_Unexist, msg_ptr->getSocketID(), msg_ptr->getCmdCode()));
            return;
        }
        // 父级为实盘/模拟盘则新增子账户也为实盘/模拟盘
        if (parent_ptr->type_ != E_ACCOUNT_TYPE::EAT_SimuReal && msg_ptr->m_rtn_acc->type_ != parent_ptr->type_)
        {
            ptr->sendMessageInter(ReplyMsg::getReply(Error_User_Over_PropRights, msg_ptr->getSocketID(), msg_ptr->getCmdCode()));
            return;
        }

        // 若为实盘账户则需要绑定实盘账号
        if (msg_ptr->m_rtn_acc->type_ == E_ACCOUNT_TYPE::EAT_Real)
        {
            SAccountPtr fund_ptr(nullptr);
            // 若为根账户或根账户的管理员,则直接获取资金账户
            if (parent_ptr->prop_ == E_ACCOUNT_PROP::EAP_Root
                || (parent_ptr->prop_ == E_ACCOUNT_PROP::EAP_Manager && parent_ptr->level_ == 1)
                )
            {
                fund_ptr = AllTrade::NPMgrCenter::IManagerCenter::instance()->getAccountByLoginName(msg_ptr->m_fund_login_name);
            }
            // 若为机构或非根账户管理员,则需要获取其父级资金帐户
            else if (parent_ptr->prop_ == E_ACCOUNT_PROP::EAP_Agency || parent_ptr->prop_ == E_ACCOUNT_PROP::EAP_Manager)
            {
                AgencyAccountPtr agy_parent_ptr(nullptr);
                if (parent_ptr->prop_ == E_ACCOUNT_PROP::EAP_Manager)
                {
                    SAccountPtr acc_parent_ptr = AllTrade::NPMgrCenter::IManagerCenter::instance()->getAccountByID(parent_ptr->parent_id_);
                    if (acc_parent_ptr->prop_ == E_ACCOUNT_PROP::EAP_Agency)
                        agy_parent_ptr = std::dynamic_pointer_cast<AgencyAccount>(acc_parent_ptr);
                }
                else if (parent_ptr->prop_ == E_ACCOUNT_PROP::EAP_Agency)
                {
                    agy_parent_ptr = std::dynamic_pointer_cast<AgencyAccount>(parent_ptr);
                }
                if (agy_parent_ptr)
                    fund_ptr = AllTrade::NPMgrCenter::IManagerCenter::instance()->getAccountByID(agy_parent_ptr->fund_user_id_);

            }

            // 获取父账户资金帐户对象
            if (!fund_ptr)
            {
                ptr->sendMessageInter(ReplyMsg::getReply(Error_User_Funder_Unexist, msg_ptr->getSocketID(), msg_ptr->getCmdCode()));
                return;
            }

            strncpy_s(msg_ptr->m_fund_login_name, fund_ptr->login_name_, sizeof(msg_ptr->m_fund_login_name) - 1);
            strncpy_s(msg_ptr->m_rtn_acc->fund_user_id_, fund_ptr->user_id_, sizeof(msg_ptr->m_rtn_acc->fund_user_id_) - 1);
        }

        SAccountPtr create_ptr = AllTrade::NPMgrCenter::IManagerCenter::instance()->getAccountByLoginName(msg_ptr->getLoginName().c_str());
        if (!create_ptr)
        {
            ptr->sendMessageInter(ReplyMsg::getReply(Error_User_Creator_Unexist, msg_ptr->getSocketID(), msg_ptr->getCmdCode()));
            return;
        }

        TradeAccountPtr item_ptr = msg_ptr->m_rtn_acc;
        strncpy_s(item_ptr->user_id_, UtilityFun::createGUID().c_str(), sizeof(item_ptr->user_id_) - 1);
        strncpy_s(item_ptr->create_id_, create_ptr->user_id_, sizeof(item_ptr->create_id_) - 1);
        strncpy_s(item_ptr->parent_id_, parent_ptr->user_id_, sizeof(item_ptr->parent_id_) - 1);

        ErrorCodeType errcode = AllTrade::NPMgrCenter::IManagerCenter::instance()->addAccount(item_ptr, std::make_shared<SMoneyInfo>(), msg_ptr->m_rtn_risk);
        AllTrade::NPMgrCenter::IManagerCenter::instance()->moneyChange(item_ptr->user_id_, Money_Change_Type::MC_In_Deposit, msg_ptr->m_rtn_money->user_deposit_, "系统初始保证金");
        AllTrade::NPMgrCenter::IManagerCenter::instance()->moneyChange(item_ptr->user_id_, Money_Change_Type::MC_In_Equipment, msg_ptr->m_rtn_money->priority_fund_, "系统初始优先资金");

        msg_ptr->setResult(errcode);

        ptr->sendMessageInter(msg_ptr);
        if (errcode == Err_Succeed)
            ptr->sendMessageToAllInter(parent_ptr->user_id_, parent_ptr->login_name_, msg_ptr);
    }

    void AsyncQryService::changeTradeAcc(const ReplyChildAccChangeMsgPtr& msg_ptr)
    {
        TCPImpl* ptr = msg_ptr->getTCPImpl();
        SAccountPtr olditem_ptr = AllTrade::NPMgrCenter::IManagerCenter::instance()->getAccountByLoginName(msg_ptr->m_rtn_acc->login_name_);
        if (!olditem_ptr)
        {
            ptr->sendMessageInter(ReplyMsg::getReply(Error_User_Unexist, msg_ptr->getSocketID(), msg_ptr->getCmdCode()));
            return;
        }
        SAccountPtr parent_ptr = AllTrade::NPMgrCenter::IManagerCenter::instance()->getAccountByLoginName(msg_ptr->m_parent_login_name);
        if (!parent_ptr)
        {
            ptr->sendMessageInter(ReplyMsg::getReply(Error_User_Parent_Unexist, msg_ptr->getSocketID(), msg_ptr->getCmdCode()));
            return;
        }
        // 账户类型改变
        if (msg_ptr->m_rtn_acc->type_ != olditem_ptr->type_ || strcmp(olditem_ptr->parent_id_, parent_ptr->user_id_) != 0)
        {
            if (!AllTrade::NPTradeCenter::ITradeCenter::instance()->getPositionList(olditem_ptr->user_id_).empty())
            {
                ptr->sendMessageInter(ReplyMsg::getReply(Error_User_HasPosition, msg_ptr->getSocketID(), msg_ptr->getCmdCode()));
                return;
            }
        }

        TradeAccountPtr item_ptr = std::dynamic_pointer_cast<TradeAccount>(olditem_ptr);
        // 资金帐户
//         LoginNameType fund_userid = { 0 };
        if (strnlen_s(msg_ptr->m_fund_login_name, sizeof(msg_ptr->m_fund_login_name)) != 0)
        {
            SAccountPtr fund_ptr = AllTrade::NPMgrCenter::IManagerCenter::instance()->getAccountByLoginName(msg_ptr->m_fund_login_name);
            if (!fund_ptr)
            {
                ptr->sendMessageInter(ReplyMsg::getReply(Error_User_Funder_Unexist, msg_ptr->getSocketID(), msg_ptr->getCmdCode()));
                return;
            }
            strncpy_s(item_ptr->fund_user_id_, fund_ptr->user_id_, sizeof(item_ptr->fund_user_id_) - 1);
            strncpy_s(msg_ptr->m_fund_login_name, fund_ptr->login_name_, sizeof(msg_ptr->m_fund_login_name) - 1);
        }
        else if (msg_ptr->m_rtn_acc->type_ == E_ACCOUNT_TYPE::EAT_SimuReal
            || msg_ptr->m_rtn_acc->type_ == E_ACCOUNT_TYPE::EAT_Real)
        {
            SAccountPtr fund_ptr(nullptr);
            AgencyAccountPtr agy_parent_ptr(nullptr);
            if (parent_ptr->prop_ == E_ACCOUNT_PROP::EAP_Manager)
            {
                SAccountPtr acc_parent_ptr = AllTrade::NPMgrCenter::IManagerCenter::instance()->getAccountByID(parent_ptr->parent_id_);
                if (acc_parent_ptr->prop_ == E_ACCOUNT_PROP::EAP_Agency)
                    agy_parent_ptr = std::dynamic_pointer_cast<AgencyAccount>(acc_parent_ptr);
            }
            else if (parent_ptr->prop_ == E_ACCOUNT_PROP::EAP_Agency)
            {
                agy_parent_ptr = std::dynamic_pointer_cast<AgencyAccount>(parent_ptr);
            }
            if (agy_parent_ptr)
                fund_ptr = AllTrade::NPMgrCenter::IManagerCenter::instance()->getAccountByID(agy_parent_ptr->fund_user_id_);

            if (!fund_ptr)
            {
                ptr->sendMessageInter(ReplyMsg::getReply(Error_User_Funder_Unexist, msg_ptr->getSocketID(), msg_ptr->getCmdCode()));
                return;
            }
            strncpy_s(item_ptr->fund_user_id_, fund_ptr->user_id_, sizeof(item_ptr->fund_user_id_) - 1);
            strncpy_s(msg_ptr->m_fund_login_name, fund_ptr->login_name_, sizeof(msg_ptr->m_fund_login_name) - 1);
        }
        else if (msg_ptr->m_rtn_acc->type_ == E_ACCOUNT_TYPE::EAT_Simulation)
        {
            memset(item_ptr->fund_user_id_, 0, sizeof(item_ptr->fund_user_id_));
        }

        strncpy_s(item_ptr->account_name_, msg_ptr->m_rtn_acc->account_name_, sizeof(item_ptr->account_name_) - 1);
        strncpy_s(item_ptr->password_, msg_ptr->m_rtn_acc->password_, sizeof(item_ptr->password_) - 1);
        strncpy_s(item_ptr->agent_link_, msg_ptr->m_rtn_acc->agent_link_, sizeof(item_ptr->agent_link_) - 1);
//         item_ptr->status_ = msg_ptr->m_rtn_acc->status_;
        item_ptr->type_ = msg_ptr->m_rtn_acc->type_;
        strncpy_s(item_ptr->identity_, msg_ptr->m_rtn_acc->identity_, sizeof(item_ptr->identity_) - 1);
        strncpy_s(item_ptr->real_name_, msg_ptr->m_rtn_acc->real_name_, sizeof(item_ptr->real_name_) - 1);
        strncpy_s(item_ptr->phone_number_, msg_ptr->m_rtn_acc->phone_number_, sizeof(item_ptr->phone_number_) - 1);
		strncpy_s(item_ptr->parent_id_, parent_ptr->user_id_, sizeof(item_ptr->parent_id_) - 1);

        ErrorCodeType errcode = AllTrade::NPMgrCenter::IManagerCenter::instance()->updateAccount(item_ptr);
        msg_ptr->m_rtn_acc = item_ptr;
        if (errcode == Err_Succeed)
        {
            errcode = AllTrade::NPMgrCenter::IManagerCenter::instance()->updateRisk(item_ptr->user_id_, msg_ptr->m_rtn_risk);
            AllTrade::NPTradeCenter::ITradeCenter::instance()->recalculate_risk(CommodityTypeType::COMMODITY_TYPE_STOCK, item_ptr->user_id_);
        }
        msg_ptr->setResult(errcode);

        msg_ptr->m_rtn_money = AllTrade::NPMgrCenter::IManagerCenter::instance()->getMoneyInfoByLoginName(item_ptr->login_name_);

        ptr->sendMessageInter(msg_ptr);
        if (errcode == Err_Succeed)
            ptr->sendMessageToAllInter(parent_ptr->user_id_, parent_ptr->login_name_, msg_ptr);
    }

    void AsyncQryService::checkTradeAcc(const ReplyChildAccApprovalMsgPtr& msg_ptr)
    {
        TCPImpl* ptr = msg_ptr->getTCPImpl();
        TradeAccountPtr item_ptr = std::dynamic_pointer_cast<TradeAccount>(AllTrade::NPMgrCenter::IManagerCenter::instance()->getAccountByLoginName(msg_ptr->m_rtn_acc->login_name_));
        if (!item_ptr)
        {
            ptr->sendMessageInter(ReplyMsg::getReply(Error_User_Unexist, msg_ptr->getSocketID(), msg_ptr->getCmdCode()));
            return;
        }
        SAccountPtr parent_ptr = AllTrade::NPMgrCenter::IManagerCenter::instance()->getAccountByID(item_ptr->parent_id_);
        if (!parent_ptr)
        {
            ptr->sendMessageInter(ReplyMsg::getReply(Error_User_Parent_Unexist, msg_ptr->getSocketID(), msg_ptr->getCmdCode()));
            return;
        }
        strncpy_s(msg_ptr->m_rtn_parent_login_name, parent_ptr->login_name_, sizeof(msg_ptr->m_rtn_parent_login_name) - 1);

        if (item_ptr->type_ != E_ACCOUNT_TYPE::EAT_Simulation)
        {
            SAccountPtr funder_ptr = AllTrade::NPMgrCenter::IManagerCenter::instance()->getAccountByID(item_ptr->fund_user_id_);
            if (!funder_ptr)
            {
                ptr->sendMessageInter(ReplyMsg::getReply(Error_User_Funder_Unexist, msg_ptr->getSocketID(), msg_ptr->getCmdCode()));
                return;
            }
            else
                strncpy_s(msg_ptr->m_rtn_fund_login_name, funder_ptr->login_name_, sizeof(msg_ptr->m_rtn_fund_login_name) - 1);
        }

        item_ptr->status_ = msg_ptr->m_bApproval;
		strncpy_s(item_ptr->auditor_name_, msg_ptr->m_opLoginName, sizeof(item_ptr->auditor_name_) - 1);
		strncpy_s(item_ptr->auditor_datetime_, UtilityFun::getCurrentDateTime().c_str(), sizeof(item_ptr->auditor_datetime_) - 1);
		strncpy_s(msg_ptr->m_crLoginName, parent_ptr->login_name_, sizeof(msg_ptr->m_crLoginName) - 1);
		

		ErrorCodeType errcode = AllTrade::NPMgrCenter::IManagerCenter::instance()->checkAccount(item_ptr->user_id_, item_ptr->status_, msg_ptr->m_opLoginName);
        msg_ptr->setResult(errcode);
        msg_ptr->m_rtn_acc = item_ptr;
        msg_ptr->m_rtn_money = AllTrade::NPMgrCenter::IManagerCenter::instance()->getMoneyInfoByLoginName(item_ptr->login_name_);
        msg_ptr->m_rtn_risk = AllTrade::NPMgrCenter::IManagerCenter::instance()->getRiskInfoByLoginName(item_ptr->login_name_);

        ptr->sendMessageInter(msg_ptr);
        if (errcode == Err_Succeed)
            ptr->sendMessageToAllInter(parent_ptr->user_id_, parent_ptr->login_name_, msg_ptr);
    }

    void AsyncQryService::qryFunderAcc(const ReplyFundAccQryMsgPtr& msg_ptr)
    {
        std::vector<SAccountPtr> vec = AllTrade::NPMgrCenter::IManagerCenter::instance()->getAllFunderAccByLoginName(msg_ptr->getLoginName().c_str());
        msg_ptr->setResult(Err_Succeed);
        TCPImpl* ptr = msg_ptr->getTCPImpl();
        for (auto item : vec)
        {
            msg_ptr->m_rtn_acc = std::dynamic_pointer_cast<FunderAccount>(item);
            SAccountPtr parent_ptr = AllTrade::NPMgrCenter::IManagerCenter::instance()->getAccountByID(msg_ptr->m_rtn_acc->parent_id_);
            strncpy_s(msg_ptr->m_rtn_parent_login_name, parent_ptr->login_name_, sizeof(msg_ptr->m_rtn_parent_login_name) - 1);

            msg_ptr->m_rtn_money = AllTrade::NPMgrCenter::IManagerCenter::instance()->getMoneyInfoByLoginName(item->login_name_);
            if (!msg_ptr->m_rtn_money)
                msg_ptr->m_rtn_money = std::make_shared<SMoneyInfo>();

            ptr->sendMessageInter(msg_ptr);
        }
        msg_ptr->m_blast = true;
        ptr->sendMessageInter(msg_ptr);
    }

    void AsyncQryService::qryUsingFunderAcc(const ReplyFundAccQryMsgPtr& msg_ptr)
    {
        std::vector<SAccountPtr> vec = AllTrade::NPMgrCenter::IManagerCenter::instance()->getAllFunderAccByLoginName(msg_ptr->getLoginName().c_str());
        msg_ptr->setResult(Err_Succeed);
        TCPImpl* ptr = msg_ptr->getTCPImpl();
        for (auto item : vec)
        {
            if (item->status_ != E_ACCOUNT_STATUS::EAS_Using)
                continue;
            msg_ptr->m_rtn_acc = std::dynamic_pointer_cast<FunderAccount>(item);
            SAccountPtr parent_ptr = AllTrade::NPMgrCenter::IManagerCenter::instance()->getAccountByID(msg_ptr->m_rtn_acc->parent_id_);
            strncpy_s(msg_ptr->m_rtn_parent_login_name, parent_ptr->login_name_, sizeof(msg_ptr->m_rtn_parent_login_name) - 1);

            msg_ptr->m_rtn_money = AllTrade::NPMgrCenter::IManagerCenter::instance()->getMoneyInfoByLoginName(item->login_name_);
            if (!msg_ptr->m_rtn_money)
                msg_ptr->m_rtn_money = std::make_shared<SMoneyInfo>();

            ptr->sendMessageInter(msg_ptr);
        }
        msg_ptr->m_blast = true;
        ptr->sendMessageInter(msg_ptr);
    }

    void AsyncQryService::addFunderAcc(const ReplyFundAccAddMsgPtr& msg_ptr)
    {
        TCPImpl* ptr = msg_ptr->getTCPImpl();
        SAccountPtr olditem_ptr = AllTrade::NPMgrCenter::IManagerCenter::instance()->getAccountByLoginName(msg_ptr->m_rtn_acc->login_name_);
        if (olditem_ptr)
        {
            ptr->sendMessageInter(ReplyMsg::getReply(Error_User_Exist, msg_ptr->getSocketID(), msg_ptr->getCmdCode()));
            return;
        }

        SAccountPtr parent_ptr = AllTrade::NPMgrCenter::IManagerCenter::instance()->getRootAccount();
        if (!parent_ptr)
        {
            ptr->sendMessageInter(ReplyMsg::getReply(Error_User_Parent_Unexist, msg_ptr->getSocketID(), msg_ptr->getCmdCode()));
            return;
        }
        SAccountPtr create_ptr = AllTrade::NPMgrCenter::IManagerCenter::instance()->getAccountByLoginName(msg_ptr->getLoginName().c_str());
        if (!create_ptr)
        {
            ptr->sendMessageInter(ReplyMsg::getReply(Error_User_Creator_Unexist, msg_ptr->getSocketID(), msg_ptr->getCmdCode()));
            return;
        }
        FunderAccountPtr item_ptr = msg_ptr->m_rtn_acc;
        strncpy_s(item_ptr->user_id_, UtilityFun::createGUID().c_str(), sizeof(item_ptr->user_id_) - 1);
        strncpy_s(item_ptr->create_id_, create_ptr->user_id_, sizeof(item_ptr->create_id_) - 1);
        strncpy_s(item_ptr->parent_id_, parent_ptr->user_id_, sizeof(item_ptr->parent_id_) - 1);

        ErrorCodeType errcode = AllTrade::NPMgrCenter::IManagerCenter::instance()->addAccount(item_ptr, msg_ptr->m_rtn_money, msg_ptr->m_rtn_risk);
        msg_ptr->setResult(errcode);

        ptr->sendMessageInter(msg_ptr);
        if (errcode == Err_Succeed)
            ptr->sendMessageToAllInter(parent_ptr->user_id_, parent_ptr->login_name_, msg_ptr);
    }

    void AsyncQryService::changeFunderAcc(const ReplyFundAccChangeMsgPtr& msg_ptr)
    {
        TCPImpl* ptr = msg_ptr->getTCPImpl();
        SAccountPtr olditem_ptr = AllTrade::NPMgrCenter::IManagerCenter::instance()->getAccountByLoginName(msg_ptr->m_rtn_acc->login_name_);
        if (!olditem_ptr)
        {
            ptr->sendMessageInter(ReplyMsg::getReply(Error_User_Unexist, msg_ptr->getSocketID(), msg_ptr->getCmdCode()));
            return;
        }
        SAccountPtr parent_ptr = AllTrade::NPMgrCenter::IManagerCenter::instance()->getAccountByLoginName(msg_ptr->getLoginName().c_str());
        if (!parent_ptr)
        {
            ptr->sendMessageInter(ReplyMsg::getReply(Error_User_Parent_Unexist, msg_ptr->getSocketID(), msg_ptr->getCmdCode()));
            return;
        }

        SAccountPtr create_ptr = AllTrade::NPMgrCenter::IManagerCenter::instance()->getAccountByLoginName(msg_ptr->getLoginName().c_str());
        if (!create_ptr)
        {
            ptr->sendMessageInter(ReplyMsg::getReply(Error_User_Creator_Unexist, msg_ptr->getSocketID(), msg_ptr->getCmdCode()));
            return;
        }

        FunderAccountPtr item_ptr = std::dynamic_pointer_cast<FunderAccount>(olditem_ptr);
        strncpy_s(item_ptr->account_name_, msg_ptr->m_rtn_acc->account_name_, sizeof(item_ptr->account_name_) - 1);
        strncpy_s(item_ptr->password_, msg_ptr->m_rtn_acc->password_, sizeof(item_ptr->password_) - 1);
        strncpy_s(item_ptr->agent_link_, msg_ptr->m_rtn_acc->agent_link_, sizeof(item_ptr->agent_link_) - 1);
//         item_ptr->status_ = msg_ptr->m_rtn_acc->status_;
        item_ptr->type_ = msg_ptr->m_rtn_acc->type_;
        strncpy_s(item_ptr->identity_, msg_ptr->m_rtn_acc->identity_, sizeof(item_ptr->identity_) - 1);
        strncpy_s(item_ptr->real_name_, msg_ptr->m_rtn_acc->real_name_, sizeof(item_ptr->real_name_) - 1);
        strncpy_s(item_ptr->phone_number_, msg_ptr->m_rtn_acc->phone_number_, sizeof(item_ptr->phone_number_) - 1);

        ErrorCodeType errcode = AllTrade::NPMgrCenter::IManagerCenter::instance()->updateAccount(item_ptr);
//         if (errcode == Err_Succeed)
//             errcode = AllTrade::NPMgrCenter::IManagerCenter::instance()->updateRisk(item_ptr->user_id_, msg_ptr->m_rtn_risk);
        msg_ptr->setResult(errcode);

        ptr->sendMessageInter(msg_ptr);
        if (errcode == Err_Succeed)
            ptr->sendMessageToAllInter(parent_ptr->user_id_, parent_ptr->login_name_, msg_ptr);
    }

    void AsyncQryService::changePassword(const ReplyPswChangeMsgPtr& msg_ptr)
    {
        TCPImpl* ptr = msg_ptr->getTCPImpl();
        SAccountPtr item_ptr = AllTrade::NPMgrCenter::IManagerCenter::instance()->getAccountByLoginName(msg_ptr->m_LoginName);
        if (!item_ptr)
        {
            ptr->sendMessageInter(ReplyMsg::getReply(Error_User_Unexist, msg_ptr->getSocketID(), msg_ptr->getCmdCode()));
            return;
        }

        ErrorCodeType errcode = AllTrade::NPMgrCenter::IManagerCenter::instance()->changePassword(item_ptr->user_id_, msg_ptr->m_old_pass, msg_ptr->m_new_pass);
        msg_ptr->setResult(errcode);
        ptr->sendMessageInter(msg_ptr);
    }

    void AsyncQryService::outInMoney(const ReplyChildAccInmoneyMsgPtr& msg_ptr)
    {
        TCPImpl* ptr = msg_ptr->getTCPImpl();
        SAccountPtr olditem_ptr = AllTrade::NPMgrCenter::IManagerCenter::instance()->getAccountByLoginName(msg_ptr->m_login_name);
        if (!olditem_ptr)
        {
            ptr->sendMessageInter(ReplyMsg::getReply(Error_User_Unexist, msg_ptr->getSocketID(), msg_ptr->getCmdCode()));
            return;
        }
        SAccountPtr opitem_ptr = AllTrade::NPMgrCenter::IManagerCenter::instance()->getAccountByLoginName(msg_ptr->getLoginName().c_str());
        if (!opitem_ptr)
        {
            ptr->sendMessageInter(ReplyMsg::getReply(Error_User_Unexist, msg_ptr->getSocketID(), msg_ptr->getCmdCode()));
            return;
        }

        ErrorCodeType errcode = AllTrade::NPMgrCenter::IManagerCenter::instance()->moneyChange(olditem_ptr->user_id_, msg_ptr->m_money_change, msg_ptr->m_money, msg_ptr->m_remark);
        LOG4CXX_WARN(logger, "后台操作出入金,操作者"LOG_NOVAR(opitem_ptr->user_id_)
            "IP"LOG_NOVAR(ptr->getAddrBySocketID(msg_ptr->getSocketID()))
            "对象"LOG_NOVAR(olditem_ptr->user_id_)
            "金额"LOG_NOVAR(msg_ptr->m_money)"备注"LOG_NOVAR(msg_ptr->m_remark)
            "结果"LOG_NOVAR(errcode));

        if (errcode == Err_Succeed)
            AllTrade::NPTradeCenter::ITradeCenter::instance()->recalculate_risk(CommodityTypeType::COMMODITY_TYPE_STOCK, olditem_ptr->user_id_);

        msg_ptr->setResult(errcode);
        ptr->sendMessageInter(msg_ptr);
    }

    void AsyncQryService::applyEquipMoney(const ReplyApplyEquipMoneyMsgPtr& msg_ptr)
    {
        TCPImpl* ptr = msg_ptr->getTCPImpl();
        SAccountPtr olditem_ptr = AllTrade::NPMgrCenter::IManagerCenter::instance()->getAccountByLoginName(msg_ptr->getLoginName().c_str());
        if (!olditem_ptr)
        {
            ptr->sendMessageInter(ReplyMsg::getReply(Error_User_Unexist, msg_ptr->getSocketID(), msg_ptr->getCmdCode()));
            return;
        }

        ErrorCodeType errcode = AllTrade::NPMgrCenter::IManagerCenter::instance()->applyMoney(olditem_ptr->user_id_, msg_ptr->m_appmoney, OIMM_Change_Type::OIMM_In_Equipment);
        msg_ptr->setResult(errcode);
        ptr->sendMessageInter(msg_ptr);
    }

    void AsyncQryService::applyAutoInMoney(const ReplyAutoInMoneyMsgPtr& msg_ptr)
    {
        TCPImpl* ptr = msg_ptr->getTCPImpl();
        SAccountPtr olditem_ptr = AllTrade::NPMgrCenter::IManagerCenter::instance()->getAccountByLoginName(msg_ptr->m_login_name);
        if (!olditem_ptr)
        {
            ptr->sendMessageInter(ReplyMsg::getReply(Error_User_Unexist, msg_ptr->getSocketID(), msg_ptr->getCmdCode()));
            return;
        }

        ErrorCodeType errcode = AllTrade::NPMgrCenter::IManagerCenter::instance()->applyMoney(olditem_ptr->user_id_, msg_ptr->m_appmoney, OIMM_Change_Type::OIMM_In_Deposit);

        msg_ptr->setResult(errcode);
        ptr->sendMessageInter(msg_ptr);
    }

    void AsyncQryService::applyAutoOutMoney(const ReplyAutoOutMoneyMsgPtr& msg_ptr)
    {
        TCPImpl* ptr = msg_ptr->getTCPImpl();
        SAccountPtr olditem_ptr = AllTrade::NPMgrCenter::IManagerCenter::instance()->getAccountByLoginName(msg_ptr->getLoginName().c_str());
        if (!olditem_ptr)
        {
            ptr->sendMessageInter(ReplyMsg::getReply(Error_User_Unexist, msg_ptr->getSocketID(), msg_ptr->getCmdCode()));
            return;
        }

        auto money_ptr = AllTrade::NPMgrCenter::IManagerCenter::instance()->getMoneyInfoByLoginName(olditem_ptr->login_name_);
        SApplyMoneyPtr moneyptr = std::make_shared<SApplyMoneyInfo>();
        strncpy_s(moneyptr->real_name_, msg_ptr->m_real_name, sizeof(moneyptr->real_name_) - 1);
        strncpy_s(moneyptr->bank_card_, msg_ptr->m_bank_card, sizeof(moneyptr->bank_card_) - 1);
        strncpy_s(moneyptr->bank_name_, msg_ptr->m_bank_name, sizeof(moneyptr->bank_name_) - 1);
        ErrorCodeType errcode = AllTrade::NPMgrCenter::IManagerCenter::instance()->applyMoney(olditem_ptr->user_id_, msg_ptr->m_appmoney, OIMM_Change_Type::OIMM_Out_Deposit, moneyptr);
        
        msg_ptr->setResult(errcode);
        ptr->sendMessageInter(msg_ptr);
    }

    void AsyncQryService::approvalApplyEquipMoney(const ReplyApprovalApplyEquipMoneyMsgPtr& msg_ptr)
    {
        TCPImpl* ptr = msg_ptr->getTCPImpl();
        SAccountPtr approval_item_ptr = AllTrade::NPMgrCenter::IManagerCenter::instance()->getAccountByLoginName(msg_ptr->getLoginName().c_str());
        if (!approval_item_ptr)
        {
            ptr->sendMessageInter(ReplyMsg::getReply(Error_User_Unexist, msg_ptr->getSocketID(), msg_ptr->getCmdCode()));
            return;
        }

        auto applymoney_ptr = AllTrade::NPMgrCenter::IManagerCenter::instance()->getApplyMoneyPtr(msg_ptr->m_apply_money_id, OIMM_Change_Type::OIMM_In_Equipment);
        if (applymoney_ptr->apply_money_id_ == 0)
        {
            ptr->sendMessageInter(ReplyMsg::getReply(Error_ApplyMoney_Unexist, msg_ptr->getSocketID(), msg_ptr->getCmdCode()));
            return;
        }

        ErrorCodeType errcode = AllTrade::NPMgrCenter::IManagerCenter::instance()->approvalApplyMoney(approval_item_ptr->user_id_, applymoney_ptr->user_id_, msg_ptr->m_apply_money_id, msg_ptr->m_apply_status, OIMM_Change_Type::OIMM_In_Equipment);
        if (errcode == Err_Succeed)
            AllTrade::NPTradeCenter::ITradeCenter::instance()->recalculate_risk(CommodityTypeType::COMMODITY_TYPE_STOCK, applymoney_ptr->user_id_);
        
        msg_ptr->setResult(errcode);
        ptr->sendMessageInter(msg_ptr);
    }

    void AsyncQryService::approvalApplyAutoInMoney(const ReplyAutoInMoneyApprovalMsgPtr& msg_ptr)
    {
        TCPImpl* ptr = msg_ptr->getTCPImpl();
        SAccountPtr approval_item_ptr = AllTrade::NPMgrCenter::IManagerCenter::instance()->getAccountByLoginName(msg_ptr->getLoginName().c_str());
        if (!approval_item_ptr)
        {
            ptr->sendMessageInter(ReplyMsg::getReply(Error_User_Unexist, msg_ptr->getSocketID(), msg_ptr->getCmdCode()));
            return;
        }

        auto applymoney_ptr = AllTrade::NPMgrCenter::IManagerCenter::instance()->getApplyMoneyPtr(msg_ptr->m_apply_money_id, OIMM_Change_Type::OIMM_In_Deposit);
        if (applymoney_ptr->apply_money_id_ == 0)
        {
            ptr->sendMessageInter(ReplyMsg::getReply(Error_ApplyMoney_Unexist, msg_ptr->getSocketID(), msg_ptr->getCmdCode()));
            return;
        }

        ErrorCodeType errcode = AllTrade::NPMgrCenter::IManagerCenter::instance()->approvalApplyMoney(approval_item_ptr->user_id_, applymoney_ptr->user_id_, msg_ptr->m_apply_money_id, msg_ptr->m_apply_status, OIMM_Change_Type::OIMM_In_Deposit);
        if (errcode == Err_Succeed)
            AllTrade::NPTradeCenter::ITradeCenter::instance()->recalculate_risk(CommodityTypeType::COMMODITY_TYPE_STOCK, applymoney_ptr->user_id_);
        
        msg_ptr->setResult(errcode);
        ptr->sendMessageInter(msg_ptr);
    }

    void AsyncQryService::approvalApplyAutoOutMoney(const ReplyAutoOutMoneyApprovalMsgPtr& msg_ptr)
    {
        TCPImpl* ptr = msg_ptr->getTCPImpl();
        SAccountPtr approval_item_ptr = AllTrade::NPMgrCenter::IManagerCenter::instance()->getAccountByLoginName(msg_ptr->getLoginName().c_str());
        if (!approval_item_ptr)
        {
            ptr->sendMessageInter(ReplyMsg::getReply(Error_User_Unexist, msg_ptr->getSocketID(), msg_ptr->getCmdCode()));
            return;
        }

        auto applymoney_ptr = AllTrade::NPMgrCenter::IManagerCenter::instance()->getApplyMoneyPtr(msg_ptr->m_apply_money_id, OIMM_Change_Type::OIMM_Out_Deposit);
        if (applymoney_ptr->apply_money_id_ == 0)
        {
            ptr->sendMessageInter(ReplyMsg::getReply(Error_ApplyMoney_Unexist, msg_ptr->getSocketID(), msg_ptr->getCmdCode()));
            return;
        }

        ErrorCodeType errcode = AllTrade::NPMgrCenter::IManagerCenter::instance()->approvalApplyMoney(approval_item_ptr->user_id_, applymoney_ptr->user_id_, msg_ptr->m_apply_money_id, msg_ptr->m_apply_status, OIMM_Change_Type::OIMM_Out_Deposit);
        if (errcode == Err_Succeed)
            AllTrade::NPTradeCenter::ITradeCenter::instance()->recalculate_risk(CommodityTypeType::COMMODITY_TYPE_STOCK, applymoney_ptr->user_id_);
        
        msg_ptr->setResult(errcode);
        ptr->sendMessageInter(msg_ptr);
    }

    void AsyncQryService::qryEquipMoneyInfos(const ReplyEquipmentMoneyQryMsgPtr& msg_ptr)
    {
        TCPImpl* ptr = msg_ptr->getTCPImpl();
        msg_ptr->m_rtn_acc = std::dynamic_pointer_cast<TradeAccount>(AllTrade::NPMgrCenter::IManagerCenter::instance()->getAccountByLoginName(msg_ptr->m_rtn_acc->login_name_));
        if (!msg_ptr->m_rtn_acc)
        {
            ptr->sendMessageInter(ReplyMsg::getReply(Error_User_Unexist, msg_ptr->getSocketID(), msg_ptr->getCmdCode()));
            return;
        }
        
        std::vector<AllTrade::NPMgrCenter::SApplyMoneyPtr> vec = AllTrade::NPMgrCenter::IManagerCenter::instance()->getApplyMoney(msg_ptr->m_rtn_acc->user_id_, msg_ptr->m_start_day, msg_ptr->m_end_day, OIMM_Change_Type::OIMM_In_Equipment);
        msg_ptr->setResult(Err_Succeed);
        for (auto item : vec)
        {
            msg_ptr->m_money = item;
            ptr->sendMessageInter(msg_ptr);
        }
        msg_ptr->m_blast = true;
        ptr->sendMessageInter(msg_ptr);
    }

    void AsyncQryService::qryAutoInMoneyInfos(const ReplyAutoInMoneyQryMsgPtr& msg_ptr)
    {
        TCPImpl* ptr = msg_ptr->getTCPImpl();
        msg_ptr->m_rtn_acc = std::dynamic_pointer_cast<TradeAccount>(AllTrade::NPMgrCenter::IManagerCenter::instance()->getAccountByLoginName(msg_ptr->m_rtn_acc->login_name_));
        if (!msg_ptr->m_rtn_acc)
        {
            ptr->sendMessageInter(ReplyMsg::getReply(Error_User_Unexist, msg_ptr->getSocketID(), msg_ptr->getCmdCode()));
            return;
        }

        std::vector<AllTrade::NPMgrCenter::SApplyMoneyPtr> vec = AllTrade::NPMgrCenter::IManagerCenter::instance()->getApplyMoney(msg_ptr->m_rtn_acc->user_id_, msg_ptr->m_start_day, msg_ptr->m_end_day, OIMM_Change_Type::OIMM_In_Deposit);
        msg_ptr->setResult(Err_Succeed);
        for (auto item : vec)
        {
            msg_ptr->m_money = item;
            ptr->sendMessageInter(msg_ptr);
        }
        msg_ptr->m_blast = true;
        ptr->sendMessageInter(msg_ptr);
    }

    void AsyncQryService::qryAutoOutMoneyInfos(const ReplyAutoOutMoneyQryMsgPtr& msg_ptr)
    {
        TCPImpl* ptr = msg_ptr->getTCPImpl();
        msg_ptr->m_rtn_acc = std::dynamic_pointer_cast<TradeAccount>(AllTrade::NPMgrCenter::IManagerCenter::instance()->getAccountByLoginName(msg_ptr->m_rtn_acc->login_name_));
        if (!msg_ptr->m_rtn_acc)
        {
            ptr->sendMessageInter(ReplyMsg::getReply(Error_User_Unexist, msg_ptr->getSocketID(), msg_ptr->getCmdCode()));
            return;
        }

        std::vector<AllTrade::NPMgrCenter::SApplyMoneyPtr> vec = AllTrade::NPMgrCenter::IManagerCenter::instance()->getApplyMoney(msg_ptr->m_rtn_acc->user_id_, msg_ptr->m_start_day, msg_ptr->m_end_day, OIMM_Change_Type::OIMM_Out_Deposit);
        msg_ptr->setResult(Err_Succeed);
        for (auto item : vec)
        {
            msg_ptr->m_money = item;
            ptr->sendMessageInter(msg_ptr);
        }
        msg_ptr->m_blast = true;
        ptr->sendMessageInter(msg_ptr);
    }

    void AsyncQryService::handlePlaceOrder(const ReplyOpenCloseMsgPtr& msg_ptr, const NPMgrCenter::SOnlineAccountPtr& user_online)
    {
        TCPImpl* ptr = msg_ptr->getTCPImpl();
        SAccountPtr item_ptr = AllTrade::NPMgrCenter::IManagerCenter::instance()->getAccountByLoginName(msg_ptr->m_orderLoginName);
        if (!item_ptr)
        {
            ptr->sendMessageInter(ReplyMsg::getReply(Error_User_Unexist, msg_ptr->getSocketID(), msg_ptr->getCmdCode()));
            return;
        }
        SContractPtr stock_contract_ptr = AllTrade::NPMgrCenter::IManagerCenter::instance()->getStockContractByCode(msg_ptr->m_order_ptr->stock_area_, msg_ptr->m_contract_code);
        if (!stock_contract_ptr)
        {
            ptr->sendMessageInter(ReplyMsg::getReply(Err_Trade_UnknownContract, msg_ptr->getSocketID(), msg_ptr->getCmdCode()));
            return;
        }
        strncpy_s(msg_ptr->m_order_ptr->contract_id_, stock_contract_ptr->contract_id_, sizeof(msg_ptr->m_order_ptr->contract_id_) - 1);
        strncpy_s(msg_ptr->m_order_ptr->exchange_id_, stock_contract_ptr->exchange_id_, sizeof(msg_ptr->m_order_ptr->exchange_id_) - 1);
        strncpy_s(msg_ptr->m_order_ptr->currency_id_, stock_contract_ptr->currency_id_, sizeof(msg_ptr->m_order_ptr->currency_id_) - 1);
        msg_ptr->m_order_ptr->currency_rate_ = 1;
        if (item_ptr->type_ == E_ACCOUNT_TYPE::EAT_Simulation)
            msg_ptr->m_order_ptr->order_trade_mode_ =  OrderTradeModeType::ORDERTRADE_MODE_SIMULATE;
        else if (item_ptr->type_ == E_ACCOUNT_TYPE::EAT_Real)
            msg_ptr->m_order_ptr->order_trade_mode_ = OrderTradeModeType::ORDERTRADE_MODE_SYNC;
        else
        { 
            assert(0);
            msg_ptr->m_order_ptr->order_trade_mode_ = OrderTradeModeType::ORDERTRADE_MODE_Invalid;
        }

        std::string new_order_stream = item_ptr->user_id_;
        new_order_stream += "&" + UtilityFun::createGUID();
        strncpy_s(msg_ptr->m_order_ptr->order_stream_, new_order_stream.c_str(), sizeof(msg_ptr->m_order_ptr->order_stream_) - 1);
        msg_ptr->m_order_ptr->order_state_ = OrderStateType::ORDER_STATE_SUPPENDED;
        msg_ptr->m_order_ptr->orser_state_explain_ = OSET_Err_No;
        strncpy_s(msg_ptr->m_order_ptr->generate_datetime_, UtilityFun::getCurrentDateTime().c_str(), sizeof(msg_ptr->m_order_ptr->generate_datetime_) - 1);

        AllTrade::NPTradeCenter::ITradeCenter::instance()->handlePlaceOrder(msg_ptr->m_order_ptr, item_ptr->user_id_, user_online);
    }

    void AsyncQryService::handleCancelOrder(const ReplyCancelOrderMsgPtr& msg_ptr)
    {
        TCPImpl* ptr = msg_ptr->getTCPImpl();
        SAccountPtr item_ptr = AllTrade::NPMgrCenter::IManagerCenter::instance()->getAccountByLoginName(msg_ptr->m_orderLoginName);
        if (!item_ptr)
        {
            ptr->sendMessageInter(ReplyMsg::getReply(Error_User_Unexist, msg_ptr->getSocketID(), msg_ptr->getCmdCode()));
            return;
        }
        
        if (!AllTrade::NPTradeCenter::ITradeCenter::instance()->canCancelOrder(item_ptr->user_id_, msg_ptr->m_orderstream))
        {
            ptr->sendMessageInter(ReplyMsg::getReply(Err_CancelOrder_Param_Error, msg_ptr->getSocketID(), msg_ptr->getCmdCode()));
            return;
        }
        AllTrade::NPTradeCenter::ITradeCenter::instance()->handleCancelOrder(CommodityTypeType::COMMODITY_TYPE_STOCK, item_ptr->user_id_, msg_ptr->m_orderstream);
    }

    void AsyncQryService::qryStockContract(const ReplyStockContractQryMsgPtr& msg_ptr)
    {
        TCPImpl* ptr = msg_ptr->getTCPImpl();

        SExchangePtr ex_ptr = AllTrade::NPMgrCenter::IManagerCenter::instance()->getExchangeByCode(CommodityTypeType::COMMODITY_TYPE_STOCK, msg_ptr->m_exchange_code);
        if (!ex_ptr)
        {
            ptr->sendMessageInter(ReplyMsg::getReply(Error_Exchange_Unexist, msg_ptr->getSocketID(), msg_ptr->getCmdCode()));
            return;
        }

        std::vector<AllTrade::NPMgrCenter::SContractPtr> vec = AllTrade::NPMgrCenter::IManagerCenter::instance()->getContracts(ex_ptr);
        msg_ptr->setResult(Err_Succeed);
        for (auto& item : vec)
        {
            msg_ptr->m_stock_ptr = std::dynamic_pointer_cast<SStockContract>(item);
            ptr->sendMessageInter(msg_ptr);
        }
        msg_ptr->m_blast = true;
        ptr->sendMessageInter(msg_ptr);
    }

    void AsyncQryService::qryAccountFund(const ReplyFundQryMsgPtr& msg_ptr)
    {
        TCPImpl* ptr = msg_ptr->getTCPImpl();
        TradeAccountPtr item_ptr = std::dynamic_pointer_cast<TradeAccount>(AllTrade::NPMgrCenter::IManagerCenter::instance()->getAccountByLoginName(msg_ptr->m_rtn_acc->login_name_));
        if (!item_ptr)
        {
            ptr->sendMessageInter(ReplyMsg::getReply(Error_User_Unexist, msg_ptr->getSocketID(), msg_ptr->getCmdCode()));
            return;
        }
        msg_ptr->m_rtn_acc = item_ptr;
        SAccountPtr parent_ptr = AllTrade::NPMgrCenter::IManagerCenter::instance()->getAccountByID(msg_ptr->m_rtn_acc->parent_id_);
        if (!parent_ptr)
        {
            ptr->sendMessageInter(ReplyMsg::getReply(Error_User_Parent_Unexist, msg_ptr->getSocketID(), msg_ptr->getCmdCode()));
            return;
        }
        strncpy_s(msg_ptr->m_parent_login_name, parent_ptr->login_name_, sizeof(msg_ptr->m_parent_login_name) - 1);

        msg_ptr->m_rtn_money = AllTrade::NPMgrCenter::IManagerCenter::instance()->getMoneyInfoByLoginName(msg_ptr->m_rtn_acc->login_name_);
        msg_ptr->m_rtn_risk = AllTrade::NPMgrCenter::IManagerCenter::instance()->getRiskInfoByLoginName(msg_ptr->m_rtn_acc->login_name_);
        msg_ptr->setResult(Err_Succeed);
        ptr->sendMessageInter(msg_ptr);
    }

    void AsyncQryService::qryHistoryFundSerial(const ReplyFundSerialQryMsgPtr& msg_ptr)
    {
        TCPImpl* ptr = msg_ptr->getTCPImpl();
        TradeAccountPtr item_ptr = std::dynamic_pointer_cast<TradeAccount>(AllTrade::NPMgrCenter::IManagerCenter::instance()->getAccountByLoginName(msg_ptr->m_rtn_acc->login_name_));
        if (!item_ptr)
        {
            ptr->sendMessageInter(ReplyMsg::getReply(Error_User_Unexist, msg_ptr->getSocketID(), msg_ptr->getCmdCode()));
            return;
        }
        msg_ptr->m_rtn_acc = item_ptr;
        SAccountPtr parent_ptr = AllTrade::NPMgrCenter::IManagerCenter::instance()->getAccountByID(msg_ptr->m_rtn_acc->parent_id_);
        if (!parent_ptr)
        {
            ptr->sendMessageInter(ReplyMsg::getReply(Error_User_Parent_Unexist, msg_ptr->getSocketID(), msg_ptr->getCmdCode()));
            return;
        }
        strncpy_s(msg_ptr->m_parent_login_name, parent_ptr->login_name_, sizeof(msg_ptr->m_parent_login_name) - 1);

        auto rslt = AllTrade::NPMgrCenter::IManagerCenter::instance()->getFundSerial(item_ptr->user_id_, msg_ptr->m_qry_start_time, msg_ptr->m_qry_end_time);

        for (auto& item : rslt)
        {
            msg_ptr->m_rtn_money = std::dynamic_pointer_cast<SMoneyDetailInfo>(item);
            msg_ptr->setResult(Err_Succeed);
            ptr->sendMessageInter(msg_ptr);
        }
        msg_ptr->m_blast = true;
        ptr->sendMessageInter(msg_ptr);
    }

    void AsyncQryService::qryPosition(const ReplyPosiQryMsgPtr& msg_ptr)
    {
        TCPImpl* ptr = msg_ptr->getTCPImpl();
        TradeAccountPtr item_ptr = std::dynamic_pointer_cast<TradeAccount>(AllTrade::NPMgrCenter::IManagerCenter::instance()->getAccountByLoginName(msg_ptr->m_rtn_acc->login_name_));
        if (!item_ptr)
        {
            ptr->sendMessageInter(ReplyMsg::getReply(Error_User_Unexist, msg_ptr->getSocketID(), msg_ptr->getCmdCode()));
            return;
        }
        msg_ptr->m_rtn_acc = item_ptr;
        SAccountPtr parent_ptr = AllTrade::NPMgrCenter::IManagerCenter::instance()->getAccountByID(msg_ptr->m_rtn_acc->parent_id_);
        if (!parent_ptr)
        {
            ptr->sendMessageInter(ReplyMsg::getReply(Error_User_Parent_Unexist, msg_ptr->getSocketID(), msg_ptr->getCmdCode()));
            return;
        }
        strncpy_s(msg_ptr->m_parent_login_name, parent_ptr->login_name_, sizeof(msg_ptr->m_parent_login_name) - 1);

        std::vector<PositionInfoPtr> pos_vec = AllTrade::NPTradeCenter::ITradeCenter::instance()->getPositionList(item_ptr->user_id_);
        for (auto& item : pos_vec)
        {
            msg_ptr->m_position_ptr = std::dynamic_pointer_cast<StockPositionInfo>(item);
            if (msg_ptr->m_position_ptr)
                msg_ptr->m_stock_ptr = AllTrade::NPMgrCenter::IManagerCenter::instance()->getStockContractByID(msg_ptr->m_position_ptr->stock_area_, msg_ptr->m_position_ptr->contract_id_);
            msg_ptr->setResult(Err_Succeed);
            ptr->sendMessageInter(msg_ptr);
        }
        msg_ptr->m_blast = true;
        ptr->sendMessageInter(msg_ptr);
    }

    void AsyncQryService::qryCurrentyEntrust(const ReplyCurrentyEntrustQryMsgPtr& msg_ptr)
    {
        TCPImpl* ptr = msg_ptr->getTCPImpl();
        TradeAccountPtr item_ptr = std::dynamic_pointer_cast<TradeAccount>(AllTrade::NPMgrCenter::IManagerCenter::instance()->getAccountByLoginName(msg_ptr->m_rtn_acc->login_name_));
        if (!item_ptr)
        {
            ptr->sendMessageInter(ReplyMsg::getReply(Error_User_Unexist, msg_ptr->getSocketID(), msg_ptr->getCmdCode()));
            return;
        }
        msg_ptr->m_rtn_acc = item_ptr;
        SAccountPtr parent_ptr = AllTrade::NPMgrCenter::IManagerCenter::instance()->getAccountByID(msg_ptr->m_rtn_acc->parent_id_);
        if (!parent_ptr)
        {
            ptr->sendMessageInter(ReplyMsg::getReply(Error_User_Parent_Unexist, msg_ptr->getSocketID(), msg_ptr->getCmdCode()));
            return;
        }
        strncpy_s(msg_ptr->m_parent_login_name, parent_ptr->login_name_, sizeof(msg_ptr->m_parent_login_name) - 1);

        std::vector<OrderInfoPtr> pos_vec = AllTrade::NPTradeCenter::ITradeCenter::instance()->getCurrentOrderList(item_ptr->user_id_);
        for (auto& item : pos_vec)
        {
            msg_ptr->m_order_ptr = std::dynamic_pointer_cast<StockOrderInfo>(item);
            if (msg_ptr->m_order_ptr)
                msg_ptr->m_stock_ptr = AllTrade::NPMgrCenter::IManagerCenter::instance()->getStockContractByID(msg_ptr->m_order_ptr->stock_area_, msg_ptr->m_order_ptr->contract_id_);
            msg_ptr->setResult(Err_Succeed);
            ptr->sendMessageInter(msg_ptr);
        }
        msg_ptr->m_blast = true;
        ptr->sendMessageInter(msg_ptr);
    }

    void AsyncQryService::qryTodayEntrust(const ReplyTodayEntrustQryMsgPtr& msg_ptr)
    {
        TCPImpl* ptr = msg_ptr->getTCPImpl();
        TradeAccountPtr item_ptr = std::dynamic_pointer_cast<TradeAccount>(AllTrade::NPMgrCenter::IManagerCenter::instance()->getAccountByLoginName(msg_ptr->m_rtn_acc->login_name_));
        if (!item_ptr)
        {
            ptr->sendMessageInter(ReplyMsg::getReply(Error_User_Unexist, msg_ptr->getSocketID(), msg_ptr->getCmdCode()));
            return;
        }
        msg_ptr->m_rtn_acc = item_ptr;
        SAccountPtr parent_ptr = AllTrade::NPMgrCenter::IManagerCenter::instance()->getAccountByID(msg_ptr->m_rtn_acc->parent_id_);
        if (!parent_ptr)
        {
            ptr->sendMessageInter(ReplyMsg::getReply(Error_User_Parent_Unexist, msg_ptr->getSocketID(), msg_ptr->getCmdCode()));
            return;
        }
        strncpy_s(msg_ptr->m_parent_login_name, parent_ptr->login_name_, sizeof(msg_ptr->m_parent_login_name) - 1);

        std::vector<OrderInfoPtr> pos_vec = AllTrade::NPTradeCenter::ITradeCenter::instance()->getTodayOrderList(item_ptr->user_id_);
        for (auto& item : pos_vec)
        {
            msg_ptr->m_order_ptr = std::dynamic_pointer_cast<StockOrderInfo>(item);
            if (msg_ptr->m_order_ptr)
                msg_ptr->m_stock_ptr = AllTrade::NPMgrCenter::IManagerCenter::instance()->getStockContractByID(msg_ptr->m_order_ptr->stock_area_, msg_ptr->m_order_ptr->contract_id_);
            msg_ptr->setResult(Err_Succeed);
            ptr->sendMessageInter(msg_ptr);
        }
        msg_ptr->m_blast = true;
        ptr->sendMessageInter(msg_ptr);
    }

    void AsyncQryService::qryHistoryEntrust(const ReplyHistoryEntrustQryMsgPtr& msg_ptr)
    {
        TCPImpl* ptr = msg_ptr->getTCPImpl();
        TradeAccountPtr item_ptr = std::dynamic_pointer_cast<TradeAccount>(AllTrade::NPMgrCenter::IManagerCenter::instance()->getAccountByLoginName(msg_ptr->m_rtn_acc->login_name_));
        if (!item_ptr)
        {
            ptr->sendMessageInter(ReplyMsg::getReply(Error_User_Unexist, msg_ptr->getSocketID(), msg_ptr->getCmdCode()));
            return;
        }
        msg_ptr->m_rtn_acc = item_ptr;
        SAccountPtr parent_ptr = AllTrade::NPMgrCenter::IManagerCenter::instance()->getAccountByID(msg_ptr->m_rtn_acc->parent_id_);
        if (!parent_ptr)
        {
            ptr->sendMessageInter(ReplyMsg::getReply(Error_User_Parent_Unexist, msg_ptr->getSocketID(), msg_ptr->getCmdCode()));
            return;
        }
        strncpy_s(msg_ptr->m_parent_login_name, parent_ptr->login_name_, sizeof(msg_ptr->m_parent_login_name) - 1);

        std::vector<OrderInfoPtr> pos_vec = AllTrade::NPTradeCenter::ITradeCenter::instance()->getHistoryOrderList(item_ptr->user_id_, msg_ptr->m_qry_start_time, msg_ptr->m_qry_end_time);
        for (auto& item : pos_vec)
        {
            msg_ptr->m_order_ptr = std::dynamic_pointer_cast<StockOrderInfo>(item);
            if (msg_ptr->m_order_ptr)
                msg_ptr->m_stock_ptr = AllTrade::NPMgrCenter::IManagerCenter::instance()->getStockContractByID(msg_ptr->m_order_ptr->stock_area_, msg_ptr->m_order_ptr->contract_id_);
            msg_ptr->setResult(Err_Succeed);
            ptr->sendMessageInter(msg_ptr);
        }
        msg_ptr->m_blast = true;
        ptr->sendMessageInter(msg_ptr);
    }

    void AsyncQryService::qryTrade(const ReplyTradeQryMsgPtr& msg_ptr)
    {
        TCPImpl* ptr = msg_ptr->getTCPImpl();
        TradeAccountPtr item_ptr = std::dynamic_pointer_cast<TradeAccount>(AllTrade::NPMgrCenter::IManagerCenter::instance()->getAccountByLoginName(msg_ptr->m_rtn_acc->login_name_));
        if (!item_ptr)
        {
            ptr->sendMessageInter(ReplyMsg::getReply(Error_User_Unexist, msg_ptr->getSocketID(), msg_ptr->getCmdCode()));
            return;
        }
        msg_ptr->m_rtn_acc = item_ptr;

        SAccountPtr parent_ptr = AllTrade::NPMgrCenter::IManagerCenter::instance()->getAccountByID(msg_ptr->m_rtn_acc->parent_id_);
        if (!parent_ptr)
        {
            ptr->sendMessageInter(ReplyMsg::getReply(Error_User_Parent_Unexist, msg_ptr->getSocketID(), msg_ptr->getCmdCode()));
            return;
        }
        strncpy_s(msg_ptr->m_parent_login_name, parent_ptr->login_name_, sizeof(msg_ptr->m_parent_login_name) - 1);

        std::vector<TradeInfoPtr> pos_vec = AllTrade::NPTradeCenter::ITradeCenter::instance()->getTradeList(item_ptr->user_id_);
        for (auto& item : pos_vec)
        {
            msg_ptr->m_trade_ptr = std::dynamic_pointer_cast<StockTradeInfo>(item);
            if (msg_ptr->m_trade_ptr)
                msg_ptr->m_stock_ptr = AllTrade::NPMgrCenter::IManagerCenter::instance()->getStockContractByID(msg_ptr->m_trade_ptr->stock_area_, msg_ptr->m_trade_ptr->contract_id_);
            msg_ptr->setResult(Err_Succeed);
            ptr->sendMessageInter(msg_ptr);
        }
        msg_ptr->m_blast = true;
        ptr->sendMessageInter(msg_ptr);
    }

    void AsyncQryService::qryHistoryTrade(const ReplyHistoryTradeQryMsgPtr& msg_ptr)
    {
        TCPImpl* ptr = msg_ptr->getTCPImpl();
        TradeAccountPtr item_ptr = std::dynamic_pointer_cast<TradeAccount>(AllTrade::NPMgrCenter::IManagerCenter::instance()->getAccountByLoginName(msg_ptr->m_rtn_acc->login_name_));
        if (!item_ptr)
        {
            ptr->sendMessageInter(ReplyMsg::getReply(Error_User_Unexist, msg_ptr->getSocketID(), msg_ptr->getCmdCode()));
            return;
        }
        msg_ptr->m_rtn_acc = item_ptr;
        SAccountPtr parent_ptr = AllTrade::NPMgrCenter::IManagerCenter::instance()->getAccountByID(msg_ptr->m_rtn_acc->parent_id_);
        if (!parent_ptr)
        {
            ptr->sendMessageInter(ReplyMsg::getReply(Error_User_Parent_Unexist, msg_ptr->getSocketID(), msg_ptr->getCmdCode()));
            return;
        }
        strncpy_s(msg_ptr->m_parent_login_name, parent_ptr->login_name_, sizeof(msg_ptr->m_parent_login_name) - 1);

        std::vector<TradeInfoPtr> pos_vec = AllTrade::NPTradeCenter::ITradeCenter::instance()->getHistoryTradeList(item_ptr->user_id_, msg_ptr->m_qry_start_time, msg_ptr->m_qry_end_time);
        for (auto& item : pos_vec)
        {
            msg_ptr->m_trade_ptr = std::dynamic_pointer_cast<StockTradeInfo>(item);
            if (msg_ptr->m_trade_ptr)
                msg_ptr->m_stock_ptr = AllTrade::NPMgrCenter::IManagerCenter::instance()->getStockContractByID(msg_ptr->m_trade_ptr->stock_area_, msg_ptr->m_trade_ptr->contract_id_);
            msg_ptr->setResult(Err_Succeed);
            ptr->sendMessageInter(msg_ptr);
        }
        msg_ptr->m_blast = true;
        ptr->sendMessageInter(msg_ptr);
    }

    void AsyncQryService::qryStockBlackWhiteStatus(const ReplyStockBlackQryMsgPtr& msg_ptr)
    {
        TCPImpl* ptr = msg_ptr->getTCPImpl();
        auto black_map = AllTrade::NPMgrCenter::IManagerCenter::instance()->qryStockBlackWhiteStatus();
        msg_ptr->setResult(Err_Succeed);

        for (auto& item : black_map)
        {
            auto contract_ptr = AllTrade::NPMgrCenter::IManagerCenter::instance()->getStockContractByID(StockAreaType::STOCKAREA_TYPE_A, item.first.c_str());
            if (!contract_ptr)
                continue;

            strncpy_s(msg_ptr->m_contract_code, contract_ptr->contract_code_, sizeof(msg_ptr->m_contract_code) - 1);
            strncpy_s(msg_ptr->m_contract_name, contract_ptr->contract_name_, sizeof(msg_ptr->m_contract_name) - 1);
            msg_ptr->m_isBlack = item.second;
            ptr->sendMessageInter(msg_ptr);
        }
        msg_ptr->m_blast = true;
        ptr->sendMessageInter(msg_ptr);
    }

    void AsyncQryService::setStockBlackWhiteStatus(const ReplyStockBlackSetMsgPtr& msg_ptr)
    {
        TCPImpl* ptr = msg_ptr->getTCPImpl();
        auto contract_ptr = AllTrade::NPMgrCenter::IManagerCenter::instance()->getStockContractByCode(StockAreaType::STOCKAREA_TYPE_A, msg_ptr->m_contract_code);
        if (!contract_ptr)
        {
            ptr->sendMessageInter(ReplyMsg::getReply(Err_Contract_Qry, msg_ptr->getSocketID(), msg_ptr->getCmdCode()));
            return;
        }
        strncpy_s(msg_ptr->m_contract_name, contract_ptr->contract_name_, sizeof(msg_ptr->m_contract_name) - 1);
        ErrorCodeType errcode = AllTrade::NPMgrCenter::IManagerCenter::instance()->setStockBlackWhiteStatus(contract_ptr->contract_id_, msg_ptr->m_isBlack);
        msg_ptr->setResult(errcode);
        ptr->sendMessageInter(msg_ptr);
    }

    void AsyncQryService::qryForbidTradeStatus(const ReplyForbidBuySellQryMsgPtr& msg_ptr)
    {
        TCPImpl* ptr = msg_ptr->getTCPImpl();
        auto forbid_vec = AllTrade::NPTradeCenter::ITradeCenter::instance()->getAllForbidTradeStatus();
        msg_ptr->setResult(Err_Succeed);

        for (auto& item : forbid_vec)
        {
            msg_ptr->forbid_trade = item;
            ptr->sendMessageInter(msg_ptr);
        }
        msg_ptr->m_blast = true;
        ptr->sendMessageInter(msg_ptr);
    }

    void AsyncQryService::setForbidTradeStatus(const ReplyForbidBuySellSetMsgPtr& msg_ptr)
    {
        TCPImpl* ptr = msg_ptr->getTCPImpl();
        ErrorCodeType errcode = AllTrade::NPTradeCenter::ITradeCenter::instance()->updateForbidTradeStatus(msg_ptr->forbid_trade);
        msg_ptr->setResult(errcode);
        ptr->sendMessageInter(msg_ptr);
    }

    void AsyncQryService::qryPosiRateStatus(const ReplyPosiRateQryMsgPtr& msg_ptr)
    {
        TCPImpl* ptr = msg_ptr->getTCPImpl();
        auto posit_rate_vec = AllTrade::NPTradeCenter::ITradeCenter::instance()->getAllPositionRateStatus();
        msg_ptr->setResult(Err_Succeed);

        for (auto& item : posit_rate_vec)
        {
            msg_ptr->posit_rate = item;
            ptr->sendMessageInter(msg_ptr);
        }
        msg_ptr->m_blast = true;
        ptr->sendMessageInter(msg_ptr);
    }

    void AsyncQryService::setPosiRateStatus(const ReplyPosiRateSetMsgPtr& msg_ptr)
    {
        TCPImpl* ptr = msg_ptr->getTCPImpl();
        ErrorCodeType errcode = AllTrade::NPTradeCenter::ITradeCenter::instance()->updatePositionRateStatus(msg_ptr->posit_rate);
        msg_ptr->setResult(errcode);
        ptr->sendMessageInter(msg_ptr);
    }

    void AsyncQryService::deleteAgency(const ReplyAgencyDeleteMsgPtr& msg_ptr)
    {
        TCPImpl* ptr = msg_ptr->getTCPImpl();
        SAccountPtr item_ptr = AllTrade::NPMgrCenter::IManagerCenter::instance()->getAccountByLoginName(msg_ptr->m_login_name);
        if (!item_ptr || item_ptr->prop_ != E_ACCOUNT_PROP::EAP_Agency)
        {
            ptr->sendMessageInter(ReplyMsg::getReply(Error_User_Unexist, msg_ptr->getSocketID(), msg_ptr->getCmdCode()));
            return;
        }
        SAccountPtr op_item_ptr = AllTrade::NPMgrCenter::IManagerCenter::instance()->getAccountByLoginName(msg_ptr->getLoginName().c_str());
        if (!op_item_ptr || op_item_ptr->prop_ == E_ACCOUNT_PROP::EAP_Trader || op_item_ptr->prop_ == E_ACCOUNT_PROP::EAP_Funder
            || op_item_ptr->status_ != E_ACCOUNT_STATUS::EAS_Using)
        {
            ptr->sendMessageInter(ReplyMsg::getReply(Err_No_Oper_Rights, msg_ptr->getSocketID(), msg_ptr->getCmdCode()));
            return;
        }

        if (!AllTrade::NPTradeCenter::ITradeCenter::instance()->getPositionList(item_ptr->user_id_).empty())
        {
            ptr->sendMessageInter(ReplyMsg::getReply(Error_User_HasPosition, msg_ptr->getSocketID(), msg_ptr->getCmdCode()));
            return;
        }

		auto& vec = AllTrade::NPMgrCenter::IManagerCenter::instance()->getAllUsingTradeAccByLoginName(item_ptr->login_name_);
		if (vec.size() > 0)
		{
			msg_ptr->setResult(AllTrade::Error_User_Delete_HasBind);
			ptr->sendMessageInter(msg_ptr);
			return;
		}

		ErrorCodeType errcode = AuthorityControl::CAuthorityControl::instance()->judgeRoleUsersRelation(msg_ptr->m_login_name);
        if (errcode != Err_Succeed)
        {
            msg_ptr->setResult(errcode);
            ptr->sendMessageInter(msg_ptr);
            return;
        }

        // 判断子账户持仓资金
        std::vector<SAccountPtr> rslt = AllTrade::NPMgrCenter::IManagerCenter::instance()->getAllTrades(item_ptr->user_id_);
        for (auto& acc_item : rslt)
        {
            if (!AllTrade::NPTradeCenter::ITradeCenter::instance()->getPositionList(acc_item->user_id_).empty())
            {
                ptr->sendMessageInter(ReplyMsg::getReply(Error_User_HasPosition, msg_ptr->getSocketID(), msg_ptr->getCmdCode()));
                return;
            }
            auto money_ptr = AllTrade::NPMgrCenter::IManagerCenter::instance()->getMoneyInfoByLoginName(acc_item->login_name_);
            if (money_ptr && (money_ptr->logic_can_extract_ != 0 || money_ptr->logic_wait_thaw_ != 0
                || money_ptr->order_freeze_ != 0 || money_ptr->user_deposit_ != 0 || money_ptr->priority_fund_ != 0))
            {
                ptr->sendMessageInter(ReplyMsg::getReply(Error_User_HasMoney, msg_ptr->getSocketID(), msg_ptr->getCmdCode()));
                return;
            }
        }

        errcode = AllTrade::NPMgrCenter::IManagerCenter::instance()->deleteAccount(item_ptr->user_id_);

        msg_ptr->setResult(errcode);
        if (errcode == Err_Succeed)
        {
            ptr->sendMessageToAllInter(op_item_ptr->user_id_, op_item_ptr->login_name_, msg_ptr);

            // 删除其下子账户
            ReplyMsgPtr tmpptr_b(nullptr);
            RequestPtr tmpreqptr = std::make_shared<Request>();

            std::vector<SAccountPtr> child_rslt = AllTrade::NPMgrCenter::IManagerCenter::instance()->getAllChildren(item_ptr->user_id_);
            for (auto item : child_rslt)
            {
                switch (item->prop_)
                {
                case AllTrade::EAP_Agency:
                {
                    tmpreqptr->command_ = gszMsgCommandCode[E_COMM_MSG_TYPE::INSTITUTION_DEL_RSP];
                    ReplyAgencyDeleteMsgPtr tmpptr = std::make_shared<ReplyAgencyDeleteMsg>(tmpreqptr);
                    strncpy_s(tmpptr->m_login_name, item->login_name_, sizeof(LoginNameType) - 1);
                    tmpptr_b = tmpptr;
                }
                    break;
                case AllTrade::EAP_Manager:
                {
                    tmpreqptr->command_ = gszMsgCommandCode[E_COMM_MSG_TYPE::MANAGER_DEL_RSP];
                    ReplyManagerDeleteMsgPtr tmpptr = std::make_shared<ReplyManagerDeleteMsg>(tmpreqptr);
                    strncpy_s(tmpptr->m_login_name, item->login_name_, sizeof(LoginNameType) - 1);
                    tmpptr_b = tmpptr;
                }
                break;
                case AllTrade::EAP_Trader:
                {
                    tmpreqptr->command_ = gszMsgCommandCode[E_COMM_MSG_TYPE::CHILDUSER_DEL_RSP];
                    ReplyChildDeleteMsgPtr tmpptr = std::make_shared<ReplyChildDeleteMsg>(tmpreqptr);
                    strncpy_s(tmpptr->m_login_name, item->login_name_, sizeof(LoginNameType) - 1);
                    tmpptr_b = tmpptr;
                }
                break;
                case AllTrade::EAP_Funder:
                {
                    tmpreqptr->command_ = gszMsgCommandCode[E_COMM_MSG_TYPE::FUNDUSER_DEL_RSP];
                    ReplyFunderDeleteMsgPtr tmpptr = std::make_shared<ReplyFunderDeleteMsg>(tmpreqptr);
                    strncpy_s(tmpptr->m_login_name, item->login_name_, sizeof(LoginNameType) - 1);
                    tmpptr_b = tmpptr;
                }
                break;
                default:
                    break;
                }

                AllTrade::NPMgrCenter::IManagerCenter::instance()->deleteAccount(item->user_id_);
                ptr->sendMessageToAllInter(item->parent_id_, item->login_name_, tmpptr_b);
            }
        }
        else
            ptr->sendMessageInter(msg_ptr);


    }

    void AsyncQryService::deleteChild(const ReplyChildDeleteMsgPtr& msg_ptr)
    {
        TCPImpl* ptr = msg_ptr->getTCPImpl();
        SAccountPtr item_ptr = AllTrade::NPMgrCenter::IManagerCenter::instance()->getAccountByLoginName(msg_ptr->m_login_name);
        if (!item_ptr || item_ptr->prop_ != E_ACCOUNT_PROP::EAP_Trader)
        {
            ptr->sendMessageInter(ReplyMsg::getReply(Error_User_Unexist, msg_ptr->getSocketID(), msg_ptr->getCmdCode()));
            return;
        }
        SAccountPtr op_item_ptr = AllTrade::NPMgrCenter::IManagerCenter::instance()->getAccountByLoginName(msg_ptr->getLoginName().c_str());
        if (!op_item_ptr || op_item_ptr->prop_ == E_ACCOUNT_PROP::EAP_Trader || op_item_ptr->prop_ == E_ACCOUNT_PROP::EAP_Funder
            || op_item_ptr->status_ != E_ACCOUNT_STATUS::EAS_Using)
        {
            ptr->sendMessageInter(ReplyMsg::getReply(Err_No_Oper_Rights, msg_ptr->getSocketID(), msg_ptr->getCmdCode()));
            return;
        }

        if (!AllTrade::NPTradeCenter::ITradeCenter::instance()->getPositionList(item_ptr->user_id_).empty())
        {
            ptr->sendMessageInter(ReplyMsg::getReply(Error_User_HasPosition, msg_ptr->getSocketID(), msg_ptr->getCmdCode()));
            return;
        }

        ErrorCodeType errcode = AllTrade::NPMgrCenter::IManagerCenter::instance()->deleteAccount(item_ptr->user_id_);
        msg_ptr->setResult(errcode);
        if (errcode == Err_Succeed)
            ptr->sendMessageToAllInter(op_item_ptr->user_id_, op_item_ptr->login_name_, msg_ptr);
        else
            ptr->sendMessageInter(msg_ptr);
    }

    void AsyncQryService::deleteFunder(const ReplyFunderDeleteMsgPtr& msg_ptr)
    {
        TCPImpl* ptr = msg_ptr->getTCPImpl();
        SAccountPtr item_ptr = AllTrade::NPMgrCenter::IManagerCenter::instance()->getAccountByLoginName(msg_ptr->m_login_name);
        if (!item_ptr || item_ptr->prop_ != E_ACCOUNT_PROP::EAP_Funder)
        {
            ptr->sendMessageInter(ReplyMsg::getReply(Error_User_Unexist, msg_ptr->getSocketID(), msg_ptr->getCmdCode()));
            return;
        }
        SAccountPtr op_item_ptr = AllTrade::NPMgrCenter::IManagerCenter::instance()->getAccountByLoginName(msg_ptr->getLoginName().c_str());
        if (!op_item_ptr || op_item_ptr->prop_ == E_ACCOUNT_PROP::EAP_Trader || op_item_ptr->prop_ == E_ACCOUNT_PROP::EAP_Funder
            || op_item_ptr->status_ != E_ACCOUNT_STATUS::EAS_Using)
        {
            ptr->sendMessageInter(ReplyMsg::getReply(Err_No_Oper_Rights, msg_ptr->getSocketID(), msg_ptr->getCmdCode()));
            return;
        }

        if (!AllTrade::NPTradeCenter::ITradeCenter::instance()->getPositionList(item_ptr->user_id_).empty())
        {
            ptr->sendMessageInter(ReplyMsg::getReply(Error_User_HasPosition, msg_ptr->getSocketID(), msg_ptr->getCmdCode()));
            return;
        }

        ErrorCodeType errcode = AllTrade::NPMgrCenter::IManagerCenter::instance()->deleteAccount(item_ptr->user_id_);
        msg_ptr->setResult(errcode);
        if (errcode == Err_Succeed)
            ptr->sendMessageToAllInter(op_item_ptr->user_id_, op_item_ptr->login_name_, msg_ptr);
        else
            ptr->sendMessageInter(msg_ptr);
    }

    void AsyncQryService::deleteManager(const ReplyManagerDeleteMsgPtr& msg_ptr)
    {
        TCPImpl* ptr = msg_ptr->getTCPImpl();
        SAccountPtr item_ptr = AllTrade::NPMgrCenter::IManagerCenter::instance()->getAccountByLoginName(msg_ptr->m_login_name);
        if (!item_ptr || item_ptr->prop_ != E_ACCOUNT_PROP::EAP_Manager)
        {
            ptr->sendMessageInter(ReplyMsg::getReply(Error_User_Unexist, msg_ptr->getSocketID(), msg_ptr->getCmdCode()));
            return;
        }
        SAccountPtr op_item_ptr = AllTrade::NPMgrCenter::IManagerCenter::instance()->getAccountByLoginName(msg_ptr->getLoginName().c_str());
        if (!op_item_ptr || op_item_ptr->prop_ == E_ACCOUNT_PROP::EAP_Trader || op_item_ptr->prop_ == E_ACCOUNT_PROP::EAP_Funder
            || op_item_ptr->status_ != E_ACCOUNT_STATUS::EAS_Using)
        {
            ptr->sendMessageInter(ReplyMsg::getReply(Err_No_Oper_Rights, msg_ptr->getSocketID(), msg_ptr->getCmdCode()));
            return;
        }

        if (!AllTrade::NPTradeCenter::ITradeCenter::instance()->getPositionList(item_ptr->user_id_).empty())
        {
            ptr->sendMessageInter(ReplyMsg::getReply(Error_User_HasPosition, msg_ptr->getSocketID(), msg_ptr->getCmdCode()));
            return;
        }

		ErrorCodeType errcode = AuthorityControl::CAuthorityControl::instance()->judgeRoleUsersRelation(msg_ptr->m_login_name);
        if (errcode != Err_Succeed)
        {
            msg_ptr->setResult(errcode);
            ptr->sendMessageInter(msg_ptr);
            return;
        }

        errcode = AllTrade::NPMgrCenter::IManagerCenter::instance()->deleteAccount(item_ptr->user_id_);
        msg_ptr->setResult(errcode);
        if (errcode == Err_Succeed)
            ptr->sendMessageToAllInter(op_item_ptr->user_id_, op_item_ptr->login_name_, msg_ptr);
        else
            ptr->sendMessageInter(msg_ptr);
    }

    void AsyncQryService::qryCustomStock(const ReplyGetCustomStockMsgPtr& msg_ptr)
    {
        TCPImpl* ptr = msg_ptr->getTCPImpl();

//         SExchangePtr ex_ptr = AllTrade::NPMgrCenter::IManagerCenter::instance()->getExchangeByCode(CommodityTypeType::COMMODITY_TYPE_STOCK, msg_ptr->m_exchange_code);
//         if (!ex_ptr)
//         {
//             ptr->sendMessageInter(ReplyMsg::getReply(Error_Exchange_Unexist, msg_ptr->getSocketID(), msg_ptr->getCmdCode()));
//             return;
//         }

        auto self_ptr = AllTrade::NPMgrCenter::IManagerCenter::instance()->getAccountByLoginName(msg_ptr->getLoginName().c_str());
        if (!self_ptr)
        {
            ptr->sendMessageInter(ReplyMsg::getReply(Error_User_Unexist, msg_ptr->getSocketID(), msg_ptr->getCmdCode()));
            return;
        }
        if (self_ptr->status_ != E_ACCOUNT_STATUS::EAS_Using)
        {
            ptr->sendMessageInter(ReplyMsg::getReply(Error_User_Status_Unallow, msg_ptr->getSocketID(), msg_ptr->getCmdCode()));
            return;
        }

        std::vector<AllTrade::NPMgrCenter::SContractPtr> vec = AllTrade::NPMgrCenter::IManagerCenter::instance()->getCustomStockContractsByUserID(/*ex_ptr, */self_ptr->user_id_);
        msg_ptr->setResult(Err_Succeed);
        for (auto& item : vec)
        {
            msg_ptr->m_stock_ptr = std::dynamic_pointer_cast<SStockContract>(item);
            SExchangePtr ex_ptr = AllTrade::NPMgrCenter::IManagerCenter::instance()->getExchangeByID(CommodityTypeType::COMMODITY_TYPE_STOCK, msg_ptr->m_stock_ptr->exchange_id_);
            if (ex_ptr)
                strncpy_s(msg_ptr->m_exchange_code, ex_ptr->exchange_code_, sizeof(msg_ptr->m_exchange_code) - 1);
            else
                memset(msg_ptr->m_exchange_code, 0, sizeof(msg_ptr->m_exchange_code));

            ptr->sendMessageInter(msg_ptr);
        }
        msg_ptr->m_blast = true;
        ptr->sendMessageInter(msg_ptr);
    }

    void AsyncQryService::addCustomStock(const ReplyAddCustomStockMsgPtr& msg_ptr)
    {
        TCPImpl* ptr = msg_ptr->getTCPImpl();

        SContractPtr con_ptr = AllTrade::NPMgrCenter::IManagerCenter::instance()->getStockContractByCode(StockAreaType::STOCKAREA_TYPE_A, msg_ptr->m_contract_code);
        if (!con_ptr)
        {
            ptr->sendMessageInter(ReplyMsg::getReply(Err_Contract_Qry, msg_ptr->getSocketID(), msg_ptr->getCmdCode()));
            return;
        }
        msg_ptr->m_stock_ptr = std::dynamic_pointer_cast<SStockContract>(con_ptr);

        auto self_ptr = AllTrade::NPMgrCenter::IManagerCenter::instance()->getAccountByLoginName(msg_ptr->getLoginName().c_str());
        if (!self_ptr)
        {
            ptr->sendMessageInter(ReplyMsg::getReply(Error_User_Unexist, msg_ptr->getSocketID(), msg_ptr->getCmdCode()));
            return;
        }
        if (self_ptr->status_ != E_ACCOUNT_STATUS::EAS_Using)
        {
            ptr->sendMessageInter(ReplyMsg::getReply(Error_User_Status_Unallow, msg_ptr->getSocketID(), msg_ptr->getCmdCode()));
            return;
        }

        SExchangePtr ex_ptr = AllTrade::NPMgrCenter::IManagerCenter::instance()->getExchangeByID(CommodityTypeType::COMMODITY_TYPE_STOCK, msg_ptr->m_stock_ptr->exchange_id_);
        if (ex_ptr)
            strncpy_s(msg_ptr->m_exchange_code, ex_ptr->exchange_code_, sizeof(msg_ptr->m_exchange_code) - 1);

        ErrorCodeType err_code = AllTrade::NPMgrCenter::IManagerCenter::instance()->addCustomStockContractsByUserID(con_ptr, self_ptr->user_id_);
        msg_ptr->setResult(Err_Succeed);
        ptr->sendMessageInter(msg_ptr);
    }

    void AsyncQryService::deleteCustomStock(const ReplyDelCustomStockMsgPtr& msg_ptr)
    {
        TCPImpl* ptr = msg_ptr->getTCPImpl();

        SContractPtr con_ptr = AllTrade::NPMgrCenter::IManagerCenter::instance()->getStockContractByCode(StockAreaType::STOCKAREA_TYPE_A, msg_ptr->m_contract_code);
        if (!con_ptr)
        {
            ptr->sendMessageInter(ReplyMsg::getReply(Err_Contract_Qry, msg_ptr->getSocketID(), msg_ptr->getCmdCode()));
            return;
        }
        msg_ptr->m_stock_ptr = std::dynamic_pointer_cast<SStockContract>(con_ptr);

        auto self_ptr = AllTrade::NPMgrCenter::IManagerCenter::instance()->getAccountByLoginName(msg_ptr->getLoginName().c_str());
        if (!self_ptr)
        {
            ptr->sendMessageInter(ReplyMsg::getReply(Error_User_Unexist, msg_ptr->getSocketID(), msg_ptr->getCmdCode()));
            return;
        }
        if (self_ptr->status_ != E_ACCOUNT_STATUS::EAS_Using)
        {
            ptr->sendMessageInter(ReplyMsg::getReply(Error_User_Status_Unallow, msg_ptr->getSocketID(), msg_ptr->getCmdCode()));
            return;
        }

        SExchangePtr ex_ptr = AllTrade::NPMgrCenter::IManagerCenter::instance()->getExchangeByID(CommodityTypeType::COMMODITY_TYPE_STOCK, msg_ptr->m_stock_ptr->exchange_id_);
        if (ex_ptr)
            strncpy_s(msg_ptr->m_exchange_code, ex_ptr->exchange_code_, sizeof(msg_ptr->m_exchange_code) - 1);

        ErrorCodeType err_code = AllTrade::NPMgrCenter::IManagerCenter::instance()->delCustomStockContractsByUserID(con_ptr, self_ptr->user_id_);
        msg_ptr->setResult(Err_Succeed);
        ptr->sendMessageInter(msg_ptr);
    }

    long AsyncQryService::on_threadstart(void* param)
    {
        return CommonTools::dispatcher_error_no_error;
    }

    long AsyncQryService::on_threadstop(void* param)
    {
        return CommonTools::dispatcher_error_no_error;
    }

    long AsyncQryService::on_message(CommonTools::CommandPtr msg, bool cleanup)
    {
        try {
            msg->execute();
        }
        catch (std::exception&) {
            assert(0);
        }
        return CommonTools::dispatcher_error_no_error;
    }

    long AsyncQryService::on_event(CommonTools::handler evt)
    {
        return CommonTools::dispatcher_error_no_error;
    }

	void AsyncQryService::addRole(const ReplyRolesAddMsgPtr& msg_ptr)
	{
		TCPImpl* ptr = msg_ptr->getTCPImpl();

		ErrorCodeType errcode(Err_Succeed);
        SAccountPtr item_ptr = IManagerCenter::instance()->getAccountByLoginName(msg_ptr->getLoginName().c_str());
        if (!item_ptr)
        {
            ptr->sendMessageInter(ReplyMsg::getReply(Error_User_Unexist, msg_ptr->getSocketID(), msg_ptr->getCmdCode()));
            return;
        }

		// 该角色名已经存在的判断
		errcode = AuthorityControl::CAuthorityControl::instance()->isHaveRoleName(msg_ptr->m_rtn_arp->rolesName);
		if (errcode == Err_Succeed) // 成功
		{
			errcode = AuthorityControl::CAuthorityControl::instance()->addRolesUserInfo(msg_ptr->m_rtn_arp);
			msg_ptr->setResult(errcode);
            ptr->sendMessageToAllInter(item_ptr->user_id_, item_ptr->login_name_, msg_ptr);
		}
		else // 失败
		{
			msg_ptr->setResult(errcode);
			ptr->sendMessageInter(msg_ptr);
		}

// 		SAccountPtr parent_ptr = AllTrade::NPMgrCenter::IManagerCenter::instance()->getAccountByID(item_ptr->parent_id_);
// 		if (errcode == Err_Succeed)
// 			ptr->sendMessageToAllInter(parent_ptr->user_id_, parent_ptr->login_name_, msg_ptr);
// 		else
// 			ptr->sendMessageInter(msg_ptr);
	}

	void AsyncQryService::bindRoleFunctionRelation(const ReplyBindRelationMsgPtr& msg_ptr)
	{
		TCPImpl* ptr = msg_ptr->getTCPImpl();

		ErrorCodeType errcode = AuthorityControl::CAuthorityControl::instance()->addAuthorityRoleFunctions(msg_ptr->m_roleId,msg_ptr->m_rtn_arfp);
		msg_ptr->setResult(errcode);
		ptr->sendMessageInter(msg_ptr);
	}

	void AsyncQryService::qryRoleInfo(const ReplyRolesQryMsgPtr& msg_ptr)
	{
		TCPImpl* ptr = msg_ptr->getTCPImpl();

		SAccountPtr item_ptr = AllTrade::NPMgrCenter::IManagerCenter::instance()->getAccountByLoginName(msg_ptr->getLoginName().c_str());
		if (!item_ptr || item_ptr->status_ != E_ACCOUNT_STATUS::EAS_Using
			|| item_ptr->prop_ == E_ACCOUNT_PROP::EAP_Trader || item_ptr->prop_ == E_ACCOUNT_PROP::EAP_Funder)
		{
			ptr->sendMessageInter(ReplyMsg::getReply(Error_User_Unexist, msg_ptr->getSocketID(), msg_ptr->getCmdCode()));
			return;
		}

		ErrorCodeType errcode(Err_Succeed);
		std::vector<AuthorityRolesPtr> vec;
		if (item_ptr->prop_ == E_ACCOUNT_PROP::EAP_Manager)
		{
			errcode = AuthorityControl::CAuthorityControl::instance()->getRolesUserInfo(item_ptr->parent_id_, vec);
		}
		else 
		{
			errcode = AuthorityControl::CAuthorityControl::instance()->getRolesUserInfo(item_ptr->user_id_, vec);
		}
		
		msg_ptr->setResult(errcode);

		for (auto item : vec)
		{
			strncpy_s(msg_ptr->m_rtn_arp->rolesName, item->rolesName, sizeof(msg_ptr->m_rtn_arp->rolesName) - 1);
			strncpy_s(msg_ptr->m_rtn_arp->login_name_, item->login_name_, sizeof(msg_ptr->m_rtn_arp->login_name_) - 1);
			msg_ptr->m_rtn_arp->rolesID = item->rolesID;
			msg_ptr->m_rtn_arp->rolesType = item->rolesType;
			msg_ptr->m_rtn_arp->operationType = item->operationType;

			ptr->sendMessageInter(msg_ptr);
		}

        msg_ptr->m_blast = true;
        ptr->sendMessageInter(msg_ptr);
    }

	void AsyncQryService::qrySelfFunctionsInfo(const ReplySelfFunctionMsgPtr& msg_ptr)
	{
		TCPImpl* ptr = msg_ptr->getTCPImpl();

        ErrorCodeType errcode = AuthorityControl::CAuthorityControl::instance()->getSelfFunctionsByLoginName(msg_ptr->getLoginName().c_str(), msg_ptr->m_rtn_ptr);
		msg_ptr->setResult(errcode);
		ptr->sendMessageInter(msg_ptr);
	}

	void AsyncQryService::qryRoleFunctionsInfo(const ReplyRoleFunctionMsgPtr& msg_ptr)
	{
		TCPImpl* ptr = msg_ptr->getTCPImpl();

		ErrorCodeType errcode = AuthorityControl::CAuthorityControl::instance()->getAuthorityRoleFunctionsByRoleId(msg_ptr->m_roleId, msg_ptr->m_rtn_ptr);
		msg_ptr->setResult(errcode);
		ptr->sendMessageInter(msg_ptr);
	}

	void AsyncQryService::changeRole(const ReplyRolesChangeMsgPtr& msg_ptr)
	{
		TCPImpl* ptr = msg_ptr->getTCPImpl();
		ErrorCodeType errcode(Err_Succeed);
		// 判断角色是否被功能 绑定关系
		errcode = AuthorityControl::CAuthorityControl::instance()->judgeRoleAndFunctionsRelationOne(msg_ptr->m_rtn_arfp->rolesID);
		if (errcode)
		{
			msg_ptr->setResult(errcode);
			ptr->sendMessageInter(msg_ptr);
			return;
		}

		// 判断该角色是否被用户绑定关系
		errcode = AuthorityControl::CAuthorityControl::instance()->judgeRoleUsersRelation(msg_ptr->m_rtn_arfp->rolesID);
		if (errcode)
		{
			msg_ptr->setResult(errcode);
			ptr->sendMessageInter(msg_ptr);
			return;
		}

        SAccountPtr item_ptr = IManagerCenter::instance()->getAccountByLoginName(msg_ptr->getLoginName().c_str());
        if (!item_ptr)
        {
            ptr->sendMessageInter(ReplyMsg::getReply(Error_User_Unexist, msg_ptr->getSocketID(), msg_ptr->getCmdCode()));
            return;
        }

        errcode = AuthorityControl::CAuthorityControl::instance()->updateRolesUserInfo(msg_ptr->m_rtn_arfp);
		msg_ptr->setResult(errcode);
        ptr->sendMessageToAllInter(item_ptr->user_id_, item_ptr->login_name_, msg_ptr);
    }

	void AsyncQryService::deleteRole(const ReplyDelRoleMsgPtr& msg_ptr)
	{
		TCPImpl* ptr = msg_ptr->getTCPImpl();

		ErrorCodeType errcode(Err_Succeed);

		SAccountPtr item_ptr = IManagerCenter::instance()->getAccountByLoginName(msg_ptr->getLoginName().c_str());
		if (!item_ptr)
		{
			ptr->sendMessageInter(ReplyMsg::getReply(Error_User_Unexist, msg_ptr->getSocketID(), msg_ptr->getCmdCode()));
			return;
		}

		// 判断角色是否被功能 绑定关系
		errcode = AuthorityControl::CAuthorityControl::instance()->judgeRoleAndFunctionsRelationOne(msg_ptr->m_roleId);
		if (errcode)
		{
			msg_ptr->setResult(errcode);
			ptr->sendMessageInter(msg_ptr);
			return;
		}	

		// 判断该角色是否被用户绑定关系
		errcode = AuthorityControl::CAuthorityControl::instance()->judgeRoleUsersRelation(msg_ptr->m_roleId);
		if (errcode == Err_Succeed)
		{
			errcode = AuthorityControl::CAuthorityControl::instance()->deleteRolesUser(msg_ptr->m_roleId);
			msg_ptr->setResult(errcode);
			ptr->sendMessageToAllInter(item_ptr->user_id_, item_ptr->login_name_, msg_ptr);
		}
		else
		{
			msg_ptr->setResult(errcode);
			ptr->sendMessageInter(msg_ptr);
		}

		
	}

	void AsyncQryService::getRoleUserInfo(const ReplyAgencyRolesQryMsgPtr& msg_ptr)
	{
		TCPImpl* ptr = msg_ptr->getTCPImpl();

		SAccountPtr item_ptr = AllTrade::NPMgrCenter::IManagerCenter::instance()->getAccountByLoginName(msg_ptr->getLoginName().c_str());
		if (!item_ptr || item_ptr->status_ != E_ACCOUNT_STATUS::EAS_Using
			|| item_ptr->prop_ == E_ACCOUNT_PROP::EAP_Trader || item_ptr->prop_ == E_ACCOUNT_PROP::EAP_Funder)
		{
			ptr->sendMessageInter(ReplyMsg::getReply(Error_User_Unexist, msg_ptr->getSocketID(), msg_ptr->getCmdCode()));
			return;
		}

		ErrorCodeType errcode(Err_Succeed);
		std::vector<AllTrade::AuthorityRoleUsersPtr> vecSt_;
		if (item_ptr->prop_ == E_ACCOUNT_PROP::EAP_Manager) // 为管理员登录
		{
			SAccountPtr parent_ptr = AllTrade::NPMgrCenter::IManagerCenter::instance()->getAccountByID(item_ptr->parent_id_);
			errcode = AuthorityControl::CAuthorityControl::instance()->getAuthorityRoleUsers(parent_ptr->login_name_, vecSt_);
		}
		else
		{
			errcode = AuthorityControl::CAuthorityControl::instance()->getAuthorityRoleUsers(msg_ptr->getLoginName().c_str(), vecSt_);
		}

		msg_ptr->setResult(errcode);
		for (auto item : vecSt_)
		{
			strncpy_s(msg_ptr->m_rtn_arp->login_name_, item->login_name_, sizeof(msg_ptr->m_rtn_arp->login_name_) - 1);
			msg_ptr->m_rtn_arp->rolesID = item->rolesID;

			ptr->sendMessageInter(msg_ptr);
		}

        msg_ptr->m_blast = true;
        ptr->sendMessageInter(msg_ptr);
	}

	void AsyncQryService::addRoleUserInfo(const ReplyUserRoleAddRelationMsgPtr& msg_ptr)
	{
		TCPImpl* ptr = msg_ptr->getTCPImpl();

		ErrorCodeType errcode(Err_Succeed);

		SAccountPtr item_ptr = AllTrade::NPMgrCenter::IManagerCenter::instance()->getAccountByLoginName(msg_ptr->m_rtn_arup->login_name_);
		// SAccountPtr item_ptr = IManagerCenter::instance()->getAccountByLoginName(msg_ptr->getLoginName().c_str());
		if (!item_ptr)
		{
			ptr->sendMessageInter(ReplyMsg::getReply(Error_User_Unexist, msg_ptr->getSocketID(), msg_ptr->getCmdCode()));
			return;
		}

		// 该用户已经绑定角色的不能添加
		errcode = AuthorityControl::CAuthorityControl::instance()->judgeRoleUsersRelation(msg_ptr->m_rtn_arup->login_name_, msg_ptr->m_rtn_arup->rolesID);
	
		if (errcode == Err_Succeed)
		{		
			std::vector<AllTrade::AuthorityRoleUsersPtr> vecSt_;
			vecSt_.emplace_back(msg_ptr->m_rtn_arup);
			errcode = AuthorityControl::CAuthorityControl::instance()->addAuthorityRoleUsers(vecSt_);
			msg_ptr->setResult(errcode);
			ptr->sendMessageToAllInter(item_ptr->user_id_, item_ptr->login_name_, msg_ptr);
		}
		else
		{
			msg_ptr->setResult(errcode);
			ptr->sendMessageInter(msg_ptr);
		}
	}

    void AsyncQryService::deleteRoleUserInfo(const ReplyDelRoleUserMsgPtr& msg_ptr)
	{
		TCPImpl* ptr = msg_ptr->getTCPImpl();

		ErrorCodeType errcode(Err_Succeed);

		SAccountPtr item_ptr = AllTrade::NPMgrCenter::IManagerCenter::instance()->getAccountByLoginName(msg_ptr->m_rtn_arup->login_name_);
	//	SAccountPtr item_ptr = IManagerCenter::instance()->getAccountByLoginName(msg_ptr->getLoginName().c_str());
		if (!item_ptr)
		{
			ptr->sendMessageInter(ReplyMsg::getReply(Error_User_Unexist, msg_ptr->getSocketID(), msg_ptr->getCmdCode()));
			return;
		}

		std::vector<AllTrade::AuthorityRoleUsersPtr> vecSt_;
		vecSt_.emplace_back(msg_ptr->m_rtn_arup);
		errcode = AuthorityControl::CAuthorityControl::instance()->deleteAuthorityRoleUsers(vecSt_);
		if (errcode == Err_Succeed)
		{
			msg_ptr->setResult(errcode);
			ptr->sendMessageToAllInter(item_ptr->user_id_, item_ptr->login_name_, msg_ptr);
		}
		else
		{
			msg_ptr->setResult(errcode);
			ptr->sendMessageInter(msg_ptr);
		}
	}

	void AsyncQryService::getAllBussnessInfo(const ReplyGetAllBussnessMsgPtr& msg_ptr)
	{
		TCPImpl* ptr = msg_ptr->getTCPImpl();
		
		ErrorCodeType errcode = AuthorityControl::CAuthorityControl::instance()->getAllBussness(msg_ptr->m_rtn_abp);
		msg_ptr->setResult(errcode);
		ptr->sendMessageInter(msg_ptr);
	}

    void AsyncQryService::getOnlineChildren(bool& bFind, std::vector<SAccountPtr>& rslt, const ReplyOnlineAccQryMsgPtr& msg_ptr)
    {
        TCPImpl* ptr = msg_ptr->getTCPImpl();

        SAccountPtr item_ptr = AllTrade::NPMgrCenter::IManagerCenter::instance()->getAccountByLoginName(msg_ptr->getLoginName().c_str());
        if (!item_ptr)
        {
            ptr->sendMessageInter(ReplyMsg::getReply(Error_User_Unexist, msg_ptr->getSocketID(), msg_ptr->getCmdCode()));
            return;
        }

        if ((item_ptr->prop_ != E_ACCOUNT_PROP::EAP_Root
                && item_ptr->prop_ != E_ACCOUNT_PROP::EAP_Agency
                && item_ptr->prop_ != E_ACCOUNT_PROP::EAP_Risker
                && item_ptr->prop_ != E_ACCOUNT_PROP::EAP_Manager)
            || !AuthorityControl::CAuthorityControl::instance()->isHaveOnLineUserAuthority(item_ptr->login_name_)
            )
        {
            ptr->sendMessageInter(ReplyMsg::getReply(Err_No_Oper_Rights, msg_ptr->getSocketID(), msg_ptr->getCmdCode()));
            return;
        }

        if (item_ptr->prop_ == E_ACCOUNT_PROP::EAP_Manager)
        {
            rslt = AllTrade::NPMgrCenter::IManagerCenter::instance()->getAllChildren(item_ptr->parent_id_);
            for (auto iter = rslt.begin(); iter != rslt.end(); )
            {
                if (msg_ptr->getLoginName() == (*iter)->login_name_
                    || ((*iter)->prop_ == E_ACCOUNT_PROP::EAP_Agency&& !AuthorityControl::CAuthorityControl::instance()->isHaveAuthority(item_ptr->login_name_, IMC_InstitutionSetQuery))
                    || ((*iter)->prop_ == E_ACCOUNT_PROP::EAP_Manager&& !AuthorityControl::CAuthorityControl::instance()->isHaveAuthority(item_ptr->login_name_, AMC_ManagerUserQuery))
                    || ((*iter)->prop_ == E_ACCOUNT_PROP::EAP_Funder&& !AuthorityControl::CAuthorityControl::instance()->isHaveAuthority(item_ptr->login_name_, AMC_FundUserQuery))
                    || ((*iter)->prop_ == E_ACCOUNT_PROP::EAP_Trader&& !AuthorityControl::CAuthorityControl::instance()->isHaveAuthority(item_ptr->login_name_, AMC_ChildQuery))
                    )
                {
                    iter = rslt.erase(iter);
                }
                else
                    iter++;
            }
        }
        else
            rslt = AllTrade::NPMgrCenter::IManagerCenter::instance()->getAllChildren(item_ptr->user_id_);
        bFind = true;
    }

    void AsyncQryService::qryFeeSet(const ReplyFeeSetQryMsgPtr& msg_ptr)
    {
        TCPImpl* ptr = msg_ptr->getTCPImpl();

        msg_ptr->m_rtn_fee = AllTrade::NPTradeCenter::ITradeCenter::instance()->getFeeSetPtr();
        if (msg_ptr->m_rtn_fee)
            msg_ptr->setResult(Err_Succeed);
        else
            msg_ptr->setResult(Err_Unknown);

        ptr->sendMessageInter(msg_ptr);
    }

    void AsyncQryService::changeFeeSet(const ReplyFeeSetMsgPtr& msg_ptr)
    {
        TCPImpl* ptr = msg_ptr->getTCPImpl();

        ErrorCodeType errcode = AllTrade::NPTradeCenter::ITradeCenter::instance()->setFeeSetPtr(msg_ptr->m_trade_fee);
        msg_ptr->setResult(errcode);

        ptr->sendMessageInter(msg_ptr);
    }

	void AsyncQryService::changeRoleUserInfo(const ReplyChangeRoleUserMsgPtr& msg_ptr)
	{
		TCPImpl* ptr = msg_ptr->getTCPImpl();

		ErrorCodeType errcode(Err_Succeed);

		SAccountPtr item_ptr = AllTrade::NPMgrCenter::IManagerCenter::instance()->getAccountByLoginName(msg_ptr->m_rtn_arup->login_name_);
		if (!item_ptr)
		{
			ptr->sendMessageInter(ReplyMsg::getReply(Error_User_Unexist, msg_ptr->getSocketID(), msg_ptr->getCmdCode()));
			return;
		}

		errcode = AuthorityControl::CAuthorityControl::instance()->changeAuthorityRoleUsers(msg_ptr->m_rtn_arup);
		if (errcode == Err_Succeed)
		{
			msg_ptr->setResult(errcode);
			ptr->sendMessageToAllInter(item_ptr->user_id_, item_ptr->login_name_, msg_ptr);
		}
		else
		{
			msg_ptr->setResult(errcode);
			ptr->sendMessageInter(msg_ptr);
		}
	}

    void AsyncQryService::qryAgencyCommissInfo(const ReplyCommissQryMsgPtr& msg_ptr)
    {
        TCPImpl* ptr = msg_ptr->getTCPImpl();
        ErrorCodeType errcode(Err_Succeed);
        msg_ptr->m_rtn_acc = AllTrade::NPMgrCenter::IManagerCenter::instance()->getAccountByLoginName(msg_ptr->m_qry_login_name);
        if (!msg_ptr->m_rtn_acc)
        {
            ptr->sendMessageInter(ReplyMsg::getReply(Error_User_Unexist, msg_ptr->getSocketID(), msg_ptr->getCmdCode()));
            return;
        }
        if (!OperationManager::COperationManager::instance()->qryAgencyCommissInfo(msg_ptr->m_rtn_acc->user_id_, msg_ptr->m_start_day, msg_ptr->m_end_day, msg_ptr->m_infomatch, msg_ptr->m_tradefee, msg_ptr->m_comm_all))
            errcode = Err_Database;

        if (msg_ptr->m_rtn_acc->prop_ != E_ACCOUNT_PROP::EAP_Root)
        {
            auto risk = AllTrade::NPMgrCenter::IManagerCenter::instance()->getRiskInfoByLoginName(msg_ptr->m_qry_login_name);
            assert(risk);
            if (risk)
            {
                msg_ptr->m_infomatch_rate = risk->custom_commissionrate_;
                msg_ptr->m_tradefee_rate = risk->commissionrate_;
            }
        }
        else
        {
            msg_ptr->m_infomatch_rate = 1000;
            msg_ptr->m_tradefee_rate = 1000;
        }

        msg_ptr->setResult(errcode);
        ptr->sendMessageInter(msg_ptr);
    }

    void AsyncQryService::qryAgencyCommissDtlInfo(const ReplyCommissDtlQryMsgPtr& msg_ptr)
    {
        TCPImpl* ptr = msg_ptr->getTCPImpl();
        ErrorCodeType errcode(Err_Succeed);
        msg_ptr->m_rtn_acc = AllTrade::NPMgrCenter::IManagerCenter::instance()->getAccountByLoginName(msg_ptr->m_qry_login_name);
        if (!msg_ptr->m_rtn_acc)
        {
            ptr->sendMessageInter(ReplyMsg::getReply(Error_User_Unexist, msg_ptr->getSocketID(), msg_ptr->getCmdCode()));
            return;
        }
        std::vector<SAgencyMoneyDetailInfoPtr> vec = OperationManager::COperationManager::instance()->qryAgencyCommissDtlInfo(msg_ptr->m_rtn_acc->user_id_, msg_ptr->m_start_day, msg_ptr->m_end_day);
        msg_ptr->setResult(Err_Succeed);
        for (auto item : vec)
        {
            msg_ptr->m_detail_ptr = item;
            msg_ptr->m_rtn_source_acc = AllTrade::NPMgrCenter::IManagerCenter::instance()->getAccountByID(item->source_user_id_);

            ptr->sendMessageInter(msg_ptr);
        }
        msg_ptr->m_blast = true;
        ptr->sendMessageInter(msg_ptr);
    }

    void AsyncQryService::qryAgencyProfitInfo(const ReplyProfitCommisslQryMsgPtr& msg_ptr)
    {
        TCPImpl* ptr = msg_ptr->getTCPImpl();
        ErrorCodeType errcode(Err_Succeed);
        msg_ptr->m_rtn_acc = AllTrade::NPMgrCenter::IManagerCenter::instance()->getAccountByLoginName(msg_ptr->m_qry_login_name);
        if (!msg_ptr->m_rtn_acc)
        {
            ptr->sendMessageInter(ReplyMsg::getReply(Error_User_Unexist, msg_ptr->getSocketID(), msg_ptr->getCmdCode()));
            return;
        }
        if (!OperationManager::COperationManager::instance()->qryAgencyProfitInfo(msg_ptr->m_rtn_acc->user_id_, msg_ptr->m_start_day, msg_ptr->m_end_day, msg_ptr->m_profit))
            errcode = Err_Database;

        if (msg_ptr->m_rtn_acc->prop_ != E_ACCOUNT_PROP::EAP_Root)
        {
            auto risk = AllTrade::NPMgrCenter::IManagerCenter::instance()->getRiskInfoByLoginName(msg_ptr->m_qry_login_name);
            assert(risk);
            if (risk)
                msg_ptr->m_profit_rate = risk->procommrate_;
        }
        else
        {
            auto fee_set_ptr = AllTrade::NPTradeCenter::ITradeCenter::instance()->getFeeSetPtr();
            if (fee_set_ptr)
                msg_ptr->m_profit_rate = fee_set_ptr->user_profit_rate_;
        }

        msg_ptr->setResult(errcode);
        ptr->sendMessageInter(msg_ptr);
    }

    void AsyncQryService::qryAgencyProfitDtlInfo(const ReplyProfitCommissDtlQryMsgPtr& msg_ptr)
    {
        TCPImpl* ptr = msg_ptr->getTCPImpl();
        ErrorCodeType errcode(Err_Succeed);
        msg_ptr->m_rtn_acc = AllTrade::NPMgrCenter::IManagerCenter::instance()->getAccountByLoginName(msg_ptr->m_qry_login_name);
        if (!msg_ptr->m_rtn_acc)
        {
            ptr->sendMessageInter(ReplyMsg::getReply(Error_User_Unexist, msg_ptr->getSocketID(), msg_ptr->getCmdCode()));
            return;
        }
        std::vector<SAgencyMoneyDetailInfoPtr> vec = OperationManager::COperationManager::instance()->qryAgencyProfitDtlInfo(msg_ptr->m_rtn_acc->user_id_, msg_ptr->m_start_day, msg_ptr->m_end_day);
        msg_ptr->setResult(Err_Succeed);
        for (auto item : vec)
        {
            msg_ptr->m_detail_ptr = item;
            msg_ptr->m_rtn_source_acc = AllTrade::NPMgrCenter::IManagerCenter::instance()->getAccountByID(item->source_user_id_);

            ptr->sendMessageInter(msg_ptr);
        }
        msg_ptr->m_blast = true;
        ptr->sendMessageInter(msg_ptr);
    }

	void AsyncQryService::qryRiskHistoryInfos(const ReplyRiskHistoryMsgPtr& msg_ptr)
	{
		TCPImpl* ptr = msg_ptr->getTCPImpl();

		SAccountPtr item_ptr = AllTrade::NPMgrCenter::IManagerCenter::instance()->getAccountByLoginName(msg_ptr->getLoginName().c_str());
		if (!item_ptr || item_ptr->status_ != E_ACCOUNT_STATUS::EAS_Using
			|| item_ptr->prop_ == E_ACCOUNT_PROP::EAP_Trader || item_ptr->prop_ == E_ACCOUNT_PROP::EAP_Funder)
		{
			ptr->sendMessageInter(ReplyMsg::getReply(Error_User_Unexist, msg_ptr->getSocketID(), msg_ptr->getCmdCode()));
			return;
		}

		std::vector<AllTrade::NPTradeCenter::ImmRiskControlPtr> vecSt_;
		SAccountPtr child_ptr = AllTrade::NPMgrCenter::IManagerCenter::instance()->getAccountByLoginName(msg_ptr->m_login_name);

		ErrorCodeType errcode(Err_Succeed);
		if (!OperationManager::COperationManager::instance()->selectHistoryRiskRecord(child_ptr->user_id_, msg_ptr->m_start_day, msg_ptr->m_end_day, vecSt_))
			errcode = Err_Database;

		msg_ptr->setResult(errcode);

		
		for (auto& item : vecSt_)
		{
			strncpy_s(msg_ptr->m_login_name, child_ptr->login_name_, sizeof(child_ptr->login_name_) - 1);
			strncpy_s(msg_ptr->m_acc_name, child_ptr->account_name_, sizeof(child_ptr->account_name_) - 1);
			msg_ptr->m_contextPtr->rc_type_ = item->rc_type_;
			strncpy_s(msg_ptr->m_contextPtr->date_time_, item->date_time_, sizeof(msg_ptr->m_contextPtr->date_time_) - 1);
			strncpy_s(msg_ptr->m_contextPtr->trigger_text_, item->trigger_text_, sizeof(msg_ptr->m_contextPtr->trigger_text_) - 1);

			ptr->sendMessageInter(msg_ptr);
		}

		msg_ptr->m_blast = true;
		ptr->sendMessageInter(msg_ptr);
	}

	void AsyncQryService::qryRiskTimerInfos(const ReplyTimeWarnQryMsgPtr& msg_ptr)
	{
		TCPImpl* ptr = msg_ptr->getTCPImpl();

		SAccountPtr item_ptr = AllTrade::NPMgrCenter::IManagerCenter::instance()->getAccountByLoginName(msg_ptr->getLoginName().c_str());
		if (!item_ptr || item_ptr->status_ != E_ACCOUNT_STATUS::EAS_Using
			|| item_ptr->prop_ == E_ACCOUNT_PROP::EAP_Trader || item_ptr->prop_ == E_ACCOUNT_PROP::EAP_Funder)
		{
			ptr->sendMessageInter(ReplyMsg::getReply(Error_User_Unexist, msg_ptr->getSocketID(), msg_ptr->getCmdCode()));
			return;
		}
		SAccountPtr child_ptr = AllTrade::NPMgrCenter::IManagerCenter::instance()->getAccountByLoginName(msg_ptr->m_login_name);

		std::vector<AllTrade::NPTradeCenter::ImmRiskControlPtr> vecSt_;
		ErrorCodeType errcode(Err_Succeed);
		if (!OperationManager::COperationManager::instance()->getRiskRecord(child_ptr->user_id_, vecSt_))
			errcode = Err_Database;

		msg_ptr->setResult(errcode);

		
		for (auto& item : vecSt_)
		{
			strncpy_s(msg_ptr->m_login_name, child_ptr->login_name_, sizeof(child_ptr->login_name_) - 1);
			strncpy_s(msg_ptr->m_acc_name, child_ptr->account_name_, sizeof(child_ptr->account_name_) - 1);
			msg_ptr->m_contextPtr->rc_type_ = item->rc_type_;
			strncpy_s(msg_ptr->m_contextPtr->date_time_, item->date_time_, sizeof(msg_ptr->m_contextPtr->date_time_) - 1);
			strncpy_s(msg_ptr->m_contextPtr->trigger_text_, item->trigger_text_, sizeof(msg_ptr->m_contextPtr->trigger_text_) - 1);
	
			ptr->sendMessageInter(msg_ptr);
		}

		msg_ptr->m_blast = true;
		ptr->sendMessageInter(msg_ptr);
	}

	void AsyncQryService::setMarginInfo(const ReplySetMarginMsgPtr& msg_ptr)
	{
		TCPImpl* ptr = msg_ptr->getTCPImpl();

		SAccountPtr item_ptr = AllTrade::NPMgrCenter::IManagerCenter::instance()->getAccountByLoginName(msg_ptr->getLoginName().c_str());
		if (!item_ptr || item_ptr->status_ != E_ACCOUNT_STATUS::EAS_Using
			|| item_ptr->prop_ == E_ACCOUNT_PROP::EAP_Trader || item_ptr->prop_ == E_ACCOUNT_PROP::EAP_Funder)
		{
			ptr->sendMessageInter(ReplyMsg::getReply(Error_User_Unexist, msg_ptr->getSocketID(), msg_ptr->getCmdCode()));
			return;
		}

		// 判断1：总数量修改不能小于已融券数量
		int margin_qty_ = 0;

		// 判断2：剩余数量的计算

		ErrorCodeType errcode(Err_Succeed);
		if (!OperationManager::COperationManager::instance()->updateMarginInfoTable(msg_ptr->m_margin_set_))
			errcode = Err_Database;

		msg_ptr->setResult(errcode);

		msg_ptr->m_blast = true;
		ptr->sendMessageInter(msg_ptr);
	}

	void AsyncQryService::getMarginLeftInfo(const ReplyMarginLeftQtyMsgPtr& msg_ptr)
	{
		TCPImpl* ptr = msg_ptr->getTCPImpl();

		SAccountPtr item_ptr = AllTrade::NPMgrCenter::IManagerCenter::instance()->getAccountByLoginName(msg_ptr->getLoginName().c_str());
		if (!item_ptr || item_ptr->status_ != E_ACCOUNT_STATUS::EAS_Using
			|| item_ptr->prop_ == E_ACCOUNT_PROP::EAP_Trader || item_ptr->prop_ == E_ACCOUNT_PROP::EAP_Funder)
		{
			ptr->sendMessageInter(ReplyMsg::getReply(Error_User_Unexist, msg_ptr->getSocketID(), msg_ptr->getCmdCode()));
			return;
		}


		ErrorCodeType errcode(Err_Succeed);
		if (!OperationManager::COperationManager::instance()->getMarginLeftTable(msg_ptr->m_margin_left_))
			errcode = Err_Database;

		msg_ptr->setResult(errcode);

		msg_ptr->m_blast = true;
		ptr->sendMessageInter(msg_ptr);
	}

	void AsyncQryService::getMarginManagerInfo(const ReplyMarginManagerQtyMsgPtr& msg_ptr)
	{
		TCPImpl* ptr = msg_ptr->getTCPImpl();

		SAccountPtr item_ptr = AllTrade::NPMgrCenter::IManagerCenter::instance()->getAccountByLoginName(msg_ptr->getLoginName().c_str());
		if (!item_ptr || item_ptr->status_ != E_ACCOUNT_STATUS::EAS_Using
			|| item_ptr->prop_ == E_ACCOUNT_PROP::EAP_Trader || item_ptr->prop_ == E_ACCOUNT_PROP::EAP_Funder)
		{
			ptr->sendMessageInter(ReplyMsg::getReply(Error_User_Unexist, msg_ptr->getSocketID(), msg_ptr->getCmdCode()));
			return;
		}


		ErrorCodeType errcode(Err_Succeed);
		if (!OperationManager::COperationManager::instance()->getAllMarginInfo(msg_ptr->m_margin_set_))
			errcode = Err_Database;

		msg_ptr->setResult(errcode);

		msg_ptr->m_blast = true;
		ptr->sendMessageInter(msg_ptr);
	}

	void AsyncQryService::getMarginLiabilitiesInfo(const ReplyMarginLiabilitiesQtyMsgPtr& msg_ptr)
	{
		TCPImpl* ptr = msg_ptr->getTCPImpl();

		SAccountPtr item_ptr = AllTrade::NPMgrCenter::IManagerCenter::instance()->getAccountByLoginName(msg_ptr->getLoginName().c_str());
		if (!item_ptr || item_ptr->status_ != E_ACCOUNT_STATUS::EAS_Using
			|| item_ptr->prop_ == E_ACCOUNT_PROP::EAP_Trader || item_ptr->prop_ == E_ACCOUNT_PROP::EAP_Funder)
		{
			ptr->sendMessageInter(ReplyMsg::getReply(Error_User_Unexist, msg_ptr->getSocketID(), msg_ptr->getCmdCode()));
			return;
		}


		ErrorCodeType errcode(Err_Succeed);
		////////////////////////////////////////////////////////////////////////////////////

		msg_ptr->setResult(errcode);

		msg_ptr->m_blast = true;
		ptr->sendMessageInter(msg_ptr);
	}

	void AsyncQryService::getInterestStatisticsInfo(const ReplyInterestStatisticsMsgPtr& msg_ptr)
	{
		TCPImpl* ptr = msg_ptr->getTCPImpl();

		SAccountPtr item_ptr = AllTrade::NPMgrCenter::IManagerCenter::instance()->getAccountByLoginName(msg_ptr->getLoginName().c_str());
		if (!item_ptr || item_ptr->status_ != E_ACCOUNT_STATUS::EAS_Using
			|| item_ptr->prop_ == E_ACCOUNT_PROP::EAP_Trader || item_ptr->prop_ == E_ACCOUNT_PROP::EAP_Funder)
		{
			ptr->sendMessageInter(ReplyMsg::getReply(Error_User_Unexist, msg_ptr->getSocketID(), msg_ptr->getCmdCode()));
			return;
		}


		SAccountPtr child_ptr = AllTrade::NPMgrCenter::IManagerCenter::instance()->getAccountByLoginName(msg_ptr->m_login_name);
		if (!child_ptr)
		{
			ptr->sendMessageInter(ReplyMsg::getReply(Error_User_Unexist, msg_ptr->getSocketID(), msg_ptr->getCmdCode()));
			return;
		}
		ErrorCodeType errcode(Err_Succeed);
		////////////////////////////////////////////////////////////////////////////////////
		if (!OperationManager::COperationManager::instance()->getInterestStatisticsTable(child_ptr->user_id_,msg_ptr->m_ptr_))
			errcode = Err_Database;

		msg_ptr->setResult(errcode);

		msg_ptr->m_blast = true;
		ptr->sendMessageInter(msg_ptr);
	}

	void AsyncQryService::getInterestDetailInfo(const ReplyInterestDetailMsgPtr& msg_ptr)
	{
		TCPImpl* ptr = msg_ptr->getTCPImpl();

		SAccountPtr item_ptr = AllTrade::NPMgrCenter::IManagerCenter::instance()->getAccountByLoginName(msg_ptr->getLoginName().c_str());
		if (!item_ptr || item_ptr->status_ != E_ACCOUNT_STATUS::EAS_Using
			|| item_ptr->prop_ == E_ACCOUNT_PROP::EAP_Trader || item_ptr->prop_ == E_ACCOUNT_PROP::EAP_Funder)
		{
			ptr->sendMessageInter(ReplyMsg::getReply(Error_User_Unexist, msg_ptr->getSocketID(), msg_ptr->getCmdCode()));
			return;
		}


		SAccountPtr child_ptr = AllTrade::NPMgrCenter::IManagerCenter::instance()->getAccountByLoginName(msg_ptr->m_login_name);
		if (!child_ptr)
		{
			ptr->sendMessageInter(ReplyMsg::getReply(Error_User_Unexist, msg_ptr->getSocketID(), msg_ptr->getCmdCode()));
			return;
		}
		ErrorCodeType errcode(Err_Succeed);

		std::vector<AllTrade::NPMgrCenter::InterestDetailPtr> vec;
		////////////////////////////////////////////////////////////////////////////////////
		if (!OperationManager::COperationManager::instance()->getInterestDetailTable(child_ptr->user_id_, vec))
			errcode = Err_Database;

		for (auto& item : vec)
		{
			strncpy_s(msg_ptr->m_login_name, child_ptr->login_name_, sizeof(msg_ptr->m_login_name) - 1);
			strncpy_s(msg_ptr->m_acount_name, child_ptr->account_name_, sizeof(msg_ptr->m_acount_name) - 1);
			strncpy_s(msg_ptr->m_ptr_->user_id_, item->user_id_, sizeof(msg_ptr->m_ptr_->user_id_) - 1);
			msg_ptr->m_ptr_->sum_interest_ = item->sum_interest_;
			strncpy_s(msg_ptr->m_ptr_->date_time_, item->date_time_, sizeof(msg_ptr->m_ptr_->date_time_) - 1);

			msg_ptr->m_ptr_->change_type_ = item->change_type_;
			strncpy_s(msg_ptr->m_ptr_->source_user_id_, item->source_user_id_, sizeof(msg_ptr->m_ptr_->source_user_id_) - 1);
			msg_ptr->m_ptr_->interest_rate_ = item->interest_rate_;	
			
			msg_ptr->setResult(errcode);
		}
		

		msg_ptr->m_blast = true;
		ptr->sendMessageInter(msg_ptr);
	}

	void AsyncQryService::getCurrentMarginEntrustInfo(const ReplyCurrentMarginEntrustMsgPtr& msg_ptr)
	{
		TCPImpl* ptr = msg_ptr->getTCPImpl();
		TradeAccountPtr item_ptr = std::dynamic_pointer_cast<TradeAccount>(AllTrade::NPMgrCenter::IManagerCenter::instance()->getAccountByLoginName(msg_ptr->m_rtn_acc->login_name_));
		if (!item_ptr)
		{
			ptr->sendMessageInter(ReplyMsg::getReply(Error_User_Unexist, msg_ptr->getSocketID(), msg_ptr->getCmdCode()));
			return;
		}
		msg_ptr->m_rtn_acc = item_ptr;
		SAccountPtr parent_ptr = AllTrade::NPMgrCenter::IManagerCenter::instance()->getAccountByID(msg_ptr->m_rtn_acc->parent_id_);
		if (!parent_ptr)
		{
			ptr->sendMessageInter(ReplyMsg::getReply(Error_User_Parent_Unexist, msg_ptr->getSocketID(), msg_ptr->getCmdCode()));
			return;
		}
		strncpy_s(msg_ptr->m_parent_login_name, parent_ptr->login_name_, sizeof(msg_ptr->m_parent_login_name) - 1);

		// 待处理 ××××××××××××××××××××××××××××××××
		std::vector<OrderInfoPtr> pos_vec; //= AllTrade::NPTradeCenter::ITradeCenter::instance()->getCurrentOrderList(item_ptr->user_id_);
		for (auto& item : pos_vec)
		{
			msg_ptr->m_order_ptr = std::dynamic_pointer_cast<StockOrderInfo>(item);
			if (msg_ptr->m_order_ptr)
				msg_ptr->m_stock_ptr = AllTrade::NPMgrCenter::IManagerCenter::instance()->getStockContractByID(msg_ptr->m_order_ptr->stock_area_, msg_ptr->m_order_ptr->contract_id_);
			msg_ptr->setResult(Err_Succeed);
			ptr->sendMessageInter(msg_ptr);
		}
		msg_ptr->m_blast = true;
		ptr->sendMessageInter(msg_ptr);
	}

	void AsyncQryService::qryCurrentMarginTrade(const ReplyCurrentMarginTradeQryMsgPtr& msg_ptr)
	{
		TCPImpl* ptr = msg_ptr->getTCPImpl();
		TradeAccountPtr item_ptr = std::dynamic_pointer_cast<TradeAccount>(AllTrade::NPMgrCenter::IManagerCenter::instance()->getAccountByLoginName(msg_ptr->m_rtn_acc->login_name_));
		if (!item_ptr)
		{
			ptr->sendMessageInter(ReplyMsg::getReply(Error_User_Unexist, msg_ptr->getSocketID(), msg_ptr->getCmdCode()));
			return;
		}
		msg_ptr->m_rtn_acc = item_ptr;

		SAccountPtr parent_ptr = AllTrade::NPMgrCenter::IManagerCenter::instance()->getAccountByID(msg_ptr->m_rtn_acc->parent_id_);
		if (!parent_ptr)
		{
			ptr->sendMessageInter(ReplyMsg::getReply(Error_User_Parent_Unexist, msg_ptr->getSocketID(), msg_ptr->getCmdCode()));
			return;
		}
		strncpy_s(msg_ptr->m_parent_login_name, parent_ptr->login_name_, sizeof(msg_ptr->m_parent_login_name) - 1);

		// 待处理 ××××××××××××××××××××××××××××××××
		std::vector<TradeInfoPtr> pos_vec; //= AllTrade::NPTradeCenter::ITradeCenter::instance()->getTradeList(item_ptr->user_id_);
		for (auto& item : pos_vec)
		{
			msg_ptr->m_trade_ptr = std::dynamic_pointer_cast<StockTradeInfo>(item);
			if (msg_ptr->m_trade_ptr)
				msg_ptr->m_stock_ptr = AllTrade::NPMgrCenter::IManagerCenter::instance()->getStockContractByID(msg_ptr->m_trade_ptr->stock_area_, msg_ptr->m_trade_ptr->contract_id_);
			msg_ptr->setResult(Err_Succeed);
			ptr->sendMessageInter(msg_ptr);
		}
		msg_ptr->m_blast = true;
		ptr->sendMessageInter(msg_ptr);
	}

}