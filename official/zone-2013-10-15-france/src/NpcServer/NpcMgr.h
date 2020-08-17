#pragma once
#include "NpcServer/NpcObj.h"


class CNpcMgr
{
public:
	void Clear();
	CNpc* Add(int npcId);
	CNpc* Get(int npcId);
	CNpc* GetFromName(const char* name);
	void Delete(int npcID);

public:
	CNpcMgr();
	virtual ~CNpcMgr();

private:
	/* this+0 */ //const CNpcMgr::`vftable';
	/* this+4 */ std::map<int,CNpc*> m_map;
};
