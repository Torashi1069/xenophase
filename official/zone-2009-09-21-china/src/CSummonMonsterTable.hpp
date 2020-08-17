#pragma once
#include "std/map"
#include "std/vector"


class CSummonMonsterTable
{
	struct SUMMON_MONSTER_INFO
	{
		/* this+0x0 */ int monsterType;
		/* this+0x4 */ int monsterAI;
	};

	/* this+0 */ private: mystd::map<int,mystd::vector<CSummonMonsterTable::SUMMON_MONSTER_INFO>*> m_matchMap;

	public: CSummonMonsterTable::CSummonMonsterTable(void);
	public: CSummonMonsterTable::~CSummonMonsterTable(void);
	public: void CSummonMonsterTable::LoadFromFile(const char* fileName);
	public: bool CSummonMonsterTable::GetRandomMatch(int itemID, int& monsterType, int& monsterAI);

private:
	static hook_method<void (CSummonMonsterTable::*)(const char* fileName)> CSummonMonsterTable::_LoadFromFile;
	static hook_method<bool (CSummonMonsterTable::*)(int itemID, int& monsterType, int& monsterAI)> CSummonMonsterTable::_GetRandomMatch;
};
