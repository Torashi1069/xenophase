#include "Network3/Process.h"
#include "Network3/Stream.h"


CProcess::CProcess()
{
	m_dwIP = 0;
	m_dwSessionID = 0;
	m_pStream = NULL;
}


CProcess::~CProcess()
{
}


bool CProcess::Init(DWORD dwStreamSessionID, DWORD dwIP)
{
	m_cs.Enter();
	m_dwSessionID = dwStreamSessionID;
	m_dwIP = dwIP;
	m_cs.Leave();

	return this->OnConnect();
}


bool CProcess::CloseOuter(DWORD dwSessionID, DWORD dwTime)
{
	if( m_dwSessionID == 0 || dwSessionID != m_dwSessionID )
		return false;

	m_pStream->CStream::CloseOuter(m_dwSessionID, dwTime);
	return true;
}


void CProcess::OnStreamClose()
{
	m_cs.Enter();

	if( m_dwSessionID != 0 )
	{
		m_dwSessionID = 0;
		m_cs.Leave();
		this->OnClose();
		m_dwIP = 0;
	}
	else
	{
		m_cs.Leave();
		m_dwIP = 0;
	}
}


void CProcess::Send(char* buf, int len, DWORD dwSessionID, bool bBroadcast)
{
	m_pStream->CStream::Send(buf, len, dwSessionID, bBroadcast);
}


void CProcess::SetStream(CStream* pStream)
{
	m_pStream = pStream;
}


DWORD CProcess::GetSessionID()
{
	return m_dwSessionID;
}


DWORD CProcess::GetIP()
{
	return m_dwIP;
}
