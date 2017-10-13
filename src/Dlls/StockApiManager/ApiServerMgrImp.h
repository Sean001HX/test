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
            //  ������Ϣ
            struct CNetClientInfo
            {
                int									 connectionID;                     //  ���ӱ�ʶ
                NetGateway::Server::NetCommHandle   *net_comm_handle_;                 //  ����ͨ�Ŷ���	
            };

            struct BaseConnectionInfo
            {
                char login_name_[REAL_USERNAME_LEN];
                CNetClientInfo net_client_info_;             //  ������Ϣ
                bool   trade_login_flag_;                    //  ���׵�¼�ɹ�״̬��־
                bool   quotation_login_flag_;                //  �����¼�ɹ�״̬��־
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
                //  ע��ص�
                void RegisterCallBack(StockApiServerCallBack *callback) override;
                //  �µ�����, isXSHG: �Ƿ�Ϊ�Ͻ���
                int ReqOrderInsert(const char *real_name, const ContractCodeType& cont_code, const StockOrderPtr& norderInfo, bool isXSHG) override;
                //  ��������
                int ReqCancelOrder(const char *real_name, const ContractCodeType& cont_code, const StockOrderPtr& orderInfo, bool isXSHG) override;

            private:
                //   �����ӵ���ʱ��֪ͨ�ص�
                //   connectionID�����Ӷ���ID
                //   net_object: ���Ӷ���handle
                virtual void OnNewConnection(int connectionID, NetGateway::Server::NetCommHandle *netObject);

                //   ���ӶϿ�
                virtual void OnDisconnect(int connectionID, NetGateway::Server::NetCommHandle *netObject);

                //   �յ����ݻص�
                virtual void OnRecv(int connectionID, NetGateway::Server::NetCommHandle *netObject, short netCommand, char *buf, int bufLen);

                //   �������ݻص�
                virtual void OnSend(int connectionID, NetGateway::Server::NetCommHandle *netObject);

            private:
                // �������ݽ���
                // api_service��¼
                void HandleLogin(int connectionID, NetGateway::Server::NetCommHandle * netObject, short netCommand, char * buf, int bufLen);
                // ʵ���ʻ�����״̬���֪ͨ
                void HandleRealAccountNetStatus(int connectionID, NetGateway::Server::NetCommHandle * netObject, short netCommand, char * buf, int bufLen);
                //  �µ�����
                void HandlePlaceOrderRsp(int connectionID, NetGateway::Server::NetCommHandle * netObject, short netCommand, char * buf, int bufLen);
                //  ί��״̬����
                void HandleOrderStatusUpdate(int connectionID, NetGateway::Server::NetCommHandle * netObject, short netCommand, char * buf, int bufLen);
                //  �ɽ���Ϣ����
                void HandleTradeInfo(int connectionID, NetGateway::Server::NetCommHandle * netObject, short netCommand, char * buf, int bufLen);
                //  ������Ϣ����
                void HandleCancelOrder(int connectionID, NetGateway::Server::NetCommHandle * netObject, short netCommand, char * buf, int bufLen);

            private:
                std::string getLoginName(int connectionID);
                StockOrderPtr ConvertFromDLLToServerOrder(const StockDLL::DLLOrderInfo& tcasOrder);
                StockOrderPtr ConvertFromDLLToServerOrder(const StockDLL::DLLOrderCancal& tcasOrder);
                StockOrderPtr ConvertFromDLLToServerOrder(const StockDLL::DLLOrderInsert& tcasOrder);
                StockTradePtr ConvertFromDLLToServerTrade(const StockDLL::DLLTradeInfo& tcasTrade);

                // �۸�����,�м��޼�
                OrderTypeType getOrderTypeFromDll(StockDLL::PriceType type) const;
                StockDLL::PriceType getOrderTypeToDll(OrderTypeType type) const;

                // ��������,��/��
                DirectType getDirectTypeFromDll(StockDLL::OrderType type) const;
                StockDLL::OrderType getDirectTypeToDll(DirectType type) const;

                // ί��״̬
                OrderStateType getOrderStateTypeFromDll(StockDLL::OrderStatus type) const;
                StockDLL::OrderStatus getOrderStateTypeToDll(OrderStateType type) const;

            private:
                //  ҵ��ص�����
                StockApiServerCallBack *callback_;
                //  ����ͨ�Ŷ���
                NetGateway::Server::CNetHandler *net_handler_;  // 

                //  �����Ӷ�δ��¼����
                std::map<int, CNetClientInfo> unlogin_connections_;
                //
                CHxMutex mutex_unlogin_connections_;

                //  �ѵ�¼����
                std::map<std::string, std::shared_ptr<CVerifiedConnectionInfo>>  map_verified_connections_by_name;
                std::map<int, std::shared_ptr<CVerifiedConnectionInfo>>          map_verified_connections_by_connectionID;
                //
                CHxMutex mutex_verified_connections_;
                //  ��ǰ�������ʻ�
                char quotation_main_account_[HX_TB_ACCOUNT_NAME_LEN];
            };

        }  // ApiServerMgr
    }
}

#endif  // API_SERVER_MGR_IMP_H