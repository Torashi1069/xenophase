#pragma once


class CIsvrSchedulerIdentity
{
public:
	bool isOK() const;

	enum
	{
		TASK_NONE  = 0,
		TASK_PING  = 1,
		TASK_STATE = 2,
		TASK_LAST  = 3,
	};

	unsigned int Get();

public:
	static bool CreateInstance();
	static void DestroyInstance();
	static CIsvrSchedulerIdentity* GetObj(); /// @custom

private:
	CIsvrSchedulerIdentity();
	virtual ~CIsvrSchedulerIdentity();
	CIsvrSchedulerIdentity(CIsvrSchedulerIdentity&); // = delete;
	CIsvrSchedulerIdentity& operator=(const CIsvrSchedulerIdentity&); // = delete;

private:
	/* static */ static CIsvrSchedulerIdentity*& m_cpSelf; //TODO
	/* this+0 */ //const CIsvrSchedulerIdentity::`vftable';
	/* this+4 */ bool m_bOK;
	/* this+8 */ unsigned int m_IdentityCnt;
};
