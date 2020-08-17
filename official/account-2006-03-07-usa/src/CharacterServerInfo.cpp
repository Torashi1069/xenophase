#include "CharacterServerInfo.h"


CCharacterServerInfo::CCharacterServerInfo()
{
	m_nOffset = 0;
	memset(m_nSID, 0, sizeof(m_nSID));
	memset(m_characterServerInfo, 0, sizeof(m_characterServerInfo));
}


void CCharacterServerInfo::AddCharacterServerInfo(SSERVERINFO* pServerInfo, WORD wState)
{
	m_nSID[m_nOffset] = pServerInfo->m_nSID;
	m_characterServerInfo[m_nOffset].ip = pServerInfo->m_dwIP;
	m_characterServerInfo[m_nOffset].port = (short)pServerInfo->m_nPort;
	m_characterServerInfo[m_nOffset].state = wState;
	memcpy(m_characterServerInfo[m_nOffset].name, pServerInfo->m_szName, sizeof(pServerInfo->m_szName)-1); //FIXME: buffer overflow
	++m_nOffset;
}


void CCharacterServerInfo::SetUserCount(int nSID, WORD wCount)
{
	for( int i = 0; i < countof(m_nSID); ++i )
	{
		if( m_nSID[i] == nSID )
		{
			m_characterServerInfo[i].usercount = wCount;
			break;
		}
	}
}


SERVER_ADDR* CCharacterServerInfo::GetCharacterServerInfo(int* pnCount)
{
	*pnCount = m_nOffset;
	return m_characterServerInfo;
}
