#pragma once
#include "Common/Database.h"
#include "Common/Singleton.h"


class CIPInfoDB : public CDatabase, public CSingleton<CIPInfoDB>
{
private:
	/* this+   0 */ //CDatabase baseclass_0;
	/* this+2056 */ //CSingleton<CIPInfoDB> baseclass_2056;

public:
	CIPInfoDB();
	~CIPInfoDB();
	void InitMapInfoList();
};
