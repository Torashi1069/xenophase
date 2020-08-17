#pragma once
#include "AsyncDBWork/NAsyncDBRequestCircularQueue.h"
#include "AsyncDBWork/NAsyncDBResponseCircularQueue.h"
#include "AsyncDBWork/NODBCCtrl.h"
#include "AsyncDBWork/NTPMessageQueue.h"
#include "AsyncDBWork/NXInter.h"
#include "AsyncDBWork/NXObject.h"
#include "AsyncDBWork/NXThread.h"


class NAsyncDBThread : public NXObject, public NXThread, public NXInter
{
private:
	/* this+  0 */ //NXObject baseclass_0;
	/* this+ 36 */ //NXThread baseclass_36;
	/* this+ 84 */ //NXInter baseclass_84;
	/* this+ 88 */ bool m_bOK;
	/* this+ 92 */ NTPMessageQueue m_MessageQueue;
	/* this+140 */ HANDLE m_hMessageEvent;
	/* this+144 */ const std::string m_ODBCConnectionStr;
	/* this+172 */ NODBCCtrl m_ODBCCtrl;
	/* this+188 */ const unsigned int m_hMotherInter;
	/* this+192 */ NAsyncDBRequestCircularQueue* const m_vcpRequestCircularQueue;
	/* this+196 */ NAsyncDBResponseCircularQueue* const m_vcpReponseCircularQueue;
	/* this+200 */ enum enumState { STATE_DISCONNECT = 0, STATE_CONNECT = 1 } m_State;

private:
	bool Create();
	void Destory();

public:
	const bool isOK() const;
	bool Start();
	void Stop();
	virtual void PostInterMessage(const unsigned int in_FromInter, const DWORD in_ExecTimeMS, const int in_Msg, const int in_wParam, const int in_lParam);

private:
	virtual bool PeekInterMessage(const DWORD in_ExecTimeMS, unsigned int& out_FromInter, int& out_Msg, int& out_wParam, int& out_lParam, const bool in_bRemove);
	virtual unsigned int ThreadFunction();
	const bool ThreadFunction_Message();
	virtual void PostThreadQuitMessage();

public:
	NAsyncDBThread(const unsigned int in_hMotherInter, const std::string in_ODBCConnectionStr, NAsyncDBRequestCircularQueue* const in_cpRequestCircularQueue, NAsyncDBResponseCircularQueue* const in_cpReponseCircularQueue);
	virtual ~NAsyncDBThread();
};
