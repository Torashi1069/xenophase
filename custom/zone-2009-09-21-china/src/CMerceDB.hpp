#pragma once
#include "ODBC.h"
#include "struct.hpp"


class CMerceDB : public CODBC
{
public:
	//public: void CMerceDB::CMerceDB(void);
	//public: void CMerceDB::~CMerceDB(void);
	public: int CMerceDB::InsertHomunInfo(int GID, HOMUN_DBINFO* info);
	public: int CMerceDB::SaveHomunInfo(int GID, HOMUN_DBINFO* info);
	public: int CMerceDB::GetHomunInfo(int GID, HOMUN_DBINFO* info);
	public: void CMerceDB::DeleteHomunInfo(int GID);
	public: int CMerceDB::InsertSkill_HO(int GID);
	public: void CMerceDB::UpdateSkill_HO(int GID, unsigned char* buf, int bufSize);
	public: int CMerceDB::GetSkill_HO(int GID, unsigned char* buf);
	public: void CMerceDB::DeleteSkill_HO(int GID);

private:
	static hook_method<int (CMerceDB::*)(int GID, HOMUN_DBINFO* info)> CMerceDB::_InsertHomunInfo;
	static hook_method<int (CMerceDB::*)(int GID, HOMUN_DBINFO* info)> CMerceDB::_SaveHomunInfo;
	static hook_method<int (CMerceDB::*)(int GID, HOMUN_DBINFO* info)> CMerceDB::_GetHomunInfo;
	static hook_method<void (CMerceDB::*)(int GID)> CMerceDB::_DeleteHomunInfo;
	static hook_method<int (CMerceDB::*)(int GID)> CMerceDB::_InsertSkill_HO;
	static hook_method<void (CMerceDB::*)(int GID, unsigned char* buf, int bufSize)> CMerceDB::_UpdateSkill_HO;
	static hook_method<int (CMerceDB::*)(int GID, unsigned char* buf)> CMerceDB::_GetSkill_HO;
	static hook_method<void (CMerceDB::*)(int GID)> CMerceDB::_DeleteSkill_HO;
};
