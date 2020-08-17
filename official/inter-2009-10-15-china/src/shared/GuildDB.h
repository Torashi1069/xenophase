#pragma once
#include "ODBC.h"
#include "std/map"


class CGuildDB : public CODBC
{
	/* this+0x0  */ //CODBC
	/* this+0x14 */ private: mystd::map<int,char*> m_getProcTable;

	//public: void CGuildDB::CGuildDB();
	//public: void CGuildDB::~CGuildDB();
	public: int CGuildDB::Init(const char* DSN, const char* UID, const char* PASS, const char* DB, unsigned char type);
	//public: unsigned long CGuildDB::GetTableDWORD(unsigned long, int);
	public: void CGuildDB::GetTableChar(unsigned long GDID, int Type, char* Data, int Length);
	//public: int UpdateTableChar(unsigned long, char *, int);
	//public: int UpdateTableDWORD(unsigned long, unsigned long, int);
	//public: int CGuildDB::GetGuildList(int, int, int, int &, char *);
	//public: int CGuildDB::GetGuildID(char *);
	//private: unsigned long CGuildDB::GetDWORD(unsigned long, char *);
	//private: void CGuildDB::GetChar(unsigned long, char *, char *, int);
	//private: void CGuildDB::InitStoredProcTable();

private:
	static hook_method<int (CGuildDB::*)(const char* DSN, const char* UID, const char* PASS, const char* DB, unsigned char type)> CGuildDB::_Init;
	static hook_method<void (CGuildDB::*)(unsigned long GDID, int Type, char* Data, int Length)> CGuildDB::_GetTableChar;
};
