#ifndef API_GETWAY_STOCK_H
#define API_GETWAY_STOCK_H

#ifdef APIGETAWAY_EXPORTS
#define APIGETAWAY_API __declspec(dllexport)
#else
#define APIGETAWAY_API __declspec(dllimport)
#endif

class api_getaway_stock
{
public:
	api_getaway_stock();
	~api_getaway_stock();
};
#endif
