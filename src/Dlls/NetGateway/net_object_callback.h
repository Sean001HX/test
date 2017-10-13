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
			//  �����ӻص�
			//  @peer_addrs�� �Զ�ip��ַ "xxx.xxx.xxx.xxx", 
			//  @peer_port:  �Զ˶˿�
			virtual bool OnNewConnection(CNetObjectCallback *pHandler, const char *peer_addrs) = 0;
			//  ���ط��ͻص�
			//  @pHandler��ͨ�ŷ��ʹ����
			//  @bytes_to_send: Ҫ���͵��ֽ���
			//  @bytes_sent: ʵ�ʷ����ֽ���
			virtual void OnWrite(CNetObjectCallback *handler, int bytes_to_send, int bytes_sent) = 0;

			//  �յ����ݻص�
			//  @pHandler��ͨ�ŷ��ʹ����
			//  @read_buf: ���յ����ݻ�������
			//  @bytes_received: ���յ����ֽ���
			virtual void OnRead(CNetObjectCallback *handler, const char *read_buf, int bytes_received) = 0;

			//  ���߻ص�
			//  @pHandler��ͨ�ŷ��ʹ����
			virtual void OnDisconnected(CNetObjectCallback *handler) = 0;
		};
	}
}


#endif  //  NET_OBJECT_CALLBACK_H