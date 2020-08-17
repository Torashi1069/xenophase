#include "CharacterMgr.h"
#include "MapResMgr.h"
#include "ZGuildMgr.h"
#include "ZoneProcess.h"
#include "Common/Packet.h"


CZGuildMgr::CZGuildMgr()
: CGuildMgr(), m_zGuildMPool(), m_set(), m_MaxGuildCounter(0)
{
}


CZGuildMgr::~CZGuildMgr()
{
	m_guildInfo.clear(); //FIXME: pointless + leaks memory 
}


void CZGuildMgr::Init()
{
	m_zGuildMPool.CMemoryMgr<CZGuildInfo>::Init(15000);
}


void CZGuildMgr::Init(int Max_Guild)
{
	if( Max_Guild < 15000 )
		Max_Guild = 15000;

	m_zGuildMPool.CMemoryMgr<CZGuildInfo>::Init(Max_Guild);
	m_MaxGuildCounter = Max_Guild;
}


CGuild* CZGuildMgr::AllocGuild()
{
	return m_zGuildMPool.CMemoryMgr<CZGuildInfo>::Alloc();
}


void CZGuildMgr::FreeGuild(CGuild* guild, BOOL disorganize)
{
	unsigned long GDID = guild->GetGDID();

	std::set<unsigned long>::const_iterator it = m_set.find(GDID);
	if( it != m_set.end() )
	{
		if( !disorganize )
			return;

		m_set.erase(it);

		g_mapResMgr.CMapResMgr::OnDisoranizeGuild(GDID);
	}

	guild->CGuild::ClearAll();
	m_zGuildMPool.CMemoryMgr<CZGuildInfo>::Free(static_cast<CZGuildInfo*>(guild));

	std::map<unsigned long,CGuild*>::const_iterator it2 = m_guildInfo.find(GDID);
	if( it2 != m_guildInfo.end() )
		m_guildInfo.erase(it2);
}


namespace GuildStuff
{


std::string GetMyCurrentDirectory()
{
	char Folder[260] = {};
	GetCurrentDirectoryA(sizeof(Folder), Folder);

	return Folder;
}


std::list<std::string> GetFileNameList(const char* in_path, const char* in_wildcard)
{
	std::string pathWildcard = std::string() + in_path + "\\" + in_wildcard;
	std::list<std::string> FileNameList;

	WIN32_FIND_DATAA wfd = {};
	HANDLE hFile = FindFirstFileA(pathWildcard.c_str(), &wfd);
	if( hFile == INVALID_HANDLE_VALUE )
		return FileNameList;

	static std::string cur0 = ".";
	static std::string cur1 = "..";

	do
	{
		if( cur0 != wfd.cFileName && cur1 != wfd.cFileName )
			FileNameList.push_back(wfd.cFileName);
	}
	while( FindNextFileA(hFile, &wfd) );

	FindClose(hFile);

	return FileNameList;
}


void OnIZ_GET_GUILD_EMBLEM_IMG(const PACKET_IZ_GET_GUILD_EMBLEM_IMG* in_pPacket)
{
	const int in_EmblemBytes = in_pPacket->PacketLength - sizeof(PACKET_IZ_GET_GUILD_EMBLEM_IMG);
	if( in_EmblemBytes > 3072 )
		return;

	static std::string CurrentFolder = GuildStuff::GetMyCurrentDirectory() + std::string("\\Emblem");
	if( access(CurrentFolder.c_str(), 0) != 0 && mkdir(CurrentFolder.c_str()) != 0 )
		return;

	char FileName[MAX_PATH];
	_snprintf(FileName, countof(FileName), "%d_*.emb", in_pPacket->GDID);
	std::list<std::string> emblemList = GuildStuff::GetFileNameList(CurrentFolder.c_str(), FileName);

	_snprintf(FileName, countof(FileName), "%s\\%d_%d.emb", CurrentFolder.c_str(), in_pPacket->GDID, in_pPacket->emblemVersion);
	FILE* fp = fopen(FileName, "wb");
	if( fp == NULL )
		return;

	fwrite(in_pPacket->Emblem, in_EmblemBytes, sizeof(char), fp);
	fclose(fp);

	for( std::list<std::string>::const_iterator it = emblemList.begin(); it != emblemList.end(); ++it )
	{
		_snprintf(FileName, countof(FileName), "%s\\%s", CurrentFolder.c_str(), (*it).c_str());
		_chmod(FileName, _S_IWRITE);
		_unlink(FileName);
	}

	CZGuildInfo* guild = (CZGuildInfo*)g_ZGuildMgr.CGuildMgr::SearchGuild(in_pPacket->GDID);
	if( guild == NULL )
		return;

	guild->CZGuildInfo::SetEmblem(in_pPacket->Emblem, in_EmblemBytes, in_pPacket->emblemVersion); /// @custom

	PACKET_ZC_GUILD_EMBLEM_IMG ZCPacket;
	ZCPacket.PacketType = HEADER_ZC_GUILD_EMBLEM_IMG;
	ZCPacket.PacketLength = sizeof(PACKET_ZC_GUILD_EMBLEM_IMG) + in_EmblemBytes;
	ZCPacket.emblemVersion = in_pPacket->emblemVersion;
	ZCPacket.GDID = in_pPacket->GDID;
	CCharacterMgr::GetObj()->CCharacterMgr::SendMsg(NULL, in_pPacket->AID, CM_SEND_PACKET, sizeof(ZCPacket), (int)&ZCPacket, 0, 0);
	CCharacterMgr::GetObj()->CCharacterMgr::SendMsg(NULL, in_pPacket->AID, CM_SEND_PACKET, in_EmblemBytes, (int)&in_pPacket->Emblem, 0, 0);

	g_mapResMgr.CMapResMgr::OnChangeEmblem(in_pPacket->GDID, in_pPacket->emblemVersion);
}


}; // namespace


void CZGuildMgr::SendPacket(const unsigned long in_GDID, const short in_PacketType, const int in_Len, const char* in_pBuffer)
{
	switch( in_PacketType )
	{
	case HEADER_IZ_GET_GUILD_EMBLEM_IMG:
	{
		const PACKET_IZ_GET_GUILD_EMBLEM_IMG* packet = reinterpret_cast<const PACKET_IZ_GET_GUILD_EMBLEM_IMG*>(in_pBuffer);
		GuildStuff::OnIZ_GET_GUILD_EMBLEM_IMG(packet);
	}
	break;
	case HEADER_IZ_GET_GUILD_EMBLEM_IMG2:
	{
	}
	break;
	default:
	{
		CZGuildInfo* guild = (CZGuildInfo*)this->CGuildMgr::SearchGuild(in_GDID);
		if( guild != NULL )
			guild->m_packetDispatcher.CZGuildInfoPacketDispatcher::DispatchPacket(in_GDID, in_PacketType, in_Len, const_cast<char*>(in_pBuffer));
	}
	break;
	};

}


void CZGuildMgr::MakeGuild(unsigned long GDID, GUILDINFO* Info)
{
	CZGuildInfo* guild = (CZGuildInfo*)this->CGuildMgr::SearchGuild(GDID);
	if( guild != NULL )
	{
		guild->CGuild::ClearAll();
		guild->Init();
		guild->CGuild::SetGDID(GDID);
		guild->CGuild::SetGuildInfo(Info);
		guild->CZGuildInfo::LoadEmblem();
	}
	else
	{
		CZGuildInfo* guild = (CZGuildInfo*)m_zGuildMPool.CMemoryMgr<CZGuildInfo>::Alloc();
		if( guild != NULL )
		{
			guild->Init();
			guild->CGuild::SetGDID(GDID);
			guild->CGuild::SetGuildInfo(Info);
			guild->CZGuildInfo::LoadEmblem();
			this->CGuildMgr::AddGuild(guild);
		}
	}
}


void CZGuildMgr::AddGuildExp(unsigned long GDID, unsigned long GID, int Exp)
{
	if( Exp == 0 )
		return;

	PACKET_ZI_ADD_EXP ZIPacket;
	ZIPacket.PacketType = HEADER_ZI_ADD_EXP;
	ZIPacket.GDID = GDID;
	ZIPacket.GID = GID;
	ZIPacket.Exp = Exp;
	CCharacterMgr::GetObj()->CCharacterMgr::SendToIServer(sizeof(ZIPacket), (char*)&ZIPacket);
}


void CZGuildMgr::AddAgitGuild(unsigned long GDID)
{
	m_set.insert(GDID);
}


void CZGuildMgr::OnChangeAgitGuild(const char* mapName, unsigned long a, unsigned long b)
{
	if( a != 0 )
	{
		std::set<unsigned long>::const_iterator it = m_set.find(a);
		if( it != m_set.end() )
			m_set.erase(it);
	}

	if( b != 0 )
	{
		this->CZGuildMgr::AddAgitGuild(b);
	}

	PACKET_ZI_GUILD_CHANGEOWNER_AGIT ZIPacket;
	ZIPacket.PacketType = HEADER_ZI_GUILD_CHANGEOWNER_AGIT;
	ZIPacket.oldGDID = a;
	ZIPacket.newGDID = b;
	memcpy_s(ZIPacket.mapName, sizeof(ZIPacket.mapName), mapName, 16);
	CCharacterMgr::GetObj()->CCharacterMgr::SendToIServer(sizeof(ZIPacket), (char*)&ZIPacket);
}


int CZGuildMgr::GetGuildSkillLevel(unsigned long GDID, unsigned short SKID)
{
	if( GDID == 0 )
		return 0;
	
	CZGuildInfo* guild = (CZGuildInfo*)this->CGuildMgr::SearchGuild(GDID);
	if( guild == NULL )
		return 0;
	
	return guild->CZGuildInfo::GetSkillLevel(SKID);
}


unsigned long CZGuildMgr::GetFreeSize()
{
	return m_zGuildMPool.CMemoryMgr<CZGuildInfo>::GetFreeSize();
}


unsigned long CZGuildMgr::GetOffset()
{
	return m_MaxGuildCounter - m_guildInfo.size() - m_zGuildMPool.CMemoryMgr<CZGuildInfo>::GetFreeSize();
}


BOOL CZGuildMgr::isAgitGuild(unsigned long GDID)
{
	std::set<unsigned long>::const_iterator it = m_set.find(GDID);
	return ( it != m_set.end() );
}


BOOL CZGuildMgr::JoinInsertGID(unsigned long GDID, unsigned long GID)
{
	CZGuildInfo* guild = (CZGuildInfo*)this->CGuildMgr::SearchGuild(GDID);
	if( guild == NULL )
		return FALSE;

	guild->CZGuildInfo::SetJoinGID(GID);
	return TRUE;
}


BOOL CZGuildMgr::JoinChkeckGID(unsigned long GDID, unsigned long GID)
{
	CZGuildInfo* guild = (CZGuildInfo*)this->CGuildMgr::SearchGuild(GDID);
	if( guild == NULL )
		return FALSE;

	return ( GID == guild->CZGuildInfo::GetJoinGID() );
}
