#pragma once
#include "Network2/StreamManager.h"


/// @see CWUCSStreamManager::ConnectThread
struct WUCS_SVR_INFO
{
	/* this+ 0 */ char m_pszIP[15+1];
	/* this+16 */ char m_pszSecIP[15+1];
	/* this+32 */ WORD m_wPort;
};


class CWUCSStreamManager : public CStreamManager
{
public:
	CWUCSStreamManager();
	virtual ~CWUCSStreamManager();
	bool Connect(const char* szIP, const char* szSecIP, unsigned short wPort, int nWorkerThreadNum, unsigned long dwPingTime);
//	void SwapPrimaryAddress(WUCS_SVR_INFO* pSvrInfo);

private:
	void ConnectThread(void* lpParam);
};
