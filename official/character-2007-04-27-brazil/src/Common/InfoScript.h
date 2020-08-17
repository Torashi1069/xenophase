#pragma once
#include "Common/CriticalSection.h"


class CInfoScript
{
private:
	/* this+ 0 */ CCriticalSection m_csInfoScript;
	/* this+24 */ std::map<std::string,std::string> m_mapInfoScript;

public:
	CInfoScript();
	CInfoScript(const char* pszScript);
	~CInfoScript();
	void Open(const char* pszScript);
	const char* GetInfo(char* lpszColumn);
};
