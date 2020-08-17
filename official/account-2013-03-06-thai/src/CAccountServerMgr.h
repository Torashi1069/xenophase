#pragma once
#include "Common/NSystem/NInter.h"
#include "Common/NSystem/NObject.h"
#include "Common/NSystem/NThread.h"
#include "Common/NSystem/NMessageQueue.h"


class CAccountServerMgr : public NThread, public NInter, public NObject
{
public:
	enum { MSG_THREAD_QUIT = 0 };

public:
	bool isOK() const;
	bool Start();
	void Stop();
	virtual void Receive(const unsigned int in_Msg, const unsigned int in_wParam, const unsigned int in_lParam);

private:
	std::pair<bool,std::string> CAccountServerMgr::Startup1st();
	void Cleanup();

private:
	virtual unsigned int ThreadFunction();
	virtual void PostThreadQuitMessage();

public:
	static bool CreateInstance();
	static void DestroyInstance();
	static CAccountServerMgr* GetObj();

private:
	CAccountServerMgr();
	virtual ~CAccountServerMgr();

private:
	/* this+ 0 */ //NThread baseclass_0;
	/* this+48 */ //NInter baseclass_48;
	/* this+52 */ //NObject baseclass_52;
	/* this+60 */ bool m_bOK;
	/* this+64 */ NMessageQueue m_MessageQueue;
	/* static  */ static CAccountServerMgr* m_cpSelf;
};
