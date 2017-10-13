/*
* purpose: 实现平台无关的读写锁
*/
#ifndef  _RW_MUTEX_H_
#define  _RW_MUTEX_H_

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif

#if defined(_WIN32) || defined(_WIN64) || defined(WIN32) || defined(WIN64)
# include <concrt.h>
  using namespace Concurrency;

  typedef Concurrency::reader_writer_lock					rwMutex;
  typedef Concurrency::reader_writer_lock::scoped_lock_read	readLock;
  typedef Concurrency::reader_writer_lock::scoped_lock		writeLock;
#else
# error("包含Linux下的读写锁相关定义")  
#endif

#endif _RW_MUTEX_H_
