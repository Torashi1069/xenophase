#include "ErrorLog.h"
#include "globals.hpp"


CErrorLog::CErrorLog(void)
{
	InitializeCriticalSection(&m_csCriticalError);
}


CErrorLog::~CErrorLog(void)
{
	DeleteCriticalSection(&m_csCriticalError);
}


hook_method<void (CErrorLog::*)(const char* in_pFileName, const int in_Line, const char* in_pFmt, ...)> CErrorLog::_CriticalErrorLogFmt(SERVER, "CErrorLog::CriticalErrorLogFmt");
void CErrorLog::CriticalErrorLogFmt(const char* in_pFileName, const int in_Line, const char* in_pFmt, ...)
{
//	return (this->*_CriticalErrorLogFmt)(in_pFileName, in_Line, in_pFmt, ...);

	if( g_isCriticalLog == 0 )
		return;

	va_list ap;
	va_start(ap, in_pFmt);

	char Buffer[2049];
	memset(Buffer, 0, 2049);
	_vsnprintf(Buffer, 2048, in_pFmt, ap);

	if( strrchr(in_pFileName, '\\') )
		in_pFileName = strrchr(in_pFileName, '\\');

	EnterCriticalSection(&m_csCriticalError);

	FILE* fp = fopen(g_szCriticalLogFileName, "a");
	if( fp != NULL )
	{
		SYSTEMTIME st;
		GetLocalTime(&st);
		fprintf(fp, "%-30s(%04d) %02d-%02d-%02d %02d:%02d:%02d.%03d %s\n", in_pFileName, in_Line, st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond, st.wMilliseconds, Buffer);
		fclose(fp);
	}

	LeaveCriticalSection(&m_csCriticalError);
}


hook_method<void (CErrorLog::*)(const char* buf, const int line, const char* filename)> CErrorLog::_CriticalErrorLog(SERVER, "CErrorLog::CriticalErrorLog");
void CErrorLog::CriticalErrorLog(const char* buf, const int line, const char* filename)
{
	return (this->*_CriticalErrorLog)(buf, line, filename);

	if( buf == NULL )
		return;

	if( g_isCriticalLog == 0 )
		return;

	EnterCriticalSection(&m_csCriticalError);

	FILE* fp = fopen(g_szCriticalLogFileName, "a");
	if( fp != NULL )
	{
		SYSTEMTIME st;
		GetLocalTime(&st);
		fprintf(fp, "%s(%d) %02d-%02d-%02d %02d:%02d:%02d.%03d %s\n", filename, line, st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond, st.wMilliseconds, buf);
		fclose(fp);
	}

	LeaveCriticalSection(&m_csCriticalError);
}


//hook_method<void (CErrorLog::*)(char* buf)> CErrorLog::_KillAllLog(SERVER, "CErrorLog::KillAllLog");
void CErrorLog::KillAllLog(char* buf)
{
//	return (this->*_KillAllLog)(buf);

	if( buf == NULL )
		return;

	EnterCriticalSection(&m_csCriticalError);

	FILE* fp = fopen("killall.log", "a");
	if( fp != NULL )
	{
		SYSTEMTIME st;
		GetLocalTime(&st);
		fprintf(fp, "Kill All Log : IP %s %u-%u-%u %u:%u \n", buf, st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute);
		fclose(fp);
	}

	LeaveCriticalSection(&m_csCriticalError);
}


hook_method<void (CErrorLog::*)(char* buf)> CErrorLog::_MoveLog(SERVER, "CErrorLog::MoveLog");
void CErrorLog::MoveLog(char* buf)
{
	return (this->*_MoveLog)(buf);

	if( buf == NULL )
		return;

	EnterCriticalSection(&m_csCriticalError);

	FILE* fp = fopen("RemoveLog.log", "a");
	if( fp != NULL )
	{
		SYSTEMTIME st;
		GetLocalTime(&st);
		fprintf(fp, "Log : %s %u-%u-%u %u:%u \n", buf, st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute);
		fclose(fp);
	}

	LeaveCriticalSection(&m_csCriticalError);
}


hook_method<void (CErrorLog::*)(char* buf)> CErrorLog::_CreateLog(SERVER, "CErrorLog::CreateLog");
void CErrorLog::CreateLog(char* buf)
{
	return (this->*_CreateLog)(buf);

	if( buf == NULL )
		return;

	EnterCriticalSection(&m_csCriticalError);

	FILE* fp = fopen("CreateLog.log", "a");
	if( fp != NULL )
	{
		SYSTEMTIME st;
		GetLocalTime(&st);
		fprintf(fp, "Log : %s %u-%u-%u %u:%u \n", buf, st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute);
		fclose(fp);
	}

	LeaveCriticalSection(&m_csCriticalError);
}


hook_method<void (CErrorLog::*)(char* buf, unsigned long IP)> CErrorLog::_PacketErrorLog(SERVER, "CErrorLog::PacketErrorLog");
void CErrorLog::PacketErrorLog(char* buf, unsigned long IP)
{
	return (this->*_PacketErrorLog)(buf, IP);

	if( buf == NULL || IP == 0 )
		return;

	if( g_isPacketLog == 0 )
		return;

	char stIP[256];
	sprintf(stIP, "%d.%d.%d.%d", BYTE(IP >> 0), BYTE(IP >> 8), BYTE(IP >> 16), BYTE(IP >> 24));

	EnterCriticalSection(&m_csCriticalError);

	FILE* fp = fopen("PacketErrorLog.Log", "a");
	if( fp != NULL )
	{
		SYSTEMTIME st;
		GetLocalTime(&st);
		fprintf(fp, "Log : %s IP: %s %u-%u-%u %u:%u \n", buf, stIP, st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute);
		fclose(fp);
	}

	LeaveCriticalSection(&m_csCriticalError);
}
