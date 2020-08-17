#include "Connection.h"
#include "ConnectionMgr.h"
#include "Version.h"


ConnectionMgr::ConnectionMgr()
: m_wsSocket(NULL), m_wsClose(NULL), m_wsConnect(NULL), m_wsSelect(NULL), m_wsSend(NULL), m_wsRecv(NULL)
{
}


ConnectionMgr::~ConnectionMgr()
{
}


ConnectionMgr& ConnectionMgr::getInstance()
{
	static ConnectionMgr s_mgr;
	return s_mgr;
}


void ConnectionMgr::Init()
{
	// deploy winsock hooks
	HookDB::DB().Hook("socket", &::socket, &onSocket);
	HookDB::DB().Hook("closesocket", &::closesocket, &onClose);
	HookDB::DB().Hook("connect", &::connect, &onConnect);
	HookDB::DB().Hook("accept", &::accept, &onAccept);
	HookDB::DB().Hook("select", &::select, &onSelect);
	HookDB::DB().Hook("send", &::send, &onSend);
	HookDB::DB().Hook("recv", &::recv, &onRecv);
	m_wsSocket  = (SOCKETFUNC*)HookDB::DB().Get("socket")->original();
	m_wsClose   = (CLOSEFUNC*)HookDB::DB().Get("closesocket")->original();
	m_wsConnect = (CONNECTFUNC*)HookDB::DB().Get("connect")->original();
	m_wsAccept  = (ACCEPTFUNC*)HookDB::DB().Get("accept")->original();
	m_wsSelect  = (SELECTFUNC*)HookDB::DB().Get("select")->original();
	m_wsSend    = (SENDFUNC*)HookDB::DB().Get("send")->original();
	m_wsRecv    = (RECVFUNC*)HookDB::DB().Get("recv")->original();
}


void ConnectionMgr::Reset()
{
	for( std::map<SOCKET,Connection*>::iterator it = m_mapS2C.begin(); it != m_mapS2C.end(); ++it )
		delete it->second;

	m_mapS2C.clear();
	m_mapC2S.clear();

	// undo winsock hooks
	HookDB::DB().Get("socket")->unhook();
	HookDB::DB().Get("closesocket")->unhook();
	HookDB::DB().Get("connect")->unhook();
	HookDB::DB().Get("accept")->unhook();
	HookDB::DB().Get("select")->unhook();
	HookDB::DB().Get("send")->unhook();
	HookDB::DB().Get("recv")->unhook();
	m_wsSocket  = NULL;
	m_wsClose   = NULL;
	m_wsConnect = NULL;
	m_wsAccept  = NULL;
	m_wsSelect  = NULL;
	m_wsSend    = NULL;
	m_wsRecv    = NULL;
}


Connection* ConnectionMgr::find(SOCKET s)
{
	std::map<SOCKET,Connection*>::iterator it = m_mapS2C.find(s);
	return ( it != m_mapS2C.end() ) ? it->second : NULL;
}


SOCKET ConnectionMgr::find(Connection* c)
{
	std::map<Connection*,SOCKET>::iterator it = m_mapC2S.find(c);
	return ( it != m_mapC2S.end() ) ? it->second : INVALID_SOCKET;
}


SOCKET PASCAL ConnectionMgr::onSocket(int af, int type, int protocol)
{
	ConnectionMgr& self = getInstance();

	return self.m_wsSocket(af, type, protocol);
}


int PASCAL ConnectionMgr::onClose(SOCKET s)
{
	ConnectionMgr& self = getInstance();

	Connection* c = self.find(s);
	if( c != NULL )
	{
		self.m_mapS2C.erase(s);
		self.m_mapC2S.erase(c);
		delete c;
	}

	return self.m_wsClose(s);
}


int PASCAL ConnectionMgr::onConnect(SOCKET s, const struct sockaddr* name, int namelen)
{
	ConnectionMgr& self = getInstance();

	int result = self.m_wsConnect(s, name, namelen);
	if( result == SOCKET_ERROR && WSAGetLastError() != WSAEWOULDBLOCK )
		return SOCKET_ERROR; // failure.
	DWORD err = WSAGetLastError();

	Connection* c = new Connection();
	CStream* strm = new CStream(LOCALVER(), REMOTEVER(s));
	c->SetStream(strm);

	self.m_mapS2C[s] = c;
	self.m_mapC2S[c] = s;

	WSASetLastError(err);
	return result;
}


int PASCAL ConnectionMgr::onAccept(SOCKET s, sockaddr* addr, int* addrlen)
{
	ConnectionMgr& self = getInstance();

	//TODO
	return self.m_wsAccept(s, addr, addrlen);
}


int PASCAL ConnectionMgr::onSelect(int nfds, fd_set* readfds, fd_set* writefds, fd_set* exceptfds, const timeval* timeout)
{
	ConnectionMgr& self = getInstance();

	//TODO: scan for signaled connections and use zero timeout if any are found
	int result = self.m_wsSelect(nfds, readfds, writefds, exceptfds, timeout);
	if( result == SOCKET_ERROR )
		return SOCKET_ERROR; // failure.

	for( std::map<SOCKET,Connection*>::iterator it = self.m_mapS2C.begin(); it != self.m_mapS2C.end(); ++it )
	{
		SOCKET s = it->first;
		Connection* c = it->second;

		if( readfds != NULL && c->isRecvSignaled() && !FD_ISSET(s, readfds) )
		{// forced recv
			FD_SET(s, readfds);
			++result;
		}

		if( writefds != NULL && c->isSendSignaled() && !FD_ISSET(s, writefds) )
		{// forced send
			FD_SET(s, writefds);
			++result;
		}
	}

	return result;
}


int PASCAL ConnectionMgr::onSend(SOCKET s, const void* buf, int len, int flags)
{
	ConnectionMgr& self = getInstance();

	Connection* c = self.find(s);
	if( c == NULL ) // not a managed connection
		return self.m_wsSend(s, buf, len, flags);

	return c->OnSend((const BYTE*)buf, len);
}


int PASCAL ConnectionMgr::onRecv(SOCKET s, void* buf, int len, int flags)
{
	ConnectionMgr& self = getInstance();

	Connection* c = self.find(s);
	if( c == NULL ) // not a managed connection
		return self.m_wsRecv(s, buf, len, flags);

	return c->OnRecv((BYTE*)buf, len);
}


void ConnectionMgr::Initialize()
{
	ConnectionMgr& self = getInstance();

	return self.Init();
}


void ConnectionMgr::Finalize()
{
	ConnectionMgr& self = getInstance();

	return self.Reset();
}


int ConnectionMgr::Send(Connection* c, const void* buf, int len)
{
	ConnectionMgr& self = getInstance();

	SOCKET s = self.find(c);
	return self.m_wsSend(s, buf, len, 0);
}


int ConnectionMgr::Recv(Connection* c, void* buf, int len)
{
	ConnectionMgr& self = getInstance();

	SOCKET s = self.find(c);
	return self.m_wsRecv(s, buf, len, 0);
}
