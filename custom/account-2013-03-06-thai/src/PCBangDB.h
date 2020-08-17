#pragma once
#include "Common/CriticalSection.h"
#include "Common/Database.h"


class CPCBangDB : public CDatabase
{
private:
	/* this+ 0 */ //CDatabase baseclass_0;
	/* this+36 */ int m_nCurrPos;
	/* this+40 */ std::vector<DWORD> m_vecPCBangIPListBuffer[2];
	/* this+72 */ CCriticalSection m_cs;

public:
//	CPCBangDB();
//	~CPCBangDB();
//	bool IsPCBangIP(unsigned long);
//	int IsPCBangIP(const char*, int);
//	int InitPCBangIPList();
//	int ReloadPCBangIPList();
};
