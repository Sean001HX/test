#include "C:/ng_tools/ng_header_for_log4cxx/ng_header_for_log4cxx.hpp"
#include "C:/ng_tools/ng_header_for_log4cxx/ng_header_for_log4cxx_log_var.hpp"
#include "CatchMiniDump.h"
#include "Network/tcpserver.h"
#include <QtWidgets/QApplication>
#include <QMessageBox>
#include "include/OperationManager/OperationManager.h"
#include "include/ManagerCenter/ManagerCenter.h"
#include "include/TradeCenter/TradeCenter.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    InitMinDump();
    NG_LOGGER_INIT(logger, "hx", "AllTradeService.xml");
    LOG4CXX_INFO(logger, "AllTradeService start");

    if (!OperationManager::COperationManager::instance()->initialize())
    {
        QMessageBox::warning(nullptr, QStringLiteral("警告"), QStringLiteral("数据库初始化失败!"));
        LOG4CXX_ERROR(logger, "数据库初始化失败");
        LOG4CXX_INFO(logger, "AllTradeService end");
        return -1;
    }
    TCPServer w;
    AllTrade::NPMgrCenter::IManagerCenter::instance();
    AllTrade::NPTradeCenter::ITradeCenter::instance();
    w.show();

    int tmp = a.exec();
    w.stop();
    AllTrade::NPTradeCenter::ITradeCenter::unInstance();
    AllTrade::NPMgrCenter::IManagerCenter::unInstance();
    OperationManager::COperationManager::unInstance();
    LOG4CXX_INFO(logger, "AllTradeService end");
    return tmp;
}
