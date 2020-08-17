#pragma once
#include "Common/CriticalSection.h"
#include "Common/Database.h"


class CBillingDB : public CDatabase
{
public:
	CBillingDB(int idx);
	~CBillingDB();
//	int CanLogin(char* szID, DWORD dwIP, int& nAmountRemain, int& nQuantityRemain);

private:
	/* this+   0 */ //CDatabase baseclass_0;
	/* this+2056 */ CCriticalSection m_csBillingDB;
	/* this+2080 */ int m_idx;
};
