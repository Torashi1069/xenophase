#pragma once
#include "std/list"


class NInterMessageQueueN
{
	class Message
	{
		/* this+0x0 */ unsigned int m_FromInter;
		/* this+0x4 */ int m_Message;
		/* this+0x8 */ int m_wParam;
		/* this+0xC */ int m_lParam;

		//public: void Message(const unsigned int, const int, const int, const int);
		//public: void Message();
	};

	typedef mystd::list<NInterMessageQueueN::Message>::const_iterator MESSAGE_CONTAINER_ITER;

	struct vtable_t
	{
		void (NInterMessageQueueN::* Post)(const unsigned int, const int, const int, const int);
		bool (NInterMessageQueueN::* Peek)(unsigned int&, int&, int&, int&, bool);
		void* (NInterMessageQueueN::* scalar_deleting_destructor)(unsigned int);
	};

	/* this+0x0  */ //const NInterMessageQueueN::`vftable'
	/* this+0x4  */ protected: RTL_CRITICAL_SECTION m_CS;
	/* this+0x1C */ protected: mystd::list<NInterMessageQueueN::Message> m_Container;

	//public: virtual void Post(const unsigned int, const int, const int, const int);
	//public: virtualbool Peek(unsigned int &, int &, int &, int &, const bool);
	//public: NInterMessageQueueN(void);
	//public: virtual ~NInterMessageQueueN(void);
};
