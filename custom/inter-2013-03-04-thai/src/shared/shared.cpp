#include "shared/DES.h"
#include "shared/NTraceLog.h"
#include "shared/shared.h"


/// globals
void(*& Trace)(const char* str, ...) = VTOR<void(*)(const char* str, ...)>(DetourFindFunction(EXEPATH(), "Trace")); // = &TraceO;


void Decrypt(const char* encBuf, unsigned char* decBuf)
{
	unsigned char key[7] = { 0x78, 0x11, 0x23, 0x2A, 0xF1, 0xED, 0x07 };

	DES des(key);

	char szString[2+1] = {};

	size_t hexlen = strlen(encBuf) / 2;

	// unpack hex-string to binary
	for( size_t i = 0; i < hexlen; ++i )
	{
		szString[0] = encBuf[2*i+0];
		szString[1] = encBuf[2*i+1];
		sscanf(szString, "%02X", &decBuf[i]);
	}

	// decode data, block by block
	for( size_t i = 0; i < hexlen; i += 8 )
		des.DES::decrypt(&decBuf[i], 8);
}


void TraceN(const char* str, ...)
{
}


void TraceO(const char* str, ...)
{
	va_list va;
	va_start(va, str);

	char szBuffer[1024+1] = {};
	_vsnprintf(szBuffer, countof(szBuffer)-1, str, va);

	OutputDebugStringA(szBuffer);
}


void TraceF(const char* str, ...)
{
	va_list va;
	va_start(va, str);

	char szBuffer[1024];
	_vsnprintf_s(szBuffer, countof(szBuffer), _TRUNCATE, str, va);

	NTraceLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__, szBuffer);
}


void InitializeSharedLib(BOOL isInstallFilter, int logOption)
{
	if( logOption == 0 )
		Trace = &TraceN;
	else
	if( logOption == 1 )
		Trace = &TraceF;
	else
	if( logOption == 2 )
		Trace = &TraceO;
}
