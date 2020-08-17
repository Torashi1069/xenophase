#include "N2Thread.h"


N2Thread::N2Thread(void) // line 9
{
	m_State = STATE_UNLOAD;
	m_hThread = NULL;
	m_ThreadID = 0;
	m_bOK = true;
}


N2Thread::~N2Thread(void) // line 17
{
	this->N2Thread::End();
}


hook_method<static unsigned int (__stdcall *)(void* in_pParam)> N2Thread::_ThreadFunctionCaller(SERVER, "N2Thread::ThreadFunctionCaller");
unsigned int __stdcall N2Thread::ThreadFunctionCaller(void* in_pParam) // line 29
{
	return (_ThreadFunctionCaller)(in_pParam);

	return ((N2Thread*)in_pParam)->ThreadFunction();
}


hook_method<const bool (N2Thread::*)(void) const> N2Thread::_isOK(SERVER, "N2Thread::isOK");
const bool N2Thread::isOK(void) const // line 23
{
	return (this->*_isOK)();

	return m_bOK;
}


hook_method<bool (N2Thread::*)(void)> N2Thread::_Begin(SERVER, "N2Thread::Begin");
bool N2Thread::Begin(void) // line 61
{
	return (this->*_Begin)();

	if( m_hThread != NULL )
		return false;

	if( m_State != STATE_UNLOAD )
		return false;

	m_hThread = (HANDLE)::_beginthreadex(NULL, 0, &N2Thread::ThreadFunctionCaller, (void*)this, CREATE_SUSPENDED, (unsigned int*)&m_ThreadID);
	if( m_hThread == NULL )
		return false;

	ResumeThread(m_hThread);
	m_State = STATE_RUN;
	return true;
}


hook_method<void (N2Thread::*)(void)> N2Thread::_End(SERVER, "N2Thread::End");
void N2Thread::End(void) // line 34
{
	return (this->*_End)();

	switch( m_State )
	{
	case STATE_UNLOAD:
		break;
	case STATE_PAUSE:
		this->N2Thread::Resume();
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
	}
}


hook_method<void (N2Thread::*)(void)> N2Thread::_Resume(SERVER, "N2Thread::Resume");
void N2Thread::Resume(void) // line 85
{
	return (this->*_Resume)();

	if( m_State == STATE_PAUSE && ::ResumeThread(m_hThread) != -1 )
		m_State = STATE_RUN;
}


hook_method<void (N2Thread::*)(void)> N2Thread::_Suspend(SERVER, "N2Thread::Suspend");
void N2Thread::Suspend(void) // line 101
{
	return (this->*_Suspend)();

	if( m_State == STATE_RUN && ::SuspendThread(m_hThread) != -1 )
		m_State = STATE_PAUSE;
}


hook_method<DWORD_PTR (N2Thread::*)(const DWORD_PTR in_Mask)> N2Thread::_SetThreadAffinityMask(SERVER, "N2Thread::SetThreadAffinityMask");
DWORD_PTR N2Thread::SetThreadAffinityMask(const DWORD_PTR in_Mask) // line 119
{
	return (this->*_SetThreadAffinityMask)(in_Mask);

	return ::SetThreadAffinityMask(m_hThread, in_Mask);
}
