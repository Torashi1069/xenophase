#pragma once
#include <WS2tcpip.h>
#include <MSTcpIP.h>


class SocketAddress
{
public:
	// Default constructor.
	SocketAddress() : m_addr()
	{
	}

	/// Initialize from a standard sockaddr-compatible structure.
	/// @param len Actual size of the sockaddr structure (-1 to autodetect).
	SocketAddress(const sockaddr* sa, int len = -1) : m_addr()
	{
		this->fromaddr(sa, len);
	}

	/// Initialize from a SOCKET handle.
	/// @param remote Whether to use the address of the remote or local endpoint.
	SocketAddress(const SOCKET s, bool remote = true) : m_addr()
	{
		this->fromsock(s, remote);
	}

	/// Initialize from a character string containing a socket address.
	/// Supported formats: IPv4 address:port, IPv6 [address]:port
	SocketAddress(const char* str) : m_addr()
	{
		this->fromstr(str);
	}

	/// Initialize from a standard sockaddr-compatible structure.
	/// @param len Actual size of the sockaddr structure (-1 to autodetect).
	bool fromaddr(const sockaddr* sa, int len = -1)
	{
		// very crude and limited detection of address size
		if( len == -1 ) switch( sa->sa_family ) {
		case AF_INET: len = sizeof(sockaddr_in); break;
		case AF_INET6: len = sizeof(sockaddr_in6); break;
		default: return false; // unsupported address type
		}

		if( len < 0 || len > sizeof(m_addr) )
			return false; // should not happen

		memcpy(&m_addr, sa, len);
		return true;
	}

	/// Initialize from a SOCKET handle.
	/// @param remote Whether to use the address of the remote or local endpoint.
	bool fromsock(const SOCKET s, bool remote = true)
	{
		sockaddr_storage ss;
		int sslen = sizeof(ss);

		if( remote )
		{// remote endpoint
			if( getpeername(s, (sockaddr*)&ss, &sslen) != 0 )
				return false;
		}
		else
		{// local endpoint
			if( getsockname(s, (sockaddr*)&ss, &sslen) != 0 )
				return false;
		}

		return this->fromaddr((sockaddr*)&ss, sslen);
	}

	/// Initialize from a character string containing a socket address.
	bool fromstr(const char* str)
	{
		// local copy because the parser is non-const
		char strbuf[255+1];
		if( sprintf(strbuf, "%.255s", str) == 255 )
			return false; // too long

		// very crude and limited detection of address type
		INT af = ( strbuf[0] == '[' ) ? AF_INET6 : AF_INET;

		INT addrlen = sizeof(m_addr);
		return ( WSAStringToAddressA(strbuf, af, NULL, (sockaddr*)&m_addr, &addrlen) == 0 );
	}

	/// Format socket address into character string.
	bool tostr(char* str, size_t size) const
	{
		DWORD len = size;
		return ( WSAAddressToStringA((sockaddr*)&m_addr, sizeof(m_addr), NULL, str, &len) == 0 );
	}

	/// Test if two addresses are the same.
	/// Supported address types: IPv4, IPv6.
	bool operator ==(const SocketAddress& addr) const
	{
		if( !( m_addr.ss_family == addr.m_addr.ss_family ) )
			return false; // address family mismatch

		if( m_addr.ss_family == AF_INET )
		{// IPv4
			const sockaddr_in& self = reinterpret_cast<const sockaddr_in&>(m_addr);
			const sockaddr_in& other = reinterpret_cast<const sockaddr_in&>(addr.m_addr);

			if( !( IN4_ADDR_EQUAL(&self.sin_addr, &other.sin_addr) || IN4_IS_ADDR_UNSPECIFIED(&self.sin_addr) || IN4_IS_ADDR_UNSPECIFIED(&other.sin_addr) ) )
				return false; // address mismatch

			if( !( self.sin_port == other.sin_port ) )
				return false; // port mismatch
		}
		else
		if( m_addr.ss_family == AF_INET6 )
		{// IPv6
			const sockaddr_in6& self = reinterpret_cast<const sockaddr_in6&>(m_addr);
			const sockaddr_in6& other = reinterpret_cast<const sockaddr_in6&>(addr.m_addr);

			if( !( IN6_ADDR_EQUAL(&self.sin6_addr, &other.sin6_addr) || IN6_IS_ADDR_UNSPECIFIED(&self.sin6_addr) || IN6_IS_ADDR_UNSPECIFIED(&other.sin6_addr) ) )
				return false; // address mismatch

			if( !( self.sin6_port == other.sin6_port ) )
				return false; // port mismatch
		}
		else
		{// unsupported address type
			return false;
		}

		return true; // success.
	}

private:
	// Portable socket structure (RFC 2553).
	sockaddr_storage m_addr;
};
