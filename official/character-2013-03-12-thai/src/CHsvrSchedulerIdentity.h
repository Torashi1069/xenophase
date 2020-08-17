#pragma once


class CHsvrSchedulerIdentity
{
public:
	bool isOK() const;

	enum
	{
		TASK_NONE = 0,
		TASK_PING = 1,
		TASK_LAST = 2,
	};

	unsigned int Get();

public:
	static bool CreateInstance();
	static void DestroyInstance();

private:
	CHsvrSchedulerIdentity();
	virtual ~CHsvrSchedulerIdentity();

private:
	/* this+0 */ //const CHsvrSchedulerIdentity::`vftable';
	/* this+4 */ bool m_bOK;
	/* this+8 */ unsigned int m_IdentityCnt;
	/* static */ static CHsvrSchedulerIdentity* m_cpSelf;
};
