#include "shared.h"
#include "Common/Packet.h"
#include "globals.hpp"


hook_func<void (__cdecl *)(const char* encBuf, unsigned char* decBuf)> _Decrypt(SERVER, "Decrypt");
void __cdecl Decrypt(const char* encBuf, unsigned char* decBuf) // line 31
{
	return (_Decrypt)(encBuf, decBuf);

	//TODO
}


//hook_func<void (__cdecl *)(const char* str, ...)> _TraceN(SERVER, "TraceN");
static void __cdecl TraceN(const char* str, ...) // line 179
{
//	return (_TraceN)(str, ...);

	;
}


//hook_func<void (__cdecl *)(const char *str, ...)> _TraceO(SERVER, "TraceO");
static void __cdecl TraceO(const char* str, ...) // line 182
{
//	return (_TraceO)(str, ...);

	va_list ap;
	va_start(ap, str);

	char szBuffer[1024];
	vsprintf(szBuffer, str, ap);

	OutputDebugStringA(szBuffer);
}


//hook_func<void (__cdecl *)(const char* str, ...)> _TraceF(SERVER, "TraceF");
static void __cdecl TraceF(const char* str, ...) // line 198
{
//	return (_TraceF)(str, ...);

	va_list ap;
	va_start(ap, str);

	EnterCriticalSection(&g_csTraceLog);

	FILE* fp = fopen(g_szTraceLogFileName, "at");
	if( fp != NULL )
	{
		SYSTEMTIME st;
		GetLocalTime(&st);

		char szDateBuffer[32];
		_snprintf(szDateBuffer, 30, "[%04d-%02d-%02d %02d:%02d:%02d.%03d]", st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond, st.wMilliseconds);

		char szBuffer[1024];
		vsprintf(szBuffer, str, ap);

		fprintf(fp, "%s%s", szDateBuffer, szBuffer);
		fclose(fp);
	}

	LeaveCriticalSection(&g_csTraceLog);
}


hook_func<void (__cdecl *)(int isInstallFilter, int logOption)> _InitializeSharedLib(SERVER, "InitializeSharedLib");
void __cdecl InitializeSharedLib(int isInstallFilter, int logOption) // line 251
{
	return (_InitializeSharedLib)(isInstallFilter, logOption);

	InitializeCriticalSection(&g_csTraceLog);

	if( isInstallFilter )
		InitializeCriticalSection(&g_exception_symbol_cs);

	InitPacketLen();

	Trace = ( logOption == 1 ) ? &TraceF
	      : ( logOption == 2 ) ? &TraceO
	      :                      &TraceN;
}
