#ifndef  __COMM_MESSAGE_H__
#define  __COMM_MESSAGE_H__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif

#if defined(_MSC_VER) && (_MSC_VER < 1700)
#error "编译器版本必须是VS2012或以上!"
#endif

#include <loki/Visitor.h>		// 使用了Loki中的cyclic visitor模板
#include <loki/TypelistMacros.h>
#include <loki/Functor.h>
#include <loki/AssocVector.h>

#include <memory>
#include <atomic>
#include <exception>
#include <map>
#include <tuple>
#include "RequestMsgDefine.h"
#include "define/protocol_error.h"
#include "define/net_illustrate.h"//命令码
#include "commmsg_declare.h"

namespace xyc_communication
{
	//////////////////////////////////////////////////////////////////////////
	// 通讯消息基类定义；用于封装请求消息。
	class CommMsgBase : public std::enable_shared_from_this<CommMsgBase>
	{
    protected:
		CommMsgBase();
        CommMsgBase(E_COMM_MSG_TYPE type);
        CommMsgBase(RequestPtr request);
        CommMsgBase(E_COMM_MSG_TYPE type, RequestPtr request);
		virtual ~CommMsgBase();

    public:
		virtual void Accept(CommVisitor& ) {}

		// 静态成员初始化和反初始化
		static bool initialize();
		static void unInitialize();

		// 由"Request"创建具体的消息对象
        static std::tuple<CommMsgPtr, AllTrade::ErrorCodeType> create(RequestPtr request);

        // 根据命令码获取命令类型
        static E_COMM_MSG_TYPE getTypeFromCmd(const std::string& cmd);

    public:
        // 获取请求字段结构对象
		RequestPtr getRequest() const { return request_; }
        E_COMM_MSG_TYPE getType() const { return type_; }
        int getSocketID() const {
            if (request_)
                return request_->socketDescriptor_;
            return 0;
        }

	protected:
		RequestPtr		request_;
        E_COMM_MSG_TYPE type_;

		static TypeToMsgMap        _sTypeToMsg;     // 消息类型到消息创建函数的映射
		static CmdTypeMap          _sCmdTypeMap;    // 命令码<-->命令类型
	};

	//////////////////////////////////////////////////////////////////////////
	// 派生类－－请求消息类定义

	/*
	* 登录消息
	*/
    class CommMsgLogin : public CommMsgBase
	{
	public:
        CommMsgLogin() : CommMsgBase(LOGIN_TRADE_REQ) {}
        CommMsgLogin(RequestPtr req) : CommMsgBase(LOGIN_TRADE_REQ, req) {
			assert( req && !req->parameters_.empty() );
		}

		// 消息接收方(本程序)用以构造一个对象
        static CommMsgLoginPtr createFromReq(RequestPtr req)
		{
			return std::make_shared<CommMsgLogin>(req);
		}

		LOKI_DEFINE_CYCLIC_VISITABLE(CommVisitor);
	};

	/*
	* 登出消息
	*/
    class CommMsgLogout : public CommMsgBase
	{
	public:
        CommMsgLogout() : CommMsgBase(LOGIN_OUT_REQ) {}
        CommMsgLogout(RequestPtr req) : CommMsgBase(LOGIN_OUT_REQ, req) {
			assert( req );
		}

		// 消息接收方(本程序)用以构造一个对象
        static CommMsgLogoutPtr createFromReq(RequestPtr req)
		{
            return std::make_shared<CommMsgLogout>(req);
		}

		LOKI_DEFINE_CYCLIC_VISITABLE(CommVisitor);
	};

	/*
	* 心跳消息
	*/
    class CommMsgHeartBeat : public CommMsgBase
	{
	public:
        CommMsgHeartBeat() : CommMsgBase(HEART_BEAT_MSG) {}
        CommMsgHeartBeat(RequestPtr req) : CommMsgBase(HEART_BEAT_MSG, req) {
			assert( req );
		}

		// 消息接收方(本程序)用以构造一个对象
        static CommMsgHeartBeatPtr createFromReq(RequestPtr req)
		{
            return std::make_shared<CommMsgHeartBeat>(req);
		}

		LOKI_DEFINE_CYCLIC_VISITABLE(CommVisitor);
	};

    /*
    * 机构查询请求消息
    */
    class CommMsgAgencyQry : public CommMsgBase
    {
    public:
        CommMsgAgencyQry() : CommMsgBase(INSTITUTION_REQ) {}
        CommMsgAgencyQry(RequestPtr req) : CommMsgBase(INSTITUTION_REQ, req) {
            assert(req && !req->parameters_.empty());
        }

        // 消息接收方(本程序)用以构造一个对象
        static CommMsgAgencyQryPtr createFromReq(RequestPtr req)
        {
            return std::make_shared<CommMsgAgencyQry>(req);
        }

        LOKI_DEFINE_CYCLIC_VISITABLE(CommVisitor);
    };

    /*
    * 待审核机构查询请求
    */
    class CommMsgAgencyPreApprovalQry : public CommMsgBase
    {
    public:
        CommMsgAgencyPreApprovalQry() : CommMsgBase(INSTITUTION_PREAPPROVAL_REQ) {}
        CommMsgAgencyPreApprovalQry(RequestPtr req) : CommMsgBase(INSTITUTION_PREAPPROVAL_REQ, req) {
            assert(req && !req->parameters_.empty());
        }

        // 消息接收方(本程序)用以构造一个对象
        static CommMsgAgencyPreApprovalQryPtr createFromReq(RequestPtr req)
        {
            return std::make_shared<CommMsgAgencyPreApprovalQry>(req);
        }

        LOKI_DEFINE_CYCLIC_VISITABLE(CommVisitor);
    };

    /*
    * 机构推广查询请求
    */
    class CommMsgAgencyLinkQry : public CommMsgBase
    {
    public:
        CommMsgAgencyLinkQry() : CommMsgBase(INSTITUTION_LINK_REQ) {}
        CommMsgAgencyLinkQry(RequestPtr req) : CommMsgBase(INSTITUTION_LINK_REQ, req) {
            assert(req && !req->parameters_.empty());
        }

        // 消息接收方(本程序)用以构造一个对象
        static CommMsgAgencyLinkQryPtr createFromReq(RequestPtr req)
        {
            return std::make_shared<CommMsgAgencyLinkQry>(req);
        }

        LOKI_DEFINE_CYCLIC_VISITABLE(CommVisitor);
    };

    /*
    * 角色查询请求
    */
    class CommMsgRolesQry : public CommMsgBase
    {
    public:
        CommMsgRolesQry() : CommMsgBase(ROLES_QUERY_REQ) {}
        CommMsgRolesQry(RequestPtr req) : CommMsgBase(ROLES_QUERY_REQ, req) {
            assert(req && !req->parameters_.empty());
        }

        // 消息接收方(本程序)用以构造一个对象
        static CommMsgRolesQryPtr createFromReq(RequestPtr req)
        {
            return std::make_shared<CommMsgRolesQry>(req);
        }

        LOKI_DEFINE_CYCLIC_VISITABLE(CommVisitor);
    };

    /*
    * 机构（用户）角色关系查询请求
    */
    class CommMsgAgencyRolesQry : public CommMsgBase
    {
    public:
        CommMsgAgencyRolesQry() : CommMsgBase(INSTITUTIONUSER_ROLE_RELATION_REQ) {}
        CommMsgAgencyRolesQry(RequestPtr req) : CommMsgBase(INSTITUTIONUSER_ROLE_RELATION_REQ, req) {
            assert(req && !req->parameters_.empty());
        }

        // 消息接收方(本程序)用以构造一个对象
        static CommMsgAgencyRolesQryPtr createFromReq(RequestPtr req)
        {
            return std::make_shared<CommMsgAgencyRolesQry>(req);
        }

        LOKI_DEFINE_CYCLIC_VISITABLE(CommVisitor);
    };

    /*
    * 佣金查询请求
    */
    class CommMsgCommissQry : public CommMsgBase
    {
    public:
        CommMsgCommissQry() : CommMsgBase(COMMISSION_QUERY_REQ) {}
        CommMsgCommissQry(RequestPtr req) : CommMsgBase(COMMISSION_QUERY_REQ, req) {
            assert(req && !req->parameters_.empty());
        }

        // 消息接收方(本程序)用以构造一个对象
        static CommMsgCommissQryPtr createFromReq(RequestPtr req)
        {
            return std::make_shared<CommMsgCommissQry>(req);
        }

        LOKI_DEFINE_CYCLIC_VISITABLE(CommVisitor);
    };

    /*
    * 佣金明细查询请求
    */
    class CommMsgCommissDtlQry : public CommMsgBase
    {
    public:
        CommMsgCommissDtlQry() : CommMsgBase(COMMISSION_DETAIL_REQ) {}
        CommMsgCommissDtlQry(RequestPtr req) : CommMsgBase(COMMISSION_DETAIL_REQ, req) {
            assert(req && !req->parameters_.empty());
        }

        // 消息接收方(本程序)用以构造一个对象
        static CommMsgCommissDtlQryPtr createFromReq(RequestPtr req)
        {
            return std::make_shared<CommMsgCommissDtlQry>(req);
        }

        LOKI_DEFINE_CYCLIC_VISITABLE(CommVisitor);
    };

    /*
    * 分成查询请求
    */
    class CommMsgProfitCommisslQry : public CommMsgBase
    {
    public:
        CommMsgProfitCommisslQry() : CommMsgBase(PROFITCOMMISSION_QUERY_REQ) {}
        CommMsgProfitCommisslQry(RequestPtr req) : CommMsgBase(PROFITCOMMISSION_QUERY_REQ, req) {
            assert(req && !req->parameters_.empty());
        }

        // 消息接收方(本程序)用以构造一个对象
        static CommMsgProfitCommisslQryPtr createFromReq(RequestPtr req)
        {
            return std::make_shared<CommMsgProfitCommisslQry>(req);
        }

        LOKI_DEFINE_CYCLIC_VISITABLE(CommVisitor);
    };

    /*
    * 分成明细查询请求
    */
    class CommMsgProfitCommissDtlQry : public CommMsgBase
    {
    public:
        CommMsgProfitCommissDtlQry() : CommMsgBase(PROFITCOMMISSION_DETAIL_REQ) {}
        CommMsgProfitCommissDtlQry(RequestPtr req) : CommMsgBase(PROFITCOMMISSION_DETAIL_REQ, req) {
            assert(req && !req->parameters_.empty());
        }

        // 消息接收方(本程序)用以构造一个对象
        static CommMsgProfitCommissDtlQryPtr createFromReq(RequestPtr req)
        {
            return std::make_shared<CommMsgProfitCommissDtlQry>(req);
        }

        LOKI_DEFINE_CYCLIC_VISITABLE(CommVisitor);
    };

    /*
    * 拓扑树查询请求
    */
    class CommMsgToplogicalTreeQry : public CommMsgBase
    {
    public:
        CommMsgToplogicalTreeQry() : CommMsgBase(TOPOLOGICAL_TREE_REQ) {}
        CommMsgToplogicalTreeQry(RequestPtr req) : CommMsgBase(TOPOLOGICAL_TREE_REQ, req) {
            assert(req && !req->parameters_.empty());
        }

        // 消息接收方(本程序)用以构造一个对象
        static CommMsgToplogicalTreeQryPtr createFromReq(RequestPtr req)
        {
            return std::make_shared<CommMsgToplogicalTreeQry>(req);
        }

        LOKI_DEFINE_CYCLIC_VISITABLE(CommVisitor);
    };

    /*
    * 子账户查询请求
    */
    class CommMsgChildAccQry : public CommMsgBase
    {
    public:
        CommMsgChildAccQry() : CommMsgBase(CHILD_QUERY_REQ) {}
        CommMsgChildAccQry(RequestPtr req) : CommMsgBase(CHILD_QUERY_REQ, req) {
            assert(req && !req->parameters_.empty());
        }

        // 消息接收方(本程序)用以构造一个对象
        static CommMsgChildAccQryPtr createFromReq(RequestPtr req)
        {
            return std::make_shared<CommMsgChildAccQry>(req);
        }

        LOKI_DEFINE_CYCLIC_VISITABLE(CommVisitor);
    };

    /*
    * 子账户审核查询请求
    */
    class CommMsgChildApprovalQry : public CommMsgBase
    {
    public:
        CommMsgChildApprovalQry() : CommMsgBase(CHILD_APPROVAL_REQ) {}
        CommMsgChildApprovalQry(RequestPtr req) : CommMsgBase(CHILD_APPROVAL_REQ, req) {
            assert(req && !req->parameters_.empty());
        }

        // 消息接收方(本程序)用以构造一个对象
        static CommMsgChildApprovalQryPtr createFromReq(RequestPtr req)
        {
            return std::make_shared<CommMsgChildApprovalQry>(req);
        }

        LOKI_DEFINE_CYCLIC_VISITABLE(CommVisitor);
    };

    /*
    * 资金账户查询请求
    */
    class CommMsgFundAccQry : public CommMsgBase
    {
    public:
        CommMsgFundAccQry() : CommMsgBase(FUNDACC_QUERY_REQ) {}
        CommMsgFundAccQry(RequestPtr req) : CommMsgBase(FUNDACC_QUERY_REQ, req) {
            assert(req && !req->parameters_.empty());
        }

        // 消息接收方(本程序)用以构造一个对象
        static CommMsgFundAccQryPtr createFromReq(RequestPtr req)
        {
            return std::make_shared<CommMsgFundAccQry>(req);
        }

        LOKI_DEFINE_CYCLIC_VISITABLE(CommVisitor);
    };

    /*
    * 在线用户查询请求
    */
    class CommMsgOnlineAccQry : public CommMsgBase
    {
    public:
        CommMsgOnlineAccQry() : CommMsgBase(ONLINE_USER_REQ) {}
        CommMsgOnlineAccQry(RequestPtr req) : CommMsgBase(ONLINE_USER_REQ, req) {
            assert(req && !req->parameters_.empty());
        }

        // 消息接收方(本程序)用以构造一个对象
        static CommMsgOnlineAccQryPtr createFromReq(RequestPtr req)
        {
            return std::make_shared<CommMsgOnlineAccQry>(req);
        }

        LOKI_DEFINE_CYCLIC_VISITABLE(CommVisitor);
    };

    /*
    * 股票合约查询请求
    */
    class CommMsgStockContractQry : public CommMsgBase
    {
    public:
        CommMsgStockContractQry() : CommMsgBase(STOCK_CONTRACT_QUERY_REQ) {}
        CommMsgStockContractQry(RequestPtr req) : CommMsgBase(STOCK_CONTRACT_QUERY_REQ, req) {
            assert(req && !req->parameters_.empty());
        }

        // 消息接收方(本程序)用以构造一个对象
        static CommMsgStockContractQryPtr createFromReq(RequestPtr req)
        {
            return std::make_shared<CommMsgStockContractQry>(req);
        }

        LOKI_DEFINE_CYCLIC_VISITABLE(CommVisitor);
    }; 

    /*
    * 股票黑名单查询请求
    */
    class CommMsgStockBlackQry : public CommMsgBase
    {
    public:
        CommMsgStockBlackQry() : CommMsgBase(STOCK_INSTRUMENT_QUERY_REQ) {}
        CommMsgStockBlackQry(RequestPtr req) : CommMsgBase(STOCK_INSTRUMENT_QUERY_REQ, req) {
            assert(req && !req->parameters_.empty());
        }

        // 消息接收方(本程序)用以构造一个对象
        static CommMsgStockBlackQryPtr createFromReq(RequestPtr req)
        {
            return std::make_shared<CommMsgStockBlackQry>(req);
        }

        LOKI_DEFINE_CYCLIC_VISITABLE(CommVisitor);
    };

    /*
    * 禁止买卖查询请求
    */
    class CommMsgForbidBuySellQry : public CommMsgBase
    {
    public:
        CommMsgForbidBuySellQry() : CommMsgBase(FORBID_BUY_SELL_QUERY_REQ) {}
        CommMsgForbidBuySellQry(RequestPtr req) : CommMsgBase(FORBID_BUY_SELL_QUERY_REQ, req) {
            assert(req && !req->parameters_.empty());
        }

        // 消息接收方(本程序)用以构造一个对象
        static CommMsgForbidBuySellQryPtr createFromReq(RequestPtr req)
        {
            return std::make_shared<CommMsgForbidBuySellQry>(req);
        }

        LOKI_DEFINE_CYCLIC_VISITABLE(CommVisitor);
    };

    /*
    * 持仓比例设置查询请求
    */
    class CommMsgPosiRateQry : public CommMsgBase
    {
    public:
        CommMsgPosiRateQry() : CommMsgBase(POSI_RATE_QUERY_REQ) {}
        CommMsgPosiRateQry(RequestPtr req) : CommMsgBase(POSI_RATE_QUERY_REQ, req) {
            assert(req && !req->parameters_.empty());
        }

        // 消息接收方(本程序)用以构造一个对象
        static CommMsgPosiRateQryPtr createFromReq(RequestPtr req)
        {
            return std::make_shared<CommMsgPosiRateQry>(req);
        }

        LOKI_DEFINE_CYCLIC_VISITABLE(CommVisitor);
    };

    /*
    * 持仓查询请求
    */
    class CommMsgPosiQry : public CommMsgBase
    {
    public:
        CommMsgPosiQry() : CommMsgBase(POSI_QUERY_REQ) {}
        CommMsgPosiQry(RequestPtr req) : CommMsgBase(POSI_QUERY_REQ, req) {
            assert(req && !req->parameters_.empty());
        }

        // 消息接收方(本程序)用以构造一个对象
        static CommMsgPosiQryPtr createFromReq(RequestPtr req)
        {
            return std::make_shared<CommMsgPosiQry>(req);
        }

        LOKI_DEFINE_CYCLIC_VISITABLE(CommVisitor);
    };

    /*
    * 当前委托查询请求
    */
    class CommMsgCurrentyEntrustQry : public CommMsgBase
    {
    public:
        CommMsgCurrentyEntrustQry() : CommMsgBase(CURRENTENTRUST_QUERY_REQ) {}
        CommMsgCurrentyEntrustQry(RequestPtr req) : CommMsgBase(CURRENTENTRUST_QUERY_REQ, req) {
            assert(req && !req->parameters_.empty());
        }

        // 消息接收方(本程序)用以构造一个对象
        static CommMsgCurrentyEntrustQryPtr createFromReq(RequestPtr req)
        {
            return std::make_shared<CommMsgCurrentyEntrustQry>(req);
        }

        LOKI_DEFINE_CYCLIC_VISITABLE(CommVisitor);
    };

    /*
    * 当日委托查询请求
    */
    class CommMsgTodayEntrustQry : public CommMsgBase
    {
    public:
        CommMsgTodayEntrustQry() : CommMsgBase(TODAYENTRUST_QUERY_REQ) {}
        CommMsgTodayEntrustQry(RequestPtr req) : CommMsgBase(TODAYENTRUST_QUERY_REQ, req) {
            assert(req && !req->parameters_.empty());
        }

        // 消息接收方(本程序)用以构造一个对象
        static CommMsgTodayEntrustQryPtr createFromReq(RequestPtr req)
        {
            return std::make_shared<CommMsgTodayEntrustQry>(req);
        }

        LOKI_DEFINE_CYCLIC_VISITABLE(CommVisitor);
    };

    /*
    * 历史委托查询请求
    */
    class CommMsgHistoryEntrustQry : public CommMsgBase
    {
    public:
        CommMsgHistoryEntrustQry() : CommMsgBase(HISTORYENTRUST_QUERY_REQ) {}
        CommMsgHistoryEntrustQry(RequestPtr req) : CommMsgBase(HISTORYENTRUST_QUERY_REQ, req) {
            assert(req && !req->parameters_.empty());
        }

        // 消息接收方(本程序)用以构造一个对象
        static CommMsgHistoryEntrustQryPtr createFromReq(RequestPtr req)
        {
            return std::make_shared<CommMsgHistoryEntrustQry>(req);
        }

        LOKI_DEFINE_CYCLIC_VISITABLE(CommVisitor);
    };

    /*
    * 成交查询请求
    */
    class CommMsgTradeQry : public CommMsgBase
    {
    public:
        CommMsgTradeQry() : CommMsgBase(TRADE_QUERY_REQ) {}
        CommMsgTradeQry(RequestPtr req) : CommMsgBase(TRADE_QUERY_REQ, req) {
            assert(req && !req->parameters_.empty());
        }

        // 消息接收方(本程序)用以构造一个对象
        static CommMsgTradeQryPtr createFromReq(RequestPtr req)
        {
            return std::make_shared<CommMsgTradeQry>(req);
        }

        LOKI_DEFINE_CYCLIC_VISITABLE(CommVisitor);
    };

    /*
    * 历史成交查询请求
    */
    class CommMsgHistoryTradeQry : public CommMsgBase
    {
    public:
        CommMsgHistoryTradeQry() : CommMsgBase(HISTORYTRADE_QUERY_REQ) {}
        CommMsgHistoryTradeQry(RequestPtr req) : CommMsgBase(HISTORYTRADE_QUERY_REQ, req) {
            assert(req && !req->parameters_.empty());
        }

        // 消息接收方(本程序)用以构造一个对象
        static CommMsgHistoryTradeQryPtr createFromReq(RequestPtr req)
        {
            return std::make_shared<CommMsgHistoryTradeQry>(req);
        }

        LOKI_DEFINE_CYCLIC_VISITABLE(CommVisitor);
    };

    /*
    * 资金查询请求
    */
    class CommMsgFundQry : public CommMsgBase
    {
    public:
        CommMsgFundQry() : CommMsgBase(FUND_QUERY_REQ) {}
        CommMsgFundQry(RequestPtr req) : CommMsgBase(FUND_QUERY_REQ, req) {
            assert(req && !req->parameters_.empty());
        }

        // 消息接收方(本程序)用以构造一个对象
        static CommMsgFundQryPtr createFromReq(RequestPtr req)
        {
            return std::make_shared<CommMsgFundQry>(req);
        }

        LOKI_DEFINE_CYCLIC_VISITABLE(CommVisitor);
    };

    /*
    * 资金流水查询请求
    */
    class CommMsgFundSerialQry : public CommMsgBase
    {
    public:
        CommMsgFundSerialQry() : CommMsgBase(FUND_SERIAL_QUERY_REQ) {}
        CommMsgFundSerialQry(RequestPtr req) : CommMsgBase(FUND_SERIAL_QUERY_REQ, req) {
            assert(req && !req->parameters_.empty());
        }

        // 消息接收方(本程序)用以构造一个对象
        static CommMsgFundSerialQryPtr createFromReq(RequestPtr req)
        {
            return std::make_shared<CommMsgFundSerialQry>(req);
        }

        LOKI_DEFINE_CYCLIC_VISITABLE(CommVisitor);
    };

    /*
    * 交割查询请求
    */
    class CommMsgDeliveryQry : public CommMsgBase
    {
    public:
        CommMsgDeliveryQry() : CommMsgBase(DELIVERY_QUERY_REQ) {}
        CommMsgDeliveryQry(RequestPtr req) : CommMsgBase(DELIVERY_QUERY_REQ, req) {
            assert(req && !req->parameters_.empty());
        }

        // 消息接收方(本程序)用以构造一个对象
        static CommMsgDeliveryQryPtr createFromReq(RequestPtr req)
        {
            return std::make_shared<CommMsgDeliveryQry>(req);
        }

        LOKI_DEFINE_CYCLIC_VISITABLE(CommVisitor);
    };

    /*
    * 子帐户实时资金监控查询请求
    */
    class CommMsgFundMonitQry : public CommMsgBase
    {
    public:
        CommMsgFundMonitQry() : CommMsgBase(CHILD_FUNDMONITIOR_QUERY_REQ) {}
        CommMsgFundMonitQry(RequestPtr req) : CommMsgBase(CHILD_FUNDMONITIOR_QUERY_REQ, req) {
            assert(req && !req->parameters_.empty());
        }

        // 消息接收方(本程序)用以构造一个对象
        static CommMsgFundMonitQryPtr createFromReq(RequestPtr req)
        {
            return std::make_shared<CommMsgFundMonitQry>(req);
        }

        LOKI_DEFINE_CYCLIC_VISITABLE(CommVisitor);
    };

    /*
    * 子帐户实时成交请求
    */
//     class CommMsgTimeTradeQry : public CommMsgBase
//     {
//     public:
//         CommMsgTimeTradeQry() : CommMsgBase(CHILD_TIMETRADE_QUERY_REQ) {}
//         CommMsgTimeTradeQry(RequestPtr req) : CommMsgBase(CHILD_TIMETRADE_QUERY_REQ, req) {
//             assert(req && !req->parameters_.empty());
//         }
// 
//         // 消息接收方(本程序)用以构造一个对象
//         static CommMsgTimeTradeQryPtr createFromReq(RequestPtr req)
//         {
//             return std::make_shared<CommMsgTimeTradeQry>(req);
//         }
// 
//         LOKI_DEFINE_CYCLIC_VISITABLE(CommVisitor);
//     };

    /*
    * 系统总持仓查询请求
    */
    class CommMsgSumPosiQry : public CommMsgBase
    {
    public:
        CommMsgSumPosiQry() : CommMsgBase(CHILD_SUMPOSITION_QUERY_REQ) {}
        CommMsgSumPosiQry(RequestPtr req) : CommMsgBase(CHILD_SUMPOSITION_QUERY_REQ, req) {
            assert(req && !req->parameters_.empty());
        }

        // 消息接收方(本程序)用以构造一个对象
        static CommMsgSumPosiQryPtr createFromReq(RequestPtr req)
        {
            return std::make_shared<CommMsgSumPosiQry>(req);
        }

        LOKI_DEFINE_CYCLIC_VISITABLE(CommVisitor);
    };

    /*
    * 实时预警通知查询请求
    */
    class CommMsgTimeWarnQry : public CommMsgBase
    {
    public:
        CommMsgTimeWarnQry() : CommMsgBase(CHILD_TIMEWARN_NOTIFY_QUERY_REQ) {}
        CommMsgTimeWarnQry(RequestPtr req) : CommMsgBase(CHILD_TIMEWARN_NOTIFY_QUERY_REQ, req) {
            assert(req && !req->parameters_.empty());
        }

        // 消息接收方(本程序)用以构造一个对象
        static CommMsgTimeWarnQryPtr createFromReq(RequestPtr req)
        {
            return std::make_shared<CommMsgTimeWarnQry>(req);
        }

        LOKI_DEFINE_CYCLIC_VISITABLE(CommVisitor);
    };

    /*
    * 子帐户融资审核查询请求
    */
    class CommMsgEquipMoneyQry : public CommMsgBase
    {
    public:
        CommMsgEquipMoneyQry() : CommMsgBase(CHILD_EQUIPMENTMONEY_QUERY_REQ) {}
        CommMsgEquipMoneyQry(RequestPtr req) : CommMsgBase(CHILD_EQUIPMENTMONEY_QUERY_REQ, req) {
            assert(req && !req->parameters_.empty());
        }

        // 消息接收方(本程序)用以构造一个对象
        static CommMsgEquipMoneyQryPtr createFromReq(RequestPtr req)
        {
            return std::make_shared<CommMsgEquipMoneyQry>(req);
        }

        LOKI_DEFINE_CYCLIC_VISITABLE(CommVisitor);
    };

    /*
    * 子帐户出金审核查询请求
    */
    class CommMsgAutoOutMoneyQry : public CommMsgBase
    {
    public:
        CommMsgAutoOutMoneyQry() : CommMsgBase(CHILD_AUTOOUTMONEY_QUERY_REQ) {}
        CommMsgAutoOutMoneyQry(RequestPtr req) : CommMsgBase(CHILD_AUTOOUTMONEY_QUERY_REQ, req) {
            assert(req && !req->parameters_.empty());
        }

        // 消息接收方(本程序)用以构造一个对象
        static CommMsgAutoOutMoneyQryPtr createFromReq(RequestPtr req)
        {
            return std::make_shared<CommMsgAutoOutMoneyQry>(req);
        }

        LOKI_DEFINE_CYCLIC_VISITABLE(CommVisitor);
    };

    /*
    * 费用设置查询请求
    */
    class CommMsgFeeSetQry : public CommMsgBase
    {
    public:
        CommMsgFeeSetQry() : CommMsgBase(FEE_MANAGER_QUERY_REQ) {}
        CommMsgFeeSetQry(RequestPtr req) : CommMsgBase(FEE_MANAGER_QUERY_REQ, req) {
            assert(req && !req->parameters_.empty());
        }

        // 消息接收方(本程序)用以构造一个对象
        static CommMsgFeeSetQryPtr createFromReq(RequestPtr req)
        {
            return std::make_shared<CommMsgFeeSetQry>(req);
        }

        LOKI_DEFINE_CYCLIC_VISITABLE(CommVisitor);
    };

    /*
    * 管理账户查询请求
    */
    class CommMsgManagerQry : public CommMsgBase
    {
    public:
        CommMsgManagerQry() : CommMsgBase(MANAGER_QUERY_REQ) {}
        CommMsgManagerQry(RequestPtr req) : CommMsgBase(MANAGER_QUERY_REQ, req) {
            assert(req && !req->parameters_.empty());
        }

        // 消息接收方(本程序)用以构造一个对象
        static CommMsgManagerQryPtr createFromReq(RequestPtr req)
        {
            return std::make_shared<CommMsgManagerQry>(req);
        }

        LOKI_DEFINE_CYCLIC_VISITABLE(CommVisitor);
    };

    /*
    * 机构增加请求请求
    */
    class CommMsgAgencyAdd : public CommMsgBase
    {
    public:
        CommMsgAgencyAdd() : CommMsgBase(INSTITUTION_ADD_REQ) {}
        CommMsgAgencyAdd(RequestPtr req) : CommMsgBase(INSTITUTION_ADD_REQ, req) {
            assert(req && !req->parameters_.empty());
        }

        // 消息接收方(本程序)用以构造一个对象
        static CommMsgAgencyAddPtr createFromReq(RequestPtr req)
        {
            return std::make_shared<CommMsgAgencyAdd>(req);
        }

        LOKI_DEFINE_CYCLIC_VISITABLE(CommVisitor);
    };

    /*
    * 机构修改请求
    */
    class CommMsgAgencyChange : public CommMsgBase
    {
    public:
        CommMsgAgencyChange() : CommMsgBase(INSTITUTION_CHANGE_REQ) {}
        CommMsgAgencyChange(RequestPtr req) : CommMsgBase(INSTITUTION_CHANGE_REQ, req) {
            assert(req && !req->parameters_.empty());
        }

        // 消息接收方(本程序)用以构造一个对象
        static CommMsgAgencyChangePtr createFromReq(RequestPtr req)
        {
            return std::make_shared<CommMsgAgencyChange>(req);
        }

        LOKI_DEFINE_CYCLIC_VISITABLE(CommVisitor);
    };

    /*
    * 机构审核请求
    */
    class CommMsgAgencyApproval : public CommMsgBase
    {
    public:
        CommMsgAgencyApproval() : CommMsgBase(INSTITUTION_APPROVAL_REQ) {}
        CommMsgAgencyApproval(RequestPtr req) : CommMsgBase(INSTITUTION_APPROVAL_REQ, req) {
            assert(req && !req->parameters_.empty());
        }

        // 消息接收方(本程序)用以构造一个对象
        static CommMsgAgencyApprovalPtr createFromReq(RequestPtr req)
        {
            return std::make_shared<CommMsgAgencyApproval>(req);
        }

        LOKI_DEFINE_CYCLIC_VISITABLE(CommVisitor);
    };

    /*
    * 增加角色请求
    */
    class CommMsgRolesAdd : public CommMsgBase
    {
    public:
        CommMsgRolesAdd() : CommMsgBase(ROLES_ADD_REQ) {}
        CommMsgRolesAdd(RequestPtr req) : CommMsgBase(ROLES_ADD_REQ, req) {
            assert(req && !req->parameters_.empty());
        }

        // 消息接收方(本程序)用以构造一个对象
        static CommMsgRolesAddPtr createFromReq(RequestPtr req)
        {
            return std::make_shared<CommMsgRolesAdd>(req);
        }

        LOKI_DEFINE_CYCLIC_VISITABLE(CommVisitor);
    };

    /*
    * 修改角色请求
    */
    class CommMsgRolesChange : public CommMsgBase
    {
    public:
        CommMsgRolesChange() : CommMsgBase(ROLES_CHANGE_REQ) {}
        CommMsgRolesChange(RequestPtr req) : CommMsgBase(ROLES_CHANGE_REQ, req) {
            assert(req && !req->parameters_.empty());
        }

        // 消息接收方(本程序)用以构造一个对象
        static CommMsgRolesChangePtr createFromReq(RequestPtr req)
        {
            return std::make_shared<CommMsgRolesChange>(req);
        }

        LOKI_DEFINE_CYCLIC_VISITABLE(CommVisitor);
    };

    /*
    * 绑定功能角色关系请求
    */
    class CommMsgBindRelation : public CommMsgBase
    {
    public:
        CommMsgBindRelation() : CommMsgBase(BIND_FUNCTION_ROLE_RELATIUON_REQ) {}
        CommMsgBindRelation(RequestPtr req) : CommMsgBase(BIND_FUNCTION_ROLE_RELATIUON_REQ, req) {
            assert(req && !req->parameters_.empty());
        }

        // 消息接收方(本程序)用以构造一个对象
        static CommMsgBindRelationPtr createFromReq(RequestPtr req)
        {
            return std::make_shared<CommMsgBindRelation>(req);
        }

        LOKI_DEFINE_CYCLIC_VISITABLE(CommVisitor);
    };

    /*
    * 增加用户(机构)角色关系请求请求
    */
    class CommMsgUserRoleAddRelation : public CommMsgBase
    {
    public:
        CommMsgUserRoleAddRelation() : CommMsgBase(USERROLE_ADDRELATION_REQ) {}
        CommMsgUserRoleAddRelation(RequestPtr req) : CommMsgBase(USERROLE_ADDRELATION_REQ, req) {
            assert(req && !req->parameters_.empty());
        }

        // 消息接收方(本程序)用以构造一个对象
        static CommMsgUserRoleAddRelationPtr createFromReq(RequestPtr req)
        {
            return std::make_shared<CommMsgUserRoleAddRelation>(req);
        }

        LOKI_DEFINE_CYCLIC_VISITABLE(CommVisitor);
    };

    /*
    * 子帐户增加请求
    */
    class CommMsgChildAccAdd : public CommMsgBase
    {
    public:
        CommMsgChildAccAdd() : CommMsgBase(CHILDUSER_ADD_REQ) {}
        CommMsgChildAccAdd(RequestPtr req) : CommMsgBase(CHILDUSER_ADD_REQ, req) {
            assert(req && !req->parameters_.empty());
        }

        // 消息接收方(本程序)用以构造一个对象
        static CommMsgChildAccAddPtr createFromReq(RequestPtr req)
        {
            return std::make_shared<CommMsgChildAccAdd>(req);
        }

        LOKI_DEFINE_CYCLIC_VISITABLE(CommVisitor);
    };

    /*
    * 子帐户修改请求
    */
    class CommMsgChildAccChange : public CommMsgBase
    {
    public:
        CommMsgChildAccChange() : CommMsgBase(CHILDUSER_CHANGE_REQ) {}
        CommMsgChildAccChange(RequestPtr req) : CommMsgBase(CHILDUSER_CHANGE_REQ, req) {
            assert(req && !req->parameters_.empty());
        }

        // 消息接收方(本程序)用以构造一个对象
        static CommMsgChildAccChangePtr createFromReq(RequestPtr req)
        {
            return std::make_shared<CommMsgChildAccChange>(req);
        }

        LOKI_DEFINE_CYCLIC_VISITABLE(CommVisitor);
    };

    /*
    * 子帐户出入金请求
    */
    class CommMsgChildAccInmoney : public CommMsgBase
    {
    public:
        CommMsgChildAccInmoney() : CommMsgBase(CHILDUSER_INOUTMONEY_REQ) {}
        CommMsgChildAccInmoney(RequestPtr req) : CommMsgBase(CHILDUSER_INOUTMONEY_REQ, req) {
            assert(req && !req->parameters_.empty());
        }

        // 消息接收方(本程序)用以构造一个对象
        static CommMsgChildAccInmoneyPtr createFromReq(RequestPtr req)
        {
            return std::make_shared<CommMsgChildAccInmoney>(req);
        }

        LOKI_DEFINE_CYCLIC_VISITABLE(CommVisitor);
    };

    /*
    * 子帐户审核请求
    */
    class CommMsgChildAccApproval : public CommMsgBase
    {
    public:
        CommMsgChildAccApproval() : CommMsgBase(CHILDUSER_APPROVAL_REQ) {}
        CommMsgChildAccApproval(RequestPtr req) : CommMsgBase(CHILDUSER_APPROVAL_REQ, req) {
            assert(req && !req->parameters_.empty());
        }

        // 消息接收方(本程序)用以构造一个对象
        static CommMsgChildAccApprovalPtr createFromReq(RequestPtr req)
        {
            return std::make_shared<CommMsgChildAccApproval>(req);
        }

        LOKI_DEFINE_CYCLIC_VISITABLE(CommVisitor);
    };

    /*
    * 资金账户增加请求
    */
    class CommMsgFundAccAdd : public CommMsgBase
    {
    public:
        CommMsgFundAccAdd() : CommMsgBase(FUNDUSER_ADD_REQ) {}
        CommMsgFundAccAdd(RequestPtr req) : CommMsgBase(FUNDUSER_ADD_REQ, req) {
            assert(req && !req->parameters_.empty());
        }

        // 消息接收方(本程序)用以构造一个对象
        static CommMsgFundAccAddPtr createFromReq(RequestPtr req)
        {
            return std::make_shared<CommMsgFundAccAdd>(req);
        }

        LOKI_DEFINE_CYCLIC_VISITABLE(CommVisitor);
    };

    /*
    * 资金账户修改请求
    */
    class CommMsgFundAccChange : public CommMsgBase
    {
    public:
        CommMsgFundAccChange() : CommMsgBase(FUNDUSER_CHANGE_REQ) {}
        CommMsgFundAccChange(RequestPtr req) : CommMsgBase(FUNDUSER_CHANGE_REQ, req) {
            assert(req && !req->parameters_.empty());
        }

        // 消息接收方(本程序)用以构造一个对象
        static CommMsgFundAccChangePtr createFromReq(RequestPtr req)
        {
            return std::make_shared<CommMsgFundAccChange>(req);
        }

        LOKI_DEFINE_CYCLIC_VISITABLE(CommVisitor);
    };

    /*
    * 费用设置请求
    */
    class CommMsgFeeSet : public CommMsgBase
    {
    public:
        CommMsgFeeSet() : CommMsgBase(FEE_SET_REQ) {}
        CommMsgFeeSet(RequestPtr req) : CommMsgBase(FEE_SET_REQ, req) {
            assert(req && !req->parameters_.empty());
        }

        // 消息接收方(本程序)用以构造一个对象
        static CommMsgFeeSetPtr createFromReq(RequestPtr req)
        {
            return std::make_shared<CommMsgFeeSet>(req);
        }

        LOKI_DEFINE_CYCLIC_VISITABLE(CommVisitor);
    };

    /*
    * 股票黑名单设置请求
    */
    class CommMsgStockBlackSet : public CommMsgBase
    {
    public:
        CommMsgStockBlackSet() : CommMsgBase(STOCK_INSTRUMENTBLACK_SET_REQ) {}
        CommMsgStockBlackSet(RequestPtr req) : CommMsgBase(STOCK_INSTRUMENTBLACK_SET_REQ, req) {
            assert(req && !req->parameters_.empty());
        }

        // 消息接收方(本程序)用以构造一个对象
        static CommMsgStockBlackSetPtr createFromReq(RequestPtr req)
        {
            return std::make_shared<CommMsgStockBlackSet>(req);
        }

        LOKI_DEFINE_CYCLIC_VISITABLE(CommVisitor);
    };

    /*
    * 禁止买卖设置请求
    */
    class CommMsgForbidBuySellSet : public CommMsgBase
    {
    public:
        CommMsgForbidBuySellSet() : CommMsgBase(FORBID_BUY_SELL_SET_REQ) {}
        CommMsgForbidBuySellSet(RequestPtr req) : CommMsgBase(FORBID_BUY_SELL_SET_REQ, req) {
            assert(req && !req->parameters_.empty());
        }

        // 消息接收方(本程序)用以构造一个对象
        static CommMsgForbidBuySellSetPtr createFromReq(RequestPtr req)
        {
            return std::make_shared<CommMsgForbidBuySellSet>(req);
        }

        LOKI_DEFINE_CYCLIC_VISITABLE(CommVisitor);
    };

    /*
    * 持仓比例设置请求
    */
    class CommMsgPosiRateSet : public CommMsgBase
    {
    public:
        CommMsgPosiRateSet() : CommMsgBase(POSI_RATE_SET_REQ) {}
        CommMsgPosiRateSet(RequestPtr req) : CommMsgBase(POSI_RATE_SET_REQ, req) {
            assert(req && !req->parameters_.empty());
        }

        // 消息接收方(本程序)用以构造一个对象
        static CommMsgPosiRateSetPtr createFromReq(RequestPtr req)
        {
            return std::make_shared<CommMsgPosiRateSet>(req);
        }

        LOKI_DEFINE_CYCLIC_VISITABLE(CommVisitor);
    };

    /*
    * 子账户入金审核请求
    */
    class CommMsgAutoInMoneyApproval : public CommMsgBase
    {
    public:
        CommMsgAutoInMoneyApproval() : CommMsgBase(CHILDUSER_AUTOINMONEY_APPROVAL_REQ) {}
        CommMsgAutoInMoneyApproval(RequestPtr req) : CommMsgBase(CHILDUSER_AUTOINMONEY_APPROVAL_REQ, req) {
            assert(req && !req->parameters_.empty());
        }

        // 消息接收方(本程序)用以构造一个对象
        static CommMsgAutoInMoneyApprovalPtr createFromReq(RequestPtr req)
        {
            return std::make_shared<CommMsgAutoInMoneyApproval>(req);
        }

        LOKI_DEFINE_CYCLIC_VISITABLE(CommVisitor);
    };

    /*
    * 子账户出金审核请求
    */
    class CommMsgAutoOutMoneyApproval : public CommMsgBase
    {
    public:
        CommMsgAutoOutMoneyApproval() : CommMsgBase(CHILDUSER_AUTOOUTMONEY_APPROVAL_REQ) {}
        CommMsgAutoOutMoneyApproval(RequestPtr req) : CommMsgBase(CHILDUSER_AUTOOUTMONEY_APPROVAL_REQ, req) {
            assert(req && !req->parameters_.empty());
        }

        // 消息接收方(本程序)用以构造一个对象
        static CommMsgAutoOutMoneyApprovalPtr createFromReq(RequestPtr req)
        {
            return std::make_shared<CommMsgAutoOutMoneyApproval>(req);
        }

        LOKI_DEFINE_CYCLIC_VISITABLE(CommVisitor);
    };

    /*
    * 密码修改请求
    */
    class CommMsgPswChange : public CommMsgBase
    {
    public:
        CommMsgPswChange() : CommMsgBase(PASSWORD_CHANGE_REQ) {}
        CommMsgPswChange(RequestPtr req) : CommMsgBase(PASSWORD_CHANGE_REQ, req) {
            assert(req && !req->parameters_.empty());
        }

        // 消息接收方(本程序)用以构造一个对象
        static CommMsgPswChangePtr createFromReq(RequestPtr req)
        {
            return std::make_shared<CommMsgPswChange>(req);
        }

        LOKI_DEFINE_CYCLIC_VISITABLE(CommVisitor);
    };

    /*
    * 管理员增加请求
    */
    class CommMsgManagerAdd : public CommMsgBase
    {
    public:
        CommMsgManagerAdd() : CommMsgBase(MANAGER_ADD_REQ) {}
        CommMsgManagerAdd(RequestPtr req) : CommMsgBase(MANAGER_ADD_REQ, req) {
            assert(req && !req->parameters_.empty());
        }

        // 消息接收方(本程序)用以构造一个对象
        static CommMsgManagerAddPtr createFromReq(RequestPtr req)
        {
            return std::make_shared<CommMsgManagerAdd>(req);
        }

        LOKI_DEFINE_CYCLIC_VISITABLE(CommVisitor);
    };

    /*
    * 管理员修改请求
    */
    class CommMsgManagerChange : public CommMsgBase
    {
    public:
        CommMsgManagerChange() : CommMsgBase(MANAGER_CHANGE_REQ) {}
        CommMsgManagerChange(RequestPtr req) : CommMsgBase(MANAGER_CHANGE_REQ, req) {
            assert(req && !req->parameters_.empty());
        }

        // 消息接收方(本程序)用以构造一个对象
        static CommMsgManagerChangePtr createFromReq(RequestPtr req)
        {
            return std::make_shared<CommMsgManagerChange>(req);
        }

        LOKI_DEFINE_CYCLIC_VISITABLE(CommVisitor);
    };

    /*
    * 开平仓请求
    */
    class CommMsgOpenClose : public CommMsgBase
    {
    public:
        CommMsgOpenClose() : CommMsgBase(OPENCLOSE_REQ) {}
        CommMsgOpenClose(RequestPtr req) : CommMsgBase(OPENCLOSE_REQ, req) {
            assert(req && !req->parameters_.empty());
        }

        // 消息接收方(本程序)用以构造一个对象
        static CommMsgOpenClosePtr createFromReq(RequestPtr req)
        {
            return std::make_shared<CommMsgOpenClose>(req);
        }

        LOKI_DEFINE_CYCLIC_VISITABLE(CommVisitor);
    };

    /*
    * 撤单请求
    */
    class CommMsgCancelOrder : public CommMsgBase
    {
    public:
        CommMsgCancelOrder() : CommMsgBase(CANCELORDER_REQ) {}
        CommMsgCancelOrder(RequestPtr req) : CommMsgBase(CANCELORDER_REQ, req) {
            assert(req && !req->parameters_.empty());
        }

        // 消息接收方(本程序)用以构造一个对象
        static CommMsgCancelOrderPtr createFromReq(RequestPtr req)
        {
            return std::make_shared<CommMsgCancelOrder>(req);
        }

        LOKI_DEFINE_CYCLIC_VISITABLE(CommVisitor);
    };

	/*
	* 登陆者自身功能查询请求
	*/
	class CommMsgSelfFunctionQry : public CommMsgBase
	{
	public:
		CommMsgSelfFunctionQry() : CommMsgBase(SELFFUNCTION_QUERY_REQ) {}
        CommMsgSelfFunctionQry(RequestPtr req) : CommMsgBase(SELFFUNCTION_QUERY_REQ, req) {
			assert(req && !req->parameters_.empty());
		}

		// 消息接收方(本程序)用以构造一个对象
		static CommMsgSelfFunctionQryPtr createFromReq(RequestPtr req)
		{
			return std::make_shared<CommMsgSelfFunctionQry>(req);
		}

		LOKI_DEFINE_CYCLIC_VISITABLE(CommVisitor);
	};

	/*
	* 角色功能查询请求
	*/
	class CommMsgRoleFunctionQry : public CommMsgBase
	{
	public:
		CommMsgRoleFunctionQry() : CommMsgBase(ROLEFUNCTION_QUERY_REQ) {}
        CommMsgRoleFunctionQry(RequestPtr req) : CommMsgBase(ROLEFUNCTION_QUERY_REQ, req) {
			assert(req && !req->parameters_.empty());
		}

		// 消息接收方(本程序)用以构造一个对象
		static CommMsgRoleFunctionQryPtr createFromReq(RequestPtr req)
		{
			return std::make_shared<CommMsgRoleFunctionQry>(req);
		}

		LOKI_DEFINE_CYCLIC_VISITABLE(CommVisitor);
	};

	/*
	* 删除角色请求
	*/
	class CommMsgDelRole : public CommMsgBase
	{
	public:
		CommMsgDelRole() : CommMsgBase(ROLES_DEL_REQ) {}
        CommMsgDelRole(RequestPtr req) : CommMsgBase(ROLES_DEL_REQ, req) {
			assert(req && !req->parameters_.empty());
		}

		// 消息接收方(本程序)用以构造一个对象
		static CommMsgDelRolePtr createFromReq(RequestPtr req)
		{
			return std::make_shared<CommMsgDelRole>(req);
		}

		LOKI_DEFINE_CYCLIC_VISITABLE(CommVisitor);
	};

	/*
	* 删除角色/用户请求
	*/
	class CommMsgDelRoleUser : public CommMsgBase
	{
	public:
		CommMsgDelRoleUser() : CommMsgBase(ROLES_USER_DEL_REQ) {}
        CommMsgDelRoleUser(RequestPtr req) : CommMsgBase(ROLES_USER_DEL_REQ, req) {
			assert(req && !req->parameters_.empty());
		}

		// 消息接收方(本程序)用以构造一个对象
		static CommMsgDelRoleUserPtr createFromReq(RequestPtr req)
		{
			return std::make_shared<CommMsgDelRoleUser>(req);
		}

		LOKI_DEFINE_CYCLIC_VISITABLE(CommVisitor);
	};

	/*
	* 查询所有业务
	*/
	class CommMsgGetAllBussnessUser : public CommMsgBase
	{
	public:
        CommMsgGetAllBussnessUser() : CommMsgBase(BUSSNESS_QUERY_REQ) {}
        CommMsgGetAllBussnessUser(RequestPtr req) : CommMsgBase(BUSSNESS_QUERY_REQ, req) {
			assert(req && !req->parameters_.empty());
		}

		// 消息接收方(本程序)用以构造一个对象
		static CommMsgGetAllBussnessUserPtr createFromReq(RequestPtr req)
		{
			return std::make_shared<CommMsgGetAllBussnessUser>(req);
		}

		LOKI_DEFINE_CYCLIC_VISITABLE(CommVisitor);
	};

    /*
    * 申请融资资金请求
    */
    class CommMsgApplyEquipMoney : public CommMsgBase
    {
    public:
        CommMsgApplyEquipMoney() : CommMsgBase(APPLY_EQUIPMONEY_REQ) {}
        CommMsgApplyEquipMoney(RequestPtr req) : CommMsgBase(APPLY_EQUIPMONEY_REQ, req) {
            assert(req && !req->parameters_.empty());
        }

        // 消息接收方(本程序)用以构造一个对象
        static CommMsgApplyEquipMoneyPtr createFromReq(RequestPtr req)
        {
            return std::make_shared<CommMsgApplyEquipMoney>(req);
        }

        LOKI_DEFINE_CYCLIC_VISITABLE(CommVisitor);
    };
    
    /*
    * 审核申请资金请求
    */
    class CommMsgApprovalApplyEquipMoney : public CommMsgBase
    {
    public:
        CommMsgApprovalApplyEquipMoney() : CommMsgBase(APPLY_EQUIPMONEY_APPROVAL_REQ) {}
        CommMsgApprovalApplyEquipMoney(RequestPtr req) : CommMsgBase(APPLY_EQUIPMONEY_APPROVAL_REQ, req) {
            assert(req && !req->parameters_.empty());
        }

        // 消息接收方(本程序)用以构造一个对象
        static CommMsgApprovalApplyEquipMoneyPtr createFromReq(RequestPtr req)
        {
            return std::make_shared<CommMsgApprovalApplyEquipMoney>(req);
        }

        LOKI_DEFINE_CYCLIC_VISITABLE(CommVisitor);
    };

    /*
    * 机构删除请求
    */
    class CommMsgAgencyDelete : public CommMsgBase
    {
    public:
        CommMsgAgencyDelete() : CommMsgBase(INSTITUTION_DEL_REQ) {}
        CommMsgAgencyDelete(RequestPtr req) : CommMsgBase(INSTITUTION_DEL_REQ, req) {
            assert(req && !req->parameters_.empty());
        }

        // 消息接收方(本程序)用以构造一个对象
        static CommMsgAgencyDeletePtr createFromReq(RequestPtr req)
        {
            return std::make_shared<CommMsgAgencyDelete>(req);
        }

        LOKI_DEFINE_CYCLIC_VISITABLE(CommVisitor);
    };

    /*
    * 子账户删除请求
    */
    class CommMsgChildDelete : public CommMsgBase
    {
    public:
        CommMsgChildDelete() : CommMsgBase(CHILDUSER_DEL_REQ) {}
        CommMsgChildDelete(RequestPtr req) : CommMsgBase(CHILDUSER_DEL_REQ, req) {
            assert(req && !req->parameters_.empty());
        }

        // 消息接收方(本程序)用以构造一个对象
        static CommMsgChildDeletePtr createFromReq(RequestPtr req)
        {
            return std::make_shared<CommMsgChildDelete>(req);
        }

        LOKI_DEFINE_CYCLIC_VISITABLE(CommVisitor);
    };

    /*
    * 资金账户删除请求
    */
    class CommMsgFunderDelete : public CommMsgBase
    {
    public:
        CommMsgFunderDelete() : CommMsgBase(FUNDUSER_DEL_REQ) {}
        CommMsgFunderDelete(RequestPtr req) : CommMsgBase(FUNDUSER_DEL_REQ, req) {
            assert(req && !req->parameters_.empty());
        }

        // 消息接收方(本程序)用以构造一个对象
        static CommMsgFunderDeletePtr createFromReq(RequestPtr req)
        {
            return std::make_shared<CommMsgFunderDelete>(req);
        }

        LOKI_DEFINE_CYCLIC_VISITABLE(CommVisitor);
    };

    /*
    * 管理员删除请求
    */
    class CommMsgManagerDelete : public CommMsgBase
    {
    public:
        CommMsgManagerDelete() : CommMsgBase(MANAGER_DEL_REQ) {}
        CommMsgManagerDelete(RequestPtr req) : CommMsgBase(MANAGER_DEL_REQ, req) {
            assert(req && !req->parameters_.empty());
        }

        // 消息接收方(本程序)用以构造一个对象
        static CommMsgManagerDeletePtr createFromReq(RequestPtr req)
        {
            return std::make_shared<CommMsgManagerDelete>(req);
        }

        LOKI_DEFINE_CYCLIC_VISITABLE(CommVisitor);
    };



    /*
    * 自选股票查询请求
    */
    class CommMsgGetCustomStock : public CommMsgBase
    {
    public:
        CommMsgGetCustomStock() : CommMsgBase(CUSTOMSTOCK_REQ) {}
        CommMsgGetCustomStock(RequestPtr req) : CommMsgBase(CUSTOMSTOCK_REQ, req) {
            assert(req);
        }

        // 消息接收方(本程序)用以构造一个对象
        static CommMsgGetCustomStockPtr createFromReq(RequestPtr req)
        {
            return std::make_shared<CommMsgGetCustomStock>(req);
        }

        LOKI_DEFINE_CYCLIC_VISITABLE(CommVisitor);
    };

    /*
    * 自选股票新增请求
    */
    class CommMsgAddCustomStock : public CommMsgBase
    {
    public:
        CommMsgAddCustomStock() : CommMsgBase(CUSTOMSTOCK_ADD_REQ) {}
        CommMsgAddCustomStock(RequestPtr req) : CommMsgBase(CUSTOMSTOCK_ADD_REQ, req) {
            assert(req && !req->parameters_.empty());
        }

        // 消息接收方(本程序)用以构造一个对象
        static CommMsgAddCustomStockPtr createFromReq(RequestPtr req)
        {
            return std::make_shared<CommMsgAddCustomStock>(req);
        }

        LOKI_DEFINE_CYCLIC_VISITABLE(CommVisitor);
    };

    /*
    * 自选股票删除请求
    */
    class CommMsgDelCustomStock : public CommMsgBase
    {
    public:
        CommMsgDelCustomStock() : CommMsgBase(CUSTOMSTOCK_DEL_REQ) {}
        CommMsgDelCustomStock(RequestPtr req) : CommMsgBase(CUSTOMSTOCK_DEL_REQ, req) {
            assert(req && !req->parameters_.empty());
        }

        // 消息接收方(本程序)用以构造一个对象
        static CommMsgDelCustomStockPtr createFromReq(RequestPtr req)
        {
            return std::make_shared<CommMsgDelCustomStock>(req);
        }

        LOKI_DEFINE_CYCLIC_VISITABLE(CommVisitor);
    };


	/*
	* 修改角色/用户请求
	*/
	class CommMsgChangeRoleUser : public CommMsgBase
	{
	public:
		CommMsgChangeRoleUser() : CommMsgBase(ROLES_USER_CHANGE_REQ) {}
		CommMsgChangeRoleUser(RequestPtr req) : CommMsgBase(ROLES_USER_CHANGE_REQ, req) {
			assert(req && !req->parameters_.empty());
		}

		// 消息接收方(本程序)用以构造一个对象
		static CommMsgChangeRoleUserPtr createFromReq(RequestPtr req)
		{
			return std::make_shared<CommMsgChangeRoleUser>(req);
		}

		LOKI_DEFINE_CYCLIC_VISITABLE(CommVisitor);
	};

    // 入金审核查询请求
    class CommMsgAutoInMoneyQry : public CommMsgBase
    {
    public:
        CommMsgAutoInMoneyQry() : CommMsgBase(CHILD_AUTOINTOMONEY_QUERY_REQ) {}
        CommMsgAutoInMoneyQry(RequestPtr req) : CommMsgBase(CHILD_AUTOINTOMONEY_QUERY_REQ, req) {
            assert(req && !req->parameters_.empty());
        }

        // 消息接收方(本程序)用以构造一个对象
        static CommMsgAutoInMoneyQryPtr createFromReq(RequestPtr req)
        {
            return std::make_shared<CommMsgAutoInMoneyQry>(req);
        }

        LOKI_DEFINE_CYCLIC_VISITABLE(CommVisitor);
    };

    // 自动入金请求
    class CommMsgAutoInMoney : public CommMsgBase
    {
    public:
        CommMsgAutoInMoney() : CommMsgBase(CHILDUSER_AUTO_INMONEY_REQ) {}
        CommMsgAutoInMoney(RequestPtr req) : CommMsgBase(CHILDUSER_AUTO_INMONEY_REQ, req) {
            assert(req && !req->parameters_.empty());
        }

        // 消息接收方(本程序)用以构造一个对象
        static CommMsgAutoInMoneyPtr createFromReq(RequestPtr req)
        {
            return std::make_shared<CommMsgAutoInMoney>(req);
        }

        LOKI_DEFINE_CYCLIC_VISITABLE(CommVisitor);
    };

    // 自动出金请求
    class CommMsgAutoOutMoney : public CommMsgBase
    {
    public:
        CommMsgAutoOutMoney() : CommMsgBase(CHILDUSER_AUTO_OUTMONEY_REQ) {}
        CommMsgAutoOutMoney(RequestPtr req) : CommMsgBase(CHILDUSER_AUTO_OUTMONEY_REQ, req) {
            assert(req && !req->parameters_.empty());
        }

        // 消息接收方(本程序)用以构造一个对象
        static CommMsgAutoOutMoneyPtr createFromReq(RequestPtr req)
        {
            return std::make_shared<CommMsgAutoOutMoney>(req);
        }

        LOKI_DEFINE_CYCLIC_VISITABLE(CommVisitor);
    };


    /*
    * 自动开户
    */
    class CommMsgChildAccAutoAdd : public CommMsgBase
    {
    public:
        CommMsgChildAccAutoAdd() : CommMsgBase(CHILDUSER_AUTO_ADD_REQ) {}
        CommMsgChildAccAutoAdd(RequestPtr req) : CommMsgBase(CHILDUSER_AUTO_ADD_REQ, req) {
            assert(req && !req->parameters_.empty());
        }

        // 消息接收方(本程序)用以构造一个对象
        static CommMsgChildAccAutoAddPtr createFromReq(RequestPtr req)
        {
            return std::make_shared<CommMsgChildAccAutoAdd>(req);
        }

        LOKI_DEFINE_CYCLIC_VISITABLE(CommVisitor);
    };

	// 风控历史查询请求
	class RiskHistoryQry : public CommMsgBase
	{
	public:
		RiskHistoryQry() : CommMsgBase(RISK_HISTORY_REQ) {}
		RiskHistoryQry(RequestPtr req) : CommMsgBase(RISK_HISTORY_REQ, req) {
			assert(req && !req->parameters_.empty());
		}

		// 消息接收方(本程序)用以构造一个对象
		static RiskHistoryQryPtr createFromReq(RequestPtr req)
		{
			return std::make_shared<RiskHistoryQry>(req);
		}

		LOKI_DEFINE_CYCLIC_VISITABLE(CommVisitor);
	};

	// 融券设置请求
	class MarginSetQry : public CommMsgBase
	{
	public:
		MarginSetQry() : CommMsgBase(MARGIN_SET_REQ) {}
		MarginSetQry(RequestPtr req) : CommMsgBase(MARGIN_SET_REQ, req) {
			assert(req && !req->parameters_.empty());
		}

		// 消息接收方(本程序)用以构造一个对象
		static MarginSetQryPtr createFromReq(RequestPtr req)
		{
			return std::make_shared<MarginSetQry>(req);
		}

		LOKI_DEFINE_CYCLIC_VISITABLE(CommVisitor);
	};

	// 剩余融券数量查询请求
	class MarginLeftQry : public CommMsgBase
	{
	public:
		MarginLeftQry() : CommMsgBase(MARGIN_LEFTQTY_REQ) {}
		MarginLeftQry(RequestPtr req) : CommMsgBase(MARGIN_LEFTQTY_REQ, req) {
			assert(req && !req->parameters_.empty());
		}

		// 消息接收方(本程序)用以构造一个对象
		static MarginLeftQryPtr createFromReq(RequestPtr req)
		{
			return std::make_shared<MarginLeftQry>(req);
		}

		LOKI_DEFINE_CYCLIC_VISITABLE(CommVisitor);
	};

	// 融券管理查询请求
	class MarginManagerQry : public CommMsgBase
	{
	public:
		MarginManagerQry() : CommMsgBase(MARGIN_MANAGER_REQ) {}
		MarginManagerQry(RequestPtr req) : CommMsgBase(MARGIN_MANAGER_REQ, req) {
			assert(req && !req->parameters_.empty());
		}

		// 消息接收方(本程序)用以构造一个对象
		static MarginManagerQryPtr createFromReq(RequestPtr req)
		{
			return std::make_shared<MarginManagerQry>(req);
		}

		LOKI_DEFINE_CYCLIC_VISITABLE(CommVisitor);
	};

	// 融券管理查询请求
	class MarginLiabilitiesQry : public CommMsgBase
	{
	public:
		MarginLiabilitiesQry() : CommMsgBase(MARGIN_LIABILITIES_REQ) {}
		MarginLiabilitiesQry(RequestPtr req) : CommMsgBase(MARGIN_LIABILITIES_REQ, req) {
			assert(req && !req->parameters_.empty());
		}

		// 消息接收方(本程序)用以构造一个对象
		static MarginLiabilitiesQryPtr createFromReq(RequestPtr req)
		{
			return std::make_shared<MarginLiabilitiesQry>(req);
		}

		LOKI_DEFINE_CYCLIC_VISITABLE(CommVisitor);
	};

	// 利息统计查询请求
	class InterestStatisticsQry : public CommMsgBase
	{
	public:
		InterestStatisticsQry() : CommMsgBase(INTEREST_STATISTICS_REQ) {}
		InterestStatisticsQry(RequestPtr req) : CommMsgBase(INTEREST_STATISTICS_REQ, req) {
			assert(req && !req->parameters_.empty());
		}

		// 消息接收方(本程序)用以构造一个对象
		static InterestStatisticsQryPtr createFromReq(RequestPtr req)
		{
			return std::make_shared<InterestStatisticsQry>(req);
		}

		LOKI_DEFINE_CYCLIC_VISITABLE(CommVisitor);
	};

	// 利息明细查询请求
	class InterestDetailQry : public CommMsgBase
	{
	public:
		InterestDetailQry() : CommMsgBase(INTEREST_DETAIL_REQ) {}
		InterestDetailQry(RequestPtr req) : CommMsgBase(INTEREST_DETAIL_REQ, req) {
			assert(req && !req->parameters_.empty());
		}

		// 消息接收方(本程序)用以构造一个对象
		static InterestDetailQryPtr createFromReq(RequestPtr req)
		{
			return std::make_shared<InterestDetailQry>(req);
		}

		LOKI_DEFINE_CYCLIC_VISITABLE(CommVisitor);
	};

	/*
	* 当前融资委托查询请求
	*/
	class CommMsgCurrentyMarginEntrustQry : public CommMsgBase
	{
	public:
		CommMsgCurrentyMarginEntrustQry() : CommMsgBase(CURRENT_MARGINENTRUST_REQ) {}
		CommMsgCurrentyMarginEntrustQry(RequestPtr req) : CommMsgBase(CURRENT_MARGINENTRUST_REQ, req) {
			assert(req && !req->parameters_.empty());
		}

		// 消息接收方(本程序)用以构造一个对象
		static CommMsgCurrentyMarginEntrustQryPtr createFromReq(RequestPtr req)
		{
			return std::make_shared<CommMsgCurrentyMarginEntrustQry>(req);
		}

		LOKI_DEFINE_CYCLIC_VISITABLE(CommVisitor);
	};

	/*
	* 当前融资委托查询请求
	*/
	class CommMsgCurrentyMarginTradeQry : public CommMsgBase
	{
	public:
		CommMsgCurrentyMarginTradeQry() : CommMsgBase(CURRENT_MARGINTRADE_REQ) {}
		CommMsgCurrentyMarginTradeQry(RequestPtr req) : CommMsgBase(CURRENT_MARGINTRADE_REQ, req) {
			assert(req && !req->parameters_.empty());
		}

		// 消息接收方(本程序)用以构造一个对象
		static CommMsgCurrentyMarginTradeQryPtr createFromReq(RequestPtr req)
		{
			return std::make_shared<CommMsgCurrentyMarginTradeQry>(req);
		}

		LOKI_DEFINE_CYCLIC_VISITABLE(CommVisitor);
	};

} // namespace xyc_communication

#endif // __COMM_MESSAGE_H__
