#include "Common/Packet.h"
#include "shared.h"


hook_val<void (__cdecl *)(char const* str,...)> Trace(SERVER, "Trace"); // = TraceO;
hook_val<RTL_CRITICAL_SECTION> g_csTraceLog(SERVER, "g_csTraceLog");
hook_val<RTL_CRITICAL_SECTION> g_exception_symbol_cs(SERVER, "g_exception_symbol_cs");


hook_func<void (__cdecl *)(const char* str, ...)> _TraceO(SERVER, "TraceO");
void __cdecl TraceO(const char* str, ...) // line 182
{
//	return (_TraceO)(str, ...);

	va_list va;
	va_start(va, str);

	char szBuffer[1024];
	vsprintf(szBuffer, str, va);

	OutputDebugStringA(szBuffer);
}


hook_func<void (__cdecl *)(const char* str, ...)> _TraceF(SERVER, "TraceF");
void __cdecl TraceF(const char* str, ...) // line 198
{
//	return (_TraceF)(str, ...);

	va_list va;
	va_start(va, str);

	EnterCriticalSection(&g_csTraceLog);

	FILE* f = fopen("TraceLog(Sep 21 2009).txt", "at");
	if( f != NULL )
	{
		SYSTEMTIME st;
		GetLocalTime(&st);

		char szDateBuffer[32];
		_snprintf(szDateBuffer, sizeof(szDateBuffer)-1, "[%04d-%02d-%02d %02d:%02d:%02d.%03d]", st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond, st.wMilliseconds);

		char szBuffer[1024];
		vsprintf(szBuffer, str, va);

		fprintf(f, "%s%s", szDateBuffer, szBuffer);

		fclose(f);
	}

	LeaveCriticalSection(&g_csTraceLog);
}


hook_func<void (__cdecl *)(const char* str, ...)> _TraceN(SERVER, "TraceN");
void __cdecl TraceN(const char* str, ...) // line ???
{
//	return (_TraceN)(str, ...);

	;
}


hook_func<void (__cdecl *)(int isInstallFilter, int logOption)> _InitializeSharedLib(SERVER, "InitializeSharedLib");
void __cdecl InitializeSharedLib(int isInstallFilter, int logOption) // line 251
{
	return (_InitializeSharedLib)(isInstallFilter, logOption);

	InitializeCriticalSection(&g_csTraceLog);

	if( isInstallFilter )
		InitializeCriticalSection(&g_exception_symbol_cs);

	InitPacketLen();

	if( logOption == 0 )
		Trace = TraceN;
	else
	if( logOption == 1 )
		Trace = TraceF;
	else
	if( logOption == 2 )
		Trace = TraceO;
}
