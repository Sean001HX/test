#include <assert.h>
#include "TcpCallBack.h"
#include "define/struct_extern.h"
#include "include/ManagerCenter/ManagerCenter.h"
#include "../../Handler/orderhandler.h"
#include "../../Handler/orderlistmanager.h"
#include "../../Application/taskmsg_order_mgr.h"
#include "../../Application/taskmsg_declare.h"
#include "../../Application/taskmsg.h"

using namespace AllTrade::NPMgrCenter;

namespace AllTrade {
    namespace NPTradeCenter {

        TcpCallBack::TcpCallBack()
            : m_api_interface(StockApiManager::GetApiServerMgr())
        {
            m_api_interface->RegisterCallBack(this);
        }

        TcpCallBack::~TcpCallBack()
        {

        }

        bool TcpCallBack::ReqOrderInsert(const char *fundreal_name, const ContractCodeType& cont_code, const OrderHrPtr& order_hr_ptr, bool isXSHG)
        {
            OrderInfoPtr order_ptr = order_hr_ptr->getOrderInfoCopy();
            int rslt = m_api_interface->ReqOrderInsert(fundreal_name, cont_code, std::dynamic_pointer_cast<StockOrderInfo>(order_ptr), isXSHG);

            if (rslt != 0)
            {
                order_ptr->order_state_ = OrderStateType::ORDER_STATE_FAIL;
                UserOperator::UserTaskCommMsgPtr trade_msg_ptr = UserOperator::UserTaskCommMsg::createOrderMsg(order_hr_ptr);
                trade_msg_ptr->setErrorCode(Err_Trade_RejectByUpper);
                TaskMsgOrderManager::instance()->sendMsgToFront(trade_msg_ptr);

                TaskMsgOrderManager::instance()->handleOrderChangeCbk(order_ptr, order_hr_ptr->getUserID().c_str());
            }

            return rslt == 0;
        }

        bool TcpCallBack::ReqCancelOrder(const char *fundreal_name, const ContractCodeType& cont_code, const OrderHrPtr& order_hr_ptr, bool isXSHG)
        {
            OrderInfoPtr order_ptr = order_hr_ptr->getOrderInfoCopy();
            int rslt = m_api_interface->ReqCancelOrder(fundreal_name, cont_code, std::dynamic_pointer_cast<StockOrderInfo>(order_ptr), isXSHG);

            if (rslt != 0)
            {
                UserOperator::UserTaskCommMsgPtr trade_msg_ptr = UserOperator::UserTaskCommMsg::createCancelOrderMsg(order_hr_ptr);
                trade_msg_ptr->setErrorCode(Err_Trade_RejectByUpper);
                TaskMsgOrderManager::instance()->sendMsgToFront(trade_msg_ptr);
            }

            return rslt == 0;
        }

        void TcpCallBack::OnRealAccountTradeLogin(const char *real_name, bool ok)
        {
        }

        void TcpCallBack::OnOrderInsert(const char *real_name, const ContractCodeType contract_code, const StockOrderPtr& order_ptr)
        {
            auto con_ptr = IManagerCenter::instance()->getStockContractByCode(StockAreaType::STOCKAREA_TYPE_A, contract_code);
            assert(con_ptr);
            
            auto order_hr_ptr = OrderListManager::instance()->getOrderHrPtrByContractIDAndRef(con_ptr->contract_id_, order_ptr->order_ref_);
            if (!order_hr_ptr)
            {
                assert(0);
                return;
            }

            order_hr_ptr->setSystemOrderID(order_ptr->system_order_id_);
            StockOrderPtr tmp_ptr = std::dynamic_pointer_cast<StockOrderInfo>(order_hr_ptr->getOrderInfoCopy());
            tmp_ptr->order_state_ = order_ptr->order_state_;

            TransactionOperator::TransTaskCommMsgPtr trade_msg_ptr = TransactionOperator::TransTaskCommMsg::createOrderMsg(tmp_ptr, order_hr_ptr->getUserID().c_str());
            TaskMsgOrderManager::instance()->handleOrderInsertCbk(tmp_ptr, order_hr_ptr->getUserID().c_str());
        }

        void TcpCallBack::OnOrderCancel(const char *real_name, const ContractCodeType contract_code, const OrderInfoPtr& order_ptr)
        {
            auto con_ptr = IManagerCenter::instance()->getStockContractByCode(StockAreaType::STOCKAREA_TYPE_A, contract_code);
            assert(con_ptr);

            std::vector<OrderHrPtr> order_hr_ptrs = OrderListManager::instance()->getOrderHrListByContractID(con_ptr->contract_id_);
            for (OrderHrPtr& order_hr_ptr : order_hr_ptrs)
            {
                if (strcmp(order_hr_ptr->getSystemOrderID().c_str(), order_ptr->system_order_id_) == 0)
                {
                    StockOrderPtr tmp_ptr = std::dynamic_pointer_cast<StockOrderInfo>(order_hr_ptr->getOrderInfoCopy());
                    tmp_ptr->order_state_ = order_ptr->order_state_;
                    TaskMsgOrderManager::instance()->handleCancelOrderCbk(tmp_ptr, order_hr_ptr->getUserID().c_str());
                    return;
                }
            }

        }

        void TcpCallBack::OnOrderStatusUpdate(const char *real_name, const ContractCodeType contract_code, const StockOrderPtr& order_ptr)
        {
            auto con_ptr = IManagerCenter::instance()->getStockContractByCode(StockAreaType::STOCKAREA_TYPE_A, contract_code);
            assert(con_ptr);

            auto order_hr_ptr = OrderListManager::instance()->getOrderHrPtrByContractIDAndRef(con_ptr->contract_id_, order_ptr->order_ref_);
            if (!order_hr_ptr)
            {
                assert(0);
                return;
            }
            order_hr_ptr->setSystemOrderID(order_ptr->system_order_id_);

            StockOrderPtr tmp_ptr = std::dynamic_pointer_cast<StockOrderInfo>(order_hr_ptr->getOrderInfoCopy());
            tmp_ptr->order_state_ = order_ptr->order_state_;

            TaskMsgOrderManager::instance()->handleOrderChangeCbk(tmp_ptr, order_hr_ptr->getUserID().c_str());
        }

        void TcpCallBack::OnTradeInfo(const char *real_name, const ContractCodeType contract_code, const StockTradePtr& tradeInfo)
        {
            auto con_ptr = IManagerCenter::instance()->getStockContractByCode(StockAreaType::STOCKAREA_TYPE_A, contract_code);
            assert(con_ptr);

            StockOrderHrPtr tmp_hr(nullptr);
            auto order_hr_ptrs = OrderListManager::instance()->getOrderHrListByContractID(con_ptr->contract_id_, tradeInfo->direct_type_);
            for (auto& order_hr_ptr : order_hr_ptrs)
            {
                if (strcmp(order_hr_ptr->getContractID().c_str(), con_ptr->contract_id_) == 0
                    && strcmp(order_hr_ptr->getSystemID().c_str(), tradeInfo->system_order_id_) == 0)
                {
                    tmp_hr = std::dynamic_pointer_cast<StockOrderHandler>(order_hr_ptr);
                    break;
                }
            }

            if (!tmp_hr)
            {
                assert(0);
                return;
            }

            tmp_hr->realTrade(tradeInfo);
        }

    }
}