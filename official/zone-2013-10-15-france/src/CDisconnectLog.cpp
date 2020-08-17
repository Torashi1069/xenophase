#include "CDisconnectLog.h"


/// singleton instance
CDisconnectLog*& CDisconnectLog::m_cpSelf = VTOR<CDisconnectLog*>(DetourFindFunction(EXEPATH(), "CDisconnectLog::m_cpSelf"));


CDisconnectLog::CDisconnectLog()
: NFileLog("logs", "Disconnect", false), m_bOK(false)
{
	if( this->NFileLog::isOK() )
		m_bOK = true;
}


CDisconnectLog::~CDisconnectLog()
{
}


bool CDisconnectLog::CreateInstance()
{
	if( m_cpSelf != NULL )
		return false;
	
	m_cpSelf = new(std::nothrow) CDisconnectLog();
	if( m_cpSelf == NULL )
		return false;

	if( !m_cpSelf->CDisconnectLog::isOK() )
	{
		delete m_cpSelf;
		m_cpSelf = NULL;
		return false;
	}

	return true;
}


void CDisconnectLog::DestroyInstance()
{
	if( m_cpSelf != NULL )
	{
		delete m_cpSelf;
		m_cpSelf = NULL;
	}
}


CDisconnectLog* CDisconnectLog::GetObj() /// @custom
{
	return m_cpSelf;
}


bool CDisconnectLog::isOK() const
{
	return m_bOK;
}
