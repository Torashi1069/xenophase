#include "UserLogMgr.h"


CUserLogMgr::CUserLogMgr()
{
}


CUserLogMgr::~CUserLogMgr()
{
}


void CUserLogMgr::Init()
{
	m_LogIdleTime = timeGetTime();
}


void CUserLogMgr::OnProcess()
{
	// 25 lines disabled here
}
