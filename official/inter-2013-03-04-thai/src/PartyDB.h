#pragma once
#include "shared/ODBC.h"


enum enumMAKEGROUPRETCODE
{
	GROUP_MAKE_SUCCEED                    = 0,
	GROUP_MAKE_FAILED_SAMENAME            = 1,
	GROUP_MAKE_FAILED_ALEADY_GROUP_MEMBER = 2,
	GROUP_MAKE_FAILED_INVALID_MAPPROPERTY = 3,
};


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
private:
	struct RULE_VALUE
	{
		/* this(bf)+0:0 len(1) */ unsigned int ItemPickupRule   : 1;
		/* this(bf)+0:1 len(1) */ unsigned int ItemDivisionRule : 1;
		/* this(bf)+0:2 len(2) */ unsigned int expOption        : 2; // enumGROUPEXPOPTION
	};

	union PARTY_RULE_VALUE
	{
		/* this+0 */ RULE_VALUE RuleValue;
		/* this+0 */ int DBValue;
	};

public:
	unsigned long MakeGroup(unsigned long AID, unsigned long GID, const char* name);
	unsigned long MakeGroup(unsigned long AID, unsigned long GID, const char* name, bool ItemPickupRule, bool ItemDivisionRule);
	void GetGroupName(unsigned long GRID, char* name);
	void GetGroupInfo(unsigned long GRID, char* name, bool& ItemPickupRule, bool& ItemDivisionRule);
	BOOL DeleteGroup(unsigned long GRID);
	BOOL DeleteGroup(char* name);
	unsigned long GetGroupID(const char* name);
	int GetGroupMembers(const unsigned long in_GRID, DBGROUPINFO* const in_pGroupInfoArray, const int in_GroupInfoArrayNum);
	BOOL InsertMember(unsigned long GID, unsigned long AID, unsigned long GRID, char* charName, int Role);
	BOOL DeleteMember(unsigned long GID);
	BOOL DeleteMemberByName(char* name);
	unsigned long SearchMember(unsigned long GID);
	void UpdateMemberRole(unsigned long in_GRID, unsigned long in_firstGID, int in_firstRole, unsigned long in_secondGID, int in_secondRole);

public:
	static bool CreateInstance();
	static void DestroyInstance();
	static CPartyDB* GetObj(); /// @custom

private:
	CPartyDB();
	virtual ~CPartyDB();

private:
	/* static */ static CPartyDB*& m_cpSelf; //TODO
};
