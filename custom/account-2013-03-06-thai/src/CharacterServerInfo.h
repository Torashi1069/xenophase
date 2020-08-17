#pragma once
#include "Common/CriticalSection.h"
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
//	void AddCharacterServerInfo(int, DWORD, int, char*, WORD);
	void AddCharacterServerInfo(SSERVERINFO* pServerInfo, WORD wState);
	void SetUserCount(int nSID, WORD wCount);
	SERVER_ADDR* GetCharacterServerInfo(int* pnCount);
//	SERVER_ADDR** GetCharacterServerInfo_thai(int*);
//	const int GetBalkyrieCharSvrOffset();

private:
	/* this+  0 */ int m_nSID[10];
	/* this+ 40 */ SERVER_ADDR m_characterServerInfo[10];
	/* this+360 */ int m_nOffset;
	/* this+364 */ CCriticalSection m_csCharSvrInfo;
	/* this+388 */ int m_nBalkyrieCharSvrOffset;
	/* this+392 */ int m_nCountCharSvr_thai;
	/* this+396 */ SERVER_ADDR* m_arPtrCharacterServerInfo_thai[10];
};
