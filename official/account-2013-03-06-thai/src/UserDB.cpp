#include "UserDB.h"


CUserDB::CUserDB()
{
	InitializeCriticalSection(&m_cs);
}


CUserDB::~CUserDB()
{
	DeleteCriticalSection(&m_cs);
}
