#pragma once
#include "Common/Database.h"


class CPCBangBillingDB : public CDatabase
{
public:
	bool isOK();
	static bool CreateInstance();
	static void DestroyInstance();
	static CPCBangBillingDB* GetObj();

	CPCBangBillingDB();
	virtual ~CPCBangBillingDB();
	bool IsPCBangIP(DWORD dwIP);
	bool SetIPBonusLimit(DWORD in_dwIP);
	bool GetIPBonusLimit(DWORD in_dwIP);
	void DeleteIPBonusLimit(DWORD in_dwIP);

private:
	/* this+ 0 */ //const CPCBangBillingDB::`vftable';
	/* this+ 4 */ //CDatabase baseclass_4;
	/* this+40 */ bool m_bOK;
	/* this+44 */ RTL_CRITICAL_SECTION m_CS;
	/* this+68 */ std::list<DWORD> m_listIPBonusLicenseLimit;
	/* static  */ static CPCBangBillingDB* m_cpSelf;
};
