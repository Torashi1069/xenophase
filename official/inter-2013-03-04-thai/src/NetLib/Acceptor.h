#pragma once


enum enumIPADDRESSTYPE
{
	PUBLIC_OR_PRIVATE_IP_ADDRESS = 0,
	PUBLIC_IP_ADDRESS            = 1,
	PRIVATE_IP_ADDRESS           = 2,
};


DWORD GetLocalIPAddr(int type); // enumIPADDRESSTYPE
DWORD GetDWORDIP2(char* lpszIP);
bool IsPrivateIPAddr(DWORD dwIP);


class CAcceptHandler
{
public:
	CAcceptHandler();
	~CAcceptHandler();

public:
	virtual int OnConnect(SOCKET s, DWORD ip) = 0;
};


struct _ACCEPT_PARM
{
	/* this+ 0 */ DWORD ip;
	/* this+ 4 */ short port;
	/* this+ 8 */ int backlog;
	/* this+12 */ unsigned int ipLog;
	/* this+16 */ CAcceptHandler* handler;
};
