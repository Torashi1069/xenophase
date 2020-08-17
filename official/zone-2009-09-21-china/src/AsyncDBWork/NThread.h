#pragma once


class NThread
{
	struct vtable_t
	{
		unsigned int (NThread::* ThreadFunction)(void); //__purecall
		void (NThread::* PostThreadQuitMessage)(void); //__purecall
		void* (NThread::* vector_deleting_destructor)(unsigned int);
	};

	enum enumState
	{
		STATE_UNLOAD = 0x0,
		STATE_RUN    = 0x1,
		STATE_PAUSE  = 0x2,
	};

	/* this+0x0  */ //const NThread::`vftable'
	/* this+0x4  */ private: unsigned long m_ThreadID;
	/* this+0x8  */ private: bool m_bOK;
	/* this+0xC  */ private: enum NThread::enumState m_State;
	/* this+0x10 */ private: HANDLE m_hThread;

	private: static unsigned int __stdcall NThread::ThreadFunctionCaller(void* in_pParam);
	private: virtual unsigned int NThread::ThreadFunction(void) = 0;
	private: virtual void NThread::PostThreadQuitMessage(void) = 0;
	public: const bool NThread::isOK(void);
	public: bool NThread::Begin(void);
	public: void NThread::End(void);
	public: void NThread::Resume(void);
	public: void NThread::Suspend(void);
	public: DWORD_PTR NThread::SetThreadAffinityMask(const DWORD_PTR in_Mask);
	public: NThread::NThread(void);
	public: virtual NThread::~NThread(void);

private:
	static hook_method<static unsigned int (__stdcall *)(void* in_pParam)> NThread::_ThreadFunctionCaller;
	static hook_method<const bool (NThread::*)(void)> NThread::_isOK;
	static hook_method<bool (NThread::*)(void)> NThread::_Begin;
	static hook_method<void (NThread::*)(void)> NThread::_End;
	static hook_method<void (NThread::*)(void)> NThread::_Resume;
	static hook_method<void (NThread::*)(void)> NThread::_Suspend;
	static hook_method<DWORD_PTR (NThread::*)(const DWORD_PTR in_Mask)> NThread::_SetThreadAffinityMask;
};
