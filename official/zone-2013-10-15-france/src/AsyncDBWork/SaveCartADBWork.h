#pragma once
#include "AsyncDBWork/NAsyncDBWork.h"


class CSaveCartADBWork : public NAsyncDBWork
{
public:
	enum enumResult
	{
		RESULT_SUCCESS         = 0,
		RESULT_ERROR_UNKNOWN   = 1,
		RESULT_ERROR_SAVE_CART = 2,
	};

private:
	/* this+    0 */ //NAsyncDBWork baseclass_0;
	/* this+   20 */ enumResult m_Result;
	/* this+   24 */ unsigned long m_GID;
	/* this+   28 */ unsigned long m_AID;
public:
	/* this+   32 */ unsigned char m_Data[16300];
	/* this+16332 */ int m_Length;

public:
	const unsigned long GetAID() const;
	const unsigned long GetGID() const;
	const enumResult GetResult() const;

private:
	virtual bool ExecQuery(NODBCCtrl& in_ODBCCtrl);

public:
	void Init(const unsigned long in_AID, const unsigned long in_GID);

private:
	CSaveCartADBWork();
	virtual ~CSaveCartADBWork();

	template<typename T> friend class CObjectRecycleMgr;
};
