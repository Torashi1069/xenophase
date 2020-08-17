#pragma once
#include "DGNpcBin.h"


class CDGNpcMgr
{
private:
	typedef std::map<std::string,CDGNpcBin*> TMAP;

public:
	CDGNpcMgr();
	~CDGNpcMgr();

private:
	/* static */ static CDGNpcMgr*& m_cpSelf; //TODO
protected:
	/* this+0 */ //const CDGNpcMgr::`vftable';
	/* this+4 */ TMAP m_map;

public:
	void Clear();
	static CDGNpcMgr* GetObj();
	bool AddInstantMap(const char* mapName);
	void DeleteDunGeon(const char* mapName);
	CDGNpcBin* FindDunGeonBin(const char* mapName);
};
