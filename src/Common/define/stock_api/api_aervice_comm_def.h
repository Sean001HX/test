/*
brief : api service ������Ϣ
author :
created date : 2016-05-11
*/


#ifndef API_SERVICE_COMM_DEF_H
#define API_SERVICE_COMM_DEF_H


//  �ӿ����Ͷ���

#define API_SERVICE_TYPE_CTP              1             //  CTP
#define API_SERVICE_TYPE_SP               2             //  SP
#define API_SERVICE_TYPE_ESUNNY           3             //  esunny ��ʢ
#define API_SERVICE_TYPE_IB               4             //  IB ӯ͸


//  CTP �ӿڹ��ܱ��

enum ApiServiceOfCTP
{
	//   ���׻ص�����
	TradeRspBegin   =   0,
	OnRspUserLogin,                                         ///  ��¼������Ӧ
	OnRspUserLogout,                                        ///  �ǳ�������Ӧ
	OnRspOrderInsert,                                       ///  ����¼��������Ӧ
	OnRspSettlementInfoConfirm,                             ///  Ͷ���߽�����ȷ����Ӧ
	OnRspQryOrder,                                          ///  �����ѯ������Ӧ
	OnRspQryTrade,                                          ///  �����ѯ�ɽ���Ӧ
	OnRspQryInvestorPosition,                               ///  �����ѯͶ���ֲ߳���Ӧ
	OnRspQryTradingAccount,                                 ///  �����ѯ�ʽ��˻���Ӧ
	OnRspQryExchange,                                       ///  �����ѯ��������Ӧ
	OnRspQryProduct,                                        ///  �����ѯ��Ʒ��Ӧ
	OnRspQryInstrument,                                     ///  �����ѯ��Լ��Ӧ
	OnRspQryDepthMarketData,                                ///  �����ѯ������Ӧ
	OnRspQrySettlementInfo,                                 ///  �����ѯͶ���߽�������Ӧ
	OnRspQryInvestorPositionDetail,                         ///  �����ѯͶ���ֲ߳���ϸ��Ӧ
	OnRspQrySettlementInfoConfirm,                          ///  �����ѯ������Ϣȷ����Ӧ

	// ********************************************************************************* //
	//   �������󷽷�
	TradeReqBegin   =   0x800,
	ReqUserLogin,                                        	///  �û���¼����  
	ReqUserLogout,                                          ///  �ǳ�����
	ReqOrderInsert,                                         ///  ����¼������
	ReqQueryMaxOrderVolume,                                 ///  ��ѯ��󱨵���������
	ReqSettlementInfoConfirm,                               ///  Ͷ���߽�����ȷ��
	ReqQryOrder,                                            ///  �����ѯ����
	ReqQryTrade,                                            ///  �����ѯ�ɽ�
	ReqQryInvestorPosition,                                 ///  �����ѯͶ���ֲ߳�
	ReqQryTradingAccount,                                   ///  �����ѯ�ʽ��˻�
	ReqQryTradingCode,                                      ///  �����ѯ���ױ���
	ReqQryInstrumentMarginRate,                             ///  �����ѯ��Լ��֤����
	ReqQryInstrumentCommissionRate,                         ///  �����ѯ��Լ��������
	ReqQryExchange,                                         ///  �����ѯ������
	ReqQryProduct,                                          ///  �����ѯ��Ʒ
	ReqQryInstrument,                                       ///  �����ѯ��Լ
	ReqQryDepthMarketData,                                  ///  �����ѯ����
	ReqQryInvestorPositionDetail,                           ///  �����ѯͶ���ֲ߳���ϸ
	ReqQryExchangeRate,                                     ///  �����ѯ����

	//  ********************************************************************************  //
	//  ����ص�
	QuotationRspBegin =  0xa00,
	OnRspSubMarketData,                                    ///  ��������Ӧ��
	OnRspUnSubMarketData,                                  ///  ȡ����������Ӧ��    
	OnRtnDepthMarketData,                                  ///  �������֪ͨ

	//  ********************************************************************************  //
	//  ��������
	QuotationReqBegin =  0xb00,
	SubscribeMarketData,                                   ///  ��������
	UnSubscribeMarketData,                                 ///  �˶�����
};


struct ApiServiceProtoHead                                ///  api service Э��ͷ
{
	short       apiType;                                  ///  �ӿ�����
	short       apiServiceProtoCode;                      ///  ��Ӧ�ӿڵ�Э�鹦�ܱ��
	int         dataLen;                                  ///  Э�����ݳ���

	ApiServiceProtoHead()
	{
		apiType = 0;
		apiServiceProtoCode = 0;
		dataLen = 0;
	}
};

#endif  // API_SERVICE_COMM_DEF_H