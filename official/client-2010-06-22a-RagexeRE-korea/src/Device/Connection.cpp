#include "Globals.h" // Trace(), ErrorMsg()
#include "Packet.h"
#include "Device/Connection.h"
////////////////////////////////////////


/// static members
WSADATA& CConnection::s_wsaData = VTOR<WSADATA>(SymDB::Find("CConnection::s_wsaData"));
HINSTANCE& CConnection::s_wsmodule = VTOR<HINSTANCE>(SymDB::Find("CConnection::s_wsmodule"));
SENDFUNC*& CConnection::s_wsSend = VTOR<SENDFUNC*>(SymDB::Find("CConnection::s_wsSend"));
RECVFUNC*& CConnection::s_wsRecv = VTOR<RECVFUNC*>(SymDB::Find("CConnection::s_wsRecv"));


CConnection::CConnection()
: m_socket(INVALID_SOCKET), m_bBlock(false), m_dwTime(0)
{
	this->CConnection::ResetQueue();
}


CConnection::~CConnection()
{
}


void CConnection::SetBlock(bool bBlock)
{
	m_bBlock = bBlock;

	if( !bBlock )
	{// flush block queue
		while( m_blockQueue.CPacketQueue::GetSize() != 0 )
		{
			int iSize = m_blockQueue.CPacketQueue::GetSize();
			const char* pData = m_blockQueue.CPacketQueue::GetDataPtr();

			m_sendQueue.CPacketQueue::InsertData(iSize, pData);
			m_blockQueue.CPacketQueue::RemoveData(iSize);
			this->CConnection::OnSend();
		}
	}
}


void CConnection::SetDelay(DWORD dwDelay)
{
	m_dwTime = dwDelay;
}


bool CConnection::Connect(const ServerAddress* addr)
{
	this->CConnection::SetBlock(false);
	this->CConnection::ResetQueue();

	m_socket = socket(AF_INET, SOCK_STREAM, 0);
	if( m_socket == INVALID_SOCKET )
		return false;

	u_long ul = 1;
	if( ioctlsocket(m_socket, FIONBIO, &ul) == SOCKET_ERROR )
	{
		ErrorMsg("Failed to setup select mode");
		return false;
	}

	memset(&m_addr, 0, sizeof(m_addr));
	m_addr.sin_family = AF_INET;
	m_addr.sin_addr.s_addr = inet_addr(addr->ip);
	m_addr.sin_port = htons(addr->port);

	if( connect(m_socket, (sockaddr*)&m_addr, sizeof(m_addr)) == SOCKET_ERROR )
	{
		if( WSAGetLastError() != WSAEWOULDBLOCK )
		{
			Trace("connect error %d", WSAGetLastError());
			this->CConnection::Disconnect();
			return false;
		}
	}

	m_bLastPoll2Failed = FALSE;
	return true;
}


bool CConnection::Poll()
{
	if( m_socket != INVALID_SOCKET )
	{
		return ( this->CConnection::OnRecv() && this->CConnection::OnSend() );
	}
	else
	{
		return true;
	}
}


void CConnection::Poll2()
{
	if( m_socket != INVALID_SOCKET )
	{
		m_bLastPoll2Failed = !( this->CConnection::OnRecv() && this->CConnection::OnSend() );
	}
}


BOOL CConnection::GetLastPoll2Failed()
{
	return m_bLastPoll2Failed;
}


void CConnection::Disconnect()
{
	if( m_socket != INVALID_SOCKET )
	{
		closesocket(m_socket);
		m_socket = INVALID_SOCKET;
		m_sendQueue.CPacketQueue::Init(40*1024);
		m_blockQueue.CPacketQueue::Init(40*1024);
	}

	m_bLastPoll2Failed = FALSE;
}


void CConnection::Send(int size, const char* buf)
{
	if( m_socket != INVALID_SOCKET )
	{
		if( m_bBlock )
		{
			m_blockQueue.CPacketQueue::InsertData(size, buf);
		}
		else
		{
			m_sendQueue.CPacketQueue::InsertData(size, buf);
			this->CConnection::OnSend();
		}
	}
}


int CConnection::Recv(char* buf, int size, bool mustRecv)
{
	int iRecv;

	if( mustRecv )
	{
		iRecv = ( m_recvQueue.CPacketQueue::GetData(size, buf) ) ? size : 0;
	}
	else
	{
		iRecv = min(size, m_recvQueue.CPacketQueue::GetSize());
		m_recvQueue.CPacketQueue::GetData(iRecv, buf);
	}

	return iRecv;
}


void CConnection::ResetQueue()
{
	m_recvQueue.CPacketQueue::Init(40*1024);
	m_sendQueue.CPacketQueue::Init(40*1024);
	m_blockQueue.CPacketQueue::Init(40*1024);
}


bool CConnection::OnSend()
{
	while( m_dwTime < timeGetTime() && m_sendQueue.CPacketQueue::GetSize() != 0 )
	{
		timeval tval;
		tval.tv_sec = 0;
		tval.tv_usec = 0;

		fd_set fdwrite;
		FD_ZERO(&fdwrite);
		FD_SET(m_socket, &fdwrite);

		int nfds = select(0, NULL, &fdwrite, NULL, &tval);
		if( nfds == SOCKET_ERROR )
			continue;
		if( nfds <= 0 )
			break;

		const char* pData = m_sendQueue.CPacketQueue::GetDataPtr();
		int iSize = m_sendQueue.CPacketQueue::GetSize();

		int sent = s_wsSend(m_socket, pData, iSize, 0);
		if( sent == SOCKET_ERROR )
		{
			if( WSAGetLastError() == WSAEWOULDBLOCK || WSAGetLastError() == WSAENOTCONN )
				continue;

			this->CConnection::Disconnect();
			return false;
		}

		m_sendQueue.CPacketQueue::RemoveData(sent);
	}

	return true;
}


bool CConnection::OnRecv()
{
	timeval tval;
	tval.tv_sec = 0;
	tval.tv_usec = 0;

	fd_set fdread;
	FD_ZERO(&fdread);
	FD_SET(m_socket, &fdread);

	int nfds = select(0, &fdread, NULL, NULL, &tval);
	if( nfds == SOCKET_ERROR || nfds <= 0 )
		return true;

	char tempBuf[2048];
	int rcvd = s_wsRecv(m_socket, tempBuf, sizeof(tempBuf), 0);
	if( rcvd == SOCKET_ERROR )
	{
		if( WSAGetLastError() == WSAEWOULDBLOCK || WSAGetLastError() == WSAENOTCONN )
			return true;

		this->CConnection::Disconnect();
		return false;
	}

	if( rcvd <= 0 )
	{
		this->CConnection::Disconnect();
		return false;
	}

	m_recvQueue.CPacketQueue::InsertData(rcvd, tempBuf);
	return true;
}


void CConnection::OnConnect()
{
}


void CConnection::OnClose()
{
}


bool CConnection::Startup()
{
	if( WSAStartup(MAKEWORD(1,1), &s_wsaData) != 0 )
	{
		ErrorMsg("Failed to load Winsock library!");
		WSACleanup();
		return false;
	}

	s_wsmodule = LoadLibraryA("ws2_32.dll");
	s_wsSend = (SENDFUNC*)GetProcAddress(s_wsmodule, "send");
	s_wsRecv = (RECVFUNC*)GetProcAddress(s_wsmodule, "recv");

	if( s_wsSend == NULL )
	{
		s_wsSend = &send;
		MessageBoxA(NULL, "GetProcAddress(\"send\") Failed.", "Module Hooking Error", MB_OK);
	}

	if( s_wsRecv == NULL )
	{
		s_wsRecv = &recv;
		MessageBoxA(NULL, "GetProcAddress(\"recv\") Failed.", "Module Hooking Error", MB_OK);
	}

	CRagConnection::instanceR().CConnection::CheckModulePt(); // NOTE: return value ignored

	return true;
}


void CConnection::Cleanup()
{
	WSACleanup();
	FreeLibrary(s_wsmodule);
}


bool CConnection::CheckModulePt()
{
	const char* funcs[] = { "connect", "closesocket", "send", "select" };

	HMODULE hLibModule = LoadLibraryA("ws2_32.dll");
	if( hLibModule == NULL )
		return true;

	for( size_t i = 0; i < countof(funcs); ++i )
	{
		if( GetProcAddress(hLibModule, funcs[i]) != GetProcAddress(s_wsmodule, funcs[i]) )
		{
			FreeLibrary(hLibModule);
			return false;
		}
	}

	FreeLibrary(hLibModule);
	return true;
}


////////////////////////////////////////


CRagConnection::CRagConnection()
{
	this->CRagConnection::InitPacketMap();
}


bool CRagConnection::SendPacket(int size, const char* buf)
{
	if( m_socket != INVALID_SOCKET )
	{
		if( m_bBlock )
		{
			m_blockQueue.CPacketQueue::InsertData(size, buf);
		}
		else
		{
			m_sendQueue.CPacketQueue::InsertData(size, buf);
			this->CConnection::OnSend();
		}
	}

	return true;
}


bool CRagConnection::RecvPacket(char* buf)
{
	WORD packetHeader;
	if( !m_recvQueue.CPacketQueue::PeekData(2, (char*)&packetHeader) )
		return false;

	WORD packetLength;
	if( this->CRagConnection::IsFixedPacket(packetHeader) )
	{
		packetLength = (WORD)this->CRagConnection::GetPacketSize(packetHeader);
	}
	else
	{
		DWORD headerWithSize;
		if( !m_recvQueue.CPacketQueue::PeekData(4, (char*)&headerWithSize) )
			return false;

		packetLength = headerWithSize >> 16;
	}

	if( !m_recvQueue.CPacketQueue::GetData(packetLength, buf) )
		return false;

	return true;
}


int CRagConnection::GetPacketSize(int packetType)
{
	return ::GetPacketSize(packetType);
}


short CRagConnection::GetPacketType(const char* buf)
{
	return *(short*)buf;
}


bool CRagConnection::IsFixedPacket(int packetType)
{
	return ::IsFixedPacket(packetType);
}


void CRagConnection::InitPacketMap()
{
	::InitPacketLenWithClient();
}


CRagConnection& CRagConnection::instanceR()
{
	static CRagConnection s_RagConnection;
	return s_RagConnection;
}


////////////////////////////////////////
