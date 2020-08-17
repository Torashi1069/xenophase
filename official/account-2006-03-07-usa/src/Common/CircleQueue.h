#pragma once
#include "Common/CriticalSection.h"


class CCircleQueue
{
private:
	/* this+ 0 */ int m_nBufferSize;     // total buffer size
	/* this+ 4 */ BYTE* m_pbyQueue;      // data buffer
	/* this+ 8 */ int m_nFront;          // first occupied position
	/* this+12 */ int m_nRear;           // first free position
	/* this+16 */ int m_nDataLength;     // used size (NOTE: can be derived from other vars)
	/* this+20 */ CCriticalSection m_cs;

private:
	int IsOverflow(int nLength);
	int IsUnderflow(int nLength);

public:
	CCircleQueue();
	~CCircleQueue();
	bool Create(int nSize);
	void ClearBuffer();
	int GetDataLength();
	BOOL Insert(void* pData, int nLength);
	BOOL Peek(void* pData, int nLength);
	BOOL Get(void* pData, int nLength);
	bool RemoveFrontData(int nLength);
	int GetFreeSize();
	int GetBufferSize();
	bool Empty();
//	int LengthTo(char*);
};
