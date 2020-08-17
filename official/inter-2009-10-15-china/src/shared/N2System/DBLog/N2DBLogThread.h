#pragma once
#include "N2System/N2Thread.h"
#include "N2System/N2MessageQueue.h"
#include "N2System/ODBC(open database connectivity)/N2ODBCCtrl.h"
#include "N2System/DBLog/N2DBLogRequestQueue.h"
#include "std/string"


class N2DBLogThread : public N2Thread, public N2MessageQueue<int>
{
	/* this+0x0  */ //N2Thread
	/* this+0x14 */ //N2MessageQueue<int>
	/* this+0x40 */ private: bool m_bOK;
	/* this+0x44 */ private: N2ODBCCtrl m_ODBCCtrl;
	/* this+0x58 */ private: N2DBLogRequestQueue* m_cpRequestQueue;
	/* this+0x5C */ private: HANDLE m_hMessageSemaphore;
	/* this+0x60 */ private: const mystd::string m_ConnectStr;

	enum enumMessage
	{
		MSG_NONE             = 0x0,
		MSG_CONNECT_REQUEST  = 0x1,
		MSG_THREAD_TERMINATE = 0x2,
	};

	//private: bool N2DBLogThread::Create();
	//private: void N2DBLogThread::Destroy();
	//private: bool N2DBLogThread::MessageProcessor();
	//private: void N2DBLogThread::PostMessageA(const enum N2DBLogThread::enumMessage);
	//private: const enum N2DBLogThread::enumMessage N2DBLogThread::GetMessageA();
	//private: unsigned int N2DBLogThread::ThreadFunction();
	//private: void N2DBLogThread::PostThreadQuitMessage();
	//public: bool N2DBLogThread::isOK();
	//public: void N2DBLogThread::N2DBLogThread(N2DBLogRequestQueue *, const mystd::string);
	//public: void N2DBLogThread::~N2DBLogThread();
};
