#include "shared/CVTBLErrorLog.h"


/// singleton instance
CVTBLErrorLog*& CVTBLErrorLog::m_cpSelf = VTOR<CVTBLErrorLog*>(DetourFindFunction(EXEPATH(), "CVTBLErrorLog::m_cpSelf"));


CVTBLErrorLog::CVTBLErrorLog()
: NFileLog("logs", "VtblError", false)
{
	m_bOK = false;

	if( this->NFileLog::isOK() )
		m_bOK = true;
}


CVTBLErrorLog::~CVTBLErrorLog()
{
}


bool CVTBLErrorLog::CreateInstance()
{
	if( m_cpSelf != NULL )
		return false;

	m_cpSelf = new(std::nothrow) CVTBLErrorLog();
	if( m_cpSelf == NULL )
		return false;

	if( !m_cpSelf->CVTBLErrorLog::isOK() )
	{
		delete m_cpSelf;
		m_cpSelf = NULL;
		return false;
	}

	return true;
}


void CVTBLErrorLog::DestroyInstance()
{
	if( m_cpSelf != NULL )
	{
		delete m_cpSelf;
		m_cpSelf = NULL;
	}
}


CVTBLErrorLog* CVTBLErrorLog::GetObj() /// @custom
{
	return m_cpSelf;
}


bool CVTBLErrorLog::isOK() const
{
	return m_bOK;
}
