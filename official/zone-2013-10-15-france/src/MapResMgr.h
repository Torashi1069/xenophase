#pragma once
class CMapRes;
#include "shared/PollTimer.h"


class CMapResMgr
{
public:
	std::pair<bool,std::string> Init(int ZSID);
	CMapRes* GetMapRes(const char* mapName);
	CMapRes* GetFirstMap();
	BOOL UpdateTileInfo(CMapRes* mapRes, int xPos, int yPos, int type, unsigned long exceptAID);
	bool UpdateWinPoint(CMapRes* mapRes, unsigned int AID, int winpoint);
	bool DeleteWinPoint(CMapRes* mapRes, unsigned long AID);
	int GetTotalSectionSize();
	void Process();
	void OnDisoranizeGuild(unsigned long GDID);
	void UnlinkNPC();
	void OnChangeEmblem(unsigned long GDID, short ver);
	void OnDeleteRelated(unsigned long GDID, unsigned long deleted);
	bool LoadBattleFieldMapInfo();
	int GetPcRanking(CMapRes* mapRes, unsigned long AID); //TODO
	void OutputAll() const;
	void OnChangeGDForce(unsigned long GDID);
	bool InstantMapAdd(CMapRes* const in_cpMapRes);
	void InstantMapRemove(CMapRes* const in_cpMapRes);
	int GetServiceMapNum(); //TODO
	std::vector<int> GetServiceMapIDList(); //TODO

public:
	CMapResMgr();
	virtual ~CMapResMgr();

private:
	/* this+ 0 */ //const CMapResMgr::`vftable';
	typedef std::map<std::string,CMapRes*> MAPCONTAINER;
	typedef std::map<std::string,CMapRes*>::iterator MAPCONTAINER_ITER;
	/* this+ 4 */ MAPCONTAINER m_map;
	/* this+20 */ CPollTimer m_timer;
};
