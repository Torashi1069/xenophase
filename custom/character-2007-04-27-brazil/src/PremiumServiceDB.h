#pragma once
#include "Common/CriticalSection.h"
#include "Common/Database.h"
#include "Common/Singleton.h"


struct SExtraExp
{
	/* this+0 */ float fExp1;
	/* this+4 */ float fExp2;
	/* this+8 */ float fdrp;
};


class CPremiumServiceDB : public CDatabase, public CSingleton<CPremiumServiceDB>
{
private:
	/* this+   0 */ //CDatabase baseclass_0;
	/* this+2056 */ //CSingleton<CPremiumServiceDB> baseclass_2056;
	/* this+2056 */ CCriticalSection m_csPremiumServiceDB;

public:
	CPremiumServiceDB();
	~CPremiumServiceDB();
//	int IsRegistedAddress(char* szIP);
	BOOL GetExtraExpInfo(char* szIP, SExtraExp* pExraExp);
//	float TestFloat(char* szIP);
};
