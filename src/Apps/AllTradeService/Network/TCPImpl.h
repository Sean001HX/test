#ifndef TCPIMPL_H
#define TCPIMPL_H

#include <boost/noncopyable.hpp>
#include <boost\multi_index_container.hpp>
#include <boost\multi_index\mem_fun.hpp>
#include <boost\multi_index\ordered_index.hpp>
#include <boost\multi_index\global_fun.hpp>

#include <map>
#include <QTcpServer>
#include "NetInfo/CommMessage.h"
#include "utility/rwmutex.h"
#include "NetInfo/commmsg_declare.h"
#include "define/struct_declare.h"
#include "utility/dispatcher_core.h"
#include "utility/command.h"
#include "utility/sync.h"

class FortuneThread;

namespace xyc_communication {
    //////////////////////////////////////////////////////////////////////////
    // Communicate message nop visitor 
    class NopVisitor : public CommVisitor
    {
    public:
        virtual void Visit(CommMsgBase&)        { assert(0); }
        virtual void Visit(CommMsgLogin&)	    { assert(0); }
        virtual void Visit(CommMsgLogout&)	    { assert(0); }
        virtual void Visit(CommMsgHeartBeat&)	    { assert(0); }
        virtual void Visit(CommMsgAgencyQry&)	    { assert(0); }
        virtual void Visit(CommMsgAgencyPreApprovalQry&)	    { assert(0); }
        virtual void Visit(CommMsgAgencyLinkQry&)	    { assert(0); }
        virtual void Visit(CommMsgRolesQry&)	    { assert(0); }
        virtual void Visit(CommMsgAgencyRolesQry&)	    { assert(0); }
        virtual void Visit(CommMsgCommissQry&)	    { assert(0); }
        virtual void Visit(CommMsgCommissDtlQry&)	    { assert(0); }
        virtual void Visit(CommMsgProfitCommisslQry&)	    { assert(0); }
        virtual void Visit(CommMsgProfitCommissDtlQry&)	    { assert(0); }
        virtual void Visit(CommMsgToplogicalTreeQry&)	    { assert(0); }
        virtual void Visit(CommMsgChildAccQry&)	    { assert(0); }
        virtual void Visit(CommMsgChildApprovalQry&)	    { assert(0); }
        virtual void Visit(CommMsgFundAccQry&)	    { assert(0); }
        virtual void Visit(CommMsgOnlineAccQry&)	    { assert(0); }
        virtual void Visit(CommMsgStockContractQry&)	    { assert(0); }
        virtual void Visit(CommMsgStockBlackQry&)	    { assert(0); }
        virtual void Visit(CommMsgForbidBuySellQry&)	    { assert(0); }
        virtual void Visit(CommMsgPosiRateQry&)	    { assert(0); }
        virtual void Visit(CommMsgPosiQry&)	    { assert(0); }
        virtual void Visit(CommMsgCurrentyEntrustQry&)	    { assert(0); }
        virtual void Visit(CommMsgTodayEntrustQry&)	    { assert(0); }
        virtual void Visit(CommMsgHistoryEntrustQry&)	    { assert(0); }
        virtual void Visit(CommMsgTradeQry&)	    { assert(0); }
        virtual void Visit(CommMsgHistoryTradeQry&)	    { assert(0); }
        virtual void Visit(CommMsgFundQry&)	    { assert(0); }
        virtual void Visit(CommMsgFundSerialQry&)	    { assert(0); }
        virtual void Visit(CommMsgDeliveryQry&)	    { assert(0); }
        virtual void Visit(CommMsgFundMonitQry&)	    { assert(0); }
//         virtual void Visit(CommMsgTimeTradeQry&)	    { assert(0); }
        virtual void Visit(CommMsgSumPosiQry&)	    { assert(0); }
        virtual void Visit(CommMsgTimeWarnQry&)	    { assert(0); }
        virtual void Visit(CommMsgEquipMoneyQry&)	    { assert(0); }
        virtual void Visit(CommMsgAutoOutMoneyQry&)	    { assert(0); }
        virtual void Visit(CommMsgFeeSetQry&)	    { assert(0); }
        virtual void Visit(CommMsgManagerQry&)	    { assert(0); }
        virtual void Visit(CommMsgAgencyAdd&)	    { assert(0); }
        virtual void Visit(CommMsgAgencyChange&)	    { assert(0); }
        virtual void Visit(CommMsgAgencyApproval&)	    { assert(0); }
        virtual void Visit(CommMsgRolesAdd&)	    { assert(0); }
        virtual void Visit(CommMsgRolesChange&)	    { assert(0); }
        virtual void Visit(CommMsgBindRelation&)	    { assert(0); }
        virtual void Visit(CommMsgUserRoleAddRelation&)	    { assert(0); }
        virtual void Visit(CommMsgChildAccAdd&)	    { assert(0); }
        virtual void Visit(CommMsgChildAccChange&)	    { assert(0); }
        virtual void Visit(CommMsgChildAccInmoney&)	    { assert(0); }
        virtual void Visit(CommMsgChildAccApproval&)	    { assert(0); }
        virtual void Visit(CommMsgFundAccAdd&)	    { assert(0); }
        virtual void Visit(CommMsgFundAccChange&)	    { assert(0); }
        virtual void Visit(CommMsgFeeSet&)	    { assert(0); }
        virtual void Visit(CommMsgStockBlackSet&)	    { assert(0); }
        virtual void Visit(CommMsgForbidBuySellSet&)	    { assert(0); }
        virtual void Visit(CommMsgPosiRateSet&)	    { assert(0); }
        virtual void Visit(CommMsgAutoInMoneyApproval&)	    { assert(0); }
        virtual void Visit(CommMsgAutoOutMoneyApproval&)	    { assert(0); }
        virtual void Visit(CommMsgPswChange&)	    { assert(0); }
        virtual void Visit(CommMsgManagerAdd&)	    { assert(0); }
        virtual void Visit(CommMsgManagerChange&)	{ assert(0); }
        virtual void Visit(CommMsgOpenClose&)	    { assert(0); }
        virtual void Visit(CommMsgCancelOrder&)	    { assert(0); }
        
		virtual void Visit(CommMsgSelfFunctionQry&)	    { assert(0); }
		virtual void Visit(CommMsgRoleFunctionQry&)	    { assert(0); }
		virtual void Visit(CommMsgDelRole&)				{ assert(0); }
		virtual void Visit(CommMsgDelRoleUser&)			{ assert(0); }
		virtual void Visit(CommMsgGetAllBussnessUser&)	{ assert(0); }
//         virtual void Visit(CommMsgGetOnlineChildren&)	{ assert(0); }
        virtual void Visit(CommMsgApplyEquipMoney&)	        { assert(0); }
        virtual void Visit(CommMsgApprovalApplyEquipMoney&)	{ assert(0); }

        virtual void Visit(CommMsgAgencyDelete&)	    { assert(0); }
        virtual void Visit(CommMsgChildDelete&)	        { assert(0); }
        virtual void Visit(CommMsgFunderDelete&)	    { assert(0); }
        virtual void Visit(CommMsgManagerDelete&)	    { assert(0); }
   
        virtual void Visit(CommMsgGetCustomStock&)	    { assert(0); }
        virtual void Visit(CommMsgAddCustomStock&)	    { assert(0); }
		virtual void Visit(CommMsgDelCustomStock&)	    { assert(0); }
		virtual void Visit(CommMsgChangeRoleUser&)	    { assert(0); }
        virtual void Visit(CommMsgAutoInMoney&)	        { assert(0); }
        virtual void Visit(CommMsgAutoOutMoney&)	    { assert(0); }
        virtual void Visit(CommMsgChildAccAutoAdd&)	    { assert(0); }
        virtual void Visit(CommMsgAutoInMoneyQry&)	    { assert(0); }
		virtual void Visit(RiskHistoryQry&)				{ assert(0); }

		virtual void Visit(MarginSetQry&)				{ assert(0); }
		virtual void Visit(MarginLeftQry&)				{ assert(0); }
		virtual void Visit(MarginManagerQry&)			{ assert(0); }
		virtual void Visit(MarginLiabilitiesQry&)		{ assert(0); }
		virtual void Visit(InterestStatisticsQry&)		{ assert(0); }
		virtual void Visit(InterestDetailQry&)			{ assert(0); }
		virtual void Visit(CommMsgCurrentyMarginEntrustQry&)		{ assert(0); }
		virtual void Visit(CommMsgCurrentyMarginTradeQry&)		{ assert(0); }
    };
}

struct SocketSt
{
    SocketSt() :socket_descriptor_(0), socket_ptr_(nullptr), socket_thread_(nullptr){}
    SocketSt(qintptr socket_descriptor, QTcpSocket* socket_ptr, FortuneThread* socket_thread)
        : socket_descriptor_(socket_descriptor)
        , socket_ptr_(socket_ptr)
        , socket_thread_(socket_thread)
    {
    }

    AllTrade::LoginNameType     login_name_;
    qintptr                     socket_descriptor_;
    QTcpSocket*                 socket_ptr_;
    FortuneThread*              socket_thread_;
};

//////////////////////////////////////////////////////////////////////////
const AllTrade::PLoginNameType get_socket_login_name(const SocketSt&);
qintptr get_socket_descriptor(const SocketSt&);
const QTcpSocket* get_socket_ptr(const SocketSt&);
const FortuneThread* get_fortune_thread(const SocketSt&);

//////////////////////////////////////////////////////////////////////////
// socket多索引排序
class SocketIndex : public boost::noncopyable
{
public:
    SocketIndex() {}
    ~SocketIndex() {}

    void clear();
    void addToList(const SocketSt& socket_st);
    void removefromList(const QTcpSocket* socket_ptr);

    // 获取socket_id
    qintptr getSocketDescriptByPtr(const QTcpSocket* socket_ptr) const;
    // 获取socket_ptr
    const QTcpSocket* getSocketPtrByDescript(qintptr socket_id) const;
    QTcpSocket* getSocketPtrByFortuneThread(const FortuneThread* fortune_thread) const;
    // 获取FortuneThread
    FortuneThread* getFortuneThreadByPtr(const QTcpSocket* socket_ptr) const;
    FortuneThread* getFortuneThreadByDescript(qintptr socket_id) const;
    std::vector<FortuneThread*> getFortuneThreadByLoginName(const AllTrade::LoginNameType loginname) const;
    std::vector<qintptr> getSocketDescriptByLoginName(const AllTrade::LoginNameType loginname) const;
    // 获取登录名
    AllTrade::PLoginNameType getLoginNameByDescript(qintptr socket_id) const;

    void setLoginName(qintptr socket_id, const AllTrade::LoginNameType login_name);

private:
    template<typename Tag, typename ParamType>
    SocketSt getSocket(const ParamType param) const
    {
        readLock    rl(m_mtx);

        auto& indexoftag = m_sockets.get<Tag>();
        auto fit = indexoftag.find(param);
        if (fit != indexoftag.end())
            return *fit;

        return SocketSt();
    }

private:
    ///////////////////////////////////////////////
    struct DescriptorTag {};
    struct SocketPtrTag {};
    struct ThreadTag {};
    struct LoginNameTag {};
    typedef boost::multi_index::multi_index_container <
        SocketSt,
        boost::multi_index::indexed_by<
        boost::multi_index::ordered_unique<boost::multi_index::tag<DescriptorTag>, boost::multi_index::global_fun<const SocketSt&, qintptr, get_socket_descriptor> >,
        boost::multi_index::ordered_unique<boost::multi_index::tag<SocketPtrTag>, boost::multi_index::global_fun<const SocketSt&, const QTcpSocket*, get_socket_ptr> >,
        boost::multi_index::ordered_unique<boost::multi_index::tag<ThreadTag>, boost::multi_index::global_fun<const SocketSt&, const FortuneThread*, get_fortune_thread> >,
        boost::multi_index::ordered_non_unique<boost::multi_index::tag<LoginNameTag>, boost::multi_index::global_fun<const SocketSt&, const AllTrade::PLoginNameType, get_socket_login_name> >
        >
    > SocketStSet;

private:
    mutable rwMutex    m_mtx;
    SocketStSet        m_sockets;
};


class TCPImpl : public QTcpServer, public std::enable_shared_from_this<TCPImpl>, public CommonTools::dispatcher_callback<CommonTools::CommandPtr>
{
    Q_OBJECT

public:
    TCPImpl(QObject *parent);
    ~TCPImpl();
    void sendMessageInter(xyc_communication::ReplyMsgPtr reply_ptr);
    void sendMessageToAllInter(const AllTrade::UserIDType user_id, const AllTrade::LoginNameType login_name, xyc_communication::ReplyMsgPtr reply_ptr);
    void setLoginName(qintptr socket_id, const AllTrade::LoginNameType login_name);

    void closeSocketInter(qintptr socket_id);

    std::string getAddrBySocketID(qintptr socket_id);

public slots:
    void slotNewConnection();
    void slotRead();
    void slotSendMessage(const QString& msg, int socketDesc);
    void slotSocketError();

private:
    void onOrderInsertCbk(AllTrade::ErrorCodeType errcode, const AllTrade::UserIDType user_id, const AllTrade::NPTradeCenter::OrderInfoPtr& order_ptr, const AllTrade::NPMgrCenter::SOnlineAccountPtr& user_ptr);
    void onOrderCancelCbk(AllTrade::ErrorCodeType errcode, const AllTrade::UserIDType user_id, const AllTrade::NPTradeCenter::OrderInfoPtr& order_ptr, const AllTrade::NPMgrCenter::SOnlineAccountPtr& user_ptr);
    void onOrderChangeCbk(AllTrade::ErrorCodeType errcode, const AllTrade::UserIDType user_id, const AllTrade::NPTradeCenter::OrderInfoPtr& order_ptr);
    void onTradeCbk(AllTrade::ErrorCodeType errcode, const AllTrade::UserIDType user_id, const AllTrade::NPTradeCenter::TradeInfoPtr& trade_ptr);
    void onPositionCbk(AllTrade::ErrorCodeType errcode, const AllTrade::UserIDType user_id, const AllTrade::NPTradeCenter::PositionInfoPtr& position_ptr);
    void onMoneyCbk(const AllTrade::UserIDType user_id, const AllTrade::NPMgrCenter::SMoneyInfoPtr& money_ptr);
    void onRiskControlCbk(const AllTrade::UserIDType user_id, const AllTrade::DateTimeType date_time, AllTrade::RiskControlType rc_type, const AllTrade::RemarkTextType remark_text);

private slots:
    void slotOrderInsertCbk(AllTrade::ErrorCodeType errcode, const std::string& user_id, const AllTrade::NPTradeCenter::OrderInfoPtr& order_ptr, const AllTrade::NPMgrCenter::SOnlineAccountPtr& user_ptr);
    void slotOrderCancelCbk(AllTrade::ErrorCodeType errcode, const std::string& user_id, const AllTrade::NPTradeCenter::OrderInfoPtr& order_ptr);
    void slotOrderChangeCbk(AllTrade::ErrorCodeType errcode, const std::string& user_id, const AllTrade::NPTradeCenter::OrderInfoPtr& order_ptr);
    void slotTradeCbk(AllTrade::ErrorCodeType errcode, const std::string& user_id, const AllTrade::NPTradeCenter::TradeInfoPtr& trade_ptr);
    void slotPositionCbk(AllTrade::ErrorCodeType errcode, const std::string& user_id, const AllTrade::NPTradeCenter::PositionInfoPtr& position_ptr);
    void slotMoneyCbk(const std::string& user_id, const AllTrade::NPMgrCenter::SMoneyInfoPtr& money_ptr);
    void slotRiskControlCbk(const std::string& user_id, const std::string& date_time, AllTrade::RiskControlType rc_type, const std::string& remark_text);

signals:
    void sglOrderInsertCbk(AllTrade::ErrorCodeType errcode, const std::string& user_id, const AllTrade::NPTradeCenter::OrderInfoPtr& order_ptr, const AllTrade::NPMgrCenter::SOnlineAccountPtr& user_ptr);
    void sglOrderCancelCbk(AllTrade::ErrorCodeType errcode, const std::string& user_id, const AllTrade::NPTradeCenter::OrderInfoPtr& order_ptr);
    void sglOrderChangeCbk(AllTrade::ErrorCodeType errcode, const std::string& user_id, const AllTrade::NPTradeCenter::OrderInfoPtr& order_ptr);
    void sglTradeCbk(AllTrade::ErrorCodeType errcode, const std::string& user_id, const AllTrade::NPTradeCenter::TradeInfoPtr& trade_ptr);
    void sglPositionCbk(AllTrade::ErrorCodeType errcode, const std::string& user_id, const AllTrade::NPTradeCenter::PositionInfoPtr& position_ptr);
    void sglMoneyCbk(const std::string& user_id, const AllTrade::NPMgrCenter::SMoneyInfoPtr& money_ptr);
    void sglRiskControlCbk(const std::string& user_id, const std::string& date_time, AllTrade::RiskControlType rc_type, const std::string& remark_text);

private:
    void receivedMsgProcess(QByteArray str, qintptr socketDescriptor);
    std::vector<xyc_communication::RequestPtr> createRequest(QByteArray str, qintptr socketDescriptor);
    void write(qintptr socketDescriptor, const QString& str);
    void write(const AllTrade::LoginNameType login_name, const QString& str);
    void writeToAll(const AllTrade::UserIDType user_id, const AllTrade::LoginNameType login_name, const QString& str);
    void writeToMC(const AllTrade::UserIDType user_id, const QString& str);

    void closeSocket(QTcpSocket* socket);

private:
    void onReceivedMsgProcess(QByteArray str, qintptr socketDescriptor);

protected:
    // 对接收到的消息进行处理
    class RecvMsgVisitor : public xyc_communication::NopVisitor
    {
    public:
        RecvMsgVisitor(TCPImpl* pParent) : m_pParent(pParent){}
        ~RecvMsgVisitor() {}

        virtual void Visit(xyc_communication::CommMsgLogin&);
        virtual void Visit(xyc_communication::CommMsgLogout&);
        virtual void Visit(xyc_communication::CommMsgHeartBeat&);
        virtual void Visit(xyc_communication::CommMsgAgencyQry&);
        virtual void Visit(xyc_communication::CommMsgAgencyPreApprovalQry&);
        virtual void Visit(xyc_communication::CommMsgAgencyLinkQry&);
        virtual void Visit(xyc_communication::CommMsgRolesQry&);			// 查询角色信息
        virtual void Visit(xyc_communication::CommMsgAgencyRolesQry&);		// 查询角色/用户关系
        virtual void Visit(xyc_communication::CommMsgCommissQry&);
        virtual void Visit(xyc_communication::CommMsgCommissDtlQry&);
        virtual void Visit(xyc_communication::CommMsgProfitCommisslQry&);
        virtual void Visit(xyc_communication::CommMsgProfitCommissDtlQry&);
        virtual void Visit(xyc_communication::CommMsgToplogicalTreeQry&);
        virtual void Visit(xyc_communication::CommMsgChildAccQry&);
        virtual void Visit(xyc_communication::CommMsgChildApprovalQry&);
        virtual void Visit(xyc_communication::CommMsgFundAccQry&);
        virtual void Visit(xyc_communication::CommMsgOnlineAccQry&);
        virtual void Visit(xyc_communication::CommMsgStockContractQry&);
        virtual void Visit(xyc_communication::CommMsgStockBlackQry&);
        virtual void Visit(xyc_communication::CommMsgForbidBuySellQry&);
        virtual void Visit(xyc_communication::CommMsgPosiRateQry&);
        virtual void Visit(xyc_communication::CommMsgPosiQry&);
        virtual void Visit(xyc_communication::CommMsgCurrentyEntrustQry&);
        virtual void Visit(xyc_communication::CommMsgTodayEntrustQry&);
        virtual void Visit(xyc_communication::CommMsgHistoryEntrustQry&);
        virtual void Visit(xyc_communication::CommMsgTradeQry&);
        virtual void Visit(xyc_communication::CommMsgHistoryTradeQry&);
        virtual void Visit(xyc_communication::CommMsgFundQry&);
        virtual void Visit(xyc_communication::CommMsgFundSerialQry&);
        virtual void Visit(xyc_communication::CommMsgDeliveryQry&);
        virtual void Visit(xyc_communication::CommMsgFundMonitQry&);
//         virtual void Visit(xyc_communication::CommMsgTimeTradeQry&);
        virtual void Visit(xyc_communication::CommMsgSumPosiQry&);
        virtual void Visit(xyc_communication::CommMsgTimeWarnQry&); // 实时预警通知查询
        virtual void Visit(xyc_communication::CommMsgEquipMoneyQry&);
        virtual void Visit(xyc_communication::CommMsgAutoOutMoneyQry&);
        virtual void Visit(xyc_communication::CommMsgFeeSetQry&);
        virtual void Visit(xyc_communication::CommMsgManagerQry&);
        virtual void Visit(xyc_communication::CommMsgAgencyAdd&);
        virtual void Visit(xyc_communication::CommMsgAgencyChange&);
        virtual void Visit(xyc_communication::CommMsgAgencyApproval&);
        virtual void Visit(xyc_communication::CommMsgRolesAdd&);		// 增加角色
        virtual void Visit(xyc_communication::CommMsgRolesChange&);		// 修改角色
        virtual void Visit(xyc_communication::CommMsgBindRelation&);	// 绑定角色 / 功能关系
        virtual void Visit(xyc_communication::CommMsgUserRoleAddRelation&);// 增加角色/用户关系
        virtual void Visit(xyc_communication::CommMsgChildAccAdd&);
        virtual void Visit(xyc_communication::CommMsgChildAccChange&);
        virtual void Visit(xyc_communication::CommMsgChildAccInmoney&);
        virtual void Visit(xyc_communication::CommMsgChildAccApproval&);
        virtual void Visit(xyc_communication::CommMsgFundAccAdd&);
        virtual void Visit(xyc_communication::CommMsgFundAccChange&);
        virtual void Visit(xyc_communication::CommMsgFeeSet&);
        virtual void Visit(xyc_communication::CommMsgStockBlackSet&);
        virtual void Visit(xyc_communication::CommMsgForbidBuySellSet&);
        virtual void Visit(xyc_communication::CommMsgPosiRateSet&);
        virtual void Visit(xyc_communication::CommMsgAutoInMoneyApproval&);
        virtual void Visit(xyc_communication::CommMsgAutoOutMoneyApproval&);
        virtual void Visit(xyc_communication::CommMsgPswChange&);
        virtual void Visit(xyc_communication::CommMsgManagerAdd&);
        virtual void Visit(xyc_communication::CommMsgManagerChange&);
        virtual void Visit(xyc_communication::CommMsgOpenClose&);
        virtual void Visit(xyc_communication::CommMsgCancelOrder&);

		virtual void Visit(xyc_communication::CommMsgSelfFunctionQry&);	// 登陆者查询自身权限功能
		virtual void Visit(xyc_communication::CommMsgRoleFunctionQry&);	// 角色查询所属的权限功能
		virtual void Visit(xyc_communication::CommMsgDelRole&);			// 删除角色
		virtual void Visit(xyc_communication::CommMsgDelRoleUser&);		// 删除角色/用户
		virtual void Visit(xyc_communication::CommMsgGetAllBussnessUser&);		// 查询所有业务

        virtual void Visit(xyc_communication::CommMsgApplyEquipMoney&);                         // 
        virtual void Visit(xyc_communication::CommMsgApprovalApplyEquipMoney&);

        virtual void Visit(xyc_communication::CommMsgAgencyDelete&);
        virtual void Visit(xyc_communication::CommMsgChildDelete&);
        virtual void Visit(xyc_communication::CommMsgFunderDelete&);
        virtual void Visit(xyc_communication::CommMsgManagerDelete&);
        virtual void Visit(xyc_communication::CommMsgGetCustomStock&);
        virtual void Visit(xyc_communication::CommMsgAddCustomStock&);
        virtual void Visit(xyc_communication::CommMsgDelCustomStock&);

		virtual void Visit(xyc_communication::CommMsgChangeRoleUser&);		// 修改角色/用户

        virtual void Visit(xyc_communication::CommMsgAutoInMoney&);
        virtual void Visit(xyc_communication::CommMsgAutoOutMoney&);
        virtual void Visit(xyc_communication::CommMsgChildAccAutoAdd&);
        virtual void Visit(xyc_communication::CommMsgAutoInMoneyQry&);
		virtual void Visit(xyc_communication::RiskHistoryQry&);

		virtual void Visit(xyc_communication::MarginSetQry&);		// 证券信息设置
		virtual void Visit(xyc_communication::MarginLeftQry&);		// 证券剩余数量查询
		virtual void Visit(xyc_communication::MarginManagerQry&);	// 融券管理查询请求
		virtual void Visit(xyc_communication::MarginLiabilitiesQry&);	// 融券负债查询请求

		virtual void Visit(xyc_communication::InterestStatisticsQry&);	// 利息统计查询请求
		virtual void Visit(xyc_communication::InterestDetailQry&);		// 利息明细查询请求
		virtual void Visit(xyc_communication::CommMsgCurrentyMarginEntrustQry&);		// 当前融券委托查询
		virtual void Visit(xyc_communication::CommMsgCurrentyMarginTradeQry&);		// 当前成交查询
    protected:
        TCPImpl*	m_pParent;
    };
    friend class RecvMsgVisitor;
    RecvMsgVisitor	m_recvMsgVisitor;

protected:
    // dispatcher_callback functions
    long on_threadstart(void* param);
    long on_threadstop(void* param);
    long on_message(CommonTools::CommandPtr msg, bool cleanup);
    long on_event(CommonTools::handler evt);
    bool postDispMsg(CommonTools::CommandPtr pCmd) {
        if (!pCmd)
            return false;
        return m_dispatcher.post_message(pCmd);
    }

private:
    CommonTools::dispatcher<CommonTools::CommandPtr>    m_dispatcher;
    SocketIndex m_sockets;
};

#endif // TCPIMPL_H
