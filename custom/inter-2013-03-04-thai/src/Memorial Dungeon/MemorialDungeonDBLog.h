#pragma once
#include "shared/N2System/DBLog/N2DBLog.h"


class CMemorialDungeonDBLog : public N2DBLog
{
public:
	enum enumTYPE
	{
		TYPE_SUBSCRIPTION                       = 0,
		TYPE_SUBSCRIPTION_CANCEL_BY_USER        = 1,
		TYPE_SUBSCRIPTION_CANCEL_BY_CREATE_FAIL = 2,
		TYPE_CREATE                             = 3,
		TYPE_DESTROY_BY_USER                    = 4,
		TYPE_DESTROY_BY_LIVETIME                = 5,
		TYPE_DESTROY_BY_ENTERTIME               = 6,
	};

private:
	/* this+ 0 */ //N2DBLog baseclass_0;
	/* this+ 8 */ bool m_bOK;
	/* this+12 */ const enumTYPE m_Type;
	/* this+16 */ const std::string m_MemorialDungeonName;
	/* this+44 */ const std::string m_PartyName;
	/* this+72 */ const int m_PartyID;
	/* this+76 */ const int m_CreateZSID;

private:
	virtual bool Run(N2ODBCCtrl& in_ODBCCtrl);

public:
	bool isOK() const;

public:
	CMemorialDungeonDBLog(const enumTYPE in_Type, const std::string in_MemorialDungeonName, const std::string in_PartyName, const int in_PartyID, const int in_CreateZSID);
	virtual ~CMemorialDungeonDBLog();
};
