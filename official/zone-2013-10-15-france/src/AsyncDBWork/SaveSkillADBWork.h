#pragma once
#include "AsyncDBWork/NAsyncDBWork.h"


class CSaveSkillADBWork : public NAsyncDBWork
{
public:
	enum enumResult
	{
		RESULT_SUCCESS          = 0,
		RESULT_ERROR_UNKNOWN    = 1,
		RESULT_ERROR_SAVE_SKILL = 2,
	};

private:
	/* this+  0 */ //NAsyncDBWork baseclass_0;
	/* this+ 20 */ const unsigned long m_AID;
	/* this+ 24 */ const unsigned long m_GID;
	/* this+ 28 */ enumResult m_Result;
public:
	/* this+ 32 */ unsigned char m_Data[512];
	/* this+544 */ int m_Length;

public:
	const unsigned long GetGID() const;
	const unsigned long GetAID() const;
	const enumResult GetResult() const;

private:
	virtual bool ExecQuery(NODBCCtrl& in_ODBCCtrl);
	NAsyncDBWork::enumRETURN SaveSkill(NODBCCtrl& in_ODBCCtrl);

public:
	CSaveSkillADBWork(const unsigned long in_AID, const unsigned long in_GID);
	virtual ~CSaveSkillADBWork();
};
