#include "ErrorLog.h"
#include "IGuildInfoDB.h"
#include "IGuildMgr.h"
#include "ZServerMgr.h"
#include "Common/Packet.h"
#include "enums.hpp"
#include "globals.hpp"


hook_ptr<CIGuildMgr*> CIGuildMgr::m_cpSelf(SERVER, "CIGuildMgr::m_cpSelf"); // = NULL;


hook_method<void (CIGuildMgr::*)(int MaxGuild)> CIGuildMgr::_Init(SERVER, "CIGuildMgr::Init");
void CIGuildMgr::Init(int MaxGuild) // line 58
{
	return (this->*_Init)(MaxGuild);

	//TODO
}


hook_method<CGuild* (CIGuildMgr::*)(void)> CIGuildMgr::_AllocGuild(SERVER, "CIGuildMgr::AllocGuild");
CGuild* CIGuildMgr::AllocGuild(void) // line 63
{
	return (this->*_AllocGuild)();

	//TODO
}


hook_method<void (CIGuildMgr::*)(unsigned long ZSID, unsigned long GID, unsigned long AID)> CIGuildMgr::_LogonUserA(SERVER, "CIGuildMgr::LogonUserA");
void CIGuildMgr::LogonUserA(unsigned long ZSID, unsigned long GID, unsigned long AID) // line 69-100
{
	return (this->*_LogonUserA)(ZSID, GID, AID);

	// TODO
}


hook_method<void (CIGuildMgr::*)(void)> CIGuildMgr::_GuildAllSave(SERVER, "CIGuildMgr::GuildAllSave");
void CIGuildMgr::GuildAllSave(void) // line 922
{
	return (this->*_GuildAllSave)();

	//TODO
}


hook_method<void (CIGuildMgr::*)(unsigned long ZSID, unsigned long AID, unsigned long GID)> CIGuildMgr::_ExitUser(SERVER, "CIGuildMgr::ExitUser");
void CIGuildMgr::ExitUser(unsigned long ZSID, unsigned long AID, unsigned long GID) // line 167-196
{
	return (this->*_ExitUser)(ZSID, AID, GID);

	// TODO
}


hook_method<void (CIGuildMgr::*)(unsigned long ZSID, unsigned long AID, unsigned long GID, unsigned long MyGID, unsigned long MyAID)> CIGuildMgr::_ReqJoinGuild(SERVER, "CIGuildMgr::ReqJoinGuild");
void CIGuildMgr::ReqJoinGuild(unsigned long ZSID, unsigned long AID, unsigned long GID, unsigned long MyGID, unsigned long MyAID)
{
	return (this->*_ReqJoinGuild)(ZSID, AID, GID, MyGID, MyAID);

	if( g_IGuildDB.CIGuildInfoDB::GetGDID(GID) )
	{
		PACKET_IZ_ACK_REQ_JOIN_GUILD OutPacket;
		OutPacket.PacketType = HEADER_IZ_ACK_REQ_JOIN_GUILD;
		OutPacket.AID = MyAID;
		OutPacket.answer = 0;
		g_zServerMgr.CZServerMgr::SendMsgToZServer(ZSID, sizeof(OutPacket), (char*)&OutPacket);
		return; // done.
	}

	unsigned long GDID = g_IGuildDB.CIGuildInfoDB::GetGDID(MyGID);
	if( GDID == 0 )
		return; // not in a guild

	CGuild* g;
	if( (g = this->CGuildMgr::SearchGuild(GDID)) == NULL && (g = this->CIGuildMgr::LoadGuild(0,0)) == NULL )
		return; // guild not found

	int posID = g->CGuild::GetGuildPosID(MyGID);
	if( g->CGuild::GetPosJoinRight(posID) == 0 )
		return; // not allowed to invite

	if( g->CGuild::GetGuildMSize() >= g->CGuild::GetMaxUserNum() )
	{
		Trace("Member OverSize UserNum : %d, MaxUserNum: %d\n", g->CGuild::GetGuildMSize(), g->CGuild::GetMaxUserNum());
		PACKET_IZ_ACK_REQ_JOIN_GUILD OutPacket;
		OutPacket.PacketType = HEADER_IZ_ACK_REQ_JOIN_GUILD;
		OutPacket.AID = MyAID;
		OutPacket.answer = 3;
		g_zServerMgr.CZServerMgr::SendMsgToZServer(ZSID, sizeof(OutPacket), (char*)&OutPacket);
		return; // no more room
	}

	m_guildAIDQueue[GID] = MyAID;

	PACKET_IZ_REQ_JOIN_GUILD Packet;
	Packet.PacketType = HEADER_IZ_REQ_JOIN_GUILD;
	Packet.GDID = GDID;
	Packet.AID = AID;
	g_IGuildDB.CGuildDB::GetTableChar(GDID, 1, Packet.guildName, sizeof(Packet.guildName));
	g_zServerMgr.CZServerMgr::SendMsgToZServer(ZSID, sizeof(Packet), (char*)&Packet);
}


hook_method<CIGuildInfo* (CIGuildMgr::*)(unsigned long GDID, int bNotify)> CIGuildMgr::_LoadGuild(SERVER, "CIGuildMgr::LoadGuild");
CIGuildInfo* CIGuildMgr::LoadGuild(unsigned long GDID, int bNotify)
{
	return (this->*_LoadGuild)(GDID, bNotify);

	//TODO
}


hook_method<void (CIGuildMgr::*)(unsigned long ZSID, short PacketType, unsigned long GDID, int Len, char* buf)> CIGuildMgr::_SendPacket(SERVER, "CIGuildMgr::SendPacket");
void CIGuildMgr::SendPacket(unsigned long ZSID, short PacketType, unsigned long GDID, int Len, char* buf)
{
	return (this->*_SendPacket)(ZSID, PacketType, GDID, Len, buf);

	CIGuildInfo* g;
	if( (g = (CIGuildInfo *)this->CGuildMgr::SearchGuild(GDID)) == NULL
	&&  (g = (CIGuildInfo *)this->CIGuildMgr::LoadGuild(GDID,1)) == NULL )
		return;

	g->CIGuildInfo::SetAllNotifyInfo(1);

	if( g->m_packetDispatcher.CIGuildInfoPacketDispatcher::DispatchPacket(ZSID, GDID, PacketType, Len, buf) != -1 )
	{
		char buff[1024];
		sprintf(buff, "Guild DispatchPacket error- PacketType:%d \n", PacketType);
		g_errorLogs.CErrorLog::CriticalErrorLog(buff, 488, ".\\IGuildMgr.cpp");
	}
}


hook_method<void (CIGuildMgr::*)(void)> CIGuildMgr::_ProcessAllGuild(SERVER, "CIGuildMgr::ProcessAllGuild");
void CIGuildMgr::ProcessAllGuild(void) // line 707
{
	return (this->*_ProcessAllGuild)();

	//TODO
}


hook_method<unsigned long (CIGuildMgr::*)(unsigned long GID)> CIGuildMgr::_SearchAIDMap(SERVER, "CIGuildMgr::SearchAIDMap");
unsigned long CIGuildMgr::SearchAIDMap(unsigned long GID)
{
	return (this->*_SearchAIDMap)(GID);

	//TODO
}


hook_method<unsigned long (CIGuildMgr::*)(void)> CIGuildMgr::_GetFreeSize(SERVER, "CIGuildMgr::GetFreeSize");
HOOKED unsigned long CIGuildMgr::GetFreeSize(void) // line 39 (IGuildMgr.h)
{
	return m_iGuildMPool.size() - m_guildInfo.size();
	return (this->*_GetFreeSize)();

	return m_iGuildMPool.CMemoryMgr<CIGuildInfo>::GetFreeSize();
}


hook_method<void (CIGuildMgr::*)(void)> CIGuildMgr::_GetGuildAgitDB(SERVER, "CIGuildMgr::GetGuildAgitDB");
void CIGuildMgr::GetGuildAgitDB(void) // line 756
{
	return (this->*_GetGuildAgitDB)();

	//TODO
}


hook_method<void (CIGuildMgr::*)(unsigned long GDID)> CIGuildMgr::_OutPutGuildInfo(SERVER, "CIGuildMgr::OutPutGuildInfo");
void CIGuildMgr::OutPutGuildInfo(unsigned long GDID) // line 892
{
	return (this->*_OutPutGuildInfo)(GDID);

	CIGuildInfo* info = (CIGuildInfo*)this->CGuildMgr::SearchGuild(GDID);
	if( info != NULL )
		info->CIGuildInfo::OutPutGuildInfo(0);
}


hook_method<bool (CIGuildMgr::*)(void)> CIGuildMgr::_Create(SERVER, "CIGuildMgr::Create");
bool CIGuildMgr::Create(void) // line 30
{
	return (this->*_Create)();

	return true;
}


hook_method<void (CIGuildMgr::*)(void)> CIGuildMgr::_Destroy(SERVER, "CIGuildMgr::Destroy");
void CIGuildMgr::Destroy(void) // line 36
{
	return (this->*_Destroy)();

	;
}


CIGuildMgr::CIGuildMgr(void) // line 13
{
	m_bOK = false;
	m_lastSaveTime = timeGetTime();

	if( this->CIGuildMgr::Create() )
		m_bOK = true;
}


CIGuildMgr::~CIGuildMgr(void) // line 21
{
}


hook_method<static bool (__cdecl *)(void)> CIGuildMgr::_CreateInstance(SERVER, "CIGuildMgr::CreateInstance");
bool CIGuildMgr::CreateInstance(void)
{
	return (CIGuildMgr::_CreateInstance)();

	//TODO
}


hook_method<static void (__cdecl *)(void)> CIGuildMgr::_DestroyInstance(SERVER, "CIGuildMgr::DestroyInstance");
void CIGuildMgr::DestroyInstance(void)
{
	return (CIGuildMgr::_DestroyInstance)();

	//TODO
}


/// @custom
CIGuildMgr* CIGuildMgr::GetObj(void)
{
	return m_cpSelf;
}
