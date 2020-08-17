#pragma once
#include "PollTimer.h"
#include "SvrIO.h"


class CISvrIO : public CSvrIO
{
	struct vtable_t // const CISvrIO::`vftable'
	{
		void* (CISvrIO::* scalar_deleting_destructor)(unsigned int flags);
		int (CISvrIO::* OnProcess)(void);
		void (CISvrIO::* OnCustomInit)(void);
	};

	/* this+    0 */ public: //CSvrIO baseclass_0;
	/* this+20740 */ private: CPollTimer m_PingTimer;

	enum
	{
		PING_TIME = 60000,
	};

	public: CISvrIO::CISvrIO(void);
	public: virtual CISvrIO::~CISvrIO(void);
	private: virtual void CISvrIO::OnCustomInit(void);
	public: virtual int CISvrIO::OnProcess(void);
	public: void CISvrIO::SendPing(void);

private:
	static hook_method<void (CISvrIO::*)(void)> CISvrIO::_OnCustomInit;
	static hook_method<int (CISvrIO::*)(void)> CISvrIO::_OnProcess;
	static hook_method<void (CISvrIO::*)(void)> CISvrIO::_SendPing;
};
