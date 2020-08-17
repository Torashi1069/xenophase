#pragma once
#include "std/vector"
class CCharacter;
class CMapRes;
struct NEIGHBORHOOD_SECTION;


class CSectionMgr
{
	/* this+ 0 */ public: //const CSectionMgr::`vftable';
	/* this+ 4 */ private: int m_w;
	/* this+ 8 */ private: int m_h;
	/* this+12 */ private: int m_scale;
	/* this+16 */ private: mystd::vector<CCharacter*>** m_sectionList;
	/* this+20 */ private: const CMapRes* m_mapRes;
	/* this+24 */ private: char m_mapName[15+1];
	/* this+40 */ private: int m_MaxSectionList;

	public: CSectionMgr::CSectionMgr(void);
	public: virtual CSectionMgr::~CSectionMgr(void);
	public: void CSectionMgr::Init(const char* mapName, int w, int h, int scale, const CMapRes* mapRes);
	public: mystd::vector<CCharacter*>* CSectionMgr::GetSectionByCellPos(int x, int y);
	public: int CSectionMgr::GetEmptyPosition(unsigned long AID, int& xPos, int& yPos);
	public: int CSectionMgr::AddCharacter(int x, int y, CCharacter* ch);
	public: void CSectionMgr::RemoveCharacter(CCharacter* ch);
	public: int CSectionMgr::GetTotalSectionSize(void);
	public: int CSectionMgr::MoveCharacter(mystd::vector<CCharacter*>* src, mystd::vector<CCharacter*>* dst, CCharacter* ch);
	//public: int CSectionMgr::MoveChracter(mystd::vector<CCharacter*>* src, mystd::vector<CCharacter*>::iterator& iter, int x, int y, CCharacter* ch);
	public: void CSectionMgr::GetNeighborhoodSections(int x, int y, int range, NEIGHBORHOOD_SECTION* result);
	public: int CSectionMgr::GetSectionSize(void);
	public: mystd::vector<CCharacter*>** CSectionMgr::GetSectionList(void);
	private: int CSectionMgr::IsEmptyPos(unsigned long AID, int xPos, int yPos);
	private: mystd::vector<CCharacter*>* CSectionMgr::GetSectionListPtr(const int in_X, const int in_Y, const int in_Range, const int in_Idx);

private:
	static hook_method<void (CSectionMgr::*)(const char* mapName, int w, int h, int scale, const CMapRes* mapRes)> CSectionMgr::_Init;
	static hook_method<mystd::vector<CCharacter*>* (CSectionMgr::*)(int x, int y)> CSectionMgr::_GetSectionByCellPos;
	static hook_method<int (CSectionMgr::*)(unsigned long AID, int& xPos, int& yPos)> CSectionMgr::_GetEmptyPosition;
	static hook_method<int (CSectionMgr::*)(int x, int y, CCharacter* ch)> CSectionMgr::_AddCharacter;
	static hook_method<void (CSectionMgr::*)(CCharacter* ch)> CSectionMgr::_RemoveCharacter;
	static hook_method<int (CSectionMgr::*)(void)> CSectionMgr::_GetTotalSectionSize;
	static hook_method<int (CSectionMgr::*)(mystd::vector<CCharacter*>* src, mystd::vector<CCharacter*>* dst, CCharacter* ch)> CSectionMgr::_MoveCharacter;
	static hook_method<void (CSectionMgr::*)(int x, int y, int range, NEIGHBORHOOD_SECTION* result)> CSectionMgr::_GetNeighborhoodSections;
	static hook_method<int (CSectionMgr::*)(void)> CSectionMgr::_GetSectionSize;
	static hook_method<mystd::vector<CCharacter*>** (CSectionMgr::*)(void)> CSectionMgr::_GetSectionList;
	static hook_method<int (CSectionMgr::*)(unsigned long AID, int xPos, int yPos)> CSectionMgr::_IsEmptyPos;
	static hook_method<mystd::vector<CCharacter*>* (CSectionMgr::*)(const int in_X, const int in_Y, const int in_Range, const int in_Idx)> CSectionMgr::_GetSectionListPtr;

	friend class CMapRes;
};
