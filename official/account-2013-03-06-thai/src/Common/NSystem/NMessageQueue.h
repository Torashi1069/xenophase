#pragma once


class NMessageQueue
{
public:
	bool isOK() const;
	HANDLE GetEventObj() const;

	typedef std::tr1::tuple<bool,unsigned int,unsigned int,unsigned int> RETG;
	void Put(const unsigned int in_Message, const unsigned int in_wParam, const unsigned int in_lParam);
	RETG Get();

//	void Init();
	NMessageQueue();
	virtual ~NMessageQueue();

private:
	class lcData
	{
	public:
		/* this+0 */ unsigned int m_Message;
		/* this+4 */ unsigned int m_wParam;
		/* this+8 */ unsigned int m_lParam;

	//	lcData();
		lcData(const unsigned int in_Message, const unsigned int in_wParam, const unsigned int in_lParam) : m_Message(in_Message), m_wParam(in_wParam), m_lParam(in_lParam) { }
	};

private:
	/* this+ 0 */ //const NMessageQueue::`vftable';
	/* this+ 4 */ RTL_CRITICAL_SECTION m_CS;
	/* this+28 */ std::deque<NMessageQueue::lcData> m_Queue;
	/* this+52 */ HANDLE m_hSemaphore;
	/* this+56 */ bool m_bOK;
};
