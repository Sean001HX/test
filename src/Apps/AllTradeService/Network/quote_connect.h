#ifndef QUOTECONNECT_H
#define QUOTECONNECT_H

#include <memory>
#include <QThread>
#include <QtWebSockets/QWebSocket>
#include "mdl_api_tl.h"
#include "define/params_declare.h"
#include "define/ystruct_define.h"
#include "utility/rwmutex.h"
#include "utility/sync.h"

class TCPImpl;
class MyMessageHandler;

class VirtualQuote : public QThread
{
    Q_OBJECT

signals:
    void sglChangeQuoteStatus(bool bCanTrade);

public:
    VirtualQuote(QObject *parent = Q_NULLPTR) :QThread(parent) {}
    virtual ~VirtualQuote(){}

    virtual void stopUpdate() = 0;

};

// 通联数据接口
class InitContractThread : public VirtualQuote, public TLDataCbk
{
    Q_OBJECT

public:
    InitContractThread(QObject *parent = Q_NULLPTR);
    ~InitContractThread();

    void stopUpdate() override;

private:
    void run();

protected:
    virtual void onUpdateEquityQuoteInfo(const mdl_shl1_msg::Equity& info) override; // 更新股票行情
    virtual void onUpdateEquityQuoteInfo(const mdl_szl1_msg::SZL1Stock& info) override; // 更新股票行情

private:
    struct HttpContractSt
    {
        HttpContractSt(){ memset(this, 0, sizeof(*this)); }
        AllTrade::ContractCodeType    contract_code_;
        AllTrade::ContractNameType    contract_name_;
        AllTrade::ExchangeCodeType    exchange_code_;
        AllTrade::StockStatusType     stock_status_;
        AllTrade::DateType            open_datetime_;       // 创建时间, eg:yyyy-MM-dd
        AllTrade::ContractPYCodeType  contract_py_code_;
        AllTrade::CurrencyCodeType    currency_code_;
        AllTrade::DisplayPropType     display_prop_;        // 显示属性
        AllTrade::DisplayPropTypeType display_prop_type_;   // 显示属性
        YDouble                       totalShares_;         // 总股本(最新)
        AllTrade::StockPlateAreaType  listSectorCD_;        //上市板块编码。例如，1-主板；2-创业板；3-中小板
    };

    void updateContract(const HttpContractSt& json);

private:
    MyMessageHandler*           m_quote_tl_data;
    std::map<std::string, AllTrade::StockStatusType> m_stockStatus;
};

class QTimer;

// C#自定义接口
class CSharpQuote : public VirtualQuote
{
    Q_OBJECT

signals :
    void sglSendMessage(const QString& data);

public:
    CSharpQuote(QObject *parent = Q_NULLPTR);
    ~CSharpQuote();

    void stopUpdate() override;

public:
    void init();
    void handleConnect();
    void registerQuotation();

public slots:
    void onConnected();
    void onTextMessageReceived(const QString &message);
    void onError(QAbstractSocket::SocketError error);
    void onDisConnected();

    void slotSendMessage(const QString& data);
    void handleMonitTimer();

    // 更新合约
//     void updateContract(const QMap<QString, QVariant>& data);

    // 更新行情
    void updateQuote(const QMap<QString, QVariant>& data);

private:
    void run();
    void boostTextMessageReceived(const QString &message);

private:
    QWebSocket				m_socketClient;
    QTimer*					m_timer;		    // 定时器
    QTimer*					m_timer_monit;		// 行情数据监控定时器,超时后仍未有任何数据更新视为断开行情,终止交易
    bool                    m_hasConnect;

    rwMutex                 m_mtx;
    QStringList             m_msgs;
    CommonTools::event      m_read_event;
    CommonTools::event      m_close_event;

    QTimer*                 m_test;
};

#endif // QUOTECONNECT
