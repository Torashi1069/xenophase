#pragma once
#include "shared/N3System/N3Inter.h"
#include "shared/N3System/N3MessageQueue.h"
#include "shared/N3System/N3Object.h"
#include "shared/N3System/N3Thread.h"


class CProcessMgr : public N3Thread, public N3Inter, public N3Object
{
public:
	bool isOK() const;
	bool Start();
	void Stop();

private:
	std::tr1::tuple<bool,std::string,std::string> Startup();
	void Cleanup();

public:
	enum
	{
		MSG_THREAD_QUIT = 0,
		MSG_ACCEPT      = 1,
	};

private:
	bool MessageProcess();

public:
	virtual void Receive(const unsigned int in_Msg, const unsigned int in_wParam, const unsigned int in_lParam);

private:
	virtual unsigned int ThreadFunction();
	virtual void PostThreadQuitMessage();

public:
	static bool CreateInstance();
	static void DestroyInstance();
	static CProcessMgr* GetObj(); /// @custom

private:
	CProcessMgr();
	virtual ~CProcessMgr();
	CProcessMgr(const CProcessMgr&); // = delete;
	CProcessMgr& operator=(const CProcessMgr&); // = delete;

private:
	/* static  */ static CProcessMgr*& m_cpSelf; //TODO
	/* this+ 0 */ //N3Thread baseclass_0;
	/* this+48 */ //N3Inter baseclass_48;
	/* this+52 */ //N3Object baseclass_52;
	/* this+60 */ bool m_bOK;
	/* this+61 */ bool m_bReqExit;
	/* this+64 */ N3MessageQueue m_MessageQueue;
};
