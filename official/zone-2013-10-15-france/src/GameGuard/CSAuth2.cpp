#include "GameGuard/CSAuth2.h"


CCSAuth2::CCSAuth2()
{
	m_pProtocol = ggGlobal.lpCurrentAuthProtocol;
	memset(&m_AuthQuery, 0, sizeof(m_AuthQuery));
	memset(&m_AuthAnswer, 0, sizeof(m_AuthAnswer));
	m_bPrtcRef = FALSE;
	m_dwUserFlag = 0;
	srand(time(NULL));
}


CCSAuth2::~CCSAuth2()
{
	if( m_bPrtcRef == TRUE )
	{
		--m_pProtocol->dwQueryCount;

		if( m_pProtocol->dwQueryCount == 0 )
		{
			if( m_pProtocol != ggGlobal.lpCurrentAuthProtocol )
			{
				UnloadAuthProtocol(m_pProtocol);
			}
		}
	}
}


void CCSAuth2::Init()
{
	m_pProtocol = ggGlobal.lpCurrentAuthProtocol;
	memset(&m_AuthQuery, 0, sizeof(m_AuthQuery));
	memset(&m_AuthAnswer, 0, sizeof(m_AuthAnswer));
	m_bPrtcRef = FALSE;
	m_dwUserFlag = 0;
	srand(time(NULL));
}


DWORD CCSAuth2::GetAuthQuery()
{
	if( m_pProtocol == NULL )
		return ERROR_GGAUTH_FAIL_BEFORE_INIT;

	if( m_bPrtcRef == FALSE )
	{
		++m_pProtocol->dwQueryCount;

		if( !(ggGlobal.lpCurrentAuthProtocol->dwFlag & 2) )
		{
			if ( ggGlobal.lpCurrentAuthProtocol->dwQueryCount > ggGlobal.nMaxCount )
			{
				ggGlobal.lpCurrentAuthProtocol->dwFlag = ggGlobal.lpCurrentAuthProtocol->dwFlag | 2;
			}
		}

		m_bPrtcRef = TRUE;
	}

	return m_pProtocol->PtrcGetAuthQuery(m_pProtocol->dwFlag, (_GG_AUTH*)&m_dwUserFlag, &m_AuthQuery, &m_AuthAnswer);
}


DWORD CCSAuth2::CheckAuthAnswer()
{
	if( !m_pProtocol )
		return ERROR_GGAUTH_FAIL_BEFORE_INIT;

	if( m_AuthAnswer.dwIndex != m_pProtocol->dwPtrcVersion )
	{
		if( ggGlobal.lpCurrentAuthProtocol->dwFlag & 2 )
			return ERROR_GGAUTH_INVALID_PROTOCOL_VERSION;
		
		if( ggGlobal.lpCurrentAuthProtocol->lpPrevProtocol == NULL )
			return ERROR_GGAUTH_INVALID_PROTOCOL_VERSION;

		--m_pProtocol->dwQueryCount;
		m_pProtocol = ggGlobal.lpCurrentAuthProtocol->lpPrevProtocol;
		++ggGlobal.lpCurrentAuthProtocol->lpPrevProtocol->dwQueryCount;
	}

	return m_pProtocol->PtrcCheckAuthAnswer(m_pProtocol->dwFlag, (_GG_AUTH*)&m_dwUserFlag, &m_AuthQuery, &m_AuthAnswer);
}
