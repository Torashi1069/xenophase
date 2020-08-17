#pragma once
#include "shared/N3System/N3Inter.h"
#include "shared/N3System/N3MessageQueue.h"
#include "shared/N3System/N3Object.h"
#include "shared/N3System/N3Thread.h"


class CInstantMapWorkerThread : public N3Object, public N3Thread, public N3Inter
{
public:
	enum
	{
		MSG_REQ_THREAD_QUIT2 = 0,
		MSG_REQUEST_WORK2    = 1,
		MSG_RESPONSE_WORK2   = 2,
	};

private:
	/* static   */ static CInstantMapWorkerThread*& m_cpSelf; //TODO
	/* this+  0 */ //N3Object baseclass_0;
	/* this+  8 */ //N3Thread baseclass_8;
	/* this+ 56 */ //N3Inter baseclass_56;
	/* this+ 60 */ N3MessageQueue m_MessageQueue;
	/* this+120 */ bool m_bOK;

private:
	virtual unsigned int ThreadFunction();
	virtual void PostThreadQuitMessage();

public:
	bool Start();
	void Stop();
	const bool isOK() const;

public:
	virtual void Receive(const unsigned int in_Msg, const unsigned int in_wParam, const unsigned int in_lParam);

public:
	static bool CreateInstance();
	static void DestoryInstance();
	static CInstantMapWorkerThread* GetObj(); /// @custom

private:
	CInstantMapWorkerThread();
	virtual ~CInstantMapWorkerThread();
	CInstantMapWorkerThread(CInstantMapWorkerThread&); // = delete;
	CInstantMapWorkerThread& operator=(CInstantMapWorkerThread&); // = delete;
};
