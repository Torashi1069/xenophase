#pragma once
#include "ODBC.h"


struct DBGROUPINFO
{
	/* this+ 0 */ unsigned long AID;
	/* this+ 4 */ unsigned long GID;
	/* this+ 8 */ unsigned long GRID;
	/* this+12 */ char name[24];
	/* this+36 */ unsigned long Role;
};


class CPartyDB : public CODBC
{
	/* this+0 */ public: //CODBC baseclass_0;

	struct RULE_VALUE
	{
		/* this(bf)+0x0:0x0 len(0x1) */ unsigned int ItemPickupRule : 1,
		/* this(bf)+0x0:0x1 len(0x1) */              ItemDivisionRule : 1,
		/* this(bf)+0x0:0x2 len(0x2) */              expOption : 2;
	};

	union PARTY_RULE_VALUE
	{
		/* this+0 */ CPartyDB::RULE_VALUE RuleValue;
		/* this+0 */ int DBValue;
	};

	public: CPartyDB::CPartyDB(void);
	public: CPartyDB::~CPartyDB(void);
	public: unsigned long CPartyDB::MakeGroup(unsigned long AID, unsigned long GID, const char* name, unsigned char ItemPickupRule, unsigned char ItemDivisionRule);
	public: unsigned long CPartyDB::MakeGroup(unsigned long AID, unsigned long GID, const char* name);
	public: void CPartyDB::GetGroupName(unsigned long GRID, char* name);
	public: void CPartyDB::GetGroupInfo(unsigned long GRID, char* name, unsigned char& ItemPickupRule, unsigned char& ItemDivisionRule);
	public: int CPartyDB::DeleteGroup(char* name);
	public: int CPartyDB::DeleteGroup(unsigned long GRID);
	public: unsigned long CPartyDB::GetGroupID(const char* name);
	public: int CPartyDB::GetGroupMembers(const unsigned long in_GRID, DBGROUPINFO* const in_pGroupInfoArray, const int in_GroupInfoArrayNum);
	public: int CPartyDB::InsertMember(unsigned long GID, unsigned long AID, unsigned long GRID, char* charName, int Role);
	public: int CPartyDB::DeleteMember(unsigned long GID);
	public: int CPartyDB::DeleteMemberByName(char* name);
	public: unsigned long CPartyDB::SearchMember(unsigned long GID);

private:
	static hook_method<unsigned long (CPartyDB::*)(unsigned long AID, unsigned long GID, const char* name, unsigned char ItemPickupRule, unsigned char ItemDivisionRule)> CPartyDB::_MakeGroup;
	static hook_method<unsigned long (CPartyDB::*)(unsigned long AID, unsigned long GID, const char* name)> CPartyDB::_MakeGroup2;
	static hook_method<void (CPartyDB::*)(unsigned long GRID, char* name)> CPartyDB::_GetGroupName;
	static hook_method<void (CPartyDB::*)(unsigned long GRID, char* name, unsigned char& ItemPickupRule, unsigned char& ItemDivisionRule)> CPartyDB::_GetGroupInfo;
	static hook_method<int (CPartyDB::*)(char* name)> CPartyDB::_DeleteGroup;
	static hook_method<int (CPartyDB::*)(unsigned long GRID)> CPartyDB::_DeleteGroup2;
	static hook_method<unsigned long (CPartyDB::*)(const char* name)> CPartyDB::_GetGroupID;
	static hook_method<int (CPartyDB::*)(const unsigned long in_GRID, DBGROUPINFO* const in_pGroupInfoArray, const int in_GroupInfoArrayNum)> CPartyDB::_GetGroupMembers;
	static hook_method<int (CPartyDB::*)(unsigned long GID, unsigned long AID, unsigned long GRID, char* charName, int Role)> CPartyDB::_InsertMember;
	static hook_method<int (CPartyDB::*)(unsigned long GID)> CPartyDB::_DeleteMember;
	static hook_method<int (CPartyDB::*)(char* name)> CPartyDB::_DeleteMemberByName;
	static hook_method<unsigned long (CPartyDB::*)(unsigned long GID)> CPartyDB::_SearchMember;
};
