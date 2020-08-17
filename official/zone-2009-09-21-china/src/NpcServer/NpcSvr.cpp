#include "NpcServer/NpcSvr.h"
#include "MonParameterMgr.h"
#include "ScriptCompiler.h" // GetScriptFileName()
#include "ServerInfo.h"
#include "shared.h" // Trace()


hook_func<void (__cdecl *)(void)> _InitBabyJobData(SERVER, "InitBabyJobData");
static void __cdecl InitBabyJobData(void) // line 32
{
	return _InitBabyJobData();

	//TODO
}


CNpcSvr::CNpcSvr(void) // line 84
{
}


CNpcSvr::~CNpcSvr(void) // line 88
{
}


hook_method<void (CNpcSvr::*)(void)> CNpcSvr::_Clear(SERVER, "CNpcSvr::Clear");
void CNpcSvr::Clear(void) // line 92
{
	return (this->*_Clear)();

	m_mobMgr.CNpcMgr::Clear();
	m_binBuf.CBinBuf::Clear();
	m_npcMgr.CNpcMgr::Clear();

	m_eventNo = 0;
	for( mystd::map<int,CNpcEvent*>::iterator it = m_eventMap.begin(); it != m_eventMap.end(); ++it )
	{
		it->second->CNpcEvent::Stop();
		m_pool.pool<CNpcEvent>::Free(it->second); //inlined
	}

	m_eventMap.clear();
	m_pool.pool<CNpcEvent>::clear();
}


hook_method<bool (CNpcSvr::*)(void)> CNpcSvr::_Start(SERVER, "CNpcSvr::Start");
bool CNpcSvr::Start(void) // line 198
{
	return (this->*_Start)();

	CNpcEvent::m_serverID = g_serverInfo->CServerInfo::GetLocalServerID();
	this->CNpcSvr::Clear();
	timeGetTime();
	Trace("npc script compile start\n");

	if( m_binBuf.CBinBuf::Load(GetScriptFileName(BIN_NPC)) )
	{
		Trace("LoadScript : success\n");
		m_clearFirstEvent = false;
		this->CNpcSvr::RunEvent(0, 0, 0, 0, false);
		Trace("Begin Main Event\n");
		InitBabyJobData();
		return true;
	}
	else
	{
		Trace("LoadScript : failure\n");
		MessageBoxA(NULL, "LoadScript : failure", "error", MB_OK);
		return false;
	}
}


hook_method<void (CNpcSvr::*)(void)> CNpcSvr::_Process(SERVER, "CNpcSvr::Process");
void CNpcSvr::Process(void) // line 451
{
	return (this->*_Process)();

	DWORD maxTime = 0;

	mystd::map<int,CNpcEvent*>::iterator nextit;
	for( mystd::map<int,CNpcEvent*>::iterator it = m_eventMap.begin(); it != m_eventMap.end(); it = nextit )
	{
		nextit = it;
		++nextit;

		CNpcEvent* evt = it->second;
		DWORD reserveTime = evt->CNpcEvent::GetReserveTime();

		if( reserveTime != 0 )
		{
			if( reserveTime == -1 )
			{
				m_pool.pool<CNpcEvent>::Free(evt);
				m_eventMap.erase(it);
				continue;
			}

			if( reserveTime > timeGetTime() )
				continue;
		}

		DWORD startTime = timeGetTime();

		for( int i = 0; i < 50; ++i )
		{
			unsigned int retcode = evt->Proc(false);

			if( retcode == 0 )
			{
				evt->CNpcEvent::Stop();
				m_pool.pool<CNpcEvent>::Free(evt);
				m_eventMap.erase(it);
				break;
			}

			if( retcode == 2 )
				break;
		}

		DWORD delta = timeGetTime() - startTime;
		if( maxTime == 0 || maxTime < delta )
			maxTime = delta;
	}

	g_NpcProcessTimeList[0] = (int)maxTime;
	if( g_NpcProcessTimeList[0] < 0 )
		g_NpcProcessTimeList[0] += 0x100000000;

	if( g_NpcProcessTimeList[1] == 0.0 || g_NpcProcessTimeList[1] < g_NpcProcessTimeList[0] )
		g_NpcProcessTimeList[1] = g_NpcProcessTimeList[0];
}


hook_method<int (CNpcSvr::*)(unsigned long senderAID, unsigned long receiverAID, CZNPC2Msg* msg)> CNpcSvr::_SendMsg(SERVER, "CNpcSvr::SendMsg");
int CNpcSvr::SendMsg(unsigned long senderAID, unsigned long receiverAID, CZNPC2Msg* msg) // line 243
{
	return (this->*_SendMsg)(senderAID, receiverAID, msg);

	//TODO
}


hook_method<int (CNpcSvr::*)(int pcId, int npcId, int act, int reserveTime, bool oninit)> CNpcSvr::_RunEvent(SERVER, "CNpcSvr::RunEvent");
int CNpcSvr::RunEvent(int pcId, int npcId, int act, int reserveTime, bool oninit) // line 395
{
	return (this->*_RunEvent)(pcId, npcId, act, reserveTime, oninit);

	CNpc* npc = m_npcMgr.CNpcMgr::Get(npcId);
	if( npc != NULL && npc->CNpc::GetType() == 1 )
		return this->CNpcSvr::RunEvent_Dungeon(pcId, npcId, act, reserveTime, npc->CNpc::GetMapName(), 0, oninit);

	CNpcEvent* evt = m_pool.pool<CNpcEvent>::Alloc();
	if( evt == NULL )
		return 0;

	if( !evt->CNpcEvent::Run(&m_npcMgr, &m_binBuf, pcId, npcId, act) )
	{
		m_pool.pool<CNpcEvent>::Free(evt);
		return 0;
	}

	evt->CNpcEvent::RegisterMobMgr(&m_mobMgr);
	evt->CNpcEvent::SetReserveTime(reserveTime);
	evt->CNpcEvent::SetOnInit(oninit);
	++m_eventNo;
	m_eventMap[m_eventNo] = evt;

	return m_eventNo;
}


hook_method<void (CNpcSvr::*)(int eventNo)> CNpcSvr::_CancelEvent(SERVER, "CNpcSvr::CancelEvent");
void CNpcSvr::CancelEvent(int eventNo) // line 425
{
	return (this->*_CancelEvent)(eventNo);

	mystd::map<int,CNpcEvent*>::iterator it = m_eventMap.find(eventNo);
	if( it == m_eventMap.end() )
		return;

	CNpcEvent* evt = it->second;
	if( evt->CNpcEvent::GetReserveTime() != 0 )
	{
		evt->CNpcEvent::SetReserveTime(-1);
		return;
	}

	it->second->CNpcEvent::Stop();
	m_pool.pool<CNpcEvent>::Free(evt);
	m_eventMap.erase(it);
}


//hook_method<void (CNpcSvr::*)(void)> CNpcSvr::_CreateMobNameDbNameFile(SERVER, "CNpcSvr::CreateMobNameDbNameFile");
void CNpcSvr::CreateMobNameDbNameFile(void) // line ???
{
//	return (this->*_CreateMobNameDbNameFile)();

	//TODO
}


//hook_method<CNpcMgr* (CNpcSvr::*)(void)> CNpcSvr::_GetNpcMgr(SERVER, "CNpcSvr::GetNpcMgr");
CNpcMgr* CNpcSvr::GetNpcMgr(void) // line ???
{
//	return (this->*_GetNpcMgr)();

	return &m_npcMgr;
}


//hook_method<bool (CNpcSvr::*)(void)> CNpcSvr::_ClearFirstEvent(SERVER, "CNpcSvr::ClearFirstEvent");
bool CNpcSvr::ClearFirstEvent(void) // line ???
{
//	return (this->*_ClearFirstEvent)();

	return m_clearFirstEvent;
}


hook_method<void (CNpcSvr::*)(mystd::string mapName)> CNpcSvr::_FinalNpcEvent(SERVER, "CNpcSvr::FinalNpcEvent");
void CNpcSvr::FinalNpcEvent(mystd::string mapName) // line 538
{
	return (this->*_FinalNpcEvent)(mapName);

	//TODO
}


hook_method<void (CNpcSvr::*)(int npcId)> CNpcSvr::_FinalDungeonNpc(SERVER, "CNpcSvr::FinalDungeonNpc");
void CNpcSvr::FinalDungeonNpc(int npcId) // line 589
{
	return (this->*_FinalDungeonNpc)(npcId);

	//TODO
}


hook_method<bool (CNpcSvr::*)(const char* mapName, unsigned int instantID)> CNpcSvr::_AddGunGeon(SERVER, "CNpcSvr::AddGunGeon");
bool CNpcSvr::AddGunGeon(const char* mapName, unsigned int instantID) // line 593
{
	return (this->*_AddGunGeon)(mapName, instantID);

	//TODO
}


hook_method<int (CNpcSvr::*)(int pcId, int npcId, int act, int reserveTime, mystd::string mapName, unsigned int instantID, bool oninit)> CNpcSvr::_RunEvent_Dungeon(SERVER, "CNpcSvr::RunEvent_Dungeon");
int CNpcSvr::RunEvent_Dungeon(int pcId, int npcId, int act, int reserveTime, mystd::string mapName, unsigned int instantID, bool oninit) // line 605
{
	return (this->*_RunEvent_Dungeon)(pcId, npcId, act, reserveTime, mapName, instantID, oninit);

	//TODO
}


/// guessed
//hook_method<bool (CNpcSvr::*)(void)> CNpcSvr::_LoadScript(SERVER, "CNpcSvr::LoadScript");
bool CNpcSvr::LoadScript(void) // line ???
{
//	return (this->*_LoadScript)();

	return m_binBuf.CBinBuf::Load(".\\npcdata\\npc.bin");
}


//hook_method<bool (CNpcSvr::*)(void)> CNpcSvr::_Compile(SERVER, "CNpcSvr::Compile");
bool CNpcSvr::Compile(void) // line ???
{
//	return (this->*_Compile)();
	return false; //TODO

	//TODO
}
