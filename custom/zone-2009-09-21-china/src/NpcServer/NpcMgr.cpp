#include "ZoneProcess.h"
#include "NpcServer/NpcObj.h"
#include "NpcServer/NpcMgr.h"
#include "shared/shared.h"
#include "StdAfx.h" // stlwipe_second<>


CNpcMgr::CNpcMgr()
{
	this->CNpcMgr::Clear();
}


CNpcMgr::~CNpcMgr()
{
}


void CNpcMgr::Clear()
{
	m_alloc = NPC_MINIMUM_AID;
	stlwipe_second<mystd::map<int,CNpc*>>(&m_map);
}


CNpc* CNpcMgr::Add(int npcId)
{
	CNpc* npc = new CNpc();
	if( npc == NULL )
		return NULL;

	if( !m_map.insert(mystd::pair<const int,CNpc*>(npcId, npc)).second )
	{
		char temp[256];
		sprintf(temp, "NpcMgr.Add(%d) dupicated npcId %s\n", npcId, m_map[npcId]->CNpc::GetName());
		Trace(temp);
		MessageBoxA(NULL, temp, "std.sc error", MB_OK);

		delete npc;
		return NULL;
	}

	Trace("NpcMgr.Add(%d)\n", npcId);
	return npc;
}


CNpc* CNpcMgr::Get(int npcId)
{
	mystd::map<int,CNpc*>::iterator mapi = m_map.find(npcId);
	if( mapi == m_map.end() )
		return NULL;

	return mapi->second;
}


CNpc* CNpcMgr::GetFromName(const char* name)
{
	mystd::map<int,CNpc*>::iterator mapi;
	for( mapi = m_map.begin(); mapi != m_map.end(); ++mapi )
		if( strcmp(mapi->second->CNpc::GetName(), name) == 0 )
			break;

	if( mapi == m_map.end() )
		return NULL;

	return mapi->second;
}


int CNpcMgr::GetNewID()
{
	++m_alloc;
	return m_alloc;
}


void CNpcMgr::Delete(int npcID)
{
	mystd::map<int,CNpc*>::iterator mapi = m_map.find(npcID);
	if( mapi != m_map.end() )
		delete mapi->second;

	m_map.erase(npcID);
}
