#include "InterServer.h"
#include "shared/ErrorLog.h"


/// globals
CErrorLog& g_errorLogs = VTOR<CErrorLog>(DetourFindFunction(EXEPATH(), "g_errorLogs"));


CErrorLog::CErrorLog()
{
	InitializeCriticalSection(&m_csCriticalError);
}


CErrorLog::~CErrorLog()
{
	DeleteCriticalSection(&m_csCriticalError);
}


void CErrorLog::CmtLog(const unsigned long in_AID, const std::string in_CharName, const std::string in_MapName, const int in_x, const int in_y, const int in_type)
{
	EnterCriticalSection(&m_csCriticalError);

	FILE* fp = fopen("Cmt.log", "a");
	if( fp != NULL )
	{
		SYSTEMTIME st;
		GetLocalTime(&st);
		fprintf(fp, "%u-%u-%u %u:%u:%u AID %u Chr %s Map %s x %d y %d type %d\n", st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond, in_AID, in_CharName.c_str(), in_MapName.c_str(), in_x, in_y, in_type);

		fclose(fp);
	}

	LeaveCriticalSection(&m_csCriticalError);
}


void CErrorLog::KillAllLog(char* buf)
{
	if( buf == NULL )
		return; // invalid input

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


void CErrorLog::MoveLog(char* buf)
{
	if( buf == NULL )
		return; // invalid input

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


void CErrorLog::MoveLogFmt(const char* in_pFmt, ...)
{
	va_list va;
	va_start(va, in_pFmt);

	char Buffer[2048+1] = {};
	_vsnprintf(Buffer, countof(Buffer), in_pFmt, va);

	this->CErrorLog::MoveLog(Buffer);
}


void CErrorLog::CreateLog(char* buf)
{
	if( buf == NULL )
		return; // invalid input

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


void CErrorLog::PacketErrorLog(char* buf, unsigned long IP)
{
	if( buf == NULL || IP == INADDR_ANY )
		return; // invalid input

	if( !g_isPacketLog )
		return; // disabled

	BYTE Ip[4];
	memcpy_s(Ip, sizeof(Ip), &IP, sizeof(IP));

	char stIP[256];
	sprintf_s(stIP, countof(stIP), "%d.%d.%d.%d", Ip[0], Ip[1], Ip[2], Ip[3]);

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
