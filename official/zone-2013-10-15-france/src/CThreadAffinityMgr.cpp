#include "CThreadAffinityMgr.h"


/// singleton instance
CThreadAffinityMgr*& CThreadAffinityMgr::m_cpSelf = VTOR<CThreadAffinityMgr*>(DetourFindFunction(EXEPATH(), "CThreadAffinityMgr::m_cpSelf"));


CThreadAffinityMgr::CThreadAffinityMgr()
{
	m_hMutex = NULL;
	m_bOK = true;
}


CThreadAffinityMgr::~CThreadAffinityMgr()
{
	if( m_hMutex != NULL )
	{
		CloseHandle(m_hMutex);
		m_hMutex = NULL;
	}
}


bool CThreadAffinityMgr::CreateInstance()
{
	if( m_cpSelf != NULL )
		return false;

	m_cpSelf = new(std::nothrow) CThreadAffinityMgr();
	if( m_cpSelf == NULL )
		return false;

	if( !m_cpSelf->m_bOK )
	{
		delete m_cpSelf;
		m_cpSelf = NULL;
		return false;
	}

	return true;
}


void CThreadAffinityMgr::DestroyInstance()
{
	if( m_cpSelf != NULL )
	{
		delete m_cpSelf;
		m_cpSelf = NULL;
	}
}


CThreadAffinityMgr* CThreadAffinityMgr::GetObj() /// @custom
{
	return m_cpSelf;
}


bool CThreadAffinityMgr::isOK() const
{
	return m_bOK;
}


unsigned long CThreadAffinityMgr::GetThreadAffinityMask()
{
	SYSTEM_INFO info;
	GetSystemInfo(&info);

	for( DWORD i = 1; i <= info.dwNumberOfProcessors; i += 2 )
	{
		char name[260] = {};
		_snprintf_s(name, countof(name), _TRUNCATE, "RAG_ZONESVR_PROCESSOR%02d", i);

		HANDLE hMutex = OpenMutexA(MUTEX_ALL_ACCESS, FALSE, name);
		if( hMutex != NULL )
		{// already taken
			CloseHandle(hMutex);
			continue;
		}

		// reserve these two unused cores
		m_hMutex = CreateMutexA(NULL, FALSE, name);
		unsigned long result = (1|2) << (i - 1);
		return result; // done.
	}

	// no unused cores available
	unsigned long result = 0;
	for( DWORD i = 1; i <= info.dwNumberOfProcessors; ++i )
		result |= 1 << (i - 1);
	return result;
}
