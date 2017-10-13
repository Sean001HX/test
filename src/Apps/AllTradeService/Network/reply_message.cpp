#include <assert.h>
#include <codecvt>
#include <sstream>
#include "reply_message.h"
#include "define/CommMsgDefine.h"
#include "define/net_illustrate.h"
#include "NetInfo/RequestMsgDefine.h"
#include "include/ManagerCenter/ManagerCenter.h"
#include "define/communition_struct_serialize.h"
#include "define/struct_extern.h"
#include "TCPImpl.h"

using namespace AllTrade;
using namespace AllTrade::NPMgrCenter;
using namespace AllTrade::NPTradeCenter;

namespace xyc_communication{

    //////////////////////////////////////////////////////////////////////////
    // ReplyMsg class 
    ReplyMsg::ReplyMsg()
        : result_(Err_Succeed)
        , request_()
    {
    }

    ReplyMsg::ReplyMsg(RequestPtr req)
        : result_(Err_Succeed)
        , request_(req)
    {
    }

    ReplyMsg::ReplyMsg(AllTrade::ErrorCodeType rslt, int socketID, const std::string& command)
        : result_(rslt)
    {
        request_ = std::make_shared<Request>();
        request_->socketDescriptor_ = socketID;
        request_->command_ = command;
    }

    ReplyMsg::ReplyMsg(RequestPtr req, AllTrade::ErrorCodeType rslt)
        : result_(rslt)
        , request_(req)
    {
    }

    ReplyMsg::~ReplyMsg()
    {
        try
        {
            if (request_ && request_.unique())
                request_.reset();
        }
        catch (...) {}
    }

    std::string ReplyMsg::to_string()
    {
        return toJson(getResult(), getCmdCode());
    }

    void ReplyMsg::setResult(AllTrade::ErrorCodeType result)
    {
        result_ = result;
    }

    void ReplyMsg::setRequest(RequestPtr preq)
    {
        assert(preq);
        request_ = preq;
    }

    int ReplyMsg::getSocketID() const
    {
        return request_->socketDescriptor_;
    }

    TCPImpl* ReplyMsg::getTCPImpl() const
    {
        return request_->session_ptr_;
    }

    AllTrade::PLoginNameType ReplyMsg::getLoginName() const
    {
        return request_->login_name_;
    }

    //////////////////////////////////////////////////////////////////////////
    // ReplyLoginMsg class 
    ReplyLoginMsg::ReplyLoginMsg()
        : ReplyMsg()
    {
    }

    ReplyLoginMsg::ReplyLoginMsg(RequestPtr req)
        : ReplyMsg(req)
        , m_rtn_acc(nullptr)
    {
        memset(m_parent_login_name, 0, sizeof(m_parent_login_name));
		req->command_ = gszMsgCommandCode[E_COMM_MSG_TYPE::LOGIN_TRADE_RSP];
		m_login_info = std::make_shared<SOnlineAccount>();
        m_login_info->session_id_ = req->socketDescriptor_;

        fromJson(this, req->parameters_);
        req->session_ptr_->setLoginName(req->socketDescriptor_, m_login_name);
        result_ = IManagerCenter::instance()->canLogin(m_login_name, m_password);
        if (result_ == Err_Succeed)
        {
            m_rtn_acc = IManagerCenter::instance()->getAccountByLoginName(m_login_name);
            if (m_rtn_acc->prop_ == EAP_Manager)
            {
                SAccountPtr parent_acc = IManagerCenter::instance()->getAccountByID(m_rtn_acc->parent_id_);
                strncpy_s(m_parent_login_name, parent_acc->login_name_, sizeof(m_parent_login_name) - 1);
            }
        }
    }

    std::string ReplyLoginMsg::to_string()
    {
        return toJson(shared_from_this());
    }

    //////////////////////////////////////////////////////////////////////////
    ReplyAgencyQryMsg::ReplyAgencyQryMsg()
        : ReplyMsg()
    {

    }

    ReplyAgencyQryMsg::ReplyAgencyQryMsg(RequestPtr req)
        : ReplyMsg(req)
        , m_blast(false)
    {
        memset(m_fund_login_name, 0, sizeof(m_fund_login_name));
        req->command_ = gszMsgCommandCode[E_COMM_MSG_TYPE::INSTITUTION_RSP];
//         fromJson(this, req->parameters_);
    }

    std::string ReplyAgencyQryMsg::to_string()
    {
        return toJson(shared_from_this());
    }

    //////////////////////////////////////////////////////////////////////////
    ReplyAgencyPreApprovalQryMsg::ReplyAgencyPreApprovalQryMsg()
        : ReplyMsg()
    {

    }

    ReplyAgencyPreApprovalQryMsg::ReplyAgencyPreApprovalQryMsg(RequestPtr req)
        : ReplyMsg(req)
        , m_blast(false)
    {
        memset(m_fund_login_name, 0, sizeof(m_fund_login_name));
        req->command_ = gszMsgCommandCode[E_COMM_MSG_TYPE::INSTITUTION_PREAPPROVAL_RSP];
//         fromJson(this, req->parameters_);
    }

    std::string ReplyAgencyPreApprovalQryMsg::to_string()
    {
        return toJson(shared_from_this());
    }

	//////////////////////////////////////////////////////////////////////////
	ReplyRolesQryMsg::ReplyRolesQryMsg()
		: ReplyMsg()
		, m_blast(false)
	{

	}

	ReplyRolesQryMsg::ReplyRolesQryMsg(RequestPtr req)
        : ReplyMsg(req)
        , m_blast(false)
    {
		req->command_ = gszMsgCommandCode[E_COMM_MSG_TYPE::ROLES_QUERY_RSP];
        m_rtn_arp = std::make_shared<AuthorityRoles>();
//         strncpy_s(m_qryLoginName, req->login_name_.c_str(), sizeof(m_qryLoginName) - 1);
//         fromJson(this, req->parameters_);
	}

	std::string ReplyRolesQryMsg::to_string()
	{
		return toJson(shared_from_this());
	}


	///////////////////////////////////////
	ReplyAgencyRolesQryMsg::ReplyAgencyRolesQryMsg()
		: ReplyMsg()
	{

	}
    
	ReplyAgencyRolesQryMsg::ReplyAgencyRolesQryMsg(RequestPtr req)
        : ReplyMsg(req)
        , m_blast(false)
	{
		req->command_ = gszMsgCommandCode[E_COMM_MSG_TYPE::INSTITUTIONUSER_ROLE_RELATION_RSP];
//         strncpy_s(m_LoginName, req->login_name_.c_str(), sizeof(m_LoginName) - 1);
        m_rtn_arp = std::make_shared<AuthorityRoleUsers>();
		
// 		fromJson(this, req->parameters_);
	}

	std::string ReplyAgencyRolesQryMsg::to_string()
	{
		return toJson(shared_from_this());
	}

    //////////////////////////////////////////////////////////////////////////
    ReplyCommissQryMsg::ReplyCommissQryMsg()
        : ReplyMsg()
    {

    }

    ReplyCommissQryMsg::ReplyCommissQryMsg(RequestPtr req)
        : ReplyMsg(req)
        , m_infomatch_rate(0)
        , m_infomatch(0)
        , m_tradefee_rate(0)
        , m_tradefee(0)
        , m_comm_all(0)
    {
        req->command_ = gszMsgCommandCode[E_COMM_MSG_TYPE::COMMISSION_QUERY_RSP];
        fromJson(this, req->parameters_);
    }

    std::string ReplyCommissQryMsg::to_string()
    {
        return toJson(shared_from_this());
    }

    //////////////////////////////////////////////////////////////////////////
    ReplyCommissDtlQryMsg::ReplyCommissDtlQryMsg()
        : ReplyMsg()
        , m_blast(false)
    {

    }

    ReplyCommissDtlQryMsg::ReplyCommissDtlQryMsg(RequestPtr req)
        : ReplyMsg(req)
        , m_blast(false)
        , m_rtn_acc(nullptr)
    {
        req->command_ = gszMsgCommandCode[E_COMM_MSG_TYPE::COMMISSION_DETAIL_RSP];
        m_detail_ptr = std::make_shared<SAgencyMoneyDetailInfo>();
        fromJson(this, req->parameters_);
    }

    std::string ReplyCommissDtlQryMsg::to_string()
    {
        return toJson(shared_from_this());
    }

    //////////////////////////////////////////////////////////////////////////
    ReplyProfitCommisslQryMsg::ReplyProfitCommisslQryMsg()
        : ReplyMsg()
    {

    }

    ReplyProfitCommisslQryMsg::ReplyProfitCommisslQryMsg(RequestPtr req)
        : ReplyMsg(req)
        , m_profit_rate(0)
        , m_profit(0)
    {
        req->command_ = gszMsgCommandCode[E_COMM_MSG_TYPE::PROFITCOMMISSION_QUERY_RSP];
        fromJson(this, req->parameters_);
    }

    std::string ReplyProfitCommisslQryMsg::to_string()
    {
        return toJson(shared_from_this());
    }

    //////////////////////////////////////////////////////////////////////////
    ReplyProfitCommissDtlQryMsg::ReplyProfitCommissDtlQryMsg()
        : ReplyMsg()
        , m_blast(false)
    {

    }

    ReplyProfitCommissDtlQryMsg::ReplyProfitCommissDtlQryMsg(RequestPtr req)
        : ReplyMsg(req)
        , m_blast(false)
        , m_rtn_acc(nullptr)
    {
        req->command_ = gszMsgCommandCode[E_COMM_MSG_TYPE::PROFITCOMMISSION_DETAIL_RSP];
        m_detail_ptr = std::make_shared<SAgencyMoneyDetailInfo>();
        fromJson(this, req->parameters_);
    }

    std::string ReplyProfitCommissDtlQryMsg::to_string()
    {
        return toJson(shared_from_this());
    }

    //////////////////////////////////////////////////////////////////////////
    ReplyChildAccQryMsg::ReplyChildAccQryMsg()
        : ReplyMsg()
    {

    }

    ReplyChildAccQryMsg::ReplyChildAccQryMsg(RequestPtr req)
        : ReplyMsg(req)
        , m_blast(false)
    {
        req->command_ = gszMsgCommandCode[E_COMM_MSG_TYPE::CHILD_QUERY_RSP];
        memset(m_rtn_fund_login_name, 0, sizeof(m_rtn_fund_login_name));
//         strncpy_s(m_qryLoginName, req->login_name_.c_str(), sizeof(m_qryLoginName) - 1);
        m_rtn_acc = std::make_shared<TradeAccount>();
        m_rtn_money = std::make_shared<SMoneyInfo>();
        m_rtn_risk = std::make_shared<SRiskInfo>();
//         fromJson(this, req->parameters_);
    }

    std::string ReplyChildAccQryMsg::to_string()
    {
        return toJson(shared_from_this());
    }

    //////////////////////////////////////////////////////////////////////////
    ReplyChildApprovalQryMsg::ReplyChildApprovalQryMsg()
        : ReplyMsg()
    {

    }

    ReplyChildApprovalQryMsg::ReplyChildApprovalQryMsg(RequestPtr req)
        : ReplyMsg(req)
        , m_blast(false)
    {
        req->command_ = gszMsgCommandCode[E_COMM_MSG_TYPE::CHILD_APPROVAL_RSP];
        memset(m_rtn_fund_login_name, 0, sizeof(m_rtn_fund_login_name));
//         strncpy_s(m_qryLoginName, req->login_name_.c_str(), sizeof(m_qryLoginName) - 1);
        m_rtn_acc = std::make_shared<TradeAccount>();
        m_rtn_money = std::make_shared<SMoneyInfo>();
        m_rtn_risk = std::make_shared<SRiskInfo>();
//         fromJson(this, req->parameters_);
    }

    std::string ReplyChildApprovalQryMsg::to_string()
    {
        return toJson(shared_from_this());
    }

    //////////////////////////////////////////////////////////////////////////
    ReplyFundAccQryMsg::ReplyFundAccQryMsg()
        : ReplyMsg()
    {

    }

    ReplyFundAccQryMsg::ReplyFundAccQryMsg(RequestPtr req)
        : ReplyMsg(req)
        , m_blast(false)
    {
        req->command_ = gszMsgCommandCode[E_COMM_MSG_TYPE::FUNDACC_QUERY_RSP];
//         strncpy_s(m_qryLoginName, req->login_name_.c_str(), sizeof(m_qryLoginName) - 1);
        m_rtn_acc = std::make_shared<FunderAccount>();
        m_rtn_money = std::make_shared<SMoneyInfo>();
//         fromJson(this, req->parameters_);
    }

    std::string ReplyFundAccQryMsg::to_string()
    {
        return toJson(shared_from_this());
    }

    //////////////////////////////////////////////////////////////////////////
    ReplyOnlineAccQryMsg::ReplyOnlineAccQryMsg()
    {

    }

    ReplyOnlineAccQryMsg::ReplyOnlineAccQryMsg(RequestPtr req)
        : ReplyMsg(req)
        , m_blast(false)
    {
        req->command_ = gszMsgCommandCode[E_COMM_MSG_TYPE::ONLINE_USER_RSP];
//         strncpy_s(m_LoginName, req->login_name_.c_str(), sizeof(m_LoginName) - 1);
    }

    std::string ReplyOnlineAccQryMsg::to_string()
    {
        return toJson(shared_from_this());
    }

    //////////////////////////////////////////////////////////////////////////
    ReplyStockContractQryMsg::ReplyStockContractQryMsg()
        : ReplyMsg()
    {

    }

    ReplyStockContractQryMsg::ReplyStockContractQryMsg(RequestPtr req)
        : ReplyMsg(req)
        , m_blast(false)
    {
        req->command_ = gszMsgCommandCode[E_COMM_MSG_TYPE::STOCK_CONTRACT_QUERY_RSP];
        m_stock_ptr = std::make_shared<SStockContract>();
        fromJson(this, req->parameters_);
    }

    std::string ReplyStockContractQryMsg::to_string()
    {
        return toJson(shared_from_this());
    }

    //////////////////////////////////////////////////////////////////////////
    ReplyStockBlackQryMsg::ReplyStockBlackQryMsg()
        : ReplyMsg()
    {

    }

    ReplyStockBlackQryMsg::ReplyStockBlackQryMsg(RequestPtr req)
        : ReplyMsg(req)
        , m_blast(false)
    {
        req->command_ = gszMsgCommandCode[E_COMM_MSG_TYPE::STOCK_INSTRUMENT_QUERY_RSP];
    }

    std::string ReplyStockBlackQryMsg::to_string()
    {
        return toJson(shared_from_this());
    }

    //////////////////////////////////////////////////////////////////////////
    ReplyForbidBuySellQryMsg::ReplyForbidBuySellQryMsg()
        : ReplyMsg()
    {

    }

    ReplyForbidBuySellQryMsg::ReplyForbidBuySellQryMsg(RequestPtr req)
        : ReplyMsg(req)
        , m_blast(false)
    {
        forbid_trade = std::make_shared<SForbidTradeInfo>();
        req->command_ = gszMsgCommandCode[E_COMM_MSG_TYPE::FORBID_BUY_SELL_QUERY_RSP];
    }

    std::string ReplyForbidBuySellQryMsg::to_string()
    {
        return toJson(shared_from_this());
    }

    //////////////////////////////////////////////////////////////////////////
    ReplyPosiRateQryMsg::ReplyPosiRateQryMsg()
        : ReplyMsg()
    {

    }

    ReplyPosiRateQryMsg::ReplyPosiRateQryMsg(RequestPtr req)
        : ReplyMsg(req)
        , m_blast(false)
    {
        posit_rate = std::make_shared<SPositionRateInfo>();
        req->command_ = gszMsgCommandCode[E_COMM_MSG_TYPE::POSI_RATE_QUERY_RSP];
    }

    std::string ReplyPosiRateQryMsg::to_string()
    {
        return toJson(shared_from_this());
    }

    //////////////////////////////////////////////////////////////////////////
    ReplyPosiQryMsg::ReplyPosiQryMsg()
        : ReplyMsg()
    {

    }

    ReplyPosiQryMsg::ReplyPosiQryMsg(RequestPtr req)
        : ReplyMsg(req)
        , m_blast(false)
    {
        req->command_ = gszMsgCommandCode[E_COMM_MSG_TYPE::POSI_QUERY_RSP];
        m_position_ptr = std::make_shared<StockPositionInfo>();
        m_stock_ptr = std::make_shared<SStockContract>();
        m_rtn_acc = std::make_shared<TradeAccount>();
        fromJson(this, req->parameters_);
    }

    std::string ReplyPosiQryMsg::to_string()
    {
        return toJson(shared_from_this());
    }

    //////////////////////////////////////////////////////////////////////////
    ReplyCurrentyEntrustQryMsg::ReplyCurrentyEntrustQryMsg()
        : ReplyMsg()
    {

    }

    ReplyCurrentyEntrustQryMsg::ReplyCurrentyEntrustQryMsg(RequestPtr req)
        : ReplyMsg(req)
        , m_blast(false)
    {
        req->command_ = gszMsgCommandCode[E_COMM_MSG_TYPE::CURRENTENTRUST_QUERY_RSP];
        m_order_ptr = std::make_shared<StockOrderInfo>();
        m_stock_ptr = std::make_shared<SStockContract>();
        m_rtn_acc = std::make_shared<TradeAccount>();
        fromJson(this, req->parameters_);
    }

    std::string ReplyCurrentyEntrustQryMsg::to_string()
    {
        return toJson(shared_from_this());
    }

    //////////////////////////////////////////////////////////////////////////
    ReplyTodayEntrustQryMsg::ReplyTodayEntrustQryMsg()
        : ReplyMsg()
    {

    }

    ReplyTodayEntrustQryMsg::ReplyTodayEntrustQryMsg(RequestPtr req)
        : ReplyMsg(req)
        , m_blast(false)
    {
        req->command_ = gszMsgCommandCode[E_COMM_MSG_TYPE::TODAYENTRUST_QUERY_RSP];
        m_order_ptr = std::make_shared<StockOrderInfo>();
        m_stock_ptr = std::make_shared<SStockContract>();
        m_rtn_acc = std::make_shared<TradeAccount>();
        fromJson(this, req->parameters_);
    }

    std::string ReplyTodayEntrustQryMsg::to_string()
    {
        return toJson(shared_from_this());
    }

    //////////////////////////////////////////////////////////////////////////
    ReplyHistoryEntrustQryMsg::ReplyHistoryEntrustQryMsg()
        : ReplyMsg()
    {

    }

    ReplyHistoryEntrustQryMsg::ReplyHistoryEntrustQryMsg(RequestPtr req)
        : ReplyMsg(req)
        , m_blast(false)
    {
        req->command_ = gszMsgCommandCode[E_COMM_MSG_TYPE::HISTORYENTRUST_QUERY_RSP];
        m_order_ptr = std::make_shared<StockOrderInfo>();
        m_stock_ptr = std::make_shared<SStockContract>();
        m_rtn_acc = std::make_shared<TradeAccount>();
        fromJson(this, req->parameters_);
    }

    std::string ReplyHistoryEntrustQryMsg::to_string()
    {
        return toJson(shared_from_this());
    }

    //////////////////////////////////////////////////////////////////////////
    ReplyTradeQryMsg::ReplyTradeQryMsg()
        : ReplyMsg()
    {

    }

    ReplyTradeQryMsg::ReplyTradeQryMsg(RequestPtr req)
        : ReplyMsg(req)
        , m_blast(false)
    {
        req->command_ = gszMsgCommandCode[E_COMM_MSG_TYPE::TRADE_QUERY_RSP];
        m_trade_ptr = std::make_shared<StockTradeInfo>();
        m_stock_ptr = std::make_shared<SStockContract>();
        m_rtn_acc = std::make_shared<TradeAccount>();
        fromJson(this, req->parameters_);
    }

    std::string ReplyTradeQryMsg::to_string()
    {
        return toJson(shared_from_this());
    }

    //////////////////////////////////////////////////////////////////////////
    ReplyHistoryTradeQryMsg::ReplyHistoryTradeQryMsg()
        : ReplyMsg()
    {

    }

    ReplyHistoryTradeQryMsg::ReplyHistoryTradeQryMsg(RequestPtr req)
        : ReplyMsg(req)
        , m_blast(false)
    {
        req->command_ = gszMsgCommandCode[E_COMM_MSG_TYPE::HISTORYTRADE_QUERY_RSP];
        m_trade_ptr = std::make_shared<StockTradeInfo>();
        m_stock_ptr = std::make_shared<SStockContract>();
        m_rtn_acc = std::make_shared<TradeAccount>();
        fromJson(this, req->parameters_);
    }

    std::string ReplyHistoryTradeQryMsg::to_string()
    {
        return toJson(shared_from_this());
    }

    //////////////////////////////////////////////////////////////////////////
    ReplyFundQryMsg::ReplyFundQryMsg()
        : ReplyMsg()
    {

    }

    ReplyFundQryMsg::ReplyFundQryMsg(RequestPtr req)
        : ReplyMsg(req)
    {
        m_rtn_money = std::make_shared<SMoneyInfo>();
        m_rtn_acc = std::make_shared<TradeAccount>();
        req->command_ = gszMsgCommandCode[E_COMM_MSG_TYPE::FUND_QUERY_RSP];
        fromJson(this, req->parameters_);
    }

    std::string ReplyFundQryMsg::to_string()
    {
        return toJson(shared_from_this());
    }

    //////////////////////////////////////////////////////////////////////////
    ReplyFundSerialQryMsg::ReplyFundSerialQryMsg()
        : ReplyMsg()
        , m_blast(false)
    {

    }

    ReplyFundSerialQryMsg::ReplyFundSerialQryMsg(RequestPtr req)
        : ReplyMsg(req)
        , m_blast(false)
    {
        m_rtn_money = std::make_shared<SMoneyDetailInfo>();
        m_rtn_acc = std::make_shared<TradeAccount>();
        req->command_ = gszMsgCommandCode[E_COMM_MSG_TYPE::FUND_SERIAL_QUERY_RSP];
        fromJson(this, req->parameters_);
    }

    std::string ReplyFundSerialQryMsg::to_string()
    {
        return toJson(shared_from_this());
    }

	//////////////////////////////////////////////////////////////////////////
	ReplyTimeWarnQryMsg::ReplyTimeWarnQryMsg()
		: ReplyMsg()
	{

	}

	ReplyTimeWarnQryMsg::ReplyTimeWarnQryMsg(RequestPtr req)
		: ReplyMsg(req)
		, m_blast(false)
	{
		req->command_ = gszMsgCommandCode[E_COMM_MSG_TYPE::CHILD_TIMEWARN_NOTIFY_QUERY_RSP];
		m_contextPtr = std::make_shared<ImmRiskControlSt>();
		fromJson(this, req->parameters_);
	}

	std::string ReplyTimeWarnQryMsg::to_string()
	{
		return toJson(shared_from_this());
	}

    //////////////////////////////////////////////////////////////////////////
    ReplyEquipmentMoneyQryMsg::ReplyEquipmentMoneyQryMsg()
        : ReplyMsg()
    {

		
    }

    ReplyEquipmentMoneyQryMsg::ReplyEquipmentMoneyQryMsg(RequestPtr req)
        : ReplyMsg(req)
        , m_blast(false)
    {
        req->command_ = gszMsgCommandCode[E_COMM_MSG_TYPE::CHILD_EQUIPMENTMONEY_QUERY_RSP];
        m_rtn_acc = std::make_shared<TradeAccount>();
        m_money = std::make_shared<SApplyMoneyInfo>();
        fromJson(this, req->parameters_);
    }

    std::string ReplyEquipmentMoneyQryMsg::to_string()
    {
        return toJson(shared_from_this());
    }

    //////////////////////////////////////////////////////////////////////////
    ReplyFeeSetQryMsg::ReplyFeeSetQryMsg()
        : ReplyMsg()
    {

    }

    ReplyFeeSetQryMsg::ReplyFeeSetQryMsg(RequestPtr req)
        : ReplyMsg(req)
    {
        req->command_ = gszMsgCommandCode[E_COMM_MSG_TYPE::FEE_MANAGER_QUERY_RSP];
        m_rtn_fee = std::make_shared<TradeFee>();
    }

    std::string ReplyFeeSetQryMsg::to_string()
    {
        return toJson(shared_from_this());
    }

    //////////////////////////////////////////////////////////////////////////
    ReplyManagerQryMsg::ReplyManagerQryMsg()
        : ReplyMsg()
    {

    }

    ReplyManagerQryMsg::ReplyManagerQryMsg(RequestPtr req)
        : ReplyMsg(req)
        , m_blast(false)
    {
        req->command_ = gszMsgCommandCode[E_COMM_MSG_TYPE::MANAGER_QUERY_RSP];
//         strncpy_s(m_qryLoginName, req->login_name_.c_str(), sizeof(m_qryLoginName) - 1);
        m_rtn_acc = std::make_shared<ManagerAccount>();
    }

    std::string ReplyManagerQryMsg::to_string()
    {
        return toJson(shared_from_this());
    }

    //////////////////////////////////////////////////////////////////////////
    ReplyAgencyAddMsg::ReplyAgencyAddMsg()
        : ReplyMsg()
    {

    }

    ReplyAgencyAddMsg::ReplyAgencyAddMsg(RequestPtr req)
        : ReplyMsg(req)
    {
        memset(m_fund_login_name, 0, sizeof(m_fund_login_name));
        m_rtn_acc = std::make_shared<AgencyAccount>();
        m_rtn_money = std::make_shared<SMoneyInfo>();
        m_rtn_risk = std::make_shared<SRiskInfo>();
        req->command_ = gszMsgCommandCode[E_COMM_MSG_TYPE::INSTITUTION_ADD_RSP];
        fromJson(this, req->parameters_);
//         strncpy_s(m_creatorLoginName, req->login_name_.c_str(), sizeof(m_creatorLoginName) - 1);
    }

    std::string ReplyAgencyAddMsg::to_string()
    {
        return toJson(shared_from_this());
    }

    //////////////////////////////////////////////////////////////////////////
    ReplyAgencyChangeMsg::ReplyAgencyChangeMsg()
        : ReplyMsg()
    {
        memset(m_fund_login_name, 0, sizeof(m_fund_login_name));
        m_rtn_acc = std::make_shared<AgencyAccount>();
        m_rtn_money = std::make_shared<SMoneyInfo>();
        m_rtn_risk = std::make_shared<SRiskInfo>();
        request_ = std::make_shared<Request>();
        request_->command_ = gszMsgCommandCode[E_COMM_MSG_TYPE::INSTITUTION_CHANGE_RSP];
    }

    ReplyAgencyChangeMsg::ReplyAgencyChangeMsg(RequestPtr req)
        : ReplyMsg(req)
    {
        memset(m_fund_login_name, 0, sizeof(m_fund_login_name));
        m_rtn_acc = std::make_shared<AgencyAccount>();
        m_rtn_money = std::make_shared<SMoneyInfo>();
        m_rtn_risk = std::make_shared<SRiskInfo>();
        req->command_ = gszMsgCommandCode[E_COMM_MSG_TYPE::INSTITUTION_CHANGE_RSP];
        fromJson(this, req->parameters_);
    }

    std::string ReplyAgencyChangeMsg::to_string()
    {
        return toJson(shared_from_this());
    }
    
    //////////////////////////////////////////////////////////////////////////
    ReplyAgencyApprovalMsg::ReplyAgencyApprovalMsg()
        : ReplyMsg()
    {

    }

    ReplyAgencyApprovalMsg::ReplyAgencyApprovalMsg(RequestPtr req)
        : ReplyMsg(req)
    {
        memset(m_fund_login_name, 0, sizeof(m_fund_login_name));
        m_rtn_acc = std::make_shared<AgencyAccount>();
        m_rtn_money = std::make_shared<SMoneyInfo>();
        m_rtn_risk = std::make_shared<SRiskInfo>();
        req->command_ = gszMsgCommandCode[E_COMM_MSG_TYPE::INSTITUTION_APPROVAL_RSP];
        fromJson(this, req->parameters_);
    }

    std::string ReplyAgencyApprovalMsg::to_string()
    {
        return toJson(shared_from_this());
    }

	/////////////////////////////////////////////////////////////////////////
	ReplyUserRoleAddRelationMsg::ReplyUserRoleAddRelationMsg()
		: ReplyMsg()
	{

	}

	ReplyUserRoleAddRelationMsg::ReplyUserRoleAddRelationMsg(RequestPtr req)
        : ReplyMsg(req)
	{
		req->command_ = gszMsgCommandCode[E_COMM_MSG_TYPE::USERROLE_ADDRELATION_RSP];
		m_rtn_arup = std::make_shared<AuthorityRoleUsers>();
		
		fromJson(this, req->parameters_);
	}

	std::string ReplyUserRoleAddRelationMsg::to_string()
	{
		return toJson(shared_from_this());
	}

    //////////////////////////////////////////////////////////////////////////
    ReplyChildAccAddMsg::ReplyChildAccAddMsg()
        : ReplyMsg()
    {

    }

    ReplyChildAccAddMsg::ReplyChildAccAddMsg(RequestPtr req)
        : ReplyMsg(req)
    {
        req->command_ = gszMsgCommandCode[E_COMM_MSG_TYPE::CHILDUSER_ADD_RSP];
        m_rtn_acc = std::make_shared<TradeAccount>();
        m_rtn_money = std::make_shared<SMoneyInfo>();
        m_rtn_risk = std::make_shared<SRiskInfo>();
        fromJson(this, req->parameters_);
    }

    std::string ReplyChildAccAddMsg::to_string()
    {
        return toJson(shared_from_this());
    }

    //////////////////////////////////////////////////////////////////////////
    ReplyChildAccChangeMsg::ReplyChildAccChangeMsg()
        : ReplyMsg()
    {
        memset(m_fund_login_name, 0, sizeof(m_fund_login_name));
        memset(m_parent_login_name, 0, sizeof(m_parent_login_name));
        m_rtn_acc = std::make_shared<TradeAccount>();
        m_rtn_money = std::make_shared<SMoneyInfo>();
        m_rtn_risk = std::make_shared<SRiskInfo>();
        request_ = std::make_shared<Request>();
        request_->command_ = gszMsgCommandCode[E_COMM_MSG_TYPE::CHILDUSER_CHANGE_RSP];
    }

    ReplyChildAccChangeMsg::ReplyChildAccChangeMsg(RequestPtr req)
        : ReplyMsg(req)
    {
        memset(m_fund_login_name, 0, sizeof(m_fund_login_name));
        memset(m_parent_login_name, 0, sizeof(m_parent_login_name));
        req->command_ = gszMsgCommandCode[E_COMM_MSG_TYPE::CHILDUSER_CHANGE_RSP];
        m_rtn_acc = std::make_shared<TradeAccount>();
        m_rtn_money = std::make_shared<SMoneyInfo>();
        m_rtn_risk = std::make_shared<SRiskInfo>();
        fromJson(this, req->parameters_);
    }

    std::string ReplyChildAccChangeMsg::to_string()
    {
        return toJson(shared_from_this());
    }

    //////////////////////////////////////////////////////////////////////////
    ReplyChildAccInmoneyMsg::ReplyChildAccInmoneyMsg()
        : ReplyMsg()
    {

    }

    ReplyChildAccInmoneyMsg::ReplyChildAccInmoneyMsg(RequestPtr req)
        : ReplyMsg(req)
    {
        m_money_change = Money_Change_Type::MC_Type_Invalid;
        req->command_ = gszMsgCommandCode[E_COMM_MSG_TYPE::CHILDUSER_INOUTMONEY_RSP];
        fromJson(this, req->parameters_);
    }

    std::string ReplyChildAccInmoneyMsg::to_string()
    {
        return toJson(shared_from_this());
    }

    //////////////////////////////////////////////////////////////////////////
    ReplyChildAccApprovalMsg::ReplyChildAccApprovalMsg()
        : ReplyMsg()
    {

    }

    ReplyChildAccApprovalMsg::ReplyChildAccApprovalMsg(RequestPtr req)
        : ReplyMsg(req)
    {
//         memset(m_opLoginName, 0, sizeof(m_opLoginName));
        memset(m_rtn_parent_login_name, 0, sizeof(m_rtn_parent_login_name));
        memset(m_rtn_fund_login_name, 0, sizeof(m_rtn_fund_login_name));
        req->command_ = gszMsgCommandCode[E_COMM_MSG_TYPE::CHILDUSER_APPROVAL_RSP];
        m_rtn_acc = std::make_shared<TradeAccount>();
        m_rtn_money = std::make_shared<SMoneyInfo>();
        m_rtn_risk = std::make_shared<SRiskInfo>();

        fromJson(this, req->parameters_);
    }

    std::string ReplyChildAccApprovalMsg::to_string()
    {
        return toJson(shared_from_this());
    }

    //////////////////////////////////////////////////////////////////////////
    ReplyFundAccAddMsg::ReplyFundAccAddMsg()
        : ReplyMsg()
    {

    }

    ReplyFundAccAddMsg::ReplyFundAccAddMsg(RequestPtr req)
        : ReplyMsg(req)
    {
        req->command_ = gszMsgCommandCode[E_COMM_MSG_TYPE::FUNDUSER_ADD_RSP];
        m_rtn_acc = std::make_shared<FunderAccount>();
        m_rtn_money = std::make_shared<SMoneyInfo>();
        m_rtn_risk = std::make_shared<SRiskInfo>();
        fromJson(this, req->parameters_);
    }

    std::string ReplyFundAccAddMsg::to_string()
    {
        return toJson(shared_from_this());
    }

    //////////////////////////////////////////////////////////////////////////
    ReplyFundAccChangeMsg::ReplyFundAccChangeMsg()
        : ReplyMsg()
    {

    }

    ReplyFundAccChangeMsg::ReplyFundAccChangeMsg(RequestPtr req)
        : ReplyMsg(req)
    {
        req->command_ = gszMsgCommandCode[E_COMM_MSG_TYPE::FUNDUSER_CHANGE_RSP];
        m_rtn_acc = std::make_shared<FunderAccount>();
        m_rtn_money = std::make_shared<SMoneyInfo>();
        m_rtn_risk = std::make_shared<SRiskInfo>();
        fromJson(this, req->parameters_);
    }

    std::string ReplyFundAccChangeMsg::to_string()
    {
        return toJson(shared_from_this());
    }

    //////////////////////////////////////////////////////////////////////////
    ReplyFeeSetMsg::ReplyFeeSetMsg()
        : ReplyMsg()
    {

    }

    ReplyFeeSetMsg::ReplyFeeSetMsg(RequestPtr req)
        : ReplyMsg(req)
    {
        req->command_ = gszMsgCommandCode[E_COMM_MSG_TYPE::FEE_SET_RSP];
        m_trade_fee = std::make_shared<TradeFee>();
        fromJson(this, req->parameters_);
    }

    std::string ReplyFeeSetMsg::to_string()
    {
        return toJson(shared_from_this());
    }

    //////////////////////////////////////////////////////////////////////////
    ReplyStockBlackSetMsg::ReplyStockBlackSetMsg()
        : ReplyMsg()
    {

    }

    ReplyStockBlackSetMsg::ReplyStockBlackSetMsg(RequestPtr req)
        : ReplyMsg(req)
    {
        req->command_ = gszMsgCommandCode[E_COMM_MSG_TYPE::STOCK_INSTRUMENTBLACK_SET_RSP];
        fromJson(this, req->parameters_);
    }

    std::string ReplyStockBlackSetMsg::to_string()
    {
        return toJson(shared_from_this());
    }

    //////////////////////////////////////////////////////////////////////////
    ReplyForbidBuySellSetMsg::ReplyForbidBuySellSetMsg()
        : ReplyMsg()
    {

    }

    ReplyForbidBuySellSetMsg::ReplyForbidBuySellSetMsg(RequestPtr req)
        : ReplyMsg(req)
    {
        forbid_trade = std::make_shared<SForbidTradeInfo>();
        req->command_ = gszMsgCommandCode[E_COMM_MSG_TYPE::FORBID_BUY_SELL_SET_RSP];
        fromJson(this, req->parameters_);
    }

    std::string ReplyForbidBuySellSetMsg::to_string()
    {
        return toJson(shared_from_this());
    }

    //////////////////////////////////////////////////////////////////////////
    ReplyPosiRateSetMsg::ReplyPosiRateSetMsg()
        : ReplyMsg()
    {

    }

    ReplyPosiRateSetMsg::ReplyPosiRateSetMsg(RequestPtr req)
        : ReplyMsg(req)
    {
        posit_rate = std::make_shared<SPositionRateInfo>();
        req->command_ = gszMsgCommandCode[E_COMM_MSG_TYPE::POSI_RATE_SET_RSP];
        fromJson(this, req->parameters_);
    }

    std::string ReplyPosiRateSetMsg::to_string()
    {
        return toJson(shared_from_this());
    }

    //////////////////////////////////////////////////////////////////////////
    ReplyRolesAddMsg::ReplyRolesAddMsg()
		: ReplyMsg()
	{

	}

	ReplyRolesAddMsg::ReplyRolesAddMsg(RequestPtr req)
		: ReplyMsg(req)
	{
		m_rtn_arp = std::make_shared<AuthorityRoles>();
		req->command_ = gszMsgCommandCode[E_COMM_MSG_TYPE::ROLES_ADD_RSP];
		fromJson(this, req->parameters_);
	}

	std::string ReplyRolesAddMsg::to_string()
	{
		return toJson(shared_from_this());
	}

	ReplyBindRelationMsg::ReplyBindRelationMsg()
		: ReplyMsg()
	{

	}

	ReplyBindRelationMsg::ReplyBindRelationMsg(RequestPtr req)
		: ReplyMsg(req)
	{
		req->command_ = gszMsgCommandCode[E_COMM_MSG_TYPE::BIND_FUNCTION_ROLE_RELATIUON_RSP];
		fromJson(this, req->parameters_);
	}

	std::string ReplyBindRelationMsg::to_string()
	{
		return toJson(shared_from_this());
	}

	//////////////////////////////////////////////////////////////////////////
	ReplyRolesChangeMsg::ReplyRolesChangeMsg(RequestPtr req)
		: ReplyMsg(req)
	{
		req->command_ = gszMsgCommandCode[E_COMM_MSG_TYPE::ROLES_CHANGE_RSP];
		m_rtn_arfp = std::make_shared<AuthorityRoles>();
		fromJson(this, req->parameters_);
	}

	ReplyRolesChangeMsg::ReplyRolesChangeMsg()
		: ReplyMsg()
	{

	}

	std::string ReplyRolesChangeMsg::to_string()
	{
		return toJson(shared_from_this());
	}

    //////////////////////////////////////////////////////////////////////////
    ReplyPswChangeMsg::ReplyPswChangeMsg()
        : ReplyMsg()
    {

    }

    ReplyPswChangeMsg::ReplyPswChangeMsg(RequestPtr req)
        : ReplyMsg(req)
    {
        req->command_ = gszMsgCommandCode[E_COMM_MSG_TYPE::PASSWORD_CHANGE_RSP];
        fromJson(this, req->parameters_);
//         strncpy_s(m_opLoginName, req->login_name_.c_str(), sizeof(m_opLoginName) - 1);
    }

    std::string ReplyPswChangeMsg::to_string()
    {
        return toJson(shared_from_this());
    }

    //////////////////////////////////////////////////////////////////////////
    ReplyManagerAddMsg::ReplyManagerAddMsg()
        : ReplyMsg()
    {

    }

    ReplyManagerAddMsg::ReplyManagerAddMsg(RequestPtr req)
        : ReplyMsg(req)
    {
        req->command_ = gszMsgCommandCode[E_COMM_MSG_TYPE::MANAGER_ADD_RSP];
        m_rtn_acc = std::make_shared<ManagerAccount>();
        fromJson(this, req->parameters_);
//         strncpy_s(m_creatorLoginName, req->login_name_.c_str(), sizeof(m_creatorLoginName) - 1);
    }

    std::string ReplyManagerAddMsg::to_string()
    {
        return toJson(shared_from_this());
    }

    //////////////////////////////////////////////////////////////////////////
    ReplyManagerChangeMsg::ReplyManagerChangeMsg()
        : ReplyMsg()
    {

    }

    ReplyManagerChangeMsg::ReplyManagerChangeMsg(RequestPtr req)
        : ReplyMsg(req)
    {
        req->command_ = gszMsgCommandCode[E_COMM_MSG_TYPE::MANAGER_CHANGE_RSP];
        m_rtn_acc = std::make_shared<ManagerAccount>();
        fromJson(this, req->parameters_);
//         strncpy_s(m_creatorLoginName, req->login_name_.c_str(), sizeof(m_creatorLoginName) - 1);
    }

    std::string ReplyManagerChangeMsg::to_string()
    {
        return toJson(shared_from_this());
    }

    //////////////////////////////////////////////////////////////////////////
    ReplyOpenCloseMsg::ReplyOpenCloseMsg()
        : ReplyMsg()
    {

    }

    ReplyOpenCloseMsg::ReplyOpenCloseMsg(RequestPtr req)
        : ReplyMsg(req)
    {
        req->command_ = gszMsgCommandCode[E_COMM_MSG_TYPE::ORDERINSERT_MSG];
        m_order_ptr = std::make_shared<StockOrderInfo>();
        fromJson(this, req->parameters_);
    }

    std::string ReplyOpenCloseMsg::to_string()
    {
        return toJson(shared_from_this());
    }

    //////////////////////////////////////////////////////////////////////////
    ReplyCancelOrderMsg::ReplyCancelOrderMsg()
        : ReplyMsg()
    {

    }

    ReplyCancelOrderMsg::ReplyCancelOrderMsg(RequestPtr req)
        : ReplyMsg(req)
    {
        memset(m_orderstream, 0, sizeof(m_orderstream));
        req->command_ = gszMsgCommandCode[E_COMM_MSG_TYPE::ORDERCANCEL_MSG];
        fromJson(this, req->parameters_);
    }

    std::string ReplyCancelOrderMsg::to_string()
    {
        return toJson(shared_from_this());
    }

    //////////////////////////////////////////////////////////////////////////
    PushOrderMsg::PushOrderMsg()
        : ReplyMsg()
    {

    }

    PushOrderMsg::PushOrderMsg(AllTrade::ErrorCodeType rslt, const SAccountPtr account, const std::string& command, const AllTrade::NPTradeCenter::OrderInfoPtr& order_ptr)
        : ReplyMsg()
        , m_order_ptr(order_ptr)
        , m_account(account)
    {
        result_ = rslt;
        request_ = std::make_shared<Request>();
        request_->command_ = command;
        memset(m_parent_login_name, 0, sizeof(m_parent_login_name) - 1);
    }

    std::string PushOrderMsg::to_string()
    {
        return toJson(shared_from_this());
    }

    //////////////////////////////////////////////////////////////////////////
    PushTradeMsg::PushTradeMsg()
        : ReplyMsg()
    {

    }

    PushTradeMsg::PushTradeMsg(AllTrade::ErrorCodeType rslt, const SAccountPtr account, const std::string& command, const AllTrade::NPTradeCenter::StockTradePtr& trade_ptr)
        : ReplyMsg()
        , m_trade_ptr(trade_ptr)
        , m_account(account)
    {
        result_ = rslt;
        request_ = std::make_shared<Request>();
        request_->command_ = command;
    }

    std::string PushTradeMsg::to_string()
    {
        return toJson(shared_from_this());
    }

    //////////////////////////////////////////////////////////////////////////
    PushPositionMsg::PushPositionMsg()
        : ReplyMsg()
    {

    }

    PushPositionMsg::PushPositionMsg(AllTrade::ErrorCodeType rslt, const SAccountPtr account, const std::string& command, const AllTrade::NPTradeCenter::PositionInfoPtr& position_ptr)
        : ReplyMsg()
        , m_position_ptr(position_ptr)
        , m_currency_rate(0)
        , m_account(account)
    {
        result_ = rslt;
        request_ = std::make_shared<Request>();
        request_->command_ = command;
    }

    std::string PushPositionMsg::to_string()
    {
        return toJson(shared_from_this());
    }

    //////////////////////////////////////////////////////////////////////////
    PushMoneyMsg::PushMoneyMsg()
        : ReplyMsg()
    {

    }

    PushMoneyMsg::PushMoneyMsg(AllTrade::ErrorCodeType rslt, const AllTrade::NPMgrCenter::SAccountPtr account, const std::string& command, const AllTrade::NPMgrCenter::SMoneyInfoPtr& money_ptr)
        : ReplyMsg()
        , m_money_ptr(money_ptr)
        , m_account(account)
    {
        memset(m_parent_login_name, 0, sizeof(m_parent_login_name));
        result_ = rslt;
        request_ = std::make_shared<Request>();
        request_->command_ = command;
    }

    std::string PushMoneyMsg::to_string()
    {
        return toJson(shared_from_this());
    }

    //////////////////////////////////////////////////////////////////////////
    PushRiskControlMsg::PushRiskControlMsg()
        : ReplyMsg()
    {

    }

    PushRiskControlMsg::PushRiskControlMsg(AllTrade::ErrorCodeType rslt, const std::string& command)
        : ReplyMsg()
    {
        result_ = rslt;
        request_ = std::make_shared<Request>();
        request_->command_ = command;
    }

    std::string PushRiskControlMsg::to_string()
    {
        return toJson(shared_from_this());
    }

	//////////////////////////////////////
    ReplySelfFunctionMsg::ReplySelfFunctionMsg()
        : ReplyMsg()
    {

    }

    ReplySelfFunctionMsg::ReplySelfFunctionMsg(RequestPtr req)
        : ReplyMsg(req)
    {
		req->command_ = gszMsgCommandCode[E_COMM_MSG_TYPE::SELFFUNCTION_QUERY_RSP];
// 		fromJson(this, req->parameters_);
	}

	std::string ReplySelfFunctionMsg::to_string()
	{
		return toJson(shared_from_this());
	}

	//////////////////////////////////////
	ReplyRoleFunctionMsg::ReplyRoleFunctionMsg(RequestPtr req)
        : ReplyMsg(req)
	{

		req->command_ = gszMsgCommandCode[E_COMM_MSG_TYPE::ROLEFUNCTION_QUERY_RSP];
		fromJson(this, req->parameters_);
	}

	ReplyRoleFunctionMsg::ReplyRoleFunctionMsg()
		: ReplyMsg()
	{

	}

	std::string ReplyRoleFunctionMsg::to_string()
	{
		return toJson(shared_from_this());
	}

	///////////////////////////////////////////////////////
	ReplyDelRoleMsg::ReplyDelRoleMsg()
		: ReplyMsg()
	{

	}

	ReplyDelRoleMsg::ReplyDelRoleMsg(RequestPtr req)
        : ReplyMsg(req)
	{
		req->command_ = gszMsgCommandCode[E_COMM_MSG_TYPE::ROLES_DEL_RSP];
		fromJson(this, req->parameters_);
	}

	std::string ReplyDelRoleMsg::to_string()
	{
		return toJson(shared_from_this());
	}

	///////////////////////////////////////////////////////
	ReplyDelRoleUserMsg::ReplyDelRoleUserMsg()
		: ReplyMsg()
	{

	}

	ReplyDelRoleUserMsg::ReplyDelRoleUserMsg(RequestPtr req)
        : ReplyMsg(req)
	{
		req->command_ = gszMsgCommandCode[E_COMM_MSG_TYPE::ROLES_USER_DEL_RSP];
		m_rtn_arup = std::make_shared<AuthorityRoleUsers>();
		fromJson(this, req->parameters_);
	}

	std::string ReplyDelRoleUserMsg::to_string()
	{
		return toJson(shared_from_this());
	}

	/////////////////////////////////////////
	ReplyGetAllBussnessMsg::ReplyGetAllBussnessMsg()
		: ReplyMsg()
	{

	}

	ReplyGetAllBussnessMsg::ReplyGetAllBussnessMsg(RequestPtr req)
        : ReplyMsg(req)
	{
		req->command_ = gszMsgCommandCode[E_COMM_MSG_TYPE::BUSSNESS_QUERY_RSP];
// 		fromJson(this, req->parameters_);
	}

	std::string ReplyGetAllBussnessMsg::to_string()
	{
		return toJson(shared_from_this());
	}

    //////////////////////////////////////////////////////////////////////////
    ReplyApplyEquipMoneyMsg::ReplyApplyEquipMoneyMsg()
        : ReplyMsg()
    {

    }

    ReplyApplyEquipMoneyMsg::ReplyApplyEquipMoneyMsg(RequestPtr req)
        : ReplyMsg(req)
    {
        req->command_ = gszMsgCommandCode[E_COMM_MSG_TYPE::APPLY_EQUIPMONEY_RSP];
//         strncpy_s(m_login_name, req->login_name_.c_str(), sizeof(m_login_name) - 1);
        fromJson(this, req->parameters_);
    }

    std::string ReplyApplyEquipMoneyMsg::to_string()
    {
        return toJson(shared_from_this());
    }

    //////////////////////////////////////////////////////////////////////////
    ReplyApprovalApplyEquipMoneyMsg::ReplyApprovalApplyEquipMoneyMsg()
        : ReplyMsg()
    {

    }

    ReplyApprovalApplyEquipMoneyMsg::ReplyApprovalApplyEquipMoneyMsg(RequestPtr req)
        : ReplyMsg(req)
    {
        req->command_ = gszMsgCommandCode[E_COMM_MSG_TYPE::APPLY_EQUIPMONEY_APPROVAL_RSP];
//         strncpy_s(m_approval_login_name, req->login_name_.c_str(), sizeof(m_approval_login_name) - 1);
        fromJson(this, req->parameters_);
    }

    std::string ReplyApprovalApplyEquipMoneyMsg::to_string()
    {
        return toJson(shared_from_this());
    }

    //////////////////////////////////////////////////////////////////////////
    ReplyAgencyDeleteMsg::ReplyAgencyDeleteMsg()
        : ReplyMsg()
    {

    }

    ReplyAgencyDeleteMsg::ReplyAgencyDeleteMsg(RequestPtr req)
        : ReplyMsg(req)
    {
        req->command_ = gszMsgCommandCode[E_COMM_MSG_TYPE::INSTITUTION_DEL_RSP];
//         strncpy_s(m_deleter_login_name, req->login_name_.c_str(), sizeof(m_deleter_login_name) - 1);
        fromJson(this, req->parameters_);
    }

    std::string ReplyAgencyDeleteMsg::to_string()
    {
        return toJson(shared_from_this());
    }

    //////////////////////////////////////////////////////////////////////////
    ReplyChildDeleteMsg::ReplyChildDeleteMsg()
        : ReplyMsg()
    {

    }

    ReplyChildDeleteMsg::ReplyChildDeleteMsg(RequestPtr req)
        : ReplyMsg(req)
    {
        req->command_ = gszMsgCommandCode[E_COMM_MSG_TYPE::CHILDUSER_DEL_RSP];
//         strncpy_s(m_deleter_login_name, req->login_name_.c_str(), sizeof(m_deleter_login_name) - 1);
        fromJson(this, req->parameters_);
    }

    std::string ReplyChildDeleteMsg::to_string()
    {
        return toJson(shared_from_this());
    }

    //////////////////////////////////////////////////////////////////////////
    ReplyFunderDeleteMsg::ReplyFunderDeleteMsg()
        : ReplyMsg()
    {

    }

    ReplyFunderDeleteMsg::ReplyFunderDeleteMsg(RequestPtr req)
        : ReplyMsg(req)
    {
        req->command_ = gszMsgCommandCode[E_COMM_MSG_TYPE::FUNDUSER_DEL_RSP];
//         strncpy_s(m_deleter_login_name, req->login_name_.c_str(), sizeof(m_deleter_login_name) - 1);
        fromJson(this, req->parameters_);
    }

    std::string ReplyFunderDeleteMsg::to_string()
    {
        return toJson(shared_from_this());
    }

    //////////////////////////////////////////////////////////////////////////
    ReplyManagerDeleteMsg::ReplyManagerDeleteMsg()
        : ReplyMsg()
    {

    }

    ReplyManagerDeleteMsg::ReplyManagerDeleteMsg(RequestPtr req)
        : ReplyMsg(req)
    {
        req->command_ = gszMsgCommandCode[E_COMM_MSG_TYPE::MANAGER_DEL_RSP];
//         strncpy_s(m_deleter_login_name, req->login_name_.c_str(), sizeof(m_deleter_login_name) - 1);
        fromJson(this, req->parameters_);
    }

    std::string ReplyManagerDeleteMsg::to_string()
    {
        return toJson(shared_from_this());
    }

    //////////////////////////////////////////////////////////////////////////
    ReplyGetCustomStockMsg::ReplyGetCustomStockMsg()
        : ReplyMsg()
    {

    }

    ReplyGetCustomStockMsg::ReplyGetCustomStockMsg(RequestPtr req)
        : ReplyMsg(req)
        , m_blast(false)
    {
        memset(m_exchange_code, 0, sizeof(m_exchange_code));
        req->command_ = gszMsgCommandCode[E_COMM_MSG_TYPE::CUSTOMSTOCK_RSP];
    }

    std::string ReplyGetCustomStockMsg::to_string()
    {
        return toJson(shared_from_this());
    }

    //////////////////////////////////////////////////////////////////////////
    ReplyAddCustomStockMsg::ReplyAddCustomStockMsg()
        : ReplyMsg()
    {

    }

    ReplyAddCustomStockMsg::ReplyAddCustomStockMsg(RequestPtr req)
        : ReplyMsg(req)
    {
        memset(m_exchange_code, 0, sizeof(m_exchange_code));
        req->command_ = gszMsgCommandCode[E_COMM_MSG_TYPE::CUSTOMSTOCK_ADD_RSP];
        fromJson(this, req->parameters_);
    }

    std::string ReplyAddCustomStockMsg::to_string()
    {
        return toJson(shared_from_this());
    }

    //////////////////////////////////////////////////////////////////////////
    ReplyDelCustomStockMsg::ReplyDelCustomStockMsg()
        : ReplyMsg()
    {

    }

    ReplyDelCustomStockMsg::ReplyDelCustomStockMsg(RequestPtr req)
        : ReplyMsg(req)
    {
        memset(m_exchange_code, 0, sizeof(m_exchange_code));
        req->command_ = gszMsgCommandCode[E_COMM_MSG_TYPE::CUSTOMSTOCK_DEL_RSP];
        fromJson(this, req->parameters_);
    }

    std::string ReplyDelCustomStockMsg::to_string()
    {
        return toJson(shared_from_this());
    }


	//////////////////////////////////////////////////////////////////////////
	ReplyChangeRoleUserMsg::ReplyChangeRoleUserMsg()
		: ReplyMsg()
	{

	}

	ReplyChangeRoleUserMsg::ReplyChangeRoleUserMsg(RequestPtr req)
		: ReplyMsg(req)
	{
		req->command_ = gszMsgCommandCode[E_COMM_MSG_TYPE::ROLES_USER_CHANGE_RSP];
		m_rtn_arup = std::make_shared<AuthorityRoleUsers>();
		fromJson(this, req->parameters_);
	}

	std::string ReplyChangeRoleUserMsg::to_string()
	{
		return toJson(shared_from_this());
	}

    //////////////////////////////////////////////////////////////////////////
    ReplyChildAccAutoAddMsg::ReplyChildAccAutoAddMsg()
        : ReplyMsg()
    {

    }

    ReplyChildAccAutoAddMsg::ReplyChildAccAutoAddMsg(RequestPtr req)
        : ReplyMsg(req)
    {
        req->command_ = gszMsgCommandCode[E_COMM_MSG_TYPE::CHILDUSER_AUTO_ADD_RSP];
        m_rtn_acc = std::make_shared<TradeAccount>();
        m_rtn_money = std::make_shared<SMoneyInfo>();
        m_rtn_risk = std::make_shared<SRiskInfo>();
        fromJson(this, req->parameters_);
    }

    std::string ReplyChildAccAutoAddMsg::to_string()
    {
        return toJson(shared_from_this());
    }

    //////////////////////////////////////////////////////////////////////////
    ReplyAutoInMoneyQryMsg::ReplyAutoInMoneyQryMsg()
        : ReplyMsg()
        , m_blast(false)
    {

    }

    ReplyAutoInMoneyQryMsg::ReplyAutoInMoneyQryMsg(RequestPtr req)
        : ReplyMsg(req)
        , m_blast(false)
    {
        req->command_ = gszMsgCommandCode[E_COMM_MSG_TYPE::CHILD_AUTOINTOMONEY_QUERY_RSP];
        m_rtn_acc = std::make_shared<TradeAccount>();
        m_money = std::make_shared<SApplyMoneyInfo>();
        fromJson(this, req->parameters_);
    }

    std::string ReplyAutoInMoneyQryMsg::to_string()
    {
        return toJson(shared_from_this());
    }

    //////////////////////////////////////////////////////////////////////////
    ReplyAutoInMoneyMsg::ReplyAutoInMoneyMsg()
        : ReplyMsg()
    {

    }

    ReplyAutoInMoneyMsg::ReplyAutoInMoneyMsg(RequestPtr req)
        : ReplyMsg(req)
    {
        req->command_ = gszMsgCommandCode[E_COMM_MSG_TYPE::CHILDUSER_AUTO_INMONEY_RSP];
        fromJson(this, req->parameters_);
    }

    std::string ReplyAutoInMoneyMsg::to_string()
    {
        return toJson(shared_from_this());
    }

    //////////////////////////////////////////////////////////////////////////
    ReplyAutoInMoneyApprovalMsg::ReplyAutoInMoneyApprovalMsg()
        : ReplyMsg()
    {

    }

    ReplyAutoInMoneyApprovalMsg::ReplyAutoInMoneyApprovalMsg(RequestPtr req)
        : ReplyMsg(req)
    {
        req->command_ = gszMsgCommandCode[E_COMM_MSG_TYPE::CHILDUSER_AUTOINMONEY_APPROVAL_RSP];
        fromJson(this, req->parameters_);
    }

    std::string ReplyAutoInMoneyApprovalMsg::to_string()
    {
        return toJson(shared_from_this());
    }

    //////////////////////////////////////////////////////////////////////////
    ReplyAutoOutMoneyQryMsg::ReplyAutoOutMoneyQryMsg()
        : ReplyMsg()
    {

    }

    ReplyAutoOutMoneyQryMsg::ReplyAutoOutMoneyQryMsg(RequestPtr req)
        : ReplyMsg(req)
        , m_blast(false)
    {
        req->command_ = gszMsgCommandCode[E_COMM_MSG_TYPE::CHILD_AUTOOUTMONEY_QUERY_RSP];
        m_rtn_acc = std::make_shared<TradeAccount>();
        m_money = std::make_shared<SApplyMoneyInfo>();
        fromJson(this, req->parameters_);
    }

    std::string ReplyAutoOutMoneyQryMsg::to_string()
    {
        return toJson(shared_from_this());
    }

    //////////////////////////////////////////////////////////////////////////
    ReplyAutoOutMoneyMsg::ReplyAutoOutMoneyMsg()
        : ReplyMsg()
    {

    }

    ReplyAutoOutMoneyMsg::ReplyAutoOutMoneyMsg(RequestPtr req)
        : ReplyMsg(req)
    {
        req->command_ = gszMsgCommandCode[E_COMM_MSG_TYPE::CHILDUSER_AUTO_OUTMONEYL_RSP];
        fromJson(this, req->parameters_);
    }

    std::string ReplyAutoOutMoneyMsg::to_string()
    {
        return toJson(shared_from_this());
    }
    //////////////////////////////////////////////////////////////////////////
    ReplyAutoOutMoneyApprovalMsg::ReplyAutoOutMoneyApprovalMsg()
        : ReplyMsg()
    {

    }

    ReplyAutoOutMoneyApprovalMsg::ReplyAutoOutMoneyApprovalMsg(RequestPtr req)
        : ReplyMsg(req)
    {
        req->command_ = gszMsgCommandCode[E_COMM_MSG_TYPE::CHILDUSER_AUTOOUTMONEY_APPROVAL_RSP];
        fromJson(this, req->parameters_);
    }

    std::string ReplyAutoOutMoneyApprovalMsg::to_string()
    {
        return toJson(shared_from_this());
    }
	//////////////////////////////////////////////////////////////////////////
	ReplyRiskHistoryMsg::ReplyRiskHistoryMsg()
		: ReplyMsg()
	{

	}

	ReplyRiskHistoryMsg::ReplyRiskHistoryMsg(RequestPtr req)
		: ReplyMsg(req)
		, m_blast(false)
	{
		req->command_ = gszMsgCommandCode[E_COMM_MSG_TYPE::RISK_HISTORY_RSP];
		m_contextPtr = std::make_shared<ImmRiskControlSt>();
		fromJson(this, req->parameters_);
		
	}

	std::string ReplyRiskHistoryMsg::to_string()
	{
		return toJson(shared_from_this());
	}

	//////////////////////////////////////////////////////////////////////////
	ReplySetMarginMsg::ReplySetMarginMsg()
		: ReplyMsg()
	{
		
	}

	ReplySetMarginMsg::ReplySetMarginMsg(RequestPtr req)
		: ReplyMsg(req)
		, m_blast(false)
	{
		req->command_ = gszMsgCommandCode[E_COMM_MSG_TYPE::MARGIN_SET_RSP];
		m_margin_set_ = std::make_shared<MarginInfo>();
		fromJson(this, req->parameters_);
	}

	std::string ReplySetMarginMsg::to_string()
	{
		return toJson(shared_from_this());
	}


	//////////////////////////////////////////////////////////////////////////
	ReplyMarginLeftQtyMsg::ReplyMarginLeftQtyMsg()
		: ReplyMsg()
	{

	}

	ReplyMarginLeftQtyMsg::ReplyMarginLeftQtyMsg(RequestPtr req)
		: ReplyMsg(req)
		, m_blast(false)
	{
		req->command_ = gszMsgCommandCode[E_COMM_MSG_TYPE::MARGIN_LEFTQTY_RSP];
		m_margin_left_ = std::make_shared<MarginLeftInfo>();
		fromJson(this, req->parameters_);

	}

	std::string ReplyMarginLeftQtyMsg::to_string()
	{
		return toJson(shared_from_this());
	}

	//////////////////////////////////////////////////////////////
	ReplyMarginManagerQtyMsg::ReplyMarginManagerQtyMsg()
		: ReplyMsg()
	{

	}

	ReplyMarginManagerQtyMsg::ReplyMarginManagerQtyMsg(RequestPtr req)
		: ReplyMsg(req)
		, m_blast(false)
	{
		req->command_ = gszMsgCommandCode[E_COMM_MSG_TYPE::MARGIN_MANAGER_RSP];
		m_margin_set_ = std::make_shared<MarginInfo>();
		fromJson(this, req->parameters_);
	}

	std::string ReplyMarginManagerQtyMsg::to_string()
	{
		return toJson(shared_from_this());
	}

	//////////////////////////////////////////////////////////////
	ReplyMarginLiabilitiesQtyMsg::ReplyMarginLiabilitiesQtyMsg()
		: ReplyMsg()
	{

	}

	ReplyMarginLiabilitiesQtyMsg::ReplyMarginLiabilitiesQtyMsg(RequestPtr req)
		: ReplyMsg(req)
		, m_blast(false)
	{
		req->command_ = gszMsgCommandCode[E_COMM_MSG_TYPE::MARGIN_LIABILITIES_RSP];
		m_margin_posi_ = std::make_shared<AllTrade::NPTradeCenter::MarginPositionInfo>();
		fromJson(this, req->parameters_);
	}

	std::string ReplyMarginLiabilitiesQtyMsg::to_string()
	{
		return toJson(shared_from_this());
	}

	//////////////////////////////////////////////////////////////
	ReplyInterestStatisticsMsg::ReplyInterestStatisticsMsg()
		: ReplyMsg()
	{

	}

	ReplyInterestStatisticsMsg::ReplyInterestStatisticsMsg(RequestPtr req)
		: ReplyMsg(req)
		, m_blast(false)
	{
		req->command_ = gszMsgCommandCode[E_COMM_MSG_TYPE::INTEREST_STATISTICS_RSP];
		m_ptr_ = std::make_shared<AllTrade::NPMgrCenter::InterestStatistics>();
		fromJson(this, req->parameters_);
	}

	std::string ReplyInterestStatisticsMsg::to_string()
	{
		return toJson(shared_from_this());
	}

	//////////////////////////////////////////////////////////////
	ReplyInterestDetailMsg::ReplyInterestDetailMsg()
		: ReplyMsg()
	{

	}

	ReplyInterestDetailMsg::ReplyInterestDetailMsg(RequestPtr req)
		: ReplyMsg(req)
		, m_blast(false)
	{
		req->command_ = gszMsgCommandCode[E_COMM_MSG_TYPE::INTEREST_DETAIL_RSP];
		m_ptr_ = std::make_shared<AllTrade::NPMgrCenter::InterestDetail>();
		fromJson(this, req->parameters_);
	}

	std::string ReplyInterestDetailMsg::to_string()
	{
		return toJson(shared_from_this());
	}


	//////////////////////////////////////////////////////////////
	ReplyCurrentMarginEntrustMsg::ReplyCurrentMarginEntrustMsg()
		: ReplyMsg()
	{

	}

	ReplyCurrentMarginEntrustMsg::ReplyCurrentMarginEntrustMsg(RequestPtr req)
		: ReplyMsg(req)
		, m_blast(false)
	{
		req->command_ = gszMsgCommandCode[E_COMM_MSG_TYPE::CURRENT_MARGINENTRUST_RSP];
		m_order_ptr = std::make_shared<StockOrderInfo>();
		m_stock_ptr = std::make_shared<SStockContract>();
		m_rtn_acc = std::make_shared<TradeAccount>();
		fromJson(this, req->parameters_);
	}

	std::string ReplyCurrentMarginEntrustMsg::to_string()
	{
		return toJson(shared_from_this());
	}

	//////////////////////////////////////////////////////////////
	ReplyCurrentMarginTradeQryMsg::ReplyCurrentMarginTradeQryMsg()
		: ReplyMsg()
	{

	}

	ReplyCurrentMarginTradeQryMsg::ReplyCurrentMarginTradeQryMsg(RequestPtr req)
		: ReplyMsg(req)
		, m_blast(false)
	{
		req->command_ = gszMsgCommandCode[E_COMM_MSG_TYPE::CURRENT_MARGINTRADE_RSP];
		m_trade_ptr = std::make_shared<StockTradeInfo>();
		m_stock_ptr = std::make_shared<SStockContract>();
		m_rtn_acc = std::make_shared<TradeAccount>();
		fromJson(this, req->parameters_);
	}

	std::string ReplyCurrentMarginTradeQryMsg::to_string()
	{
		return toJson(shared_from_this());
	}

}