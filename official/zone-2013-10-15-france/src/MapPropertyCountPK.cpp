#include "CharacterMgr.h"
#include "MapPropertyCountPK.h"


CMapPropertyCountPK::CMapPropertyCountPK()
{
	m_winpointPool.CMemoryMgr<WINPOINT>::Init(256);
}


CMapPropertyCountPK::~CMapPropertyCountPK()
{
	this->CMapPropertyCountPK::Reset();
}


void CMapPropertyCountPK::Reset()
{
	this->CMapPropertyCountPK::ClearWinpoint();
}


std::list<WINPOINT*>::iterator CMapPropertyCountPK::UpperBound(int winpoint)
{
	int count = m_list.size();
	std::list<WINPOINT*>::iterator it = m_list.begin();

	while( count > 0 )
	{
		std::list<WINPOINT*>::iterator mid = it;
		std::advance(mid, count / 2);

		if( (*mid)->winpoint <= winpoint )
		{
			count = count / 2;
		}
		else
		{
			it = ++mid;
			count -= count / 2 + 1;
		}
	}

	return it;
}


void CMapPropertyCountPK::DeleteFromList(WINPOINT* p)
{
	std::list<WINPOINT*>::iterator it = this->CMapPropertyCountPK::UpperBound(p->winpoint);
	while( (*it)->AID != p->AID ) //FIXME: no list bounds check, assumes item exists
		++it;
	m_list.erase(it);
}


bool CMapPropertyCountPK::UpdateWinPoint(unsigned long AID, int winpoint)
{
	WINPOINT* p;

	std::map<unsigned long,WINPOINT*>::iterator it = m_map.find(AID);
	if( it == m_map.end() )
	{
		if( m_map.size() >= 256 )
			return false;

		p = m_winpointPool.CMemoryMgr<WINPOINT>::Alloc();
		if( p == NULL )
			return 0;

		p->AID = AID;
		m_map.insert(std::pair<const unsigned long,WINPOINT*>(AID, p));
	}
	else
	{
		p = it->second;
		this->CMapPropertyCountPK::DeleteFromList(p);
	}

	p->winpoint = winpoint;

	std::list<WINPOINT*>::iterator i = this->CMapPropertyCountPK::UpperBound(winpoint - 1);
	m_list.insert(i, p);

	this->CMapPropertyCountPK::BroadCastRankingInfo();

	return true;
}


void CMapPropertyCountPK::BroadCastRankingInfo()
{
	int winpoint = -1;
	int total = m_list.size();

	int i = 0;
	int j = 1;
	for( std::list<WINPOINT*>::iterator it = m_list.begin(); it != m_list.end(); ++it )
	{
		if( winpoint == (*it)->winpoint )
		{
			if( i == 1 )
				i = 2;
			else
				++j;
		}
		else
		{
			i += j;
			j = 1;
			winpoint = (*it)->winpoint;
		}

		if( CCharacterMgr::GetObj()->CCharacterMgr::SendMsg(NULL, (*it)->AID, CM_RANKINGINFO, i, total, 0, 0) != 0 )
		{
			std::map<unsigned long,WINPOINT*>::iterator iM = m_map.find((*it)->AID);
			if( iM != m_map.end() )
			{
				m_winpointPool.CMemoryMgr<WINPOINT>::Free(iM->second);
				m_map.erase(iM);
				it = m_list.erase(it); //FIXME: next item will get skipped
			}
		}
	}
}


bool CMapPropertyCountPK::DeleteWinPoint(unsigned long AID)
{
	std::map<unsigned long,WINPOINT*>::iterator it = m_map.find(AID);
	if( it == m_map.end() )
		return false;

	WINPOINT* p = it->second;
	this->CMapPropertyCountPK::DeleteFromList(it->second);
	m_map.erase(it);
	m_winpointPool.CMemoryMgr<WINPOINT>::Free(p);

	this->CMapPropertyCountPK::BroadCastRankingInfo();

	return true;
}


void CMapPropertyCountPK::ClearWinpoint()
{
	for( std::map<unsigned long,WINPOINT*>::iterator it = m_map.begin(); it != m_map.end(); ++it )
		m_winpointPool.CMemoryMgr<WINPOINT>::Free(it->second);

	m_map.clear();
	m_list.clear();
}


int CMapPropertyCountPK::GetPCRanking(unsigned long AID)
{
	int i;
	std::list<WINPOINT*>::iterator it;

	for( i = 1, it = m_list.begin(); it != m_list.end(); ++i, ++it )
		if( (*it)->AID == AID )
			return i; // found.

	return -1; // not found.
}
