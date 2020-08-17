#pragma once
#include "shared/NFileLog.h"


class NTraceLog : public NFileLog
{
public:
	bool isOK() const;
	static bool CreateInstance();
	static void DestroyInstance();
	static NTraceLog* GetObj(); /// @custom

private:
	NTraceLog();
	NTraceLog(const NTraceLog&); // = delete;
	NTraceLog& operator=(const NTraceLog&); // = delete;
	virtual ~NTraceLog();

private:
	/* this+   0 */ //NFileLog baseclass_0;
	/* static    */ static NTraceLog*& m_cpSelf; //TODO
	/* this+2088 */ bool m_bOK;
};
