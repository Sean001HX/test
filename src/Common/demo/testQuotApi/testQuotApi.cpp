// testQuotApi.cpp : Defines the entry point for the console application.
//

#include "include/QuotationApi.h"
#include <iostream>
#include <tchar.h>

#ifdef _WIN64
#	ifdef  _DEBUG
#		pragma comment(lib, "QuotationApi64d")
#	else
#		pragma comment(lib, "QuotationApi64")
#	endif
#else
#	ifdef  _DEBUG
#		pragma comment(lib, "QuotationApi32d")
#	else
#		pragma comment(lib, "QuotationApi32")
#	endif
#endif


#define TLOG(x)   << #x << "[" << x << "]"

#define  TEST_HOST                          "127.0.0.1"
#define  TEST_PORT                          6666
#define  TEST_LOGINNAME                     "test"
#define  TEST_PASSWORD                      "password"

class TestSpi : public AllQuotation::QuotationSpi
{
public:
	virtual void OnLogin(bool ok, const char *msg)
	{
		std::cout << "OnLogin(" << ok << ", " << msg << ")\n";

		if (ok)
		{
			api_->RegisterMarket("HKFE HSI 1704", true);
			api_->RegisterMarket("HKFE HMI 1704", true);
			api_->RegisterMarket("NYMEX CL 1705", true);
			api_->RegisterMarket("NYMEX CL 1706", true);
		}
	};
	virtual void OnMarketData(const AllQuotation::QuotationCommon *quot)
	{
		std::cout << "OnMarketData() ====================================\n";
		std::cout TLOG(quot->quotationCode) TLOG((int)(quot->type)) TLOG(quot->high) TLOG(quot->low) TLOG(quot->open) TLOG(quot->close) TLOG(quot->askPrice[0]) TLOG(quot->askVolume[0]) 
			TLOG(quot->bidPrice[0]) TLOG(quot->bidVolume[0]) TLOG(quot->lastPrice) TLOG(quot->lastVolume) TLOG(quot->openInterest) TLOG(quot->turnOverAmount) TLOG(quot->turnOverVolume);
		std::cout << "OnMarketData() ====================================\n";
	};
	virtual void OnRegisterMarket(const char *quotationCode, bool ok)
	{
		std::cout << "OnRegisterMarket(" << quotationCode << ", " << ok << ")\n";
	};

public:
	AllQuotation::QuotationApi *api_;
};

int _tmain(int argc, _TCHAR* argv[])
{
	AllQuotation::QuotationApi *api = AllQuotation::AllocQuotationApi();
	if (0 == api)
	{
		std::cerr << "AllQuotation::AllocQuotationApi() failed\n";
		getchar();
		return -1;
	}

	TestSpi spi;
	spi.api_ = api;
	api->RegisterCallback(&spi);

	api->Login(TEST_HOST, TEST_PORT, TEST_LOGINNAME, TEST_PASSWORD);


	getchar();

	api->RegisterMarket("HKFE HSI 1704", false);
	api->RegisterMarket("HKFE HMI 1704", false);
	api->RegisterMarket("NYMEX CL 1705", false);
	api->RegisterMarket("NYMEX CL 1706", false);

	getchar();

	api->RegisterMarket("HKFE HSI 1704", true);
	api->RegisterMarket("HKFE HMI 1704", true);
	api->RegisterMarket("NYMEX CL 1705", true);
	api->RegisterMarket("NYMEX CL 1706", true);

	getchar();

	return 0;
}

