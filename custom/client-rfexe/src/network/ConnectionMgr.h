#pragma once
#include <map>
class Connection;


class ConnectionMgr
{
public: // public API
	static void Initialize();
	static void Finalize();

public: // internal API
	static int Send(Connection* c, const void* buf, int len);
	static int Recv(Connection* c, void* buf, int len);

private:
	ConnectionMgr();
	~ConnectionMgr();
	static ConnectionMgr& getInstance();
	void Init();
	void Reset();

private:
	// containers for managed connections
	std::map<SOCKET,Connection*> m_mapS2C;
	std::map<Connection*,SOCKET> m_mapC2S;
	Connection* find(SOCKET s);
	SOCKET find(Connection* c);

private:
	// winsock function types
	typedef SOCKET (PASCAL SOCKETFUNC)(int af, int type, int protocol);
	typedef int (PASCAL CLOSEFUNC)(SOCKET s);
	typedef int (PASCAL CONNECTFUNC)(SOCKET s, const struct sockaddr* name, int namelen);
	typedef int (PASCAL ACCEPTFUNC)(SOCKET s, sockaddr* addr, int* addrlen);
	typedef int (PASCAL SELECTFUNC)(int nfds, fd_set* readfds, fd_set* writefds, fd_set* exceptfds, const timeval* timeout);
	typedef int (PASCAL SENDFUNC)(SOCKET s, const void* buf, int len, int flags);
	typedef int (PASCAL RECVFUNC)(SOCKET s, void* buf, int len, int flags);

	// winsock intercept functions
	static SOCKET PASCAL onSocket(int af, int type, int protocol);
	static int PASCAL onClose(SOCKET s);
	static int PASCAL onConnect(SOCKET s, const struct sockaddr* name, int namelen);
	static int PASCAL onAccept(SOCKET s, sockaddr* addr, int* addrlen);
	static int PASCAL onSelect(int nfds, fd_set* readfds, fd_set* writefds, fd_set* exceptfds, const timeval* timeout);
	static int PASCAL onSend(SOCKET s, const void* buf, int len, int flags);
	static int PASCAL onRecv(SOCKET s, void* buf, int len, int flags);

	// pointers to original functions
	SOCKETFUNC* m_wsSocket;
	CLOSEFUNC* m_wsClose;
	CONNECTFUNC* m_wsConnect;
	ACCEPTFUNC* m_wsAccept;
	SELECTFUNC* m_wsSelect;
	SENDFUNC* m_wsSend;
	RECVFUNC* m_wsRecv;
};
