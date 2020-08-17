#include "shared/NCriticalErrorLog.h"


/// singleton instance
NCriticalErrorLog*& NCriticalErrorLog::m_cpSelf = VTOR<NCriticalErrorLog*>(DetourFindFunction(EXEPATH(), "NCriticalErrorLog::m_cpSelf"));


NCriticalErrorLog::NCriticalErrorLog()
: NFileLog("logs", "CriticalError", false)
{
	m_bOK = false;

	if( this->NFileLog::isOK() )
		m_bOK = true;
}


NCriticalErrorLog::~NCriticalErrorLog()
{
}


bool NCriticalErrorLog::CreateInstance()
{
	if( m_cpSelf != NULL )
		return false;

	m_cpSelf = new(std::nothrow) NCriticalErrorLog();
	if( m_cpSelf == NULL )
		return false;

	if( !m_cpSelf->NCriticalErrorLog::isOK() )
	{
		delete m_cpSelf;
		m_cpSelf = NULL;
		return false;
	}

	return true;
}


void NCriticalErrorLog::DestroyInstance()
{
	if( m_cpSelf != NULL )
	{
		delete m_cpSelf;
		m_cpSelf = NULL;
	}
}


NCriticalErrorLog* NCriticalErrorLog::GetObj() /// @custom
{
	return m_cpSelf;
}


bool NCriticalErrorLog::isOK() const
{
	return m_bOK;
}
