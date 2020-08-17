#pragma once
#include "AsyncDBWork/Effect3rd.h"
#include "AsyncDBWork/NAsyncDBWork.h"


class CEffect3rdUpdateAllADBWork : public NAsyncDBWork
{
public:
	enum enumResult
	{
		RESULT_SUCCESS       = 0,
		RESULT_ERROR_UNKNOWN = 1,
	};

private:
	/* this+ 0 */ //NAsyncDBWork baseclass_0;
	/* this+20 */ enumResult m_Result;
	/* this+24 */ const unsigned long m_GID;
	/* this+28 */ const unsigned long m_AID;
public:
	/* this+32 */ std::vector<Effect3rd::tagEffect3rdDBFmt> m_List;

private:
	virtual bool ExecQuery(NODBCCtrl& in_ODBCCtrl);

public:
	const unsigned long GetAID();
	const unsigned long GetGID();
	const enumResult GetResult();

public:
	CEffect3rdUpdateAllADBWork(const unsigned long in_AID, const unsigned long in_GID);
	virtual ~CEffect3rdUpdateAllADBWork();
};
