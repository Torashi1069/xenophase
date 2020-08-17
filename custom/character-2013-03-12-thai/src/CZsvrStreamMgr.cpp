#include "CZsvrStreamMgr.h"
#include "Common/EnterTraceLog.h"
#include "Common/NOutputTextMgr.h"
#include "Common/NSystem/NIPAddr.h"


CZsvrStreamMgr::CZsvrStreamMgr()
: m_ListenIPAddr("127.0.0.1"), m_ListenPortNum(4000)
{
}


CZsvrStreamMgr::~CZsvrStreamMgr()
{
}


bool CZsvrStreamMgr::Listen(WORD port, int nBackLog, DWORD dwPingTime, DWORD dwListenIP)
{
	m_ListenIPAddr = dwListenIP;
	m_ListenPortNum = port;

	if( !this->CStreamManager::Listen(port, nBackLog, dwPingTime, dwListenIP) )
		return false;

	NOutputTextMgr::GetObj()->NOutputTextMgr::InsertFmt("[listen] ZSVR %s:%d", NIPAddapter(dwListenIP), port);
	CEnterTraceLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__, "[listen] ZSVR %s:%d", NIPAddapter(dwListenIP), port);
	return true;
}


NIPAddr CZsvrStreamMgr::GetListenIPAddr() const
{
    return m_ListenIPAddr;
}


int CZsvrStreamMgr::GetListenPortNum() const
{
	return m_ListenPortNum;
}
