#pragma once
#include "shared/NSystem/NIPAddr.h"
#include "shared/N3System/N3Thread.h"
#include "shared/N3System/N3Inter.h"
#include "shared/N3System/N3Object.h"
#include "shared/N3System/N3MessageQueue.h"


class CZsvrAcceptThread : public N3Thread, public N3Inter, public N3Object
{
public:
	enum { MSG_REQ_THREAD_QUIT = 0 };

public:
	bool isOK() const;
	bool Start();
	void Stop();
	NIPAddr GetIPAddr() const;
	int GetPort();

private:
	virtual unsigned int ThreadFunction();
	virtual void PostThreadQuitMessage();

public:
	virtual void Receive(const unsigned int in_Msg, const unsigned int in_wParam, const unsigned int in_lParam);

private:
	bool Create();
	void Destory();

public:
	static bool CreateInstance(const DWORD in_IPaddr, const short in_Port);
	static void DestroyInstance();
	static CZsvrAcceptThread* GetObj(); /// @custom

private:
	CZsvrAcceptThread(const DWORD in_IPaddr, const short in_Port);
	virtual ~CZsvrAcceptThread();
	CZsvrAcceptThread(CZsvrAcceptThread&); // = delete;
	CZsvrAcceptThread& operator=(CZsvrAcceptThread&); // = delete;

private:
	/* static   */ static CZsvrAcceptThread*& m_cpSelf; //TODO
	/* this+  0 */ //N3Thread baseclass_0;
	/* this+ 48 */ //N3Inter baseclass_48;
	/* this+ 52 */ //N3Object baseclass_52;
	/* this+ 60 */ bool m_bOK;
	/* this+ 64 */ N3MessageQueue m_MessageQueue;
	/* this+132 */ SOCKET m_Socket;
	/* this+136 */ fd_set m_Readfdset;
	/* this+396 */ const DWORD m_IPaddr;
	/* this+400 */ const short m_Port;

	class lCSession
	{
	public:
		void AddRequestDisconnectCnt(); //TODO

	public:
		lCSession(const SOCKET in_Socket, const DWORD in_IPaddr) : m_Socket(in_Socket), m_AcceptTM(timeGetTime()), m_IPaddr(in_IPaddr), m_bAuth(false), m_ZSID(0), m_RequestDisconnectCnt(0), m_packetbuffer() { }
		virtual ~lCSession() { }

	public:
		/* this+ 0 */ //const CZsvrAcceptThread::lCSession::`vftable';
		/* this+ 4 */ SOCKET m_Socket;
		/* this+ 8 */ const DWORD m_AcceptTM;
		/* this+12 */ DWORD m_IPaddr;
		/* this+16 */ bool m_bAuth;
		/* this+20 */ int m_ZSID;
		/* this+24 */ int m_RequestDisconnectCnt;
		/* this+28 */ std::vector<BYTE> m_packetbuffer;
	};

	typedef std::map<SOCKET,lCSession> SESSION_CONTAINER;
	/* this+404 */ SESSION_CONTAINER m_SessionMap;
};
