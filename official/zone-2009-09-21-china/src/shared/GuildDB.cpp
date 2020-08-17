#include "GuildDB.h"


CGuildDB::CGuildDB(void)
{
	this->CGuildDB::InitStoredProcTable();
}


CGuildDB::~CGuildDB(void)
{
	this->CODBC::Reset();
}


hook_method<int (CGuildDB::*)(const char* DSN, const char* UID, const char* PASS, const char* DB, char type)> CGuildDB::_Init(SERVER, "CGuildDB::Init");
int CGuildDB::Init(const char* DSN, const char* UID, const char* PASS, const char* DB, char type)
{
	return (this->*_Init)(DSN, UID, PASS, DB, type);

	//TODO
}


/* hook_method<unsigned long (CGuildDB::*)(unsigned long GDID, int Type)> CGuildDB::_GetTableDWORD(SERVER, "CGuildDB::GetTableDWORD");
unsigned long CGuildDB::GetTableDWORD(unsigned long GDID, int Type)
{
	return (this->*_GetTableDWORD)(GDID, Type);

	//TODO
} */


/* hook_method<void (CGuildDB::*)(unsigned long GDID, int Type, char* Data, int Length)> CGuildDB::_GetTableChar(SERVER, "CGuildDB::GetTableChar");
void CGuildDB::GetTableChar(unsigned long GDID, int Type, char* Data, int Length)
{
	return (this->*_GetTableChar)(GDID, Type, Data, Length);

	//TODO
} */


/* hook_method<int (CGuildDB::*)(int AID, int GID, int GDID, int& buflen, char* buf)> CGuildDB::_GetGuildList(SERVER, "CGuildDB::GetGuildList");
int CGuildDB::GetGuildList(int AID, int GID, int GDID, int& buflen, char* buf)
{
	return (this->*_GetGuildList)(AID, GID, GDID, buflen, buf);

	//TODO
} */


/* hook_method<int (CGuildDB::*)(char* GName)> CGuildDB::_GetGuildID(SERVER, "CGuildDB::GetGuildID");
int CGuildDB::GetGuildID(char* GName)
{
	return (this->*_GetGuildID)(GName);

	//TODO
} */


/* hook_method<unsigned long (CGuildDB::*)(unsigned long GDID, char* StoredProc)> CGuildDB::_GetDWORD(SERVER, "CGuildDB::GetDWORD");
unsigned long CGuildDB::GetDWORD(unsigned long GDID, char* StoredProc)
{
	return (this->*_GetDWORD)(GDID, StoredProc);

	//TODO
} */


/* hook_method<void (CGuildDB::*)(unsigned long GDID, char* StoredProc, char* Data, int Length)> CGuildDB::_GetChar(SERVER, "CGuildDB::GetChar");
void CGuildDB::GetChar(unsigned long GDID, char* StoredProc, char* Data, int Length)
{
	return (this->*_GetChar)(GDID, StoredProc, Data, Length);

	//TODO
} */


hook_method<void (CGuildDB::*)(void)> CGuildDB::_InitStoredProcTable(SERVER, "CGuildDB::InitStoredProcTable");
void CGuildDB::InitStoredProcTable(void)
{
	return (this->*_InitStoredProcTable)();

	//TODO
}
