#pragma once
#include "shared/NFileLog.h"


class CMemorialDungeonFileLog : public NFileLog
{
public:
	bool isOK() const;
	void WriteFmt(const char* in_SourceFileName, const int in_SourceLineNum, int in_hMemorialDungeon, int in_hParty, const char* in_pFmt, ...);

public:
	static bool CreateInstance();
	static void DestroyInstance();
	static CMemorialDungeonFileLog* GetObj(); /// @custom

private:
	CMemorialDungeonFileLog();
	virtual ~CMemorialDungeonFileLog();
	CMemorialDungeonFileLog(CMemorialDungeonFileLog&); // = delete;
	CMemorialDungeonFileLog& operator=(CMemorialDungeonFileLog&); // = delete;

private:
	/* static    */ static CMemorialDungeonFileLog*& m_cpSelf; //TODO
	/* this+   0 */ //NFileLog baseclass_0;
	/* this+2088 */ bool m_bOK;
};
