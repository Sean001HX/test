#include <QJsonParseError>
#include <QString>
#include <QVariant>
#include <QJsonObject>
#include <QJsonArray>
#include <QVector>

#include "define/struct_extern.h"
#include "communition_struct_serialize.h"
#include "params_declare.h"
#include "struct_content.h"
#include "net_illustrate.h"
#include "communition_struct_define.h"
#include "Network/reply_message.h"
#include "utility/utility_fun.h"

using namespace AllTrade;
using namespace AllTrade::NPMgrCenter;
using namespace xyc_communication;

//////////////////////////////////////////////////////////////////////////
std::string toJson(AllTrade::ErrorCodeType result, const std::string& cmd_code)
{
    QJsonObject ob1;
    ob1[ERRCODE] = result;

    QJsonObject ob;
    ob[CMDCODE] = cmd_code.c_str();
    ob[CONTENT] = ob1;

    return QString(QJsonDocument(ob).toJson()).toUtf8().data();
}

void fromJson(xyc_communication::ReplyLoginMsg* msg_info, const std::string& json)
{
    QJsonParseError error;
    QJsonDocument jsonDocument = QJsonDocument::fromJson(QString::fromUtf8(json.c_str()).toUtf8(), &error);
    if (error.error == QJsonParseError::NoError) {
        if (jsonDocument.isObject())
        {
            auto rsltMap = jsonDocument.toVariant().toMap();
            strncpy_s(msg_info->m_login_name, rsltMap[LOGINNAME].toString().toLocal8Bit().data(), sizeof(msg_info->m_login_name) - 1);
            strncpy_s(msg_info->m_password, rsltMap[PASSWORD].toString().toLocal8Bit().data(), sizeof(msg_info->m_password) - 1);

            strncpy_s(msg_info->m_login_info->login_ip_, rsltMap[LOGINIP].toString().toLocal8Bit().data(), sizeof(msg_info->m_login_info->login_ip_) - 1);
            strncpy_s(msg_info->m_login_info->mac_info_, rsltMap[MACADDRESS].toString().toLocal8Bit().data(), sizeof(msg_info->m_login_info->mac_info_) - 1);
            strncpy_s(msg_info->m_login_info->login_datetime_, UtilityFun::getCurrentDateTime().c_str(), sizeof(msg_info->m_login_info->login_datetime_) - 1);
            msg_info->m_login_info->op_type_ = (OperatorTradeType)rsltMap[RESOURCE].toInt();
        }
    }
}

std::string toJson(xyc_communication::ReplyLoginMsgPtr msg_info)
{
    QMap<QString, QVariant> m_map;

    QMap<QString, QVariant> map_cont;

    map_cont.insert(ERRCODE, msg_info->getResult());
    map_cont.insert(LOGINNAME, QString::fromLocal8Bit(msg_info->m_login_name));
    map_cont.insert(PASSWORD, QString::fromLocal8Bit(msg_info->m_password));

    if (msg_info->m_rtn_acc)
    {
        map_cont.insert(ACCOUNTNAME, QString::fromLocal8Bit(msg_info->m_rtn_acc->account_name_));
        map_cont.insert(POPULARLINK, QString::fromLocal8Bit(msg_info->m_rtn_acc->agent_link_));
        map_cont.insert(ACCOUNTSTATUS, msg_info->m_rtn_acc->status_);
        map_cont.insert(ACCOUNTTYPE, msg_info->m_rtn_acc->type_);
        map_cont.insert(ACCOUNTPROP, msg_info->m_rtn_acc->prop_);

        if (msg_info->m_rtn_acc->prop_ == E_ACCOUNT_PROP::EAP_Manager)
        {
            map_cont.insert(ROOTMANAGERORNOT, msg_info->m_rtn_acc->level_ == 1);
            map_cont.insert(UPPERMANAGER, QString::fromLocal8Bit(msg_info->m_parent_login_name));
        }
    }

    m_map.insert(CMDCODE, msg_info->getCmdCode().c_str());
    m_map.insert(CONTENT, map_cont);

    QJsonDocument doc = QJsonDocument::fromVariant(QVariant(m_map));
    return QString(doc.toJson()).toUtf8().data();
}

// void fromJson(xyc_communication::ReplyAgencyQryMsg* msg_info, const std::string& json)
// {
//     QJsonParseError error;
//     QJsonDocument jsonDocument = QJsonDocument::fromJson(QString::fromUtf8(json.c_str()).toUtf8(), &error);
//     if (error.error == QJsonParseError::NoError) {
//         if (jsonDocument.isObject())
//         {
//             auto rsltMap = jsonDocument.toVariant().toMap();
//             strncpy_s(msg_info->m_qryLoginName, rsltMap[LOGINNAME].toString().toLocal8Bit().data(), sizeof(msg_info->m_qryLoginName) - 1);
//         }
//     }
// }

std::string toJson(xyc_communication::ReplyAgencyQryMsgPtr msg_info)
{
    QMap<QString, QVariant> m_map;

    QMap<QString, QVariant> map_cont;

    map_cont.insert(ERRCODE, msg_info->getResult());
    map_cont.insert(BLAST, msg_info->m_blast);
    if (!msg_info->m_blast)
    {
        map_cont.insert(LOGINNAME, QString::fromLocal8Bit(msg_info->m_rtn_agency->login_name_));
        map_cont.insert(ACCOUNTNAME, QString::fromLocal8Bit(msg_info->m_rtn_agency->account_name_));
        map_cont.insert(PASSWORD, QString::fromLocal8Bit(msg_info->m_rtn_agency->password_));
        map_cont.insert(TELNO, QString::fromLocal8Bit(msg_info->m_rtn_agency->phone_number_));
        map_cont.insert(ACCOUNTTYPE, msg_info->m_rtn_agency->type_);
        map_cont.insert(UPPERMANAGER, QString::fromLocal8Bit(msg_info->m_rtn_parent_login_name));
        map_cont.insert(COMMISSIONRATE, (double)msg_info->m_rtn_risk->commissionrate_);
        map_cont.insert(MATCHFEERATE, (double)msg_info->m_rtn_risk->custom_commissionrate_);
        map_cont.insert(PROCOMMRATE, (double)msg_info->m_rtn_risk->procommrate_);
        map_cont.insert(ACCOUNTSTATUS, msg_info->m_rtn_agency->status_);
        map_cont.insert(BINDFUNDLOGINNAME, QString::fromLocal8Bit(msg_info->m_fund_login_name));
    }

    m_map.insert(CMDCODE, msg_info->getCmdCode().c_str());
    m_map.insert(CONTENT, map_cont);

    QJsonDocument doc = QJsonDocument::fromVariant(QVariant(m_map));
    return QString(doc.toJson()).toUtf8().data();
}

// void fromJson(xyc_communication::ReplyAgencyPreApprovalQryMsg* msg_info, const std::string& json)
// {
//     QJsonParseError error;
//     QJsonDocument jsonDocument = QJsonDocument::fromJson(QString::fromUtf8(json.c_str()).toUtf8(), &error);
//     if (error.error == QJsonParseError::NoError) {
//         if (jsonDocument.isObject())
//         {
//             auto rsltMap = jsonDocument.toVariant().toMap();
//             strncpy_s(msg_info->m_qryLoginName, rsltMap[LOGINNAME].toString().toLocal8Bit().data(), sizeof(msg_info->m_qryLoginName) - 1);
//         }
//     }
// }

std::string toJson(xyc_communication::ReplyAgencyPreApprovalQryMsgPtr msg_info)
{
    QMap<QString, QVariant> m_map;

    QMap<QString, QVariant> map_cont;

    map_cont.insert(ERRCODE, msg_info->getResult());
    map_cont.insert(BLAST, msg_info->m_blast);
    if (!msg_info->m_blast)
    {
        map_cont.insert(LOGINNAME, QString::fromLocal8Bit(msg_info->m_rtn_agency->login_name_));
        map_cont.insert(ACCOUNTNAME, QString::fromLocal8Bit(msg_info->m_rtn_agency->account_name_));
        map_cont.insert(PASSWORD, QString::fromLocal8Bit(msg_info->m_rtn_agency->password_));
        map_cont.insert(TELNO, QString::fromLocal8Bit(msg_info->m_rtn_agency->phone_number_));
        map_cont.insert(ACCOUNTTYPE, msg_info->m_rtn_agency->type_);
        map_cont.insert(UPPERMANAGER, QString::fromLocal8Bit(msg_info->m_rtn_parent_login_name));
        map_cont.insert(COMMISSIONRATE, (double)msg_info->m_rtn_risk->commissionrate_);
        map_cont.insert(MATCHFEERATE, (double)msg_info->m_rtn_risk->custom_commissionrate_);
        map_cont.insert(PROCOMMRATE, (double)msg_info->m_rtn_risk->procommrate_);
        map_cont.insert(ACCOUNTSTATUS, msg_info->m_rtn_agency->status_);
        map_cont.insert(BINDFUNDLOGINNAME, QString::fromLocal8Bit(msg_info->m_fund_login_name));
    }

    m_map.insert(CMDCODE, msg_info->getCmdCode().c_str());
    m_map.insert(CONTENT, map_cont);

    QJsonDocument doc = QJsonDocument::fromVariant(QVariant(m_map));
    return QString(doc.toJson()).toUtf8().data();
}

///////////////////////////////////////////////////////////// 角色查询
//void fromJson(xyc_communication::ReplyRolesQryMsg* msg_info, const std::string& json)
//{
//	QJsonParseError error;
//	QJsonDocument jsonDocument = QJsonDocument::fromJson(QString::fromUtf8(json.c_str()).toUtf8(), &error);
//	if (error.error == QJsonParseError::NoError) {
//		if (jsonDocument.isObject())
//		{
//			auto rsltMap = jsonDocument.toVariant().toMap();
//			msg_info->prop_ = (E_ACCOUNT_PROP)rsltMap[ACCOUNTPROP].toInt();
//			// strncpy_s(msg_info->m_qryLoginName, rsltMap[LOGINNAME].toString().toLocal8Bit().data(), sizeof(msg_info->m_qryLoginName) - 1);
//		}
//	}
//}

std::string toJson(xyc_communication::ReplyRolesQryMsgPtr msg_info)
{
    QMap<QString, QVariant> m_map;

    QMap<QString, QVariant> map_cont;

    map_cont.insert(ERRCODE, msg_info->getResult());
    map_cont.insert(BLAST, msg_info->m_blast);
    if (!msg_info->m_blast)
    {
        map_cont.insert(ROLEID, msg_info->m_rtn_arp->rolesID);
        map_cont.insert(ROLESNAME, QString::fromLocal8Bit(msg_info->m_rtn_arp->rolesName));
        map_cont.insert(ROLETYPE, E_RolesType(msg_info->m_rtn_arp->rolesType));
		map_cont.insert(CREATELOGINNAME, QString::fromLocal8Bit(msg_info->m_rtn_arp->login_name_));
		map_cont.insert(OPERATIONTYPE, E_OperationType(msg_info->m_rtn_arp->operationType));
    }

    m_map.insert(CMDCODE, msg_info->getCmdCode().c_str());
    m_map.insert(CONTENT, map_cont);

    QJsonDocument doc = QJsonDocument::fromVariant(QVariant(m_map));
    return QString(doc.toJson()).toUtf8().data();
}

/////////////////////////////////////////////////////////////
// void fromJson(xyc_communication::ReplyChildAccQryMsg* msg_info, const std::string& json)
// {
//     QJsonParseError error;
//     QJsonDocument jsonDocument = QJsonDocument::fromJson(QString::fromUtf8(json.c_str()).toUtf8(), &error);
//     if (error.error == QJsonParseError::NoError) {
//         if (jsonDocument.isObject())
//         {
//             auto rsltMap = jsonDocument.toVariant().toMap();
//             strncpy_s(msg_info->m_qryLoginName, rsltMap[LOGINNAME].toString().toLocal8Bit().data(), sizeof(msg_info->m_qryLoginName) - 1);
//         }
//     }
// }

std::string toJson(xyc_communication::ReplyChildAccQryMsgPtr msg_info)
{
    QMap<QString, QVariant> m_map;
    QMap<QString, QVariant> map_cont;

    map_cont.insert(ERRCODE, msg_info->getResult());
    map_cont.insert(BLAST, msg_info->m_blast);
    if (!msg_info->m_blast)
    {
        map_cont.insert(LOGINNAME, QString::fromLocal8Bit(msg_info->m_rtn_acc->login_name_));
        map_cont.insert(ACCOUNTNAME, QString::fromLocal8Bit(msg_info->m_rtn_acc->account_name_));
        map_cont.insert(INFERIORFUND, (double)(msg_info->m_rtn_money->user_deposit_));
        map_cont.insert(PRIORITYFUND, (double)msg_info->m_rtn_money->priority_fund_);
        map_cont.insert(PASSWORD, QString::fromLocal8Bit(msg_info->m_rtn_acc->password_));
        map_cont.insert(UPPERFUNDNAME, QString::fromLocal8Bit(msg_info->m_rtn_fund_login_name));
        map_cont.insert(UPPERMANAGER, QString::fromLocal8Bit(msg_info->m_rtn_parent_login_name));
        map_cont.insert(WARNINGLINE, (double)msg_info->m_rtn_risk->warningline_);
        map_cont.insert(FORCELINE, (double)msg_info->m_rtn_risk->forceline_);
        map_cont.insert(LIMITLINE, (double)msg_info->m_rtn_risk->limitline_);
        map_cont.insert(LEVERAGERATE, (double)msg_info->m_rtn_risk->lever_rate_);
        map_cont.insert(COMMISSIONRATE, (double)msg_info->m_rtn_risk->commissionrate_);

//     map_cont.insert(PASSWORD, msg_info->m_rtn_acc->password_);
        map_cont.insert(ACCOUNTTYPE, msg_info->m_rtn_acc->type_);
        map_cont.insert(ACCOUNTSTATUS, msg_info->m_rtn_acc->status_);
    }

    m_map.insert(CMDCODE, msg_info->getCmdCode().c_str());
    m_map.insert(CONTENT, map_cont);

    QJsonDocument doc = QJsonDocument::fromVariant(QVariant(m_map));
    return QString(doc.toJson()).toUtf8().data();
}

// void fromJson(xyc_communication::ReplyChildApprovalQryMsg* msg_info, const std::string& json)
// {
//     QJsonParseError error;
//     QJsonDocument jsonDocument = QJsonDocument::fromJson(QString::fromUtf8(json.c_str()).toUtf8(), &error);
//     if (error.error == QJsonParseError::NoError) {
//         if (jsonDocument.isObject())
//         {
//             auto rsltMap = jsonDocument.toVariant().toMap();
//             strncpy_s(msg_info->m_qryLoginName, rsltMap[LOGINNAME].toString().toLocal8Bit().data(), sizeof(msg_info->m_qryLoginName) - 1);
//         }
//     }
// }

std::string toJson(xyc_communication::ReplyChildApprovalQryMsgPtr msg_info)
{
    QMap<QString, QVariant> m_map;
    QMap<QString, QVariant> map_cont;

    map_cont.insert(ERRCODE, msg_info->getResult());
    map_cont.insert(BLAST, msg_info->m_blast);
    if (!msg_info->m_blast)
    {
        map_cont.insert(LOGINNAME, QString::fromLocal8Bit(msg_info->m_rtn_acc->login_name_));
        map_cont.insert(ACCOUNTNAME, QString::fromLocal8Bit(msg_info->m_rtn_acc->account_name_));
        map_cont.insert(PASSWORD, QString::fromLocal8Bit(msg_info->m_rtn_acc->password_));
        map_cont.insert(INFERIORFUND, (double)(msg_info->m_rtn_money->user_deposit_));
        map_cont.insert(PRIORITYFUND, (double)msg_info->m_rtn_money->priority_fund_);
        map_cont.insert(UPPERFUNDNAME, QString::fromLocal8Bit(msg_info->m_rtn_fund_login_name));
        map_cont.insert(UPPERMANAGER, QString::fromLocal8Bit(msg_info->m_rtn_parent_login_name));
        map_cont.insert(WARNINGLINE, (double)msg_info->m_rtn_risk->warningline_);
        map_cont.insert(FORCELINE, (double)msg_info->m_rtn_risk->forceline_);
        map_cont.insert(LIMITLINE, (double)msg_info->m_rtn_risk->limitline_);
        map_cont.insert(LEVERAGERATE, (double)msg_info->m_rtn_risk->lever_rate_);
        map_cont.insert(COMMISSIONRATE, (double)msg_info->m_rtn_risk->commissionrate_);

//     map_cont.insert(PASSWORD, msg_info->m_rtn_acc->password_);
        map_cont.insert(ACCOUNTTYPE, msg_info->m_rtn_acc->type_);
        map_cont.insert(ACCOUNTSTATUS, msg_info->m_rtn_acc->status_);

		map_cont.insert(CREATELOGINNAME, QString::fromLocal8Bit(msg_info->m_crLoginName));
		map_cont.insert(APPROVALLOGINNAME, QString::fromLocal8Bit(msg_info->m_rtn_acc->auditor_name_));
		map_cont.insert(APPROVALTIME, QString::fromLocal8Bit(msg_info->m_rtn_acc->auditor_datetime_));
    }

    m_map.insert(CMDCODE, msg_info->getCmdCode().c_str());
    m_map.insert(CONTENT, map_cont);

    QJsonDocument doc = QJsonDocument::fromVariant(QVariant(m_map));
    return QString(doc.toJson()).toUtf8().data();
}

void fromJson(xyc_communication::ReplyAgencyAddMsg* msg_info, const std::string& json)
{
    QJsonParseError error;
    QJsonDocument jsonDocument = QJsonDocument::fromJson(QString::fromUtf8(json.c_str()).toUtf8(), &error);
    if (error.error == QJsonParseError::NoError) {
        if (jsonDocument.isObject())
        {
            auto rsltMap = jsonDocument.toVariant().toMap();
//             strncpy_s(msg_info->m_creatorLoginName, rsltMap[CREATELOGINNAME].toString().toLocal8Bit().data(), sizeof(msg_info->m_creatorLoginName) - 1);

            strncpy_s(msg_info->m_rtn_acc->login_name_, rsltMap[LOGINNAME].toString().toLocal8Bit().data(), sizeof(msg_info->m_rtn_acc->login_name_) - 1);
            strncpy_s(msg_info->m_rtn_acc->account_name_, rsltMap[ACCOUNTNAME].toString().toLocal8Bit().data(), sizeof(msg_info->m_rtn_acc->account_name_) - 1);
            strncpy_s(msg_info->m_rtn_acc->phone_number_, rsltMap[TELNO].toString().toLocal8Bit().data(), sizeof(msg_info->m_rtn_acc->phone_number_) - 1);
            strncpy_s(msg_info->m_rtn_acc->password_, rsltMap[PASSWORD].toString().toLocal8Bit().data(), sizeof(msg_info->m_rtn_acc->password_) - 1);
            strncpy_s(msg_info->m_parent_login_name, rsltMap[UPPERMANAGER].toString().toLocal8Bit().data(), sizeof(msg_info->m_parent_login_name) - 1);
            msg_info->m_rtn_risk->commissionrate_ = rsltMap[COMMISSIONRATE].toDouble();
            msg_info->m_rtn_risk->custom_commissionrate_ = rsltMap[MATCHFEERATE].toDouble();
            msg_info->m_rtn_risk->procommrate_ = rsltMap[PROCOMMRATE].toDouble();

            msg_info->m_rtn_acc->type_ = (E_ACCOUNT_TYPE)rsltMap[ACCOUNTTYPE].toInt();
            strncpy_s(msg_info->m_fund_login_name, rsltMap[BINDFUNDLOGINNAME].toString().toLocal8Bit().data(), sizeof(msg_info->m_fund_login_name) - 1);
        }
    }
}

std::string toJson(xyc_communication::ReplyAgencyAddMsgPtr msg_info)
{
    QMap<QString, QVariant> m_map;

    QMap<QString, QVariant> map_cont;

    map_cont.insert(ERRCODE, msg_info->getResult());
    map_cont.insert(CREATELOGINNAME, QString::fromLocal8Bit(msg_info->getLoginName().c_str()));
    map_cont.insert(ACCOUNTNAME, QString::fromLocal8Bit(msg_info->m_rtn_acc->account_name_));
    map_cont.insert(LOGINNAME, QString::fromLocal8Bit(msg_info->m_rtn_acc->login_name_));
    map_cont.insert(PASSWORD, QString::fromLocal8Bit(msg_info->m_rtn_acc->password_));
    map_cont.insert(TELNO, QString::fromLocal8Bit(msg_info->m_rtn_acc->phone_number_));
    map_cont.insert(BINDFUNDLOGINNAME, QString::fromLocal8Bit(msg_info->m_fund_login_name));
    map_cont.insert(UPPERMANAGER, QString::fromLocal8Bit(msg_info->m_parent_login_name));
    map_cont.insert(PROCOMMRATE, (double)msg_info->m_rtn_risk->procommrate_);
    map_cont.insert(MATCHFEERATE, (double)msg_info->m_rtn_risk->custom_commissionrate_);
    map_cont.insert(COMMISSIONRATE, (double)msg_info->m_rtn_risk->commissionrate_);
    map_cont.insert(ACCOUNTTYPE, (int)msg_info->m_rtn_acc->type_);
    map_cont.insert(ACCOUNTSTATUS, msg_info->m_rtn_acc->status_);

    m_map.insert(CMDCODE, msg_info->getCmdCode().c_str());
    m_map.insert(CONTENT, map_cont);

    QJsonDocument doc = QJsonDocument::fromVariant(QVariant(m_map));
    return QString(doc.toJson()).toUtf8().data();
}

void fromJson(xyc_communication::ReplyAgencyChangeMsg* msg_info, const std::string& json)
{
    QJsonParseError error;
    QJsonDocument jsonDocument = QJsonDocument::fromJson(QString::fromUtf8(json.c_str()).toUtf8(), &error);
    if (error.error == QJsonParseError::NoError) {
        if (jsonDocument.isObject())
        {
            auto rsltMap = jsonDocument.toVariant().toMap();
//             strncpy_s(msg_info->m_creatorLoginName, rsltMap[CREATELOGINNAME].toString().toLocal8Bit().data(), sizeof(msg_info->m_creatorLoginName) - 1);

            strncpy_s(msg_info->m_rtn_acc->account_name_, rsltMap[ACCOUNTNAME].toString().toLocal8Bit().data(), sizeof(msg_info->m_rtn_acc->account_name_) - 1);
            strncpy_s(msg_info->m_rtn_acc->login_name_, rsltMap[LOGINNAME].toString().toLocal8Bit().data(), sizeof(msg_info->m_rtn_acc->login_name_) - 1);
            strncpy_s(msg_info->m_rtn_acc->password_, rsltMap[PASSWORD].toString().toLocal8Bit().data(), sizeof(msg_info->m_rtn_acc->password_) - 1);
            strncpy_s(msg_info->m_fund_login_name, rsltMap[BINDFUNDLOGINNAME].toString().toLocal8Bit().data(), sizeof(msg_info->m_fund_login_name) - 1);
            strncpy_s(msg_info->m_parent_login_name, rsltMap[UPPERMANAGER].toString().toLocal8Bit().data(), sizeof(msg_info->m_parent_login_name) - 1);
            msg_info->m_rtn_acc->type_ = (E_ACCOUNT_TYPE)rsltMap[ACCOUNTTYPE].toInt();
            strncpy_s(msg_info->m_rtn_acc->phone_number_, rsltMap[TELNO].toString().toLocal8Bit().data(), sizeof(msg_info->m_rtn_acc->phone_number_) - 1);

            msg_info->m_rtn_risk->lever_rate_ = rsltMap[LEVERAGERATE].toDouble();
            msg_info->m_rtn_risk->commissionrate_ = rsltMap[COMMISSIONRATE].toDouble();
            msg_info->m_rtn_risk->procommrate_ = rsltMap[PROCOMMRATE].toDouble();
            msg_info->m_rtn_risk->custom_commissionrate_ = rsltMap[MATCHFEERATE].toDouble();
        }
    }
}

std::string toJson(xyc_communication::ReplyAgencyChangeMsgPtr msg_info)
{
    QMap<QString, QVariant> m_map;

    QMap<QString, QVariant> map_cont;

    map_cont.insert(ERRCODE, msg_info->getResult());
    map_cont.insert(CREATELOGINNAME, QString::fromLocal8Bit(msg_info->getLoginName().c_str()));
    map_cont.insert(ACCOUNTNAME, QString::fromLocal8Bit(msg_info->m_rtn_acc->account_name_));
    map_cont.insert(LOGINNAME, QString::fromLocal8Bit(msg_info->m_rtn_acc->login_name_));
    map_cont.insert(PASSWORD, QString::fromLocal8Bit(msg_info->m_rtn_acc->password_));
    map_cont.insert(BINDFUNDLOGINNAME, QString::fromLocal8Bit(msg_info->m_fund_login_name));
    map_cont.insert(UPPERMANAGER, QString::fromLocal8Bit(msg_info->m_parent_login_name));
    map_cont.insert(PROCOMMRATE, (double)msg_info->m_rtn_risk->procommrate_);
    map_cont.insert(COMMISSIONRATE, (double)msg_info->m_rtn_risk->commissionrate_);
    map_cont.insert(MATCHFEERATE, (double)msg_info->m_rtn_risk->custom_commissionrate_);
    map_cont.insert(ACCOUNTTYPE, msg_info->m_rtn_acc->type_);
    map_cont.insert(TELNO, msg_info->m_rtn_acc->phone_number_);
    map_cont.insert(ACCOUNTSTATUS, msg_info->m_rtn_acc->status_);

    m_map.insert(CMDCODE, msg_info->getCmdCode().c_str());
    m_map.insert(CONTENT, map_cont);

    QJsonDocument doc = QJsonDocument::fromVariant(QVariant(m_map));
    return QString(doc.toJson()).toUtf8().data();
}

void fromJson(xyc_communication::ReplyAgencyApprovalMsg* msg_info, const std::string& json)
{
    QJsonParseError error;
    QJsonDocument jsonDocument = QJsonDocument::fromJson(QString::fromUtf8(json.c_str()).toUtf8(), &error);
    if (error.error == QJsonParseError::NoError) {
        if (jsonDocument.isObject())
        {
            auto rsltMap = jsonDocument.toVariant().toMap();
//             strncpy_s(msg_info->m_opLoginName, rsltMap[CREATELOGINNAME].toString().toLocal8Bit().data(), sizeof(msg_info->m_opLoginName) - 1);
            strncpy_s(msg_info->m_acc_login_name, rsltMap[LOGINNAME].toString().toLocal8Bit().data(), sizeof(msg_info->m_acc_login_name) - 1);
            msg_info->m_bApproval = (E_ACCOUNT_STATUS)rsltMap[ACCOUNTSTATUS].toInt();
        }
    }
}

std::string toJson(xyc_communication::ReplyAgencyApprovalMsgPtr msg_info)
{
    QMap<QString, QVariant> m_map;

    QMap<QString, QVariant> map_cont;

    map_cont.insert(ERRCODE, msg_info->getResult());
    map_cont.insert(ACCOUNTNAME, QString::fromLocal8Bit(msg_info->m_rtn_acc->account_name_));
    map_cont.insert(LOGINNAME, QString::fromLocal8Bit(msg_info->m_rtn_acc->login_name_));
    map_cont.insert(PASSWORD, QString::fromLocal8Bit(msg_info->m_rtn_acc->password_));
    map_cont.insert(TELNO, QString::fromLocal8Bit(msg_info->m_rtn_acc->phone_number_));
    map_cont.insert(UPPERMANAGER, QString::fromLocal8Bit(msg_info->m_parent_login_name));
    map_cont.insert(BINDFUNDLOGINNAME, QString::fromLocal8Bit(msg_info->m_fund_login_name));
    map_cont.insert(PROCOMMRATE, (double)msg_info->m_rtn_risk->procommrate_);
    map_cont.insert(MATCHFEERATE, (double)msg_info->m_rtn_risk->custom_commissionrate_);
    map_cont.insert(COMMISSIONRATE, (double)msg_info->m_rtn_risk->commissionrate_);
    map_cont.insert(ACCOUNTTYPE, (int)msg_info->m_rtn_acc->type_);
    map_cont.insert(ACCOUNTSTATUS, msg_info->m_rtn_acc->status_);

    map_cont.insert(LOGINNAME, msg_info->m_acc_login_name);

    m_map.insert(CMDCODE, msg_info->getCmdCode().c_str());
    m_map.insert(CONTENT, map_cont);

    QJsonDocument doc = QJsonDocument::fromVariant(QVariant(m_map));
    return QString(doc.toJson()).toUtf8().data();
}

void fromJson(xyc_communication::ReplyChildAccAddMsg* msg_info, const std::string& json)
{
    QJsonParseError error;
    QJsonDocument jsonDocument = QJsonDocument::fromJson(QString::fromUtf8(json.c_str()).toUtf8(), &error);
    if (error.error == QJsonParseError::NoError) {
        if (jsonDocument.isObject())
        {
            auto rsltMap = jsonDocument.toVariant().toMap();
//             strncpy_s(msg_info->m_creatorLoginName, rsltMap[CREATELOGINNAME].toString().toLocal8Bit().data(), sizeof(msg_info->m_creatorLoginName) - 1);

            strncpy_s(msg_info->m_rtn_acc->account_name_, rsltMap[ACCOUNTNAME].toString().toLocal8Bit().data(), sizeof(msg_info->m_rtn_acc->account_name_) - 1);
            strncpy_s(msg_info->m_rtn_acc->login_name_, rsltMap[LOGINNAME].toString().toLocal8Bit().data(), sizeof(msg_info->m_rtn_acc->login_name_) - 1);
            strncpy_s(msg_info->m_rtn_acc->password_, rsltMap[PASSWORD].toString().toLocal8Bit().data(), sizeof(msg_info->m_rtn_acc->password_) - 1);
            strncpy_s(msg_info->m_fund_login_name, rsltMap[UPPERFUNDNAME].toString().toLocal8Bit().data(), sizeof(msg_info->m_fund_login_name) - 1);
            strncpy_s(msg_info->m_parent_login_name, rsltMap[UPPERMANAGER].toString().toLocal8Bit().data(), sizeof(msg_info->m_parent_login_name) - 1);
            msg_info->m_rtn_acc->type_ = (E_ACCOUNT_TYPE)rsltMap[ACCOUNTTYPE].toInt();

            msg_info->m_rtn_money->addDeposit(rsltMap[INFERIORFUND].toDouble());
            msg_info->m_rtn_money->addEquipment(rsltMap[PRIORITYFUND].toDouble());

            msg_info->m_rtn_risk->warningline_ = rsltMap[WARNINGLINE].toDouble();
            msg_info->m_rtn_risk->forceline_ = rsltMap[FORCELINE].toDouble();
            msg_info->m_rtn_risk->limitline_ = rsltMap[LIMITLINE].toDouble();
            msg_info->m_rtn_risk->lever_rate_ = rsltMap[LEVERAGERATE].toDouble();
            msg_info->m_rtn_risk->commissionrate_ = rsltMap[COMMISSIONRATE].toDouble();
        }
    }
}

std::string toJson(xyc_communication::ReplyChildAccAddMsgPtr msg_info)
{
    QMap<QString, QVariant> m_map;

    QMap<QString, QVariant> map_cont;

    map_cont.insert(ERRCODE, msg_info->getResult());
    map_cont.insert(CREATELOGINNAME, QString::fromLocal8Bit(msg_info->getLoginName().c_str()));
    map_cont.insert(ACCOUNTNAME, QString::fromLocal8Bit(msg_info->m_rtn_acc->account_name_));
    map_cont.insert(LOGINNAME, QString::fromLocal8Bit(msg_info->m_rtn_acc->login_name_));
    map_cont.insert(PASSWORD, QString::fromLocal8Bit(msg_info->m_rtn_acc->password_));
    map_cont.insert(INFERIORFUND, (double)(msg_info->m_rtn_money->user_deposit_));
    map_cont.insert(PRIORITYFUND, (double)msg_info->m_rtn_money->priority_fund_);
    map_cont.insert(AVAILABLEFUNDS, (double)(msg_info->m_rtn_money->getCanUse()));
    map_cont.insert(AVAILABLEGETFUNDS, (double)(msg_info->m_rtn_money->getCanExtract()));
    map_cont.insert(OPENCOST, (double)(msg_info->m_rtn_money->position_cost_price_));
    map_cont.insert(UPPERFUNDNAME, QString::fromLocal8Bit(msg_info->m_fund_login_name));
    map_cont.insert(UPPERMANAGER, QString::fromLocal8Bit(msg_info->m_parent_login_name));
    map_cont.insert(WARNINGLINE, (double)msg_info->m_rtn_risk->warningline_);
    map_cont.insert(FORCELINE, (double)msg_info->m_rtn_risk->forceline_);
    map_cont.insert(LIMITLINE, (double)msg_info->m_rtn_risk->limitline_);
    map_cont.insert(LEVERAGERATE, (double)msg_info->m_rtn_risk->lever_rate_);
    map_cont.insert(COMMISSIONRATE, (double)msg_info->m_rtn_risk->commissionrate_);
    map_cont.insert(ACCOUNTTYPE, msg_info->m_rtn_acc->type_);
    map_cont.insert(ACCOUNTSTATUS, msg_info->m_rtn_acc->status_);

    m_map.insert(CMDCODE, msg_info->getCmdCode().c_str());
    m_map.insert(CONTENT, map_cont);

    QJsonDocument doc = QJsonDocument::fromVariant(QVariant(m_map));
    return QString(doc.toJson()).toUtf8().data();
}

void fromJson(xyc_communication::ReplyChildAccChangeMsg* msg_info, const std::string& json)
{
    QJsonParseError error;
    QJsonDocument jsonDocument = QJsonDocument::fromJson(QString::fromUtf8(json.c_str()).toUtf8(), &error);
    if (error.error == QJsonParseError::NoError) {
        if (jsonDocument.isObject())
        {
            auto rsltMap = jsonDocument.toVariant().toMap();
//             strncpy_s(msg_info->m_creatorLoginName, rsltMap[CREATELOGINNAME].toString().toLocal8Bit().data(), sizeof(msg_info->m_creatorLoginName) - 1);

            strncpy_s(msg_info->m_rtn_acc->account_name_, rsltMap[ACCOUNTNAME].toString().toLocal8Bit().data(), sizeof(msg_info->m_rtn_acc->account_name_) - 1);
            strncpy_s(msg_info->m_rtn_acc->login_name_, rsltMap[LOGINNAME].toString().toLocal8Bit().data(), sizeof(msg_info->m_rtn_acc->login_name_) - 1);
            strncpy_s(msg_info->m_rtn_acc->password_, rsltMap[PASSWORD].toString().toLocal8Bit().data(), sizeof(msg_info->m_rtn_acc->password_) - 1);
            strncpy_s(msg_info->m_fund_login_name, rsltMap[UPPERFUNDNAME].toString().toLocal8Bit().data(), sizeof(msg_info->m_fund_login_name) - 1);
            strncpy_s(msg_info->m_parent_login_name, rsltMap[UPPERMANAGER].toString().toLocal8Bit().data(), sizeof(msg_info->m_parent_login_name) - 1);
            msg_info->m_rtn_acc->type_ = (E_ACCOUNT_TYPE)rsltMap[ACCOUNTTYPE].toInt();

            msg_info->m_rtn_risk->warningline_ = rsltMap[WARNINGLINE].toDouble();
            msg_info->m_rtn_risk->forceline_ = rsltMap[FORCELINE].toDouble();
            msg_info->m_rtn_risk->limitline_ = rsltMap[LIMITLINE].toDouble();
            msg_info->m_rtn_risk->lever_rate_ = rsltMap[LEVERAGERATE].toDouble();
            msg_info->m_rtn_risk->commissionrate_ = rsltMap[COMMISSIONRATE].toDouble();
        }
    }
}

std::string toJson(xyc_communication::ReplyChildAccChangeMsgPtr msg_info)
{
    QMap<QString, QVariant> m_map;

    QMap<QString, QVariant> map_cont;

    map_cont.insert(ERRCODE, msg_info->getResult());
    map_cont.insert(CREATELOGINNAME, QString::fromLocal8Bit(msg_info->getLoginName().c_str()));
    map_cont.insert(ACCOUNTNAME, QString::fromLocal8Bit(msg_info->m_rtn_acc->account_name_));
    map_cont.insert(LOGINNAME, QString::fromLocal8Bit(msg_info->m_rtn_acc->login_name_));
    map_cont.insert(PASSWORD, QString::fromLocal8Bit(msg_info->m_rtn_acc->password_));
    map_cont.insert(UPPERFUNDNAME, QString::fromLocal8Bit(msg_info->m_fund_login_name));
    map_cont.insert(UPPERMANAGER, QString::fromLocal8Bit(msg_info->m_parent_login_name));
    map_cont.insert(WARNINGLINE, (double)msg_info->m_rtn_risk->warningline_);
    map_cont.insert(FORCELINE, (double)msg_info->m_rtn_risk->forceline_);
    map_cont.insert(LIMITLINE, (double)msg_info->m_rtn_risk->limitline_);
    map_cont.insert(LEVERAGERATE, (double)msg_info->m_rtn_risk->lever_rate_);
    map_cont.insert(COMMISSIONRATE, (double)msg_info->m_rtn_risk->commissionrate_);
    map_cont.insert(ACCOUNTTYPE, msg_info->m_rtn_acc->type_);
    map_cont.insert(INFERIORFUND, (double)(msg_info->m_rtn_money->user_deposit_));
    map_cont.insert(PRIORITYFUND, (double)msg_info->m_rtn_money->priority_fund_);
    map_cont.insert(ACCOUNTSTATUS, msg_info->m_rtn_acc->status_);

    m_map.insert(CMDCODE, msg_info->getCmdCode().c_str());
    m_map.insert(CONTENT, map_cont);

    QJsonDocument doc = QJsonDocument::fromVariant(QVariant(m_map));
    return QString(doc.toJson()).toUtf8().data();
}

void fromJson(xyc_communication::ReplyChildAccApprovalMsg* msg_info, const std::string& json)
{
    QJsonParseError error;
    QJsonDocument jsonDocument = QJsonDocument::fromJson(QString::fromUtf8(json.c_str()).toUtf8(), &error);
    if (error.error == QJsonParseError::NoError) {
        if (jsonDocument.isObject())
        {
            auto rsltMap = jsonDocument.toVariant().toMap();
			strncpy_s(msg_info->m_opLoginName, rsltMap[APPROVALLOGINNAME].toString().toLocal8Bit().data(), sizeof(msg_info->m_opLoginName) - 1);
            strncpy_s(msg_info->m_rtn_acc->login_name_, rsltMap[LOGINNAME].toString().toLocal8Bit().data(), sizeof(msg_info->m_rtn_acc->login_name_) - 1);
            msg_info->m_bApproval = (E_ACCOUNT_STATUS)rsltMap[ACCOUNTSTATUS].toInt();
        }
    }
}

std::string toJson(xyc_communication::ReplyChildAccApprovalMsgPtr msg_info)
{
    QMap<QString, QVariant> m_map;

    QMap<QString, QVariant> map_cont;

    map_cont.insert(ERRCODE, msg_info->getResult());
    map_cont.insert(LOGINNAME, QString::fromLocal8Bit(msg_info->m_rtn_acc->login_name_));
    map_cont.insert(ACCOUNTNAME, QString::fromLocal8Bit(msg_info->m_rtn_acc->account_name_));
    map_cont.insert(PASSWORD, QString::fromLocal8Bit(msg_info->m_rtn_acc->password_));
    map_cont.insert(INFERIORFUND, (double)(msg_info->m_rtn_money->user_deposit_));
    map_cont.insert(PRIORITYFUND, (double)msg_info->m_rtn_money->priority_fund_);
    map_cont.insert(UPPERFUNDNAME, QString::fromLocal8Bit(msg_info->m_rtn_fund_login_name));
    map_cont.insert(UPPERMANAGER, QString::fromLocal8Bit(msg_info->m_rtn_parent_login_name));
    map_cont.insert(WARNINGLINE, (double)msg_info->m_rtn_risk->warningline_);
    map_cont.insert(FORCELINE, (double)msg_info->m_rtn_risk->forceline_);
    map_cont.insert(LIMITLINE, (double)msg_info->m_rtn_risk->limitline_);
    map_cont.insert(LEVERAGERATE, (double)msg_info->m_rtn_risk->lever_rate_);
    map_cont.insert(COMMISSIONRATE, (double)msg_info->m_rtn_risk->commissionrate_);
    map_cont.insert(AVAILABLEFUNDS, (double)msg_info->m_rtn_money->getCanUse());

    //     map_cont.insert(PASSWORD, msg_info->m_rtn_acc->password_);
    map_cont.insert(ACCOUNTTYPE, msg_info->m_rtn_acc->type_);
    map_cont.insert(ACCOUNTSTATUS, (int)msg_info->m_rtn_acc->status_);

	map_cont.insert(CREATELOGINNAME, QString::fromLocal8Bit(msg_info->m_crLoginName));
	map_cont.insert(APPROVALLOGINNAME, QString::fromLocal8Bit(msg_info->m_rtn_acc->auditor_name_));
	map_cont.insert(APPROVALTIME, QString::fromLocal8Bit(msg_info->m_rtn_acc->auditor_datetime_));


    m_map.insert(CMDCODE, msg_info->getCmdCode().c_str());
    m_map.insert(CONTENT, map_cont);

    QJsonDocument doc = QJsonDocument::fromVariant(QVariant(m_map));
    return QString(doc.toJson()).toUtf8().data();
}

void fromJson(xyc_communication::ReplyChildAccInmoneyMsg* msg_info, const std::string& json)
{
    QJsonParseError error;
    QJsonDocument jsonDocument = QJsonDocument::fromJson(QString::fromUtf8(json.c_str()).toUtf8(), &error);
    if (error.error == QJsonParseError::NoError) {
        if (jsonDocument.isObject())
        {
            auto rsltMap = jsonDocument.toVariant().toMap();
            strncpy_s(msg_info->m_login_name, rsltMap[LOGINNAME].toString().toLocal8Bit().data(), sizeof(msg_info->m_login_name) - 1);
            switch ((OIMM_Change_Type)rsltMap[BUSINESSTYPE].toInt())
            {
            case AllTrade::OIMM_In_Deposit:
                msg_info->m_money_change = Money_Change_Type::MC_In_Deposit;
                break;
            case AllTrade::OIMM_In_Equipment:
                msg_info->m_money_change = Money_Change_Type::MC_In_Equipment;
                break;
            case AllTrade::OIMM_In_BlueAdd:
                msg_info->m_money_change = Money_Change_Type::MC_In_BlueAdd;
                break;
            case AllTrade::OIMM_Out_Deposit:
                msg_info->m_money_change = Money_Change_Type::MC_Out_Deposit;
                break;
            case AllTrade::OIMM_Out_Equipment:
                msg_info->m_money_change = Money_Change_Type::MC_Out_Equipment;
                break;
            case AllTrade::OIMM_Out_RedSub:
                msg_info->m_money_change = Money_Change_Type::MC_Out_RedSub;
                break;
            default:
                break;
            }
            msg_info->m_money = rsltMap[AMOUNTMONEY].toDouble();
            strncpy_s(msg_info->m_remark, rsltMap[REMARKSINFO].toString().toLocal8Bit().data(), sizeof(msg_info->m_remark) - 1);
        }
    }
}

std::string toJson(xyc_communication::ReplyChildAccInmoneyMsgPtr msg_info)
{
    QMap<QString, QVariant> m_map;

    QMap<QString, QVariant> map_cont;

    map_cont.insert(ERRCODE, msg_info->getResult());
    map_cont.insert(LOGINNAME, QString::fromLocal8Bit(msg_info->m_login_name));
    map_cont.insert(BUSINESSTYPE, (int)msg_info->m_money_change);
    map_cont.insert(AMOUNTMONEY, (double)msg_info->m_money);
    map_cont.insert(REMARKSINFO, QString::fromLocal8Bit(msg_info->m_remark));

    m_map.insert(CMDCODE, msg_info->getCmdCode().c_str());
    m_map.insert(CONTENT, map_cont);

    QJsonDocument doc = QJsonDocument::fromVariant(QVariant(m_map));
    return QString(doc.toJson()).toUtf8().data();
}

// void fromJson(xyc_communication::ReplyFundAccQryMsg* msg_info, const std::string& json)
// {
//     QJsonParseError error;
//     QJsonDocument jsonDocument = QJsonDocument::fromJson(QString::fromUtf8(json.c_str()).toUtf8(), &error);
//     if (error.error == QJsonParseError::NoError) {
//         if (jsonDocument.isObject())
//         {
//             auto rsltMap = jsonDocument.toVariant().toMap();
//             strncpy_s(msg_info->m_qryLoginName, rsltMap[LOGINNAME].toString().toLocal8Bit().data(), sizeof(msg_info->m_qryLoginName) - 1);
//         }
//     }
// }

std::string toJson(xyc_communication::ReplyFundAccQryMsgPtr msg_info)
{
    QMap<QString, QVariant> m_map;
    QMap<QString, QVariant> map_cont;

    map_cont.insert(ERRCODE, msg_info->getResult());
    map_cont.insert(BLAST, msg_info->m_blast);
    if (!msg_info->m_blast)
    {
        map_cont.insert(ACCOUNTNAME, QString::fromLocal8Bit(msg_info->m_rtn_acc->account_name_));
        map_cont.insert(LOGINNAME, QString::fromLocal8Bit(msg_info->m_rtn_acc->login_name_));
        map_cont.insert(UPPERMANAGER, QString::fromLocal8Bit(msg_info->m_rtn_parent_login_name));
        map_cont.insert(SECURITIESCOMPANY, QString::fromLocal8Bit(msg_info->m_rtn_acc->fund_company_));
        map_cont.insert(INFERIORFUND, (double)(msg_info->m_rtn_money->user_deposit_));
        map_cont.insert(PRIORITYFUND, (double)msg_info->m_rtn_money->priority_fund_);
    }

    m_map.insert(CMDCODE, msg_info->getCmdCode().c_str());
    m_map.insert(CONTENT, map_cont);

    QJsonDocument doc = QJsonDocument::fromVariant(QVariant(m_map));
    return QString(doc.toJson()).toUtf8().data();
}

void fromJson(xyc_communication::ReplyStockContractQryMsg* msg_info, const std::string& json)
{
    QJsonParseError error;
    QJsonDocument jsonDocument = QJsonDocument::fromJson(QString::fromUtf8(json.c_str()).toUtf8(), &error);
    if (error.error == QJsonParseError::NoError) {
        if (jsonDocument.isObject())
        {
            auto rsltMap = jsonDocument.toVariant().toMap();
            strncpy_s(msg_info->m_exchange_code, rsltMap[EXCHANGECD].toString().toLocal8Bit().data(), sizeof(msg_info->m_exchange_code) - 1);
        }
    }
}

std::string toJson(xyc_communication::ReplyStockContractQryMsgPtr msg_info)
{
    QMap<QString, QVariant> m_map;
    QMap<QString, QVariant> map_cont;

    map_cont.insert(ERRCODE, msg_info->getResult());
    map_cont.insert(BLAST, msg_info->m_blast);
    if (!msg_info->m_blast)
    {
        map_cont.insert(STOCKCODE, QString::fromLocal8Bit(msg_info->m_stock_ptr->contract_code_));
        map_cont.insert(STOCKNAME, QString::fromLocal8Bit(msg_info->m_stock_ptr->contract_name_));
        map_cont.insert(EXCHANGECD, QString::fromLocal8Bit(msg_info->m_exchange_code));
        map_cont.insert(OPENTIME, QString::fromLocal8Bit(msg_info->m_stock_ptr->open_datetime_));
        map_cont.insert(STOCKAREA, (int)msg_info->m_stock_ptr->stock_area_);
        map_cont.insert(STOCKPLATEAREA, (int)msg_info->m_stock_ptr->stock_plate_area_);
        map_cont.insert(TOTALSHARES, (double)msg_info->m_stock_ptr->total_shares_);
    }

    m_map.insert(CMDCODE, msg_info->getCmdCode().c_str());
    m_map.insert(CONTENT, map_cont);

    QJsonDocument doc = QJsonDocument::fromVariant(QVariant(m_map));
    return QString(doc.toJson()).toUtf8().data();
}

void fromJson(xyc_communication::ReplyFundAccAddMsg* msg_info, const std::string& json)
{
    QJsonParseError error;
    QJsonDocument jsonDocument = QJsonDocument::fromJson(QString::fromUtf8(json.c_str()).toUtf8(), &error);
    if (error.error == QJsonParseError::NoError) {
        if (jsonDocument.isObject())
        {
            auto rsltMap = jsonDocument.toVariant().toMap();
//             strncpy_s(msg_info->m_creatorLoginName, rsltMap[CREATELOGINNAME].toString().toLocal8Bit().data(), sizeof(msg_info->m_creatorLoginName) - 1);

            strncpy_s(msg_info->m_rtn_acc->login_name_, rsltMap[LOGINNAME].toString().toLocal8Bit().data(), sizeof(msg_info->m_rtn_acc->login_name_) - 1);
            strncpy_s(msg_info->m_rtn_acc->account_name_, rsltMap[ACCOUNTNAME].toString().toLocal8Bit().data(), sizeof(msg_info->m_rtn_acc->account_name_) - 1);
            strncpy_s(msg_info->m_rtn_acc->fund_company_, rsltMap[SECURITIESCOMPANY].toString().toLocal8Bit().data(), sizeof(msg_info->m_rtn_acc->fund_company_) - 1);
            msg_info->m_rtn_money->priority_fund_ = rsltMap[PRIORITYFUND].toDouble();


//             msg_info->m_rtn_money->user_deposit_ = rsltMap[INFERIORFUND].toDouble();
//             msg_info->m_rtn_money->priority_fund_ = rsltMap[PRIORITYFUND].toDouble();
// 
        }
    }
}

std::string toJson(xyc_communication::ReplyFundAccAddMsgPtr msg_info)
{
    QMap<QString, QVariant> m_map;

    QMap<QString, QVariant> map_cont;

    map_cont.insert(ERRCODE, msg_info->getResult());
    map_cont.insert(CREATELOGINNAME, QString::fromLocal8Bit(msg_info->getLoginName().c_str()));
    map_cont.insert(UPPERMANAGER, QString::fromLocal8Bit(msg_info->getLoginName().c_str()));
    map_cont.insert(ACCOUNTNAME, QString::fromLocal8Bit(msg_info->m_rtn_acc->account_name_));
    map_cont.insert(LOGINNAME, QString::fromLocal8Bit(msg_info->m_rtn_acc->login_name_));
    map_cont.insert(SECURITIESCOMPANY, QString::fromLocal8Bit(msg_info->m_rtn_acc->fund_company_));
    map_cont.insert(INFERIORFUND, (double)(msg_info->m_rtn_money->user_deposit_));
    map_cont.insert(PRIORITYFUND, (double)msg_info->m_rtn_money->priority_fund_);

    m_map.insert(CMDCODE, msg_info->getCmdCode().c_str());
    m_map.insert(CONTENT, map_cont);

    QJsonDocument doc = QJsonDocument::fromVariant(QVariant(m_map));
    return QString(doc.toJson()).toUtf8().data();
}

void fromJson(xyc_communication::ReplyFundAccChangeMsg* msg_info, const std::string& json)
{
    QJsonParseError error;
    QJsonDocument jsonDocument = QJsonDocument::fromJson(QString::fromUtf8(json.c_str()).toUtf8(), &error);
    if (error.error == QJsonParseError::NoError) {
        if (jsonDocument.isObject())
        {
            auto rsltMap = jsonDocument.toVariant().toMap();
//             strncpy_s(msg_info->m_creatorLoginName, rsltMap[CREATELOGINNAME].toString().toLocal8Bit().data(), sizeof(msg_info->m_creatorLoginName) - 1);

            strncpy_s(msg_info->m_rtn_acc->login_name_, rsltMap[LOGINNAME].toString().toLocal8Bit().data(), sizeof(msg_info->m_rtn_acc->login_name_) - 1);
            strncpy_s(msg_info->m_rtn_acc->account_name_, rsltMap[ACCOUNTNAME].toString().toLocal8Bit().data(), sizeof(msg_info->m_rtn_acc->account_name_) - 1);
            strncpy_s(msg_info->m_rtn_acc->fund_company_, rsltMap[SECURITIESCOMPANY].toString().toLocal8Bit().data(), sizeof(msg_info->m_rtn_acc->fund_company_) - 1);
            msg_info->m_rtn_money->priority_fund_ = rsltMap[PRIORITYFUND].toDouble();
        }
    }
}

std::string toJson(xyc_communication::ReplyFundAccChangeMsgPtr msg_info)
{
    QMap<QString, QVariant> m_map;

    QMap<QString, QVariant> map_cont;

    map_cont.insert(ERRCODE, msg_info->getResult());
    map_cont.insert(CREATELOGINNAME, QString::fromLocal8Bit(msg_info->getLoginName().c_str()));
    map_cont.insert(UPPERMANAGER, QString::fromLocal8Bit(msg_info->getLoginName().c_str()));
    map_cont.insert(ACCOUNTNAME, QString::fromLocal8Bit(msg_info->m_rtn_acc->account_name_));
    map_cont.insert(LOGINNAME, QString::fromLocal8Bit(msg_info->m_rtn_acc->login_name_));
    map_cont.insert(SECURITIESCOMPANY, QString::fromLocal8Bit(msg_info->m_rtn_acc->fund_company_));
    map_cont.insert(INFERIORFUND, (double)(msg_info->m_rtn_money->user_deposit_));
    map_cont.insert(PRIORITYFUND, (double)msg_info->m_rtn_money->priority_fund_);

    m_map.insert(CMDCODE, msg_info->getCmdCode().c_str());
    m_map.insert(CONTENT, map_cont);

    QJsonDocument doc = QJsonDocument::fromVariant(QVariant(m_map));
    return QString(doc.toJson()).toUtf8().data();
}

void fromJson(xyc_communication::ReplyFeeSetMsg* msg_info, const std::string& json)
{
    QJsonParseError error;
    QJsonDocument jsonDocument = QJsonDocument::fromJson(QString::fromUtf8(json.c_str()).toUtf8(), &error);
    if (error.error == QJsonParseError::NoError) {
        if (jsonDocument.isObject())
        {
            auto rsltMap = jsonDocument.toVariant().toMap();
//             strncpy_s(msg_info->m_login_name, rsltMap[LOGINNAME].toString().toLocal8Bit().data(), sizeof(msg_info->m_login_name) - 1);
            
            msg_info->m_trade_fee->trade_commission_ = rsltMap[COMMISSIONRATE].toDouble();
            msg_info->m_trade_fee->stamp_duty_ = rsltMap[STAMPFEERATE].toDouble();
            msg_info->m_trade_fee->transfer_ = rsltMap[TRANSFERTAXRATE].toDouble();
            msg_info->m_trade_fee->min_trade_commission_ = rsltMap[ONCELOWESTFEE].toDouble();
            msg_info->m_trade_fee->info_match_ = rsltMap[MATCHFEERATERATE].toDouble();
            msg_info->m_trade_fee->user_profit_rate_ = rsltMap[PROCOMMRATE].toInt();
        }
    }
}

std::string toJson(xyc_communication::ReplyFeeSetMsgPtr msg_info)
{
    QMap<QString, QVariant> m_map;

    QMap<QString, QVariant> map_cont;

    map_cont.insert(ERRCODE, msg_info->getResult());
    map_cont.insert(COMMISSIONRATE, (double)msg_info->m_trade_fee->trade_commission_);
    map_cont.insert(STAMPFEERATE, (double)msg_info->m_trade_fee->stamp_duty_);
    map_cont.insert(TRANSFERTAXRATE, (double)msg_info->m_trade_fee->transfer_);
    map_cont.insert(ONCELOWESTFEE, (double)msg_info->m_trade_fee->min_trade_commission_);
    map_cont.insert(MATCHFEERATERATE, (double)msg_info->m_trade_fee->info_match_);

    m_map.insert(CMDCODE, msg_info->getCmdCode().c_str());
    m_map.insert(CONTENT, map_cont);

    QJsonDocument doc = QJsonDocument::fromVariant(QVariant(m_map));
    return QString(doc.toJson()).toUtf8().data();
}

void fromJson(xyc_communication::ReplyRolesAddMsg* msg_info, const std::string& json)
{
    QJsonParseError error;
    QJsonDocument jsonDocument = QJsonDocument::fromJson(QString::fromUtf8(json.c_str()).toUtf8(), &error);
    if (error.error == QJsonParseError::NoError) {
        if (jsonDocument.isObject())
        {
            auto rsltMap = jsonDocument.toVariant().toMap();

// 			strncpy_s(msg_info->m_login_name, rsltMap[LOGINNAME].toString().toLocal8Bit().data(), sizeof(msg_info->m_login_name) - 1);

            msg_info->m_rtn_arp->rolesID = rsltMap[ROLEID].toInt();
            strncpy_s(msg_info->m_rtn_arp->rolesName, rsltMap[ROLESNAME].toString().toLocal8Bit().data(), sizeof(msg_info->m_rtn_arp->rolesName) - 1);
            strncpy_s(msg_info->m_rtn_arp->login_name_, rsltMap[LOGINNAME].toString().toLocal8Bit().data(), sizeof(msg_info->m_rtn_arp->login_name_) - 1);

            // 获取当前日期和时间
            UtilityFun::GetCurrentIntdateAndIntTime(msg_info->m_rtn_arp->createDate, msg_info->m_rtn_arp->createTime);

//		msg_info->m_rtn_arp->createDate = rsltMap[REGDATE].toInt();
//		msg_info->m_rtn_arp->createTime = rsltMap[COMMITIME].toInt();
			msg_info->m_rtn_arp->rolesType = (E_RolesType)rsltMap[ROLETYPE].toInt();
			msg_info->m_rtn_arp->operationType = E_OperationType::EOT_IsOperation;
        }
    }
}

std::string toJson(xyc_communication::ReplyRolesAddMsgPtr msg_info)
{
    QMap<QString, QVariant> m_map;

    QMap<QString, QVariant> map_cont;

    map_cont.insert(ERRCODE, msg_info->getResult());
    map_cont.insert(ROLEID, msg_info->m_rtn_arp->rolesID);
	map_cont.insert(CREATELOGINNAME, msg_info->m_rtn_arp->login_name_);
    map_cont.insert(ROLESNAME, QString::fromLocal8Bit(msg_info->m_rtn_arp->rolesName));
	map_cont.insert(ROLETYPE, msg_info->m_rtn_arp->rolesType);
	map_cont.insert(OPERATIONTYPE, msg_info->m_rtn_arp->operationType);

    m_map.insert(CMDCODE, msg_info->getCmdCode().c_str());
    m_map.insert(CONTENT, map_cont);

    QJsonDocument doc = QJsonDocument::fromVariant(QVariant(m_map));
    return QString(doc.toJson()).toUtf8().data();
}


void fromJson(xyc_communication::ReplyBindRelationMsg* msg_info, const std::string& json)
{
    QJsonParseError error;
    QJsonDocument jsonDocument = QJsonDocument::fromJson(QString::fromUtf8(json.c_str()).toUtf8(), &error);
    if (error.error == QJsonParseError::NoError) {
        if (jsonDocument.isArray())
        {
            auto rsltList = jsonDocument.toVariant().toList();
	
            for (auto& item : rsltList)
			{
				AuthorityRoleFunctionsPtr ptrSt_ = std::make_shared<AuthorityRoleFunctions>();
                auto rsltMap = item.toMap();

// 				strncpy_s(msg_info->m_login_name, rsltMap[LOGINNAME].toString().toLocal8Bit().data(), sizeof(msg_info->m_login_name) - 1);
				msg_info->m_roleId = rsltMap[OPROLEID].toInt();

                ptrSt_->functionID = rsltMap[FUNCTIONID].toInt();
                ptrSt_->roleID = rsltMap[ROLEID].toInt();

                msg_info->m_rtn_arfp.emplace_back(ptrSt_);
            }

        }
    }
}

std::string toJson(xyc_communication::ReplyBindRelationMsgPtr msg_info)
{
    QMap<QString, QVariant> m_map;

    QJsonObject jsonOb;
    QJsonArray jsonArr;

    // content
    for (auto& item : msg_info->m_rtn_arfp)
    {
        jsonOb.insert(ERRCODE, msg_info->getResult());
        jsonOb.insert(FUNCTIONID, item->functionID);
        jsonOb.insert(ROLEID, item->roleID);
        jsonArr.append(jsonOb);
    }

    // cmdcode
    m_map.insert(CMDCODE, msg_info->getCmdCode().c_str());
    m_map.insert(CONTENT, jsonArr);

    QJsonDocument doc = QJsonDocument::fromVariant(QVariant(m_map));
    return QString(doc.toJson()).toUtf8().data();
}


void fromJson(xyc_communication::ReplyRolesChangeMsg* msg_info, const std::string& json)
{
	QJsonParseError error;
	QJsonDocument jsonDocument = QJsonDocument::fromJson(QString::fromUtf8(json.c_str()).toUtf8(), &error);
	if (error.error == QJsonParseError::NoError) {
		if (jsonDocument.isObject())
		{
			auto rsltMap = jsonDocument.toVariant().toMap();
// 			strncpy_s(msg_info->m_login_name, rsltMap[LOGINNAME].toString().toLocal8Bit().data(), sizeof(msg_info->m_login_name) - 1);

			msg_info->m_rtn_arfp->rolesID = rsltMap[ROLEID].toInt();
			strncpy_s(msg_info->m_rtn_arfp->rolesName, rsltMap[ROLESNAME].toString().toLocal8Bit().data(), sizeof(msg_info->m_rtn_arfp->rolesName) - 1);

		}
	}
}


std::string toJson(xyc_communication::ReplyRolesChangeMsgPtr msg_info)
{
	QMap<QString, QVariant> m_map;

	QMap<QString, QVariant> map_cont;

	map_cont.insert(ERRCODE, msg_info->getResult());
	map_cont.insert(ROLEID, msg_info->m_rtn_arfp->rolesID);
	map_cont.insert(ROLESNAME, QString::fromLocal8Bit(msg_info->m_rtn_arfp->rolesName));
	map_cont.insert(OPERATIONTYPE, msg_info->m_rtn_arfp->operationType);
    map_cont.insert(CREATELOGINNAME, msg_info->getLoginName().c_str());

	m_map.insert(CMDCODE, msg_info->getCmdCode().c_str());
	m_map.insert(CONTENT, map_cont);

	QJsonDocument doc = QJsonDocument::fromVariant(QVariant(m_map));
	return QString(doc.toJson()).toUtf8().data();
}


void fromJson(xyc_communication::ReplyOpenCloseMsg* msg_info, const std::string& json)
{
    QJsonParseError error;
    QJsonDocument jsonDocument = QJsonDocument::fromJson(QString::fromUtf8(json.c_str()).toUtf8(), &error);
    if (error.error == QJsonParseError::NoError) {
        if (jsonDocument.isObject())
        {
            auto rsltMap = jsonDocument.toVariant().toMap();
            msg_info->m_order_ptr->op_type_ = (OperatorTradeType)rsltMap[RESOURCE].toInt();
            msg_info->m_order_ptr->commodity_type_ = CommodityTypeType::COMMODITY_TYPE_STOCK;
            msg_info->m_order_ptr->direct_type_ = (DirectType)rsltMap[ORDERDERECTION].toInt();
            msg_info->m_order_ptr->order_price_ = rsltMap[ORDERPICE].toDouble();
            msg_info->m_order_ptr->order_type_ = (OrderTypeType)rsltMap[ORDERTYPE].toInt();
            msg_info->m_order_ptr->order_vol_ = rsltMap[ORDERVOLUME].toInt();
            msg_info->m_order_ptr->order_mode_ = OrderModeType::ORDER_MODE_GFD/*(OrderModeType)rsltMap[ORDERMODE].toInt()*/;
            msg_info->m_order_ptr->stock_area_ = StockAreaType::STOCKAREA_TYPE_A/*(OrderModeType)rsltMap[ORDERMODE].toInt()*/;
            strncpy_s(msg_info->m_order_ptr->order_localtmp_ref_, rsltMap[ORDERREF].toString().toLocal8Bit().data(), sizeof(msg_info->m_order_ptr->order_localtmp_ref_) - 1);

            strncpy_s(msg_info->m_orderLoginName, rsltMap[LOGINNAME].toString().toLocal8Bit().data(), sizeof(msg_info->m_orderLoginName) - 1);
            strncpy_s(msg_info->m_contract_code, rsltMap[STOCKCODE].toString().toLocal8Bit().data(), sizeof(msg_info->m_contract_code) - 1);
        }
    }
}

std::string toJson(xyc_communication::ReplyOpenCloseMsgPtr msg_info)
{
    QMap<QString, QVariant> m_map;
    QMap<QString, QVariant> map_cont;

    map_cont.insert(ERRCODE, msg_info->getResult());
    map_cont.insert(LOGINNAME, QString::fromLocal8Bit(msg_info->m_orderLoginName));
    map_cont.insert(ORDERDERECTION, (int)msg_info->m_order_ptr->direct_type_);
    map_cont.insert(ORDERPICE, (double)msg_info->m_order_ptr->order_price_);
    map_cont.insert(ORDERTYPE, (int)msg_info->m_order_ptr->order_type_);
    map_cont.insert(COMMITIME, msg_info->m_order_ptr->generate_datetime_);
    map_cont.insert(ORDERVOLUME, msg_info->m_order_ptr->order_vol_);
    map_cont.insert(ORDERMODE, (int)msg_info->m_order_ptr->order_mode_);
    map_cont.insert(ORDERREF, msg_info->m_order_ptr->order_localtmp_ref_);
    map_cont.insert(ORDERID, msg_info->m_order_ptr->shadow_order_id_);
    map_cont.insert(STOCKCODE, msg_info->m_contract_code);
    map_cont.insert(ORDERSTREAM, msg_info->m_order_ptr->order_stream_);

    m_map.insert(CMDCODE, msg_info->getCmdCode().c_str());
    m_map.insert(CONTENT, map_cont);

    QJsonDocument doc = QJsonDocument::fromVariant(QVariant(m_map));
    return QString(doc.toJson()).toUtf8().data();
}

void fromJson(xyc_communication::ReplyCancelOrderMsg* msg_info, const std::string& json)
{
    QJsonParseError error;
    QJsonDocument jsonDocument = QJsonDocument::fromJson(QString::fromUtf8(json.c_str()).toUtf8(), &error);
    if (error.error == QJsonParseError::NoError) {
        if (jsonDocument.isObject())
        {
            auto rsltMap = jsonDocument.toVariant().toMap();
            strncpy_s(msg_info->m_orderLoginName, rsltMap[LOGINNAME].toString().toLocal8Bit().data(), sizeof(msg_info->m_orderLoginName) - 1);
            strncpy_s(msg_info->m_orderstream, rsltMap[ORDERSTREAM].toString().toLocal8Bit().data(), sizeof(msg_info->m_orderstream) - 1);
        }
    }
}

std::string toJson(xyc_communication::ReplyCancelOrderMsgPtr msg_info)
{
    QMap<QString, QVariant> m_map;
    QMap<QString, QVariant> map_cont;

    map_cont.insert(ERRCODE, msg_info->getResult());
    map_cont.insert(LOGINNAME, QString::fromLocal8Bit(msg_info->m_orderLoginName));

    m_map.insert(CMDCODE, msg_info->getCmdCode().c_str());
    m_map.insert(CONTENT, map_cont);

    QJsonDocument doc = QJsonDocument::fromVariant(QVariant(m_map));
    return QString(doc.toJson()).toUtf8().data();
}

void fromJson(xyc_communication::ReplyFundQryMsg* msg_info, const std::string& json)
{
    QJsonParseError error;
    QJsonDocument jsonDocument = QJsonDocument::fromJson(QString::fromUtf8(json.c_str()).toUtf8(), &error);
    if (error.error == QJsonParseError::NoError) {
        if (jsonDocument.isObject())
        {
            auto rsltMap = jsonDocument.toVariant().toMap();
            strncpy_s(msg_info->m_rtn_acc->login_name_, rsltMap[LOGINNAME].toString().toLocal8Bit().data(), sizeof(msg_info->m_rtn_acc->login_name_) - 1);
        }
    }
}

std::string toJson(xyc_communication::ReplyFundQryMsgPtr msg_info)
{
    QMap<QString, QVariant> m_map;
    QMap<QString, QVariant> map_cont;

    map_cont.insert(ERRCODE, msg_info->getResult());
    map_cont.insert(ACCOUNTNAME, QString::fromLocal8Bit(msg_info->m_rtn_acc->account_name_));
    map_cont.insert(LOGINNAME, QString::fromLocal8Bit(msg_info->m_rtn_acc->login_name_));
    map_cont.insert(INFERIORFUND, (double)(msg_info->m_rtn_money->user_deposit_));
    map_cont.insert(PRIORITYFUND, (double)(msg_info->m_rtn_money->priority_fund_));
    map_cont.insert(AVAILABLEFUNDS, (double)(msg_info->m_rtn_money->getCanUse()));
    map_cont.insert(AVAILABLEGETFUNDS, (double)(msg_info->m_rtn_money->getCanExtract()));
    map_cont.insert(OPENCOST, (double)(msg_info->m_rtn_money->position_cost_price_));
    map_cont.insert(FROZENFUND, (double)msg_info->m_rtn_money->order_freeze_);
    map_cont.insert(UPPERMANAGER, QString::fromLocal8Bit(msg_info->m_parent_login_name));
    map_cont.insert(WARNINGLINE, (double)msg_info->m_rtn_risk->warningline_);
    map_cont.insert(FORCELINE, (double)msg_info->m_rtn_risk->forceline_);
    map_cont.insert(LIMITLINE, (double)msg_info->m_rtn_risk->limitline_);
    map_cont.insert(LEVERAGERATE, (double)msg_info->m_rtn_risk->lever_rate_);
    map_cont.insert(COMMISSIONRATE, (double)msg_info->m_rtn_risk->commissionrate_);

    m_map.insert(CMDCODE, msg_info->getCmdCode().c_str());
    m_map.insert(CONTENT, map_cont);

    QJsonDocument doc = QJsonDocument::fromVariant(QVariant(m_map));
    return QString(doc.toJson()).toUtf8().data();
}

void fromJson(xyc_communication::ReplyFundSerialQryMsg* msg_info, const std::string& json)
{
    QJsonParseError error;
    QJsonDocument jsonDocument = QJsonDocument::fromJson(QString::fromUtf8(json.c_str()).toUtf8(), &error);
    if (error.error == QJsonParseError::NoError) {
        if (jsonDocument.isObject())
        {
            auto rsltMap = jsonDocument.toVariant().toMap();
            strncpy_s(msg_info->m_rtn_acc->login_name_, rsltMap[LOGINNAME].toString().toLocal8Bit().data(), sizeof(msg_info->m_rtn_acc->login_name_) - 1);
            strncpy_s(msg_info->m_qry_start_time, rsltMap[QRYSTARTDATETIME].toString().toLocal8Bit().data(), sizeof(msg_info->m_qry_start_time) - 1);
            strncpy_s(msg_info->m_qry_end_time, UtilityFun::getAddDate(rsltMap[QRYENDDATETIME].toString().toLocal8Bit().data(), 1).c_str(), sizeof(msg_info->m_qry_end_time) - 1);
        }
    }
}

std::string toJson(xyc_communication::ReplyFundSerialQryMsgPtr msg_info)
{
    QMap<QString, QVariant> m_map;
    QMap<QString, QVariant> map_cont;

    map_cont.insert(ERRCODE, msg_info->getResult());
    map_cont.insert(BLAST, msg_info->m_blast);
    if (!msg_info->m_blast)
    {
        map_cont.insert(FUNDSERIALID, msg_info->m_rtn_money->stream_);
        map_cont.insert(ACCOUNTNAME, QString::fromLocal8Bit(msg_info->m_rtn_acc->account_name_));
        map_cont.insert(LOGINNAME, QString::fromLocal8Bit(msg_info->m_rtn_acc->login_name_));
        map_cont.insert(UPPERMANAGER, QString::fromLocal8Bit(msg_info->m_parent_login_name));
        map_cont.insert(CHANGEMONEY, (double)(msg_info->m_rtn_money->change_money_));
        map_cont.insert(CHANGETYPE, msg_info->m_rtn_money->change_type_);
        map_cont.insert(CHANGETIME, msg_info->m_rtn_money->date_time_);
        map_cont.insert(REMARKSINFO, QString::fromLocal8Bit(msg_info->m_rtn_money->remark_));
    }
    m_map.insert(CMDCODE, msg_info->getCmdCode().c_str());
    m_map.insert(CONTENT, map_cont);

    QJsonDocument doc = QJsonDocument::fromVariant(QVariant(m_map));
    return QString(doc.toJson()).toUtf8().data();
}

void fromJson(xyc_communication::ReplyPosiQryMsg* msg_info, const std::string& json)
{
    QJsonParseError error;
    QJsonDocument jsonDocument = QJsonDocument::fromJson(QString::fromUtf8(json.c_str()).toUtf8(), &error);
    if (error.error == QJsonParseError::NoError) {
        if (jsonDocument.isObject())
        {
            auto rsltMap = jsonDocument.toVariant().toMap();
            strncpy_s(msg_info->m_rtn_acc->login_name_, rsltMap[LOGINNAME].toString().toLocal8Bit().data(), sizeof(msg_info->m_rtn_acc->login_name_) - 1);
        }
    }
}

std::string toJson(xyc_communication::ReplyPosiQryMsgPtr msg_info)
{
    QMap<QString, QVariant> m_map;
    QMap<QString, QVariant> map_cont;

    map_cont.insert(ERRCODE, msg_info->getResult());
    map_cont.insert(BLAST, msg_info->m_blast);
    if (!msg_info->m_blast)
    {
        map_cont.insert(LOGINNAME, QString::fromLocal8Bit(msg_info->m_rtn_acc->login_name_));
        map_cont.insert(ACCOUNTNAME, QString::fromLocal8Bit(msg_info->m_rtn_acc->account_name_));
        map_cont.insert(DEALNO, msg_info->m_position_ptr->position_id_);
        map_cont.insert(STOCKCODE, msg_info->m_stock_ptr->contract_code_);
        map_cont.insert(STOCKNAME, QString::fromLocal8Bit(msg_info->m_stock_ptr->contract_name_));
        map_cont.insert(POSITIONPRICE, (double)msg_info->m_position_ptr->cost_price_ / (msg_info->m_position_ptr->volume_ + msg_info->m_position_ptr->T_volume_));
        map_cont.insert(POSITIONCOST, (double)msg_info->m_position_ptr->cost_price_);
        map_cont.insert(POSITIONQTY, msg_info->m_position_ptr->volume_ + msg_info->m_position_ptr->T_volume_);
        map_cont.insert(ISSELLQTY, msg_info->m_position_ptr->volume_ - msg_info->m_position_ptr->freeze_order_vol_);
        map_cont.insert(FROZENNUMBER, msg_info->m_position_ptr->freeze_order_vol_);
        map_cont.insert(TRADEDIR, (int)msg_info->m_position_ptr->direct_type_);
        map_cont.insert(CURRENCYRATE, (double)msg_info->m_currency_rate);
        map_cont.insert(UPPERMANAGER, QString::fromLocal8Bit(msg_info->m_parent_login_name));
    }

    m_map.insert(CMDCODE, msg_info->getCmdCode().c_str());
    m_map.insert(CONTENT, map_cont);

    QJsonDocument doc = QJsonDocument::fromVariant(QVariant(m_map));
    return QString(doc.toJson()).toUtf8().data();
}

void fromJson(xyc_communication::ReplyCurrentyEntrustQryMsg* msg_info, const std::string& json)
{
    QJsonParseError error;
    QJsonDocument jsonDocument = QJsonDocument::fromJson(QString::fromUtf8(json.c_str()).toUtf8(), &error);
    if (error.error == QJsonParseError::NoError) {
        if (jsonDocument.isObject())
        {
            auto rsltMap = jsonDocument.toVariant().toMap();
            strncpy_s(msg_info->m_rtn_acc->login_name_, rsltMap[LOGINNAME].toString().toLocal8Bit().data(), sizeof(msg_info->m_rtn_acc->login_name_) - 1);
        }
    }
}

std::string toJson(xyc_communication::ReplyCurrentyEntrustQryMsgPtr msg_info)
{
    QMap<QString, QVariant> m_map;
    QMap<QString, QVariant> map_cont;

    map_cont.insert(ERRCODE, msg_info->getResult());
    map_cont.insert(BLAST, msg_info->m_blast);
    if (!msg_info->m_blast)
    {
        map_cont.insert(ACCOUNTNAME, QString::fromLocal8Bit(msg_info->m_rtn_acc->account_name_));
        map_cont.insert(LOGINNAME, QString::fromLocal8Bit(msg_info->m_rtn_acc->login_name_));
        map_cont.insert(STOCKCODE, msg_info->m_stock_ptr->contract_code_);
        map_cont.insert(STOCKNAME, QString::fromLocal8Bit(msg_info->m_stock_ptr->contract_name_));
        map_cont.insert(ORDERPICE, (double)msg_info->m_order_ptr->order_price_);
        map_cont.insert(ORDERVOLUME, msg_info->m_order_ptr->order_vol_);
        map_cont.insert(DEALQTY, msg_info->m_order_ptr->effected_vol_);
        map_cont.insert(ORDERSTATUS, (int)msg_info->m_order_ptr->order_state_);
        map_cont.insert(ORDERREF, msg_info->m_order_ptr->order_localtmp_ref_);
        map_cont.insert(ORDERID, msg_info->m_order_ptr->shadow_order_id_);
        map_cont.insert(ORDERTYPE, (int)msg_info->m_order_ptr->order_type_);
        map_cont.insert(ORDERMODE, (int)msg_info->m_order_ptr->order_mode_);
        map_cont.insert(ORDERDERECTION, (int)msg_info->m_order_ptr->direct_type_);
        map_cont.insert(CURRENCYRATE, (double)msg_info->m_order_ptr->currency_rate_);
        map_cont.insert(UPPERMANAGER, QString::fromLocal8Bit(msg_info->m_parent_login_name));
        map_cont.insert(COMMITIME, msg_info->m_order_ptr->generate_datetime_);
        map_cont.insert(CHANGETIME, msg_info->m_order_ptr->update_datetime_);
        map_cont.insert(ORDERSTREAM, msg_info->m_order_ptr->order_stream_);
        if (msg_info->m_order_ptr->order_state_ == OrderStateType::ORDER_STATE_DELETED)
            map_cont.insert(CANCELORDERNUMBER, msg_info->m_order_ptr->order_vol_ - msg_info->m_order_ptr->effected_vol_);
        else
            map_cont.insert(CANCELORDERNUMBER, 0);
        map_cont.insert(FROZENFUND, (double)msg_info->m_order_ptr->freeze_money_);
    }

    m_map.insert(CMDCODE, msg_info->getCmdCode().c_str());
    m_map.insert(CONTENT, map_cont);

    QJsonDocument doc = QJsonDocument::fromVariant(QVariant(m_map));
    return QString(doc.toJson()).toUtf8().data();
}

void fromJson(xyc_communication::ReplyTodayEntrustQryMsg* msg_info, const std::string& json)
{
    QJsonParseError error;
    QJsonDocument jsonDocument = QJsonDocument::fromJson(QString::fromUtf8(json.c_str()).toUtf8(), &error);
    if (error.error == QJsonParseError::NoError) {
        if (jsonDocument.isObject())
        {
            auto rsltMap = jsonDocument.toVariant().toMap();
            strncpy_s(msg_info->m_rtn_acc->login_name_, rsltMap[LOGINNAME].toString().toLocal8Bit().data(), sizeof(msg_info->m_rtn_acc->login_name_) - 1);
        }
    }
}

std::string toJson(xyc_communication::ReplyTodayEntrustQryMsgPtr msg_info)
{
    QMap<QString, QVariant> m_map;
    QMap<QString, QVariant> map_cont;

    map_cont.insert(ERRCODE, msg_info->getResult());
    map_cont.insert(BLAST, msg_info->m_blast);
    if (!msg_info->m_blast)
    {
        map_cont.insert(ACCOUNTNAME, QString::fromLocal8Bit(msg_info->m_rtn_acc->account_name_));
        map_cont.insert(LOGINNAME, QString::fromLocal8Bit(msg_info->m_rtn_acc->login_name_));
        map_cont.insert(STOCKCODE, msg_info->m_stock_ptr->contract_code_);
        map_cont.insert(STOCKNAME, QString::fromLocal8Bit(msg_info->m_stock_ptr->contract_name_));
        map_cont.insert(ORDERPICE, (double)msg_info->m_order_ptr->order_price_);
        map_cont.insert(ORDERVOLUME, msg_info->m_order_ptr->order_vol_);
        map_cont.insert(DEALQTY, msg_info->m_order_ptr->effected_vol_);
        map_cont.insert(ORDERSTATUS, (int)msg_info->m_order_ptr->order_state_);
        map_cont.insert(ORDERREF, msg_info->m_order_ptr->order_localtmp_ref_);
        map_cont.insert(ORDERID, msg_info->m_order_ptr->shadow_order_id_);
        map_cont.insert(ORDERTYPE, (int)msg_info->m_order_ptr->order_type_);
        map_cont.insert(ORDERMODE, (int)msg_info->m_order_ptr->order_mode_);
        map_cont.insert(ORDERDERECTION, (int)msg_info->m_order_ptr->direct_type_);
        map_cont.insert(CURRENCYRATE, (double)msg_info->m_order_ptr->currency_rate_);
        map_cont.insert(UPPERMANAGER, QString::fromLocal8Bit(msg_info->m_parent_login_name));
        map_cont.insert(COMMITIME, msg_info->m_order_ptr->generate_datetime_);
        map_cont.insert(CHANGETIME, msg_info->m_order_ptr->update_datetime_);
        map_cont.insert(ORDERSTREAM, msg_info->m_order_ptr->order_stream_);
        if (msg_info->m_order_ptr->order_state_ == OrderStateType::ORDER_STATE_DELETED)
            map_cont.insert(CANCELORDERNUMBER, msg_info->m_order_ptr->order_vol_ - msg_info->m_order_ptr->effected_vol_);
        else
            map_cont.insert(CANCELORDERNUMBER, 0);
        map_cont.insert(FROZENFUND, (double)msg_info->m_order_ptr->freeze_money_);
    }

    m_map.insert(CMDCODE, msg_info->getCmdCode().c_str());
    m_map.insert(CONTENT, map_cont);

    QJsonDocument doc = QJsonDocument::fromVariant(QVariant(m_map));
    return QString(doc.toJson()).toUtf8().data();
}

void fromJson(xyc_communication::ReplyHistoryEntrustQryMsg* msg_info, const std::string& json)
{
    QJsonParseError error;
    QJsonDocument jsonDocument = QJsonDocument::fromJson(QString::fromUtf8(json.c_str()).toUtf8(), &error);
    if (error.error == QJsonParseError::NoError) {
        if (jsonDocument.isObject())
        {
            auto rsltMap = jsonDocument.toVariant().toMap();
            strncpy_s(msg_info->m_rtn_acc->login_name_, rsltMap[LOGINNAME].toString().toLocal8Bit().data(), sizeof(msg_info->m_rtn_acc->login_name_) - 1);
            strncpy_s(msg_info->m_qry_start_time, rsltMap[QRYSTARTDATETIME].toString().toLocal8Bit().data(), sizeof(msg_info->m_qry_start_time) - 1);
            strncpy_s(msg_info->m_qry_end_time, UtilityFun::getAddDate(rsltMap[QRYENDDATETIME].toString().toLocal8Bit().data(), 1).c_str(), sizeof(msg_info->m_qry_end_time) - 1);
        }
    }
}

std::string toJson(xyc_communication::ReplyHistoryEntrustQryMsgPtr msg_info)
{
    QMap<QString, QVariant> m_map;
    QMap<QString, QVariant> map_cont;

    map_cont.insert(ERRCODE, msg_info->getResult());
    map_cont.insert(BLAST, msg_info->m_blast);
    if (!msg_info->m_blast)
    {
        map_cont.insert(ACCOUNTNAME, QString::fromLocal8Bit(msg_info->m_rtn_acc->account_name_));
        map_cont.insert(LOGINNAME, QString::fromLocal8Bit(msg_info->m_rtn_acc->login_name_));
        map_cont.insert(STOCKCODE, msg_info->m_stock_ptr->contract_code_);
        map_cont.insert(STOCKNAME, QString::fromLocal8Bit(msg_info->m_stock_ptr->contract_name_));
        map_cont.insert(ORDERPICE, (double)msg_info->m_order_ptr->order_price_);
        map_cont.insert(ORDERVOLUME, msg_info->m_order_ptr->order_vol_);
        map_cont.insert(DEALQTY, msg_info->m_order_ptr->effected_vol_);
        map_cont.insert(ORDERSTATUS, (int)msg_info->m_order_ptr->order_state_);
        map_cont.insert(ORDERREF, msg_info->m_order_ptr->order_localtmp_ref_);
        map_cont.insert(ORDERID, msg_info->m_order_ptr->shadow_order_id_);
        map_cont.insert(ORDERTYPE, (int)msg_info->m_order_ptr->order_type_);
        map_cont.insert(ORDERMODE, (int)msg_info->m_order_ptr->order_mode_);
        map_cont.insert(ORDERDERECTION, (int)msg_info->m_order_ptr->direct_type_);
        map_cont.insert(CURRENCYRATE, (double)msg_info->m_order_ptr->currency_rate_);
        map_cont.insert(UPPERMANAGER, QString::fromLocal8Bit(msg_info->m_parent_login_name));
        map_cont.insert(COMMITIME, msg_info->m_order_ptr->generate_datetime_);
        map_cont.insert(CHANGETIME, msg_info->m_order_ptr->update_datetime_);
        map_cont.insert(ORDERSTREAM, msg_info->m_order_ptr->order_stream_);
        if (msg_info->m_order_ptr->order_state_ == OrderStateType::ORDER_STATE_DELETED)
            map_cont.insert(CANCELORDERNUMBER, msg_info->m_order_ptr->order_vol_ - msg_info->m_order_ptr->effected_vol_);
        else
            map_cont.insert(CANCELORDERNUMBER, 0);
        map_cont.insert(FROZENFUND, (double)msg_info->m_order_ptr->freeze_money_);
    }

    m_map.insert(CMDCODE, msg_info->getCmdCode().c_str());
    m_map.insert(CONTENT, map_cont);

    QJsonDocument doc = QJsonDocument::fromVariant(QVariant(m_map));
    return QString(doc.toJson()).toUtf8().data();
}

void fromJson(xyc_communication::ReplyTradeQryMsg* msg_info, const std::string& json)
{
    QJsonParseError error;
    QJsonDocument jsonDocument = QJsonDocument::fromJson(QString::fromUtf8(json.c_str()).toUtf8(), &error);
    if (error.error == QJsonParseError::NoError) {
        if (jsonDocument.isObject())
        {
            auto rsltMap = jsonDocument.toVariant().toMap();
            strncpy_s(msg_info->m_rtn_acc->login_name_, rsltMap[LOGINNAME].toString().toLocal8Bit().data(), sizeof(msg_info->m_rtn_acc->login_name_) - 1);
        }
    }

}

std::string toJson(xyc_communication::ReplyTradeQryMsgPtr msg_info)
{
    QMap<QString, QVariant> m_map;
    QMap<QString, QVariant> map_cont;

    map_cont.insert(ERRCODE, msg_info->getResult());
    map_cont.insert(BLAST, msg_info->m_blast);
    if (!msg_info->m_blast)
    {
        map_cont.insert(ACCOUNTNAME, QString::fromLocal8Bit(msg_info->m_rtn_acc->account_name_));
        map_cont.insert(LOGINNAME, QString::fromLocal8Bit(msg_info->m_rtn_acc->login_name_));
        map_cont.insert(CURRENCYRATE, (double)msg_info->m_trade_ptr->currency_rate_);
        map_cont.insert(DEALNO, msg_info->m_trade_ptr->shadow_trade_id_);
        map_cont.insert(STOCKCODE, msg_info->m_stock_ptr->contract_code_);
        map_cont.insert(STOCKNAME, QString::fromLocal8Bit(msg_info->m_stock_ptr->contract_name_));
        map_cont.insert(TRADEDIR, (int)msg_info->m_trade_ptr->direct_type_);
        map_cont.insert(DEALQTY, msg_info->m_trade_ptr->volume_);
        map_cont.insert(DEALAVGPRICE, (double)msg_info->m_trade_ptr->trade_price_);
        map_cont.insert(COMMISSION, (double)msg_info->m_trade_ptr->trade_fee_);
        map_cont.insert(STAMPFEE, (double)msg_info->m_trade_ptr->stamp_fee_);
        map_cont.insert(TRANSFERFEE, (double)msg_info->m_trade_ptr->transfer_fee_);
        map_cont.insert(INFOMATCHFEE, (double)msg_info->m_trade_ptr->infomatch_fee_);
        map_cont.insert(UPPERMANAGER, QString::fromLocal8Bit(msg_info->m_parent_login_name));
        map_cont.insert(DEALTIME, msg_info->m_trade_ptr->generate_datetime_);
    }

    m_map.insert(CMDCODE, msg_info->getCmdCode().c_str());
    m_map.insert(CONTENT, map_cont);

    QJsonDocument doc = QJsonDocument::fromVariant(QVariant(m_map));
    return QString(doc.toJson()).toUtf8().data();
}

void fromJson(xyc_communication::ReplyHistoryTradeQryMsg* msg_info, const std::string& json)
{
    QJsonParseError error;
    QJsonDocument jsonDocument = QJsonDocument::fromJson(QString::fromUtf8(json.c_str()).toUtf8(), &error);
    if (error.error == QJsonParseError::NoError) {
        if (jsonDocument.isObject())
        {
            auto rsltMap = jsonDocument.toVariant().toMap();
            strncpy_s(msg_info->m_rtn_acc->login_name_, rsltMap[LOGINNAME].toString().toLocal8Bit().data(), sizeof(msg_info->m_rtn_acc->login_name_) - 1);
            strncpy_s(msg_info->m_qry_start_time, rsltMap[QRYSTARTDATETIME].toString().toLocal8Bit().data(), sizeof(msg_info->m_qry_start_time) - 1);
            strncpy_s(msg_info->m_qry_end_time, UtilityFun::getAddDate(rsltMap[QRYENDDATETIME].toString().toLocal8Bit().data(), 1).c_str(), sizeof(msg_info->m_qry_end_time) - 1);
        }
    }
}

std::string toJson(xyc_communication::ReplyHistoryTradeQryMsgPtr msg_info)
{
    QMap<QString, QVariant> m_map;
    QMap<QString, QVariant> map_cont;

    map_cont.insert(ERRCODE, msg_info->getResult());
    map_cont.insert(BLAST, msg_info->m_blast);
    if (!msg_info->m_blast)
    {
        map_cont.insert(ACCOUNTNAME, QString::fromLocal8Bit(msg_info->m_rtn_acc->account_name_));
        map_cont.insert(LOGINNAME, QString::fromLocal8Bit(msg_info->m_rtn_acc->login_name_));
        map_cont.insert(CURRENCYRATE, (double)msg_info->m_trade_ptr->currency_rate_);
        map_cont.insert(DEALNO, msg_info->m_trade_ptr->shadow_trade_id_);
        map_cont.insert(STOCKCODE, msg_info->m_stock_ptr->contract_code_);
        map_cont.insert(STOCKNAME, QString::fromLocal8Bit(msg_info->m_stock_ptr->contract_name_));
        map_cont.insert(TRADEDIR, (int)msg_info->m_trade_ptr->direct_type_);
        map_cont.insert(DEALQTY, msg_info->m_trade_ptr->volume_);
        map_cont.insert(DEALAVGPRICE, (double)msg_info->m_trade_ptr->trade_price_);
        map_cont.insert(COMMISSION, (double)msg_info->m_trade_ptr->trade_fee_);
        map_cont.insert(STAMPFEE, (double)msg_info->m_trade_ptr->stamp_fee_);
        map_cont.insert(TRANSFERFEE, (double)msg_info->m_trade_ptr->transfer_fee_);
        map_cont.insert(INFOMATCHFEE, (double)msg_info->m_trade_ptr->infomatch_fee_);
        map_cont.insert(UPPERMANAGER, QString::fromLocal8Bit(msg_info->m_parent_login_name));
        map_cont.insert(DEALTIME, msg_info->m_trade_ptr->generate_datetime_);
    }

    m_map.insert(CMDCODE, msg_info->getCmdCode().c_str());
    m_map.insert(CONTENT, map_cont);

    QJsonDocument doc = QJsonDocument::fromVariant(QVariant(m_map));
    return QString(doc.toJson()).toUtf8().data();
}

void fromJson(xyc_communication::ReplyPswChangeMsg* msg_info, const std::string& json)
{
    QJsonParseError error;
    QJsonDocument jsonDocument = QJsonDocument::fromJson(QString::fromUtf8(json.c_str()).toUtf8(), &error);
    if (error.error == QJsonParseError::NoError) {
        if (jsonDocument.isObject())
        {
            auto rsltMap = jsonDocument.toVariant().toMap();
            strncpy_s(msg_info->m_LoginName, rsltMap[LOGINNAME].toString().toLocal8Bit().data(), sizeof(msg_info->m_LoginName) - 1);
            strncpy_s(msg_info->m_old_pass, rsltMap[OLDPASSWORD].toString().toLocal8Bit().data(), sizeof(msg_info->m_old_pass) - 1);
            strncpy_s(msg_info->m_new_pass, rsltMap[NEWPASSWORD].toString().toLocal8Bit().data(), sizeof(msg_info->m_new_pass) - 1);
        }
    }
}

std::string toJson(xyc_communication::ReplyPswChangeMsgPtr msg_info)
{
    QMap<QString, QVariant> m_map;
    QMap<QString, QVariant> map_cont;

    map_cont.insert(ERRCODE, msg_info->getResult());
    map_cont.insert(LOGINNAME, msg_info->m_LoginName);
    map_cont.insert(OLDPASSWORD, msg_info->m_old_pass);
    map_cont.insert(NEWPASSWORD, msg_info->m_new_pass);

    // cmdcode
    m_map.insert(CMDCODE, msg_info->getCmdCode().c_str());
    m_map.insert(CONTENT, map_cont);

    QJsonDocument doc = QJsonDocument::fromVariant(QVariant(m_map));
    return QString(doc.toJson()).toUtf8().data();
}

void fromJson(xyc_communication::ReplyManagerAddMsg* msg_info, const std::string& json)
{
    QJsonParseError error;
    QJsonDocument jsonDocument = QJsonDocument::fromJson(QString::fromUtf8(json.c_str()).toUtf8(), &error);
    if (error.error == QJsonParseError::NoError) {
        if (jsonDocument.isObject())
        {
            auto rsltMap = jsonDocument.toVariant().toMap();
//             strncpy_s(msg_info->m_creatorLoginName, rsltMap[CREATELOGINNAME].toString().toLocal8Bit().data(), sizeof(msg_info->m_creatorLoginName) - 1);
            strncpy_s(msg_info->m_rtn_acc->login_name_, rsltMap[LOGINNAME].toString().toLocal8Bit().data(), sizeof(msg_info->m_rtn_acc->login_name_) - 1);
            strncpy_s(msg_info->m_rtn_acc->account_name_, rsltMap[ACCOUNTNAME].toString().toLocal8Bit().data(), sizeof(msg_info->m_rtn_acc->account_name_) - 1);
            strncpy_s(msg_info->m_rtn_acc->password_, rsltMap[PASSWORD].toString().toLocal8Bit().data(), sizeof(msg_info->m_rtn_acc->password_) - 1);
        }
    }
}

std::string toJson(xyc_communication::ReplyManagerAddMsgPtr msg_info)
{
    QMap<QString, QVariant> m_map;
    QMap<QString, QVariant> map_cont;

    map_cont.insert(ERRCODE, msg_info->getResult());
    map_cont.insert(CREATELOGINNAME, QString::fromLocal8Bit(msg_info->getLoginName().c_str()));
    map_cont.insert(ACCOUNTNAME, QString::fromLocal8Bit(msg_info->m_rtn_acc->account_name_));
    map_cont.insert(LOGINNAME, QString::fromLocal8Bit(msg_info->m_rtn_acc->login_name_));
    map_cont.insert(PASSWORD, QString::fromLocal8Bit(msg_info->m_rtn_acc->password_));

    m_map.insert(CMDCODE, msg_info->getCmdCode().c_str());
    m_map.insert(CONTENT, map_cont);

    QJsonDocument doc = QJsonDocument::fromVariant(QVariant(m_map));
    return QString(doc.toJson()).toUtf8().data();
}

void fromJson(xyc_communication::ReplyManagerChangeMsg* msg_info, const std::string& json)
{
    QJsonParseError error;
    QJsonDocument jsonDocument = QJsonDocument::fromJson(QString::fromUtf8(json.c_str()).toUtf8(), &error);
    if (error.error == QJsonParseError::NoError) {
        if (jsonDocument.isObject())
        {
            auto rsltMap = jsonDocument.toVariant().toMap();
            strncpy_s(msg_info->m_rtn_acc->login_name_, rsltMap[LOGINNAME].toString().toLocal8Bit().data(), sizeof(msg_info->m_rtn_acc->login_name_) - 1);
            strncpy_s(msg_info->m_rtn_acc->account_name_, rsltMap[ACCOUNTNAME].toString().toLocal8Bit().data(), sizeof(msg_info->m_rtn_acc->account_name_) - 1);
            strncpy_s(msg_info->m_rtn_acc->password_, rsltMap[PASSWORD].toString().toLocal8Bit().data(), sizeof(msg_info->m_rtn_acc->password_) - 1);
        }
    }
}

std::string toJson(xyc_communication::ReplyManagerChangeMsgPtr msg_info)
{
    QMap<QString, QVariant> m_map;
    QMap<QString, QVariant> map_cont;

    map_cont.insert(ERRCODE, msg_info->getResult());
    map_cont.insert(ACCOUNTNAME, QString::fromLocal8Bit(msg_info->m_rtn_acc->account_name_));
    map_cont.insert(LOGINNAME, QString::fromLocal8Bit(msg_info->m_rtn_acc->login_name_));
    map_cont.insert(PASSWORD, QString::fromLocal8Bit(msg_info->m_rtn_acc->password_));

    m_map.insert(CMDCODE, msg_info->getCmdCode().c_str());
    m_map.insert(CONTENT, map_cont);

    QJsonDocument doc = QJsonDocument::fromVariant(QVariant(m_map));
    return QString(doc.toJson()).toUtf8().data();
}

void fromJson(xyc_communication::ReplyEquipmentMoneyQryMsg* msg_info, const std::string& json)
{
    QJsonParseError error;
    QJsonDocument jsonDocument = QJsonDocument::fromJson(QString::fromUtf8(json.c_str()).toUtf8(), &error);
    if (error.error == QJsonParseError::NoError) {
        if (jsonDocument.isObject())
        {
            auto rsltMap = jsonDocument.toVariant().toMap();
            strncpy_s(msg_info->m_rtn_acc->login_name_, rsltMap[LOGINNAME].toString().toLocal8Bit().data(), sizeof(msg_info->m_rtn_acc->login_name_) - 1);
            strncpy_s(msg_info->m_start_day, rsltMap[QRYSTARTDATETIME].toString().toLocal8Bit().data(), sizeof(msg_info->m_start_day) - 1);
            strncpy_s(msg_info->m_end_day, UtilityFun::getAddDate(rsltMap[QRYENDDATETIME].toString().toLocal8Bit().data(), 1).c_str(), sizeof(msg_info->m_end_day) - 1);
        }
    }
}

std::string toJson(xyc_communication::ReplyEquipmentMoneyQryMsgPtr msg_info)
{
    QMap<QString, QVariant> m_map;
    QMap<QString, QVariant> map_cont;

    map_cont.insert(ERRCODE, msg_info->getResult());
    map_cont.insert(BLAST, msg_info->m_blast);
    if (!msg_info->m_blast)
    {
        map_cont.insert(ACCOUNTNAME, QString::fromLocal8Bit(msg_info->m_rtn_acc->account_name_));
        map_cont.insert(LOGINNAME, QString::fromLocal8Bit(msg_info->m_rtn_acc->login_name_));
        map_cont.insert(COMMITIME, msg_info->m_money->apply_date_time_);
        map_cont.insert(APPROVALTIME, msg_info->m_money->approval_date_time_);
        map_cont.insert(FINACEMONEY, (double)msg_info->m_money->apply_money_);
        map_cont.insert(APPROVALSTATUS, msg_info->m_money->apply_status_);
        map_cont.insert(SERIALNO, msg_info->m_money->apply_money_id_);
    }

    m_map.insert(CMDCODE, msg_info->getCmdCode().c_str());
    m_map.insert(CONTENT, map_cont);

    QJsonDocument doc = QJsonDocument::fromVariant(QVariant(m_map));
    return QString(doc.toJson()).toUtf8().data();
}

std::string toJson(xyc_communication::ReplyFeeSetQryMsgPtr msg_info)
{
    QMap<QString, QVariant> m_map;
    QMap<QString, QVariant> map_cont;

    map_cont.insert(ERRCODE, msg_info->getResult());
    map_cont.insert(COMMISSIONRATE, (double)msg_info->m_rtn_fee->trade_commission_);
    map_cont.insert(STAMPFEERATE, (double)msg_info->m_rtn_fee->stamp_duty_);
    map_cont.insert(TRANSFERTAXRATE, (double)msg_info->m_rtn_fee->transfer_);
    map_cont.insert(ONCELOWESTFEE, (double)msg_info->m_rtn_fee->min_trade_commission_);
    map_cont.insert(MATCHFEERATERATE, (double)msg_info->m_rtn_fee->info_match_);
    map_cont.insert(PROCOMMRATE, (double)msg_info->m_rtn_fee->user_profit_rate_);

    m_map.insert(CMDCODE, msg_info->getCmdCode().c_str());
    m_map.insert(CONTENT, map_cont);

    QJsonDocument doc = QJsonDocument::fromVariant(QVariant(m_map));
    return QString(doc.toJson()).toUtf8().data();
}

std::string toJson(xyc_communication::ReplyManagerQryMsgPtr msg_info)
{
    QMap<QString, QVariant> m_map;
    QMap<QString, QVariant> map_cont;

    map_cont.insert(ERRCODE, msg_info->getResult());
    map_cont.insert(BLAST, msg_info->m_blast);
    if (!msg_info->m_blast)
    {
        map_cont.insert(ACCOUNTNAME, QString::fromLocal8Bit(msg_info->m_rtn_acc->account_name_));
        map_cont.insert(LOGINNAME, QString::fromLocal8Bit(msg_info->m_rtn_acc->login_name_));
        map_cont.insert(PASSWORD, QString::fromLocal8Bit(msg_info->m_rtn_acc->password_));
        map_cont.insert(UPPERMANAGER, QString::fromLocal8Bit(msg_info->m_parent_login_name));
    }

    m_map.insert(CMDCODE, msg_info->getCmdCode().c_str());
    m_map.insert(CONTENT, map_cont);

    QJsonDocument doc = QJsonDocument::fromVariant(QVariant(m_map));
    return QString(doc.toJson()).toUtf8().data();
}

std::string toJson(xyc_communication::PushOrderMsgPtr msg_info)
{
    QMap<QString, QVariant> m_map;
    QMap<QString, QVariant> map_cont;

    map_cont.insert(ERRCODE, msg_info->getResult());
    map_cont.insert(ACCOUNTNAME, QString::fromLocal8Bit(msg_info->m_account->account_name_));
    map_cont.insert(LOGINNAME, QString::fromLocal8Bit(msg_info->m_account->login_name_));
    map_cont.insert(STOCKCODE, QString::fromLocal8Bit(msg_info->m_stock_ptr->contract_code_));
    map_cont.insert(STOCKNAME, QString::fromLocal8Bit(msg_info->m_stock_ptr->contract_name_));
    map_cont.insert(ORDERPICE, (double)msg_info->m_order_ptr->order_price_);
    map_cont.insert(ORDERVOLUME, msg_info->m_order_ptr->order_vol_);
    map_cont.insert(DEALQTY, msg_info->m_order_ptr->trade_vol_);
    map_cont.insert(ORDERSTATUS, (int)msg_info->m_order_ptr->order_state_);
    map_cont.insert(ORDERREF, msg_info->m_order_ptr->order_localtmp_ref_);
    map_cont.insert(ORDERID, msg_info->m_order_ptr->shadow_order_id_);
    map_cont.insert(ORDERSTREAM, msg_info->m_order_ptr->order_stream_);
    map_cont.insert(ORDERTYPE, (int)msg_info->m_order_ptr->order_type_);
    map_cont.insert(ORDERMODE, (int)msg_info->m_order_ptr->order_mode_);
    map_cont.insert(ORDERDERECTION, (int)msg_info->m_order_ptr->direct_type_);
    if (msg_info->m_order_ptr->order_state_ == OrderStateType::ORDER_STATE_DELETED)
        map_cont.insert(CANCELORDERNUMBER, msg_info->m_order_ptr->order_vol_ - msg_info->m_order_ptr->trade_vol_);
    else
        map_cont.insert(CANCELORDERNUMBER, 0);
    map_cont.insert(FROZENFUND, (double)msg_info->m_order_ptr->freeze_money_);

    map_cont.insert(CURRENCYRATE, (double)msg_info->m_order_ptr->currency_rate_);
    map_cont.insert(COMMITIME, msg_info->m_order_ptr->generate_datetime_);
    map_cont.insert(CHANGETIME, msg_info->m_order_ptr->update_datetime_);
    map_cont.insert(UPPERMANAGER, QString::fromLocal8Bit(msg_info->m_parent_login_name));

    m_map.insert(CMDCODE, msg_info->getCmdCode().c_str());
    m_map.insert(CONTENT, map_cont);

    QJsonDocument doc = QJsonDocument::fromVariant(QVariant(m_map));
    return QString(doc.toJson()).toUtf8().data();
}

std::string toJson(xyc_communication::PushTradeMsgPtr msg_info)
{
    QMap<QString, QVariant> m_map;
    QMap<QString, QVariant> map_cont;

    map_cont.insert(ERRCODE, msg_info->getResult());
    map_cont.insert(LOGINNAME, QString::fromLocal8Bit(msg_info->m_account->login_name_));
    map_cont.insert(ACCOUNTNAME, QString::fromLocal8Bit(msg_info->m_account->account_name_));
    map_cont.insert(DEALNO, msg_info->m_trade_ptr->shadow_trade_id_);
    map_cont.insert(STOCKCODE, QString::fromLocal8Bit(msg_info->m_stock_ptr->contract_code_));
    map_cont.insert(STOCKNAME, QString::fromLocal8Bit(msg_info->m_stock_ptr->contract_name_));
    map_cont.insert(TRADEDIR, (int)msg_info->m_trade_ptr->direct_type_);
    map_cont.insert(DEALQTY, msg_info->m_trade_ptr->volume_);
    map_cont.insert(DEALAVGPRICE, (double)msg_info->m_trade_ptr->trade_price_);
    map_cont.insert(COMMISSION, (double)msg_info->m_trade_ptr->trade_fee_);
    map_cont.insert(STAMPFEE, (double)msg_info->m_trade_ptr->stamp_fee_);
    map_cont.insert(TRANSFERFEE, (double)msg_info->m_trade_ptr->transfer_fee_);
    map_cont.insert(INFOMATCHFEE, (double)msg_info->m_trade_ptr->infomatch_fee_);
    map_cont.insert(DEALTIME, msg_info->m_trade_ptr->generate_datetime_);
    map_cont.insert(UPPERMANAGER, QString::fromLocal8Bit(msg_info->m_parent_login_name));
    map_cont.insert(CURRENCYRATE, (double)msg_info->m_trade_ptr->currency_rate_);

    m_map.insert(CMDCODE, msg_info->getCmdCode().c_str());
    m_map.insert(CONTENT, map_cont);

    QJsonDocument doc = QJsonDocument::fromVariant(QVariant(m_map));
    return QString(doc.toJson()).toUtf8().data();
}

std::string toJson(xyc_communication::PushPositionMsgPtr msg_info)
{
    QMap<QString, QVariant> m_map;
    QMap<QString, QVariant> map_cont;

    map_cont.insert(ERRCODE, msg_info->getResult());
    map_cont.insert(LOGINNAME, QString::fromLocal8Bit(msg_info->m_account->login_name_));
    map_cont.insert(ACCOUNTNAME, QString::fromLocal8Bit(msg_info->m_account->account_name_));
    map_cont.insert(DEALNO, msg_info->m_position_ptr->position_id_);
    map_cont.insert(STOCKCODE, QString::fromLocal8Bit(msg_info->m_stock_ptr->contract_code_));
    map_cont.insert(STOCKNAME, QString::fromLocal8Bit(msg_info->m_stock_ptr->contract_name_));
    map_cont.insert(POSITIONPRICE, (double)msg_info->m_position_ptr->cost_price_ / (msg_info->m_position_ptr->volume_ + msg_info->m_position_ptr->T_volume_));
    map_cont.insert(POSITIONCOST, (double)msg_info->m_position_ptr->cost_price_);
    map_cont.insert(POSITIONQTY, msg_info->m_position_ptr->volume_ + msg_info->m_position_ptr->T_volume_);
    map_cont.insert(ISSELLQTY, msg_info->m_position_ptr->volume_);
    map_cont.insert(FROZENNUMBER, msg_info->m_position_ptr->freeze_order_vol_);
    map_cont.insert(TRADEDIR, (int)msg_info->m_position_ptr->direct_type_);
    map_cont.insert(CURRENCYRATE, (double)msg_info->m_currency_rate);
    map_cont.insert(UPPERMANAGER, QString::fromLocal8Bit(msg_info->m_parent_login_name));

    m_map.insert(CMDCODE, msg_info->getCmdCode().c_str());
    m_map.insert(CONTENT, map_cont);

    QJsonDocument doc = QJsonDocument::fromVariant(QVariant(m_map));
    return QString(doc.toJson()).toUtf8().data();
}

std::string toJson(xyc_communication::PushMoneyMsgPtr msg_info)
{
    QMap<QString, QVariant> m_map;
    QMap<QString, QVariant> map_cont;

    map_cont.insert(ERRCODE, msg_info->getResult());
    map_cont.insert(LOGINNAME, QString::fromLocal8Bit(msg_info->m_account->login_name_));
    map_cont.insert(ACCOUNTNAME, QString::fromLocal8Bit(msg_info->m_account->account_name_));
    map_cont.insert(PRIORITYFUND, (double)(msg_info->m_money_ptr->priority_fund_));
    map_cont.insert(INFERIORFUND, (double)(msg_info->m_money_ptr->user_deposit_));
    map_cont.insert(AVAILABLEFUNDS, (double)(msg_info->m_money_ptr->getCanUse()));
    map_cont.insert(AVAILABLEGETFUNDS, (double)(msg_info->m_money_ptr->getCanExtract()));
    map_cont.insert(OPENCOST, (double)(msg_info->m_money_ptr->position_cost_price_));
    map_cont.insert(FROZENFUND, (double)msg_info->m_money_ptr->order_freeze_);
    map_cont.insert(UPPERMANAGER, QString::fromLocal8Bit(msg_info->m_parent_login_name));
//     map_cont.insert(WARNINGLINE, (double)msg_info->m_rtn_risk->warningline_);
//     map_cont.insert(FORCELINE, (double)msg_info->m_rtn_risk->forceline_);
//     map_cont.insert(LIMITLINE, (double)msg_info->m_rtn_risk->limitline_);
//     map_cont.insert(LEVERAGERATE, (double)msg_info->m_rtn_risk->lever_rate_);
//     map_cont.insert(COMMISSIONRATE, (double)msg_info->m_rtn_risk->commissionrate_);

    m_map.insert(CMDCODE, msg_info->getCmdCode().c_str());
    m_map.insert(CONTENT, map_cont);

    QJsonDocument doc = QJsonDocument::fromVariant(QVariant(m_map));
    return QString(doc.toJson()).toUtf8().data();
}

std::string toJson(xyc_communication::PushRiskControlMsgPtr msg_info)
{
    QMap<QString, QVariant> m_map;
    QMap<QString, QVariant> map_cont;

    map_cont.insert(ERRCODE, msg_info->getResult());
    map_cont.insert(LOGINNAME, QString::fromLocal8Bit(msg_info->m_account->login_name_));
    map_cont.insert(ACCOUNTNAME, QString::fromLocal8Bit(msg_info->m_account->account_name_));
    map_cont.insert(DATETIME, msg_info->m_date_time);
    map_cont.insert(RISKType, msg_info->m_rc_type);
    map_cont.insert(RISKTEXT, QString::fromLocal8Bit(msg_info->m_remark_text));

    m_map.insert(CMDCODE, msg_info->getCmdCode().c_str());
    m_map.insert(CONTENT, map_cont);

    QJsonDocument doc = QJsonDocument::fromVariant(QVariant(m_map));
    return QString(doc.toJson()).toUtf8().data();
}

// void fromJson(xyc_communication::ReplySelfFunctionMsg* msg_info, const std::string& json)
// {
// 	QJsonParseError error;
// 	QJsonDocument jsonDocument = QJsonDocument::fromJson(QString::fromUtf8(json.c_str()).toUtf8(), &error);
// 	if (error.error == QJsonParseError::NoError) {
// 		if (jsonDocument.isObject())
// 		{
// 			auto rsltMap = jsonDocument.toVariant().toMap();
// 			strncpy_s(msg_info->m_LoginName, rsltMap[LOGINNAME].toString().toLocal8Bit().data(), sizeof(msg_info->m_LoginName) - 1);
// 		}
// 	}
// }

std::string toJson(xyc_communication::ReplySelfFunctionMsgPtr msg_info)
{
	QMap<QString, QVariant> m_map;

	QJsonObject jsonOb;
	QJsonArray jsonArr;

	// content
	for (auto& item : msg_info->m_rtn_ptr)
	{
		jsonOb.insert(ERRCODE, msg_info->getResult());
		jsonOb.insert(FUNCTIONID, item->functionID);
		jsonOb.insert(BUSSNESSID, item->bussnessID);
		jsonOb.insert(NAVIGATIONID, item->NavigationID);
        jsonOb.insert(FUNCTIONNAME, QString::fromLocal8Bit(item->functionName));
        jsonOb.insert(LOGINNAME, QString::fromLocal8Bit(item->login_name_));
		jsonArr.append(jsonOb);
	}

	// cmdcode
	m_map.insert(CMDCODE, msg_info->getCmdCode().c_str());
	m_map.insert(CONTENT, jsonArr);

	QJsonDocument doc = QJsonDocument::fromVariant(QVariant(m_map));
	return QString(doc.toJson()).toUtf8().data();
}

void fromJson(xyc_communication::ReplyRoleFunctionMsg* msg_info, const std::string& json)
{
	QJsonParseError error;
	QJsonDocument jsonDocument = QJsonDocument::fromJson(QString::fromUtf8(json.c_str()).toUtf8(), &error);
	if (error.error == QJsonParseError::NoError) {
		if (jsonDocument.isObject())
		{
			auto rsltMap = jsonDocument.toVariant().toMap();
// 			strncpy_s(msg_info->m_LoginName, rsltMap[LOGINNAME].toString().toLocal8Bit().data(), sizeof(msg_info->m_LoginName) - 1);
			msg_info->m_roleId = rsltMap[OPROLEID].toInt();
		}
	}
}


std::string toJson(xyc_communication::ReplyRoleFunctionMsgPtr msg_info)
{
	QMap<QString, QVariant> m_map;

	QJsonObject jsonOb;
	QJsonArray jsonArr;

	// content
	for (auto& item : msg_info->m_rtn_ptr)
	{
		jsonOb.insert(ERRCODE, msg_info->getResult());
		jsonOb.insert(FUNCTIONID, item->functionID);
		jsonOb.insert(ROLEID, item->roleID);

		jsonOb.insert(OPROLEID, msg_info->m_roleId);
		jsonArr.append(jsonOb);
	}

	// cmdcode
	m_map.insert(CMDCODE, msg_info->getCmdCode().c_str());
	m_map.insert(CONTENT, jsonArr);

	QJsonDocument doc = QJsonDocument::fromVariant(QVariant(m_map));
	return QString(doc.toJson()).toUtf8().data();
}

void fromJson(xyc_communication::ReplyDelRoleMsg* msg_info, const std::string& json)
{
	QJsonParseError error;
	QJsonDocument jsonDocument = QJsonDocument::fromJson(QString::fromUtf8(json.c_str()).toUtf8(), &error);
	if (error.error == QJsonParseError::NoError) {
		if (jsonDocument.isObject())
		{
			auto rsltMap = jsonDocument.toVariant().toMap();

// 			strncpy_s(msg_info->m_LoginName, rsltMap[LOGINNAME].toString().toLocal8Bit().data(), sizeof(msg_info->m_LoginName) - 1);
			msg_info->m_roleId = rsltMap[ROLEID].toInt();
		}
	}
}

std::string toJson(xyc_communication::ReplyDelRoleMsgPtr msg_info)
{
	QMap<QString, QVariant> m_map;
	QMap<QString, QVariant> map_cont;

	map_cont.insert(ERRCODE, msg_info->getResult());
	map_cont.insert(ROLEID, msg_info->m_roleId);

	m_map.insert(CMDCODE, msg_info->getCmdCode().c_str());
	m_map.insert(CONTENT, map_cont);

	QJsonDocument doc = QJsonDocument::fromVariant(QVariant(m_map));
	return QString(doc.toJson()).toUtf8().data();
}

////////////////////////////////
// void fromJson(xyc_communication::ReplyAgencyRolesQryMsg* msg_info, const std::string& json)
// {
// 	QJsonParseError error;
// 	QJsonDocument jsonDocument = QJsonDocument::fromJson(QString::fromUtf8(json.c_str()).toUtf8(), &error);
// 	if (error.error == QJsonParseError::NoError) {
// 		if (jsonDocument.isObject())
// 		{
// 			auto rsltMap = jsonDocument.toVariant().toMap();
// 
// 			strncpy_s(msg_info->m_LoginName, rsltMap[LOGINNAME].toString().toLocal8Bit().data(), sizeof(msg_info->m_LoginName) - 1);
// 		}
// 	}
// }


std::string toJson(xyc_communication::ReplyAgencyRolesQryMsgPtr msg_info)
{
	QMap<QString, QVariant> m_map;
	QMap<QString, QVariant> map_cont;

	map_cont.insert(ERRCODE, msg_info->getResult());
    map_cont.insert(BLAST, msg_info->m_blast);
    if (!msg_info->m_blast)
    {
        map_cont.insert(ROLEID, msg_info->m_rtn_arp->rolesID);
        map_cont.insert(LOGINNAME, QString::fromLocal8Bit(msg_info->m_rtn_arp->login_name_));
    }

	m_map.insert(CMDCODE, msg_info->getCmdCode().c_str());
	m_map.insert(CONTENT, map_cont);

	QJsonDocument doc = QJsonDocument::fromVariant(QVariant(m_map));
	return QString(doc.toJson()).toUtf8().data();
}

/////////////////////////////////////////////////////////////
void fromJson(xyc_communication::ReplyUserRoleAddRelationMsg* msg_info, const std::string& json)
{
	QJsonParseError error;
	QJsonDocument jsonDocument = QJsonDocument::fromJson(QString::fromUtf8(json.c_str()).toUtf8(), &error);
	if (error.error == QJsonParseError::NoError) {
		if (jsonDocument.isObject())
		{
			auto rsltMap = jsonDocument.toVariant().toMap();

// 			strncpy_s(msg_info->m_login_name, rsltMap[OPERATIONLOGINNAME].toString().toLocal8Bit().data(), sizeof(msg_info->m_login_name) - 1);
			strncpy_s(msg_info->m_rtn_arup->login_name_, rsltMap[LOGINNAME].toString().toLocal8Bit().data(), sizeof(msg_info->m_rtn_arup->login_name_) - 1);
			msg_info->m_rtn_arup->rolesID = rsltMap[ROLEID].toInt();
		}
	}
}

std::string toJson(xyc_communication::ReplyUserRoleAddRelationMsgPtr msg_info)
{
	QMap<QString, QVariant> m_map;
	QMap<QString, QVariant> map_cont;

	map_cont.insert(ERRCODE, msg_info->getResult());

	map_cont.insert(ROLEID, msg_info->m_rtn_arup->rolesID);
    map_cont.insert(LOGINNAME, QString::fromLocal8Bit(msg_info->m_rtn_arup->login_name_));

	m_map.insert(CMDCODE, msg_info->getCmdCode().c_str());
	m_map.insert(CONTENT, map_cont);

	QJsonDocument doc = QJsonDocument::fromVariant(QVariant(m_map));
	return QString(doc.toJson()).toUtf8().data();
}

/////////////////////////////////////////////////////

void fromJson(xyc_communication::ReplyDelRoleUserMsg* msg_info, const std::string& json)
{
	QJsonParseError error;
	QJsonDocument jsonDocument = QJsonDocument::fromJson(QString::fromUtf8(json.c_str()).toUtf8(), &error);
	if (error.error == QJsonParseError::NoError) {
		if (jsonDocument.isObject())
		{
			auto rsltMap = jsonDocument.toVariant().toMap();

// 			strncpy_s(msg_info->m_LoginName, rsltMap[OPERATIONLOGINNAME].toString().toLocal8Bit().data(), sizeof(msg_info->m_LoginName) - 1);


			strncpy_s(msg_info->m_rtn_arup->login_name_, rsltMap[LOGINNAME].toString().toLocal8Bit().data(), sizeof(msg_info->m_rtn_arup->login_name_) - 1);
			msg_info->m_rtn_arup->rolesID = rsltMap[ROLEID].toInt();
		}
	}
}

std::string toJson(xyc_communication::ReplyDelRoleUserMsgPtr msg_info)
{
	QMap<QString, QVariant> m_map;
	QMap<QString, QVariant> map_cont;

	map_cont.insert(ERRCODE, msg_info->getResult());

	map_cont.insert(ROLEID, msg_info->m_rtn_arup->rolesID);
    map_cont.insert(LOGINNAME, QString::fromLocal8Bit(msg_info->m_rtn_arup->login_name_));

	m_map.insert(CMDCODE, msg_info->getCmdCode().c_str());
	m_map.insert(CONTENT, map_cont);

	QJsonDocument doc = QJsonDocument::fromVariant(QVariant(m_map));
	return QString(doc.toJson()).toUtf8().data();
}

//////////////////

// void fromJson(xyc_communication::ReplyGetAllBussnessMsg* msg_info, const std::string& json)
// {
// 	QJsonParseError error;
// 	QJsonDocument jsonDocument = QJsonDocument::fromJson(QString::fromUtf8(json.c_str()).toUtf8(), &error);
// 	if (error.error == QJsonParseError::NoError) {
// 		if (jsonDocument.isObject())
// 		{
// 			auto rsltMap = jsonDocument.toVariant().toMap();
// 
// 			strncpy_s(msg_info->m_LoginName, rsltMap[LOGINNAME].toString().toLocal8Bit().data(), sizeof(msg_info->m_LoginName) - 1);
// 		}
// 	}
// }

std::string toJson(xyc_communication::ReplyGetAllBussnessMsgPtr msg_info)
{
	QMap<QString, QVariant> m_map;

	QJsonObject jsonOb;
	QJsonArray jsonArr;

	// content
	for (auto& item : msg_info->m_rtn_abp)
	{
		jsonOb.insert(ERRCODE, msg_info->getResult());
		jsonOb.insert(BUSSNESSID, item->bussnessID);
        jsonOb.insert(BUSSNESSNAME, QString::fromLocal8Bit(item->bussnessName));
		jsonArr.append(jsonOb);
	}

	// cmdcode
	m_map.insert(CMDCODE, msg_info->getCmdCode().c_str());
	m_map.insert(CONTENT, jsonArr);

	QJsonDocument doc = QJsonDocument::fromVariant(QVariant(m_map));
	return QString(doc.toJson()).toUtf8().data();
}

std::string toJson(xyc_communication::ReplyOnlineAccQryMsgPtr msg_info)
{
    QMap<QString, QVariant> m_map;
    QMap<QString, QVariant> map_cont;

    map_cont.insert(ERRCODE, msg_info->getResult());

    map_cont.insert(BLAST, msg_info->m_blast);
    if (!msg_info->m_blast && msg_info->getResult() == Err_Succeed)
    {
        map_cont.insert(ACCOUNTNAME, QString::fromLocal8Bit(msg_info->m_rtn_loginName));
        map_cont.insert(LOGINNAME, QString::fromLocal8Bit(msg_info->m_rtn_accName));
        map_cont.insert(REGDATE, QString::fromLocal8Bit(msg_info->m_rtn_reg_dt));
        map_cont.insert(LOGINTIME, QString::fromLocal8Bit(msg_info->m_rtn_acc->login_datetime_));
        map_cont.insert(LOGINIP, QString::fromLocal8Bit(msg_info->m_rtn_acc->login_ip_));
        map_cont.insert(MACADDRESS, QString::fromLocal8Bit(msg_info->m_rtn_acc->mac_info_));
        map_cont.insert(OPERATIONTYPE, (int)msg_info->m_rtn_acc->op_type_);
    }
    m_map.insert(CMDCODE, msg_info->getCmdCode().c_str());
    m_map.insert(CONTENT, map_cont);

    QJsonDocument doc = QJsonDocument::fromVariant(QVariant(m_map));
    return QString(doc.toJson()).toUtf8().data();
}

void fromJson(xyc_communication::ReplyApplyEquipMoneyMsg* msg_info, const std::string& json)
{
    QJsonParseError error;
    QJsonDocument jsonDocument = QJsonDocument::fromJson(QString::fromUtf8(json.c_str()).toUtf8(), &error);
    if (error.error == QJsonParseError::NoError) {
        if (jsonDocument.isObject())
        {
            auto rsltMap = jsonDocument.toVariant().toMap();
            msg_info->m_appmoney = rsltMap[INMONEYFUND].toDouble();
        }
    }
}

std::string toJson(xyc_communication::ReplyApplyEquipMoneyMsgPtr msg_info)
{
    QMap<QString, QVariant> m_map;
    QMap<QString, QVariant> map_cont;

    map_cont.insert(ERRCODE, msg_info->getResult());

    m_map.insert(CMDCODE, msg_info->getCmdCode().c_str());
    m_map.insert(CONTENT, map_cont);

    QJsonDocument doc = QJsonDocument::fromVariant(QVariant(m_map));
    return QString(doc.toJson()).toUtf8().data();

//     QMap<QString, QVariant> m_map;
// 
//     QJsonObject jsonOb;
//     QJsonArray jsonArr;
//     jsonOb.insert(ERRCODE, msg_info->getResult());
//     jsonArr.append(jsonOb);
// 
//     // cmdcode
//     m_map.insert(CMDCODE, msg_info->getCmdCode().c_str());
//     m_map.insert(CONTENT, jsonArr);
// 
//     QJsonDocument doc = QJsonDocument::fromVariant(QVariant(m_map));
//     return QString(doc.toJson()).toUtf8().data();
}

void fromJson(xyc_communication::ReplyApprovalApplyEquipMoneyMsg* msg_info, const std::string& json)
{
    QJsonParseError error;
    QJsonDocument jsonDocument = QJsonDocument::fromJson(QString::fromUtf8(json.c_str()).toUtf8(), &error);
    if (error.error == QJsonParseError::NoError) {
        if (jsonDocument.isObject())
        {
            auto rsltMap = jsonDocument.toVariant().toMap();
//             strncpy_s(msg_info->m_approval_login_name, rsltMap[APPROVALLOGINNAME].toString().toLocal8Bit().data(), sizeof(msg_info->m_approval_login_name) - 1);
//             strncpy_s(msg_info->m_apply_login_name, rsltMap[LOGINNAME].toString().toLocal8Bit().data(), sizeof(msg_info->m_apply_login_name) - 1);
            msg_info->m_apply_money_id = rsltMap[SERIALNO].toInt();
//             strncpy_s(msg_info->m_apply_money_id, rsltMap[SERIALNO].toString().toLocal8Bit().data(), sizeof(msg_info->m_apply_money_id) - 1);
            msg_info->m_apply_status = (E_APPLY_MONEY_STATUS)rsltMap[APPROVALSTATUS].toInt();
        }
    }
}

std::string toJson(xyc_communication::ReplyApprovalApplyEquipMoneyMsgPtr msg_info)
{
    QMap<QString, QVariant> m_map;
    QMap<QString, QVariant> map_cont;

    map_cont.insert(ERRCODE, msg_info->getResult());
    map_cont.insert(APPROVALSTATUS, msg_info->m_apply_status);
    map_cont.insert(SERIALNO, msg_info->m_apply_money_id);
    map_cont.insert(APPROVALTIME, UtilityFun::getCurrentDateTime().c_str());

    // cmdcode
    m_map.insert(CMDCODE, msg_info->getCmdCode().c_str());
    m_map.insert(CONTENT, map_cont);

    QJsonDocument doc = QJsonDocument::fromVariant(QVariant(m_map));
    return QString(doc.toJson()).toUtf8().data();
}

void fromJson(xyc_communication::ReplyAgencyDeleteMsg* msg_info, const std::string& json)
{
    QJsonParseError error;
    QJsonDocument jsonDocument = QJsonDocument::fromJson(QString::fromUtf8(json.c_str()).toUtf8(), &error);
    if (error.error == QJsonParseError::NoError) {
        if (jsonDocument.isObject())
        {
            auto rsltMap = jsonDocument.toVariant().toMap();
            strncpy_s(msg_info->m_login_name, rsltMap[LOGINNAME].toString().toLocal8Bit().data(), sizeof(msg_info->m_login_name) - 1);
        }
    }
}

std::string toJson(xyc_communication::ReplyAgencyDeleteMsgPtr msg_info)
{
    QMap<QString, QVariant> m_map;
    QMap<QString, QVariant> map_cont;

    map_cont.insert(ERRCODE, msg_info->getResult());
    map_cont.insert(LOGINNAME, msg_info->m_login_name);

    // cmdcode
    m_map.insert(CMDCODE, msg_info->getCmdCode().c_str());
    m_map.insert(CONTENT, map_cont);

    QJsonDocument doc = QJsonDocument::fromVariant(QVariant(m_map));
    return QString(doc.toJson()).toUtf8().data();
}

void fromJson(xyc_communication::ReplyChildDeleteMsg* msg_info, const std::string& json)
{
    QJsonParseError error;
    QJsonDocument jsonDocument = QJsonDocument::fromJson(QString::fromUtf8(json.c_str()).toUtf8(), &error);
    if (error.error == QJsonParseError::NoError) {
        if (jsonDocument.isObject())
        {
            auto rsltMap = jsonDocument.toVariant().toMap();
            strncpy_s(msg_info->m_login_name, rsltMap[LOGINNAME].toString().toLocal8Bit().data(), sizeof(msg_info->m_login_name) - 1);
        }
    }
}

std::string toJson(xyc_communication::ReplyChildDeleteMsgPtr msg_info)
{
    QMap<QString, QVariant> m_map;
    QMap<QString, QVariant> map_cont;

    map_cont.insert(ERRCODE, msg_info->getResult());
    map_cont.insert(LOGINNAME, msg_info->m_login_name);

    // cmdcode
    m_map.insert(CMDCODE, msg_info->getCmdCode().c_str());
    m_map.insert(CONTENT, map_cont);

    QJsonDocument doc = QJsonDocument::fromVariant(QVariant(m_map));
    return QString(doc.toJson()).toUtf8().data();
}

void fromJson(xyc_communication::ReplyFunderDeleteMsg* msg_info, const std::string& json)
{
    QJsonParseError error;
    QJsonDocument jsonDocument = QJsonDocument::fromJson(QString::fromUtf8(json.c_str()).toUtf8(), &error);
    if (error.error == QJsonParseError::NoError) {
        if (jsonDocument.isObject())
        {
            auto rsltMap = jsonDocument.toVariant().toMap();
            strncpy_s(msg_info->m_login_name, rsltMap[LOGINNAME].toString().toLocal8Bit().data(), sizeof(msg_info->m_login_name) - 1);
        }
    }
}

std::string toJson(xyc_communication::ReplyFunderDeleteMsgPtr msg_info)
{
    QMap<QString, QVariant> m_map;
    QMap<QString, QVariant> map_cont;

    map_cont.insert(ERRCODE, msg_info->getResult());
    map_cont.insert(LOGINNAME, msg_info->m_login_name);

    // cmdcode
    m_map.insert(CMDCODE, msg_info->getCmdCode().c_str());
    m_map.insert(CONTENT, map_cont);

    QJsonDocument doc = QJsonDocument::fromVariant(QVariant(m_map));
    return QString(doc.toJson()).toUtf8().data();
}

void fromJson(xyc_communication::ReplyManagerDeleteMsg* msg_info, const std::string& json)
{
    QJsonParseError error;
    QJsonDocument jsonDocument = QJsonDocument::fromJson(QString::fromUtf8(json.c_str()).toUtf8(), &error);
    if (error.error == QJsonParseError::NoError) {
        if (jsonDocument.isObject())
        {
            auto rsltMap = jsonDocument.toVariant().toMap();
            strncpy_s(msg_info->m_login_name, rsltMap[LOGINNAME].toString().toLocal8Bit().data(), sizeof(msg_info->m_login_name) - 1);
        }
    }
}

std::string toJson(xyc_communication::ReplyManagerDeleteMsgPtr msg_info)
{
    QMap<QString, QVariant> m_map;
    QMap<QString, QVariant> map_cont;

    map_cont.insert(ERRCODE, msg_info->getResult());
    map_cont.insert(LOGINNAME, msg_info->m_login_name);

    // cmdcode
    m_map.insert(CMDCODE, msg_info->getCmdCode().c_str());
    m_map.insert(CONTENT, map_cont);

    QJsonDocument doc = QJsonDocument::fromVariant(QVariant(m_map));
    return QString(doc.toJson()).toUtf8().data();
}

std::string toJson(xyc_communication::ReplyStockBlackQryMsgPtr msg_info)
{
    QMap<QString, QVariant> m_map;
    QMap<QString, QVariant> map_cont;

    map_cont.insert(ERRCODE, msg_info->getResult());
    map_cont.insert(BLAST, msg_info->m_blast);
    if (!msg_info->m_blast)
    {
        map_cont.insert(STOCKCODE, msg_info->m_contract_code);
        map_cont.insert(STOCKNAME, QString::fromLocal8Bit(msg_info->m_contract_name));
        map_cont.insert(BBLACK, msg_info->m_isBlack);
    }
    // cmdcode
    m_map.insert(CMDCODE, msg_info->getCmdCode().c_str());
    m_map.insert(CONTENT, map_cont);

    QJsonDocument doc = QJsonDocument::fromVariant(QVariant(m_map));
    return QString(doc.toJson()).toUtf8().data();
}

void fromJson(xyc_communication::ReplyStockBlackSetMsg* msg_info, const std::string& json)
{
    QJsonParseError error;
    QJsonDocument jsonDocument = QJsonDocument::fromJson(QString::fromUtf8(json.c_str()).toUtf8(), &error);
    if (error.error == QJsonParseError::NoError) {
        if (jsonDocument.isObject())
        {
            auto rsltMap = jsonDocument.toVariant().toMap();
            strncpy_s(msg_info->m_contract_code, rsltMap[STOCKCODE].toString().toLocal8Bit().data(), sizeof(msg_info->m_contract_code) - 1);
            msg_info->m_isBlack = rsltMap[BBLACK].toBool();
        }
    }
}

std::string toJson(xyc_communication::ReplyStockBlackSetMsgPtr msg_info)
{
    QMap<QString, QVariant> m_map;
    QMap<QString, QVariant> map_cont;
    
    map_cont.insert(ERRCODE, msg_info->getResult());
    map_cont.insert(STOCKCODE, msg_info->m_contract_code);
    map_cont.insert(STOCKNAME, QString::fromLocal8Bit(msg_info->m_contract_name));
    map_cont.insert(BBLACK, msg_info->m_isBlack);
   
    // cmdcode
    m_map.insert(CMDCODE, msg_info->getCmdCode().c_str());
    m_map.insert(CONTENT, map_cont);

    QJsonDocument doc = QJsonDocument::fromVariant(QVariant(m_map));
    return QString(doc.toJson()).toUtf8().data();
}

std::string toJson(xyc_communication::ReplyForbidBuySellQryMsgPtr msg_info)
{
    QMap<QString, QVariant> m_map;
    QMap<QString, QVariant> map_cont;

    map_cont.insert(ERRCODE, msg_info->getResult());
    map_cont.insert(BLAST, msg_info->m_blast);
    if (!msg_info->m_blast)
    {
        map_cont.insert(RISKPROJECT, msg_info->forbid_trade->forbid_trade_type_);
        map_cont.insert(OPERATIONTYPE, msg_info->forbid_trade->forbid_trade_op_type_);
        map_cont.insert(SWITCHFLAG, msg_info->forbid_trade->bstart_);
    }
    // cmdcode
    m_map.insert(CMDCODE, msg_info->getCmdCode().c_str());
    m_map.insert(CONTENT, map_cont);

    QJsonDocument doc = QJsonDocument::fromVariant(QVariant(m_map));
    return QString(doc.toJson()).toUtf8().data();
}

void fromJson(xyc_communication::ReplyForbidBuySellSetMsg* msg_info, const std::string& json)
{
    QJsonParseError error;
    QJsonDocument jsonDocument = QJsonDocument::fromJson(QString::fromUtf8(json.c_str()).toUtf8(), &error);
    if (error.error == QJsonParseError::NoError) {
        if (jsonDocument.isObject())
        {
            auto rsltMap = jsonDocument.toVariant().toMap();
            msg_info->forbid_trade->forbid_trade_type_ = (ForbidTradeType)rsltMap[RISKPROJECT].toInt();
            msg_info->forbid_trade->forbid_trade_op_type_ = (ForbidTradeOperatorType)rsltMap[OPERATIONTYPE].toInt();
            msg_info->forbid_trade->bstart_ = rsltMap[SWITCHFLAG].toBool();
        }
    }
}

std::string toJson(xyc_communication::ReplyForbidBuySellSetMsgPtr msg_info)
{
    QMap<QString, QVariant> m_map;
    QMap<QString, QVariant> map_cont;

    map_cont.insert(ERRCODE, msg_info->getResult());
    map_cont.insert(RISKPROJECT, msg_info->forbid_trade->forbid_trade_type_);
    map_cont.insert(OPERATIONTYPE, msg_info->forbid_trade->forbid_trade_op_type_);
    map_cont.insert(SWITCHFLAG, msg_info->forbid_trade->bstart_);

    // cmdcode
    m_map.insert(CMDCODE, msg_info->getCmdCode().c_str());
    m_map.insert(CONTENT, map_cont);

    QJsonDocument doc = QJsonDocument::fromVariant(QVariant(m_map));
    return QString(doc.toJson()).toUtf8().data();
}

std::string toJson(xyc_communication::ReplyPosiRateQryMsgPtr msg_info)
{
    QMap<QString, QVariant> m_map;
    QMap<QString, QVariant> map_cont;

    map_cont.insert(ERRCODE, msg_info->getResult());
    map_cont.insert(BLAST, msg_info->m_blast);
    if (!msg_info->m_blast)
    {
        map_cont.insert(RISKPROJECT, msg_info->posit_rate->position_rate_type_);
        map_cont.insert(POSITIONRATE, msg_info->posit_rate->position_rate_);
        map_cont.insert(SWITCHFLAG, msg_info->posit_rate->bstart_);
    }

    // cmdcode
    m_map.insert(CMDCODE, msg_info->getCmdCode().c_str());
    m_map.insert(CONTENT, map_cont);

    QJsonDocument doc = QJsonDocument::fromVariant(QVariant(m_map));
    return QString(doc.toJson()).toUtf8().data();
}

void fromJson(xyc_communication::ReplyPosiRateSetMsg* msg_info, const std::string& json)
{
    QJsonParseError error;
    QJsonDocument jsonDocument = QJsonDocument::fromJson(QString::fromUtf8(json.c_str()).toUtf8(), &error);
    if (error.error == QJsonParseError::NoError) {
        if (jsonDocument.isObject())
        {
            auto rsltMap = jsonDocument.toVariant().toMap();
            msg_info->posit_rate->position_rate_type_ = (PositionRateType)rsltMap[RISKPROJECT].toInt();
            msg_info->posit_rate->position_rate_ = rsltMap[POSITIONRATE].toInt();
            msg_info->posit_rate->bstart_ = rsltMap[SWITCHFLAG].toBool();
        }
    }
}

std::string toJson(xyc_communication::ReplyPosiRateSetMsgPtr msg_info)
{
    QMap<QString, QVariant> m_map;
    QMap<QString, QVariant> map_cont;

    map_cont.insert(ERRCODE, msg_info->getResult());
    map_cont.insert(RISKPROJECT, msg_info->posit_rate->position_rate_type_);
    map_cont.insert(POSITIONRATE, msg_info->posit_rate->position_rate_);
    map_cont.insert(SWITCHFLAG, msg_info->posit_rate->bstart_);

    // cmdcode
    m_map.insert(CMDCODE, msg_info->getCmdCode().c_str());
    m_map.insert(CONTENT, map_cont);

    QJsonDocument doc = QJsonDocument::fromVariant(QVariant(m_map));
    return QString(doc.toJson()).toUtf8().data();
}

std::string toJson(xyc_communication::ReplyGetCustomStockMsgPtr msg_info)
{
    QMap<QString, QVariant> m_map;
    QMap<QString, QVariant> map_cont;

    map_cont.insert(ERRCODE, msg_info->getResult());
    map_cont.insert(BLAST, msg_info->m_blast);
    if (!msg_info->m_blast)
    {
        map_cont.insert(STOCKCODE, QString::fromLocal8Bit(msg_info->m_stock_ptr->contract_code_));
        map_cont.insert(STOCKNAME, QString::fromLocal8Bit(msg_info->m_stock_ptr->contract_name_));
        map_cont.insert(EXCHANGECD, QString::fromLocal8Bit(msg_info->m_exchange_code));
        map_cont.insert(OPENTIME, QString::fromLocal8Bit(msg_info->m_stock_ptr->open_datetime_));
        map_cont.insert(STOCKAREA, (int)msg_info->m_stock_ptr->stock_area_);
        map_cont.insert(STOCKPLATEAREA, (int)msg_info->m_stock_ptr->stock_plate_area_);
        map_cont.insert(TOTALSHARES, (double)msg_info->m_stock_ptr->total_shares_);
    }

    m_map.insert(CMDCODE, msg_info->getCmdCode().c_str());
    m_map.insert(CONTENT, map_cont);

    QJsonDocument doc = QJsonDocument::fromVariant(QVariant(m_map));
    return QString(doc.toJson()).toUtf8().data();
}

void fromJson(xyc_communication::ReplyAddCustomStockMsg* msg_info, const std::string& json)
{
    QJsonParseError error;
    QJsonDocument jsonDocument = QJsonDocument::fromJson(QString::fromUtf8(json.c_str()).toUtf8(), &error);
    if (error.error == QJsonParseError::NoError) {
        if (jsonDocument.isObject())
        {
            auto rsltMap = jsonDocument.toVariant().toMap();
            strncpy_s(msg_info->m_contract_code, rsltMap[STOCKCODE].toString().toLocal8Bit().data(), sizeof(msg_info->m_contract_code) - 1);
        }
    }
}

std::string toJson(xyc_communication::ReplyAddCustomStockMsgPtr msg_info)
{
    QMap<QString, QVariant> m_map;
    QMap<QString, QVariant> map_cont;

    map_cont.insert(ERRCODE, msg_info->getResult());
    map_cont.insert(STOCKCODE, QString::fromLocal8Bit(msg_info->m_stock_ptr->contract_code_));
    map_cont.insert(STOCKNAME, QString::fromLocal8Bit(msg_info->m_stock_ptr->contract_name_));
    map_cont.insert(OPENTIME, QString::fromLocal8Bit(msg_info->m_stock_ptr->open_datetime_));
    map_cont.insert(STOCKAREA, (int)msg_info->m_stock_ptr->stock_area_);
    map_cont.insert(STOCKPLATEAREA, (int)msg_info->m_stock_ptr->stock_plate_area_);
    map_cont.insert(TOTALSHARES, (double)msg_info->m_stock_ptr->total_shares_);
    map_cont.insert(EXCHANGECD, QString::fromLocal8Bit(msg_info->m_exchange_code));

    m_map.insert(CMDCODE, msg_info->getCmdCode().c_str());
    m_map.insert(CONTENT, map_cont);

    QJsonDocument doc = QJsonDocument::fromVariant(QVariant(m_map));
    return QString(doc.toJson()).toUtf8().data();
}

void fromJson(xyc_communication::ReplyDelCustomStockMsg* msg_info, const std::string& json)
{
    QJsonParseError error;
    QJsonDocument jsonDocument = QJsonDocument::fromJson(QString::fromUtf8(json.c_str()).toUtf8(), &error);
    if (error.error == QJsonParseError::NoError) {
        if (jsonDocument.isObject())
        {
            auto rsltMap = jsonDocument.toVariant().toMap();
            strncpy_s(msg_info->m_contract_code, rsltMap[STOCKCODE].toString().toLocal8Bit().data(), sizeof(msg_info->m_contract_code) - 1);
        }
    }
}

std::string toJson(xyc_communication::ReplyDelCustomStockMsgPtr msg_info)
{
    QMap<QString, QVariant> m_map;
    QMap<QString, QVariant> map_cont;

    map_cont.insert(ERRCODE, msg_info->getResult());
    map_cont.insert(STOCKCODE, QString::fromLocal8Bit(msg_info->m_stock_ptr->contract_code_));
    map_cont.insert(STOCKNAME, QString::fromLocal8Bit(msg_info->m_stock_ptr->contract_name_));
    map_cont.insert(OPENTIME, QString::fromLocal8Bit(msg_info->m_stock_ptr->open_datetime_));
    map_cont.insert(STOCKAREA, (int)msg_info->m_stock_ptr->stock_area_);
    map_cont.insert(STOCKPLATEAREA, (int)msg_info->m_stock_ptr->stock_plate_area_);
    map_cont.insert(TOTALSHARES, (double)msg_info->m_stock_ptr->total_shares_);
    map_cont.insert(EXCHANGECD, QString::fromLocal8Bit(msg_info->m_exchange_code));

    m_map.insert(CMDCODE, msg_info->getCmdCode().c_str());
    m_map.insert(CONTENT, map_cont);

    QJsonDocument doc = QJsonDocument::fromVariant(QVariant(m_map));
    return QString(doc.toJson()).toUtf8().data();
}


void fromJson(xyc_communication::ReplyChangeRoleUserMsg* msg_info, const std::string& json)
{
	QJsonParseError error;
	QJsonDocument jsonDocument = QJsonDocument::fromJson(QString::fromUtf8(json.c_str()).toUtf8(), &error);
	if (error.error == QJsonParseError::NoError) {
		if (jsonDocument.isObject())
		{
			auto rsltMap = jsonDocument.toVariant().toMap();

			strncpy_s(msg_info->m_rtn_arup->login_name_, rsltMap[LOGINNAME].toString().toLocal8Bit().data(), sizeof(msg_info->m_rtn_arup->login_name_) - 1);
			msg_info->m_rtn_arup->rolesID = rsltMap[ROLEID].toInt();
		}
	}
}

std::string toJson(xyc_communication::ReplyChangeRoleUserMsgPtr msg_info)
{
	QMap<QString, QVariant> m_map;
	QMap<QString, QVariant> map_cont;

	map_cont.insert(ERRCODE, msg_info->getResult());

	map_cont.insert(ROLEID, msg_info->m_rtn_arup->rolesID);
	map_cont.insert(LOGINNAME, QString::fromLocal8Bit(msg_info->m_rtn_arup->login_name_));

	m_map.insert(CMDCODE, msg_info->getCmdCode().c_str());
	m_map.insert(CONTENT, map_cont);

	QJsonDocument doc = QJsonDocument::fromVariant(QVariant(m_map));
	return QString(doc.toJson()).toUtf8().data();
}

void fromJson(xyc_communication::ReplyChildAccAutoAddMsg* msg_info, const std::string& json)
{
    QJsonParseError error;
    QJsonDocument jsonDocument = QJsonDocument::fromJson(QString::fromUtf8(json.c_str()).toUtf8(), &error);
    if (error.error == QJsonParseError::NoError) {
        if (jsonDocument.isObject())
        {
            auto rsltMap = jsonDocument.toVariant().toMap();

            strncpy_s(msg_info->m_rtn_acc->account_name_, rsltMap[ACCOUNTNAME].toString().toLocal8Bit().data(), sizeof(msg_info->m_rtn_acc->account_name_) - 1);
            strncpy_s(msg_info->m_rtn_acc->login_name_, rsltMap[LOGINNAME].toString().toLocal8Bit().data(), sizeof(msg_info->m_rtn_acc->login_name_) - 1);
            strncpy_s(msg_info->m_rtn_acc->password_, rsltMap[PASSWORD].toString().toLocal8Bit().data(), sizeof(msg_info->m_rtn_acc->password_) - 1);
            strncpy_s(msg_info->m_pop_link, rsltMap[POPULARLINK].toString().toLocal8Bit().data(), sizeof(msg_info->m_rtn_acc->login_name_) - 1);
            msg_info->m_rtn_acc->type_ = (E_ACCOUNT_TYPE)rsltMap[ACCOUNTTYPE].toInt();
        }
    }
}

std::string toJson(xyc_communication::ReplyChildAccAutoAddMsgPtr msg_info)
{
    QMap<QString, QVariant> m_map;

    QMap<QString, QVariant> map_cont;

    map_cont.insert(ERRCODE, msg_info->getResult());
    map_cont.insert(CREATELOGINNAME, QString::fromLocal8Bit(msg_info->getLoginName().c_str()));
    map_cont.insert(ACCOUNTNAME, QString::fromLocal8Bit(msg_info->m_rtn_acc->account_name_));
    map_cont.insert(LOGINNAME, QString::fromLocal8Bit(msg_info->m_rtn_acc->login_name_));
    map_cont.insert(PASSWORD, QString::fromLocal8Bit(msg_info->m_rtn_acc->password_));
    map_cont.insert(INFERIORFUND, (double)(msg_info->m_rtn_money->user_deposit_));
    map_cont.insert(PRIORITYFUND, (double)msg_info->m_rtn_money->priority_fund_);
    map_cont.insert(AVAILABLEFUNDS, (double)(msg_info->m_rtn_money->getCanUse()));
    map_cont.insert(AVAILABLEGETFUNDS, (double)(msg_info->m_rtn_money->getCanExtract()));
    map_cont.insert(OPENCOST, (double)(msg_info->m_rtn_money->position_cost_price_));
    map_cont.insert(UPPERFUNDNAME, QString::fromLocal8Bit(msg_info->m_fund_login_name));
    map_cont.insert(UPPERMANAGER, QString::fromLocal8Bit(msg_info->m_parent_login_name));
    map_cont.insert(WARNINGLINE, (double)msg_info->m_rtn_risk->warningline_);
    map_cont.insert(FORCELINE, (double)msg_info->m_rtn_risk->forceline_);
    map_cont.insert(LIMITLINE, (double)msg_info->m_rtn_risk->limitline_);
    map_cont.insert(LEVERAGERATE, (double)msg_info->m_rtn_risk->lever_rate_);
    map_cont.insert(COMMISSIONRATE, (double)msg_info->m_rtn_risk->commissionrate_);
    map_cont.insert(ACCOUNTTYPE, msg_info->m_rtn_acc->type_);
    map_cont.insert(ACCOUNTSTATUS, msg_info->m_rtn_acc->status_);

    m_map.insert(CMDCODE, msg_info->getCmdCode().c_str());
    m_map.insert(CONTENT, map_cont);

    QJsonDocument doc = QJsonDocument::fromVariant(QVariant(m_map));
    return QString(doc.toJson()).toUtf8().data();
}

void fromJson(xyc_communication::ReplyAutoInMoneyMsg* msg_info, const std::string& json)
{
    QJsonParseError error;
    QJsonDocument jsonDocument = QJsonDocument::fromJson(QString::fromUtf8(json.c_str()).toUtf8(), &error);
    if (error.error == QJsonParseError::NoError) {
        if (jsonDocument.isObject())
        {
            auto rsltMap = jsonDocument.toVariant().toMap();
            msg_info->m_appmoney = rsltMap[INMONEYFUND].toDouble();
            strncpy_s(msg_info->m_login_name, rsltMap[LOGINNAME].toString().toLocal8Bit().data(), sizeof(msg_info->m_login_name) - 1);
        }
    }
}

std::string toJson(xyc_communication::ReplyAutoInMoneyMsgPtr msg_info)
{
    QMap<QString, QVariant> m_map;
    QMap<QString, QVariant> map_cont;

    map_cont.insert(ERRCODE, msg_info->getResult());

    m_map.insert(CMDCODE, msg_info->getCmdCode().c_str());
    m_map.insert(CONTENT, map_cont);

    QJsonDocument doc = QJsonDocument::fromVariant(QVariant(m_map));
    return QString(doc.toJson()).toUtf8().data();
}

void fromJson(xyc_communication::ReplyAutoInMoneyApprovalMsg* msg_info, const std::string& json)
{
    QJsonParseError error;
    QJsonDocument jsonDocument = QJsonDocument::fromJson(QString::fromUtf8(json.c_str()).toUtf8(), &error);
    if (error.error == QJsonParseError::NoError) {
        if (jsonDocument.isObject())
        {
            auto rsltMap = jsonDocument.toVariant().toMap();
            msg_info->m_apply_money_id = rsltMap[SERIALNO].toInt();
//             strncpy_s(msg_info->m_apply_money_id, rsltMap[SERIALNO].toString().toLocal8Bit().data(), sizeof(msg_info->m_apply_money_id) - 1);
            msg_info->m_apply_status = (E_APPLY_MONEY_STATUS)rsltMap[APPROVALSTATUS].toInt();
        }
    }
}

std::string toJson(xyc_communication::ReplyAutoInMoneyApprovalMsgPtr msg_info)
{
    QMap<QString, QVariant> m_map;
    QMap<QString, QVariant> map_cont;

    map_cont.insert(ERRCODE, msg_info->getResult());
    map_cont.insert(APPROVALSTATUS, msg_info->m_apply_status);
    map_cont.insert(SERIALNO, msg_info->m_apply_money_id);
    map_cont.insert(APPROVALTIME, UtilityFun::getCurrentDateTime().c_str());

    // cmdcode
    m_map.insert(CMDCODE, msg_info->getCmdCode().c_str());
    m_map.insert(CONTENT, map_cont);

    QJsonDocument doc = QJsonDocument::fromVariant(QVariant(m_map));
    return QString(doc.toJson()).toUtf8().data();
}

void fromJson(xyc_communication::ReplyAutoInMoneyQryMsg* msg_info, const std::string& json)
{
    QJsonParseError error;
    QJsonDocument jsonDocument = QJsonDocument::fromJson(QString::fromUtf8(json.c_str()).toUtf8(), &error);
    if (error.error == QJsonParseError::NoError) {
        if (jsonDocument.isObject())
        {
            auto rsltMap = jsonDocument.toVariant().toMap();
            strncpy_s(msg_info->m_rtn_acc->login_name_, rsltMap[LOGINNAME].toString().toLocal8Bit().data(), sizeof(msg_info->m_rtn_acc->login_name_) - 1);
            strncpy_s(msg_info->m_start_day, rsltMap[QRYSTARTDATETIME].toString().toLocal8Bit().data(), sizeof(msg_info->m_start_day) - 1);
            strncpy_s(msg_info->m_end_day, UtilityFun::getAddDate(rsltMap[QRYENDDATETIME].toString().toLocal8Bit().data(), 1).c_str(), sizeof(msg_info->m_end_day) - 1);
        }
    }
}

std::string toJson(xyc_communication::ReplyAutoInMoneyQryMsgPtr msg_info)
{
    QMap<QString, QVariant> m_map;
    QMap<QString, QVariant> map_cont;

    map_cont.insert(ERRCODE, msg_info->getResult());
    map_cont.insert(BLAST, msg_info->m_blast);
    if (!msg_info->m_blast)
    {
        map_cont.insert(ACCOUNTNAME, QString::fromLocal8Bit(msg_info->m_rtn_acc->account_name_));
        map_cont.insert(LOGINNAME, QString::fromLocal8Bit(msg_info->m_rtn_acc->login_name_));
        map_cont.insert(COMMITIME, msg_info->m_money->apply_date_time_);
        map_cont.insert(APPROVALTIME, msg_info->m_money->approval_date_time_);
        map_cont.insert(INMONEYFUND, (double)msg_info->m_money->apply_money_);
        map_cont.insert(APPROVALSTATUS, msg_info->m_money->apply_status_);
        map_cont.insert(SERIALNO, msg_info->m_money->apply_money_id_);
    }

    m_map.insert(CMDCODE, msg_info->getCmdCode().c_str());
    m_map.insert(CONTENT, map_cont);

    QJsonDocument doc = QJsonDocument::fromVariant(QVariant(m_map));
    return QString(doc.toJson()).toUtf8().data();
}

void fromJson(xyc_communication::ReplyAutoOutMoneyMsg* msg_info, const std::string& json)
{
    QJsonParseError error;
    QJsonDocument jsonDocument = QJsonDocument::fromJson(QString::fromUtf8(json.c_str()).toUtf8(), &error);
    if (error.error == QJsonParseError::NoError) {
        if (jsonDocument.isObject())
        {
            auto rsltMap = jsonDocument.toVariant().toMap();
            strncpy_s(msg_info->m_real_name, rsltMap[BANKOPNENAME].toString().toLocal8Bit().data(), sizeof(msg_info->m_real_name) - 1);
            strncpy_s(msg_info->m_bank_name, rsltMap[BANKNAME].toString().toLocal8Bit().data(), sizeof(msg_info->m_bank_name) - 1);
            strncpy_s(msg_info->m_bank_card, rsltMap[BANKCARD].toString().toLocal8Bit().data(), sizeof(msg_info->m_bank_card) - 1);
            msg_info->m_appmoney = rsltMap[OUTMONEYFUND].toDouble();
        }
    }
}

std::string toJson(xyc_communication::ReplyAutoOutMoneyMsgPtr msg_info)
{
    QMap<QString, QVariant> m_map;
    QMap<QString, QVariant> map_cont;

    map_cont.insert(ERRCODE, msg_info->getResult());

    m_map.insert(CMDCODE, msg_info->getCmdCode().c_str());
    m_map.insert(CONTENT, map_cont);

    QJsonDocument doc = QJsonDocument::fromVariant(QVariant(m_map));
    return QString(doc.toJson()).toUtf8().data();
}

void fromJson(xyc_communication::ReplyAutoOutMoneyApprovalMsg* msg_info, const std::string& json)
{
    QJsonParseError error;
    QJsonDocument jsonDocument = QJsonDocument::fromJson(QString::fromUtf8(json.c_str()).toUtf8(), &error);
    if (error.error == QJsonParseError::NoError) {
        if (jsonDocument.isObject())
        {
            auto rsltMap = jsonDocument.toVariant().toMap();
            msg_info->m_apply_money_id = rsltMap[SERIALNO].toInt();
//             strncpy_s(msg_info->m_apply_money_id, rsltMap[SERIALNO].toString().toLocal8Bit().data(), sizeof(msg_info->m_apply_money_id) - 1);
            msg_info->m_apply_status = (E_APPLY_MONEY_STATUS)rsltMap[APPROVALSTATUS].toInt();
        }
    }
}

std::string toJson(xyc_communication::ReplyAutoOutMoneyApprovalMsgPtr msg_info)
{
    QMap<QString, QVariant> m_map;
    QMap<QString, QVariant> map_cont;

    map_cont.insert(ERRCODE, msg_info->getResult());
    map_cont.insert(APPROVALSTATUS, msg_info->m_apply_status);
    map_cont.insert(SERIALNO, msg_info->m_apply_money_id);
    map_cont.insert(APPROVALTIME, UtilityFun::getCurrentDateTime().c_str());

    // cmdcode
    m_map.insert(CMDCODE, msg_info->getCmdCode().c_str());
    m_map.insert(CONTENT, map_cont);

    QJsonDocument doc = QJsonDocument::fromVariant(QVariant(m_map));
    return QString(doc.toJson()).toUtf8().data();
}

void fromJson(xyc_communication::ReplyAutoOutMoneyQryMsg* msg_info, const std::string& json)
{
    QJsonParseError error;
    QJsonDocument jsonDocument = QJsonDocument::fromJson(QString::fromUtf8(json.c_str()).toUtf8(), &error);
    if (error.error == QJsonParseError::NoError) {
        if (jsonDocument.isObject())
        {
            auto rsltMap = jsonDocument.toVariant().toMap();
            strncpy_s(msg_info->m_rtn_acc->login_name_, rsltMap[LOGINNAME].toString().toLocal8Bit().data(), sizeof(msg_info->m_rtn_acc->login_name_) - 1);
            strncpy_s(msg_info->m_start_day, rsltMap[QRYSTARTDATETIME].toString().toLocal8Bit().data(), sizeof(msg_info->m_start_day) - 1);
            strncpy_s(msg_info->m_end_day, UtilityFun::getAddDate(rsltMap[QRYENDDATETIME].toString().toLocal8Bit().data(), 1).c_str(), sizeof(msg_info->m_end_day) - 1);
        }
    }
}

std::string toJson(xyc_communication::ReplyAutoOutMoneyQryMsgPtr msg_info)
{
    QMap<QString, QVariant> m_map;
    QMap<QString, QVariant> map_cont;

    map_cont.insert(ERRCODE, msg_info->getResult());
    map_cont.insert(BLAST, msg_info->m_blast);
    if (!msg_info->m_blast)
    {
        map_cont.insert(ACCOUNTNAME, QString::fromLocal8Bit(msg_info->m_rtn_acc->account_name_));
        map_cont.insert(LOGINNAME, QString::fromLocal8Bit(msg_info->m_rtn_acc->login_name_));
        map_cont.insert(COMMITIME, msg_info->m_money->apply_date_time_);
        map_cont.insert(APPROVALTIME, msg_info->m_money->approval_date_time_);
        map_cont.insert(OUTMONEYFUND, (double)msg_info->m_money->apply_money_);
        map_cont.insert(BANKOPNENAME, QString::fromLocal8Bit(msg_info->m_money->real_name_));
        map_cont.insert(BANKNAME, QString::fromLocal8Bit(msg_info->m_money->bank_name_));
        map_cont.insert(BANKCARD, QString::fromLocal8Bit(msg_info->m_money->bank_card_));
        map_cont.insert(APPROVALSTATUS, (E_APPLY_MONEY_STATUS)msg_info->m_money->apply_status_);
        map_cont.insert(SERIALNO, msg_info->m_money->apply_money_id_);
    }

    m_map.insert(CMDCODE, msg_info->getCmdCode().c_str());
    m_map.insert(CONTENT, map_cont);

    QJsonDocument doc = QJsonDocument::fromVariant(QVariant(m_map));
    return QString(doc.toJson()).toUtf8().data();
}

void fromJson(xyc_communication::ReplyCommissQryMsg* msg_info, const std::string& json)
{
    QJsonParseError error;
    QJsonDocument jsonDocument = QJsonDocument::fromJson(QString::fromUtf8(json.c_str()).toUtf8(), &error);
    if (error.error == QJsonParseError::NoError) {
        if (jsonDocument.isObject())
        {
            auto rsltMap = jsonDocument.toVariant().toMap();
            strncpy_s(msg_info->m_qry_login_name, rsltMap[LOGINNAME].toString().toLocal8Bit().data(), sizeof(msg_info->m_qry_login_name) - 1);
            strncpy_s(msg_info->m_start_day, UtilityFun::getAddDate(rsltMap[QRYSTARTDATETIME].toString().toLocal8Bit().data(), 0).c_str(), sizeof(msg_info->m_start_day) - 1);
            strncpy_s(msg_info->m_end_day, rsltMap[QRYENDDATETIME].toString().toLocal8Bit().data(), sizeof(msg_info->m_end_day) - 1);
        }
    }
}

std::string toJson(xyc_communication::ReplyCommissQryMsgPtr msg_info)
{
    QMap<QString, QVariant> m_map;
    QMap<QString, QVariant> map_cont;

    map_cont.insert(ERRCODE, msg_info->getResult());
    map_cont.insert(ACCOUNTNAME, QString::fromLocal8Bit(msg_info->m_rtn_acc->account_name_));
    map_cont.insert(LOGINNAME, QString::fromLocal8Bit(msg_info->m_rtn_acc->login_name_));
    map_cont.insert(MATCHFEERATE, (double)msg_info->m_infomatch_rate);
    map_cont.insert(INFOMATCHFEE, (double)msg_info->m_infomatch);
    map_cont.insert(COMMISSIONRATE, (double)msg_info->m_tradefee_rate);
    map_cont.insert(COUNTERFEE, (double)msg_info->m_tradefee);
    map_cont.insert(SUMCOMMISSION, (double)msg_info->m_comm_all);
    m_map.insert(CMDCODE, msg_info->getCmdCode().c_str());
    m_map.insert(CONTENT, map_cont);

    QJsonDocument doc = QJsonDocument::fromVariant(QVariant(m_map));
    return QString(doc.toJson()).toUtf8().data();
}

void fromJson(xyc_communication::ReplyCommissDtlQryMsg* msg_info, const std::string& json)
{
    QJsonParseError error;
    QJsonDocument jsonDocument = QJsonDocument::fromJson(QString::fromUtf8(json.c_str()).toUtf8(), &error);
    if (error.error == QJsonParseError::NoError) {
        if (jsonDocument.isObject())
        {
            auto rsltMap = jsonDocument.toVariant().toMap();
            strncpy_s(msg_info->m_qry_login_name, rsltMap[LOGINNAME].toString().toLocal8Bit().data(), sizeof(msg_info->m_qry_login_name) - 1);
            strncpy_s(msg_info->m_start_day, rsltMap[QRYSTARTDATETIME].toString().toLocal8Bit().data(), sizeof(msg_info->m_start_day) - 1);
            strncpy_s(msg_info->m_end_day, UtilityFun::getAddDate(rsltMap[QRYENDDATETIME].toString().toLocal8Bit().data(), 1).c_str(), sizeof(msg_info->m_end_day) - 1);
        }
    }
}

std::string toJson(xyc_communication::ReplyCommissDtlQryMsgPtr msg_info)
{
    QMap<QString, QVariant> m_map;
    QMap<QString, QVariant> map_cont;

    map_cont.insert(ERRCODE, msg_info->getResult());
    map_cont.insert(BLAST, msg_info->m_blast);
    if (!msg_info->m_blast)
    {
        map_cont.insert(ACCOUNTNAME, QString::fromLocal8Bit(msg_info->m_rtn_acc->account_name_));
        map_cont.insert(LOGINNAME, QString::fromLocal8Bit(msg_info->m_rtn_acc->login_name_));
        map_cont.insert(COMMISSIONCHANGE, (double)msg_info->m_detail_ptr->change_money_);
        map_cont.insert(CHANGETIME, msg_info->m_detail_ptr->date_time_);
        map_cont.insert(CHANGETYPE, msg_info->m_detail_ptr->change_type_);
        map_cont.insert(COMMISSIONSOURCE, msg_info->m_rtn_source_acc->login_name_);
        map_cont.insert(COMMISSIONRATE, (double)msg_info->m_detail_ptr->commission_rate_);
    }

    m_map.insert(CMDCODE, msg_info->getCmdCode().c_str());
    m_map.insert(CONTENT, map_cont);

    QJsonDocument doc = QJsonDocument::fromVariant(QVariant(m_map));
    return QString(doc.toJson()).toUtf8().data();
}

void fromJson(xyc_communication::ReplyProfitCommisslQryMsg* msg_info, const std::string& json)
{
    QJsonParseError error;
    QJsonDocument jsonDocument = QJsonDocument::fromJson(QString::fromUtf8(json.c_str()).toUtf8(), &error);
    if (error.error == QJsonParseError::NoError) {
        if (jsonDocument.isObject())
        {
            auto rsltMap = jsonDocument.toVariant().toMap();
            strncpy_s(msg_info->m_qry_login_name, rsltMap[LOGINNAME].toString().toLocal8Bit().data(), sizeof(msg_info->m_qry_login_name) - 1);
            strncpy_s(msg_info->m_start_day, UtilityFun::getAddDate(rsltMap[QRYSTARTDATETIME].toString().toLocal8Bit().data(),0).c_str(), sizeof(msg_info->m_start_day) - 1);
            strncpy_s(msg_info->m_end_day, rsltMap[QRYENDDATETIME].toString().toLocal8Bit().data(), sizeof(msg_info->m_end_day) - 1);
        }
    }
}

std::string toJson(xyc_communication::ReplyProfitCommisslQryMsgPtr msg_info)
{
    QMap<QString, QVariant> m_map;
    QMap<QString, QVariant> map_cont;

    map_cont.insert(ERRCODE, msg_info->getResult());
    map_cont.insert(ACCOUNTNAME, QString::fromLocal8Bit(msg_info->m_rtn_acc->account_name_));
    map_cont.insert(LOGINNAME, QString::fromLocal8Bit(msg_info->m_rtn_acc->login_name_));
    map_cont.insert(PROCOMMRATE, (double)msg_info->m_profit_rate);
    map_cont.insert(SUMLEVELFEE, (double)msg_info->m_profit);
    m_map.insert(CMDCODE, msg_info->getCmdCode().c_str());
    m_map.insert(CONTENT, map_cont);

    QJsonDocument doc = QJsonDocument::fromVariant(QVariant(m_map));
    return QString(doc.toJson()).toUtf8().data();
}

void fromJson(xyc_communication::ReplyProfitCommissDtlQryMsg* msg_info, const std::string& json)
{
    QJsonParseError error;
    QJsonDocument jsonDocument = QJsonDocument::fromJson(QString::fromUtf8(json.c_str()).toUtf8(), &error);
    if (error.error == QJsonParseError::NoError) {
        if (jsonDocument.isObject())
        {
            auto rsltMap = jsonDocument.toVariant().toMap();
            strncpy_s(msg_info->m_qry_login_name, rsltMap[LOGINNAME].toString().toLocal8Bit().data(), sizeof(msg_info->m_qry_login_name) - 1);
            strncpy_s(msg_info->m_start_day, rsltMap[QRYSTARTDATETIME].toString().toLocal8Bit().data(), sizeof(msg_info->m_start_day) - 1);
            strncpy_s(msg_info->m_end_day, UtilityFun::getAddDate(rsltMap[QRYENDDATETIME].toString().toLocal8Bit().data(), 1).c_str(), sizeof(msg_info->m_end_day) - 1);
        }
    }
}

std::string toJson(xyc_communication::ReplyProfitCommissDtlQryMsgPtr msg_info)
{
    QMap<QString, QVariant> m_map;
    QMap<QString, QVariant> map_cont;

    map_cont.insert(ERRCODE, msg_info->getResult());
    map_cont.insert(BLAST, msg_info->m_blast);
    if (!msg_info->m_blast)
    {
        map_cont.insert(ACCOUNTNAME, QString::fromLocal8Bit(msg_info->m_rtn_acc->account_name_));
        map_cont.insert(LOGINNAME, QString::fromLocal8Bit(msg_info->m_rtn_acc->login_name_));
        map_cont.insert(PROCOMMCHANGE, (double)msg_info->m_detail_ptr->change_money_);
        map_cont.insert(CHANGETIME, msg_info->m_detail_ptr->date_time_);
        map_cont.insert(CHANGETYPE, msg_info->m_detail_ptr->change_type_);
        map_cont.insert(PROCOMMSOURCE, msg_info->m_rtn_source_acc->login_name_);
        map_cont.insert(PROCOMMRATE, (double)msg_info->m_detail_ptr->commission_rate_);
    }

    m_map.insert(CMDCODE, msg_info->getCmdCode().c_str());
    m_map.insert(CONTENT, map_cont);

    QJsonDocument doc = QJsonDocument::fromVariant(QVariant(m_map));
    return QString(doc.toJson()).toUtf8().data();
}

void fromJson(xyc_communication::ReplyRiskHistoryMsg* msg_info, const std::string& json)
{
	QJsonParseError error;
	QJsonDocument jsonDocument = QJsonDocument::fromJson(QString::fromUtf8(json.c_str()).toUtf8(), &error);
	if (error.error == QJsonParseError::NoError) {
		if (jsonDocument.isObject())
		{
			auto rsltMap = jsonDocument.toVariant().toMap();
			strncpy_s(msg_info->m_login_name, rsltMap[LOGINNAME].toString().toLocal8Bit().data(), sizeof(msg_info->m_login_name) - 1);
			strncpy_s(msg_info->m_start_day, rsltMap[QRYSTARTDATETIME].toString().toLocal8Bit().data(), sizeof(msg_info->m_start_day) - 1);
			strncpy_s(msg_info->m_end_day, UtilityFun::getAddDate(rsltMap[QRYENDDATETIME].toString().toLocal8Bit().data(), 1).c_str(), sizeof(msg_info->m_end_day) - 1);
		}
	}
}

std::string toJson(xyc_communication::ReplyRiskHistoryMsgPtr msg_info)
{
	QMap<QString, QVariant> m_map;
	QMap<QString, QVariant> map_cont;

	map_cont.insert(ERRCODE, msg_info->getResult());
	map_cont.insert(USERID, QString::fromLocal8Bit(msg_info->m_contextPtr->user_id_));
	map_cont.insert(LOGINNAME, QString::fromLocal8Bit(msg_info->m_login_name));
	map_cont.insert(ACCOUNTNAME, QString::fromLocal8Bit(msg_info->m_acc_name));
	map_cont.insert(RISKType, (int)msg_info->m_contextPtr->rc_type_);
	map_cont.insert(DATETIME, QString::fromLocal8Bit(msg_info->m_contextPtr->date_time_));
	map_cont.insert(RISKTEXT, QString::fromLocal8Bit(msg_info->m_contextPtr->trigger_text_));
	map_cont.insert(BLAST, msg_info->m_blast);
	m_map.insert(CMDCODE, msg_info->getCmdCode().c_str());
	m_map.insert(CONTENT, map_cont);

	QJsonDocument doc = QJsonDocument::fromVariant(QVariant(m_map));
	return QString(doc.toJson()).toUtf8().data();
}

void fromJson(xyc_communication::ReplyTimeWarnQryMsg* msg_info, const std::string& json)
{
	QJsonParseError error;
	QJsonDocument jsonDocument = QJsonDocument::fromJson(QString::fromUtf8(json.c_str()).toUtf8(), &error);
	if (error.error == QJsonParseError::NoError) {
		if (jsonDocument.isObject())
		{
			auto rsltMap = jsonDocument.toVariant().toMap();
			strncpy_s(msg_info->m_login_name, rsltMap[LOGINNAME].toString().toLocal8Bit().data(), sizeof(msg_info->m_login_name) - 1);
		}
	}
}


std::string toJson(xyc_communication::ReplyTimeWarnQryMsgPtr msg_info)
{
	QMap<QString, QVariant> m_map;
	QMap<QString, QVariant> map_cont;

	map_cont.insert(ERRCODE, msg_info->getResult());
	map_cont.insert(USERID, QString::fromLocal8Bit(msg_info->m_contextPtr->user_id_));
	map_cont.insert(LOGINNAME, QString::fromLocal8Bit(msg_info->m_login_name));
	map_cont.insert(ACCOUNTNAME, QString::fromLocal8Bit(msg_info->m_acc_name));
	map_cont.insert(RISKType, (int)msg_info->m_contextPtr->rc_type_);
	map_cont.insert(DATETIME, QString::fromLocal8Bit(msg_info->m_contextPtr->date_time_));
	map_cont.insert(RISKTEXT, QString::fromLocal8Bit(msg_info->m_contextPtr->trigger_text_));
	map_cont.insert(BLAST, msg_info->m_blast);
	m_map.insert(CMDCODE, msg_info->getCmdCode().c_str());
	m_map.insert(CONTENT, map_cont);

	QJsonDocument doc = QJsonDocument::fromVariant(QVariant(m_map));
	return QString(doc.toJson()).toUtf8().data();
}


void fromJson(xyc_communication::ReplySetMarginMsg* msg_info, const std::string& json)
{
	QJsonParseError error;
	QJsonDocument jsonDocument = QJsonDocument::fromJson(QString::fromUtf8(json.c_str()).toUtf8(), &error);
	if (error.error == QJsonParseError::NoError) {
		if (jsonDocument.isObject())
		{
			AllTrade::NPTradeCenter::MarginInfoPtr ptrSt_ = std::make_shared<AllTrade::NPTradeCenter::MarginInfo>();
			auto rsltMap = jsonDocument.toVariant().toMap();
			strncpy_s(msg_info->m_login_name, rsltMap[LOGINNAME].toString().toLocal8Bit().data(), sizeof(msg_info->m_login_name) - 1);

			ptrSt_->sum_Margin_Qty_ = rsltMap[SUMMARGINSET].toInt();
			ptrSt_->Interest_ = rsltMap[INTEREST].toDouble();
		}
	}

}

std::string toJson(xyc_communication::ReplySetMarginMsgPtr msg_info)
{
	QMap<QString, QVariant> m_map;
	QMap<QString, QVariant> map_cont;

	map_cont.insert(ERRCODE, msg_info->getResult());
	map_cont.insert(SUMMARGINSET, msg_info->m_margin_set_->sum_Margin_Qty_);
	map_cont.insert(INTEREST, msg_info->m_margin_set_->Interest_);
	

	QJsonDocument doc = QJsonDocument::fromVariant(QVariant(m_map));
	return QString(doc.toJson()).toUtf8().data();
}

void fromJson(xyc_communication::ReplyMarginLeftQtyMsg* msg_info, const std::string& json)
{
	QJsonParseError error;
	QJsonDocument jsonDocument = QJsonDocument::fromJson(QString::fromUtf8(json.c_str()).toUtf8(), &error);
	if (error.error == QJsonParseError::NoError) {
		if (jsonDocument.isObject())
		{
			AllTrade::NPTradeCenter::MarginLeftInfoPtr ptrSt_ = std::make_shared<AllTrade::NPTradeCenter::MarginLeftInfo>();
			auto rsltMap = jsonDocument.toVariant().toMap();
			strncpy_s(msg_info->m_login_name, rsltMap[LOGINNAME].toString().toLocal8Bit().data(), sizeof(msg_info->m_login_name) - 1);

			strncpy_s(ptrSt_->contract_id_, rsltMap[STOCKCODE].toString().toLocal8Bit().data(), sizeof(ptrSt_->contract_id_) - 1);
			// ptrSt_->Interest_ = rsltMap[LEFTMARGINSET].toInt();
		}
	}
}

std::string toJson(xyc_communication::ReplyMarginLeftQtyMsgPtr msg_info)
{
	QMap<QString, QVariant> m_map;
	QMap<QString, QVariant> map_cont;

	map_cont.insert(ERRCODE, msg_info->getResult());
	map_cont.insert(STOCKCODE, msg_info->m_margin_left_->contract_id_);
	map_cont.insert(LEFTMARGINSET, msg_info->m_margin_left_->left_Margin_Qty_);


	QJsonDocument doc = QJsonDocument::fromVariant(QVariant(m_map));
	return QString(doc.toJson()).toUtf8().data();
}

/////////////////// 融券管理查询请求 //////////////////////////////
void fromJson(xyc_communication::ReplyMarginManagerQtyMsg* msg_info, const std::string& json)
{
	QJsonParseError error;
	QJsonDocument jsonDocument = QJsonDocument::fromJson(QString::fromUtf8(json.c_str()).toUtf8(), &error);
	if (error.error == QJsonParseError::NoError) {
		if (jsonDocument.isObject())
		{
			AllTrade::NPTradeCenter::MarginLeftInfoPtr ptrSt_ = std::make_shared<AllTrade::NPTradeCenter::MarginLeftInfo>();
			auto rsltMap = jsonDocument.toVariant().toMap();
			strncpy_s(msg_info->m_login_name, rsltMap[LOGINNAME].toString().toLocal8Bit().data(), sizeof(msg_info->m_login_name) - 1);

			// strncpy_s(ptrSt_->contract_id_, rsltMap[STOCKCODE].toString().toLocal8Bit().data(), sizeof(ptrSt_->contract_id_) - 1);
			// ptrSt_->Interest_ = rsltMap[LEFTMARGINSET].toInt();
		}
	}
}


std::string toJson(xyc_communication::ReplyMarginManagerQtyMsgPtr msg_info)
{
	QMap<QString, QVariant> m_map;
	QMap<QString, QVariant> map_cont;

	map_cont.insert(ERRCODE, msg_info->getResult());
	map_cont.insert(SUMMARGINSET, msg_info->m_margin_set_->sum_Margin_Qty_);
	map_cont.insert(INTEREST, msg_info->m_margin_set_->Interest_);

	QJsonDocument doc = QJsonDocument::fromVariant(QVariant(m_map));
	return QString(doc.toJson()).toUtf8().data();
}

/////////////////// 融券负债查询请求 //////////////////////////////
void fromJson(xyc_communication::ReplyMarginLiabilitiesQtyMsg* msg_info, const std::string& json)
{
	QJsonParseError error;
	QJsonDocument jsonDocument = QJsonDocument::fromJson(QString::fromUtf8(json.c_str()).toUtf8(), &error);
	if (error.error == QJsonParseError::NoError) {
		if (jsonDocument.isObject())
		{
			AllTrade::NPTradeCenter::MarginLeftInfoPtr ptrSt_ = std::make_shared<AllTrade::NPTradeCenter::MarginLeftInfo>();
			auto rsltMap = jsonDocument.toVariant().toMap();
			strncpy_s(msg_info->m_login_name, rsltMap[LOGINNAME].toString().toLocal8Bit().data(), sizeof(msg_info->m_login_name) - 1);

		}
	}
}


std::string toJson(xyc_communication::ReplyMarginLiabilitiesQtyMsgPtr msg_info)
{
	QMap<QString, QVariant> m_map;
	QMap<QString, QVariant> map_cont;

	///////// 尚未处理 //////////

	QJsonDocument doc = QJsonDocument::fromVariant(QVariant(m_map));
	return QString(doc.toJson()).toUtf8().data();
}

/////////////////// 融券负债查询请求 //////////////////////////////
void fromJson(xyc_communication::ReplyInterestStatisticsMsg* msg_info, const std::string& json)
{
	QJsonParseError error;
	QJsonDocument jsonDocument = QJsonDocument::fromJson(QString::fromUtf8(json.c_str()).toUtf8(), &error);
	if (error.error == QJsonParseError::NoError) {
		if (jsonDocument.isObject())
		{
			AllTrade::NPMgrCenter::InterestStatisticsPtr ptrSt_ = std::make_shared<AllTrade::NPMgrCenter::InterestStatistics>();
			auto rsltMap = jsonDocument.toVariant().toMap();
			strncpy_s(msg_info->m_login_name, rsltMap[LOGINNAME].toString().toLocal8Bit().data(), sizeof(msg_info->m_login_name) - 1);

		}
	}
}



std::string toJson(xyc_communication::ReplyInterestStatisticsMsgPtr msg_info)
{
	QMap<QString, QVariant> m_map;
	QMap<QString, QVariant> map_cont;

	map_cont.insert(ERRCODE, msg_info->getResult());
	map_cont.insert(USERID, msg_info->m_ptr_->user_id_);
	map_cont.insert(SUMINTEREST, (double)msg_info->m_ptr_->sum_interest_);

	QJsonDocument doc = QJsonDocument::fromVariant(QVariant(m_map));
	return QString(doc.toJson()).toUtf8().data();
}

/////////////////// 利息明细查询请求 //////////////////////////////
void fromJson(xyc_communication::ReplyInterestDetailMsg* msg_info, const std::string& json)
{
	QJsonParseError error;
	QJsonDocument jsonDocument = QJsonDocument::fromJson(QString::fromUtf8(json.c_str()).toUtf8(), &error);
	if (error.error == QJsonParseError::NoError) {
		if (jsonDocument.isObject())
		{
			AllTrade::NPMgrCenter::InterestDetailPtr ptrSt_ = std::make_shared<AllTrade::NPMgrCenter::InterestDetail>();
			auto rsltMap = jsonDocument.toVariant().toMap();
			strncpy_s(msg_info->m_login_name, rsltMap[LOGINNAME].toString().toLocal8Bit().data(), sizeof(msg_info->m_login_name) - 1);

		}
	}
}

std::string toJson(xyc_communication::ReplyInterestDetailMsgPtr msg_info)
{
	QMap<QString, QVariant> m_map;
	QMap<QString, QVariant> map_cont;

	map_cont.insert(ERRCODE, msg_info->getResult());
	map_cont.insert(BLAST, msg_info->m_blast);
	if (!msg_info->m_blast)
	{
		map_cont.insert(LOGINNAME, QString::fromLocal8Bit(msg_info->m_login_name));
		map_cont.insert(ACCOUNTNAME, QString::fromLocal8Bit(msg_info->m_acount_name));
		map_cont.insert(SUMINTEREST, msg_info->m_ptr_->sum_interest_);
		map_cont.insert(CHANGETYPE, msg_info->m_ptr_->change_type_);

		map_cont.insert(INTERESTSOURCE, QString::fromLocal8Bit(msg_info->m_ptr_->source_user_id_));
		map_cont.insert(INTEREST, (double)msg_info->m_ptr_->interest_rate_);
	
	}

	m_map.insert(CMDCODE, msg_info->getCmdCode().c_str());
	m_map.insert(CONTENT, map_cont);

	QJsonDocument doc = QJsonDocument::fromVariant(QVariant(m_map));
	return QString(doc.toJson()).toUtf8().data();

}

/////////////////// 融券当前委托查询请求 //////////////////////////////
void fromJson(xyc_communication::ReplyCurrentMarginEntrustMsg* msg_info, const std::string& json)
{
	QJsonParseError error;
	QJsonDocument jsonDocument = QJsonDocument::fromJson(QString::fromUtf8(json.c_str()).toUtf8(), &error);
	if (error.error == QJsonParseError::NoError) {
		if (jsonDocument.isObject())
		{
			auto rsltMap = jsonDocument.toVariant().toMap();
			strncpy_s(msg_info->m_rtn_acc->login_name_, rsltMap[LOGINNAME].toString().toLocal8Bit().data(), sizeof(msg_info->m_rtn_acc->login_name_) - 1);
		}
	}
}


std::string toJson(xyc_communication::ReplyCurrentMarginEntrustMsgPtr msg_info)
{
	QMap<QString, QVariant> m_map;
	QMap<QString, QVariant> map_cont;

	map_cont.insert(ERRCODE, msg_info->getResult());
	map_cont.insert(BLAST, msg_info->m_blast);
	if (!msg_info->m_blast)
	{
		map_cont.insert(ACCOUNTNAME, QString::fromLocal8Bit(msg_info->m_rtn_acc->account_name_));
		map_cont.insert(LOGINNAME, QString::fromLocal8Bit(msg_info->m_rtn_acc->login_name_));
		map_cont.insert(STOCKCODE, msg_info->m_stock_ptr->contract_code_);
		map_cont.insert(STOCKNAME, QString::fromLocal8Bit(msg_info->m_stock_ptr->contract_name_));
		map_cont.insert(ORDERPICE, (double)msg_info->m_order_ptr->order_price_);
		map_cont.insert(ORDERVOLUME, msg_info->m_order_ptr->order_vol_);
		map_cont.insert(DEALQTY, msg_info->m_order_ptr->effected_vol_);
		map_cont.insert(ORDERSTATUS, (int)msg_info->m_order_ptr->order_state_);
		map_cont.insert(ORDERREF, msg_info->m_order_ptr->order_localtmp_ref_);
		map_cont.insert(ORDERID, msg_info->m_order_ptr->shadow_order_id_);
		map_cont.insert(ORDERTYPE, (int)msg_info->m_order_ptr->order_type_);
		map_cont.insert(ORDERMODE, (int)msg_info->m_order_ptr->order_mode_);
		map_cont.insert(ORDERDERECTION, (int)msg_info->m_order_ptr->direct_type_);
		map_cont.insert(CURRENCYRATE, (double)msg_info->m_order_ptr->currency_rate_);
		map_cont.insert(UPPERMANAGER, QString::fromLocal8Bit(msg_info->m_parent_login_name));
		map_cont.insert(COMMITIME, msg_info->m_order_ptr->generate_datetime_);
		map_cont.insert(CHANGETIME, msg_info->m_order_ptr->update_datetime_);
		map_cont.insert(ORDERSTREAM, msg_info->m_order_ptr->order_stream_);
		if (msg_info->m_order_ptr->order_state_ == OrderStateType::ORDER_STATE_DELETED)
			map_cont.insert(CANCELORDERNUMBER, msg_info->m_order_ptr->order_vol_ - msg_info->m_order_ptr->effected_vol_);
		else
			map_cont.insert(CANCELORDERNUMBER, 0);
		map_cont.insert(FROZENFUND, (double)msg_info->m_order_ptr->freeze_money_);
	}

	m_map.insert(CMDCODE, msg_info->getCmdCode().c_str());
	m_map.insert(CONTENT, map_cont);

	QJsonDocument doc = QJsonDocument::fromVariant(QVariant(m_map));
	return QString(doc.toJson()).toUtf8().data();
}

/////////////////// 融券当前成交查询请求 //////////////////////////////
void fromJson(xyc_communication::ReplyCurrentMarginTradeQryMsg* msg_info, const std::string& json)
{
	QJsonParseError error;
	QJsonDocument jsonDocument = QJsonDocument::fromJson(QString::fromUtf8(json.c_str()).toUtf8(), &error);
	if (error.error == QJsonParseError::NoError) {
		if (jsonDocument.isObject())
		{
			auto rsltMap = jsonDocument.toVariant().toMap();
			strncpy_s(msg_info->m_rtn_acc->login_name_, rsltMap[LOGINNAME].toString().toLocal8Bit().data(), sizeof(msg_info->m_rtn_acc->login_name_) - 1);
		}
	}
}
std::string toJson(xyc_communication::ReplyCurrentMarginTradeQryMsgPtr msg_info)
{
	QMap<QString, QVariant> m_map;
	QMap<QString, QVariant> map_cont;

	map_cont.insert(ERRCODE, msg_info->getResult());
	map_cont.insert(BLAST, msg_info->m_blast);
	if (!msg_info->m_blast)
	{
		map_cont.insert(ACCOUNTNAME, QString::fromLocal8Bit(msg_info->m_rtn_acc->account_name_));
		map_cont.insert(LOGINNAME, QString::fromLocal8Bit(msg_info->m_rtn_acc->login_name_));
		map_cont.insert(CURRENCYRATE, (double)msg_info->m_trade_ptr->currency_rate_);
		map_cont.insert(DEALNO, msg_info->m_trade_ptr->shadow_trade_id_);
		map_cont.insert(STOCKCODE, msg_info->m_stock_ptr->contract_code_);
		map_cont.insert(STOCKNAME, QString::fromLocal8Bit(msg_info->m_stock_ptr->contract_name_));
		map_cont.insert(TRADEDIR, (int)msg_info->m_trade_ptr->direct_type_);
		map_cont.insert(DEALQTY, msg_info->m_trade_ptr->volume_);
		map_cont.insert(DEALAVGPRICE, (double)msg_info->m_trade_ptr->trade_price_);
		map_cont.insert(COMMISSION, (double)msg_info->m_trade_ptr->trade_fee_);
		map_cont.insert(STAMPFEE, (double)msg_info->m_trade_ptr->stamp_fee_);
		map_cont.insert(TRANSFERFEE, (double)msg_info->m_trade_ptr->transfer_fee_);
		map_cont.insert(INFOMATCHFEE, (double)msg_info->m_trade_ptr->infomatch_fee_);
		map_cont.insert(UPPERMANAGER, QString::fromLocal8Bit(msg_info->m_parent_login_name));
		map_cont.insert(DEALTIME, msg_info->m_trade_ptr->generate_datetime_);
	}

	m_map.insert(CMDCODE, msg_info->getCmdCode().c_str());
	m_map.insert(CONTENT, map_cont);

	QJsonDocument doc = QJsonDocument::fromVariant(QVariant(m_map));
	return QString(doc.toJson()).toUtf8().data();
}

