//  网络通信包协议头

#ifndef PROTO_HEAD_HPP
#define PROTO_HEAD_HPP

namespace NetGateway
{

#pragma pack(push, 1)

	class CProtoHead
	{
	public:
		unsigned short net_command_;   //  网络功能码
		unsigned short seed_;          //  通信种子
		int user_data_len_;            //  用户数据长度
		int crc_;                      //  校验码
	};

#pragma pack(pop)
}


#endif  //  PROTO_HEAD_HPP