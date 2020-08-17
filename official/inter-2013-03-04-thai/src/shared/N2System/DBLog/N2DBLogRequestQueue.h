#pragma once
#include "shared/N2System/DBLog/N2DBLog.h"


class N2DBLogRequestQueue
{
private:
	/* this+ 0 */ //const N2DBLogRequestQueue::`vftable';
	typedef std::list<N2DBLog*> CONTAINER;
	typedef std::list<N2DBLog*>::iterator CONTAINER_ITER;
	/* this+ 4 */ CONTAINER m_Container;
	/* this+32 */ bool m_bOK;
	/* this+36 */ HANDLE m_hSemaphore;
	/* this+40 */ RTL_CRITICAL_SECTION m_CS;

private:
	bool Create();
	void Destroy();
	N2DBLog* Get();
	HANDLE& GetEventObject();

public:
	bool isOK() const;
	bool Add(N2DBLog* const in_cpDBLog);

private:
	N2DBLogRequestQueue();
	virtual ~N2DBLogRequestQueue();

	friend class N2DBLogMgr; // ctor/dtor
	friend class N2DBLogThread; // GetEventObject()
};
