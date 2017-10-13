#ifndef API_SERVER_MGR_H
#define API_SERVER_MGR_H

#ifdef APISERVERMGR_EXPORTS
#define APISERVERMGR_API __declspec(dllexport)
#else
#define APISERVERMGR_API __declspec(dllimport)
#endif

#define  STATIC_APIS_MAX        200    //  支持垢Api上限
#define  REAL_USERNAME_LEN      16     //  实盘 帐户名长度

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
                //  real_name = 实盘帐户名
                //  errCode = 请求错误码
                //  交易接口登录状态返回
                virtual void OnRealAccountTradeLogin(const char *real_name, bool ok) {};
                //  下单返回
                virtual void OnOrderInsert(const char *real_name, const ContractCodeType contract_code, const StockOrderPtr& orderInfo) {};
                //  撤单返回
                virtual void OnOrderCancel(const char *real_name, const ContractCodeType contract_code, const OrderInfoPtr& order_ptr) {};
                //  委托状态更新返回
                virtual void OnOrderStatusUpdate(const char *real_name, const ContractCodeType contract_code, const StockOrderPtr& orderInfo) {};
                //  成交信息返回
                virtual void OnTradeInfo(const char *real_name, const ContractCodeType contract_code, const StockTradePtr& tradeInfo) {};
            };

            class StockApiServerInterface
            {
            public:
                //  注册回调
                virtual void RegisterCallBack(StockApiServerCallBack *callback) {};
                //  下单请求
                virtual int ReqOrderInsert(const char *real_name, const ContractCodeType& cont_code, const StockOrderPtr& norderInfo, bool isXSHG) { return 0; }
                //  撤单请求
                virtual int ReqCancelOrder(const char *real_name, const ContractCodeType& cont_code, const StockOrderPtr& orderInfo, bool isXSHG) { return 0; }
            };

            //  获取ApiServerMgr实例
            APISERVERMGR_API StockApiServerInterface *GetApiServerMgr();
            //  初始化ApiServerMgr
            // @param: listen_port=模块要侦听的端口
            // @return: 错误码
            APISERVERMGR_API int InitApiServerMgr(int listen_port);

            //  释放ApiServerMgr
            APISERVERMGR_API int FiniApiServerMgr();
        }
    }
}

#endif  // API_SERVER_MGR_H