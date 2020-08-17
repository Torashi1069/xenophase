#pragma once
#include "shared/ODBC.h"


class CGlobalVarDB : public CODBC
{
public:
	CGlobalVarDB();
	virtual ~CGlobalVarDB();

public:
	int CreateGlobalVar(const char* name, int value);
	int GetGlobalVar(const char* name, int& value);
	int SetGlobalVar(const char* name, int value);
	int IncGlobalVar(const char* in_Name, int in_nValue);
	int DecGlobalVar(const char* in_Name, int in_nValue);
	bool CreateGlobalStr(const char* name, char* value);
	bool GetGlobalStr(const char* name, char* value);
	bool SetGlobalStr(const char* name, char* value);
};
