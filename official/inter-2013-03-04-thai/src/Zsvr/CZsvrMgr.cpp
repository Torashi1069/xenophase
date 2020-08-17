#include "Zsvr/CZsvrAcceptHandler.h"
#include "Zsvr/CZsvrMgr.h"
#include "shared/NCriticalErrorLog.h"
#include "shared/NOutputTextMgr.h"
#include "shared/NSystem/NIPAddr.h"
#include "shared/N3System/N3DataTransferMgr.h"
#include "shared/N3System/N3MessageMgr.h"


/// singleton instance
CZsvrMgr*& CZsvrMgr::m_cpSelf = VTOR<CZsvrMgr*>(DetourFindFunction(EXEPATH(), "CZsvrMgr::m_cpSelf"));


CZsvrMgr::CZsvrMgr()
{
	m_bOK = false;

	N3MessageMgr::GetObj()->N3MessageMgr::Insert(this->N3Object::GetMyID(), this);
	m_bOK = true;
}


CZsvrMgr::~CZsvrMgr()
{
	N3MessageMgr::GetObj()->N3MessageMgr::Remove(this->N3Object::GetMyID(), this);
}


void CZsvrMgr::DeleteServer(int SID)
{
	N3SyncObject sync(m_serverMap_cs);

	std::map<int,CZServer*>::iterator iter = m_serverMap.find(SID);
	if( iter == m_serverMap.end() )
		return;

	CZServer* server = iter->second;
	server->CZServer::GetAsyncStream()->Close(false);
	CZsvrAcceptHandler::GetObj()->CZsvrAcceptHandler::FreeStream(server->CZServer::GetAsyncStream());
	this->CZServerMgr::FreeServer(server);
	m_serverMap.erase(iter);
}


void CZsvrMgr::ProcessMSG()
{
	if( WaitForSingleObject(m_MessageQueue.N3MessageQueue::GetEventObj(), 0) == WAIT_OBJECT_0 )
	{
		N3MessageQueue::RETGET ret = m_MessageQueue.N3MessageQueue::Get();
		if( std::tr1::get<0>(ret) == true )
		{
			unsigned int msg = std::tr1::get<1>(ret);
			switch( msg )
			{
			case N3MSGID(CZsvrMgr,MSG_ZSVR_ACCEPT):
			{
				SOCKET s = std::tr1::get<2>(ret);
				ULONG ip = std::tr1::get<3>(ret);

				std::vector<unsigned char> data = N3DataTransferMgr::GetObj()->N3DataTransferMgr::Get(ip);
				if( data.size() < 8 )
					return; // invalid input

				DWORD dwIP = *(DWORD*)&data[0];
				int ZSID = *(int*)&data[4];

				if( !CZsvrAcceptHandler::GetObj()->CZsvrAcceptHandler::OnConnect(s, ZSID, dwIP) )
				{
					closesocket(s);
					NOutputTextMgr::GetObj()->NOutputTextMgr::InsertFmt("ZSVR(%s) connect fail : OnZsvrConnect", NIPAddapter(NIPAddr(dwIP)));
					NCriticalErrorLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__, "ZSVR(%s) connect fail : OnZsvrConnect", NIPAddapter(NIPAddr(dwIP)));
				}
			}
			break;
			default:
			{
				NCriticalErrorLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__, "unknown message receive(Msg:0x%X)", msg);
			}
			break;
			};
		}
	}
}


void CZsvrMgr::Receive(const unsigned int in_Msg, const unsigned int in_wParam, const unsigned int in_lParam)
{
	m_MessageQueue.N3MessageQueue::Put(in_Msg, in_wParam, in_lParam);
}


void CZsvrMgr::Process()
{
	this->CZsvrMgr::ProcessMSG();

	N3SyncObject sync(m_serverMap_cs);

	for( std::map<int,CZServer*>::iterator iter = m_serverMap.begin(); iter != m_serverMap.end(); )
	{
		CZServer* zserver = iter->second;

		if( zserver->CZServer::OnProcess() != -1 || zserver->CClient::IsErrorServer() )
		{
			NOutputTextMgr::GetObj()->NOutputTextMgr::InsertFmt("ZSVR(%d) disconnected...(%s)", zserver->CZServer::GetZServerID(), NIPAddapter(NIPAddr(zserver->CZServer::GetIP())));

			zserver->CZServer::Cleanup();

			if( zserver->CZServer::GetAsyncStream()->CAsyncStream::GetLastError() != 0 )
				NCriticalErrorLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__, "io between servers closed. %d", zserver->CZServer::GetAsyncStream()->CAsyncStream::GetLastError());

			NCriticalErrorLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__, "ZoneProcess Disconnected:%d, IsErrorServer:%d", zserver->CZServer::GetZServerID(), zserver->CClient::IsErrorServer());

			zserver->CClient::Close();
			CZsvrAcceptHandler::GetObj()->CZsvrAcceptHandler::FreeStream(zserver->CZServer::GetAsyncStream());
			this->CZServerMgr::FreeServer(zserver);

			iter = m_serverMap.erase(iter);
		}
		else
		{
			++iter;
		}
	}
}


bool CZsvrMgr::CreateInstance()
{
	if( m_cpSelf != NULL )
		return false;

	m_cpSelf = new(std::nothrow) CZsvrMgr();
	if( m_cpSelf == NULL )
		return false;

	if( !m_cpSelf->CZsvrMgr::isOK() )
	{
		delete m_cpSelf;
		m_cpSelf = NULL;
		return false;
	}

	return true;
}


void CZsvrMgr::DestroyInstance()
{
	if( m_cpSelf != NULL )
	{
		delete m_cpSelf;
		m_cpSelf = NULL;
	}
}


CZsvrMgr* CZsvrMgr::GetObj() /// @custom
{
	return m_cpSelf;
}


bool CZsvrMgr::isOK() const
{
	return m_bOK;
}
