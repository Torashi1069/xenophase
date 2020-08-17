#include "UserList.h"
#include "Common/Reporter.h"


#define NUM_BUCKETS 500


CUserList::CUserList()
{
	m_nSize = 0;
	m_nCountAuth = 0;
	m_pUser = NULL;

	m_pUser = new tag_SMAP[NUM_BUCKETS];
}


CUserList::~CUserList()
{
	if( m_pUser == NULL )
		return;

	for( int i = 0; i < NUM_BUCKETS; ++i )
	{
		tag_SMAP* pUser = &m_pUser[i];

		pUser->m_csMap.Enter();

		for( stdext::hash_map<int,SUSER_*>::iterator iObject = pUser->m_mapMap.begin(); iObject != pUser->m_mapMap.end(); ++iObject )
			delete iObject->second;

		pUser->m_mapMap.clear();

		pUser->m_csMap.Leave();
	}

	delete[] m_pUser;
	m_pUser = NULL;
}


void CUserList::Insert(DWORD dwAID, SUSER_& object)
{
	if( dwAID <= 0 || dwAID >= 9999999 )
		return;

	SUSER_* newUser = new SUSER_;
	if( newUser == NULL )
	{
		CSingleton<CReporter>::getSingletonPtr()->CReporter::Log("CUserList::Insert error !!!!! new fail.. aid %u \n", dwAID);
		return;
	}

	memcpy(newUser, &object, sizeof(SUSER_));

	tag_SMAP* pUser = &m_pUser[dwAID % NUM_BUCKETS];

	pUser->m_csMap.Enter();

	stdext::hash_map<int,SUSER_*>::iterator iObject = pUser->m_mapMap.find(dwAID);
	if( iObject == pUser->m_mapMap.end() )
	{
		pUser->m_mapMap[dwAID] = newUser;

		if( newUser->m_nIsGameStarted )
			InterlockedIncrement((LONG*)&m_nCountAuth);
		InterlockedIncrement((LONG*)&m_nSize);
	}
	else
	{
		SUSER_* existingUser = iObject->second;
		pUser->m_mapMap.erase(iObject);

		if( !existingUser->m_nIsGameStarted && newUser->m_nIsGameStarted )
			InterlockedIncrement((LONG*)&m_nCountAuth);

		delete existingUser;

		pUser->m_mapMap[dwAID] = newUser;
	}

	pUser->m_csMap.Leave();
}


void CUserList::Delete(DWORD dwAID)
{
	if( dwAID <= 0 || dwAID >= 9999999 )
		return;

	tag_SMAP* pUser = &m_pUser[dwAID % NUM_BUCKETS];

	pUser->m_csMap.Enter();

	stdext::hash_map<int,SUSER_*>::iterator iObject = pUser->m_mapMap.find(dwAID);
	if( iObject == pUser->m_mapMap.end() )
	{
		pUser->m_csMap.Leave();
		return;
	}

	SUSER_* existingUser = iObject->second;
	pUser->m_mapMap.erase(iObject);

	if( existingUser->m_nIsGameStarted )
		InterlockedDecrement((LONG*)&m_nCountAuth);
	InterlockedDecrement((LONG*)&m_nSize);

	delete existingUser;

	pUser->m_csMap.Leave();
}


BOOL CUserList::Bring(DWORD dwAID, SUSER_* pObject)
{
	if( dwAID <= 0 || dwAID >= 9999999 )
		return FALSE;

	tag_SMAP* pUser = &m_pUser[dwAID % NUM_BUCKETS];

	pUser->m_csMap.Enter();

	stdext::hash_map<int,SUSER_*>::iterator iObject = pUser->m_mapMap.find(dwAID);
	if( iObject == pUser->m_mapMap.end() )
	{
		pUser->m_csMap.Leave();
		return FALSE;
	}

	SUSER_* existingUser = iObject->second;
	pUser->m_mapMap.erase(iObject);
	memcpy(pObject, existingUser, sizeof(SUSER_));

	if( existingUser->m_nIsGameStarted )
		InterlockedDecrement((LONG*)&m_nCountAuth);
	InterlockedDecrement((LONG*)&m_nSize);

	pUser->m_csMap.Leave();
	delete existingUser;

	return TRUE;
}


BOOL CUserList::Get(DWORD dwAID, SUSER_* pObject)
{
	if( dwAID <= 0 || dwAID >= 9999999 )
		return FALSE;

	tag_SMAP* pUser = &m_pUser[dwAID % NUM_BUCKETS];

	pUser->m_csMap.Enter();

	stdext::hash_map<int,SUSER_*>::iterator iObject = pUser->m_mapMap.find(dwAID);
	if( iObject == pUser->m_mapMap.end() )
	{
		pUser->m_csMap.Leave();
		return FALSE;
	}

	memcpy(pObject, iObject->second, sizeof(SUSER_));

	pUser->m_csMap.Leave();

	return TRUE;
}


int CUserList::GetCount()
{
	return m_nSize;
}


int CUserList::GetCountAuth()
{
	return m_nCountAuth;
}
