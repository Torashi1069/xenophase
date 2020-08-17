#include "CStaticNPCAIDGenerator.h"
#include "ZoneProcess.h"
#include "shared/NCriticalErrorLog.h"


/// singleton instance
CStaticNPCAIDGenerator*& CStaticNPCAIDGenerator::m_cpSelf = VTOR<CStaticNPCAIDGenerator*>(DetourFindFunction(EXEPATH(), "CStaticNPCAIDGenerator::m_cpSelf"));


bool CStaticNPCAIDGenerator::IsOk()
{
	return m_bOK;
}


void CStaticNPCAIDGenerator::Free(const int in_AID)
{
	if( (unsigned long)in_AID < m_MinimumAID || (unsigned long)in_AID > m_MaximumAID )
		return;

	m_AIDPool.push_back(in_AID);
}


int CStaticNPCAIDGenerator::Alloc()
{
	if( m_AIDPool.size() == 0 )
	{
		NCriticalErrorLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__, "CStaticNPCAIDGenerator::Alloc() error ***********");
		return 0;
	}

	int AID = m_AIDPool.front();
	m_AIDPool.pop_front();
	return AID;
}


bool CStaticNPCAIDGenerator::CreateInstance(const int in_MinimumAID, const int in_MaximumAID)
{
	if( m_cpSelf != NULL )
		return false;

	m_cpSelf = new(std::nothrow) CStaticNPCAIDGenerator(in_MinimumAID, in_MaximumAID);
	if( m_cpSelf == NULL )
		return false;

	if( !m_cpSelf->CStaticNPCAIDGenerator::IsOk() )
	{
		delete m_cpSelf;
		m_cpSelf = NULL;
		return false;
	}

	return true;
}


void CStaticNPCAIDGenerator::DestroyInsance()
{
	if( m_cpSelf != NULL )
	{
		delete m_cpSelf;
		m_cpSelf = NULL;
	}
}


CStaticNPCAIDGenerator* CStaticNPCAIDGenerator::GetObj() /// @custom
{
	return m_cpSelf;
}


CStaticNPCAIDGenerator::CStaticNPCAIDGenerator(const int in_MinimumAID, const int in_MaximumAID)
: m_MinimumAID(NPC_MINIMUM_AID), m_MaximumAID(NPC_MAXIMUM_AID), m_AIDPool(), m_bOK(false)
{
	for( unsigned long AID = m_MinimumAID; AID <= m_MaximumAID; ++AID )
		m_AIDPool.push_back(AID);

	m_bOK = true;
}


CStaticNPCAIDGenerator::~CStaticNPCAIDGenerator()
{
}
