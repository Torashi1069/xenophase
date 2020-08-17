#pragma once
#include "NetLib/MemoryMgr.h"


struct ClientCache
{
	/* this+ 0 */ int AID;
	/* this+ 4 */ int Index;
	/* this+ 8 */ DWORD MoveLastTime;
	/* this+12 */ DWORD ConnectedTime;
};


class CNeighborCache
{
public:
	CNeighborCache();
	virtual ~CNeighborCache();

public:
	void Reset();
//	void Delete(unsigned long );
//	std::vector<ClientCache*>& GetListPoint();
//	int GetUpdateInfo(CCharacter* , CPC* );
//	void OnMultiCast(CCharacter* , int , char* , int );
//	CPC* FindPC(unsigned long );
	void Init();
//	void InitThePCCacheInfo(unsigned long );
//	int GetNum();

private:
//	ClientCache* Search(unsigned long , unsigned long );
//	ClientCache* Insert(CPC* );
//	int CheckUpdateInfo(ClientCache* , CCharacter* , CPC* );

private:
	/* this+ 0 */ //const CNeighborCache::`vftable';
	/* this+ 4 */ std::vector<ClientCache*> m_List;
	/* this+20 */ CMemoryMgr<ClientCache> m_cacheMPool;
};
