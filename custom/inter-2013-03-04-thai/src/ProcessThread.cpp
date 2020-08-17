#include "IGuildMgr.h"
#include "Interserver.h"
#include "PartyMgr.h"
#include "ProcessThread.h"
#include "UserMgr.h"
#include "Instant Map/InstantMapMgr.h"
#include "Memorial Dungeon/MemorialDungeonMgr.h"
#include "ServerManager/CMsvrMgr.h"
#include "Statistics/StatisticsMgr.h"
#include "Zsvr/CZsvrMgr.h"
#include "shared/NOutputTextMgr.h"


/// singleton instance
CProcessThread*& CProcessThread::m_cpSelf = VTOR<CProcessThread*>(DetourFindFunction(EXEPATH(), "CProcessThread::m_cpSelf"));

/// locals
static int& g_MaxProcessTime = VTOR<int>(DetourFindFunction(EXEPATH(), "g_MaxProcessTime"));
static int& g_userMgrUserCount = VTOR<int>(DetourFindFunction(EXEPATH(), "g_userMgrUserCount"));
static int& g_userMgrFreeSize = VTOR<int>(DetourFindFunction(EXEPATH(), "g_userMgrFreeSize"));
static int& g_groupMgrGroupSize = VTOR<int>(DetourFindFunction(EXEPATH(), "g_groupMgrGroupSize"));
static int& g_groupMgrFreeSize = VTOR<int>(DetourFindFunction(EXEPATH(), "g_groupMgrFreeSize"));
static int& g_IGuildMgrGuildSize = VTOR<int>(DetourFindFunction(EXEPATH(), "g_IGuildMgrGuildSize"));
static int& g_IGuildMgrFreeSize = VTOR<int>(DetourFindFunction(EXEPATH(), "g_IGuildMgrFreeSize"));


CProcessThread::CProcessThread()
: N2Thread("ProcessThread")
{
	m_bReqExit = false;
	m_bOK = true;
}


CProcessThread::~CProcessThread()
{
}


bool CProcessThread::CreateInstance()
{
	if( m_cpSelf != NULL )
		return false;

	m_cpSelf = new(std::nothrow) CProcessThread();
	if( m_cpSelf == NULL )
		return false;

	if( !m_cpSelf->CProcessThread::isOK() )
	{
		delete m_cpSelf;
		m_cpSelf = NULL;
		return false;
	}

	return true;
}


void CProcessThread::DestoryInstance()
{
	if( m_cpSelf != NULL )
	{
		delete m_cpSelf;
		m_cpSelf = NULL;
	}
}


CProcessThread* CProcessThread::GetObj()
{
	return m_cpSelf;
}


const bool CProcessThread::isOK() const
{
	return m_bOK;
}


bool CProcessThread::Start()
{
	NOutputTextMgr::GetObj()->NOutputTextMgr::InsertFmt("service start...");
	return this->N2Thread::Begin();
}


void CProcessThread::Stop()
{
	NOutputTextMgr::GetObj()->NOutputTextMgr::InsertFmt("service stop...");
	this->N2Thread::End();
}


unsigned int CProcessThread::ThreadFunction()
{
	int SleepCounter = 0;

	while( !m_bReqExit )
	{
		DWORD ProcessTime = timeGetTime();

		CMemorialDungeonMgr::GetObj()->CMemorialDungeonMgr::Process();
		CInstantMapMgr::GetObj()->CInstantMapMgr::Process();
		CStatisticsMgr::GetObj()->CStatisticsMgr::Process();
		CZsvrMgr::GetObj()->CZsvrMgr::Process();
		CIGuildMgr::GetObj()->CIGuildMgr::ProcessAllGuild();
		CMsvrMgr::GetObj()->CMsvrMgr::Process();

		/// [patch] reduce cpu load by skipping the unused, excessive and inefficient memory statistics in the processing thread
		/*
		//FIXME: this runs too often, the calls are expensive, and the values are not used anywhere.
		if( SleepCounter % 3 == 0 )
		{
			g_userMgrUserCount = g_userMgr.CUserMgr::GetUserCount();
			g_userMgrFreeSize = g_userMgr.CUserMgr::GetFreeSize();
			g_groupMgrGroupSize = g_groupMgr.CPartyMgr::GetGroupSize();
			g_groupMgrFreeSize = g_groupMgr.CPartyMgr::GetFreeSize();
			g_IGuildMgrGuildSize = CIGuildMgr::GetObj()->CGuildMgr::GetGuildSize();
			g_IGuildMgrFreeSize = CIGuildMgr::GetObj()->CIGuildMgr::GetFreeSize();
		}
		*/
		/// [/patch]

		int ProcessTimeDelta = int(timeGetTime() - ProcessTime);
		if( g_MaxProcessTime < ProcessTimeDelta )
			g_MaxProcessTime = ProcessTimeDelta;

		if( g_SendChkProrcessTime == TRUE )
		{
			time_t the_time;
		    PACKET_IZ_CHK_PROCESSTIME SendPacket;
			SendPacket.PacketType = HEADER_IZ_CHK_PROCESSTIME;
			SendPacket.InterProcessTime = time(&the_time);
			CZsvrMgr::GetObj()->CZServerMgr::BroadCast(sizeof(SendPacket), (char*)&SendPacket);

			g_SendChkProrcessTime = FALSE;
		}

		if( SleepCounter++ > 100 )
		{
			Sleep(g_sleep);
			SleepCounter = 0;
		}
	}

	return 0;
}


void CProcessThread::PostThreadQuitMessage()
{
	m_bReqExit = true;
}
