#include <assert.h>
#include <tbb/tbb.h>
#include <tbb/blocked_range.h>
#include <tbb/parallel_for.h>
#include "SimulateOrder.h"
#include "define/struct_extern.h"
#include "define/protocol_error.h"
#include "utility/scopeguard.h"
#include "../Handler/orderhandler.h"
#include "../Handler/quotehandler.h"
#include "../Handler/quotelistmanager.h"
#include "../Handler/tradehandler.h"
#include "../Handler/orderlistmanager.h"
#include "../Application/chinafutureservermgr.h"
#include "../Application/foreignfutureservermgr.h"
#include "../Application/stockservermgr.h"
#include "include/OperationManager/OperationManager.h"
#include "../Application/taskmsg_order_mgr.h"

#include "C:/ng_tools/ng_header_for_log4cxx/ng_header_for_log4cxx.hpp"
#include "C:/ng_tools/ng_header_for_log4cxx/ng_header_for_log4cxx_log_var.hpp"
NG_LOGGER(logger, "SimulateOrder");

using namespace AllTrade::NPMgrCenter;
using namespace OperationManager;

namespace AllTrade{
    namespace NPTradeCenter {

        SimulateOrder::SimulateOrder()
            : m_thread_call(this, &SimulateOrder::thread_quote_calculate)
        {
            QuoteListManager::instance()->setQuoteEvent(&m_quote_event);
            m_thread_call.set_priority(THREAD_PRIORITY_ABOVE_NORMAL);// ��׼+1
            m_thread_call.start(this);
        }

        SimulateOrder::~SimulateOrder()
        {
            QuoteListManager::instance()->setQuoteEvent(nullptr);
            try {
                // �رռ����߳�
                if (m_thread_call.is_running()) {
                    m_close_event.set();
                    m_thread_call.stop();
                }
            }
            catch (...) {}
        }

        void SimulateOrder::createOrder(const OrderHrPtr& order_hr_ptr)
        {
            LOG4CXX_DEBUG(logger, "������Ͻ���ί��,ID" LOG_NOVAR(order_hr_ptr->getOrderID())
                ",��Լ" LOG_NOVAR(order_hr_ptr->getContractID())
                ",�û�" LOG_NOVAR(order_hr_ptr->getUserID())
                ",����" LOG_NOVAR((int)order_hr_ptr->getDirect())
                ",����" LOG_NOVAR((int)order_hr_ptr->getOrderVol()));

            order_hr_ptr->setOrderState(OrderStateType::ORDER_STATE_QUEUED);

            TaskMsgOrderManager::instance()->handleOrderInsertCbk(order_hr_ptr->getOrderInfoCopy(), order_hr_ptr->getUserID().c_str(), order_hr_ptr->getOpUserLoginInfo());

            matchOrder(order_hr_ptr);
        }

        long SimulateOrder::thread_quote_calculate(void* param)
        {
            try
            {
                const int handlerCnt = 2;
                CommonTools::handler handlerTable[] = { m_quote_event, m_close_event };

                while (true)
                {
                    int index = CommonTools::wait_for_multiple_events(handlerTable, handlerCnt);
                    if (index == -1)
                    {
                        // �쳣�ȴ��¼�
                        break;
                    }
                    else if (handlerTable[index] == m_close_event)// �ر��¼�
                    {
                        break;
                    }

                    calculateAll();
                }
                return 0;
            }
            catch (...)
            {
                // �����߳��쳣����
                return -1;
            }
        }

        void SimulateOrder::calculateAll()
        {
            std::set<PContractIDType> change_quotes = QuoteListManager::instance()->getChangeQuote();

            // ���ݺ�ԼID���ȡ�Ŷ�ί��
            std::vector<OrderHrPtr> order_hr_ptrs;
            for(auto contract_id : change_quotes)
            {
                std::vector<OrderHrPtr> tmp = OrderListManager::instance()->getOrderHrListByContractID(contract_id.c_str());
                order_hr_ptrs.insert(order_hr_ptrs.end(), tmp.begin(), tmp.end());
            }

            // ���۳ɽ�,����tbb����
            typedef std::vector<OrderHrPtr>::iterator OrderInfoHrVecIter;
            tbb::parallel_for(tbb::blocked_range<OrderInfoHrVecIter>(order_hr_ptrs.begin(), order_hr_ptrs.end())
                , [&](const tbb::blocked_range<OrderInfoHrVecIter>& range){
                for (auto i = range.begin(); i != range.end(); i++)
                {
                    matchOrder(*i);
                }
            });
        }

        void SimulateOrder::matchOrder(const OrderHrPtr& order_hr_ptr, QuoteHrPtr quote_ptr)
        {
            assert(order_hr_ptr);
            if (order_hr_ptr->getOrderTradeMode() != OrderTradeModeType::ORDERTRADE_MODE_SIMULATE)
                return;

            if (!quote_ptr)
                quote_ptr = QuoteListManager::instance()->getQuoteHrByID(order_hr_ptr->getContractID().c_str());

            if (!quote_ptr)
            {
                LOG4CXX_ERROR(logger, "δ�ҵ���Լ��Ӧ������"LOG_NOVAR(quote_ptr->getContractName()));

                // δ�ҵ���Ӧ����
                assert(0);
                return;
            }

            // !!!!!!���ڸ�Ϊ���������������仯
            if (order_hr_ptr->simulateTrade(quote_ptr))
                matchOrder(order_hr_ptr, quote_ptr);
        }

        void SimulateOrder::cancelOrder(const OrderHrPtr& order_hr_ptr)
        {
            order_hr_ptr->simulateCancelOrder();
        }

    }
}