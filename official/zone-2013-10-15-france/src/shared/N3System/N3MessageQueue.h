#pragma once


class N3MessageQueue
{
public:
	bool isOK() const;
	HANDLE GetEventObj();
	void Put(const unsigned int in_Message, const unsigned int in_wParam, const unsigned int in_lParam);
	typedef std::tr1::tuple<bool, const unsigned int, const unsigned int, const unsigned int> RETGET;
	RETGET Get();
	void Init(); //TODO

public:
	N3MessageQueue();
	virtual ~N3MessageQueue();
	N3MessageQueue(const N3MessageQueue&); // = delete;
	N3MessageQueue& operator=(const N3MessageQueue&); // = delete;

private:
	class lcData
	{
	public:
		/* this+0 */ unsigned int m_Message;
		/* this+4 */ unsigned int m_wParam;
		/* this+8 */ unsigned int m_lParam;

	public:
		lcData(); //TODO
		lcData(const unsigned int in_Message, const unsigned int in_wParam, const unsigned int in_lParam) : m_Message(in_Message), m_wParam(in_wParam), m_lParam(in_lParam) { }
	};

private:
	/* this+ 0 */ //const N3MessageQueue::`vftable';
	/* this+ 4 */ RTL_CRITICAL_SECTION m_CS;
	/* this+28 */ std::deque<N3MessageQueue::lcData> m_Queue;
	/* this+52 */ HANDLE m_hSemaphore;
	/* this+56 */ bool m_bOK;
};
