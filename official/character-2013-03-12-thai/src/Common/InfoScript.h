#pragma once
#include "Common/CriticalSection.h"


class CInfoScript
{
private:
	/* this+ 0 */ //const CInfoScript::`vftable';
	/* this+ 4 */ CCriticalSection m_csInfoScript;
	/* this+28 */ std::map<std::string,std::string> m_mapInfoScript;

public:
	CInfoScript();
	CInfoScript(const char* pszScript);
	virtual ~CInfoScript();
	virtual void Open(const char* pszScript);
	const char* GetInfo(char* lpszColumn);
//	int GetSize();
};
