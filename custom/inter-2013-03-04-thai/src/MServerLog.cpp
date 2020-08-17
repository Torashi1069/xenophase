#include "MServerLog.h"
#include "shared/NSystem/NSyncObject.h"


/// singleton instance
CMServerLog*& CMServerLog::m_cpSelf = VTOR<CMServerLog*>(DetourFindFunction(EXEPATH(), "CMServerLog::m_cpSelf"));


CMServerLog::CMServerLog()
{
	m_bOK = false;

	InitializeCriticalSection(&m_CS);
	CreateDirectoryA("Log", NULL);

	SYSTEMTIME st;
	GetLocalTime(&st);
	_snprintf(m_LogFileName, countof(m_LogFileName), "Log/Mserverlog(%04d%02d%02d).txt", st.wYear, st.wMonth, st.wDay);

	m_bOK = true;
}


CMServerLog::~CMServerLog()
{
	DeleteCriticalSection(&m_CS);
}


bool CMServerLog::CreateInstance()
{
	if( m_cpSelf != NULL )
		return false;

	m_cpSelf = new(std::nothrow) CMServerLog();
	if( m_cpSelf == NULL )
		return false;

	if( !m_cpSelf->CMServerLog::isOK() )
	{
		delete m_cpSelf;
		m_cpSelf = NULL;
		return false;
	}

	return true;
}


void CMServerLog::DestroyInstance()
{
	if( m_cpSelf != NULL )
	{
		delete m_cpSelf;
		m_cpSelf = NULL;
	}
}


CMServerLog* CMServerLog::GetObj() /// @custom
{
	return m_cpSelf;
}


bool CMServerLog::isOK() const
{
	return m_bOK;
}


void CMServerLog::LogFmt(const char* in_pFmt, ...)
{
	va_list va;
	va_start(va, in_pFmt);

	char Buffer[2048] = {};
	_vsnprintf(Buffer, countof(Buffer)-1, in_pFmt, va);

	NSyncObject sync(m_CS);

	FILE* fp = fopen(m_LogFileName, "a");
	if( fp == NULL )
		return;

	SYSTEMTIME st;
	GetLocalTime(&st);
	fprintf(fp, "%02d-%02d-%02d %02d:%02d:%02d.%03d %s\n", st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond, st.wMilliseconds, Buffer);

	fclose(fp);
}
