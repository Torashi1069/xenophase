#pragma once
#include "shared/ODBC.h"


class CUserLogDB : public CODBC
{
public:
	CUserLogDB();
	virtual ~CUserLogDB();

public:
	BOOL InsertZoneUserLog(int SID, int DestSID, int UserNum);
	BOOL InsertInterUserLog(int SID, int UserNum);
};
