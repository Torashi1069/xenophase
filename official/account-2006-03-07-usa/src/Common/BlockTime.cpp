#include "Common/BlockTime.h"
#include "Common/Reporter.h"


/// singleton instance
static CBlockTime g_BlockTime;
CBlockTime* CSingleton<CBlockTime>::ms_Singleton;


CBlockTime::CBlockTime()
{
	m_pBlockTime = new tag_BLOCKTIME[100];
}


CBlockTime::~CBlockTime()
{
	delete[] m_pBlockTime;
}


void CBlockTime::UpdateBlockTime(DWORD dwKey, DWORD dwBlockTime)
{
	tag_BLOCKTIME* p = &m_pBlockTime[dwKey % 100];

	p->m_csMap.Enter();

	stdext::hash_map<DWORD,DWORD>::iterator it = p->m_map.find(dwKey);
	if( p->m_map.end() != it )
		p->m_map.erase(it);

	p->m_map[dwKey] = dwBlockTime + timeGetTime();

	p->m_csMap.Leave();
}


// guessed
void CBlockTime::DeleteBlockTime(DWORD dwKey)
{
	tag_BLOCKTIME* p = &m_pBlockTime[dwKey % 100];

	p->m_csMap.Enter();

	stdext::hash_map<DWORD,DWORD>::iterator it = p->m_map.find(dwKey);
	if( p->m_map.end() != it )
		p->m_map.erase(it);
	else
	{
		p->m_map[dwKey] = 0;
		CSingleton<CReporter>::getSingletonPtr()->CReporter::Log("%s %d  not Find Key[%u]\n", __FILE__, __LINE__, dwKey);
	}

	p->m_csMap.Leave();
}


BOOL CBlockTime::IsBlock(DWORD dwKey)
{
	tag_BLOCKTIME* p = &m_pBlockTime[dwKey % 100];

	int result;
	p->m_csMap.Enter();

	stdext::hash_map<DWORD,DWORD>::iterator it = p->m_map.find(dwKey);
	if( p->m_map.end() == it )
	{// not blocked
		result = FALSE;
	}
	else
	if( timeGetTime() >= it->second )
	{// not blocked anymore
		p->m_map.erase(dwKey);
		result = FALSE;
	}
	else
	{// still blocked
		result = TRUE;
	}

	p->m_csMap.Leave();
	return result;
}
