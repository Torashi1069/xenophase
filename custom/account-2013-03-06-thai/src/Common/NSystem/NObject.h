#pragma once


class NObject
{
public:
	enum
	{
		AccountServerMgr            = 0,
		ASYNC_BILLING_THREAD        = 1,
		ASYNC_BILLING_WORKER_THREAD = 2,
		SHUTDOWN_POLICY_THREAD      = 3,
		ENTER_QUEUE_THREAD          = 4,
		COMMON_THREAD               = 5,
		CASyncLogDBThread           = 6,
	};

public:
	const unsigned int GetMyID() const;
	NObject();
	virtual ~NObject();

private:
	/* this+0 */ //const NObject::`vftable';
	/* this+4 */ const unsigned int m_MyID;
};
