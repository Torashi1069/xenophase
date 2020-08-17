#pragma once
#include "Client/C2Client.h"
#include "Client/CharacterServerClient/C2CharacterServerClientPacketHandler.h"
#include "shared/N3System/N3Scheduler.h"


class C2CharacterServerClient : public C2Client
{
public:
	bool isOK() const;
	bool Init(SOCKET in_hSocket);
	void Send(const int in_nLen, const char* in_pBuf);
	virtual void Process();

public:
	bool isAuth();
	void SetAuth(const bool bAuth);
	DWORD GetLastPacketRecvTM();
	DWORD GetLastPacketSendTM();

private:
	class lcProcessStep
	{
	public:
		enum enumStep
		{
			enumStep_DISCONNECT    = 0,
			enumStep_CONNECT       = 1,
			enumStep_CLEAN_START   = 2,
			enumStep_CLEAN_NETWORK = 3,
			enumStep_CLEAN_WAIT    = 4,
		};

	public:
		void operator()(const enumStep in_enumStep) { m_enumStep = in_enumStep; m_dwRequestTM = timeGetTime(); }
		enumStep operator()() { return m_enumStep; }

	public:
		lcProcessStep() : m_enumStep(enumStep_DISCONNECT), m_dwRequestTM(timeGetTime()) { }
		virtual ~lcProcessStep() { }

	public:
		/* this+0 */ //const C2InterServerClient::lcProcessStep::`vftable';
		/* this+4 */ enumStep m_enumStep;
		/* this+8 */ DWORD m_dwRequestTM;
	};

private:
	/* this+20812 */ lcProcessStep m_ProcessStep;

private:
	void MessageProcess();
	void ProcessCleanUp();

public:
	static bool CreateInstance(N3IPAddr in_ServerIPAddr, int in_ServerPortNum);
	static void DestroyInstance();
	static C2CharacterServerClient* GetObj(); /// @custom

private:
	C2CharacterServerClient(N3IPAddr in_ServerIPAddr, int in_ServerPortNum);
	virtual ~C2CharacterServerClient();

private:
	/* this+20824 */ bool m_bOK;
	/* static     */ static C2CharacterServerClient*& m_cpSelf; //TODO
	/* this+20828 */ C2CharacterServerClientPacketHandler m_PacketHandler;
	/* this+20848 */ N3Scheduler<C2CharacterServerClient> m_Scheduler;
	/* this+20868 */ bool m_bAuth;
	/* this+20872 */ DWORD m_LastPacketSendTM;
};
