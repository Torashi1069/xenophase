#include "globals.hpp"
#include "FSMMgr.h"
#include "CITPMgr.hpp"
#include "MonParameterMgr.h"
#include "CSummonMonsterTable.hpp"
#include "zoneprocess.h" // GetServerRandom()
#include "shared.h" // Trace


hook_method<void (CSummonMonsterTable::*)(const char* fileName)> CSummonMonsterTable::_LoadFromFile(SERVER, "CSummonMonsterTable::LoadFromFile");
hook_method<bool (CSummonMonsterTable::*)(int itemID, int& monsterType, int& monsterAI)> CSummonMonsterTable::_GetRandomMatch(SERVER, "CSummonMonsterTable::GetRandomMatch");


CSummonMonsterTable::CSummonMonsterTable(void)
{
}


CSummonMonsterTable::~CSummonMonsterTable(void)
{
}


void CSummonMonsterTable::LoadFromFile(const char* fileName)
{
	return (this->*_LoadFromFile)(fileName);

	FILE* fp = fopen(fileName, "r");
	if( fp == NULL )
		return;

	while( !feof(fp) )
	{
		char buf[1024];
		memset(buf, 0, sizeof(buf));

		if( !fgets(buf, sizeof(buf), fp) )
			break;

		// read item name column
		char* v6 = strtok(buf, " \t\n");
		if( v6 == NULL )
			continue;

		char* v8 = strstr(v6, "//");
		if( v8 != NULL )
			continue;

		int itemID = g_itpMgr->CITPMgr::GetITID(v6);
		if( itemID == 0 )
		{
			Trace("CSummonMonsterTable::LoadFromFile, 아이템 %s 가 존재하지 않습니다.\n", v6);
			continue;
		}

		// read monster name column
		char* v10 = strtok(NULL, " \t\n");
		if( v10 == NULL )
			continue;

		unsigned long v12 = g_monParameter->CMonParameterMgr::SearchKeyword(v10);
		if( v12 == -1 )
		{
			Trace("CSummonMonsterTable::LoadFromFile, 몬스터 %s 가 존재하지 않습니다.\n", v10);
			continue;
		}

		// read monster AI column (optional)
		char* v13 = strtok(0, " \t\n");
		unsigned long v15 = ( v13 != NULL ) ? g_fsmMgr->CFSMMgr::GetKeyWord(v13) : 9;
		if( v15 == -1 )
		{
			Trace("CSummonMonsterTable::LoadFromFile, 몬스터 인공지능 %s 가 존재하지 않습니다.\n", v13);
			continue;
		}

		mystd::map<int,mystd::vector<CSummonMonsterTable::SUMMON_MONSTER_INFO> *>::iterator result = m_matchMap.find(itemID);
		mystd::vector<CSummonMonsterTable::SUMMON_MONSTER_INFO>* v17;
		if( result == m_matchMap.end() )
		{
			v17 = new mystd::vector<CSummonMonsterTable::SUMMON_MONSTER_INFO>;
			m_matchMap[itemID] = v17;
		}
		else
		{
			v17 = result->second;
		}

		CSummonMonsterTable::SUMMON_MONSTER_INFO info;
		info.monsterType = v12;
		info.monsterAI = v15;
		v17->push_back(info);
	}

	fclose(fp);
}


bool CSummonMonsterTable::GetRandomMatch(int itemID, int& monsterType, int& monsterAI)
{
	return (this->*_GetRandomMatch)(itemID, monsterType, monsterAI);

	mystd::map<int,mystd::vector<CSummonMonsterTable::SUMMON_MONSTER_INFO>*>::iterator v5 = m_matchMap.find(itemID);
	if( v5 == m_matchMap.end() )
		return false;

	mystd::vector<CSummonMonsterTable::SUMMON_MONSTER_INFO>* v6 = v5->second;
	if( v6 == NULL )
		return false;

	int v7 = v6->size();
	if( v7 == 0 )
		return false;

	int v8 = GetServerRandom(0, v7 - 1);
	SUMMON_MONSTER_INFO& v9 = v6->at(v8);

	monsterType = v9.monsterType;
	monsterAI = v9.monsterAI;
	return true;
}
