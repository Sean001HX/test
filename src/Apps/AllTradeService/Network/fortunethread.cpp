/****************************************************************************
**
** Copyright (C) 2015 The Qt Company Ltd.
** Contact: http://www.qt.io/licensing/
**
** This file is part of the examples of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** You may use this file under the terms of the BSD license as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of The Qt Company Ltd nor the names of its
**     contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include "fortunethread.h"
#include "TCPImpl.h"

#include <QtNetwork>
#include "c:/ng_tools/ng_header_for_log4cxx/ng_header_for_log4cxx.hpp"
#include "C:/ng_tools/ng_header_for_log4cxx/ng_header_for_log4cxx_log_var.hpp"

NG_LOGGER(logger, "FortuneThread");

//! [0]
FortuneThread::FortuneThread(qintptr socketDescriptor, const QString& ip, QObject *parent)
    : QThread(parent)
    , m_socketDescriptor(socketDescriptor)
    , m_ip(ip)
{
    m_parent = static_cast<TCPImpl*>(parent);

    qDebug() << QStringLiteral("创建监控线程") << m_socketDescriptor;
    qRegisterMetaType<QAbstractSocket::SocketError>("QAbstractSocket::SocketError");
    connect(this, &FortuneThread::finished, this, &FortuneThread::deleteLater);
    LOG4CXX_TRACE(logger, "创建监控线程"LOG_NOVAR(m_socketDescriptor)LOG_NOVAR(m_ip.toLocal8Bit().data()));
    start();
}

FortuneThread::~FortuneThread()
{
    LOG4CXX_TRACE(logger, "退出监控线程"LOG_NOVAR(m_socketDescriptor));
    qDebug() << QStringLiteral("退出监控线程") << m_socketDescriptor;
}

void FortuneThread::write(const QString& msg)
{
    writeLock lock(m_rw_mutex);
	m_texts.push_back(msg);
    m_write_event.set();
}

//! [1]
void FortuneThread::run()
{
    try
    {
//         QTcpSocket* curSocket = const_cast<QTcpSocket*>(m_parent->m_sockets.getSocketPtrByDescript(m_socketDescriptor));
//         if (!curSocket){
//             slotErroring();
//             LOG4CXX_TRACE(logger, "finished!"LOG_NOVAR(m_socketDescriptor));
//             return;
//         }

//         QTcpSocket tcpSocket;
//         if (!tcpSocket.setSocketDescriptor(m_socketDescriptor)) {
//             slotErroring();
//             LOG4CXX_TRACE(logger, "finished!"LOG_NOVAR(m_socketDescriptor));
//             return;
//         }
// 
//         connect(&tcpSocket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(slotErroring()));
//         connect(&tcpSocket, &QTcpSocket::readyRead, this, &FortuneThread::slotReadyRead);
//         connect(&tcpSocket, &QTcpSocket::disconnected, this, &FortuneThread::slotErroring);
//         connect(&tcpSocket, &QTcpSocket::stateChanged, [&](QAbstractSocket::SocketState state){
//             if (state == QAbstractSocket::ClosingState || state == QAbstractSocket::UnconnectedState)
//                 slotErroring();
//         });

        const int handlerCnt = 2;
        CommonTools::handler handlerTable[] = { m_write_event, m_close_event };

        while (true)
        {
            int index = CommonTools::wait_for_multiple_events(handlerTable, handlerCnt);
            if (index == -1)
            {
                // 异常等待事件
                break;
            }
            else if (handlerTable[index] == m_close_event)// 关闭事件
            {
                break;
            }
			QStringList tmps;
			{
				writeLock lock(m_rw_mutex);
                tmps.swap(m_texts);
			}

            for (QString& tmp : tmps)
			{
                if (m_close_event.trywait())
                {
//                     LOG4CXX_TRACE(logger, "finish1:"LOG_NOVAR(m_socketDescriptor));
                    return;
                }

                emit sglWriteToSocket(tmp, m_socketDescriptor);
//                 if (curSocket->isWritable())
//                 {
//                     qint64 tmp222 = curSocket->write(tmp.toUtf8());
//                     if (!curSocket->isWritable() || !curSocket->waitForBytesWritten())
//                     {
//                         LOG4CXX_TRACE(logger, "即将断开链接!"LOG_NOVAR(m_socketDescriptor));
//                         slotErroring();
//                         break;
//                     }
//                 }
//                 qint64 tmp222 = tcpSocket.write(tmp.toUtf8());
//                 if (!tcpSocket.waitForBytesWritten())
//                 {
//                     LOG4CXX_TRACE(logger, "长时间未接收,即将断开链接!"LOG_NOVAR(m_socketDescriptor));
//                     slotErroring();
//                     break;
//                 }
//                 LOG4CXX_TRACE(logger, "write:"LOG_NOVAR(m_socketDescriptor)LOG_NOVAR(tmp.toLocal8Bit().data()));

            }
        }
//         LOG4CXX_TRACE(logger, "finish2:"LOG_NOVAR(m_socketDescriptor));
        return;
    }
    catch (...)
    {
        // 核心线程异常处理
        LOG4CXX_ERROR(logger, "网络监控核心线程处理异常!"LOG_NOVAR(m_socketDescriptor));
        return;
    }
}

// void FortuneThread::slotErroring()
// {
// //     m_close_event.set();
//     LOG4CXX_TRACE(logger, "slotErroring:"LOG_NOVAR(m_socketDescriptor));
//     emit sglError();
// }

void FortuneThread::close()
{
    LOG4CXX_TRACE(logger, "准备关闭连接"LOG_NOVAR(m_socketDescriptor));
    m_close_event.set();

//     QTcpSocket tcpSocket;
// 
//     if (tcpSocket.setSocketDescriptor(m_socketDescriptor)) {
//         tcpSocket.disconnectFromHost();
//         bool bl = tcpSocket.waitForDisconnected();
//         qDebug() << QStringLiteral("关闭结果") << bl;
//         return;
//     }
}

// void FortuneThread::slotReadyRead()
// {
//     QTcpSocket* socket = qobject_cast<QTcpSocket*>(sender());
//     if (socket)
//     {
//         QString rawreply = socket->readAll();
//         readyRead(rawreply, socket->socketDescriptor());
//     }
// 
// }

// void FortuneThread::slotReadyRead()
// {
//     QTcpSocket* socket = static_cast<QTcpSocket*>(sender());
//     emit readMessage(socket->readAll());
// }
