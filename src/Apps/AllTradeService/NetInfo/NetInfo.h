
#ifndef  __NET_INFO_H__
#define  __NET_INFO_H__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif

#if defined(_MSC_VER) && (_MSC_VER < 1700)
	#error "编译器版本必须是VS2012或以上!"
#endif

#include <string>
#include "utility/binstream.h"
#include "RequestMsgDefine.h"
#include "utility/MsgBlockEx.h"

namespace xyc_comm_mutually
{
	class CInfoElement
	{
	public:
		CInfoElement() 
            : type_(IE_COMM_Invalid)
			, length_(0) 
		{}
		CInfoElement(unsigned short usType, const std::string& szContent) 
			: type_(usType)
			, length_((unsigned short)szContent.length())
            , content_(szContent)
		{}
		CInfoElement(const CInfoElement& rhs)
			: type_(rhs.type_)
			, length_(rhs.length_)
			, content_(rhs.content_)
		{}
		CInfoElement( CInfoElement&& rhs)
			: type_(rhs.type_)
			, length_(rhs.length_)
			, content_(std::move(rhs.content_))
		{
            rhs.type_ = IE_COMM_Invalid;
			rhs.length_ = 0;
		}
        CInfoElement(XYCTOOLS::BinaryStream& stream)
		{
			serializeFrom(stream);
		}
		virtual ~CInfoElement() {}

		CInfoElement& operator=( const CInfoElement& rhs ) 
		{
			if (this != &rhs) {
				type_ = rhs.type_;
				length_ = rhs.length_;
				content_ = rhs.content_;
			}
			return *this;
		}
		CInfoElement& operator=( CInfoElement&& rhs ) 
		{
			if (this != &rhs) 
			{
				type_ = rhs.type_;
				length_ = rhs.length_;
				content_ = std::move(rhs.content_);

                rhs.type_ = IE_COMM_Invalid;
				rhs.length_ = 0;
			}
			return *this;
		}

		bool operator<( const CInfoElement& rhs ) { return type_ < rhs.type_; }
		bool operator>( const CInfoElement& rhs ) { return type_ > rhs.type_; }
		bool operator==( const CInfoElement& rhs ) { return type_ == rhs.type_; }
		bool operator!=( const CInfoElement& rhs ) { return type_ != rhs.type_; }

        XYCTOOLS::BinaryStream& serializeTo(XYCTOOLS::BinaryStream& stream) const {
//			stream << type_ <<  length_ << content_;
			stream << type_ << content_;
			return stream;
		}
        XYCTOOLS::BinaryStream& serializeFrom(XYCTOOLS::BinaryStream& stream) {
			stream >> type_ >> content_;
			length_ = (unsigned short)content_.length();
			return stream;
		}
		int serializeLen() const {		// 是整个IE的持久化长度!
			size_t len = sizeof(type_) + sizeof(int) + content_.length();
			return (int)len;
		}

        void serializeToMB(XYCTOOLS::MessageBlockEx* pmsg) const {
			assert(pmsg != NULL);
			pmsg->copy((const char*)&type_, sizeof(type_));
			int nlen = (int)content_.length();
			pmsg->copy((const char*)&nlen, sizeof(int));
			pmsg->copy(content_.c_str(), nlen);
		}
        void serializeFromMB(XYCTOOLS::MessageBlockEx* pmsg) {
			assert(pmsg != NULL);
			memcpy_s(&type_, sizeof(type_), pmsg->rd_ptr(), sizeof(type_));
			pmsg->rd_ptr(sizeof(type_));
			int nlen;
			memcpy_s(&nlen, sizeof(nlen), pmsg->rd_ptr(), sizeof(nlen));
			pmsg->rd_ptr(sizeof(nlen));
			content_.append(pmsg->rd_ptr(), (size_t)nlen);
			pmsg->rd_ptr(nlen);
			length_ = (unsigned short)nlen;
		}

	public:
		unsigned short getType() const { return type_; }
		unsigned short getContentLen() const { return length_; }
		const std::string&  getContent() const { return content_; }

		void setType(unsigned short ust) { type_ = ust; }
		void setContentLen(unsigned short usl) { length_ = usl; }
		void setContent(const std::string& szc) { content_ = szc; }

		unsigned long getItemCount() const {
			unsigned long cnt;
            XYCTOOLS::BinaryStream stream(getContent());
			stream >> cnt;
			return cnt;
		}

	private:
		unsigned short	type_;			// IE类型；见“E_COMM_IE_TYPE”的定义
		unsigned short	length_;		// IE的内容长度
		std::string		content_;		// IE的具体内容
	}; // class CInfoElement

} // namespace xyc_comm_mutually

#endif // __NET_INFO_H__
