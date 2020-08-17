#include "Connection.h"
#include "ConnectionMgr.h"


Connection::Connection()
{
	m_stream = NULL;
}


Connection::~Connection()
{
	delete m_stream;
	m_stream = NULL;
}


void Connection::SetStream(CStream* stream)
{
	m_stream = stream;
}


int Connection::OnRecv(BYTE* buffer, int capacity)
{
	// receive data (using caller's buffer as scratch space)
	int inbytes = ConnectionMgr::Recv(this, buffer, capacity);
	if( inbytes == SOCKET_ERROR )
	{
		if( WSAGetLastError() != WSAEWOULDBLOCK && WSAGetLastError() != WSAENOTCONN )
			return SOCKET_ERROR;

		inbytes = 0; // adjust value
	}

	// feed client recv into stream parser
	m_stream->RecvIn(buffer, inbytes);

	// obtain processed packets
	m_stream->RecvOut(m_recvbuf);

	if( m_recvbuf.size() == 0 )
	{// nothing yet, try again later
		WSASetLastError(WSAEWOULDBLOCK);
		return SOCKET_ERROR;
	}

	// move data to caller's buffer
	size_t size = min(m_recvbuf.size(), size_t(capacity));
	std::copy(m_recvbuf.begin(), m_recvbuf.begin() + size, buffer);
	m_recvbuf.erase(m_recvbuf.begin(), m_recvbuf.begin() + size);

	WSASetLastError(ERROR_SUCCESS);
	return size;
}


int Connection::OnSend(const BYTE* buffer, int size)
{
	// feed client send into stream parser
	m_stream->SendIn(buffer, size);

	// obtain processed packets
	m_stream->SendOut(m_sendbuf);

	// perform the actual send
	if( m_sendbuf.size() != 0 )
	{
		int outbytes = ConnectionMgr::Send(this, &m_sendbuf.front(), m_sendbuf.size());
		if( outbytes == SOCKET_ERROR )
		{
			if( WSAGetLastError() != WSAEWOULDBLOCK && WSAGetLastError() != WSAENOTCONN )
				return SOCKET_ERROR;

			outbytes = 0; // adjust value
		}

		m_sendbuf.erase(m_sendbuf.begin(), m_sendbuf.begin() + outbytes);
	}

	WSASetLastError(ERROR_SUCCESS);
	return size;
}


bool Connection::isRecvSignaled()
{
	return ( m_recvbuf.size() != 0 );
}


bool Connection::isSendSignaled()
{
	return ( m_sendbuf.size() != 0 );
}
