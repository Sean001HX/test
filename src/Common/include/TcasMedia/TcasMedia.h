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

	//��ʼ
	TCASMEDIA_API void InitTcasApi();

	//����
	TCASMEDIA_API void FiniTcasApi();

	
	//API�ӿ���
	class TCASMEDIA_API CTcasMedia
	{
	public:
		CTcasMedia(void);
		~CTcasMedia();
		static CTcasMedia *GetInstance();
	public:
		//ע��ص�
		void RegisterCallBack(CTcasMediaCallBack *callback);
		//�����������
		bool StartNetService(char *ip, int port);
		//��ֹ�������
		bool EndNetService();
		//��������״̬
		bool NetIsOK();

		/*
		* @brief: �û���¼�ӿ�
		* @param: szName ��¼�û���
		* @param: szPsw �û�����
		* @return: ������
		* @Notes:
		*/
		int Login(StockDLL::LoginToTc *loginInfo);

		/*
		* @brief: apiService��TC֪ͨ�Լ�������״̬
		* @param: TcasASNetStatus *tans--����״̬��Ϣ
		* @return: ������
		* @Notes:
		*/
		int NotifyNetStatus(StockDLL::RealNetStatus *tans);

		/*
		* @brief: ��Ӧ�µ�֮״̬,�µ�ָ��ɹ�,����������ָ��ɹ�
		* @param: TcasOrderStatus *tos--�µ�״̬
		* @return: ������
		* @Notes:
		*/
		int ResponsePlaceOrderStatus(StockDLL::DLLOrderInsert *doi);


		/*
		* @brief: ��Ӧ�µ�֮��������,ί��ִ������
		* @param: TcasOrderInfo *toi--��������
		* @return: ������
		* @Notes:
		*/
		int ResponsePlaceOrderOrder(StockDLL::DLLOrderInfo *tos);

		/*
		* @brief: ��Ӧ�µ�֮�ɽ���Ϣ
		* @param: TcasTradeInfo *tti--�ɽ���Ϣ
		* @return: ������
		* @Notes:
		*/
		int ResponsePlaceOrderTrade(StockDLL::DLLTradeInfo *tti);

		/*
		* @brief: ��Ӧȡ���µĵ���
		* @param: TcasOrderCancelInfo *toci--Ҫȡ���ĵ���
		* @return: ������
		* @Notes:
		*/
		int ResponseCancelOrder(StockDLL::DLLOrderCancal *tcor);

		/* ������
		* @brief: ��ѯί�м�¼
		* @param: std::vector<TcasOrderInfo> &arrOrder--��ѯ���صĵ���
		* @return: ������
		* @Notes:
		*/
		//int ResponseQueryOrder(TcasQueryRtn *pRtn,std::vector<TcasOrderInfo> &arrOrder);

		/* ������
		* @brief: ��Ӧ��ѯ
		* @param: std::vector<TcasOrderInfo> &arrOrder--��ѯ���صĵ���
		* @return: ������
		* @Notes:
		*/
		//int ResponseQueryPostion(TcasQueryRtn *pRtn, std::vector<TcasPostionInfo> &arrPosition);

		/* 
		* @brief: ͬ��֪ͨί�м�¼��Ϣ
		* @param: std::vector<Financing::OrderInfo> &vecOrderInfos--֪ͨί�м�¼��Ϣ
		* @return: ������
		* @Notes:
		*/
		//int NotifyAsyncOrderRecords(std::vector<Financing::OrderInfo> &vecOrderInfos);

		/*
		* @brief: ͬ��֪ͨ�ɽ���¼��Ϣ
		* @param: std::vector<Financing::TradeInfo> &vecTradeInfos--֪ͨί�м�¼��Ϣ
		* @return: ������
		* @Notes:
		*/
		//int NotifyAsyncTradeRecords(std::vector<Financing::TradeInfo> &vecTradeInfos);
	private:
		CNetMgr *mgr_;
		CTcasBuss *buss_;
	};
};



