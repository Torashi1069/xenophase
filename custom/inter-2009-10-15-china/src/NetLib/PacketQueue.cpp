#include "PacketQueue.h"


hook_method<void (CPacketQueue::*)(int capacity)> CPacketQueue::_Init(SERVER, "CPacketQueue::Init");
void CPacketQueue::Init(int capacity)
{
	return (this->*_Init)(capacity);

	//TODO
}


hook_method<void (CPacketQueue::*)(void)> CPacketQueue::_Reset(SERVER, "CPacketQueue::Reset");
void CPacketQueue::Reset(void)
{
	return (this->*_Reset)();

	//TODO
}


hook_method<int (CPacketQueue::*)(int len, const char* src)> CPacketQueue::_InsertData(SERVER, "CPacketQueue::InsertData");
int CPacketQueue::InsertData(int len, const char* src)
{
	return (this->*_InsertData)(len, src);

	//TODO
}


hook_method<int (CPacketQueue::*)(int len)> CPacketQueue::_RemoveData(SERVER, "CPacketQueue::RemoveData");
int CPacketQueue::RemoveData(int len)
{
	return (this->*_RemoveData)(len);

	//TODO
}


hook_method<void (CPacketQueue::*)(int len, char* dst)> CPacketQueue::_PeekData(SERVER, "CPacketQueue::PeekData");
void CPacketQueue::PeekData(int len, char* dst)
{
	return (this->*_PeekData)(len, dst);

	//TODO
}


hook_method<int (CPacketQueue::*)(int len, char* dst)> CPacketQueue::_GetData(SERVER, "CPacketQueue::GetData");
int CPacketQueue::GetData(int len, char* dst)
{
	return (this->*_GetData)(len, dst);

	//TODO
}


hook_method<int (CPacketQueue::*)(void)> CPacketQueue::_GetSize(SERVER, "CPacketQueue::GetSize");
int CPacketQueue::GetSize(void)
{
	return (this->*_GetSize)();

	//TODO
}


hook_method<int (CPacketQueue::*)(void)> CPacketQueue::_GetFreeSize(SERVER, "CPacketQueue::GetFreeSize");
int CPacketQueue::GetFreeSize(void)
{
	return (this->*_GetFreeSize)();

	//TODO
}
