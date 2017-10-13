#include <assert.h>
#include "SyncOrder.h"
#include "define/struct_declare.h"

#include "include/StockApiManager/StockApiManager.h"
#include "include/ManagerCenter/ManagerCenter.h"
#include "../Handler/orderhandler.h"
#include "../Handler/orderlistmanager.h"
#include "define/struct_extern.h"
#include "../Handler/quotehandler.h"
#include "../Handler/quotelistmanager.h"
#include "TcpListen/TcpCallBack.h"

#include "C:/ng_tools/ng_header_for_log4cxx/ng_header_for_log4cxx.hpp"
#include "C:/ng_tools/ng_header_for_log4cxx/ng_header_for_log4cxx_log_var.hpp"
NG_LOGGER(logger, "SyncOrder");

using namespace AllTrade::NPMgrCenter;

namespace AllTrade{
    namespace NPTradeCenter {

        SyncOrder::SyncOrder()
        {
            m_tcp_cbk = new TcpCallBack();
            int port = GetPrivateProfileIntA("Sync", "port", 2550, "./config.hxc");
            if (StockApiManager::InitApiServerMgr(port) != 0)
            {
                LOG4CXX_ERROR(logger, "初始化实盘交易监听端口失败!"LOG_NOVAR(port));
            } 
        }

        SyncOrder::~SyncOrder()
        {
            if (m_tcp_cbk)
            {
                delete m_tcp_cbk;
                m_tcp_cbk = nullptr;
            }
        }

        void SyncOrder::createOrder(const OrderHrPtr& order_hr_ptr)
        {
            auto quote_hr_ptr = QuoteListManager::instance()->getQuoteHrByID(order_hr_ptr->getContractID().c_str());
            assert(quote_hr_ptr);

            if (order_hr_ptr->getOrderType() == OrderTypeType::ORDER_TYPE_MARKET)
            {
                if (order_hr_ptr->getDirect() == DirectType::DIRECT_BUY)
                    order_hr_ptr->setOrderPrice(quote_hr_ptr->getRisePrice());
                else
                    order_hr_ptr->setOrderPrice(quote_hr_ptr->getFallPrice());

                order_hr_ptr->setOrderType(OrderTypeType::ORDER_TYPE_LIMIT);
            }

            LOG4CXX_DEBUG(logger, "创建实盘交易委托,ID" LOG_NOVAR(order_hr_ptr->getOrderID())
                ",合约" LOG_NOVAR(order_hr_ptr->getContractID())
                ",用户" LOG_NOVAR(order_hr_ptr->getUserID())
                ",方向" LOG_NOVAR((int)order_hr_ptr->getDirect())
                ",手数" LOG_NOVAR((int)order_hr_ptr->getOrderVol()));

            auto user = IManagerCenter::instance()->getAccountByID(order_hr_ptr->getUserID().c_str());
            assert(user);

            TradeAccountPtr trade_user = std::dynamic_pointer_cast<TradeAccount>(user);
            assert(trade_user);

            auto funder_user = IManagerCenter::instance()->getAccountByID(trade_user->fund_user_id_);
            assert(funder_user);

            StockOrderPtr stock_order_ptr = std::dynamic_pointer_cast<StockOrderInfo>(order_hr_ptr->getOrderInfoCopy());
            assert(stock_order_ptr);

            auto con_ptr = IManagerCenter::instance()->getStockContractByID(stock_order_ptr->stock_area_, stock_order_ptr->contract_id_);
            assert(con_ptr);

            bool isXSHG(quote_hr_ptr->getExchangeCode() == "XSHG");
            
            if (m_tcp_cbk)
                m_tcp_cbk->ReqOrderInsert(funder_user->login_name_, con_ptr->contract_code_, order_hr_ptr, isXSHG);
        }

        void SyncOrder::cancelOrder(const OrderHrPtr& order_hr_ptr)
        {
            auto user = IManagerCenter::instance()->getAccountByID(order_hr_ptr->getUserID().c_str());
            assert(user);

            TradeAccountPtr trade_user = std::dynamic_pointer_cast<TradeAccount>(user);
            assert(trade_user);

            auto funder_user = IManagerCenter::instance()->getAccountByID(trade_user->fund_user_id_);
            assert(funder_user);

            StockOrderPtr stock_order_ptr = std::dynamic_pointer_cast<StockOrderInfo>(order_hr_ptr->getOrderInfoCopy());
            assert(stock_order_ptr);

            auto con_ptr = IManagerCenter::instance()->getStockContractByID(stock_order_ptr->stock_area_, stock_order_ptr->contract_id_);
            assert(con_ptr);

            bool isXSHG(strcmp(IManagerCenter::instance()->getExchangeByID(con_ptr->commodity_type_, con_ptr->exchange_id_)->exchange_code_, "XSHG") == 0);

            if (m_tcp_cbk)
                m_tcp_cbk->ReqCancelOrder(funder_user->login_name_, con_ptr->contract_code_, order_hr_ptr, isXSHG);
        }

    }
}