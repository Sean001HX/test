#include "CommmsgDefine.h"

namespace xyc_communication
{
	// 命令消息头
	const char* const gszMsgHeader = "§HX§";

	// '*' + 命令消息头
    const char* const gszMsgStarHeader = "*§HX§";

//     // 回应消息(OK)
//     const char* const gszMsgResponse = "{\"errcode\":\"0\"}";

	// 命令消息结束标志
    const char* const gszMsgEndFlag = "§END§";

} // namespace xyc_communication

