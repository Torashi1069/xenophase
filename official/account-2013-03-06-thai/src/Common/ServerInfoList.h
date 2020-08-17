#pragma once
#include "Common/CriticalSection.h"
#include "Common/Singleton.h"


struct SSERVERINFO
{
	/* this+ 0 */ int m_nSID;
	/* this+ 4 */ int m_nType;
	/* this+ 8 */ DWORD m_dwIP;
	/* this+12 */ char m_szIP[19+1];
	/* this+32 */ int m_nPort;
	/* this+36 */ int m_nPrimaryDestnation;
	/* this+40 */ int m_nSecondDestnation;
	/* this+44 */ char m_szName[24+1];
};


class CServerInfoList : public CSingleton<CServerInfoList>
{
public:
	CServerInfoList();
	~CServerInfoList();
//	int GetServerInfo(int, SSERVERINFO*, ...);
	BOOL GetServerInfo(SSERVERINFO* pServerInfo, int nSID);
	void AddServerInfo(SSERVERINFO* pServerInfo);
	int GetIPType(DWORD dwIP);
//	bool GetIPType(DWORD dwIP, int ServerType);
//	int GetPort(int);
//	const std::vector<SSERVERINFO> GetSIDList(const int, const int);
	int GetSID(DWORD dwIP, int nType);
	int GetSID(int nPrimaryDestnation, int* pnSID);
//	bool IsIPType(DWORD, int);
//	DWORD GetIP(int);
//	int GetAllServerInfo(int, SSERVERINFO*);

private:
	/* this+ 0 */ //CSingleton<CServerInfoList> baseclass_0;
	/* this+ 0 */ CCriticalSection m_csServerInfoList;
	/* this+24 */ std::vector<SSERVERINFO> m_vectorServerInfoList;
};
