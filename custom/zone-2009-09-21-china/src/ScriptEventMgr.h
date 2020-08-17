#pragma once
#include "std/map"
class CScriptEventHandler;


class CScriptEventMgr
{
public:
	/* this+0 */ public: mystd::map<int,CScriptEventHandler*> m_events;

	//public: void CScriptEventMgr::~CScriptEventMgr();
	public: void CScriptEventMgr::Process(void);
	//public: bool CScriptEventMgr::SendMsg(int, unsigned long, int, int, int);
	//public: void CScriptEventMgr::AddEvent(CScriptEventHandler *);
	//public: void CScriptEventMgr::RemoveEvent(int);
	//private: void CScriptEventMgr::Reset();
	//private: int CScriptEventMgr::AllocEventNo();
	//private: CScriptEventHandler* CScriptEventMgr::GetEvent(int);
	//public: void CScriptEventMgr::CScriptEventMgr();

private:
	static hook_method<void (CScriptEventMgr::*)(void)> CScriptEventMgr::_Process;
};
