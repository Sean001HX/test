#pragma once

#include "base/base.h"
#include <stdint.h>
#include <stddef.h>
#include <limits.h>
#include <string>

namespace datayes {
namespace mdl {

#pragma pack(1)

static const uint16_t MDL_VERSION = 2111;
static const uint16_t MDL_CLIENT_VERSION = MDL_VERSION;

///////////////////////////////////////////////////////////////////////////////////////////////////////////
// Identify the service (data source)
enum MDLServiceID {
	MDLSID_UNDEFINED = 0,
	MDLSID_MDL_API = 1,		// sent by mdl api to report network events
	MDLSID_MDL_SYS = 2,		// sent by mdl server accroding to mdl api requests
	MDLSID_MDL_SHL1 = 3,	// the shanghai exchange level1 data source
	MDLSID_MDL_SHL2 = 4,	// the shanghai exchange level2 data source
	MDLSID_MDL_SZL1 = 5,	// the shengzhen exchange level1 data source
	MDLSID_MDL_SZL2 = 6,	// the shengzhen exchange level2 data source
	MDLSID_MDL_CFFEX = 7, 	// CFFEX
	MDLSID_MDL_CZCE = 8,	// CZCE
	MDLSID_MDL_SHFE = 9,	// SHFE
	MDLSID_MDL_DCE = 10,	// DCE
	MDLSID_MDL_HKEX = 11,	// hk exchange data source
	MDLSID_MDL_SWG = 12,	// 
	MDLSID_MDL_BAR = 13,	// 
	MDLSID_SHL1 = 101,	// original data source
	MDLSID_SHL2 = 102,	// original data source
	MDLSID_SZL1 = 103,	// original data source
	MDLSID_SZL2 = 104,	// original data source
	MDLSID_HKEX = 105,	// original data source
	MDLSID_MAX = 256	// maximum service id
};
 
///////////////////////////////////////////////////////////////////////////////////////////////////////////
// Identify the service version
// 00.00.0 major.minor.revision
struct MDLServiceVersion {
	uint16_t GetMajorVersion() const {
		return m_Value / 1000;
	}
	uint8_t GetMinorVersion() const {
		return m_Value % 1000 / 10;
	}
	uint8_t GetRevision() const {
		return m_Value % 10;
	}
	uint16_t m_Value;
};
static const uint16_t MDLVID_MAX = 65535;

///////////////////////////////////////////////////////////////////////////////////////////////////////////
// Message ID is defined by individual service
static const uint16_t MDLMID_MAX = 65535;

///////////////////////////////////////////////////////////////////////////////////////////////////////////
// The encoding type of message body
enum MDLMessageEncoding {
	MDLEID_UNDEFINED = 0,
	MDLEID_BINARY = 1,	
	MDLEID_FAST = 2,	
	MDLEID_JSON = 3,
	MDLEID_PROTOBUF = 4,
	MDLEID_CSV = 5,
	MDLEID_MKTDATA = 6,
	MDLEID_DEFLATE = 0x80,
	MDLEID_DEFLATE_PROTOBUF = 0x84
};

enum MDLCompressEncoding {
	MDLCE_NONE = 0,
	MDLCE_DEFLATE_STREAM = 1,	
	MDLCE_DEFLATE = 2,
	MDLCE_GZIP = 3
};

enum MDLTextCharset {
	MDLTC_ASIIC = 0,
	MDLTC_UTF8 = 1,	
	MDLTC_GB2312 = 2
};

enum MDLErrorCode {
	MDLEC_OK = 0, 
	MDLEC_INVALID_SVR_ID = 1, 
	MDLEC_INVALID_MSG_ID = 2, 
	MDLEC_INVALID_SVR_VERSION = 3,
	MDLEC_INVALID_PASSWD = 4,
	MDLEC_UNAUTHORIZED = 5,
	MDLEC_TOO_MANY_USERS = 6,
	MDLEC_NO_RESOURCE = 7,
	MDLEC_INVALID_FIELDNAME = 8,
	MDLEC_INVALID_PARAMETER = 9,
	MDLEC_UNDEFINED = 10,
	MDLEC_TIMEOUT = 11,
	MDLEC_PENDING = 12,
	MDLEC_TOO_MANY_REQUEST = 13,
	MDLEC_BUSY = 14
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////
// A list contains items with same type
struct MDLList {
	uint32_t Length;
	uint32_t Offset;
};

template <class T>
struct MDLListT : public MDLList {
	const T* operator [](size_t i) const {
		if (Offset != 0 && i < (size_t)Length) {
			return (const T*)((char*)this + Offset) + i;
		}
		return 0;
	}
	T* operator [](size_t i) {
		if (Offset != 0 && i < (size_t)Length) {
			return (T*)((char*)this + Offset) + i;
		}
		return 0;
	}
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////
// yyyymmdd
struct MDLDate {
	uint16_t GetYear() const {
		return m_Value / 10000;
	}
	uint8_t GetMonth() const {
		return m_Value % 10000 / 100;
	}
	uint8_t GetDay() const {
		return m_Value % 100;
	}
	uint32_t m_Value;
};

// hhmmssmmm
struct MDLTime {
	uint8_t GetHour() const {
		return m_Value % 1000000000 / 10000000;
	}
	uint8_t GetMinute() const {
		return m_Value % 10000000 / 100000;
	}
	uint8_t GetSecond() const {
		return m_Value % 100000 / 1000;
	}
	uint16_t GetMilliSec() const {
		return m_Value % 1000;
	}
	uint32_t m_Value;
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////
extern "C" uint32_t DTAPIDLLCALL DllConvertUTF8ToAnsi(const char* putf8, uint32_t cutf8, char* pansi, uint32_t cansi);
extern "C" uint32_t DTAPIDLLCALL DllConvertAnsiToUTF8(const char* pansi, uint32_t cansi, char* putf8, uint32_t cutf8);

struct MDLString {
	uint16_t Length;
	uint32_t Offset;
}; 

// 7 bit ASIIC character string
struct MDLAnsiString : public MDLString {
	char* c_str() const {
		if (Offset != 0 && Length != 0) {
			return (char*)this + Offset;
		}
		return (char*)"";		
	}
	std::string std_str() const {
		if (Offset != 0 && Length != 0) {
			return std::string((char*)this + Offset, Length);
		}
		return std::string();	
	}
	std::string ToUTF8() const {
		if (Offset != 0 && Length != 0) {
			uint32_t cansi = Length;
			const char* pansi = (const char*)this + Offset;
			std::string ret(cansi, ' ');
			uint32_t c = DllConvertAnsiToUTF8(pansi, cansi, (char*)ret.c_str(), (uint32_t)ret.size());
			if (c > ret.size()) {
				ret.resize(c);
				c = DllConvertAnsiToUTF8(pansi, cansi, (char*)ret.c_str(), (uint32_t)ret.size());
			}
			ret.resize(c);
			return ret;
		}
		return std::string();	
	}
};

// zn-CH UTF8 string
struct MDLUTF8String : public MDLString {
	char* c_str() const {
		if (Offset != 0 && Length != 0) {
			return (char*)this + Offset;
		}
		return (char*)"";		
	}
	std::string std_str() const {
#ifdef __linux__
		if (Offset != 0 && Length != 0) {
			return std::string((char*)this + Offset, Length);
		}
		return std::string();	
#else
		return ToAnsi();
#endif
	}
	std::string ToAnsi() const {
		if (Offset != 0 && Length != 0) {
			uint32_t cutf8 = Length;
			const char* putf8 = (const char*)this + Offset;
			std::string ret(cutf8, ' ');
			uint32_t c = DllConvertUTF8ToAnsi(putf8, cutf8, (char*)ret.c_str(), (uint32_t)ret.size());
			if (c > ret.size()) {
				ret.resize(c);
				c = DllConvertUTF8ToAnsi(putf8, cutf8, (char*)ret.c_str(), (uint32_t)ret.size());
			}
			ret.resize(c);
			return ret;
		}
		return std::string();	
	}
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////
inline int GetDecimalShiftByPlacement(uint32_t decPlace) {
	static const int s_DecimalShift[] = {1, 10, 100, 1000, 10000, 100000, 1000000, 10000000, 100000000};
	if (decPlace < sizeof(s_DecimalShift) / sizeof(s_DecimalShift[0])) {
		return s_DecimalShift[decPlace];
	}
	int shift = 1;
	for (uint32_t i = 0; i < decPlace; ++i) {
		shift *= 10;
	}
	return shift;
}

template <uint32_t decPlace>
struct MDLFloatT {
	uint32_t GetDecimalPlace() const {
		return decPlace;
	}
	int GetDecimalShift() const {
		return GetDecimalShiftByPlacement(decPlace);
	}
	float GetFloat() const {
		if (m_Value == INT_MIN) {
			return 0.0f;
		}
		else {
			return (m_Value / GetDecimalShift()) + (float)(m_Value % GetDecimalShift()) / GetDecimalShift();
		}
	} 
	bool IsNull() const {
		return m_Value == INT_MIN;
	}
	int32_t m_Value;
};

template <uint32_t decPlace>
struct MDLDoubleT { 
	uint32_t GetDecimalPlace() const {
		return decPlace;
	}
	uint32_t GetDecimalShift() const {
		return GetDecimalShiftByPlacement(decPlace);
	}
	double GetDouble() const {
		if (m_Value == LLONG_MIN) {
			return 0.0f;
		}
		else {
			return (m_Value / GetDecimalShift()) + (double)(m_Value % GetDecimalShift()) / GetDecimalShift();
		}
	} 
	bool IsNull() const {
		return m_Value == LLONG_MIN;
	}
	int64_t m_Value;
};


/////////////////////////////////////////////////////////////////////////////////////////////////////////// 

struct MDLMessageHead {
  uint8_t			HeadSize;			// head size, 
  uint32_t			MessageSize;		// head size + body size
  uint8_t			MessageEncoding;	// enum MDLMessageEncoding
  uint8_t			ServiceID;			// enum MDLServiceID
  MDLServiceVersion	ServiceVersion;		//
  uint16_t			MessageID;			// enum MDLMessageID
  MDLTime			LocalTime;			// message creation time
  uint64_t			SequenceID;			// per message sequence ID
};

#pragma pack()
 

}
}
