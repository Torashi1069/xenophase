#include "Enum.h"
#include "ExpParameter.h"
#include "IGuildInfo.h"
#include "IGuildInfoDB.h"
#include "IGuildMgr.h"
#include "InterServer.h"
#include "UserMgr.h"
#include "Common/Packet.h"
#include "shared/NCriticalErrorLog.h"
#include "Zsvr/CZsvrMgr.h"


unsigned short skillInfo[15][2] = {
	{ SKID_GD_APPROVAL,      0 },
	{ SKID_GD_KAFRACONTRACT, 0 },
	{ SKID_GD_GUARDRESEARCH, 0 },
	{ SKID_GD_GUARDUP,       0 },
	{ SKID_GD_EXTENSION,     0 },
	{ SKID_GD_GLORYGUILD,    0 },
	{ SKID_GD_LEADERSHIP,    0 },
	{ SKID_GD_GLORYWOUNDS,   0 },
	{ SKID_GD_SOULCOLD,      0 },
	{ SKID_GD_HAWKEYES,      0 },
	{ SKID_GD_DEVELOPMENT,   0 },
	{ SKID_GD_BATTLEORDER,   0 },
	{ SKID_GD_REGENERATION,  0 },
	{ SKID_GD_RESTORE,       0 },
	{ SKID_GD_EMERGENCYCALL, 0 },
};


CIGuildInfo::CIGuildInfo()
{
	m_DBInfoChange = 0; // unused?
}


CIGuildInfo::~CIGuildInfo()
{
}


void CIGuildInfo::Init()
{
	m_packetDispatcher.m_guildInfo = this;
	m_lastSaveTime = timeGetTime();

	this->CGuild::Init();

	memset(m_ZServerInfo, 0, sizeof(m_ZServerInfo));
	m_bAllNotifyInfo = FALSE;
	m_bSkillSave = TRUE;
	m_InfoUse = TRUE;

	if( g_isGuildAllSend == TRUE )
		m_bAllNotifyInfo = FALSE;

	m_ZServerList.clear();
//	m_MemberZSID.clear();
}


void CIGuildInfo::OnProcess(const unsigned long CurTime)
{
	if( !m_InfoUse )
		return;

	if( CurTime > m_lastSaveTime + 3000000 || CurTime < m_lastSaveTime )
	{
		g_IGuildDB.CIGuildInfoDB::UpdateGuildInfoDB(*this);
		m_lastSaveTime = CurTime;
	}
}


void CIGuildInfo::Send(int ZSID, short len, char* buf)
{
	if( m_bAllNotifyInfo == TRUE )
	{
		CZsvrMgr::GetObj()->CZServerMgr::BroadCast(len, buf);
	}
	else
	if( ZSID == -1 )
	{
		for( std::list<int>::iterator iter = m_ZServerList.begin(); iter != m_ZServerList.end(); ++iter )
			CZsvrMgr::GetObj()->CZServerMgr::SendMsgToZServer(*iter, len, buf);
	}
	else
	{
		CZsvrMgr::GetObj()->CZServerMgr::SendMsgToZServer(ZSID, len, buf);
	}
}


BOOL CIGuildInfo::AllLoadDB(unsigned long GDID)
{
	BOOL Result;

	GUILDINFO info;
	Result = g_IGuildDB.CIGuildInfoDB::GetGuildInfoDB(GDID, info);

	if( info.Level >= 50 )
		info.Level = 50;

	this->CGuild::SetGuildInfo(&info);

	g_IGuildDB.CIGuildInfoDB::GetGuildNoticeDB(GDID, m_guildNotice);

	if( Result )
		Result = this->CIGuildInfo::GetMInfo(GDID);

	this->CIGuildInfo::GetAllyInfo(GDID);
	this->CIGuildInfo::GetBanishInfo(GDID);

	if( Result )
		Result = this->CIGuildInfo::GetMPosition(GDID);

	if( IsSetting(SETTING_GUILDWAR) && Result )
		this->CIGuildInfo::LoadSkill(FALSE);

	return Result;
}


BOOL CIGuildInfo::ReLoadDB()
{
	GUILDINFO info;
	BOOL result = g_IGuildDB.CIGuildInfoDB::GetGuildInfoDB(m_GDID, info);

	if( info.Level >= 50 )
		info.Level = 50;

	this->CGuild::SetGuildInfo(&info);
	memset(m_ZServerInfo, 0, sizeof(m_ZServerInfo));

	return result;
}


BOOL CIGuildInfo::GetMInfo(unsigned long GDID)
{
	char Buf[MAX_GUILD_MEMBER_LIST*sizeof(GUILDMINFO)] = {};
	int buflen = 0;

	if( g_IGuildDB.CIGuildInfoDB::GetGuildMInfoDB(GDID, buflen, Buf) == 0 )
		return FALSE;

	GUILDMINFO* Data = reinterpret_cast<GUILDMINFO*>(Buf);
	int count = buflen / sizeof(GUILDMINFO);
	if( count < 1 )
		return FALSE;
	if( count > MAX_GUILD_MEMBER_LIST )
		count = MAX_GUILD_MEMBER_LIST;

	if( m_GuildMInfoMPool.CMemoryMgr2<GUILDMINFO>::GetAllocSize() != 0 )
	{// already loaded(?)
		NCriticalErrorLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__, "GetMInfo Size Error : %d ", m_GuildMInfoMPool.CMemoryMgr2<GUILDMINFO>::GetAllocSize());
		m_GuildMInfoMPool.CMemoryMgr2<GUILDMINFO>::Reset();
	}

	for( int i = 0; i < count; ++i )
	{
		GUILDMINFO* Info = m_GuildMInfoMPool.CMemoryMgr2<GUILDMINFO>::Alloc();
		if( Info == NULL )
		{
			NCriticalErrorLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__, "m_GuildMInfoMPool Over Size");
			break;
		}

		memcpy(Info, &Data[i], sizeof(GUILDMINFO));
		if( Info->MemberExp < 0 )
			Info->MemberExp = 0;
		Info->sex = 0;
		Info->head = 0;
		Info->headPalette = 0;
		Info->status = 0;

		this->CGuild::AddGuildMInfo(Info);
	}

	return TRUE;
}


void CIGuildInfo::GetAllyInfo(unsigned long GDID)
{
	int buflen = 0;
	char Buf[3072] = {};

	if( g_IGuildDB.CIGuildInfoDB::GetGuildAllyInfoDB(GDID, buflen, Buf) == 0 )
		return;

	GUILDALLYINFO* Data = reinterpret_cast<GUILDALLYINFO*>(Buf);
	int count = buflen / sizeof(GUILDALLYINFO);

	m_GuildAllyInfoMPool.CMemoryMgr2<GUILDALLYINFO>::Reset();

	for( int i = 0; i < count; ++i )
	{
		GUILDALLYINFO* Info = m_GuildAllyInfoMPool.CMemoryMgr2<GUILDALLYINFO>::Alloc();
		if( Info == NULL )
			continue;

		memcpy(Info, &Data[i], sizeof(GUILDALLYINFO));
		this->CGuild::AddGuildAllyInfo(Info);

		if( i + 1 >= 6 )
			break;
	}
}


void CIGuildInfo::GetBanishInfo(unsigned long GDID)
{
	int buflen = 0;
	char Buf[4440] = {};

	if( g_IGuildDB.CIGuildInfoDB::GetGuildBanishInfoDB(GDID, buflen, Buf) == 0 )
		return;

	GUILDBANISHINFO* Data = reinterpret_cast<GUILDBANISHINFO*>(Buf);
	int count = buflen / sizeof(GUILDBANISHINFO);
	if( count < 1 )
		return;

	for( int i = 0; i < count; ++i )
	{
		if( this->CGuild::GetGuildBanishSize() >= 1 )
		{
			int GID = this->CGuild::DeleteFirstBanishInfo();
			if( GID == 0 )
				continue;

			g_IGuildDB.CIGuildInfoDB::DeleteGuildBanishInfo(m_GDID, GID);
		}

		GUILDBANISHINFO* Info = m_GuildBanishInfoMPool.CMemoryMgr2<GUILDBANISHINFO>::Alloc();
		if( Info == NULL )
			continue;

		memcpy(Info, &Data[i], sizeof(GUILDBANISHINFO));
		this->CGuild::AddGuildBanishInfo(Info);

		if( i + 1 >= 2 )
			break;
	}
}


BOOL CIGuildInfo::GetMPosition(unsigned long GDID)
{
	int buflen = 0;
	char Buf[3072] = {};

	if( g_IGuildDB.CIGuildInfoDB::GetGuildMemberPositionDB(GDID, buflen, Buf) == 0 )
		return FALSE;

	GUILDMPOSITION* Data = reinterpret_cast<GUILDMPOSITION*>(Buf);
	int count = buflen / sizeof(GUILDMPOSITION);
	if( count < 1 )
		return FALSE;

	for( int i = 0; i < count; ++i )
	{
		GUILDMPOSITION* Info = m_GuildMPositionMPool.CMemoryMgr2<GUILDMPOSITION>::Alloc();
		if( Info == NULL )
			continue;

		memcpy(Info, &Data[i], sizeof(GUILDMPOSITION));
		this->CGuild::AddGuildMPosition(Info);

		if( i + 1 >= 20 )
			break;
	}

	return TRUE;
}


void CIGuildInfo::JoinGuild(unsigned long ZSID, unsigned long GID, unsigned long AID, char* Name, char* Account, unsigned char answer)
{
	unsigned long OLDAID = CIGuildMgr::GetObj()->CIGuildMgr::SearchAIDMap(GID);
	if( OLDAID == 0 )
		return;

	if( answer == 0 )
	{
		PACKET_IZ_ACK_REQ_JOIN_GUILD Packet;
		Packet.PacketType = HEADER_IZ_ACK_REQ_JOIN_GUILD;
		Packet.AID = OLDAID;
//		Packet.ReqAID = 0;
//		Packet.GDID = 0;
		Packet.answer = 1;
		this->CIGuildInfo::Send(ZSID, sizeof(Packet), (char*)&Packet);
		return;
	}

	if( g_IGuildDB.CIGuildInfoDB::GetGDID(GID) )
	{
		PACKET_IZ_ACK_REQ_JOIN_GUILD Packet;
		Packet.PacketType = HEADER_IZ_ACK_REQ_JOIN_GUILD;
		Packet.AID = OLDAID;
//		Packet.ReqAID = 0;
//		Packet.GDID = 0;
		Packet.answer = 0;
		this->CIGuildInfo::Send(ZSID, sizeof(Packet), (char*)&Packet);
		return;
	}

	if( this->CGuild::GetGuildMSize() >= m_maxUserNum )
	{
		PACKET_IZ_ACK_REQ_JOIN_GUILD Packet;
		Packet.PacketType = HEADER_IZ_ACK_REQ_JOIN_GUILD;
		Packet.AID = AID;
//		Packet.ReqAID = 0;
//		Packet.GDID = 0;
		Packet.answer = 3;
		this->CIGuildInfo::Send(ZSID, sizeof(Packet), (char*)&Packet);
		return;
	}

	GUILDMINFO* MInfo = this->CGuild::AllocGuildMInfo();
	if( MInfo == NULL )
		return;

	USER_STRING_MAP_DATA* User = g_userMgr.CUserMgr::SearchUser(AID, GID);
	if( User == NULL )
		return;

	if( User->level <= 0 )
		return;

	memset(MInfo, 0, sizeof(*MInfo));
	this->CGuild::InitGuildMInfo(MInfo, Name, Account, AID, m_GDID, GID, 19, 1, User->level, User->job, User->head, User->headpalette, User->sex);

	g_IGuildDB.CIGuildInfoDB::InsertGuildMember(*MInfo);
	this->CGuild::AddGuildMInfo(MInfo);

	PACKET_IZ_GUILD_MEMBER_ADD PacketMInfo;
	PacketMInfo.PacketType = HEADER_IZ_GUILD_MEMBER_ADD;
	PacketMInfo.GDID = m_GDID;
	memcpy(&PacketMInfo.Info, MInfo, sizeof(PacketMInfo.Info));
	this->CIGuildInfo::Send(-1, sizeof(PacketMInfo), (char*)&PacketMInfo);

	this->CIGuildInfo::ChangeMemberInfo(ZSID, AID, GID, 1);
	this->CIGuildInfo::UpdateCharGDID(PACKET_IZ_UPDATE_CHARGDID::TYPE_JOIN, ZSID, AID, GID, m_GDID, m_emblemVersion);

	PACKET_IZ_ACK_REQ_JOIN_GUILD Packet;
	Packet.PacketType = HEADER_IZ_ACK_REQ_JOIN_GUILD;
	Packet.AID = AID;
	Packet.ReqAID = OLDAID;
	Packet.GDID = m_GDID;
	Packet.answer = 2;
	this->CIGuildInfo::Send(ZSID, sizeof(Packet), (char*)&Packet);
}


template<typename T> class MyMemoryMgrPtr
{
public:
	MyMemoryMgrPtr(CMemoryMgr2<T>& in_cpMemoryMgr) : m_cpMemoryMgr(in_cpMemoryMgr) { m_myptr = m_cpMemoryMgr.CMemoryMgr2<T>::Alloc(); }
	~MyMemoryMgrPtr() { if( m_myptr != NULL ) { m_cpMemoryMgr.CMemoryMgr2<T>::Free(m_myptr); m_myptr = NULL; } }

private:
	MyMemoryMgrPtr(const MyMemoryMgrPtr&); // = delete;
	MyMemoryMgrPtr& operator=(const MyMemoryMgrPtr&); // = delete;

public:
	void release() { m_myptr = NULL; }
	T* operator->() { return m_myptr; }
	T* get() { return m_myptr; }

private:
	/* this+0 */ CMemoryMgr2<T>& m_cpMemoryMgr;
	/* this+4 */ GUILDBANISHINFO* m_myptr;
};


void CIGuildInfo::BanMember(const PACKET_ZI_REQ_BAN_GUILD* in_pPacket)
{
	int PosID = this->CGuild::GetGuildPosID(in_pPacket->MyGID);
	if( !this->CGuild::GetPosPenaltyRight(PosID) )
		return;

	std::vector<GUILDMINFO*>::iterator iter;

	for( iter = m_guildMInfo.begin(); iter != m_guildMInfo.end(); ++iter )
		if( (*iter)->GID == in_pPacket->GID )
			break;

	if( iter == m_guildMInfo.end() )
		return;

	GUILDMINFO* cpMember = *iter;

	if( cpMember->PositionID == 0 )
		return;

	if( this->CGuild::GetGuildBanishSize() >= 1 )
	{
		int FirstGID = this->CGuild::DeleteFirstBanishInfo();
		if( FirstGID == 0 )
			return;
		g_IGuildDB.CIGuildInfoDB::DeleteGuildBanishInfo(m_GDID, FirstGID);
	}

	MyMemoryMgrPtr<GUILDBANISHINFO> banishPtr(m_GuildBanishInfoMPool);
	GUILDBANISHINFO* banishInfo = banishPtr.get();
	if( banishInfo == NULL )
		return;

	if( !g_IGuildDB.CIGuildInfoDB::DeleteGuildMInfo(in_pPacket->GID) )
	{
		this->CIGuildInfo::GuildErrorLog("Guild Ban DB Failed\n", __LINE__, __FILE__);
		return;
	}

	banishInfo->AID = in_pPacket->AID;
	banishInfo->GDID = m_GDID;
	banishInfo->GID = in_pPacket->GID;
	memcpy(banishInfo->MemberAccount, cpMember->AccountName, 24);
	memcpy(banishInfo->MemberName, cpMember->CharName, 24);
	memcpy(banishInfo->Reason, in_pPacket->reasonDesc, 40);

	if( !this->CGuild::FindBanishMember(in_pPacket->GID) )
	{
		g_IGuildDB.CIGuildInfoDB::InsertGuildBanishInfo(*banishInfo);
		this->CGuild::AddGuildBanishInfo(banishInfo);
		banishPtr.release();
	}

	// banishPtr destroyed here

	static const char BlankMapName[] = "";
	this->CIGuildInfo::UpdateMapName(in_pPacket->AID, BlankMapName);

	PACKET_IZ_ACK_BAN_GUILD IZPacket;
	IZPacket.PacketType = HEADER_IZ_ACK_BAN_GUILD;
	IZPacket.GDID = in_pPacket->GDID;
	IZPacket.AID = in_pPacket->AID;
	IZPacket.GID = in_pPacket->GID;
	memcpy(IZPacket.charName, cpMember->CharName, sizeof(IZPacket.charName));
	memcpy(IZPacket.AccountName, cpMember->AccountName, sizeof(IZPacket.AccountName));
	memcpy(IZPacket.reasonDesc, in_pPacket->reasonDesc, sizeof(IZPacket.reasonDesc));
	this->CIGuildInfo::Send(-1, sizeof(IZPacket), (char*)&IZPacket);

	USER_STRING_MAP_DATA* User = g_userMgr.CUserMgr::SearchUser(in_pPacket->AID, in_pPacket->GID);
	if( User != NULL )
		this->CIGuildInfo::RemoveZoneServer(User->ServerID);

	m_GuildMInfoMPool.CMemoryMgr2<GUILDMINFO>::Free(*iter);
	m_guildMInfo.erase(iter);
}


BOOL CIGuildInfo::DeleteMember(unsigned long ZSID, char* Buf)
{
	PACKET_ZI_REQ_LEAVE_GUILD& ZIPacket = *reinterpret_cast<PACKET_ZI_REQ_LEAVE_GUILD*>(Buf);

	std::vector<GUILDMINFO*>::iterator iter;

	for( iter = m_guildMInfo.begin(); iter != m_guildMInfo.end(); ++iter )
		if( (*iter)->GID == ZIPacket.GID )
			break;

	if( iter == m_guildMInfo.end() )
		return FALSE;

	if( (*iter)->PositionID == 0 && this->CGuild::GetGuildMSize() >= 2 )
		return FALSE;

	if( !g_IGuildDB.CIGuildInfoDB::DeleteGuildMInfo(ZIPacket.GID) )
		return FALSE;

	char mapName[16] = {};
	this->CIGuildInfo::UpdateMapName(ZIPacket.AID, mapName);

	PACKET_IZ_ACK_LEAVE_GUILD IZPacket;
	IZPacket.PacketType = HEADER_IZ_ACK_LEAVE_GUILD;
	IZPacket.GDID = m_GDID;
	IZPacket.AID = ZIPacket.AID;
	IZPacket.GID = ZIPacket.GID;
	memcpy(IZPacket.charName, (*iter)->CharName, sizeof(IZPacket.charName));
	memcpy(IZPacket.reasonDesc, ZIPacket.reasonDesc, sizeof(IZPacket.reasonDesc));
	this->CIGuildInfo::Send(-1, sizeof(IZPacket), (char*)&IZPacket);
	this->CIGuildInfo::RemoveZoneServer(ZSID);

	m_GuildMInfoMPool.CMemoryMgr2<GUILDMINFO>::Free(*iter);
	m_guildMInfo.erase(iter);

	return TRUE;
}


BOOL CIGuildInfo::DeleteMember(unsigned long GID)
{
	std::vector<GUILDMINFO*>::iterator iter;

	for( iter = m_guildMInfo.begin(); iter != m_guildMInfo.end(); ++iter )
		if( (*iter)->GID == GID )
			break;

	if( iter == m_guildMInfo.end() )
		return FALSE;

	if( !g_IGuildDB.CIGuildInfoDB::DeleteGuildMInfo(GID) )
		return FALSE;

	m_GuildMInfoMPool.CMemoryMgr2<GUILDMINFO>::Free(*iter);
	m_guildMInfo.erase(iter);

	return TRUE;
}


BOOL CIGuildInfo::DisOrganizeGuild(unsigned long ZSID, int GDID, int AID, int GID)
{
	if( this->CGuild::GetGuildMSize() >= 2 )
	{
		PACKET_IZ_REQ_DISORGANIZE_GUILD_RESULT IZPacket;
		IZPacket.PacketType = HEADER_IZ_REQ_DISORGANIZE_GUILD_RESULT;
		IZPacket.GDID = GDID;
		IZPacket.AID = AID;
		IZPacket.GID = GID;
		IZPacket.result = 2;
		this->CIGuildInfo::Send(ZSID, sizeof(IZPacket), (char*)&IZPacket);

		return FALSE;
	}

	this->CIGuildInfo::DeleteMember(GID);
	this->CIGuildInfo::UpdateCharGDID(PACKET_IZ_UPDATE_CHARGDID::TYPE_DISORGANIZE, ZSID, AID, GID, 0, 0);

	if( !g_IGuildDB.CIGuildInfoDB::DeleteAllGuildAllyInfo(GDID)
	 || !g_IGuildDB.CIGuildInfoDB::DeleteAllGuildBanish(GDID)
	 || !g_IGuildDB.CIGuildInfoDB::DeleteAllGuildMPosition(GDID)
	 || !g_IGuildDB.CIGuildInfoDB::DeleteGuildInfoDB(GDID)
	 || !g_IGuildDB.CIGuildInfoDB::DeleteGuildNotice(GDID)
	 || !g_IGuildDB.CIGuildInfoDB::DeleteGuildSkill(GDID) )
		return FALSE;

	for( std::vector<GUILDALLYINFO*>::iterator iter = m_guildAllyInfo.begin(); iter != m_guildAllyInfo.end(); ++iter )
	{
		GUILDALLYINFO* info = *iter;
		if( info == NULL )
			continue;

		if( info->Relation != RELATED_GUILD_TYPE_ALLY )
			continue;

		CIGuildMgr::GetObj()->CIGuildMgr::OnDeleteRelatedGuild(info->OpponentGDID, GDID, RELATED_GUILD_TYPE_ALLY, TRUE);
	}

	PACKET_IZ_REQ_DISORGANIZE_GUILD_RESULT IZPacket;
	IZPacket.PacketType = HEADER_IZ_REQ_DISORGANIZE_GUILD_RESULT;
	IZPacket.GDID = GDID;
	IZPacket.AID = AID;
	IZPacket.GID = GID;
	IZPacket.result = 0;
	this->CIGuildInfo::Send(ZSID, sizeof(IZPacket), (char*)&IZPacket);

	return TRUE;
}


void CIGuildInfo::OnReqGuildPositionInfo(char* buf, unsigned short Len)
{
	PACKET_ZI_REQ_GUILD_POSITION_INFO& ZIPacket = *reinterpret_cast<PACKET_ZI_REQ_GUILD_POSITION_INFO*>(buf);
	int DataLen = ZIPacket.PacketLength - sizeof(ZIPacket);

	char Buffer[3072] = {};
	PACKET_IZ_ACK_GUILD_POSITION_INFO& IZPacket = *reinterpret_cast<PACKET_IZ_ACK_GUILD_POSITION_INFO*>(Buffer);

	int count = DataLen / sizeof(GUILD_REG_POSITION_INFO);
	if( DataLen % sizeof(GUILD_REG_POSITION_INFO) != 0 )
		return;
	
	if( count < 1 )
		return;

	for( int Index = 0; Index < count; ++Index )
	{
		GUILD_REG_POSITION_INFO Guild;
		memcpy(&Guild, &ZIPacket.Info[Index], sizeof(GUILD_REG_POSITION_INFO));

		BOOL JoinRight = FALSE;
		if( Guild.right & 0x01 )
			JoinRight = TRUE;

		BOOL PenaltyRight = FALSE;
		if( Guild.right & 0x10 )
			PenaltyRight = TRUE;

		if( Guild.payRate > 50 )
			Guild.payRate = 50;

		if( !g_IGuildDB.CIGuildInfoDB::UpdateMemberPos(m_GDID, Guild, JoinRight, PenaltyRight) )
			break;

		this->CGuild::UpdateMemberPosition(Guild.positionID, Guild.posName, Guild.payRate, JoinRight, PenaltyRight);
	}

	IZPacket.PacketType = HEADER_IZ_ACK_GUILD_POSITION_INFO;
	IZPacket.PacketLength = Len; //FIXME: unreliable
	IZPacket.GDID = m_GDID;
	IZPacket.AID = ZIPacket.AID;
	memcpy(IZPacket.Info, ZIPacket.Info, Len - 12); //FIXME: unreliable
	this->CIGuildInfo::Send(-1, IZPacket.PacketLength, (char*)&IZPacket);
}


void CIGuildInfo::OnReqChangePosition(char* buf, unsigned short Len)
{
	PACKET_ZI_REQ_CHANGE_MEMBERPOS& ZIPacket = *reinterpret_cast<PACKET_ZI_REQ_CHANGE_MEMBERPOS*>(buf);
	int DataLen = ZIPacket.PacketLength - sizeof(ZIPacket);

	char Buffer[3072] = {};
	PACKET_IZ_ACK_CHANGE_MEMBERPOS& IZPacket = *reinterpret_cast<PACKET_IZ_ACK_CHANGE_MEMBERPOS*>(Buffer);

	if( buf == NULL )
		return;

	int count = DataLen / sizeof(MEMBER_POSITION_INFO);
	if( DataLen % sizeof(MEMBER_POSITION_INFO) != 0 )
		return;

	if( count < 1 || count > 9 )
		return;

	if( this->CGuild::GetMasterName() == NULL )
		return;

	IZPacket.PacketType = HEADER_IZ_ACK_CHANGE_MEMBERPOS;
	IZPacket.PacketLength = sizeof(IZPacket) + DataLen;
	IZPacket.GDID = m_GDID;
	IZPacket.AID = ZIPacket.AID;

	for( int Index = 0; Index < count; ++Index )
	{
		MEMBER_POSITION_INFO Guild;
		memcpy(&Guild, &ZIPacket.Info[Index], sizeof(MEMBER_POSITION_INFO));

		if( this->CGuild::GetMemberName(Guild.GID) == NULL )
			return;

		if( strcmp(m_guildMasterName, this->CGuild::GetMemberName(Guild.GID)) == 0 )
			Guild.positionID = 0;
		else
		if( Guild.positionID == 0 )
			Guild.positionID = 19;

		if( !g_IGuildDB.CIGuildInfoDB::UpdateMemberChangePos(m_GDID, Guild.GID, Guild.positionID) )
			return;

		this->CGuild::UpdateMemberChangePos(Guild.GID, Guild.positionID);

		memcpy(&IZPacket.Info[Index], &Guild, sizeof(MEMBER_POSITION_INFO));
	}

	this->CIGuildInfo::Send(-1, IZPacket.PacketLength, (char*)&IZPacket);
}


void CIGuildInfo::RegisterGuildEmblem(char* buf, unsigned short Len)
{
	PACKET_ZI_REGISTER_GUILD_EMBLEM_IMG& ZIPacket = *reinterpret_cast<PACKET_ZI_REGISTER_GUILD_EMBLEM_IMG*>(buf);
	int DataLen = Len - sizeof(ZIPacket);

	++m_emblemVersion;
	g_IGuildDB.CIGuildInfoDB::UpdateGuildEmblem(m_GDID, m_emblemVersion);

	char Buffer[3072] = {};
	PACKET_IZ_GET_GUILD_EMBLEM_IMG& IZPacket = *reinterpret_cast<PACKET_IZ_GET_GUILD_EMBLEM_IMG*>(Buffer);
	IZPacket.PacketType = HEADER_IZ_GET_GUILD_EMBLEM_IMG;
	IZPacket.PacketLength = sizeof(IZPacket) + DataLen;
	IZPacket.AID = ZIPacket.AID;
	IZPacket.GDID = m_GDID;
	IZPacket.emblemVersion = m_emblemVersion;
	memcpy(IZPacket.Data, ZIPacket.Data, DataLen);
	CZsvrMgr::GetObj()->CZServerMgr::BroadCast(IZPacket.PacketLength, (char*)&IZPacket);
}


void CIGuildInfo::GetGuildNotice(char* buf)
{
	PACKET_ZI_GUILD_NOTICE& ZIPacket = *reinterpret_cast<PACKET_ZI_GUILD_NOTICE*>(buf);

	if( !g_IGuildDB.CIGuildInfoDB::UpdateGuildNotice(m_GDID, ZIPacket.subject, ZIPacket.notice) )
		return;

	m_guildNotice.GDID = m_GDID;
	memcpy(m_guildNotice.Subject, ZIPacket.subject, sizeof(m_guildNotice.Subject));
	memcpy(m_guildNotice.Notice, ZIPacket.notice, sizeof(m_guildNotice.Notice));

	PACKET_IZ_GUILD_NOTICE IZPacket;
	IZPacket.PacketType = HEADER_IZ_GUILD_NOTICE;
	IZPacket.GDID = m_GDID;
	memcpy(IZPacket.subject, ZIPacket.subject, sizeof(IZPacket.subject));
	memcpy(IZPacket.notice, ZIPacket.notice, sizeof(IZPacket.notice));
	this->CIGuildInfo::Send(-1, sizeof(IZPacket), (char*)&IZPacket);
}


BOOL CIGuildInfo::DeleteRelatedGuild(unsigned long GDID, unsigned long OpponentGDID, int Relation)
{
	this->CGuild::DeleteGuildAllyInfo(OpponentGDID, Relation);

	PACKET_IZ_DELETE_RELATED_GUILD DeletePacket;
	DeletePacket.PacketType = HEADER_IZ_DELETE_RELATED_GUILD;
	DeletePacket.GDID = GDID;
	DeletePacket.OpponentGDID = OpponentGDID;
	DeletePacket.Relation = Relation;
	this->CIGuildInfo::Send(-1, sizeof(DeletePacket), (char*)&DeletePacket);

	return TRUE;
}


void CIGuildInfo::UpdateCharGDID(unsigned char TYPE, unsigned long ZSID, unsigned long AID, unsigned long GID, unsigned long GDID, int EmblemVer)
{
	PACKET_IZ_UPDATE_CHARGDID Packet;
	Packet.PacketType = HEADER_IZ_UPDATE_CHARGDID;
	Packet.Type = TYPE;
	Packet.AID = AID;
	Packet.GDID = GDID;
	Packet.GID = GID;
	Packet.right = 0;

	if( GDID != 0 )
	{
		Packet.emblemVer = EmblemVer;

		if( this->CGuild::GetGuildName() != NULL )
			memcpy(Packet.GuildName, m_guildName, sizeof(Packet.GuildName));

		int PosID = this->CGuild::GetGuildPosID(GID);
		BOOL JoinRight = this->CGuild::GetPosJoinRight(PosID);
		BOOL PenaltyRight = this->CGuild::GetPosPenaltyRight(PosID);

		if( this->CGuild::IsMaster(GID) )
		{
			Packet.right |= 0x11;
			Packet.isMaster = true;
		}
		else
		{
			if( JoinRight )
				Packet.right |= 0x01;
			if( PenaltyRight )
				Packet.right |= 0x10;
			Packet.isMaster = false;
		}
	}
	else
	{
		Packet.emblemVer = 0;
		Packet.GuildName[0] = '\0';
		Packet.isMaster = false;
	}

	this->CIGuildInfo::Send(ZSID, sizeof(Packet), (char*)&Packet);
}


void CIGuildInfo::OnUpdateGuildZeny(char* buf)
{
	PACKET_ZI_GUILD_ZENY& ZIPacket = *reinterpret_cast<PACKET_ZI_GUILD_ZENY*>(buf);

	if( ZIPacket.AID == -1 )
	{
		m_money -= ZIPacket.zeny;

		PACKET_IZ_GUILD_ZENY_UPDATE_ALL Update;
		Update.PacketType = HEADER_IZ_GUILD_ZENY_UPDATE_ALL;
		Update.GDID = ZIPacket.GDID;
		Update.Zeny = m_money;
		this->CIGuildInfo::Send(-1, sizeof(Update), (char*)&Update);
	}
	else
	{
		int ret = this->CGuild::UpdateMoney(ZIPacket.zeny, ZIPacket.type);

		PACKET_IZ_GUILD_ZENY IZPacket;
		IZPacket.PacketType = HEADER_IZ_GUILD_ZENY;
		IZPacket.GDID = ZIPacket.GDID;
		IZPacket.AID = ZIPacket.AID;
		IZPacket.GID = ZIPacket.GID;
		memcpy(IZPacket.mapName, ZIPacket.mapName, sizeof(IZPacket.mapName));
		IZPacket.type = ZIPacket.type;
		IZPacket.zeny = ZIPacket.zeny;
		IZPacket.ret = ret;
		int HsvrID = g_userMgr.CUserMgr::SearchUserServerID(ZIPacket.AID);
		CZsvrMgr::GetObj()->CZServerMgr::SendMsgToZServer(HsvrID, sizeof(IZPacket), (char*)&IZPacket);

		if( ret != ZENY_UPDATE_SUCCESS )
			return;

		PACKET_IZ_GUILD_ZENY_UPDATE_ALL Update;
		Update.PacketType = HEADER_IZ_GUILD_ZENY_UPDATE_ALL;
		Update.GDID = ZIPacket.GDID;
		Update.Zeny = m_money;
		this->CIGuildInfo::Send(-1, sizeof(Update), (char*)&Update);
	}
}


void CIGuildInfo::GuildErrorLog(char* buf, int line, char* filename)
{
	if( buf == NULL )
		return;

	FILE* fp = fopen("GuildError.txt", "a");
	if( fp == NULL )
		return;

	SYSTEMTIME st;
	GetLocalTime(&st);
	fprintf(fp, "file:%s, line:%d Error:%u day_%u:%u:%u %s \n", filename, line, st.wDay, st.wHour, st.wMinute, st.wSecond, buf);

	fclose(fp);
}


BOOL CIGuildInfo::LoadSkill(BOOL bNotify)
{
	m_skillDataLength = g_IGuildSkillDB.CIGuildSkillDB::GetSkill(m_GDID, m_skillData, m_skillPoint);
	if( m_skillDataLength != 0 && m_skillDataLength != 60 )
	{
		int count;
		for( count = 20; count < 60; count += 4 )
			memcpy(m_skillData + count, (BYTE*)skillInfo + count, 4);

		m_skillDataLength = count;
		this->CIGuildInfo::SaveSkillDB();
	}

	if( m_skillDataLength == 0 )
	{
		m_skillPoint = m_level - 1;
		g_IGuildSkillDB.CIGuildSkillDB::InsertSkill(m_GDID, m_skillPoint);

		int count;
		for( count = 0; count < 60; count += 4 )
			memcpy(m_skillData + count, (BYTE*)skillInfo + count, 4);

		m_skillDataLength = count;
		this->CIGuildInfo::SaveSkillDB();
	}

	int SkillLevel = 0;
	memcpy(&SkillLevel, &m_skillData[18], 2); // SKID_GD_EXTENSION
	m_maxUserNum = 16 + 4 * SkillLevel;

	if( bNotify )
		this->CIGuildInfo::NotifyGuildSkillInfo(-1);

	return TRUE;
};


void CIGuildInfo::NotifyGuildSkillInfo(unsigned long ZSID)
{
	if( !IsSetting(SETTING_GUILDWAR) )
		return;

	PACKET_IZ_GUILD_NOTIFYSKILLDATA IZPacket;
	IZPacket.PacketType = HEADER_IZ_GUILD_NOTIFYSKILLDATA;
	IZPacket.PacketLength = sizeof(IZPacket) + (short)m_skillDataLength;
	IZPacket.SkillPoint = m_skillPoint;
	IZPacket.GDID = m_GDID;
	IZPacket.isForceSend = 1;
	this->CIGuildInfo::Send(ZSID, sizeof(IZPacket), (char*)&IZPacket);
	this->CIGuildInfo::Send(ZSID, (short)m_skillDataLength, (char*)m_skillData);
}


void CIGuildInfo::SaveSkillDB()
{
	if( m_GDID <= 0 )
		return;

	if( m_skillPoint >= 100 )
		return;

	m_bSkillSave = g_IGuildSkillDB.CIGuildSkillDB::UpdateSkill(m_GDID, (char*)m_skillData, m_skillDataLength, m_skillPoint);
}


void CIGuildInfo::OnGuildSkillUpdate(char* buf)
{
	PACKET_ZI_GDSKILL_UPDATE& ZIPacket = *reinterpret_cast<PACKET_ZI_GDSKILL_UPDATE*>(buf);
	int DataLen = ZIPacket.PacketLength - sizeof(ZIPacket);

	if( buf == NULL )
		return;

	memcpy(m_skillData, ZIPacket.Data, DataLen);
	m_skillDataLength = DataLen;
	m_skillPoint = ZIPacket.SkillPoint;
	this->CIGuildInfo::SaveSkillDB();
	this->CIGuildInfo::NotifyGuildSkillInfo(-1);
}


static int SortMember(const void* pOne, const void* pTwo)
{
	return reinterpret_cast<const GUILDMINFO*>(pOne)->PositionID
	     - reinterpret_cast<const GUILDMINFO*>(pTwo)->PositionID;
}


void CIGuildInfo::NotifyAllInfo(int ZSID)
{
	int buflen;
	char Buf[10240];

	PACKET_IZ_GUILDINFO_TOD Packet;
	Packet.PacketType = HEADER_IZ_GUILDINFO_TOD;
	Packet.GDID = m_GDID;
	Packet.Data.GDID = Packet.GDID;
	Packet.Data.Level = m_level;
	strcpy(Packet.Data.Name, m_guildName);
	strcpy(Packet.Data.MName, m_guildMasterName);
	Packet.Data.MaxUserNum = m_maxUserNum;
	Packet.Data.Honor = m_honor;
	Packet.Data.Virtue = m_virtue;
	Packet.Data.Type = m_type;
	Packet.Data.Class = m_class;
	Packet.Data.Money = m_money;
	Packet.Data.ArenaWin = m_arenaWin;
	Packet.Data.ArenaLose = m_arenaLose;
	Packet.Data.ArenaDrawn = m_arenaDrawn;
	strcpy(Packet.Data.ManageLand, m_manageLand);
	Packet.Data.Exp = m_exp;
	Packet.Data.EmblemVersion = m_emblemVersion;
	Packet.Data.Point = m_point;
	strcpy(Packet.Data.Desc, m_desc);
	this->CIGuildInfo::Send(ZSID, sizeof(Packet), (char*)&Packet);

	PACKET_IZ_GUILD_NOTICE IZPacket;
	IZPacket.PacketType = HEADER_IZ_GUILD_NOTICE;
	IZPacket.GDID = m_GDID;
	memcpy(IZPacket.notice, m_guildNotice.Notice, 120);
	memcpy(IZPacket.subject, m_guildNotice.Subject, 60);
	this->CIGuildInfo::Send(ZSID, sizeof(IZPacket), (char*)&IZPacket);

	int MemberCounter = 0;
	char GuildMBuf[MAX_GUILD_MEMBER_LIST * sizeof(GUILDMINFO)];

	buflen = 0;
	for( std::vector<GUILDMINFO*>::iterator i = m_guildMInfo.begin(); i != m_guildMInfo.end(); ++i )
	{
		memcpy(GuildMBuf + buflen, *i, sizeof(GUILDMINFO));
		buflen += sizeof(GUILDMINFO);

		++MemberCounter;
		if( MemberCounter >= MAX_GUILD_MEMBER_LIST )
			break;
	}

	qsort(GuildMBuf, m_guildMInfo.size(), sizeof(GUILDMINFO), &SortMember); //FIXME: does not consider the MAX_GUILD_MEMBER_LIST limit

	PACKET_IZ_GUILD_MEMBERINFO_TOD PacketMInfo;
	PacketMInfo.PacketType = HEADER_IZ_GUILD_MEMBERINFO_TOD;
	PacketMInfo.PacketLength = sizeof(PacketMInfo) + buflen;
	PacketMInfo.GDID = m_GDID;
//	PacketMPos.AID = 0;
	this->CIGuildInfo::Send(ZSID, sizeof(PacketMInfo), (char*)&PacketMInfo);
	this->CIGuildInfo::Send(ZSID, buflen, GuildMBuf);

	buflen = 0;
	for( std::vector<GUILDALLYINFO*>::iterator i = m_guildAllyInfo.begin(); i != m_guildAllyInfo.end(); ++i )
	{
		memcpy(Buf + buflen, *i, sizeof(GUILDALLYINFO));
		buflen += sizeof(GUILDALLYINFO);
	}
	PACKET_IZ_GUILD_ALLYINFO_TOD PacketAllyInfo;
	PacketAllyInfo.PacketType = HEADER_IZ_GUILD_ALLYINFO_TOD;
	PacketAllyInfo.PacketLength = sizeof(PacketAllyInfo) + buflen;
	PacketAllyInfo.GDID = m_GDID;
//	PacketMPos.AID = 0;
	this->CIGuildInfo::Send(ZSID, sizeof(PacketAllyInfo), (char*)&PacketAllyInfo);
	this->CIGuildInfo::Send(ZSID, buflen, Buf);

	buflen = 0;
	for( std::vector<GUILDBANISHINFO*>::iterator i = m_guildBanishInfo.begin(); i != m_guildBanishInfo.end(); ++i )
	{
		memcpy(Buf + buflen, *i, sizeof(GUILDBANISHINFO));
		buflen += sizeof(GUILDBANISHINFO);
	}
	PACKET_IZ_GUILD_BANISHINFO_TOD PacketBanishInfo;
	PacketBanishInfo.PacketType = HEADER_IZ_GUILD_BANISHINFO_TOD;
	PacketBanishInfo.PacketLength = sizeof(PacketBanishInfo) + buflen;
	PacketBanishInfo.GDID = m_GDID;
//	PacketMPos.AID = 0;
	this->CIGuildInfo::Send(ZSID, sizeof(PacketBanishInfo), (char*)&PacketBanishInfo);
	this->CIGuildInfo::Send(ZSID, buflen, Buf);

	buflen = 0;
	for( std::vector<GUILDMPOSITION*>::iterator i = m_guildMPosition.begin(); i != m_guildMPosition.end(); ++i )
	{
		memcpy(Buf + buflen, *i, sizeof(GUILDMPOSITION));
		buflen += sizeof(GUILDMPOSITION);
	}
	PACKET_IZ_GUILD_MPOSITION_TOD PacketMPos;
	PacketMPos.PacketType = HEADER_IZ_GUILD_MPOSITION_TOD;
	PacketMPos.PacketLength = sizeof(PacketMPos) + buflen;
	PacketMPos.GDID = m_GDID;
//	PacketMPos.AID = 0;
	this->CIGuildInfo::Send(ZSID, sizeof(PacketMPos), (char*)&PacketMPos);
	this->CIGuildInfo::Send(ZSID, buflen, Buf);

	this->CIGuildInfo::NotifyGuildSkillInfo(ZSID);
}


void CIGuildInfo::UpdateMapName(const unsigned long AID, const char* mapName)
{
	PACKET_IZ_GUILD_MAP_CHANGE GuildMapChange;
	GuildMapChange.PacketType = HEADER_IZ_GUILD_MAP_CHANGE;
	GuildMapChange.GDID = m_GDID;
	GuildMapChange.AID = AID;
	memcpy(GuildMapChange.mapName, mapName, sizeof(GuildMapChange.mapName));
	this->CIGuildInfo::Send(-1, sizeof(GuildMapChange), (char*)&GuildMapChange);
}


BOOL CIGuildInfo::ChangeMemberInfo(unsigned long ZSID, unsigned long AID, unsigned long GID, int status)
{
	USER_STRING_MAP_DATA* User = g_userMgr.CUserMgr::SearchUser(AID, GID);
	if( User == NULL )
		return FALSE;

	PACKET_IZ_UPDATE_CHARSTAT ZIPacket;
	ZIPacket.PacketType = HEADER_IZ_UPDATE_CHARSTAT;
	ZIPacket.GID = GID;
	ZIPacket.GDID = m_GDID;
	ZIPacket.AID = AID;
	ZIPacket.sex = LOWORD(User->sex);
	ZIPacket.head = User->head;
	ZIPacket.headPalette = User->headpalette;
	ZIPacket.job = User->job;
	ZIPacket.Level = User->level;
	ZIPacket.status = status;
	this->CGuild::UpdateMemberStatus(status, GID, User->job, User->level, LOWORD(User->sex), User->head, User->headpalette);

	if( status == 1 )
	{
		this->CIGuildInfo::AddZoneServer(ZSID);
		this->CIGuildInfo::Send(-1, sizeof(ZIPacket), (char*)&ZIPacket);
	}
	else
	{
		this->CIGuildInfo::Send(-1, sizeof(ZIPacket), (char*)&ZIPacket);
		this->CIGuildInfo::RemoveZoneServer(ZSID);
	}

	return TRUE;
}


void CIGuildInfo::AddZoneServer(unsigned long ZSID)
{
	if( m_bAllNotifyInfo == 1 )
		return;

	if( this->CIGuildInfo::FindZoneServer(ZSID) == TRUE )
	{
		for( int i = 0; i < countof(m_ZServerInfo); ++i )
		{
			if( ZSID == m_ZServerInfo[i].ServerID )
			{
				++m_ZServerInfo[i].MemberNumber;
				return;
			}
		}
	}

	for( int i = 0; i < countof(m_ZServerInfo); ++i )
	{
		if( m_ZServerInfo[i].ServerID == 0 )
		{
			m_ZServerInfo[i].ServerID = ZSID;
			m_ZServerInfo[i].MemberNumber = 1;
			m_ZServerList.push_back(ZSID);

			this->CIGuildInfo::NotifyAllInfo(ZSID);

			break;
		}
	}
}


void CIGuildInfo::RemoveZoneServer(unsigned long ZSID)
{
	if( m_bAllNotifyInfo == TRUE )
		return;

	for( int i = 0; i < countof(m_ZServerInfo); ++i )
	{
		if( ZSID == m_ZServerInfo[i].ServerID )
		{
			--m_ZServerInfo[i].MemberNumber;
			if( m_ZServerInfo[i].MemberNumber == 0 )
			{
				m_ZServerInfo[i].ServerID = 0;

				PACKET_IZ_FREE_GUILD IZPacket;
				IZPacket.PacketType = HEADER_IZ_FREE_GUILD;
				IZPacket.GDID = m_GDID;
				CZsvrMgr::GetObj()->CZServerMgr::SendMsgToZServer(ZSID, sizeof(IZPacket), (char*)&IZPacket);

				m_ZServerList.remove(ZSID);
			}

			break;
		}
	}
}


void CIGuildInfo::ResetZoneServer(unsigned long ZSID)
{
	if( this->CIGuildInfo::FindZoneServer(ZSID) )
	{
		for( int i = 0; i < countof(m_ZServerInfo); ++i )
		{
			if( ZSID == m_ZServerInfo[i].ServerID )
			{
				m_ZServerInfo[i].ServerID = 0;
				m_ZServerInfo[i].MemberNumber = 0;
				m_ZServerList.remove(ZSID);

				break;
			}
		}
	}
}


BOOL CIGuildInfo::FindZoneServer(unsigned long ZSID)
{
	if( m_bAllNotifyInfo == TRUE )
		return TRUE;

	for( std::list<int>::iterator iter = m_ZServerList.begin(); iter != m_ZServerList.end(); ++iter )
		if( *iter == ZSID )
			return TRUE; // found.

	return FALSE; // not found.
}


void CIGuildInfo::OutPutGuildInfo(BOOL bLevelUp)
{
}


void CIGuildInfo::SetAllNotifyInfo(BOOL bAllNotifyInfo)
{
	m_bAllNotifyInfo = bAllNotifyInfo;
	this->CIGuildInfo::NotifyAllInfo(-1);
}


BOOL CIGuildInfo::ReloadGuildInfo()
{
	GUILDINFO info;
	if( !g_IGuildDB.CIGuildInfoDB::GetGuildInfoDB(m_GDID, info) )
		return FALSE;

	if( info.Level > m_level || info.Exp > m_exp )
		this->CGuild::SetGuildInfo(&info);

	this->CIGuildInfo::NotifyAllInfo(-1);

	return TRUE;
}


BOOL CIGuildInfo::ReloadAllyGuildInfo()
{
	int buflen = 0;
	char Buf[3072] = {};

	if( !g_IGuildDB.CIGuildInfoDB::GetGuildAllyInfoDB(m_GDID, buflen, Buf) )
		return FALSE;

	GUILDALLYINFO* Data = reinterpret_cast<GUILDALLYINFO*>(Buf);
	int count = buflen / sizeof(GUILDALLYINFO);

	this->CGuild::DeleteAllyInfo();

	for( int i = 0; i < count; ++i )
	{
		GUILDALLYINFO* Info = m_GuildAllyInfoMPool.CMemoryMgr2<GUILDALLYINFO>::Alloc();
		if( Info == NULL )
			continue;

		memcpy(Info, &Data[i], sizeof(GUILDALLYINFO));
		this->CGuild::AddGuildAllyInfo(Info);

		if( i + 1 >= 6 )
			return FALSE;
	}

	this->CIGuildInfo::NotifyAllInfo(-1);

	return TRUE;
}


void CIGuildInfo::OnAddExp(char* buf)
{
	PACKET_ZI_ADD_EXP& ZIPacket = *reinterpret_cast<PACKET_ZI_ADD_EXP*>(buf);

	if( ZIPacket.Exp < 0 )
		return;

	int Level = m_level;
	if( Level >= 50 )
		return;

	int currentExp = this->CGuild::AddGuildExp(ZIPacket.GID, ZIPacket.Exp);
	int nextExp = g_expParameter.CExpParameter::GetGuildNextExp(Level);

	if( currentExp < nextExp )
	{
		PACKET_IZ_ADD_EXP packet = {};
		packet.PacketType = HEADER_IZ_ADD_EXP;
		packet.GDID = ZIPacket.GDID;
		packet.GID = ZIPacket.GID;
		packet.Exp = ZIPacket.Exp;
		packet.MaxUserNum = m_maxUserNum;
		this->CIGuildInfo::Send(-1, sizeof(packet), (char*)&packet);
	}
	else
	{
		++m_skillPoint;
		m_level = Level + 1;
		m_exp = currentExp - nextExp;
		g_IGuildDB.CIGuildInfoDB::UpdateGuildInfoDB(*this);
		this->CIGuildInfo::NotifyAllInfo(-1);
	}
}


void CIGuildInfo::SetUseInfo(BOOL InfoUse)
{
	m_InfoUse = InfoUse;
}


BOOL CIGuildInfo::GetUseInfo()
{
	return m_InfoUse;
}
