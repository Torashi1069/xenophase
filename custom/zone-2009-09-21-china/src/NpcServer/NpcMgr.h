#pragma once
#include "NpcServer/NpcObj.h"


class CNpcMgr
{
public:
	CNpcMgr();
	~CNpcMgr();

public:
	void Clear();
	int GetNewID();
	CNpc* Add(int npcId);
	CNpc* Get(int npcId);
	CNpc* GetFromName(const char* name);
	void Delete(int npcID);

private:
	/* this+ 0 */ mystd::map<int,CNpc*> m_map;
	/* this+12 */ int m_alloc;
};
