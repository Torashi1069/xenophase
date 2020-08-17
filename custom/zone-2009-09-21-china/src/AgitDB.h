#pragma once
#include "ODBC.h"
#include "struct.hpp"
#include "std/vector"


class CAgitDB : public CODBC
{
public:
	/* this+0 */ public: //CAgitDB baseclass_0;

	public: CAgitDB::CAgitDB(void);
	public: virtual CAgitDB::~CAgitDB(void);
	public: int CAgitDB::Update(const char* mapName, AGIT_DBINFO* pInfo);
	public: int CAgitDB::Get(mystd::vector<AGIT_DBINFO*>& vt);

private:
	static hook_method<int (CAgitDB::*)(const char* mapName, AGIT_DBINFO* pInfo)> CAgitDB::_Update;
	static hook_method<int (CAgitDB::*)(mystd::vector<AGIT_DBINFO*>& vt)> CAgitDB::_Get;
};
