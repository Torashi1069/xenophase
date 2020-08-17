#include "PetLog.h"
#include "globals.hpp"


hook_method<void (CPetLog::*)(const unsigned long in_GID, const PET_PROPERTY in_petProperty, const char* in_mapName, const int in_logType)> CPetLog::_AddPetLog(SERVER, "CPetLog::AddPetLog");
void CPetLog::AddPetLog(const unsigned long in_GID, const PET_PROPERTY in_petProperty, const char* in_mapName, const int in_logType) // line 14
{
	return (this->*_AddPetLog)(in_GID, in_petProperty, in_mapName, in_logType);

	//TODO
}


hook_method<void (CPetLog::*)(const char* Log)> CPetLog::_ConnectToDatabase(SERVER, "CPetLog::ConnectToDatabase");
void CPetLog::ConnectToDatabase(const char* Log) // line 10
{
	return (this->*_ConnectToDatabase)(Log);

	this->CExtendedODBC::Connect("Loger", g_dbPWD, Log, 0, "");
}


hook_method<int (CPetLog::*)(SQLHSTMT hStmt, SPETLOG* pLog)> CPetLog::_SaveToDatabase(SERVER, "CPetLog::SaveToDatabase");
int CPetLog::SaveToDatabase(SQLHSTMT hStmt, SPETLOG* pLog) // line 22
{
	return (this->*_SaveToDatabase)(hStmt, pLog);

	//TODO
}
