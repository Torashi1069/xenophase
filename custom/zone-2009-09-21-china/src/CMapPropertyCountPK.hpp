#pragma once
#include "std/list"
#include "std/map"
#include "struct.hpp"
#include "NetLib/MemoryMgr.h"


class CMapPropertyCountPK
{
public:
	struct vtable_t // const CMapPropertyCountPK::`vftable'
	{
		void (CMapPropertyCountPK::* scalar_deleting_destructor)(unsigned int);
	};

	/* this+0x0  */ // const CMapPropertyCountPK::`vftable'
	/* this+0x4  */ CMemoryMgr<WINPOINT> m_winpointPool;
	/* this+0x34 */ mystd::list<WINPOINT*> m_list;
	/* this+0x40 */ mystd::map<unsigned long,WINPOINT*> m_map;

	public: CMapPropertyCountPK::CMapPropertyCountPK(void);
	public: virtual CMapPropertyCountPK::~CMapPropertyCountPK(void);
	public: bool CMapPropertyCountPK::UpdateWinPoint(unsigned long AID, int winpoint);
	public: bool CMapPropertyCountPK::DeleteWinPoint(unsigned long AID);
	public: void CMapPropertyCountPK::Reset(void);
	public: int CMapPropertyCountPK::GetPCRanking(unsigned long AID);
	private: void CMapPropertyCountPK::DeleteFromList(WINPOINT* p);
	private: mystd::list<WINPOINT*>::iterator CMapPropertyCountPK::UpperBound(int winpoint);
	private: void CMapPropertyCountPK::BroadCastRankingInfo(void);
	private: void CMapPropertyCountPK::ClearWinpoint(void);

private:
	static hook_method<bool (CMapPropertyCountPK::*)(unsigned long AID, int winpoint)> CMapPropertyCountPK::_UpdateWinPoint;
	static hook_method<bool (CMapPropertyCountPK::*)(unsigned long AID)> CMapPropertyCountPK::_DeleteWinPoint;
	static hook_method<void (CMapPropertyCountPK::*)(void)> CMapPropertyCountPK::_Reset;
	static hook_method<int (CMapPropertyCountPK::*)(unsigned long AID)> CMapPropertyCountPK::_GetPCRanking;
	static hook_method<void (CMapPropertyCountPK::*)(WINPOINT* p)> CMapPropertyCountPK::_DeleteFromList;
	static hook_method<mystd::list<WINPOINT*>::iterator (CMapPropertyCountPK::*)(int winpoint)> CMapPropertyCountPK::_UpperBound;
	static hook_method<void (CMapPropertyCountPK::*)(void)> CMapPropertyCountPK::_BroadCastRankingInfo;
	static hook_method<void (CMapPropertyCountPK::*)(void)> CMapPropertyCountPK::_ClearWinpoint;
};
