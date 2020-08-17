#include "ZoneServerInfoList.h"


/// singleton instance
static CZoneServerInfoList g_ZoneServerInfoList;
CZoneServerInfoList* CSingleton<CZoneServerInfoList>::ms_Singleton;


void CZoneServerInfoList::AddZoneServerInfo(SSERVERINFO* pServerInfo)
{
	m_csZoneServerInfoList.Enter();

	SZONESERVERINFO zoneserverinfo;
	zoneserverinfo.m_nSID = pServerInfo->m_nSID;
	zoneserverinfo.m_dwIP = pServerInfo->m_dwIP;
	zoneserverinfo.m_nPort = pServerInfo->m_nPort;
	zoneserverinfo.m_dwPrivateIP = pServerInfo->m_dwPrivateIP;
	zoneserverinfo.m_nPrivatePort = pServerInfo->m_nPrivatePort;
	zoneserverinfo.m_bConnect = TRUE;
	zoneserverinfo.m_dwUserCount = 0;

	m_vectorZoneServerInfoList.push_back(zoneserverinfo);
	printf("%s\n", pServerInfo->m_szName);

	m_csZoneServerInfoList.Leave();
}


BOOL CZoneServerInfoList::GetZoneServerInfo(int nSID, SZONESERVERINFO* pZoneServerInfo)
{
	BOOL result = FALSE;
	m_csZoneServerInfoList.Enter();

	for( size_t i = 0; i < m_vectorZoneServerInfoList.size(); ++i )
	{
		if( m_vectorZoneServerInfoList[i].m_nSID == nSID )
		{
			*pZoneServerInfo = m_vectorZoneServerInfoList[i];
			result = TRUE;
			break;
		}
	}

	m_csZoneServerInfoList.Leave();
	return result;
}


int CZoneServerInfoList::GetSID(DWORD dwIP)
{
	int nSID = 0;
	m_csZoneServerInfoList.Enter();

	for( size_t i = 0; i < m_vectorZoneServerInfoList.size(); ++i )
	{
		if( m_vectorZoneServerInfoList[i].m_dwIP == dwIP
		||  m_vectorZoneServerInfoList[i].m_dwPrivateIP != 0 && m_vectorZoneServerInfoList[i].m_dwPrivateIP == dwIP )
			nSID = m_vectorZoneServerInfoList[i].m_nSID;
	}

	m_csZoneServerInfoList.Leave();
	return nSID;
}


BOOL CZoneServerInfoList::IsZoneServer(DWORD dwIP)
{
	BOOL result = FALSE;
	m_csZoneServerInfoList.Enter();

	for( size_t i = 0; i < m_vectorZoneServerInfoList.size(); ++i )
	{
		if( m_vectorZoneServerInfoList[i].m_dwIP == dwIP )
		{
			result = TRUE;
			break;
		}

		if( m_vectorZoneServerInfoList[i].m_dwPrivateIP != 0 && m_vectorZoneServerInfoList[i].m_dwPrivateIP == dwIP )
		{
			result = TRUE;
			break;
		}
	}

	m_csZoneServerInfoList.Leave();
	return result;
}


SZONESERVERINFO* CZoneServerInfoList::GetZoneServerInfo(int nSID)
{
	for( size_t i = 0; i < m_vectorZoneServerInfoList.size(); ++i )
		if( m_vectorZoneServerInfoList[i].m_nSID == nSID )
			return &m_vectorZoneServerInfoList[i];

	return NULL;
}


int CZoneServerInfoList::GetTotalUserCount()
{
	int result = 0;
	m_csZoneServerInfoList.Enter();

	for( size_t i = 0; i < m_vectorZoneServerInfoList.size(); ++i )
		result += m_vectorZoneServerInfoList[i].m_dwUserCount;

	m_csZoneServerInfoList.Leave();
	return result;
}


void CZoneServerInfoList::SetUserCount(int nSID, int nCount)
{
	m_csZoneServerInfoList.Enter();

	SZONESERVERINFO* info = this->CZoneServerInfoList::GetZoneServerInfo(nSID);
	if( info != NULL )
		info->m_dwUserCount = nCount;

	m_csZoneServerInfoList.Leave();
}
