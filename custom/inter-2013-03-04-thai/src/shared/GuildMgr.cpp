#include "shared/GuildMgr.h"


CGuildMgr::CGuildMgr()
{
}


CGuildMgr::~CGuildMgr()
{
	this->CGuildMgr::ClearGuildInfo();
}


void CGuildMgr::Init()
{
}


void CGuildMgr::ClearGuildInfo()
{
	for( std::map<unsigned long,CGuild*>::iterator iter = m_guildInfo.begin(); iter != m_guildInfo.end(); iter = m_guildInfo.erase(iter) )
		delete iter->second;
}


BOOL CGuildMgr::AddGuild(CGuild* guild)
{
	if( guild == NULL )
		return FALSE;

	std::map<unsigned long,CGuild*>::iterator iter = m_guildInfo.find(guild->CGuild::GetGDID());
	if( iter != m_guildInfo.end() )
		return FALSE; // already present.

	m_guildInfo[guild->CGuild::GetGDID()] = guild;
	return TRUE;
}


CGuild* CGuildMgr::SearchGuild(unsigned long GDID)
{
	std::map<unsigned long,CGuild*>::iterator iter = m_guildInfo.find(GDID);
	if( iter == m_guildInfo.end() )
		return NULL;

	return iter->second;
}


unsigned long CGuildMgr::GetGuildSize()
{
	return m_guildInfo.size();
}
