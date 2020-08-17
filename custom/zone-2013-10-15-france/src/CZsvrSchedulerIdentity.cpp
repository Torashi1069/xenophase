#include "CZsvrSchedulerIdentity.h"


/// singleton instance
CZsvrSchedulerIdentity*& CZsvrSchedulerIdentity::m_cpSelf = VTOR<CZsvrSchedulerIdentity*>(DetourFindFunction(EXEPATH(), "CZsvrSchedulerIdentity::m_cpSelf"));


CZsvrSchedulerIdentity::CZsvrSchedulerIdentity()
{
	m_IdentityCnt = TASK_LAST + 1;
	m_bOK = 1;
}


CZsvrSchedulerIdentity::~CZsvrSchedulerIdentity()
{
}


unsigned int CZsvrSchedulerIdentity::Get()
{
	unsigned int result = m_IdentityCnt;

	if( m_IdentityCnt < UINT_MAX )
		m_IdentityCnt = m_IdentityCnt + 1;
	else
		m_IdentityCnt = TASK_LAST + 1;

	return result;
}


bool CZsvrSchedulerIdentity::CreateInstance()
{
	if( m_cpSelf != NULL )
		return false;

	m_cpSelf = new(std::nothrow) CZsvrSchedulerIdentity();
	if( m_cpSelf == NULL )
		return false;

	if( !m_cpSelf->CZsvrSchedulerIdentity::isOK() )
	{
		delete m_cpSelf;
		m_cpSelf = NULL;
		return false;
	}

	return true;
}


void CZsvrSchedulerIdentity::DestroyInstance()
{
	if( m_cpSelf != NULL )
	{
		delete m_cpSelf;
		m_cpSelf = NULL;
	}
}


CZsvrSchedulerIdentity* CZsvrSchedulerIdentity::GetObj() /// @custom
{
	return m_cpSelf;
}


bool CZsvrSchedulerIdentity::isOK() const
{
	return m_bOK;
}
