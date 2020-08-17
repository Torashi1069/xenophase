#pragma once


class CAcceptHandler
{
public:
	struct vtable_t
	{
		int (CAcceptHandler::* OnConnect)(unsigned int s, unsigned long ip); // __purecall
	};

	/* this+0 */ public: //const CAcceptHandler::`vftable';

	public: virtual int CAcceptHandler::OnConnect(unsigned int s, unsigned long ip) = 0;
};


struct _ACCEPT_PARM
{
	/* this+ 0 */ unsigned long ip;
	/* this+ 4 */ short port;
	/* this+ 8 */ int backlog;
	/* this+12 */ unsigned int ipLog;
	/* this+16 */ CAcceptHandler* handler;
};


enum enumIPADDRESSTYPE
{
	PUBLIC_OR_PRIVATE_IP_ADDRESS = 0,
	PUBLIC_IP_ADDRESS            = 1,
	PRIVATE_IP_ADDRESS           = 2,
};


unsigned int __stdcall AcceptThread(void* p);
HOOKED unsigned long __cdecl GetLocalIPAddr(int type); // enumIPADDRESSTYPE
bool __cdecl IsPrivateIPAddr(unsigned long dwIP);
