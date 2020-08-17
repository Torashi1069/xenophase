#pragma once


class NInterMessageQueue
{
protected:
	class Message
	{
	public:
		/* this+ 0 */ unsigned int m_FromInter;
		/* this+ 4 */ int m_Message;
		/* this+ 8 */ int m_wParam;
		/* this+12 */ int m_lParam;
		/* this+16 */ DWORD m_ExecTimeMS;

	class Less
	{
	public:
		bool operator()(const Message& in_Lhs, const Message& in_Rhs) { return ( in_Lhs.m_ExecTimeMS > in_Rhs.m_ExecTimeMS ); }
	};

	public:
		Message() { }
		Message(const unsigned int in_FromInter, const DWORD in_ExecTimeMS, const int in_Message, const int in_wParam, const int in_lParam) : m_FromInter(in_FromInter), m_ExecTimeMS(in_ExecTimeMS), m_Message(in_Message), m_wParam(in_wParam), m_lParam(in_lParam) { }
	};

protected:
	/* this+ 0 */ //const NInterMessageQueue::`vftable';
	/* this+ 4 */ std::priority_queue<Message,std::vector<Message>,Message::Less> m_queue;
	/* this+24 */ RTL_CRITICAL_SECTION m_CS;

public:
	virtual void Post(const unsigned int in_FromInter, const DWORD in_ExecTimeMS, const int in_Message, const int in_wParam, const int in_lParam);
	virtual bool Peek(const DWORD in_ExecTimeMS, unsigned int& out_FromInter, int& out_Message, int& out_wParam, int& out_lParam, const bool in_bRemove);

public:
	NInterMessageQueue();
	virtual ~NInterMessageQueue();
};
