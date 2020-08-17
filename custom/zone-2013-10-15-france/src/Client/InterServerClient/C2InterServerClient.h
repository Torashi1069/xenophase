#pragma once
#include "Client/C2Client.h"
#include "Client/InterServerClient/C2InterServerClientPacketHandler.h"
#include "shared/N3System/N3Scheduler.h"


class C2InterServerClient : public C2Client
{
public:
	enum { MSG_DISCONNECTREQCNT_ADD = 0 };

public:
	bool isOK() const;
	bool Init(SOCKET in_hSocket);
	virtual void Process();
	void Send(int len, const char* buf);

public:
	bool isAuth();
	void SetAuth(bool bAuth);
	DWORD GetLastPacketRecvTM();
	DWORD GetLastPacketSendTM();

private:
	void MessageProcess();

private:
	class lcProcessStep
	{
	public:
		enum enumStep
		{
			STEP_DISCONNECT      = 0,
			STEP_CONNECT         = 1,
			STEP_CLEANUP_START   = 2,
			STEP_CLEANUP_NETWORK = 3,
			STEP_CLEANUP_WAIT    = 4,
		};

	public:
		/* this+0 */ //const C2InterServerClient::lcProcessStep::`vftable';
		/* this+4 */ enumStep m_Step;
		/* this+8 */ DWORD m_RequestTM;

	public:
		void operator()(const enumStep in_Step) { m_Step = in_Step; m_RequestTM = timeGetTime(); }
		enumStep operator()() { return m_Step; }

	public:
		lcProcessStep() : m_Step(STEP_DISCONNECT), m_RequestTM(timeGetTime()) { }
		virtual ~lcProcessStep() { }
	};

private:
	/* this+20812 */ lcProcessStep m_ProcessStep;
	void ProcessCleanup();

public:
	static bool CreateInstance(N3IPAddr in_ServerIPAddr, int in_ServerPortNum);
	static void DestroyInstance();
	static C2InterServerClient* GetObj(); /// @custom

private:
	C2InterServerClient(N3IPAddr in_ServerIPAddr, int in_ServerPortNum);
	virtual ~C2InterServerClient();

private:
	/* static     */ static C2InterServerClient*& m_cpSelf; //TODO
	/* this+20824 */ bool m_bOK;
	/* this+20828 */ C2InterServerClientPacketHandler m_PacketHandler;
	/* this+36212 */ N3Scheduler<C2InterServerClient> m_Scheduler;
	/* this+36232 */ bool m_bAuth;
	/* this+36236 */ DWORD m_LastPacketSendTM;
};
