#pragma once
#include "AsyncDBWork/NAsyncDBWork.h"


class CElementalDeleteADBWork : public NAsyncDBWork
{
public:
	enum enumResult
	{
		RESULT_SUCCESS                = 0,
		RESULT_ERROR_UNKNOWN          = 1,
		RESULT_ERROR_ELEMENTAL_DELETE = 2,
	};

public:
	unsigned long GetGID();
	unsigned long GetAID(); //TODO
	enumResult GetResult();

private:
	virtual bool ExecQuery(NODBCCtrl& in_ODBCCtrl);
	NAsyncDBWork::enumRETURN Delete(NODBCCtrl& in_ODBCCtrl);

public:
	CElementalDeleteADBWork(const unsigned long in_AID, const unsigned long in_GID);
	virtual ~CElementalDeleteADBWork();

private:
	/* this+ 0 */ //NAsyncDBWork baseclass_0;
	/* this+20 */ enumResult m_Result;
	/* this+24 */ const unsigned long m_GID;
};
