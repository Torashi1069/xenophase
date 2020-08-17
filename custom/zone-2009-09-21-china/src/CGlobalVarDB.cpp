#include "CGlobalVarDB.hpp"


CGlobalVarDB::CGlobalVarDB(void)
{
}


CGlobalVarDB::~CGlobalVarDB(void)
{
}


hook_method<int (CGlobalVarDB::*)(const char* name, int value)> CGlobalVarDB::_CreateGlobalVar(SERVER, "CGlobalVarDB::CreateGlobalVar");
int CGlobalVarDB::CreateGlobalVar(const char* name, int value)
{
	return (this->*_CreateGlobalVar)(name, value);

	//TODO
}


hook_method<int (CGlobalVarDB::*)(const char* name, int& value)> CGlobalVarDB::_GetGlobalVar(SERVER, "CGlobalVarDB::GetGlobalVar");
int CGlobalVarDB::GetGlobalVar(const char* name, int& value)
{
	return (this->*_GetGlobalVar)(name, value);

	//TODO
}


hook_method<int (CGlobalVarDB::*)(const char* name, int value)> CGlobalVarDB::_SetGlobalVar(SERVER, "CGlobalVarDB::SetGlobalVar");
int CGlobalVarDB::SetGlobalVar(const char* name, int value)
{
	return (this->*_SetGlobalVar)(name, value);

	//TODO
}


hook_method<bool (CGlobalVarDB::*)(const char* name, char* value)> CGlobalVarDB::_CreateGlobalStr(SERVER, "CGlobalVarDB::CreateGlobalStr");
bool CGlobalVarDB::CreateGlobalStr(const char* name, char* value)
{
	return (this->*_CreateGlobalStr)(name, value);

	//TODO
}


hook_method<bool (CGlobalVarDB::*)(const char* name, char* value)> CGlobalVarDB::_GetGlobalStr(SERVER, "CGlobalVarDB::GetGlobalStr");
bool CGlobalVarDB::GetGlobalStr(const char* name, char* value)
{
	return (this->*_GetGlobalStr)(name, value);

	//TODO
}


hook_method<bool (CGlobalVarDB::*)(const char* name, char* value)> CGlobalVarDB::_SetGlobalStr(SERVER, "CGlobalVarDB::SetGlobalStr");
bool CGlobalVarDB::SetGlobalStr(const char* name, char* value)
{
	return (this->*_SetGlobalStr)(name, value);

	//TODO
}
