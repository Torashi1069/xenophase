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
	for( std::map<unsigned long,CGuild*>::iterator iter = m_guildInfo.begin(); iter != m_guildInfo.end(); )
	{
		CGuild* guild = iter->second;
		iter = m_guildInfo.erase(iter);
		delete guild;
	}
}


BOOL CGuildMgr::AddGuild(CGuild* guild)
{
	if( guild == NULL )
		return FALSE;

	unsigned long GDID = guild->CGuild::GetGDID();
	std::map<unsigned long,CGuild*>::iterator iter = m_guildInfo.find(GDID);
	if( iter != m_guildInfo.end() )
		return FALSE; // already present.

	m_guildInfo[GDID] = guild;
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
