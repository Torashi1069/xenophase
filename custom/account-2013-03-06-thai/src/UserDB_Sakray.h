#pragma once
#include "Common/CriticalSection.h"
#include "Common/Database.h"


class CSakrayUserDB : public CDatabase
{
public:
//	int IsUser(int);

private:
	/* this+ 0 */ //CDatabase baseclass_0;
	/* this+36 */ CCriticalSection m_csUserDB;
};
