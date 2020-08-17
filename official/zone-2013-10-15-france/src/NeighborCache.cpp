#include "CharacterMgr.h"
#include "NeighborCache.h"


CNeighborCache::CNeighborCache()
{
	m_cacheMPool.CMemoryMgr<ClientCache>::Init(250);
}


CNeighborCache::~CNeighborCache()
{
	this->CNeighborCache::Reset();
}


void CNeighborCache::Init() // 21-23
{
	this->CNeighborCache::Reset();
}


void CNeighborCache::Reset() // 121-128
{
	for( std::vector<ClientCache*>::iterator iter = m_List.begin(); iter != m_List.end(); iter = m_List.erase(iter) )
		m_cacheMPool.CMemoryMgr<ClientCache>::Free(*iter);

	m_cacheMPool.CMemoryMgr<ClientCache>::Reset();
}


void CNeighborCache::OnMultiCast(CCharacter* master, int len, char* buf, int Range) // 131-154
{
	if( master == NULL )
		return;

	for( std::vector<ClientCache*>::iterator iter = m_List.begin(); iter != m_List.end(); )
	{
		CPC* pc = CCharacterMgr::GetObj()->CCharacterMgr::FindCharacterByIndex((*iter)->AID, (*iter)->Index);
		if( pc != NULL && pc->m_characterTimeInfo.connectedTime == (*iter)->ConnectedTime )
		{
			if( master->IsMyArea(pc, Range) && pc->m_pcClientUpdater.CPCClientUpdater::IsSendable() )
				pc->Send(len, buf);
			++iter;
		}
		else
		{
			m_cacheMPool.CMemoryMgr<ClientCache>::Free(*iter);
			iter = m_List.erase(iter);
		}
	}
}


std::vector<ClientCache*>& CNeighborCache::GetListPoint() // 202-204
{
	return m_List;
}


int CNeighborCache::GetNum() const // 207-209
{
	return (int)m_List.size();
}
