#pragma once
#include "AsyncDBWork/NAsyncDBWork.h"


class CSaveStoreADBWork : public NAsyncDBWork
{
public:
	enum enumResult
	{
		RESULT_SUCCESS          = 0,
		RESULT_ERROR_UNKNOWN    = 1,
		RESULT_ERROR_SAVE_STORE = 2,
	};

private:
	/* this+    0 */ //NAsyncDBWork baseclass_0;
	/* this+   20 */ enumResult m_Result;
	/* this+   24 */ unsigned long m_GID;
	/* this+   28 */ unsigned long m_AID;
	/* this+   32 */ bool m_bAfterCloseStore;
public:
	/* this+   33 */ unsigned char m_Data[16300];
	/* this+16336 */ int m_Length;

public:
	const unsigned long GetAID() const;
	const unsigned long GetGID() const;
	const enumResult GetResult() const;
	bool IsCloseStore() const;

private:
	virtual bool ExecQuery(NODBCCtrl& in_ODBCCtrl);

public:
	void Init(const unsigned long in_AID, const unsigned long in_GID, const bool in_bAfterCloseStore);

private:
	CSaveStoreADBWork();
	virtual ~CSaveStoreADBWork();

	template<typename T> friend class CObjectRecycleMgr;
};
