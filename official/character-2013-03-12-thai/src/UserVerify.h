#pragma once
#include "Common/CriticalSection.h"
#include "Common/Singleton.h"


struct SUSERVERIFY
{
	/* this+0 */ DWORD m_dwAID;
	/* this+4 */ DWORD m_dwVerifyTime;
	/* this+8 */ DWORD m_dwLastPingTime;
};


class CUserVerify : public CSingleton<CUserVerify>
{
public:
	CUserVerify();
	~CUserVerify();
	void StartThread();
	void EndThread();
	void UpdateUserVerify(DWORD dwAID, DWORD dwVerifyTime);
	void DeleteUserVerify(DWORD dwAID);
	void threadUserVerify(void* pVoid);
	BOOL Get(DWORD dwAID, SUSERVERIFY& UserVerifyInfo);

private:
	/* this+   0 */ //CSingleton<CUserVerify> baseclass_0;
	/* this+   0 */ std::list<SUSERVERIFY> m_listUserVerify[100];
	/* this+1200 */ CCriticalSection m_csUserVerify[100];
	/* this+3600 */ bool m_bThread;
};
