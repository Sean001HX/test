/*
* Version: 1.0.0.0
* 解决：若出现类似“C:\Program Files\Microsoft SDKs\Windows\v6.0A\include\winnt.h(236) : 
* error C2146: 语法错误 : 缺少“;”(在标识符“PVOID64”的前面)”不能识别PVOID64的问题，
* 通常是应用于不同Windows SDK版本的头包含造成的宏冲突的问题
* 用法：该文件应用于使用预编译头或不使用预编译头的各种情况，只需要INCLUDE进来就OK了
*/
#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif

#ifndef __POINTERDEF_H__
#define __POINTERDEF_H__

#ifndef POINTER_64  
#if !defined(_MAC) && (defined(_M_MRX000) || defined(_M_AMD64) || defined(_M_IA64)) && (_MSC_VER >= 1100) && !(defined(MIDL_PASS) || defined(RC_INVOKED))  
#define POINTER_64 __ptr64  
typedef unsigned __int64 POINTER_64_INT;  
#if defined(_WIN64)  
#define POINTER_32 __ptr32  
#else  
#define POINTER_32  
#endif  
#else  
#if defined(_MAC) && defined(_MAC_INT_64)  
#define POINTER_64 __ptr64  
typedef unsigned __int64 POINTER_64_INT;  
#else  
#if (_MSC_VER >= 1300) && !(defined(MIDL_PASS) || defined(RC_INVOKED))  
#define POINTER_64 __ptr64  
#else  
#define POINTER_64  
#endif  
typedef unsigned long POINTER_64_INT;  
#endif  
#define POINTER_32  
#endif  
#endif // #ifndef POINTER_64 

#endif
