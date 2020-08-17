#include "CharacterMgr.h"
#include "StackDumpLog.h"
#include "ZoneProcess.h"
#include "NpcServer/NpcMgr.h"
#include "shared/NCriticalErrorLog.h"


CNpcMgr::CNpcMgr()
{
}


CNpcMgr::~CNpcMgr()
{
	this->CNpcMgr::Clear();
}


void CNpcMgr::Clear()
{
	for( std::map<int,CNpc*>::iterator it = m_map.begin(); it != m_map.end(); ++it )
		delete it->second;

	m_map.clear();
}


CNpc* CNpcMgr::Add(int npcId)
{
	CNpc* npc = new(std::nothrow) CNpc();
	if( npc == NULL )
		return NULL;

	if( !m_map.insert(std::pair<const int,CNpc*>(npcId, npc)).second )
	{
		if( CCharacterMgr::GetObj()->CCharacterMgr::FastFindCharacter(npcId) )
			NCriticalErrorLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__, "found Char");
		else
			NCriticalErrorLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__, "not found char");

		NCriticalErrorLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__, "NpcMgr.Add(%d) duplicated npcId %s mapname=%s", npcId, m_map[npcId]->CNpc::GetName(), m_map[npcId]->CNpc::GetMapName());

		g_stackdumpLog.CStackDumpLog::WriteFmt(__FILE__, __LINE__, "NpcMgr.Add(%d) duplicated npcId %s", npcId, m_map[npcId]->CNpc::GetName());

		delete npc;
		return NULL;
	}

	return npc;
}


CNpc* CNpcMgr::Get(int npcId)
{
	std::map<int,CNpc*>::iterator it = m_map.find(npcId);
	if( it == m_map.end() )
		return NULL;

	return it->second;
}


CNpc* CNpcMgr::GetFromName(const char* name)
{
	for( std::map<int,CNpc*>::iterator it = m_map.begin(); it != m_map.end(); ++it )
		if( strcmp(it->second->CNpc::GetName(), name) == 0 )
			return it->second; // found.

	return NULL; // not found.
}


void CNpcMgr::Delete(int npcID)
{
	std::map<int,CNpc*>::iterator it = m_map.find(npcID);
	if( it == m_map.end() )
		return;

	CNpc* npc = it->second;
	m_map.erase(it);
	delete npc;
}
