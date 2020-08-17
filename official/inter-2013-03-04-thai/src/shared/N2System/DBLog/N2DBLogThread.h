#pragma once
#include "shared/N2System/N2Thread.h"
#include "shared/N2System/N2MessageQueue.h"
#include "shared/N2System/ODBC(open database connectivity)/N2ODBCCtrl.h"
class N2DBLogRequestQueue;


class N2DBLogThread : public N2Thread, public N2MessageQueue<int>
{
private:
	/* this+  0 */ //N2Thread baseclass_0;
	/* this+ 48 */ //N2MessageQueue<int> baseclass_48;
	/* this+108 */ bool m_bOK;
	/* this+112 */ N2ODBCCtrl m_ODBCCtrl;
	/* this+132 */ N2DBLogRequestQueue* m_cpRequestQueue;
	/* this+136 */ HANDLE m_hMessageSemaphore;
	/* this+140 */ const std::string m_ConnectStr;

private:
	enum enumMessage
	{
		MSG_NONE             = 0,
		MSG_CONNECT_REQUEST  = 1,
		MSG_THREAD_TERMINATE = 2,
	};

private:
	bool Create();
	void Destroy();
	bool MessageProcessor();
	void PostMessage(const enumMessage in_Message);
	const enumMessage GetMessage();
	virtual unsigned int ThreadFunction();
	virtual void PostThreadQuitMessage();

public:
	bool isOK() const;
	N2DBLogThread(N2DBLogRequestQueue* in_cpRequestQueue, const std::string in_ConnectStr);
	virtual ~N2DBLogThread();
};
