#include "Common/CriticalSection.h"
#include "Common/Database.h"
#include "Common/Singleton.h"


class CWucsDB : public CDatabase, public CSingleton<CWucsDB>
{
private:
	/* this+ 0 */ //CDatabase baseclass_0;
	/* this+37 */ //CSingleton<CWucsDB> baseclass_37;
	/* this+40 */ CCriticalSection m_csSyncObj;

public:
	CWucsDB();
	~CWucsDB();
//	int InsertUserCountLog(int, char*, char*, int);
};
