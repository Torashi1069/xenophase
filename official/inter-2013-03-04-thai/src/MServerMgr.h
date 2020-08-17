#pragma once
#include "MServer.h"
#include "NetLib/MemoryMgr.h"


class CMClientMgr
{
public:
	CMClientMgr();
	virtual ~CMClientMgr();

public:
	void Init(int count);
	void SendMsgToMServer(int zServerID, short len, const char* buf);
	void BroadCast(short len, const char* buf);
	CMClient* AllocServer();
	void FreeServer(CMClient* server);
	int AddServer(CMClient* mServer);
	BOOL IsConnectedServer(int SID);

protected:
	/* this+ 0 */ //const CMClientMgr::`vftable';
	/* this+ 4 */ int m_serverIDcounter;
	/* this+ 8 */ std::map<int,CMClient*> m_mServerMap;
	/* this+40 */ CMemoryMgr<CMClient> m_mserverMemoryPool;
	/* this+80 */ RTL_CRITICAL_SECTION m_mserverMgr_cs;
};
