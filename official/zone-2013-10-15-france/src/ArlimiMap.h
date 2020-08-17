#pragma once
#include "QVar.h"
#include "NetLib/MemoryMgr.h"


struct T_ARLIMI_DATA
{
	/* this+ 0 */ unsigned long t_npcID;
	/* this+ 4 */ bool t_nonNpc;
	/* this+ 8 */ int t_xPos;
	/* this+12 */ int t_yPos;
	/* this+16 */ std::vector<unsigned long> t_questList;
};


struct T_MAP_IN_ARLIMI
{
	/* this+0 */ unsigned long t_mapID;
	/* this+4 */ std::vector<unsigned long> t_npcList;
};


class CArlimiMap
{
private:
	typedef std::map<unsigned long,T_ARLIMI_DATA*> TARLIMI_MAP;
	typedef std::map<unsigned long,T_MAP_IN_ARLIMI*> TMAPINARLIMI;

public:
	CArlimiMap();
	virtual ~CArlimiMap();

private:
	/* this+  0 */ //const CArlimiMap::`vftable';
	/* this+  4 */ CMemoryMgr<T_ARLIMI_DATA> m_pool;
	/* this+ 40 */ CMemoryMgr<T_MAP_IN_ARLIMI> m_maPool;
	/* this+ 76 */ TARLIMI_MAP m_arlimiMap;
	/* this+ 92 */ TMAPINARLIMI m_mapInArlimi;
	/* this+108 */ unsigned int m_index;

public:
	bool Initialize();
	void Filnalize();
	bool LoadArlimiMap(const char* file_name);
	bool AddArlimiMap(std::vector<CQVar> value);
	bool AddMapInArlimi(unsigned long mapID, unsigned int index);
	bool AddArlimiInQuest(unsigned int index, unsigned long npcID, bool mapInNpc, int xPos, int yPos, std::vector<CQVar> data);
	void GetQuestNpcList(unsigned long mapID, std::list<unsigned long>& qNpcList);
	T_ARLIMI_DATA* GetArlimiData(unsigned int index);
};
