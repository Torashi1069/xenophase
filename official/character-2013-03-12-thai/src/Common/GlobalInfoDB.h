#pragma once
#include "Common/Database.h"


class CGlobalInfoDB : public CDatabase
{
private:
	void InitColumnInfo();

public:
	void InitServerInfoList(bool bLogInfo);
	bool IsColumnPrivateAdded();
//	int EventResult(int);
//	std::string GetWorldName(const int);
//	bool GetWorldName(const int, char*, const int);
//	int GetEventItemCount(const int, const int);
//	int GetEventItemCount(const int);
//	int GetBlockedUser(const int, int &, int &, char *);
//	bool GetUserBlockList(std::vector<DWORD>* const);
//	void DeleteBlockedUser(const int);

public:
	CGlobalInfoDB();
	~CGlobalInfoDB();

private:
	/* this+ 0 */ //CDatabase baseclass_0;
	/* this+36 */ bool m_bIsColumnPrivateAdded;
};
