#include "stdafx.h"
#include "ClientObject.h"
#include "ace/Guard_T.h"
#include <assert.h>
#include "ClientConnector.h"
#include "include/NetGateway/net_gateway.h"
#include "net_gateway_proto_code.h"
#include "include/NetGateway/net_gateway_interface_def.h"
#include "c:/ng_tools/ng_header_for_log4cxx/ng_header_for_log4cxx.hpp"
#include "C:/ng_tools/ng_header_for_log4cxx/ng_header_for_log4cxx_log_var.hpp"

NG_LOGGER(logger, "NetGateway::Client::CClientObject");



namespace NetGateway
{
	namespace Client
	{


		void CClientObject::RegisterCallback(CClientCallback *callback)
		{
// 			NGTrace trace(logger,  "RegisterCallback()");

			mutex_client_object_.acquire();

			if (!callback_)
			{
				callback_ = callback;
			}
			else
			{
				LOG4CXX_ERROR(logger, "RegisterCallback()"
					LOG_VAR(callback)
					LOG_VAR(callback_)
					);
			}
			mutex_client_object_.release();
		}

		int CClientObject::Connect(const char *host, int port)
		{
// 			NGTrace trace(logger,  "Connect()");

			ACE_Guard<ACE_Recursive_Thread_Mutex> mon(mutex_client_object_, true);

			if (!callback_)
			{
				LOG4CXX_ERROR(logger, "Connect()未注册回调"
					LOG_VAR(host)
					LOG_VAR(port)
					);
				return NonCallbackRegistered;
			}

			if (connector_)
			{
				LOG4CXX_WARN(logger, "Connect()重复操作"
					LOG_VAR(connector_)
					LOG_VAR(peer_addr_)
					);
				return ConnectAgain;
			}

			_snprintf_s(peer_addr_, sizeof(peer_addr_) - 1, "%s:%d", host, port);

			connector_ = new (std::nothrow) CClientConnector(this);
			if (!connector_)
			{
				LOG4CXX_FATAL(logger, "connector_ = new (std::nothrow) CClientConnector(this);"
					LOG_VAR(peer_addr_)
					);
				return CommError;
			}

		

			if (connector_->Connect(host, port))
			{
				delete connector_;
				connector_ = 0;
				return CommError;
			}
				
			return NoError;
		}

		int CClientObject::Send(short netCommand, const void *buf, int bufLen)
		{
// 			NGTrace trace(logger,  "Send()");
			if (bufLen < 0 || bufLen > MAX_SERVER_PACKET_SIZE - sizeof(CProtoHead) || (!buf && bufLen))
			{
				LOG4CXX_ERROR(logger, "Send()"
					LOG_VAR(netCommand)
					LOG_VAR(bufLen)
					);
				return InvalidTcpSendParameter;
			}
			ACE_Guard<ACE_Recursive_Thread_Mutex> mon(mutex_client_object_, true);

			if (!seed_)
			{
				LOG4CXX_ERROR(logger, "Send()连接未验证"
					LOG_VAR(seed_)
					LOG_VAR(peer_addr_)
					);
				return ConnectionUnverified;
			}

			if (client_handler_)
				return client_handler_->Send(netCommand, buf, bufLen);

			return ConnectionDisconnected;
		}

		void CClientObject::CloseConnection()
		{
// 			NGTrace trace(logger,  "CloseConnection()");
			ACE_Guard<ACE_Recursive_Thread_Mutex> mon(mutex_client_object_, true);

			if (client_handler_)
			{
				client_handler_->CloseConnection();
				client_handler_ = 0;
			}
			Reset();
		}

		void CClientObject::OnConnected(bool is_ok, CClientHandler *client_handler, CClientConnector *connector)
		{
// 			NGTrace trace(logger,  "OnConnected()");
			LOG4CXX_DEBUG(logger, "OnConnected()"
				LOG_VAR(this)
				LOG_VAR(is_ok)
				LOG_VAR(client_handler)
				LOG_VAR(connector)
				);

			ACE_Guard<ACE_Recursive_Thread_Mutex> mon(mutex_client_object_, true);

			//  之前关闭的连接器
			if (connector && connector != connector_)
			{
				return;
			}

			if (connector_)
			{
				//delete connector_;
				connector_ = 0;
			}

			if (is_ok)
			{
				if (!client_handler_)
				{
					Reset();
					client_handler_ = client_handler;
				}
				else
				{
					LOG4CXX_ERROR(logger, "OnConnected()同一对象多次连接"
						LOG_VAR(is_ok)
						LOG_VAR(client_handler)
						);
					client_handler->CloseConnection();
					return;
				}
			}

			if (!is_ok && !client_handler)  //  连接失败
			{
				if (callback_)
				{
					callback_->OnConnected(is_ok);
				}
				else
				{
					LOG4CXX_ERROR(logger, "OnConnected()"
						LOG_VAR(is_ok)
						LOG_VAR(client_handler)
						LOG_VAR(callback_)
						);
				}
			}	
			else if (!is_ok)  //  掉线
			{
				if (client_handler_ == client_handler && callback_)
				{
					callback_->OnConnected(false);
					client_handler_ = 0;
				}
			}
			//  连接成功
		}

		void CClientObject::Reset()
		{
// 			NGTrace trace(logger,  "Reset()");
			seed_ = 0;
			unparsed_data_len_ = 0;
			if (client_handler_)
			{
				client_handler_->CloseConnection();
				client_handler_ = 0;
			}
				
			if (connector_)
			{
				//delete connector_;
				connector_->cancel();
				connector_ = 0;
			}
		}

		void CClientObject::OnRead(CClientHandler *client_handler, const char *read_buf, int bytes_received)
		{
// 			NGTrace trace(logger,  "OnRead()");

 			LOG4CXX_DEBUG(logger, "OnRead()"
 				LOG_VAR(this)
 				LOG_VAR(client_handler)
 				LOG_VAR(client_handler_)
 				LOG_VAR(bytes_received)
 				LOG_VAR(peer_addr_)
 				);

			ACE_Guard<ACE_Recursive_Thread_Mutex> mon(mutex_client_object_, true);
			if (client_handler_ != client_handler)
			{
				LOG4CXX_ERROR(logger, "OnRead()"
					LOG_VAR(client_handler)
					LOG_VAR(client_handler_)
					LOG_VAR(bytes_received)
					LOG_VAR(peer_addr_)
					);
				client_handler->CloseConnection();
				return;
			}

			if (client_handler_)
			{
				int bytes_copied = 0;
				while (true)
				{
					if (unparsed_data_len_ < sizeof(CProtoHead))
					{
						//  构造包头
						if (bytes_received - bytes_copied >= sizeof(CProtoHead) - unparsed_data_len_)
						{
							int delta = sizeof(CProtoHead) - unparsed_data_len_;
							memcpy(recv_buf_ + unparsed_data_len_, read_buf + bytes_copied, delta);
							unparsed_data_len_ = sizeof(CProtoHead);
							bytes_copied += delta;
						}
						else
						{
							//  不足数据包头
							memcpy(recv_buf_ + unparsed_data_len_, read_buf + bytes_copied, bytes_received - bytes_copied);
							unparsed_data_len_ += bytes_received - bytes_copied;
							return;
						}
					}
					CProtoHead *phead = (CProtoHead*)recv_buf_;
					if (phead->user_data_len_ < 0 || phead->user_data_len_ > MAX_CLIENT_PACKET_SIZE - sizeof(CProtoHead))
					{
						//  错误包
						LOG4CXX_ERROR(logger, "收到异常数据包"
							LOG_VAR(phead->net_command_)
							LOG_VAR(phead->user_data_len_)
							);
						auto tmp_seed = seed_;
						CloseConnection();
						client_handler_ = 0;
						if (tmp_seed && callback_)
						{
							callback_->OnConnected(false);
						}

						return;
					}
					//  复制用户数据
					if (bytes_received - bytes_copied < phead->user_data_len_ + sizeof(CProtoHead) - unparsed_data_len_)
					{
						if (bytes_received > bytes_copied)
						{
							memcpy(recv_buf_ + unparsed_data_len_, read_buf + bytes_copied, bytes_received - bytes_copied);
							unparsed_data_len_ += bytes_received - bytes_copied;
						}	
						return;
					}
					else
					{
						if (phead->user_data_len_ + sizeof(CProtoHead) > unparsed_data_len_)
						{
							int delta = phead->user_data_len_ + sizeof(CProtoHead) - unparsed_data_len_;
							memcpy(recv_buf_ + unparsed_data_len_, read_buf + bytes_copied, delta);
							unparsed_data_len_ = phead->user_data_len_ + sizeof(CProtoHead);
							bytes_copied += delta;
						}
						if (NetGateway_InitSeed == phead->net_command_)
						{
							seed_ = phead->seed_;
							if (client_handler->Send(NetGateway_InitSeed, 0, 0))
							{
								LOG4CXX_ERROR(logger, "新连接验证失败"
									LOG_VAR(peer_addr_)
									LOG_VAR(client_handler_)
									);
								CloseConnection();
								return;
							}

							if (callback_)
								callback_->OnConnected(true);
							else
							{
								LOG4CXX_ERROR(logger, "对象没有绑定回调"
									LOG_VAR(peer_addr_)
									LOG_VAR(callback_)
									LOG_VAR(client_handler_)
									);
								CloseConnection();
								return;
							}
							unparsed_data_len_ = 0;
							continue;
						}
						//   去掉未验证成功的数据包
						if (!seed_)
						{
							LOG4CXX_WARN(logger, "收到未验证的用户数据包"
								LOG_VAR(client_handler)
								LOG_VAR(peer_addr_)
								);
							CloseConnection();
							return;
						}

						int crc = 0;  //  校验码
						//  decrypt
						if (phead->user_data_len_ > 0)
						{

							int cycle4 = phead->user_data_len_ >> 2;
							int cycle2 = phead->user_data_len_ & 2;
							int cycle1 = phead->user_data_len_ & 1;
							unsigned short seed2 = (seed_ & 0xff00) | (phead->seed_ & 0xff);
							char seed1 = seed2 & 0xff;
							int seed4 = seed2 << 16 | seed2;
							if (cycle4 > 0)
							{
								for (int i = 0; i < cycle4; ++i)
								{
									int *pint = (int *)(recv_buf_ + sizeof(CProtoHead) + 4 * i);
									*(pint) ^= seed4;
									crc += *pint;
								}
							}
							if (cycle2)
							{
								unsigned short *pshort = (unsigned short *)(recv_buf_ + sizeof(CProtoHead) + 4 * cycle4);
								*(pshort) ^= seed2;
								crc += *pshort;
							}
							if (cycle1)
							{
								char *pchar = recv_buf_ + sizeof(CProtoHead) + 4 * cycle4 + cycle2;
								*(pchar) ^= seed1;
								crc += *pchar;
							}
						}

						if (crc != phead->crc_)
						{
							LOG4CXX_WARN(logger, "收到校验码错误的数据包"
								LOG_VAR(crc)
								LOG_VAR(phead->crc_)
								LOG_VAR(peer_addr_)
								);

							auto tmp_seed = seed_;
							CloseConnection();
							if (tmp_seed && callback_)
							{
								callback_->OnConnected(false);
							}

							return;
						}

						DispatchPacket(phead->net_command_, recv_buf_ + sizeof(CProtoHead), phead->user_data_len_);
						unparsed_data_len_ = 0;
					}
				}
			}
		}

		void CClientObject::Init()
		{
// 			NGTrace trace(logger,  "Init()");
			seed_ = 0;
			unparsed_data_len_ = 0;
			client_handler_ = 0;
			flag_in_use_ = false;
			connector_ = 0;
			callback_ = 0;
			peer_addr_[0] = 0;
		}

		bool CClientObject::Occupy()
		{
// 			NGTrace trace(logger,  "Occupy()");
			if (flag_in_use_)
				return false;

			ACE_Guard<ACE_Recursive_Thread_Mutex> mon(mutex_client_object_, true);

			if (flag_in_use_)
				return false;

			if (0 == recv_buf_)
			{
				recv_buf_ = new (std::nothrow) char[MAX_CLIENT_PACKET_SIZE];
				if (0 == recv_buf_)
				{
					LOG4CXX_FATAL(logger, "recv_buf_ = new (std::nothrow) char[MAX_CLIENT_PACKET_SIZE];");
					return false;
				}
			}

			flag_in_use_ = true;
			peer_addr_[0] = 0;
			return true;
		}

		void CClientObject::Free()
		{
// 			NGTrace trace(logger,  "Free()");
			if (!flag_in_use_)
			{
				LOG4CXX_ERROR(logger, "Free()试图释放一个未被占用的对象");
			}

			ACE_Guard<ACE_Recursive_Thread_Mutex> mon(mutex_client_object_, true);

			flag_in_use_ = false;
			callback_ = 0;
		}

		bool CClientObject::PackData(CProtoHead &proto_head, const char *buf, int bufLen, ACE_Message_Block &rmb)
		{
// 			NGTrace trace(logger,  "PackData()");
			if (!seed_)
				return false;

			proto_head.seed_ = seed_;
			proto_head.user_data_len_ = bufLen;
			if (NetGateway_InitSeed != proto_head.net_command_)
			{
				proto_head.seed_ = seed_ & 0xff00;
				proto_head.seed_ |= (rand() & 0xff);
			}
			
			int cycle4 = bufLen >> 2;
			int cycle2 = bufLen & 2;
			int cycle1 = bufLen & 1;

			ACE_Message_Block *mb = &rmb;
			char *pos_begin = mb->wr_ptr();
			CProtoHead *phead = (CProtoHead *)pos_begin;
			assert(pos_begin);
			mb->copy((char *)&proto_head, sizeof(proto_head));
			mb->copy((char*)buf, bufLen);

			// encrypt
			if (cycle4 > 0)
			{
				int seed4 = proto_head.seed_;
				seed4 <<= 16;
				seed4 |= proto_head.seed_;
				for (int i = 0; i < cycle4; ++i)
				{
					int *ptmp_int = (int *)(pos_begin + sizeof(proto_head) + i * sizeof(int));
					phead->crc_ += *ptmp_int;
					*(ptmp_int) ^= seed4;
				}
			}
			if (cycle2 > 0)
			{
				unsigned short *pshort = (unsigned short *)(pos_begin + sizeof(proto_head) + (cycle4 << 2));
				phead->crc_ += *pshort;
				*(pshort) ^= proto_head.seed_;
			}
			if (cycle1)
			{
				char ch = (char)proto_head.seed_;
				char *pchar = pos_begin + sizeof(proto_head) + (cycle4 << 2) + cycle2;
				phead->crc_ += *pchar;
				*(pchar) ^= ch;
			}

			if (NetGateway_InitSeed != proto_head.net_command_)
				phead->seed_ &= 0xff;

			return true;
		}

		void CClientObject::DispatchPacket(unsigned short netCommand, void *buf, int bufLen)
		{
// 			NGTrace trace(logger,  "DispatchPacket()");
			LOG4CXX_INFO(logger, "DispatchPacket()" LOG_VAR(netCommand) LOG_VAR(peer_addr_) LOG_VAR(bufLen) LOG_VAR(this) LOG_VAR(client_handler_) LOG_VAR(callback_));

			if (Server::NetCommandUserBase <= netCommand)  // 用户协议
			{
				if (callback_)
					callback_->OnRecv(netCommand, (char*)buf, bufLen);
				return;
			}
			//  网络模块协议
		}

		void CClientObject::SendHeartBeat()
		{
// 			NGTrace trace(logger,  "SendHeartBeat()");
			if (!client_handler_ || !seed_)
				return;

			ACE_Guard<ACE_Recursive_Thread_Mutex> mon(mutex_client_object_, true);
			if (!client_handler_ || !seed_)
				return;

			unsigned timeStamp = time(0);
//             OutputDebugString(TEXT("CClientObject::SendHeartBeat()"));
// 			LOG4CXX_TRACE(logger, "SendHeartBeat()" LOG_VAR(timeStamp) );

			int errCode = client_handler_->Send(NetGateway_HeartBeat, 0, 0);
			if (errCode)
			{
				LOG4CXX_INFO(logger, "SendHeartBeat()" LOG_VAR(seed_) LOG_VAR(peer_addr_) LOG_VAR(this) LOG_VAR(client_handler_) LOG_VAR(callback_) LOG_VAR(errCode) );
				CloseConnection();
				if (callback_)
					callback_->OnConnected(false);
			}
		}

		CClientObject::CClientObject() : recv_buf_(0)
		{

		}

		CClientObject::~CClientObject()
		{
			if (recv_buf_)
				delete [] recv_buf_;
		}

	}  //  Client
}  //  NetGateway