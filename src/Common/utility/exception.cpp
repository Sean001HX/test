#include "exception.h"
#include "stringhelper.h"

namespace CommonTools
{
	QxException::QxException(const std::string& msg1) {
		size_t msgLen = msg1.length();
		if (msgLen > MSG_SIZE) msgLen = MSG_SIZE;
		memcpy(this->msg, (char*) msg1.data(), msgLen);
		this->msg[msgLen] = 0;
	}

	QxException::QxException(const char* szmsg) {
		if (szmsg != NULL) {
			size_t msgLen = strlen(szmsg);
			if (msgLen > MSG_SIZE) {
				msgLen = MSG_SIZE;
			}
			memcpy(msg, szmsg, msgLen);
			msg[msgLen] = 0;
		}
		else {
#if defined(__STDC_LIB_EXT1__) || defined(__STDC_SECURE_LIB__)
			strcpy_s(msg, 14, "Unknown error!");
#else
			strcpy(msg, "Unknown error!");
#endif
		}
	}

	QxException::QxException(const QxException& src) : std::exception() {
#if defined(__STDC_LIB_EXT1__) || defined(__STDC_SECURE_LIB__)
		strcpy_s(msg, sizeof msg, src.msg);
#else
		strcpy(msg, src.msg);
#endif
	}

	QxException& QxException::operator=(const QxException& src) {
#if defined(__STDC_LIB_EXT1__) || defined(__STDC_SECURE_LIB__)
		strcpy_s(msg, sizeof msg, src.msg);
#else
		strcpy(msg, src.msg);
#endif
		return *this;
	}

	const char* QxException::what() const throw() {
		return msg;
	}

	RuntimeException::RuntimeException(const std::string& msg1)
		: QxException(msg1) {
	}

	RuntimeException::RuntimeException(const RuntimeException& src) : QxException(src) {
	}

	RuntimeException& RuntimeException::operator=(const RuntimeException& src) {
		QxException::operator=(src);
		return *this;
	}

	NullPointerException::NullPointerException(const std::string& msg1) : RuntimeException(msg1) {
	}

	NullPointerException::NullPointerException(const NullPointerException& src) : RuntimeException(src) {
	}

	NullPointerException& NullPointerException::operator=(const NullPointerException& src) {
		RuntimeException::operator=(src);
		return *this;
	}

	IllegalArgumentException::IllegalArgumentException(const std::string& msg1) : RuntimeException(msg1) {
	}

	IllegalArgumentException::IllegalArgumentException(const IllegalArgumentException& src) : RuntimeException(src) {
	}

	IllegalArgumentException& IllegalArgumentException::operator=(const IllegalArgumentException& src) {
		RuntimeException::operator=(src);
		return *this;
	}

	IOException::IOException() : QxException("IO exception") {
	}

	IOException::IOException(long stat) : QxException(formatMessage(stat)) {
	}

	IOException::IOException(const std::string& msg1) : QxException(msg1) {
	}

	IOException::IOException(const IOException& src)
		: QxException(src) {
	}

	IOException& IOException::operator=(const IOException& src) {
		QxException::operator=(src);
		return *this;
	}

	std::string IOException::formatMessage(long stat) {
		std::string s("IO QxException : status code = ");
		StringHelper::toString((int)stat, s);
		return s;
	}


	MissingResourceException::MissingResourceException(const std::string& key)
		: QxException(formatMessage(key)) {
	}


	MissingResourceException::MissingResourceException(const MissingResourceException& src)
		: QxException(src) {
	}

	MissingResourceException& MissingResourceException::operator=(const MissingResourceException& src) {
		QxException::operator=(src);
		return *this;
	}

	std::string MissingResourceException::formatMessage(const std::string& key) {
		std::string s("MissingResourceException: resource key = \"");
		s.append(key);
		s.append("\".");
		return s;
	}

	MutexException::MutexException(long stat)
		: QxException(formatMessage(stat)) {
	}

	MutexException::MutexException(const MutexException &src)
		: QxException(src) {
	}

	MutexException& MutexException::operator=(const MutexException& src) {
		QxException::operator=(src);
		return *this;
	}

	std::string MutexException::formatMessage(long stat) {
		std::string s("Mutex exception: stat = ");
		StringHelper::toString((int)stat, s);
		return s;
	}

	ConditionException::ConditionException(long stat)
		: QxException(formatMessage(stat)) {
	}

	ConditionException::ConditionException(const ConditionException &src)
		: QxException(src) {
	}

	ConditionException& ConditionException::operator=(const MutexException& src) {
		QxException::operator=(src);
		return *this;
	}

	std::string ConditionException::formatMessage(long stat) {
		std::string s("Condition exception: stat = ");
		StringHelper::toString((int)stat, s);
		return s;
	}

	ThreadException::ThreadException(long stat)
		: QxException(formatMessage(stat)) {
	}

	ThreadException::ThreadException(const ThreadException &src)
		: QxException(src) {
	}

	ThreadException& ThreadException::operator=(const ThreadException& src) {
		QxException::operator=(src);
		return *this;
	}

	std::string ThreadException::formatMessage(long stat) {
		std::string s("Thread exception: stat = ");
		StringHelper::toString((int)stat, s);
		return s;
	}

	IllegalMonitorStateException::IllegalMonitorStateException(const std::string& msg1)
		: QxException(msg1) {
	}

	IllegalMonitorStateException::IllegalMonitorStateException(const IllegalMonitorStateException& src)
		: QxException(src) {
	}

	IllegalMonitorStateException& IllegalMonitorStateException::operator=(const IllegalMonitorStateException& src) {
		QxException::operator=(src);
		return *this;
	}

	InstantiationException::InstantiationException(const std::string& msg1) : QxException(msg1) {
	}

	InstantiationException::InstantiationException(const InstantiationException& src) : QxException(src) {
	}

	InstantiationException& InstantiationException::operator=(const InstantiationException& src) {
		QxException::operator=(src);
		return *this;
	}

	ClassNotFoundException::ClassNotFoundException(const std::string& className) : QxException(formatMessage(className)) {
	}

	ClassNotFoundException::ClassNotFoundException(const ClassNotFoundException& src) : QxException(src) {
	}


	ClassNotFoundException& ClassNotFoundException::operator=(const ClassNotFoundException& src) {
		QxException::operator=(src);
		return *this;
	}

	std::string ClassNotFoundException::formatMessage(const std::string& className) {
		std::string s("Class not found: ");
		s.append(className);
		return s;
	}


	NoSuchElementException::NoSuchElementException() : QxException("No such element") {
	}

	NoSuchElementException::NoSuchElementException(const NoSuchElementException& src) : QxException(src) {
	}

	NoSuchElementException& NoSuchElementException::operator=(const NoSuchElementException& src) {
		QxException::operator=(src);
		return *this;
	}

	IllegalStateException::IllegalStateException() : QxException("Illegal state") {
	}

	IllegalStateException::IllegalStateException(const IllegalStateException& src) : QxException(src) {
	}

	IllegalStateException& IllegalStateException::operator=(const IllegalStateException& src) {
		QxException::operator=(src);
		return *this;
	}

} // namespace CommonTools
