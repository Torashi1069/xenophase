#pragma once


class CCriticalSection
{
private:
	/* this+0 */ RTL_CRITICAL_SECTION m_cs;

public:
	CCriticalSection();
	~CCriticalSection();
	void Enter();
	void Leave();
	int TryEnter();
};
