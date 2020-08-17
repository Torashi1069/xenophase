#pragma once
#include "shared/NFileLog.h"


class CProgrammerSupportLog : public NFileLog
{
public:
	bool isOK() const;
	static bool CreateInstance();
	static void DestroyInstance();
	static CProgrammerSupportLog* GetObj(); /// @custom

private:
	CProgrammerSupportLog();
	virtual ~CProgrammerSupportLog();

private:
	CProgrammerSupportLog(CProgrammerSupportLog&); // = delete;
	CProgrammerSupportLog& operator=(CProgrammerSupportLog&); // = delete;

private:
	/* static    */ static CProgrammerSupportLog*& m_cpSelf; //TODO
	/* this+   0 */ //NFileLog baseclass_0;
	/* this+2088 */ bool m_bOK;
};
