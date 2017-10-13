#include <QMessageBox>
#include <QCloseEvent>
#include "quote_connect.h"
#include "tcpserver.h"
#include "TCPImpl.h"
#include "include/TradeCenter/TradeCenter.h"

using namespace AllTrade;
using namespace AllTrade::NPMgrCenter;
using namespace AllTrade::NPTradeCenter;

//////////////////////////////////////////////////////////////////////////
TCPServer::TCPServer(QWidget *parent)
    : QMainWindow(parent)
{
    m_server = std::make_shared<TCPImpl>(this);

    int i_source = GetPrivateProfileIntA("Quote", "source", 0, "./config.hxc");
    if (i_source == 0)
        m_threads.push_back(new CSharpQuote(this));

    m_threads.push_back(new InitContractThread(this));

    for (auto m_thread : m_threads)
    {
        m_thread->start();
        connect(m_thread, &CSharpQuote::sglChangeQuoteStatus, this, &TCPServer::slotChangeQuoteStatus);
    }

    int i_simul = GetPrivateProfileIntA("Trade", "simul_trade", 1, "./config.hxc");
    if (i_simul == 1)
        ITradeCenter::instance()->changeQuoteStatus(true);
}

TCPServer::~TCPServer()
{
    stop();
}

void TCPServer::stop()
{
    for (auto m_thread : m_threads)
    {
        if (m_thread)
        {
            if (m_thread->isRunning())
                m_thread->terminate();

            m_thread->stopUpdate();
        }
    }
}

void TCPServer::closeEvent(QCloseEvent *event)
{
    int rslt = QMessageBox::warning(this, QStringLiteral("退出"), QStringLiteral("是否确定退出?"), QMessageBox::Yes, QMessageBox::No);
    if (rslt == QMessageBox::No)
        event->ignore();
    else
        QMainWindow::closeEvent(event);
}

void TCPServer::slotChangeQuoteStatus(bool bl)
{
    ITradeCenter::instance()->changeQuoteStatus(bl);
}
