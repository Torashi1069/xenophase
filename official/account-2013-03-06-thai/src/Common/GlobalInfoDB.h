#pragma once
#include "Common/Database.h"


class CGlobalInfoDB : public CDatabase
{
private:
	void InitColumnInfo();

public:
	void InitServerInfoList(bool bLogInfo);
	bool IsColumnPrivateAdded();
	int EventResult(int ); //TODO
	bool GetWorldName(const int , char* , const int ); //TODO
	std::string GetWorldName(const int ); //TODO
	int GetEventItemCount(const int ); //TODO
	int GetEventItemCount(const int iAID, const int nServerType);
	int GetBlockedUser(const int nAID, int& nBlockType, int& nReason, char* szBlockDate);
	bool GetUserBlockList(std::vector<DWORD>* const list);
	void DeleteBlockedUser(const int nAID);

public:
	static bool CreateInstance();
	static void DestroyInstance();
	static CGlobalInfoDB* GetObj();
	bool isOK() const;
	
private:
	CGlobalInfoDB();
	~CGlobalInfoDB();
	CGlobalInfoDB(CGlobalInfoDB&); // = delete;
	CGlobalInfoDB& operator=(CGlobalInfoDB&); // = delete;

private:
	/* this+ 0 */ //CDatabase baseclass_0;
	/* this+36 */ bool m_bIsColumnPrivateAdded;
	/* this+37 */ bool m_bOK;
	/* static  */ static CGlobalInfoDB* m_cpSelf;
};
