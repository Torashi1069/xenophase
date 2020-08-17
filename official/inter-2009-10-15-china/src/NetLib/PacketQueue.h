#pragma once


class CPacketQueue
{
	/* this+ 0 */ private: char* m_buf;
	/* this+ 4 */ private: int m_capacity;
	/* this+ 8 */ private: int m_front;
	/* this+12 */ private: int m_rear;
	/* this+16 */ private: int m_size;
	/* this+20 */ private: RTL_CRITICAL_SECTION m_cs;

	//public: CPacketQueue::CPacketQueue(int capacity);
	//public: CPacketQueue::CPacketQueue(void);
	//public: CPacketQueue::~CPacketQueue(void);
	public: void CPacketQueue::Init(int capacity);
	public: void CPacketQueue::Reset(void);
	public: int CPacketQueue::InsertData(int len, const char* src);
	public: int CPacketQueue::RemoveData(int len);
	public: void CPacketQueue::PeekData(int len, char* dst);
	public: int CPacketQueue::GetData(int len, char* dst);
	public: int CPacketQueue::GetSize(void);
	public: int CPacketQueue::GetFreeSize(void);

private:
	static hook_method<void (CPacketQueue::*)(int capacity)> CPacketQueue::_Init;
	static hook_method<void (CPacketQueue::*)(void)> CPacketQueue::_Reset;
	static hook_method<int (CPacketQueue::*)(int len, const char* src)> CPacketQueue::_InsertData;
	static hook_method<int (CPacketQueue::*)(int len)> CPacketQueue::_RemoveData;
	static hook_method<void (CPacketQueue::*)(int len, char* dst)> CPacketQueue::_PeekData;
	static hook_method<int (CPacketQueue::*)(int len, char* dst)> CPacketQueue::_GetData;
	static hook_method<int (CPacketQueue::*)(void)> CPacketQueue::_GetSize;
	static hook_method<int (CPacketQueue::*)(void)> CPacketQueue::_GetFreeSize;
};
