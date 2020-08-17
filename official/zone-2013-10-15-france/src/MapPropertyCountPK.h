#pragma once
#include "NetLib/MemoryMgr.h"


struct WINPOINT
{
	/* this+0 */ unsigned long AID;
	/* this+4 */ int winpoint;
};


class CMapPropertyCountPK
{
public:
	CMapPropertyCountPK();
	virtual ~CMapPropertyCountPK();

public:
	bool UpdateWinPoint(unsigned long AID, int winpoint);
	bool DeleteWinPoint(unsigned long AID);
	void Reset();
	int GetPCRanking(unsigned long AID);

private:
	/* this+ 0 */ //const CMapPropertyCountPK::`vftable';
	/* this+ 4 */ CMemoryMgr<WINPOINT> m_winpointPool;
	/* this+40 */ std::list<WINPOINT*> m_list;
	/* this+52 */ std::map<unsigned long,WINPOINT*> m_map;

private:
	void DeleteFromList(WINPOINT* p);
	std::list<WINPOINT*>::iterator UpperBound(int winpoint);
	void BroadCastRankingInfo();
	void ClearWinpoint();
};
