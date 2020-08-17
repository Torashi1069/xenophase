#include "Account.h" // g_LocalSID
#include "CharacterServerInfo.h"


CCharacterServerInfo::CCharacterServerInfo()
{
	m_nBalkyrieCharSvrOffset = -1;
	m_nCountCharSvr_thai = 0;
	m_nOffset = 0;
	memset(m_characterServerInfo, 0, sizeof(m_characterServerInfo));
	memset(m_arPtrCharacterServerInfo_thai, 0, sizeof(m_arPtrCharacterServerInfo_thai));
	memset(m_nSID, 0, sizeof(m_nSID));
}


void CCharacterServerInfo::AddCharacterServerInfo(SSERVERINFO* pServerInfo, WORD wState)
{
	m_nSID[m_nOffset] = pServerInfo->m_nSID;
	m_characterServerInfo[m_nOffset].ip = pServerInfo->m_dwIP;
	m_characterServerInfo[m_nOffset].port = (short)pServerInfo->m_nPort;
	m_characterServerInfo[m_nOffset].state = wState;
	memcpy(m_characterServerInfo[m_nOffset].name, pServerInfo->m_szName, sizeof(m_characterServerInfo[m_nOffset].name)-1);
	++m_nOffset;

	if( pServerInfo->m_nSID == 2332 )
	{
		m_nBalkyrieCharSvrOffset = m_nOffset - 1;
		if( g_LocalSID != 10 )
			return;
	}

	m_arPtrCharacterServerInfo_thai[m_nCountCharSvr_thai] = &m_characterServerInfo[m_nOffset];
	++m_nCountCharSvr_thai;
}


void CCharacterServerInfo::SetUserCount(int nSID, WORD wCount)
{
	for( int i = 0; i < countof(m_nSID); ++i )
	{
		if( m_nSID[i] == nSID )
		{
			m_csCharSvrInfo.Enter();
			m_characterServerInfo[i].usercount = wCount;
			m_csCharSvrInfo.Leave();
			break;
		}
	}
}


SERVER_ADDR* CCharacterServerInfo::GetCharacterServerInfo(int* pnCount)
{
	*pnCount = m_nOffset;
	return m_characterServerInfo;
}
