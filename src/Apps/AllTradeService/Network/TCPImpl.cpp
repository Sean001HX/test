#include <QMessageBox>
#include <QTcpSocket>
#include <QDataStream>
#include <QJsonParseError>
#include <QJsonDocument>
#include <QJsonObject>
#include "TCPImpl.h"
#include "fortunethread.h"
#include "reply_message.h"
#include "define/CommMsgDefine.h"
#include "utility/scopeguard.h"
#include "define/struct_content.h"
#include "../AsyncQryService.h"
#include "include/TradeCenter/TradeCenter.h"
#include "include/ManagerCenter/ManagerCenter.h"
#include "define/struct_extern.h"
#include "OnlineUserManager.h"

#include "c:/ng_tools/ng_header_for_log4cxx/ng_header_for_log4cxx.hpp"
#include "C:/ng_tools/ng_header_for_log4cxx/ng_header_for_log4cxx_log_var.hpp"

NG_LOGGER(logger, "TCPImpl");

using namespace xyc_communication;
using namespace AllTrade;
using namespace AllTrade::NPTradeCenter;
using namespace CommonTools;

//////////////////////////////////////////////////////////////////////////
const PLoginNameType get_socket_login_name(const SocketSt& st)
{
    return st.login_name_;
}

qintptr get_socket_descriptor(const SocketSt& st)
{
    return st.socket_descriptor_;
}

const QTcpSocket* get_socket_ptr(const SocketSt& st)
{
    return st.socket_ptr_;
}

const FortuneThread* get_fortune_thread(const SocketSt& st)
{
    return st.socket_thread_;
}

//////////////////////////////////////////////////////////////////////////
void SocketIndex::clear()
{
    writeLock    rl(m_mtx);
    m_sockets.clear();
}

void SocketIndex::addToList(const SocketSt& socket_st)
{
    writeLock    rl(m_mtx);

    auto& indexoftag = m_sockets.get<SocketPtrTag>();
    auto iter = indexoftag.find(socket_st.socket_ptr_);
    if (iter == indexoftag.end())
        indexoftag.insert(socket_st);
    else
        indexoftag.replace(iter, socket_st);// 注意modify在替换失败时会导致删除,但效率较高
}

void SocketIndex::removefromList(const QTcpSocket* socket_ptr)
{
    writeLock    rl(m_mtx);

    auto& indexoftag = m_sockets.get<SocketPtrTag>();
    auto iter = indexoftag.find(socket_ptr);
    if (iter != indexoftag.end())
        indexoftag.erase(iter);
}

qintptr SocketIndex::getSocketDescriptByPtr(const QTcpSocket* socket_ptr) const
{
    return getSocket<SocketPtrTag>(socket_ptr).socket_descriptor_;
}

const QTcpSocket* SocketIndex::getSocketPtrByDescript(qintptr socket_id) const
{
    return getSocket<DescriptorTag>(socket_id).socket_ptr_;
}

QTcpSocket* SocketIndex::getSocketPtrByFortuneThread(const FortuneThread* fortune_thread) const
{
    return getSocket<ThreadTag>(fortune_thread).socket_ptr_;
}

FortuneThread* SocketIndex::getFortuneThreadByPtr(const QTcpSocket* socket_ptr) const
{
    return getSocket<SocketPtrTag>(socket_ptr).socket_thread_;
}

FortuneThread* SocketIndex::getFortuneThreadByDescript(qintptr socket_id) const
{
    return getSocket<DescriptorTag>(socket_id).socket_thread_;
}

std::vector<FortuneThread*> SocketIndex::getFortuneThreadByLoginName(const AllTrade::LoginNameType loginname) const
{
    std::vector<FortuneThread*> rslt;
    readLock    rl(m_mtx);

    auto& indexoftag = m_sockets.get<LoginNameTag>();
    auto fit_begin = indexoftag.lower_bound(loginname);
    auto fit_end = indexoftag.upper_bound(loginname);
    while (fit_begin != fit_end)
    {
        rslt.push_back((*fit_begin).socket_thread_);
        ++fit_begin;
    }

    return rslt;
}

std::vector<qintptr> SocketIndex::getSocketDescriptByLoginName(const AllTrade::LoginNameType loginname) const
{
    std::vector<qintptr> rslt;
    readLock    rl(m_mtx);

    auto& indexoftag = m_sockets.get<LoginNameTag>();
    auto fit_begin = indexoftag.lower_bound(loginname);
    auto fit_end = indexoftag.upper_bound(loginname);
    while (fit_begin != fit_end)
    {
        rslt.push_back((*fit_begin).socket_descriptor_);
        ++fit_begin;
    }

    return rslt;
}

AllTrade::PLoginNameType SocketIndex::getLoginNameByDescript(qintptr socket_id) const
{
    return getSocket<DescriptorTag>(socket_id).login_name_;
}

void SocketIndex::setLoginName(qintptr socket_id, const AllTrade::LoginNameType login_name)
{
    SocketSt st = getSocket<DescriptorTag>(socket_id);
    strncpy_s(st.login_name_, login_name, sizeof(st.login_name_) - 1);
    addToList(st);
}

//////////////////////////////////////////////////////////////////////////
TCPImpl::TCPImpl(QObject *parent)
    : QTcpServer(parent)
    , m_recvMsgVisitor(this)
    , m_dispatcher(this)
{
    m_dispatcher.start();

    qRegisterMetaType<AllTrade::ErrorCodeType>("AllTrade::ErrorCodeType");
    qRegisterMetaType<std::string>("std::string");
    qRegisterMetaType<AllTrade::NPTradeCenter::OrderInfoPtr>("AllTrade::NPTradeCenter::OrderInfoPtr");
    qRegisterMetaType<AllTrade::NPTradeCenter::TradeInfoPtr>("AllTrade::NPTradeCenter::TradeInfoPtr");
    qRegisterMetaType<AllTrade::NPTradeCenter::PositionInfoPtr>("AllTrade::NPTradeCenter::PositionInfoPtr");
    qRegisterMetaType<AllTrade::NPMgrCenter::SMoneyInfoPtr>("AllTrade::NPMgrCenter::SMoneyInfoPtr");
    qRegisterMetaType<AllTrade::RiskControlType>("AllTrade::RiskControlType");
    qRegisterMetaType<AllTrade::NPMgrCenter::SOnlineAccountPtr>("AllTrade::NPMgrCenter::SOnlineAccountPtr");
    bool bl = connect(this, &TCPImpl::sglOrderInsertCbk, this, &TCPImpl::slotOrderInsertCbk);
    bl = connect(this, &TCPImpl::sglOrderCancelCbk, this, &TCPImpl::slotOrderCancelCbk);
    bl = connect(this, &TCPImpl::sglOrderChangeCbk, this, &TCPImpl::slotOrderChangeCbk);
    bl = connect(this, &TCPImpl::sglTradeCbk, this, &TCPImpl::slotTradeCbk);
    bl = connect(this, &TCPImpl::sglPositionCbk, this, &TCPImpl::slotPositionCbk);
    bl = connect(this, &TCPImpl::sglMoneyCbk, this, &TCPImpl::slotMoneyCbk);
    bl = connect(this, &TCPImpl::sglRiskControlCbk, this, &TCPImpl::slotRiskControlCbk);

    AllTrade::NPTradeCenter::ITradeCenter::instance()->setOrderInsertCbk(std::bind(&TCPImpl::onOrderInsertCbk, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4));
    AllTrade::NPTradeCenter::ITradeCenter::instance()->setOrderCancelCbk(std::bind(&TCPImpl::onOrderCancelCbk, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4));
    AllTrade::NPTradeCenter::ITradeCenter::instance()->setOrderChangeCbk(std::bind(&TCPImpl::onOrderChangeCbk, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
    AllTrade::NPTradeCenter::ITradeCenter::instance()->setTradeCbk(std::bind(&TCPImpl::onTradeCbk, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
    AllTrade::NPTradeCenter::ITradeCenter::instance()->setPositionCbk(std::bind(&TCPImpl::onPositionCbk, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
    AllTrade::NPMgrCenter::IManagerCenter::instance()->setMoneyCbk(std::bind(&TCPImpl::onMoneyCbk, this, std::placeholders::_1, std::placeholders::_2));
    AllTrade::NPTradeCenter::ITradeCenter::instance()->setRiskControlCbk(std::bind(&TCPImpl::onRiskControlCbk, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4));

    int i_port = GetPrivateProfileIntA("Trade", "port", 65500, "./config.hxc");
    
    if (listen(QHostAddress::Any, i_port))
        CommMsgBase::initialize();
    else
    {
        LOG4CXX_ERROR(logger, "开启监听端口失败!"LOG_NOVAR(i_port));
        QMessageBox::warning(nullptr, QStringLiteral("错误"), QStringLiteral("开启监听端口失败!"));
    }

    connect(this, &TCPImpl::newConnection, this, &TCPImpl::slotNewConnection, Qt::QueuedConnection);
}

TCPImpl::~TCPImpl()
{
    m_dispatcher.stop();
    m_sockets.clear();
    CommMsgBase::unInitialize();
}

void TCPImpl::slotNewConnection()
{
    QTcpSocket* tcpSocket = nextPendingConnection();
    if (tcpSocket->socketDescriptor() == -1)
        return;
    LOG4CXX_TRACE(logger, "有新连接!"LOG_NOVAR(tcpSocket->socketDescriptor()));
    connect(tcpSocket, &QTcpSocket::readyRead, this, &TCPImpl::slotRead, Qt::QueuedConnection);
    connect(tcpSocket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(slotSocketError()));
    connect(tcpSocket, &QTcpSocket::disconnected, this, &TCPImpl::slotSocketError);
    connect(tcpSocket, &QTcpSocket::disconnected, tcpSocket, &QTcpSocket::deleteLater);
    connect(tcpSocket, &QTcpSocket::stateChanged, [&](QAbstractSocket::SocketState state){
        if (state == QAbstractSocket::ClosingState || state == QAbstractSocket::UnconnectedState)
        {
            QTcpSocket* socket = qobject_cast<QTcpSocket*>(sender());
            closeSocket(socket);
        }
    });

    FortuneThread* thread = new FortuneThread(tcpSocket->socketDescriptor(), tcpSocket->peerAddress().toString(), this);
    connect(thread, &FortuneThread::sglWriteToSocket, this, &TCPImpl::slotSendMessage, Qt::QueuedConnection);

    m_sockets.addToList(SocketSt(tcpSocket->socketDescriptor(), tcpSocket, thread));
}

void TCPImpl::slotRead()
{
    QTcpSocket* socket = qobject_cast<QTcpSocket*>(sender());
    if (socket)
    {
        QByteArray rawreply = socket->readAll();

        LOG4CXX_TRACE(logger, "read:"LOG_NOVAR(socket->socketDescriptor())LOG_NOVAR(QString(rawreply).toLocal8Bit().data()));
        receivedMsgProcess(rawreply, socket->socketDescriptor());
    }
}

void TCPImpl::slotSendMessage(const QString& msg, int socketDesc)
{
    QTcpSocket* socket = const_cast<QTcpSocket*>(m_sockets.getSocketPtrByDescript(socketDesc));
    if (socket && socket->isWritable())
    {
        socket->write(msg.toUtf8());
        if (!socket->flush())
        {
            closeSocket(socket);
            return;
        }
        if (msg.indexOf("\"cmdcode\": \"2030\"") == -1)
            LOG4CXX_TRACE(logger, "write:"LOG_NOVAR(socketDesc)LOG_NOVAR(msg.toLocal8Bit().data()));
    }
}


void TCPImpl::slotSocketError()
{
    QTcpSocket* socket = qobject_cast<QTcpSocket*>(sender());
    closeSocket(socket);
}

void TCPImpl::closeSocket(QTcpSocket* socket)
{
    if (!socket) return;

    FortuneThread* thread = m_sockets.getFortuneThreadByPtr(socket);
   
    if (thread && !thread->isFinished())
    {
        thread->close();
    }

    AllTrade::OnlineUserManager::instance()->removeLoginUser(m_sockets.getSocketDescriptByPtr(socket));
    m_sockets.removefromList(socket);

}

void TCPImpl::slotOrderInsertCbk(AllTrade::ErrorCodeType errcode, const std::string& user_id, const AllTrade::NPTradeCenter::OrderInfoPtr& order_ptr, const AllTrade::NPMgrCenter::SOnlineAccountPtr& user_ptr)
{
    if (!user_ptr)
        return;

    auto acc_ptr = AllTrade::NPMgrCenter::IManagerCenter::instance()->getAccountByID(user_id.c_str());
    auto push_msg_ptr = PushOrderMsg::getReply(errcode, acc_ptr, gszMsgCommandCode[E_COMM_MSG_TYPE::ORDERINSERT_MSG], order_ptr);
    auto acc_parent_ptr = AllTrade::NPMgrCenter::IManagerCenter::instance()->getAccountByID(acc_ptr->parent_id_);
    if (acc_parent_ptr)
        strncpy_s(push_msg_ptr->m_parent_login_name, acc_parent_ptr->login_name_, sizeof(push_msg_ptr->m_parent_login_name) - 1);

    push_msg_ptr->m_stock_ptr = AllTrade::NPMgrCenter::IManagerCenter::instance()->getStockContractByID((std::dynamic_pointer_cast<StockOrderInfo>(order_ptr))->stock_area_, order_ptr->contract_id_);
    if (!push_msg_ptr->m_stock_ptr)
    {
        assert(0);
        return;
    }
        
    write(user_ptr->session_id_, QString::fromUtf8(push_msg_ptr->to_string().c_str()));
}

void TCPImpl::slotOrderCancelCbk(AllTrade::ErrorCodeType errcode, const std::string& user_id, const AllTrade::NPTradeCenter::OrderInfoPtr& order_ptr)
{
    auto acc_ptr = AllTrade::NPMgrCenter::IManagerCenter::instance()->getAccountByID(user_id.c_str());
    auto push_msg_ptr = PushOrderMsg::getReply(errcode, acc_ptr, gszMsgCommandCode[E_COMM_MSG_TYPE::ORDERCANCEL_MSG], order_ptr);
    auto acc_parent_ptr = AllTrade::NPMgrCenter::IManagerCenter::instance()->getAccountByID(acc_ptr->parent_id_);
    if (acc_parent_ptr)
        strncpy_s(push_msg_ptr->m_parent_login_name, acc_parent_ptr->login_name_, sizeof(push_msg_ptr->m_parent_login_name) - 1);
    
    push_msg_ptr->m_stock_ptr = AllTrade::NPMgrCenter::IManagerCenter::instance()->getStockContractByID((std::dynamic_pointer_cast<StockOrderInfo>(order_ptr))->stock_area_, order_ptr->contract_id_);
    if (!push_msg_ptr->m_stock_ptr)
    {
        assert(0);
        return;
    }
    writeToAll(user_id.c_str(), acc_ptr->login_name_, QString::fromUtf8(push_msg_ptr->to_string().c_str()));
}

void TCPImpl::slotOrderChangeCbk(AllTrade::ErrorCodeType errcode, const std::string& user_id, const AllTrade::NPTradeCenter::OrderInfoPtr& order_ptr)
{
    auto acc_ptr = AllTrade::NPMgrCenter::IManagerCenter::instance()->getAccountByID(user_id.c_str());
    auto push_msg_ptr = PushOrderMsg::getReply(errcode, acc_ptr, gszMsgCommandCode[E_COMM_MSG_TYPE::ORDERCHANGE_MSG], order_ptr);
    auto acc_parent_ptr = AllTrade::NPMgrCenter::IManagerCenter::instance()->getAccountByID(acc_ptr->parent_id_);
    if (acc_parent_ptr)
        strncpy_s(push_msg_ptr->m_parent_login_name, acc_parent_ptr->login_name_, sizeof(push_msg_ptr->m_parent_login_name) - 1);
    
    push_msg_ptr->m_stock_ptr = AllTrade::NPMgrCenter::IManagerCenter::instance()->getStockContractByID((std::dynamic_pointer_cast<StockOrderInfo>(order_ptr))->stock_area_, order_ptr->contract_id_);
    if (!push_msg_ptr->m_stock_ptr)
    {
        assert(0);
        return;
    }
    writeToAll(user_id.c_str(), acc_ptr->login_name_, QString::fromUtf8(push_msg_ptr->to_string().c_str()));
}

void TCPImpl::slotTradeCbk(AllTrade::ErrorCodeType errcode, const std::string& user_id, const AllTrade::NPTradeCenter::TradeInfoPtr& trade_ptr)
{
    auto acc_ptr = AllTrade::NPMgrCenter::IManagerCenter::instance()->getAccountByID(user_id.c_str());
    auto push_msg_ptr = PushTradeMsg::getReply(errcode, acc_ptr, gszMsgCommandCode[E_COMM_MSG_TYPE::TRADEOVER_MSG], std::dynamic_pointer_cast<StockTradeInfo>(trade_ptr));
    auto acc_parent_ptr = AllTrade::NPMgrCenter::IManagerCenter::instance()->getAccountByID(acc_ptr->parent_id_);
    if (acc_parent_ptr)
        strncpy_s(push_msg_ptr->m_parent_login_name, acc_parent_ptr->login_name_, sizeof(push_msg_ptr->m_parent_login_name) - 1);
    
    push_msg_ptr->m_stock_ptr = AllTrade::NPMgrCenter::IManagerCenter::instance()->getStockContractByID((std::dynamic_pointer_cast<StockTradeInfo>(trade_ptr))->stock_area_, trade_ptr->contract_id_);
    if (!push_msg_ptr->m_stock_ptr)
    {
        assert(0);
        return;
    }
    writeToAll(user_id.c_str(), acc_ptr->login_name_, QString::fromUtf8(push_msg_ptr->to_string().c_str()));
}

void TCPImpl::slotPositionCbk(AllTrade::ErrorCodeType errcode, const std::string& user_id, const AllTrade::NPTradeCenter::PositionInfoPtr& position_ptr)
{
    auto acc_ptr = AllTrade::NPMgrCenter::IManagerCenter::instance()->getAccountByID(user_id.c_str());
    auto push_msg_ptr = PushPositionMsg::getReply(errcode, acc_ptr, gszMsgCommandCode[E_COMM_MSG_TYPE::POSITION_MSG], position_ptr);
    auto acc_parent_ptr = AllTrade::NPMgrCenter::IManagerCenter::instance()->getAccountByID(acc_ptr->parent_id_);
    if (acc_parent_ptr)
        strncpy_s(push_msg_ptr->m_parent_login_name, acc_parent_ptr->login_name_, sizeof(push_msg_ptr->m_parent_login_name) - 1);
    
    push_msg_ptr->m_stock_ptr = AllTrade::NPMgrCenter::IManagerCenter::instance()->getStockContractByID((std::dynamic_pointer_cast<StockPositionInfo>(position_ptr))->stock_area_, position_ptr->contract_id_);
    if (!push_msg_ptr->m_stock_ptr)
    {
        assert(0);
        return;
    }
    writeToAll(user_id.c_str(), acc_ptr->login_name_, QString::fromUtf8(push_msg_ptr->to_string().c_str()));
}

void TCPImpl::slotMoneyCbk(const std::string& user_id, const AllTrade::NPMgrCenter::SMoneyInfoPtr& money_ptr)
{
    auto acc_ptr = AllTrade::NPMgrCenter::IManagerCenter::instance()->getAccountByID(user_id.c_str());
    auto push_msg_ptr = PushMoneyMsg::getReply(Err_Succeed, acc_ptr, gszMsgCommandCode[E_COMM_MSG_TYPE::MONEYCHANGE_MSG]
        , AllTrade::NPMgrCenter::IManagerCenter::instance()->getMoneyInfoByLoginName(acc_ptr->login_name_));
    auto acc_parent_ptr = AllTrade::NPMgrCenter::IManagerCenter::instance()->getAccountByID(acc_ptr->parent_id_);
    if (acc_parent_ptr)
        strncpy_s(push_msg_ptr->m_parent_login_name, acc_parent_ptr->login_name_, sizeof(push_msg_ptr->m_parent_login_name) - 1);
    
    writeToAll(user_id.c_str(), acc_ptr->login_name_, QString::fromUtf8(push_msg_ptr->to_string().c_str()));
}

void TCPImpl::slotRiskControlCbk(const std::string& user_id, const std::string& date_time, AllTrade::RiskControlType rc_type, const std::string& remark_text)
{
    auto push_msg_ptr = PushRiskControlMsg::getReply(Err_Succeed, gszMsgCommandCode[E_COMM_MSG_TYPE::RISKTIGGER_MSG]);
    push_msg_ptr->m_account = AllTrade::NPMgrCenter::IManagerCenter::instance()->getAccountByID(user_id.c_str());
    strncpy_s(push_msg_ptr->m_date_time, date_time.c_str(), sizeof(push_msg_ptr->m_date_time) - 1);
    push_msg_ptr->m_rc_type = rc_type;
    strncpy_s(push_msg_ptr->m_remark_text, remark_text.c_str(), sizeof(push_msg_ptr->m_remark_text) - 1);
    writeToMC(user_id.c_str(), QString::fromUtf8(push_msg_ptr->to_string().c_str()));
}

void TCPImpl::onOrderInsertCbk(AllTrade::ErrorCodeType errcode, const AllTrade::UserIDType user_id, const AllTrade::NPTradeCenter::OrderInfoPtr& order_ptr, const AllTrade::NPMgrCenter::SOnlineAccountPtr& user_ptr)
{
    emit sglOrderInsertCbk(errcode, user_id, order_ptr, user_ptr);
}

void TCPImpl::onOrderCancelCbk(AllTrade::ErrorCodeType errcode, const AllTrade::UserIDType user_id, const AllTrade::NPTradeCenter::OrderInfoPtr& order_ptr, const AllTrade::NPMgrCenter::SOnlineAccountPtr& user_ptr)
{
    emit sglOrderCancelCbk(errcode, user_id, order_ptr);
}

void TCPImpl::onOrderChangeCbk(AllTrade::ErrorCodeType errcode, const AllTrade::UserIDType user_id, const AllTrade::NPTradeCenter::OrderInfoPtr& order_ptr)
{
    emit sglOrderChangeCbk(errcode, user_id, order_ptr);
}

void TCPImpl::onTradeCbk(AllTrade::ErrorCodeType errcode, const AllTrade::UserIDType user_id, const AllTrade::NPTradeCenter::TradeInfoPtr& trade_ptr)
{
    emit sglTradeCbk(errcode, user_id, trade_ptr);
}

void TCPImpl::onPositionCbk(AllTrade::ErrorCodeType errcode, const AllTrade::UserIDType user_id, const AllTrade::NPTradeCenter::PositionInfoPtr& position_ptr)
{
    emit sglPositionCbk(errcode, user_id, position_ptr);
}

void TCPImpl::onMoneyCbk(const AllTrade::UserIDType user_id, const AllTrade::NPMgrCenter::SMoneyInfoPtr& money_ptr)
{
    emit sglMoneyCbk(user_id, money_ptr);
}

void TCPImpl::onRiskControlCbk(const AllTrade::UserIDType user_id, const AllTrade::DateTimeType date_time, AllTrade::RiskControlType rc_type, const AllTrade::RemarkTextType remark_text)
{
    emit sglRiskControlCbk(user_id, date_time, rc_type, remark_text);
}

void TCPImpl::receivedMsgProcess(QByteArray str, qintptr socketDescriptor)
{
    postDispMsg(GeneralTaskCmd2::create(shared_from_this(), &TCPImpl::onReceivedMsgProcess, str, socketDescriptor));
}

void TCPImpl::onReceivedMsgProcess(QByteArray str, qintptr socketDescriptor)
{
    // 根据内容创建消息
    std::vector<RequestPtr> msgs = createRequest(str, socketDescriptor);

    for (auto msg : msgs)
    {
        // 无效消息返回错误
        if (!msg)
        {
            sendMessageInter(ReplyMsg::getReply(Err_Unknown, socketDescriptor, ""));
            continue;
        }

        // 生成对应的消息对象
        CommMsgPtr pacm_msg;
        AllTrade::ErrorCodeType rslt;

        std::tie(pacm_msg, rslt) = CommMsgBase::create(msg);
        if (rslt != Err_Succeed || !pacm_msg)
        {
            sendMessageInter(ReplyMsg::getReply(rslt, socketDescriptor, msg->command_));
            continue;
        }

        // 访问"visit"以处理各个消息
        pacm_msg->Accept(m_recvMsgVisitor);
    }
}

std::vector<RequestPtr> TCPImpl::createRequest(QByteArray all_msg_str, qintptr socketDescriptor)
{// 带包头包尾
    static QByteArray last_msg;

    all_msg_str = last_msg + all_msg_str;
    std::string login_name = m_sockets.getLoginNameByDescript(socketDescriptor);
    std::vector<RequestPtr> rslt;

    QString content;
    QString tmpMsgHeader = QString::fromLocal8Bit(gszMsgHeader);
    QString tmpMsgEndFlag = QString::fromLocal8Bit(gszMsgEndFlag);
    
    int str_startpos(all_msg_str.indexOf(tmpMsgHeader)), end_startpos(all_msg_str.indexOf(tmpMsgEndFlag));
    int msghead_size(tmpMsgHeader.toLocal8Bit().length());
    if (str_startpos == -1 || end_startpos == -1)
        last_msg = all_msg_str;

    while (str_startpos != -1 && end_startpos != -1)
    {
        CommonTools::ScopeGuard ext([&]{
            last_msg = all_msg_str.right(all_msg_str.length() - end_startpos - tmpMsgEndFlag.length());

            str_startpos = all_msg_str.indexOf(tmpMsgHeader, str_startpos + msghead_size);
            end_startpos = all_msg_str.indexOf(tmpMsgEndFlag, end_startpos + 1);
        });
        str_startpos = str_startpos + msghead_size;
        content = all_msg_str.mid(str_startpos, end_startpos - str_startpos);
        QJsonParseError error;
        QJsonDocument jsonDocument = QJsonDocument::fromJson(content.toUtf8(), &error);
        if (error.error == QJsonParseError::NoError) {
            if (jsonDocument.isObject())
            {
                RequestPtr ptr = std::make_shared<Request>();
                ptr->socketDescriptor_ = socketDescriptor;
                ptr->session_ptr_ = this;
                auto rsltMap = jsonDocument.toVariant().toMap();
                ptr->command_ = rsltMap[CMDCODE].toString().toUtf8();
                int startpos = content.indexOf(CONTENT);
                if (startpos == -1)
                {
                    rslt.push_back(ptr);
                    continue;
                }

				size_t msgcontent_size(strnlen_s(CONTENT, 10));
				startpos = startpos + msgcontent_size + 2;// 包含":

                int endpos = content.lastIndexOf("}");
                if (endpos == -1)
                {
                    rslt.push_back(ptr);
                    continue;
                }

                ptr->parameters_ = content.mid(startpos, endpos - startpos).toUtf8();
                ptr->login_name_ = login_name;
                rslt.push_back(ptr);
            }
        }
    }
    return rslt;
}

void TCPImpl::sendMessageInter(ReplyMsgPtr reply_ptr)
{
    assert(reply_ptr);
    write(reply_ptr->getSocketID(), QString::fromUtf8(reply_ptr->to_string().c_str()));
}

void TCPImpl::sendMessageToAllInter(const AllTrade::UserIDType user_id, const AllTrade::LoginNameType login_name, ReplyMsgPtr reply_ptr)
{
    writeToAll(user_id, login_name, QString::fromUtf8(reply_ptr->to_string().c_str()));
}

void TCPImpl::setLoginName(qintptr socket_id, const AllTrade::LoginNameType login_name)
{
    m_sockets.setLoginName(socket_id, login_name);
}

void TCPImpl::closeSocketInter(qintptr socket_id)
{
    auto ptr = const_cast<QTcpSocket*>(m_sockets.getSocketPtrByDescript(socket_id));
    if (ptr)
        closeSocket(ptr);
}

std::string TCPImpl::getAddrBySocketID(qintptr socket_id)
{
    auto ptr = const_cast<QTcpSocket*>(m_sockets.getSocketPtrByDescript(socket_id));
    if (ptr)
        return ptr->peerAddress().toString().toLocal8Bit().data();

    return "";
}

void TCPImpl::write(qintptr socketDescriptor, const QString& str)
{
    FortuneThread* thread = m_sockets.getFortuneThreadByDescript(socketDescriptor);
	if (thread)
        thread->write(QString::fromLocal8Bit(gszMsgHeader) + str + QString::fromLocal8Bit(gszMsgEndFlag));
}

void TCPImpl::write(const AllTrade::LoginNameType login_name, const QString& str)
{
    std::vector<FortuneThread*> threads = m_sockets.getFortuneThreadByLoginName(login_name);
    for (auto thread : threads)
    {
        if (thread)
            thread->write(QString::fromLocal8Bit(gszMsgHeader) + str + QString::fromLocal8Bit(gszMsgEndFlag));
    }
}

void TCPImpl::writeToAll(const AllTrade::UserIDType user_id, const AllTrade::LoginNameType login_name, const QString& str)
{
    write(login_name, str);

    auto acc_ptrs = AllTrade::NPMgrCenter::IManagerCenter::instance()->getAllParentsByID(user_id);
    for (auto& acc_ptr : acc_ptrs)
    {
        write(acc_ptr->login_name_, str);
    }
}

void TCPImpl::writeToMC(const AllTrade::UserIDType user_id, const QString& str)
{
    auto acc_ptrs = AllTrade::NPMgrCenter::IManagerCenter::instance()->getAllParentsByID(user_id);
    for (auto& acc_ptr : acc_ptrs)
    {
        write(acc_ptr->login_name_, str);
    }
}

long TCPImpl::on_threadstart(void* param)
{
    return CommonTools::dispatcher_error_no_error;
}

long TCPImpl::on_threadstop(void* param)
{
    return CommonTools::dispatcher_error_no_error;
}

long TCPImpl::on_message(CommonTools::CommandPtr msg, bool cleanup)
{
    try {
        msg->execute();
    }
    catch (std::exception&) {
        assert(0);
    }
    return CommonTools::dispatcher_error_no_error;
}

long TCPImpl::on_event(CommonTools::handler evt)
{
    return CommonTools::dispatcher_error_no_error;
}

void TCPImpl::RecvMsgVisitor::Visit(xyc_communication::CommMsgLogin& msg)
{
    if (msg.getType() == E_COMM_MSG_TYPE::EMPT_Init_Null
        || msg.getType() >= E_COMM_MSG_TYPE::EMPT_Max_Count)
    {
        m_pParent->sendMessageInter(ReplyMsg::getReply(msg.getRequest(), Err_Req_Parameter));
    }
    else
    {
        ReplyLoginMsgPtr ptr = ReplyLoginMsg::getReply(msg.getRequest());
        m_pParent->sendMessageInter(ptr);
        if (ptr->getResult() == Err_Succeed)
        {
            auto login_acc = AllTrade::NPMgrCenter::IManagerCenter::instance()->getAccountByLoginName(ptr->m_login_name);
            if (!login_acc) return;

            strncpy_s(ptr->m_login_info->user_id_, login_acc->user_id_, sizeof(ptr->m_login_info->user_id_));
            auto socket_ptr = m_pParent->m_sockets.getSocketPtrByDescript(msg.getRequest()->socketDescriptor_);
            if (socket_ptr)
                strncpy_s(ptr->m_login_info->login_ip_, QHostAddress(socket_ptr->peerAddress().toIPv4Address()).toString().toLocal8Bit().data(), sizeof(ptr->m_login_info->login_ip_) - 1);
            AllTrade::OnlineUserManager::instance()->addLoginUser(ptr->m_login_info);

            if (login_acc->prop_ == E_ACCOUNT_PROP::EAP_Trader)
                return;

            auto vec = m_pParent->m_sockets.getSocketDescriptByLoginName(ptr->m_login_name);
            for (auto item : vec)
            {
                if (item == ptr->getSocketID())
                    continue;

                RequestPtr req_ptr = std::make_shared<Request>();
                req_ptr->login_name_ = ptr->m_login_name;
                req_ptr->command_ = gszMsgCommandCode[E_COMM_MSG_TYPE::LOGIN_QUIT_MSG];
                req_ptr->socketDescriptor_ = item;

                m_pParent->sendMessageInter(ReplyMsg::getReply(req_ptr, Error_User_Other_Login));
                m_pParent->closeSocketInter(item);
            }

        }
        
    }
}

void TCPImpl::RecvMsgVisitor::Visit(xyc_communication::CommMsgLogout& msg)
{
    if (msg.getType() == E_COMM_MSG_TYPE::EMPT_Init_Null
        || msg.getType() >= E_COMM_MSG_TYPE::EMPT_Max_Count)
    {
        m_pParent->sendMessageInter(ReplyMsg::getReply(msg.getRequest(), Err_Req_Parameter));
    }
    else
    {
        m_pParent->sendMessageInter(ReplyMsg::getReply(msg.getRequest(), Err_Pending));
        m_pParent->closeSocketInter(msg.getSocketID());
    }
}

void TCPImpl::RecvMsgVisitor::Visit(xyc_communication::CommMsgHeartBeat& msg)
{
    if (msg.getType() == E_COMM_MSG_TYPE::EMPT_Init_Null
        || msg.getType() >= E_COMM_MSG_TYPE::EMPT_Max_Count)
    {
        m_pParent->sendMessageInter(ReplyMsg::getReply(msg.getRequest(), Err_Req_Parameter));
    }
    else
    {
        m_pParent->sendMessageInter(ReplyMsg::getReply(msg.getRequest(), Err_Succeed));
    }
}

void TCPImpl::RecvMsgVisitor::Visit(xyc_communication::CommMsgAgencyQry& msg)
{
    if (msg.getType() == E_COMM_MSG_TYPE::EMPT_Init_Null
        || msg.getType() >= E_COMM_MSG_TYPE::EMPT_Max_Count)
    {
        m_pParent->sendMessageInter(ReplyMsg::getReply(msg.getRequest(), Err_Req_Parameter));
    }
    else if (msg.getRequest()->login_name_.empty())
    {
        m_pParent->sendMessageInter(ReplyMsg::getReply(msg.getRequest(), Err_Not_Login));
    }
    else
    {
        m_pParent->sendMessageInter(ReplyMsg::getReply(msg.getRequest(), Err_Pending));
        AsyncQryService::instance()->qryUsingAgencys(ReplyAgencyQryMsg::getReply(msg.getRequest()));
    }
}

void TCPImpl::RecvMsgVisitor::Visit(xyc_communication::CommMsgAgencyPreApprovalQry& msg)
{
    if (msg.getType() == E_COMM_MSG_TYPE::EMPT_Init_Null
        || msg.getType() >= E_COMM_MSG_TYPE::EMPT_Max_Count)
    {
        m_pParent->sendMessageInter(ReplyMsg::getReply(msg.getRequest(), Err_Req_Parameter));
    }
    else if (msg.getRequest()->login_name_.empty())
    {
        m_pParent->sendMessageInter(ReplyMsg::getReply(msg.getRequest(), Err_Not_Login));
    }
    else
    {
        m_pParent->sendMessageInter(ReplyMsg::getReply(msg.getRequest(), Err_Pending));
        AsyncQryService::instance()->qryCheckingAgencys(ReplyAgencyPreApprovalQryMsg::getReply(msg.getRequest()));
    }
}

void TCPImpl::RecvMsgVisitor::Visit(xyc_communication::CommMsgAgencyLinkQry& msg)
{

}

void TCPImpl::RecvMsgVisitor::Visit(xyc_communication::CommMsgRolesQry& msg)
{
	if (msg.getType() == E_COMM_MSG_TYPE::EMPT_Init_Null
		|| msg.getType() >= E_COMM_MSG_TYPE::EMPT_Max_Count)
	{
		m_pParent->sendMessageInter(ReplyMsg::getReply(msg.getRequest(), Err_Req_Parameter));
	}
    else if (msg.getRequest()->login_name_.empty())
    {
        m_pParent->sendMessageInter(ReplyMsg::getReply(msg.getRequest(), Err_Not_Login));
    }
    else
	{
		m_pParent->sendMessageInter(ReplyMsg::getReply(msg.getRequest(), Err_Pending));
		AsyncQryService::instance()->qryRoleInfo(ReplyRolesQryMsg::getReply(msg.getRequest()));
	}
}

void TCPImpl::RecvMsgVisitor::Visit(xyc_communication::CommMsgAgencyRolesQry& msg)
{
	if (msg.getType() == E_COMM_MSG_TYPE::EMPT_Init_Null
		|| msg.getType() >= E_COMM_MSG_TYPE::EMPT_Max_Count)
	{
		m_pParent->sendMessageInter(ReplyMsg::getReply(msg.getRequest(), Err_Req_Parameter));
	}
    else if (msg.getRequest()->login_name_.empty())
    {
        m_pParent->sendMessageInter(ReplyMsg::getReply(msg.getRequest(), Err_Not_Login));
    }
    else
	{
		m_pParent->sendMessageInter(ReplyMsg::getReply(msg.getRequest(), Err_Pending));
		AsyncQryService::instance()->getRoleUserInfo(ReplyAgencyRolesQryMsg::getReply(msg.getRequest()));
	}
}

void TCPImpl::RecvMsgVisitor::Visit(xyc_communication::CommMsgCommissQry& msg)
{
    if (msg.getType() == E_COMM_MSG_TYPE::EMPT_Init_Null
        || msg.getType() >= E_COMM_MSG_TYPE::EMPT_Max_Count)
    {
        m_pParent->sendMessageInter(ReplyMsg::getReply(msg.getRequest(), Err_Req_Parameter));
    }
    else if (msg.getRequest()->login_name_.empty())
    {
        m_pParent->sendMessageInter(ReplyMsg::getReply(msg.getRequest(), Err_Not_Login));
    }
    else
    {
        m_pParent->sendMessageInter(ReplyMsg::getReply(msg.getRequest(), Err_Pending));
        AsyncQryService::instance()->qryAgencyCommissInfo(ReplyCommissQryMsg::getReply(msg.getRequest()));
    }
}

void TCPImpl::RecvMsgVisitor::Visit(xyc_communication::CommMsgCommissDtlQry& msg)
{
    if (msg.getType() == E_COMM_MSG_TYPE::EMPT_Init_Null
        || msg.getType() >= E_COMM_MSG_TYPE::EMPT_Max_Count)
    {
        m_pParent->sendMessageInter(ReplyMsg::getReply(msg.getRequest(), Err_Req_Parameter));
    }
    else if (msg.getRequest()->login_name_.empty())
    {
        m_pParent->sendMessageInter(ReplyMsg::getReply(msg.getRequest(), Err_Not_Login));
    }
    else
    {
        m_pParent->sendMessageInter(ReplyMsg::getReply(msg.getRequest(), Err_Pending));
        AsyncQryService::instance()->qryAgencyCommissDtlInfo(ReplyCommissDtlQryMsg::getReply(msg.getRequest()));
    }
}

void TCPImpl::RecvMsgVisitor::Visit(xyc_communication::CommMsgProfitCommisslQry& msg)
{
    if (msg.getType() == E_COMM_MSG_TYPE::EMPT_Init_Null
        || msg.getType() >= E_COMM_MSG_TYPE::EMPT_Max_Count)
    {
        m_pParent->sendMessageInter(ReplyMsg::getReply(msg.getRequest(), Err_Req_Parameter));
    }
    else if (msg.getRequest()->login_name_.empty())
    {
        m_pParent->sendMessageInter(ReplyMsg::getReply(msg.getRequest(), Err_Not_Login));
    }
    else
    {
        m_pParent->sendMessageInter(ReplyMsg::getReply(msg.getRequest(), Err_Pending));
        AsyncQryService::instance()->qryAgencyProfitInfo(ReplyProfitCommisslQryMsg::getReply(msg.getRequest()));
    }
}

void TCPImpl::RecvMsgVisitor::Visit(xyc_communication::CommMsgProfitCommissDtlQry& msg)
{
    if (msg.getType() == E_COMM_MSG_TYPE::EMPT_Init_Null
        || msg.getType() >= E_COMM_MSG_TYPE::EMPT_Max_Count)
    {
        m_pParent->sendMessageInter(ReplyMsg::getReply(msg.getRequest(), Err_Req_Parameter));
    }
    else if (msg.getRequest()->login_name_.empty())
    {
        m_pParent->sendMessageInter(ReplyMsg::getReply(msg.getRequest(), Err_Not_Login));
    }
    else
    {
        m_pParent->sendMessageInter(ReplyMsg::getReply(msg.getRequest(), Err_Pending));
        AsyncQryService::instance()->qryAgencyProfitDtlInfo(ReplyProfitCommissDtlQryMsg::getReply(msg.getRequest()));
    }
}

void TCPImpl::RecvMsgVisitor::Visit(xyc_communication::CommMsgToplogicalTreeQry& msg)
{

}

void TCPImpl::RecvMsgVisitor::Visit(xyc_communication::CommMsgChildAccQry& msg)
{
    if (msg.getType() == E_COMM_MSG_TYPE::EMPT_Init_Null
        || msg.getType() >= E_COMM_MSG_TYPE::EMPT_Max_Count)
    {
        m_pParent->sendMessageInter(ReplyMsg::getReply(msg.getRequest(), Err_Req_Parameter));
    }
    else if (msg.getRequest()->login_name_.empty())
    {
        m_pParent->sendMessageInter(ReplyMsg::getReply(msg.getRequest(), Err_Not_Login));
    }
    else
    {
        m_pParent->sendMessageInter(ReplyMsg::getReply(msg.getRequest(), Err_Pending));
        AsyncQryService::instance()->qryUsingTradeAcc(ReplyChildAccQryMsg::getReply(msg.getRequest()));
    }
}

void TCPImpl::RecvMsgVisitor::Visit(xyc_communication::CommMsgChildApprovalQry& msg)
{
    if (msg.getType() == E_COMM_MSG_TYPE::EMPT_Init_Null
        || msg.getType() >= E_COMM_MSG_TYPE::EMPT_Max_Count)
    {
        m_pParent->sendMessageInter(ReplyMsg::getReply(msg.getRequest(), Err_Req_Parameter));
    }
    else if (msg.getRequest()->login_name_.empty())
    {
        m_pParent->sendMessageInter(ReplyMsg::getReply(msg.getRequest(), Err_Not_Login));
    }
    else
    {
        m_pParent->sendMessageInter(ReplyMsg::getReply(msg.getRequest(), Err_Pending));
        AsyncQryService::instance()->qryCheckingTradeAcc(ReplyChildApprovalQryMsg::getReply(msg.getRequest()));
    }
}

void TCPImpl::RecvMsgVisitor::Visit(xyc_communication::CommMsgFundAccQry& msg)
{
    if (msg.getType() == E_COMM_MSG_TYPE::EMPT_Init_Null
        || msg.getType() >= E_COMM_MSG_TYPE::EMPT_Max_Count)
    {
        m_pParent->sendMessageInter(ReplyMsg::getReply(msg.getRequest(), Err_Req_Parameter));
    }
    else if (msg.getRequest()->login_name_.empty())
    {
        m_pParent->sendMessageInter(ReplyMsg::getReply(msg.getRequest(), Err_Not_Login));
    }
    else
    {
        m_pParent->sendMessageInter(ReplyMsg::getReply(msg.getRequest(), Err_Pending));
        AsyncQryService::instance()->qryUsingFunderAcc(ReplyFundAccQryMsg::getReply(msg.getRequest()));
    }
}

void TCPImpl::RecvMsgVisitor::Visit(xyc_communication::CommMsgOnlineAccQry& msg)
{
    if (msg.getType() == E_COMM_MSG_TYPE::EMPT_Init_Null
        || msg.getType() >= E_COMM_MSG_TYPE::EMPT_Max_Count)
    {
        m_pParent->sendMessageInter(ReplyMsg::getReply(msg.getRequest(), Err_Req_Parameter));
    }
    else
    {
        m_pParent->sendMessageInter(ReplyMsg::getReply(msg.getRequest(), Err_Pending));

        std::vector<AllTrade::NPMgrCenter::SAccountPtr> rslt;
        bool bFind(false);
        ReplyOnlineAccQryMsgPtr msg_ptr = ReplyOnlineAccQryMsg::getReply(msg.getRequest());
        AsyncQryService::instance()->getOnlineChildren(bFind, rslt, msg_ptr);
        if (bFind)
        {
            for (auto item : rslt)
            {
                auto sess_vec = m_pParent->m_sockets.getSocketDescriptByLoginName(item->login_name_);
                AllTrade::NPMgrCenter::SOnlineAccountPtr ptr(nullptr);
                for (auto& sess_item : sess_vec)
                {
                    ptr = AllTrade::OnlineUserManager::instance()->getLoginInfo(sess_item);
                    if (!ptr)
                        continue;
                    strncpy_s(msg_ptr->m_rtn_loginName, item->login_name_, sizeof(msg_ptr->m_rtn_loginName));
                    strncpy_s(msg_ptr->m_rtn_accName, item->login_name_, sizeof(msg_ptr->m_rtn_accName));
                    strncpy_s(msg_ptr->m_rtn_reg_dt, item->regist_datetime_, sizeof(msg_ptr->m_rtn_reg_dt));
                    msg_ptr->m_rtn_acc = ptr;
                    m_pParent->sendMessageInter(msg_ptr);
                }
            }
            msg_ptr->m_blast = true;
            m_pParent->sendMessageInter(msg_ptr);
        }
    }
}

void TCPImpl::RecvMsgVisitor::Visit(xyc_communication::CommMsgStockContractQry& msg)
{
    if (msg.getType() == E_COMM_MSG_TYPE::EMPT_Init_Null
        || msg.getType() >= E_COMM_MSG_TYPE::EMPT_Max_Count)
    {
        m_pParent->sendMessageInter(ReplyMsg::getReply(msg.getRequest(), Err_Req_Parameter));
    }
    else
    {
        m_pParent->sendMessageInter(ReplyMsg::getReply(msg.getRequest(), Err_Pending));
        AsyncQryService::instance()->qryStockContract(ReplyStockContractQryMsg::getReply(msg.getRequest()));
    }
}

void TCPImpl::RecvMsgVisitor::Visit(xyc_communication::CommMsgStockBlackQry& msg)
{
    if (msg.getType() == E_COMM_MSG_TYPE::EMPT_Init_Null
        || msg.getType() >= E_COMM_MSG_TYPE::EMPT_Max_Count)
    {
        m_pParent->sendMessageInter(ReplyMsg::getReply(msg.getRequest(), Err_Req_Parameter));
    }
    else if (msg.getRequest()->login_name_.empty())
    {
        m_pParent->sendMessageInter(ReplyMsg::getReply(msg.getRequest(), Err_Not_Login));
    }
    else
    {
        m_pParent->sendMessageInter(ReplyMsg::getReply(msg.getRequest(), Err_Pending));
        AsyncQryService::instance()->qryStockBlackWhiteStatus(ReplyStockBlackQryMsg::getReply(msg.getRequest()));
    }
}

void TCPImpl::RecvMsgVisitor::Visit(xyc_communication::CommMsgForbidBuySellQry& msg)
{
    if (msg.getType() == E_COMM_MSG_TYPE::EMPT_Init_Null
        || msg.getType() >= E_COMM_MSG_TYPE::EMPT_Max_Count)
    {
        m_pParent->sendMessageInter(ReplyMsg::getReply(msg.getRequest(), Err_Req_Parameter));
    }
    else if (msg.getRequest()->login_name_.empty())
    {
        m_pParent->sendMessageInter(ReplyMsg::getReply(msg.getRequest(), Err_Not_Login));
    }
    else
    {
        m_pParent->sendMessageInter(ReplyMsg::getReply(msg.getRequest(), Err_Pending));
        AsyncQryService::instance()->qryForbidTradeStatus(ReplyForbidBuySellQryMsg::getReply(msg.getRequest()));
    }
}

void TCPImpl::RecvMsgVisitor::Visit(xyc_communication::CommMsgPosiRateQry& msg)
{
    if (msg.getType() == E_COMM_MSG_TYPE::EMPT_Init_Null
        || msg.getType() >= E_COMM_MSG_TYPE::EMPT_Max_Count)
    {
        m_pParent->sendMessageInter(ReplyMsg::getReply(msg.getRequest(), Err_Req_Parameter));
    }
    else if (msg.getRequest()->login_name_.empty())
    {
        m_pParent->sendMessageInter(ReplyMsg::getReply(msg.getRequest(), Err_Not_Login));
    }
    else
    {
        m_pParent->sendMessageInter(ReplyMsg::getReply(msg.getRequest(), Err_Pending));
        AsyncQryService::instance()->qryPosiRateStatus(ReplyPosiRateQryMsg::getReply(msg.getRequest()));
    }
}

void TCPImpl::RecvMsgVisitor::Visit(xyc_communication::CommMsgPosiQry& msg)
{
    if (msg.getType() == E_COMM_MSG_TYPE::EMPT_Init_Null
        || msg.getType() >= E_COMM_MSG_TYPE::EMPT_Max_Count)
    {
        m_pParent->sendMessageInter(ReplyMsg::getReply(msg.getRequest(), Err_Req_Parameter));
    }
    else if (msg.getRequest()->login_name_.empty())
    {
        m_pParent->sendMessageInter(ReplyMsg::getReply(msg.getRequest(), Err_Not_Login));
    }
    else
    {
        m_pParent->sendMessageInter(ReplyMsg::getReply(msg.getRequest(), Err_Pending));
        AsyncQryService::instance()->qryPosition(ReplyPosiQryMsg::getReply(msg.getRequest()));
    }
}

void TCPImpl::RecvMsgVisitor::Visit(xyc_communication::CommMsgCurrentyEntrustQry& msg)
{
    if (msg.getType() == E_COMM_MSG_TYPE::EMPT_Init_Null
        || msg.getType() >= E_COMM_MSG_TYPE::EMPT_Max_Count)
    {
        m_pParent->sendMessageInter(ReplyMsg::getReply(msg.getRequest(), Err_Req_Parameter));
    }
    else if (msg.getRequest()->login_name_.empty())
    {
        m_pParent->sendMessageInter(ReplyMsg::getReply(msg.getRequest(), Err_Not_Login));
    }
    else
    {
        m_pParent->sendMessageInter(ReplyMsg::getReply(msg.getRequest(), Err_Pending));
        AsyncQryService::instance()->qryCurrentyEntrust(ReplyCurrentyEntrustQryMsg::getReply(msg.getRequest()));
    }
}

void TCPImpl::RecvMsgVisitor::Visit(xyc_communication::CommMsgTodayEntrustQry& msg)
{
    if (msg.getType() == E_COMM_MSG_TYPE::EMPT_Init_Null
        || msg.getType() >= E_COMM_MSG_TYPE::EMPT_Max_Count)
    {
        m_pParent->sendMessageInter(ReplyMsg::getReply(msg.getRequest(), Err_Req_Parameter));
    }
    else if (msg.getRequest()->login_name_.empty())
    {
        m_pParent->sendMessageInter(ReplyMsg::getReply(msg.getRequest(), Err_Not_Login));
    }
    else
    {
        m_pParent->sendMessageInter(ReplyMsg::getReply(msg.getRequest(), Err_Pending));
        AsyncQryService::instance()->qryTodayEntrust(ReplyTodayEntrustQryMsg::getReply(msg.getRequest()));
    }
}

void TCPImpl::RecvMsgVisitor::Visit(xyc_communication::CommMsgHistoryEntrustQry& msg)
{
    if (msg.getType() == E_COMM_MSG_TYPE::EMPT_Init_Null
        || msg.getType() >= E_COMM_MSG_TYPE::EMPT_Max_Count)
    {
        m_pParent->sendMessageInter(ReplyMsg::getReply(msg.getRequest(), Err_Req_Parameter));
    }
    else if (msg.getRequest()->login_name_.empty())
    {
        m_pParent->sendMessageInter(ReplyMsg::getReply(msg.getRequest(), Err_Not_Login));
    }
    else
    {
        m_pParent->sendMessageInter(ReplyMsg::getReply(msg.getRequest(), Err_Pending));
        AsyncQryService::instance()->qryHistoryEntrust(ReplyHistoryEntrustQryMsg::getReply(msg.getRequest()));
    }
}

void TCPImpl::RecvMsgVisitor::Visit(xyc_communication::CommMsgTradeQry& msg)
{
    if (msg.getType() == E_COMM_MSG_TYPE::EMPT_Init_Null
        || msg.getType() >= E_COMM_MSG_TYPE::EMPT_Max_Count)
    {
        m_pParent->sendMessageInter(ReplyMsg::getReply(msg.getRequest(), Err_Req_Parameter));
    }
    else if (msg.getRequest()->login_name_.empty())
    {
        m_pParent->sendMessageInter(ReplyMsg::getReply(msg.getRequest(), Err_Not_Login));
    }
    else
    {
        m_pParent->sendMessageInter(ReplyMsg::getReply(msg.getRequest(), Err_Pending));
        AsyncQryService::instance()->qryTrade(ReplyTradeQryMsg::getReply(msg.getRequest()));
    }
}

void TCPImpl::RecvMsgVisitor::Visit(xyc_communication::CommMsgHistoryTradeQry& msg)
{
    if (msg.getType() == E_COMM_MSG_TYPE::EMPT_Init_Null
        || msg.getType() >= E_COMM_MSG_TYPE::EMPT_Max_Count)
    {
        m_pParent->sendMessageInter(ReplyMsg::getReply(msg.getRequest(), Err_Req_Parameter));
    }
    else if (msg.getRequest()->login_name_.empty())
    {
        m_pParent->sendMessageInter(ReplyMsg::getReply(msg.getRequest(), Err_Not_Login));
    }
    else
    {
        m_pParent->sendMessageInter(ReplyMsg::getReply(msg.getRequest(), Err_Pending));
        AsyncQryService::instance()->qryHistoryTrade(ReplyHistoryTradeQryMsg::getReply(msg.getRequest()));
    }
}

void TCPImpl::RecvMsgVisitor::Visit(xyc_communication::CommMsgFundQry& msg)
{
    if (msg.getType() == E_COMM_MSG_TYPE::EMPT_Init_Null
        || msg.getType() >= E_COMM_MSG_TYPE::EMPT_Max_Count)
    {
        m_pParent->sendMessageInter(ReplyMsg::getReply(msg.getRequest(), Err_Req_Parameter));
    }
    else if (msg.getRequest()->login_name_.empty())
    {
        m_pParent->sendMessageInter(ReplyMsg::getReply(msg.getRequest(), Err_Not_Login));
    }
    else
    {
        m_pParent->sendMessageInter(ReplyMsg::getReply(msg.getRequest(), Err_Pending));
        AsyncQryService::instance()->qryAccountFund(ReplyFundQryMsg::getReply(msg.getRequest()));
    }
}

void TCPImpl::RecvMsgVisitor::Visit(xyc_communication::CommMsgFundSerialQry& msg)
{
    if (msg.getType() == E_COMM_MSG_TYPE::EMPT_Init_Null
        || msg.getType() >= E_COMM_MSG_TYPE::EMPT_Max_Count)
    {
        m_pParent->sendMessageInter(ReplyMsg::getReply(msg.getRequest(), Err_Req_Parameter));
    }
    else if (msg.getRequest()->login_name_.empty())
    {
        m_pParent->sendMessageInter(ReplyMsg::getReply(msg.getRequest(), Err_Not_Login));
    }
    else
    {
        m_pParent->sendMessageInter(ReplyMsg::getReply(msg.getRequest(), Err_Pending));
        AsyncQryService::instance()->qryHistoryFundSerial(ReplyFundSerialQryMsg::getReply(msg.getRequest()));
    }
}

void TCPImpl::RecvMsgVisitor::Visit(xyc_communication::CommMsgDeliveryQry& msg)
{

}

void TCPImpl::RecvMsgVisitor::Visit(xyc_communication::CommMsgFundMonitQry& msg)
{

}

// void TCPImpl::RecvMsgVisitor::Visit(xyc_communication::CommMsgTimeTradeQry& msg)
// {
// 
// }

void TCPImpl::RecvMsgVisitor::Visit(xyc_communication::CommMsgSumPosiQry& msg)
{

}

void TCPImpl::RecvMsgVisitor::Visit(xyc_communication::CommMsgTimeWarnQry& msg)
{
	if (msg.getType() == E_COMM_MSG_TYPE::EMPT_Init_Null
		|| msg.getType() >= E_COMM_MSG_TYPE::EMPT_Max_Count)
	{
		m_pParent->sendMessageInter(ReplyMsg::getReply(msg.getRequest(), Err_Req_Parameter));
	}
	else if (msg.getRequest()->login_name_.empty())
	{
		m_pParent->sendMessageInter(ReplyMsg::getReply(msg.getRequest(), Err_Not_Login));
	}
	else
	{
		m_pParent->sendMessageInter(ReplyMsg::getReply(msg.getRequest(), Err_Pending));
		AsyncQryService::instance()->qryRiskTimerInfos(ReplyTimeWarnQryMsg::getReply(msg.getRequest()));
	}
}

void TCPImpl::RecvMsgVisitor::Visit(xyc_communication::CommMsgEquipMoneyQry& msg)
{
    if (msg.getType() == E_COMM_MSG_TYPE::EMPT_Init_Null
        || msg.getType() >= E_COMM_MSG_TYPE::EMPT_Max_Count)
    {
        m_pParent->sendMessageInter(ReplyMsg::getReply(msg.getRequest(), Err_Req_Parameter));
    }
    else if (msg.getRequest()->login_name_.empty())
    {
        m_pParent->sendMessageInter(ReplyMsg::getReply(msg.getRequest(), Err_Not_Login));
    }
    else
    {
        m_pParent->sendMessageInter(ReplyMsg::getReply(msg.getRequest(), Err_Pending));
        AsyncQryService::instance()->qryEquipMoneyInfos(ReplyEquipmentMoneyQryMsg::getReply(msg.getRequest()));
    }
}

void TCPImpl::RecvMsgVisitor::Visit(xyc_communication::CommMsgAutoOutMoneyQry& msg)
{
    if (msg.getType() == E_COMM_MSG_TYPE::EMPT_Init_Null
        || msg.getType() >= E_COMM_MSG_TYPE::EMPT_Max_Count)
    {
        m_pParent->sendMessageInter(ReplyMsg::getReply(msg.getRequest(), Err_Req_Parameter));
    }
    else if (msg.getRequest()->login_name_.empty())
    {
        m_pParent->sendMessageInter(ReplyMsg::getReply(msg.getRequest(), Err_Not_Login));
    }
    else
    {
        m_pParent->sendMessageInter(ReplyMsg::getReply(msg.getRequest(), Err_Pending));
        AsyncQryService::instance()->qryAutoOutMoneyInfos(ReplyAutoOutMoneyQryMsg::getReply(msg.getRequest()));
    }
}

void TCPImpl::RecvMsgVisitor::Visit(xyc_communication::CommMsgFeeSetQry& msg)
{
    if (msg.getType() == E_COMM_MSG_TYPE::EMPT_Init_Null
        || msg.getType() >= E_COMM_MSG_TYPE::EMPT_Max_Count)
    {
        m_pParent->sendMessageInter(ReplyMsg::getReply(msg.getRequest(), Err_Req_Parameter));
    }
    else if (msg.getRequest()->login_name_.empty())
    {
        m_pParent->sendMessageInter(ReplyMsg::getReply(msg.getRequest(), Err_Not_Login));
    }
    else
    {
        m_pParent->sendMessageInter(ReplyMsg::getReply(msg.getRequest(), Err_Pending));
        AsyncQryService::instance()->qryFeeSet(ReplyFeeSetQryMsg::getReply(msg.getRequest()));
    }
}

void TCPImpl::RecvMsgVisitor::Visit(xyc_communication::CommMsgManagerQry& msg)
{
    if (msg.getType() == E_COMM_MSG_TYPE::EMPT_Init_Null
        || msg.getType() >= E_COMM_MSG_TYPE::EMPT_Max_Count)
    {
        m_pParent->sendMessageInter(ReplyMsg::getReply(msg.getRequest(), Err_Req_Parameter));
    }
    else if (msg.getRequest()->login_name_.empty())
    {
        m_pParent->sendMessageInter(ReplyMsg::getReply(msg.getRequest(), Err_Not_Login));
    }
    else
    {
        m_pParent->sendMessageInter(ReplyMsg::getReply(msg.getRequest(), Err_Pending));
        AsyncQryService::instance()->qryUsingManagerAcc(ReplyManagerQryMsg::getReply(msg.getRequest()));
    }
}

void TCPImpl::RecvMsgVisitor::Visit(xyc_communication::CommMsgAgencyAdd& msg)
{
    if (msg.getType() == E_COMM_MSG_TYPE::EMPT_Init_Null
        || msg.getType() >= E_COMM_MSG_TYPE::EMPT_Max_Count)
    {
        m_pParent->sendMessageInter(ReplyMsg::getReply(msg.getRequest(), Err_Req_Parameter));
    }
    else if (msg.getRequest()->login_name_.empty())
    {
        m_pParent->sendMessageInter(ReplyMsg::getReply(msg.getRequest(), Err_Not_Login));
    }
    else
    {
        m_pParent->sendMessageInter(ReplyMsg::getReply(msg.getRequest(), Err_Pending));
        AsyncQryService::instance()->addAgencyAcc(ReplyAgencyAddMsg::getReply(msg.getRequest()));
    }

}

void TCPImpl::RecvMsgVisitor::Visit(xyc_communication::CommMsgAgencyChange& msg)
{
    if (msg.getType() == E_COMM_MSG_TYPE::EMPT_Init_Null
        || msg.getType() >= E_COMM_MSG_TYPE::EMPT_Max_Count)
    {
        m_pParent->sendMessageInter(ReplyMsg::getReply(msg.getRequest(), Err_Req_Parameter));
    }
    else if (msg.getRequest()->login_name_.empty())
    {
        m_pParent->sendMessageInter(ReplyMsg::getReply(msg.getRequest(), Err_Not_Login));
    }
    else
    {
        m_pParent->sendMessageInter(ReplyMsg::getReply(msg.getRequest(), Err_Pending));
        AsyncQryService::instance()->changeAgencyAcc(ReplyAgencyChangeMsg::getReply(msg.getRequest()));
    }

}

void TCPImpl::RecvMsgVisitor::Visit(xyc_communication::CommMsgAgencyApproval& msg)
{
    if (msg.getType() == E_COMM_MSG_TYPE::EMPT_Init_Null
        || msg.getType() >= E_COMM_MSG_TYPE::EMPT_Max_Count)
    {
        m_pParent->sendMessageInter(ReplyMsg::getReply(msg.getRequest(), Err_Req_Parameter));
    }
    else if (msg.getRequest()->login_name_.empty())
    {
        m_pParent->sendMessageInter(ReplyMsg::getReply(msg.getRequest(), Err_Not_Login));
    }
    else
    {
        m_pParent->sendMessageInter(ReplyMsg::getReply(msg.getRequest(), Err_Pending));
        AsyncQryService::instance()->checkAgencyAcc(ReplyAgencyApprovalMsg::getReply(msg.getRequest()));
    }
}

void TCPImpl::RecvMsgVisitor::Visit(xyc_communication::CommMsgRolesAdd& msg)
{
	if (msg.getType() == E_COMM_MSG_TYPE::EMPT_Init_Null
		|| msg.getType() >= E_COMM_MSG_TYPE::EMPT_Max_Count)
	{
		m_pParent->sendMessageInter(ReplyMsg::getReply(msg.getRequest(), Err_Req_Parameter));
	}
    else if (msg.getRequest()->login_name_.empty())
    {
        m_pParent->sendMessageInter(ReplyMsg::getReply(msg.getRequest(), Err_Not_Login));
    }
    else
	{
		m_pParent->sendMessageInter(ReplyMsg::getReply(msg.getRequest(), Err_Pending));
		AsyncQryService::instance()->addRole(ReplyRolesAddMsg::getReply(msg.getRequest()));
	}
}

void TCPImpl::RecvMsgVisitor::Visit(xyc_communication::CommMsgRolesChange& msg)
{
	if (msg.getType() == E_COMM_MSG_TYPE::EMPT_Init_Null
		|| msg.getType() >= E_COMM_MSG_TYPE::EMPT_Max_Count)
	{
		m_pParent->sendMessageInter(ReplyMsg::getReply(msg.getRequest(), Err_Req_Parameter));
	}
    else if (msg.getRequest()->login_name_.empty())
    {
        m_pParent->sendMessageInter(ReplyMsg::getReply(msg.getRequest(), Err_Not_Login));
    }
    else
	{
		m_pParent->sendMessageInter(ReplyMsg::getReply(msg.getRequest(), Err_Pending));
		AsyncQryService::instance()->changeRole(ReplyRolesChangeMsg::getReply(msg.getRequest()));
	}
}

void TCPImpl::RecvMsgVisitor::Visit(xyc_communication::CommMsgBindRelation& msg)
{
	if (msg.getType() == E_COMM_MSG_TYPE::EMPT_Init_Null
		|| msg.getType() >= E_COMM_MSG_TYPE::EMPT_Max_Count)
	{
		m_pParent->sendMessageInter(ReplyMsg::getReply(msg.getRequest(), Err_Req_Parameter));
	}
    else if (msg.getRequest()->login_name_.empty())
    {
        m_pParent->sendMessageInter(ReplyMsg::getReply(msg.getRequest(), Err_Not_Login));
    }
    else
	{
		m_pParent->sendMessageInter(ReplyMsg::getReply(msg.getRequest(), Err_Pending));
		AsyncQryService::instance()->bindRoleFunctionRelation(ReplyBindRelationMsg::getReply(msg.getRequest()));
	}
}

void TCPImpl::RecvMsgVisitor::Visit(xyc_communication::CommMsgUserRoleAddRelation& msg)
{
	if (msg.getType() == E_COMM_MSG_TYPE::EMPT_Init_Null
		|| msg.getType() >= E_COMM_MSG_TYPE::EMPT_Max_Count)
	{
		m_pParent->sendMessageInter(ReplyMsg::getReply(msg.getRequest(), Err_Req_Parameter));
	}
    else if (msg.getRequest()->login_name_.empty())
    {
        m_pParent->sendMessageInter(ReplyMsg::getReply(msg.getRequest(), Err_Not_Login));
    }
    else
	{
		m_pParent->sendMessageInter(ReplyMsg::getReply(msg.getRequest(), Err_Pending));
		AsyncQryService::instance()->addRoleUserInfo(ReplyUserRoleAddRelationMsg::getReply(msg.getRequest()));
	}
}

void TCPImpl::RecvMsgVisitor::Visit(xyc_communication::CommMsgChildAccAdd& msg)
{
    if (msg.getType() == E_COMM_MSG_TYPE::EMPT_Init_Null
        || msg.getType() >= E_COMM_MSG_TYPE::EMPT_Max_Count)
    {
        m_pParent->sendMessageInter(ReplyMsg::getReply(msg.getRequest(), Err_Req_Parameter));
    }
    else if (msg.getRequest()->login_name_.empty())
    {
        m_pParent->sendMessageInter(ReplyMsg::getReply(msg.getRequest(), Err_Not_Login));
    }
    else
    {
        m_pParent->sendMessageInter(ReplyMsg::getReply(msg.getRequest(), Err_Pending));
        AsyncQryService::instance()->addTradeAcc(ReplyChildAccAddMsg::getReply(msg.getRequest()));
    }
}

void TCPImpl::RecvMsgVisitor::Visit(xyc_communication::CommMsgChildAccChange& msg)
{
    if (msg.getType() == E_COMM_MSG_TYPE::EMPT_Init_Null
        || msg.getType() >= E_COMM_MSG_TYPE::EMPT_Max_Count)
    {
        m_pParent->sendMessageInter(ReplyMsg::getReply(msg.getRequest(), Err_Req_Parameter));
    }
    else if (msg.getRequest()->login_name_.empty())
    {
        m_pParent->sendMessageInter(ReplyMsg::getReply(msg.getRequest(), Err_Not_Login));
    }
    else
    {
        m_pParent->sendMessageInter(ReplyMsg::getReply(msg.getRequest(), Err_Pending));
        AsyncQryService::instance()->changeTradeAcc(ReplyChildAccChangeMsg::getReply(msg.getRequest()));
    }
}

void TCPImpl::RecvMsgVisitor::Visit(xyc_communication::CommMsgChildAccInmoney& msg)
{
    if (msg.getType() == E_COMM_MSG_TYPE::EMPT_Init_Null
        || msg.getType() >= E_COMM_MSG_TYPE::EMPT_Max_Count)
    {
        m_pParent->sendMessageInter(ReplyMsg::getReply(msg.getRequest(), Err_Req_Parameter));
    }
    else if (msg.getRequest()->login_name_.empty())
    {
        m_pParent->sendMessageInter(ReplyMsg::getReply(msg.getRequest(), Err_Not_Login));
    }
    else
    {
        m_pParent->sendMessageInter(ReplyMsg::getReply(msg.getRequest(), Err_Pending));
        AsyncQryService::instance()->outInMoney(ReplyChildAccInmoneyMsg::getReply(msg.getRequest()));
    }
}

void TCPImpl::RecvMsgVisitor::Visit(xyc_communication::CommMsgChildAccApproval& msg)
{
    if (msg.getType() == E_COMM_MSG_TYPE::EMPT_Init_Null
        || msg.getType() >= E_COMM_MSG_TYPE::EMPT_Max_Count)
    {
        m_pParent->sendMessageInter(ReplyMsg::getReply(msg.getRequest(), Err_Req_Parameter));
    }
    else if (msg.getRequest()->login_name_.empty())
    {
        m_pParent->sendMessageInter(ReplyMsg::getReply(msg.getRequest(), Err_Not_Login));
    }
    else
    {
        m_pParent->sendMessageInter(ReplyMsg::getReply(msg.getRequest(), Err_Pending));
        AsyncQryService::instance()->checkTradeAcc(ReplyChildAccApprovalMsg::getReply(msg.getRequest()));
    }
}

void TCPImpl::RecvMsgVisitor::Visit(xyc_communication::CommMsgFundAccAdd& msg)
{
    if (msg.getType() == E_COMM_MSG_TYPE::EMPT_Init_Null
        || msg.getType() >= E_COMM_MSG_TYPE::EMPT_Max_Count)
    {
        m_pParent->sendMessageInter(ReplyMsg::getReply(msg.getRequest(), Err_Req_Parameter));
    }
    else if (msg.getRequest()->login_name_.empty())
    {
        m_pParent->sendMessageInter(ReplyMsg::getReply(msg.getRequest(), Err_Not_Login));
    }
    else
    {
        m_pParent->sendMessageInter(ReplyMsg::getReply(msg.getRequest(), Err_Pending));
        AsyncQryService::instance()->addFunderAcc(ReplyFundAccAddMsg::getReply(msg.getRequest()));
    }
}

void TCPImpl::RecvMsgVisitor::Visit(xyc_communication::CommMsgFundAccChange& msg)
{
    if (msg.getType() == E_COMM_MSG_TYPE::EMPT_Init_Null
        || msg.getType() >= E_COMM_MSG_TYPE::EMPT_Max_Count)
    {
        m_pParent->sendMessageInter(ReplyMsg::getReply(msg.getRequest(), Err_Req_Parameter));
    }
    else if (msg.getRequest()->login_name_.empty())
    {
        m_pParent->sendMessageInter(ReplyMsg::getReply(msg.getRequest(), Err_Not_Login));
    }
    else
    {
        m_pParent->sendMessageInter(ReplyMsg::getReply(msg.getRequest(), Err_Pending));
        AsyncQryService::instance()->changeFunderAcc(ReplyFundAccChangeMsg::getReply(msg.getRequest()));
    }
}

void TCPImpl::RecvMsgVisitor::Visit(xyc_communication::CommMsgFeeSet& msg)
{
    if (msg.getType() == E_COMM_MSG_TYPE::EMPT_Init_Null
        || msg.getType() >= E_COMM_MSG_TYPE::EMPT_Max_Count)
    {
        m_pParent->sendMessageInter(ReplyMsg::getReply(msg.getRequest(), Err_Req_Parameter));
    }
    else if (msg.getRequest()->login_name_.empty())
    {
        m_pParent->sendMessageInter(ReplyMsg::getReply(msg.getRequest(), Err_Not_Login));
    }
    else
    {
        m_pParent->sendMessageInter(ReplyMsg::getReply(msg.getRequest(), Err_Pending));
        AsyncQryService::instance()->changeFeeSet(ReplyFeeSetMsg::getReply(msg.getRequest()));
    }
}

void TCPImpl::RecvMsgVisitor::Visit(xyc_communication::CommMsgStockBlackSet& msg)
{
    if (msg.getType() == E_COMM_MSG_TYPE::EMPT_Init_Null
        || msg.getType() >= E_COMM_MSG_TYPE::EMPT_Max_Count)
    {
        m_pParent->sendMessageInter(ReplyMsg::getReply(msg.getRequest(), Err_Req_Parameter));
    }
    else if (msg.getRequest()->login_name_.empty())
    {
        m_pParent->sendMessageInter(ReplyMsg::getReply(msg.getRequest(), Err_Not_Login));
    }
    else
    {
        m_pParent->sendMessageInter(ReplyMsg::getReply(msg.getRequest(), Err_Pending));
        AsyncQryService::instance()->setStockBlackWhiteStatus(ReplyStockBlackSetMsg::getReply(msg.getRequest()));
    }
}

void TCPImpl::RecvMsgVisitor::Visit(xyc_communication::CommMsgForbidBuySellSet& msg)
{
    if (msg.getType() == E_COMM_MSG_TYPE::EMPT_Init_Null
        || msg.getType() >= E_COMM_MSG_TYPE::EMPT_Max_Count)
    {
        m_pParent->sendMessageInter(ReplyMsg::getReply(msg.getRequest(), Err_Req_Parameter));
    }
    else if (msg.getRequest()->login_name_.empty())
    {
        m_pParent->sendMessageInter(ReplyMsg::getReply(msg.getRequest(), Err_Not_Login));
    }
    else
    {
        m_pParent->sendMessageInter(ReplyMsg::getReply(msg.getRequest(), Err_Pending));
        AsyncQryService::instance()->setForbidTradeStatus(ReplyForbidBuySellSetMsg::getReply(msg.getRequest()));
    }
}

void TCPImpl::RecvMsgVisitor::Visit(xyc_communication::CommMsgPosiRateSet& msg)
{
    if (msg.getType() == E_COMM_MSG_TYPE::EMPT_Init_Null
        || msg.getType() >= E_COMM_MSG_TYPE::EMPT_Max_Count)
    {
        m_pParent->sendMessageInter(ReplyMsg::getReply(msg.getRequest(), Err_Req_Parameter));
    }
    else if (msg.getRequest()->login_name_.empty())
    {
        m_pParent->sendMessageInter(ReplyMsg::getReply(msg.getRequest(), Err_Not_Login));
    }
    else
    {
        m_pParent->sendMessageInter(ReplyMsg::getReply(msg.getRequest(), Err_Pending));
        AsyncQryService::instance()->setPosiRateStatus(ReplyPosiRateSetMsg::getReply(msg.getRequest()));
    }
}

void TCPImpl::RecvMsgVisitor::Visit(xyc_communication::CommMsgAutoInMoneyApproval& msg)
{
    if (msg.getType() == E_COMM_MSG_TYPE::EMPT_Init_Null
        || msg.getType() >= E_COMM_MSG_TYPE::EMPT_Max_Count)
    {
        m_pParent->sendMessageInter(ReplyMsg::getReply(msg.getRequest(), Err_Req_Parameter));
    }
    else if (msg.getRequest()->login_name_.empty())
    {
        m_pParent->sendMessageInter(ReplyMsg::getReply(msg.getRequest(), Err_Not_Login));
    }
    else
    {
        m_pParent->sendMessageInter(ReplyMsg::getReply(msg.getRequest(), Err_Pending));
        AsyncQryService::instance()->approvalApplyAutoInMoney(ReplyAutoInMoneyApprovalMsg::getReply(msg.getRequest()));
    }
}

void TCPImpl::RecvMsgVisitor::Visit(xyc_communication::CommMsgAutoOutMoneyApproval& msg)
{
    if (msg.getType() == E_COMM_MSG_TYPE::EMPT_Init_Null
        || msg.getType() >= E_COMM_MSG_TYPE::EMPT_Max_Count)
    {
        m_pParent->sendMessageInter(ReplyMsg::getReply(msg.getRequest(), Err_Req_Parameter));
    }
    else if (msg.getRequest()->login_name_.empty())
    {
        m_pParent->sendMessageInter(ReplyMsg::getReply(msg.getRequest(), Err_Not_Login));
    }
    else
    {
        m_pParent->sendMessageInter(ReplyMsg::getReply(msg.getRequest(), Err_Pending));
        AsyncQryService::instance()->approvalApplyAutoOutMoney(ReplyAutoOutMoneyApprovalMsg::getReply(msg.getRequest()));
    }
}

void TCPImpl::RecvMsgVisitor::Visit(xyc_communication::CommMsgPswChange& msg)
{
    if (msg.getType() == E_COMM_MSG_TYPE::EMPT_Init_Null
        || msg.getType() >= E_COMM_MSG_TYPE::EMPT_Max_Count)
    {
        m_pParent->sendMessageInter(ReplyMsg::getReply(msg.getRequest(), Err_Req_Parameter));
    }
    else if (msg.getRequest()->login_name_.empty())
    {
        m_pParent->sendMessageInter(ReplyMsg::getReply(msg.getRequest(), Err_Not_Login));
    }
    else
    {
        m_pParent->sendMessageInter(ReplyMsg::getReply(msg.getRequest(), Err_Pending));
        AsyncQryService::instance()->changePassword(ReplyPswChangeMsg::getReply(msg.getRequest()));
    }
}

void TCPImpl::RecvMsgVisitor::Visit(xyc_communication::CommMsgManagerAdd& msg)
{
    if (msg.getType() == E_COMM_MSG_TYPE::EMPT_Init_Null
        || msg.getType() >= E_COMM_MSG_TYPE::EMPT_Max_Count)
    {
        m_pParent->sendMessageInter(ReplyMsg::getReply(msg.getRequest(), Err_Req_Parameter));
    }
    else if (msg.getRequest()->login_name_.empty())
    {
        m_pParent->sendMessageInter(ReplyMsg::getReply(msg.getRequest(), Err_Not_Login));
    }
    else
    {
        m_pParent->sendMessageInter(ReplyMsg::getReply(msg.getRequest(), Err_Pending));
        AsyncQryService::instance()->addManagerAcc(ReplyManagerAddMsg::getReply(msg.getRequest()));
    }
}

void TCPImpl::RecvMsgVisitor::Visit(xyc_communication::CommMsgManagerChange& msg)
{
    if (msg.getType() == E_COMM_MSG_TYPE::EMPT_Init_Null
        || msg.getType() >= E_COMM_MSG_TYPE::EMPT_Max_Count)
    {
        m_pParent->sendMessageInter(ReplyMsg::getReply(msg.getRequest(), Err_Req_Parameter));
    }
    else if (msg.getRequest()->login_name_.empty())
    {
        m_pParent->sendMessageInter(ReplyMsg::getReply(msg.getRequest(), Err_Not_Login));
    }
    else
    {
        m_pParent->sendMessageInter(ReplyMsg::getReply(msg.getRequest(), Err_Pending));
        AsyncQryService::instance()->changeManagerAcc(ReplyManagerChangeMsg::getReply(msg.getRequest()));
    }
}

void TCPImpl::RecvMsgVisitor::Visit(xyc_communication::CommMsgOpenClose& msg)
{
    if (msg.getType() == E_COMM_MSG_TYPE::EMPT_Init_Null
        || msg.getType() >= E_COMM_MSG_TYPE::EMPT_Max_Count)
    {
        m_pParent->sendMessageInter(ReplyMsg::getReply(msg.getRequest(), Err_Req_Parameter));
    }
    else if (msg.getRequest()->login_name_.empty())
    {
        m_pParent->sendMessageInter(ReplyMsg::getReply(msg.getRequest(), Err_Not_Login));
    }
    else
    {
        m_pParent->sendMessageInter(ReplyMsg::getReply(msg.getRequest(), Err_Pending));
        AsyncQryService::instance()->handlePlaceOrder(ReplyOpenCloseMsg::getReply(msg.getRequest()), AllTrade::OnlineUserManager::instance()->getLoginInfo(msg.getSocketID()));
    }

}

void TCPImpl::RecvMsgVisitor::Visit(xyc_communication::CommMsgCancelOrder& msg)
{
    if (msg.getType() == E_COMM_MSG_TYPE::EMPT_Init_Null
        || msg.getType() >= E_COMM_MSG_TYPE::EMPT_Max_Count)
    {
        m_pParent->sendMessageInter(ReplyMsg::getReply(msg.getRequest(), Err_Req_Parameter));
    }
    else if (msg.getRequest()->login_name_.empty())
    {
        m_pParent->sendMessageInter(ReplyMsg::getReply(msg.getRequest(), Err_Not_Login));
    }
    else
    {
        m_pParent->sendMessageInter(ReplyMsg::getReply(msg.getRequest(), Err_Pending));
        AsyncQryService::instance()->handleCancelOrder(ReplyCancelOrderMsg::getReply(msg.getRequest()));
    }
}

void TCPImpl::RecvMsgVisitor::Visit(xyc_communication::CommMsgSelfFunctionQry& msg)
{
	if (msg.getType() == E_COMM_MSG_TYPE::EMPT_Init_Null
		|| msg.getType() >= E_COMM_MSG_TYPE::EMPT_Max_Count)
	{
		m_pParent->sendMessageInter(ReplyMsg::getReply(msg.getRequest(), Err_Req_Parameter));
	}
    else if (msg.getRequest()->login_name_.empty())
    {
        m_pParent->sendMessageInter(ReplyMsg::getReply(msg.getRequest(), Err_Not_Login));
    }
    else
	{
		m_pParent->sendMessageInter(ReplyMsg::getReply(msg.getRequest(), Err_Pending));
		AsyncQryService::instance()->qrySelfFunctionsInfo(ReplySelfFunctionMsg::getReply(msg.getRequest()));
	}
}

void TCPImpl::RecvMsgVisitor::Visit(xyc_communication::CommMsgRoleFunctionQry& msg)
{
	if (msg.getType() == E_COMM_MSG_TYPE::EMPT_Init_Null
		|| msg.getType() >= E_COMM_MSG_TYPE::EMPT_Max_Count)
	{
		m_pParent->sendMessageInter(ReplyMsg::getReply(msg.getRequest(), Err_Req_Parameter));
	}
    else if (msg.getRequest()->login_name_.empty())
    {
        m_pParent->sendMessageInter(ReplyMsg::getReply(msg.getRequest(), Err_Not_Login));
    }
    else
	{
		m_pParent->sendMessageInter(ReplyMsg::getReply(msg.getRequest(), Err_Pending));
		AsyncQryService::instance()->qryRoleFunctionsInfo(ReplyRoleFunctionMsg::getReply(msg.getRequest()));
	}
}

void TCPImpl::RecvMsgVisitor::Visit(xyc_communication::CommMsgDelRole& msg)
{
	if (msg.getType() == E_COMM_MSG_TYPE::EMPT_Init_Null
		|| msg.getType() >= E_COMM_MSG_TYPE::EMPT_Max_Count)
	{
		m_pParent->sendMessageInter(ReplyMsg::getReply(msg.getRequest(), Err_Req_Parameter));
	}
    else if (msg.getRequest()->login_name_.empty())
    {
        m_pParent->sendMessageInter(ReplyMsg::getReply(msg.getRequest(), Err_Not_Login));
    }
    else
	{
		m_pParent->sendMessageInter(ReplyMsg::getReply(msg.getRequest(), Err_Pending));
		AsyncQryService::instance()->deleteRole(ReplyDelRoleMsg::getReply(msg.getRequest()));
	}
}

void TCPImpl::RecvMsgVisitor::Visit(xyc_communication::CommMsgDelRoleUser& msg)
{
	if (msg.getType() == E_COMM_MSG_TYPE::EMPT_Init_Null
		|| msg.getType() >= E_COMM_MSG_TYPE::EMPT_Max_Count)
	{
		m_pParent->sendMessageInter(ReplyMsg::getReply(msg.getRequest(), Err_Req_Parameter));
	}
    else if (msg.getRequest()->login_name_.empty())
    {
        m_pParent->sendMessageInter(ReplyMsg::getReply(msg.getRequest(), Err_Not_Login));
    }
    else
	{
		m_pParent->sendMessageInter(ReplyMsg::getReply(msg.getRequest(), Err_Pending));
		AsyncQryService::instance()->deleteRoleUserInfo(ReplyDelRoleUserMsg::getReply(msg.getRequest()));
	}

}

void TCPImpl::RecvMsgVisitor::Visit(xyc_communication::CommMsgGetAllBussnessUser& msg)
{
	if (msg.getType() == E_COMM_MSG_TYPE::EMPT_Init_Null
		|| msg.getType() >= E_COMM_MSG_TYPE::EMPT_Max_Count)
	{
		m_pParent->sendMessageInter(ReplyMsg::getReply(msg.getRequest(), Err_Req_Parameter));
	}
    else if (msg.getRequest()->login_name_.empty())
    {
        m_pParent->sendMessageInter(ReplyMsg::getReply(msg.getRequest(), Err_Not_Login));
    }
    else
	{
		m_pParent->sendMessageInter(ReplyMsg::getReply(msg.getRequest(), Err_Pending));
		AsyncQryService::instance()->getAllBussnessInfo(ReplyGetAllBussnessMsg::getReply(msg.getRequest()));
	}
}

void TCPImpl::RecvMsgVisitor::Visit(xyc_communication::CommMsgApplyEquipMoney& msg)
{
    if (msg.getType() == E_COMM_MSG_TYPE::EMPT_Init_Null
        || msg.getType() >= E_COMM_MSG_TYPE::EMPT_Max_Count)
    {
        m_pParent->sendMessageInter(ReplyMsg::getReply(msg.getRequest(), Err_Req_Parameter));
    }
    else if (msg.getRequest()->login_name_.empty())
    {
        m_pParent->sendMessageInter(ReplyMsg::getReply(msg.getRequest(), Err_Not_Login));
    }
    else
    {
        m_pParent->sendMessageInter(ReplyMsg::getReply(msg.getRequest(), Err_Pending));
        AsyncQryService::instance()->applyEquipMoney(ReplyApplyEquipMoneyMsg::getReply(msg.getRequest()));
    }
}

void TCPImpl::RecvMsgVisitor::Visit(xyc_communication::CommMsgApprovalApplyEquipMoney& msg)
{
    if (msg.getType() == E_COMM_MSG_TYPE::EMPT_Init_Null
        || msg.getType() >= E_COMM_MSG_TYPE::EMPT_Max_Count)
    {
        m_pParent->sendMessageInter(ReplyMsg::getReply(msg.getRequest(), Err_Req_Parameter));
    }
    else if (msg.getRequest()->login_name_.empty())
    {
        m_pParent->sendMessageInter(ReplyMsg::getReply(msg.getRequest(), Err_Not_Login));
    }
    else
    {
        m_pParent->sendMessageInter(ReplyMsg::getReply(msg.getRequest(), Err_Pending));
        AsyncQryService::instance()->approvalApplyEquipMoney(ReplyApprovalApplyEquipMoneyMsg::getReply(msg.getRequest()));
    }
}

void TCPImpl::RecvMsgVisitor::Visit(xyc_communication::CommMsgAgencyDelete& msg)
{
    if (msg.getType() == E_COMM_MSG_TYPE::EMPT_Init_Null
        || msg.getType() >= E_COMM_MSG_TYPE::EMPT_Max_Count)
    {
        m_pParent->sendMessageInter(ReplyMsg::getReply(msg.getRequest(), Err_Req_Parameter));
    }
    else if (msg.getRequest()->login_name_.empty())
    {
        m_pParent->sendMessageInter(ReplyMsg::getReply(msg.getRequest(), Err_Not_Login));
    }
    else
    {
        m_pParent->sendMessageInter(ReplyMsg::getReply(msg.getRequest(), Err_Pending));
        AsyncQryService::instance()->deleteAgency(ReplyAgencyDeleteMsg::getReply(msg.getRequest()));
    }
}

void TCPImpl::RecvMsgVisitor::Visit(xyc_communication::CommMsgChildDelete& msg)
{
    if (msg.getType() == E_COMM_MSG_TYPE::EMPT_Init_Null
        || msg.getType() >= E_COMM_MSG_TYPE::EMPT_Max_Count)
    {
        m_pParent->sendMessageInter(ReplyMsg::getReply(msg.getRequest(), Err_Req_Parameter));
    }
    else if (msg.getRequest()->login_name_.empty())
    {
        m_pParent->sendMessageInter(ReplyMsg::getReply(msg.getRequest(), Err_Not_Login));
    }
    else
    {
        m_pParent->sendMessageInter(ReplyMsg::getReply(msg.getRequest(), Err_Pending));
        AsyncQryService::instance()->deleteChild(ReplyChildDeleteMsg::getReply(msg.getRequest()));
    }
}

void TCPImpl::RecvMsgVisitor::Visit(xyc_communication::CommMsgFunderDelete& msg)
{
    if (msg.getType() == E_COMM_MSG_TYPE::EMPT_Init_Null
        || msg.getType() >= E_COMM_MSG_TYPE::EMPT_Max_Count)
    {
        m_pParent->sendMessageInter(ReplyMsg::getReply(msg.getRequest(), Err_Req_Parameter));
    }
    else if (msg.getRequest()->login_name_.empty())
    {
        m_pParent->sendMessageInter(ReplyMsg::getReply(msg.getRequest(), Err_Not_Login));
    }
    else
    {
        m_pParent->sendMessageInter(ReplyMsg::getReply(msg.getRequest(), Err_Pending));
        AsyncQryService::instance()->deleteFunder(ReplyFunderDeleteMsg::getReply(msg.getRequest()));
    }
}

void TCPImpl::RecvMsgVisitor::Visit(xyc_communication::CommMsgManagerDelete& msg)
{
    if (msg.getType() == E_COMM_MSG_TYPE::EMPT_Init_Null
        || msg.getType() >= E_COMM_MSG_TYPE::EMPT_Max_Count)
    {
        m_pParent->sendMessageInter(ReplyMsg::getReply(msg.getRequest(), Err_Req_Parameter));
    }
    else if (msg.getRequest()->login_name_.empty())
    {
        m_pParent->sendMessageInter(ReplyMsg::getReply(msg.getRequest(), Err_Not_Login));
    }
    else
    {
        m_pParent->sendMessageInter(ReplyMsg::getReply(msg.getRequest(), Err_Pending));
        AsyncQryService::instance()->deleteManager(ReplyManagerDeleteMsg::getReply(msg.getRequest()));
    }
}

void TCPImpl::RecvMsgVisitor::Visit(xyc_communication::CommMsgGetCustomStock& msg)
{
    if (msg.getType() == E_COMM_MSG_TYPE::EMPT_Init_Null
        || msg.getType() >= E_COMM_MSG_TYPE::EMPT_Max_Count)
    {
        m_pParent->sendMessageInter(ReplyMsg::getReply(msg.getRequest(), Err_Req_Parameter));
    }
    else if (msg.getRequest()->login_name_.empty())
    {
        m_pParent->sendMessageInter(ReplyMsg::getReply(msg.getRequest(), Err_Not_Login));
    }
    else
    {
        m_pParent->sendMessageInter(ReplyMsg::getReply(msg.getRequest(), Err_Pending));
        AsyncQryService::instance()->qryCustomStock(ReplyGetCustomStockMsg::getReply(msg.getRequest()));
    }
}

void TCPImpl::RecvMsgVisitor::Visit(xyc_communication::CommMsgAddCustomStock& msg)
{
    if (msg.getType() == E_COMM_MSG_TYPE::EMPT_Init_Null
        || msg.getType() >= E_COMM_MSG_TYPE::EMPT_Max_Count)
    {
        m_pParent->sendMessageInter(ReplyMsg::getReply(msg.getRequest(), Err_Req_Parameter));
    }
    else if (msg.getRequest()->login_name_.empty())
    {
        m_pParent->sendMessageInter(ReplyMsg::getReply(msg.getRequest(), Err_Not_Login));
    }
    else
    {
        m_pParent->sendMessageInter(ReplyMsg::getReply(msg.getRequest(), Err_Pending));
        AsyncQryService::instance()->addCustomStock(ReplyAddCustomStockMsg::getReply(msg.getRequest()));
    }
}

void TCPImpl::RecvMsgVisitor::Visit(xyc_communication::CommMsgDelCustomStock& msg)
{
    if (msg.getType() == E_COMM_MSG_TYPE::EMPT_Init_Null
        || msg.getType() >= E_COMM_MSG_TYPE::EMPT_Max_Count)
    {
        m_pParent->sendMessageInter(ReplyMsg::getReply(msg.getRequest(), Err_Req_Parameter));
    }
    else if (msg.getRequest()->login_name_.empty())
    {
        m_pParent->sendMessageInter(ReplyMsg::getReply(msg.getRequest(), Err_Not_Login));
    }
    else
    {
        m_pParent->sendMessageInter(ReplyMsg::getReply(msg.getRequest(), Err_Pending));
        AsyncQryService::instance()->deleteCustomStock(ReplyDelCustomStockMsg::getReply(msg.getRequest()));
    }
}

void TCPImpl::RecvMsgVisitor::Visit(xyc_communication::CommMsgChangeRoleUser& msg)
{
	if (msg.getType() == E_COMM_MSG_TYPE::EMPT_Init_Null
		|| msg.getType() >= E_COMM_MSG_TYPE::EMPT_Max_Count)
	{
		m_pParent->sendMessageInter(ReplyMsg::getReply(msg.getRequest(), Err_Req_Parameter));
	}
    else if (msg.getRequest()->login_name_.empty())
    {
        m_pParent->sendMessageInter(ReplyMsg::getReply(msg.getRequest(), Err_Not_Login));
    }
    else
	{
		m_pParent->sendMessageInter(ReplyMsg::getReply(msg.getRequest(), Err_Pending));
		AsyncQryService::instance()->changeRoleUserInfo(ReplyChangeRoleUserMsg::getReply(msg.getRequest()));
	}
}

void TCPImpl::RecvMsgVisitor::Visit(xyc_communication::CommMsgAutoInMoney& msg)
{
    if (msg.getType() == E_COMM_MSG_TYPE::EMPT_Init_Null
        || msg.getType() >= E_COMM_MSG_TYPE::EMPT_Max_Count)
    {
        m_pParent->sendMessageInter(ReplyMsg::getReply(msg.getRequest(), Err_Req_Parameter));
    }
    else
    {
        m_pParent->sendMessageInter(ReplyMsg::getReply(msg.getRequest(), Err_Pending));
        AsyncQryService::instance()->applyAutoInMoney(ReplyAutoInMoneyMsg::getReply(msg.getRequest()));
    }
}

void TCPImpl::RecvMsgVisitor::Visit(xyc_communication::CommMsgAutoOutMoney& msg)
{
    if (msg.getType() == E_COMM_MSG_TYPE::EMPT_Init_Null
        || msg.getType() >= E_COMM_MSG_TYPE::EMPT_Max_Count)
    {
        m_pParent->sendMessageInter(ReplyMsg::getReply(msg.getRequest(), Err_Req_Parameter));
    }
    else if (msg.getRequest()->login_name_.empty())
    {
        m_pParent->sendMessageInter(ReplyMsg::getReply(msg.getRequest(), Err_Not_Login));
    }
    else
    {
        m_pParent->sendMessageInter(ReplyMsg::getReply(msg.getRequest(), Err_Pending));
        AsyncQryService::instance()->applyAutoOutMoney(ReplyAutoOutMoneyMsg::getReply(msg.getRequest()));
    }
}

void TCPImpl::RecvMsgVisitor::Visit(xyc_communication::CommMsgChildAccAutoAdd& msg)
{
    if (msg.getType() == E_COMM_MSG_TYPE::EMPT_Init_Null
        || msg.getType() >= E_COMM_MSG_TYPE::EMPT_Max_Count)
    {
        m_pParent->sendMessageInter(ReplyMsg::getReply(msg.getRequest(), Err_Req_Parameter));
    }
    else
    {
        m_pParent->sendMessageInter(ReplyMsg::getReply(msg.getRequest(), Err_Pending));
        AsyncQryService::instance()->autoCreateTradeUser(ReplyChildAccAutoAddMsg::getReply(msg.getRequest()));
    }
}

void TCPImpl::RecvMsgVisitor::Visit(xyc_communication::CommMsgAutoInMoneyQry& msg)
{
    if (msg.getType() == E_COMM_MSG_TYPE::EMPT_Init_Null
        || msg.getType() >= E_COMM_MSG_TYPE::EMPT_Max_Count)
    {
        m_pParent->sendMessageInter(ReplyMsg::getReply(msg.getRequest(), Err_Req_Parameter));
    }
    else if (msg.getRequest()->login_name_.empty())
    {
        m_pParent->sendMessageInter(ReplyMsg::getReply(msg.getRequest(), Err_Not_Login));
    }
    else
    {
        m_pParent->sendMessageInter(ReplyMsg::getReply(msg.getRequest(), Err_Pending));
        AsyncQryService::instance()->qryAutoInMoneyInfos(ReplyAutoInMoneyQryMsg::getReply(msg.getRequest()));
    }
}

void TCPImpl::RecvMsgVisitor::Visit(xyc_communication::RiskHistoryQry& msg)
{
	if (msg.getType() == E_COMM_MSG_TYPE::EMPT_Init_Null
		|| msg.getType() >= E_COMM_MSG_TYPE::EMPT_Max_Count)
	{
		m_pParent->sendMessageInter(ReplyMsg::getReply(msg.getRequest(), Err_Req_Parameter));
	}
	else if (msg.getRequest()->login_name_.empty())
	{
		m_pParent->sendMessageInter(ReplyMsg::getReply(msg.getRequest(), Err_Not_Login));
	}
	else
	{
		m_pParent->sendMessageInter(ReplyMsg::getReply(msg.getRequest(), Err_Pending));
		AsyncQryService::instance()->qryRiskHistoryInfos(ReplyRiskHistoryMsg::getReply(msg.getRequest()));
	}
}

void TCPImpl::RecvMsgVisitor::Visit(xyc_communication::MarginSetQry& msg)
{
	if (msg.getType() == E_COMM_MSG_TYPE::EMPT_Init_Null
		|| msg.getType() >= E_COMM_MSG_TYPE::EMPT_Max_Count)
	{
		m_pParent->sendMessageInter(ReplyMsg::getReply(msg.getRequest(), Err_Req_Parameter));
	}
	else if (msg.getRequest()->login_name_.empty())
	{
		m_pParent->sendMessageInter(ReplyMsg::getReply(msg.getRequest(), Err_Not_Login));
	}
	else
	{
		m_pParent->sendMessageInter(ReplyMsg::getReply(msg.getRequest(), Err_Pending));
		AsyncQryService::instance()->setMarginInfo(ReplySetMarginMsg::getReply(msg.getRequest()));
	}
}

void TCPImpl::RecvMsgVisitor::Visit(xyc_communication::MarginLeftQry& msg)
{
	if (msg.getType() == E_COMM_MSG_TYPE::EMPT_Init_Null
		|| msg.getType() >= E_COMM_MSG_TYPE::EMPT_Max_Count)
	{
		m_pParent->sendMessageInter(ReplyMsg::getReply(msg.getRequest(), Err_Req_Parameter));
	}
	else if (msg.getRequest()->login_name_.empty())
	{
		m_pParent->sendMessageInter(ReplyMsg::getReply(msg.getRequest(), Err_Not_Login));
	}
	else
	{
		m_pParent->sendMessageInter(ReplyMsg::getReply(msg.getRequest(), Err_Pending));
		AsyncQryService::instance()->setMarginInfo(ReplySetMarginMsg::getReply(msg.getRequest()));
	}
}

void TCPImpl::RecvMsgVisitor::Visit(xyc_communication::MarginManagerQry& msg)
{
	if (msg.getType() == E_COMM_MSG_TYPE::EMPT_Init_Null
		|| msg.getType() >= E_COMM_MSG_TYPE::EMPT_Max_Count)
	{
		m_pParent->sendMessageInter(ReplyMsg::getReply(msg.getRequest(), Err_Req_Parameter));
	}
	else if (msg.getRequest()->login_name_.empty())
	{
		m_pParent->sendMessageInter(ReplyMsg::getReply(msg.getRequest(), Err_Not_Login));
	}
	else
	{
		m_pParent->sendMessageInter(ReplyMsg::getReply(msg.getRequest(), Err_Pending));
		AsyncQryService::instance()->getMarginManagerInfo(ReplyMarginManagerQtyMsg::getReply(msg.getRequest()));
	}
}

void TCPImpl::RecvMsgVisitor::Visit(xyc_communication::MarginLiabilitiesQry& msg)
{
	if (msg.getType() == E_COMM_MSG_TYPE::EMPT_Init_Null
		|| msg.getType() >= E_COMM_MSG_TYPE::EMPT_Max_Count)
	{
		m_pParent->sendMessageInter(ReplyMsg::getReply(msg.getRequest(), Err_Req_Parameter));
	}
	else if (msg.getRequest()->login_name_.empty())
	{
		m_pParent->sendMessageInter(ReplyMsg::getReply(msg.getRequest(), Err_Not_Login));
	}
	else
	{
		m_pParent->sendMessageInter(ReplyMsg::getReply(msg.getRequest(), Err_Pending));
		AsyncQryService::instance()->getMarginLiabilitiesInfo(ReplyMarginLiabilitiesQtyMsg::getReply(msg.getRequest()));
	}
}

void TCPImpl::RecvMsgVisitor::Visit(xyc_communication::InterestStatisticsQry& msg)
{
	if (msg.getType() == E_COMM_MSG_TYPE::EMPT_Init_Null
		|| msg.getType() >= E_COMM_MSG_TYPE::EMPT_Max_Count)
	{
		m_pParent->sendMessageInter(ReplyMsg::getReply(msg.getRequest(), Err_Req_Parameter));
	}
	else if (msg.getRequest()->login_name_.empty())
	{
		m_pParent->sendMessageInter(ReplyMsg::getReply(msg.getRequest(), Err_Not_Login));
	}
	else
	{
		m_pParent->sendMessageInter(ReplyMsg::getReply(msg.getRequest(), Err_Pending));
		AsyncQryService::instance()->getInterestStatisticsInfo(ReplyInterestStatisticsMsg::getReply(msg.getRequest()));
	}

}

void TCPImpl::RecvMsgVisitor::Visit(xyc_communication::InterestDetailQry& msg)
{
	if (msg.getType() == E_COMM_MSG_TYPE::EMPT_Init_Null
		|| msg.getType() >= E_COMM_MSG_TYPE::EMPT_Max_Count)
	{
		m_pParent->sendMessageInter(ReplyMsg::getReply(msg.getRequest(), Err_Req_Parameter));
	}
	else if (msg.getRequest()->login_name_.empty())
	{
		m_pParent->sendMessageInter(ReplyMsg::getReply(msg.getRequest(), Err_Not_Login));
	}
	else
	{
		m_pParent->sendMessageInter(ReplyMsg::getReply(msg.getRequest(), Err_Pending));
		AsyncQryService::instance()->getInterestDetailInfo(ReplyInterestDetailMsg::getReply(msg.getRequest()));
	}
}

void TCPImpl::RecvMsgVisitor::Visit(xyc_communication::CommMsgCurrentyMarginEntrustQry& msg)
{
	if (msg.getType() == E_COMM_MSG_TYPE::EMPT_Init_Null
		|| msg.getType() >= E_COMM_MSG_TYPE::EMPT_Max_Count)
	{
		m_pParent->sendMessageInter(ReplyMsg::getReply(msg.getRequest(), Err_Req_Parameter));
	}
	else if (msg.getRequest()->login_name_.empty())
	{
		m_pParent->sendMessageInter(ReplyMsg::getReply(msg.getRequest(), Err_Not_Login));
	}
	else
	{
		m_pParent->sendMessageInter(ReplyMsg::getReply(msg.getRequest(), Err_Pending));
		AsyncQryService::instance()->getCurrentMarginEntrustInfo(ReplyCurrentMarginEntrustMsg::getReply(msg.getRequest()));
	}
}

void TCPImpl::RecvMsgVisitor::Visit(xyc_communication::CommMsgCurrentyMarginTradeQry& msg)
{
	if (msg.getType() == E_COMM_MSG_TYPE::EMPT_Init_Null
		|| msg.getType() >= E_COMM_MSG_TYPE::EMPT_Max_Count)
	{
		m_pParent->sendMessageInter(ReplyMsg::getReply(msg.getRequest(), Err_Req_Parameter));
	}
	else if (msg.getRequest()->login_name_.empty())
	{
		m_pParent->sendMessageInter(ReplyMsg::getReply(msg.getRequest(), Err_Not_Login));
	}
	else
	{
		m_pParent->sendMessageInter(ReplyMsg::getReply(msg.getRequest(), Err_Pending));
		AsyncQryService::instance()->qryCurrentMarginTrade(ReplyCurrentMarginTradeQryMsg::getReply(msg.getRequest()));
	}
}
