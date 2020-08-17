#pragma once
#include "Common/CriticalSection.h"


class CNightEnv
{
public:
//	CNightEnv();
//	~CNightEnv();
//	void checkTimeAndAction();
//	bool canAccept(SUSER_&);
//	bool IsAdult(SUSER_&);
//	bool IsNight();

private:
//	void SetTime(tm*);
//	void GetTime(tm*);
//	bool nightModeAction();
//	int getAge(int);
//	int getAge(const char*);
//	bool canAcceptAtNight(SUSER_&);

private:
	/* this+ 0 */ //const CNightEnv::`vftable';
	/* this+ 4 */ DWORD m_dwActionTime;
	/* this+ 8 */ bool m_bNightMode;
	/* this+12 */ tm m_CurTime;
	/* this+48 */ CCriticalSection m_csCurTime;
};
