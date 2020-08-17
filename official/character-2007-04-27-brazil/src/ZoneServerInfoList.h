#pragma once
#include "Common/CriticalSection.h"
#include "Common/ServerInfoList.h"
#include "Common/Singleton.h"


struct SZONESERVERINFO
{
	/* this+ 0 */ int m_nSID;
	/* this+ 4 */ BOOL m_bConnect;
	/* this+ 8 */ DWORD m_dwIP;
	/* this+12 */ DWORD m_dwUserCount;
	/* this+16 */ int m_nPort;
	/* this+20 */ DWORD m_dwPrivateIP;
	/* this+24 */ int m_nPrivatePort;
};


class CZoneServerInfoList : public CSingleton<CZoneServerInfoList>
{
public:
//	void AddZoneServerInfo(SZONESERVERINFO*);
	void AddZoneServerInfo(SSERVERINFO* pServerInfo);
	BOOL GetZoneServerInfo(int nSID, SZONESERVERINFO* pZoneServerInfo);
	SZONESERVERINFO* GetZoneServerInfo(int nSID);
//	void SetConnect(int nSID, int bConnect);
//	int GetConnect(int nSID);
//	DWORD GetUserCount(int);
	void SetUserCount(int nSID, int nCount);
	int GetTotalUserCount();
//	DWORD GetIP(int nSID);
	int GetSID(DWORD dwIP);
	BOOL IsZoneServer(DWORD dwIP);

private:
	/* this+ 0 */ //CSingleton<CZoneServerInfoList> baseclass_0;
	/* this+ 0 */ std::vector<SZONESERVERINFO> m_vectorZoneServerInfoList;
	/* this+16 */ CCriticalSection m_csZoneServerInfoList;
};
