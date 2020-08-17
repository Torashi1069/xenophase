#pragma once
#include "shared/ODBC.h"


enum DWORDPROCTABLE
{
	SP_Level          = 0,
	SP_Name           = 1,
	SP_MName          = 2,
	SP_MaxUserNum     = 3,
	SP_Honor          = 4,
	SP_Virtue         = 5,
	SP_Type           = 6,
	SP_Class          = 7,
	SP_Money          = 8,
	SP_ArenaWin       = 9,
	SP_ArenaLose      = 10,
	SP_ArenaDrawn     = 11,
	SP_ManageLand     = 12,
	SP_Exp            = 13,
	SP_Emblem         = 14,
	SP_Point          = 15,
	SP_Desc           = 16,
	SP_MCharName      = 17,
	SP_MClass         = 18,
	SP_MLevel         = 19,
	SP_MMemo          = 20,
	SP_MService       = 21,
	SP_MExp           = 22,
	SP_MAID           = 23,
	SP_MPositionID    = 24,
	SP_MGDID          = 25,
	SP_MGID           = 26,
	SP_OpponentGDID   = 27,
	SP_Relation       = 28,
	SP_Notice         = 29,
	SP_BMemberName    = 30,
	SP_BMemberAccount = 31,
	SP_BReason        = 32,
	SP_BGID           = 33,
	SP_BAID           = 34,
	SP_MPGrade        = 35,
	SP_MPPos          = 36,
	SP_MPJoinRight    = 37,
	SP_MPPenaltyRight = 38,
	SP_MPPositionID   = 39,
};


class CGuildDB : public CODBC
{
public:
	CGuildDB();
	virtual ~CGuildDB();

public:
	BOOL Init(const char* dsnFile, const char* PASS);
	DWORD GetTableDWORD(unsigned long GDID, int Type);
	int GetGuildList(int AID, int GID, int GDID, int& buflen, char* buf, int ); //TODO
	void GetTableChar(unsigned long GDID, int Type, char* Data, int Length);
	int UpdateTableChar(unsigned long GDID, char* , int ); //TODO
	int UpdateTableDWORD(unsigned long GDID, DWORD , int ); //TODO
	int GetGuildID(char* GName);

private:
	DWORD GetDWORD(unsigned long GDID, char* StoredProc);
	void GetChar(unsigned long GDID, char* StoredProc, char* Data, int Length);
	void InitStoredProcTable();

private:
	/* this+ 0 */ //CODBC baseclass_0;
	/* this+20 */ std::map<int,char*> m_getProcTable;
};
