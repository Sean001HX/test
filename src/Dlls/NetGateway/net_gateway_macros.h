#ifndef NET_GATEWAY_MACROS_H
#define NET_GATEWAY_MACROS_H

#define  NET_ADDR_BUF_LEN					32                            // 网络地址缓冲区长度

#ifndef USE_FOR_CLIENT_ONLY
#define MAX_NET_OBJECT_LIMIT				10000                         // 网络模块所允许的连接上限
#else
#define MAX_NET_OBJECT_LIMIT				1                        // 网络模块所允许的连接上限
#endif

#define CONNECT_TRY_TIMES					MAX_NET_OBJECT_LIMIT          // 新连接到来时尝试分配次数的上限

#define TCP_RECV_DATA						2048                          // 单次TCP异步接收缓冲区度
				
#define MAX_SERVER_PACKET_SIZE			    (64 * 1024)                   // 服务器允许接收的单个数据包最大长度

#define MAX_CLIENT_PACKET_SIZE              (32 * 1024)                   // 客户端允许接收的单个数据包最大长度

#define NET_PROTO_HEAD_LEN                  16                            // 网络协议头预留长度

#define NET_CLIENT_OBJECTS_LIMIT            1000                          // 作为客户端使用时， 允许同时发起的连接个数

#endif // !NET_GATEWAY_MACROS_H
