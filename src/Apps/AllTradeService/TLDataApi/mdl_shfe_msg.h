// Generated by the code_gen tool.  DO NOT EDIT!
// source: C:/SVN/project/mdl/src/resource/mdl_shfe_msg.xml
// time: 2015/07/04 15:32:55

#pragma once

#include "mdl_api_types.h"

namespace datayes {
namespace mdl {
namespace mdl_shfe_msg {

static const uint16_t MDLVID_MDL_SHFE = 101;

enum MDL_SHFEMessageID {
	MDLMID_MDL_SHFE_CTPFuture = 1
};

#pragma pack(1)

struct CTPFuture {
	enum {
		ServiceID = MDLSID_MDL_SHFE,
		ServiceVer = MDLVID_MDL_SHFE,
		MessageID = MDLMID_MDL_SHFE_CTPFuture
	};
	MDLAnsiString InstruID;
	MDLDoubleT<3> LastPrice;
	MDLDoubleT<3> PreSetPrice;
	MDLDoubleT<3> OpenPrice;
	MDLDoubleT<3> HighPrice;
	MDLDoubleT<3> LowPrice;
	MDLDoubleT<3> Turnover;
	MDLDoubleT<3> OpenInt;
	MDLDoubleT<3> SetPrice;
	MDLDoubleT<3> ULimitPrice;
	MDLDoubleT<3> LLimitPrice;
	MDLDate TradDay;
	MDLDoubleT<3> PreCloPrice;
	int32_t Volume;
	MDLDoubleT<3> ClosePrice;
	MDLDoubleT<3> PreDelta;
	MDLDoubleT<3> CurrDelta;
	MDLTime UpdateTime;
	MDLDoubleT<3> PreOpenInt;
	MDLDoubleT<3> BidPrice1;
	int32_t BidVolume1;
	MDLDoubleT<3> AskPrice1;
	int32_t AskVolume1;
	MDLDoubleT<3> BidPrice2;
	int32_t BidVolume2;
	MDLDoubleT<3> AskPrice2;
	int32_t AskVolume2;
	MDLDoubleT<3> BidPrice3;
	int32_t BidVolume3;
	MDLDoubleT<3> AskPrice3;
	int32_t AskVolume3;
	MDLDoubleT<3> BidPrice4;
	int32_t BidVolume4;
	MDLDoubleT<3> AskPrice4;
	int32_t AskVolume4;
	MDLDoubleT<3> BidPrice5;
	int32_t BidVolume5;
	MDLDoubleT<3> AskPrice5;
	int32_t AskVolume5;
	MDLDoubleT<3> AveragePrice;
	MDLDate ActionDay;
};
 
#pragma pack()

} // namespace mdl_shfe_msg
} // namespace mdl
} // namespace datayes
