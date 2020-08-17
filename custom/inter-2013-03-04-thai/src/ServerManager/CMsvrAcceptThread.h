#pragma once
#include "shared/NSystem/NIPAddr.h"
#include "shared/N3System/N3Thread.h"
#include "shared/N3System/N3Inter.h"
#include "shared/N3System/N3Object.h"
#include "shared/N3System/N3MessageQueue.h"


class CMsvrAcceptThread : public N3Thread, public N3Inter, public N3Object
{
public:
	enum { MSG_REQ_THREAD_QUIT = 0 };

public:
	bool isOK() const;
	bool Start();
	void Stop();

private:
	virtual unsigned int ThreadFunction();
	virtual void PostThreadQuitMessage();

public:
	virtual void Receive(const unsigned int in_Msg, const unsigned int in_wParam, const unsigned int in_lParam);

private:
	bool Create();
	void Destory();

public:
	static bool CreateInstance(NIPAddr in_IPAddr, int in_Port);
	static void DestroyInstance();
	static CMsvrAcceptThread* GetObj(); /// @custom

private:
	CMsvrAcceptThread(const unsigned long in_IPaddr, const short in_Port);
	virtual ~CMsvrAcceptThread();
	CMsvrAcceptThread(CMsvrAcceptThread&); // = delete;
	CMsvrAcceptThread& operator=(CMsvrAcceptThread&); // = delete;

private:
	/* static   */ static CMsvrAcceptThread*& m_cpSelf; //TODO
	/* this+  0 */ //N3Thread baseclass_0;
	/* this+ 48 */ //N3Inter baseclass_48;
	/* this+ 52 */ //N3Object baseclass_52;
	/* this+ 60 */ bool m_bOK;
	/* this+ 64 */ N3MessageQueue m_MessageQueue;
	/* this+132 */ unsigned int m_Socket;
	/* this+136 */ const unsigned long m_IPaddr;
	/* this+140 */ const short m_Port;
};
