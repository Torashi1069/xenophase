#include "Instant Map/InstantMapIDGenerator.h"


/// singleton instance
CInstantMapIDGenerator*& CInstantMapIDGenerator::m_cpSelf = VTOR<CInstantMapIDGenerator*>(DetourFindFunction(EXEPATH(), "CInstantMapIDGenerator::m_cpSelf"));


CInstantMapIDGenerator::CInstantMapIDGenerator()
: CN3RecycleIDGenerator(10000, 30000, 100)
{
}


CInstantMapIDGenerator::~CInstantMapIDGenerator()
{
}


bool CInstantMapIDGenerator::CreateInstance()
{
	if( m_cpSelf != NULL )
		return false;

	m_cpSelf = new(std::nothrow) CInstantMapIDGenerator();
	if( m_cpSelf == NULL )
		return false;

	if( !m_cpSelf->CInstantMapIDGenerator::isOK() )
	{
		delete m_cpSelf;
		m_cpSelf = NULL;
		return false;
	}

	return true;
}


void CInstantMapIDGenerator::DestoryInstance()
{
	if( m_cpSelf != NULL )
	{
		delete m_cpSelf;
		m_cpSelf = NULL;
	}
}


CInstantMapIDGenerator* CInstantMapIDGenerator::GetObj() /// @custom
{
	return m_cpSelf;
}
