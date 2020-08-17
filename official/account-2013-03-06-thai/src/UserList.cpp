#include "Account.h"
#include "UserList.h"
#include "Common/EnterTraceLog.h"


CUserList::CUserList()
{
	m_nSize = 0;
	m_nCountAuth = 0;
	m_nAllocSize = 0;
	m_bInitSuccess = false;

	m_pUser = new SUSER_*[MAX_ACCOUNTID];
	m_pLock = new LONG[MAX_ACCOUNTID];
	m_pStatus = new char[MAX_ACCOUNTID];

	if( m_pUser != NULL )
		for( int i = 0; i < MAX_ACCOUNTID; ++i )
			m_pUser[i] = NULL;

	if( m_pLock != NULL )
		for( int i = 0; i < MAX_ACCOUNTID; ++i )
			m_pLock[i] = NULL;

	if( m_pStatus != NULL )
		for( int i = 0; i < MAX_ACCOUNTID; ++i )
			m_pStatus[i] = NULL;

	if( m_pUser != NULL && m_pLock != NULL && m_pStatus != NULL )
		m_bInitSuccess = true;
}


CUserList::~CUserList()
{
	m_bInitSuccess = false;

	if( m_pUser != NULL )
	{
		for( int i = 0; i < MAX_ACCOUNTID; ++i )
			if( m_pUser[i] != NULL )
				delete m_pUser[i];

		delete[] m_pUser;
		m_pUser = NULL;
	}

	if( m_pLock != NULL )
	{
		delete[] m_pLock;
		m_pLock = NULL;
	}

	if( m_pStatus != NULL )
	{
		delete[] m_pStatus;
		m_pStatus = NULL;
	}
}


void CUserList::LockAID(DWORD dwAID)
{
	while( InterlockedExchange(&m_pLock[dwAID], 1) == 1 )
		SwitchToThread();
}


void CUserList::ReleaseAID(DWORD dwAID)
{
	InterlockedExchange(&m_pLock[dwAID], 0);
}


void CUserList::Insert(DWORD dwAID, SUSER_& object)
{
	if( dwAID <= 0 || dwAID >= MAX_ACCOUNTID - 1 || !m_bInitSuccess )
		return;

	this->CUserList::LockAID(dwAID);

	if( m_pUser[dwAID] != NULL )
	{
		if( m_pStatus[dwAID] == 1 )
		{
			if( object.m_nIsGameStarted )
				InterlockedIncrement((LONG*)&m_nCountAuth);

			memcpy(m_pUser[dwAID], &object, sizeof(SUSER_));

			InterlockedIncrement((LONG*)&m_nSize);
			m_pStatus[dwAID] = 2;
		}
		else
		if( m_pStatus[dwAID] == 2 )
		{
			if( object.m_nIsGameStarted && !m_pUser[dwAID]->m_nIsGameStarted )
				InterlockedIncrement((LONG*)&m_nCountAuth);

			memcpy(m_pUser[dwAID], &object, sizeof(SUSER_));
		}
	}
	else
	{
		m_pUser[dwAID] = new SUSER_;
		if( m_pUser[dwAID] == NULL )
		{
			CEnterTraceLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__, "CUserList::Insert error !!!!! new fail.. aid %u \n", dwAID);
		}
		else
		{
			m_pStatus[dwAID] = 1;
			InterlockedIncrement((LONG*)&m_nAllocSize);

			if( object.m_nIsGameStarted )
				InterlockedIncrement((LONG*)&m_nCountAuth);

			memcpy(m_pUser[dwAID], &object, sizeof(SUSER_));

			m_pStatus[dwAID] = 2;
			InterlockedIncrement((LONG*)&m_nSize);
		}
	}

	this->CUserList::ReleaseAID(dwAID);
}


void CUserList::Delete(DWORD dwAID)
{
	if( dwAID <= 0 || dwAID >= MAX_ACCOUNTID - 1 || !m_bInitSuccess )
		return;

	this->CUserList::LockAID(dwAID);

	if( m_pUser[dwAID] == NULL || m_pStatus[dwAID] != 2 )
	{
		this->CUserList::ReleaseAID(dwAID);
		return;
	}

	if( m_pUser[dwAID]->m_nIsGameStarted )
		InterlockedDecrement((LONG*)&m_nCountAuth);

	m_pStatus[dwAID] = 1;
	InterlockedDecrement((LONG*)&m_nSize);

	this->CUserList::ReleaseAID(dwAID);
}


BOOL CUserList::Bring(DWORD dwAID, SUSER_* pObject)
{
	if( dwAID <= 0 || dwAID >= MAX_ACCOUNTID - 1 || !m_bInitSuccess )
		return FALSE;

	this->CUserList::LockAID(dwAID);

	if( m_pUser[dwAID] == NULL || m_pStatus[dwAID] != 2 )
	{
		this->CUserList::ReleaseAID(dwAID);
		return FALSE;
	}

	memcpy(pObject, m_pUser[dwAID], sizeof(*pObject));

	if( m_pUser[dwAID]->m_nIsGameStarted )
		InterlockedDecrement((LONG*)&m_nCountAuth);

	m_pStatus[dwAID] = 1;
	InterlockedDecrement((LONG*)&m_nSize);

	this->CUserList::ReleaseAID(dwAID);
	return TRUE;
}


BOOL CUserList::Get(DWORD dwAID, SUSER_* pObject)
{
	if( dwAID <= 0 || dwAID >= MAX_ACCOUNTID - 1 || !m_bInitSuccess )
		return FALSE;

	this->CUserList::LockAID(dwAID);

	if( m_pUser[dwAID] == NULL || m_pStatus[dwAID] != 2 )
	{
		this->CUserList::ReleaseAID(dwAID);
		return FALSE;
	}

	memcpy(pObject, m_pUser[dwAID], sizeof(*pObject));

	this->CUserList::ReleaseAID(dwAID);
	return TRUE;
}


CCharSvrProcess* CUserList::GetCharProcess(DWORD dwAID)
{
	if( dwAID <= 0 || dwAID >= MAX_ACCOUNTID - 1 )
		return NULL;

	CCharSvrProcess* result = NULL;
	this->CUserList::LockAID(dwAID);

	if( m_pUser[dwAID] != NULL )
		if( m_pUser[dwAID]->m_process != NULL )
			result = m_pUser[dwAID]->m_process;

	this->CUserList::ReleaseAID(dwAID);
	return result;
}


bool CUserList::IsPCBangUser(DWORD dwAID)
{
	if( dwAID <= 0 || dwAID >= MAX_ACCOUNTID - 1 )
		return false;

	bool result = false;
	this->CUserList::LockAID(dwAID);

	if( m_pUser[dwAID] != NULL )
		result = ( m_pUser[dwAID]->m_isPCBang > 0 );

	this->CUserList::ReleaseAID(dwAID);
	return result;
}


int CUserList::GetCount()
{
	return m_nSize;
}


int CUserList::GetCountAuth()
{
	return m_nCountAuth;
}


int CUserList::GetAllocCount()
{
	return m_nAllocSize;
}
