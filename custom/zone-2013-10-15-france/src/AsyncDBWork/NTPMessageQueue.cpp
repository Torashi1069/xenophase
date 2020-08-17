#include "AsyncDBWork/NTPMessageQueue.h"
#include "AsyncDBWork/NXSyncObject.h"


NTPMessageQueue::NTPMessageQueue()
{
}


NTPMessageQueue::~NTPMessageQueue()
{
}


bool NTPMessageQueue::isEmpty()
{
	NXSyncObject sync(m_CS);

	return ( m_queue.size() == 0 );
}


DWORD NTPMessageQueue::GetFirstExecTimeMS()
{
	NXSyncObject sync(m_CS);

	if( m_queue.size() == 0 )
		return GetTickCount();

	Message& msg = m_queue.top();
	return msg.m_ExecTimeMS;
}


bool NTPMessageQueue::Peek(unsigned int& out_FromInter, int& out_Message, int& out_wParam, int& out_lParam, const bool in_bRemove)
{
	NXSyncObject sync(m_CS);

	if( m_queue.size() == 0 )
		return false;

	Message& msg = m_queue.top();
	out_FromInter = msg.m_FromInter;
	out_Message = msg.m_Message;
	out_wParam = msg.m_wParam;
	out_lParam = msg.m_lParam;

	if( in_bRemove == true )
		m_queue.pop();

	return true;
}
