#pragma once
#include "AsyncDBWork/NAsyncDBWork.h"


class CLoadCartADBWork : public NAsyncDBWork
{
public:
	enum enumResult
	{
		RESULT_SUCCESS                = 0,
		RESULT_ERROR_UNKNOWN          = 1,
		RESULT_ERROR_LOAD_CART        = 2,
		RESULT_ERROR_LOAD_CART_INSERT = 3,
	};

private:
	/* this+    0 */ //NAsyncDBWork baseclass_0;
	/* this+   20 */ unsigned long m_AID;
	/* this+   24 */ unsigned long m_GID;
	/* this+   28 */ enumResult m_Result;
public:
	/* this+   32 */ unsigned char m_Data[16300];
	/* this+16332 */ int m_Length;
	/* this+16336 */ int m_SKLevel;

public:
	const enumResult GetResult() const;
	const unsigned long GetGID() const;
	const unsigned long GetAID() const;

private:
	virtual bool ExecQuery(NODBCCtrl& in_ODBCCtrl);
	enumRETURN LoadCart(NODBCCtrl& in_ODBCCtrl);
	enumRETURN InsertCart(NODBCCtrl& in_ODBCCtrl);

public:
	void Init(const unsigned long in_AID, const unsigned long in_GID, const int in_SKLevel);

private:
	CLoadCartADBWork();
	virtual ~CLoadCartADBWork();
};
