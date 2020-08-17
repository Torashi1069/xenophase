#include "CMemorialDungeonFileLog.h"
#include "Enum.h"
#include "ScriptCompiler.h"
#include "NpcServer/NpcSvr.h"
#include "shared/NCriticalErrorLog.h"
#include "shared/ServerInfo.h"
#include "shared/shared.h"


/// globals
std::map<int,int>& g_mapNormal2BabyJob = VTOR<std::map<int,int>>(DetourFindFunction(EXEPATH(), "g_mapNormal2BabyJob"));
std::map<int,int>& g_mapBabyJob2Normal = VTOR<std::map<int,int>>(DetourFindFunction(EXEPATH(), "g_mapBabyJob2Normal"));


void InitBabyJobData()
{
	g_mapNormal2BabyJob[JT_NOVICE] = JT_NOVICE_B;
	g_mapNormal2BabyJob[JT_SWORDMAN] = JT_SWORDMAN_B;
	g_mapNormal2BabyJob[JT_MAGICIAN] = JT_MAGICIAN_B;
	g_mapNormal2BabyJob[JT_ARCHER] = JT_ARCHER_B;
	g_mapNormal2BabyJob[JT_ACOLYTE] = JT_ACOLYTE_B;
	g_mapNormal2BabyJob[JT_MERCHANT] = JT_MERCHANT_B;
	g_mapNormal2BabyJob[JT_THIEF] = JT_THIEF_B;
	g_mapNormal2BabyJob[JT_KNIGHT] = JT_KNIGHT_B;
	g_mapNormal2BabyJob[JT_PRIEST] = JT_PRIEST_B;
	g_mapNormal2BabyJob[JT_WIZARD] = JT_WIZARD_B;
	g_mapNormal2BabyJob[JT_BLACKSMITH] = JT_BLACKSMITH_B;
	g_mapNormal2BabyJob[JT_HUNTER] = JT_HUNTER_B;
	g_mapNormal2BabyJob[JT_ASSASSIN] = JT_ASSASSIN_B;
	g_mapNormal2BabyJob[JT_CRUSADER] = JT_CRUSADER_B;
	g_mapNormal2BabyJob[JT_MONK] = JT_MONK_B;
	g_mapNormal2BabyJob[JT_SAGE] = JT_SAGE_B;
	g_mapNormal2BabyJob[JT_ROGUE] = JT_ROGUE_B;
	g_mapNormal2BabyJob[JT_ALCHEMIST] = JT_ALCHEMIST_B;
	g_mapNormal2BabyJob[JT_BARD] = JT_BARD_B;
	g_mapNormal2BabyJob[JT_DANCER] = JT_DANCER_B;
	g_mapNormal2BabyJob[JT_SUPERNOVICE] = JT_SUPERNOVICE_B;
	g_mapNormal2BabyJob[JT_SUPERNOVICE2] = JT_SUPERNOVICE2_B;
	g_mapNormal2BabyJob[JT_RUNE_KNIGHT] = JT_RUNE_KNIGHT_B;
	g_mapNormal2BabyJob[JT_WARLOCK] = JT_WARLOCK_B;
	g_mapNormal2BabyJob[JT_RANGER] = JT_RANGER_B;
	g_mapNormal2BabyJob[JT_ARCHBISHOP] = JT_ARCHBISHOP_B;
	g_mapNormal2BabyJob[JT_MECHANIC] = JT_MECHANIC_B;
	g_mapNormal2BabyJob[JT_GUILLOTINE_CROSS] = JT_GUILLOTINE_CROSS_B;
	g_mapNormal2BabyJob[JT_ROYAL_GUARD] = JT_ROYAL_GUARD_B;
	g_mapNormal2BabyJob[JT_SORCERER] = JT_SORCERER_B;
	g_mapNormal2BabyJob[JT_MINSTREL] = JT_MINSTREL_B;
	g_mapNormal2BabyJob[JT_WANDERER] = JT_WANDERER_B;
	g_mapNormal2BabyJob[JT_SURA] = JT_SURA_B;
	g_mapNormal2BabyJob[JT_GENETIC] = JT_GENETIC_B;
	g_mapNormal2BabyJob[JT_SHADOW_CHASER] = JT_SHADOW_CHASER_B;

	g_mapBabyJob2Normal[JT_NOVICE_B] = JT_NOVICE;
	g_mapBabyJob2Normal[JT_SWORDMAN_B] = JT_SWORDMAN;
	g_mapBabyJob2Normal[JT_MAGICIAN_B] = JT_MAGICIAN;
	g_mapBabyJob2Normal[JT_ARCHER_B] = JT_ARCHER;
	g_mapBabyJob2Normal[JT_ACOLYTE_B] = JT_ACOLYTE;
	g_mapBabyJob2Normal[JT_MERCHANT_B] = JT_MERCHANT;
	g_mapBabyJob2Normal[JT_THIEF_B] = JT_THIEF;
	g_mapBabyJob2Normal[JT_KNIGHT_B] = JT_KNIGHT;
	g_mapBabyJob2Normal[JT_PRIEST_B] = JT_PRIEST;
	g_mapBabyJob2Normal[JT_WIZARD_B] = JT_WIZARD;
	g_mapBabyJob2Normal[JT_BLACKSMITH_B] = JT_BLACKSMITH;
	g_mapBabyJob2Normal[JT_HUNTER_B] = JT_HUNTER;
	g_mapBabyJob2Normal[JT_ASSASSIN_B] = JT_ASSASSIN;
	g_mapBabyJob2Normal[JT_CRUSADER_B] = JT_CRUSADER;
	g_mapBabyJob2Normal[JT_MONK_B] = JT_MONK;
	g_mapBabyJob2Normal[JT_SAGE_B] = JT_SAGE;
	g_mapBabyJob2Normal[JT_ROGUE_B] = JT_ROGUE;
	g_mapBabyJob2Normal[JT_ALCHEMIST_B] = JT_ALCHEMIST;
	g_mapBabyJob2Normal[JT_BARD_B] = JT_BARD;
	g_mapBabyJob2Normal[JT_DANCER_B] = JT_DANCER;
	g_mapBabyJob2Normal[JT_SUPERNOVICE_B] = JT_SUPERNOVICE;
	g_mapBabyJob2Normal[JT_SUPERNOVICE2_B] = JT_SUPERNOVICE2;
	g_mapBabyJob2Normal[JT_RUNE_KNIGHT_B] = JT_RUNE_KNIGHT;
	g_mapBabyJob2Normal[JT_WARLOCK_B] = JT_WARLOCK;
	g_mapBabyJob2Normal[JT_RANGER_B] = JT_RANGER;
	g_mapBabyJob2Normal[JT_ARCHBISHOP_B] = JT_ARCHBISHOP;
	g_mapBabyJob2Normal[JT_MECHANIC_B] = JT_MECHANIC;
	g_mapBabyJob2Normal[JT_GUILLOTINE_CROSS_B] = JT_GUILLOTINE_CROSS;
	g_mapBabyJob2Normal[JT_ROYAL_GUARD_B] = JT_ROYAL_GUARD;
	g_mapBabyJob2Normal[JT_SORCERER_B] = JT_SORCERER;
	g_mapBabyJob2Normal[JT_MINSTREL_B] = JT_MINSTREL;
	g_mapBabyJob2Normal[JT_WANDERER_B] = JT_WANDERER;
	g_mapBabyJob2Normal[JT_SURA_B] = JT_SURA;
	g_mapBabyJob2Normal[JT_GENETIC_B] = JT_GENETIC;
	g_mapBabyJob2Normal[JT_SHADOW_CHASER_B] = JT_SHADOW_CHASER;
}


CNpcSvr::CNpcSvr()
{
}


CNpcSvr::~CNpcSvr()
{
}


void CNpcSvr::Clear()
{
	m_binBuf.CBinBuf::Clear();
	m_staticNpcMgr.CNpcMgr::Clear();
	m_eventNo = 0;

	for( std::map<int,CNpcEvent*>::iterator iter = m_eventMap.begin(); iter != m_eventMap.end(); ++iter )
	{
		CNpcEvent* event = iter->second;

		event->CNpcEvent::Stop();
		event->CNpcEvent::AddDeleteCount();
	}
}


bool CNpcSvr::LoadScript()
{
	return m_binBuf.CBinBuf::Load(".\\npcdata\\npc.bin");
}


bool CNpcSvr::Start()
{
	CNpcEvent::m_serverID = g_serverInfo.CServerInfo::GetLocalServerID();
	this->CNpcSvr::Clear();

	timeGetTime(); // unused?
	Trace("npc script compile start\n");

	if( !m_binBuf.CBinBuf::Load(GetScriptFileName(BIN_NPC)) )
	{
		Trace("LoadScript : failure\n");
		MessageBoxA(NULL, "LoadScript : failure", "error", MB_OK);
		return false;
	}

	Trace("LoadScript : success\n");

	m_clearFirstEvent = false;
	this->CNpcSvr::RunEvent(0, 0, 0, 0, false);
	Trace("Begin Main Event\n");
	InitBabyJobData();

	return true;
}


bool CNpcSvr::IsExistScriptEvent(const int in_AID, const int in_Event)
{
	CNpc* npc = m_staticNpcMgr.CNpcMgr::Get(in_AID);
	if( npc == NULL )
		return false;
	
	if( !npc->CNpc::GetOnInit() )
		return false;

	if( npc->CNpc::GetActionScriptIdx(in_Event, 0, 0) == 0 )
		return false;

	return true;
}


hook_func<void (__stdcall *)()> CNpcSvr__SendMsg(EXEPATH(), "CNpcSvr::SendMsg");
int CNpcSvr::SendMsg(unsigned long senderAID, unsigned long receiverAID, CZNPC2Msg* msg) // 310-438 (243-388)
{
	int result;
	void* hookptr = CNpcSvr__SendMsg;
	__asm mov eax, msg
	__asm push receiverAID
	__asm push senderAID
	__asm call hookptr
	__asm mov result, eax
	return result;
	//TODO
}


int CNpcSvr::RunEvent(int pcId, int npcId, int act, int reserveTime, bool oninit)
{
	CNpc* npc = m_staticNpcMgr.CNpcMgr::Get(npcId);
	if( npc != NULL && npc->CNpc::IsNpcType() == 1 ) //TODO
		return this->CNpcSvr::RunEvent_Dungeon(pcId, npcId, act, reserveTime, npc->CNpc::GetMapName(), 0, oninit);

	CNpcEvent* event = m_pool.pool<CNpcEvent>::Alloc();
	if( event == NULL )
		return false;

	if( !event->CNpcEvent::Run(&m_staticNpcMgr, &m_binBuf, pcId, npcId, act) )
	{
		m_pool.pool<CNpcEvent>::Free(event);
		return false;
	}

	event->CNpcEvent::SetReserveTime(reserveTime);
	event->CNpcEvent::SetOnInit(oninit);
	m_eventMap[++m_eventNo] = event;

	return m_eventNo;
}


void CNpcSvr::CancelEvent(int eventNo)
{
	std::map<int,CNpcEvent*>::iterator iter = m_eventMap.find(eventNo);
	if( iter == m_eventMap.end() )
		return;

	CNpcEvent* event = iter->second;

	if( event->CNpcEvent::GetReserveTime() != 0 )
	{
		event->CNpcEvent::SetReserveTime(-1);
	}
	else
	{
		event->CNpcEvent::Stop();
		event->CNpcEvent::AddDeleteCount();
	}
}


void CNpcSvr::Process()
{
	for( std::map<int,CNpcEvent*>::iterator iter = m_eventMap.begin(); iter != m_eventMap.end(); ++iter )
	{
		CNpcEvent* event = iter->second;

		if( event->CNpcEvent::GetDeleteCount() > 0 )
			continue;

		unsigned long reserveTime = event->CNpcEvent::GetReserveTime();
		if( reserveTime != 0 )
		{
			if( reserveTime == -1 )
			{
				event->CNpcEvent::AddDeleteCount();
				continue;
			}

			if( reserveTime > timeGetTime() )
				continue;
		}

		for( int i = 0; i < 50; ++i )
		{
			unsigned int ret = event->Proc(false);
			if( ret == 0 )
			{
				event->CNpcEvent::Stop();
				event->CNpcEvent::AddDeleteCount();
				break;
			}

			if( ret == 2 )
				break;
		}
	}

	for( std::map<int,CNpcEvent*>::iterator iter = m_eventMap.begin(); iter != m_eventMap.end(); )
	{
		CNpcEvent* event = iter->second;

		if( event->CNpcEvent::GetDeleteCount() > 0 )
		{
			m_pool.pool<CNpcEvent>::Free(event);
			iter = m_eventMap.erase(iter);
		}
		else
		{
			++iter;
		}
	}
}


void CNpcSvr::FinalNpcEvent(std::string mapName)
{
	if( mapName.size() == 0 )
		return;

	std::string strIdent = mapName.substr(0, 3);

	for( std::map<int,CNpcEvent*>::iterator iter = m_eventMap.begin(); iter != m_eventMap.end(); ++iter )
	{
		CNpcEvent* event = iter->second;
		if( event == NULL )
			continue;

		CNpc* npc = event->CNpcEvent::GetNpc();
		if( npc == NULL )
			continue;

		if( strcmp(event->CNpcEvent::GetDungeonIdent(), strIdent.c_str()) != 0 )
			continue;

		if( strcmp(npc->CNpc::GetMapName(), mapName.c_str()) != 0 )
			continue;

		if( npc->CNpc::GetType() != 1 )
			continue;

		event->CNpcEvent::StopDungern();
		event->CNpcEvent::AddDeleteCount();
	}
}


void CNpcSvr::FinalDungeonNpc(int npcId)
{
	m_staticNpcMgr.CNpcMgr::Delete(npcId);
}


bool CNpcSvr::AddDunGeon(const char* mapName, unsigned int instantID)
{
	NCriticalErrorLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__, "Start Dungeon Script Start mapName = %s ident %d", mapName, instantID);

	int eventNo = this->CNpcSvr::RunEvent_Dungeon(0, 0, 0, 0, mapName, instantID, false);

	NCriticalErrorLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__, "End Dungeon Script Start mapName = %s ident %d", mapName, instantID);

	return ( eventNo != 0 );
}


int CNpcSvr::RunEvent_Dungeon(int pcId, int npcId, int act, int reserveTime, std::string mapName, unsigned int instantID, bool oninit)
{
	CNpcEvent* event = m_pool.pool<CNpcEvent>::Alloc();
	if( event == NULL )
		return 0;

	if( mapName.size() < 1 )
		return 0;

	std::string org_name = mapName.substr(3, mapName.size() - 7);

	CDGNpcBin* dgnbin = CDGNpcMgr::GetObj()->CDGNpcMgr::FindDunGeonBin(org_name.c_str());
	if( dgnbin == NULL )
	{
		CMemorialDungeonFileLog::GetObj()->CMemorialDungeonFileLog::WriteFmt(__FILE__, __LINE__, 0, 0, "instantmap script not found!!! [%s]", mapName.c_str());
		CMemorialDungeonFileLog::GetObj()->CMemorialDungeonFileLog::WriteFmt(__FILE__, __LINE__, 0, 0, "instantmap please check /npcdata/DungeonList.txt");
		NCriticalErrorLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__, "Please Check File : /npcdata/DungeonList.txt ");
		m_pool.pool<CNpcEvent>::Free(event);
		return 0;
	}

	if( !event->CNpcEvent::Run_Dungeon(&m_staticNpcMgr, &dgnbin->m_binBuf, mapName.substr(0, 3).c_str(), instantID, pcId, npcId, act) )
	{
		NCriticalErrorLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__, "Please Check File : /npcdata/DungeonList.txt ");
		m_pool.pool<CNpcEvent>::Free(event);
		return 0;
	}

	event->CNpcEvent::SetReserveTime(reserveTime);
	event->CNpcEvent::SetOnInit(oninit);
	m_eventMap[++m_eventNo] = event;

	return m_eventNo;
}


CStaticNpcMgr* CNpcSvr::GetStaticNpcMgr()
{
	return &m_staticNpcMgr;
}


bool CNpcSvr::ClearFirstEvent()
{
	return m_clearFirstEvent;
}
