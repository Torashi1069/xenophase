#include "IGuildInfo.h"
#include "IGuildInfoDB.h"
#include "IGuildMgr.h"
#include "InterServer.h"
#include "UserMgr.h"
#include "Zsvr/CZSvrMgr.h"
#include "Common/Packet.h"
#include "shared/NCriticalErrorLog.h"


/// singleton instance
CIGuildMgr*& CIGuildMgr::m_cpSelf = VTOR<CIGuildMgr*>(DetourFindFunction(EXEPATH(), "CIGuildMgr::m_cpSelf"));


CIGuildMgr::CIGuildMgr()
{
	m_bOK = false;

	m_lastSaveTime = timeGetTime();
	if( this->CIGuildMgr::Create() )
		m_bOK = true;
}


CIGuildMgr::~CIGuildMgr()
{
	m_GarbageGDID.clear();
	m_guildInfo.clear();
}


bool CIGuildMgr::Create()
{
	return true;
}


void CIGuildMgr::Destroy()
{
}


bool CIGuildMgr::CreateInstance()
{
	if( m_cpSelf != NULL )
		return false;

	m_cpSelf = new(std::nothrow) CIGuildMgr();
	if( m_cpSelf == NULL )
		return false;
	
	if( !m_cpSelf->CIGuildMgr::isOK() )
	{
		delete m_cpSelf;
		m_cpSelf = NULL;
		return false;
	}

	return true;
}


void CIGuildMgr::DestroyInstance()
{
	if( m_cpSelf != NULL )
	{
		delete m_cpSelf;
		m_cpSelf = NULL;
	}
}


CIGuildMgr* CIGuildMgr::GetObj() /// @custom
{
	return m_cpSelf;
}


bool CIGuildMgr::isOK() const
{
	return m_bOK;
}


void CIGuildMgr::Init(int MaxGuild)
{
	m_iGuildMPool.CMemoryMgr<CIGuildInfo>::Init(MaxGuild);
}


unsigned long CIGuildMgr::GetFreeSize()
{
	return m_iGuildMPool.CMemoryMgr<CIGuildInfo>::GetFreeSize();
}


CGuild* CIGuildMgr::AllocGuild()
{
	return m_iGuildMPool.CMemoryMgr<CIGuildInfo>::Alloc();
}


void CIGuildMgr::LogonUser(unsigned long ZSID, unsigned long GID, unsigned long AID)
{
	unsigned long GDID = g_IGuildDB.CIGuildInfoDB::GetGDID(GID);
	if( GDID == 0 )
		return;

	CIGuildInfo* Info = (CIGuildInfo*)this->CGuildMgr::SearchGuild(GDID);
	if( Info != NULL )
	{
		if( !Info->CIGuildInfo::GetUseInfo() )
		{
			Info->CIGuildInfo::SetUseInfo(TRUE);
			m_GarbageGDID.remove(GDID);
			Info->CIGuildInfo::ReLoadDB();
		}
	}
	else
	{
		Info = this->CIGuildMgr::LoadGuild(GDID, TRUE);
		if( Info == NULL )
		{
			g_IGuildDB.CIGuildInfoDB::DeleteGuildMInfo(GID);
			return;
		}
	}

	Info->CIGuildInfo::ChangeMemberInfo(ZSID, AID, GID, 1);
	Info->CIGuildInfo::UpdateCharGDID(PACKET_IZ_UPDATE_CHARGDID::TYPE_LOGONUSER, ZSID, AID, GID, GDID, Info->CIGuildInfo::GetEmblemVersion());
}


void CIGuildMgr::ChangeZoneServer(unsigned long OldZSID, unsigned long NewZSID, unsigned long GID, unsigned long AID)
{
	unsigned long GDID = g_IGuildDB.CIGuildInfoDB::GetGDID(GID);
	if( GDID == 0 )
		return;

	CIGuildInfo* Guild = (CIGuildInfo*)this->CGuildMgr::SearchGuild(GDID);
	if( Guild == NULL )
		Guild = this->CIGuildMgr::LoadGuild(GDID, TRUE);
	if( Guild == NULL )
	{
		g_IGuildDB.CIGuildInfoDB::DeleteGuildMInfo(GID);
		return;
	}

	Guild->CIGuildInfo::RemoveZoneServer(OldZSID);
	Guild->CIGuildInfo::AddZoneServer(NewZSID);
	Guild->CIGuildInfo::UpdateCharGDID(PACKET_IZ_UPDATE_CHARGDID::TYPE_CHANGEZONESERVER, NewZSID, AID, GID, GDID, Guild->CGuild::GetEmblemVersion());
}


CIGuildInfo* CIGuildMgr::LoadGuild(unsigned long GDID, BOOL bNotify)
{
	CIGuildInfo* Guild = static_cast<CIGuildInfo*>(this->CGuildMgr::SearchGuild(GDID));
	if( Guild == NULL )
	{
		Guild = m_iGuildMPool.CMemoryMgr<CIGuildInfo>::Alloc();
		if( Guild == NULL )
			return NULL;

		Guild->Init();

		if( !Guild->CIGuildInfo::AllLoadDB(GDID) )
		{
			m_iGuildMPool.CMemoryMgr<CIGuildInfo>::Free(Guild);
			//FIXME: now in an inconsistent state because Init() will not clear Guild's arrays
			return NULL;
		}

		if( !this->CGuildMgr::AddGuild(Guild) )
		{
			char Buf[256] = {};
			sprintf(Buf, "Add Guild %d Failed\n", GDID);
			Guild->CIGuildInfo::GuildErrorLog(Buf, __LINE__, __FILE__);

			m_iGuildMPool.CMemoryMgr<CIGuildInfo>::Free(Guild);
			//FIXME: now in an inconsistent state because Init() will not clear Guild's arrays
			return NULL;
		}
	}

	return Guild;
}


void CIGuildMgr::ExitUser(unsigned long ZSID, unsigned long AID, unsigned long GID)
{
	unsigned long GDID = g_IGuildDB.CIGuildInfoDB::GetGDID(GID);
	if( GDID == 0 )
		return;

	CIGuildInfo* Info = (CIGuildInfo*)CGuildMgr::SearchGuild(GDID);
	if( Info == NULL )
		return;

	int Exp = Info->CGuild::GetMemberExp(GID);
	int Level = Info->CGuild::GetMemberLevel(GID);
	int Class = Info->CGuild::GetMemberClass(GID);
	Info->CIGuildInfo::ChangeMemberInfo(ZSID, AID, GID, 0);
	g_IGuildDB.CIGuildInfoDB::UpdateGuildMember(GDID, GID, 0, Exp, Level, Class);

	if( !Info->CGuild::GetGuildMemberOnline() )
	{
		g_IGuildDB.CIGuildInfoDB::UpdateGuildInfoDB(*Info);
		this->CIGuildMgr::FreeGuild(Info, 0);
	}
}


void CIGuildMgr::ServerMoveUser(unsigned long ZSID, unsigned long AID, unsigned long GID, BOOL isOnLine)
{
	unsigned long GDID = g_IGuildDB.CIGuildInfoDB::GetGDID(GID);
	if( GDID == 0 )
		return;

	CIGuildInfo* Guild = (CIGuildInfo*)this->CGuildMgr::SearchGuild(GDID);
	if( Guild == NULL )
		return;

	if( isOnLine )
		Guild->CIGuildInfo::ChangeMemberInfo(ZSID, AID, GID, 1);
	else
		Guild->CIGuildInfo::ChangeMemberInfo(ZSID, AID, GID, 0);
}


void CIGuildMgr::FreeGuild(CIGuildInfo* guild, BOOL disorganize)
{
	unsigned long GDID = guild->CGuild::GetGDID();

	AGIT_OWNER_GUILDID_CONTANIER_ITER it = m_AgitOwnerGuildIDList.find(GDID);
	if( it != m_AgitOwnerGuildIDList.end() )
	{
		if( !disorganize )
			return;
		it = m_AgitOwnerGuildIDList.erase(it);
	}

	if( disorganize )
	{
		this->CIGuildMgr::RemoveGuildInfo(GDID);
	}
	else
	{
		m_GarbageGDID.push_back(GDID);
		guild->CIGuildInfo::SetUseInfo(FALSE);

		if( m_GarbageGDID.size() > 5000 )
		{
			int GDID = m_GarbageGDID.front();
			m_GarbageGDID.pop_front();
			this->CIGuildMgr::RemoveGuildInfo(GDID);
		}
	}
}


void CIGuildMgr::RemoveGuildInfo(unsigned long GDID)
{
	CIGuildInfo* Guild = static_cast<CIGuildInfo*>(this->CGuildMgr::SearchGuild(GDID));
	if( Guild == NULL )
		return;

	Guild->CGuild::ClearAll();
	m_iGuildMPool.CMemoryMgr<CIGuildInfo>::Free(Guild);

	std::map<unsigned long,CGuild*>::iterator iter = m_guildInfo.find(GDID);
	if( iter != m_guildInfo.end() )
		m_guildInfo.erase(iter);

	if( IsSetting(SETTING_GUILDWAR) )
	{
		PACKET_IZ_FREE_GUILD IZPacket;
		IZPacket.PacketType = HEADER_IZ_FREE_GUILD;
		IZPacket.GDID = GDID;
		CZsvrMgr::GetObj()->CZServerMgr::BroadCast(sizeof(IZPacket), (char*)&IZPacket);
	}
}


int CIGuildMgr::MakeGuild(unsigned long ZSID, unsigned long AID, unsigned long GID, unsigned long& GDID, char* Name, char* GName, char* AccountName)
{
	if( this->CGuildMgr::SearchGuild(GDID) )
		return -1;

	GName[24-1] = '\0';
	if( strlen(GName) >= 24 )
		return -1;

	if( g_IGuildDB.CIGuildInfoDB::GetGDID(GID) )
	{
		this->CIGuildMgr::SendGuildMakeResult(ZSID, AID, GID, 1);
		return -1;
	}

	if( g_IGuildDB.CGuildDB::GetGuildID(GName) )
	{
		this->CIGuildMgr::SendGuildMakeResult(ZSID, AID, GID, 2);
		return -1;
	}

	CIGuildInfo* Guild = m_iGuildMPool.CMemoryMgr<CIGuildInfo>::Alloc();
	if( Guild == NULL )
	{
		this->CIGuildMgr::SendGuildMakeResult(ZSID, AID, GID, 2);
		NCriticalErrorLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__, "Make Guild Alloc Failed");
		return -1;
	}

	g_IGuildDB.CIGuildInfoDB::MakeGuild(AID, GID, GDID, Name, GName);

	GDID = g_IGuildDB.CGuildDB::GetGuildID(GName);
	if( GDID == NULL )
	{
		NCriticalErrorLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__, "savageox : Get Guild ID Failed");
		this->CIGuildMgr::SendGuildMakeResult(ZSID, AID, GID, 2);
		this->CIGuildMgr::FreeGuild(Guild, TRUE);
		return -1;
	}

	Guild->Init();
	Guild->CGuild::SetGDID(GDID);
	Guild->CGuild::SetGuildMasterName(Name);
	Guild->CGuild::SetGuildName(GName);

	g_IGuildDB.CIGuildInfoDB::UpdateGuildInfoDB(*Guild);

	if( !this->CGuildMgr::AddGuild(Guild) )
	{
		this->CIGuildMgr::FreeGuild(Guild, FALSE);
		this->CIGuildMgr::SendGuildMakeResult(ZSID, AID, GID, 2);
		return -1;
	}

	GUILDINFO GuildInfo;
	g_IGuildDB.CIGuildInfoDB::GetGuildInfoDB(GDID, GuildInfo);
	Guild->CGuild::SetGuildInfo(&GuildInfo);

	PACKET_IZ_GUILDINFO_TOD GPacket;
	GPacket.PacketType = HEADER_IZ_GUILDINFO_TOD;
	GPacket.GDID = GDID;
	memcpy(&GPacket.Data, &GuildInfo, sizeof(GPacket.Data));
	CZsvrMgr::GetObj()->CZServerMgr::SendMsgToZServer(ZSID, sizeof(GPacket), (char*)&GPacket);

	PACKET_IZ_RESULT_MAKE_GUILD Packet;
	Packet.PacketType = HEADER_IZ_RESULT_MAKE_GUILD;
	Packet.AID = AID;
	Packet.GID = GID;
	Packet.result = 0;
	CZsvrMgr::GetObj()->CZServerMgr::SendMsgToZServer(ZSID, sizeof(Packet), (char*)&Packet);

	GUILDMINFO* MInfo = Guild->CGuild::AllocGuildMInfo();
	if( MInfo == NULL )
		return -1;

	USER_STRING_MAP_DATA* User = g_userMgr.CUserMgr::SearchUser(AID, GID);
	if( User == NULL )
	{
		NCriticalErrorLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__, "savageox : Insert Guild Member Failed");
		this->CIGuildMgr::SendGuildMakeResult(ZSID, AID, GID, 2);
		this->CIGuildMgr::FreeGuild(Guild, TRUE);
		return -1;
	}

	MInfo->sex = static_cast<short>(User->sex);
	MInfo->head = User->head;
	MInfo->headPalette = User->headpalette;
	MInfo->job = User->job;
	MInfo->Level = User->level;
	Guild->CGuild::InitGuildMInfo(MInfo, Name, AccountName, AID, GDID, GID, 0, 1, User->level, User->job, User->head, User->headpalette, User->sex);
	Guild->CGuild::AddGuildMInfo(MInfo);

	char Buf[MAX_GUILD_MEMBER_LIST * sizeof(GUILDMINFO)];
	memcpy(Buf, MInfo, sizeof(GUILDMINFO));

	PACKET_IZ_GUILD_MEMBERINFO_TOD PacketMInfo;
	PacketMInfo.PacketType = HEADER_IZ_GUILD_MEMBERINFO_TOD;
	PacketMInfo.PacketLength = sizeof(PacketMInfo) + 1 * sizeof(GUILDMINFO);
	PacketMInfo.GDID = GDID;
//	PacketMInfo.AID = AID;
	CZsvrMgr::GetObj()->CZServerMgr::SendMsgToZServer(ZSID, sizeof(PacketMInfo), (char*)&PacketMInfo);
	CZsvrMgr::GetObj()->CZServerMgr::SendMsgToZServer(ZSID, 1 * sizeof(GUILDMINFO), Buf);

	g_IGuildDB.CIGuildInfoDB::InsertGuildMember(*MInfo);
	Guild->CIGuildInfo::ChangeMemberInfo(ZSID, AID, GID, 1);
	Guild->CIGuildInfo::UpdateCharGDID(PACKET_IZ_UPDATE_CHARGDID::TYPE_GUILDMAKE, ZSID, AID, GID, GDID, 0);

	char PosBuf[3072] = {}; // GUILDMPOSITION[64]
	GUILDMPOSITION* PosArr = reinterpret_cast<GUILDMPOSITION*>(PosBuf);

	GUILDMPOSITION* MPos = Guild->CGuild::AllocGuildMPosition();
	if( MPos == NULL )
	{
		NCriticalErrorLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__, "savageox : Make Guild Pos Failed");
		this->CIGuildMgr::SendGuildMakeResult(ZSID, AID, GID, 2);
		this->CIGuildMgr::FreeGuild(Guild, TRUE);
		return -1;
	}

	MPos->Grade = 0;
	MPos->PositionID = 0;
	MPos->GDID = GDID;
	MPos->JoinRight = TRUE;
	MPos->PenaltyRight = TRUE;
	memcpy(MPos->PosName, "Master", sizeof(MPos->PosName)); //FIXME: out-of-bounds read
	MPos->Service = 0;
	memcpy(&PosArr[0], MPos, sizeof(GUILDMPOSITION));

	g_IGuildDB.CIGuildInfoDB::InsertGuildMPosition(*MPos);
	Guild->CGuild::AddGuildMPosition(MPos);

	for( int i = 1; i < 20; ++i )
	{
		GUILDMPOSITION* MPos = Guild->CGuild::AllocGuildMPosition();
		if( MPos == NULL )
		{
			NCriticalErrorLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__, "savageox : Make Guild Pos Failed");
			this->CIGuildMgr::SendGuildMakeResult(ZSID, AID, GID, 2);
			this->CIGuildMgr::FreeGuild(Guild, TRUE);
			return -1;
		}

		MPos->Grade = i;
		MPos->PositionID = i;
		MPos->GDID = GDID;
		MPos->JoinRight = FALSE;
		MPos->PenaltyRight = FALSE;
		char PosName[24];
		sprintf(PosName, "Position %d", i + 1);
		memcpy(MPos->PosName, PosName, sizeof(MPos->PosName));
		MPos->Service = 0;
		memcpy(&PosArr[i], MPos, sizeof(GUILDMPOSITION));

		g_IGuildDB.CIGuildInfoDB::InsertGuildMPosition(*MPos);
		Guild->CGuild::AddGuildMPosition(MPos);
	}

	PACKET_IZ_GUILD_MPOSITION_TOD PacketMPos;
	PacketMPos.PacketType = HEADER_IZ_GUILD_MPOSITION_TOD;
	PacketMPos.PacketLength = sizeof(PacketMPos) + 20 * sizeof(GUILDMPOSITION);
	PacketMPos.GDID = GDID;
	PacketMPos.AID = 0;
	CZsvrMgr::GetObj()->CZServerMgr::SendMsgToZServer(ZSID, sizeof(PacketMPos), (char*)&PacketMPos);
	CZsvrMgr::GetObj()->CZServerMgr::SendMsgToZServer(ZSID, 20 * sizeof(GUILDMPOSITION), PosBuf);

	g_IGuildDB.CIGuildInfoDB::InsertGuildNotice(GDID);

	if( IsSetting(SETTING_GUILDWAR) )
		Guild->CIGuildInfo::LoadSkill(TRUE);

	return -1;
}


void CIGuildMgr::SendPacket(unsigned long ZSID, short PacketType, unsigned long GDID, int Len, char* buf)
{
	CIGuildInfo* Guild = (CIGuildInfo*)CGuildMgr::SearchGuild(GDID);
	if( Guild == NULL )
	{
		Guild = this->CIGuildMgr::LoadGuild(GDID, TRUE);
		if( Guild == NULL )
			return;

		Guild->CIGuildInfo::SetAllNotifyInfo(TRUE);
	}

	if( Guild->m_packetDispatcher.CIGuildInfoPacketDispatcher::DispatchPacket(ZSID, GDID, PacketType, Len, buf) != -1 )
		NCriticalErrorLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__, "Guild DispatchPacket error- PacketType:%d", PacketType);
}


void CIGuildMgr::ReqJoinGuild(unsigned long ZSID, unsigned long AID, unsigned long GID, unsigned long MyGID, unsigned long MyAID)
{
	if( g_IGuildDB.CIGuildInfoDB::GetGDID(GID) != 0 )
	{
		PACKET_IZ_ACK_REQ_JOIN_GUILD Packet;
		Packet.PacketType = HEADER_IZ_ACK_REQ_JOIN_GUILD;
		Packet.AID = MyAID;
//		Packet.ReqAID = 0;
//		Packet.GDID = 0;
		Packet.answer = 0;
		CZsvrMgr::GetObj()->CZServerMgr::SendMsgToZServer(ZSID, sizeof(Packet), (char*)&Packet);
		return;
	}

	unsigned long GDID = g_IGuildDB.CIGuildInfoDB::GetGDID(MyGID);
	if( GDID == 0 )
		return;

	CIGuildInfo* Guild = (CIGuildInfo*)this->CGuildMgr::SearchGuild(GDID);
	if( Guild == NULL )
		Guild = this->CIGuildMgr::LoadGuild(0, FALSE); //FIXME: why '0' and not 'GDID'?
	if( Guild == NULL )
		return;

	int PosID = Guild->CGuild::GetGuildPosID(MyGID);
	if( !Guild->CGuild::GetPosJoinRight(PosID) )
		return;

	if( Guild->CGuild::GetGuildMSize() >= Guild->CGuild::GetMaxUserNum() )
	{
		PACKET_IZ_ACK_REQ_JOIN_GUILD Packet;
		Packet.PacketType = HEADER_IZ_ACK_REQ_JOIN_GUILD;
		Packet.AID = MyAID;
//		Packet.ReqAID = 0;
//		Packet.GDID = 0;
		Packet.answer = 3;
		CZsvrMgr::GetObj()->CZServerMgr::SendMsgToZServer(ZSID, sizeof(Packet), (char*)&Packet);
		return;
	}

	PACKET_IZ_REQ_JOIN_GUILD Packet;
	Packet.PacketType = HEADER_IZ_REQ_JOIN_GUILD;
	Packet.GDID = GDID;
	Packet.AID = AID;
	m_guildAIDQueue[GID] = MyAID;
	g_IGuildDB.CGuildDB::GetTableChar(GDID, SP_Name, Packet.guildName, sizeof(Packet.guildName)); //FIXME: why query the db?
	CZsvrMgr::GetObj()->CZServerMgr::SendMsgToZServer(ZSID, sizeof(Packet), (char*)&Packet);
}


unsigned long CIGuildMgr::SearchAIDMap(unsigned long GID)
{
	std::map<unsigned long,unsigned long>::iterator iter = m_guildAIDQueue.find(GID);
	if( iter == m_guildAIDQueue.end() )
		return 0;

	unsigned long AID = iter->second;
	m_guildAIDQueue.erase(iter);

	return AID;
}


void CIGuildMgr::AllyGuild(unsigned long ZSID, unsigned long GDID, char* buf)
{
	PACKET_ZI_ALLY_GUILD& ZIPacket = *reinterpret_cast<PACKET_ZI_ALLY_GUILD*>(buf);

	if( GDID == ZIPacket.otherGDID )
		return; // invalid input

	CIGuildInfo* MyGuild = (CIGuildInfo*)CGuildMgr::SearchGuild(GDID);
	CIGuildInfo* OtherGuild = (CIGuildInfo*)this->CGuildMgr::SearchGuild(ZIPacket.otherGDID);

	if( MyGuild == NULL || OtherGuild == NULL )
		return;

	if( MyGuild->CGuild::FindAllyGuild(ZIPacket.otherGDID) == TRUE || OtherGuild->CGuild::FindAllyGuild(GDID) == TRUE )
		this->CIGuildMgr::OnDeleteRelatedGuild(GDID, ZIPacket.otherGDID, 0, FALSE);

	if( MyGuild->CGuild::GetAllyCount() >= 3 )
	{
		PACKET_IZ_ADD_ALLY_GUILD PacketAllyInfo;
		PacketAllyInfo.PacketType = 10595;
		PacketAllyInfo.GDID = ZIPacket.otherGDID;
		PacketAllyInfo.AID = ZIPacket.otherAID;
		PacketAllyInfo.answer = 4;
		CZsvrMgr::GetObj()->CZServerMgr::SendMsgToZServer(ZSID, sizeof(PacketAllyInfo), (char*)&PacketAllyInfo);
		return;
	}

	if( OtherGuild->CGuild::GetAllyCount() >= 3 )
	{
		PACKET_IZ_ADD_ALLY_GUILD PacketAllyInfo;
		PacketAllyInfo.PacketType = 10595;
		PacketAllyInfo.GDID = ZIPacket.otherGDID;
		PacketAllyInfo.AID = ZIPacket.otherAID;
		PacketAllyInfo.answer = 3;
		CZsvrMgr::GetObj()->CZServerMgr::SendMsgToZServer(ZSID, sizeof(PacketAllyInfo), (char*)&PacketAllyInfo);
		return;
	}

	GUILDALLYINFO* MyAllyInfo = MyGuild->CGuild::AllocGuildAllyInfo();
	if( MyAllyInfo == NULL )
		return;

	GUILDALLYINFO* OtherAllyInfo = OtherGuild->CGuild::AllocGuildAllyInfo();
	if( OtherAllyInfo == NULL )
		return;

	MyAllyInfo->GDID = GDID;
	memcpy(MyAllyInfo->GuildName, OtherGuild->CGuild::GetGuildName(), sizeof(MyAllyInfo->GuildName));
	MyAllyInfo->Relation = RELATED_GUILD_TYPE_ALLY;
	MyAllyInfo->OpponentGDID = ZIPacket.otherGDID;
	if( g_IGuildDB.CIGuildInfoDB::InsertGuildAlly(*MyAllyInfo) == -1 )
		return;
	MyGuild->CGuild::AddGuildAllyInfo(MyAllyInfo);

	OtherAllyInfo->GDID = ZIPacket.otherGDID;
	memcpy(OtherAllyInfo->GuildName, MyGuild->CGuild::GetGuildName(), sizeof(OtherAllyInfo->GuildName));
	OtherAllyInfo->Relation = RELATED_GUILD_TYPE_ALLY;
	OtherAllyInfo->OpponentGDID = GDID;
	if( g_IGuildDB.CIGuildInfoDB::InsertGuildAlly(*OtherAllyInfo) == -1 )
		return;
	OtherGuild->CGuild::AddGuildAllyInfo(OtherAllyInfo);

	PACKET_IZ_ADD_ALLY_GUILD PacketAllyInfo;
	PacketAllyInfo.PacketType = HEADER_IZ_ADD_ALLY_GUILD;
	PacketAllyInfo.GDID = GDID;
	PacketAllyInfo.AID = ZIPacket.myAID;
	PacketAllyInfo.answer = 2;
	memcpy(&PacketAllyInfo.Ally, MyAllyInfo, sizeof(PacketAllyInfo.Ally));
	MyGuild->CIGuildInfo::Send(-1, sizeof(PacketAllyInfo), (char*)&PacketAllyInfo);

//	PACKET_IZ_ADD_ALLY_GUILD PacketAllyInfo;
	PacketAllyInfo.PacketType = HEADER_IZ_ADD_ALLY_GUILD;
	PacketAllyInfo.GDID = ZIPacket.otherGDID;
	PacketAllyInfo.AID = ZIPacket.otherAID;
	PacketAllyInfo.answer = 2;
	memcpy(&PacketAllyInfo.Ally, OtherAllyInfo, sizeof(PacketAllyInfo.Ally));
	OtherGuild->CIGuildInfo::Send(-1, sizeof(PacketAllyInfo), (char*)&PacketAllyInfo);
}


void CIGuildMgr::HostileGuild(unsigned long GDID, char* buf)
{
	PACKET_ZI_REQ_HOSTILE_GUILD& ZIPacket = *reinterpret_cast<PACKET_ZI_REQ_HOSTILE_GUILD*>(buf);

	CIGuildInfo* MyGuild = (CIGuildInfo*)this->CGuildMgr::SearchGuild(GDID);
	CIGuildInfo* OtherGuild = (CIGuildInfo*)this->CGuildMgr::SearchGuild(ZIPacket.OtherGDID);

	if( MyGuild == NULL )
		MyGuild = this->CIGuildMgr::LoadGuild(GDID, FALSE);
	if( MyGuild == NULL )
		return;

	if( OtherGuild == NULL )
		OtherGuild = this->CIGuildMgr::LoadGuild(ZIPacket.OtherGDID, FALSE);
	if( OtherGuild == NULL )
		return;

	if( MyGuild->CGuild::FindHostileGuild(ZIPacket.OtherGDID) )
		return; // already in list
	
	if( MyGuild->CGuild::GetHostileCount() >= 3 )
		return; // no more room

	GUILDALLYINFO* MyAllyInfo = MyGuild->CGuild::AllocGuildAllyInfo();
	if( MyAllyInfo == NULL )
		return;

	MyAllyInfo->GDID = GDID;
	memcpy(MyAllyInfo->GuildName, OtherGuild->CGuild::GetGuildName(), sizeof(MyAllyInfo->GuildName));
	MyAllyInfo->OpponentGDID = ZIPacket.OtherGDID;
	MyAllyInfo->Relation = RELATED_GUILD_TYPE_ENEMY;
	g_IGuildDB.CIGuildInfoDB::InsertGuildAlly(*MyAllyInfo);
	MyGuild->CGuild::AddGuildAllyInfo(MyAllyInfo);

	PACKET_IZ_ADD_HOSTILE_GUILD PacketHostileInfo;
	PacketHostileInfo.PacketType = HEADER_IZ_ADD_HOSTILE_GUILD;
	PacketHostileInfo.AID = ZIPacket.MyAID;
	PacketHostileInfo.GDID = GDID;
	memcpy(&PacketHostileInfo.Hostile, MyAllyInfo, sizeof(PacketHostileInfo.Hostile));
	PacketHostileInfo.answer = 0;
	CZsvrMgr::GetObj()->CZServerMgr::BroadCast(sizeof(PacketHostileInfo), (char*)&PacketHostileInfo);
}


void CIGuildMgr::ProcessAllGuild()
{
	DWORD CurTime = timeGetTime();

	if( CurTime <= m_lastSaveTime + 10000 )
		return;

	for( std::map<unsigned long,CGuild*>::iterator iter = m_guildInfo.begin(); iter != m_guildInfo.end(); ++iter )
		static_cast<CIGuildInfo*>(iter->second)->CIGuildInfo::OnProcess(CurTime);

	m_lastSaveTime = CurTime;
}


void CIGuildMgr::SendGuildMakeResult(unsigned long ZSID, unsigned long AID, unsigned long GID, int Result)
{
	PACKET_IZ_RESULT_MAKE_GUILD Packet;
	Packet.PacketType = HEADER_IZ_RESULT_MAKE_GUILD;
	Packet.AID = AID;
	Packet.GID = GID;
	Packet.result = Result;
	CZsvrMgr::GetObj()->CZServerMgr::SendMsgToZServer(ZSID, sizeof(Packet), (char*)&Packet);
}


void CIGuildMgr::OnChangeAgitGuild(unsigned long OldGID, unsigned long NewGID)
{
	if( OldGID != 0 )
	{
		AGIT_OWNER_GUILDID_CONTANIER_ITER it = m_AgitOwnerGuildIDList.find(OldGID);
		if( it != m_AgitOwnerGuildIDList.end() )
			it = m_AgitOwnerGuildIDList.erase(it);
	}

	if( NewGID != 0 )
	{
		m_AgitOwnerGuildIDList.insert(NewGID);

		CIGuildInfo* Guild = (CIGuildInfo*)this->CGuildMgr::SearchGuild(NewGID);
		if( Guild != NULL )
			Guild->CIGuildInfo::SetAllNotifyInfo(TRUE);
	}
}


void CIGuildMgr::GetGuildAgitDB()
{
	if( !g_IGuildDB.CIGuildInfoDB::GetGuildAgitDB(m_AgitOwnerGuildIDList) )
		return;

	for( AGIT_OWNER_GUILDID_CONTANIER_ITER iter = m_AgitOwnerGuildIDList.begin(); iter != m_AgitOwnerGuildIDList.end(); ++iter )
	{
		unsigned long GDID = *iter;
		CIGuildInfo* Guild = this->CIGuildMgr::LoadGuild(GDID, FALSE);
		if( Guild != NULL )
			Guild->CIGuildInfo::NotifyAllInfo(-1);
	}
}


void CIGuildMgr::OnDeleteRelatedGuild(unsigned long GDID, unsigned long OpponentGDID, int Relation, BOOL bDisOrganize)
{
	CIGuildInfo* Info = (CIGuildInfo*)this->CGuildMgr::SearchGuild(GDID);

	if( !bDisOrganize )
	{
		if( !g_IGuildDB.CIGuildInfoDB::DeleteGuildAllyInfo(GDID, OpponentGDID, Relation) )
			return;

		if( Info == NULL )
		{
			Info = this->CIGuildMgr::LoadGuild(GDID, FALSE);
			if( Info != NULL )
				Info->CIGuildInfo::DeleteRelatedGuild(GDID, OpponentGDID, Relation);
		}

		if( Relation == RELATED_GUILD_TYPE_ALLY )
		{
			if( !g_IGuildDB.CIGuildInfoDB::DeleteGuildAllyInfo(OpponentGDID, GDID, RELATED_GUILD_TYPE_ALLY) )
				return;

			CIGuildInfo* AllyInfo = (CIGuildInfo*)this->CGuildMgr::SearchGuild(OpponentGDID);
			if( AllyInfo != NULL )
				AllyInfo->CIGuildInfo::DeleteRelatedGuild(OpponentGDID, GDID, RELATED_GUILD_TYPE_ALLY);
		}
	}

	if( Info != NULL )
		Info->CIGuildInfo::DeleteRelatedGuild(GDID, OpponentGDID, Relation);
}


void CIGuildMgr::InitZServerGuild(unsigned long ZSID, std::list<unsigned long>* GDIDList)
{
	for( std::map<unsigned long,CGuild*>::iterator iter = m_guildInfo.begin(); iter != m_guildInfo.end(); ++iter )
	{
		CIGuildInfo* pInfo = static_cast<CIGuildInfo*>(iter->second);

		if( m_AgitOwnerGuildIDList.find(pInfo->CIGuildInfo::GetGDID()) == m_AgitOwnerGuildIDList.end() )
		{
			pInfo->CIGuildInfo::ResetZoneServer(ZSID);

			if( pInfo->CIGuildInfo::FindZoneServer(ZSID) == TRUE )
				GDIDList->push_back(pInfo->CIGuildInfo::GetGDID());
		}
		else
		{
			pInfo->CIGuildInfo::NotifyAllInfo(ZSID);
			Sleep(5);
		}
	}
}


void CIGuildMgr::NotifyGuild(unsigned long ZSID, unsigned long GDID)
{
	CIGuildInfo* Guild = (CIGuildInfo*)this->CGuildMgr::SearchGuild(GDID);
	if( Guild == NULL )
		return;

	Guild->CIGuildInfo::NotifyAllInfo(ZSID);
}


void CIGuildMgr::MapMove(unsigned long AID, char* mapName)
{
	USER_STRING_MAP_DATA* User = g_userMgr.CUserMgr::SearchUser(AID, 0);
	if( User == NULL )
		return;

	unsigned long GDID = g_IGuildDB.CIGuildInfoDB::GetGDID(User->GID);
	if( GDID == 0 )
		return;

	CIGuildInfo* Guild = (CIGuildInfo*)this->CGuildMgr::SearchGuild(GDID);
	if( Guild == NULL )
		return;

	Guild->CIGuildInfo::UpdateMapName(AID, mapName);
}


void CIGuildMgr::OutPutGuildInfo(unsigned long GDID)
{
	CIGuildInfo* Guild = static_cast<CIGuildInfo*>(this->CGuildMgr::SearchGuild(GDID));
	if( Guild == NULL )
		return;

	Guild->CIGuildInfo::OutPutGuildInfo(FALSE);
}


void CIGuildMgr::OnReqDisorganizeGuild(unsigned long ZSID, int GDID, int AID, int GID)
{
	CIGuildInfo* Guild = (CIGuildInfo*)this->CGuildMgr::SearchGuild(GDID);
	if( Guild == NULL )
		Guild = this->CIGuildMgr::LoadGuild(GDID, FALSE);
	if( Guild == NULL )
	{
		g_IGuildDB.CIGuildInfoDB::DeleteGuildMInfo(GID);
		return;
	}

	if( Guild->CIGuildInfo::DisOrganizeGuild(ZSID, GDID, AID, GID) == TRUE )
		this->CIGuildMgr::FreeGuild(Guild, TRUE);
}


void CIGuildMgr::GuildAllSave()
{
	while( m_GarbageGDID.size() != 0 )
	{
		unsigned long GDID = m_GarbageGDID.front();
		m_GarbageGDID.pop_front();
		this->CIGuildMgr::RemoveGuildInfo(GDID);
	}

	for( std::map<unsigned long,CGuild*>::iterator iter = m_guildInfo.begin(); iter != m_guildInfo.end(); ++iter )
	{
		CIGuildInfo* Guild = static_cast<CIGuildInfo*>(iter->second);
		g_IGuildDB.CIGuildInfoDB::UpdateGuildInfoDB(*Guild);
	}
}


BOOL CIGuildMgr::GetGuildInfo(unsigned long GDID, PACKET_IM_REQ_GUILD_INFO* pPacket)
{
	BOOL bFreeGuild = FALSE;

	CIGuildInfo* Guild = (CIGuildInfo*)this->CGuildMgr::SearchGuild(GDID);
	if( Guild == NULL )
	{
		this->CIGuildMgr::LoadGuild(GDID, FALSE); //FIXME: why call it twice?
		if( !this->CIGuildMgr::LoadGuild(GDID, FALSE) )
		{
			pPacket->PacketType = HEADER_IM_REQ_GUILD_INFO;
			pPacket->GuildID = 0;
			return FALSE;
		}

		bFreeGuild = TRUE;
	}

	pPacket->PacketType = HEADER_IM_REQ_GUILD_INFO;
	pPacket->GuildID = GDID;
	strcpy(pPacket->GuildName, Guild->CGuild::GetGuildName());
	pPacket->GuildLevel = static_cast<char>(Guild->CGuild::GetLevel());
	pPacket->GuildExp = Guild->CGuild::GetExp();

	if( bFreeGuild == TRUE )
		this->CIGuildMgr::FreeGuild(Guild, FALSE);

	return TRUE;
}


BOOL CIGuildMgr::GuildInfoInit(unsigned long GDID)
{
	CIGuildInfo* Guild = (CIGuildInfo*)this->CGuildMgr::SearchGuild(GDID);
	if( Guild == NULL )
		return FALSE;

	return Guild->CIGuildInfo::ReloadGuildInfo();
}


BOOL CIGuildMgr::AllyGuildInfoInit(unsigned long GDID)
{
	CIGuildInfo* Guild = (CIGuildInfo*)this->CGuildMgr::SearchGuild(GDID);
	if( Guild == NULL )
		return FALSE;

	return Guild->CIGuildInfo::ReloadAllyGuildInfo();
}
