#pragma once


class CAcceptHandler
{
	struct vtable_t
	{
		int (CAcceptHandler::* OnConnect)(SOCKET s, unsigned long ip); // __purecall
	};

	/* this+0 */ public: //const CAcceptHandler::`vftable';

	public: CAcceptHandler::CAcceptHandler(void);
	public: CAcceptHandler::~CAcceptHandler(void);
	public: virtual int CAcceptHandler::OnConnect(SOCKET s, unsigned long ip) = 0;
};


enum enumIPADDRESSTYPE
{
	PUBLIC_OR_PRIVATE_IP_ADDRESS = 0,
	PUBLIC_IP_ADDRESS            = 1,
	PRIVATE_IP_ADDRESS           = 2,
};


DWORD __cdecl GetLocalIPAddr(int type); // enumIPADDRESSTYPE
DWORD __cdecl GetDWORDIP2(char* lpszIP);
bool __cdecl IsPrivateIPAddr(DWORD dwIP);
