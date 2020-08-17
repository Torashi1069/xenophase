#pragma once


class CPacketQueue
{
public:
	void Init(int capacity);
	void Reset();
	int InsertData(int len, const char* src);
	int RemoveData(int len);
	void PeekData(int len, char* dst);
	int GetData(int len, char* dst);
	int GetSize();
	int GetFreeSize();
	int resetANDinsert(const int in_Bytes, const char* in_pData);

public:
	CPacketQueue();
	CPacketQueue(int capacity);
	~CPacketQueue();

private:
	/* this+ 0 */ char* m_buf;
	/* this+ 4 */ int m_capacity;
	/* this+ 8 */ int m_front;
	/* this+12 */ int m_rear;
	/* this+16 */ int m_size;
	/* this+20 */ RTL_CRITICAL_SECTION m_cs;
};
