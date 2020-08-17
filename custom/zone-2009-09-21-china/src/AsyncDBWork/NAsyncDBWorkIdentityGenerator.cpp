#include "AsyncDBWork/NAsyncDBWorkIdentityGenerator.h"


int CNAsyncDBWorkIdentityGenerator::operator()(void)
{
	int result = m_IdentityCnt;

	m_IdentityCnt++;
	if( m_IdentityCnt < MINIMUM_IDENTITY )
		m_IdentityCnt = MINIMUM_IDENTITY;

	return result;
}


CNAsyncDBWorkIdentityGenerator::CNAsyncDBWorkIdentityGenerator(void)
{
	m_IdentityCnt = MINIMUM_IDENTITY;
}


CNAsyncDBWorkIdentityGenerator::~CNAsyncDBWorkIdentityGenerator(void)
{
}
