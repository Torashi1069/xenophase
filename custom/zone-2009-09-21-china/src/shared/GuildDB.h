#pragma once
#include "ODBC.h"
#include "std/map"


class CGuildDB : public CODBC
{
public:
	/* this+0x0  */ //CODBC
	/* this+0x14 */ private: mystd::map<int,char *> m_getProcTable;

	public: CGuildDB::CGuildDB(void);
	public: virtual CGuildDB::~CGuildDB(void);
	public: int CGuildDB::Init(const char* DSN, const char* UID, const char* PASS, const char* DB, char type);
	public: unsigned long CGuildDB::GetTableDWORD(unsigned long GDID, int Type);
	public: void CGuildDB::GetTableChar(unsigned long GDID, int Type, char* Data, int Length);
	//public: int CGuildDB::UpdateTableChar(unsigned long, char *, int);
	//public: int CGuildDB::UpdateTableDWORD(unsigned long, unsigned long, int);
	public: int CGuildDB::GetGuildList(int AID, int GID, int GDID, int& buflen, char* buf);
	public: int CGuildDB::GetGuildID(char* GName);
	private: unsigned long CGuildDB::GetDWORD(unsigned long GDID, char* StoredProc);
	private: void CGuildDB::GetChar(unsigned long GDID, char* StoredProc, char* Data, int Length);
	private: void CGuildDB::InitStoredProcTable(void);

private:
	static hook_method<int (CGuildDB::*)(const char* DSN, const char* UID, const char* PASS, const char* DB, char type)> CGuildDB::_Init;
	static hook_method<unsigned long (CGuildDB::*)(unsigned long GDID, int Type)> CGuildDB::_GetTableDWORD;
	static hook_method<void (CGuildDB::*)(unsigned long GDID, int Type, char* Data, int Length)> CGuildDB::_GetTableChar;
	static hook_method<int (CGuildDB::*)(int AID, int GID, int GDID, int& buflen, char* buf)> CGuildDB::_GetGuildList;
	static hook_method<int (CGuildDB::*)(char* GName)> CGuildDB::_GetGuildID;
	static hook_method<unsigned long (CGuildDB::*)(unsigned long GDID, char* StoredProc)> CGuildDB::_GetDWORD;
	static hook_method<void (CGuildDB::*)(unsigned long GDID, char* StoredProc, char* Data, int Length)> CGuildDB::_GetChar;
	static hook_method<void (CGuildDB::*)(void)> CGuildDB::_InitStoredProcTable;
};
