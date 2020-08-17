#pragma once
#include "PollTimer.h"
#include "std/map"
#include "std/string"
class CMapRes;


class CMapResMgr
{
	/* this+ 0 */ public: //const CMapRes::`vftable';
	/* this+ 4 */ private: mystd::map<mystd::string,CMapRes*> m_map;
	/* this+16 */ private: CPollTimer m_timer;

	typedef mystd::map<mystd::string,CMapRes*>::const_iterator MAPCONTAINER_ITER;

	public: CMapResMgr::CMapResMgr(void);
	public: virtual CMapResMgr::~CMapResMgr(void);
	public: int CMapResMgr::Init(int ZSID);
	public: CMapRes* CMapResMgr::GetMapRes(const char* mapName);
	public: CMapRes* CMapResMgr::GetFirstMap(void);
	public: int CMapResMgr::UpdateTileInfo(CMapRes* mapRes, int xPos, int yPos, int type, unsigned long exceptAID);
	public: bool CMapResMgr::UpdateWinPoint(CMapRes* mapRes, unsigned int AID, int winpoint);
	public: bool CMapResMgr::DeleteWinPoint(CMapRes* mapRes, unsigned long AID);
	public: int CMapResMgr::GetTotalSectionSize(void);
	public: void CMapResMgr::Process(void);
	public: void CMapResMgr::OnDisoranizeGuild(unsigned long GDID);
	public: void CMapResMgr::UnlinkNPC(void);
	//public: void CMapResMgr::OnChangeEmblem(unsigned long GDID, short ver);
	public: void CMapResMgr::OnDeleteRelated(unsigned long GDID, unsigned long deleted);
	public: bool CMapResMgr::LoadBattleFieldMapInfo(void);
	//public: int CMapResMgr::GetPcRanking(CMapRes* mapRes, unsigned long AID);
	//public: void CMapResMgr::OnChangeGDForce(unsigned long GDID);
	//public: mystd::map<mystd::string,CMapRes *>& CMapResMgr::GetAllMapRes(void);
	//public: bool CMapResMgr::InstantMapAdd(CMapRes* const in_cpMapRes);
	//public: void CMapResMgr::InstantMapRemove(CMapRes* const in_cpMapRes);
	//public: int CMapResMgr::GetServiceMapNum(void);

private:
	static hook_method<int (CMapResMgr::*)(int ZSID)> CMapResMgr::_Init;
	static hook_method<CMapRes* (CMapResMgr::*)(const char* mapName)> CMapResMgr::_GetMapRes;
	static hook_method<CMapRes* (CMapResMgr::*)(void)> CMapResMgr::_GetFirstMap;
	static hook_method<int (CMapResMgr::*)(CMapRes* mapRes, int xPos, int yPos, int type, unsigned long exceptAID)> CMapResMgr::_UpdateTileInfo;
	static hook_method<bool (CMapResMgr::*)(CMapRes* mapRes, unsigned int AID, int winpoint)> CMapResMgr::_UpdateWinPoint;
	static hook_method<bool (CMapResMgr::*)(CMapRes* mapRes, unsigned long AID)> CMapResMgr::_DeleteWinPoint;
	static hook_method<int (CMapResMgr::*)(void)> CMapResMgr::_GetTotalSectionSize;
	static hook_method<void (CMapResMgr::*)(void)> CMapResMgr::_Process;
	static hook_method<void (CMapResMgr::*)(unsigned long GDID)> CMapResMgr::_OnDisoranizeGuild;
	static hook_method<void (CMapResMgr::*)(void)> CMapResMgr::_UnlinkNPC;
	static hook_method<void (CMapResMgr::*)(unsigned long GDID, unsigned long deleted)> CMapResMgr::_OnDeleteRelated;
	static hook_method<bool (CMapResMgr::*)(void)> CMapResMgr::_LoadBattleFieldMapInfo;
};
