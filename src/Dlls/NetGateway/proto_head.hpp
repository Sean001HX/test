//  ����ͨ�Ű�Э��ͷ

#ifndef PROTO_HEAD_HPP
#define PROTO_HEAD_HPP

namespace NetGateway
{

#pragma pack(push, 1)

	class CProtoHead
	{
	public:
		unsigned short net_command_;   //  ���繦����
		unsigned short seed_;          //  ͨ������
		int user_data_len_;            //  �û����ݳ���
		int crc_;                      //  У����
	};

#pragma pack(pop)
}


#endif  //  PROTO_HEAD_HPP