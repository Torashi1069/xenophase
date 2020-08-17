#pragma once
#include "shared/N3System/N3MessageQueue.h"
#include "shared/N3System/N3Inter.h"
#include "shared/N3System/N3Object.h"
#include "shared/N3System/N3Thread.h"


class NNetworkWorkThread : public N3Thread, public N3Inter, public N3Object
{
public:
	enum
	{
		MSG_THREAD_QUIT = 0,
	};

public:
	bool Start();
	void Stop();

private:
	bool MessageDispatch();
	virtual unsigned int ThreadFunction();
	virtual void PostThreadQuitMessage();

public:
	virtual void Receive(const unsigned int in_Msg, const unsigned int in_wParam, const unsigned int in_lParam);

public:
	NNetworkWorkThread(const std::string in_Name);
	virtual ~NNetworkWorkThread();

private:
	/* this+ 0 */ //N3Thread baseclass_0;
	/* this+48 */ //N3Inter baseclass_48;
	/* this+52 */ //N3Object baseclass_52;
	/* this+60 */ N3MessageQueue m_MessageQueue;
};
