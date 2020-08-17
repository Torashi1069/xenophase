#pragma once
#include "Common/Singleton.h"


class CPreventNameList : public CSingleton<CPreventNameList>
{
public:
	CPreventNameList();
	~CPreventNameList();
//	void InitPreventNameList();
	BOOL IsPreventName(char* pszName);

private:
	/* this+0 */ //CSingleton<CPreventNameList> baseclass_0;
	/* this+0 */ int m_nCount;
	/* this+4 */ char m_szPreventName[10000][26];
};
