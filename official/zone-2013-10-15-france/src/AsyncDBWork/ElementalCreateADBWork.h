#pragma once
#include "AsyncDBWork/NAsyncDBWork.h"
#include "NPCElemental.h"


class CElementalCreateADBWork : public NAsyncDBWork
{
public:
	enum enumResult
	{
		RESULT_SUCCESS                = 0,
		RESULT_ERROR_UNKNOWN          = 1,
		RESULT_ERROR_ELEMENTAL_CREATE = 2,
	};

public:
	unsigned long GetGID();
	unsigned long GetAID(); //TODO
	enumResult GetResult();
	ElementalStuff::enumKind GetKind();
	ElementalStuff::enumScale GetScale();
	ElementalStuff::ESummaryData GetSummaryData();
	int GetLifeTM();
	int GetReduceSPAmount();

private:
	virtual bool ExecQuery(NODBCCtrl& in_ODBCCtrl);
	NAsyncDBWork::enumRETURN Create(NODBCCtrl& in_ODBCCtrl);

public:
	CElementalCreateADBWork(const unsigned long in_AID, const unsigned long in_GID, const ElementalStuff::enumKind in_Kind, const ElementalStuff::enumScale in_Scale, const ElementalStuff::ESummaryData& in_SummaryData, const int in_LifeTM, const int in_ReduceSPAmount);
	virtual ~CElementalCreateADBWork();

private:
	/* this+0 */ //NAsyncDBWork baseclass_0;
	/* this+20 */ enumResult m_Result;
	/* this+24 */ const unsigned long m_GID;
	/* this+28 */ const ElementalStuff::enumKind m_Kind;
	/* this+32 */ const ElementalStuff::enumScale m_Scale;
	/* this+36 */ const ElementalStuff::ESummaryData m_SummaryData;
	/* this+80 */ const int m_LifeTM;
	/* this+84 */ const int m_ReduceSPAmount;
};
