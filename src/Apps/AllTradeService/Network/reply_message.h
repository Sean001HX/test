/*
* Purpose: ͨѶ��Ӧ��Ϣ���ࡢ�����ඨ�壻
*/

#ifndef  __PCA_REPLY_MSG_H__
#define  __PCA_REPLY_MSG_H__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif

#include <vector>
#include <memory>
#include <tuple>
#include "define/protocol_error.h"
#include "../NetInfo/RequestMsgDefine.h"
#include "define/struct_declare.h"
#include "define/reply_message_declare.h"

class TCPImpl;

namespace xyc_communication
{
    /// ��Ϣ��Ӧ��
	class ReplyMsg
	{
	public:
		ReplyMsg();
		ReplyMsg(RequestPtr req);
        ReplyMsg(AllTrade::ErrorCodeType rslt, int socketID, const std::string& command);
        ReplyMsg(RequestPtr req, AllTrade::ErrorCodeType rslt);

		virtual ~ReplyMsg() ;

        /// �������ڷ��͵Ļ�Ӧ��Ϣ�ı���
		virtual std::string to_string() ;

        void setResult(AllTrade::ErrorCodeType result);
        AllTrade::ErrorCodeType getResult() const { return result_; }
        void setRequest(RequestPtr preq);
		RequestPtr getRequest()const {return request_;}
        const std::string& getCmdCode() const { return request_->command_; }

        int getSocketID() const;
        TCPImpl* getTCPImpl() const;
        AllTrade::PLoginNameType getLoginName() const;

        static ReplyMsgPtr getReply(AllTrade::ErrorCodeType rslt, int socketID, const std::string& command)	// ����һ����Ӧ��Ϣ����
		{
            return std::make_shared<ReplyMsg>(rslt, socketID, command);
		}
		
        static ReplyMsgPtr getReply(RequestPtr preq, AllTrade::ErrorCodeType rslt)	// ����һ����Ӧ��Ϣ����
		{
            return std::make_shared<ReplyMsg>(preq, rslt);
		}

	protected:
		AllTrade::ErrorCodeType		result_;
		RequestPtr		            request_;
    };

	/// ��¼Ӧ��
    class ReplyLoginMsg : public ReplyMsg, public std::enable_shared_from_this<ReplyLoginMsg>
	{
    public:
        ReplyLoginMsg();
		ReplyLoginMsg(RequestPtr req);

        static ReplyLoginMsgPtr getReply(RequestPtr req){
            return std::make_shared<ReplyLoginMsg>(req);
        }

        std::string to_string();

        AllTrade::LoginNameType       m_parent_login_name;   // ��¼�� 
        AllTrade::LoginNameType       m_login_name;   // ��¼�� 
        AllTrade::LoginPasswordType   m_password;     // ����

        AllTrade::NPMgrCenter::SAccountPtr m_rtn_acc;

        AllTrade::NPMgrCenter::SOnlineAccountPtr     m_login_info;  // ��¼��Ϣ
    };

    /// ������ѯӦ��
    class ReplyAgencyQryMsg : public ReplyMsg, public std::enable_shared_from_this<ReplyAgencyQryMsg>
    {
    public:
        ReplyAgencyQryMsg();
        ReplyAgencyQryMsg(RequestPtr req);

    public:
        std::string to_string();

        static ReplyAgencyQryMsgPtr getReply(RequestPtr req){
            return std::make_shared<ReplyAgencyQryMsg>(req);
        }

        AllTrade::NPMgrCenter::AgencyAccountPtr m_rtn_agency;
        AllTrade::NPMgrCenter::SRiskInfoPtr     m_rtn_risk;
        AllTrade::LoginNameType                 m_rtn_parent_login_name;
        AllTrade::LoginNameType      m_fund_login_name;
        bool                                    m_blast;
    };

    /// ����˻�����ѯӦ��
    class ReplyAgencyPreApprovalQryMsg : public ReplyMsg, public std::enable_shared_from_this<ReplyAgencyPreApprovalQryMsg>
    {
    public:
        ReplyAgencyPreApprovalQryMsg();
        ReplyAgencyPreApprovalQryMsg(RequestPtr req);

        std::string to_string();

        static ReplyAgencyPreApprovalQryMsgPtr getReply(RequestPtr req){
            return std::make_shared<ReplyAgencyPreApprovalQryMsg>(req);
        }

        AllTrade::NPMgrCenter::AgencyAccountPtr m_rtn_agency;
        AllTrade::NPMgrCenter::SRiskInfoPtr     m_rtn_risk;
        AllTrade::LoginNameType                 m_rtn_parent_login_name;
        AllTrade::LoginNameType      m_fund_login_name;
        bool                                    m_blast;
    };
    /*
    /// �����ƹ��ѯӦ��
    class ReplyAgencyLinkQryMsg : public ReplyMsg
    {
    public:
        ReplyAgencyLinkQryMsg();
        ReplyAgencyLinkQryMsg(RequestPtr req);

        std::string to_string();

        static ReplyMsgPtr getReply(RequestPtr req);
    };*/

	/// ��ɫ��ѯӦ��
	class ReplyRolesQryMsg : public ReplyMsg, public std::enable_shared_from_this<ReplyRolesQryMsg>
	{
	public:
		ReplyRolesQryMsg();
		ReplyRolesQryMsg(RequestPtr req);

		std::string to_string();

		static ReplyRolesQryMsgPtr getReply(RequestPtr req){
			return std::make_shared<ReplyRolesQryMsg>(req);
		}

		AllTrade::AuthorityRolesPtr		m_rtn_arp;
        bool                            m_blast;
    };

    /// �������û�����ɫ��ϵ��ѯӦ��
	class ReplyAgencyRolesQryMsg : public ReplyMsg, public std::enable_shared_from_this<ReplyAgencyRolesQryMsg>
    {
    public:
        ReplyAgencyRolesQryMsg();
        ReplyAgencyRolesQryMsg(RequestPtr req);

        std::string to_string();

		static ReplyAgencyRolesQryMsgPtr getReply(RequestPtr req){
			return std::make_shared<ReplyAgencyRolesQryMsg>(req);
		}
		AllTrade::AuthorityRoleUsersPtr		m_rtn_arp;
        bool                                m_blast;
    };

    /// Ӷ���ѯӦ��
    class ReplyCommissQryMsg : public ReplyMsg, public std::enable_shared_from_this<ReplyCommissQryMsg>
    {
    public:
        ReplyCommissQryMsg();
        ReplyCommissQryMsg(RequestPtr req);

        std::string to_string();

        static ReplyCommissQryMsgPtr getReply(RequestPtr req){
            return std::make_shared<ReplyCommissQryMsg>(req);
        }

        AllTrade::UserIDType                    m_qry_login_name;
        AllTrade::DateType                      m_start_day;
        AllTrade::DateType                      m_end_day;

        AllTrade::NPMgrCenter::SAccountPtr      m_rtn_acc;
        YDouble                                 m_infomatch_rate;
        YDouble                                 m_infomatch;
        YDouble                                 m_tradefee_rate;
        YDouble                                 m_tradefee;
        YDouble                                 m_comm_all;

    };

    /// Ӷ����ϸ��ѯӦ��
    class ReplyCommissDtlQryMsg : public ReplyMsg, public std::enable_shared_from_this<ReplyCommissDtlQryMsg>
    {
    public:
        ReplyCommissDtlQryMsg();
        ReplyCommissDtlQryMsg(RequestPtr req);

        std::string to_string();

        static ReplyCommissDtlQryMsgPtr getReply(RequestPtr req){
            return std::make_shared<ReplyCommissDtlQryMsg>(req);
        }

        AllTrade::UserIDType                                m_qry_login_name;
        AllTrade::DateType                                  m_start_day;
        AllTrade::DateType                                  m_end_day;

        AllTrade::NPMgrCenter::SAgencyMoneyDetailInfoPtr    m_detail_ptr;
        AllTrade::NPMgrCenter::SAccountPtr                  m_rtn_acc;
        AllTrade::NPMgrCenter::SAccountPtr                  m_rtn_source_acc;
        bool                                                m_blast;
    };

    /// �ֳɲ�ѯӦ��
    class ReplyProfitCommisslQryMsg : public ReplyMsg, public std::enable_shared_from_this<ReplyProfitCommisslQryMsg>
    {
    public:
        ReplyProfitCommisslQryMsg();
        ReplyProfitCommisslQryMsg(RequestPtr req);

        std::string to_string();

        static ReplyProfitCommisslQryMsgPtr getReply(RequestPtr req){
            return std::make_shared<ReplyProfitCommisslQryMsg>(req);
        }

        AllTrade::UserIDType                    m_qry_login_name;
        AllTrade::DateType                      m_start_day;
        AllTrade::DateType                      m_end_day;

        AllTrade::NPMgrCenter::SAccountPtr      m_rtn_acc;
        YDouble                                 m_profit_rate;
        YDouble                                 m_profit;
    };

    /// �ֳ���ϸ��ѯӦ��
    class ReplyProfitCommissDtlQryMsg : public ReplyMsg, public std::enable_shared_from_this<ReplyProfitCommissDtlQryMsg>
    {
    public:
        ReplyProfitCommissDtlQryMsg();
        ReplyProfitCommissDtlQryMsg(RequestPtr req);

        std::string to_string();

        static ReplyProfitCommissDtlQryMsgPtr getReply(RequestPtr req){
            return std::make_shared<ReplyProfitCommissDtlQryMsg>(req);
        }

        AllTrade::UserIDType                                m_qry_login_name;
        AllTrade::DateType                                  m_start_day;
        AllTrade::DateType                                  m_end_day;

        AllTrade::NPMgrCenter::SAgencyMoneyDetailInfoPtr    m_detail_ptr;
        AllTrade::NPMgrCenter::SAccountPtr                  m_rtn_acc;
        AllTrade::NPMgrCenter::SAccountPtr                  m_rtn_source_acc;
        bool                                                m_blast;
    };

    /*
    /// ��������ѯӦ��
    class ReplyToplogicalTreeQryMsg : public ReplyMsg
    {
    public:
        ReplyToplogicalTreeQryMsg();
        ReplyToplogicalTreeQryMsg(RequestPtr req);

        std::string& to_string();

        static ReplyMsgPtr getReply(RequestPtr req);
    };
    */
    /// ���˻���ѯӦ��
    class ReplyChildAccQryMsg : public ReplyMsg, public std::enable_shared_from_this<ReplyChildAccQryMsg>
    {
    public:
        ReplyChildAccQryMsg();
        ReplyChildAccQryMsg(RequestPtr req);

        std::string to_string();

        static ReplyChildAccQryMsgPtr getReply(RequestPtr req){
            return std::make_shared<ReplyChildAccQryMsg>(req);
        }

        AllTrade::NPMgrCenter::TradeAccountPtr  m_rtn_acc;
        AllTrade::NPMgrCenter::SMoneyInfoPtr    m_rtn_money;
        AllTrade::NPMgrCenter::SRiskInfoPtr     m_rtn_risk;
        AllTrade::LoginNameType    m_rtn_parent_login_name;
        AllTrade::LoginNameType    m_rtn_fund_login_name;
        bool                                    m_blast;
    };

    /// ���˻���˲�ѯӦ��
    class ReplyChildApprovalQryMsg : public ReplyMsg, public std::enable_shared_from_this<ReplyChildApprovalQryMsg>
    {
    public:
        ReplyChildApprovalQryMsg();
        ReplyChildApprovalQryMsg(RequestPtr req);

        std::string to_string();

        static ReplyChildApprovalQryMsgPtr getReply(RequestPtr req){
            return std::make_shared<ReplyChildApprovalQryMsg>(req);
        }

        AllTrade::NPMgrCenter::TradeAccountPtr  m_rtn_acc;
        AllTrade::NPMgrCenter::SRiskInfoPtr     m_rtn_risk;
        AllTrade::NPMgrCenter::SMoneyInfoPtr    m_rtn_money;
        AllTrade::LoginNameType    m_rtn_parent_login_name;
        AllTrade::LoginNameType    m_rtn_fund_login_name;
        bool                        m_blast;
		AllTrade::LoginNameType    m_crLoginName;
    };

    
    /// �ʽ��˻�Ӧ��
    class ReplyFundAccQryMsg : public ReplyMsg, public std::enable_shared_from_this<ReplyFundAccQryMsg>
    {
    public:
        ReplyFundAccQryMsg();
        ReplyFundAccQryMsg(RequestPtr req);

        std::string to_string();

        static ReplyFundAccQryMsgPtr getReply(RequestPtr req){
            return std::make_shared<ReplyFundAccQryMsg>(req);
        }

        AllTrade::NPMgrCenter::FunderAccountPtr     m_rtn_acc;
        AllTrade::NPMgrCenter::SMoneyInfoPtr        m_rtn_money;
        AllTrade::LoginNameType                     m_rtn_parent_login_name;

        bool                                        m_blast;
    };
    
    // ��ѯ�������˻�
    class ReplyOnlineAccQryMsg : public ReplyMsg, public std::enable_shared_from_this<ReplyOnlineAccQryMsg>
    {
    public:
        ReplyOnlineAccQryMsg();
        ReplyOnlineAccQryMsg(RequestPtr req);

        std::string to_string();

        static ReplyOnlineAccQryMsgPtr getReply(RequestPtr req){
            return std::make_shared<ReplyOnlineAccQryMsg>(req);
        }

        AllTrade::LoginNameType                     m_rtn_loginName;
        AllTrade::DateTimeType                      m_rtn_reg_dt;
        AllTrade::AccountNameType                   m_rtn_accName;
        AllTrade::NPMgrCenter::SOnlineAccountPtr    m_rtn_acc;
        bool                                        m_blast;
    };

    /// ��Ʊ��Լ��ѯӦ��
    class ReplyStockContractQryMsg : public ReplyMsg, public std::enable_shared_from_this<ReplyStockContractQryMsg>
    {
    public:
        ReplyStockContractQryMsg();
        ReplyStockContractQryMsg(RequestPtr req);

        std::string to_string();

        static ReplyStockContractQryMsgPtr getReply(RequestPtr req){
            return std::make_shared<ReplyStockContractQryMsg>(req);
        }

        AllTrade::ExchangeCodeType                  m_exchange_code;
        AllTrade::NPMgrCenter::SStockContractPtr    m_stock_ptr;
        bool                                        m_blast;
    };
    

    /// ��Ʊ��������ѯӦ��
    class ReplyStockBlackQryMsg : public ReplyMsg, public std::enable_shared_from_this<ReplyStockBlackQryMsg>
    {
    public:
        ReplyStockBlackQryMsg();
        ReplyStockBlackQryMsg(RequestPtr req);

        std::string to_string();

        static ReplyStockBlackQryMsgPtr getReply(RequestPtr req){
            return std::make_shared<ReplyStockBlackQryMsg>(req);
        }
  
        AllTrade::ContractCodeType  m_contract_code;
        AllTrade::ContractNameType  m_contract_name;
        bool                        m_isBlack;
        bool                        m_blast;
    };

    /// ��ֹ������ѯӦ��
    class ReplyForbidBuySellQryMsg : public ReplyMsg, public std::enable_shared_from_this<ReplyForbidBuySellQryMsg>
    {
    public:
        ReplyForbidBuySellQryMsg();
        ReplyForbidBuySellQryMsg(RequestPtr req);

        std::string to_string();

        static ReplyForbidBuySellQryMsgPtr getReply(RequestPtr req){
            return std::make_shared<ReplyForbidBuySellQryMsg>(req);
        }

        AllTrade::NPTradeCenter::SForbidTradePtr    forbid_trade;
        bool                                        m_blast;
    };

    /// �ֱֲ������ò�ѯӦ��
    class ReplyPosiRateQryMsg : public ReplyMsg, public std::enable_shared_from_this<ReplyPosiRateQryMsg>
    {
    public:
        ReplyPosiRateQryMsg();
        ReplyPosiRateQryMsg(RequestPtr req);

        std::string to_string();

        static ReplyPosiRateQryMsgPtr getReply(RequestPtr req){
            return std::make_shared<ReplyPosiRateQryMsg>(req);
        }

        AllTrade::NPTradeCenter::SPositionRatePtr   posit_rate;
        bool                                        m_blast;
    };

    /// �ֲֲ�ѯӦ��
    class ReplyPosiQryMsg : public ReplyMsg, public std::enable_shared_from_this<ReplyPosiQryMsg>
    {
    public:
        ReplyPosiQryMsg();
        ReplyPosiQryMsg(RequestPtr req);

        std::string to_string();

        static ReplyPosiQryMsgPtr getReply(RequestPtr req){
            return std::make_shared<ReplyPosiQryMsg>(req);
        }

        AllTrade::LoginNameType                     m_parent_login_name;
        AllTrade::NPTradeCenter::StockPositionPtr   m_position_ptr;
        AllTrade::NPMgrCenter::SContractPtr         m_stock_ptr;
        AllTrade::NPMgrCenter::TradeAccountPtr      m_rtn_acc;
        YDouble                                     m_currency_rate;
        bool                                        m_blast;
    };
    
    /// ��ǰί�в�ѯӦ��
    class ReplyCurrentyEntrustQryMsg : public ReplyMsg, public std::enable_shared_from_this<ReplyCurrentyEntrustQryMsg>
    {
    public:
        ReplyCurrentyEntrustQryMsg();
        ReplyCurrentyEntrustQryMsg(RequestPtr req);

        std::string to_string();

        static ReplyCurrentyEntrustQryMsgPtr getReply(RequestPtr req){
            return std::make_shared<ReplyCurrentyEntrustQryMsg>(req);
        }

        AllTrade::LoginNameType                     m_parent_login_name;
        AllTrade::NPTradeCenter::StockOrderPtr      m_order_ptr;
        AllTrade::NPMgrCenter::SContractPtr         m_stock_ptr;
        AllTrade::NPMgrCenter::TradeAccountPtr      m_rtn_acc;
        bool                                        m_blast;
    };

    /// ����ί�в�ѯӦ��
    class ReplyTodayEntrustQryMsg : public ReplyMsg, public std::enable_shared_from_this<ReplyTodayEntrustQryMsg>
    {
    public:
        ReplyTodayEntrustQryMsg();
        ReplyTodayEntrustQryMsg(RequestPtr req);

        std::string to_string();

        static ReplyTodayEntrustQryMsgPtr getReply(RequestPtr req){
            return std::make_shared<ReplyTodayEntrustQryMsg>(req);
        }
 
        AllTrade::LoginNameType                     m_parent_login_name;
        AllTrade::NPTradeCenter::StockOrderPtr      m_order_ptr;
        AllTrade::NPMgrCenter::SContractPtr         m_stock_ptr;
        AllTrade::NPMgrCenter::TradeAccountPtr      m_rtn_acc;
        bool                                        m_blast;
    };

    /// ��ʷί�в�ѯӦ��
    class ReplyHistoryEntrustQryMsg : public ReplyMsg, public std::enable_shared_from_this<ReplyHistoryEntrustQryMsg>
    {
    public:
        ReplyHistoryEntrustQryMsg();
        ReplyHistoryEntrustQryMsg(RequestPtr req);

        std::string to_string();

        static ReplyHistoryEntrustQryMsgPtr getReply(RequestPtr req){
            return std::make_shared<ReplyHistoryEntrustQryMsg>(req);
        }
   
        AllTrade::LoginNameType                     m_parent_login_name;
        AllTrade::NPTradeCenter::StockOrderPtr      m_order_ptr;
        AllTrade::NPMgrCenter::SContractPtr         m_stock_ptr;
        AllTrade::NPMgrCenter::TradeAccountPtr      m_rtn_acc;
        AllTrade::DateType                          m_qry_start_time;
        AllTrade::DateType                          m_qry_end_time;
        bool                                        m_blast;
    };

    /// �ɽ���ѯӦ��
    class ReplyTradeQryMsg : public ReplyMsg, public std::enable_shared_from_this<ReplyTradeQryMsg>
    {
    public:
        ReplyTradeQryMsg();
        ReplyTradeQryMsg(RequestPtr req);

        std::string to_string();

        static ReplyTradeQryMsgPtr getReply(RequestPtr req){
            return std::make_shared<ReplyTradeQryMsg>(req);
        }
   
        AllTrade::LoginNameType                     m_parent_login_name;
        AllTrade::NPTradeCenter::StockTradePtr      m_trade_ptr;
        AllTrade::NPMgrCenter::SContractPtr         m_stock_ptr;
        AllTrade::NPMgrCenter::TradeAccountPtr      m_rtn_acc;
        bool                                        m_blast;
    };

    /// ��ʷ�ɽ���ѯӦ��
    class ReplyHistoryTradeQryMsg : public ReplyMsg, public std::enable_shared_from_this<ReplyHistoryTradeQryMsg>
    {
    public:
        ReplyHistoryTradeQryMsg();
        ReplyHistoryTradeQryMsg(RequestPtr req);

        std::string to_string();

        static ReplyHistoryTradeQryMsgPtr getReply(RequestPtr req){
            return std::make_shared<ReplyHistoryTradeQryMsg>(req);
        }
   
        AllTrade::LoginNameType                     m_parent_login_name;
        AllTrade::NPTradeCenter::StockTradePtr      m_trade_ptr;
        AllTrade::NPMgrCenter::SContractPtr         m_stock_ptr;
        AllTrade::NPMgrCenter::TradeAccountPtr      m_rtn_acc;
        AllTrade::DateType                          m_qry_start_time;
        AllTrade::DateType                          m_qry_end_time;
        bool                                        m_blast;
    };

    /// �ʽ��ѯӦ��
    class ReplyFundQryMsg : public ReplyMsg, public std::enable_shared_from_this<ReplyFundQryMsg>
    {
    public:
        ReplyFundQryMsg();
        ReplyFundQryMsg(RequestPtr req);

        std::string to_string();

        static ReplyFundQryMsgPtr getReply(RequestPtr req){
            return std::make_shared<ReplyFundQryMsg>(req);
        }

        AllTrade::LoginNameType                     m_parent_login_name;
        AllTrade::NPMgrCenter::TradeAccountPtr      m_rtn_acc;
        AllTrade::NPMgrCenter::SMoneyInfoPtr        m_rtn_money;
        AllTrade::NPMgrCenter::SRiskInfoPtr         m_rtn_risk;
    };
    
    /// �ʽ���ˮ��ѯӦ��
    class ReplyFundSerialQryMsg : public ReplyMsg, public std::enable_shared_from_this<ReplyFundSerialQryMsg>
    {
    public:
        ReplyFundSerialQryMsg();
        ReplyFundSerialQryMsg(RequestPtr req);

        std::string to_string();

        static ReplyFundSerialQryMsgPtr getReply(RequestPtr req){
            return std::make_shared<ReplyFundSerialQryMsg>(req);
        }

        AllTrade::LoginNameType                     m_parent_login_name;
        AllTrade::NPMgrCenter::SMoneyDetailInfoPtr  m_rtn_money;
        AllTrade::NPMgrCenter::TradeAccountPtr      m_rtn_acc;
        AllTrade::DateType                          m_qry_start_time;
        AllTrade::DateType                          m_qry_end_time;
        bool                                        m_blast;
    };
    /*
    /// �����ѯӦ��
    class ReplyDeliveryQryMsg : public ReplyMsg
    {
    protected:
        ReplyDeliveryQryMsg();
        ReplyDeliveryQryMsg(RequestPtr req);

    public:
        std::string& to_string();

        static ReplyMsgPtr getReply(RequestPtr req);
    };

    /// ���ʻ�ʵʱ�ʽ��ز�ѯӦ��
    class ReplyFundMonitQryMsg : public ReplyMsg
    {
    protected:
        ReplyFundMonitQryMsg();
        ReplyFundMonitQryMsg(RequestPtr req);

    public:
        std::string& to_string();

        static ReplyMsgPtr getReply(RequestPtr req);
    };

    /// ���ʻ�ʵʱ�ɽ�Ӧ��
    class ReplyTimeTradeQryMsg : public ReplyMsg
    {
    protected:
        ReplyTimeTradeQryMsg();
        ReplyTimeTradeQryMsg(RequestPtr req);

    public:
        std::string& to_string();

        static ReplyMsgPtr getReply(RequestPtr req);
    };

    /// ϵͳ�ֲֲܳ�ѯӦ��
    class ReplySumPosiQryMsg : public ReplyMsg
    {
    protected:
        ReplySumPosiQryMsg();
        ReplySumPosiQryMsg(RequestPtr req);

    public:
        std::string& to_string();

        static ReplyMsgPtr getReply(RequestPtr req);
    };*/

    /// ʵʱԤ��֪ͨ��ѯӦ��
	class ReplyTimeWarnQryMsg : public ReplyMsg, public std::enable_shared_from_this<ReplyTimeWarnQryMsg>
    {
	public:
        ReplyTimeWarnQryMsg();
        ReplyTimeWarnQryMsg(RequestPtr req);


        std::string to_string();

		static ReplyTimeWarnQryMsgPtr getReply(RequestPtr req){
			return std::make_shared<ReplyTimeWarnQryMsg>(req);
		}

		AllTrade::LoginNameType			m_login_name;
		AllTrade::AccountNameType		m_acc_name;

		AllTrade::NPTradeCenter::ImmRiskControlPtr	m_contextPtr;
		bool                                        m_blast;
    };
    
    /// ���ʻ�������˲�ѯӦ��
    class ReplyEquipmentMoneyQryMsg : public ReplyMsg, public std::enable_shared_from_this<ReplyEquipmentMoneyQryMsg>
    {
    public:
        ReplyEquipmentMoneyQryMsg();
        ReplyEquipmentMoneyQryMsg(RequestPtr req);

        std::string to_string();

		static ReplyEquipmentMoneyQryMsgPtr getReply(RequestPtr req){
            return std::make_shared<ReplyEquipmentMoneyQryMsg>(req);
        }

        AllTrade::DateType                          m_start_day;
        AllTrade::DateType                          m_end_day;
        AllTrade::NPMgrCenter::TradeAccountPtr      m_rtn_acc;
        AllTrade::NPMgrCenter::SApplyMoneyPtr       m_money;        // ����ʽ�
        bool                                        m_blast;
    };
    /*
    /// ���ʻ�������˲�ѯӦ��
    class ReplyAutoOutMoneyQryMsg : public ReplyMsg
    {
    protected:
        ReplyAutoOutMoneyQryMsg();
        ReplyAutoOutMoneyQryMsg(RequestPtr req);

    public:
        std::string& to_string();

        static ReplyMsgPtr getReply(RequestPtr req);
    };
    */


    /// �������ò�ѯӦ��
    class ReplyFeeSetQryMsg : public ReplyMsg, public std::enable_shared_from_this<ReplyFeeSetQryMsg>
    {
    public:
        ReplyFeeSetQryMsg();
        ReplyFeeSetQryMsg(RequestPtr req);

        std::string to_string();

        static ReplyFeeSetQryMsgPtr getReply(RequestPtr req){
            return std::make_shared<ReplyFeeSetQryMsg>(req);
        }

        AllTrade::NPTradeCenter::TradeFeePtr    m_rtn_fee;
    };
    

    /// �����˻���ѯӦ��
    class ReplyManagerQryMsg : public ReplyMsg, public std::enable_shared_from_this<ReplyManagerQryMsg>
    {
    public:
        ReplyManagerQryMsg();
        ReplyManagerQryMsg(RequestPtr req);

        std::string to_string();

        static ReplyManagerQryMsgPtr getReply(RequestPtr req){
            return std::make_shared<ReplyManagerQryMsg>(req);
        }

        AllTrade::NPMgrCenter::ManagerAccountPtr    m_rtn_acc;
        AllTrade::LoginNameType                     m_parent_login_name;
        bool                                        m_blast;
    };


    /// ������������Ӧ��
    class ReplyAgencyAddMsg : public ReplyMsg, public std::enable_shared_from_this<ReplyAgencyAddMsg>
    {
    public:
        ReplyAgencyAddMsg();
        ReplyAgencyAddMsg(RequestPtr req);

        std::string to_string();

        static ReplyAgencyAddMsgPtr getReply(RequestPtr req){
            return std::make_shared<ReplyAgencyAddMsg>(req);
        }

        AllTrade::NPMgrCenter::AgencyAccountPtr     m_rtn_acc;
        AllTrade::NPMgrCenter::SMoneyInfoPtr        m_rtn_money;
        AllTrade::NPMgrCenter::SRiskInfoPtr         m_rtn_risk;
        AllTrade::LoginNameType      m_parent_login_name;
        AllTrade::LoginNameType      m_fund_login_name;
    };

    /// �����޸�Ӧ��
    class ReplyAgencyChangeMsg : public ReplyMsg, public std::enable_shared_from_this<ReplyAgencyChangeMsg>
    {
    public:
        ReplyAgencyChangeMsg();
        ReplyAgencyChangeMsg(RequestPtr req);

        std::string to_string();

        static ReplyAgencyChangeMsgPtr getReply(RequestPtr req){
            return std::make_shared<ReplyAgencyChangeMsg>(req);
        }

        AllTrade::NPMgrCenter::AgencyAccountPtr     m_rtn_acc;
        AllTrade::NPMgrCenter::SMoneyInfoPtr        m_rtn_money;
        AllTrade::NPMgrCenter::SRiskInfoPtr         m_rtn_risk;
        AllTrade::LoginNameType      m_parent_login_name;
        AllTrade::LoginNameType      m_fund_login_name;
    };

    /// �������Ӧ��
    class ReplyAgencyApprovalMsg : public ReplyMsg, public std::enable_shared_from_this<ReplyAgencyApprovalMsg>
    {
    public:
        ReplyAgencyApprovalMsg();
        ReplyAgencyApprovalMsg(RequestPtr req);

        std::string to_string();

        static ReplyAgencyApprovalMsgPtr getReply(RequestPtr req){
            return std::make_shared<ReplyAgencyApprovalMsg>(req);
        }

        AllTrade::LoginNameType   m_acc_login_name;
        AllTrade::NPMgrCenter::AgencyAccountPtr     m_rtn_acc;
        AllTrade::NPMgrCenter::SMoneyInfoPtr        m_rtn_money;
        AllTrade::NPMgrCenter::SRiskInfoPtr         m_rtn_risk;
        AllTrade::E_ACCOUNT_STATUS   m_bApproval;
        AllTrade::LoginNameType      m_parent_login_name;
        AllTrade::LoginNameType      m_fund_login_name;
    };
    
    /// ���ӽ�ɫӦ��
    class ReplyRolesAddMsg : public ReplyMsg, public std::enable_shared_from_this<ReplyRolesAddMsg>
    {
    public:
        ReplyRolesAddMsg();
        ReplyRolesAddMsg(RequestPtr req);

        std::string to_string();

		static ReplyRolesAddMsgPtr getReply(RequestPtr req){
			return std::make_shared<ReplyRolesAddMsg>(req);
		}

		AllTrade::AuthorityRolesPtr		m_rtn_arp;
    };

	/// �󶨹��ܽ�ɫ��ϵӦ��
    class ReplyBindRelationMsg : public ReplyMsg, public std::enable_shared_from_this<ReplyBindRelationMsg>
	{
    public:
        ReplyBindRelationMsg();
		ReplyBindRelationMsg(RequestPtr req);

		std::string to_string();

		static ReplyBindRelationMsgPtr getReply(RequestPtr req)
		{
			return std::make_shared<ReplyBindRelationMsg>(req);
		}

        std::vector<AllTrade::AuthorityRoleFunctionsPtr>	m_rtn_arfp;
		int							m_roleId;
	};

    /// �޸Ľ�ɫӦ��
	class ReplyRolesChangeMsg : public ReplyMsg, public std::enable_shared_from_this<ReplyRolesChangeMsg>
    {
    public:
        ReplyRolesChangeMsg();
        ReplyRolesChangeMsg(RequestPtr req);

        std::string to_string();

		static ReplyRolesChangeMsgPtr getReply(RequestPtr req)
		{
			return std::make_shared<ReplyRolesChangeMsg>(req);
		}

		AllTrade::AuthorityRolesPtr	m_rtn_arfp;
    };

    /// �����û�(����)��ɫ��ϵ����Ӧ��
	class ReplyUserRoleAddRelationMsg : public ReplyMsg, public std::enable_shared_from_this<ReplyUserRoleAddRelationMsg>
    {
    public:
        ReplyUserRoleAddRelationMsg();
        ReplyUserRoleAddRelationMsg(RequestPtr req);

        std::string to_string();

		static ReplyUserRoleAddRelationMsgPtr getReply(RequestPtr req)
		{
			return std::make_shared<ReplyUserRoleAddRelationMsg>(req);
		}

        AllTrade::AuthorityRoleUsersPtr		m_rtn_arup;
    };

    /// ���ʻ��Զ�����Ӧ��
    class ReplyChildAccAutoAddMsg : public ReplyMsg, public std::enable_shared_from_this<ReplyChildAccAutoAddMsg>
    {
    public:
        ReplyChildAccAutoAddMsg();
        ReplyChildAccAutoAddMsg(RequestPtr req);

        std::string to_string();

        static ReplyChildAccAutoAddMsgPtr getReply(RequestPtr req){
            return std::make_shared<ReplyChildAccAutoAddMsg>(req);
        }

        AllTrade::NPMgrCenter::TradeAccountPtr      m_rtn_acc;
        AllTrade::PopularizeLinkType                m_pop_link;

        AllTrade::NPMgrCenter::SMoneyInfoPtr        m_rtn_money;
        AllTrade::NPMgrCenter::SRiskInfoPtr         m_rtn_risk;
        AllTrade::LoginNameType      m_parent_login_name;
        AllTrade::LoginNameType      m_fund_login_name;

    };
    
    /// ���ʻ�����Ӧ��
    class ReplyChildAccAddMsg : public ReplyMsg, public std::enable_shared_from_this<ReplyChildAccAddMsg>
    {
    public:
        ReplyChildAccAddMsg();
        ReplyChildAccAddMsg(RequestPtr req);

        std::string to_string();

        static ReplyChildAccAddMsgPtr getReply(RequestPtr req){
            return std::make_shared<ReplyChildAccAddMsg>(req);
        }

        AllTrade::NPMgrCenter::TradeAccountPtr      m_rtn_acc;
        AllTrade::NPMgrCenter::SMoneyInfoPtr        m_rtn_money;
        AllTrade::NPMgrCenter::SRiskInfoPtr         m_rtn_risk;
        AllTrade::LoginNameType      m_parent_login_name;
        AllTrade::LoginNameType      m_fund_login_name;
    };

    /// ���ʻ��޸�Ӧ��
    class ReplyChildAccChangeMsg : public ReplyMsg, public std::enable_shared_from_this<ReplyChildAccChangeMsg>
    {
    public:
        ReplyChildAccChangeMsg();
        ReplyChildAccChangeMsg(RequestPtr req);

        std::string to_string();

        static ReplyChildAccChangeMsgPtr getReply(RequestPtr req){
            return std::make_shared<ReplyChildAccChangeMsg>(req);
        }

        AllTrade::NPMgrCenter::TradeAccountPtr      m_rtn_acc;
        AllTrade::NPMgrCenter::SMoneyInfoPtr        m_rtn_money;
        AllTrade::NPMgrCenter::SRiskInfoPtr         m_rtn_risk;
        AllTrade::LoginNameType      m_parent_login_name;
        AllTrade::LoginNameType      m_fund_login_name;
    };
    
    /// ���ʻ������Ӧ��
    class ReplyChildAccInmoneyMsg : public ReplyMsg, public std::enable_shared_from_this<ReplyChildAccInmoneyMsg>
    {
    public:
        ReplyChildAccInmoneyMsg();
        ReplyChildAccInmoneyMsg(RequestPtr req);

        std::string to_string();

        static ReplyChildAccInmoneyMsgPtr getReply(RequestPtr req){
            return std::make_shared<ReplyChildAccInmoneyMsg>(req);
        }

        AllTrade::LoginNameType       m_login_name;
        AllTrade::Money_Change_Type   m_money_change;
        YDouble                       m_money;
        AllTrade::RemarkTextType      m_remark;
    };
    
    /// ���ʻ����Ӧ��
    class ReplyChildAccApprovalMsg : public ReplyMsg, public std::enable_shared_from_this<ReplyChildAccApprovalMsg>
    {
    public:
        ReplyChildAccApprovalMsg();
        ReplyChildAccApprovalMsg(RequestPtr req);

        std::string to_string();

        static ReplyChildAccApprovalMsgPtr getReply(RequestPtr req){
            return std::make_shared<ReplyChildAccApprovalMsg>(req);
        }

        AllTrade::NPMgrCenter::TradeAccountPtr  m_rtn_acc;
        AllTrade::NPMgrCenter::SRiskInfoPtr     m_rtn_risk;
        AllTrade::NPMgrCenter::SMoneyInfoPtr    m_rtn_money;
        AllTrade::LoginNameType    m_rtn_parent_login_name;
        AllTrade::LoginNameType    m_rtn_fund_login_name;
        AllTrade::E_ACCOUNT_STATUS  m_bApproval;
		AllTrade::LoginNameType    m_opLoginName;
		AllTrade::LoginNameType    m_crLoginName;
    };
    
    /// �ʽ��˻�����Ӧ��
    class ReplyFundAccAddMsg : public ReplyMsg, public std::enable_shared_from_this<ReplyFundAccAddMsg>
    {
    public:
        ReplyFundAccAddMsg();
        ReplyFundAccAddMsg(RequestPtr req);

        std::string to_string();

        static ReplyFundAccAddMsgPtr getReply(RequestPtr req){
            return std::make_shared<ReplyFundAccAddMsg>(req);
        }

        AllTrade::NPMgrCenter::FunderAccountPtr     m_rtn_acc;
        AllTrade::NPMgrCenter::SMoneyInfoPtr        m_rtn_money;
        AllTrade::NPMgrCenter::SRiskInfoPtr         m_rtn_risk;
//         AllTrade::LoginNameType      m_parent_login_name;
    };

    /// �ʽ��˻��޸�Ӧ��
    class ReplyFundAccChangeMsg : public ReplyMsg, public std::enable_shared_from_this<ReplyFundAccChangeMsg>
    {
    public:
        ReplyFundAccChangeMsg();
        ReplyFundAccChangeMsg(RequestPtr req);

        std::string to_string();

        static ReplyFundAccChangeMsgPtr getReply(RequestPtr req){
            return std::make_shared<ReplyFundAccChangeMsg>(req);
        }

        AllTrade::NPMgrCenter::FunderAccountPtr     m_rtn_acc;
        AllTrade::NPMgrCenter::SMoneyInfoPtr        m_rtn_money;
        AllTrade::NPMgrCenter::SRiskInfoPtr         m_rtn_risk;
    };
    
    /// ��������Ӧ��
    class ReplyFeeSetMsg : public ReplyMsg, public std::enable_shared_from_this<ReplyFeeSetMsg>
    {
    public:
        ReplyFeeSetMsg();
        ReplyFeeSetMsg(RequestPtr req);

        std::string to_string();

        static ReplyFeeSetMsgPtr getReply(RequestPtr req){
            return std::make_shared<ReplyFeeSetMsg>(req);
        }

        AllTrade::NPTradeCenter::TradeFeePtr    m_trade_fee;
    };
    
    /// ��Ʊ����������Ӧ��
    class ReplyStockBlackSetMsg : public ReplyMsg, public std::enable_shared_from_this<ReplyStockBlackSetMsg>
    {
    public:
        ReplyStockBlackSetMsg();
        ReplyStockBlackSetMsg(RequestPtr req);

        std::string to_string();

        static ReplyStockBlackSetMsgPtr getReply(RequestPtr req){
            return std::make_shared<ReplyStockBlackSetMsg>(req);
        }

        AllTrade::ContractCodeType  m_contract_code;
        AllTrade::ContractNameType  m_contract_name;
        bool                        m_isBlack;
    };

    /// ��ֹ��������Ӧ��
    class ReplyForbidBuySellSetMsg : public ReplyMsg, public std::enable_shared_from_this<ReplyForbidBuySellSetMsg>
    {
    public:
        ReplyForbidBuySellSetMsg();
        ReplyForbidBuySellSetMsg(RequestPtr req);

        std::string to_string();

        static ReplyForbidBuySellSetMsgPtr getReply(RequestPtr req){
            return std::make_shared<ReplyForbidBuySellSetMsg>(req);
        }

        AllTrade::NPTradeCenter::SForbidTradePtr    forbid_trade;
    };

    /// �ֱֲ�������Ӧ��
    class ReplyPosiRateSetMsg : public ReplyMsg, public std::enable_shared_from_this<ReplyPosiRateSetMsg>
    {
    public:
        ReplyPosiRateSetMsg();
        ReplyPosiRateSetMsg(RequestPtr req);

        std::string to_string();

        static ReplyPosiRateSetMsgPtr getReply(RequestPtr req){
            return std::make_shared<ReplyPosiRateSetMsg>(req);
        }

        AllTrade::NPTradeCenter::SPositionRatePtr   posit_rate;
    };
    /*
    /// ���˻�������Ӧ��
    class ReplyChildInmoneyApprovalMsg : public ReplyMsg
    {
    protected:
        ReplyChildInmoneyApprovalMsg();
        ReplyChildInmoneyApprovalMsg(RequestPtr req);

    public:
        std::string& to_string();

        static ReplyMsgPtr getReply(RequestPtr req);
    };

    /// ���˻��������Ӧ��
    class ReplyChildOutmoneyApprovalMsg : public ReplyMsg
    {
    protected:
        ReplyChildOutmoneyApprovalMsg();
        ReplyChildOutmoneyApprovalMsg(RequestPtr req);

    public:
        std::string& to_string();

        static ReplyMsgPtr getReply(RequestPtr req);
    };
    */

    /// �����޸�Ӧ��
    class ReplyPswChangeMsg : public ReplyMsg, public std::enable_shared_from_this<ReplyPswChangeMsg>
    {
    public:
        ReplyPswChangeMsg();
        ReplyPswChangeMsg(RequestPtr req);

        std::string to_string();

        static ReplyPswChangeMsgPtr getReply(RequestPtr req){
            return std::make_shared<ReplyPswChangeMsg>(req);
        }
  
        AllTrade::LoginNameType                     m_LoginName;    // ���޸��ߵ�¼��
        AllTrade::LoginPasswordType                 m_old_pass;
        AllTrade::LoginPasswordType                 m_new_pass;
    };

    class ReplyManagerAddMsg : public ReplyMsg, public std::enable_shared_from_this<ReplyManagerAddMsg>
    {
    public:
        ReplyManagerAddMsg();
        ReplyManagerAddMsg(RequestPtr req);

        std::string to_string();

        static ReplyManagerAddMsgPtr getReply(RequestPtr req){
            return std::make_shared<ReplyManagerAddMsg>(req);
        }

        AllTrade::NPMgrCenter::ManagerAccountPtr    m_rtn_acc;
    };

    class ReplyManagerChangeMsg : public ReplyMsg, public std::enable_shared_from_this<ReplyManagerChangeMsg>
    {
    public:
        ReplyManagerChangeMsg();
        ReplyManagerChangeMsg(RequestPtr req);

        std::string to_string();

        static ReplyManagerChangeMsgPtr getReply(RequestPtr req){
            return std::make_shared<ReplyManagerChangeMsg>(req);
        }

        AllTrade::NPMgrCenter::ManagerAccountPtr    m_rtn_acc;
    };

    /// ��ƽ��Ӧ��
    class ReplyOpenCloseMsg : public ReplyMsg, public std::enable_shared_from_this<ReplyOpenCloseMsg>
    {
    public:
        ReplyOpenCloseMsg();
        ReplyOpenCloseMsg(RequestPtr req);

        std::string to_string();

        static ReplyOpenCloseMsgPtr getReply(RequestPtr req){
            return std::make_shared<ReplyOpenCloseMsg>(req);
        }

        AllTrade::NPTradeCenter::StockOrderPtr m_order_ptr;
        AllTrade::LoginNameType     m_orderLoginName;   // �µ��ߵ�¼��
        AllTrade::ContractCodeType  m_contract_code;
    };

    /// ����Ӧ��
    class ReplyCancelOrderMsg : public ReplyMsg, public std::enable_shared_from_this<ReplyCancelOrderMsg>
    {
    public:
        ReplyCancelOrderMsg();
        ReplyCancelOrderMsg(RequestPtr req);

        std::string to_string();

        static ReplyCancelOrderMsgPtr getReply(RequestPtr req){
            return std::make_shared<ReplyCancelOrderMsg>(req);
        }
  
        AllTrade::LoginNameType     m_orderLoginName;   // �µ��ߵ�¼��
        AllTrade::OrderStreamType   m_orderstream;
    };

    // ί�����������Ϣ
    class PushOrderMsg : public ReplyMsg, public std::enable_shared_from_this<PushOrderMsg>
    {
    public:
        PushOrderMsg();
        PushOrderMsg(AllTrade::ErrorCodeType rslt, const AllTrade::NPMgrCenter::SAccountPtr account, const std::string& command, const AllTrade::NPTradeCenter::OrderInfoPtr& order_ptr);

        std::string to_string();

        static PushOrderMsgPtr getReply(AllTrade::ErrorCodeType rslt, const AllTrade::NPMgrCenter::SAccountPtr account, const std::string& command, const AllTrade::NPTradeCenter::OrderInfoPtr& order_ptr){
            return std::make_shared<PushOrderMsg>(rslt, account, command, order_ptr);
        }

        AllTrade::NPTradeCenter::OrderInfoPtr   m_order_ptr;
        AllTrade::NPMgrCenter::SContractPtr     m_stock_ptr;
        AllTrade::NPMgrCenter::SAccountPtr      m_account;
        AllTrade::LoginNameType                 m_parent_login_name;
    };

    // �ɽ����������Ϣ
    class PushTradeMsg : public ReplyMsg, public std::enable_shared_from_this<PushTradeMsg>
    {
    public:
        PushTradeMsg();
        PushTradeMsg(AllTrade::ErrorCodeType rslt, const AllTrade::NPMgrCenter::SAccountPtr account, const std::string& command, const AllTrade::NPTradeCenter::StockTradePtr& trade_ptr);

        std::string to_string();

        static PushTradeMsgPtr getReply(AllTrade::ErrorCodeType rslt, const AllTrade::NPMgrCenter::SAccountPtr account, const std::string& command, const AllTrade::NPTradeCenter::StockTradePtr& trade_ptr){
            return std::make_shared<PushTradeMsg>(rslt, account, command, trade_ptr);
        }

        AllTrade::NPTradeCenter::StockTradePtr  m_trade_ptr;
        AllTrade::NPMgrCenter::SContractPtr     m_stock_ptr;
        AllTrade::NPMgrCenter::SAccountPtr      m_account;
        AllTrade::LoginNameType                 m_parent_login_name;
    };

    // �ֲ����������Ϣ
    class PushPositionMsg : public ReplyMsg, public std::enable_shared_from_this<PushPositionMsg>
    {
    public:
        PushPositionMsg();
        PushPositionMsg(AllTrade::ErrorCodeType rslt, const AllTrade::NPMgrCenter::SAccountPtr m_account, const std::string& command, const AllTrade::NPTradeCenter::PositionInfoPtr& position_ptr);

        std::string to_string();

        static PushPositionMsgPtr getReply(AllTrade::ErrorCodeType rslt, const AllTrade::NPMgrCenter::SAccountPtr account, const std::string& command, const AllTrade::NPTradeCenter::PositionInfoPtr& position_ptr){
            return std::make_shared<PushPositionMsg>(rslt, account, command, position_ptr);
        }

        AllTrade::NPTradeCenter::PositionInfoPtr    m_position_ptr;
        AllTrade::NPMgrCenter::SContractPtr         m_stock_ptr;
        AllTrade::NPMgrCenter::SAccountPtr          m_account;
        YDouble                                     m_currency_rate;
        AllTrade::LoginNameType                     m_parent_login_name;
    };

    // �ʽ����������Ϣ
    class PushMoneyMsg : public ReplyMsg, public std::enable_shared_from_this<PushMoneyMsg>
    {
    public:
        PushMoneyMsg();
        PushMoneyMsg(AllTrade::ErrorCodeType rslt, const AllTrade::NPMgrCenter::SAccountPtr account, const std::string& command
            , const AllTrade::NPMgrCenter::SMoneyInfoPtr& money_ptr);

        std::string to_string();

        static PushMoneyMsgPtr getReply(AllTrade::ErrorCodeType rslt, const AllTrade::NPMgrCenter::SAccountPtr account, const std::string& command
            , const AllTrade::NPMgrCenter::SMoneyInfoPtr& money_ptr){
            return std::make_shared<PushMoneyMsg>(rslt, account, command, money_ptr);
        }

        AllTrade::NPMgrCenter::SMoneyInfoPtr    m_money_ptr;
//         AllTrade::NPMgrCenter::SRiskInfoPtr     m_rtn_risk;
        AllTrade::NPMgrCenter::SAccountPtr      m_account;
        AllTrade::LoginNameType                 m_parent_login_name;
    };

    // ������������Ϣ
    class PushRiskControlMsg : public ReplyMsg, public std::enable_shared_from_this<PushRiskControlMsg>
    {
    public:
        PushRiskControlMsg();
        PushRiskControlMsg(AllTrade::ErrorCodeType rslt, const std::string& command);

        std::string to_string();


        static PushRiskControlMsgPtr getReply(AllTrade::ErrorCodeType rslt, const std::string& command){
            return std::make_shared<PushRiskControlMsg>(rslt, command);
        }

        AllTrade::NPMgrCenter::SAccountPtr      m_account;   // ������ߵ�¼��
        AllTrade::RiskControlType       m_rc_type;
        AllTrade::DateTimeType          m_date_time;
        AllTrade::RemarkTextType        m_remark_text;
    };


	/// ��½�������ܲ�ѯ
	class ReplySelfFunctionMsg : public ReplyMsg, public std::enable_shared_from_this<ReplySelfFunctionMsg>
	{
	public:
		ReplySelfFunctionMsg();
		ReplySelfFunctionMsg(RequestPtr req);

		std::string to_string();

		static ReplySelfFunctionMsgPtr getReply(RequestPtr req){
			return std::make_shared<ReplySelfFunctionMsg>(req);
		}

		std::vector<AllTrade::AuthorityFunctionsUserIdPtr> m_rtn_ptr;
	};

	/// ��ɫ���ܲ�ѯ
	class ReplyRoleFunctionMsg : public ReplyMsg, public std::enable_shared_from_this<ReplyRoleFunctionMsg>
	{
	public:
		ReplyRoleFunctionMsg();
		ReplyRoleFunctionMsg(RequestPtr req);

		std::string to_string();

		static ReplyRoleFunctionMsgPtr getReply(RequestPtr req){
			return std::make_shared<ReplyRoleFunctionMsg>(req);
		}

		std::vector<AllTrade::AuthorityRoleFunctionsPtr> m_rtn_ptr;
		int	m_roleId;
	};

	/// ��ɫɾ��
	class ReplyDelRoleMsg : public ReplyMsg, public std::enable_shared_from_this<ReplyDelRoleMsg>
	{
	public:
		ReplyDelRoleMsg();
		ReplyDelRoleMsg(RequestPtr req);

		std::string to_string();

		static ReplyDelRoleMsgPtr getReply(RequestPtr req){
			return std::make_shared<ReplyDelRoleMsg>(req);
		}

		int	m_roleId;
	};

	/// ��ɫ/�û�ɾ��
	class ReplyDelRoleUserMsg : public ReplyMsg, public std::enable_shared_from_this<ReplyDelRoleUserMsg>
	{
	public:
		ReplyDelRoleUserMsg();
		ReplyDelRoleUserMsg(RequestPtr req);

		std::string to_string();

		static ReplyDelRoleUserMsgPtr getReply(RequestPtr req){
			return std::make_shared<ReplyDelRoleUserMsg>(req);
		}

		AllTrade::AuthorityRoleUsersPtr		m_rtn_arup;
	};

	/// ��ѯ��ҵ��
	class ReplyGetAllBussnessMsg : public ReplyMsg, public std::enable_shared_from_this<ReplyGetAllBussnessMsg>
	{
	public:
		ReplyGetAllBussnessMsg();
		ReplyGetAllBussnessMsg(RequestPtr req);

		std::string to_string();

		static ReplyGetAllBussnessMsgPtr getReply(RequestPtr req){
			return std::make_shared<ReplyGetAllBussnessMsg>(req);
		}

		std::vector<AllTrade::AuthorityBussnessesPtr>		m_rtn_abp;
	};

    /// ��������
    class ReplyApplyEquipMoneyMsg : public ReplyMsg, public std::enable_shared_from_this<ReplyApplyEquipMoneyMsg>
    {
    public:
        ReplyApplyEquipMoneyMsg();
        ReplyApplyEquipMoneyMsg(RequestPtr req);

        std::string to_string();

        static ReplyApplyEquipMoneyMsgPtr getReply(RequestPtr req){
            return std::make_shared<ReplyApplyEquipMoneyMsg>(req);
        }

        YDouble				                m_appmoney;    //�����ʽ�
    };

    /// �����������
    class ReplyApprovalApplyEquipMoneyMsg : public ReplyMsg, public std::enable_shared_from_this<ReplyApprovalApplyEquipMoneyMsg>
    {
    public:
        ReplyApprovalApplyEquipMoneyMsg();
        ReplyApprovalApplyEquipMoneyMsg(RequestPtr req);

        std::string to_string();

        static ReplyApprovalApplyEquipMoneyMsgPtr getReply(RequestPtr req){
            return std::make_shared<ReplyApprovalApplyEquipMoneyMsg>(req);
        }

        AllTrade::ApplyMoneyIDType          m_apply_money_id;       //�����ʽ���ˮ��
        AllTrade::E_APPLY_MONEY_STATUS		m_apply_status;         //�����ʽ�״̬
    };

    /// ����ɾ��
    class ReplyAgencyDeleteMsg : public ReplyMsg, public std::enable_shared_from_this<ReplyAgencyDeleteMsg>
    {
    public:
        ReplyAgencyDeleteMsg();
        ReplyAgencyDeleteMsg(RequestPtr req);

        std::string to_string();

        static ReplyAgencyDeleteMsgPtr getReply(RequestPtr req){
            return std::make_shared<ReplyAgencyDeleteMsg>(req);
        }

        AllTrade::LoginNameType				m_login_name;           // ��ɾ���ߵ�¼��
    };

    /// ���˻�ɾ������
    class ReplyChildDeleteMsg : public ReplyMsg, public std::enable_shared_from_this<ReplyChildDeleteMsg>
    {
    public:
        ReplyChildDeleteMsg();
        ReplyChildDeleteMsg(RequestPtr req);

        std::string to_string();

        static ReplyChildDeleteMsgPtr getReply(RequestPtr req){
            return std::make_shared<ReplyChildDeleteMsg>(req);
        }

        AllTrade::LoginNameType				m_login_name;           // ��ɾ���ߵ�¼��
    };

    /// �ʽ��˻�ɾ������
    class ReplyFunderDeleteMsg : public ReplyMsg, public std::enable_shared_from_this<ReplyFunderDeleteMsg>
    {
    public:
        ReplyFunderDeleteMsg();
        ReplyFunderDeleteMsg(RequestPtr req);

        std::string to_string();

        static ReplyFunderDeleteMsgPtr getReply(RequestPtr req){
            return std::make_shared<ReplyFunderDeleteMsg>(req);
        }

        AllTrade::LoginNameType				m_login_name;           // ��ɾ���ߵ�¼��
    };

    /// ����Աɾ������
    class ReplyManagerDeleteMsg : public ReplyMsg, public std::enable_shared_from_this<ReplyManagerDeleteMsg>
    {
    public:
        ReplyManagerDeleteMsg();
        ReplyManagerDeleteMsg(RequestPtr req);

        std::string to_string();

        static ReplyManagerDeleteMsgPtr getReply(RequestPtr req){
            return std::make_shared<ReplyManagerDeleteMsg>(req);
        }

        AllTrade::LoginNameType				m_login_name;           // ��ɾ���ߵ�¼��
    };

    /// ��ѡ��Ʊ��ѯ����
    class ReplyGetCustomStockMsg : public ReplyMsg, public std::enable_shared_from_this<ReplyGetCustomStockMsg>
    {
    public:
        ReplyGetCustomStockMsg();
        ReplyGetCustomStockMsg(RequestPtr req);

        std::string to_string();

        static ReplyGetCustomStockMsgPtr getReply(RequestPtr req){
            return std::make_shared<ReplyGetCustomStockMsg>(req);
        }
   
        AllTrade::ExchangeCodeType                  m_exchange_code;
        AllTrade::NPMgrCenter::SStockContractPtr    m_stock_ptr;
        bool                                        m_blast;
    };

    /// ��ѡ��Ʊ��������
    class ReplyAddCustomStockMsg : public ReplyMsg, public std::enable_shared_from_this<ReplyAddCustomStockMsg>
    {
    public:
        ReplyAddCustomStockMsg();
        ReplyAddCustomStockMsg(RequestPtr req);

        std::string to_string();

        static ReplyAddCustomStockMsgPtr getReply(RequestPtr req){
            return std::make_shared<ReplyAddCustomStockMsg>(req);
        }

        AllTrade::ExchangeCodeType                  m_exchange_code;
        AllTrade::ContractCodeType				    m_contract_code;
        AllTrade::NPMgrCenter::SStockContractPtr    m_stock_ptr;
    };

    /// ��ѡ��Ʊɾ������
    class ReplyDelCustomStockMsg : public ReplyMsg, public std::enable_shared_from_this<ReplyDelCustomStockMsg>
    {
    public:
        ReplyDelCustomStockMsg();
        ReplyDelCustomStockMsg(RequestPtr req);

        std::string to_string();

        static ReplyDelCustomStockMsgPtr getReply(RequestPtr req){
            return std::make_shared<ReplyDelCustomStockMsg>(req);
        }

        AllTrade::ExchangeCodeType                  m_exchange_code;
        AllTrade::ContractCodeType				    m_contract_code;
        AllTrade::NPMgrCenter::SStockContractPtr    m_stock_ptr;
    };


	/// ��ɫ/�û��޸�
	class ReplyChangeRoleUserMsg : public ReplyMsg, public std::enable_shared_from_this<ReplyChangeRoleUserMsg>
	{
	public:
		ReplyChangeRoleUserMsg();
		ReplyChangeRoleUserMsg(RequestPtr req);

		std::string to_string();

		static ReplyChangeRoleUserMsgPtr getReply(RequestPtr req){
			return std::make_shared<ReplyChangeRoleUserMsg>(req);
		}

		AllTrade::AuthorityRoleUsersPtr		m_rtn_arup;
	};

    /// ���˻��Զ������˲�ѯ
    class ReplyAutoInMoneyQryMsg : public ReplyMsg, public std::enable_shared_from_this<ReplyAutoInMoneyQryMsg>
    {
    public:
        ReplyAutoInMoneyQryMsg();
        ReplyAutoInMoneyQryMsg(RequestPtr req);

        std::string to_string();

        static ReplyAutoInMoneyQryMsgPtr getReply(RequestPtr req){
            return std::make_shared<ReplyAutoInMoneyQryMsg>(req);
        }

        AllTrade::DateType                          m_start_day;
        AllTrade::DateType                          m_end_day;
        AllTrade::NPMgrCenter::TradeAccountPtr      m_rtn_acc;
        AllTrade::NPMgrCenter::SApplyMoneyPtr       m_money;        // ����ʽ�
        bool                                        m_blast;
    };

    /// �������˻��Զ����
    class ReplyAutoInMoneyMsg : public ReplyMsg, public std::enable_shared_from_this<ReplyAutoInMoneyMsg>
    {
    public:
        ReplyAutoInMoneyMsg();
        ReplyAutoInMoneyMsg(RequestPtr req);

        std::string to_string();

        static ReplyAutoInMoneyMsgPtr getReply(RequestPtr req){
            return std::make_shared<ReplyAutoInMoneyMsg>(req);
        }

        YDouble				                m_appmoney;    //�����ʽ�
        AllTrade::LoginNameType             m_login_name;   // ��¼�� 
    };

    /// ����Զ��������
    class ReplyAutoInMoneyApprovalMsg : public ReplyMsg, public std::enable_shared_from_this<ReplyAutoInMoneyApprovalMsg>
    {
    public:
        ReplyAutoInMoneyApprovalMsg();
        ReplyAutoInMoneyApprovalMsg(RequestPtr req);

        std::string to_string();

        static ReplyAutoInMoneyApprovalMsgPtr getReply(RequestPtr req){
            return std::make_shared<ReplyAutoInMoneyApprovalMsg>(req);
        }

        AllTrade::ApplyMoneyIDType          m_apply_money_id;       //�����ʽ���ˮ��
        AllTrade::E_APPLY_MONEY_STATUS		m_apply_status;         //�����ʽ�״̬
    };

    /// ���˻��Զ�������˲�ѯ
    class ReplyAutoOutMoneyQryMsg : public ReplyMsg, public std::enable_shared_from_this<ReplyAutoOutMoneyQryMsg>
    {
    public:
        ReplyAutoOutMoneyQryMsg();
        ReplyAutoOutMoneyQryMsg(RequestPtr req);

        std::string to_string();

        static ReplyAutoOutMoneyQryMsgPtr getReply(RequestPtr req){
            return std::make_shared<ReplyAutoOutMoneyQryMsg>(req);
        }

        AllTrade::DateType                          m_start_day;
        AllTrade::DateType                          m_end_day;
        AllTrade::NPMgrCenter::TradeAccountPtr      m_rtn_acc;
        AllTrade::NPMgrCenter::SApplyMoneyPtr       m_money;        // ����ʽ�
        bool                                        m_blast;
    };

    /// �������˻��Զ�����
    class ReplyAutoOutMoneyMsg : public ReplyMsg, public std::enable_shared_from_this<ReplyAutoOutMoneyMsg>
    {
    public:
        ReplyAutoOutMoneyMsg();
        ReplyAutoOutMoneyMsg(RequestPtr req);

        std::string to_string();

        static ReplyAutoOutMoneyMsgPtr getReply(RequestPtr req){
            return std::make_shared<ReplyAutoOutMoneyMsg>(req);
        }

        YDouble				            m_appmoney;         //�����ʽ�
        AllTrade::RealNameType          m_real_name;         // ��ʵ����
        AllTrade::BankNameType          m_bank_name;         // ������
        AllTrade::BankCardNoType        m_bank_card;         // ���п���
    };

    /// ����Զ���������
    class ReplyAutoOutMoneyApprovalMsg : public ReplyMsg, public std::enable_shared_from_this<ReplyAutoOutMoneyApprovalMsg>
    {
    public:
        ReplyAutoOutMoneyApprovalMsg();
        ReplyAutoOutMoneyApprovalMsg(RequestPtr req);

        std::string to_string();

        static ReplyAutoOutMoneyApprovalMsgPtr getReply(RequestPtr req){
            return std::make_shared<ReplyAutoOutMoneyApprovalMsg>(req);
        }

        AllTrade::ApplyMoneyIDType          m_apply_money_id;       //�����ʽ���ˮ��
        AllTrade::E_APPLY_MONEY_STATUS		m_apply_status;         //�����ʽ�״̬
    };

	/// �����ʷ����
	class ReplyRiskHistoryMsg : public ReplyMsg, public std::enable_shared_from_this<ReplyRiskHistoryMsg>
	{
	public:
		ReplyRiskHistoryMsg();
		ReplyRiskHistoryMsg(RequestPtr req);

		std::string to_string();

		static ReplyRiskHistoryMsgPtr getReply(RequestPtr req){
			return std::make_shared<ReplyRiskHistoryMsg>(req);
		}

		AllTrade::DateType              m_start_day;
		AllTrade::DateType              m_end_day;
		AllTrade::LoginNameType			m_login_name;
		AllTrade::AccountNameType		m_acc_name;
		
		AllTrade::NPTradeCenter::ImmRiskControlPtr	m_contextPtr;
		bool                            m_blast;
	};


	/// ������ȯ����
	class ReplySetMarginMsg : public ReplyMsg, public std::enable_shared_from_this<ReplySetMarginMsg>
	{
	public:
		ReplySetMarginMsg();
		ReplySetMarginMsg(RequestPtr req);

		std::string to_string();

		static ReplySetMarginMsgPtr getReply(RequestPtr req){
			return std::make_shared<ReplySetMarginMsg>(req);
		}

		AllTrade::LoginNameType						m_login_name;
		AllTrade::NPTradeCenter::MarginInfoPtr		m_margin_set_;
		bool                            m_blast;
	};

	/// ��ȯʣ����������
	class ReplyMarginLeftQtyMsg : public ReplyMsg, public std::enable_shared_from_this<ReplyMarginLeftQtyMsg>
	{
	public:
		ReplyMarginLeftQtyMsg();
		ReplyMarginLeftQtyMsg(RequestPtr req);

		std::string to_string();

		static ReplyMarginLeftQtyMsgPtr getReply(RequestPtr req){
			return std::make_shared<ReplyMarginLeftQtyMsg>(req);
		}

		AllTrade::LoginNameType						m_login_name;
		AllTrade::NPTradeCenter::MarginLeftInfoPtr		m_margin_left_;
		bool                            m_blast;
	};


	/// ��ȯ�����ѯ����
	class ReplyMarginManagerQtyMsg : public ReplyMsg, public std::enable_shared_from_this<ReplyMarginManagerQtyMsg>
	{
	public:
		ReplyMarginManagerQtyMsg();
		ReplyMarginManagerQtyMsg(RequestPtr req);

		std::string to_string();

		static ReplyMarginManagerQtyMsgPtr getReply(RequestPtr req){
			return std::make_shared<ReplyMarginManagerQtyMsg>(req);
		}

		AllTrade::LoginNameType						m_login_name;
		AllTrade::NPTradeCenter::MarginInfoPtr		m_margin_set_;
		bool                            m_blast;
	};

	/// ��ȯ��ծ��ѯ����
	class ReplyMarginLiabilitiesQtyMsg : public ReplyMsg, public std::enable_shared_from_this<ReplyMarginLiabilitiesQtyMsg>
	{
	public:
		ReplyMarginLiabilitiesQtyMsg();
		ReplyMarginLiabilitiesQtyMsg(RequestPtr req);

		std::string to_string();

		static ReplyMarginLiabilitiesQtyMsgPtr getReply(RequestPtr req){
			return std::make_shared<ReplyMarginLiabilitiesQtyMsg>(req);
		}

		AllTrade::LoginNameType						m_login_name;
		AllTrade::NPTradeCenter::MarginPositionInfoPtr		m_margin_posi_;
		bool                            m_blast;
	};

	/// ��Ϣͳ�Ʋ�ѯ����
	class ReplyInterestStatisticsMsg : public ReplyMsg, public std::enable_shared_from_this<ReplyInterestStatisticsMsg>
	{
	public:
		ReplyInterestStatisticsMsg();
		ReplyInterestStatisticsMsg(RequestPtr req);

		std::string to_string();

		static ReplyInterestStatisticsMsgPtr getReply(RequestPtr req){
			return std::make_shared<ReplyInterestStatisticsMsg>(req);
		}

		AllTrade::LoginNameType			m_login_name;
		AllTrade::NPMgrCenter::InterestStatisticsPtr			m_ptr_;
		bool                            m_blast;
	};

	/// ��Ϣ��ϸ��ѯ����
	class ReplyInterestDetailMsg : public ReplyMsg, public std::enable_shared_from_this<ReplyInterestDetailMsg>
	{
	public:
		ReplyInterestDetailMsg();
		ReplyInterestDetailMsg(RequestPtr req);

		std::string to_string();

		static ReplyInterestDetailMsgPtr getReply(RequestPtr req){
			return std::make_shared<ReplyInterestDetailMsg>(req);
		}

		AllTrade::LoginNameType			m_login_name;
		AllTrade::AccountNameType		m_acount_name;
		AllTrade::NPMgrCenter::InterestDetailPtr			m_ptr_;
		bool                            m_blast;
	};

	/// ��ǰί����ȯ��ѯ����
	class ReplyCurrentMarginEntrustMsg : public ReplyMsg, public std::enable_shared_from_this<ReplyCurrentMarginEntrustMsg>
	{
	public:
		ReplyCurrentMarginEntrustMsg();
		ReplyCurrentMarginEntrustMsg(RequestPtr req);

		std::string to_string();

		static ReplyCurrentMarginEntrustMsgPtr getReply(RequestPtr req){
			return std::make_shared<ReplyCurrentMarginEntrustMsg>(req);
		}

		AllTrade::LoginNameType                     m_parent_login_name;
		AllTrade::NPTradeCenter::StockOrderPtr      m_order_ptr;
		AllTrade::NPMgrCenter::SContractPtr         m_stock_ptr;
		AllTrade::NPMgrCenter::TradeAccountPtr      m_rtn_acc;
		bool                                        m_blast;
	};

	/// �ɽ���ѯӦ��
	class ReplyCurrentMarginTradeQryMsg : public ReplyMsg, public std::enable_shared_from_this<ReplyCurrentMarginTradeQryMsg>
	{
	public:
		ReplyCurrentMarginTradeQryMsg();
		ReplyCurrentMarginTradeQryMsg(RequestPtr req);

		std::string to_string();

		static ReplyCurrentMarginTradeQryMsgPtr getReply(RequestPtr req){
			return std::make_shared<ReplyCurrentMarginTradeQryMsg>(req);
		}

		AllTrade::LoginNameType                     m_parent_login_name;
		AllTrade::NPTradeCenter::StockTradePtr      m_trade_ptr;
		AllTrade::NPMgrCenter::SContractPtr         m_stock_ptr;
		AllTrade::NPMgrCenter::TradeAccountPtr      m_rtn_acc;
		bool                                        m_blast;
	};

} // namespace xyc_communication

#endif // __PCA_REPLY_MSG_H__
