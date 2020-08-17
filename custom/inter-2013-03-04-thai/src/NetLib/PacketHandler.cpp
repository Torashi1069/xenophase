#include "NetLib/PacketHandler.h"
#include "NetLib/PacketQueue.h"


CPacketHandler::CPacketHandler()
{
	m_recvQueue = NULL;
}


int CPacketHandler::OnProcess()
{
	return 0;
}


int CPacketHandler::OnRecvHook(int byteTransferred, char* buf)
{
	return 0;
}


void CPacketHandler::OnRecvOverflow(int byteTransferred)
{
}


void CPacketHandler::OnRecv(int byteTransferred)
{
}


void CPacketHandler::OnClose()
{
}


void CPacketHandler::SetLastError(DWORD lastError)
{
}


void CPacketHandler::AddSendBytes(int byteTransferred)
{
}


void CPacketHandler::Reset()
{
	m_recvQueue->CPacketQueue::Reset();
}


void CPacketHandler::SetQueue(CPacketQueue* queue)
{
	m_recvQueue = queue;
}
