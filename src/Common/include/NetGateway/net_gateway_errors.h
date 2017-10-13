#ifndef NET_GATEWAY_ERRORS_H
#define NET_GATEWAY_ERRORS_H


namespace NetGateway
{
	enum
	{
		NoError,                                    //  ����
		CommError,                                  //  ͨ�ô���
		ConnectionDisconnected,                     //  �����ѶϿ�
		InvalidTcpSendParameter,                    //  �����������ݰ�������Ч
		ErrorWriteStream,                           //  д������ʧ��
		ConnectionUnverified,                       //  ���Ӵ���δ��֤״̬
		ConnectAgain,                               //  ���Ӳ����ѷ��� 
		NonCallbackRegistered,                      //  δע��ص�
	};
}

#endif  // NET_GATEWAY_ERRORS_H