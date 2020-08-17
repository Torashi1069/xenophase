#pragma once
#include "shared/ODBC.h"


struct STRUCT_FRIEND
{
	/* this+0 */ unsigned long AID;
	/* this+4 */ unsigned long GID;
	/* this+8 */ char Name[24];
};


class CFriendDB : public CODBC
{
public:
	void DropFriend(unsigned long GID);
	int LoadFriend(unsigned long GID, STRUCT_FRIEND* pFriend);
	void SaveFriend(unsigned long GID, STRUCT_FRIEND* pFriend, int Number);

public:
	CFriendDB();
	virtual ~CFriendDB();
};
