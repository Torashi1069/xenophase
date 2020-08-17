#pragma once
#include "shared/N3System/N3Inter.h"
#include "shared/N3System/N3MessageQueue.h"
#include "shared/N3System/N3Object.h"
#include "shared/N3System/N3Scheduler.h"


class C2ClientMgr : public N3Inter, public N3Object
{
public:
	enum { MSG_CONNECT_FAIL = 0, MSG_CONNECT_SUCCESS = 1 };

public:
	bool isOK() const;
	void Process();
	void OnDisconnect(unsigned int in_hClient);
	virtual void Receive(const unsigned int in_Msg, const unsigned int in_wParam, const unsigned int in_lParam);

private:
	void MessageProcess();
	void OnMSG_CONNECT_FAIL(unsigned int in_hClient, std::string in_msg);
	void OnMSG_CONNECT_SUCCESS(unsigned int in_hClient, SOCKET in_hSocket);
	bool Create();
	void Destroy();

public:
	static bool CreateInstance();
	static void DestroyInstance();
	static C2ClientMgr* GetObj(); /// @custom

private:
	C2ClientMgr();
	virtual ~C2ClientMgr();

private:
	/* static  */ static C2ClientMgr*& m_cpSelf; //TODO
	/* this+ 0 */ //N3Inter baseclass_0;
	/* this+ 4 */ //N3Object baseclass_4;
	/* this+12 */ bool m_bOK;
	/* this+16 */ N3MessageQueue m_MessageQueue;
	/* this+76 */ N3Scheduler<C2ClientMgr> m_Scheduler;
};
