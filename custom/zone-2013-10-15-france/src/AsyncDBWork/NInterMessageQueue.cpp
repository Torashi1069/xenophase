#include "AsyncDBWork/NInterMessageQueue.h"
#include "AsyncDBWork/NXSyncObject.h"


NInterMessageQueue::NInterMessageQueue()
{
	InitializeCriticalSection(&m_CS);
}


NInterMessageQueue::~NInterMessageQueue()
{
	DeleteCriticalSection(&m_CS);
}


void NInterMessageQueue::Post(const unsigned int in_FromInter, const DWORD in_ExecTimeMS, const int in_Message, const int in_wParam, const int in_lParam)
{
	NXSyncObject sync(m_CS);

	m_queue.push(Message(in_FromInter, in_ExecTimeMS, in_Message, in_wParam, in_lParam));
}


bool NInterMessageQueue::Peek(const DWORD in_ExecTimeMS, unsigned int& out_FromInter, int& out_Message, int& out_wParam, int& out_lParam, const bool in_bRemove)
{
	NXSyncObject sync(m_CS);

	if( m_queue.empty() )
		return false;

	Message& msg = m_queue.top();
	if( msg.m_ExecTimeMS > in_ExecTimeMS )
		return false;

	out_FromInter = msg.m_FromInter;
	out_Message = msg.m_Message;
	out_wParam = msg.m_wParam;
	out_lParam = msg.m_lParam;

	if( in_bRemove == true )
		m_queue.pop();

	return true;
}
