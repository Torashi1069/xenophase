#pragma once
#include "std/list"


class N2InterMessageQueue
{
	class Message
	{
		/* this+0x0 */ public: unsigned int m_FromInter;
		/* this+0x4 */ public: int m_Message;
		/* this+0x8 */ public: int m_wParam;
		/* this+0xC */ public: int m_lParam;

		//public: void N2InterMessageQueue::Message::Message(const unsigned int, const int, const int, const int);
		//public: void Message();
	};

	/* this+0x0  */ void* vtable;
	/* this+0x4  */ protected: RTL_CRITICAL_SECTION m_CS;
	/* this+0x1C */ protected: mystd::list<N2InterMessageQueue::Message> m_Container;

	typedef mystd::list<N2InterMessageQueue::Message>::const_iterator MESSAGE_CONTAINER_ITER;

	//public: void N2InterMessageQueue::Post(const unsigned int, const int, const int, const int);
	//public: bool N2InterMessageQueue::Peek(unsigned int &, int &, int &, int &, const bool);
	//public: void N2InterMessageQueue::N2InterMessageQueue();
	//public: void N2InterMessageQueue::~N2InterMessageQueue();
};
