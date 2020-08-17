#include "Common/CriticalSection.h"


CCriticalSection::CCriticalSection()
{
	InitializeCriticalSectionAndSpinCount(&m_cs, 2000);
}


CCriticalSection::~CCriticalSection()
{
	DeleteCriticalSection(&m_cs);
}


void CCriticalSection::Enter()
{
	EnterCriticalSection(&m_cs);
}


void CCriticalSection::Leave()
{
	LeaveCriticalSection(&m_cs);
}


int CCriticalSection::TryEnter()
{
	return TryEnterCriticalSection(&m_cs);
}
