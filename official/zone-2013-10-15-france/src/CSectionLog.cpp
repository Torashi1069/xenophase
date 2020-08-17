#include "CSectionLog.h"
////////////////////////////////////////


/// singleton instances
CGameGuardLog*& CGameGuardLog::m_isSelf = VTOR<CGameGuardLog*>(DetourFindFunction(EXEPATH(), "CGameGuardLog::m_isSelf"));
CNpcEventLog*& CNpcEventLog::m_isSelf = VTOR<CNpcEventLog*>(DetourFindFunction(EXEPATH(), "CNpcEventLog::m_isSelf"));


////////////////////////////////////////


CSectionLog::CSectionLog()
{
	InitializeCriticalSection(&m_csCriticalError);
	m_fileName.clear();
}


CSectionLog::~CSectionLog()
{
	DeleteCriticalSection(&m_csCriticalError);
	m_fileName.clear();
}


void CSectionLog::Init(const char* fileName)
{
	if( fileName == NULL || strlen(fileName) < 1 )
		return;

	m_fileName = fileName;
}


void CSectionLog::Log(const char* in_pFileName, const int in_Line, const char* in_pFmt, ...)
{
	if( m_fileName.size() == 0 )
		return;

	EnterCriticalSection(&m_csCriticalError);

	va_list va;
	va_start(va, in_pFmt);

	char Buffer[2048+1] = {};
	_vsnprintf(Buffer, countof(Buffer)-1, in_pFmt, va);

	const char* pFileName = in_pFileName;
	if( strrchr(in_pFileName, '\\') != NULL )
		pFileName = strrchr(in_pFileName, '\\');

	FILE* fp = fopen(m_fileName.c_str(), "a");
	if( fp != NULL )
	{
		SYSTEMTIME st;
		GetLocalTime(&st);

		fprintf(fp, "%-30s(%04d) %02d-%02d-%02d %02d:%02d:%02d.%03d %s\n", pFileName, in_Line, st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond, st.wMilliseconds, Buffer);
		fclose(fp);
	}

	LeaveCriticalSection(&m_csCriticalError);
}


////////////////////////////////////////


CGameGuardLog::CGameGuardLog()
{
	this->CSectionLog::Init("GameGuardLog.txt");
}


CGameGuardLog::~CGameGuardLog()
{
}


bool CGameGuardLog::CreateInstance()
{
	if( m_isSelf != NULL )
		return false;

	m_isSelf = new(std::nothrow) CGameGuardLog();
	if( m_isSelf == NULL )
		return false;

	return true;
}


void CGameGuardLog::DestroyInstance()
{
	if( m_isSelf != NULL )
	{
		delete m_isSelf;
		m_isSelf = NULL;
	}
}


CGameGuardLog* CGameGuardLog::GetObj() /// @custom
{
	return m_isSelf;
}


////////////////////////////////////////


CNpcEventLog::CNpcEventLog()
{
	this->CSectionLog::Init("NpcEventLog.txt");
}


CNpcEventLog::~CNpcEventLog()
{
}


bool CNpcEventLog::CreateInstance()
{
	if( m_isSelf != NULL )
		return false;

	m_isSelf = new(std::nothrow) CNpcEventLog();
	if( m_isSelf == NULL )
		return false;

	return true;
}


void CNpcEventLog::DestroyInstance()
{
	if( m_isSelf != NULL )
	{
		delete m_isSelf;
		m_isSelf = NULL;
	}
}


CNpcEventLog* CNpcEventLog::GetObj() /// @custom
{
	return m_isSelf;
}


////////////////////////////////////////
