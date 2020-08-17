#include "shared/N2System/N2Thread.h"


N2Thread::N2Thread(const std::string in_Name)
: m_State(STATE_UNLOAD), m_Name(in_Name), m_hThread(NULL), m_ThreadID(0)
{
	m_bOK = true;
}


N2Thread::~N2Thread()
{
	this->N2Thread::End();
}


const bool N2Thread::isOK() const
{
	return m_bOK;
}


unsigned int __stdcall N2Thread::ThreadFunctionCaller(void* in_pParam)
{
	N2Thread* self = reinterpret_cast<N2Thread*>(in_pParam);

	return self->ThreadFunction();
}


void N2Thread::End()
{
	switch( m_State )
	{
	case STATE_UNLOAD:
	break;
	case STATE_PAUSE:
		this->N2Thread::Resume();
		// fall through
	case STATE_RUN:
		this->PostThreadQuitMessage();
		WaitForSingleObject(m_hThread, INFINITE);
		CloseHandle(m_hThread);
		m_hThread = NULL;
		m_State = STATE_UNLOAD;
	break;
	};
}


bool N2Thread::Begin()
{
	if( m_hThread != NULL )
		return false;

	if( m_State != STATE_UNLOAD )
		return false;

	m_hThread = (HANDLE)_beginthreadex(NULL, 0, &ThreadFunctionCaller, (void*)this, CREATE_SUSPENDED, (unsigned int*)&m_ThreadID);
	if( m_hThread == NULL )
		return false;

	ResumeThread(m_hThread);
	m_State = STATE_RUN;
	return true;
}


void N2Thread::Resume()
{
	if( m_State == STATE_PAUSE && ResumeThread(m_hThread) != (DWORD)-1 )
		m_State = STATE_RUN;
}


void N2Thread::Suspend()
{
	if( m_State == STATE_RUN && SuspendThread(m_hThread) != (DWORD)-1 )
		m_State = STATE_PAUSE;
}


DWORD_PTR N2Thread::SetThreadAffinityMask(const DWORD_PTR in_Mask)
{
	return ::SetThreadAffinityMask(m_hThread, in_Mask);
}


std::string N2Thread::GetName()
{
	return m_Name;
}
