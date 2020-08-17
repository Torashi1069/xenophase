#pragma once


class CZsvrSchedulerIdentity
{
public:
	bool isOK() const;

public:
	enum
	{
		TASK_NONE  = 0,
		TASK_PING  = 1,
		TASK_STATE = 2,
		TASK_LAST  = 3,
	};

public:
	unsigned int Get();

public:
	static bool CreateInstance();
	static void DestroyInstance();
	static CZsvrSchedulerIdentity* GetObj(); /// @custom

private:
	CZsvrSchedulerIdentity();
	virtual ~CZsvrSchedulerIdentity();

private:
	/* static */ static CZsvrSchedulerIdentity*& m_cpSelf; //TODO
	/* this+0 */ //const CZsvrSchedulerIdentity::`vftable';
	/* this+4 */ bool m_bOK;
	/* this+8 */ unsigned int m_IdentityCnt;
};
