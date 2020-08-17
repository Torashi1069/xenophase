#pragma once
#include "shared/N2System/N2Thread.h"


class CProcessThread : public N2Thread
{
private:
	/* this+ 0 */ //N2Thread baseclass_0;
	/* this+48 */ bool m_bOK;
	/* this+49 */ bool m_bReqExit;
	/* static  */ static CProcessThread*& m_cpSelf; //TODO

private:
	virtual unsigned int ThreadFunction();
	virtual void PostThreadQuitMessage();

public:
	bool Start();
	void Stop();
	const bool isOK() const;

public:
	static bool CreateInstance();
	static void DestoryInstance();
	static CProcessThread* GetObj();

private:
	CProcessThread();
	virtual ~CProcessThread();
};
