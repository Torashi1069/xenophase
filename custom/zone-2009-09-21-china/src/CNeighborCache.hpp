#pragma once
#include "std/vector"
#include "struct.hpp"
#include "NetLib/MemoryMgr.h"
class CPC;


class CNeighborCache
{
public:
	/* this+ 0 */ public: //const CNeighborCache::`vftable'
	/* this+ 4 */ private: mystd::vector<ClientCache*> m_List;
	/* this+20 */ private: CMemoryMgr<ClientCache> m_cacheMPool;

	public: HOOKED CNeighborCache::CNeighborCache(void);
	public: HOOKED virtual CNeighborCache::~CNeighborCache(void);
	public: void CNeighborCache::Reset(void);
	//public: void CNeighborCache::Delete(unsigned long);
	public: mystd::vector<ClientCache*>& CNeighborCache::GetListPoint(void);
	public: int CNeighborCache::GetUpdateInfo(CCharacter* master, CPC* other);
	public: void CNeighborCache::OnMultiCast(CCharacter* master, int len, char* buf, int Range);
	public: CPC* CNeighborCache::FindPC(unsigned long AID);
	public: void CNeighborCache::Init(void);
	public: void CNeighborCache::InitThePCCacheInfo(unsigned long AID);
	public: int CNeighborCache::GetNum(void);
	private: ClientCache* CNeighborCache::Search(unsigned long AID, unsigned long time);
	private: HOOKED ClientCache* CNeighborCache::Insert(CPC* other);
	private: int CNeighborCache::CheckUpdateInfo(ClientCache* cache, CCharacter* master, CPC* other);

private:
	static hook_method<void (CNeighborCache::*)(void)> CNeighborCache::_Reset;
	static hook_method<mystd::vector<ClientCache*>& (CNeighborCache::*)(void)> CNeighborCache::_GetListPoint;
	static hook_method<int (CNeighborCache::*)(CCharacter* master, CPC* other)> CNeighborCache::_GetUpdateInfo;
	static hook_method<void (CNeighborCache::*)(CCharacter* master, int len, char* buf, int Range)> CNeighborCache::_OnMultiCast;
	static hook_method<CPC* (CNeighborCache::*)(unsigned long AID)> CNeighborCache::_FindPC;
	static hook_method<void (CNeighborCache::*)(void)> CNeighborCache::_Init;
	static hook_method<void (CNeighborCache::*)(unsigned long AID)> CNeighborCache::_InitThePCCacheInfo;
	static hook_method<int (CNeighborCache::*)(void)> CNeighborCache::_GetNum;
	static hook_method<ClientCache* (CNeighborCache::*)(unsigned long AID, unsigned long time)> CNeighborCache::_Search;
	static hook_method<ClientCache* (CNeighborCache::*)(CPC* other)> CNeighborCache::_Insert;
	static hook_method<int (CNeighborCache::*)(ClientCache* cache, CCharacter* master, CPC* other)> CNeighborCache::_CheckUpdateInfo;
};
