#pragma once
#include "N2System/N2Thread.h"
#include "NetLib/Acceptor.h"


class CAcceptThread : public N2Thread
{
	struct vtable_t // const CAcceptThread::`vftable'
	{
		unsigned int (CAcceptThread::* ThreadFunction)(void);
		void (CAcceptThread::* PostThreadQuitMessage)(void);
		void* (CAcceptThread::* scalar_deleting_destructor)(unsigned int flags);
	};

	/* this+ 0 */ public: //N2Thread baseclass_0;
	/* this+20 */ private: bool m_bOK;
	/* this+21 */ private: bool m_bReqExit;
	/* this+24 */ private: CAcceptHandler* const m_cpHandler;
	/* this+28 */ private: const unsigned long m_IPaddr;
	/* this+32 */ private: const short m_Port;
	/* this+36 */ private: const int m_Backlog;
	/* this+40 */ private: SOCKET m_Socket;
	/* this+44 */ private: unsigned int m_ipLog;

	private: virtual unsigned int CAcceptThread::ThreadFunction(void);
	private: virtual void CAcceptThread::PostThreadQuitMessage(void);
	private: bool CAcceptThread::Create(void);
	private: void CAcceptThread::Destroy(void); //TYPO
	public: const bool CAcceptThread::isOK(void);
	public: bool CAcceptThread::Start(void);
	public: void CAcceptThread::Stop(void);
	public: CAcceptThread::CAcceptThread(CAcceptHandler* const in_cpHandler, const unsigned long in_IPaddr, const short in_Port, const int in_Backlog, const unsigned int in_ipLog);
	public: virtual CAcceptThread::~CAcceptThread(void);

private:
	static hook_method<unsigned int (CAcceptThread::*)(void)> CAcceptThread::_ThreadFunction;
	static hook_method<void (CAcceptThread::*)(void)> CAcceptThread::_PostThreadQuitMessage;
	static hook_method<bool (CAcceptThread::*)(void)> CAcceptThread::_Create;
	static hook_method<void (CAcceptThread::*)(void)> CAcceptThread::_Destroy;
	static hook_method<const bool (CAcceptThread::*)(void)> CAcceptThread::_isOK;
	static hook_method<bool (CAcceptThread::*)(void)> CAcceptThread::_Start;
	static hook_method<void (CAcceptThread::*)(void)> CAcceptThread::_Stop;
};
