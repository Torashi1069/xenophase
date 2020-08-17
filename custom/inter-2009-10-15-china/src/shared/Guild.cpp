#include "Guild.h"


CGuild::CGuild(void) // line 5
{
	m_GuildMInfoMPool.CMemoryMgr<GUILDMINFO>::Init(56);
	m_GuildAllyInfoMPool.CMemoryMgr<GUILDALLYINFO>::Init(6);
	m_GuildBanishInfoMPool.CMemoryMgr<GUILDBANISHINFO>::Init(2);
	m_GuildMPositionMPool.CMemoryMgr<GUILDMPOSITION>::Init(20);
}


CGuild::~CGuild(void) // line 15
{
}


hook_method<int (CGuild::*)(unsigned long PosID)> CGuild::_GetPosJoinRight(SERVER, "CGuild::GetPosJoinRight");
int CGuild::GetPosJoinRight(unsigned long PosID)
{
	return (this->*_GetPosJoinRight)(PosID);

	//TODO
}


/// @patch change guild maxUserNum to 28 players (w/ GD_EXTENSION)
hook_method<void (CGuild::*)(void)> CGuild::_Init(SERVER, "CGuild::Init");
HOOKED void CGuild::Init(void) // line 43
{
//	return (this->*_Init)();

	m_GDID = 0;
	m_level = 1;
	m_guildName[0] = 0;
	m_guildMasterName[0] = 0;
	m_maxUserNum = 8;
	m_userNum = 0;
	m_honor = 0;
	m_virtue = 0;
	m_type = 0;
	m_class = 0;
	m_money = 0;
	m_arenaWin = 0;
	m_arenaLose = 0;
	m_arenaDrawn = 0;
	m_manageLand[0] = '\0';
	m_exp = 0;
	m_emblemVersion = 0;
	m_point = 0;
	m_desc[0] = '\0';
	m_isEmblemLoad = 0;
	m_emblemSize = 0;
	//m_guildNotice.GDID = 0; // uninitialized
	m_guildNotice.Subject[0] = '\0';
	m_guildNotice.Notice[0] = '\0';
	m_guildEmblem[0] = '\0';
	m_skillDataLength = 0;
	m_skillPoint = 0;
}


hook_method<void (CGuild::*)(int Num)> CGuild::_SetMaxUserNum(SERVER, "CGuild::SetMaxUserNum");
void CGuild::SetMaxUserNum(int Num)
{
	return (this->*_SetMaxUserNum)(Num);

	m_maxUserNum = Num;
}


hook_method<int (CGuild::*)(unsigned long GID)> CGuild::_GetGuildPosID(SERVER, "CGuild::GetGuildPosID");
int CGuild::GetGuildPosID(unsigned long GID)
{
	return (this->*_GetGuildPosID)(GID);

	//TODO
}


hook_method<void (CGuild::*)(GUILDMINFO* Info)> CGuild::_AddGuildMInfo(SERVER, "CGuild::AddGuildMInfo");
void CGuild::AddGuildMInfo(GUILDMINFO* Info)
{
	return (this->*_AddGuildMInfo)(Info);

	//TODO
}


hook_method<int (CGuild::*)(void)> CGuild::_GetGuildMSize(SERVER, "CGuild::GetGuildMSize");
int CGuild::GetGuildMSize(void)
{
	return (this->*_GetGuildMSize)();

	return m_guildMInfo.size();
}


hook_method<GUILDMINFO* (CGuild::*)(void)> CGuild::_AllocGuildMInfo(SERVER, "CGuild::AllocGuildMInfo");
GUILDMINFO* CGuild::AllocGuildMInfo(void)
{
	return (this->*_AllocGuildMInfo)();

	//TODO
}


hook_method<GUILDALLYINFO* (CGuild::*)(void)> CGuild::_AllocGuildAllyInfo(SERVER, "CGuild::AllocGuildAllyInfo");
GUILDALLYINFO* CGuild::AllocGuildAllyInfo(void)
{
	return (this->*_AllocGuildAllyInfo)();

	//TODO
}


hook_method<GUILDBANISHINFO* (CGuild::*)(void)> CGuild::_AllocGuildBanishInfo(SERVER, "CGuild::AllocGuildBanishInfo");
GUILDBANISHINFO* CGuild::AllocGuildBanishInfo(void)
{
	return (this->*_AllocGuildBanishInfo)();

	//TODO
}


hook_method<GUILDMPOSITION* (CGuild::*)(void)> CGuild::_AllocGuildMPosition(SERVER, "CGuild::AllocGuildMPosition");
GUILDMPOSITION* CGuild::AllocGuildMPosition(void)
{
	return (this->*_AllocGuildMPosition)();

	//TODO
}


hook_method<void (CGuild::*)(GUILDMINFO* Guild, char* Name, char* Account, unsigned long AID, unsigned long GDID, unsigned long GID, int Position, int Stat, int Level, int Class)> CGuild::_InitGuildMInfo(SERVER, "?InitGuildMInfo@CGuild@@QAEXPAUGUILDMINFO@@PAD1KKKHHHH@Z");
void CGuild::InitGuildMInfo(GUILDMINFO* Guild, char* Name, char* Account, unsigned long AID, unsigned long GDID, unsigned long GID, int Position, int Stat, int Level, int Class)
{
	return (this->*_InitGuildMInfo)(Guild, Name, Account, AID, GDID, GID, Position, Stat, Level, Class);

	//TODO
}


hook_method<void (CGuild::*)(GUILDMINFO* Guild, char* Name, char* Account, unsigned long AID, unsigned long GDID, unsigned long GID, int Position, int Stat, int Level, int Job, int head, int headpal, int sex)> CGuild::_InitGuildMInfo2(SERVER, "?InitGuildMInfo@CGuild@@QAEXPAUGUILDMINFO@@PAD1KKKHHHHHHH@Z");
void CGuild::InitGuildMInfo(GUILDMINFO* Guild, char* Name, char* Account, unsigned long AID, unsigned long GDID, unsigned long GID, int Position, int Stat, int Level, int Job, int head, int headpal, int sex)
{
	return (this->*_InitGuildMInfo2)(Guild, Name, Account, AID, GDID, GID, Position, Stat, Level, Job, head, headpal, sex);

	//TODO
}


hook_method<int (CGuild::*)(void)> CGuild::_GetMaxUserNum(SERVER, "CGuild::GetMaxUserNum");
int CGuild::GetMaxUserNum(void)
{
	return (this->*_GetMaxUserNum)();

	return m_maxUserNum;
}
