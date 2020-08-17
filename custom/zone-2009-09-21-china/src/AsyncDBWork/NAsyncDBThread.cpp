#include "AsyncDBWork/NAsyncDBThread.h"
#include "AsyncDBWork/NInterMessageSystem.h"


hook_method<bool (NAsyncDBThread::*)(void)> NAsyncDBThread::_Create(SERVER, "NAsyncDBThread::Create");
bool NAsyncDBThread::Create(void) // line 52-68
{
	return (this->*_Create)();

	m_hMessageEvent = ::CreateWaitableTimerA(NULL, FALSE, NULL);
	return ( m_hMessageEvent != NULL );
}


hook_method<void (NAsyncDBThread::*)(void)> NAsyncDBThread::_Destory(SERVER, "NAsyncDBThread::Destory");
void NAsyncDBThread::Destory(void) // line 46-49
{
	return (this->*_Destory)();

	if( m_hMessageEvent != NULL )
	{
		::CloseHandle(m_hMessageEvent);
		m_hMessageEvent = NULL;
	}
}


hook_method<bool (NAsyncDBThread::*)(void)> NAsyncDBThread::_Start(SERVER, "NAsyncDBThread::Start");
bool NAsyncDBThread::Start(void) // line 71
{
	return (this->*_Start)();

	//TODO
}


hook_method<void (NAsyncDBThread::*)(const unsigned int in_FromInter, const unsigned long in_ExecTimeMS, const int in_Msg, const int in_wParam, const int in_lParam)> NAsyncDBThread::_PostInterMessage(SERVER, "NAsyncDBThread::PostInterMessage");
void NAsyncDBThread::PostInterMessage(const unsigned int in_FromInter, const unsigned long in_ExecTimeMS, const int in_Msg, const int in_wParam, const int in_lParam) // line 194-203
{
	return (this->*_PostInterMessage)(in_FromInter, in_ExecTimeMS, in_Msg, in_wParam, in_lParam);

	// TODO
}


hook_method<bool (NAsyncDBThread::*)(const unsigned long in_ExecTimeMS, unsigned int& out_FromInter, int& out_Msg, int& out_wParam, int& out_lParam, const bool in_bRemove)> NAsyncDBThread::_PeekInterMessage(SERVER, "NAsyncDBThread::PeekInterMessage");
bool NAsyncDBThread::PeekInterMessage(const unsigned long in_ExecTimeMS, unsigned int& out_FromInter, int& out_Msg, int& out_wParam, int& out_lParam, const bool in_bRemove) // line 215-225
{
	return (this->*_PeekInterMessage)(in_ExecTimeMS, out_FromInter, out_Msg, out_wParam, out_lParam, in_bRemove);

	// TODO
}


hook_method<unsigned int (NAsyncDBThread::*)(void)> NAsyncDBThread::_ThreadFunction(SERVER, "NAsyncDBThread::ThreadFunction");
unsigned int NAsyncDBThread::ThreadFunction(void) // line 145-183
{
	return (this->*_ThreadFunction)();

	//TODO
}


hook_method<void (NAsyncDBThread::*)(void)> NAsyncDBThread::_PostThreadQuitMessage(SERVER, "NAsyncDBThread::PostThreadQuitMessage");
void NAsyncDBThread::PostThreadQuitMessage(void) // line 104-106
{
	return (this->*_PostThreadQuitMessage)();

	// TODO
}


NAsyncDBThread::NAsyncDBThread(const unsigned int in_hMotherInter, const mystd::string in_ODBCConnectionStr, NAsyncDBRequestCircularQueue* const in_cpRequestCircularQueue, NAsyncDBResponseCircularQueue* const in_cpReponseCircularQueue) // line 28-37
	: NObject("NAsyncDBThread"), NThread(), NInter(), m_ODBCConnectionStr(in_ODBCConnectionStr), m_MessageQueue(), m_ODBCCtrl(), m_hMessageEvent(NULL), m_vcpReponseCircularQueue(in_cpReponseCircularQueue), m_hMotherInter(in_hMotherInter), m_vcpRequestCircularQueue(in_cpRequestCircularQueue), m_State(STATE_DISCONNECT), m_bOK(false)
{
	NInterMessageSystem::GetObj()->NInterMessageSystem::Insert(this->NObject::GetMyID(), this);
	if( this->NThread::isOK() && this->NAsyncDBThread::Create() )
		this->m_bOK = true;
}


NAsyncDBThread::~NAsyncDBThread(void) // line 40-43
{
	this->NAsyncDBThread::Destory();
	NInterMessageSystem::GetObj()->NInterMessageSystem::Remove(this->NObject::GetMyID(), this);
}
