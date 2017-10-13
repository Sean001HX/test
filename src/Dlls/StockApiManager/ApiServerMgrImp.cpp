#include "ApiServerMgrImp.h"
#include "include/NetGateway/net_gateway.h"
#include <stdio.h>
#include "define/stock_api/tcas_def.h"
#include "define/stock_api/StockDllStruct.h"
#include "define/struct_extern.h"

#include <assert.h>
#include "c:/ng_tools/ng_header_for_log4cxx/ng_header_for_log4cxx.hpp"
#include "C:/ng_tools/ng_header_for_log4cxx/ng_header_for_log4cxx_log_var.hpp"

NG_LOGGER(logger, "ApiServerMgrImp");

namespace AllTrade {
    namespace NPTradeCenter {

        namespace StockApiManager {

            ApiServerMgrImp * ApiServerMgrImp::Instance()
            {
                static ApiServerMgrImp _inst;
                return &_inst;
            }

            ApiServerMgrImp::~ApiServerMgrImp()
            {

            }

            ApiServerMgrImp::ApiServerMgrImp() : callback_(0), net_handler_(0)
            {
                NetGateway::Server::SetNetCallback(this);
                net_handler_ = NetGateway::Server::GetNetHandler();
            }

            void ApiServerMgrImp::RegisterCallBack(StockApiServerCallBack *callback)
            {
                callback_ = callback;
            }

            int ApiServerMgrImp::ReqOrderInsert(const char *real_name, const ContractCodeType& cont_code, const StockOrderPtr& orderInfo, bool isXSHG)
            {
                assert(orderInfo);

                if (!net_handler_ || !orderInfo)
                    return -1;

                BaseConnectionInfo item;
                mutex_verified_connections_.Lock();
                auto it = map_verified_connections_by_name.find(real_name);
                if (it != map_verified_connections_by_name.end())
                    item = *(it->second);
                mutex_verified_connections_.Unlock();

                if (!item.net_client_info_.net_comm_handle_ || !item.trade_login_flag_)
                {
                    return -1;
                }

                StockDLL::OrderInfo sendBuf;
                sendBuf.orderType = getDirectTypeToDll(orderInfo->direct_type_);
                sendBuf.priceType = getOrderTypeToDll(orderInfo->order_type_);
                sendBuf.price = orderInfo->order_price_;
                sendBuf.quantity = orderInfo->order_vol_;

                strncpy_s(sendBuf.stockCode, cont_code, sizeof(sendBuf.stockCode) - 1);
                strncpy_s(sendBuf.orderRef, orderInfo->order_ref_, sizeof(sendBuf.orderRef) - 1);

                sendBuf.exchange = isXSHG ? 1 : 0;

                int sendError = net_handler_->Send(item.net_client_info_.connectionID, item.net_client_info_.net_comm_handle_, NET_AS_PLACE_ORDER, &sendBuf, sizeof(sendBuf));

                LOG4CXX_INFO(logger, "ReqOrderInsert()" LOG_VAR(sendError) LOG_VAR(orderInfo->order_stream_) LOG_VAR(orderInfo->contract_id_) LOG_VAR(orderInfo->order_vol_)
                    LOG_VAR((int)orderInfo->direct_type_) LOG_VAR(orderInfo->order_price_));

                if (sendError)
                    return -1;

                return 0;
            }

            int ApiServerMgrImp::ReqCancelOrder(const char *real_name, const ContractCodeType& cont_code, const StockOrderPtr& orderInfo, bool isXSHG)
            {
                if (!net_handler_)
                    return -1;

                BaseConnectionInfo item;
                mutex_verified_connections_.Lock();
                auto it = map_verified_connections_by_name.find(real_name);
                if (it != map_verified_connections_by_name.end())
                    item = *(it->second);
                mutex_verified_connections_.Unlock();

                if (!item.net_client_info_.net_comm_handle_ || !item.trade_login_flag_)
                {
                    return -1;
                }

                StockDLL::CancelOrderInfo sendBuf;
                strncpy_s(sendBuf.stockCode, cont_code, sizeof(sendBuf.stockCode) - 1);
                if (isXSHG)
                    strncpy_s(sendBuf.exchangeID, "1", sizeof(sendBuf.exchangeID) - 1);
                else
                    strncpy_s(sendBuf.exchangeID, "0", sizeof(sendBuf.exchangeID) - 1);

                strncpy_s(sendBuf.orderNo, orderInfo->system_order_id_, sizeof(sendBuf.orderNo) - 1);

                int sendError = net_handler_->Send(item.net_client_info_.connectionID, item.net_client_info_.net_comm_handle_, NET_AS_CANCEL_ORDER, &sendBuf, sizeof(sendBuf));

                LOG4CXX_INFO(logger, "ReqCancelOrder()" LOG_VAR(sendError) LOG_VAR(sendBuf.exchangeID) LOG_VAR(sendBuf.orderNo));

                if (sendError)
                    return -1;

                return 0;
            }

            void ApiServerMgrImp::OnNewConnection(int connectionID, NetGateway::Server::NetCommHandle *netObject)
            {
                CNetClientInfo item = { 0 };
                item.connectionID = connectionID;
                item.net_comm_handle_ = netObject;

                mutex_unlogin_connections_.Lock();
                unlogin_connections_[connectionID] = item;
                mutex_unlogin_connections_.Unlock();
            }

            void ApiServerMgrImp::OnDisconnect(int connectionID, NetGateway::Server::NetCommHandle *netObject)
            {
                mutex_unlogin_connections_.Lock();
                {
                    auto it = unlogin_connections_.find(connectionID);
                    if (it != unlogin_connections_.end())
                    {
                        LOG4CXX_INFO(logger, "OnDisconnect()" LOG_VAR(connectionID) LOG_VAR(netObject));
                        unlogin_connections_.erase(it);
                    }
                }
                mutex_unlogin_connections_.Unlock();

                std::string real_account;

                mutex_verified_connections_.Lock();
                ///////////////////////////////////////////////
                auto it_co = map_verified_connections_by_connectionID.find(connectionID);
                if (it_co != map_verified_connections_by_connectionID.end())
                {
                    map_verified_connections_by_connectionID.erase(it_co);

                    auto it = map_verified_connections_by_name.begin(), it_end = map_verified_connections_by_name.end();
                    for (; it != it_end; ++it)
                    {
                        if (it->second->net_client_info_.connectionID == connectionID)
                        {
                            if (it->second->net_client_info_.net_comm_handle_ != netObject)
                            {
                                LOG4CXX_WARN(logger, "OnDisconnect()" LOG_VAR(connectionID) LOG_VAR(netObject) LOG_VAR(it->second->net_client_info_.connectionID) LOG_VAR(it->second->net_client_info_.net_comm_handle_));
                            }

                            real_account = it->second->login_name_;

                            map_verified_connections_by_name.erase(it);

                            mutex_verified_connections_.Unlock();
                            ////////////////////////////////////////////////
                            if (callback_)
                            {
                                callback_->OnRealAccountTradeLogin(real_account.c_str(), false);
                            }

                            break;
                        }
                    }
                }
                ////////////////////////////////////////////////////
                mutex_verified_connections_.Unlock();

                LOG4CXX_INFO(logger, "OnDisconnect()" LOG_VAR(real_account) LOG_VAR(netObject) LOG_VAR(connectionID));
            }

            void ApiServerMgrImp::OnRecv(int connectionID, NetGateway::Server::NetCommHandle *netObject, short netCommand, char *buf, int bufLen)
            {
                switch (netCommand)
                {
                case NET_AS_LOGIN:
                    return HandleLogin(connectionID, netObject, netCommand, buf, bufLen);
                    break;
                case NET_AS_NET_STATUS:
                    return HandleRealAccountNetStatus(connectionID, netObject, netCommand, buf, bufLen);
                    break;
                case NET_AS_PLACE_ORDER_RSP_STATUS:
                    return HandlePlaceOrderRsp(connectionID, netObject, netCommand, buf, bufLen);
                    break;
                case NET_AS_PLACE_ORDER_RSP_ORDER:
                    return HandleOrderStatusUpdate(connectionID, netObject, netCommand, buf, bufLen);
                    break;
                case NET_AS_PLACE_ORDER_RSP_TRADE:
                    return HandleTradeInfo(connectionID, netObject, netCommand, buf, bufLen);
                    break;
                case NET_AS_CANCEL_ORDER:
                    return HandleCancelOrder(connectionID, netObject, netCommand, buf, bufLen);
                    break;
                default:
                    assert(0);
                    break;
                }
            }

            void ApiServerMgrImp::OnSend(int connectionID, NetGateway::Server::NetCommHandle *netObject)
            {

            }

            void ApiServerMgrImp::HandleLogin(int connectionID, NetGateway::Server::NetCommHandle * netObject, short netCommand, char * buf, int bufLen)
            {
                CNetClientInfo netInfo;
                netInfo.connectionID = connectionID;
                netInfo.net_comm_handle_ = netObject;

                std::shared_ptr<CVerifiedConnectionInfo> item(new (std::nothrow) CVerifiedConnectionInfo);
                if (!item)
                    return;

                item->net_client_info_.connectionID = connectionID;
                item->net_client_info_.net_comm_handle_ = netObject;
                item->trade_login_flag_ = true;

                StockDLL::LoginToTc* pUserLogin = (StockDLL::LoginToTc *)buf;
                pUserLogin->loginName_[sizeof(pUserLogin->loginName_) - 1] = 0;
                _snprintf_s(item->login_name_, sizeof(item->login_name_) - 1, "%s", pUserLogin->loginName_);

                mutex_unlogin_connections_.Lock();
                auto it = unlogin_connections_.find(connectionID);
                if (it != unlogin_connections_.end())
                {
                    unlogin_connections_.erase(it);
                }
                mutex_unlogin_connections_.Unlock();


                mutex_verified_connections_.Lock();

                auto it_veryfy = map_verified_connections_by_name.find(pUserLogin->loginName_);
                if (it_veryfy != map_verified_connections_by_name.end())
                {
                    LOG4CXX_WARN(logger, "HandleLogin()" LOG_VAR(pUserLogin->loginName_) LOG_VAR(item->net_client_info_.connectionID) LOG_VAR(item->net_client_info_.net_comm_handle_) LOG_VAR(it_veryfy->second->net_client_info_.connectionID)
                        LOG_VAR(it_veryfy->second->net_client_info_.net_comm_handle_));
                }
                auto it_id = map_verified_connections_by_connectionID.find(connectionID);
                if (it_id != map_verified_connections_by_connectionID.end())
                {
                    LOG4CXX_WARN(logger, "HandleLogin()" LOG_VAR(pUserLogin->loginName_) LOG_VAR(item->net_client_info_.connectionID) LOG_VAR(item->net_client_info_.net_comm_handle_) LOG_VAR(it_id->second->net_client_info_.connectionID)
                        LOG_VAR(it_id->second->net_client_info_.net_comm_handle_));
                }

                map_verified_connections_by_name[pUserLogin->loginName_] = item;
                map_verified_connections_by_connectionID[connectionID] = item;

                mutex_verified_connections_.Unlock();

                int errCode = 0;

                if (net_handler_)
                    net_handler_->Send(connectionID, netObject, netCommand, &errCode, sizeof(errCode));
            }

            void ApiServerMgrImp::HandleRealAccountNetStatus(int connectionID, NetGateway::Server::NetCommHandle * netObject, short netCommand, char * buf, int bufLen)
            {
                StockDLL::RealNetStatus *pStatus = (StockDLL::RealNetStatus*)buf;
                pStatus->errMsg_[sizeof(pStatus->errMsg_) - 1] = 0;
                std::string real_account;

                mutex_verified_connections_.Lock();

                auto it = map_verified_connections_by_connectionID.find(connectionID);
                if (it != map_verified_connections_by_connectionID.end())
                {
                    it->second->trade_login_flag_ = pStatus->isConnect_;
                    real_account = it->second->login_name_;
                }

                mutex_verified_connections_.Unlock();

                if (callback_ && "" != real_account)
                {
                    callback_->OnRealAccountTradeLogin(real_account.c_str(), (bool)pStatus->isConnect_);
                }

                LOG4CXX_INFO(logger, "HandleRealAccountNetStatus() " LOG_VAR(real_account) LOG_VAR((int)pStatus->isConnect_) LOG_VAR(pStatus->errMsg_));
            }

            void ApiServerMgrImp::HandlePlaceOrderRsp(int connectionID, NetGateway::Server::NetCommHandle * netObject, short netCommand, char * buf, int bufLen)
            {
                if (bufLen < sizeof(StockDLL::DLLOrderInsert))
                    return;

                StockDLL::DLLOrderInsert *pStatus = (StockDLL::DLLOrderInsert*)buf;

                LOG4CXX_INFO(logger, "HandlePlaceOrderRsp()" LOG_VAR(pStatus->orderRef_) LOG_VAR(pStatus->orderNo_) LOG_VAR(pStatus->isSuccess_)LOG_VAR(pStatus->errMsg_));
                StockOrderPtr tmpOrder = ConvertFromDLLToServerOrder(*pStatus);

                ContractCodeType contract_code = { 0 };
                strncpy_s(contract_code, pStatus->stockCode_, sizeof(contract_code) - 1);

                if (callback_)
                    callback_->OnOrderInsert(getLoginName(connectionID).c_str(), contract_code, tmpOrder);
            }

            void ApiServerMgrImp::HandleOrderStatusUpdate(int connectionID, NetGateway::Server::NetCommHandle * netObject, short netCommand, char * buf, int bufLen)
            {
                if (bufLen < sizeof(StockDLL::DLLOrderInfo))
                {
                    int sizeofTcasOrderInfo = sizeof(StockDLL::DLLOrderInfo);
                    LOG4CXX_WARN(logger, "HandleOrderStatusUpdate()" LOG_VAR(connectionID) LOG_VAR(netCommand) LOG_VAR(netObject) LOG_VAR(bufLen) LOG_VAR(sizeofTcasOrderInfo));
                    return;
                }

                StockDLL::DLLOrderInfo *pStatus = (StockDLL::DLLOrderInfo*)buf;

                LOG4CXX_INFO(logger, "HandleOrderStatusUpdate()" LOG_VAR(pStatus->orderRef_) LOG_VAR(pStatus->orderNo_) LOG_VAR(pStatus->status_));
                StockOrderPtr tmpOrder = ConvertFromDLLToServerOrder(*pStatus);

                ContractCodeType contract_code = { 0 };
                strncpy_s(contract_code, pStatus->securityCode_, sizeof(contract_code) - 1);

                if (callback_)
                    callback_->OnOrderStatusUpdate(getLoginName(connectionID).c_str(), contract_code, tmpOrder);
            }

            void ApiServerMgrImp::HandleTradeInfo(int connectionID, NetGateway::Server::NetCommHandle * netObject, short netCommand, char * buf, int bufLen)
            {
                if (bufLen < sizeof(StockDLL::DLLTradeInfo))
                {
                    int sizeofTcasTradeInfo = sizeof(StockDLL::DLLTradeInfo);
                    LOG4CXX_WARN(logger, "HandleTradeInfo()" LOG_VAR(bufLen) LOG_VAR(sizeofTcasTradeInfo) LOG_VAR(netCommand) LOG_VAR(netObject));
                    return;
                }

                StockDLL::DLLTradeInfo *pTrade = (StockDLL::DLLTradeInfo*)buf;

                LOG4CXX_INFO(logger, "HandleTradeInfo()" LOG_VAR(pTrade->securityCode_)
                    LOG_VAR(pTrade->tradeNo_) LOG_VAR(pTrade->orderNo_) LOG_VAR(pTrade->tradeVolume_)
                    LOG_VAR(pTrade->tradePrice_) LOG_VAR(pTrade->direction_) );

                StockTradePtr trade_info = ConvertFromDLLToServerTrade(*pTrade);

                ContractCodeType contract_code = { 0 };
                strncpy_s(contract_code, pTrade->securityCode_, sizeof(contract_code) - 1);

                if (callback_)
                    callback_->OnTradeInfo(getLoginName(connectionID).c_str(), contract_code, trade_info);
            }

            void ApiServerMgrImp::HandleCancelOrder(int connectionID, NetGateway::Server::NetCommHandle * netObject, short netCommand, char * buf, int bufLen)
            {
                if (bufLen < sizeof(StockDLL::DLLOrderCancal))
                {
                    int sizeofTcasTradeInfo = sizeof(StockDLL::DLLOrderCancal);
                    LOG4CXX_WARN(logger, "HandleCancelOrder()" LOG_VAR(bufLen) LOG_VAR(sizeofTcasTradeInfo) LOG_VAR(netCommand) LOG_VAR(netObject));
                    return;
                }

                StockDLL::DLLOrderCancal *pStatus = (StockDLL::DLLOrderCancal*)buf;

                LOG4CXX_INFO(logger, "HandleCancelOrder()" LOG_VAR(pStatus->orderNo_) LOG_VAR(pStatus->isSuccess_) LOG_VAR(pStatus->errMsg_));

                StockOrderPtr tmpOrder = ConvertFromDLLToServerOrder(*pStatus);

                ContractCodeType contract_code = { 0 };
                strncpy_s(contract_code, pStatus->stockCode_, sizeof(contract_code) - 1);

                if (callback_)
                    callback_->OnOrderCancel(getLoginName(connectionID).c_str(), contract_code, tmpOrder);
            }

            std::string ApiServerMgrImp::getLoginName(int connectionID)
            {
                std::string real_name;

                mutex_verified_connections_.Lock();
                auto it = map_verified_connections_by_connectionID.find(connectionID);
                if (it != map_verified_connections_by_connectionID.end())
                {
                    real_name = it->second->login_name_;
                }
                mutex_verified_connections_.Unlock();
                return real_name;
            }

            StockOrderPtr ApiServerMgrImp::ConvertFromDLLToServerOrder(const StockDLL::DLLOrderInfo& pOrder)
            {
                StockOrderPtr tmpOrder = std::make_shared<StockOrderInfo>();
                strncpy_s(tmpOrder->generate_datetime_, pOrder.orderTime_, sizeof(tmpOrder->generate_datetime_) - 1);
                strncpy_s(tmpOrder->system_order_id_, pOrder.orderNo_, sizeof(tmpOrder->system_order_id_) - 1);
                strncpy_s(tmpOrder->order_ref_, pOrder.orderRef_, sizeof(tmpOrder->order_ref_) - 1);
                tmpOrder->order_price_ = pOrder.orderPrice_;
                tmpOrder->order_vol_ = pOrder.orderVolume_;
                tmpOrder->order_trade_price_ = pOrder.tradePrice_;
                tmpOrder->trade_vol_ = pOrder.tradeVolume_;

                tmpOrder->order_type_ = getOrderTypeFromDll(pOrder.priceType_);
                tmpOrder->direct_type_ = getDirectTypeFromDll(pOrder.direction_);
                tmpOrder->order_state_ = getOrderStateTypeFromDll(pOrder.status_);

                return tmpOrder;
            }

            StockOrderPtr ApiServerMgrImp::ConvertFromDLLToServerOrder(const StockDLL::DLLOrderCancal& pOrder)
            {
                StockOrderPtr tmpOrder = std::make_shared<StockOrderInfo>();
                strncpy_s(tmpOrder->system_order_id_, pOrder.orderNo_, sizeof(tmpOrder->system_order_id_) - 1);
                if (pOrder.isSuccess_)
                    tmpOrder->order_state_ = OrderStateType::ORDER_STATE_PARTDELETED;
                else
                    tmpOrder->order_state_ = OrderStateType::ORDER_STATE_FAIL;

                return tmpOrder;
            }

            StockOrderPtr ApiServerMgrImp::ConvertFromDLLToServerOrder(const StockDLL::DLLOrderInsert& pOrder)
            {
                StockOrderPtr tmpOrder = std::make_shared<StockOrderInfo>();
                strncpy_s(tmpOrder->system_order_id_, pOrder.orderNo_, sizeof(tmpOrder->system_order_id_) - 1);
                strncpy_s(tmpOrder->order_ref_, pOrder.orderRef_, sizeof(tmpOrder->order_ref_) - 1);
                if (pOrder.isSuccess_)
                    tmpOrder->order_state_ = OrderStateType::ORDER_STATE_QUEUED;
                else
                    tmpOrder->order_state_ = OrderStateType::ORDER_STATE_FAIL;

                return tmpOrder;
            }


            StockTradePtr ApiServerMgrImp::ConvertFromDLLToServerTrade(const StockDLL::DLLTradeInfo& tcasTrade)
            {
                StockTradePtr tmpTrade = std::make_shared<StockTradeInfo>();
                tmpTrade->direct_type_ = getDirectTypeFromDll(tcasTrade.direction_);
                tmpTrade->trade_price_ = tcasTrade.tradePrice_;
                tmpTrade->volume_ = tcasTrade.tradeVolume_;
                strncpy_s(tmpTrade->system_trade_id_, tcasTrade.tradeNo_, sizeof(tmpTrade->system_trade_id_) - 1);
                strncpy_s(tmpTrade->system_order_id_, tcasTrade.orderNo_, sizeof(tmpTrade->system_order_id_) - 1);

                return tmpTrade;
            }

            AllTrade::OrderTypeType ApiServerMgrImp::getOrderTypeFromDll(StockDLL::PriceType type) const
            {
                switch (type)
                {
                case StockDLL::PriceTypeType::PriceTypeLimit:
                    return OrderTypeType::ORDER_TYPE_LIMIT;
                    break;
                default:
                    assert(0);
                    break;
                }
                return OrderTypeType::ORDER_TYPE_Invalid;
            }

            StockDLL::PriceType ApiServerMgrImp::getOrderTypeToDll(OrderTypeType type) const
            {
                switch (type)
                {
                case AllTrade::OrderTypeType::ORDER_TYPE_LIMIT:
                    return StockDLL::PriceTypeType::PriceTypeLimit;
                    break;
                default:
                    assert(0);
                    break;
                }
                return StockDLL::PriceTypeType::PriceTypeErr;
            }

            AllTrade::DirectType ApiServerMgrImp::getDirectTypeFromDll(StockDLL::OrderType type) const
            {
                switch (type)
                {
                case StockDLL::OrderTypeType::OrderTypeBuy:
                    return DirectType::DIRECT_BUY;
                    break;
                case StockDLL::OrderTypeType::OrderTypeSell:
                    return DirectType::DIRECT_SELL;
                    break;
                default:
                    assert(0);
                    break;
                }
                return DirectType::DIRECT_Invalid;
            }

            StockDLL::OrderType ApiServerMgrImp::getDirectTypeToDll(DirectType type) const
            {
                switch (type)
                {
                case AllTrade::DirectType::DIRECT_BUY:
                    return StockDLL::OrderTypeType::OrderTypeBuy;
                    break;
                case AllTrade::DirectType::DIRECT_SELL:
                    return StockDLL::OrderTypeType::OrderTypeSell;
                    break;
                default:
                    break;
                }
                return StockDLL::OrderTypeType::OrderTypeError;
            }

            AllTrade::OrderStateType ApiServerMgrImp::getOrderStateTypeFromDll(StockDLL::OrderStatus type) const
            {
                switch (type)
                {
                case StockDLL::OrderStatusType::OrderStatusReceived:
                    return AllTrade::OrderStateType::ORDER_STATE_QUEUED;
                    break;
                case StockDLL::OrderStatusType::OrderStatusCanceled:
                    return AllTrade::OrderStateType::ORDER_STATE_DELETED;
                    break;
                case StockDLL::OrderStatusType::OrderStatusPartTraded:
                    return AllTrade::OrderStateType::ORDER_STATE_PARTFINISHED;
                    break;
                case StockDLL::OrderStatusType::OrderStatusAllTraded:
                    return AllTrade::OrderStateType::ORDER_STATE_FINISHED;
                    break;
                default:
                    break;
                }
                return AllTrade::OrderStateType::ORDER_STATE_Invalid;
            }

            StockDLL::OrderStatus ApiServerMgrImp::getOrderStateTypeToDll(OrderStateType type) const
            {
                switch (type)
                {
                case AllTrade::OrderStateType::ORDER_STATE_QUEUED:
                    return StockDLL::OrderStatusType::OrderStatusReceived;
                    break;
                case AllTrade::OrderStateType::ORDER_STATE_DELETED:
                    return StockDLL::OrderStatusType::OrderStatusCanceled;
                    break;
                case AllTrade::OrderStateType::ORDER_STATE_PARTFINISHED:
                    return StockDLL::OrderStatusType::OrderStatusPartTraded;
                    break;
                case AllTrade::OrderStateType::ORDER_STATE_FINISHED:
                    return StockDLL::OrderStatusType::OrderStatusAllTraded;
                    break;
                default:
                    break;
                }
                return StockDLL::OrderStatusType::OrderStatusOther;
            }

        }
    }
}  //  ApiServerMgr