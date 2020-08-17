#pragma once
#include "Common/CriticalSection.h"
#include "Common/ServerInfoList.h"
#include "Common/Singleton.h"


typedef struct tagSZONESERVERINFO
{
	/* this+ 0 */ int m_nSID;
	/* this+ 4 */ BOOL m_bConnect;
	/* this+ 8 */ DWORD m_dwIP;
	/* this+12 */ DWORD m_dwUserCount;
	/* this+16 */ int m_nPort;
	/* this+20 */ DWORD m_dwPrivateIP;
	/* this+24 */ int m_nPrivatePort;
	/* this+28 */ unsigned int m_MaxConcurrentPlayerNum;
	/* this+32 */ unsigned int m_UpdateCnt;
	/* this+36 */ bool m_bOverPopulation;

//	public: SZONESERVERINFO();
} SZONESERVERINFO;


class CZoneServerInfoList : public CSingleton<CZoneServerInfoList>
{
public:
//	void AddZoneServerInfo(SZONESERVERINFO*);
	void AddZoneServerInfo(SSERVERINFO* pServerInfo);
	BOOL GetZoneServerInfo(int nSID, SZONESERVERINFO* pZoneServerInfo);
	SZONESERVERINFO* GetZoneServerInfo(int nSID); //TODO: private
//	unsigned int SetConnect(int, int);
//	void SetInfo(const int, const unsigned int);
//	bool IsAcceptPlayer(const int);
//	int GetConnect(int);
//	DWORD GetUserCount(int);
	int GetTotalUserCount();
//	DWORD GetIP(int nSID);
	int GetSID(DWORD in_dwIP, int in_nPort);
	BOOL IsZoneServer(DWORD in_dwIP, int in_nPort);
	void SetUserCount(int nSID, int nCount);

private:
	/* this+ 0 */ //CSingleton<CZoneServerInfoList> baseclass_0;
	/* this+ 0 */ std::vector<SZONESERVERINFO> m_vectorZoneServerInfoList;
	/* this+16 */ CCriticalSection m_csZoneServerInfoList;
};
