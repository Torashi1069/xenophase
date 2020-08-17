#pragma once
#include "ODBC.h"


class CGlobalVarDB : public CODBC
{
public:
	public: CGlobalVarDB::CGlobalVarDB(void);
	public: virtual CGlobalVarDB::~CGlobalVarDB(void);
	public: int CGlobalVarDB::CreateGlobalVar(const char* name, int value);
	public: int CGlobalVarDB::GetGlobalVar(const char* name, int& value);
	public: int CGlobalVarDB::SetGlobalVar(const char* name, int value);
	public: bool CGlobalVarDB::CreateGlobalStr(const char* name, char* value);
	public: bool CGlobalVarDB::GetGlobalStr(const char* name, char* value);
	public: bool CGlobalVarDB::SetGlobalStr(const char* name, char* value);
private:
	static hook_method<int (CGlobalVarDB::*)(const char* name, int value)> CGlobalVarDB::_CreateGlobalVar;
	static hook_method<int (CGlobalVarDB::*)(const char* name, int& value)> CGlobalVarDB::_GetGlobalVar;
	static hook_method<int (CGlobalVarDB::*)(const char* name, int value)> CGlobalVarDB::_SetGlobalVar;
	static hook_method<bool (CGlobalVarDB::*)(const char* name, char* value)> CGlobalVarDB::_CreateGlobalStr;
	static hook_method<bool (CGlobalVarDB::*)(const char* name, char* value)> CGlobalVarDB::_GetGlobalStr;
	static hook_method<bool (CGlobalVarDB::*)(const char* name, char* value)> CGlobalVarDB::_SetGlobalStr;
};
