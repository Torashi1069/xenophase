#pragma once
#include "Common/Database.h"
#include "Common/Singleton.h"


class CGlobalInfoDB : public CDatabase, public CSingleton<CGlobalInfoDB>
{
private:
	void InitColumnInfo();

public:
	CGlobalInfoDB();
	~CGlobalInfoDB();

public:
	void InitServerInfoList(bool bLogInfo);
	bool IsColumnPrivateAdded();
//	int EventResult(int);

private:
	/* this+   0 */ //CDatabase baseclass_0;
	/* this+2056 */ //CSingleton<CGlobalInfoDB> baseclass_2056;
	/* this+2056 */ bool m_bIsColumnPrivateAdded;
};
