#pragma once


class N2Thread
{
	struct vtable_t
	{
		unsigned int (N2Thread::* ThreadFunction)(void); //__purecall
		void (N2Thread::* PostThreadQuitMessage)(void); //__purecall
		void* (N2Thread::* vector_deleting_destructor)(unsigned int);
	};

	enum enumState
	{
		STATE_UNLOAD = 0,
		STATE_RUN    = 1,
		STATE_PAUSE  = 2,
	};

	/* this+0x0  */ //const N2Thread::`vftable'
	/* this+0x4  */ private: unsigned long m_ThreadID;
	/* this+0x8  */ private: bool m_bOK;
	/* this+0xC  */ private: enum N2Thread::enumState m_State;
	/* this+0x10 */ private: HANDLE m_hThread;

	private: static unsigned int __stdcall N2Thread::ThreadFunctionCaller(void* in_pParam);
	private: virtual unsigned int ThreadFunction(void) = 0;
	private: virtual void PostThreadQuitMessage(void) = 0;
	public: const bool N2Thread::isOK(void) const;
	public: bool N2Thread::Begin(void);
	public: void N2Thread::End(void);
	public: void N2Thread::Resume(void);
	public: void N2Thread::Suspend(void);
	public: unsigned long N2Thread::SetThreadAffinityMask(const DWORD_PTR in_Mask);
	public: N2Thread::N2Thread(void);
	public: virtual N2Thread::~N2Thread(void);

private:
	static hook_method<static unsigned int (__stdcall *)(void* in_pParam)> N2Thread::_ThreadFunctionCaller;
	static hook_method<const bool (N2Thread::*)(void) const> N2Thread::_isOK;
	static hook_method<bool (N2Thread::*)(void)> N2Thread::_Begin;
	static hook_method<void (N2Thread::*)(void)> N2Thread::_End;
	static hook_method<void (N2Thread::*)(void)> N2Thread::_Resume;
	static hook_method<void (N2Thread::*)(void)> N2Thread::_Suspend;
	static hook_method<DWORD_PTR (N2Thread::*)(const DWORD_PTR in_Mask)> N2Thread::_SetThreadAffinityMask;
};
