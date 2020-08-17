#pragma once
#include "shared/NFileLog.h"


class CVTBLErrorLog : public NFileLog
{
public:
	bool isOK() const;
	static bool CreateInstance();
	static void DestroyInstance();
	static CVTBLErrorLog* GetObj(); /// @custom

private:
	CVTBLErrorLog();
	CVTBLErrorLog(const CVTBLErrorLog&); // = delete;
	CVTBLErrorLog& operator=(const CVTBLErrorLog&); // = delete;
	virtual ~CVTBLErrorLog();

private:
	/* static    */ static CVTBLErrorLog*& m_cpSelf; //TODO
	/* this+   0 */ //NFileLog baseclass_0;
	/* this+2088 */ bool m_bOK;
};
