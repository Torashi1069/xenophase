#pragma once
#include "MServer.h"
#include "NetLib/MemoryMgr.h"
#include "std/map"


class CMClientMgr
{
	/* this+ 0 */ public: //const CMClientMgr::`vftable';
	/* this+ 4 */ private: int m_serverIDcounter;
	/* this+ 8 */ private: mystd::map<int,CMClient*> m_mServerMap;
	/* this+20 */ private: CMemoryMgr<CMClient> m_mserverMemoryPool;
	/* this+68 */ private: RTL_CRITICAL_SECTION m_mserverMgr_cs;

	public: CMClientMgr::CMClientMgr(void);
	public: virtual CMClientMgr::~CMClientMgr(void);
	public: void CMClientMgr::Init(int count);
	public: void CMClientMgr::ProcessAllCharacter(void);
	//public: void CMClientMgr::SendMsgToMServer(int, short, const char *);
	//public: void CMClientMgr::BroadCast(short, const char *);
	public: CMClient* CMClientMgr::AllocServer(void);
	public: void CMClientMgr::FreeServer(CMClient* mServer);
	public: int CMClientMgr::AddServer(CMClient* mServer);
	public: void CMClientMgr::DeleteServer(int SID);
	//public: int CMClientMgr::IsConnectedServer(int);

private:
	static hook_method<void (CMClientMgr::*)(int count)> CMClientMgr::_Init;
	static hook_method<void (CMClientMgr::*)(void)> CMClientMgr::_ProcessAllCharacter;
	static hook_method<CMClient* (CMClientMgr::*)(void)> CMClientMgr::_AllocServer;
	static hook_method<void (CMClientMgr::*)(CMClient* mServer)> CMClientMgr::_FreeServer;
	static hook_method<int (CMClientMgr::*)(CMClient* mServer)> CMClientMgr::_AddServer;
	static hook_method<void (CMClientMgr::*)(int SID)> CMClientMgr::_DeleteServer;
};
