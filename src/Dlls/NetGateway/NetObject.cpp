#include "stdafx.h"
#include "NetObject.h"
#include "NetCommHandle.h"
#include "ace/Guard_T.h"
#include "proto_head.hpp"
#include "include/NetGateway/net_gateway_errors.h"
#include "net_gateway_proto_code.h"
#include <assert.h>
#include "include/NetGateway/net_gateway_interface_def.h"
#include "GlobaData.h"
#include "c:/ng_tools/ng_header_for_log4cxx/ng_header_for_log4cxx.hpp"
#include "C:/ng_tools/ng_header_for_log4cxx/ng_header_for_log4cxx_log_var.hpp"

NG_LOGGER(logger, "NetGateway::Server::CNetObject");

namespace NetGateway
{
	namespace Server
	{
		bool CNetObject::OnNewConnection(NetCommHandle *pHandler, const char *peer_addrs)
		{
// 			LOG4CXX_TRACE(logger, "OnNewConnection"
// 				LOG_VAR(pHandler)
// 				LOG_VAR(peer_addrs)
// 				);
			if (!pHandler)
				return false;

			if (!net_comm_handle_)      //   未加锁验证
			{
				ACE_Guard<ACE_Recursive_Thread_Mutex> mon(mutex_net_object_, true);
				if (!net_comm_handle_)  //   加锁验证
				{
					if (0 == recv_buf_)
					{
						recv_buf_ = new (std::nothrow) char[MAX_SERVER_PACKET_SIZE];
						if (0 == recv_buf_)
						{
							LOG4CXX_FATAL(logger, "recv_buf_ = new (std::nothrow) char[MAX_SERVER_PACKET_SIZE];");
							return false;
						}
					}
					//  分配成功
					Reset();
					_snprintf_s(peer_addr_, sizeof(peer_addr_) - 1, "%s", peer_addrs);
					net_comm_handle_ = pHandler;
					last_heart_beat_time_ = time(0);
					InitCommSeed(pHandler);
					return true;
				}
			}
			LOG4CXX_ERROR(logger, "OnNewConnection"
				LOG_VAR(pHandler)
				LOG_VAR(peer_addrs)
				);
			//   分配失败
			return false;
		}

		void CNetObject::OnWrite(NetCommHandle *handler, int bytes_to_send, int bytes_sent)
		{
			LOG4CXX_TRACE(logger, "OnWrite"
				LOG_VAR(handler)
				LOG_VAR(bytes_to_send)
				LOG_VAR(bytes_sent)
				);
		}

		void CNetObject::OnRead(NetCommHandle *handler, const char *read_buf, int bytes_received)
		{
// 			LOG4CXX_TRACE(logger, "OnRead"
// 				LOG_VAR(handler)
// 				LOG_VAR(bytes_received)
// 				);

			if (bytes_received <= 0)
			{
				LOG4CXX_ERROR(logger, "OnRead"
					LOG_VAR(handler)
					LOG_VAR(bytes_received)
					);
				return;
			}

			if (handler != net_comm_handle_)
			{
				LOG4CXX_ERROR(logger, "OnRead():handler != net_comm_handle_"
					LOG_VAR(handler)
					LOG_VAR(bytes_received)
					LOG_VAR(net_comm_handle_)
					);
				if (handler)
					handler->CloseConnection();

				return;
			}
				
			ACE_Guard<ACE_Recursive_Thread_Mutex> mon(mutex_net_object_, true);

			if (net_comm_handle_ && net_comm_handle_ == handler)
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
					if (phead->user_data_len_ < 0 || phead->user_data_len_ > MAX_SERVER_PACKET_SIZE - sizeof(CProtoHead))
					{
						//  错误包
						LOG4CXX_ERROR(logger, "收到异常数据包"
							LOG_VAR(phead->net_command_)
							LOG_VAR(phead->user_data_len_)
							LOG_VAR(peer_addr_)
							);
						auto tmp_seed = seed_;
						CloseConnection(handler);
						if (tmp_seed && CGlobaData::Instance()->Callback())
						{
							CGlobaData::Instance()->Callback()->OnDisconnect(index_, handler);
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
							if (phead->seed_ == seed_new_)
							{
								seed_ = seed_new_;
								seed_new_ = 0;

								LOG4CXX_TRACE(logger, "新连接验证成功"
									LOG_VAR(handler)
									LOG_VAR(peer_addr_)
									);

								//  新连接验证成功， 回调给用户
								if (CGlobaData::Instance()->Callback())
								{
									CGlobaData::Instance()->Callback()->OnNewConnection(index_, handler);
								}

								unparsed_data_len_ = 0;
								last_heart_beat_time_ = time(0);
								continue;
							}
							else
							{
								LOG4CXX_WARN(logger, "新连接验证失败"
									LOG_VAR(handler)
									LOG_VAR(peer_addr_)
									);
								auto tmp_seed = seed_;
								CloseConnection(handler);
								if (tmp_seed && CGlobaData::Instance()->Callback())
								{
									CGlobaData::Instance()->Callback()->OnDisconnect(index_, handler);
								}

								return;
							}
						}
						
						
						else  //  用户层协议
						{

						}
						//   去掉未验证成功的数据包
						if (!seed_)
						{
							LOG4CXX_WARN(logger, "收到未验证的用户数据包"
								LOG_VAR(handler)
								LOG_VAR(peer_addr_)
								);
							CloseConnection(handler);
						
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
							CloseConnection(handler);
							if (tmp_seed && CGlobaData::Instance()->Callback())
							{
								CGlobaData::Instance()->Callback()->OnDisconnect(index_, handler);
							}

							return;
						}

						DispatchPacket(phead->net_command_, recv_buf_ + sizeof(CProtoHead), phead->user_data_len_);
						unparsed_data_len_ = 0;
					}
				}	
			}
		}

		void CNetObject::OnDisconnected(NetCommHandle *handler)
		{
			LOG4CXX_TRACE(logger, "OnDisconnected"
				LOG_VAR(handler)
				LOG_VAR(peer_addr_)
				);
			if (handler != net_comm_handle_)
				return;

			ACE_Guard<ACE_Recursive_Thread_Mutex> mon(mutex_net_object_, true);
			if (handler == net_comm_handle_)
			{
				if (seed_ && CGlobaData::Instance()->Callback())
				{
					CGlobaData::Instance()->Callback()->OnDisconnect(index_, handler);
				}
				Reset();
			}
		}

		void CNetObject::InitCommSeed(NetCommHandle *handler)
		{
			LOG4CXX_TRACE(logger, "InitCommSeed"
				LOG_VAR(handler)
				LOG_VAR(peer_addr_)
				);
			if (net_comm_handle_ != handler)
				return;

			ACE_Guard<ACE_Recursive_Thread_Mutex> mon(mutex_net_object_, true);
			if (net_comm_handle_ != handler)
				return;

			seed_new_ = rand();
			while (seed_new_ < 256)
			{
				LOG4CXX_TRACE(logger, "while (!seed_new_)");
				seed_new_ = rand();
			}

			seed_generate_time_ = time(0);
			__SendImp(NetGateway_InitSeed, 0, 0);
		}

		void CNetObject::Reset()
		{
			net_comm_handle_ = 0;
			seed_ = 0;
			seed_new_ = 0;
			last_heart_beat_time_ = 0;
			seed_generate_time_ = 0;
			unparsed_data_len_ = 0;
		}

		int CNetObject::Send(NetCommHandle *netObject, unsigned short netCommand, const void *buf, int bufLen)
		{
			if (netObject != net_comm_handle_)  //  无加锁验证
			{
				return ConnectionDisconnected;
			}
			ACE_Guard<ACE_Recursive_Thread_Mutex> mon(mutex_net_object_, true);
			if (netObject != net_comm_handle_)  //  加锁验证
			{
				return ConnectionDisconnected;
			}
			
			return __SendImp(netCommand, buf, bufLen);
		}

		int CNetObject::__SendImp(unsigned short netCommand, const void *buf, int bufLen)
		{
			if (bufLen < 0 || bufLen > MAX_CLIENT_PACKET_SIZE - sizeof(CProtoHead) || (!buf && bufLen))
			{
				LOG4CXX_ERROR(logger, "__SendImp()"
					LOG_VAR(netCommand)
					LOG_VAR(buf)
					LOG_VAR(bufLen)
					);
				return InvalidTcpSendParameter;
			}
				

			CProtoHead proto_head = { 0 };
			proto_head.net_command_ = netCommand;
			if (seed_new_)
			{
				proto_head.seed_ = seed_new_;			
			}
			else if (seed_)
			{
				proto_head.seed_ = seed_;
			}
			else
			{
				LOG4CXX_ERROR(logger, "__SendImp()"
					LOG_VAR(netCommand)
					LOG_VAR(buf)
					LOG_VAR(bufLen));
				return ErrorWriteStream;
			}
			proto_head.user_data_len_ = bufLen;
			return net_comm_handle_->Write(proto_head, buf, bufLen);
		}

		int CNetObject::CloseConnection(NetCommHandle *handler)
		{
			if (!handler || handler != net_comm_handle_)
				return NoError;

			ACE_Guard<ACE_Recursive_Thread_Mutex> mon(mutex_net_object_, true);
			if (net_comm_handle_ != handler)
				return NoError;

			handler->CloseConnection();
			Reset();

			return NoError;
		}

		void CNetObject::DispatchPacket(unsigned short netCommand, void *buf, int bufLen)
		{
			if (NetCommandUserBase <= netCommand)
			{
				//  用户协议
				if (CGlobaData::Instance()->Callback())
				{
					CGlobaData::Instance()->Callback()->OnRecv(index_, net_comm_handle_, netCommand, (char*)buf, bufLen);
				}
				return;
			}

			//  网络模块协议
			switch (netCommand)
			{
			case NetGateway_HeartBeat:
				HandleHeartBeat();
				break;
			default:
				break;
			}
		}

		NetCommHandle * CNetObject::Handler() const
		{
			return net_comm_handle_;
		}

		void CNetObject::CheckHeartBeat(unsigned nowTime)
		{
			if (!net_comm_handle_ || !seed_)
				return;

			if (nowTime - last_heart_beat_time_ < 30)
				return;

			ACE_Guard<ACE_Recursive_Thread_Mutex> mon(mutex_net_object_, true);
			//  二次验证
			if (!net_comm_handle_ || !seed_)
				return;

			if (nowTime - last_heart_beat_time_ < 30)
				return;

			

			//  超时处理
			net_comm_handle_->CloseConnection();
			if (CGlobaData::Instance()->Callback())
			{
// 				LOG4CXX_INFO(logger, "CheckHeartBeat()"LOG_VAR(nowTime) LOG_VAR(peer_addr_) LOG_VAR(this) LOG_VAR(net_comm_handle_) LOG_VAR(last_heart_beat_time_));
				CGlobaData::Instance()->Callback()->OnDisconnect(index_, net_comm_handle_);
			}
			Reset();
			
		}

		void CNetObject::HandleHeartBeat()
		{
			last_heart_beat_time_ = time(0);
// 			LOG4CXX_TRACE(logger, "HandleHeartBeat()"LOG_VAR(this) LOG_VAR(last_heart_beat_time_) LOG_VAR(net_comm_handle_) LOG_VAR(peer_addr_) LOG_VAR(index_));
		}

		CNetObject::CNetObject() : recv_buf_(0)
		{

		}

		CNetObject::~CNetObject()
		{
			if (recv_buf_)
				delete [] recv_buf_;
		}

	}  // Server
}  //  NetGateway
