#include "shared/NTraceLog.h"


/// singleton instance
NTraceLog*& NTraceLog::m_cpSelf = VTOR<NTraceLog*>(DetourFindFunction(EXEPATH(), "NTraceLog::m_cpSelf"));


NTraceLog::NTraceLog()
: NFileLog("logs", "Trace", false)
{
	m_bOK = false;

	if( this->NFileLog::isOK() )
		m_bOK = true;
}


NTraceLog::~NTraceLog()
{
}


bool NTraceLog::CreateInstance()
{
	if( m_cpSelf != NULL )
		return false;

	m_cpSelf = new(std::nothrow) NTraceLog();
	if( m_cpSelf == NULL )
		return false;

	if( !m_cpSelf->NTraceLog::isOK() )
	{
		delete m_cpSelf;
		m_cpSelf = NULL;
		return false;
	}

	return true;
}


void NTraceLog::DestroyInstance()
{
	if( m_cpSelf != NULL )
	{
		delete m_cpSelf;
		m_cpSelf = NULL;
	}
}


NTraceLog* NTraceLog::GetObj() /// @custom
{
	return m_cpSelf;
}


bool NTraceLog::isOK() const
{
	return m_bOK;
}
