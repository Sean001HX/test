#ifndef NET_OBJECT_CALLBACK_H
#define NET_OBJECT_CALLBACK_H


namespace NetGateway
{
	namespace Server
	{
		class CNetObjectCallback
		{
		public:
			virtual ~CNetObjectCallback() {};
			//  新连接回调
			//  @peer_addrs： 对端ip地址 "xxx.xxx.xxx.xxx", 
			//  @peer_port:  对端端口
			virtual bool OnNewConnection(CNetObjectCallback *pHandler, const char *peer_addrs) = 0;
			//  返回发送回调
			//  @pHandler：通信访问够句柄
			//  @bytes_to_send: 要发送的字节数
			//  @bytes_sent: 实际发送字节数
			virtual void OnWrite(CNetObjectCallback *handler, int bytes_to_send, int bytes_sent) = 0;

			//  收到数据回调
			//  @pHandler：通信访问够句柄
			//  @read_buf: 已收到数据缓冲区，
			//  @bytes_received: 已收到的字节数
			virtual void OnRead(CNetObjectCallback *handler, const char *read_buf, int bytes_received) = 0;

			//  掉线回调
			//  @pHandler：通信访问够句柄
			virtual void OnDisconnected(CNetObjectCallback *handler) = 0;
		};
	}
}


#endif  //  NET_OBJECT_CALLBACK_H