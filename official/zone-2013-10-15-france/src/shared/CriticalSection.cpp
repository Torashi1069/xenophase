#include "shared/CriticalSection.h"


CCriticalSection::CCriticalSection()
{
	InitializeCriticalSectionAndSpinCount(&m_CriticalSection, 2000);
}


CCriticalSection::~CCriticalSection()
{
	DeleteCriticalSection(&m_CriticalSection);
}


void CCriticalSection::Enter()
{
	EnterCriticalSection(&m_CriticalSection);
}


void CCriticalSection::Leave()
{
	LeaveCriticalSection(&m_CriticalSection);
}
