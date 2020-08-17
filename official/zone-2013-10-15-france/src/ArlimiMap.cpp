#include "ArlimiMap.h"
#include "CharacterMgr.h"
#include "FuncExtraction.h"
#include "MapResMgr.h"
#include "QuestArlimiTxt.h"
#include "QuestEventMgr.h"
#include "ZoneProcess.h"
#include "NpcServer/NpcSvr.h"
#include "shared/CMapInfoMgr.h"
#include "shared/NCriticalErrorLog.h"
#include "shared/ServerInfo.h"


CArlimiMap::CArlimiMap()
{
	m_pool.CMemoryMgr<T_ARLIMI_DATA>::Init(50);
	m_maPool.CMemoryMgr<T_MAP_IN_ARLIMI>::Init(30);
	m_index = 0;
}


CArlimiMap::~CArlimiMap()
{
	this->CArlimiMap::Filnalize();
}


bool CArlimiMap::Initialize()
{
	this->CArlimiMap::Filnalize();
	return this->CArlimiMap::LoadArlimiMap("ArlimiMap.txt");
}


void CArlimiMap::Filnalize()
{
	m_pool.CMemoryMgr<T_ARLIMI_DATA>::Reset();
	m_arlimiMap.clear();
	m_maPool.CMemoryMgr<T_MAP_IN_ARLIMI>::Reset();
	m_mapInArlimi.clear();
	m_index = 0;
}


bool CArlimiMap::LoadArlimiMap(const char* file_name)
{
	CQuestArlimiTxt arlimiTxt;
	CFuncExtraction func;

	if( !arlimiTxt.CQuestArlimiTxt::LoadTxt("ArlimiMap.txt") )
		return true;

	if( !arlimiTxt.CQuestArlimiTxt::DeleteComment() )
		return false;

	arlimiTxt.CQuestArlimiTxt::ExtractionFuncPositonList("arlimimap");

	while( arlimiTxt.CQuestArlimiTxt::GetFuncSize() > 1 )
	{
		CQVar data = arlimiTxt.CQuestArlimiTxt::GetNextFuncData();

		std::vector<CQVar> value;
		func.CFuncExtraction::SetData(data.CQVar::o_str());
		func.CFuncExtraction::GetFuncValue("arlimimap", value);

		if( !this->CArlimiMap::AddArlimiMap(value) )
			return false;
	}

	return true;
}


bool CArlimiMap::AddArlimiMap(std::vector<CQVar> value)
{
	int Count = (int)value.size();
	if( Count < 4 )
	{
		char eLog[256] = {};
		sprintf_s(eLog, countof(eLog), "CArlimiMap::AddArlimiMap Short of Value Count = %d", Count);
		NCriticalErrorLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__, "%s", eLog);
		MessageBoxA(NULL, eLog, "Quest Notify Error", MB_OK);
		return false;
	}

	const char* map_name = value[0].CQVar::o_str();
	const char* npc_name = value[1].CQVar::o_str();
	const char* flag     = value[2].CQVar::o_str();

	int xPos = 0;
	int yPos = 0;

	bool mapInNpc;
	if( strcmp(flag, "ON") == 0 )
		mapInNpc = true;
	else
	if( strcmp(flag, "OFF") == 0 )
		mapInNpc = false;
	else
	{
		char eLog[256] = {};
		sprintf_s(eLog, countof(eLog), "CArlimiMap::AddArlimiMap  Not Defined Notify Type : %s", flag);
		NCriticalErrorLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__, "%s", eLog);
		MessageBoxA(NULL, eLog, "Quest Notify Error", MB_OK);
		return false;
	}

	CMapRes* mapRes = g_mapResMgr.CMapResMgr::GetMapRes(map_name);
	if( mapRes == NULL )
		return true;

	int mapID = mapRes->CMapRes::GetID();
	unsigned long npcID;

	if( mapInNpc )
	{
		if( g_serverInfo.CServerInfo::GetLocalServerID() != CMapInfoMgr::GetObj()->CMapInfoMgr::GetServerID(map_name) )
			return true;

		CNpc* npc = g_npcSvr.CNpcSvr::GetStaticNpcMgr()->CNpcMgr::GetFromName(npc_name);
		if( npc == NULL )
		{
			char eLog[256] = {};
			sprintf_s(eLog, countof(eLog), "CArlimiMap::AddArlimiMap Find Not Npc alimiState = true, mapName = %s, ncpName = %s, xPos = %d, yPos %d", map_name, npc_name, xPos, yPos);
			NCriticalErrorLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__, "%s", eLog);
			MessageBoxA(NULL, eLog, "Quest Notify Error", MB_OK);
			return false;
		}

		npcID = npc->CNpc::GetId();
		CNPC* chNPC = (CNPC*)CCharacterMgr::GetObj()->CCharacterMgr::FindCharacter(npc->CNpc::GetId(), NPC_TYPE);
		chNPC->GetParameterValue(VAR_CURXPOS, xPos);
		chNPC->GetParameterValue(VAR_CURYPOS, yPos);
	}
	else
	{
		npcID = 0;
		xPos = atoi(value[3].CQVar::o_str());
		yPos = atoi(value[4].CQVar::o_str());
	}

	++m_index;
	this->CArlimiMap::AddMapInArlimi(mapID, m_index);
	this->CArlimiMap::AddArlimiInQuest(m_index, npcID, mapInNpc, xPos, yPos, value);
	return true;
}


bool CArlimiMap::AddMapInArlimi(unsigned long mapID, unsigned int index)
{
	if( mapID < 1 )
		return false;

	TMAPINARLIMI::iterator iter = m_mapInArlimi.find(mapID);
	if( iter == m_mapInArlimi.end() )
	{
		T_MAP_IN_ARLIMI* map = m_maPool.CMemoryMgr<T_MAP_IN_ARLIMI>::Alloc();
		if( map == NULL )
			return false;

		map->t_mapID = mapID;
		map->t_npcList.push_back(index);
		m_mapInArlimi.insert(std::pair<const unsigned long,T_MAP_IN_ARLIMI*>(mapID, map));
	}
	else
	{
		T_MAP_IN_ARLIMI* map = iter->second;
		if( map != NULL )
			map->t_npcList.push_back(index);
	}

	return true;
}


bool CArlimiMap::AddArlimiInQuest(unsigned int index, unsigned long npcID, bool mapInNpc, int xPos, int yPos, std::vector<CQVar> data)
{
	if( m_arlimiMap.find(index) != m_arlimiMap.end() )
		return false;

	T_ARLIMI_DATA* p = m_pool.CMemoryMgr<T_ARLIMI_DATA>::Alloc();
	if( p == NULL )
		return false;

	p->t_npcID = npcID;
	p->t_nonNpc = mapInNpc;
	p->t_xPos = xPos;
	p->t_yPos = yPos;

	for( size_t i = 5; i < data.size(); ++i )
	{
		unsigned long questID = atoi(data[i].CQVar::o_str());
		if( !g_questEventMgr.CQuestEventMgr::IsQuest(questID) )
			return false;

		p->t_questList.push_back(questID);
	}

	m_arlimiMap.insert(std::pair<const unsigned long,T_ARLIMI_DATA*>(index, p));
	return true;
}


void CArlimiMap::GetQuestNpcList(unsigned long mapID, std::list<unsigned long>& qNpcList)
{
	TMAPINARLIMI::iterator iter = m_mapInArlimi.find(mapID);
	if( iter == m_mapInArlimi.end() )
		return;

	T_MAP_IN_ARLIMI* map = iter->second;
	if( map == NULL )
		return;

	for( size_t i = 0; i < map->t_npcList.size(); ++i )
		qNpcList.push_back(map->t_npcList[i]);
}


T_ARLIMI_DATA* CArlimiMap::GetArlimiData(unsigned int index)
{
	TARLIMI_MAP::iterator iter = m_arlimiMap.find(index);
	if( iter == m_arlimiMap.end() )
		return NULL;

	return iter->second;
}
