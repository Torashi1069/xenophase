#include "GuildDB.h"


hook_method<int (CGuildDB::*)(const char* DSN, const char* UID, const char* PASS, const char* DB, unsigned char type)> CGuildDB::_Init(SERVER, "CGuildDB::Init");
int CGuildDB::Init(const char* DSN, const char* UID, const char* PASS, const char* DB, unsigned char type) // line 176
{
	return (this->*_Init)(DSN, UID, PASS, DB, type);

	//TODO
}


hook_method<void (CGuildDB::*)(unsigned long GDID, int Type, char* Data, int Length)> CGuildDB::_GetTableChar(SERVER, "CGuildDB::GetTableChar");
void CGuildDB::GetTableChar(unsigned long GDID, int Type, char* Data, int Length)
{
	return (this->*_GetTableChar)(GDID, Type, Data, Length);

	//TODO
}
