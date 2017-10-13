#ifndef NET_GATEWAY_MACROS_H
#define NET_GATEWAY_MACROS_H

#define  NET_ADDR_BUF_LEN					32                            // �����ַ����������

#ifndef USE_FOR_CLIENT_ONLY
#define MAX_NET_OBJECT_LIMIT				10000                         // ����ģ�����������������
#else
#define MAX_NET_OBJECT_LIMIT				1                        // ����ģ�����������������
#endif

#define CONNECT_TRY_TIMES					MAX_NET_OBJECT_LIMIT          // �����ӵ���ʱ���Է������������

#define TCP_RECV_DATA						2048                          // ����TCP�첽���ջ�������
				
#define MAX_SERVER_PACKET_SIZE			    (64 * 1024)                   // ������������յĵ������ݰ���󳤶�

#define MAX_CLIENT_PACKET_SIZE              (32 * 1024)                   // �ͻ���������յĵ������ݰ���󳤶�

#define NET_PROTO_HEAD_LEN                  16                            // ����Э��ͷԤ������

#define NET_CLIENT_OBJECTS_LIMIT            1000                          // ��Ϊ�ͻ���ʹ��ʱ�� ����ͬʱ��������Ӹ���

#endif // !NET_GATEWAY_MACROS_H
