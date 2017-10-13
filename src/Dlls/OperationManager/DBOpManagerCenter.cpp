#include <assert.h>
#include <sstream>
#include <mutex>
#include "DBOpManagerCenter.h"
#include "define/struct_extern.h"
#include "include/DBAccess/db_access.h"
#include "define/table_define.h"

#include "C:/ng_tools/ng_header_for_log4cxx/ng_header_for_log4cxx.hpp"
#include "C:/ng_tools/ng_header_for_log4cxx/ng_header_for_log4cxx_log_var.hpp"
NG_LOGGER(logger, "DBOpManagerCenter");

#include <cctype>  
#include <algorithm> 

using namespace AllTrade;
using namespace AllTrade::NPTradeCenter;
using namespace AllTrade::NPMgrCenter;
using namespace DBAccess;

namespace OperationManager{

    DBOpManagerCenter::DBOpManagerCenter()
    {

    }

    DBOpManagerCenter::~DBOpManagerCenter()
    {

    }

    bool DBOpManagerCenter::initAllTable()
    {
        InsertVersionTable();
        bool bl = createManagerUsers()
            && createTraderUsers()
            && createAgencyUsers()
            && createFunderUsers()
            && createExchanges()
            && createStockContract()
            && createStockMoney()
            && createStockMoneyDetail()
            && createStockRisk()
            && createApplyMoney()
			&& createVersionTable()
            && createLoginInOutInfo()
            && createCustomStock()
            && createAccountGlobalData()
            && createAgencyCommiss()
            && createAgencyProfit()
			

			&& createInterestStatisticsTable()
			&& createInterestDetailTable();
        return bl;
    }

    bool DBOpManagerCenter::getRootAccount(AllTrade::NPMgrCenter::RootAccountPtr& root_ptr)
    {
        assert(!root_ptr);
        CDBHandler *phandler = AllocDBHandler();
        if (!phandler)
            return false;

        HxSqlRes res = NULL;
        int errCode = 0;
        int recNum = 0;

        std::stringstream sstr;
        sstr << "SELECT * FROM " << gszManagerUserTableName
            << " WHERE " << gszManagerUserColName[MgrUT_AccountProp] << "=" << E_ACCOUNT_PROP::EAP_Root;

        errCode = phandler->QuerySql(sstr.str().c_str(), res, true);
        if (errCode != 0)
            LOG4CXX_ERROR(logger, "获取超级帐户信息失败!"LOG_NOVAR(sstr.str().c_str()));

        if (errCode == 0 && res)
        {
            HxResRow row = NULL;
            if (row = phandler->FetchRow(res))
            {
                root_ptr = std::make_shared<RootAccount>();
                char *pchar;
                strncpy_s(root_ptr->user_id_, phandler->FetchField(row, MgrUT_UserID), sizeof(root_ptr->user_id_) - 1);
                strncpy_s(root_ptr->create_id_, phandler->FetchField(row, MgrUT_CreatorID), sizeof(root_ptr->create_id_) - 1);
                strncpy_s(root_ptr->parent_id_, phandler->FetchField(row, MgrUT_ParentID), sizeof(root_ptr->parent_id_) - 1);
                strncpy_s(root_ptr->login_name_, phandler->FetchField(row, MgrUT_LoginName), sizeof(root_ptr->login_name_) - 1);
                strncpy_s(root_ptr->nick_name_, phandler->FetchField(row, MgrUT_NickName), sizeof(root_ptr->nick_name_) - 1);
                strncpy_s(root_ptr->password_, phandler->FetchField(row, MgrUT_Password), sizeof(root_ptr->password_) - 1);
                strncpy_s(root_ptr->account_name_, phandler->FetchField(row, MgrUT_AccountName), sizeof(root_ptr->account_name_) - 1);
                strncpy_s(root_ptr->agent_link_, phandler->FetchField(row, MgrUT_PopularizeLink), sizeof(root_ptr->agent_link_) - 1);
                strncpy_s(root_ptr->real_name_, phandler->FetchField(row, MgrUT_RealName), sizeof(root_ptr->real_name_) - 1);
                strncpy_s(root_ptr->phone_number_, phandler->FetchField(row, MgrUT_PhoneNumber), sizeof(root_ptr->phone_number_) - 1);
                strncpy_s(root_ptr->identity_, phandler->FetchField(row, MgrUT_IdentityID), sizeof(root_ptr->identity_) - 1);
                strncpy_s(root_ptr->regist_datetime_, phandler->FetchField(row, MgrUT_RegistDatetime), sizeof(root_ptr->regist_datetime_) - 1);
                strncpy_s(root_ptr->update_datetime_, phandler->FetchField(row, MgrUT_UpdateDatetime), sizeof(root_ptr->update_datetime_) - 1);
                strncpy_s(root_ptr->vaild_datetime_, phandler->FetchField(row, MgrUT_VaildDatetime), sizeof(root_ptr->vaild_datetime_) - 1);

                pchar = phandler->FetchField(row, MgrUT_Level);
                root_ptr->level_ = atoi(pchar);
                pchar = phandler->FetchField(row, MgrUT_AccountProp);
                root_ptr->prop_ = (E_ACCOUNT_PROP)(atoi(pchar));
                pchar = phandler->FetchField(row, MgrUT_AccountType);
                root_ptr->type_ = (E_ACCOUNT_TYPE)(atoi(pchar));
                pchar = phandler->FetchField(row, MgrUT_AccountStatus);
                root_ptr->status_ = (E_ACCOUNT_STATUS)(atoi(pchar));
                pchar = phandler->FetchField(row, MgrUT_PermissionType);
                root_ptr->permission_ = (E_PERMISSION_TYPE)(atoi(pchar));
//                 pchar = phandler->FetchField(row, MgrUT_MgrProp);
//                 root_ptr->mgr_prop_ = (E_AGENCY_PROP)(atoi(pchar));
                pchar = phandler->FetchField(row, MgrUT_AllowMaxLevel);
                root_ptr->allow_max_level_ = atoi(pchar);
                pchar = phandler->FetchField(row, MgrUT_AllowMaxNum);
                root_ptr->allow_max_num_ = atoi(pchar);
            }
        }

        phandler->ReleaseRecords(res);
        DBAccess::FreeDBHandler(phandler);
        return errCode == 0;
    }

    bool DBOpManagerCenter::getAllDirectChildren(std::vector<SAccountPtr>& children, const SAccountPtr& account_ptr)
    {
        return getMonitChildren(children, account_ptr) && getAgencyChildren(children, account_ptr) && getTradeChildren(children, account_ptr) && getFunderChildren(children, account_ptr);
    }

    bool DBOpManagerCenter::getMonitChildren(std::vector<SAccountPtr>& children, const SAccountPtr& account_ptr)
    {
        CDBHandler *phandler = AllocDBHandler();
        if (!phandler)
            return false;

        HxSqlRes res = NULL;
        int errCode = 0;
        int recNum = 0;

        std::stringstream sstr;
        sstr << "SELECT * FROM " << gszManagerUserTableName
            << " WHERE " << gszManagerUserColName[MgrUT_ParentID] << "='" << account_ptr->user_id_ << "';";

        std::string tmp_str = sstr.str();
        errCode = phandler->QuerySql(sstr.str().c_str(), res, true);
        if (errCode != 0)
            LOG4CXX_ERROR(logger, "获取监管帐户信息失败!"LOG_NOVAR(sstr.str().c_str()));

        if (errCode == 0 && res)
        {
            HxResRow row = NULL;

            while (row = phandler->FetchRow(res))
            {
                SAccountPtr new_acc_ptr(nullptr);
                char *pchar;
                pchar = phandler->FetchField(row, MgrUT_AccountProp);
                switch ((E_ACCOUNT_PROP)(atoi(pchar)))
                {
                case AllTrade::EAP_Risker:
                    new_acc_ptr = std::make_shared<RiskAccount>();
                    break;
                case AllTrade::EAP_Manager:
                    new_acc_ptr = std::make_shared<ManagerAccount>();
                    break;
                default:
//                    assert(0);
                    break;
                };

                strncpy_s(new_acc_ptr->user_id_, phandler->FetchField(row, MgrUT_UserID), sizeof(new_acc_ptr->user_id_) - 1);
                strncpy_s(new_acc_ptr->create_id_, phandler->FetchField(row, MgrUT_CreatorID), sizeof(new_acc_ptr->create_id_) - 1);
                strncpy_s(new_acc_ptr->parent_id_, phandler->FetchField(row, MgrUT_ParentID), sizeof(new_acc_ptr->parent_id_) - 1);
                strncpy_s(new_acc_ptr->login_name_, phandler->FetchField(row, MgrUT_LoginName), sizeof(new_acc_ptr->login_name_) - 1);
                strncpy_s(new_acc_ptr->nick_name_, phandler->FetchField(row, MgrUT_NickName), sizeof(new_acc_ptr->nick_name_) - 1);
                strncpy_s(new_acc_ptr->password_, phandler->FetchField(row, MgrUT_Password), sizeof(new_acc_ptr->password_) - 1);
                strncpy_s(new_acc_ptr->account_name_, phandler->FetchField(row, MgrUT_AccountName), sizeof(new_acc_ptr->account_name_) - 1);
                strncpy_s(new_acc_ptr->agent_link_, phandler->FetchField(row, MgrUT_PopularizeLink), sizeof(new_acc_ptr->agent_link_) - 1);
                strncpy_s(new_acc_ptr->real_name_, phandler->FetchField(row, MgrUT_RealName), sizeof(new_acc_ptr->real_name_) - 1);
                strncpy_s(new_acc_ptr->phone_number_, phandler->FetchField(row, MgrUT_PhoneNumber), sizeof(new_acc_ptr->phone_number_) - 1);
                strncpy_s(new_acc_ptr->identity_, phandler->FetchField(row, MgrUT_IdentityID), sizeof(new_acc_ptr->identity_) - 1);
                strncpy_s(new_acc_ptr->regist_datetime_, phandler->FetchField(row, MgrUT_RegistDatetime), sizeof(new_acc_ptr->regist_datetime_) - 1);
                strncpy_s(new_acc_ptr->update_datetime_, phandler->FetchField(row, MgrUT_UpdateDatetime), sizeof(new_acc_ptr->update_datetime_) - 1);
                strncpy_s(new_acc_ptr->vaild_datetime_, phandler->FetchField(row, MgrUT_VaildDatetime), sizeof(new_acc_ptr->vaild_datetime_) - 1);

                pchar = phandler->FetchField(row, MgrUT_Level);
                new_acc_ptr->level_ = atoi(pchar);
                pchar = phandler->FetchField(row, MgrUT_AccountProp);
                new_acc_ptr->prop_ = (E_ACCOUNT_PROP)(atoi(pchar));
                pchar = phandler->FetchField(row, MgrUT_AccountType);
                new_acc_ptr->type_ = (E_ACCOUNT_TYPE)(atoi(pchar));
                pchar = phandler->FetchField(row, MgrUT_AccountStatus);
                new_acc_ptr->status_ = (E_ACCOUNT_STATUS)(atoi(pchar));
                pchar = phandler->FetchField(row, MgrUT_PermissionType);
                new_acc_ptr->permission_ = (E_PERMISSION_TYPE)(atoi(pchar));
                children.push_back(new_acc_ptr);
            }
        }

        phandler->ReleaseRecords(res);
        DBAccess::FreeDBHandler(phandler);
        return errCode == 0;
    }

    bool DBOpManagerCenter::getAgencyChildren(std::vector<AllTrade::NPMgrCenter::SAccountPtr>& children, const AllTrade::NPMgrCenter::SAccountPtr& account_ptr)
    {
        CDBHandler *phandler = AllocDBHandler();
        if (!phandler)
            return false;

        HxSqlRes res = NULL;
        int errCode = 0;
        int recNum = 0;

        std::stringstream sstr;
        sstr << "SELECT * FROM " << gszAgencyUserTableName
            << " WHERE " << gszAgencyUserColName[AgyUT_ParentID] << "='" << account_ptr->user_id_ << "';";

        std::string tmp_str = sstr.str();
        errCode = phandler->QuerySql(sstr.str().c_str(), res, true);
        if (errCode != 0)
            LOG4CXX_ERROR(logger, "获取机构帐户信息失败!"LOG_NOVAR(sstr.str().c_str()));

        if (errCode == 0 && res)
        {
            HxResRow row = NULL;

            while (row = phandler->FetchRow(res))
            {
                char *pchar;

                AgencyAccountPtr new_acc_ptr = std::make_shared<AgencyAccount>();
                pchar = phandler->FetchField(row, AgyUT_AllowMaxLevel);
                new_acc_ptr->allow_max_level_ = atoi(pchar);
                pchar = phandler->FetchField(row, AgyUT_AllowMaxNum);
                new_acc_ptr->allow_max_num_ = atoi(pchar);

                strncpy_s(new_acc_ptr->user_id_, phandler->FetchField(row, AgyUT_UserID), sizeof(new_acc_ptr->user_id_) - 1);
                strncpy_s(new_acc_ptr->create_id_, phandler->FetchField(row, AgyUT_CreatorID), sizeof(new_acc_ptr->create_id_) - 1);
                strncpy_s(new_acc_ptr->parent_id_, phandler->FetchField(row, AgyUT_ParentID), sizeof(new_acc_ptr->parent_id_) - 1);
                strncpy_s(new_acc_ptr->fund_user_id_, phandler->FetchField(row, AgyUT_FunderID), sizeof(new_acc_ptr->fund_user_id_) - 1);
                strncpy_s(new_acc_ptr->login_name_, phandler->FetchField(row, AgyUT_LoginName), sizeof(new_acc_ptr->login_name_) - 1);
                strncpy_s(new_acc_ptr->nick_name_, phandler->FetchField(row, AgyUT_NickName), sizeof(new_acc_ptr->nick_name_) - 1);
                strncpy_s(new_acc_ptr->password_, phandler->FetchField(row, AgyUT_Password), sizeof(new_acc_ptr->password_) - 1);
                strncpy_s(new_acc_ptr->account_name_, phandler->FetchField(row, AgyUT_AccountName), sizeof(new_acc_ptr->account_name_) - 1);
                strncpy_s(new_acc_ptr->agent_link_, phandler->FetchField(row, AgyUT_PopularizeLink), sizeof(new_acc_ptr->agent_link_) - 1);
                strncpy_s(new_acc_ptr->real_name_, phandler->FetchField(row, AgyUT_RealName), sizeof(new_acc_ptr->real_name_) - 1);
                strncpy_s(new_acc_ptr->phone_number_, phandler->FetchField(row, AgyUT_PhoneNumber), sizeof(new_acc_ptr->phone_number_) - 1);
                strncpy_s(new_acc_ptr->identity_, phandler->FetchField(row, AgyUT_IdentityID), sizeof(new_acc_ptr->identity_) - 1);
                strncpy_s(new_acc_ptr->regist_datetime_, phandler->FetchField(row, AgyUT_RegistDatetime), sizeof(new_acc_ptr->regist_datetime_) - 1);
                strncpy_s(new_acc_ptr->update_datetime_, phandler->FetchField(row, AgyUT_UpdateDatetime), sizeof(new_acc_ptr->update_datetime_) - 1);
                strncpy_s(new_acc_ptr->vaild_datetime_, phandler->FetchField(row, AgyUT_VaildDatetime), sizeof(new_acc_ptr->vaild_datetime_) - 1);

                pchar = phandler->FetchField(row, AgyUT_Level);
                new_acc_ptr->level_ = atoi(pchar);
                new_acc_ptr->prop_ = E_ACCOUNT_PROP::EAP_Agency;
                pchar = phandler->FetchField(row, AgyUT_AccountType);
                new_acc_ptr->type_ = (E_ACCOUNT_TYPE)(atoi(pchar));
                pchar = phandler->FetchField(row, AgyUT_AccountStatus);
                new_acc_ptr->status_ = (E_ACCOUNT_STATUS)(atoi(pchar));
                pchar = phandler->FetchField(row, AgyUT_PermissionType);
                new_acc_ptr->permission_ = (E_PERMISSION_TYPE)(atoi(pchar));
                pchar = phandler->FetchField(row, AgyUT_AgyProp);
                new_acc_ptr->agency_prop_ = (E_AGENCY_PROP)(atoi(pchar));
                children.push_back(new_acc_ptr);
            }
        }
        phandler->ReleaseRecords(res);
        DBAccess::FreeDBHandler(phandler);
        return errCode == 0;
    }

    bool DBOpManagerCenter::getTradeChildren(std::vector<AllTrade::NPMgrCenter::SAccountPtr>& children, const AllTrade::NPMgrCenter::SAccountPtr& account_ptr)
    {
        CDBHandler *phandler = AllocDBHandler();
        if (!phandler)
            return false;

        HxSqlRes res = NULL;
        int errCode = 0;
        int recNum = 0;

        std::stringstream sstr;
        sstr << "SELECT * FROM " << gszTradeUserTableName
            << " WHERE " << gszTradeUserColName[TUT_ParentID] << "='" << account_ptr->user_id_ << "'";

        std::string tmp_str = sstr.str();
        errCode = phandler->QuerySql(sstr.str().c_str(), res, true);
        if (errCode != 0)
            LOG4CXX_ERROR(logger, "获取交易帐户信息失败!"LOG_NOVAR(sstr.str().c_str()));

        if (errCode == 0 && res)
        {
            HxResRow row = NULL;

            while (row = phandler->FetchRow(res))
            {
                SAccountPtr new_acc_ptr(nullptr);
                char *pchar;
                pchar = phandler->FetchField(row, TUT_AccountProp);
                switch ((E_ACCOUNT_PROP)(atoi(pchar)))
                {
                case AllTrade::EAP_Trader:
                {
                    TradeAccountPtr new_acc_tmp_ptr = std::make_shared<TradeAccount>();
                    strncpy_s(new_acc_tmp_ptr->fund_user_id_, phandler->FetchField(row, TUT_FunderID), sizeof(new_acc_tmp_ptr->fund_user_id_) - 1);
                    new_acc_ptr = new_acc_tmp_ptr;
                }
                    break;
                default:
                    assert(0);
                    break;
                };

                strncpy_s(new_acc_ptr->user_id_, phandler->FetchField(row, TUT_UserID), sizeof(new_acc_ptr->user_id_) - 1);
                strncpy_s(new_acc_ptr->create_id_, phandler->FetchField(row, TUT_CreatorID), sizeof(new_acc_ptr->create_id_) - 1);
                strncpy_s(new_acc_ptr->parent_id_, phandler->FetchField(row, TUT_ParentID), sizeof(new_acc_ptr->parent_id_) - 1);
                strncpy_s(new_acc_ptr->login_name_, phandler->FetchField(row, TUT_LoginName), sizeof(new_acc_ptr->login_name_) - 1);
                strncpy_s(new_acc_ptr->nick_name_, phandler->FetchField(row, TUT_NickName), sizeof(new_acc_ptr->nick_name_) - 1);
                strncpy_s(new_acc_ptr->password_, phandler->FetchField(row, TUT_Password), sizeof(new_acc_ptr->password_) - 1);
                strncpy_s(new_acc_ptr->account_name_, phandler->FetchField(row, TUT_AccountName), sizeof(new_acc_ptr->account_name_) - 1);
                strncpy_s(new_acc_ptr->agent_link_, phandler->FetchField(row, TUT_PopularizeLink), sizeof(new_acc_ptr->agent_link_) - 1);
                strncpy_s(new_acc_ptr->real_name_, phandler->FetchField(row, TUT_RealName), sizeof(new_acc_ptr->real_name_) - 1);
                strncpy_s(new_acc_ptr->phone_number_, phandler->FetchField(row, TUT_PhoneNumber), sizeof(new_acc_ptr->phone_number_) - 1);
                strncpy_s(new_acc_ptr->identity_, phandler->FetchField(row, TUT_IdentityID), sizeof(new_acc_ptr->identity_) - 1);
                strncpy_s(new_acc_ptr->regist_datetime_, phandler->FetchField(row, TUT_RegistDatetime), sizeof(new_acc_ptr->regist_datetime_) - 1);
                strncpy_s(new_acc_ptr->update_datetime_, phandler->FetchField(row, TUT_UpdateDatetime), sizeof(new_acc_ptr->update_datetime_) - 1);
                strncpy_s(new_acc_ptr->vaild_datetime_, phandler->FetchField(row, TUT_VaildDatetime), sizeof(new_acc_ptr->vaild_datetime_) - 1);

                pchar = phandler->FetchField(row, TUT_Level);
                new_acc_ptr->level_ = atoi(pchar);
                pchar = phandler->FetchField(row, TUT_AccountProp);
                new_acc_ptr->prop_ = (E_ACCOUNT_PROP)(atoi(pchar));
                pchar = phandler->FetchField(row, TUT_AccountType);
                new_acc_ptr->type_ = (E_ACCOUNT_TYPE)(atoi(pchar));
                pchar = phandler->FetchField(row, TUT_AccountStatus);
                new_acc_ptr->status_ = (E_ACCOUNT_STATUS)(atoi(pchar));
                pchar = phandler->FetchField(row, TUT_PermissionType);

				strncpy_s(new_acc_ptr->auditor_name_, phandler->FetchField(row, TUT_AuditorName), sizeof(new_acc_ptr->auditor_name_) - 1);
				strncpy_s(new_acc_ptr->auditor_datetime_, phandler->FetchField(row, TUT_VaildDatetime), sizeof(new_acc_ptr->auditor_datetime_) - 1);
				
                children.push_back(new_acc_ptr);
            }
        }

        phandler->ReleaseRecords(res);
        DBAccess::FreeDBHandler(phandler);
        return errCode == 0;
    }

    bool DBOpManagerCenter::getFunderChildren(std::vector<AllTrade::NPMgrCenter::SAccountPtr>& children, const AllTrade::NPMgrCenter::SAccountPtr& account_ptr)
    {
        CDBHandler *phandler = AllocDBHandler();
        if (!phandler)
            return false;

        HxSqlRes res = NULL;
        int errCode = 0;
        int recNum = 0;

        std::stringstream sstr;
        sstr << "SELECT * FROM " << gszFunderUserTableName
            << " WHERE " << gszFunderUserColName[FUT_ParentID] << "='" << account_ptr->user_id_ << "'";

        std::string tmp_str = sstr.str();
        errCode = phandler->QuerySql(sstr.str().c_str(), res, true);
        if (errCode != 0)
            LOG4CXX_ERROR(logger, "获取资金帐户信息失败!"LOG_NOVAR(sstr.str().c_str()));

        if (errCode == 0 && res)
        {
            HxResRow row = NULL;

            while (row = phandler->FetchRow(res))
            {
                char *pchar;
                pchar = phandler->FetchField(row, FUT_AccountProp);

                FunderAccountPtr new_acc_ptr = std::make_shared<FunderAccount>();
                strncpy_s(new_acc_ptr->user_id_, phandler->FetchField(row, FUT_UserID), sizeof(new_acc_ptr->user_id_) - 1);
                strncpy_s(new_acc_ptr->create_id_, phandler->FetchField(row, FUT_CreatorID), sizeof(new_acc_ptr->create_id_) - 1);
                strncpy_s(new_acc_ptr->parent_id_, phandler->FetchField(row, FUT_ParentID), sizeof(new_acc_ptr->parent_id_) - 1);
                strncpy_s(new_acc_ptr->login_name_, phandler->FetchField(row, FUT_LoginName), sizeof(new_acc_ptr->login_name_) - 1);
                strncpy_s(new_acc_ptr->nick_name_, phandler->FetchField(row, FUT_NickName), sizeof(new_acc_ptr->nick_name_) - 1);
                strncpy_s(new_acc_ptr->password_, phandler->FetchField(row, FUT_Password), sizeof(new_acc_ptr->password_) - 1);
                strncpy_s(new_acc_ptr->account_name_, phandler->FetchField(row, FUT_AccountName), sizeof(new_acc_ptr->account_name_) - 1);
                strncpy_s(new_acc_ptr->agent_link_, phandler->FetchField(row, FUT_PopularizeLink), sizeof(new_acc_ptr->agent_link_) - 1);
                strncpy_s(new_acc_ptr->real_name_, phandler->FetchField(row, FUT_RealName), sizeof(new_acc_ptr->real_name_) - 1);
                strncpy_s(new_acc_ptr->phone_number_, phandler->FetchField(row, FUT_PhoneNumber), sizeof(new_acc_ptr->phone_number_) - 1);
                strncpy_s(new_acc_ptr->identity_, phandler->FetchField(row, FUT_IdentityID), sizeof(new_acc_ptr->identity_) - 1);
                strncpy_s(new_acc_ptr->fund_company_, phandler->FetchField(row, FUT_FunderCompany), sizeof(new_acc_ptr->fund_company_) - 1);
                strncpy_s(new_acc_ptr->regist_datetime_, phandler->FetchField(row, FUT_RegistDatetime), sizeof(new_acc_ptr->regist_datetime_) - 1);
                strncpy_s(new_acc_ptr->update_datetime_, phandler->FetchField(row, FUT_UpdateDatetime), sizeof(new_acc_ptr->update_datetime_) - 1);
                strncpy_s(new_acc_ptr->vaild_datetime_, phandler->FetchField(row, FUT_VaildDatetime), sizeof(new_acc_ptr->vaild_datetime_) - 1);

                pchar = phandler->FetchField(row, FUT_Level);
                new_acc_ptr->level_ = atoi(pchar);
                pchar = phandler->FetchField(row, FUT_AccountProp);
                new_acc_ptr->prop_ = (E_ACCOUNT_PROP)(atoi(pchar));
                pchar = phandler->FetchField(row, FUT_AccountType);
                new_acc_ptr->type_ = (E_ACCOUNT_TYPE)(atoi(pchar));
                pchar = phandler->FetchField(row, FUT_AccountStatus);
                new_acc_ptr->status_ = (E_ACCOUNT_STATUS)(atoi(pchar));
                pchar = phandler->FetchField(row, FUT_PermissionType);
                children.push_back(new_acc_ptr);
            }
        }

        phandler->ReleaseRecords(res);
        DBAccess::FreeDBHandler(phandler);
        return errCode == 0;
    }

    bool DBOpManagerCenter::getUserMoneyInfo(const AllTrade::UserIDType user_id, AllTrade::NPMgrCenter::SMoneyInfoPtr& money_info)
    {
        CDBHandler *phandler = AllocDBHandler();
        if (!phandler)
            return false;

        HxSqlRes res = NULL;
        int errCode = 0;
        int recNum = 0;

        std::stringstream sstr;
        sstr << "SELECT * FROM " << gszMoneyTableName
            << " WHERE " << gszMoneyColName[MnyT_UserID] << " = '" << user_id << "';";

        std::string tmp = sstr.str();
        errCode = phandler->QuerySql(sstr.str().c_str(), res, true);
        if (errCode != 0)
            LOG4CXX_ERROR(logger, "获取账户资金信息失败!"LOG_NOVAR(sstr.str().c_str()));

        money_info = std::make_shared<SMoneyInfo>();
        if (errCode == 0 && res)
        {
            HxResRow row = NULL;
            if (row = phandler->FetchRow(res))
            {
                char *pchar;
                pchar = phandler->FetchField(row, MnyT_PositionCostPrice);
                money_info->position_cost_price_ = atof(pchar);
                pchar = phandler->FetchField(row, MnyT_PositionVolume);
                money_info->position_all_vol_ = atoi(pchar);
                pchar = phandler->FetchField(row, MnyT_TradingFee);
                money_info->trading_fee_ = atof(pchar);
                pchar = phandler->FetchField(row, MnyT_CustomizeFee);
                money_info->customize_fee_ = atof(pchar);
                pchar = phandler->FetchField(row, MnyT_LogicCanExtract);
                money_info->logic_can_extract_ = atof(pchar);
                pchar = phandler->FetchField(row, MnyT_LogicWaitThaw);
                money_info->logic_wait_thaw_ = atof(pchar);
                pchar = phandler->FetchField(row, MnyT_OrderFreeze);
                money_info->order_freeze_ = atof(pchar);
                pchar = phandler->FetchField(row, MnyT_UserDeposit);
                money_info->user_deposit_ = atof(pchar);
                pchar = phandler->FetchField(row, MnyT_PriorityFund);
                money_info->priority_fund_ = atof(pchar);
            }
        }

        phandler->ReleaseRecords(res);
        DBAccess::FreeDBHandler(phandler);
        return errCode == 0;
    }

    bool DBOpManagerCenter::getUserRiskInfo(const UserIDType user_id, AllTrade::NPMgrCenter::SRiskInfoPtr& risk_info)
    {
        CDBHandler *phandler = AllocDBHandler();
        if (!phandler)
            return false;

        HxSqlRes res = NULL;
        int errCode = 0;
        int recNum = 0;

        std::stringstream sstr;
        sstr << "SELECT * FROM " << gszRiskTableName
            << " WHERE " << gszRiskColName[RiskT_UserID] << " = '" << user_id << "';";

        std::string tmp = sstr.str();
        errCode = phandler->QuerySql(sstr.str().c_str(), res, true);
        if (errCode != 0)
            LOG4CXX_ERROR(logger, "获取账户风控信息失败!"LOG_NOVAR(sstr.str().c_str()));

        risk_info = std::make_shared<SRiskInfo>();
        if (errCode == 0 && res)
        {
            HxResRow row = NULL;
            if (row = phandler->FetchRow(res))
            {
                char *pchar;
                pchar = phandler->FetchField(row, RiskT_WarningLine);
                risk_info->warningline_ = atof(pchar);
                pchar = phandler->FetchField(row, RiskT_ForceLine);
                risk_info->forceline_ = atof(pchar);
                pchar = phandler->FetchField(row, RiskT_LimitLine);
                risk_info->limitline_ = atof(pchar);
                pchar = phandler->FetchField(row, RiskT_LeverRate);
                risk_info->lever_rate_ = atof(pchar);
                pchar = phandler->FetchField(row, RiskT_CommissionRate);
                risk_info->commissionrate_ = atof(pchar);
                pchar = phandler->FetchField(row, RiskT_Custom_Commissionrate);
                risk_info->custom_commissionrate_ = atof(pchar);
                pchar = phandler->FetchField(row, RiskT_Procommrate);
                risk_info->procommrate_ = atof(pchar);
            }
        }

        phandler->ReleaseRecords(res);
        DBAccess::FreeDBHandler(phandler);
        return errCode == 0;
    }

    bool DBOpManagerCenter::getAllExchange(std::vector<AllTrade::NPMgrCenter::SExchangePtr>& exchanges)
    {
        CDBHandler *phandler = AllocDBHandler();
        if (!phandler)
            return false;

        HxSqlRes res = NULL;
        int errCode = 0;
        int recNum = 0;

        std::stringstream sstr;
        sstr << "SELECT * FROM " << gszExchangeTableName;

        std::string tmp = sstr.str();
        errCode = phandler->QuerySql(sstr.str().c_str(), res, true);
        if (errCode != 0)
            LOG4CXX_ERROR(logger, "获取交易所信息失败!"LOG_NOVAR(sstr.str().c_str()));

        if (errCode == 0 && res)
        {
            HxResRow row = NULL;
            while (row = phandler->FetchRow(res))
            {
                SExchangePtr ex_ptr = std::make_shared<SExchange>();
                char *pchar;
                strncpy_s(ex_ptr->exchange_id_, phandler->FetchField(row, ExT_ExchangeID), sizeof(ex_ptr->exchange_id_) - 1);
                strncpy_s(ex_ptr->exchange_name_, phandler->FetchField(row, ExT_ExchangeName), sizeof(ex_ptr->exchange_name_) - 1);
                strncpy_s(ex_ptr->exchange_code_, phandler->FetchField(row, ExT_ExchangeCode), sizeof(ex_ptr->exchange_code_) - 1);

                // 可交易时间段
                std::string tradable_times = phandler->FetchField(row, ExT_TradeTime);
                size_t lastpos_d(0);
                size_t pos_d(tradable_times.find(";"));
                while (pos_d != std::string::npos)
                {
                    int pos_q(tradable_times.find("-", lastpos_d));
                    assert(pos_q != std::string::npos);
                    if (pos_q == std::string::npos)
                        LOG4CXX_ERROR(logger, "交易所可交易时间设置有误!!!");

                    TimePeriod tmp_time_period;
                    strncpy_s(tmp_time_period.start_time_, tradable_times.substr(lastpos_d, pos_q - lastpos_d).c_str(), sizeof(tmp_time_period.start_time_) - 1);
                    strncpy_s(tmp_time_period.end_time_, tradable_times.substr(pos_q + 1, pos_d - pos_q - 1).c_str(), sizeof(tmp_time_period.end_time_) - 1);
                    ex_ptr->tradable_time_.push_back(tmp_time_period);
                    lastpos_d = pos_d + 1;
                    pos_d = tradable_times.find(";", lastpos_d);
                }

                // 可提交委托时间
                std::string orderable_times = phandler->FetchField(row, ExT_OrderTime);
                size_t pos_q_od(orderable_times.find("-"));
                assert(pos_q_od != std::string::npos);
                if (pos_q_od == std::string::npos)
                    LOG4CXX_ERROR(logger, "交易所可提交委托时间设置有误!!!");

                strncpy_s(ex_ptr->orderable_time_.start_time_, orderable_times.substr(0, pos_q_od).c_str(), sizeof(ex_ptr->orderable_time_.start_time_) - 1);
                strncpy_s(ex_ptr->orderable_time_.end_time_, orderable_times.substr(pos_q_od + 1).c_str(), sizeof(ex_ptr->orderable_time_.end_time_) - 1);

                pchar = phandler->FetchField(row, ExT_CommodityType);
                ex_ptr->commodity_type_ = (CommodityTypeType)atoi(pchar);
                exchanges.push_back(ex_ptr);
            }
        }

        phandler->ReleaseRecords(res);
        DBAccess::FreeDBHandler(phandler);
        return errCode == 0;
    }

    bool DBOpManagerCenter::getStockAllContract(std::vector<AllTrade::NPMgrCenter::SStockContractPtr>& contract_vec, const ExchangeIDType exchange_id)
    {
        CDBHandler *phandler = AllocDBHandler();
        if (!phandler)
            return false;

        HxSqlRes res = NULL;
        int errCode = 0;
        int recNum = 0;

        std::stringstream sstr;
        sstr << "SELECT * FROM " << gszStockContractTableName 
            << " WHERE " << gszStockContractColName[SCT_ExchangeID] << " = '" << exchange_id << "';";

        std::string tmp = sstr.str();
        errCode = phandler->QuerySql(sstr.str().c_str(), res, true);
        if (errCode != 0)
            LOG4CXX_ERROR(logger, "获取股票合约信息失败!"LOG_NOVAR(sstr.str().c_str()));

        if (errCode == 0 && res)
        {
            HxResRow row = NULL;
            while (row = phandler->FetchRow(res))
            {
                SStockContractPtr contract_ptr = std::make_shared<SStockContract>();
                char *pchar;
                strncpy_s(contract_ptr->contract_id_, phandler->FetchField(row, SCT_ContractID), sizeof(contract_ptr->contract_id_) - 1);
                strncpy_s(contract_ptr->exchange_id_, phandler->FetchField(row, SCT_ExchangeID), sizeof(contract_ptr->exchange_id_) - 1 - 1);
                strncpy_s(contract_ptr->contract_name_, phandler->FetchField(row, SCT_ContractNmae), sizeof(contract_ptr->contract_name_) - 1);
                strncpy_s(contract_ptr->contract_code_, phandler->FetchField(row, SCT_ContractCode), sizeof(contract_ptr->contract_code_) - 1);
                strncpy_s(contract_ptr->currency_id_, phandler->FetchField(row, SCT_CurrencyID), sizeof(contract_ptr->currency_id_) - 1);
                strncpy_s(contract_ptr->open_datetime_, phandler->FetchField(row, SCT_OpenDateTime), sizeof(contract_ptr->open_datetime_) - 1);
                strncpy_s(contract_ptr->delivery_datetime_, phandler->FetchField(row, SCT_DeliveryDateTime), sizeof(contract_ptr->delivery_datetime_) - 1);
                strncpy_s(contract_ptr->trade_datetime_, phandler->FetchField(row, SCT_TradeDateTime), sizeof(contract_ptr->trade_datetime_) - 1);
                strncpy_s(contract_ptr->display_prop_, phandler->FetchField(row, SCT_DisplayProp), sizeof(contract_ptr->display_prop_) - 1);
                strncpy_s(contract_ptr->plate_prop_, phandler->FetchField(row, SCT_PlateProp), sizeof(contract_ptr->plate_prop_) - 1);

                pchar = phandler->FetchField(row, SCT_LastDays);
                contract_ptr->last_days_ = atoi(pchar);
                pchar = phandler->FetchField(row, SCT_MinPriceChange);
                contract_ptr->min_price_change_ = atof(pchar);
                pchar = phandler->FetchField(row, SCT_Multiplier);
                contract_ptr->contract_multiplier_ = atoi(pchar);
                pchar = phandler->FetchField(row, SCT_OpenFeeFix);
                contract_ptr->open_fee_.bFix_ = atoi(pchar) == 1;
                pchar = phandler->FetchField(row, SCT_OpenFee);
                contract_ptr->open_fee_.fee_ = atof(pchar);
                pchar = phandler->FetchField(row, SCT_CloseYestodayFeeFix);
                contract_ptr->close_yestoday_fee_.bFix_ = atoi(pchar) == 1;
                pchar = phandler->FetchField(row, SCT_CloseYestodayFee);
                contract_ptr->close_yestoday_fee_.fee_ = atof(pchar);
                pchar = phandler->FetchField(row, SCT_MarginFix);
                contract_ptr->margin_fee_.bFix_ = atoi(pchar) == 1;
                pchar = phandler->FetchField(row, SCT_Margin);
                contract_ptr->margin_fee_.fee_ = atof(pchar);

                pchar = phandler->FetchField(row, SCT_CommodityType);
                contract_ptr->commodity_type_ = (CommodityTypeType)atoi(pchar);
                pchar = phandler->FetchField(row, SCT_StockArea);
                contract_ptr->stock_area_ = (StockAreaType)atoi(pchar);
                pchar = phandler->FetchField(row, SCT_DisplayPropType);
                contract_ptr->display_prop_type_ = (DisplayPropTypeType)atoi(pchar);
                pchar = phandler->FetchField(row, SCT_StockPlateArea);
                contract_ptr->stock_plate_area_ = (StockPlateAreaType)atoi(pchar);
                pchar = phandler->FetchField(row, SCT_StockTotalShares);
                contract_ptr->total_shares_ = atof(pchar);

                contract_vec.push_back(contract_ptr);
            }
        }

        phandler->ReleaseRecords(res);
        DBAccess::FreeDBHandler(phandler);
        return errCode == 0;
    }

    bool DBOpManagerCenter::updateUserInfo(const AllTrade::NPMgrCenter::SAccountPtr& account_ptr)
    {
        switch (account_ptr->prop_)
        {
        case AllTrade::EAP_Root:
            return updateSuperMgrUserInfo(std::dynamic_pointer_cast<RootAccount>(account_ptr));
            break;
        case AllTrade::EAP_Agency:
            return updateAgencyUserInfo(std::dynamic_pointer_cast<AgencyAccount>(account_ptr));
            break;
        case AllTrade::EAP_Risker:
            return updateRiskerUserInfo(std::dynamic_pointer_cast<RiskAccount>(account_ptr));
            break;
        case AllTrade::EAP_Manager:
            return updateMonitorUserInfo(std::dynamic_pointer_cast<ManagerAccount>(account_ptr));
            break;
        case AllTrade::EAP_Trader:
            return updateTraderUserInfo(std::dynamic_pointer_cast<TradeAccount>(account_ptr));
            break;
        case AllTrade::EAP_Funder:
            return updateFunderUserInfo(std::dynamic_pointer_cast<FunderAccount>(account_ptr));
            break;
        default:
            assert(0);
            break;
        }
        return false;
    }

    bool DBOpManagerCenter::updateExchangeInfo(const AllTrade::NPMgrCenter::SExchangePtr& exchange_ptr)
    {
        CDBHandler *phandler = AllocDBHandler();
        if (!phandler)
            return false;

        int errCode = 0;

        std::stringstream sstr;
        sstr << "REPLACE INTO " << gszExchangeTableName << " set "
            << gszExchangeColName[ExT_ExchangeID] << " = '" << exchange_ptr->exchange_id_ << "', "
            << gszExchangeColName[ExT_ExchangeName] << " = '" << exchange_ptr->exchange_name_ << "', "
            << gszExchangeColName[ExT_ExchangeCode] << " = '" << exchange_ptr->exchange_code_ << "', "
            << gszExchangeColName[ExT_TradeTime] << " = '09:30:00-11:30:00;13:00:00-15:00:00;', "
            << gszExchangeColName[ExT_OrderTime] << " = '09:15:00-09:30:00', "
            << gszExchangeColName[ExT_CommodityType] << " = " << (int)exchange_ptr->commodity_type_ << "; ";

        errCode = phandler->ExecSql(sstr.str().c_str());
        if (errCode != 0)
            LOG4CXX_ERROR(logger, "更新交易所信息失败!"LOG_NOVAR(sstr.str().c_str()));

        DBAccess::FreeDBHandler(phandler);
        return errCode == 0;
    }

    bool DBOpManagerCenter::updateContractInfo(const AllTrade::NPMgrCenter::SContractPtr& contract_ptr)
    {
        switch (contract_ptr->commodity_type_)
        {
        case AllTrade::CommodityTypeType::COMMODITY_TYPE_STOCK:
            return updateStockContractInfo(std::dynamic_pointer_cast<SStockContract>(contract_ptr));
            break;
        default:
            assert(0);
            break;
        }
        return false;
    }

    bool DBOpManagerCenter::updateUserMoneyDetailInfo(const AllTrade::UserIDType user_id, const AllTrade::NPMgrCenter::SMoneyDetailInfoPtr& money_info)
    {
        CDBHandler *phandler = AllocDBHandler();
        if (!phandler)
            return false;

        int errCode = 0;

        std::stringstream sstr;
        sstr << "REPLACE INTO " << gszMoneyChangeTableName << " set "
            << gszMoneyChangeColName[MnyCT_Stream] << " = '" << money_info->stream_ << "', "
            << gszMoneyChangeColName[MnyCT_UserID] << " = '" << user_id << "', "
            << gszMoneyChangeColName[MnyCT_Before] << " = " << money_info->total_before_ << ", "
            << gszMoneyChangeColName[MnyCT_After] << " = " << money_info->total_after_ << ", "
            << gszMoneyChangeColName[MnyCT_ChangeMoney] << " = " << money_info->change_money_ << ", "
            << gszMoneyChangeColName[MnyCT_Type] << " = " << money_info->change_type_ << ", "
            << gszMoneyChangeColName[MnyCT_Remark] << " = '" << money_info->remark_ << "', "
            << gszMoneyChangeColName[MnyCT_Time] << " = '" << money_info->date_time_ << "'; ";

        errCode = phandler->ExecSql(sstr.str().c_str());
        if (errCode != 0)
            LOG4CXX_ERROR(logger, "更新账户资金流水信息失败!"LOG_NOVAR(sstr.str().c_str()));

        DBAccess::FreeDBHandler(phandler);
        return errCode == 0;
    }

    bool DBOpManagerCenter::updateUserMoneyInfo(const AllTrade::UserIDType user_id, const AllTrade::NPMgrCenter::SMoneyInfoPtr& money_info)
    {
        CDBHandler *phandler = AllocDBHandler();
        if (!phandler)
            return false;

        int errCode = 0;

        std::stringstream sstr;
        sstr << "REPLACE INTO " << gszMoneyTableName << " set "
            << gszMoneyColName[MnyT_UserID] << " = '" << user_id << "', "
            << gszMoneyColName[MnyT_PositionCostPrice] << " = " << money_info->position_cost_price_ << ", "
            << gszMoneyColName[MnyT_PositionVolume] << " = " << money_info->position_all_vol_ << ", "
            << gszMoneyColName[MnyT_TradingFee] << " = " << money_info->trading_fee_ << ", "
            << gszMoneyColName[MnyT_CustomizeFee] << " = " << money_info->customize_fee_ << ", "
            << gszMoneyColName[MnyT_LogicCanExtract] << " = " << money_info->logic_can_extract_ << ", "
            << gszMoneyColName[MnyT_LogicWaitThaw] << " = " << money_info->logic_wait_thaw_ << ", "
            << gszMoneyColName[MnyT_OrderFreeze] << " = " << money_info->order_freeze_ << ", "
            << gszMoneyColName[MnyT_UserDeposit] << " = " << money_info->user_deposit_ << ", "
            << gszMoneyColName[MnyT_PriorityFund] << " = " << money_info->priority_fund_ << "; ";

        errCode = phandler->ExecSql(sstr.str().c_str());
        if (errCode != 0)
            LOG4CXX_ERROR(logger, "更新账户资金信息失败!"LOG_NOVAR(sstr.str().c_str()));

        DBAccess::FreeDBHandler(phandler);
        return errCode == 0;
    }

    bool DBOpManagerCenter::updateUserRiskInfo(const UserIDType user_id, const AllTrade::NPMgrCenter::SRiskInfoPtr& risk_info)
    {
        CDBHandler *phandler = AllocDBHandler();
        if (!phandler)
            return false;

        int errCode = 0;

        std::stringstream sstr;
        sstr << "REPLACE INTO " << gszRiskTableName << " set "
            << gszRiskColName[RiskT_UserID] << " = '" << user_id << "', "
            << gszRiskColName[RiskT_WarningLine] << " = " << risk_info->warningline_ << ", "
            << gszRiskColName[RiskT_ForceLine] << " = " << risk_info->forceline_ << ", "
            << gszRiskColName[RiskT_LimitLine] << " = " << risk_info->limitline_ << ", "
            << gszRiskColName[RiskT_LeverRate] << " = " << risk_info->lever_rate_ << ", "
            << gszRiskColName[RiskT_CommissionRate] << " = " << risk_info->commissionrate_ << ", "
            << gszRiskColName[RiskT_Custom_Commissionrate] << " = " << risk_info->custom_commissionrate_ << ", "
            << gszRiskColName[RiskT_Procommrate] << " = " << risk_info->procommrate_ << "; ";

        errCode = phandler->ExecSql(sstr.str().c_str());
        if (errCode != 0)
            LOG4CXX_ERROR(logger, "更新账户风控信息失败!"LOG_NOVAR(sstr.str().c_str()));

        DBAccess::FreeDBHandler(phandler);
        return errCode == 0;
    }

    bool DBOpManagerCenter::qryApplyMoney(std::vector<SApplyMoneyPtr>& apply_infos, const UserIDType user_id, const DateType start_day, const DateType end_day, AllTrade::OIMM_Change_Type money_type)
    {
        CDBHandler *phandler = AllocDBHandler();
        if (!phandler)
            return false;

        HxSqlRes res = NULL;
        int errCode = 0;
        int recNum = 0;


        switch (money_type)
        {
        case AllTrade::OIMM_In_Equipment:
        {
            std::stringstream sstr;
            sstr << "SELECT * FROM " << gszApplyMoneyTableName << " WHERE "
                << gszApplyMoneyColName[ApplyMoney_UserID] << " = '" << user_id << "' "
                << " AND " << gszApplyMoneyColName[ApplyMoney_DateTime] << " >= '" << start_day << "'"
                << " AND " << gszApplyMoneyColName[ApplyMoney_DateTime] << " <= '" << end_day << "';";

            errCode = phandler->QuerySql(sstr.str().c_str(), res, true);
            if (errCode != 0)
                LOG4CXX_ERROR(logger, "获取资金待审核信息失败!"LOG_NOVAR(sstr.str().c_str()));

            if (errCode == 0 && res)
            {
                HxResRow row = NULL;
                while (row = phandler->FetchRow(res))
                {
                    SApplyMoneyPtr apply_info = std::make_shared<SApplyMoneyInfo>();
                    char *pchar;
                    strncpy_s(apply_info->approval_user_id_, phandler->FetchField(row, ApplyMoney_Approval_UserID), sizeof(apply_info->approval_user_id_) - 1);
                    strncpy_s(apply_info->user_id_, phandler->FetchField(row, ApplyMoney_UserID), sizeof(apply_info->user_id_) - 1);
                    strncpy_s(apply_info->apply_date_time_, phandler->FetchField(row, ApplyMoney_DateTime), sizeof(apply_info->apply_date_time_) - 1);
                    strncpy_s(apply_info->approval_date_time_, phandler->FetchField(row, ApplyMoney_Approval_DateTime), sizeof(apply_info->approval_date_time_) - 1);

                    pchar = phandler->FetchField(row, ApplyMoney_ID);
                    apply_info->apply_money_id_ = atoi(pchar);

                    pchar = phandler->FetchField(row, ApplyMoney_Money);
                    apply_info->apply_money_ = atof(pchar);

                    pchar = phandler->FetchField(row, ApplyMoney_Status);
                    apply_info->apply_status_ = (E_APPLY_MONEY_STATUS)atoi(pchar);

                    apply_info->money_type_ = money_type;

                    apply_infos.push_back(apply_info);
                }
            }

        }
            break;
        case AllTrade::OIMM_In_Deposit:
        {
            std::stringstream sstr;
            sstr << "SELECT * FROM " << gszApplyInMoneyTableName << " WHERE "
                << gszApplyInMoneyColName[AIMT_AccountID] << " = '" << user_id << "' "
                << " AND " << gszApplyInMoneyColName[AIMT_PostTime] << " >= '" << start_day << "'"
                << " AND " << gszApplyInMoneyColName[AIMT_PostTime] << " <= '" << end_day << "'"
                << " AND " << gszApplyInMoneyColName[AIMT_StateID] << " = " << 1 << ";";

            errCode = phandler->QuerySql(sstr.str().c_str(), res, true);
            if (errCode != 0)
                LOG4CXX_ERROR(logger, "获取资金待审核信息失败!"LOG_NOVAR(sstr.str().c_str()));

            if (errCode == 0 && res)
            {
                HxResRow row = NULL;
                while (row = phandler->FetchRow(res))
                {
                    SApplyMoneyPtr apply_info = std::make_shared<SApplyMoneyInfo>();
                    char *pchar;
                    strncpy_s(apply_info->approval_user_id_, phandler->FetchField(row, AIMT_Approval_Userid), sizeof(apply_info->approval_user_id_) - 1);
                    strncpy_s(apply_info->user_id_, phandler->FetchField(row, AIMT_AccountID), sizeof(apply_info->user_id_) - 1);
                    strncpy_s(apply_info->apply_date_time_, phandler->FetchField(row, AIMT_PostTime), sizeof(apply_info->apply_date_time_) - 1);

                    pchar = phandler->FetchField(row, AIMT_SerialNumber);
                    apply_info->apply_money_id_ = atoi(pchar);

                    pchar = phandler->FetchField(row, AIMT_ApprovalTime);
                    if (pchar)
                        strncpy_s(apply_info->approval_date_time_, pchar, sizeof(apply_info->approval_date_time_) - 1);

                    strncpy_s(apply_info->bank_card_, phandler->FetchField(row, AIMT_BankCard), sizeof(apply_info->bank_card_) - 1);
                    strncpy_s(apply_info->bank_name_, phandler->FetchField(row, AIMT_BankName), sizeof(apply_info->bank_name_) - 1);

                    pchar = phandler->FetchField(row, AIMT_Amount);
                    apply_info->apply_money_ = atof(pchar);

                    pchar = phandler->FetchField(row, AIMT_IsApproval);
                    apply_info->apply_status_ = (E_APPLY_MONEY_STATUS)atoi(pchar);

                    apply_info->money_type_ = money_type;

                    apply_infos.push_back(apply_info);
                }
            }

        }
            break;
        case AllTrade::OIMM_Out_Deposit:
        {
            std::stringstream sstr;
            sstr << "SELECT * FROM " << gszApplyOutMoneyTableName << " WHERE "
                << gszApplyOutMoneyColName[AOMT_UserID] << " = '" << user_id << "' "
                << " AND " << gszApplyOutMoneyColName[AOMT_PostTime] << " >= '" << start_day << "'"
                << " AND " << gszApplyOutMoneyColName[AOMT_PostTime] << " <= '" << end_day << "';";

            errCode = phandler->QuerySql(sstr.str().c_str(), res, true);
            if (errCode != 0)
                LOG4CXX_ERROR(logger, "获取资金待审核信息失败!"LOG_NOVAR(sstr.str().c_str()));

            if (errCode == 0 && res)
            {
                HxResRow row = NULL;
                while (row = phandler->FetchRow(res))
                {
                    SApplyMoneyPtr apply_info = std::make_shared<SApplyMoneyInfo>();
                    char *pchar;
                    strncpy_s(apply_info->approval_user_id_, phandler->FetchField(row, AOMT_Approval_Userid), sizeof(apply_info->approval_user_id_) - 1);
                    strncpy_s(apply_info->user_id_, phandler->FetchField(row, AOMT_UserID), sizeof(apply_info->user_id_) - 1);
                    strncpy_s(apply_info->apply_date_time_, phandler->FetchField(row, AOMT_PostTime), sizeof(apply_info->apply_date_time_) - 1);
                    pchar = phandler->FetchField(row, AOMT_ApprovalTime);
                    if (pchar)
                        strncpy_s(apply_info->approval_date_time_, pchar, sizeof(apply_info->approval_date_time_) - 1);

                    strncpy_s(apply_info->real_name_, phandler->FetchField(row, AOMT_IdentityCardNo), sizeof(apply_info->real_name_) - 1);
                    strncpy_s(apply_info->bank_card_, phandler->FetchField(row, AOMT_BankCard), sizeof(apply_info->bank_card_) - 1);
                    strncpy_s(apply_info->bank_name_, phandler->FetchField(row, AOMT_BankName), sizeof(apply_info->bank_name_) - 1);

                    pchar = phandler->FetchField(row, AOMT_SerialNumber);
                    apply_info->apply_money_id_ = atoi(pchar);

                    pchar = phandler->FetchField(row, AOMT_OutAmount);
                    apply_info->apply_money_ = atof(pchar);

                    pchar = phandler->FetchField(row, AOMT_IsApproval);
                    apply_info->apply_status_ = (E_APPLY_MONEY_STATUS)atoi(pchar);

                    apply_info->money_type_ = money_type;

                    apply_infos.push_back(apply_info);
                }
            }

        }
            break;
        default:
            break;
        }

        phandler->ReleaseRecords(res);
        DBAccess::FreeDBHandler(phandler);
        return errCode == 0;
    }

    AllTrade::NPMgrCenter::SApplyMoneyPtr DBOpManagerCenter::getApplyMoneyPtr(const AllTrade::ApplyMoneyIDType apply_money_id, AllTrade::OIMM_Change_Type type)
    {
        CDBHandler *phandler = AllocDBHandler();
        if (!phandler)
            return SApplyMoneyPtr();

        HxSqlRes res = NULL;
        int errCode = 0;
        int recNum = 0;

        SApplyMoneyPtr apply_info(nullptr);
        switch (type)
        {
        case AllTrade::OIMM_In_Equipment:
        {
            std::stringstream sstr;
            sstr << "SELECT * FROM " << gszApplyMoneyTableName << " WHERE "
                << gszApplyMoneyColName[ApplyMoney_ID] << " = '" << apply_money_id << "'; ";

            errCode = phandler->QuerySql(sstr.str().c_str(), res, true);
            if (errCode != 0)
                LOG4CXX_ERROR(logger, "获取资金待审核信息失败!"LOG_NOVAR(sstr.str().c_str()));

            apply_info = std::make_shared<SApplyMoneyInfo>();
            if (errCode == 0 && res)
            {
                HxResRow row = NULL;
                if (row = phandler->FetchRow(res))
                {
                    char *pchar;
                    strncpy_s(apply_info->approval_user_id_, phandler->FetchField(row, ApplyMoney_Approval_UserID), sizeof(apply_info->approval_user_id_) - 1);
                    strncpy_s(apply_info->user_id_, phandler->FetchField(row, ApplyMoney_UserID), sizeof(apply_info->user_id_) - 1);
                    strncpy_s(apply_info->apply_date_time_, phandler->FetchField(row, ApplyMoney_DateTime), sizeof(apply_info->apply_date_time_) - 1);
                    strncpy_s(apply_info->approval_date_time_, phandler->FetchField(row, ApplyMoney_Approval_DateTime), sizeof(apply_info->approval_date_time_) - 1);

                    pchar = phandler->FetchField(row, ApplyMoney_ID);
                    apply_info->apply_money_id_ = atoi(pchar);
                    
                    pchar = phandler->FetchField(row, ApplyMoney_Money);
                    apply_info->apply_money_ = atof(pchar);

                    apply_info->money_type_ = type;

                    pchar = phandler->FetchField(row, ApplyMoney_Status);
                    apply_info->apply_status_ = (E_APPLY_MONEY_STATUS)atoi(pchar);

                }
            }
        }
            break;
        case AllTrade::OIMM_In_Deposit:
        {
            std::stringstream sstr;
            sstr << "SELECT * FROM " << gszApplyInMoneyTableName << " WHERE "
                << gszApplyInMoneyColName[AIMT_SerialNumber] << " = '" << apply_money_id << "' AND "
                << gszApplyInMoneyColName[AIMT_StateID] << " = " << 1 << ";";

            errCode = phandler->QuerySql(sstr.str().c_str(), res, true);
            if (errCode != 0)
                LOG4CXX_ERROR(logger, "获取入金资金待审核信息失败!"LOG_NOVAR(sstr.str().c_str()));

            apply_info = std::make_shared<SApplyMoneyInfo>();
            if (errCode == 0 && res)
            {
                HxResRow row = NULL;
                if (row = phandler->FetchRow(res))
                {
                    char *pchar;

                    strncpy_s(apply_info->approval_user_id_, phandler->FetchField(row, AIMT_Approval_Userid), sizeof(apply_info->approval_user_id_) - 1);
                    strncpy_s(apply_info->user_id_, phandler->FetchField(row, AIMT_AccountID), sizeof(apply_info->user_id_) - 1);

                    strncpy_s(apply_info->bank_card_, phandler->FetchField(row, AIMT_BankName), sizeof(apply_info->bank_card_) - 1);
                    strncpy_s(apply_info->bank_name_, phandler->FetchField(row, AIMT_BankCard), sizeof(apply_info->bank_name_) - 1);

                    strncpy_s(apply_info->apply_date_time_, phandler->FetchField(row, AIMT_PostTime), sizeof(apply_info->apply_date_time_) - 1);

                    pchar = phandler->FetchField(row, AIMT_SerialNumber);
                    apply_info->apply_money_id_ = atoi(pchar);

                    pchar = phandler->FetchField(row, AIMT_ApprovalTime);
                    if (pchar)
                        strncpy_s(apply_info->approval_date_time_, pchar, sizeof(apply_info->approval_date_time_) - 1);

                    pchar = phandler->FetchField(row, AIMT_Amount);
                    apply_info->apply_money_ = atof(pchar);

                    apply_info->money_type_ = type;

                    pchar = phandler->FetchField(row, AIMT_IsApproval);
                    apply_info->apply_status_ = (E_APPLY_MONEY_STATUS)atoi(pchar);

                }
            }

        }

            break;
        case AllTrade::OIMM_Out_Deposit:
        {
            std::stringstream sstr;
            sstr << "SELECT * FROM " << gszApplyOutMoneyTableName << " WHERE "
                << gszApplyOutMoneyColName[AOMT_SerialNumber] << " = '" << apply_money_id << "'; ";

            errCode = phandler->QuerySql(sstr.str().c_str(), res, true);
            if (errCode != 0)
                LOG4CXX_ERROR(logger, "获取出金资金待审核信息失败!"LOG_NOVAR(sstr.str().c_str()));

            apply_info = std::make_shared<SApplyMoneyInfo>();
            if (errCode == 0 && res)
            {
                HxResRow row = NULL;
                if (row = phandler->FetchRow(res))
                {
                    char *pchar;
                    strncpy_s(apply_info->approval_user_id_, phandler->FetchField(row, AOMT_Approval_Userid), sizeof(apply_info->approval_user_id_) - 1);
                    strncpy_s(apply_info->user_id_, phandler->FetchField(row, AOMT_UserID), sizeof(apply_info->user_id_) - 1);

                    strncpy_s(apply_info->real_name_, phandler->FetchField(row, AOMT_IdentityCardNo), sizeof(apply_info->real_name_) - 1);
                    strncpy_s(apply_info->bank_card_, phandler->FetchField(row, AOMT_BankCard), sizeof(apply_info->bank_card_) - 1);
                    strncpy_s(apply_info->bank_name_, phandler->FetchField(row, AOMT_BankName), sizeof(apply_info->bank_name_) - 1);

                    strncpy_s(apply_info->apply_date_time_, phandler->FetchField(row, AOMT_PostTime), sizeof(apply_info->apply_date_time_) - 1);
                    pchar = phandler->FetchField(row, AOMT_ApprovalTime);
                    if (pchar)
                        strncpy_s(apply_info->approval_date_time_, pchar, sizeof(apply_info->approval_date_time_) - 1);

                    pchar = phandler->FetchField(row, AOMT_OutAmount);
                    apply_info->apply_money_ = atof(pchar);

                    pchar = phandler->FetchField(row, AOMT_SerialNumber);
                    apply_info->apply_money_id_ = atoi(pchar);

                    apply_info->money_type_ = type;

                    pchar = phandler->FetchField(row, AOMT_IsApproval);
                    apply_info->apply_status_ = (E_APPLY_MONEY_STATUS)atoi(pchar);

                }
            }

        }
            break;
        default:
            assert(0);
            break;
        }

        phandler->ReleaseRecords(res);
        DBAccess::FreeDBHandler(phandler);

        return apply_info;
    }

    bool DBOpManagerCenter::applyMoney(const SApplyMoneyPtr& apply_info)
    {
        CDBHandler *phandler = AllocDBHandler();
        if (!phandler)
            return false;

        int errCode = 0;

        switch (apply_info->money_type_)
        {
        case AllTrade::OIMM_In_Equipment:
        {
            std::stringstream sstr;
            sstr << "INSERT INTO " << gszApplyMoneyTableName << " SET "
//                 << gszApplyMoneyColName[ApplyMoney_ID] << " = " << apply_info->apply_money_id_ << ", "
                << gszApplyMoneyColName[ApplyMoney_Approval_UserID] << " = '" << apply_info->approval_user_id_ << "', "
                << gszApplyMoneyColName[ApplyMoney_UserID] << " = '" << apply_info->user_id_ << "', "
                << gszApplyMoneyColName[ApplyMoney_Money] << " = " << apply_info->apply_money_ << ", "
                << gszApplyMoneyColName[ApplyMoney_DateTime] << " = '" << apply_info->apply_date_time_ << "', "
                << gszApplyMoneyColName[ApplyMoney_Approval_DateTime] << " = '" << apply_info->approval_date_time_ << "', "
                << gszApplyMoneyColName[ApplyMoney_Status] << " = " << apply_info->apply_status_ << ";";

            long long money_id(0);
            errCode = phandler->InsertWithLastID(sstr.str().c_str(), money_id);
            apply_info->apply_money_id_ = money_id;
            assert(errCode == 0);
            if (errCode != 0)
                LOG4CXX_ERROR(logger, "更新资金审核信息失败!"LOG_NOVAR(sstr.str().c_str()));
        }
            break;
        case AllTrade::OIMM_Out_Deposit:
        {
            std::stringstream sstr;
            sstr << "INSERT INTO " << gszApplyOutMoneyTableName << " SET "
//                 << gszApplyOutMoneyColName[AOMT_SerialNumber] << " = " << apply_info->apply_money_id_ << ", "
                << gszApplyOutMoneyColName[AOMT_Approval_Userid] << " = '" << apply_info->approval_user_id_ << "', "
                << gszApplyOutMoneyColName[AOMT_UserID] << " = '" << apply_info->user_id_ << "', "
                << gszApplyOutMoneyColName[AOMT_IdentityCardNo] << " = '" << apply_info->real_name_ << "', "
                << gszApplyOutMoneyColName[AOMT_BankCard] << " = '" << apply_info->bank_card_ << "', "
                << gszApplyOutMoneyColName[AOMT_BankName] << " = '" << apply_info->bank_name_ << "', "
                << gszApplyOutMoneyColName[AOMT_OutAmount] << " = " << apply_info->apply_money_ << ", "
                << gszApplyOutMoneyColName[AOMT_PostTime] << " = '" << apply_info->apply_date_time_ << "', "
                << gszApplyOutMoneyColName[AOMT_IsApproval] << " = " << apply_info->apply_status_ << ", "
                << gszApplyOutMoneyColName[AOMT_ApprovalTime] << " = '" << apply_info->approval_date_time_ << "'; ";

            long long money_id(0);
            errCode = phandler->InsertWithLastID(sstr.str().c_str(), money_id);
            apply_info->apply_money_id_ = money_id;
            assert(errCode == 0);
            if (errCode != 0)
                LOG4CXX_ERROR(logger, "更新资金审核信息失败!"LOG_NOVAR(sstr.str().c_str()));

        }
            break;
        default:
            assert(0);
            break;
        }

        DBAccess::FreeDBHandler(phandler);
        return errCode == 0;
    }

    bool DBOpManagerCenter::approvalApplyMoney(const UserIDType approval_user_id, const AllTrade::ApplyMoneyIDType apply_money_id, AllTrade::E_APPLY_MONEY_STATUS apply_status, const AllTrade::DateTimeType cur_dt, AllTrade::OIMM_Change_Type money_type)
    {
        CDBHandler *phandler = AllocDBHandler();
        if (!phandler)
            return false;

        HxSqlRes res = NULL;
        int errCode = 0;
        int recNum = 0;

        switch (money_type)
        {
        case AllTrade::OIMM_In_Equipment:
        {
            std::stringstream sstr;
            sstr << "SELECT * FROM " << gszApplyMoneyTableName << " WHERE "
                << gszApplyMoneyColName[ApplyMoney_ID] << " = '" << apply_money_id << "'"
                << " AND " << gszApplyMoneyColName[ApplyMoney_Status] << " = " << E_APPLY_MONEY_STATUS::EAMS_Check_Create << "; ";

            errCode = phandler->QuerySql(sstr.str().c_str(), res, true);
            if (errCode != 0)
                LOG4CXX_ERROR(logger, "获取资金待审核信息失败!"LOG_NOVAR(sstr.str().c_str()));

            if (errCode != 0 || !res)
            {
                phandler->ReleaseRecords(res);
                return false;
            }
            phandler->ReleaseRecords(res);

            sstr.str("");
            sstr << "UPDATE " << gszApplyMoneyTableName << " SET "
                << gszApplyMoneyColName[ApplyMoney_Approval_UserID] << " = '" << approval_user_id << "', "
                << gszApplyMoneyColName[ApplyMoney_Status] << " = " << apply_status << ", "
                << gszApplyMoneyColName[ApplyMoney_Approval_DateTime] << " = '" << cur_dt << "' "
                << " WHERE "
                << gszApplyMoneyColName[ApplyMoney_ID] << " = '" << apply_money_id << "' "
                << " AND " << gszApplyMoneyColName[ApplyMoney_Status] << " = " << E_APPLY_MONEY_STATUS::EAMS_Check_Create << "; ";

            errCode = phandler->ExecSql(sstr.str().c_str());
            assert(errCode == 0);
            if (errCode != 0)
                LOG4CXX_ERROR(logger, "审核资金融资信息失败!"LOG_NOVAR(sstr.str().c_str()));
        }
            break;
        case AllTrade::OIMM_In_Deposit:
        {
            std::stringstream sstr;
            sstr << "SELECT * FROM " << gszApplyInMoneyTableName << " WHERE "
                << gszApplyInMoneyColName[AIMT_SerialNumber] << " = '" << apply_money_id << "'"
                << " AND " << gszApplyInMoneyColName[AIMT_IsApproval] << " = " << E_APPLY_MONEY_STATUS::EAMS_Check_Create << "; ";

            errCode = phandler->QuerySql(sstr.str().c_str(), res, true);
            if (errCode != 0)
                LOG4CXX_ERROR(logger, "获取资金待审核信息失败!"LOG_NOVAR(sstr.str().c_str()));

            if (errCode != 0 || !res)
            {
                phandler->ReleaseRecords(res);
                return false;
            }
            phandler->ReleaseRecords(res);

            sstr.str("");
            sstr << "UPDATE " << gszApplyInMoneyTableName << " SET "
                << gszApplyInMoneyColName[AIMT_Approval_Userid] << " = '" << approval_user_id << "', "
                << gszApplyInMoneyColName[AIMT_IsApproval] << " = " << apply_status << ", "
                << gszApplyInMoneyColName[AIMT_ApprovalTime] << " = '" << cur_dt << "' "
                << " WHERE "
                << gszApplyInMoneyColName[AIMT_SerialNumber] << " = '" << apply_money_id << "' "
                << " AND " << gszApplyInMoneyColName[AIMT_IsApproval] << " = " << E_APPLY_MONEY_STATUS::EAMS_Check_Create << "; ";

            errCode = phandler->ExecSql(sstr.str().c_str());
            assert(errCode == 0);
            if (errCode != 0)
                LOG4CXX_ERROR(logger, "审核资金融资信息失败!"LOG_NOVAR(sstr.str().c_str()));
        }
            break;
        case AllTrade::OIMM_Out_Deposit:
        {
            std::stringstream sstr;
            sstr << "SELECT * FROM " << gszApplyOutMoneyTableName << " WHERE "
                << gszApplyOutMoneyColName[AOMT_SerialNumber] << " = '" << apply_money_id << "'"
                << " AND " << gszApplyOutMoneyColName[AOMT_IsApproval] << " = " << E_APPLY_MONEY_STATUS::EAMS_Check_Create << "; ";

            errCode = phandler->QuerySql(sstr.str().c_str(), res, true);
            if (errCode != 0)
                LOG4CXX_ERROR(logger, "获取资金待审核信息失败!"LOG_NOVAR(sstr.str().c_str()));

            if (errCode != 0 || !res)
            {
                phandler->ReleaseRecords(res);
                return false;
            }
            phandler->ReleaseRecords(res);

            sstr.str("");
            sstr << "UPDATE " << gszApplyOutMoneyTableName << " SET "
                << gszApplyOutMoneyColName[AOMT_Approval_Userid] << " = '" << approval_user_id << "', "
                << gszApplyOutMoneyColName[AOMT_IsApproval] << " = " << apply_status << ", "
                << gszApplyOutMoneyColName[AOMT_ApprovalTime] << " = '" << cur_dt << "' "
                << " WHERE "
                << gszApplyOutMoneyColName[AOMT_SerialNumber] << " = '" << apply_money_id << "' "
                << " AND " << gszApplyOutMoneyColName[AOMT_IsApproval] << " = " << E_APPLY_MONEY_STATUS::EAMS_Check_Create << "; ";

            errCode = phandler->ExecSql(sstr.str().c_str());
            assert(errCode == 0);
            if (errCode != 0)
                LOG4CXX_ERROR(logger, "审核资金融资信息失败!"LOG_NOVAR(sstr.str().c_str()));
        }
            break;
        default:
            break;
        }


        DBAccess::FreeDBHandler(phandler);
        return errCode == 0;
    }

    std::vector<AllTrade::NPMgrCenter::SMoneyDetailInfoPtr> DBOpManagerCenter::getFundSerial(const UserIDType user_id, const DateType start_day, const DateType end_day)
    {
        std::vector<AllTrade::NPMgrCenter::SMoneyDetailInfoPtr>  rslts;
        CDBHandler *phandler = AllocDBHandler();
        if (!phandler)
            return rslts;

        HxSqlRes res = NULL;
        int errCode = 0;
        int recNum = 0;

        std::stringstream sstr;
        sstr << "SELECT * FROM " << gszMoneyChangeTableName << " WHERE "
            << gszMoneyChangeColName[MnyCT_UserID] << " = '" << user_id << "' "
            << " AND " << gszMoneyChangeColName[MnyCT_Time] << " >= '" << start_day << "'"
            << " AND " << gszMoneyChangeColName[MnyCT_Time] << " <= '" << end_day << "';";
        
        std::string tmp = sstr.str();
        errCode = phandler->QuerySql(sstr.str().c_str(), res, true);
        if (errCode != 0)
            LOG4CXX_ERROR(logger, "获取资金流水信息失败!"LOG_NOVAR(sstr.str().c_str()));

        if (errCode == 0 && res)
        {
            HxResRow row = NULL;
            while (row = phandler->FetchRow(res))
            {
                SMoneyDetailInfoPtr ptr = std::make_shared<SMoneyDetailInfo>();
                char *pchar;
                strncpy_s(ptr->stream_, phandler->FetchField(row, MnyCT_Stream), sizeof(ptr->stream_) - 1);
                pchar= phandler->FetchField(row, MnyCT_Before);
                ptr->total_before_ = atof(pchar);
                pchar = phandler->FetchField(row, MnyCT_After);
                ptr->total_after_ = atof(pchar);
                pchar = phandler->FetchField(row, MnyCT_ChangeMoney);
                ptr->change_money_ = atof(pchar);
                pchar = phandler->FetchField(row, MnyCT_Type);
                ptr->change_type_ = (Money_Change_Type)atoi(pchar);
                strncpy_s(ptr->remark_, phandler->FetchField(row, MnyCT_Remark), sizeof(ptr->remark_) - 1);
                strncpy_s(ptr->date_time_, phandler->FetchField(row, MnyCT_Time), sizeof(ptr->date_time_) - 1);

                rslts.push_back(ptr);
            }
        }

        phandler->ReleaseRecords(res);
        DBAccess::FreeDBHandler(phandler);
        return rslts;
    }

    void DBOpManagerCenter::serializeLoginInUser(const AllTrade::NPMgrCenter::SOnlineAccountPtr& online_acc_ptr)
    {
        CDBHandler *phandler = AllocDBHandler();
        if (!phandler)
            return;

        int errCode = 0;

        std::stringstream sstr;
        sstr << "INSERT INTO " << gszUserLoginInfoTableName << " SET "
            << gszUserLoginInfoColName[ULI_UserID] << " = '" << online_acc_ptr->user_id_ << "', "
            << gszUserLoginInfoColName[ULI_InOut] << " = " << 0 << ", "
            << gszUserLoginInfoColName[ULI_DateTime] << " = '" << online_acc_ptr->login_datetime_ << "', "
            << gszUserLoginInfoColName[ULI_OpType] << " = " << (int)online_acc_ptr->op_type_ << ", "
            << gszUserLoginInfoColName[ULI_LoginIp] << " = '" << online_acc_ptr->login_ip_ << "', "
            << gszUserLoginInfoColName[ULI_LoginMac] << " = '" << online_acc_ptr->mac_info_ << "'; ";

        std::string tmp = sstr.str();
        errCode = phandler->ExecSql(sstr.str().c_str());
        assert(errCode == 0);
        if (errCode != 0)
            LOG4CXX_ERROR(logger, "序列化登录信息失败!"LOG_NOVAR(sstr.str().c_str()));

        DBAccess::FreeDBHandler(phandler);
    }

    void DBOpManagerCenter::serializeLoginOutUser(const AllTrade::NPMgrCenter::SOnlineAccountPtr& online_acc_ptr)
    {
        CDBHandler *phandler = AllocDBHandler();
        if (!phandler)
            return;

        int errCode = 0;

        std::stringstream sstr;
        sstr << "INSERT INTO " << gszUserLoginInfoTableName << " SET "
            << gszUserLoginInfoColName[ULI_UserID] << " = '" << online_acc_ptr->user_id_ << "', "
            << gszUserLoginInfoColName[ULI_InOut] << " = " << 1 << ", "
            << gszUserLoginInfoColName[ULI_DateTime] << " = '" << online_acc_ptr->login_datetime_ << "', "
            << gszUserLoginInfoColName[ULI_OpType] << " = " << (int)online_acc_ptr->op_type_ << ", "
            << gszUserLoginInfoColName[ULI_LoginIp] << " = '" << online_acc_ptr->login_ip_ << "', "
            << gszUserLoginInfoColName[ULI_LoginMac] << " = '" << online_acc_ptr->mac_info_ << "'; ";

        std::string tmp = sstr.str();
        errCode = phandler->ExecSql(sstr.str().c_str());
        assert(errCode == 0);
        if (errCode != 0)
            LOG4CXX_ERROR(logger, "序列化登录信息失败!"LOG_NOVAR(sstr.str().c_str()));

        DBAccess::FreeDBHandler(phandler);
    }

    std::string DBOpManagerCenter::getNewAgentLink()
    {
        static std::mutex lock;

        lock.lock();
        CDBHandler *phandler = AllocDBHandler();
        if (!phandler)
            return "";

        HxSqlRes res = NULL;
        int errCode = 0;
        int recNum = 0;

        std::stringstream sstr;
        sstr << "SELECT * FROM " << gszAccountGlobalDataTableName << ";";

        errCode = phandler->QuerySql(sstr.str().c_str(), res, true);
        if (errCode != 0)
        {
            LOG4CXX_ERROR(logger, "获取账户全局信息失败!"LOG_NOVAR(sstr.str().c_str()));
            phandler->ReleaseRecords(res);
            DBAccess::FreeDBHandler(phandler);
            lock.unlock();
            return "";
        }

        int cur_agency_id(4096);
        if (errCode == 0 && res)
        {
            HxResRow row = NULL;
            if (row = phandler->FetchRow(res))
            {
                char *pchar;
                pchar = phandler->FetchField(row, AGD_CurAgencyID);
                cur_agency_id = atoi(pchar);
            }
        }

        cur_agency_id++;
        phandler->ReleaseRecords(res);

        sstr.str("");
        sstr << "REPLACE INTO " << gszAccountGlobalDataTableName << " SET "
            << gszAccountGlobalDataColName[AGD_CommodityType] << " = " << (int)CommodityTypeType::COMMODITY_TYPE_STOCK << ", "
            << gszAccountGlobalDataColName[AGD_CurAgencyID] << " = " << cur_agency_id << "; ";

        std::string tmp = sstr.str();
        errCode = phandler->ExecSql(sstr.str().c_str());
        assert(errCode == 0);
        if (errCode != 0)
            LOG4CXX_ERROR(logger, "更新账户全局信息失败!"LOG_NOVAR(sstr.str().c_str()));

        lock.unlock();

        char buffer[8] = { 0 };
        _itoa_s(cur_agency_id, buffer, 8, 16);

        std::transform(buffer, &buffer[7], buffer, std::toupper);
        return buffer;
    }

    bool DBOpManagerCenter::addCustomStock(const AllTrade::UserIDType user_id, const AllTrade::ContractIDType contract_id)
    {
        CDBHandler *phandler = AllocDBHandler();
        if (!phandler)
            return false;

        int errCode = 0;

        std::stringstream sstr;
        sstr << "REPLACE INTO " << gszCustomStockTableName << " SET "
            << gszCustomStockColName[CST_UserID] << " = '" << user_id << "', "
            << gszCustomStockColName[CST_ContractID] << " = '" << contract_id << "';";

        std::string tmp = sstr.str();
        errCode = phandler->ExecSql(sstr.str().c_str());
        assert(errCode == 0);
        if (errCode != 0)
            LOG4CXX_ERROR(logger, "更新自选股信息失败!"LOG_NOVAR(sstr.str().c_str()));

        DBAccess::FreeDBHandler(phandler);
        return errCode == 0;
    }

    bool DBOpManagerCenter::removeCustomStock(const AllTrade::UserIDType user_id, const AllTrade::ContractIDType contract_id)
    {
        CDBHandler *phandler = AllocDBHandler();
        if (!phandler)
            return false;

        int errCode = 0;

        std::stringstream sstr;
        sstr << "DELETE FROM " << gszCustomStockTableName << " WHERE "
            << gszCustomStockColName[CST_UserID] << " = '" << user_id << "' AND "
            << gszCustomStockColName[CST_ContractID] << " = '" << contract_id << "';";

        std::string tmp = sstr.str();
        errCode = phandler->ExecSql(sstr.str().c_str());
        assert(errCode == 0);
        if (errCode != 0)
            LOG4CXX_ERROR(logger, "删除自选股信息失败!"LOG_NOVAR(sstr.str().c_str()));

        DBAccess::FreeDBHandler(phandler);
        return errCode == 0;
    }

    std::vector<AllTrade::PContractIDType> DBOpManagerCenter::getAllCustomStock(const AllTrade::UserIDType user_id)
    {
        std::vector<AllTrade::PContractIDType> rslt;
        CDBHandler *phandler = AllocDBHandler();
        if (!phandler)
            return rslt;

        HxSqlRes res = NULL;
        int errCode = 0;
        int recNum = 0;

        std::stringstream sstr;
        sstr << "SELECT * FROM " << gszCustomStockTableName << " WHERE "
            << gszCustomStockColName[CST_UserID] << " = '" << user_id << "';";

        errCode = phandler->QuerySql(sstr.str().c_str(), res, true);
        if (errCode != 0)
            LOG4CXX_ERROR(logger, "获取自选股信息失败!"LOG_NOVAR(sstr.str().c_str()));

        if (errCode == 0 && res)
        {
            HxResRow row = NULL;
            while (row = phandler->FetchRow(res))
            {
                rslt.push_back(phandler->FetchField(row, CST_ContractID));
            }
        }

        phandler->ReleaseRecords(res);
        DBAccess::FreeDBHandler(phandler);
        return rslt;
    }

    std::map<AllTrade::PUserIDType, std::vector<AllTrade::PContractIDType>> DBOpManagerCenter::getAllCustomStock()
    {
        std::map<PUserIDType, std::vector<PContractIDType>> rslt;
        CDBHandler *phandler = AllocDBHandler();
        if (!phandler)
            return rslt;

        HxSqlRes res = NULL;
        int errCode = 0;
        int recNum = 0;

        std::stringstream sstr;
        sstr << "SELECT * FROM " << gszCustomStockTableName;

        errCode = phandler->QuerySql(sstr.str().c_str(), res, true);
        if (errCode != 0)
            LOG4CXX_ERROR(logger, "获取自选股信息失败!"LOG_NOVAR(sstr.str().c_str()));

        if (errCode == 0 && res)
        {
            HxResRow row = NULL;
            while (row = phandler->FetchRow(res))
            {
                rslt[phandler->FetchField(row, CST_UserID)].push_back(phandler->FetchField(row, CST_ContractID));
            }
        }

        phandler->ReleaseRecords(res);
        DBAccess::FreeDBHandler(phandler);
        return rslt;
    }

    bool DBOpManagerCenter::updateStockContractInfo(const AllTrade::NPMgrCenter::SStockContractPtr& contract_ptr)
    {
        CDBHandler *phandler = AllocDBHandler();
        if (!phandler)
            return false;

        int errCode = 0;

        std::stringstream sstr;
        sstr << "REPLACE INTO " << gszStockContractTableName << " SET "
            << gszStockContractColName[SCT_ContractID] << " = '" << contract_ptr->contract_id_ << "', "
            << gszStockContractColName[SCT_ExchangeID] << " = '" << contract_ptr->exchange_id_ << "', "
            << gszStockContractColName[SCT_ContractNmae] << " = '" << contract_ptr->contract_name_ << "', "
            << gszStockContractColName[SCT_ContractCode] << " = '" << contract_ptr->contract_code_ << "', "
            << gszStockContractColName[SCT_CommodityType] << " = " << (int)contract_ptr->commodity_type_ << ", "
            << gszStockContractColName[SCT_CurrencyID] << " = '" << contract_ptr->currency_id_ << "', "
            << gszStockContractColName[SCT_LastDays] << " = " << contract_ptr->last_days_ << ", "
            << gszStockContractColName[SCT_OpenDateTime] << " = '" << contract_ptr->open_datetime_ << "', "
            << gszStockContractColName[SCT_DeliveryDateTime] << " = '" << contract_ptr->delivery_datetime_ << "', "
            << gszStockContractColName[SCT_TradeDateTime] << " = '" << contract_ptr->trade_datetime_ << "', "
            << gszStockContractColName[SCT_MinPriceChange] << " = " << contract_ptr->min_price_change_ << ", "
            << gszStockContractColName[SCT_Multiplier] << " = " << contract_ptr->contract_multiplier_ << ", "
            << gszStockContractColName[SCT_OpenFeeFix] << " = " << contract_ptr->open_fee_.bFix_ << ", "
            << gszStockContractColName[SCT_OpenFee] << " = " << contract_ptr->open_fee_.fee_ << ", "
            << gszStockContractColName[SCT_CloseYestodayFeeFix] << " = " << contract_ptr->close_yestoday_fee_.bFix_ << ", "
            << gszStockContractColName[SCT_CloseYestodayFee] << " = " << contract_ptr->close_yestoday_fee_.fee_ << ", "
            << gszStockContractColName[SCT_MarginFix] << " = " << contract_ptr->margin_fee_.bFix_ << ", "
            << gszStockContractColName[SCT_Margin] << " = " << contract_ptr->margin_fee_.fee_ << ", "
            << gszStockContractColName[SCT_DisplayProp] << " = '" << contract_ptr->display_prop_ << "', "
            << gszStockContractColName[SCT_DisplayPropType] << " = " << (int)contract_ptr->display_prop_type_ << ", "
            << gszStockContractColName[SCT_PlateProp] << " = '" << contract_ptr->plate_prop_ << "', "
            << gszStockContractColName[SCT_StockArea] << " = " << (int)contract_ptr->stock_area_ << ", "
            << gszStockContractColName[SCT_StockPlateArea] << " = " << (int)contract_ptr->stock_plate_area_ << ", "
            << gszStockContractColName[SCT_StockTotalShares] << " = " << contract_ptr->total_shares_ << "; ";

        std::string tmp = sstr.str();
        errCode = phandler->ExecSql(sstr.str().c_str());
        assert(errCode == 0);
        if (errCode != 0)
            LOG4CXX_ERROR(logger, "更新股票合约信息失败!"LOG_NOVAR(sstr.str().c_str()));

        DBAccess::FreeDBHandler(phandler);
        return errCode == 0;
    }

    bool DBOpManagerCenter::createExchanges()
    {
        CDBHandler *phandler = AllocDBHandler();
        if (!phandler)
            return false;

        int errCode = 0;

        std::stringstream sstr;
        sstr << "CREATE TABLE IF NOT EXISTS " << gszExchangeTableName << " (";

        for (int i = 0; i < ExT_Max; i++)
        {
            sstr << gszExchangeColName[i] << " " << gszExchangeCreateColType[i];
            if (i < ExT_Max - 1)
                sstr << ",";
        }
        sstr << ");";

        errCode = phandler->ExecSql(sstr.str().c_str());
        if (errCode != 0)
            LOG4CXX_ERROR(logger, "创建交易所表失败!"LOG_NOVAR(sstr.str().c_str()));

        DBAccess::FreeDBHandler(phandler);
        return errCode == 0;
    }

    bool DBOpManagerCenter::createStockContract()
    {
        CDBHandler *phandler = AllocDBHandler();
        if (!phandler)
            return false;

        int errCode = 0;

        std::stringstream sstr;
        sstr << "CREATE TABLE IF NOT EXISTS " << gszStockContractTableName << " (";

        for (int i = 0; i < SCT_Max; i++)
        {
            sstr << gszStockContractColName[i] << " " << gszStockContractCreateColType[i];
            if (i < SCT_Max - 1)
                sstr << ",";
        }
        sstr << ");";

        errCode = phandler->ExecSql(sstr.str().c_str());
        if (errCode != 0)
            LOG4CXX_ERROR(logger, "创建股票合约表失败!"LOG_NOVAR(sstr.str().c_str()));

        DBAccess::FreeDBHandler(phandler);
        return errCode == 0;
    }

    bool DBOpManagerCenter::createManagerUsers()
    {
        CDBHandler *phandler = AllocDBHandler();
        if (!phandler)
            return false;

        int errCode = 0;

        std::stringstream sstr;
        sstr << "CREATE TABLE IF NOT EXISTS " << gszManagerUserTableName << " (";

        for (int i = 0; i < MgrUT_Max; i++)
        {
            sstr << gszManagerUserColName[i] << " " << gszManagerUserCreateColType[i];
            if (i < MgrUT_Max - 1)
                sstr << ",";
        }
        sstr << ");";

        errCode = phandler->ExecSql(sstr.str().c_str());
        if (errCode != 0)
            LOG4CXX_ERROR(logger, "创建管理员表失败!"LOG_NOVAR(sstr.str().c_str()));

        DBAccess::FreeDBHandler(phandler);
        return errCode == 0;
    }

    bool DBOpManagerCenter::createAgencyUsers()
    {
        CDBHandler *phandler = AllocDBHandler();
        if (!phandler)
            return false;

        int errCode = 0;

        std::stringstream sstr;
        sstr << "CREATE TABLE IF NOT EXISTS " << gszAgencyUserTableName << " (";

        for (int i = 0; i < AgyUT_Max; i++)
        {
            sstr << gszAgencyUserColName[i] << " " << gszAgencyUserCreateColType[i];
            if (i < AgyUT_Max - 1)
                sstr << ",";
        }
        sstr << ");";

        errCode = phandler->ExecSql(sstr.str().c_str());
        if (errCode != 0)
            LOG4CXX_ERROR(logger, "创建机构表失败!"LOG_NOVAR(sstr.str().c_str()));

        DBAccess::FreeDBHandler(phandler);
        return errCode == 0;
    }

    bool DBOpManagerCenter::createTraderUsers()
    {
        CDBHandler *phandler = AllocDBHandler();
        if (!phandler)
            return false;

        int errCode = 0;

        std::stringstream sstr;
        sstr << "CREATE TABLE IF NOT EXISTS " << gszTradeUserTableName << " (";

        for (int i = 0; i < TUT_Max; i++)
        {
            sstr << gszTradeUserColName[i] << " " << gszTradeUserCreateColType[i];
            if (i < TUT_Max - 1)
                sstr << ",";
        }
        sstr << ");";

        errCode = phandler->ExecSql(sstr.str().c_str());
        if (errCode != 0)
            LOG4CXX_ERROR(logger, "创建交易员表失败!"LOG_NOVAR(sstr.str().c_str()));

        DBAccess::FreeDBHandler(phandler);
        return errCode == 0;
    }

    bool DBOpManagerCenter::createFunderUsers()
    {
        CDBHandler *phandler = AllocDBHandler();
        if (!phandler)
            return false;

        int errCode = 0;

        std::stringstream sstr;
        sstr << "CREATE TABLE IF NOT EXISTS " << gszFunderUserTableName << " (";

        for (int i = 0; i < FUT_Max; i++)
        {
            sstr << gszFunderUserColName[i] << " " << gszFunderUserCreateColType[i];
            if (i < FUT_Max - 1)
                sstr << ",";
        }
        sstr << ");";

        errCode = phandler->ExecSql(sstr.str().c_str());
        if (errCode != 0)
            LOG4CXX_ERROR(logger, "创建资金帐户表失败!"LOG_NOVAR(sstr.str().c_str()));

        DBAccess::FreeDBHandler(phandler);
        return errCode == 0;
    }

    bool DBOpManagerCenter::updateSuperMgrUserInfo(const AllTrade::NPMgrCenter::RootAccountPtr& account_ptr)
    {
        CDBHandler *phandler = AllocDBHandler();
        if (!phandler)
            return false;

        int errCode = 0;

        std::stringstream sstr;
        sstr << "REPLACE INTO " << gszManagerUserTableName << " set "
            << gszManagerUserColName[MgrUT_UserID] << " = '" << account_ptr->user_id_ << "', "
            << gszManagerUserColName[MgrUT_CreatorID] << " = '" << account_ptr->create_id_ << "', "
            << gszManagerUserColName[MgrUT_ParentID] << " = '" << account_ptr->parent_id_ << "', "
            << gszManagerUserColName[MgrUT_LoginName] << " = '" << account_ptr->login_name_ << "', "
            << gszManagerUserColName[MgrUT_NickName] << " = '" << account_ptr->nick_name_ << "', "
            << gszManagerUserColName[MgrUT_Password] << " = '" << account_ptr->password_ << "', "
            << gszManagerUserColName[MgrUT_AccountName] << " = '" << account_ptr->account_name_ << "', "
            << gszManagerUserColName[MgrUT_Level] << " = " << account_ptr->level_ << ", "
            << gszManagerUserColName[MgrUT_AccountProp] << " = " << (int)account_ptr->prop_ << ", "
            << gszManagerUserColName[MgrUT_AccountType] << " = " << (int)account_ptr->type_ << ", "
            << gszManagerUserColName[MgrUT_AccountStatus] << " = " << (int)account_ptr->status_ << ", "
            << gszManagerUserColName[MgrUT_PermissionType] << " = " << (int)account_ptr->permission_ << ", "
            << gszManagerUserColName[MgrUT_PopularizeLink] << " = '" << account_ptr->agent_link_ << "', "
            << gszManagerUserColName[MgrUT_RealName] << " = '" << account_ptr->real_name_ << "', "
            << gszManagerUserColName[MgrUT_PhoneNumber] << " = '" << account_ptr->phone_number_ << "', "
            << gszManagerUserColName[MgrUT_IdentityID] << " = '" << account_ptr->identity_ << "', "
            << gszManagerUserColName[MgrUT_RegistDatetime] << " = '" << account_ptr->regist_datetime_ << "', "
            << gszManagerUserColName[MgrUT_UpdateDatetime] << " = '" << account_ptr->update_datetime_ << "', "
            << gszManagerUserColName[MgrUT_VaildDatetime] << " = '" << account_ptr->vaild_datetime_ << "', "
//             << gszManagerUserColName[MgrUT_MgrProp] << " = " << (int)account_ptr->mgr_prop_ << ", "
            << gszManagerUserColName[MgrUT_AllowMaxLevel] << " = " << account_ptr->allow_max_level_ << ", "
            << gszManagerUserColName[MgrUT_AllowMaxNum] << " = " << account_ptr->allow_max_num_ << "; ";

        errCode = phandler->ExecSql(sstr.str().c_str());
        if (errCode != 0)
            LOG4CXX_ERROR(logger, "更新超级账户信息失败!"LOG_NOVAR(sstr.str().c_str()));

        DBAccess::FreeDBHandler(phandler);
        return errCode == 0;
    }

    bool DBOpManagerCenter::updateAgencyUserInfo(const AllTrade::NPMgrCenter::AgencyAccountPtr& account_ptr)
    {
        CDBHandler *phandler = AllocDBHandler();
        if (!phandler)
            return false;

        int errCode = 0;

        std::stringstream sstr;
        sstr << "REPLACE INTO " << gszAgencyUserTableName << " set "
            << gszAgencyUserColName[AgyUT_UserID] << " = '" << account_ptr->user_id_ << "', "
            << gszAgencyUserColName[AgyUT_CreatorID] << " = '" << account_ptr->create_id_ << "', "
            << gszAgencyUserColName[AgyUT_ParentID] << " = '" << account_ptr->parent_id_ << "', "
            << gszAgencyUserColName[AgyUT_LoginName] << " = '" << account_ptr->login_name_ << "', "
            << gszAgencyUserColName[AgyUT_NickName] << " = '" << account_ptr->nick_name_ << "', "
            << gszAgencyUserColName[AgyUT_Password] << " = '" << account_ptr->password_ << "', "
            << gszAgencyUserColName[AgyUT_AccountName] << " = '" << account_ptr->account_name_ << "', "
            << gszAgencyUserColName[AgyUT_FunderID] << " = '" << account_ptr->fund_user_id_ << "', "
            << gszAgencyUserColName[AgyUT_Level] << " = " << account_ptr->level_ << ", "
            << gszAgencyUserColName[AgyUT_AccountType] << " = " << (int)account_ptr->type_ << ", "
            << gszAgencyUserColName[AgyUT_AccountStatus] << " = " << (int)account_ptr->status_ << ", "
            << gszAgencyUserColName[AgyUT_PermissionType] << " = " << (int)account_ptr->permission_ << ", "
            << gszAgencyUserColName[AgyUT_PopularizeLink] << " = '" << account_ptr->agent_link_ << "', "
            << gszAgencyUserColName[AgyUT_RealName] << " = '" << account_ptr->real_name_ << "', "
            << gszAgencyUserColName[AgyUT_PhoneNumber] << " = '" << account_ptr->phone_number_ << "', "
            << gszAgencyUserColName[AgyUT_IdentityID] << " = '" << account_ptr->identity_ << "', "
            << gszAgencyUserColName[AgyUT_RegistDatetime] << " = '" << account_ptr->regist_datetime_ << "', "
            << gszAgencyUserColName[AgyUT_UpdateDatetime] << " = '" << account_ptr->update_datetime_ << "', "
            << gszAgencyUserColName[AgyUT_VaildDatetime] << " = '" << account_ptr->vaild_datetime_ << "', "
            << gszAgencyUserColName[AgyUT_AgyProp] << " = " << account_ptr->agency_prop_ << ", "
            << gszAgencyUserColName[AgyUT_AllowMaxLevel] << " = " << account_ptr->allow_max_level_ << ", "
            << gszAgencyUserColName[AgyUT_AllowMaxNum] << " = " << account_ptr->allow_max_num_ << "; ";

        errCode = phandler->ExecSql(sstr.str().c_str());
        if (errCode != 0)
            LOG4CXX_ERROR(logger, "更新管理账户信息失败!"LOG_NOVAR(sstr.str().c_str()));

        if (account_ptr->status_== E_ACCOUNT_STATUS::EAS_Using)
        {
            initCommissChange(account_ptr->user_id_);
            initProfitChange(account_ptr->user_id_);
        }

        DBAccess::FreeDBHandler(phandler);
        return errCode == 0;
    }

    bool DBOpManagerCenter::updateRiskerUserInfo(const AllTrade::NPMgrCenter::RiskAccountPtr& account_ptr)
    {
        return false;
    }

    bool DBOpManagerCenter::updateMonitorUserInfo(const AllTrade::NPMgrCenter::ManagerAccountPtr& account_ptr)
    {
        CDBHandler *phandler = AllocDBHandler();
        if (!phandler)
            return false;

        int errCode = 0;

        std::stringstream sstr;
        sstr << "REPLACE INTO " << gszManagerUserTableName << " set "
            << gszManagerUserColName[MgrUT_UserID] << " = '" << account_ptr->user_id_ << "', "
            << gszManagerUserColName[MgrUT_CreatorID] << " = '" << account_ptr->create_id_ << "', "
            << gszManagerUserColName[MgrUT_ParentID] << " = '" << account_ptr->parent_id_ << "', "
            << gszManagerUserColName[MgrUT_LoginName] << " = '" << account_ptr->login_name_ << "', "
            << gszManagerUserColName[MgrUT_NickName] << " = '" << account_ptr->nick_name_ << "', "
            << gszManagerUserColName[MgrUT_Password] << " = '" << account_ptr->password_ << "', "
            << gszManagerUserColName[MgrUT_AccountName] << " = '" << account_ptr->account_name_ << "', "
            << gszManagerUserColName[MgrUT_Level] << " = " << account_ptr->level_ << ", "
            << gszManagerUserColName[MgrUT_AccountProp] << " = " << (int)account_ptr->prop_ << ", "
            << gszManagerUserColName[MgrUT_AccountType] << " = " << (int)account_ptr->type_ << ", "
            << gszManagerUserColName[MgrUT_AccountStatus] << " = " << (int)account_ptr->status_ << ", "
            << gszManagerUserColName[MgrUT_PermissionType] << " = " << (int)account_ptr->permission_ << ", "
            << gszManagerUserColName[MgrUT_PopularizeLink] << " = '" << account_ptr->agent_link_ << "', "
            << gszManagerUserColName[MgrUT_RealName] << " = '" << account_ptr->real_name_ << "', "
            << gszManagerUserColName[MgrUT_PhoneNumber] << " = '" << account_ptr->phone_number_ << "', "
            << gszManagerUserColName[MgrUT_IdentityID] << " = '" << account_ptr->identity_ << "', "
            << gszManagerUserColName[MgrUT_RegistDatetime] << " = '" << account_ptr->regist_datetime_ << "', "
            << gszManagerUserColName[MgrUT_UpdateDatetime] << " = '" << account_ptr->update_datetime_ << "', "
            << gszManagerUserColName[MgrUT_VaildDatetime] << " = '" << account_ptr->vaild_datetime_ << "';";

        errCode = phandler->ExecSql(sstr.str().c_str());
        if (errCode != 0)
            LOG4CXX_ERROR(logger, "更新监管账户信息失败!"LOG_NOVAR(sstr.str().c_str()));

        DBAccess::FreeDBHandler(phandler);
        return errCode == 0;
    }

    bool DBOpManagerCenter::updateTraderUserInfo(const AllTrade::NPMgrCenter::TradeAccountPtr& account_ptr)
    {
        CDBHandler *phandler = AllocDBHandler();
        if (!phandler)
            return false;

        int errCode = 0;

        std::stringstream sstr;
        sstr << "REPLACE INTO " << gszTradeUserTableName << " set "
            << gszTradeUserColName[TUT_UserID] << " = '" << account_ptr->user_id_ << "', "
            << gszTradeUserColName[TUT_CreatorID] << " = '" << account_ptr->create_id_ << "', "
            << gszTradeUserColName[TUT_ParentID] << " = '" << account_ptr->parent_id_ << "', "
            << gszTradeUserColName[TUT_LoginName] << " = '" << account_ptr->login_name_ << "', "
            << gszTradeUserColName[TUT_NickName] << " = '" << account_ptr->nick_name_ << "', "
            << gszTradeUserColName[TUT_Password] << " = '" << account_ptr->password_ << "', "
            << gszTradeUserColName[TUT_AccountName] << " = '" << account_ptr->account_name_ << "', "
            << gszTradeUserColName[TUT_FunderID] << " = '" << account_ptr->fund_user_id_ << "', "
            << gszTradeUserColName[TUT_Level] << " = " << account_ptr->level_ << ", "
            << gszTradeUserColName[TUT_AccountProp] << " = " << (int)account_ptr->prop_ << ", "
            << gszTradeUserColName[TUT_AccountType] << " = " << (int)account_ptr->type_ << ", "
            << gszTradeUserColName[TUT_AccountStatus] << " = " << (int)account_ptr->status_ << ", "
            << gszTradeUserColName[TUT_PermissionType] << " = " << (int)account_ptr->permission_ << ", "
            << gszTradeUserColName[TUT_PopularizeLink] << " = '" << account_ptr->agent_link_ << "', "
            << gszTradeUserColName[TUT_RealName] << " = '" << account_ptr->real_name_ << "', "
            << gszTradeUserColName[TUT_PhoneNumber] << " = '" << account_ptr->phone_number_ << "', "
            << gszTradeUserColName[TUT_IdentityID] << " = '" << account_ptr->identity_ << "', "
            << gszTradeUserColName[TUT_RegistDatetime] << " = '" << account_ptr->regist_datetime_ << "', "
            << gszTradeUserColName[TUT_UpdateDatetime] << " = '" << account_ptr->update_datetime_ << "', "
            << gszTradeUserColName[TUT_VaildDatetime] << " = '" << account_ptr->vaild_datetime_ << "', "
			<< gszTradeUserColName[TUT_AuditorName] << " = '" << account_ptr->auditor_name_ << "', "
			<< gszTradeUserColName[TUT_AuditorDatetime] << " = '" << account_ptr->auditor_datetime_ << "'; ";

        errCode = phandler->ExecSql(sstr.str().c_str());
        if (errCode != 0)
            LOG4CXX_ERROR(logger, "更新交易账户信息失败!"LOG_NOVAR(sstr.str().c_str()));

        DBAccess::FreeDBHandler(phandler);
        return errCode == 0;
    }

    bool DBOpManagerCenter::updateFunderUserInfo(const AllTrade::NPMgrCenter::FunderAccountPtr& account_ptr)
    {
        CDBHandler *phandler = AllocDBHandler();
        if (!phandler)
            return false;

        int errCode = 0;

        std::stringstream sstr;
        sstr << "REPLACE INTO " << gszFunderUserTableName << " set "
            << gszFunderUserColName[FUT_UserID] << " = '" << account_ptr->user_id_ << "', "
            << gszFunderUserColName[FUT_CreatorID] << " = '" << account_ptr->create_id_ << "', "
            << gszFunderUserColName[FUT_ParentID] << " = '" << account_ptr->parent_id_ << "', "
            << gszFunderUserColName[FUT_LoginName] << " = '" << account_ptr->login_name_ << "', "
            << gszFunderUserColName[FUT_NickName] << " = '" << account_ptr->nick_name_ << "', "
            << gszFunderUserColName[FUT_Password] << " = '" << account_ptr->password_ << "', "
            << gszFunderUserColName[FUT_AccountName] << " = '" << account_ptr->account_name_ << "', "
            << gszFunderUserColName[FUT_Level] << " = " << account_ptr->level_ << ", "
            << gszFunderUserColName[FUT_AccountProp] << " = " << (int)account_ptr->prop_ << ", "
            << gszFunderUserColName[FUT_AccountType] << " = " << (int)account_ptr->type_ << ", "
            << gszFunderUserColName[FUT_AccountStatus] << " = " << (int)account_ptr->status_ << ", "
            << gszFunderUserColName[FUT_PermissionType] << " = " << (int)account_ptr->permission_ << ", "
            << gszFunderUserColName[FUT_PopularizeLink] << " = '" << account_ptr->agent_link_ << "', "
            << gszFunderUserColName[FUT_RealName] << " = '" << account_ptr->real_name_ << "', "
            << gszFunderUserColName[FUT_PhoneNumber] << " = '" << account_ptr->phone_number_ << "', "
            << gszFunderUserColName[FUT_IdentityID] << " = '" << account_ptr->identity_ << "', "
            << gszFunderUserColName[FUT_FunderCompany] << " = '" << account_ptr->fund_company_ << "', "
            << gszFunderUserColName[FUT_RegistDatetime] << " = '" << account_ptr->regist_datetime_ << "', "
            << gszFunderUserColName[FUT_UpdateDatetime] << " = '" << account_ptr->update_datetime_ << "', "
            << gszFunderUserColName[FUT_VaildDatetime] << " = '" << account_ptr->vaild_datetime_ << "'; ";

        errCode = phandler->ExecSql(sstr.str().c_str());
        if (errCode != 0)
            LOG4CXX_ERROR(logger, "更新资金账户信息失败!"LOG_NOVAR(sstr.str().c_str()));

        DBAccess::FreeDBHandler(phandler);
        return errCode == 0;
    }

    bool DBOpManagerCenter::createStockMoneyDetail()
    {
        CDBHandler *phandler = AllocDBHandler();
        if (!phandler)
            return false;

        int errCode = 0;

        std::stringstream sstr;
        sstr << "CREATE TABLE IF NOT EXISTS " << gszMoneyChangeTableName << " (";

        for (int i = 0; i < MnyCT_Max; i++)
        {
            sstr << gszMoneyChangeColName[i] << " " << gszMoneyChangeCreateColType[i];
            if (i < MnyCT_Max - 1)
                sstr << ",";
        }
        sstr << ");";

        errCode = phandler->ExecSql(sstr.str().c_str());
        if (errCode != 0)
            LOG4CXX_ERROR(logger, "创建股票资金流水信息表失败!"LOG_NOVAR(sstr.str().c_str()));

        DBAccess::FreeDBHandler(phandler);
        return errCode == 0;
    }

    bool DBOpManagerCenter::createStockMoney()
    {
        CDBHandler *phandler = AllocDBHandler();
        if (!phandler)
            return false;

        int errCode = 0;

        std::stringstream sstr;
        sstr << "CREATE TABLE IF NOT EXISTS " << gszMoneyTableName << " (";

        for (int i = 0; i < MnyT_Max; i++)
        {
            sstr << gszMoneyColName[i] << " " << gszMoneyCreateColType[i];
            if (i < MnyT_Max - 1)
                sstr << ",";
        }
        sstr << ");";

        errCode = phandler->ExecSql(sstr.str().c_str());
        if (errCode != 0)
            LOG4CXX_ERROR(logger, "创建股票资金表失败!"LOG_NOVAR(sstr.str().c_str()));

        DBAccess::FreeDBHandler(phandler);
        return errCode == 0;
    }

    bool DBOpManagerCenter::createStockRisk()
    {
        CDBHandler *phandler = AllocDBHandler();
        if (!phandler)
            return false;

        int errCode = 0;

        std::stringstream sstr;
        sstr << "CREATE TABLE IF NOT EXISTS " << gszRiskTableName << " (";

        for (int i = 0; i < RiskT_Max; i++)
        {
            sstr << gszRiskColName[i] << " " << gszRiskCreateColType[i];
            if (i < RiskT_Max - 1)
                sstr << ",";
        }
        sstr << ");";

        errCode = phandler->ExecSql(sstr.str().c_str());
        if (errCode != 0)
            LOG4CXX_ERROR(logger, "创建股票风控表失败!"LOG_NOVAR(sstr.str().c_str()));

        DBAccess::FreeDBHandler(phandler);
        return errCode == 0;
    }

    bool DBOpManagerCenter::createApplyMoney()
    {
        CDBHandler *phandler = AllocDBHandler();
        if (!phandler)
            return false;

        int errCode = 0;

        std::stringstream sstr;
        sstr << "CREATE TABLE IF NOT EXISTS " << gszApplyMoneyTableName << " (";
        for (int i = 0; i < ApplyMoney_Max; i++)
        {
            sstr << gszApplyMoneyColName[i] << " " << gszApplyMoneyCreateColType[i];
            if (i < ApplyMoney_Max - 1)
                sstr << ",";
        }
        sstr << ");";
        errCode = phandler->ExecSql(sstr.str().c_str());
        if (errCode != 0)
            LOG4CXX_ERROR(logger, "创建资金审核表失败!"LOG_NOVAR(sstr.str().c_str()));

        sstr.str("");
        sstr << "CREATE TABLE IF NOT EXISTS " << gszApplyInMoneyTableName << " (";
        for (int i = 0; i < AIMT_Max; i++)
        {
            sstr << gszApplyInMoneyColName[i] << " " << gszApplyInMoneyCreateColType[i];
            if (i < AIMT_Max - 1)
                sstr << ",";
        }
        sstr << ");";

        errCode = phandler->ExecSql(sstr.str().c_str());
        if (errCode != 0)
            LOG4CXX_ERROR(logger, "创建资金审核表失败!"LOG_NOVAR(sstr.str().c_str()));

        sstr.str("");
        sstr << "CREATE TABLE IF NOT EXISTS " << gszApplyOutMoneyTableName << " (";
        for (int i = 0; i < AOMT_Max; i++)
        {
            sstr << gszApplyOutMoneyColName[i] << " " << gszApplyOutMoneyCreateColType[i];
            if (i < AOMT_Max - 1)
                sstr << ",";
        }
        sstr << ");";

        errCode = phandler->ExecSql(sstr.str().c_str());
        if (errCode != 0)
            LOG4CXX_ERROR(logger, "创建资金审核表失败!"LOG_NOVAR(sstr.str().c_str()));

        DBAccess::FreeDBHandler(phandler);
        return errCode == 0;
    }

    bool DBOpManagerCenter::createVersionTable()
	{
		CDBHandler *phandler = AllocDBHandler();
		if (!phandler)
			return false;

		int errCode = 0;

		std::stringstream sstr;
		sstr << "CREATE TABLE IF NOT EXISTS " << gszVersionTableName << " (";

		for (int i = 0; i < Version_Max; i++)
		{
			sstr << gszVersionColName[i] << " " << gszVersionCreateColType[i];
			if (i < Version_Max - 1)
				sstr << ",";
		}
		sstr << ");";

		errCode = phandler->ExecSql(sstr.str().c_str());
        if (errCode != 0)
            LOG4CXX_ERROR(logger, "创建版本表失败!"LOG_NOVAR(sstr.str().c_str()));

		DBAccess::FreeDBHandler(phandler);
		return errCode == 0;
	}

	bool DBOpManagerCenter::InsertVersionTable()
	{
		CDBHandler *phandler = AllocDBHandler();
		if (!phandler)
			return false;

		int errCode = 0;

		std::stringstream sstr;

		
		sstr << "INSERT INTO " << gszVersionTableName << " SET "
			<< gszVersionColName[Version_Name] << " = '" << VERSION << "'; ";

		errCode = phandler->ExecSql(sstr.str().c_str());
		DBAccess::FreeDBHandler(phandler);
		return errCode == 0;
	}

    bool DBOpManagerCenter::createLoginInOutInfo()
    {
        CDBHandler *phandler = AllocDBHandler();
        if (!phandler)
            return false;

        int errCode = 0;

        std::stringstream sstr;
        sstr << "CREATE TABLE IF NOT EXISTS " << gszUserLoginInfoTableName << " (";

        for (int i = 0; i < ULI_Max; i++)
        {
            sstr << gszUserLoginInfoColName[i] << " " << gszUserLoginInfoCreateColType[i];
            if (i < ULI_Max - 1)
                sstr << ",";
        }
        sstr << ");";

        errCode = phandler->ExecSql(sstr.str().c_str());
        if (errCode != 0)
            LOG4CXX_ERROR(logger, "创建登入登出信息表失败!"LOG_NOVAR(sstr.str().c_str()));

        DBAccess::FreeDBHandler(phandler);
        return errCode == 0;
    }

    bool DBOpManagerCenter::createCustomStock()
    {
        CDBHandler *phandler = AllocDBHandler();
        if (!phandler)
            return false;

        int errCode = 0;

        std::stringstream sstr;
        sstr << "CREATE TABLE IF NOT EXISTS " << gszCustomStockTableName << " (";

        for (int i = 0; i < CST_Max; i++)
        {
            sstr << gszCustomStockColName[i] << " " << gszCustomStockCreateColType[i]
                << ",";
        }
        sstr << "PRIMARY KEY (" << gszCustomStockColName[CST_UserID] << "," << gszCustomStockColName[CST_ContractID] << ") );";

        errCode = phandler->ExecSql(sstr.str().c_str());
        if (errCode != 0)
            LOG4CXX_ERROR(logger, "创建自选股信息表失败!"LOG_NOVAR(sstr.str().c_str()));

        DBAccess::FreeDBHandler(phandler);
        return errCode == 0;
    }

    bool DBOpManagerCenter::createAccountGlobalData()
    {
        CDBHandler *phandler = AllocDBHandler();
        if (!phandler)
            return false;

        int errCode = 0;

        std::stringstream sstr;
        sstr << "CREATE TABLE IF NOT EXISTS " << gszAccountGlobalDataTableName << " (";

        for (int i = 0; i < AGD_Max; i++)
        {
            sstr << gszAccountGlobalDataColName[i] << " " << gszAccountGlobalDataCreateColType[i];
            if (i < AGD_Max - 1)
                sstr << ",";
        }
        sstr << ")";

        errCode = phandler->ExecSql(sstr.str().c_str());
        if (errCode != 0)
            LOG4CXX_ERROR(logger, "创建账户全局信息表失败!"LOG_NOVAR(sstr.str().c_str()));

        DBAccess::FreeDBHandler(phandler);
        return errCode == 0;
    }

    bool DBOpManagerCenter::createAgencyCommiss()
    {
        CDBHandler *phandler = AllocDBHandler();
        if (!phandler)
            return false;

        int errCode = 0;

        // 佣金统计表
        std::stringstream sstr;
        sstr << "CREATE TABLE IF NOT EXISTS " << gszAgencyCommissionTableName << " (";

        for (int i = 0; i < AgyCT_Max; i++)
        {
            sstr << gszAgencyCommissionColName[i] << " " << gszAgencyCommissionCreateColType[i];
            if (i < AgyCT_Max - 1)
                sstr << ",";
        }
        sstr << ");";

        errCode = phandler->ExecSql(sstr.str().c_str());

        // 佣金快照表
        sstr.str("");
        sstr << "CREATE TABLE IF NOT EXISTS " << gszAgencyCommissRecodeTableName << " (";

        for (int i = 0; i < AgyCRT_Max; i++)
        {
            sstr << gszAgencyCommissRecodeColName[i] << " " << gszAgencyCommissRecodeCreateColType[i]
                << ",";
        }
        sstr << "PRIMARY KEY (" << gszAgencyCommissRecodeColName[AgyCRT_UserID] << "," << gszAgencyCommissRecodeColName[AgyCRT_Date] << ") );";

        errCode = phandler->ExecSql(sstr.str().c_str());

        // 佣金变动明细表
        sstr.str("");
        sstr << "CREATE TABLE IF NOT EXISTS " << gszAgencyCommissionChangeTableName << " (";

        for (int i = 0; i < AgyCCT_Max; i++)
        {
            sstr << gszAgencyCommissionChangeColName[i] << " " << gszAgencyCommissionChangeCreateColType[i];
            if (i < AgyCCT_Max - 1)
                sstr << ",";
        }
        sstr << ");";

        errCode = phandler->ExecSql(sstr.str().c_str());

        // 初始化佣金表
        if (errCode == 0)
        {
            HxSqlRes res = NULL;
            int errCode = 0;
            int recNum = 0;

            // 获取所有机构账户
            sstr.str("");
            sstr << "SELECT * FROM " << gszAgencyUserTableName
                << " WHERE " << gszAgencyUserColName[AgyUT_AccountStatus] << " = " << E_ACCOUNT_STATUS::EAS_Using << ";";

            errCode = phandler->QuerySql(sstr.str().c_str(), res, true);
            if (errCode != 0)
                LOG4CXX_ERROR(logger, "获取机构帐户信息失败!"LOG_NOVAR(sstr.str().c_str()));

            if (errCode == 0 && res)
            {
                HxResRow row = NULL;

                while (row = phandler->FetchRow(res))
                {
                    UserIDType user_id;
                    strncpy_s(user_id, phandler->FetchField(row, AgyUT_UserID), sizeof(user_id) - 1);
                    initCommissChange(user_id);
                }
            }
            phandler->ReleaseRecords(res);

            // 获取超级账户
            sstr.str("");
            sstr << "SELECT * FROM " << gszManagerUserTableName
                << " WHERE " << gszManagerUserColName[MgrUT_AccountProp] << " = " << E_ACCOUNT_PROP::EAP_Root << ";";

            errCode = phandler->QuerySql(sstr.str().c_str(), res, true);
            if (errCode != 0)
                LOG4CXX_ERROR(logger, "获取根帐户信息失败!"LOG_NOVAR(sstr.str().c_str()));

            if (errCode == 0 && res)
            {
                HxResRow row = NULL;

                while (row = phandler->FetchRow(res))
                {
                    UserIDType user_id;
                    strncpy_s(user_id, phandler->FetchField(row, MgrUT_UserID), sizeof(user_id) - 1);
                    initCommissChange(user_id);
                }
            }
            phandler->ReleaseRecords(res);

        }

        DBAccess::FreeDBHandler(phandler);
        return errCode == 0;
    }

    bool DBOpManagerCenter::createAgencyProfit()
    {
        CDBHandler *phandler = AllocDBHandler();
        if (!phandler)
            return false;

        int errCode = 0;

        // 佣金统计表
        std::stringstream sstr;
        sstr << "CREATE TABLE IF NOT EXISTS " << gszAgencyProfitTableName << " (";

        for (int i = 0; i < AgyPT_Max; i++)
        {
            sstr << gszAgencyProfitColName[i] << " " << gszAgencyProfitCreateColType[i];
            if (i < AgyPT_Max - 1)
                sstr << ",";
        }
        sstr << ");";

        errCode = phandler->ExecSql(sstr.str().c_str());

        // 佣金快照表
        sstr.str("");
        sstr << "CREATE TABLE IF NOT EXISTS " << gszAgencyProfitRecodeTableName << " (";

        for (int i = 0; i < AgyPRT_Max; i++)
        {
            sstr << gszAgencyProfitRecodeColName[i] << " " << gszAgencyProfitRecodeCreateColType[i]
                << ",";
        }
        sstr << "PRIMARY KEY (" << gszAgencyProfitRecodeColName[AgyPRT_UserID] << "," << gszAgencyProfitRecodeColName[AgyPRT_Date] << ") );";

        errCode = phandler->ExecSql(sstr.str().c_str());

        // 佣金变动明细表
        sstr.str("");
        sstr << "CREATE TABLE IF NOT EXISTS " << gszAgencyProfitChangeTableName << " (";

        for (int i = 0; i < AgyPCT_Max; i++)
        {
            sstr << gszAgencyProfitChangeColName[i] << " " << gszAgencyProfitChangeCreateColType[i];
            if (i < AgyPCT_Max - 1)
                sstr << ",";
        }
        sstr << ");";

        errCode = phandler->ExecSql(sstr.str().c_str());

        // 初始化佣金表
        if (errCode == 0)
        {
            HxSqlRes res = NULL;
            int errCode = 0;
            int recNum = 0;

            // 获取所有机构账户
            sstr.str("");
            sstr << "SELECT * FROM " << gszAgencyUserTableName
                << " WHERE " << gszAgencyUserColName[AgyUT_AccountStatus] << " = " << E_ACCOUNT_STATUS::EAS_Using << ";";

            errCode = phandler->QuerySql(sstr.str().c_str(), res, true);
            if (errCode != 0)
                LOG4CXX_ERROR(logger, "获取机构帐户信息失败!"LOG_NOVAR(sstr.str().c_str()));

            if (errCode == 0 && res)
            {
                HxResRow row = NULL;

                while (row = phandler->FetchRow(res))
                {
                    UserIDType user_id;
                    strncpy_s(user_id, phandler->FetchField(row, AgyUT_UserID), sizeof(user_id) - 1);
                    initProfitChange(user_id);
                }
            }
            phandler->ReleaseRecords(res);

            // 获取超级账户
            sstr.str("");
            sstr << "SELECT * FROM " << gszManagerUserTableName
                << " WHERE " << gszManagerUserColName[MgrUT_AccountProp] << " = " << E_ACCOUNT_PROP::EAP_Root << ";";

            errCode = phandler->QuerySql(sstr.str().c_str(), res, true);
            if (errCode != 0)
                LOG4CXX_ERROR(logger, "获取根帐户信息失败!"LOG_NOVAR(sstr.str().c_str()));

            if (errCode == 0 && res)
            {
                HxResRow row = NULL;

                while (row = phandler->FetchRow(res))
                {
                    UserIDType user_id;
                    strncpy_s(user_id, phandler->FetchField(row, MgrUT_UserID), sizeof(user_id) - 1);
                    initProfitChange(user_id);
                }
            }
            phandler->ReleaseRecords(res);

        }

        DBAccess::FreeDBHandler(phandler);
        return errCode == 0;
    }

    void DBOpManagerCenter::initCommissChange(const AllTrade::UserIDType user_id)
    {
        CDBHandler *phandler = AllocDBHandler();
        if (!phandler)
            return;

        int errCode = 0;

        std::stringstream sstr;
        sstr << "INSERT INTO " << gszAgencyCommissionTableName << " ( "
            << gszAgencyCommissionColName[AgyCT_UserID] << ", "
            << gszAgencyCommissionColName[AgyCT_InfoMatchTotal] << ", "
            << gszAgencyCommissionColName[AgyCT_TradeFeeTotal] << ", "
            << gszAgencyCommissionColName[AgyCT_CommissionTotal] << ") "
            << " SELECT '" << user_id << "', 0 , 0, 0"
            << " FROM DUAL WHERE NOT EXISTS( SELECT " << gszAgencyCommissionColName[AgyCT_UserID]
            << " FROM " << gszAgencyCommissionTableName
            << " WHERE " << gszAgencyCommissionColName[AgyCT_UserID] << " = '" << user_id << "') "
            << " LIMIT 1";

        std::string tmp = sstr.str();
        errCode = phandler->ExecSql(sstr.str().c_str());
        if (errCode != 0)
            LOG4CXX_ERROR(logger, "初始化机构佣金明细信息失败!"LOG_NOVAR(sstr.str().c_str()));

        DBAccess::FreeDBHandler(phandler);
        return;
    }

    void DBOpManagerCenter::initProfitChange(const AllTrade::UserIDType user_id)
    {
        CDBHandler *phandler = AllocDBHandler();
        if (!phandler)
            return;

        int errCode = 0;

        std::stringstream sstr;
        sstr << "INSERT INTO " << gszAgencyProfitTableName << " ( "
            << gszAgencyProfitColName[AgyPT_UserID] << ", "
            << gszAgencyProfitColName[AgyPT_ProfitTotal] << ") "
            << " SELECT '" << user_id << "', 0"
            << " FROM DUAL WHERE NOT EXISTS( SELECT " << gszAgencyProfitColName[AgyPT_UserID]
            << " FROM " << gszAgencyProfitTableName
            << " WHERE " << gszAgencyProfitColName[AgyPT_UserID] << " = '" << user_id << "') "
            << " LIMIT 1";

        std::string tmp = sstr.str();
        errCode = phandler->ExecSql(sstr.str().c_str());
        if (errCode != 0)
            LOG4CXX_ERROR(logger, "初始化机构分成明细信息失败!"LOG_NOVAR(sstr.str().c_str()));

        DBAccess::FreeDBHandler(phandler);
        return;
    }

    void DBOpManagerCenter::agencyMoneyChange(const AllTrade::NPMgrCenter::SAgencyMoneyDetailInfoPtr agy_detail)
    {
        switch (agy_detail->change_type_)
        {
        case AllTrade::AMCT_InfoMatch_Commission:
        case AllTrade::AMCT_Exchange_Commission:
            agencyCommissChange(agy_detail);
            break;
        case AllTrade::AMCT_Trade_Profit:
            agencyProfitChange(agy_detail);
            break;
        default:
            assert(0);
            break;
        }
    }

    void DBOpManagerCenter::agencyCommissChange(const AllTrade::NPMgrCenter::SAgencyMoneyDetailInfoPtr agy_detail)
    {
        CDBHandler *phandler = AllocDBHandler();
        if (!phandler)
            return;

        AgencyCommissionTable cur_enum;
        switch (agy_detail->change_type_)
        {
        case AllTrade::AMCT_InfoMatch_Commission:
            cur_enum = AgyCT_InfoMatchTotal;
            break;
        case AllTrade::AMCT_Exchange_Commission:
            cur_enum = AgyCT_TradeFeeTotal;
            break;
        default:
            assert(0);
            break;
        }

        // 更新实时佣金信息
        int errCode = 0;
        std::stringstream sstr;
        sstr << "UPDATE " << gszAgencyCommissionTableName << " SET "
            << gszAgencyCommissionColName[cur_enum] << " = " << gszAgencyCommissionColName[cur_enum] << " + " << agy_detail->change_money_ << ", "
            << gszAgencyCommissionColName[AgyCT_CommissionTotal] << " = " << gszAgencyCommissionColName[AgyCT_CommissionTotal] << " + " << agy_detail->change_money_ << " "
            << " WHERE " << gszAgencyCommissionColName[AgyCT_UserID] << " = '" << agy_detail->user_id_ << "'; ";

        errCode = phandler->ExecSql(sstr.str().c_str());
        if (errCode != 0)
            LOG4CXX_ERROR(logger, "更新机构佣金信息失败!"LOG_NOVAR(sstr.str().c_str()));

        // 更新历史佣金记录
        sstr.str("");
        sstr << "REPLACE INTO " << gszAgencyCommissRecodeTableName << " SET "
            << gszAgencyCommissRecodeColName[AgyCRT_UserID] << " = '" << agy_detail->user_id_ << "', "
            << gszAgencyCommissRecodeColName[AgyCRT_Date] << " = '" << agy_detail->date_ << "', "
            << gszAgencyCommissRecodeColName[AgyCRT_InfoMatchTotal] << " = (SELECT " << gszAgencyCommissionColName[AgyCT_InfoMatchTotal] << " FROM " << gszAgencyCommissionTableName << " WHERE " << gszAgencyCommissionColName[AgyCT_UserID] << " = '" << agy_detail->user_id_ << "'), "
            << gszAgencyCommissRecodeColName[AgyCRT_TradeFeeTotal] << " = (SELECT " << gszAgencyCommissionColName[AgyCT_TradeFeeTotal] << " FROM " << gszAgencyCommissionTableName << " WHERE " << gszAgencyCommissionColName[AgyCT_UserID] << " = '" << agy_detail->user_id_ << "'), "
            << gszAgencyCommissRecodeColName[AgyCRT_CommissionTotal] << " = (SELECT " << gszAgencyCommissionColName[AgyCT_CommissionTotal] << " FROM " << gszAgencyCommissionTableName << " WHERE " << gszAgencyCommissionColName[AgyCT_UserID] << " = '" << agy_detail->user_id_ << "');";

        errCode = phandler->ExecSql(sstr.str().c_str());
        if (errCode != 0)
            LOG4CXX_ERROR(logger, "更新机构佣金信息失败!"LOG_NOVAR(sstr.str().c_str()));

        // 更新机构佣金变动表
        sstr.str("");
        sstr << "INSERT INTO " << gszAgencyCommissionChangeTableName << " SET "
            << gszAgencyCommissionChangeColName[AgyCCT_UserID] << " = '" << agy_detail->user_id_ << "',"
            << gszAgencyCommissionChangeColName[AgyCCT_SourceUserID] << " = '" << agy_detail->source_user_id_ << "',"
            << gszAgencyCommissionChangeColName[AgyCCT_Before] << " = " << agy_detail->total_before_ << ","
            << gszAgencyCommissionChangeColName[AgyCCT_After] << " = " << agy_detail->total_after_ << ","
            << gszAgencyCommissionChangeColName[AgyCCT_CommissionRate] << " = " << agy_detail->commission_rate_ << ","
            << gszAgencyCommissionChangeColName[AgyCCT_ChangeMoney] << " = " << agy_detail->change_money_ << ","
            << gszAgencyCommissionChangeColName[AgyCCT_Type] << " = " << agy_detail->change_type_ << ","
            << gszAgencyCommissionChangeColName[AgyCCT_Remark] << " = '" << agy_detail->remark_ << "',"
            << gszAgencyCommissionChangeColName[AgyCCT_Time] << " = '" << agy_detail->date_time_ << "';";

        errCode = phandler->ExecSql(sstr.str().c_str());
        if (errCode != 0)
            LOG4CXX_ERROR(logger, "更新机构佣金信息失败!"LOG_NOVAR(sstr.str().c_str()));

        DBAccess::FreeDBHandler(phandler);
    }

    void DBOpManagerCenter::agencyProfitChange(const AllTrade::NPMgrCenter::SAgencyMoneyDetailInfoPtr agy_detail)
    {
        CDBHandler *phandler = AllocDBHandler();
        if (!phandler)
            return;

        // 更新实时分成信息
        int errCode = 0;
        std::stringstream sstr;
        sstr << "UPDATE " << gszAgencyProfitTableName << " SET "
            << gszAgencyProfitColName[AgyPT_ProfitTotal] << " = " << gszAgencyProfitColName[AgyPT_ProfitTotal] << " + " << agy_detail->change_money_ << " "
            << " WHERE " << gszAgencyProfitColName[AgyPT_UserID] << " = '" << agy_detail->user_id_ << "'; ";

        errCode = phandler->ExecSql(sstr.str().c_str());
        if (errCode != 0)
            LOG4CXX_ERROR(logger, "更新机构分成信息失败!"LOG_NOVAR(sstr.str().c_str()));

        // 更新历史分成记录
        sstr.str("");
        sstr << "REPLACE INTO " << gszAgencyProfitRecodeTableName << " SET "
            << gszAgencyProfitRecodeColName[AgyPRT_UserID] << " = '" << agy_detail->user_id_ << "', "
            << gszAgencyProfitRecodeColName[AgyPRT_Date] << " = '" << agy_detail->date_ << "', "
            << gszAgencyProfitRecodeColName[AgyPRT_ProfitTotal] << " = (SELECT " << gszAgencyProfitColName[AgyPT_ProfitTotal] << " FROM " << gszAgencyProfitTableName << " WHERE " << gszAgencyProfitColName[AgyPT_UserID] << " = '" << agy_detail->user_id_ << "');";

        errCode = phandler->ExecSql(sstr.str().c_str());
        if (errCode != 0)
            LOG4CXX_ERROR(logger, "更新机构分成信息失败!"LOG_NOVAR(sstr.str().c_str()));

        // 更新机构分成变动表
        sstr.str("");
        sstr << "INSERT INTO " << gszAgencyProfitChangeTableName << " SET "
            << gszAgencyProfitChangeColName[AgyPCT_UserID] << " = '" << agy_detail->user_id_ << "',"
            << gszAgencyProfitChangeColName[AgyPCT_SourceUserID] << " = '" << agy_detail->source_user_id_ << "',"
            << gszAgencyProfitChangeColName[AgyPCT_Before] << " = " << agy_detail->total_before_ << ","
            << gszAgencyProfitChangeColName[AgyPCT_After] << " = " << agy_detail->total_after_ << ","
            << gszAgencyProfitChangeColName[AgyPCT_CommissionRate] << " = " << agy_detail->commission_rate_ << ","
            << gszAgencyProfitChangeColName[AgyPCT_ChangeMoney] << " = " << agy_detail->change_money_ << ","
            << gszAgencyProfitChangeColName[AgyPCT_Type] << " = " << agy_detail->change_type_ << ","
            << gszAgencyProfitChangeColName[AgyPCT_Remark] << " = '" << agy_detail->remark_ << "',"
            << gszAgencyProfitChangeColName[AgyPCT_Time] << " = '" << agy_detail->date_time_ << "';";

        errCode = phandler->ExecSql(sstr.str().c_str());
        if (errCode != 0)
            LOG4CXX_ERROR(logger, "更新机构分成信息失败!"LOG_NOVAR(sstr.str().c_str()));

        DBAccess::FreeDBHandler(phandler);
    }


	bool DBOpManagerCenter::qryAgencyCommissInfo(const AllTrade::UserIDType user_id, const AllTrade::DateType start_day, const AllTrade::DateType end_day, YDouble& infomatch, YDouble& tradefee, YDouble& comm_all)
    {
        CDBHandler *phandler = AllocDBHandler();
        if (!phandler)
            return false;

        HxSqlRes res = NULL;
        int errCode = 0;
        int recNum = 0;
        std::string tmp_strat_day, tmp_end_day;

        // 取出最接近的日期
        std::stringstream sstr;
        sstr << "SELECT MIN(" << gszAgencyCommissRecodeColName[AgyCRT_Date] << ")" << ",MAX(" << gszAgencyCommissRecodeColName[AgyCRT_Date] << ")"
            << " FROM " << gszAgencyCommissRecodeTableName
            << " WHERE " << gszAgencyCommissRecodeColName[AgyCRT_UserID] << " = '" << user_id << "' "
            << " AND " << gszAgencyCommissRecodeColName[AgyCRT_Date] << " <= '" << end_day << "' "
            << " AND " << gszAgencyCommissRecodeColName[AgyCRT_Date] << " >= '" << start_day << "' ";
        std::string tmp = sstr.str();
        errCode = phandler->QuerySql(sstr.str().c_str(), res, true);
        if (errCode != 0)
            LOG4CXX_ERROR(logger, "查询佣金信息时选取语句失败!"LOG_NOVAR(sstr.str().c_str()));

        if (errCode == 0 && res)
        {
            HxResRow row = NULL;
            if (row = phandler->FetchRow(res))
            {
                char* pchar = phandler->FetchField(row, 0);
                if (pchar)
                    tmp_strat_day = pchar;

                pchar = phandler->FetchField(row, 1);
                if (pchar)
                    tmp_end_day = pchar;
            }
        }

        phandler->ReleaseRecords(res);
        if (tmp_end_day.empty())
        {
            DBAccess::FreeDBHandler(phandler);
            return errCode == 0;
        }

        // 找到最近一天
        if (tmp_end_day == tmp_strat_day)
        {
            sstr.str("");
            sstr << "SELECT MAX(" << gszAgencyCommissRecodeColName[AgyCRT_Date] << ")"
                << " FROM " << gszAgencyCommissRecodeTableName
                << " WHERE " << gszAgencyCommissRecodeColName[AgyCRT_UserID] << " = '" << user_id << "' "
                << " AND " << gszAgencyCommissRecodeColName[AgyCRT_Date] << " < '" << tmp_strat_day << "' ";

            tmp_strat_day.clear();
            errCode = phandler->QuerySql(sstr.str().c_str(), res, true);
            if (errCode != 0)
                LOG4CXX_ERROR(logger, "查询佣金信息起始时间选取语句失败!"LOG_NOVAR(sstr.str().c_str()));

            if (errCode == 0 && res)
            {
                HxResRow row = NULL;
                if (row = phandler->FetchRow(res))
                {
                    char* pchar = phandler->FetchField(row, 0);
                    if (pchar)
                        tmp_strat_day = pchar;
                }
            }
            phandler->ReleaseRecords(res);
        }

        sstr.str("");
        // 找到最近一天起始数据则与最后一个结束数据相减
        if (!tmp_strat_day.empty())
        {
            sstr << "SELECT r1-r2,r3-r4,r5-r6 FROM (SELECT "
                << " a." << gszAgencyCommissRecodeColName[AgyCRT_InfoMatchTotal] << " r1,"
                << " b." << gszAgencyCommissRecodeColName[AgyCRT_InfoMatchTotal] << " r2,"
                << " a." << gszAgencyCommissRecodeColName[AgyCRT_TradeFeeTotal] << " r3,"
                << " b." << gszAgencyCommissRecodeColName[AgyCRT_TradeFeeTotal] << " r4,"
                << " a." << gszAgencyCommissRecodeColName[AgyCRT_CommissionTotal] << " r5,"
                << " b." << gszAgencyCommissRecodeColName[AgyCRT_CommissionTotal] << " r6 "
                << " FROM " << gszAgencyCommissRecodeTableName << " a, " << gszAgencyCommissRecodeTableName << " b "
                << " WHERE a." << gszAgencyCommissRecodeColName[AgyCRT_UserID] << " = '" << user_id << "' "
                << " AND a." << gszAgencyCommissRecodeColName[AgyCRT_Date] << " = '" << tmp_end_day << "' "
                << " AND b." << gszAgencyCommissRecodeColName[AgyCRT_UserID] << " = '" << user_id << "' "
                << " AND b." << gszAgencyCommissRecodeColName[AgyCRT_Date] << " = '" << tmp_strat_day << "' "
                << ") " << gszAgencyCommissRecodeTableName;

            errCode = phandler->QuerySql(sstr.str().c_str(), res, true);
            if (errCode != 0)
                LOG4CXX_ERROR(logger, "查询佣金信息失败!"LOG_NOVAR(sstr.str().c_str()));

            if (errCode == 0 && res)
            {
                HxResRow row = NULL;
                if (row = phandler->FetchRow(res))
                {
                    char* pchar = phandler->FetchField(row, 0);
                    infomatch = atof(pchar);
                    pchar = phandler->FetchField(row, 1);
                    tradefee = atof(pchar);
                    pchar = phandler->FetchField(row, 2);
                    comm_all = atof(pchar);
                }
            }

            phandler->ReleaseRecords(res);
        }
        // 未找到最近一天数据则直接返回最终天的数据
        else
        {
            sstr << "SELECT " << gszAgencyCommissRecodeColName[AgyCRT_InfoMatchTotal] << ","
                << gszAgencyCommissRecodeColName[AgyCRT_TradeFeeTotal] << ","
                << gszAgencyCommissRecodeColName[AgyCRT_CommissionTotal] << " "
                << " FROM " << gszAgencyCommissRecodeTableName
                << " WHERE " << gszAgencyCommissRecodeColName[AgyCRT_UserID] << " = '" << user_id << "' "
                << " AND " << gszAgencyCommissRecodeColName[AgyCRT_Date] << " = '" << tmp_end_day << "';";

            errCode = phandler->QuerySql(sstr.str().c_str(), res, true);
            if (errCode != 0)
                LOG4CXX_ERROR(logger, "查询佣金信息失败!"LOG_NOVAR(sstr.str().c_str()));

            if (errCode == 0 && res)
            {
                HxResRow row = NULL;
                if (row = phandler->FetchRow(res))
                {
                    char* pchar = phandler->FetchField(row, 0);
                    infomatch = atof(pchar);
                    pchar = phandler->FetchField(row, 1);
                    tradefee = atof(pchar);
                    pchar = phandler->FetchField(row, 2);
                    comm_all = atof(pchar);
                }
            }

            phandler->ReleaseRecords(res);
        }

        DBAccess::FreeDBHandler(phandler);
        return errCode == 0;
    }

    std::vector<AllTrade::NPMgrCenter::SAgencyMoneyDetailInfoPtr> DBOpManagerCenter::qryAgencyCommissDtlInfo(const AllTrade::UserIDType user_id, const AllTrade::DateType start_day, const AllTrade::DateType end_day)
    {
        std::vector<AllTrade::NPMgrCenter::SAgencyMoneyDetailInfoPtr> rslts;
        CDBHandler *phandler = AllocDBHandler();
        if (!phandler)
            return rslts;

        HxSqlRes res = NULL;
        int errCode = 0;
        int recNum = 0;

        std::stringstream sstr;
        sstr << "SELECT * FROM " << gszAgencyCommissionChangeTableName << " WHERE "
            << gszAgencyCommissionChangeColName[AgyCCT_UserID] << " = '" << user_id << "' "
            << " AND " << gszAgencyCommissionChangeColName[AgyCCT_Time] << " >= '" << start_day << "'"
            << " AND " << gszAgencyCommissionChangeColName[AgyCCT_Time] << " <= '" << end_day << "';";

        std::string tmp = sstr.str();
        errCode = phandler->QuerySql(sstr.str().c_str(), res, true);
        if (errCode != 0)
            LOG4CXX_ERROR(logger, "获取佣金流水信息失败!"LOG_NOVAR(sstr.str().c_str()));

        if (errCode == 0 && res)
        {
            HxResRow row = NULL;
            while (row = phandler->FetchRow(res))
            {
                SAgencyMoneyDetailInfoPtr ptr = std::make_shared<SAgencyMoneyDetailInfo>();
                char *pchar;
                pchar = phandler->FetchField(row, AgyCCT_Before);
                ptr->total_before_ = atof(pchar);
                pchar = phandler->FetchField(row, AgyCCT_After);
                ptr->total_after_ = atof(pchar);
                pchar = phandler->FetchField(row, AgyCCT_CommissionRate);
                ptr->commission_rate_ = atof(pchar);
                pchar = phandler->FetchField(row, AgyCCT_ChangeMoney);
                ptr->change_money_ = atof(pchar);
                pchar = phandler->FetchField(row, AgyCCT_Type);
                ptr->change_type_ = (Agency_Money_Change_Type)atoi(pchar);

                strncpy_s(ptr->user_id_, phandler->FetchField(row, AgyCCT_UserID), sizeof(ptr->user_id_) - 1);
                strncpy_s(ptr->source_user_id_, phandler->FetchField(row, AgyCCT_SourceUserID), sizeof(ptr->source_user_id_) - 1);
                strncpy_s(ptr->remark_, phandler->FetchField(row, AgyCCT_Remark), sizeof(ptr->remark_) - 1);
                strncpy_s(ptr->date_time_, phandler->FetchField(row, AgyCCT_Time), sizeof(ptr->date_time_) - 1);

                rslts.push_back(ptr);
            }
        }

        phandler->ReleaseRecords(res);
        DBAccess::FreeDBHandler(phandler);
        return rslts;
    }

    bool DBOpManagerCenter::qryAgencyProfitInfo(const AllTrade::UserIDType user_id, const AllTrade::DateType start_day, const AllTrade::DateType end_day, YDouble& profit)
    {
        CDBHandler *phandler = AllocDBHandler();
        if (!phandler)
            return false;

        HxSqlRes res = NULL;
        int errCode = 0;
        int recNum = 0;
        std::string tmp_strat_day, tmp_end_day;

        // 取出最接近的日期
        std::stringstream sstr;
        sstr << "SELECT MIN(" << gszAgencyProfitRecodeColName[AgyPRT_Date] << ")" << ",MAX(" << gszAgencyProfitRecodeColName[AgyPRT_Date] << ")"
            << " FROM " << gszAgencyProfitRecodeTableName
            << " WHERE " << gszAgencyProfitRecodeColName[AgyPRT_UserID] << " = '" << user_id << "' "
            << " AND " << gszAgencyProfitRecodeColName[AgyPRT_Date] << " <= '" << end_day << "' "
            << " AND " << gszAgencyProfitRecodeColName[AgyPRT_Date] << " >= '" << start_day << "' ";
        std::string tmp = sstr.str();
        errCode = phandler->QuerySql(sstr.str().c_str(), res, true);
        if (errCode != 0)
            LOG4CXX_ERROR(logger, "查询分成信息时选取语句失败!"LOG_NOVAR(sstr.str().c_str()));

        if (errCode == 0 && res)
        {
            HxResRow row = NULL;
            if (row = phandler->FetchRow(res))
            {
                char* pchar = phandler->FetchField(row, 0);
                if (pchar)
                    tmp_strat_day = pchar;

                pchar = phandler->FetchField(row, 1);
                if (pchar)
                    tmp_end_day = pchar;
            }
        }

        phandler->ReleaseRecords(res);
        if (tmp_end_day.empty())
        {
            DBAccess::FreeDBHandler(phandler);
            return errCode == 0;
        }

        // 找到最近一天
        if (tmp_end_day == tmp_strat_day)
        {
            sstr.str("");
            sstr << "SELECT MAX(" << gszAgencyProfitRecodeColName[AgyPRT_Date] << ")"
                << " FROM " << gszAgencyProfitRecodeTableName
                << " WHERE " << gszAgencyProfitRecodeColName[AgyPRT_UserID] << " = '" << user_id << "' "
                << " AND " << gszAgencyProfitRecodeColName[AgyPRT_Date] << " < '" << tmp_strat_day << "' ";

            tmp_strat_day.clear();
            errCode = phandler->QuerySql(sstr.str().c_str(), res, true);
            if (errCode != 0)
                LOG4CXX_ERROR(logger, "查询分成信息起始时间选取语句失败!"LOG_NOVAR(sstr.str().c_str()));

            if (errCode == 0 && res)
            {
                HxResRow row = NULL;
                if (row = phandler->FetchRow(res))
                {
                    char* pchar = phandler->FetchField(row, 0);
                    if (pchar)
                        tmp_strat_day = pchar;
                }
            }
            phandler->ReleaseRecords(res);
        }

        sstr.str("");
        // 找到最近一天起始数据则与最后一个结束数据相减
        if (!tmp_strat_day.empty())
        {
            sstr << "SELECT r1-r2 FROM (SELECT "
                << " a." << gszAgencyProfitRecodeColName[AgyPRT_ProfitTotal] << " r1,"
                << " b." << gszAgencyProfitRecodeColName[AgyPRT_ProfitTotal] << " r2"
                << " FROM " << gszAgencyProfitRecodeTableName << " a, " << gszAgencyProfitRecodeTableName << " b "
                << " WHERE a." << gszAgencyProfitRecodeColName[AgyPRT_UserID] << " = '" << user_id << "' "
                << " AND a." << gszAgencyProfitRecodeColName[AgyPRT_Date] << " = '" << tmp_end_day << "' "
                << " AND b." << gszAgencyProfitRecodeColName[AgyPRT_UserID] << " = '" << user_id << "' "
                << " AND b." << gszAgencyProfitRecodeColName[AgyPRT_Date] << " = '" << tmp_strat_day << "' "
                << ") " << gszAgencyProfitRecodeTableName;

            errCode = phandler->QuerySql(sstr.str().c_str(), res, true);
            if (errCode != 0)
                LOG4CXX_ERROR(logger, "查询分成信息失败!"LOG_NOVAR(sstr.str().c_str()));

            if (errCode == 0 && res)
            {
                HxResRow row = NULL;
                if (row = phandler->FetchRow(res))
                {
                    char* pchar = phandler->FetchField(row, 0);
                    if (pchar)
                        profit = atof(pchar);
                }
            }

            phandler->ReleaseRecords(res);
        }
        // 未找到最近一天数据则直接返回最终天的数据
        else
        {
            sstr << "SELECT " << gszAgencyProfitRecodeColName[AgyPRT_ProfitTotal] << " "
                << " FROM " << gszAgencyProfitRecodeTableName
                << " WHERE " << gszAgencyProfitRecodeColName[AgyPRT_UserID] << " = '" << user_id << "' "
                << " AND " << gszAgencyProfitRecodeColName[AgyPRT_Date] << " = '" << tmp_end_day << "';";

            errCode = phandler->QuerySql(sstr.str().c_str(), res, true);
            if (errCode != 0)
                LOG4CXX_ERROR(logger, "查询分成信息失败!"LOG_NOVAR(sstr.str().c_str()));

            if (errCode == 0 && res)
            {
                HxResRow row = NULL;
                if (row = phandler->FetchRow(res))
                {
                    char* pchar = phandler->FetchField(row, 0);
                    if (pchar)
                        profit = atof(pchar);
                }
            }

            phandler->ReleaseRecords(res);
        }

        DBAccess::FreeDBHandler(phandler);
        return errCode == 0;
    }

    std::vector<AllTrade::NPMgrCenter::SAgencyMoneyDetailInfoPtr> DBOpManagerCenter::qryAgencyProfitDtlInfo(const AllTrade::UserIDType user_id, const AllTrade::DateType start_day, const AllTrade::DateType end_day)
    {
        std::vector<AllTrade::NPMgrCenter::SAgencyMoneyDetailInfoPtr> rslts;
        CDBHandler *phandler = AllocDBHandler();
        if (!phandler)
            return rslts;

        HxSqlRes res = NULL;
        int errCode = 0;
        int recNum = 0;

        std::stringstream sstr;
        sstr << "SELECT * FROM " << gszAgencyProfitChangeTableName << " WHERE "
            << gszAgencyProfitChangeColName[AgyPCT_UserID] << " = '" << user_id << "' "
            << " AND " << gszAgencyProfitChangeColName[AgyPCT_Time] << " >= '" << start_day << "'"
            << " AND " << gszAgencyProfitChangeColName[AgyPCT_Time] << " <= '" << end_day << "';";

        std::string tmp = sstr.str();
        errCode = phandler->QuerySql(sstr.str().c_str(), res, true);
        if (errCode != 0)
            LOG4CXX_ERROR(logger, "获取分成流水信息失败!"LOG_NOVAR(sstr.str().c_str()));

        if (errCode == 0 && res)
        {
            HxResRow row = NULL;
            while (row = phandler->FetchRow(res))
            {
                SAgencyMoneyDetailInfoPtr ptr = std::make_shared<SAgencyMoneyDetailInfo>();
                char *pchar;
                pchar = phandler->FetchField(row, AgyPCT_Before);
                ptr->total_before_ = atof(pchar);
                pchar = phandler->FetchField(row, AgyPCT_After);
                ptr->total_after_ = atof(pchar);
                pchar = phandler->FetchField(row, AgyPCT_CommissionRate);
                ptr->commission_rate_ = atof(pchar);
                pchar = phandler->FetchField(row, AgyPCT_ChangeMoney);
                ptr->change_money_ = atof(pchar);
                pchar = phandler->FetchField(row, AgyPCT_Type);
                ptr->change_type_ = (Agency_Money_Change_Type)atoi(pchar);

                strncpy_s(ptr->user_id_, phandler->FetchField(row, AgyPCT_UserID), sizeof(ptr->user_id_) - 1);
                strncpy_s(ptr->source_user_id_, phandler->FetchField(row, AgyPCT_SourceUserID), sizeof(ptr->source_user_id_) - 1);
                strncpy_s(ptr->remark_, phandler->FetchField(row, AgyPCT_Remark), sizeof(ptr->remark_) - 1);
                strncpy_s(ptr->date_time_, phandler->FetchField(row, AgyPCT_Time), sizeof(ptr->date_time_) - 1);

                rslts.push_back(ptr);
            }
        }

        phandler->ReleaseRecords(res);
        DBAccess::FreeDBHandler(phandler);
        return rslts;
    }


	bool DBOpManagerCenter::getInterestStatisticsTable(const AllTrade::UserIDType user_id, AllTrade::NPMgrCenter::InterestStatisticsPtr& rstInfo)
	{
		CDBHandler *phandler = AllocDBHandler();
		if (!phandler)
			return false;

		HxSqlRes res = NULL;
		int errCode = 0;
		int recNum = 0;

		std::stringstream sstr;
		sstr << "SELECT * FROM " << gszSumInterestTableName
			<< " WHERE " << gszSumInterestTableColName[SIT_UserId] << " = '" << user_id << "'; ";

		errCode = phandler->QuerySql(sstr.str().c_str(), res, true);

		if (errCode == 0 && res)
		{
			HxResRow row = NULL;

			while (row = phandler->FetchRow(res))
			{
			//	AllTrade::NPMgrCenter::InterestStatisticsPtr ptr = std::make_shared<AllTrade::NPMgrCenter::InterestStatistics>();
				char *pchar;

				strncpy_s(rstInfo->user_id_, phandler->FetchField(row, SIT_UserId), sizeof(rstInfo->user_id_) - 1);

				pchar = phandler->FetchField(row, SIT_SumInterest);
				rstInfo->sum_interest_ = atof(pchar);

			//	rstInfo.emplace_back(ptr);
			}
		}

		phandler->ReleaseRecords(res);
		DBAccess::FreeDBHandler(phandler);
		return errCode == 0;
	}

	bool DBOpManagerCenter::updateInterestStatisticsTable( AllTrade::NPMgrCenter::InterestStatisticsPtr& ptrInfo)
	{
		CDBHandler *phandler = AllocDBHandler();
		if (!phandler)
			return false;

		int errCode = 0;

		std::stringstream sstr;
		sstr << "REPLACE INTO " << gszSumInterestTableName << " SET "
			<< gszSumInterestTableColName[SIT_UserId] << " = '" << ptrInfo->user_id_ << "', "
			<< gszSumInterestTableColName[SIT_SumInterest] << " = '" << ptrInfo->sum_interest_ << "',; ";
			

		errCode = phandler->ExecSql(sstr.str().c_str());
		if (errCode != 0)
			LOG4CXX_ERROR(logger, "更新利息累计信息失败!"LOG_NOVAR(sstr.str().c_str()));

		DBAccess::FreeDBHandler(phandler);
		return errCode == 0;
	}

	bool DBOpManagerCenter::getInterestDetailTable(const AllTrade::UserIDType user_id, std::vector<AllTrade::NPMgrCenter::InterestDetailPtr>& rstInfo)
	{
		CDBHandler *phandler = AllocDBHandler();
		if (!phandler)
			return false;

		HxSqlRes res = NULL;
		int errCode = 0;
		int recNum = 0;

		std::stringstream sstr;
		sstr << "SELECT * FROM " << gszInterestDetailTableName << " WHERE "
			<< " WHERE " << gszInterestDetailTableColName[InDT_UserId] << " = '" << user_id << "'; ";

		errCode = phandler->QuerySql(sstr.str().c_str(), res, true);

		if (errCode == 0 && res)
		{
			HxResRow row = NULL;
//			AllTrade::GUIDType userId;

			while (row = phandler->FetchRow(res))
			{
				AllTrade::NPMgrCenter::InterestDetailPtr ptr = std::make_shared<AllTrade::NPMgrCenter::InterestDetail>();
				char *pchar;

				strncpy_s(ptr->user_id_, phandler->FetchField(row, InDT_UserId), sizeof(ptr->user_id_) - 1);

				pchar = phandler->FetchField(row, InDT_InterestChange);
				ptr->sum_interest_ = atof(pchar);
				strncpy_s(ptr->date_time_, phandler->FetchField(row, InDT_ChanegTime), sizeof(ptr->date_time_) - 1);

				pchar = phandler->FetchField(row, InDT_ChangeType);
				ptr->change_type_ = (Agency_Money_Change_Type)atoi(pchar);
				strncpy_s(ptr->source_user_id_, phandler->FetchField(row, InDT_InterestSource), sizeof(ptr->source_user_id_) - 1);

				pchar = phandler->FetchField(row, InDT_InterestRate);
				ptr->interest_rate_ = atof(pchar);
				
				rstInfo.emplace_back(ptr);
			}
		}

		phandler->ReleaseRecords(res);
		DBAccess::FreeDBHandler(phandler);
		return errCode == 0;
	}

	bool DBOpManagerCenter::updateInterestDetailTable(AllTrade::NPMgrCenter::InterestDetailPtr& ptrInfo)
	{
		CDBHandler *phandler = AllocDBHandler();
		if (!phandler)
			return false;

		int errCode = 0;

		std::stringstream sstr;
		sstr << "REPLACE INTO " << gszInterestDetailTableName << " SET "
			<< gszInterestDetailTableColName[InDT_UserId] << " = '" << ptrInfo->user_id_ << "', "
			<< gszInterestDetailTableColName[InDT_InterestChange] << " = '" << ptrInfo->change_type_ << "', "
			<< gszInterestDetailTableColName[InDT_ChanegTime] << " = '" << ptrInfo->date_time_ << "', "
			<< gszInterestDetailTableColName[InDT_ChangeType] << " = '" << ptrInfo->change_type_ << "', "
			<< gszInterestDetailTableColName[InDT_InterestSource] << " = '" << ptrInfo->source_user_id_ << "', "
			<< gszInterestDetailTableColName[InDT_InterestRate] << " = '" << ptrInfo->interest_rate_ << "',; ";


		errCode = phandler->ExecSql(sstr.str().c_str());
		if (errCode != 0)
			LOG4CXX_ERROR(logger, "更新利息累计信息失败!"LOG_NOVAR(sstr.str().c_str()));

		DBAccess::FreeDBHandler(phandler);
		return errCode == 0;
	}

	bool DBOpManagerCenter::createInterestStatisticsTable()
	{
		CDBHandler *phandler = AllocDBHandler();
		if (!phandler)
			return false;

		int errCode = 0;

		std::stringstream sstr;
		sstr << "CREATE TABLE IF NOT EXISTS " << gszSumInterestTableName << " (";

		for (int i = 0; i < SIT_Max; i++)
		{
			sstr << gszSumInterestTableColName[i] << " " << gszSumInterestTableColType[i];
			if (i < SIT_Max - 1)
				sstr << ",";
		}
		sstr << ");";

		errCode = phandler->ExecSql(sstr.str().c_str());
		if (errCode != 0)
			LOG4CXX_ERROR(logger, "创建利息统计管理!"LOG_NOVAR(sstr.str().c_str()));

		DBAccess::FreeDBHandler(phandler);
		return errCode == 0;
	}

	bool DBOpManagerCenter::createInterestDetailTable()
	{
		CDBHandler *phandler = AllocDBHandler();
		if (!phandler)
			return false;

		int errCode = 0;

		std::stringstream sstr;
		sstr << "CREATE TABLE IF NOT EXISTS " << gszInterestDetailTableName << " (";

		for (int i = 0; i < InDT_Max; i++)
		{
			sstr << gszInterestDetailTableColName[i] << " " << gszInterestDetailTableColType[i];
			if (i < InDT_Max - 1)
				sstr << ",";
		}
		sstr << ");";

		errCode = phandler->ExecSql(sstr.str().c_str());
		if (errCode != 0)
			LOG4CXX_ERROR(logger, "创建利息明细管理!"LOG_NOVAR(sstr.str().c_str()));

		DBAccess::FreeDBHandler(phandler);
		return errCode == 0;
	}

}