#pragma once
#include "shared/N3System/N3Inter.h"
#include "shared/N3System/N3IPAddr.h"
#include "shared/N3System/N3MessageQueue.h"
#include "shared/N3System/N3Object.h"
#include "shared/N3System/N3Thread.h"


class C2ClientWorkThread : public N3Thread, public N3Inter, public N3Object
{
public:
	enum { MSG_THREAD_QUIT = 0, MSG_REQUEST_CONNECT = 1 };

public:
	bool isOK() const;
	bool Start();
	void Stop();

private:
	void OnMSG_REQUEST_CONNECT(unsigned int in_hClient, N3IPAddr in_ServerIPaddr, int in_ServerPortNum);
	virtual unsigned int ThreadFunction();
	virtual void PostThreadQuitMessage();

public:
	virtual void Receive(const unsigned int in_Msg, const unsigned int in_wParam, const unsigned int in_lParam);

public:
	static bool CreateInstance();
	static void DestroyInstance();
	static C2ClientWorkThread* GetObj(); /// @custom

private:
	C2ClientWorkThread();
	virtual ~C2ClientWorkThread();

private:
	/* static  */ static C2ClientWorkThread*& m_cpSelf; //TODO
	/* this+ 0 */ //N3Thread baseclass_0;
	/* this+48 */ //N3Inter baseclass_48;
	/* this+52 */ //N3Object baseclass_52;
	/* this+60 */ bool m_bOK;
	/* this+64 */ N3MessageQueue m_MessageQueue;
};
