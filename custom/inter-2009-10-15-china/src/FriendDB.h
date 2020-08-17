#pragma once
#include "ODBC.h"
#include "structs.hpp" // STRUCT_FRIEND


class CFriendDB : public CODBC
{
	/* this+0 */ public: //CODBC baseclass_0;

	public: CFriendDB::CFriendDB(void);
	public: virtual CFriendDB::~CFriendDB(void);
	public: void CFriendDB::DropFriend(unsigned long GID);
	public: int CFriendDB::LoadFriend(unsigned long GID, STRUCT_FRIEND* pFriend);
	public: void CFriendDB::SaveFriend(unsigned long GID, STRUCT_FRIEND* pFriend, int Number);

private:
	static hook_method<void (CFriendDB::*)(unsigned long GID)> CFriendDB::_DropFriend;
	static hook_method<int (CFriendDB::*)(unsigned long GID, STRUCT_FRIEND* pFriend)> CFriendDB::_LoadFriend;
	static hook_method<void (CFriendDB::*)(unsigned long GID, STRUCT_FRIEND* pFriend, int Number)> CFriendDB::_SaveFriend;
};
