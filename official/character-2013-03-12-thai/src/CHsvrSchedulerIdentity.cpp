#include "CHsvrSchedulerIdentity.h"


/// singleton instance
CHsvrSchedulerIdentity* CHsvrSchedulerIdentity::m_cpSelf;


CHsvrSchedulerIdentity::CHsvrSchedulerIdentity()
{
	m_IdentityCnt = 3;
	m_bOK = true;
}


CHsvrSchedulerIdentity::~CHsvrSchedulerIdentity()
{
}


bool CHsvrSchedulerIdentity::CreateInstance()
{
	if( m_cpSelf != NULL )
		return false;

	m_cpSelf = new(std::nothrow) CHsvrSchedulerIdentity();
	if( m_cpSelf == NULL )
		return false;

	if( !m_cpSelf->m_bOK )
	{
		delete m_cpSelf;
		m_cpSelf = NULL;
		return false;
	}

	return true;
}


void CHsvrSchedulerIdentity::DestroyInstance()
{
	if( m_cpSelf != NULL )
	{
		delete m_cpSelf;
		m_cpSelf = NULL;
	}
}


bool CHsvrSchedulerIdentity::isOK() const
{
	return m_bOK;
}


unsigned int CHsvrSchedulerIdentity::Get()
{
	return m_IdentityCnt;
}
