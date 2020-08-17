#pragma once
#include "AsyncDBWork/NAsyncDBWork.h"


class CDeleteCoupleADBWork : public NAsyncDBWork
{
public:
	enum enumResult
	{
		RESULT_SUCCESS       = 0,
		RESULT_ERROR_UNKNOWN = 1,
	};

public:
	const enumResult GetResult();
	const unsigned long GetGID();

private:
	/* this+ 0 */ //NAsyncDBWork baseclass_0;
	/* this+20 */ enumResult m_Result;
	/* this+24 */ const unsigned long m_GID;

private:
	virtual bool ExecQuery(NODBCCtrl& in_CharacterODBCCtrl);

public:
	CDeleteCoupleADBWork(const unsigned long in_AID, const unsigned long in_GID);
	virtual ~CDeleteCoupleADBWork();
};
