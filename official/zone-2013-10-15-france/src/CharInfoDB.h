#pragma once
#include "shared/ODBC.h"
struct MannerPointData;


class CCharInfoDB : public CODBC
{
public:
	CCharInfoDB();
	~CCharInfoDB();

public:
	void UpdateItemStoreMoney(int AID, int money);
	void DeleteItem(int GID);
	void GetCharacterName(int GID, char* charname);
	BOOL LoadMPInfo(unsigned long AID, std::list<MannerPointData>* info, int& LastDate);
	void DeleteMP(unsigned long AID, unsigned long otherGID);
	BOOL InsertNewMP(unsigned long AID, unsigned long otherGID, int type);
	BOOL GetCharacterID(char* Name, unsigned long& AID, unsigned long& GID);
	BOOL UpdatePVPEvent(char* GID, char* Name);
	BOOL GetPVPEvent(char* GID, char* Name);
	void GetErrorString(SQLHSTMT hStmt, char* lpszError);
	int GetShortCutKey(unsigned long GID, unsigned char* pShortCutKey);
	int UpdateShortCutKey(unsigned long GID, unsigned char* pShortCutKey);
	int InsertHuntingList(int GID);
	int InsertTimeList(int GID);
	int SelectHuntingList(unsigned long GID, unsigned char* buf);
	int UpdateHuntingList(unsigned long GID, unsigned char* buf, int size);
	int SelectTimeList(unsigned long GID, unsigned char* buf);
	int UpdateTimeList(unsigned long GID, unsigned char* buf, int size);
};
