#include "AsyncDBWork/NThread.h"


NThread::NThread(void) // line 13
{
	m_State = STATE_UNLOAD;
	m_hThread = NULL;
	m_ThreadID = 0;
	m_bOK = true;
}


NThread::~NThread(void) // line 21
{
	this->NThread::End();
}


hook_method<const bool (NThread::*)(void)> NThread::_isOK(SERVER, "NThread::isOK");
const bool NThread::isOK(void) // line 27?
{
	return (this->*_isOK)();

	return m_bOK;
}


hook_method<static unsigned int (__stdcall *)(void* in_pParam)> NThread::_ThreadFunctionCaller(SERVER, "NThread::ThreadFunctionCaller");
unsigned int __stdcall NThread::ThreadFunctionCaller(void* in_pParam) // line 33
{
	return (NThread::_ThreadFunctionCaller)(in_pParam);

	return ((NThread*)in_pParam)->ThreadFunction();
}


hook_method<bool (NThread::*)(void)> NThread::_Begin(SERVER, "NThread::Begin");
bool NThread::Begin(void) // line 65
{
	return (this->*_Begin)();

	if( m_hThread != NULL )
		return false;

	if( m_State != STATE_UNLOAD )
		return false;

	m_hThread = (HANDLE)::_beginthreadex(NULL, 0, &NThread::ThreadFunctionCaller, (void*)this, CREATE_SUSPENDED, (unsigned int*)&m_ThreadID);
	if( m_hThread == NULL )
		return false;

	ResumeThread(m_hThread);
	m_State = STATE_RUN;
	return true;
}


hook_method<void (NThread::*)(void)> NThread::_End(SERVER, "NThread::End");
void NThread::End(void) // line 38?
{
	return (this->*_End)();

	switch( m_State )
	{
	case STATE_UNLOAD:
		break;
	case STATE_PAUSE:
		this->NThread::Resume();
		// fall through
	case STATE_RUN:
		this->PostThreadQuitMessage();
		::WaitForSingleObject(m_hThread, INFINITE);
		::CloseHandle(m_hThread);
		m_hThread = NULL;
		m_State = STATE_UNLOAD;
		break;
	default:
		break;
	};
}


hook_method<void (NThread::*)(void)> NThread::_Resume(SERVER, "NThread::Resume");
void NThread::Resume(void) // line 89
{
	return (this->*_Resume)();

	if( m_State == STATE_PAUSE && ::ResumeThread(m_hThread) != -1 )
		m_State = STATE_RUN;
}


//hook_method<void (NThread::*)(void)> NThread::_Suspend(SERVER, "NThread::Suspend");
void NThread::Suspend(void) // line 105?
{
//	return (this->*_Suspend)();

	if( m_State == STATE_RUN && ::SuspendThread(m_hThread) != -1 )
		m_State = STATE_PAUSE;
}


//hook_method<DWORD_PTR (NThread::*)(const DWORD_PTR in_Mask)> NThread::_SetThreadAffinityMask(SERVER, "NThread::SetThreadAffinityMask");
DWORD_PTR NThread::SetThreadAffinityMask(const DWORD_PTR in_Mask) // line ???
{
//	return (this->*_SetThreadAffinityMask)(in_Mask);

	return ::SetThreadAffinityMask(m_hThread, in_Mask);
}
