#include "shared/NTraceLog.h"
#include "shared/shared.h"


/// globals
void(*& Trace)(const char* str, ...) = VTOR<void(*)(const char* str, ...)>(DetourFindFunction(EXEPATH(), "Trace")); // = &TraceO;


void Decrypt(const char* encBuf, unsigned char* decBuf)
{
	//TODO
}


static void TraceN(const char* str, ...)
{
}


static void TraceO(const char* str, ...)
{
	va_list va;
	va_start(va, str);

	char szBuffer[1024+1] = {};
	_vsnprintf(szBuffer, countof(szBuffer), str, va);

	OutputDebugStringA(szBuffer);
}


static void TraceF(const char* str, ...)
{
	va_list va;
	va_start(va, str);

	char szBuffer[1024];
	_vsnprintf_s(szBuffer, countof(szBuffer), _TRUNCATE, str, va);

	NTraceLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__, szBuffer);
}


void InitializeSharedLib(BOOL isInstallFilter, int logOption)
{
	if     ( logOption == 0 ) Trace = &TraceN;
	else if( logOption == 1 ) Trace = &TraceF;
	else if( logOption == 2 ) Trace = &TraceO;
}


short GetThirdJobGroup(short job)
{
	return 0;
	//TODO
}
