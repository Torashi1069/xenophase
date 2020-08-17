#pragma once
#include "struct.hpp"
#include "std/map"
class CPC;


class CMakerRankMgr
{
	/* this+0x0  */ public: mystd::map<unsigned long,MAKERINFO> m_MakerRankList[7];
	/* this+0x54 */ public: MAKER_RANKING m_MakerRank[7][10];

	//public: void CMakerRankMgr::CMakerRankMgr(void);
	//public: void CMakerRankMgr::~CMakerRankMgr(void);
	public: void CMakerRankMgr::ResetMakerRankList(int type);
	public: void CMakerRankMgr::SortMakerRankList(int type);
	public: void CMakerRankMgr::Get_TOP_MakerRank(int type);
	public: int CMakerRankMgr::UpdateMakerRank(CPC* pc, int type, int value, int& point);
	public: void CMakerRankMgr::GetMakerRank(unsigned long GID, int& point, int JobType);
	public: int CMakerRankMgr::GetMakerPower(unsigned long GID, int type);
	public: void CMakerRankMgr::SetMakerRankList(char* buf);
	public: int CMakerRankMgr::GetRankFromTop10(CPC* pc);

private:
	static hook_method<void (CMakerRankMgr::*)(int type)> CMakerRankMgr::_ResetMakerRankList;
	static hook_method<void (CMakerRankMgr::*)(int type)> CMakerRankMgr::_SortMakerRankList;
	static hook_method<void (CMakerRankMgr::*)(int type)> CMakerRankMgr::_Get_TOP_MakerRank;
	static hook_method<int (CMakerRankMgr::*)(CPC* pc, int type, int value, int& point)> CMakerRankMgr::_UpdateMakerRank;
	static hook_method<void (CMakerRankMgr::*)(unsigned long GID, int& point, int JobType)> CMakerRankMgr::_GetMakerRank;
	static hook_method<int (CMakerRankMgr::*)(unsigned long GID, int type)> CMakerRankMgr::_GetMakerPower;
	static hook_method<void (CMakerRankMgr::*)(char* buf)> CMakerRankMgr::_SetMakerRankList;
	static hook_method<int (CMakerRankMgr::*)(CPC* pc)> CMakerRankMgr::_GetRankFromTop10;
};
