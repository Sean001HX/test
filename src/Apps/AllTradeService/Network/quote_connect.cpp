#include <tbb/tbb.h>
#include <tbb/blocked_range.h>
#include <tbb/parallel_for.h>
#include <boost/thread/thread.hpp>
#include <QMessageBox>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <sstream>
#include "quote_connect.h"
#include "TCPImpl.h"
#include "include/ManagerCenter/ManagerCenter.h"
#include "include/TradeCenter/TradeCenter.h"
#include "define/struct_extern.h"
#include "utility/utility_fun.h"
#include "dataClient.h"
#include "define/struct_content.h"

#include <QTimer>

#include "C:/ng_tools/ng_header_for_log4cxx/ng_header_for_log4cxx.hpp"
#include "C:/ng_tools/ng_header_for_log4cxx/ng_header_for_log4cxx_log_var.hpp"

using namespace AllTrade;
using namespace AllTrade::NPMgrCenter;
using namespace AllTrade::NPTradeCenter;

NG_LOGGER(logger, "InitContractThread");

////////////////////////////////////////////////////////////////////////
InitContractThread::InitContractThread(QObject *parent)
    : VirtualQuote(parent)
{

}

InitContractThread::~InitContractThread()
{
    stopUpdate();
}

void InitContractThread::run()
{
    m_stockStatus.emplace("S", StockStatusType::STOCKSTATUS_S);
    m_stockStatus.emplace("L", StockStatusType::STOCKSTATUS_L);
    m_stockStatus.emplace("DE", StockStatusType::STOCKSTATUS_DE);
    m_stockStatus.emplace("UN", StockStatusType::STOCKSTATUS_UN);

    char chr_host[255] = { 0 };
    GetPrivateProfileStringA("Quote", "host0", "127.0.0.1", chr_host, sizeof(chr_host), "./config.hxc");
    char chr_port[255] = { 0 };
    GetPrivateProfileStringA("Quote", "port0", "8080", chr_port, sizeof(chr_port), "./config.hxc");
    std::stringstream ip_host;
    ip_host << chr_host << ":" << chr_port;

    m_quote_tl_data = new MyMessageHandler;
    m_quote_tl_data->setTLDataCbk(this);
    if (m_quote_tl_data->Open(ip_host.str().c_str())){
        LOG4CXX_TRACE(logger, "已打开行情连接端口"LOG_NOVAR(ip_host.str()));
    }

    int retcode;
    DataClient client;
    char chr_token[255] = { 0 };
    GetPrivateProfileStringA("Quote", "log4cxxkey", "", chr_token, sizeof(chr_token), "./config.hxc");
    std::string token = chr_token;//可以数据商城中获取
    std::string result;
    //初始化token
    int init_rslt = client.init(token);
    //获取GDP api
    char chr_url[255] = { 0 };
    GetPrivateProfileStringA("Quote", "url", "", chr_url, sizeof(chr_url), "./config.hxc");
    std::string URL1 = chr_url;
    retcode = client.getData(URL1, result);

    if (retcode == RETCODE_SUCC){
        QJsonParseError error;
        QJsonDocument jsonDocument = QJsonDocument::fromJson(QString::fromUtf8(result.c_str()).toUtf8(), &error);
        if (error.error == QJsonParseError::NoError) {
            if (jsonDocument.isObject())
            {
                auto rsltMap = jsonDocument.toVariant().toMap();
                auto contract_list = rsltMap["data"].toList();
                for (auto contract : contract_list)
                {
                    auto contract_map = contract.toMap();
                    if (contract_map["transCurrCD"].toString() != QString("CNY")
                        || (contract_map["exchangeCD"].toString() != QString("XSHG")
                        && contract_map["exchangeCD"].toString() != QString("XSHE"))
                        || (contract_map["listStatusCD"].toString() != QString("L")
                        && contract_map["listStatusCD"].toString() != QString("S")))
                        continue;

                    HttpContractSt json;
                    strncpy_s(json.contract_code_, contract_map["ticker"].toString().toLocal8Bit(), sizeof(json.contract_code_) - 1);
                    QString contractName = contract_map["secShortName"].toString();
                    strncpy_s(json.contract_name_, contractName.toLocal8Bit(), sizeof(json.contract_name_) - 1);
                    strncpy_s(json.exchange_code_, contract_map["exchangeCD"].toString().toLocal8Bit(), sizeof(json.exchange_code_) - 1);
                    json.stock_status_ = m_stockStatus[contract_map["listStatusCD"].toString().toLocal8Bit().data()];
                    strncpy_s(json.open_datetime_, contract_map["listDate"].toString().toLocal8Bit(), sizeof(json.open_datetime_) - 1);
                    strncpy_s(json.contract_py_code_, contract_map["cnSpell"].toString().toLocal8Bit(), sizeof(json.contract_py_code_) - 1);
                    strncpy_s(json.currency_code_, contract_map["transCurrCD"].toString().toLocal8Bit(), sizeof(json.currency_code_) - 1);
                    json.totalShares_ = contract_map["totalShares"].toDouble();
                    json.listSectorCD_ = (StockPlateAreaType)(contract_map["ListSectorCD"].toInt() - 1);

                    if (contractName.indexOf("*ST") == 0)
                    {
                        strncpy_s(json.display_prop_, "*ST", sizeof(json.display_prop_) - 1);
                        json.display_prop_type_ = DisplayPropTypeType::DPTT_StarST;
                    }
                    else if (contractName.indexOf("SST") == 0)
                    {
                        strncpy_s(json.display_prop_, "SST", sizeof(json.display_prop_) - 1);
                        json.display_prop_type_ = DisplayPropTypeType::DPTT_SST;
                    }
                    else if (contractName.indexOf("ST") == 0)
                    {
                        strncpy_s(json.display_prop_, "ST", sizeof(json.display_prop_) - 1);
                        json.display_prop_type_ = DisplayPropTypeType::DPTT_ST;
                    }
                    else if (contractName.indexOf("S*ST") == 0)
                    {
                        strncpy_s(json.display_prop_, "S*ST", sizeof(json.display_prop_) - 1);
                        json.display_prop_type_ = DisplayPropTypeType::DPTT_SStarST;
                    }
                    else if (contractName.indexOf("S") == 0)
                    {
                        strncpy_s(json.display_prop_, "S", sizeof(json.display_prop_) - 1);
                        json.display_prop_type_ = DisplayPropTypeType::DPTT_S;
                    }
                    else
                        json.display_prop_type_ = DisplayPropTypeType::DPTT_Normal;

                    updateContract(json);
                }
            }
        }

    }
    else{
        LOG4CXX_ERROR(logger, "合约获取失败,初始化结果"LOG_NOVAR(init_rslt)
            ",url"LOG_NOVAR(chr_url)
            ",获取结果"LOG_NOVAR(retcode)
            );
        assert(0);
    }

    int i_simul = GetPrivateProfileIntA("Trade", "simul_trade", 1, "./config.hxc");
    if (i_simul == 1)
    {
        SContractPtr contract_ptr = IManagerCenter::instance()->getStockContractByCode(StockAreaType::STOCKAREA_TYPE_A, "000001");
        if (!contract_ptr)
            return;

        SExchangePtr exchange_ptr = IManagerCenter::instance()->getExchangeByID(CommodityTypeType::COMMODITY_TYPE_STOCK, contract_ptr->exchange_id_);
        if (!exchange_ptr)
            return;

        QuoteInfoPtr quote_ptr = std::make_shared<QuoteInfoBase>();
        strncpy_s(quote_ptr->contract_id_, contract_ptr->contract_id_, sizeof(quote_ptr->contract_id_) - 1);
        quote_ptr->last_price_ = 11.04;
        quote_ptr->yclose_price_ = 10.67;
        quote_ptr->ysettle_price_ = 10.67;
        quote_ptr->open_price_ = 10.67;

        quote_ptr->bid_price_[0] = 11.25;
        quote_ptr->bid_volume_[0] = 100;
        quote_ptr->bid_price_[1] = 100;
        quote_ptr->bid_volume_[1] = 100;
        quote_ptr->bid_price_[2] = 100;
        quote_ptr->bid_volume_[2] = 100;
        quote_ptr->bid_price_[3] = 100;
        quote_ptr->bid_volume_[3] = 100;
        quote_ptr->bid_price_[4] = 100;
        quote_ptr->bid_volume_[4] = 100;

        quote_ptr->ask_price_[0] = 11.03;
        quote_ptr->ask_volume_[0] = 100;
        quote_ptr->ask_price_[1] = 100;
        quote_ptr->ask_volume_[1] = 100;
        quote_ptr->ask_price_[2] = 100;
        quote_ptr->ask_volume_[2] = 100;
        quote_ptr->ask_price_[3] = 100;
        quote_ptr->ask_volume_[3] = 100;
        quote_ptr->ask_price_[4] = 100;
        quote_ptr->ask_volume_[4] = 100;

        quote_ptr->quote_status_ = QuoteStatusType::QUOTESTATUS_Normal;
        ITradeCenter::instance()->updateQuote(quote_ptr, exchange_ptr, contract_ptr);
    }

}

void InitContractThread::stopUpdate()
{
    if (isRunning())
        quit();

    if (m_quote_tl_data)
    {
        m_quote_tl_data->Close();
        delete m_quote_tl_data;
        m_quote_tl_data = nullptr;
    }
}

void InitContractThread::onUpdateEquityQuoteInfo(const mdl_shl1_msg::Equity& info)
{
    int i_tl = GetPrivateProfileIntA("Quote", "source", 0, "./config.hxc");
    if (i_tl == 0)
        return;

    SContractPtr contract_ptr = IManagerCenter::instance()->getStockContractByCode(StockAreaType::STOCKAREA_TYPE_A, info.SecurityID.std_str().c_str());
    if (!contract_ptr)
        return;
    SExchangePtr exchange_ptr = IManagerCenter::instance()->getExchangeByID(CommodityTypeType::COMMODITY_TYPE_STOCK, contract_ptr->exchange_id_);
    if (!exchange_ptr)
        return;

    QuoteInfoPtr quote_ptr = std::make_shared<QuoteInfoBase>();
    strncpy_s(quote_ptr->contract_id_, contract_ptr->contract_id_, sizeof(quote_ptr->contract_id_) - 1);
    quote_ptr->last_price_ = info.LastPrice.GetDouble();
    quote_ptr->yclose_price_ = info.PreCloPrice.GetDouble();
    quote_ptr->ysettle_price_ = info.PreCloPrice.GetDouble();
    quote_ptr->open_price_ = info.OpenPrice.GetDouble();
    for (SizeType i = 0; i < info.BidPriceLevel.Length && i < 5; i++)
    {
        quote_ptr->bid_price_[i] = info.BidPriceLevel[i]->Price.GetDouble();
        quote_ptr->bid_volume_[i] = info.BidPriceLevel[i]->Volume;
    }
    for (SizeType i = 0; i < info.AskPriceLevel.Length && i < 5; i++)
    {
        quote_ptr->ask_price_[i] = info.AskPriceLevel[i]->Price.GetDouble();
        quote_ptr->ask_volume_[i] = info.AskPriceLevel[i]->Volume;
    }
//     quote_ptr->deletion_indicator_ = info.BidPriceLevel

    ITradeCenter::instance()->updateQuote(quote_ptr, exchange_ptr, contract_ptr);
}

void InitContractThread::onUpdateEquityQuoteInfo(const mdl_szl1_msg::SZL1Stock& info)
{
    int i_tl = GetPrivateProfileIntA("Quote", "source", 0, "./config.hxc");
    if (i_tl == 0)
        return;

    SContractPtr contract_ptr = IManagerCenter::instance()->getStockContractByCode(StockAreaType::STOCKAREA_TYPE_A, info.SecurityID.std_str().c_str());
    if (!contract_ptr)
        return;

    SExchangePtr exchange_ptr = IManagerCenter::instance()->getExchangeByID(CommodityTypeType::COMMODITY_TYPE_STOCK, contract_ptr->exchange_id_);
    if (!exchange_ptr)
        return;

    QuoteInfoPtr quote_ptr = std::make_shared<QuoteInfoBase>();
    strncpy_s(quote_ptr->contract_id_, contract_ptr->contract_id_, sizeof(quote_ptr->contract_id_) - 1);
    quote_ptr->last_price_ = info.LastPrice.GetFloat();
    quote_ptr->yclose_price_ = info.PreCloPrice.GetFloat();
    quote_ptr->ysettle_price_ = info.PreCloPrice.GetFloat();
    quote_ptr->open_price_ = info.OpenPrice.GetFloat();

    quote_ptr->bid_price_[0] = info.BidPrice1.GetFloat();
    quote_ptr->bid_volume_[0] = info.BidVolume1;
    quote_ptr->bid_price_[1] = info.BidPrice2.GetFloat();
    quote_ptr->bid_volume_[1] = info.BidVolume2;
    quote_ptr->bid_price_[2] = info.BidPrice3.GetFloat();
    quote_ptr->bid_volume_[2] = info.BidVolume3;
    quote_ptr->bid_price_[3] = info.BidPrice4.GetFloat();
    quote_ptr->bid_volume_[3] = info.BidVolume4;
    quote_ptr->bid_price_[4] = info.BidPrice5.GetFloat();
    quote_ptr->bid_volume_[4] = info.BidVolume5;

    quote_ptr->ask_price_[0] = info.AskPrice1.GetFloat();
    quote_ptr->ask_volume_[0] = info.AskVolume1;
    quote_ptr->ask_price_[1] = info.AskPrice2.GetFloat();
    quote_ptr->ask_volume_[1] = info.AskVolume2;
    quote_ptr->ask_price_[2] = info.AskPrice3.GetFloat();
    quote_ptr->ask_volume_[2] = info.AskVolume3;
    quote_ptr->ask_price_[3] = info.AskPrice4.GetFloat();
    quote_ptr->ask_volume_[3] = info.AskVolume4;
    quote_ptr->ask_price_[4] = info.AskPrice5.GetFloat();
    quote_ptr->ask_volume_[4] = info.AskVolume5;

    quote_ptr->quote_status_ = (QuoteStatusType)info.DeletionIndicator;

    ITradeCenter::instance()->updateQuote(quote_ptr, exchange_ptr, contract_ptr);
}

void InitContractThread::updateContract(const HttpContractSt& json)
{
    SContractPtr contract_ptr_new = IManagerCenter::instance()->getStockContractByCode(StockAreaType::STOCKAREA_TYPE_A, json.contract_code_);
    SExchangePtr exchange_ptr(nullptr);
    if (!contract_ptr_new)
    {
        exchange_ptr = IManagerCenter::instance()->getExchangeByCode(CommodityTypeType::COMMODITY_TYPE_STOCK, json.exchange_code_);
        if (!exchange_ptr)
        {
            exchange_ptr = std::make_shared<SExchange>();
            strncpy_s(exchange_ptr->exchange_id_, UtilityFun::createGUID().c_str(), sizeof(exchange_ptr->exchange_id_) - 1);
            exchange_ptr->commodity_type_ = CommodityTypeType::COMMODITY_TYPE_STOCK;
            strncpy_s(exchange_ptr->exchange_code_, json.exchange_code_, sizeof(exchange_ptr->exchange_code_) - 1);
            strncpy_s(exchange_ptr->exchange_name_, json.exchange_code_, sizeof(exchange_ptr->exchange_name_) - 1);
            exchange_ptr->open_margin_ = 0;

            AllTrade::ErrorCodeType err_code = IManagerCenter::instance()->addExchange(exchange_ptr);
            if (err_code != Err_Succeed)
            {
                assert(0);
                return;
            }
        }
		
        SStockContractPtr contract_ptr = std::make_shared<SStockContract>();
        strncpy_s(contract_ptr->contract_id_, UtilityFun::createGUID().c_str(), sizeof(contract_ptr->contract_id_) - 1);
        strncpy_s(contract_ptr->contract_py_code_, json.contract_py_code_, sizeof(contract_ptr->contract_py_code_) - 1);
        strncpy_s(contract_ptr->contract_code_, json.contract_code_, sizeof(contract_ptr->contract_code_) - 1);
        strncpy_s(contract_ptr->contract_name_, json.contract_name_, sizeof(contract_ptr->contract_name_) - 1);
        strncpy_s(contract_ptr->open_datetime_, json.open_datetime_, sizeof(contract_ptr->open_datetime_) - 1);
        strncpy_s(contract_ptr->delivery_datetime_, "0000-00-00 00:00:00", sizeof(contract_ptr->delivery_datetime_) - 1);
        strncpy_s(contract_ptr->trade_datetime_, "0000-00-00 00:00:00", sizeof(contract_ptr->trade_datetime_) - 1);
        contract_ptr->stock_status_ = json.stock_status_;
        contract_ptr->commodity_type_ = CommodityTypeType::COMMODITY_TYPE_STOCK;
        contract_ptr->stock_area_ = StockAreaType::STOCKAREA_TYPE_A;
        strncpy_s(contract_ptr->exchange_id_, exchange_ptr->exchange_id_, sizeof(contract_ptr->exchange_id_) - 1);
        contract_ptr->min_price_change_ = 0.001;
        contract_ptr->contract_multiplier_ = 100;
        strncpy_s(contract_ptr->display_prop_, json.display_prop_, sizeof(contract_ptr->display_prop_) - 1);
        contract_ptr->display_prop_type_ = json.display_prop_type_;
        contract_ptr->stock_plate_area_ = json.listSectorCD_;
        contract_ptr->total_shares_ = json.totalShares_;
        contract_ptr_new = contract_ptr;

        AllTrade::ErrorCodeType err_code = IManagerCenter::instance()->addContract(contract_ptr);
        assert(err_code == Err_Succeed);
    }
    else
    {
        SStockContractPtr contract_ptr = std::dynamic_pointer_cast<SStockContract>(contract_ptr_new);
        strncpy_s(contract_ptr->contract_py_code_, json.contract_py_code_, sizeof(contract_ptr->contract_py_code_) - 1);
        strncpy_s(contract_ptr->contract_name_, json.contract_name_, sizeof(contract_ptr->contract_name_) - 1);
        strncpy_s(contract_ptr->open_datetime_, json.open_datetime_, sizeof(contract_ptr->open_datetime_) - 1);
        contract_ptr->stock_status_ = json.stock_status_;
        contract_ptr->stock_plate_area_ = json.listSectorCD_;
        strncpy_s(contract_ptr->display_prop_, json.display_prop_, sizeof(contract_ptr->display_prop_) - 1);
        contract_ptr->display_prop_type_ = json.display_prop_type_;
        contract_ptr->total_shares_ = json.totalShares_;
        AllTrade::ErrorCodeType err_code = IManagerCenter::instance()->addContract(contract_ptr);
        assert(err_code == Err_Succeed);
    }
}

//////////////////////////////////////////////////////////////////////////
CSharpQuote::CSharpQuote(QObject *parent /*= Q_NULLPTR*/)
    : VirtualQuote(parent)
    , m_timer(nullptr)
    , m_timer_monit(nullptr)
    , m_test(nullptr)
{
    m_socketClient.setPauseMode(QAbstractSocket::PauseNever);
    m_timer = new QTimer(this);
    m_timer->setSingleShot(true);
    m_timer->setInterval(1000);


    connect(m_timer, &QTimer::timeout, this, &CSharpQuote::handleConnect);

    m_timer_monit = new QTimer(this);
    int i_interval = GetPrivateProfileIntA("Quote", "interval1", 3, "./config.hxc");
    m_timer_monit->setInterval(i_interval * 1000);
    connect(m_timer_monit, &QTimer::timeout, this, &CSharpQuote::handleMonitTimer);

    init();
}

CSharpQuote::~CSharpQuote()
{
    if (m_test)
        m_test->stop();

    stopUpdate();
}

void CSharpQuote::stopUpdate()
{
    m_close_event.set();
    m_timer->stop();
    disconnect(&m_socketClient, &QWebSocket::connected, this, &CSharpQuote::onConnected);
    disconnect(&m_socketClient, &QWebSocket::disconnected, this, &CSharpQuote::onDisConnected);
    disconnect(&m_socketClient, &QWebSocket::textMessageReceived, this, &CSharpQuote::onTextMessageReceived);
    disconnect(&m_socketClient, static_cast<void(QWebSocket::*)(QAbstractSocket::SocketError)>(&QWebSocket::error), this, &CSharpQuote::onError);
    m_socketClient.close();
}

void CSharpQuote::run()
{
    while (true)
    {
        const int handlerCnt = 2;
        CommonTools::handler handlerTable[] = { m_read_event, m_close_event };
    
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
   
        QList<QString> msg_tmps;
        {
            writeLock lock(m_mtx);
            msg_tmps.swap(m_msgs);
        }
   
        // 采用tbb并发
        typedef QList<QString>::iterator MsgListIter;
        tbb::parallel_for(tbb::blocked_range<MsgListIter>(msg_tmps.begin(), msg_tmps.end())
            , [&](const tbb::blocked_range<MsgListIter>& range){
            for (auto i = range.begin(); i != range.end(); i++)
            {
                boostTextMessageReceived(*i);
            }
        });
    }
}

void CSharpQuote::init()
{
    bool bl = connect(this, &CSharpQuote::sglSendMessage, this, &CSharpQuote::slotSendMessage, Qt::QueuedConnection);

    connect(&m_socketClient, &QWebSocket::connected, this, &CSharpQuote::onConnected);
    connect(&m_socketClient, &QWebSocket::disconnected, this, &CSharpQuote::onDisConnected);
    connect(&m_socketClient, &QWebSocket::textMessageReceived, this, &CSharpQuote::onTextMessageReceived, Qt::QueuedConnection);
    connect(&m_socketClient, static_cast<void(QWebSocket::*)(QAbstractSocket::SocketError)>(&QWebSocket::error), this, &CSharpQuote::onError);

    handleConnect();

    int i_simul = GetPrivateProfileIntA("Trade", "simul_trade", 1, "./config.hxc");
    if (i_simul == 1)
    {
        m_test = new QTimer(this);
        m_test->start(3000);
        connect(m_test, &QTimer::timeout, []{
            SContractPtr contract_ptr = IManagerCenter::instance()->getStockContractByCode(StockAreaType::STOCKAREA_TYPE_A, "000630");
            if (!contract_ptr)
                return;

            SExchangePtr exchange_ptr = IManagerCenter::instance()->getExchangeByID(CommodityTypeType::COMMODITY_TYPE_STOCK, contract_ptr->exchange_id_);
            if (!exchange_ptr)
                return;

            QuoteInfoPtr quote_ptr = std::make_shared<QuoteInfoBase>();
            strncpy_s(quote_ptr->contract_id_, contract_ptr->contract_id_, sizeof(quote_ptr->contract_id_) - 1);
            quote_ptr->last_price_ = 3.05;
            quote_ptr->yclose_price_ = 3.06;
            quote_ptr->ysettle_price_ = 3.06;
            quote_ptr->open_price_ = 3.05;

            quote_ptr->bid_price_[0] = 3.04;
            quote_ptr->bid_volume_[0] = 100;
            quote_ptr->bid_price_[1] = quote_ptr->last_price_ - 0.01;
            quote_ptr->bid_volume_[1] = 100;
            quote_ptr->bid_price_[2] = quote_ptr->last_price_ - 0.01;
            quote_ptr->bid_volume_[2] = 100;
            quote_ptr->bid_price_[3] = quote_ptr->last_price_ - 0.01;
            quote_ptr->bid_volume_[3] = 100;
            quote_ptr->bid_price_[4] = quote_ptr->last_price_ - 0.01;
            quote_ptr->bid_volume_[4] = 100;

            quote_ptr->ask_price_[0] = 3.05;
            quote_ptr->ask_volume_[0] = 100;
            quote_ptr->ask_price_[1] = quote_ptr->last_price_ + 0.01;
            quote_ptr->ask_volume_[1] = 100;
            quote_ptr->ask_price_[2] = quote_ptr->last_price_ + 0.01;
            quote_ptr->ask_volume_[2] = 100;
            quote_ptr->ask_price_[3] = quote_ptr->last_price_ + 0.01;
            quote_ptr->ask_volume_[3] = 100;
            quote_ptr->ask_price_[4] = quote_ptr->last_price_ + 0.01;
            quote_ptr->ask_volume_[4] = 100;

            quote_ptr->quote_status_ = QuoteStatusType::QUOTESTATUS_Normal;
            ITradeCenter::instance()->updateQuote(quote_ptr, exchange_ptr, contract_ptr);
        });
    }
    

}

void CSharpQuote::handleConnect()
{
    char chr_host[255] = { 0 };
    GetPrivateProfileStringA("Quote", "host1", "", chr_host, sizeof(chr_host), "./config.hxc");
    int i_port = GetPrivateProfileIntA("Quote", "port1", 3011, "./config.hxc");

    QString path = QString("ws://%1:%2").arg(QString::fromLocal8Bit(chr_host)).arg(QString::number(i_port));
    QUrl url = QUrl(path);
    m_socketClient.open(url);
    LOG4CXX_TRACE(logger, "准备连接行情"LOG_NOVAR(path.toLocal8Bit().data()));
}

void CSharpQuote::slotSendMessage(const QString& data)
{
    m_socketClient.sendTextMessage(data);
}

void CSharpQuote::registerQuotation()
{
    QDateTime time = QDateTime::currentDateTime();            // 获取系统现在的时间
    QString tmpStr = time.toString("yyyy-MM-dd hh:mm:ss");   // 设置显示格式

    QJsonObject obContent;

    obContent[SUBSCRIBETYPE] = 0;
    obContent[ISTICKER] = 2;
    obContent[CURRENTTIME] = tmpStr;

    emit sglSendMessage(QString(QJsonDocument(obContent).toJson()));
}

void CSharpQuote::onConnected()
{
    LOG4CXX_INFO(logger, "行情连接成功!");

    registerQuotation(); // 重新注册行情

    int i_simul = GetPrivateProfileIntA("Trade", "simul_trade", 1, "./config.hxc");
    if (i_simul != 1)
    {
        emit sglChangeQuoteStatus(true);
        m_timer_monit->start();
    }
}

void CSharpQuote::onTextMessageReceived(const QString &message)
{
    int i_simul = GetPrivateProfileIntA("Trade", "simul_trade", 1, "./config.hxc");
    if (i_simul != 1)
    {
        if (m_timer_monit->isActive())
            m_timer_monit->stop();
        m_timer_monit->start();
    }

    writeLock lock(m_mtx);
    m_msgs << message;
    m_read_event.set();
}

void CSharpQuote::boostTextMessageReceived(const QString &message)
{
    if (m_close_event.trywait())
    {
        m_close_event.set();
        return;
    }

    QJsonParseError error;
    QJsonDocument jsonDocument = QJsonDocument::fromJson(message.toUtf8(), &error);
    if (error.error == QJsonParseError::NoError)
    {
        if (jsonDocument.isObject())
        {
            QVariantMap result = jsonDocument.toVariant().toMap();

            // 0 开始订阅 返回行情
            if (result[SENDTYPE].toInt() == 0)
            {
                auto realQuotMap = result[QUOTATIONS].toList();
                for (auto item : realQuotMap)
                {
                    auto realMap = item.toMap(); // 转map

                    if (realMap[EXCHANGECD].toString() == XSHG || realMap[EXCHANGECD].toString() == XSHE)
                        updateQuote(realMap);
                }
            }
            // 1 行情推送
            else if (1 == result[SENDTYPE].toInt())
            {
                auto realMap = result[QUOTATION].toMap();
                updateQuote(realMap);
            }
        }
    }
}

void CSharpQuote::onError(QAbstractSocket::SocketError error)
{
    QString msg;
    switch (error)
    {
    case QAbstractSocket::ConnectionRefusedError:
        msg = QStringLiteral("行情连接被拒绝!");
        break;
    case QAbstractSocket::RemoteHostClosedError:
        msg = QStringLiteral("行情远程主机关闭!");
        break;
    case QAbstractSocket::HostNotFoundError:
        msg = QStringLiteral("未发现行情远程主机!");
        break;
    case QAbstractSocket::SocketAccessError:
        msg = QStringLiteral("行情访问错误!");
        break;
    case QAbstractSocket::SocketResourceError:
        msg = QStringLiteral("行情资源错误!");
        break;
    case QAbstractSocket::SocketTimeoutError:
        msg = QStringLiteral("行情访问超时!");
        break;
    case QAbstractSocket::DatagramTooLargeError:
        msg = QStringLiteral("行情数据报过大!");
        break;
    case QAbstractSocket::NetworkError:
        msg = QStringLiteral("网络错误!");
        break;
    case QAbstractSocket::AddressInUseError:
        msg = QStringLiteral("行情地址被占用!");
        break;
    case QAbstractSocket::SocketAddressNotAvailableError:
        msg = QStringLiteral("行情地址不可用错误!");
        break;
    case QAbstractSocket::UnsupportedSocketOperationError:
        msg = QStringLiteral("不支持的行情操作错误!");
        break;
    case QAbstractSocket::UnfinishedSocketOperationError:
        msg = QStringLiteral("未完成的行情操作错误!");
        break;
    case QAbstractSocket::ProxyAuthenticationRequiredError:
        msg = QStringLiteral("行情代理身份验证错误!");
        break;
    case QAbstractSocket::SslHandshakeFailedError:
        msg = QStringLiteral("行情SSL握手失败!");
        break;
    case QAbstractSocket::ProxyConnectionRefusedError:
        msg = QStringLiteral("行情代理服务器连接被拒绝!");
        break;
    case QAbstractSocket::ProxyConnectionClosedError:
        msg = QStringLiteral("行情代理服务器连接被关闭!");
        break;
    case QAbstractSocket::ProxyConnectionTimeoutError:
        msg = QStringLiteral("行情代理服务器连接超时!");
        break;
    case QAbstractSocket::ProxyNotFoundError:
        msg = QStringLiteral("无法找到行情代理!");
        break;
    case QAbstractSocket::ProxyProtocolError:
        msg = QStringLiteral("代理协议错误!");
        break;
    case QAbstractSocket::OperationError:
        msg = QStringLiteral("操作错误!");
        break;
    case QAbstractSocket::SslInternalError:
        msg = QStringLiteral("SSL内部错误!");
        break;
    case QAbstractSocket::SslInvalidUserDataError:
        msg = QStringLiteral("无效的SSL用户数据!");
        break;
    case QAbstractSocket::TemporaryError:
        msg = QStringLiteral("临时错误!");
        break;
    case QAbstractSocket::UnknownSocketError:
        msg = QStringLiteral("未知的Socket错误!");
        break;
    default:
        break;
    }
    LOG4CXX_ERROR(logger, "行情连接异常!"LOG_NOVAR(msg.toLocal8Bit().data()));
    onDisConnected();
}

// 重连尚未处理
void CSharpQuote::onDisConnected()
{
    int i_simul = GetPrivateProfileIntA("Trade", "simul_trade", 1, "./config.hxc");
    if (i_simul != 1)
    {
        m_timer->start();
        emit sglChangeQuoteStatus(false);
        m_timer_monit->stop();
        LOG4CXX_ERROR(logger, "行情连接断开!");
    }
}

void CSharpQuote::handleMonitTimer()
{
    qDebug() << QStringLiteral("行情长时间无更新!");
    int i_simul = GetPrivateProfileIntA("Trade", "simul_trade", 1, "./config.hxc");
    if (i_simul != 1)
    {
        emit sglChangeQuoteStatus(false);
        m_timer_monit->stop();
    }
}

void CSharpQuote::updateQuote(const QMap<QString, QVariant>& data)
{
    emit sglChangeQuoteStatus(true);

    QString tmopp = data[TICKER].toString();
//     char* contract_code = data[TICKER].toString().toLocal8Bit().data();
    SContractPtr contract_ptr = IManagerCenter::instance()->getStockContractByCode(StockAreaType::STOCKAREA_TYPE_A, tmopp.toStdString().c_str());
    if (!contract_ptr)
        return;

    SExchangePtr exchange_ptr = IManagerCenter::instance()->getExchangeByID(CommodityTypeType::COMMODITY_TYPE_STOCK, contract_ptr->exchange_id_);
    if (!exchange_ptr)
        return;

    QuoteInfoPtr quote_ptr = std::make_shared<QuoteInfoBase>();
    strncpy_s(quote_ptr->contract_id_, contract_ptr->contract_id_, sizeof(quote_ptr->contract_id_) - 1);
    quote_ptr->last_price_ = data[LASTPRICE].toDouble();
    quote_ptr->yclose_price_ = data[PREVCLOSEPRICE].toDouble();
    quote_ptr->ysettle_price_ = data[PREVCLOSEPRICE].toDouble();
    quote_ptr->open_price_ = data[OPENPRICE].toDouble();
    quote_ptr->highest_price_ = data[HIGHPRICE].toDouble();
    quote_ptr->lowest_price_ = data[LOWPRICE].toDouble();

    quote_ptr->bid_price_[0] = data[BIDBOOKPRICE1].toDouble();
    quote_ptr->bid_volume_[0] = data[BIDBOOKVOLUME1].toInt();
    quote_ptr->bid_price_[1] = data[BIDBOOKPRICE2].toDouble();
    quote_ptr->bid_volume_[1] = data[BIDBOOKVOLUME2].toInt();
    quote_ptr->bid_price_[2] = data[BIDBOOKPRICE3].toDouble();
    quote_ptr->bid_volume_[2] = data[BIDBOOKVOLUME3].toInt();
    quote_ptr->bid_price_[3] = data[BIDBOOKPRICE4].toDouble();
    quote_ptr->bid_volume_[3] = data[BIDBOOKVOLUME4].toInt();
    quote_ptr->bid_price_[4] = data[BIDBOOKPRICE5].toDouble();
    quote_ptr->bid_volume_[4] = data[BIDBOOKVOLUME5].toInt();

    quote_ptr->ask_price_[0] = data[ASKBOOKPRICE1].toDouble();
    quote_ptr->ask_volume_[0] = data[ASKBOOKVOLUME1].toInt();
    quote_ptr->ask_price_[1] = data[ASKBOOKPRICE2].toDouble();
    quote_ptr->ask_volume_[1] = data[ASKBOOKVOLUME2].toInt();
    quote_ptr->ask_price_[2] = data[ASKBOOKPRICE3].toDouble();
    quote_ptr->ask_volume_[2] = data[ASKBOOKVOLUME3].toInt();
    quote_ptr->ask_price_[3] = data[ASKBOOKPRICE4].toDouble();
    quote_ptr->ask_volume_[3] = data[ASKBOOKVOLUME4].toInt();
    quote_ptr->ask_price_[4] = data[ASKBOOKPRICE5].toDouble();
    quote_ptr->ask_volume_[4] = data[ASKBOOKVOLUME5].toInt();

    quote_ptr->quote_status_ = QuoteStatusType::QUOTESTATUS_Normal;

    if (quote_ptr->last_price_ <= 0.0 || quote_ptr->yclose_price_ <= 0.0
        || quote_ptr->ysettle_price_ <= 0.0 || quote_ptr->open_price_ <= 0.0
        || quote_ptr->highest_price_ <= 0.0 || quote_ptr->lowest_price_ <= 0.0
        /*无量涨跌停*/
        /*|| quote_ptr->bid_price_[0] <= 0.0 || quote_ptr->bid_volume_[0] <= 0*/
        /*|| quote_ptr->bid_price_[1] <= 0.0 || quote_ptr->bid_volume_[1] <= 0*/
        /*|| quote_ptr->bid_price_[2] <= 0.0 || quote_ptr->bid_volume_[2] <= 0*/
        /*|| quote_ptr->bid_price_[3] <= 0.0 || quote_ptr->bid_volume_[3] <= 0*/
        /*|| quote_ptr->bid_price_[4] <= 0.0 || quote_ptr->bid_volume_[4] <= 0*/
        /*|| quote_ptr->ask_price_[0] <= 0.0 || quote_ptr->ask_volume_[0] <= 0*/
        /*|| quote_ptr->ask_price_[1] <= 0.0 || quote_ptr->ask_volume_[1] <= 0*/
        /*|| quote_ptr->ask_price_[2] <= 0.0 || quote_ptr->ask_volume_[2] <= 0*/
        /*|| quote_ptr->ask_price_[3] <= 0.0 || quote_ptr->ask_volume_[3] <= 0*/
        /*|| quote_ptr->ask_price_[4] <= 0.0 || quote_ptr->ask_volume_[4] <= 0*/)
    {
        QJsonDocument doc = QJsonDocument::fromVariant(QVariant(data));
        LOG4CXX_WARN(logger, "行情数据有误"LOG_NOVAR(QString(doc.toJson()).toLocal8Bit().data()));
        return;
    }

    ITradeCenter::instance()->updateQuote(quote_ptr, exchange_ptr, contract_ptr);
}

// void CSharpQuote::updateContract(const QMap<QString, QVariant>& data)
// {
//     try
//     {
//         if (data[EXCHANGECD].toString() == XSHG || data[EXCHANGECD].toString() == XSHE)
//         {
//             char* exchange_code = data[EXCHANGECD].toString().toLocal8Bit().data();
//             char* contract_code = data[TICKER].toString().toLocal8Bit().data();
//             char* contract_name = data[SHORTNM].toString().toLocal8Bit().data();
// 
//             SContractPtr contract_ptr_new = IManagerCenter::instance()->getStockContractByCode(StockAreaType::STOCKAREA_TYPE_A, contract_code);
//             SExchangePtr exchange_ptr(nullptr);
//             if (!contract_ptr_new)
//             {
//                 return;
//                 exchange_ptr = IManagerCenter::instance()->getExchangeByCode(CommodityTypeType::COMMODITY_TYPE_STOCK, exchange_code);
//                 if (!exchange_ptr)
//                 {
//                     exchange_ptr = std::make_shared<SExchange>();
//                     strncpy_s(exchange_ptr->exchange_id_, UtilityFun::createGUID().c_str(), sizeof(exchange_ptr->exchange_id_) - 1);
//                     exchange_ptr->commodity_type_ = CommodityTypeType::COMMODITY_TYPE_STOCK;
//                     strncpy_s(exchange_ptr->exchange_code_, exchange_code, sizeof(exchange_ptr->exchange_code_) - 1);
//                     strncpy_s(exchange_ptr->exchange_name_, exchange_code, sizeof(exchange_ptr->exchange_name_) - 1);
//                     exchange_ptr->open_margin_ = 0;
// 
//                     AllTrade::ErrorCodeType err_code = IManagerCenter::instance()->addExchange(exchange_ptr);
//                     if (err_code != Err_Succeed)
//                     {
//                         assert(0);
//                         return;
//                     }
//                 }
// 
//                 AllTrade::DisplayPropType   display_prop;
//                 DisplayPropTypeType         display_prop_type;
//                 if (data[SHORTNM].toString().indexOf("*ST") == 0)
//                 {
//                     strncpy_s(display_prop, "*ST", sizeof(display_prop) - 1);
//                     display_prop_type = DisplayPropTypeType::DPTT_StarST;
//                 }
//                 else if (data[SHORTNM].toString().indexOf("SST") == 0)
//                 {
//                     strncpy_s(display_prop, "SST", sizeof(display_prop) - 1);
//                     display_prop_type = DisplayPropTypeType::DPTT_SST;
//                 }
//                 else if (data[SHORTNM].toString().indexOf("ST") == 0)
//                 {
//                     strncpy_s(display_prop, "ST", sizeof(display_prop) - 1);
//                     display_prop_type = DisplayPropTypeType::DPTT_ST;
//                 }
//                 else if (data[SHORTNM].toString().indexOf("S*ST") == 0)
//                 {
//                     strncpy_s(display_prop, "S*ST", sizeof(display_prop) - 1);
//                     display_prop_type = DisplayPropTypeType::DPTT_SStarST;
//                 }
//                 else if (data[SHORTNM].toString().indexOf("S") == 0)
//                 {
//                     strncpy_s(display_prop, "S", sizeof(display_prop) - 1);
//                     display_prop_type = DisplayPropTypeType::DPTT_S;
//                 }
//                 else
//                     display_prop_type = DisplayPropTypeType::DPTT_Normal;
// 
//                 SStockContractPtr contract_ptr = std::make_shared<SStockContract>();
//                 strncpy_s(contract_ptr->contract_id_, UtilityFun::createGUID().c_str(), sizeof(contract_ptr->contract_id_) - 1);
// //                 strncpy_s(contract_ptr->contract_py_code_, json.contract_py_code_, sizeof(contract_ptr->contract_py_code_) - 1);
//                 strncpy_s(contract_ptr->contract_code_, contract_code, sizeof(contract_ptr->contract_code_) - 1);
//                 strncpy_s(contract_ptr->contract_name_, contract_name, sizeof(contract_ptr->contract_name_) - 1);
// //                 strncpy_s(contract_ptr->open_datetime_, json.open_datetime_, sizeof(contract_ptr->open_datetime_) - 1);
//                 strncpy_s(contract_ptr->delivery_datetime_, "0000-00-00 00:00:00", sizeof(contract_ptr->delivery_datetime_) - 1);
//                 strncpy_s(contract_ptr->trade_datetime_, "0000-00-00 00:00:00", sizeof(contract_ptr->trade_datetime_) - 1);
//                 contract_ptr->stock_status_ = StockStatusType::STOCKSTATUS_L;
//                 contract_ptr->commodity_type_ = CommodityTypeType::COMMODITY_TYPE_STOCK;
//                 contract_ptr->stock_area_ = StockAreaType::STOCKAREA_TYPE_A;
//                 strncpy_s(contract_ptr->exchange_id_, exchange_ptr->exchange_id_, sizeof(contract_ptr->exchange_id_) - 1);
//                 contract_ptr->min_price_change_ = 0.001;
//                 contract_ptr->contract_multiplier_ = 100;
//                 strncpy_s(contract_ptr->display_prop_, display_prop, sizeof(contract_ptr->display_prop_) - 1);
//                 contract_ptr->display_prop_type_ = display_prop_type;
// //                 contract_ptr->stock_plate_area_ = json.listSectorCD_;
// //                 contract_ptr->total_shares_ = json.totalShares_;
//                 contract_ptr_new = contract_ptr;
// 
//                 AllTrade::ErrorCodeType err_code = IManagerCenter::instance()->addContract(contract_ptr);
//                 assert(err_code == Err_Succeed);
//             }
//             else
//             {
//                 SStockContractPtr contract_ptr = std::dynamic_pointer_cast<SStockContract>(contract_ptr_new);
// //                 strncpy_s(contract_ptr->contract_py_code_, json.contract_py_code_, sizeof(contract_ptr->contract_py_code_) - 1);
//                 strncpy_s(contract_ptr->contract_name_, contract_name, sizeof(contract_ptr->contract_name_) - 1);
// //                 strncpy_s(contract_ptr->open_datetime_, json.open_datetime_, sizeof(contract_ptr->open_datetime_) - 1);
// //                 contract_ptr->stock_status_ = json.stock_status_;
// //                 contract_ptr->stock_plate_area_ = json.listSectorCD_;
// //                 strncpy_s(contract_ptr->display_prop_, json.display_prop_, sizeof(contract_ptr->display_prop_) - 1);
// //                 contract_ptr->display_prop_type_ = json.display_prop_type_;
// //                 contract_ptr->total_shares_ = json.totalShares_;
//                 AllTrade::ErrorCodeType err_code = IManagerCenter::instance()->addContract(contract_ptr);
//                 assert(err_code == Err_Succeed);
//             }
//         }
// 
//     }
//     catch (...)
//     {
// 
//     }
// 
// }
