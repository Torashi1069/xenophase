#include "CUserStreamMgr.h"
#include "Common/EnterTraceLog.h"
#include "Common/NOutputTextMgr.h"
#include "Common/NSystem/NIPAddr.h"


CUserStreamMgr::CUserStreamMgr()
: m_ListenIPAddr("127.0.0.1"), m_ListenPortNum(5000)
{
}


CUserStreamMgr::~CUserStreamMgr()
{
}


bool CUserStreamMgr::Listen(WORD port, int nBackLog, DWORD dwPingTime, DWORD dwListenIP)
{
	m_ListenIPAddr = dwListenIP;
	m_ListenPortNum = port;

	if( !this->CStreamManager::Listen(port, nBackLog, dwPingTime, dwListenIP) )
		return false;

	NOutputTextMgr::GetObj()->NOutputTextMgr::InsertFmt("[listen] client %s:%d", NIPAddapter(dwListenIP), port);
	CEnterTraceLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__, "[listen] client %s:%d", NIPAddapter(dwListenIP), port);
	return true;
}


NIPAddr CUserStreamMgr::GetListenIPAddr() const
{
	return m_ListenIPAddr;
}


int CUserStreamMgr::GetListenPortNum() const
{
	return m_ListenPortNum;
}
