#include "RecvQueue.h"


CReceiveQueue::CReceiveQueue()
{
	Size = 0;
	CurPos = 0;
	Pos = 0;
	memset(Queue, 0, sizeof(Queue));
}


CReceiveQueue::~CReceiveQueue()
{
}


void CReceiveQueue::Init()
{
	Size = 0;
	CurPos = 0;
	Pos = 0;
}
