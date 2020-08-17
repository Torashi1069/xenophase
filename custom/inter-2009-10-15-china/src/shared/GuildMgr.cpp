#include "GuildMgr.h"


CGuildMgr::CGuildMgr(void)
{
}


CGuildMgr::~CGuildMgr(void)
{
	this->CGuildMgr::ClearGuildInfo();
}


hook_method<CGuild* (CGuildMgr::*)(unsigned long GDID)> CGuildMgr::_SearchGuild(SERVER, "CGuildMgr::SearchGuild");
CGuild* CGuildMgr::SearchGuild(unsigned long GDID)
{
	return (this->*_SearchGuild)(GDID);

	//TODO
}


hook_method<void (CGuildMgr::*)(void)> CGuildMgr::_Init(SERVER, "CGuildMgr::Init");
void CGuildMgr::Init(void)
{
	return (this->*_Init)();

	//TODO
}


hook_method<void (CGuildMgr::*)(void)> CGuildMgr::_ClearGuildInfo(SERVER, "CGuildMgr::ClearGuildInfo");
void CGuildMgr::ClearGuildInfo(void)
{
	return (this->*_ClearGuildInfo)();

	//TODO
}


hook_method<unsigned long (CGuildMgr::*)(void)> CGuildMgr::_GetGuildSize(SERVER, "CGuildMgr::GetGuildSize");
unsigned long CGuildMgr::GetGuildSize(void)
{
	return (this->*_GetGuildSize)();

	return m_guildInfo.size();
}
