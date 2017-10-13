#ifndef QUOTATION_API_H
#define QUOTATION_API_H

#include "define/struct_quotation_declare.h"

#ifdef QUOTATION_API_EXPORT
#define QUOTATION_API_IMPORT __declspec(dllexport)
#else
#define QUOTATION_API_IMPORT __declspec(dllimport)
#endif


#ifdef __cplusplus
#define QUOTATION_API_C_DECLARE_BEGIN    extern "C" {
#define QUOTATION_API_C_DECLARE_END      }
#else
#define QUOTATION_API_C_DECLARE_BEGIN    
#define QUOTATION_API_C_DECLARE_END     
#endif

QUOTATION_API_C_DECLARE_BEGIN

namespace AllQuotation
{
	class QuotationSpi
	{
	public:
		virtual ~QuotationSpi() {};
		virtual void OnLogin(bool ok, const char *msg) {};
		virtual void OnMarketData(const QuotationCommon *quot) {};
		virtual void OnRegisterMarket(const char *quotationCode, bool ok) {};
	};

	class QuotationApi
	{
	public:
		virtual ~QuotationApi() {};
		virtual void RegisterCallback(QuotationSpi *spi) {};
		virtual int Login(const char *IP, int port, const char *loginName, const char *password) { return -1; };
		virtual int RegisterMarket(const char *quotationCode,  bool enable = true) { return -1; };
	};

	
	QUOTATION_API_IMPORT QuotationApi   *AllocQuotationApi();
	QUOTATION_API_IMPORT void            FreeQuotationApi(QuotationApi *api);
}

QUOTATION_API_C_DECLARE_END

#endif  //  QUOTATION_API_H