#include "shared/CProgrammerSupportLog.h"


/// singleton instance
CProgrammerSupportLog*& CProgrammerSupportLog::m_cpSelf = VTOR<CProgrammerSupportLog*>(DetourFindFunction(EXEPATH(), "CProgrammerSupportLog::m_cpSelf"));


CProgrammerSupportLog::CProgrammerSupportLog()
: NFileLog("logs", "ps", true)
{
	m_bOK = false;

	if( this->NFileLog::isOK() )
		m_bOK = true;
}


CProgrammerSupportLog::~CProgrammerSupportLog()
{
}


bool CProgrammerSupportLog::CreateInstance()
{
	if( m_cpSelf != NULL )
		return false;

	m_cpSelf = new(std::nothrow) CProgrammerSupportLog();
	if( m_cpSelf == NULL )
		return false;

	if( !m_cpSelf->CProgrammerSupportLog::isOK() )
	{
		delete m_cpSelf;
		m_cpSelf = NULL;
		return false;
	}

	return true;
}


void CProgrammerSupportLog::DestroyInstance()
{
	if( m_cpSelf != NULL )
	{
		delete m_cpSelf;
		m_cpSelf = NULL;
	}
}


CProgrammerSupportLog* CProgrammerSupportLog::GetObj() /// @custom
{
	return m_cpSelf;
}


bool CProgrammerSupportLog::isOK() const
{
	return m_bOK;
}
