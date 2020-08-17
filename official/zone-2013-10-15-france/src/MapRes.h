#pragma once
#include "MapPropertyCountPK.h"
#include "MapResScheduler.h"
#include "MapTypeProperty.h"
#include "PathFinder.h"
#include "SectionMgr.h"


enum enumCLICELLTYPE /// @custom
{
	CLI_CELL_GROUND = 0,
	CLI_CELL_WALL   = 1,
	CLI_CELL_2      = 2,
	CLI_CELL_3      = 3,
	CLI_CELL_4      = 4,
	CLI_CELL_GAP    = 5,
	CLI_CELL_6      = 6,
};


enum enumSVRCELLTYPE
{
	SVR_CELL_BLOCK = 1,
	SVR_CELL_ARROW = 2,
	SVR_CELL_WATER = 4,
};


struct BROADCAST_INFO
{
	/* this+ 0 */ short packetType;
	/* this+ 2 */ short broadcastType;
	/* this+ 4 */ unsigned long fontColor;
	/* this+ 8 */ short fontType;
	/* this+10 */ short fontSize;
	/* this+12 */ short fontAlign;
	/* this+14 */ short fontY;
	/* this+16 */ char* str;
	/* this+20 */ int extra;
};


struct stMobTombInfo
{
	stMobTombInfo()
	: Dead_hour(0), Dead_min(0), MPV_Name(), Mob_Name()
	{
	}

	stMobTombInfo(const short in_Dead_hour, const short in_Dead_min, const std::string& in_MPV_Name, const std::string& in_Mob_Name)
	: Dead_hour(in_Dead_hour), Dead_min(in_Dead_min), MPV_Name(in_MPV_Name), Mob_Name(in_Mob_Name)
	{
	}

	/* this+ 0 */ short Dead_hour;
	/* this+ 2 */ short Dead_min;
	/* this+ 4 */ std::string MPV_Name;
	/* this+32 */ std::string Mob_Name;
};


class CMapRes
{
public:
	virtual const bool isInstantMap() const;
	bool IsPropertyBlockSkill(const int in_SKID, const int in_ObjType);
	bool IsPropertyBlockItem(const int in_ITID);
	bool IsPropertyBlockEquipItem(const int in_ITID);
	bool IsPropertyBlockBuff(const int in_BuffID);
	int GetPropertyTrapDurationPercent(const int in_SKID);
	int GetSkillDamagePercent(const int in_SKID);
	void GetProprtyByteArray(BYTE* out_pArray, const int in_MaxLength);

public:
	CMapRes(const int in_mapType);
	virtual ~CMapRes();

public:
	virtual BOOL Load(const char* filename, int mapID, int mapType);
	virtual void Reset();
	virtual void OnTimer();
	virtual unsigned long GetGDID();
	const char* GetName() const;
	int GetID() const;
	int GetType() const;
	int GetHeight() const;
	int GetWidth() const;
	BOOL GetRandomPos(int& xPos, int& yPos);
	void GetRandomPos(int& xPos, int& yPos, int minDis, int maxDis, unsigned long AID);
	BOOL GetRandomPosByRange(int& xPos, int& yPos, int xRange, int yRange, unsigned long AID);
	BOOL GetRandomPosExceptWarp(int& io_xPos, int& io_yPos);
	BOOL GetValidPos(int& io_xPos, int& io_yPos);
	BOOL UpdateTileInfo(int x, int y, int flag);
	int IsItPossible(int property);
	void Broadcast(const BROADCAST_INFO* in_pBROADCAST_INFO);
	void Send(int len, const char* buf, int broadcastType, int data);
	BOOL IsWaterCell(int x, int y);
	BOOL IsMovableCell(int x, int y) const;
	BOOL IsConnected(int sx, int sy, int dx, int dy);
	BOOL IsArrowCrossCell(int x, int y);
	BOOL IsDirectPath(int x1, int y1, int x2, int y2, BOOL isClose);
	bool IsDirectPath2(const int in_sourceXpos, const int in_sourceYpos, const int in_targetXpos, const int in_targetYpos, const unsigned char in_BlockCellMask);
	BOOL IsValidPosition(int x, int y);
	BOOL IsExsistCells(int xPos, int yPos, int range, unsigned long property);
	BOOL IsValidCell(int xPos, int yPos) const;

	std::vector<CCharacter*>* GetSectionByCellPos(int xCellPos, int yCellPos);
	BOOL GetEmptyPosition(unsigned long AID, int& xPos, int& yPos);
	virtual BOOL AddCharacter(int xCellPos, int yCellPos, CCharacter* character);
	void RemoveCharacter(CCharacter* character);
	int GetTotalSectionSize();
	BOOL MoveCharacter(std::vector<CCharacter*>* src, std::vector<CCharacter*>* dest, CCharacter* character);
	int MoveChracter(std::vector<CCharacter*>* src, std::vector<CCharacter*>::iterator& iter, int x, int y, CCharacter* character);
	void GetNeighborhoodSections(int xPos, int yPos, int range, NEIGHBORHOOD_SECTION* result);
	int GetSectionSize();
	std::vector<CCharacter*>** GetSectionList();

	BOOL FindPath(DWORD startTime, int sx, int sy, int xM, int yM, int dx, int dy, int speedFactor, CPathInfo* result);
	BOOL IsEmptyPos(unsigned long AID, int xPos, int yPos);
	BOOL GetCellType(int x, int y);
	bool IsVillage();
	void SectionMgrInit();
	virtual std::string GetLoadFileName();
	virtual bool IsBattleField();
	virtual bool IsAgit();
	bool AllocMapPropertyCountPK();
	bool UpdateWinPoint(unsigned long AID, int winpoint);
	bool DeleteWinPoint(unsigned long AID);
	void AddMobTombInfo(const unsigned long in_NAID, const short in_hour, const short in_min, const std::string& in_MPVName, const std::string& in_MobName);
	void DeleteMobTombInfo(const unsigned long in_NAID);
	const stMobTombInfo& GetMobTombInfo(const unsigned long in_NAID) const;
	virtual void Process();
	unsigned long InsertSchedule(std::tr1::shared_ptr<MapResScheduler::CTask>& in_TaskPtr);
	void DeleteSchedule(const unsigned long ); //TODO
	MapResScheduler::CTask* GetTask(const unsigned long ); //TODO

private:
	unsigned char GetTileInfo(int xPos, int yPos) const;

private:
	/* this+   0 */ //const CMapRes::`vftable';
	/* this+   4 */ CMapTypeProperty& m_Property;
	/* this+   8 */ int m_height;
	/* this+  12 */ int m_width;
	/* this+  16 */ unsigned char* m_TileInfo; // enumSVRCELLTYPE[]
	/* this+  20 */ int m_mapType; // enumMAPTYPE
	/* this+  24 */ int m_mapID;
	/* this+  28 */ char m_mapName[16];
	/* this+  44 */ CPathFinder m_pathFinder;
	/* this+1772 */ CSectionMgr m_sectionMgr;
	/* this+1816 */ int m_pcCount;
	/* this+1820 */ CMapPropertyCountPK* m_mapPropertyCountPK;
	/* this+1824 */ MapResScheduler::CScheduler m_Scheduler;
	/* this+1844 */ std::map<unsigned long,stMobTombInfo> m_MobTombList;
};
C_ASSERT( sizeof CMapRes == 1860 );
