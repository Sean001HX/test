/*
* Authors: XuYC
* Purpose: 通讯所有常量字符串的实现等
*/

#ifndef  __COMMMSG_DEFINE_H__
#define  __COMMMSG_DEFINE_H__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif

namespace xyc_communication
{
    // 命令消息头
    extern const char* const gszMsgHeader;			// "§HX§"

    // '*' + 命令消息头
    extern const char* const gszMsgStarHeader;		// "*§HX§"

    // 回应消息(OK)
//     extern const char* const gszMsgResponse;		// "{\"errcode\":\"0\"}"

    // 命令消息结束标志
    extern const char* const gszMsgEndFlag;			// "§END§"

} // namespace xyc_communication

#endif //! __COMMMSG_DEFINE_H__