//   网络通信模块接口声明


#ifndef NET_GATEWAY_INTERFACE_DEF_H
#define NET_GATEWAY_INTERFACE_DEF_H



namespace NetGateway
{
	namespace Server
	{
		enum
		{
			NetCommandUserBase = 1024  /*网络功能码起始点*/
		};
		//  
		class NetCommHandle;
		//  网络模块回调接口
		class CNetCallback
		{
		public:
			virtual ~CNetCallback() {};

			//   新连接到来时的通知回调
			//   connectionID：连接对象ID
			//   net_object: 连接对象handle
			virtual void OnNewConnection(int connectionID, NetCommHandle *netObject) {};

			//   连接断开
			virtual void OnDisconnect(int connectionID, NetCommHandle *netObject) {};

			//   收到数据回调
			virtual void OnRecv(int connectionID, NetCommHandle *netObject, short netCommand, char *buf, int bufLen) {};

			//   发送数据回调
			virtual void OnSend(int connectionID, NetCommHandle *netObject) {};
		};

		//   网络模块实例
		class CNetHandler
		{
		public:
			virtual ~CNetHandler() {};

			// 初始化新连接对象
			virtual void InitNewConnect(int connectionID, NetCommHandle *netObject) {};

			// 主动断开连接
			virtual void CloseConnection(int connectionID, NetCommHandle *netObject) {};

			// 发送数据
			virtual int Send(int connectionID, NetCommHandle *netObject, short netCommand, const void *buf, int bufLen) = 0;

			// 设置连接状态
			// option: 状态选项
			//  args:  选项参数
			virtual int SetConnectionStatus(int connectionID, NetCommHandle *netObject, int option, void *args) = 0;

			// 设置登录状态
			virtual int SetLoginStatus(int connectionID, NetCommHandle *netObject, int userID = 0) = 0;

			// 获取对方IP
			virtual void GetPeerAddress(int connectionID, NetCommHandle *netObject, char *addressBuf, int bufLen) {};
		};

	}
	
}





#endif  //  NET_GATEWAY_INTERFACE_DEF_H