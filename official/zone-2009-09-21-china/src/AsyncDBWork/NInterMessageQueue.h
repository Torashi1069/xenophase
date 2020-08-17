#pragma once
#include "std/queue"
#include "std/vector"


class NInterMessageQueue
{
	struct Message
	{
		/* this+0x0  */ unsigned int m_FromInter;
		/* this+0x4  */ int m_Message;
		/* this+0x8  */ int m_wParam;
		/* this+0xC  */ int m_lParam;
		/* this+0x10 */ unsigned long m_ExecTimeMS;

		class Less
		{
			public: bool operator()(const NInterMessageQueue::Message& in_Lhs, const NInterMessageQueue::Message& in_Rhs)
			{
				return ( in_Lhs.m_ExecTimeMS > in_Rhs.m_ExecTimeMS );
			}
		};

		//public: void Message(const unsigned int, const unsigned long, const int, const int, const int);
		//public: void Message();
	};

	struct vtable_t
	{
		void (NInterMessageQueue::* Post)(const unsigned int, const unsigned long, const int, const int, const int);
		bool (NInterMessageQueue::* Peek)(const unsigned long, unsigned int&, int&, int&, int&, const bool);
		void* (NInterMessageQueue::* scalar_deleting_destructor)(unsigned int);
	};

	/* this+0x0  */ //const NInterMessageQueue::`vftable'
	/* this+0x4  */ protected: mystd::priority_queue<NInterMessageQueue::Message,mystd::vector<NInterMessageQueue::Message>,NInterMessageQueue::Message::Less> m_queue;
	/* this+0x18 */ protected: RTL_CRITICAL_SECTION m_CS;

	public: virtual void NInterMessageQueue::Post(const unsigned int in_FromInter, const unsigned long in_ExecTimeMS, const int in_Message, const int in_wParam, const int in_lParam);
	public: virtual bool NInterMessageQueue::Peek(const unsigned long in_ExecTimeMS, unsigned int& out_FromInter, int& out_Message, int& out_wParam, int& out_lParam, const bool in_bRemove);
	public: NInterMessageQueue::NInterMessageQueue(void);
	public: virtual NInterMessageQueue::~NInterMessageQueue(void);

private:
	static hook_method<void (NInterMessageQueue::*)(const unsigned int in_FromInter, const unsigned long in_ExecTimeMS, const int in_Message, const int in_wParam, const int in_lParam)> NInterMessageQueue::_Post;
	static hook_method<bool (NInterMessageQueue::*)(const unsigned long in_ExecTimeMS, unsigned int& out_FromInter, int& out_Message, int& out_wParam, int& out_lParam, const bool in_bRemove)> NInterMessageQueue::_Peek;
};
