#include "PacketHandler.h"


CPacketHandler::CPacketHandler(void) // line 6
{
	m_recvQueue = NULL;
}


hook_method<void (CPacketHandler::*)(void)> CPacketHandler::_Reset(SERVER, "CPacketHandler::Reset");
void CPacketHandler::Reset(void) // line 17
{
	return (this->*_Reset)();

	m_recvQueue->CPacketQueue::Reset();
}


hook_method<int (CPacketHandler::*)(void)> CPacketHandler::_OnProcess(SERVER, "CPacketHandler::OnProcess");
int CPacketHandler::OnProcess(void) // line 22
{
	return (this->*_OnProcess)();

	return 0;
}


hook_method<int (CPacketHandler::*)(int byteTransferred, char* buf)> CPacketHandler::_OnRecvHook(SERVER, "CPacketHandler::OnRecvHook");
int CPacketHandler::OnRecvHook(int byteTransferred, char* buf) // line 36 (PacketHandler.h)
{
	return (this->*_OnRecvHook)(byteTransferred, buf);

	return 0;
}


hook_method<void (CPacketHandler::*)(int byteTransferred)> CPacketHandler::_OnRecvOverflow(SERVER, "CPacketHandler::OnRecvOverflow");
void CPacketHandler::OnRecvOverflow(int byteTransferred) // line 38 (PacketHandler.h)
{
	return (this->*_OnRecvOverflow)(byteTransferred);

	;
}


hook_method<void (CPacketHandler::*)(int byteTransferred)> CPacketHandler::_OnRecv(SERVER, "CPacketHandler::OnRecv");
void CPacketHandler::OnRecv(int byteTransferred) // line 40 (PacketHandler.h)
{
	return (this->*_OnRecv)(byteTransferred);

	;
}


hook_method<void (CPacketHandler::*)(void)> CPacketHandler::_OnClose(SERVER, "CPacketHandler::OnClose");
void CPacketHandler::OnClose(void) // line 41 (PacketHandler.h)
{
	return (this->*_OnClose)();

	;
}


hook_method<void (CPacketHandler::*)(unsigned long lastError)> CPacketHandler::_SetLastError(SERVER, "CPacketHandler::SetLastError");
void CPacketHandler::SetLastError(unsigned long lastError) // line 42 (PacketHandler.h)
{
	return (this->*_SetLastError)(lastError);

	;
}


hook_method<void (CPacketHandler::*)(int len)> CPacketHandler::_AddSendBytes(SERVER, "CPacketHandler::AddSendBytes");
void CPacketHandler::AddSendBytes(int len) // line 43 (PacketHandler.h)
{
	return (this->*_AddSendBytes)(len);

	;
}


hook_method<void (CPacketHandler::*)(CPacketQueue* queue)> CPacketHandler::_SetQueue(SERVER, "CPacketHandler::SetQueue");
void CPacketHandler::SetQueue(CPacketQueue* queue) // line 12
{
	return (this->*_SetQueue)(queue);

	m_recvQueue = queue;
}
