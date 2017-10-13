#ifndef NET_GATEWAY_PROTO_CODE_H
#define NET_GATEWAY_PROTO_CODE_H

namespace NetGateway
{
	//  网络模块内部协议功能码
	enum
	{
		NetGateway_InitSeed = 1,      //  初始化通信种子
		NetGateway_HeartBeat,         //  连接心跳包
	};
}


#endif  // NET_GATEWAY_PROTO_CODE_H