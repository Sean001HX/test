#pragma once

#include "mdl_api_types.h"

namespace datayes {
namespace mdl {
namespace mdl_api_msg {

static const uint16_t MDLVID_MDL_API = 101;

enum MDL_APIMessageID {
	MDLMID_MDL_API_ConnectingEvent = 1,
	MDLMID_MDL_API_ConnectErrorEvent = 2,
	MDLMID_MDL_API_DisconnectedEvent = 3,
	MDLMID_MDL_API_Timer = 4,
	MDLMID_MDL_API_MessageServiceTimeOutEvent = 5,
	MDLMID_MDL_API_MessageDiscardedEvent = 6
};

#pragma pack(1)

struct ConnectingEvent {
	enum {
		ServiceID = MDLSID_MDL_API,
		ServiceVer = MDLVID_MDL_API,
		MessageID = MDLMID_MDL_API_ConnectingEvent
	};
	MDLAnsiString Address;
};

struct ConnectErrorEvent {
	enum {
		ServiceID = MDLSID_MDL_API,
		ServiceVer = MDLVID_MDL_API,
		MessageID = MDLMID_MDL_API_ConnectErrorEvent
	};
	MDLAnsiString ErrorMessage;
	MDLAnsiString Address;
};

struct DisconnectedEvent {
	enum {
		ServiceID = MDLSID_MDL_API,
		ServiceVer = MDLVID_MDL_API,
		MessageID = MDLMID_MDL_API_DisconnectedEvent
	};
	MDLAnsiString ErrorMessage;
	MDLAnsiString Address;
};

struct TimerEvent {
	enum {
		ServiceID = MDLSID_MDL_API,
		ServiceVer = MDLVID_MDL_API,
		MessageID = MDLMID_MDL_API_Timer
	};
	int Dummy;
};

struct MessageServiceTimeOutEvent {
	enum {
		ServiceID = MDLSID_MDL_API,
		ServiceVer = MDLVID_MDL_API,
		MessageID = MDLMID_MDL_API_MessageServiceTimeOutEvent
	};
	MDLAnsiString Address;
	uint32_t SvcID;
};


struct MessageDiscardedEvent {
	enum {
		ServiceID = MDLSID_MDL_API,
		ServiceVer = MDLVID_MDL_API,
		MessageID = MDLMID_MDL_API_MessageDiscardedEvent
	};
	MDLAnsiString Address;
	uint32_t SvcID;
	uint32_t MsgID;
};

#pragma pack()

} // namespace mdl_api_msg
} // namespace mdl
} // namespace datayes