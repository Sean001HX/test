#ifndef DATA_BASE_H_
#define DATA_BASE_H_

#include "StockDllStruct.h"
#include <memory>
#include <map>
#include <vector>

namespace StockDLL{

	class DataBase
	{
	public:
		virtual std::shared_ptr<DLLMoneyInfo> toMoneyInfo(char *result) = 0;

		virtual std::vector<std::shared_ptr<DLLOrderInfo>> toOrderInfo(char *result) = 0;

		//map <orderNo, trade¼¯ºÏ>
		virtual std::map<std::string, std::vector<std::shared_ptr<DLLTradeInfo>>> toTradeInfo(char *result) = 0;

		virtual std::vector < std::shared_ptr<DLLPositionInfo>> toPositionInfo(char *result) = 0;

		virtual std::string getOrderIDFormOrderInsert(char *result) = 0;
	};

} //namespace StockDLL

#endif