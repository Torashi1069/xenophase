#pragma once
#include "AsyncDBWork/NInterMessageQueue.h"


class NTPMessageQueue : public NInterMessageQueue
{
public:
	bool isEmpty();
	DWORD GetFirstExecTimeMS();
	bool Peek(unsigned int& out_FromInter, int& out_Message, int& out_wParam, int& out_lParam, const bool in_bRemove);

public:
	NTPMessageQueue();
	virtual ~NTPMessageQueue();
};
