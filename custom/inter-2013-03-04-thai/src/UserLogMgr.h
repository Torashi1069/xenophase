#pragma once


class CUserLogMgr
{
public:
	void OnProcess();
	void Init();

public:
	CUserLogMgr();
	virtual ~CUserLogMgr();

public:
	/* this+0 */ //const CUserLogMgr::`vftable';
	/* this+4 */ DWORD m_LogIdleTime;
};
