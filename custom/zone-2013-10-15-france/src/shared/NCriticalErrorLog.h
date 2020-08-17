#pragma once
#include "shared/NFileLog.h"


class NCriticalErrorLog : public NFileLog
{
public:
	bool isOK() const;
	static bool CreateInstance();
	static void DestroyInstance();
	static NCriticalErrorLog* GetObj(); /// @custom

private:
	NCriticalErrorLog();
	NCriticalErrorLog(const NCriticalErrorLog&); // = delete;
	NCriticalErrorLog& operator=(const NCriticalErrorLog&); // = delete;
	virtual ~NCriticalErrorLog();

private:
	/* this+   0 */ //NFileLog baseclass_0;
	/* static    */ static NCriticalErrorLog*& m_cpSelf; //TODO
	/* this+2088 */ bool m_bOK;
};
