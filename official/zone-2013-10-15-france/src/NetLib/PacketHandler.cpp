#include "NetLib/PacketHandler.h"


CPacketHandler::CPacketHandler()
{
	m_recvQueue = NULL;
}


void CPacketHandler::SetQueue(CPacketQueue* queue)
{
	m_recvQueue = queue;
}


void CPacketHandler::Reset()
{
	m_recvQueue->CPacketQueue::Reset();
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
