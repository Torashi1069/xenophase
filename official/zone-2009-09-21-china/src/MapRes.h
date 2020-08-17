#pragma once
#include "CMapPropertyCountPK.hpp"
#include "MapTypeProperty.h"
#include "PathFinder.h"
#include "SectionMgr.h"
struct BROADCAST_INFO;


class CMapRes
{
	struct vtable_t // const CMapRes::`vftable'
	{
		const bool (CMapRes::* isInstantMap)(void) const;
		void* (CMapRes::* scalar_deleting_destructor)(unsigned int flags);
		int (CMapRes::* Load)(const char* filename, int mapID, int mapType);
		void (CMapRes::* Reset)(void);
		void (CMapRes::* OnTimer)(void);
		unsigned long (CMapRes::* GetGDID)(void);
		int (CMapRes::* AddCharacter)(int xCellPos, int yCellPos, CCharacter* character);
		mystd::string (CMapRes::* GetLoadFileName)(void);
		bool (CMapRes::* IsBattleField)(void);
		bool (CMapRes::* IsAgit)(void);
	};

	/* this+   0 */ public: //const CMapRes::`vftable';
	/* this+   4 */ private: CMapTypeProperty& m_Property;
	/* this+   8 */ private: int m_height;
	/* this+  12 */ private: int m_width;
	/* this+  16 */ private: unsigned char* m_TileInfo;
	/* this+  20 */ private: int m_mapType;
	/* this+  24 */ private: int m_mapID;
	/* this+  28 */ private: char m_mapName[16];
	/* this+  44 */ private: CPathFinder m_pathFinder;
	/* this+1768 */ private: CSectionMgr m_sectionMgr;
	/* this+1812 */ private: int m_pcCount;
	/* this+1816 */ private: CMapPropertyCountPK* m_mapPropertyCountPK;

	public: virtual const bool CMapRes::isInstantMap(void) const;
	public: CMapRes::CMapRes(const int in_mapType);
	public: virtual CMapRes::~CMapRes(void);
	public: bool CMapRes::IsPropertyBlockSkill(const int in_SKID, const int in_ObjType);
	public: bool CMapRes::IsPropertyBlockItem(const int in_ITID);
	public: bool CMapRes::IsPropertyBlockEquipItem(const int in_ITID);
	public: bool CMapRes::IsPropertyBlockBuff(const int in_BuffID);
	public: int CMapRes::GetPropertyTrapDurationPercent(const int in_SKID);
	public: int CMapRes::GetSkillDamagePercent(const int in_SKID);
	public: void CMapRes::GetProprtyByteArray(unsigned char* out_pArray, const int in_MaxLength);
	public: virtual int CMapRes::Load(const char* filename, int mapID, int mapType);
	public: virtual void CMapRes::Reset(void);
	public: virtual void CMapRes::OnTimer(void);
	public: virtual unsigned long CMapRes::GetGDID(void);
	public: const char* CMapRes::GetName(void) const;
	public: int CMapRes::GetID(void);
	public: int CMapRes::GetType(void);
	public: int CMapRes::GetHeight(void) const;
	public: int CMapRes::GetWidth(void) const;
	public: void CMapRes::GetRandomPos(int& xPos, int& yPos, int minDis, int maxDis, unsigned long AID);
	public: int CMapRes::GetRandomPos(int& xPos, int& yPos);
	public: int CMapRes::GetRandomPosByRange(int& xPos, int& yPos, int xRange, int yRange, unsigned long AID);
	public: int CMapRes::GetRandomPosExceptWarp(int& xPos, int& yPos);
	public: int CMapRes::UpdateTileInfo(int x, int y, int flag);
	public: int CMapRes::IsItPossible(int property);
	public: void CMapRes::Broadcast(BROADCAST_INFO* info);
	public: void CMapRes::Send(int len, const char* buf, int broadcastType, int data);
	public: int CMapRes::IsWaterCell(int x, int y);
	public: int CMapRes::IsMovableCell(int x, int y) const;
	public: int CMapRes::IsConnected(int sx, int sy, int dx, int dy);
	public: int CMapRes::IsArrowCrossCell(int x, int y);
	public: int CMapRes::IsDirectPath(int x1, int y1, int x2, int y2, int isClose);
	public: int CMapRes::IsValidPosition(int x, int y);
	public: int CMapRes::IsExsistCells(int xPos, int yPos, int range, unsigned long property);
	public: int CMapRes::IsValidCell(int xPos, int yPos) const;
	public: mystd::vector<CCharacter *>* CMapRes::GetSectionByCellPos(int xCellPos, int yCellPos);
	public: int CMapRes::GetEmptyPosition(unsigned long AID, int& xPos, int& yPos);
	public: virtual int CMapRes::AddCharacter(int xCellPos, int yCellPos, CCharacter* character);
	public: void CMapRes::RemoveCharacter(CCharacter* character);
	public: int CMapRes::GetTotalSectionSize(void);
	public: int CMapRes::MoveCharacter(mystd::vector<CCharacter *>* src, mystd::vector<CCharacter *>* dest, CCharacter* character);
	//public: int CMapRes::MoveChracter(mystd::vector<CCharacter *>*, mystd::vector<CCharacter *>::iterator&, int, int, CCharacter*);
	public: void CMapRes::GetNeighborhoodSections(int xPos, int yPos, int range, NEIGHBORHOOD_SECTION* result);
	public: int CMapRes::GetSectionSize(void);
	public: mystd::vector<CCharacter *>** CMapRes::GetSectionList(void);
	public: int CMapRes::FindPath(unsigned long startTime, int sx, int sy, int xM, int yM, int dx, int dy, int speedFactor, CPathInfo* result);
	public: int CMapRes::IsEmptyPos(unsigned long AID, int xPos, int yPos);
	public: int CMapRes::GetCellType(int x, int y);
	public: bool CMapRes::IsVillage(void);
	public: void CMapRes::SectionMgrInit(void);
	public: virtual mystd::string CMapRes::GetLoadFileName(void);
	public: virtual bool CMapRes::IsBattleField(void);
	public: virtual bool CMapRes::IsAgit(void);
	public: bool CMapRes::AllocMapPropertyCountPK(void);
	public: bool CMapRes::UpdateWinPoint(unsigned long AID, int winpoint);
	public: bool CMapRes::DeleteWinPoint(unsigned long AID);
	private: unsigned char CMapRes::GetTileInfo(int xPos, int yPos) const;

private:
	static hook_method<bool (CMapRes::*)(const int in_SKID, const int in_ObjType)> CMapRes::_IsPropertyBlockSkill;
	static hook_method<bool (CMapRes::*)(const int in_ITID)> CMapRes::_IsPropertyBlockItem;
	static hook_method<bool (CMapRes::*)(const int in_ITID)> CMapRes::_IsPropertyBlockEquipItem;
	static hook_method<bool (CMapRes::*)(const int in_BuffID)> CMapRes::_IsPropertyBlockBuff;
	static hook_method<int (CMapRes::*)(const int in_SKID)> CMapRes::_GetPropertyTrapDurationPercent;
	static hook_method<int (CMapRes::*)(const int in_SKID)> CMapRes::_GetSkillDamagePercent;
	static hook_method<bool (CMapRes::*)(void) const> CMapRes::_isInstantMap;
	static hook_method<void (CMapRes::*)(unsigned char* out_pArray, const int in_MaxLength)> CMapRes::_GetProprtyByteArray;
	static hook_method<int (CMapRes::*)(const char* filename, int mapID, int mapType)> CMapRes::_Load;
	static hook_method<void (CMapRes::*)(void)> CMapRes::_Reset;
	static hook_method<void (CMapRes::*)(void)> CMapRes::_OnTimer;
	static hook_method<unsigned long (CMapRes::*)(void)> CMapRes::_GetGDID;
	static hook_method<const char* (CMapRes::*)(void) const> CMapRes::_GetName;
	static hook_method<int (CMapRes::*)(void)> CMapRes::_GetID;
	static hook_method<int (CMapRes::*)(void)> CMapRes::_GetType;
	static hook_method<int (CMapRes::*)(void) const> CMapRes::_GetHeight;
	static hook_method<int (CMapRes::*)(void) const> CMapRes::_GetWidth;
	static hook_method<void (CMapRes::*)(int& xPos, int& yPos, int minDis, int maxDis, unsigned long AID)> CMapRes::_GetRandomPos;
	static hook_method<int (CMapRes::*)(int& xPos, int& yPos)> CMapRes::_GetRandomPos2;
	static hook_method<int (CMapRes::*)(int& xPos, int& yPos, int xRange, int yRange, unsigned long AID)> CMapRes::_GetRandomPosByRange;
	static hook_method<int (CMapRes::*)(int& xPos, int& yPos)> CMapRes::_GetRandomPosExceptWarp;
	static hook_method<int (CMapRes::*)(int x, int y, int flag)> CMapRes::_UpdateTileInfo;
	static hook_method<int (CMapRes::*)(int property)> CMapRes::_IsItPossible;
	static hook_method<void (CMapRes::*)(BROADCAST_INFO* info)> CMapRes::_Broadcast;
	static hook_method<void (CMapRes::*)(int len, const char* buf, int broadcastType, int data)> CMapRes::_Send;
	static hook_method<int (CMapRes::*)(int x, int y)> CMapRes::_IsWaterCell;
	static hook_method<int (CMapRes::*)(int x, int y) const> CMapRes::_IsMovableCell;
	static hook_method<int (CMapRes::*)(int sx, int sy, int dx, int dy)> CMapRes::_IsConnected;
	static hook_method<int (CMapRes::*)(int x, int y)> CMapRes::_IsArrowCrossCell;
	static hook_method<int (CMapRes::*)(int x1, int y1, int x2, int y2, int isClose)> CMapRes::_IsDirectPath;
	static hook_method<int (CMapRes::*)(int x, int y)> CMapRes::_IsValidPosition;
	static hook_method<int (CMapRes::*)(int xPos, int yPos, int range, unsigned long property)> CMapRes::_IsExsistCells;
	static hook_method<int (CMapRes::*)(int xPos, int yPos) const> CMapRes::_IsValidCell;
	static hook_method<mystd::vector<CCharacter *>* (CMapRes::*)(int xCellPos, int yCellPos)> CMapRes::_GetSectionByCellPos;
	static hook_method<int (CMapRes::*)(unsigned long AID, int& xPos, int& yPos)> CMapRes::_GetEmptyPosition;
	static hook_method<int (CMapRes::*)(int xCellPos, int yCellPos, CCharacter* character)> CMapRes::_AddCharacter;
	static hook_method<void (CMapRes::*)(CCharacter* character)> CMapRes::_RemoveCharacter;
	static hook_method<int (CMapRes::*)(void)> CMapRes::_GetTotalSectionSize;
	static hook_method<int (CMapRes::*)(mystd::vector<CCharacter *>* src, mystd::vector<CCharacter *>* dest, CCharacter* character)> CMapRes::_MoveCharacter;
	static hook_method<void (CMapRes::*)(int xPos, int yPos, int range, NEIGHBORHOOD_SECTION* result)> CMapRes::_GetNeighborhoodSections;
	static hook_method<int (CMapRes::*)(void)> CMapRes::_GetSectionSize;
	static hook_method<mystd::vector<CCharacter *>** (CMapRes::*)(void)> CMapRes::_GetSectionList;
	static hook_method<int (CMapRes::*)(unsigned long startTime, int sx, int sy, int xM, int yM, int dx, int dy, int speedFactor, CPathInfo* result)> CMapRes::_FindPath;
	static hook_method<int (CMapRes::*)(unsigned long AID, int xPos, int yPos)> CMapRes::_IsEmptyPos;
	static hook_method<int (CMapRes::*)(int x, int y)> CMapRes::_GetCellType;
	static hook_method<bool (CMapRes::*)(void)> CMapRes::_IsVillage;
	static hook_method<void (CMapRes::*)(void)> CMapRes::_SectionMgrInit;
	static hook_method<mystd::string (CMapRes::*)(void)> CMapRes::_GetLoadFileName;
	static hook_method<bool (CMapRes::*)(void)> CMapRes::_IsBattleField;
	static hook_method<bool (CMapRes::*)(void)> CMapRes::_IsAgit;
	static hook_method<bool (CMapRes::*)(void)> CMapRes::_AllocMapPropertyCountPK;
	static hook_method<bool (CMapRes::*)(unsigned long AID, int winpoint)> CMapRes::_UpdateWinPoint;
	static hook_method<bool (CMapRes::*)(unsigned long AID)> CMapRes::_DeleteWinPoint;
	static hook_method<unsigned char (CMapRes::*)(int xPos, int yPos) const> CMapRes::_GetTileInfo;
};
