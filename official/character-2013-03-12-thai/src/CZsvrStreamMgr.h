#pragma once
#include "Common/NSystem/NIPAddr.h"
#include "Network3/StreamManager.h"


class CZsvrStreamMgr : public CStreamManager
{
public:
	CZsvrStreamMgr();
	virtual ~CZsvrStreamMgr();
	bool Listen(WORD port, int nBackLog, DWORD dwPingTime, DWORD dwListenIP);
	NIPAddr GetListenIPAddr() const;
	int GetListenPortNum() const;

private:
	/* this+ 0 */ //CStreamManager baseclass_0;
	/* this+68 */ NIPAddr m_ListenIPAddr;
	/* this+76 */ int m_ListenPortNum;
};
