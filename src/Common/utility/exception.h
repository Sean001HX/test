/********************************************************************
	purpose:	STDµÄÒì³£À©Õ¹
*********************************************************************/
#ifndef _HELPERS_EXCEPTION_H
#define _HELPERS_EXCEPTION_H

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif


#include <exception>
#include <string>


namespace CommonTools
{

	/** The class QxException and its subclasses indicate conditions that a
	reasonable application might want to catch.
	*/
	class QxException : public ::std::exception
	{
	public:
		QxException(const std::string& msg);
		QxException(const char* szmsg);
		QxException(const QxException& src);
		QxException& operator=(const QxException& src);
		const char* what() const throw();
	private:
		enum { MSG_SIZE = 128 };
		char msg[MSG_SIZE + 1];
	}; // class QxException

	/** RuntimeException is the parent class of those exceptions that can be
	thrown during the normal operation of the process.
	*/
	class RuntimeException : public QxException
	{
	public:
		RuntimeException(const std::string& msg);
		RuntimeException(const RuntimeException& msg);
		RuntimeException& operator=(const RuntimeException& src);
	}; // class RuntimeException

	/** Thrown when an application attempts to use null in a case where an
	object is required.
	*/
	class  NullPointerException : public RuntimeException
	{
	public:
		NullPointerException(const std::string& msg);
		NullPointerException(const NullPointerException& msg);
		NullPointerException& operator=(const NullPointerException& src);
	}; // class NullPointerException

	/** Thrown to indicate that a method has been passed
	an illegal or inappropriate argument.*/
	class IllegalArgumentException : public RuntimeException
	{
	public:
		IllegalArgumentException(const std::string& msg);
		IllegalArgumentException(const IllegalArgumentException&);
		IllegalArgumentException& operator=(const IllegalArgumentException&);
	}; // class IllegalArgumentException

	/** Signals that an I/O exception of some sort has occurred. This class
	is the general class of exceptions produced by failed or interrupted
	I/O operations.
	*/
	class IOException : public QxException
	{
	public:
		IOException();
		IOException(long stat);
		IOException(const std::string& msg);
		IOException(const IOException &src);
		IOException& operator=(const IOException&);
	private:
		static std::string formatMessage(long stat);
	};

	class MissingResourceException : public QxException
	{
	public:
		MissingResourceException(const std::string& key);
		MissingResourceException(const MissingResourceException &src);
		MissingResourceException& operator=(const MissingResourceException&);
	private:
		static std::string formatMessage(const std::string& key);
	};

	class MutexException : public QxException
	{
	public:
		MutexException(long stat);
		MutexException(const MutexException &src);
		MutexException& operator=(const MutexException&);
	private:
		static std::string formatMessage(long stat);
	};

	class ConditionException : public QxException
	{
	public:
		ConditionException(long stat);
		ConditionException(const ConditionException &src);
		ConditionException& operator=(const MutexException&);
	private:
		static std::string formatMessage(long stat);
	};

	class ThreadException : public QxException {
	public:
		ThreadException(long stat);
		ThreadException(const ThreadException &src);
		ThreadException& operator=(const ThreadException&);
	private:
		static std::string formatMessage(long stat);
	};

	class IllegalMonitorStateException : public QxException {
	public:
		IllegalMonitorStateException(const std::string& msg);
		IllegalMonitorStateException(const IllegalMonitorStateException& msg);
		IllegalMonitorStateException& operator=(const IllegalMonitorStateException& msg);
	};

	/**
	Thrown when an application tries to create an instance of a class using
	the newInstance method in class Class, but the specified class object
	cannot be instantiated because it is an interface or is an abstract class.
	*/
	class InstantiationException : public QxException
	{
	public:
		InstantiationException(const std::string& msg);
		InstantiationException(const InstantiationException& msg);
		InstantiationException& operator=(const InstantiationException& msg);
	};

	/**
	Thrown when an application tries to load in a class through its
	string name but no definition for the class with the specified name
	could be found.
	*/
	class ClassNotFoundException : public QxException
	{
	public:
		ClassNotFoundException(const std::string& className);
		ClassNotFoundException(const ClassNotFoundException& msg);
		ClassNotFoundException& operator=(const ClassNotFoundException& msg);
	private:
		static std::string formatMessage(const std::string& className);
	};

	class NoSuchElementException : public QxException {
	public:
		NoSuchElementException();
		NoSuchElementException(const NoSuchElementException&);
		NoSuchElementException& operator=(const NoSuchElementException&);
	};

	class IllegalStateException : public QxException {
	public:
		IllegalStateException();
		IllegalStateException(const IllegalStateException&);
		IllegalStateException& operator=(const IllegalStateException&);
	};

	class ConstructMsgFailException : public QxException {
	public:
		ConstructMsgFailException(const std::string& msg="General construct comm msg fail.") 
			: QxException(msg) {}
	};

	class XMLInvalidException : public QxException {
	public:
		XMLInvalidException(const std::string& msg="Parse XML data fail.") : QxException(msg) {}
	};

}

#endif // _HELPERS_EXCEPTION_H
