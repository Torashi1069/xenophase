#pragma once
#include "AsyncDBWork/NAsyncDBWork.h"


class CMercenaryDeleteADBWork : public NAsyncDBWork
{
public:
	enum enumResult
	{
		RESULT_SUCCESS                = 0,
		RESULT_ERROR_UNKNOWN          = 1,
		RESULT_ERROR_MERCENARY_DELETE = 2,
	};

private:
	/* this+ 0 */ //NAsyncDBWork baseclass_0;
	/* this+20 */ enumResult m_Result;
	/* this+24 */ const unsigned long m_GID;
	/* this+28 */ const unsigned long m_AID;
	/* this+32 */ const int m_reason;

public:
	const unsigned long GetAID();
	const unsigned long GetGID();
	const enumResult GetResult();
	const int GetReason();

private:
	virtual bool ExecQuery(NODBCCtrl& in_ODBCCtrl);
	NAsyncDBWork::enumRETURN Delete(NODBCCtrl& in_ODBCCtrl);

public:
	CMercenaryDeleteADBWork(const unsigned long in_AID, const unsigned long in_GID, const int in_reason);
	virtual ~CMercenaryDeleteADBWork();
};
