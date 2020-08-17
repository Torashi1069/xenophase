#include "CriticalSection.h"


CCriticalSection::CCriticalSection(void)
{
	::InitializeCriticalSection(&m_CriticalSection);
}


CCriticalSection::~CCriticalSection(void)
{
	::DeleteCriticalSection(&m_CriticalSection);
}


void CCriticalSection::Init(void)
{
	::InitializeCriticalSection(&m_CriticalSection);
}


void CCriticalSection::Delete(void)
{
	::DeleteCriticalSection(&m_CriticalSection);
}


void CCriticalSection::Enter(void)
{
	::EnterCriticalSection(&m_CriticalSection);
}


void CCriticalSection::Leave(void)
{
	::LeaveCriticalSection(&m_CriticalSection);
}
