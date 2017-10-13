#include "stdafx.h"
#include "ServerTcpService.h"
#include "ace/OS.h"
#include "NetCommHandle.h"
#include "NetObjectMgr.h"
#include "ace/Message_Block.h"
#include "ace/Proactor.h"
#include <new>
#include <assert.h>
#include "net_gateway_proto_code.h"
#include "include/NetGateway/net_gateway_errors.h"
#include "c:/ng_tools/ng_header_for_log4cxx/ng_header_for_log4cxx.hpp"
#include "C:/ng_tools/ng_header_for_log4cxx/ng_header_for_log4cxx_log_var.hpp"

NG_LOGGER(logger, "NetGateway::Server::CServerTcpService");



namespace NetGateway
{
	namespace Server
	{
		class CServerMessageBlock : public ACE_Message_Block
		{
		public:
			CServerMessageBlock(int size = 0) : ACE_Message_Block(size)
			{
// 				LOG4CXX_TRACE(logger, "CServerMessageBlock()"
// 					LOG_VAR(size)
// 					LOG_VAR(this)
// 					);
			}
			~CServerMessageBlock()
			{
/*				LOG4CXX_TRACE(logger, "~CServerMessageBlock()");*/
			}
		};

		CServerTcpService::CServerTcpService() : net_object_(0)
		{
// 			LOG4CXX_TRACE(logger, "CServerTcpService()"
// 				LOG_VAR((NetCommHandle*)this)
// 				);
		}

		CServerTcpService::~CServerTcpService()
		{
// 			LOG4CXX_TRACE(logger, "~CServerTcpService()"
// 				LOG_VAR((NetCommHandle*)this)
// 				);
		}

		void CServerTcpService::open(ACE_HANDLE new_handle, ACE_Message_Block &message_block)
		{
			this->handle(new_handle);
			
			LOG4CXX_TRACE(logger, "open()"
				LOG_VAR(new_handle)
				LOG_VAR(szAddr_peer_)
				);

			// 初始化读数据流
			if (-1 == m_rs.open(*this, new_handle))
			{
				LOG4CXX_ERROR(logger, "open():构造客户读流失败:"
					LOG_VAR(new_handle)
					LOG_VAR(szAddr_peer_)
					);

				delete this;
				ACE_OS::closesocket(new_handle);
				return;
			}

			if (-1 == m_ws.open(*this, new_handle))
			{
				LOG4CXX_ERROR(logger, "open():构造客户写流失败:"
					LOG_VAR(new_handle)
					LOG_VAR(szAddr_peer_)
					);
				
				delete this;
				ACE_OS::closesocket(new_handle);
				return;
			}

			net_object_ = CNetObjectMgr::Instance()->AllocNetObject(this, szAddr_peer_);
			if (!net_object_)
			{
				LOG4CXX_ERROR(logger, "open():分配网络对象失败，连接被拒绝："
					LOG_VAR(szAddr_peer_)
					);
				delete this;
				ACE_OS::closesocket(new_handle);
				return;
			}

			// 如果客户连接时同时提交了数据,则需要伪造一个结果
			if (message_block.length() > 0)
			{
				long long message_block_length = message_block.length();
				LOG4CXX_INFO(logger, LOG_VAR(message_block_length));

				ACE_Message_Block& duplicate = *message_block.duplicate();
				ACE_Asynch_Read_Stream_Result_Impl *fake_result =
					ACE_Proactor::instance()->create_asynch_read_stream_result(this->proxy(),
					this->handle_,
					duplicate,
					TCP_RECV_DATA,
					0,
					ACE_INVALID_HANDLE,
					0,
					0);
				size_t bytes_transferred = message_block.length();
				// Accept事件处理完成，wr_ptr指针会被向前移动，将其移动到开始位置
				duplicate.wr_ptr(duplicate.wr_ptr() - bytes_transferred);

				// 这个方法将调用回调函数
				fake_result->complete(message_block.length(), 1, 0);

				// 销毁伪造的读结果
				delete fake_result;
			}
			else
			{
				if (initiate_read_stream())
				{
					LOG4CXX_ERROR(logger, "初始化客户读流失败"
						LOG_VAR(szAddr_peer_)
						);
					return;
				}
			}

// 			if (net_object_)
// 			{
// 				// 
// 				net_object_->InitCommSeed(this);
// 			}
		}

		void CServerTcpService::handle_read_stream(const ACE_Asynch_Read_Stream::Result &result)
		{
			ACE_Message_Block& mb = result.message_block();
			// 连接关闭
			if (!result.success() || result.bytes_transferred() <= 0) // no data or failed
			{
				mb.release();
				ACE_HANDLE sock_handle = this->handle_;
				NetCommHandle *net_comm_handle = this;
				LOG4CXX_INFO(logger, "[!result.success() || result.bytes_transferred() <= 0]"
					LOG_VAR(net_comm_handle)
					LOG_VAR(sock_handle)
					LOG_VAR(szAddr_peer_)
					);

				auto tmp = net_object_;
				if (tmp)
				{
					net_object_ = 0;
					tmp->OnDisconnected(this);
				}

				delete this;
				if (sock_handle != ACE_INVALID_HANDLE)
				{
					ACE_OS::closesocket(sock_handle);
				}
				return;
			}

			char *szBuf = mb.rd_ptr();
			if (net_object_ && szBuf)
			{
				net_object_->OnRead(this, szBuf, result.bytes_transferred());
			}


			mb.reset();
			if (m_rs.read(mb, mb.size()) == -1)
			{
				LOG4CXX_ERROR(logger, "初始化客户读流失败"
					LOG_VAR(szAddr_peer_)
					);
				mb.release();
				ACE_HANDLE h = this->handle_;
				if (net_object_)
				{
					auto tmp = net_object_;
					net_object_ = 0;
					tmp->OnDisconnected(this);
				}

				delete this;

				if (h != ACE_INVALID_HANDLE)
					ACE_OS::closesocket(h);
 			}
		}

		void CServerTcpService::handle_write_stream(const ACE_Asynch_Write_Stream::Result &result)
		{
			bool success = result.success();
			int bytes_to_send = result.bytes_to_write();
			int bytes_transferrd = result.bytes_transferred();
			LOG4CXX_TRACE(logger, "handle_write_stream()"
				LOG_VAR(success)
				LOG_VAR(bytes_to_send)
				LOG_VAR(bytes_transferrd)
				);

			ACE_Message_Block &mb = result.message_block();
			mb.release();
		}

	
		void CServerTcpService::addresses(const ACE_INET_Addr &remote_address, const ACE_INET_Addr &local_address)
		{
			LOG4CXX_TRACE(logger, "addresses()");
			peer_addr_ = remote_address;
			peer_addr_.addr_to_string(szAddr_peer_, sizeof(szAddr_peer_));
			szAddr_peer_[sizeof(szAddr_peer_) - 1] = 0;
		}

		

		int CServerTcpService::Write(CProtoHead &proto_head, const void *send_buf, int bytes_to_send)
		{
// 			LOG4CXX_TRACE(logger, "Write()"
// 				LOG_VAR(proto_head.net_command_)
// 				LOG_VAR(proto_head.seed_)
// 				LOG_VAR(proto_head.user_data_len_)
// 				);
			int cycle_time_4 = bytes_to_send >> 2;
			int cycle_2 = bytes_to_send & 2;
			int cycle_1 = bytes_to_send & 1;
			if (NetGateway_InitSeed != proto_head.net_command_)
			{
				unsigned short random = rand() & 0xff;
				proto_head.seed_ &= 0xff00;
				proto_head.seed_ |= random;
			}

			//  消息块
			//ACE_Message_Block *mb = new (std::nothrow) ACE_Message_Block(sizeof(proto_head) + bytes_to_send + 1);
			ACE_Message_Block *mb = new (std::nothrow) CServerMessageBlock(sizeof(proto_head) + bytes_to_send + 1);
			if (!mb)
			{
				LOG4CXX_FATAL(logger, "ACE_Message_Block *mb = new (std::nothrow) ACE_Message_Block(bytes_to_send + 1)"
					LOG_VAR(mb)
					);
				return ErrorWriteStream;
			}

			char *pos_begin = mb->wr_ptr();
			CProtoHead *phead = (CProtoHead *)pos_begin;
			assert(pos_begin);
			mb->copy((char *)&proto_head, sizeof(proto_head));
			mb->copy((char*)send_buf, bytes_to_send);
			// encrypt
			if (cycle_time_4 > 0)
			{
				int seed4 = proto_head.seed_;
				seed4 <<= 16;
				seed4 |= proto_head.seed_;
				for (int i = 0; i < cycle_time_4; ++i)
				{
					int *ptmp_int = (int *)(pos_begin + sizeof(proto_head) + i * sizeof(int));
					phead->crc_ += *ptmp_int;
					*(ptmp_int) ^= seed4;
				}
			}
			if (cycle_2 > 0)
			{
				unsigned short *pshort = (unsigned short *)(pos_begin + sizeof(proto_head) + cycle_time_4 * sizeof(int));
				phead->crc_ += *pshort;
				*(pshort) ^= proto_head.seed_;
			}
			if (cycle_1)
			{
				char ch = (char)proto_head.seed_;
				char *pchar = pos_begin + sizeof(proto_head) + cycle_time_4 * sizeof(int) + cycle_2;
				phead->crc_ += *pchar;
				*(pchar) ^= ch;
			}

			if (NetGateway_InitSeed != proto_head.net_command_)
				((CProtoHead*)pos_begin)->seed_ &= 0xff;

// 			LOG4CXX_TRACE(logger, "trace for crc "
// 				LOG_VAR(phead->crc_)
// 				LOG_VAR(szAddr_peer_)
// 				);

			if (-1 == m_ws.write(*mb, bytes_to_send + sizeof(proto_head)))
			{
				LOG4CXX_ERROR(logger, "写数据流失败"
					LOG_VAR(szAddr_peer_)
					LOG_VAR(proto_head.net_command_)
					LOG_VAR(proto_head.seed_)
					LOG_VAR(proto_head.user_data_len_)
					);
				delete mb;
				return ErrorWriteStream;
			}

			return 0;
		}

		int CServerTcpService::CloseConnection()
		{
			LOG4CXX_INFO(logger, "CloseConnection()"
				LOG_VAR(szAddr_peer_)
				LOG_VAR((NetCommHandle*)this)
				);
			ACE_HANDLE h = this->handle_;
			if (ACE_INVALID_HANDLE != h)
			{
				m_ws.cancel();
				ACE_OS::closesocket(h);
				this->handle(ACE_INVALID_HANDLE);
				net_object_ = 0;
			}
			return 0;
		}

		int CServerTcpService::initiate_read_stream()
		{
			//创建一个消息块。这个消息块将用于从套接字中异步读
			ACE_Message_Block *mb = new (std::nothrow) CServerMessageBlock(TCP_RECV_DATA);
			if (!mb)
			{
				LOG4CXX_FATAL(logger, "ACE_Message_Block *mb = new (std::nothrow) ACE_Message_Block(TCP_RECV_DATA);");
				return -1;
			}

			if (m_rs.read(*mb, mb->size()) == -1)
			{
				LOG4CXX_ERROR(logger, "(m_rs.read(*mb, mb->size()) == -1");
				delete mb;
				return -1;
			}
			return 0;
		}

	}  // Server
}  //  NetGateway