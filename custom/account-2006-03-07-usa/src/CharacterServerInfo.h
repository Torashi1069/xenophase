#pragma once
#include "Common/ServerInfoList.h" // struct SSERVERINFO


enum SERVERSTATE
{
	SERVERSTATE_NORMAL  = 0,
	SERVERSTATE_INSPECT = 1,
	SERVERSTATE_ADULT   = 2,
	SERVERSTATE_PAY     = 3,
	SERVERSTATE_FREE    = 4,
};


enum SERVERPROPERTY
{
	SERVERPROPERTY_NONE = 0,
	SERVERPROPERTY_NEW  = 1,
};


struct SERVER_ADDR
{
	/* this+ 0 */ DWORD ip;
	/* this+ 4 */ short port;
	/* this+ 6 */ unsigned char name[20];
	/* this+26 */ WORD usercount;
	/* this+28 */ WORD state; // enum SERVERSTATE
	/* this+30 */ WORD property; // enum SERVERPROPERTY
};


class CCharacterServerInfo
{
public:
	CCharacterServerInfo();
	void AddCharacterServerInfo(SSERVERINFO* pServerInfo, WORD wState);
//	void AddCharacterServerInfo(int, DWORD, int, char*);
	void SetUserCount(int nSID, WORD wCount);
	SERVER_ADDR* GetCharacterServerInfo(int* pnCount);

private:
	/* this+  0 */ int m_nSID[20];
	/* this+ 80 */ SERVER_ADDR m_characterServerInfo[20];
	/* this+720 */ int m_nOffset;
};
