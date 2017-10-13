// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the TCASMEDIA_EXPORTS
// symbol defined on the command line. This symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// TCASMEDIA_API functions as being imported from a DLL, whereas this DLL sees symbols
// defined with this macro as being exported.
#ifdef TCASMEDIA_EXPORTS
#define TCASMEDIA_API __declspec(dllexport)
#else
#define TCASMEDIA_API __declspec(dllimport)
#endif

#include <vector>
#include "define/stock_api/tcas_def.h"
#include "define/stock_api/StockDllStruct.h"

namespace TcasMedia
{ 
	class CNetMgr;
	class CTcasBuss;
	class CTcasMediaCallBack;

	//开始
	TCASMEDIA_API void InitTcasApi();

	//结束
	TCASMEDIA_API void FiniTcasApi();

	
	//API接口类
	class TCASMEDIA_API CTcasMedia
	{
	public:
		CTcasMedia(void);
		~CTcasMedia();
		static CTcasMedia *GetInstance();
	public:
		//注册回调
		void RegisterCallBack(CTcasMediaCallBack *callback);
		//启动网络服务
		bool StartNetService(char *ip, int port);
		//终止网络服务
		bool EndNetService();
		//返回网络状态
		bool NetIsOK();

		/*
		* @brief: 用户登录接口
		* @param: szName 登录用户名
		* @param: szPsw 用户密码
		* @return: 错误码
		* @Notes:
		*/
		int Login(StockDLL::LoginToTc *loginInfo);

		/*
		* @brief: apiService向TC通知自己的网络状态
		* @param: TcasASNetStatus *tans--网络状态信息
		* @return: 错误码
		* @Notes:
		*/
		int NotifyNetStatus(StockDLL::RealNetStatus *tans);

		/*
		* @brief: 回应下单之状态,下单指令成功,交易所返回指令成功
		* @param: TcasOrderStatus *tos--下单状态
		* @return: 错误码
		* @Notes:
		*/
		int ResponsePlaceOrderStatus(StockDLL::DLLOrderInsert *doi);


		/*
		* @brief: 回应下单之单子详情,委托执行详情
		* @param: TcasOrderInfo *toi--单子详情
		* @return: 错误码
		* @Notes:
		*/
		int ResponsePlaceOrderOrder(StockDLL::DLLOrderInfo *tos);

		/*
		* @brief: 回应下单之成交信息
		* @param: TcasTradeInfo *tti--成交信息
		* @return: 错误码
		* @Notes:
		*/
		int ResponsePlaceOrderTrade(StockDLL::DLLTradeInfo *tti);

		/*
		* @brief: 回应取消下的单子
		* @param: TcasOrderCancelInfo *toci--要取消的单子
		* @return: 错误码
		* @Notes:
		*/
		int ResponseCancelOrder(StockDLL::DLLOrderCancal *tcor);

		/* 已弃用
		* @brief: 查询委托记录
		* @param: std::vector<TcasOrderInfo> &arrOrder--查询返回的单子
		* @return: 错误码
		* @Notes:
		*/
		//int ResponseQueryOrder(TcasQueryRtn *pRtn,std::vector<TcasOrderInfo> &arrOrder);

		/* 已弃用
		* @brief: 回应查询
		* @param: std::vector<TcasOrderInfo> &arrOrder--查询返回的单子
		* @return: 错误码
		* @Notes:
		*/
		//int ResponseQueryPostion(TcasQueryRtn *pRtn, std::vector<TcasPostionInfo> &arrPosition);

		/* 
		* @brief: 同步通知委托记录信息
		* @param: std::vector<Financing::OrderInfo> &vecOrderInfos--通知委托记录信息
		* @return: 错误码
		* @Notes:
		*/
		//int NotifyAsyncOrderRecords(std::vector<Financing::OrderInfo> &vecOrderInfos);

		/*
		* @brief: 同步通知成交记录信息
		* @param: std::vector<Financing::TradeInfo> &vecTradeInfos--通知委托记录信息
		* @return: 错误码
		* @Notes:
		*/
		//int NotifyAsyncTradeRecords(std::vector<Financing::TradeInfo> &vecTradeInfos);
	private:
		CNetMgr *mgr_;
		CTcasBuss *buss_;
	};
};



