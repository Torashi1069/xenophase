#include "CMailCtrl.h"
#include "MServerMgr.h"
#include "IGuildMgr.h"
#include "PartyMgr.h"
#include "ProcessThread.h"
#include "UserMgr.h"
#include "ZServerMgr.h"
#include "Instant Map/InstantMapMgr.h"
#include "Memorial Dungeon/MemorialDungeonMgr.h"
#include "Statistics/StatisticsMgr.h"
#include "Common/Packet.h"
#include "enums.hpp"
#include "globals.hpp"


hook_ptr<CProcessThread*> CProcessThread::m_cpSelf(SERVER, "CProcessThread::m_cpSelf"); // = ?


CProcessThread::CProcessThread(void) // line 31
{
	m_bReqExit = false;
	m_bOK = true;
}


CProcessThread::~CProcessThread(void) // line 38
{
}


hook_method<unsigned int (CProcessThread::*)(void)> CProcessThread::_ThreadFunction(SERVER, "CProcessThread::ThreadFunction");
HOOKED unsigned int CProcessThread::ThreadFunction(void) // line 96
{
//	return (this->*_ThreadFunction)();

	int counter = 0;
	while( !m_bReqExit )
	{
		int start = timeGetTime();

		CMemorialDungeonMgr::GetObj()->CMemorialDungeonMgr::Process();
		CInstantMapMgr::GetObj()->CInstantMapMgr::Process();
		CStatisticsMgr::GetObj()->CStatisticsMgr::Process();
		g_zServerMgr.CZServerMgr::ProcessAllCharacter();
		CIGuildMgr::GetObj()->CIGuildMgr::ProcessAllGuild();
		g_mServerMgr.CMClientMgr::ProcessAllCharacter();
		g_userMgr.CUserMgr::Process();
		g_MailCtrl.CMailCtrl::Process();

		if( counter % 3 == 0 )
		{
			g_userMgrUserCount = g_userMgr.CUserMgr::GetUserCount();
			g_userMgrFreeSize = g_userMgr.CUserMgr::GetFreeSize();
			g_groupMgrGroupSize = InstanceCPartyMgr()->CPartyMgr::GetGroupSize();
			g_groupMgrFreeSize = InstanceCPartyMgr()->CPartyMgr::GetFreeSize();
			g_IGuildMgrGuildSize = CIGuildMgr::GetObj()->CGuildMgr::GetGuildSize();
			g_IGuildMgrFreeSize = CIGuildMgr::GetObj()->CIGuildMgr::GetFreeSize();
		}

		int delta = timeGetTime() - start;
		if( g_MaxProcessTime < delta )
			g_MaxProcessTime = delta;

		if( g_SendChkProrcessTime == 1 )
		{
			PACKET_IZ_CHK_PROCESSTIME SendPacket;
			SendPacket.PacketType = HEADER_IZ_CHK_PROCESSTIME;
			SendPacket.InterProcessTime = time(NULL);
			g_zServerMgr.CZServerMgr::BroadCast(sizeof(SendPacket), (char *)&SendPacket);

			g_SendChkProrcessTime = 0;
		}

		if( counter++ > 100 )
		{
			Sleep(g_sleep);
			counter = 0;
		}
	}

	return 0;
}


hook_method<void (CProcessThread::*)(void)> CProcessThread::_PostThreadQuitMessage(SERVER, "CProcessThread::PostThreadQuitMessage");
void CProcessThread::PostThreadQuitMessage(void) // line 163
{
	return (this->*_PostThreadQuitMessage)();

	m_bReqExit = true;
}


hook_method<bool (CProcessThread::*)(void)> CProcessThread::_Start(SERVER, "CProcessThread::Start");
bool CProcessThread::Start(void) // line 70
{
	return (this->*_Start)();

	return this->N2Thread::Begin();
}


hook_method<void (CProcessThread::*)(void)> CProcessThread::_Stop(SERVER, "CProcessThread::Stop");
void CProcessThread::Stop(void) // line 75
{
	return (this->*_Stop)();

	this->N2Thread::End();
}


hook_method<const bool (CProcessThread::*)(void)> CProcessThread::_isOK(SERVER, "CProcessThread::isOK");
const bool CProcessThread::isOK(void) // line 27 (ProcessThread.h)
{
	return (this->*_isOK)();

	return m_bOK;
}


hook_method<static bool (__cdecl *)(void)> CProcessThread::_CreateInstance(SERVER, "CProcessThread::CreateInstance");
bool CProcessThread::CreateInstance(void) // line 45
{
	return (_CreateInstance)();

	if( CProcessThread::m_cpSelf != NULL )
		return false;

	CProcessThread::m_cpSelf = new CProcessThread();
	if( CProcessThread::m_cpSelf == NULL )
		return false;

	if( !CProcessThread::m_cpSelf->m_bOK )
	{
		delete CProcessThread::m_cpSelf;
		CProcessThread::m_cpSelf = (CProcessThread*)NULL;
		return false;
	}

	return true;
}


hook_method<static void (__cdecl *)(void)> CProcessThread::_DestoryInstance(SERVER, "CProcessThread::DestoryInstance");
void CProcessThread::DestoryInstance(void) // line 57
{
	return (_DestoryInstance)();

	if( CProcessThread::m_cpSelf != NULL )
	{
		delete CProcessThread::m_cpSelf;
		CProcessThread::m_cpSelf = (CProcessThread*)NULL;
	}
}


hook_method<static CProcessThread* (__cdecl *)(void)> CProcessThread::_GetObj(SERVER, "CProcessThread::GetObj");
CProcessThread* CProcessThread::GetObj(void) // line 65
{
	return (_GetObj)();

	return m_cpSelf;
}
