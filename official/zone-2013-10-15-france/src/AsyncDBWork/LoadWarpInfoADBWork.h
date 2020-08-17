#pragma once
#include "PCSkill.h" // WARPPORTAL_INFO
#include "AsyncDBWork/NAsyncDBWork.h"


class CLoadWarpInfoADBWork : public NAsyncDBWork
{
public:
	enum enumResult
	{
		RESULT_SUCCESS       = 0,
		RESULT_ERROR_UNKNOWN = 1,
	};

	enum
	{
		LOAD_TYPE_PORTAL     = 0,
		LOAD_TYPE_STAR_PLACE = 1,
	};

public:
	const enumResult GetResult();
	const unsigned long GetGID();
	const WARPPORTAL_INFO& GetWarpInfo();
	const int GetLoadType();

private:
	/* this+ 0 */ //NAsyncDBWork baseclass_0;
	/* this+20 */ enumResult m_Result;
	/* this+24 */ int m_LoadType;
	/* this+28 */ const unsigned long m_GID;
	/* this+32 */ WARPPORTAL_INFO m_WarpInfo;

private:
	virtual bool ExecQuery(NODBCCtrl& in_CharacterODBCCtrl);

public:
	CLoadWarpInfoADBWork(const unsigned long in_AID, const unsigned long in_GID, const int in_LoadType);
	virtual ~CLoadWarpInfoADBWork();
};
