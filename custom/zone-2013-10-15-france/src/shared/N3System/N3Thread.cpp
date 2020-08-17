#include "shared/N3System/N3Thread.h"


N3Thread::N3Thread(const std::string in_Name)
: m_State(STATE_UNLOAD), m_Name(in_Name), m_hThread(NULL), m_ThreadID(0)
{
	m_bOK = true;
}


N3Thread::~N3Thread()
{
	this->N3Thread::End();
}


const bool N3Thread::isOK() const
{
	return m_bOK;
}


unsigned int __stdcall N3Thread::ThreadFunctionCaller(void* in_pParam)
{
	N3Thread* self = reinterpret_cast<N3Thread*>(in_pParam);

	return self->ThreadFunction();
}


void N3Thread::End()
{
	switch( m_State )
	{
	case STATE_UNLOAD:
	break;
	case STATE_PAUSE:
		this->N3Thread::Resume();
		// fall through
	case STATE_RUN:
		this->PostThreadQuitMessage();
		WaitForSingleObject(m_hThread, 3000);
		CloseHandle(m_hThread);
		m_hThread = NULL;
		m_State = STATE_UNLOAD;
	break;
	};
}


bool N3Thread::Begin()
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


void N3Thread::Resume()
{
	if( m_State == STATE_PAUSE && ResumeThread(m_hThread) != (DWORD)-1 )
		m_State = STATE_RUN;
}


void N3Thread::Suspend()
{
	if( m_State == STATE_RUN && SuspendThread(m_hThread) != (DWORD)-1 )
		m_State = STATE_PAUSE;
}


DWORD_PTR N3Thread::SetThreadAffinityMask(const DWORD_PTR in_Mask)
{
	return ::SetThreadAffinityMask(m_hThread, in_Mask);
}


std::string N3Thread::GetName()
{
	return m_Name;
}
