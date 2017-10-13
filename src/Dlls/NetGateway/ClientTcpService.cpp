#include "stdafx.h"
#include "ClientTcpService.h"
#include "ace/Message_Block.h"
#include "ace/OS.h"
#include <stdio.h>
#include "ClientObject.h"
#include "ace/Proactor.h"
#include "proto_head.hpp"
#include "c:/ng_tools/ng_header_for_log4cxx/ng_header_for_log4cxx.hpp"
#include "C:/ng_tools/ng_header_for_log4cxx/ng_header_for_log4cxx_log_var.hpp"

NG_LOGGER(logger, "NetGateway::Client::CClientTcpService");


namespace NetGateway
{
	namespace Client
	{
		class CClientMessageBlock : public ACE_Message_Block
		{
		public:
			CClientMessageBlock(int size = 0) : ACE_Message_Block(size)
			{
// 				LOG4CXX_TRACE(logger, "CClientMessageBlock()"
// 					LOG_VAR(size)
// 					LOG_VAR(this)
// 					);
			}
			~CClientMessageBlock()
			{
// 				LOG4CXX_TRACE(logger, "~CClientMessageBlock()"
// 					LOG_VAR(this)
// 					);
			}
		};

		CClientTcpService::CClientTcpService() : client_connector_(0)
		{
// 			NGTrace trace(logger,  "CClientTcpService()");
		}

		CClientTcpService::~CClientTcpService()
		{
// 			NGTrace trace(logger,  "~CClientTcpService()");
		}

		int CClientTcpService::Connect(const char *host, int port)
		{
			_snprintf_s(szAddr_peer_, sizeof(szAddr_peer_) - 1, "%s", host);
			return 0;
		}

		int CClientTcpService::Send(short netCommand, const void *buf, int bufLen)
		{
// 			NGTrace trace(logger,  "Send()");

			CProtoHead proto_head = { 0 };
			proto_head.net_command_ = netCommand;
			proto_head.user_data_len_ = bufLen;

			if (client_object_)
			{
				ACE_Message_Block *mb = new (std::nothrow) CClientMessageBlock(sizeof(CProtoHead) + bufLen + 1);
				if (!mb)
				{
					LOG4CXX_FATAL(logger, "ACE_Message_Block *mb = new (std::nothrow) ACE_Message_Block(TCP_RECV_DATA);");
					return CommError;
				}
				bool done = client_object_->PackData(proto_head, (char*)buf, bufLen, *mb);
				if (!done)
				{
					return ConnectionUnverified;
				}

				if (-1 == m_ws.write(*mb, bufLen + sizeof(proto_head)))
				{
					LOG4CXX_ERROR(logger, "写数据流失败"
						LOG_VAR(szAddr_peer_)
						LOG_VAR(proto_head.net_command_)
						LOG_VAR(proto_head.seed_)
						LOG_VAR(proto_head.user_data_len_)
						LOG_VAR(proto_head.crc_)
						);
					delete mb;
					return ErrorWriteStream;
				}
			}
			else
			{
				return ConnectionDisconnected;
			}

			return 0;
		}

		void CClientTcpService::CloseConnection()
		{
// 			NGTrace trace(logger,  "CloseConnection()");
			LOG4CXX_DEBUG(logger, "CloseConnection()"
				LOG_VAR(szAddr_peer_)
				LOG_VAR((CClientHandler*)this)
				);
			ACE_HANDLE h = this->handle_;
			if (ACE_INVALID_HANDLE != h)
			{
				m_ws.cancel();
				ACE_OS::closesocket(h);
				this->handle(ACE_INVALID_HANDLE);
				client_object_ = 0;
			}
			return ;
		}

		void CClientTcpService::SetClientObject(CClientObject *client_object)
		{
			NGTrace trace(logger,  "SetClientObject()");
// 			LOG4CXX_DEBUG(logger, "SetClientObject()"
// 				LOG_VAR(szAddr_peer_)
// 				LOG_VAR(client_object_)
// 				);
			client_object_ = client_object;
		}

		void CClientTcpService::open(ACE_HANDLE new_handle, ACE_Message_Block &message_block)
		{
// 			NGTrace trace(logger,  "open()");
			this->handle(new_handle);

			LOG4CXX_DEBUG(logger, "open()"
				LOG_VAR(new_handle)
				LOG_VAR(szAddr_peer_)
				LOG_VAR(client_object_)
				);

			if (!client_object_)
			{
				LOG4CXX_ERROR(logger, "open()"
					LOG_VAR(client_object_)
					);

				delete this;
				if (ACE_INVALID_HANDLE != new_handle)
				{
					ACE_OS::closesocket(new_handle);
				}
				return;
			}

			// 初始化读数据流
			if (-1 == m_rs.open(*this, new_handle))
			{
				LOG4CXX_ERROR(logger, "open():构造读流失败:"
					LOG_VAR(new_handle)
					LOG_VAR(szAddr_peer_)
					);

				client_object_->OnConnected(false, 0, client_connector_);

				delete this;
				ACE_OS::closesocket(new_handle);
				return;
			}

			if (-1 == m_ws.open(*this, new_handle))
			{
				LOG4CXX_ERROR(logger, "open():构造写流失败:"
					LOG_VAR(new_handle)
					LOG_VAR(szAddr_peer_)
					);

				client_object_->OnConnected(false, 0, client_connector_);

				delete this;
				ACE_OS::closesocket(new_handle);
				return;
			}

			client_object_->OnConnected(true, this, 0);
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
				duplicate.wr_ptr(duplicate.wr_ptr() - bytes_transferred);  // ?

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

					client_object_->OnConnected(false, 0, 0);
					delete this;
					ACE_OS::closesocket(new_handle);
					return;
				}
			}
		}

		int CClientTcpService::initiate_read_stream()
		{
// 			NGTrace trace(logger,  "initiate_read_stream()");
			//创建一个消息块。这个消息块将用于从套接字中异步读
			ACE_Message_Block *mb = new (std::nothrow) CClientMessageBlock(TCP_RECV_DATA);
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

		void CClientTcpService::handle_write_stream(const ACE_Asynch_Write_Stream::Result &result)
		{
// 			NGTrace trace(logger,  "handle_write_stream()");
			result.message_block().release();
		}

		void CClientTcpService::handle_read_stream(const ACE_Asynch_Read_Stream::Result &result)
		{
// 			NGTrace trace(logger,  "handle_read_stream()");
			ACE_Message_Block& mb = result.message_block();
			// 连接关闭
			if (!result.success() || result.bytes_transferred() <= 0) // no data or failed
			{
				mb.release();
				ACE_HANDLE sock_handle = this->handle_;
				CClientHandler *client_handler = this;
				LOG4CXX_INFO(logger, "[!result.success() || result.bytes_transferred() <= 0]"
					LOG_VAR(client_handler)
					LOG_VAR(sock_handle)
					LOG_VAR(szAddr_peer_)
					);

				auto tmp_client_object = client_object_;
				if (tmp_client_object)
				{
					client_object_ = 0;
					tmp_client_object->OnConnected(false, this, 0);
				}

				delete this;
				if (sock_handle != ACE_INVALID_HANDLE)
				{
					ACE_OS::closesocket(sock_handle);
				}
				return;
			}

			char *szBuf = mb.rd_ptr();
			if (client_object_ && szBuf)
			{
				client_object_->OnRead(this, szBuf, result.bytes_transferred());
			}

			mb.reset();
			if (m_rs.read(mb, mb.size()) == -1)
			{
				LOG4CXX_ERROR(logger, "初始化客户读流失败"
					LOG_VAR(szAddr_peer_)
					);
				mb.release();
				ACE_HANDLE h = this->handle_;
				if (client_object_)
				{
					client_object_->OnConnected(false, this, 0);
					client_object_ = 0;
				}

				delete this;

				if (h != ACE_INVALID_HANDLE)
					ACE_OS::closesocket(h);
			}
		}

		void CClientTcpService::SetConnectorInfo(CClientConnector *connector)
		{
// 			NGTrace trace(logger,  "SetConnectorInfo()");
			client_connector_ = connector;
		}

	}  // Client
}  //  NetGateway