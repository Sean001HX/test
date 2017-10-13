/*
* Authors: XuYC
* Purpose: ͨѶ���г����ַ�����ʵ�ֵ�
*/

#ifndef  __COMMMSG_DEFINE_H__
#define  __COMMMSG_DEFINE_H__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif

namespace xyc_communication
{
    // ������Ϣͷ
    extern const char* const gszMsgHeader;			// "��HX��"

    // '*' + ������Ϣͷ
    extern const char* const gszMsgStarHeader;		// "*��HX��"

    // ��Ӧ��Ϣ(OK)
//     extern const char* const gszMsgResponse;		// "{\"errcode\":\"0\"}"

    // ������Ϣ������־
    extern const char* const gszMsgEndFlag;			// "��END��"

} // namespace xyc_communication

#endif //! __COMMMSG_DEFINE_H__