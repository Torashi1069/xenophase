#pragma once
#include "Common/CriticalSection.h"
#include "Common/Database.h"


class CBillingDB : public CDatabase
{
public:
	CBillingDB();
	~CBillingDB();
//	int CanLogin(char* szID, unsigned long dwIP, int& nAmountRemain, int& nQuantityRemain);

private:
	/* this+ 0 */ //CDatabase baseclass_0;
	/* this+36 */ CCriticalSection m_csBillingDB;
};
