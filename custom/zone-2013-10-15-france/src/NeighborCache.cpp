#include "NeighborCache.h"


CNeighborCache::CNeighborCache()
{
	m_cacheMPool.CMemoryMgr<ClientCache>::Init(250);
}


CNeighborCache::~CNeighborCache()
{
	this->CNeighborCache::Reset();
}


void CNeighborCache::Init()
{
	this->CNeighborCache::Reset();
}


void CNeighborCache::Reset()
{
	for( std::vector<ClientCache*>::iterator iter = m_List.begin(); iter != m_List.end(); iter = m_List.erase(iter) )
		m_cacheMPool.CMemoryMgr<ClientCache>::Free(*iter);

	m_cacheMPool.CMemoryMgr<ClientCache>::Reset();
}
