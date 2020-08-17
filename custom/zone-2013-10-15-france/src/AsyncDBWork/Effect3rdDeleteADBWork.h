#pragma once
#include "AsyncDBWork/NAsyncDBWork.h"


class CEffect3rdDeleteADBWork : public NAsyncDBWork
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
	/* this+32 */ const int m_EffectID;

private:
	virtual bool ExecQuery(NODBCCtrl& in_ODBCCtrl);
	enumRETURN Effect3rd_Delete(NODBCCtrl& in_ODBCCtrl, const int in_GID, const int in_ID);

public:
	const unsigned long GetAID();
	const unsigned long GetGID();
	const enumResult GetResult();

public:
	CEffect3rdDeleteADBWork(const unsigned long in_AID, const unsigned long in_GID, const int in_EffectID);
	virtual ~CEffect3rdDeleteADBWork();
};
