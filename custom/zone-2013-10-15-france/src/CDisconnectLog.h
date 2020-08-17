#pragma once
#include "shared/NFileLog.h"


class CDisconnectLog : public NFileLog
{
public:
	bool isOK() const;

public:
	static bool CreateInstance();
	static void DestroyInstance();
	static CDisconnectLog* GetObj(); /// @custom

private:
	CDisconnectLog();
	virtual ~CDisconnectLog();
	CDisconnectLog(CDisconnectLog&); // = delete;
	CDisconnectLog& operator=(CDisconnectLog&); // = delete;

private:
	/* static    */ static CDisconnectLog*& m_cpSelf; //TODO
	/* this+   0 */ //NFileLog baseclass_0;
	/* this+2088 */ bool m_bOK;
};
