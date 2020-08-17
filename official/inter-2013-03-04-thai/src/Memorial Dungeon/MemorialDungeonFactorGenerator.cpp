#include "Memorial Dungeon/MemorialDungeonFactorGenerator.h"


/// singleton instance
CMemorialDungeonFactorGenerator*& CMemorialDungeonFactorGenerator::m_cpSelf = VTOR<CMemorialDungeonFactorGenerator*>(DetourFindFunction(EXEPATH(), "CMemorialDungeonFactorGenerator::m_cpSelf"));


CMemorialDungeonFactorGenerator::CMemorialDungeonFactorGenerator()
: CN3RecycleIDGenerator(1, 46655, 100)
{
}


CMemorialDungeonFactorGenerator::~CMemorialDungeonFactorGenerator()
{
}


bool CMemorialDungeonFactorGenerator::CreateInstance()
{
	if( m_cpSelf != NULL )
		return false;

	m_cpSelf = new(std::nothrow) CMemorialDungeonFactorGenerator();
	if( m_cpSelf == NULL )
		return false;

	if( !m_cpSelf->CN3RecycleIDGenerator::isOK() ) //FIXME: calling baseclass
	{
		delete m_cpSelf;
		m_cpSelf = NULL;
		return false;
	}

	return true;
}


void CMemorialDungeonFactorGenerator::DestoryInstance()
{
	if( m_cpSelf != NULL )
	{
		delete m_cpSelf;
		m_cpSelf = NULL;
	}
}


CMemorialDungeonFactorGenerator* CMemorialDungeonFactorGenerator::GetObj() /// @custom
{
	return m_cpSelf;
}
