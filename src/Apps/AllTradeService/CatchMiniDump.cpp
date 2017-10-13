#include "CatchMiniDump.h"
#include <windows.h>
#include <DbgHelp.h>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>

#pragma comment(lib, "dbghelp")

#pragma warning(disable:4996) 

LPTOP_LEVEL_EXCEPTION_FILTER g_unhandledExceptonHandler = 0;

inline BOOL IsDataSectionNeeded(const WCHAR* pModuleName)  
{  
	if(pModuleName == 0)  
	{  
		return FALSE;  
	}  

	WCHAR szFileName[_MAX_FNAME] = L"";  
	_wsplitpath(pModuleName, NULL, NULL, szFileName, NULL);  

	if(wcsicmp(szFileName, L"ntdll") == 0)  
		return TRUE;  

	return FALSE;  
}  

inline BOOL CALLBACK MiniDumpCallback(PVOID    pParam,  
	const PMINIDUMP_CALLBACK_INPUT   pInput,  
	PMINIDUMP_CALLBACK_OUTPUT        pOutput)  
{  
	if(pInput == 0 || pOutput == 0)  
		return FALSE;  

	switch(pInput->CallbackType)  
	{  
	case ModuleCallback:  
 		if(pOutput->ModuleWriteFlags & ModuleWriteDataSeg)  
 			if(!IsDataSectionNeeded(pInput->Module.FullPath))  
 				pOutput->ModuleWriteFlags &= (~ModuleWriteDataSeg);  
	case IncludeModuleCallback:  
	case IncludeThreadCallback:  
	case ThreadCallback:  
	case ThreadExCallback:  
		return TRUE;  
	default:;  
	}  

	return TRUE;  
}  

inline void CreateMiniDump(PEXCEPTION_POINTERS pep, LPCSTR strFileName)  
{  
	HANDLE hFile = CreateFileA(strFileName, GENERIC_READ | GENERIC_WRITE,  
		FILE_SHARE_WRITE, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);  

	if((hFile != NULL) && (hFile != INVALID_HANDLE_VALUE))  
	{  
		MINIDUMP_EXCEPTION_INFORMATION mdei;  
		mdei.ThreadId           = GetCurrentThreadId();  
		mdei.ExceptionPointers  = pep;  
		mdei.ClientPointers     = NULL;  

		MINIDUMP_CALLBACK_INFORMATION mci;  
		mci.CallbackRoutine     = (MINIDUMP_CALLBACK_ROUTINE)MiniDumpCallback;  
		mci.CallbackParam       = 0;  

		::MiniDumpWriteDump(::GetCurrentProcess(), ::GetCurrentProcessId(), hFile, MiniDumpWithFullMemory, (pep != 0) ? &mdei : 0, NULL, &mci);

		CloseHandle(hFile);  
	}  
}  

LONG __stdcall HxUnhandledExceptionFilter(PEXCEPTION_POINTERS pExceptionInfo)  
{  
	SYSTEMTIME tt;
	GetLocalTime(&tt);

	char path[512] = { 0 };

	_snprintf_s(path, sizeof(path) - 1, "%d%02d%02d_%02d%02d%02d.%03d_%p_%08X.dmp", 
		tt.wYear, tt.wMonth, tt.wDay, tt.wHour, tt.wMinute, tt.wSecond,tt.wMilliseconds, path, GetCurrentThreadId());

	CreateMiniDump(pExceptionInfo, path);  

	if (g_unhandledExceptonHandler)
		return g_unhandledExceptonHandler(pExceptionInfo);

	return EXCEPTION_EXECUTE_HANDLER;
}  


void InitMinDump()  
{  
	//注册异常处理函数  
	g_unhandledExceptonHandler = SetUnhandledExceptionFilter(HxUnhandledExceptionFilter);   
}  