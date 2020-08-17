#include "AsyncDBWork/NInterMessageQueue.h"


NInterMessageQueue::NInterMessageQueue(void) // line 12
{
	InitializeCriticalSection(&m_CS);
}


NInterMessageQueue::~NInterMessageQueue(void) // line 17
{
	DeleteCriticalSection(&m_CS);
}


hook_method<void (NInterMessageQueue::*)(const unsigned int in_FromInter, const unsigned long in_ExecTimeMS, const int in_Message, const int in_wParam, const int in_lParam)> NInterMessageQueue::_Post(SERVER, "NInterMessageQueue::Post");
void NInterMessageQueue::Post(const unsigned int in_FromInter, const unsigned long in_ExecTimeMS, const int in_Message, const int in_wParam, const int in_lParam) // line 22
{
	return (this->*_Post)(in_FromInter, in_ExecTimeMS, in_Message, in_wParam, in_lParam);

	//TODO
}


hook_method<bool (NInterMessageQueue::*)(const unsigned long in_ExecTimeMS, unsigned int& out_FromInter, int& out_Message, int& out_wParam, int& out_lParam, const bool in_bRemove)> NInterMessageQueue::_Peek(SERVER, "NInterMessageQueue::Peek");
bool NInterMessageQueue::Peek(const unsigned long in_ExecTimeMS, unsigned int& out_FromInter, int& out_Message, int& out_wParam, int& out_lParam, const bool in_bRemove) // line 28
{
	return (this->*_Peek)(in_ExecTimeMS, out_FromInter, out_Message, out_wParam, out_lParam, in_bRemove);

	//TODO
}
