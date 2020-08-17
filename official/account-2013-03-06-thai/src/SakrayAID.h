#pragma once
#include "Common/CriticalSection.h"


class CSakrayAID
{
private:
	/* this+       0 */ bool m_bSakrayAID[10000000];
	/* this+10000000 */ CCriticalSection m_cs;

public:
	CSakrayAID()
	{
		m_cs.CCriticalSection::Enter();
		memset(m_bSakrayAID, 0, sizeof(m_bSakrayAID));
		m_cs.CCriticalSection::Leave();
	}

//	void InsertAID(int AID);
//	bool IsSakrayAID(int AID);
};
