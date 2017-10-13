#ifndef API_SERVER_MGR_H
#define API_SERVER_MGR_H

#ifdef APISERVERMGR_EXPORTS
#define APISERVERMGR_API __declspec(dllexport)
#else
#define APISERVERMGR_API __declspec(dllimport)
#endif

#define  STATIC_APIS_MAX        200    //  ֧�ֹ�Api����
#define  REAL_USERNAME_LEN      16     //  ʵ�� �ʻ�������

#include "define/struct_declare.h"
#include "define/params_declare.h"
#include <vector>
#include <string>

namespace AllTrade {
    namespace NPTradeCenter {

        namespace StockApiManager
        {
            class StockApiServerCallBack
            {
            public:
                //  real_name = ʵ���ʻ���
                //  errCode = ���������
                //  ���׽ӿڵ�¼״̬����
                virtual void OnRealAccountTradeLogin(const char *real_name, bool ok) {};
                //  �µ�����
                virtual void OnOrderInsert(const char *real_name, const ContractCodeType contract_code, const StockOrderPtr& orderInfo) {};
                //  ��������
                virtual void OnOrderCancel(const char *real_name, const ContractCodeType contract_code, const OrderInfoPtr& order_ptr) {};
                //  ί��״̬���·���
                virtual void OnOrderStatusUpdate(const char *real_name, const ContractCodeType contract_code, const StockOrderPtr& orderInfo) {};
                //  �ɽ���Ϣ����
                virtual void OnTradeInfo(const char *real_name, const ContractCodeType contract_code, const StockTradePtr& tradeInfo) {};
            };

            class StockApiServerInterface
            {
            public:
                //  ע��ص�
                virtual void RegisterCallBack(StockApiServerCallBack *callback) {};
                //  �µ�����
                virtual int ReqOrderInsert(const char *real_name, const ContractCodeType& cont_code, const StockOrderPtr& norderInfo, bool isXSHG) { return 0; }
                //  ��������
                virtual int ReqCancelOrder(const char *real_name, const ContractCodeType& cont_code, const StockOrderPtr& orderInfo, bool isXSHG) { return 0; }
            };

            //  ��ȡApiServerMgrʵ��
            APISERVERMGR_API StockApiServerInterface *GetApiServerMgr();
            //  ��ʼ��ApiServerMgr
            // @param: listen_port=ģ��Ҫ�����Ķ˿�
            // @return: ������
            APISERVERMGR_API int InitApiServerMgr(int listen_port);

            //  �ͷ�ApiServerMgr
            APISERVERMGR_API int FiniApiServerMgr();
        }
    }
}

#endif  // API_SERVER_MGR_H