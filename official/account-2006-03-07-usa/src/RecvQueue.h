#pragma once


class CReceiveQueue
{
public:
	/* this+ 0 */ int Size;
	/* this+ 4 */ int CurPos;
	/* this+ 8 */ int Pos;
	/* this+12 */ char Queue[800*1024];

public:
	CReceiveQueue();
	~CReceiveQueue();
	void Init();
};
