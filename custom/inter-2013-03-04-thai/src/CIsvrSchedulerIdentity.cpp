#include "CIsvrSchedulerIdentity.h"


/// singleton instance
CIsvrSchedulerIdentity*& CIsvrSchedulerIdentity::m_cpSelf = VTOR<CIsvrSchedulerIdentity*>(DetourFindFunction(EXEPATH(), "CIsvrSchedulerIdentity::m_cpSelf"));


CIsvrSchedulerIdentity::CIsvrSchedulerIdentity()
{
	m_IdentityCnt = 4;
	m_bOK = true;
}


CIsvrSchedulerIdentity::~CIsvrSchedulerIdentity()
{
}


unsigned int CIsvrSchedulerIdentity::Get()
{
	return m_IdentityCnt;
}


bool CIsvrSchedulerIdentity::CreateInstance()
{
	if( m_cpSelf != NULL )
		return false;

	m_cpSelf = new(std::nothrow) CIsvrSchedulerIdentity();
	if( m_cpSelf == NULL )
		return false;

	if( !m_cpSelf->CIsvrSchedulerIdentity::isOK() )
	{
		delete m_cpSelf;
		m_cpSelf = NULL;
		return false;
	}

	return true;
}


void CIsvrSchedulerIdentity::DestroyInstance()
{
	if( m_cpSelf != NULL )
	{
		delete m_cpSelf;
		m_cpSelf = NULL;
	}
}


CIsvrSchedulerIdentity* CIsvrSchedulerIdentity::GetObj() /// @custom
{
	return m_cpSelf;
}


bool CIsvrSchedulerIdentity::isOK() const
{
	return m_bOK;
}
