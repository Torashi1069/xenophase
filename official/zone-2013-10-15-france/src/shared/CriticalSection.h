#pragma once


class CCriticalSection
{
private:
	/* this+0 */ RTL_CRITICAL_SECTION m_CriticalSection;

public:
	CCriticalSection();
	~CCriticalSection();

public:
	void Init();
	void Delete();
	void Enter();
	void Leave();
};
