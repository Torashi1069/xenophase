#include "NetLib/AsyncStream.h"
#include "ServerManager/CMsvrAcceptHandler.h"
#include "ServerManager/CMsvrMgr.h"
#include "shared/NCriticalErrorLog.h"
#include "shared/NOutputTextMgr.h"
#include "shared/NSystem/NIPAddr.h"
#include "shared/N3System/N3MessageMgr.h"


/// singleton instance
CMsvrMgr*& CMsvrMgr::m_cpSelf = VTOR<CMsvrMgr*>(DetourFindFunction(EXEPATH(), "CMsvrMgr::m_cpSelf"));

/// locals
static int& g_MServerSize = VTOR<int>(DetourFindFunction(EXEPATH(), "g_MServerSize"));


CMsvrMgr::CMsvrMgr()
{
	m_bOK = false;

	N3MessageMgr::GetObj()->N3MessageMgr::Insert(this->N3Object::GetMyID(), this);
	m_bOK = true;
}


CMsvrMgr::~CMsvrMgr()
{
	N3MessageMgr::GetObj()->N3MessageMgr::Remove(this->N3Object::GetMyID(), this);
}


bool CMsvrMgr::CreateInstance()
{
	if( m_cpSelf != NULL )
		return false;

	m_cpSelf = new(std::nothrow) CMsvrMgr();
	if( m_cpSelf == NULL )
		return false;

	if( !m_cpSelf->CMsvrMgr::isOK() )
	{
		delete m_cpSelf;
		m_cpSelf = NULL;
		return false;
	}

	return true;
}


void CMsvrMgr::DestroyInstance()
{
	if( m_cpSelf != NULL )
	{
		delete m_cpSelf;
		m_cpSelf = NULL;
	}
}


CMsvrMgr* CMsvrMgr::GetObj() /// @custom
{
	return m_cpSelf;
}


bool CMsvrMgr::isOK() const
{
	return m_bOK;
}


void CMsvrMgr::Process()
{
	this->CMsvrMgr::ProcessMSG();

	N3SyncObject sync(m_mserverMgr_cs);

	for( std::map<int,CMClient*>::iterator iter = m_mServerMap.begin(); iter != m_mServerMap.end(); )
	{
		CMClient* mserver = iter->second;

		if( mserver->CMClient::OnProcess() != -1 || mserver->CClient::GetErrorCount() >= 4 )
		{
			NOutputTextMgr::GetObj()->NOutputTextMgr::InsertFmt("SVRMGR(%s) disconnected", NIPAddapter(NIPAddr(mserver->CMClient::GetIPaddr())));
			NCriticalErrorLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__, "SVRMGR(%s) disconnected", NIPAddapter(NIPAddr(mserver->CMClient::GetIPaddr())));

			mserver->CMClient::GetAsyncStream()->Close(false);
			CMsvrAcceptHandler::GetObj()->CMsvrAcceptHandler::FreeStream(mserver->CMClient::GetAsyncStream());
			this->CMClientMgr::FreeServer(mserver);

			iter = m_mServerMap.erase(iter);
		}
		else
		{
			++iter;
		}
	}

	g_MServerSize = m_mServerMap.size();
}


int CMsvrMgr::GetClientNumber() const
{
	if( this == NULL )
		return 0;

	N3SyncObject sync(const_cast<RTL_CRITICAL_SECTION&>(m_mserverMgr_cs));

	return m_mServerMap.size();
}


void CMsvrMgr::DeleteServer(int SID)
{
	N3SyncObject sync(m_mserverMgr_cs);

	std::map<int,CMClient*>::iterator iter = m_mServerMap.find(SID);
	if( iter == m_mServerMap.end() )
		return;

	CMClient* mserver = iter->second;

	mserver->CMClient::GetAsyncStream()->Close(false);
	CMsvrAcceptHandler::GetObj()->CMsvrAcceptHandler::FreeStream(mserver->CMClient::GetAsyncStream());
	this->CMClientMgr::FreeServer(mserver);
	m_mServerMap.erase(iter);
}


void CMsvrMgr::ProcessMSG()
{
	if( WaitForSingleObject(m_MessageQueue.N3MessageQueue::GetEventObj(), 0) != WAIT_OBJECT_0 )
		return;

	N3MessageQueue::RETGET ret = m_MessageQueue.N3MessageQueue::Get();
	if( std::tr1::get<0>(ret) != true )
		return;

	unsigned int msg = std::tr1::get<1>(ret);
	SOCKET s = std::tr1::get<2>(ret);
	ULONG ip = std::tr1::get<3>(ret);

	switch( msg )
	{
	case N3MSG(CMsvrMgr,MSG_MSVR_ACCEPT):
	{
		if( CMsvrAcceptHandler::GetObj()->OnConnect(s, ip) )
		{
			NOutputTextMgr::GetObj()->NOutputTextMgr::InsertFmt("SVRMGR(%s) connect", NIPAddapter(NIPAddr(ip)));
			NCriticalErrorLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__, "SVRMGR(%s) connect", NIPAddapter(NIPAddr(ip)));
		}
		else
		{
			closesocket(s);
			NOutputTextMgr::GetObj()->NOutputTextMgr::InsertFmt("SVRMGR(%s) connect fail", NIPAddapter(NIPAddr(ip)));
			NCriticalErrorLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__, "SVRMGR(%s) connect fail", NIPAddapter(NIPAddr(ip)));
		}
	}
	break;
	default:
		NCriticalErrorLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__, "unknown message receive(Msg:0x%X)", msg);
	break;
	};
}


void CMsvrMgr::Receive(const unsigned int in_Msg, const unsigned int in_wParam, const unsigned int in_lParam)
{
	m_MessageQueue.N3MessageQueue::Put(in_Msg, in_wParam, in_lParam);
}
