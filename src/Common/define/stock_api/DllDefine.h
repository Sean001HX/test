#pragma once

#include <windows.h>
#include <winbase.h>

	/// ��ͨ����ʵ��
	typedef void(__stdcall* OpenTdxDelegate)();					//��ͨ��
	//typedef bool(__stdcall* OpenTdxDelegate)(char* ErrInfo);	//������
	/// �ر�ͨ����ʵ��
	typedef void(__stdcall* CloseTdxDelegate)();
	/// �����˻���¼
	typedef int(__stdcall* LogonDelegate)(char* IP, short Port, char* Version, short YybID, char* AccountNo, char* TradeAccount, char* JyPassword, char* TxPassword, char* ErrInfo);  //��ͨ��
	//typedef int(__stdcall* LogonDelegate)(char* IP, short Port, char* Version, short YybID, unsigned char LoginMode, char* AccountNo, char* TradeAccount, char* JyPassword, char* TxPassword, char* ErrInfo);  //������
	/// �����˻��ǳ�
	typedef void(__stdcall* LogoffDelegate)(int ClientID);
	/// ��ѯ���ֽ�������
	typedef void(__stdcall* QueryDataDelegate)(int ClientID, int Category, char* Result, char* ErrInfo);
	/// ������ͨ�����湦��,��ѯ������ʷ����
	typedef void(__stdcall* QueryHistoryDataDelegate)(int ClientID, int Category, char* StartDate, char* EndDate, char* Result, char* ErrInfo);
	/// ������ͨ�����湦��,������ѯ���ֽ�������,�����鴫��ÿ��ί�еĲ����������i��Ԫ�ر�ʾ��i����ѯ����Ӧ����
	typedef void(__stdcall* QueryDatasDelegate)(int ClientID, int Category[], int Count, char* Result[], char* ErrInfo[]);
	/// ���ڸ߼������湦��,������ѯ���ֽ�������,�����鴫��ÿ��ί�еĲ����������i��Ԫ�ر�ʾ��i����ѯ����Ӧ����
	typedef void(__stdcall* QueryMultiAccountsDatasDelegate)(int ClientID[], int Category[], int Count, char* Result[], char* ErrInfo[]);
	/// ��ί�н���֤ȯ
	typedef void(__stdcall* SendOrderDelegate)(int ClientID, int Category, int PriceType, char* Gddm, char* Zqdm, float Price, int Quantity, char* Result, char* ErrInfo);
	/// ������ͨ�����湦��,������ί�н���֤ȯ�������鴫��ÿ��ί�еĲ����������i��Ԫ�ر�ʾ��i��ί�е���Ӧ����
	typedef void(__stdcall* SendOrdersDelegate)(int ClientID, int Category[], int PriceType[], char* Gddm[], char* Zqdm[], float Price[], int Quantity[], int Count, char* Result[], char* ErrInfo[]);
	/// ���ڸ߼������湦��,������ί�н���֤ȯ�������鴫��ÿ��ί�еĲ����������i��Ԫ�ر�ʾ��i��ί�е���Ӧ����
	typedef void(__stdcall* SendMultiAccountsOrdersDelegate)(int ClientID[], int Category[], int PriceType[], char* Gddm[], char* Zqdm[], float Price[], int Quantity[], int Count, char* Result[], char* ErrInfo[]);
	/// ��ί��
	typedef void(__stdcall* CancelOrderDelegate)(int ClientID, char* ExchangeID, char* hth, char* Result, char* ErrInfo);
	/// ������ͨ�����湦��,������ί��, �����鴫��ÿ��ί�еĲ����������i��Ԫ�ر�ʾ��i����ί�е���Ӧ����
	typedef void(__stdcall* CancelOrdersDelegate)(int ClientID, char* ExchangeID[], char* hth[], int Count, char* Result[], char* ErrInfo[]);
	/// ���ڸ߼������湦��,������ί��, �����鴫��ÿ��ί�еĲ����������i��Ԫ�ر�ʾ��i����ί�е���Ӧ����
	typedef void(__stdcall* CancelMultiAccountsOrdersDelegate)(int ClientID[], char* ExchangeID[], char* hth[], int Count, char* Result[], char* ErrInfo[]);
	/// ��ȡ֤ȯ��ʵʱ�嵵����
	typedef void(__stdcall* GetQuoteDelegate)(int ClientID, char* Zqdm, char* Result, char* ErrInfo);
	/// ������ͨ�����湦��,������ȡ֤ȯ��ʵʱ�嵵����
	typedef void(__stdcall* GetQuotesDelegate)(int ClientID, char* Zqdm[], int Count, char* Result[], char* ErrInfo[]);
	/// ���ڸ߼������湦��,������ȡ֤ȯ��ʵʱ�嵵����
	typedef void(__stdcall* GetMultiAccountsQuotesDelegate)(int ClientID[], char* Zqdm[], int Count, char* Result[], char* ErrInfo[]);
	/// ������ȯֱ�ӻ���
	typedef void(__stdcall* RepayDelegate)(int ClientID, char* Amount, char* Result, char* ErrInfo);

	HMODULE HMODULE1 = LoadLibrary(L"Trade.dll");

	//��ȡapi����
	OpenTdxDelegate OpenTdx = (OpenTdxDelegate)GetProcAddress(HMODULE1, "OpenTdx");
	CloseTdxDelegate CloseTdx = (CloseTdxDelegate)GetProcAddress(HMODULE1, "CloseTdx");
	LogonDelegate Logon = (LogonDelegate)GetProcAddress(HMODULE1, "Logon");
	LogoffDelegate Logoff = (LogoffDelegate)GetProcAddress(HMODULE1, "Logoff");
	QueryDataDelegate QueryData = (QueryDataDelegate)GetProcAddress(HMODULE1, "QueryData");
	SendOrderDelegate SendOrder = (SendOrderDelegate)GetProcAddress(HMODULE1, "SendOrder");
	CancelOrderDelegate CancelOrder = (CancelOrderDelegate)GetProcAddress(HMODULE1, "CancelOrder");
	GetQuoteDelegate GetQuote = (GetQuoteDelegate)GetProcAddress(HMODULE1, "GetQuote");
	RepayDelegate Repay = (RepayDelegate)GetProcAddress(HMODULE1, "Repay");


	//��������ͨ�����湦�ܺ���
	QueryDatasDelegate QueryDatas = (QueryDatasDelegate)GetProcAddress(HMODULE1, "QueryDatas");
	QueryHistoryDataDelegate QueryHistoryData = (QueryHistoryDataDelegate)GetProcAddress(HMODULE1, "QueryHistoryData");
	SendOrdersDelegate SendOrders = (SendOrdersDelegate)GetProcAddress(HMODULE1, "SendOrders");
	CancelOrdersDelegate CancelOrders = (CancelOrdersDelegate)GetProcAddress(HMODULE1, "CancelOrders");
	GetQuotesDelegate GetQuotes = (GetQuotesDelegate)GetProcAddress(HMODULE1, "GetQuotes");

	//�����Ǹ߼������湦�ܺ���
	QueryMultiAccountsDatasDelegate QueryMultiAccountsDatas = (QueryMultiAccountsDatasDelegate)GetProcAddress(HMODULE1, "QueryMultiAccountsDatas");
	SendMultiAccountsOrdersDelegate SendMultiAccountsOrders = (SendMultiAccountsOrdersDelegate)GetProcAddress(HMODULE1, "SendMultiAccountsOrders");
	CancelMultiAccountsOrdersDelegate CancelMultiAccountsOrders = (CancelMultiAccountsOrdersDelegate)GetProcAddress(HMODULE1, "CancelMultiAccountsOrders");
	GetMultiAccountsQuotesDelegate GetMultiAccountsQuotes = (GetMultiAccountsQuotesDelegate)GetProcAddress(HMODULE1, "GetMultiAccountsQuotes");
