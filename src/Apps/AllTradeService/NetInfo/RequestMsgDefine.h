/*
* Purpose: ���罻��ͨѶ��ͨѶЭ����غꡢö�١��ṹ�ȶ���;
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
    // ͨ����Ϣ���Ͷ���
    enum E_COMM_MSG_TYPE_TAG : unsigned short
    {
        MSG_USER_CONNECT = 0,   	// �û�����
        MSG_USER_CONNECT_RES,		// ���ӻ�Ӧ
        MSG_USER_LOGIN,			    // �û���¼
        MSG_USER_LOGIN_RES,			// ��¼��Ӧ
        MSG_USER_LOGOUT,			// �û��ǳ�
        MSG_NORMAL_RESPONSE,		// ͨ�û�Ӧ��Ϣ
        MSG_COMM_MAX
    };

    // ������Ϣ����Ϣ��Ԫ(IE)�����Ͷ���
    enum E_COMM_IE_TYPE : unsigned short
    {
        IE_COMM_Invalid = 0,
        IE_USER_NAME=1,				// �û��ĵ�¼��
        IE_USER_PASSWORD,			// �û��ĵ�¼����
        IE_USER_OTHERS,				// �û���������Ϣ
        IE_USER_LOGIN_RES,			// �û���¼��Ӧ
        IE_NORMAL_RESPONSE,			// ͨ�û�Ӧ����
        IE_COMM_MaxCount,
    };

    const int comm_resed_len = 6;

    // ��ǰЭ��汾��
#define COMM_MSG_VER			    ((unsigned short)0x0001)

    // ��Ϣ�д��������ʱ���ַ����ĳ���
#define MSG_DATE_TIME_LEN		    19

#define MSG_MAX_NAME_LEN			32
#define MSG_MAX_GUID_LEN			40

    struct Request
    {
        std::string	    login_name_;	    // ��¼��
        std::string	    command_;	        // ��Ϣ��������: "1001"��"2001"...
        std::string	    parameters_;	    // ��Ϣ����
        int             socketDescriptor_;  // socket�׽���ID
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
