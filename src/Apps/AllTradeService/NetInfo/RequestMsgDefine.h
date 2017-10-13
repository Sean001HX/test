/*
* Purpose: 网络交互通讯的通讯协议相关宏、枚举、结构等定义;
*/

#ifndef  __REQUESTMSG_DEFINE_H__
#define  __REQUESTMSG_DEFINE_H__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif

#include <string>
#include <memory>

class TCPImpl;

namespace xyc_communication
{
    // 通信消息类型定义
    enum E_COMM_MSG_TYPE_TAG : unsigned short
    {
        MSG_USER_CONNECT = 0,   	// 用户连接
        MSG_USER_CONNECT_RES,		// 连接回应
        MSG_USER_LOGIN,			    // 用户登录
        MSG_USER_LOGIN_RES,			// 登录回应
        MSG_USER_LOGOUT,			// 用户登出
        MSG_NORMAL_RESPONSE,		// 通用回应消息
        MSG_COMM_MAX
    };

    // 以上消息中信息单元(IE)的类型定义
    enum E_COMM_IE_TYPE : unsigned short
    {
        IE_COMM_Invalid = 0,
        IE_USER_NAME=1,				// 用户的登录名
        IE_USER_PASSWORD,			// 用户的登录密码
        IE_USER_OTHERS,				// 用户的其他信息
        IE_USER_LOGIN_RES,			// 用户登录回应
        IE_NORMAL_RESPONSE,			// 通用回应参数
        IE_COMM_MaxCount,
    };

    const int comm_resed_len = 6;

    // 当前协议版本号
#define COMM_MSG_VER			    ((unsigned short)0x0001)

    // 消息中传输的日期时间字符串的长度
#define MSG_DATE_TIME_LEN		    19

#define MSG_MAX_NAME_LEN			32
#define MSG_MAX_GUID_LEN			40

    struct Request
    {
        std::string	    login_name_;	    // 登录名
        std::string	    command_;	        // 消息中命令码: "1001"、"2001"...
        std::string	    parameters_;	    // 消息内容
        int             socketDescriptor_;  // socket套接字ID
        TCPImpl*        session_ptr_;

        Request()
            : socketDescriptor_(0)
            , session_ptr_(nullptr)
        {}

        void clear()
        {
            login_name_.clear();
            command_.clear();
            parameters_.clear();
            socketDescriptor_ = 0;
            session_ptr_ = nullptr;
        }
    };

    typedef std::shared_ptr<Request>		RequestPtr;

} // namespace xyc_communication

#endif // __REQUESTMSG_DEFINE_H__
