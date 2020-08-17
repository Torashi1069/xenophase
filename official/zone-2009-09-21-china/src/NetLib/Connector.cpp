#include "NetLib/Connector.h"
#include "shared.h" // Trace
#include "globals.hpp"


CConnector::CConnector(void)
{
}


CConnector::~CConnector(void)
{
}


hook_method<SOCKET (CConnector::*)(const Addr& addr)> CConnector::_Connect(SERVER, "CConnector::Connect");
SOCKET CConnector::Connect(const Addr& addr)
{
	return (this->*_Connect)(addr);

	SOCKET s = socket(AF_INET, SOCK_STREAM, 0);
	if( s == INVALID_SOCKET )
	{
		Trace("socket() failed : %d", WSAGetLastError());
		return INVALID_SOCKET;
	}

	sockaddr_in sa = {};
	sa.sin_family = AF_INET;
	sa.sin_addr.s_addr = addr.ip;
	sa.sin_port = htons(addr.port);

	char buf[16];
	addr.GetIp(buf);

	Trace("connecting to server IP:%s, port:%d\n", buf, addr.port);

	if( connect(s, (sockaddr*)&sa, sizeof(sa)) == SOCKET_ERROR )
	{
		Trace("connecting to server(IP:%s, port:%d) failed: %d\n", buf, addr.port, WSAGetLastError());
		return INVALID_SOCKET;
	}

	return s;
}
