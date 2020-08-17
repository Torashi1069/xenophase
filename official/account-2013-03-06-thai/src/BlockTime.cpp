#include "Account.h"
#include "BlockTime.h"
#include "Common/EnterTraceLog.h"
#include "Common/Thread.h"


/// singleton instance
static CBlockTime g_BlockTime;
CBlockTime* CSingleton<CBlockTime>::ms_Singleton;


CBlockTime::CBlockTime()
{
	CreateMemberThread<CBlockTime>(this, &CBlockTime::threadBlockTime, NULL);
}


CBlockTime::~CBlockTime()
{
}


void CBlockTime::UpdateBlockTime(DWORD dwKey, DWORD dwBlockTime)
{
	int nHash = dwKey % 100;
	if( nHash < 0 )
		return;

	m_csBlockTime[nHash].Enter();

	for( std::list<SBLOCKTIME>::iterator it = m_listBlockTime[nHash].begin(); it != m_listBlockTime[nHash].end(); ++it )
	{
		if( it->m_dwKey == dwKey )
		{
			m_listBlockTime[nHash].erase(it);
			break;
		}
	}

	SBLOCKTIME blockTime;
	blockTime.m_dwKey = dwKey;
	blockTime.m_dwBlockTime = timeGetTime() + dwBlockTime;
	m_listBlockTime[nHash].push_back(blockTime);

	m_csBlockTime[nHash].Leave();
}


// guessed
void CBlockTime::DeleteBlockTime(DWORD dwKey)
{
	int nHash = dwKey % 100;

	m_csBlockTime[nHash].Enter();

	for( std::list<SBLOCKTIME>::iterator it = m_listBlockTime[nHash].begin(); it != m_listBlockTime[nHash].end(); ++it )
	{
		if( it->m_dwKey == dwKey )
		{
			m_listBlockTime[nHash].erase(it);
			break;
		}
	}

	m_csBlockTime[nHash].Leave();
}


BOOL CBlockTime::IsBlock(DWORD dwKey)
{
	int nHash = dwKey % 100;
	if( nHash < 0 )
		return FALSE;

	BOOL result;
	m_csBlockTime[nHash].Enter();

	std::list<SBLOCKTIME>::const_iterator it;
	for( it = m_listBlockTime[nHash].begin(); it != m_listBlockTime[nHash].end(); ++it )
		if( it->m_dwKey == dwKey )
			break;

	result = ( it != m_listBlockTime[nHash].end() ) ? TRUE : FALSE;

	m_csBlockTime[nHash].Leave();
	return result;
}


void CBlockTime::threadBlockTime(void* lpParam)
{
	while( g_bProcessPermit )
	{
		for( int i = 0; i < 100; ++i )
		{
			Sleep(2);

			m_csBlockTime[i].Enter();

			for( std::list<SBLOCKTIME>::iterator it = m_listBlockTime[i].begin(); it != m_listBlockTime[i].end(); ++it )
			{
				if( timeGetTime() > it->m_dwBlockTime )
				{
					m_listBlockTime[i].erase(it);
					break;
				}
			}

			m_csBlockTime[i].Leave();
		}
	}

	CEnterTraceLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__, "CBlockTime::threadBlockTime out\n");
}
