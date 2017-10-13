#ifndef TCPSERVER_H
#define TCPSERVER_H

#include <memory>
#include <QtWidgets/QMainWindow>

class TCPImpl;
class VirtualQuote;

class TCPServer : public QMainWindow
{
    Q_OBJECT

public:
    TCPServer(QWidget *parent = 0);
    ~TCPServer();

    void stop();

protected:
    virtual void closeEvent(QCloseEvent *event) override;

public slots:
    void slotChangeQuoteStatus(bool bl);

private:
    std::shared_ptr<TCPImpl>    m_server;
    std::vector<VirtualQuote*>  m_threads;
};

#endif // TCPSERVER_H
