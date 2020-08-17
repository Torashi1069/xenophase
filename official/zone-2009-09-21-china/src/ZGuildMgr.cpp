#include "CharacterMgr.h"
#include "MapResMgr.h"
#include "ZGuildMgr.h"
#include "Common/Packet.h"
#include "shared.h" // Trace()


CZGuildMgr::CZGuildMgr(void) // line 10
{
	m_MaxGuildCounter = 0;
}


CZGuildMgr::~CZGuildMgr(void) // line 15
{
}


hook_method<void (CZGuildMgr::*)(unsigned long GDID, unsigned long GID, int Exp)> CZGuildMgr::_AddGuildExp(SERVER, "CZGuildMgr::AddGuildExp");
void CZGuildMgr::AddGuildExp(unsigned long GDID, unsigned long GID, int Exp) // line 118
{
	return (this->*_AddGuildExp)(GDID, GID, Exp);

	if( Exp == 0 )
		return;

	PACKET_ZI_ADD_EXP ZIPacket;
	ZIPacket.PacketType = HEADER_ZI_ADD_EXP;
	ZIPacket.GDID = GDID;
	ZIPacket.GID = GID;
	ZIPacket.Exp = Exp;
	g_characterMgr->CCharacterMgr::SendToIServer(sizeof(ZIPacket), (char*)&ZIPacket);
}


hook_method<void (CZGuildMgr::*)(unsigned long GDID, short PacketType, int Len, char* buf)> CZGuildMgr::_SendPacket(SERVER, "CZGuildMgr::SendPacket");
void CZGuildMgr::SendPacket(unsigned long GDID, short PacketType, int Len, char* buf) // line 78
{
	return (this->*_SendPacket)(GDID, PacketType, Len, buf);

	CZGuildInfo* g = (CZGuildInfo*)this->CGuildMgr::SearchGuild(GDID);
	if( g != NULL )
		g->m_packetDispatcher.CZGuildInfoPacketDispatcher::DispatchPacket(GDID, PacketType, Len, buf);
	else
	if( PacketType == HEADER_IZ_GET_GUILD_EMBLEM_IMG )
		this->CZGuildMgr::GetGuildEmblem(buf, Len);
}


hook_method<void (CZGuildMgr::*)(unsigned long GDID, GUILDINFO* Info)> CZGuildMgr::_MakeGuild(SERVER, "CZGuildMgr::MakeGuild");
void CZGuildMgr::MakeGuild(unsigned long GDID, GUILDINFO* Info) // line 95
{
	return (this->*_MakeGuild)(GDID, Info);

	CZGuildInfo* g;
	
	g = (CZGuildInfo*)this->CGuildMgr::SearchGuild(GDID);
	if( g != NULL )
	{
		g->CGuild::ClearAll();

		g->Init();
		g->CGuild::SetGDID(GDID);
		g->CGuild::SetGuildInfo(Info);
		g->CZGuildInfo::LoadEmblem();
	}
	else
	{
		g = m_zGuildMPool.CMemoryMgr<CZGuildInfo>::Alloc();
		if( g == NULL )
			return;

		g->Init();
		g->CGuild::SetGDID(GDID);
		g->CGuild::SetGuildInfo(Info);
		g->CZGuildInfo::LoadEmblem();

		this->CGuildMgr::AddGuild(g);
	}
}


hook_method<void (CZGuildMgr::*)(void)> CZGuildMgr::_Init(SERVER, "?Init@CZGuildMgr@@UAEXXZ");
void CZGuildMgr::Init(void) // line 21
{
	return (this->*_Init)();

	m_zGuildMPool.CMemoryMgr<CZGuildInfo>::Init(15000);
}


hook_method<void (CZGuildMgr::*)(int Max_Guild)> CZGuildMgr::_Init2(SERVER, "?Init@CZGuildMgr@@QAEXH@Z");
void CZGuildMgr::Init(int Max_Guild) // line 25
{
	return (this->*_Init2)(Max_Guild);

	if( Max_Guild < 15000 )
		Max_Guild = 15000;
	m_zGuildMPool.CMemoryMgr<CZGuildInfo>::Init(Max_Guild);
	m_MaxGuildCounter = Max_Guild;
}


hook_method<CGuild* (CZGuildMgr::*)(void)> CZGuildMgr::_AllocGuild(SERVER, "CZGuildMgr::AllocGuild");
CGuild* CZGuildMgr::AllocGuild(void) // line 45
{
	return (this->*_AllocGuild)();

	return (CGuild*)m_zGuildMPool.CMemoryMgr<CZGuildInfo>::Alloc();
}


hook_method<void (CZGuildMgr::*)(CGuild* guild, int disorganize)> CZGuildMgr::_FreeGuild(SERVER, "CZGuildMgr::FreeGuild");
void CZGuildMgr::FreeGuild(CGuild* guild, int disorganize) // line 49
{
	return (this->*_FreeGuild)(guild, disorganize);

	unsigned long GDID = guild->CGuild::GetGDID();

	mystd::set<unsigned long>::iterator it = m_set.find(GDID);
	if( it != m_set.end() )
	{
		if( !disorganize )
			return;
		m_set.erase(it);
		g_mapResMgr->CMapResMgr::OnDisoranizeGuild(GDID);
	}

	guild->CGuild::ClearAll();
	m_zGuildMPool.Free(static_cast<CZGuildInfo*>(guild));

	mystd::map<unsigned long,CGuild*>::iterator it2 = m_guildInfo.find(GDID);
	if( it2 != m_guildInfo.end() )
		m_guildInfo.erase(it2);

	Trace("현재 길드 정보 %d 개 \n", m_guildInfo.size());
}


hook_method<void (CZGuildMgr::*)(unsigned long GDID)> CZGuildMgr::_AddAgitGuild(SERVER, "CZGuildMgr::AddAgitGuild");
void CZGuildMgr::AddAgitGuild(unsigned long GDID) // line 130
{
	return (this->*_AddAgitGuild)(GDID);

	//TODO
}


hook_method<void (CZGuildMgr::*)(const char* mapName, unsigned long a, unsigned long b)> CZGuildMgr::_OnChangeAgitGuild(SERVER, "CZGuildMgr::OnChangeAgitGuild");
void CZGuildMgr::OnChangeAgitGuild(const char* mapName, unsigned long a, unsigned long b) // line 137
{
	return (this->*_OnChangeAgitGuild)(mapName, a, b);

	//TODO
}


hook_method<int (CZGuildMgr::*)(unsigned long GDID, unsigned short SKID)> CZGuildMgr::_GetGuildSkillLevel(SERVER, "CZGuildMgr::GetGuildSkillLevel");
int CZGuildMgr::GetGuildSkillLevel(unsigned long GDID, unsigned short SKID) // line 161
{
	return (this->*_GetGuildSkillLevel)(GDID, SKID);

	if( GDID == 0 )
		return 0;

	CZGuildInfo* g = (CZGuildInfo*)this->CGuildMgr::SearchGuild(GDID);
	if( g == NULL )
		return 0;

	return g->CZGuildInfo::GetSkillLevel(SKID);
}


//hook_method<unsigned long (CZGuildMgr::*)(void)> CZGuildMgr::_GetFreeSize(SERVER, "CZGuildMgr::GetFreeSize");
unsigned long CZGuildMgr::GetFreeSize(void) // line ???
{
//	return (this->*_GetFreeSize)();

	return m_zGuildMPool.CMemoryMgr<CZGuildInfo>::GetFreeSize();
}


hook_method<unsigned long (CZGuildMgr::*)(void)> CZGuildMgr::_GetOffset(SERVER, "CZGuildMgr::GetOffset");
unsigned long CZGuildMgr::GetOffset(void) // line 170
{
	return (this->*_GetOffset)();

	return m_MaxGuildCounter - m_guildInfo.size() - m_zGuildMPool.CMemoryMgr<CZGuildInfo>::GetFreeSize();
}


hook_method<int (CZGuildMgr::*)(unsigned long GDID, unsigned long GID)> CZGuildMgr::_JoinInsertGID(SERVER, "CZGuildMgr::JoinInsertGID");
int CZGuildMgr::JoinInsertGID(unsigned long GDID, unsigned long GID) // line 258
{
	return (this->*_JoinInsertGID)(GDID, GID);

	CZGuildInfo* g = (CZGuildInfo*)this->CGuildMgr::SearchGuild(GDID);
	if( g == NULL )
		return 0;

	g->m_JoinGID = GID;
	return 1;
}


hook_method<int (CZGuildMgr::*)(unsigned long GDID, unsigned long GID)> CZGuildMgr::_JoinChkeckGID(SERVER, "CZGuildMgr::JoinChkeckGID");
int CZGuildMgr::JoinChkeckGID(unsigned long GDID, unsigned long GID) // line 271
{
	return (this->*_JoinChkeckGID)(GDID, GID);

	CZGuildInfo* g = (CZGuildInfo*)this->CGuildMgr::SearchGuild(GDID);
	return ( g != NULL && GID == g->CZGuildInfo::GetJoinGID() );
}


hook_method<int (CZGuildMgr::*)(unsigned long GDID)> CZGuildMgr::_isAgitGuild(SERVER, "CZGuildMgr::isAgitGuild");
int CZGuildMgr::isAgitGuild(unsigned long GDID) // line 175
{
	return (this->*_isAgitGuild)(GDID);

	return ( m_set.find(GDID) != m_set.end() );
}


hook_method<void (CZGuildMgr::*)(char* buf, unsigned short Len)> CZGuildMgr::_GetGuildEmblem(SERVER, "CZGuildMgr::GetGuildEmblem");
void CZGuildMgr::GetGuildEmblem(char* buf, unsigned short Len) // line 215
{
	return (this->*_GetGuildEmblem)(buf, Len);

	PACKET_IZ_GET_GUILD_EMBLEM_IMG& packet = *(PACKET_IZ_GET_GUILD_EMBLEM_IMG*)buf;
	size_t emblemLen = Len - sizeof(packet);

	char Emblem[3072];
	memset(Emblem, 0, sizeof(Emblem));
	memcpy(Emblem, packet.emblemData, emblemLen);

	char Folder[200];
	memset(Folder, 0, sizeof(Folder));
	GetCurrentDirectoryA(sizeof(Folder), Folder);

	char CurrentFolder[200];
	memset(CurrentFolder, 0, sizeof(CurrentFolder));
	sprintf(CurrentFolder, "%s\\Emblem", Folder);
	if( access(CurrentFolder, 0) != 0 && mkdir(CurrentFolder) != 0 )
		return;

	char emblemtodeletem[256];
	sprintf(emblemtodeletem, "%d_*.emb", packet.GDID);

	mystd::list<mystd::string> emblemList;
	this->CZGuildMgr::GetFileNames(emblemList, CurrentFolder, emblemtodeletem);

	for( mystd::list<mystd::string>::iterator i = emblemList.begin(); i != emblemList.end(); ++i )
	{
		const char* EmblemFile = i->c_str();

		char EmblemPath[256];
		sprintf(EmblemPath, "%s\\%s", CurrentFolder, EmblemFile);
		chmod(EmblemPath, _S_IWRITE);
		unlink(EmblemPath);
	}

	char FileName[200];
	memset(FileName, 0, sizeof(FileName));
	sprintf(FileName, "%s\\%d_%d.emb", CurrentFolder, packet.GDID, packet.emblemVersion);
	FILE* fp = fopen(FileName, "wb");
	if( fp == NULL )
		return;
	fwrite(Emblem, emblemLen, 1, fp);
	fclose(fp);
}


hook_method<void (CZGuildMgr::*)(mystd::list<mystd::string>& fileNameList, const char* path, const char* szFileName_wildcard)> CZGuildMgr::_GetFileNames(SERVER, "CZGuildMgr::GetFileNames");
void CZGuildMgr::GetFileNames(mystd::list<mystd::string>& fileNameList, const char* path, const char* szFileName_wildcard) // line 188
{
	return (this->*_GetFileNames)(fileNameList, path, szFileName_wildcard);

	mystd::string pathWildcard;
	pathWildcard += path;
	pathWildcard += "\\";
	pathWildcard += szFileName_wildcard;

	WIN32_FIND_DATAA wfd;
	memset(&wfd, 0, sizeof(wfd));

	HANDLE hFile = FindFirstFileA(pathWildcard.c_str(), &wfd);
	if( hFile == INVALID_HANDLE_VALUE )
	{
		Trace("INVALID_HANDLE_VALUE");
		FindClose(hFile);
		return;
	}

	mystd::string cur0 = ".";
	mystd::string cur1 = "..";

	do
	{
		if( cur0 != wfd.cFileName && cur1 != wfd.cFileName )
			fileNameList.push_back(wfd.cFileName);
	}
	while( FindNextFileA(hFile, &wfd) );

	FindClose(hFile);
}
