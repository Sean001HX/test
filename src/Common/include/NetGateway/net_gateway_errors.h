#ifndef NET_GATEWAY_ERRORS_H
#define NET_GATEWAY_ERRORS_H


namespace NetGateway
{
	enum
	{
		NoError,                                    //  正常
		CommError,                                  //  通用错误
		ConnectionDisconnected,                     //  连接已断开
		InvalidTcpSendParameter,                    //  发送网络数据包参数无效
		ErrorWriteStream,                           //  写数据流失败
		ConnectionUnverified,                       //  连接处于未验证状态
		ConnectAgain,                               //  连接操作已发起 
		NonCallbackRegistered,                      //  未注册回调
	};
}

#endif  // NET_GATEWAY_ERRORS_H