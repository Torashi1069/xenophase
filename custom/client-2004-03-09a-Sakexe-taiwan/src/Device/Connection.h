#pragma once
#include "Device/PacketQueue.h"


typedef int (WSAAPI SENDFUNC)(SOCKET s, const char* buf, int len, int flags);
typedef int (WSAAPI RECVFUNC)(SOCKET s, char* buf, int len, int flags);


struct ServerAddress
{
	/* this+ 0 */ char ip[16];
	/* this+16 */ int port;
};


class CConnection
{
public:
	CConnection();
	virtual ~CConnection();

public:
	bool Connect(const ServerAddress* addr);
	bool Poll();
	void Disconnect();
	void Send(int size, const char* buf);
	int Recv(char* buf, int size, bool mustRecv);
	void ResetQueue();
	void SetBlock(bool bBlock);
	void SetDelay(DWORD dwDelay);

protected:
	bool OnSend();
	bool OnRecv();
	void OnConnect();
	void OnClose();

public:
	static bool Startup();
	static void Cleanup();

protected:
	/* this+ 0 */ //const CConnection::`vftable';
	/* this+ 4 */ SOCKET m_socket;
	/* this+ 8 */ SOCKADDR_IN m_addr;
	/* this+24 */ bool m_bBlock;
	/* this+28 */ DWORD m_dwTime;
	/* this+32 */ CPacketQueue m_sendQueue;
	/* this+60 */ CPacketQueue m_recvQueue;
	/* this+88 */ CPacketQueue m_blockQueue;
private:
	/* static  */ static WSADATA& s_wsaData; //TODO
	/* static  */ static HINSTANCE& s_wsmodule; //TODO
	/* static  */ static SENDFUNC*& s_wsSend; //TODO
	/* static  */ static RECVFUNC*& s_wsRecv; //TODO
};


class CRagConnection : public CConnection
{
public:
	CRagConnection();
//	virtual ~CRagConnection();

public:
	bool SendPacket(int size, const char* buf);
	bool RecvPacket(char* buf);
	int GetPacketSize(int packetType);
	short GetPacketType(const char* buf);

protected:
	bool IsFixedPacket(int packetType);
	void InitPacketMap();

protected:
	/* this+  0 */ //CConnection baseclass_0;
	/* this+116 */ mystd::map<int,int> m_packetLenMap;
};
