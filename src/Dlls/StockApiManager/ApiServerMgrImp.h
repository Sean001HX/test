#pragma once

#ifndef API_SERVER_MGR_IMP_H
#define API_SERVER_MGR_IMP_H

#include "include/StockApiManager/StockApiManager.h"
#include "include/NetGateway/net_gateway_interface_def.h"
#include "asm_mutex.h"
#include "define/stock_api/trade_bussness_struct_def.h"
#include "define/stock_api/StockDllStruct.h"

#include <map>
#include <memory>
#include <vector>

namespace AllTrade {
    namespace NPTradeCenter {

        namespace StockApiManager
        {
            //  连接信息
            struct CNetClientInfo
            {
                int									 connectionID;                     //  连接标识
                NetGateway::Server::NetCommHandle   *net_comm_handle_;                 //  网络通信对象	
            };

            struct BaseConnectionInfo
            {
                char login_name_[REAL_USERNAME_LEN];
                CNetClientInfo net_client_info_;             //  连接信息
                bool   trade_login_flag_;                    //  交易登录成功状态标志
                bool   quotation_login_flag_;                //  行情登录成功状态标志
                BaseConnectionInfo()
                {
                    memset(this, 0, sizeof(*this));
                }
            };

            struct CVerifiedConnectionInfo : public BaseConnectionInfo
            {
                CVerifiedConnectionInfo()
                {
                    login_name_[0] = 0;
                    trade_login_flag_ = false;
                    quotation_login_flag_ = false;
                    net_client_info_.connectionID = 0;
                    net_client_info_.net_comm_handle_ = 0;
                };

                CVerifiedConnectionInfo(const CVerifiedConnectionInfo &other)
                {
                    memcpy(login_name_, other.login_name_, sizeof(login_name_));
                    net_client_info_ = other.net_client_info_;
                    trade_login_flag_ = other.trade_login_flag_;
                    quotation_login_flag_ = other.quotation_login_flag_;
                }

                CVerifiedConnectionInfo &operator=(const CVerifiedConnectionInfo &other)
                {
                    if (this == &other)
                        return *this;

                    memcpy(login_name_, other.login_name_, sizeof(login_name_));
                    net_client_info_ = other.net_client_info_;
                    trade_login_flag_ = other.trade_login_flag_;
                    quotation_login_flag_ = other.quotation_login_flag_;

                    return *this;
                }
            };

            class ApiServerMgrImp : public StockApiServerInterface, public NetGateway::Server::CNetCallback
            {
            public:
                static ApiServerMgrImp *Instance();
                ~ApiServerMgrImp();
            private:
                ApiServerMgrImp();
                //  注册回调
                void RegisterCallBack(StockApiServerCallBack *callback) override;
                //  下单请求, isXSHG: 是否为上交所
                int ReqOrderInsert(const char *real_name, const ContractCodeType& cont_code, const StockOrderPtr& norderInfo, bool isXSHG) override;
                //  撤单请求
                int ReqCancelOrder(const char *real_name, const ContractCodeType& cont_code, const StockOrderPtr& orderInfo, bool isXSHG) override;

            private:
                //   新连接到来时的通知回调
                //   connectionID：连接对象ID
                //   net_object: 连接对象handle
                virtual void OnNewConnection(int connectionID, NetGateway::Server::NetCommHandle *netObject);

                //   连接断开
                virtual void OnDisconnect(int connectionID, NetGateway::Server::NetCommHandle *netObject);

                //   收到数据回调
                virtual void OnRecv(int connectionID, NetGateway::Server::NetCommHandle *netObject, short netCommand, char *buf, int bufLen);

                //   发送数据回调
                virtual void OnSend(int connectionID, NetGateway::Server::NetCommHandle *netObject);

            private:
                // 网络数据解析
                // api_service登录
                void HandleLogin(int connectionID, NetGateway::Server::NetCommHandle * netObject, short netCommand, char * buf, int bufLen);
                // 实盘帐户连接状态变更通知
                void HandleRealAccountNetStatus(int connectionID, NetGateway::Server::NetCommHandle * netObject, short netCommand, char * buf, int bufLen);
                //  下单返回
                void HandlePlaceOrderRsp(int connectionID, NetGateway::Server::NetCommHandle * netObject, short netCommand, char * buf, int bufLen);
                //  委托状态更新
                void HandleOrderStatusUpdate(int connectionID, NetGateway::Server::NetCommHandle * netObject, short netCommand, char * buf, int bufLen);
                //  成交信息处理
                void HandleTradeInfo(int connectionID, NetGateway::Server::NetCommHandle * netObject, short netCommand, char * buf, int bufLen);
                //  撤单信息处理
                void HandleCancelOrder(int connectionID, NetGateway::Server::NetCommHandle * netObject, short netCommand, char * buf, int bufLen);

            private:
                std::string getLoginName(int connectionID);
                StockOrderPtr ConvertFromDLLToServerOrder(const StockDLL::DLLOrderInfo& tcasOrder);
                StockOrderPtr ConvertFromDLLToServerOrder(const StockDLL::DLLOrderCancal& tcasOrder);
                StockOrderPtr ConvertFromDLLToServerOrder(const StockDLL::DLLOrderInsert& tcasOrder);
                StockTradePtr ConvertFromDLLToServerTrade(const StockDLL::DLLTradeInfo& tcasTrade);

                // 价格类型,市价限价
                OrderTypeType getOrderTypeFromDll(StockDLL::PriceType type) const;
                StockDLL::PriceType getOrderTypeToDll(OrderTypeType type) const;

                // 买卖方向,买/卖
                DirectType getDirectTypeFromDll(StockDLL::OrderType type) const;
                StockDLL::OrderType getDirectTypeToDll(DirectType type) const;

                // 委托状态
                OrderStateType getOrderStateTypeFromDll(StockDLL::OrderStatus type) const;
                StockDLL::OrderStatus getOrderStateTypeToDll(OrderStateType type) const;

            private:
                //  业务回调对象
                StockApiServerCallBack *callback_;
                //  网络通信对象
                NetGateway::Server::CNetHandler *net_handler_;  // 

                //  已连接而未登录队列
                std::map<int, CNetClientInfo> unlogin_connections_;
                //
                CHxMutex mutex_unlogin_connections_;

                //  已登录连接
                std::map<std::string, std::shared_ptr<CVerifiedConnectionInfo>>  map_verified_connections_by_name;
                std::map<int, std::shared_ptr<CVerifiedConnectionInfo>>          map_verified_connections_by_connectionID;
                //
                CHxMutex mutex_verified_connections_;
                //  当前行情主帐户
                char quotation_main_account_[HX_TB_ACCOUNT_NAME_LEN];
            };

        }  // ApiServerMgr
    }
}

#endif  // API_SERVER_MGR_IMP_H