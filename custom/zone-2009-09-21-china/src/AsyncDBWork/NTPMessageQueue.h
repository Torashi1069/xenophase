#pragma once
#include "AsyncDBWork/NInterMessageQueue.h"


class NTPMessageQueue : public NInterMessageQueue
{
	struct vtable_t // const NTPMessageQueue::`vftable'
	{
		void (NInterMessageQueue::* Post)(const unsigned int, const unsigned long, const int, const int, const int);
		bool (NInterMessageQueue::* Peek)(const unsigned long, unsigned int&, int&, int&, int&, const bool);
		void* (NTPMessageQueue::* scalar_deleting_destructor)(unsigned int);
};

	/* this+0x0 */ //NInterMessageQueue

	//public: bool NTPMessageQueue::isEmpty();
	//public: unsigned long NTPMessageQueue::GetFirstExecTimeMS();
	//public: bool NTPMessageQueue::Peek(unsigned int&, int&, int&, int&, const bool);
	//public: NTPMessageQueue::NTPMessageQueue(void);
	//public: virtual NTPMessageQueue::~NTPMessageQueue(void);
};
