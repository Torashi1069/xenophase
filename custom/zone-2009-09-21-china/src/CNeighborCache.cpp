#include "CNeighborCache.hpp"
#include "CharacterMgr.h"
#include "PC.h"
#include "shared.h" // Trace


/// @patch dynamic client cache memmgr - r2556 r2561
HOOKED CNeighborCache::CNeighborCache(void) // line 10
{
	m_cacheMPool.CMemoryMgr<ClientCache>::Init(DYNAMIC);
}


/// @patch dynamic client cache memmgr - r2556
HOOKED CNeighborCache::~CNeighborCache(void) // line 15
{
	this->CNeighborCache::Reset();
}


hook_method<void (CNeighborCache::*)(void)> CNeighborCache::_Reset(SERVER, "CNeighborCache::Reset");
void CNeighborCache::Reset(void) // line 120
{
	return (this->*_Reset)();

	mystd::vector<ClientCache*>::iterator it = m_List.begin();
	while( it != m_List.end() )
	{
		m_cacheMPool.CMemoryMgr<ClientCache>::Free(*it);
		it = m_List.erase(it);
	}

	m_cacheMPool.CMemoryMgr<ClientCache>::Reset();
}


hook_method<mystd::vector<ClientCache*>& (CNeighborCache::*)(void)> CNeighborCache::_GetListPoint(SERVER, "CNeighborCache::GetListPoint");
mystd::vector<ClientCache*>& CNeighborCache::GetListPoint(void) // line 202
{
	return (this->*_GetListPoint)();

	return m_List;
}


hook_method<int (CNeighborCache::*)(CCharacter* master, CPC* other)> CNeighborCache::_GetUpdateInfo(SERVER, "CNeighborCache::GetUpdateInfo");
int CNeighborCache::GetUpdateInfo(CCharacter* master, CPC* other) // line 77
{
	return (this->*_GetUpdateInfo)(master, other);

	ClientCache* cache1 = this->CNeighborCache::Search(other->GetAccountID(), other->m_characterTimeInfo.connectedTime);
	if( cache1 != NULL )
		return this->CNeighborCache::CheckUpdateInfo(cache1, master, other);

	ClientCache* cache2 = this->CNeighborCache::Insert(other);
	if( cache2 != NULL )
		return this->CNeighborCache::CheckUpdateInfo(cache2, master, other);

	return -1;
}


hook_method<void (CNeighborCache::*)(CCharacter* master, int len, char* buf, int Range)> CNeighborCache::_OnMultiCast(SERVER, "CNeighborCache::OnMultiCast");
void CNeighborCache::OnMultiCast(CCharacter* master, int len, char* buf, int Range) // line 131
{
	return (this->*_OnMultiCast)(master, len, buf, Range);

	if( master == NULL )
	{
		Trace("Vital Error OnMultiCast CNPC\n");
		return;
	}

	mystd::vector<ClientCache*>::iterator it = m_List.begin();
	while( it != m_List.end() )
	{
		CPC* other = g_characterMgr->CCharacterMgr::FindCharacterByIndex((*it)->AID, (*it)->Index);
		if( other && other->m_characterTimeInfo.connectedTime == (*it)->ConnectedTime )
		{
			if( master->IsMyArea(other, Range) )
				if( other->m_pcClientUpdater.CPCClientUpdater::IsSendable() )
					other->CPC::Send(len, buf);

			++it;
		}
		else
		{
			m_cacheMPool.CMemoryMgr<ClientCache>::Free(*it);
			it = m_List.erase(it);
		}
	}
}


hook_method<CPC* (CNeighborCache::*)(unsigned long AID)> CNeighborCache::_FindPC(SERVER, "CNeighborCache::FindPC");
CPC* CNeighborCache::FindPC(unsigned long AID) // line 189
{
	return (this->*_FindPC)(AID);

	for( mystd::vector<ClientCache*>::iterator it = m_List.begin(); it != m_List.end(); ++it )
		if( (*it)->AID == AID )
			return g_characterMgr->CCharacterMgr::FindCharacterByIndex((*it)->AID, (*it)->Index);

	return NULL;
}


hook_method<void (CNeighborCache::*)(void)> CNeighborCache::_Init(SERVER, "CNeighborCache::Init");
void CNeighborCache::Init(void) // line 21
{
	return (this->*_Init)();

	this->CNeighborCache::Reset();
}


hook_method<void (CNeighborCache::*)(unsigned long AID)> CNeighborCache::_InitThePCCacheInfo(SERVER, "CNeighborCache::InitThePCCacheInfo");
void CNeighborCache::InitThePCCacheInfo(unsigned long AID) // line 174
{
	return (this->*_InitThePCCacheInfo)(AID);

	mystd::vector<ClientCache*>::iterator it;
	for( it = m_List.begin(); it != m_List.end(); ++it )
		if( (*it)->AID == AID )
			(*it)->MoveLastTime = 0;
}


//hook_method<int (CNeighborCache::*)(void)> CNeighborCache::_GetNum(SERVER, "CNeighborCache::GetNum");
int CNeighborCache::GetNum(void) // line ???
{
//	return (this->*_GetNum)();

	return m_List.size();
}


hook_method<ClientCache* (CNeighborCache::*)(unsigned long AID, unsigned long time)> CNeighborCache::_Search(SERVER, "CNeighborCache::Search");
ClientCache* CNeighborCache::Search(unsigned long AID, unsigned long time) // line 51
{
	return (this->*_Search)(AID, time);

	mystd::vector<ClientCache*>::iterator it = m_List.begin();
	while( it != m_List.end() )
	{
		if( (*it)->AID == AID && (*it)->ConnectedTime == time )
			break; // found

		if( (*it)->AID == AID )
		{
			m_cacheMPool.CMemoryMgr<ClientCache>::Free(*it);
			it = m_List.erase(it);
		}
		else
		{
			++it;
		}
	}

	if( it == m_List.end() )
		return NULL;

	if( g_characterMgr->CCharacterMgr::FindCharacterByIndex(AID, (*it)->Index) == NULL )
	{
		m_cacheMPool.CMemoryMgr<ClientCache>::Free(*it);
		it = m_List.erase(it);
		return NULL;
	}

	return *it;
}


/// @patch dynamic client cache memmgr - r2556
hook_method<ClientCache* (CNeighborCache::*)(CPC* other)> CNeighborCache::_Insert(SERVER, "CNeighborCache::Insert");
HOOKED ClientCache* CNeighborCache::Insert(CPC* other) // line 25
{
//	return (this->*_Insert)(other);

	if( m_List.size() >= 0xF8 )
	{
		mystd::vector<ClientCache*>::iterator it = m_List.begin();
		while( it != m_List.end() )
		{
			if( (*it)->MoveLastTime != 0 && g_characterMgr->CCharacterMgr::FindCharacterByIndex((*it)->AID, (*it)->Index) != NULL )
			{
				++it;
			}
			else
			{
				m_cacheMPool.CMemoryMgr<ClientCache>::Free(*it);
				it = m_List.erase(it);
			}
		}
	}

	ClientCache* cache = m_cacheMPool.CMemoryMgr<ClientCache>::Alloc();
	if( cache == NULL )
		return NULL;

	cache->AID = other->GetAccountID();
	cache->ConnectedTime = other->m_characterTimeInfo.connectedTime;
	cache->MoveLastTime = 0;
	cache->Index = other->m_index;
	m_List.push_back(cache);

	return cache;
}


hook_method<int (CNeighborCache::*)(ClientCache* cache, CCharacter* master, CPC* other)> CNeighborCache::_CheckUpdateInfo(SERVER, "CNeighborCache::CheckUpdateInfo");
int CNeighborCache::CheckUpdateInfo(ClientCache* cache, CCharacter* master, CPC* other) // line 92
{
	return (this->*_CheckUpdateInfo)(cache, master, other);

	int x;
	int y;
	int moveReqTime;
	int state;

	master->GetParameterValue(VAR_CURXPOS, x);
	master->GetParameterValue(VAR_CURYPOS, y);
	master->GetParameterValue(VAR_MOVEREQTIME, moveReqTime);
	master->GetParameterValue(VAR_STATE, state);

	if( abs(x - other->m_pathInfo.m_moveInfo.xPos) >= 15 || abs(y - other->m_pathInfo.m_moveInfo.yPos) >= 15 )
	{
		if( cache->MoveLastTime != 0 )
		{
			cache->MoveLastTime = 0;
			return CHARACTER_STATE_EXIT;
		}
	}
	else
	{
		if( cache->MoveLastTime != moveReqTime && (DWORD)moveReqTime <= timeGetTime() )
		{
			cache->MoveLastTime = moveReqTime;
			return state;
		}

		if( other->GetState() == CHARACTER_STATE_ENTER )
			return state;
	}

	return -1;
}
