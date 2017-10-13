//   ����ͨ��ģ��ӿ�����


#ifndef NET_GATEWAY_INTERFACE_DEF_H
#define NET_GATEWAY_INTERFACE_DEF_H



namespace NetGateway
{
	namespace Server
	{
		enum
		{
			NetCommandUserBase = 1024  /*���繦������ʼ��*/
		};
		//  
		class NetCommHandle;
		//  ����ģ��ص��ӿ�
		class CNetCallback
		{
		public:
			virtual ~CNetCallback() {};

			//   �����ӵ���ʱ��֪ͨ�ص�
			//   connectionID�����Ӷ���ID
			//   net_object: ���Ӷ���handle
			virtual void OnNewConnection(int connectionID, NetCommHandle *netObject) {};

			//   ���ӶϿ�
			virtual void OnDisconnect(int connectionID, NetCommHandle *netObject) {};

			//   �յ����ݻص�
			virtual void OnRecv(int connectionID, NetCommHandle *netObject, short netCommand, char *buf, int bufLen) {};

			//   �������ݻص�
			virtual void OnSend(int connectionID, NetCommHandle *netObject) {};
		};

		//   ����ģ��ʵ��
		class CNetHandler
		{
		public:
			virtual ~CNetHandler() {};

			// ��ʼ�������Ӷ���
			virtual void InitNewConnect(int connectionID, NetCommHandle *netObject) {};

			// �����Ͽ�����
			virtual void CloseConnection(int connectionID, NetCommHandle *netObject) {};

			// ��������
			virtual int Send(int connectionID, NetCommHandle *netObject, short netCommand, const void *buf, int bufLen) = 0;

			// ��������״̬
			// option: ״̬ѡ��
			//  args:  ѡ�����
			virtual int SetConnectionStatus(int connectionID, NetCommHandle *netObject, int option, void *args) = 0;

			// ���õ�¼״̬
			virtual int SetLoginStatus(int connectionID, NetCommHandle *netObject, int userID = 0) = 0;

			// ��ȡ�Է�IP
			virtual void GetPeerAddress(int connectionID, NetCommHandle *netObject, char *addressBuf, int bufLen) {};
		};

	}
	
}





#endif  //  NET_GATEWAY_INTERFACE_DEF_H