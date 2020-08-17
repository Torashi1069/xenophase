#pragma once
#include "Memorial Dungeon/MemorialDungeonDBLog.h"
#include "shared/N2System/ODBC(open database connectivity)/N2ODBCCtrl.h"


class CMemorialDungeonDBLogMgr
{
private:
	/* static  */ static CMemorialDungeonDBLogMgr*& m_cpSelf; //TODO
	/* this+ 0 */ //const CMemorialDungeonDBLogMgr::`vftable';
	/* this+ 4 */ bool m_bOK;
	/* this+ 8 */ N2ODBCCtrl m_ODBCCtrl;

private:
	bool Create();
	void Destroy();

public:
	bool isOK() const;
	void Add(const CMemorialDungeonDBLog::enumTYPE in_Type, const std::string in_MemorialDungeonName, const std::string in_PartyName, const int in_PartyID, const int in_ZSID);

public:
	static bool CreateInstance();
	static void DestroyInstance();
	static CMemorialDungeonDBLogMgr* GetObj(); /// @custom

private:
	CMemorialDungeonDBLogMgr();
	virtual ~CMemorialDungeonDBLogMgr();
};
