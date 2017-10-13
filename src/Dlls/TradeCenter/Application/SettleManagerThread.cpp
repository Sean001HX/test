#include <boost\format.hpp>
#include <boost\algorithm\string.hpp>
#include "define/struct_extern.h"
#include "define/protocol_error.h"
#include "SettleManagerThread.h"
#include "GlobalDataManager.h"
#include "../Handler/positionlistmanager.h"
#include "../Handler/positionhandler.h"
#include "../Handler/orderlistmanager.h"
#include "../Handler/orderhandler.h"
#include "include/OperationManager/OperationManager.h"
#include "include/ManagerCenter/ManagerCenter.h"
#include "utility/utility_fun.h"
#include "../SimulateTrade/SimulateOrder.h"
#include "ServerMgrBase.h"
#include "taskmsg_order_mgr.h"

#include "C:/ng_tools/ng_header_for_log4cxx/ng_header_for_log4cxx.hpp"
#include "C:/ng_tools/ng_header_for_log4cxx/ng_header_for_log4cxx_log_var.hpp"
NG_LOGGER(logger, "SettleManagerThread");

using namespace OperationManager;
using namespace AllTrade::NPMgrCenter;

namespace AllTrade {
    namespace NPTradeCenter {

        SettleManagerThread::SettleManagerThread()
            : m_servicePool()
            , m_timerQueue(m_servicePool)
        {
            m_servicePool.start(1);

            GetPrivateProfileStringA("Trade", "settleTime", "", m_settle_time, sizeof(m_settle_time), "./config.hxc");
            settle();
        }

        SettleManagerThread::~SettleManagerThread()
        {
            m_timerQueue.clear();
        }

        void SettleManagerThread::unInitialize()
        {
            m_timerQueue.clear();
            m_servicePool.stop();
        }

        void SettleManagerThread::start()
        {
            m_timerQueue.insert(m_timerQueue.makeTimePoint(getNextSettleTime(m_settle_time))
                                , boost::bind(&SettleManagerThread::settle_thread, shared_from_this(), _1));
        }

        void SettleManagerThread::settle()
        {
            std::string settle_datetime = UtilityFun::getCurrentDate() + " ";
            settle_datetime += m_settle_time;
            if (!COperationManager::instance()->canSettle(settle_datetime.c_str(), UtilityFun::getCurrentDateTime().c_str()))
            {
                LOG4CXX_TRACE(logger, "当前时间无需结算!"LOG_NOVAR(settle_datetime)LOG_NOVAR(UtilityFun::getCurrentDateTime()));
                return;
            }

            auto users = IManagerCenter::instance()->getAllTrades(IManagerCenter::instance()->getRootAccount()->user_id_);
            for (auto& user_item : users)
            {
                IManagerCenter::instance()->moneyChange(user_item->user_id_, MC_Money_Settle, 0, "系统结算");
                for (auto& posi_item : PositionListManager::instance()->getPositionHrsByUserID(user_item->user_id_))
                    posi_item->settlePosition();

                std::vector<OrderHrPtr> orders = OrderListManager::instance()->getOrderHrListByUserID(user_item->user_id_);
                for (auto& order_item : orders)
                {
                    if (order_item->getOrderMode() != OrderModeType::ORDER_MODE_GFD)
                        continue;

                    if (order_item->canCancelOrder() != Err_Succeed)
                        continue;

                    TaskMsgOrderManager::instance()->handleCancelOrder(order_item->getUserID().c_str(), order_item->getOrderStream().c_str(), true, true);
                }
            }

            GlobalDataManager::instance()->settle();

            COperationManager::instance()->updateSettle(UtilityFun::getCurrentDateTime().c_str());

        }

        void SettleManagerThread::settle_thread(bool is_erased)
        {
            if (!is_erased)
                return;

            settle();

            m_timerQueue.insert(m_timerQueue.makeTimePoint(getNextSettleTime(m_settle_time))
                , boost::bind(&SettleManagerThread::settle_thread, shared_from_this(), _1));
        }

        std::tm SettleManagerThread::getNextSettleTime(TimeType settle_time)
        {
            std::string tmp = settle_time;

            std::vector<std::string>	vecStr;
            boost::split(vecStr, settle_time, boost::is_any_of(":"));
            if (vecStr.empty() || vecStr.size() != 3)
            {
                LOG4CXX_FATAL(logger, "无法设置结算时间"LOG_NOVAR(settle_time));
                return std::tm();
            }

            std::tm tmp_tm = { 0 };
            std::time_t t = std::time(nullptr);
            localtime_s(&tmp_tm, &t);

            if (tmp_tm.tm_hour > std::stoi(vecStr[0])
                || (tmp_tm.tm_hour == std::stoi(vecStr[0]) && tmp_tm.tm_min > std::stoi(vecStr[1]))
                || (tmp_tm.tm_hour == std::stoi(vecStr[0]) && tmp_tm.tm_min == std::stoi(vecStr[1]) && tmp_tm.tm_sec >= std::stoi(vecStr[2]) - 30))
            {
                std::string nextday = UtilityFun::getAddDate(1);
                std::vector<std::string>	vecDate;
                boost::split(vecDate, nextday, boost::is_any_of("-"));
                if (vecDate.empty() || vecDate.size() != 3)
                {
                    LOG4CXX_FATAL(logger, "无法获取明天时间"LOG_NOVAR(nextday));
                    return std::tm();
                }
                tmp_tm.tm_year = std::stoi(vecDate[0]) - 1900;
                tmp_tm.tm_mon = std::stoi(vecDate[1]) - 1;
                tmp_tm.tm_mday = std::stoi(vecDate[2]);
            }

            tmp_tm.tm_hour = std::stoi(vecStr[0]);
            tmp_tm.tm_min = std::stoi(vecStr[1]);
            tmp_tm.tm_sec = std::stoi(vecStr[2]);

            return tmp_tm;
        }

    }
}