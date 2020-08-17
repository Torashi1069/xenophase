#pragma once
#include "ScriptEventHandler.h"


class CScriptEventMgr
{
private:
	typedef std::map<int,CScriptEventHandler*> SCRIPT_EVENTS;

public:
//	CScriptEventMgr();
	~CScriptEventMgr();

public:
	void Process();
	bool SendMsg(int eventNo, unsigned long msgID, int par1, int par2, int par3);
	void AddEvent(CScriptEventHandler* event);
	void RemoveEvent(int eventNo);

private:
	void Reset();
	int AllocEventNo();
	CScriptEventHandler* GetEvent(int eventNo);

private:
	/* this+0 */ SCRIPT_EVENTS m_events;
};
