#pragma once
#include "N2System/N2Thread.h"


class CProcessThread : public N2Thread
{
	struct vtable_t // const CProcessThread::`vftable'
	{
		unsigned int (CProcessThread::* ThreadFunction)(void);
		void (CProcessThread::* PostThreadQuitMessage)(void);
		void* (CProcessThread::* vector_deleting_destructor)(unsigned int);
	};

	/* this+0x0  */ //N2Thread
	/* this+0x14 */ private: bool m_bOK;
	/* this+0x15 */ private: bool m_bReqExit;
	/* static    */ private: static hook_ptr<CProcessThread*> m_cpSelf;

	private: virtual unsigned int CProcessThread::ThreadFunction(void);
	private: virtual void CProcessThread::PostThreadQuitMessage(void);
	public: bool CProcessThread::Start(void);
	public: void CProcessThread::Stop(void);
	public: const bool CProcessThread::isOK(void);
	public: static bool CProcessThread::CreateInstance(void);
	public: static void CProcessThread::DestoryInstance(void);
	public: static CProcessThread* CProcessThread::GetObj(void);
	private: CProcessThread::CProcessThread(void);
	private: virtual CProcessThread::~CProcessThread(void);

private:
	static hook_method<unsigned int (CProcessThread::*)(void)> CProcessThread::_ThreadFunction;
	static hook_method<void (CProcessThread::*)(void)> CProcessThread::_PostThreadQuitMessage;
	static hook_method<bool (CProcessThread::*)(void)> CProcessThread::_Start;
	static hook_method<void (CProcessThread::*)(void)> CProcessThread::_Stop;
	static hook_method<const bool (CProcessThread::*)(void)> CProcessThread::_isOK;
	static hook_method<static bool (__cdecl *)(void)> CProcessThread::_CreateInstance;
	static hook_method<static void (__cdecl *)(void)> CProcessThread::_DestoryInstance;
	static hook_method<static CProcessThread* (__cdecl *)(void)> CProcessThread::_GetObj;
};
