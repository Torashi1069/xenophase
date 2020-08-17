#include "Common/NSystem/NThread.h"
namespace { void SetThreadName(DWORD dwThreadID, const char* threadName); };
////////////////////////////////////////


NThread::NThread(const std::string in_Name)
: m_Name(in_Name)
{
	m_State = STATE_UNLOAD;
	m_hThread = NULL;
	m_ThreadID = 0;
	m_bOK = true;
}


NThread::~NThread()
{
	this->NThread::End();
}


unsigned int NThread::ThreadFunctionCaller(void* in_pParam)
{
	return reinterpret_cast<NThread*>(in_pParam)->ThreadFunction();
}


bool NThread::Begin()
{
	if( m_hThread != NULL )
		return false;

	if( m_State != STATE_UNLOAD )
		return false;

	m_hThread = (HANDLE)_beginthreadex(NULL, 0, &NThread::ThreadFunctionCaller, this, CREATE_SUSPENDED, &m_ThreadID);
	if( m_hThread == NULL )
		return false;

	ResumeThread(m_hThread);
	m_State = STATE_RUN;

	SetThreadName(m_ThreadID, m_Name.c_str());
	return true;
}


bool NThread::isRun()
{
	return ( WaitForSingleObject(m_hThread, 0) != WAIT_OBJECT_0 );
}


void NThread::End()
{
	if( m_State != STATE_UNLOAD )
	{
		if( m_State != STATE_RUN )
		{
			if( m_State != STATE_PAUSE )
				return;

			if( ResumeThread(m_hThread) != (DWORD)-1 )
				m_State = STATE_RUN;
		}

		this->PostThreadQuitMessage();
		WaitForSingleObject(m_hThread, INFINITE);

		CloseHandle(m_hThread);
		m_hThread = NULL;

		m_State = STATE_UNLOAD;
	}
}


////////////////////////////////////////


/// @source "How to: Set a Thread Name in Native Code" http://msdn.microsoft.com/en-us/library/xcb2z8hs(v=vs.100).aspx
namespace {

const DWORD MS_VC_EXCEPTION = 0x406D1388;

#pragma pack(push,8)
typedef struct tagTHREADNAME_INFO
{
   DWORD dwType; // Must be 0x1000.
   LPCSTR szName; // Pointer to name (in user addr space).
   DWORD dwThreadID; // Thread ID (-1=caller thread).
   DWORD dwFlags; // Reserved for future use, must be zero.

} THREADNAME_INFO;
#pragma pack(pop)

void SetThreadName(DWORD dwThreadID, const char* threadName)
{
	THREADNAME_INFO info;
	info.dwType = 0x1000;
	info.szName = threadName;
	info.dwThreadID = dwThreadID;
	info.dwFlags = 0;

	__try
	{
		RaiseException(MS_VC_EXCEPTION, 0, sizeof(info)/sizeof(ULONG_PTR), (ULONG_PTR*)&info);
	}
	__except(EXCEPTION_EXECUTE_HANDLER)
	{
	}
}

}; // namespace


////////////////////////////////////////
