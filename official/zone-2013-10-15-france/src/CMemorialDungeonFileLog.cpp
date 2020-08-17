#include "CMemorialDungeonFileLog.h"


/// singleton instance
CMemorialDungeonFileLog*& CMemorialDungeonFileLog::m_cpSelf = VTOR<CMemorialDungeonFileLog*>(DetourFindFunction(EXEPATH(), "CMemorialDungeonFileLog::m_cpSelf"));


CMemorialDungeonFileLog::CMemorialDungeonFileLog()
: NFileLog("logs", "MemorialDungeon", false), m_bOK(false)
{
	if( this->NFileLog::isOK() )
		m_bOK = true;
}


CMemorialDungeonFileLog::~CMemorialDungeonFileLog()
{
}


bool CMemorialDungeonFileLog::CreateInstance()
{
	if( m_cpSelf != NULL )
		return false;
	
	m_cpSelf = new(std::nothrow) CMemorialDungeonFileLog();
	if( m_cpSelf == NULL )
		return false;

	if( !m_cpSelf->CMemorialDungeonFileLog::isOK() )
	{
		delete m_cpSelf;
		m_cpSelf = NULL;
		return false;
	}

	return true;
}


void CMemorialDungeonFileLog::DestroyInstance()
{
	if( m_cpSelf != NULL )
	{
		delete m_cpSelf;
		m_cpSelf = NULL;
	}
}


CMemorialDungeonFileLog* CMemorialDungeonFileLog::GetObj() /// @custom
{
	return m_cpSelf;
}


bool CMemorialDungeonFileLog::isOK() const
{
	return m_bOK;
}


void CMemorialDungeonFileLog::WriteFmt(const char* in_SourceFileName, const int in_SourceLineNum, int in_hMemorialDungeon, int in_hParty, const char* in_pFmt, ...)
{
	if( this == NULL )
		return;

	if( !this->NFileLog::GetOutput() )
		return;

	va_list va;
	va_start(va, in_pFmt);

	char buffer[2048] = {};
	_vsnprintf_s(buffer, countof(buffer), _TRUNCATE, in_pFmt, va);

	this->NFileLog::WriteFmt(in_SourceFileName, in_SourceLineNum, "[%05d] [%d] %s", in_hMemorialDungeon, in_hParty, buffer);
}
