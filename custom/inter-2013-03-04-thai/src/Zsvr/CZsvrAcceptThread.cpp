#include "InterServer.h"
#include "Common/Packet.h"
#include "Zsvr/CzsvrAcceptThread.h"
#include "Zsvr/CZsvrMgr.h"
#include "shared/NCriticalErrorLog.h"
#include "shared/NOutputTextMgr.h"
#include "shared/ServerInfo.h"
#include "shared/NSystem/NIPAddr.h"
#include "shared/N3System/N3DataTransferMgr.h"
#include "shared/N3System/N3MessageMgr.h"


/// singleton instance
CZsvrAcceptThread*& CZsvrAcceptThread::m_cpSelf = VTOR<CZsvrAcceptThread*>(DetourFindFunction(EXEPATH(), "CZsvrAcceptThread::m_cpSelf"));


CZsvrAcceptThread::CZsvrAcceptThread(const DWORD in_IPaddr, const short in_Port)
: N3Thread("CZsvrAcceptThread"), m_Socket(INVALID_SOCKET), m_IPaddr(in_IPaddr), m_Port(in_Port)
{
	m_bOK = false;

	if( this->CZsvrAcceptThread::Create() )
		m_bOK = true;
}


CZsvrAcceptThread::~CZsvrAcceptThread()
{
	this->CZsvrAcceptThread::Destory();
}


bool CZsvrAcceptThread::Create()
{
	m_Socket = WSASocketA(AF_INET, SOCK_STREAM, 0, NULL, 0, WSA_FLAG_OVERLAPPED);
	if( m_Socket == INVALID_SOCKET )
	{
		MessageBoxA(NULL, "WSASocket() failed: listener", "error", MB_OK);
		return false;
	}

	sockaddr_in hostAddr = {};
	hostAddr.sin_family = AF_INET;
	hostAddr.sin_addr.s_addr = m_IPaddr;
	hostAddr.sin_port = htons(m_Port);

	if( bind(m_Socket, (sockaddr*)&hostAddr, sizeof(hostAddr)) == SOCKET_ERROR )
	{
		MessageBoxA(NULL, "bind() failed: listener", "error", MB_OK);
		return false;
	}

	if( listen(m_Socket, 20) == SOCKET_ERROR )
	{
		MessageBoxA(NULL, "listen() failed: listener", "error", MB_OK);
		return false;
	}

	FD_ZERO(&m_Readfdset);
	FD_SET(m_Socket, &m_Readfdset);

	NOutputTextMgr::GetObj()->NOutputTextMgr::InsertFmt("[listen] ZSVR %s:%d", NIPAddapter(NIPAddr(m_IPaddr)), m_Port);
	NCriticalErrorLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__, "[listen] ZSVR %s:%d", NIPAddapter(NIPAddr(m_IPaddr)), m_Port);

	return true;
}


void CZsvrAcceptThread::Destory()
{
	if( m_Socket != INVALID_SOCKET )
	{
		closesocket(m_Socket);
		m_Socket = INVALID_SOCKET;
	}
}


bool CZsvrAcceptThread::CreateInstance(const DWORD in_IPaddr, const short in_Port)
{
	if( m_cpSelf != NULL )
		return false;

	m_cpSelf = new(std::nothrow) CZsvrAcceptThread(in_IPaddr, in_Port);
	if( m_cpSelf == NULL )
		return false;

	if( !m_cpSelf->CZsvrAcceptThread::isOK() )
	{
		delete m_cpSelf;
		m_cpSelf = NULL;
		return false;
	}

	return true;
}


void CZsvrAcceptThread::DestroyInstance()
{
	if( m_cpSelf != NULL )
	{
		delete m_cpSelf;
		m_cpSelf = NULL;
	}
}


CZsvrAcceptThread* CZsvrAcceptThread::GetObj() /// @custom
{
	return m_cpSelf;
}


bool CZsvrAcceptThread::isOK() const
{
	return m_bOK;
}


bool CZsvrAcceptThread::Start()
{
	NOutputTextMgr::GetObj()->NOutputTextMgr::InsertFmt("ZSVR wait %s(%d)", NIPAddapter(NIPAddr(m_IPaddr)), m_Port);
	return this->N3Thread::Begin();
}


void CZsvrAcceptThread::Stop()
{
	this->N3Thread::End();
}


NIPAddr CZsvrAcceptThread::GetIPAddr() const
{
	return m_IPaddr;
}


int CZsvrAcceptThread::GetPort()
{
	return m_Port;
}


unsigned int CZsvrAcceptThread::ThreadFunction()
{
	while( 1 )
	{
		if( WaitForSingleObject(m_MessageQueue.N3MessageQueue::GetEventObj(), 0) == WAIT_OBJECT_0 )
		{
			N3MessageQueue::RETGET ret = m_MessageQueue.N3MessageQueue::Get();
			if( std::tr1::get<0>(ret) == true )
			{
				unsigned int Message = std::tr1::get<1>(ret);

				switch( Message )
				{
				case N3MSG(CZsvrAcceptThread,MSG_REQ_THREAD_QUIT):
					return 0;
				break;
				default:
					NCriticalErrorLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__, "unknown message receive(Msg:0x%X)", Message);
				break;
				};
			}
		}

		fd_set tempfdset;
		memcpy(&tempfdset, &m_Readfdset, sizeof(tempfdset));

		timeval timeout;
		timeout.tv_sec = 0;
		timeout.tv_usec = 10000;

		int nfds = select(tempfdset.fd_count, &tempfdset, NULL, NULL, &timeout);
		if( nfds == SOCKET_ERROR || nfds == 0 )
			continue;

		if( nfds > 0 )
		{
			if( FD_ISSET(m_Socket, &tempfdset) )
			{
				sockaddr_in remoteAddr = {};
				int sockLen = sizeof(remoteAddr);

				SOCKET s = WSAAccept(m_Socket, (sockaddr*)&remoteAddr, &sockLen, NULL, NULL);
				if( s == INVALID_SOCKET )
					continue;

				std::pair<SESSION_CONTAINER::iterator,bool> iRet = m_SessionMap.insert(std::pair<const SOCKET,lCSession>(s, lCSession(s, remoteAddr.sin_addr.s_addr)));
				if( !iRet.second )
				{
					NCriticalErrorLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__, "ZSVR(%s) auth fail: unknown", NIPAddapter(NIPAddr(remoteAddr.sin_addr.s_addr)));
					closesocket(s);
					continue;
				}

				FD_SET(s, &m_Readfdset);

				NOutputTextMgr::GetObj()->NOutputTextMgr::InsertFmt("ZSVR(%s) accept", NIPAddapter(NIPAddr(remoteAddr.sin_addr.s_addr)));
				NCriticalErrorLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__, "ZSVR(%s) accept", NIPAddapter(NIPAddr(remoteAddr.sin_addr.s_addr)));
			}

			for( SESSION_CONTAINER::iterator iter = m_SessionMap.begin(); iter != m_SessionMap.end(); ++iter )
			{
				CZsvrAcceptThread::lCSession* session = &iter->second;

				if( FD_ISSET(session->m_Socket, &tempfdset) )
				{
					char buffer[sizeof(PACKET_ZI_AUTH_REQ)] = {};
					int ReadBytes = recv(session->m_Socket, buffer, sizeof(buffer), 0);
					if( ReadBytes > 0 )
					{
						session->m_packetbuffer.insert(session->m_packetbuffer.end(), &buffer[0], &buffer[ReadBytes]);
					}
					else
					{
						++session->m_RequestDisconnectCnt;
						NOutputTextMgr::GetObj()->NOutputTextMgr::InsertFmt("ZSVR(%s) auth fail : disconnect", NIPAddapter(NIPAddr(session->m_IPaddr)));
						NCriticalErrorLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__, "ZSVR(%s) auth fail : disconnect", NIPAddapter(NIPAddr(session->m_IPaddr)));
					}
				}
			}
		}

		const DWORD CurTM = timeGetTime();

		for( SESSION_CONTAINER::iterator iter = m_SessionMap.begin(); iter != m_SessionMap.end(); ++iter )
		{
			CZsvrAcceptThread::lCSession* session = &iter->second;

			if( session->m_packetbuffer.size() > sizeof(PACKET_ZI_AUTH_REQ) )
			{
				NOutputTextMgr::GetObj()->NOutputTextMgr::InsertFmt("ZSVR(%s) auth fail : auth packet size error", NIPAddapter(NIPAddr(session->m_IPaddr)));
				NCriticalErrorLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__, "ZSVR(%s) auth fail : auth packet size error", NIPAddapter(NIPAddr(session->m_IPaddr)));
				++session->m_RequestDisconnectCnt;
				continue;
			}

			if( session->m_packetbuffer.size() != sizeof(PACKET_ZI_AUTH_REQ) )
			{
				if( CurTM > session->m_AcceptTM + 10000 )
				{
					NOutputTextMgr::GetObj()->NOutputTextMgr::InsertFmt("ZSVR(%s) auth timeout", NIPAddapter(NIPAddr(session->m_IPaddr)));
					NCriticalErrorLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__, "ZSVR(%s) auth timeout", NIPAddapter(NIPAddr(session->m_IPaddr)));
					++session->m_RequestDisconnectCnt;
				}
				continue;
			}

			PACKET_ZI_AUTH_REQ& ZIPacket = *reinterpret_cast<PACKET_ZI_AUTH_REQ*>(&session->m_packetbuffer[0]);
			if( HEADER_ZI_AUTH_REQ != ZIPacket.PacketType )
			{
				NOutputTextMgr::GetObj()->NOutputTextMgr::InsertFmt("ZSVR(%s) auth fail : unknown auth packet", NIPAddapter(NIPAddr(session->m_IPaddr)));
				NCriticalErrorLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__, "ZSVR(%s) auth fail : unknown auth packet", NIPAddapter(NIPAddr(session->m_IPaddr)));
				++session->m_RequestDisconnectCnt;
				continue;
			}

			DWORD ZsvrIPAddr = g_serverInfo.CServerInfo::GetServerIPAddr(ZIPacket.ZSID);
			DWORD ZsvrPrivateIPAddr = g_serverInfo.CServerInfo::GetServerPrivateIPAddr(ZIPacket.ZSID);

			if( session->m_IPaddr != ZsvrIPAddr && session->m_IPaddr != ZsvrPrivateIPAddr )
			{
				NOutputTextMgr::GetObj()->NOutputTextMgr::InsertFmt("ZSVR(%s) auth fail : not registered ip addr", NIPAddapter(NIPAddr(session->m_IPaddr)));
				NCriticalErrorLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__, "ZSVR(%s) auth fail : not registered ip addr", NIPAddapter(NIPAddr(session->m_IPaddr)));
				++session->m_RequestDisconnectCnt;
				continue;
			}

			session->m_bAuth = true;
			session->m_ZSID = ZIPacket.ZSID;

			NOutputTextMgr::GetObj()->NOutputTextMgr::InsertFmt("ZSVR(%s) auth success", NIPAddapter(NIPAddr(session->m_IPaddr)));
			NCriticalErrorLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__, "ZSVR(%s) auth success", NIPAddapter(NIPAddr(session->m_IPaddr)));
		}

		for( SESSION_CONTAINER::iterator iter = m_SessionMap.begin(); iter != m_SessionMap.end(); )
		{
			CZsvrAcceptThread::lCSession* session = &iter->second;

			if( session->m_RequestDisconnectCnt > 0 || session->m_bAuth )
			{
				if( session->m_bAuth )
				{
					std::vector<BYTE> data;
					data.insert(data.end(), (BYTE*)&session->m_IPaddr, (BYTE*)&session->m_IPaddr + sizeof(session->m_IPaddr));
					data.insert(data.end(), (BYTE*)&session->m_ZSID, (BYTE*)&session->m_ZSID + sizeof(session->m_ZSID));

					unsigned int ZsvrMgrID = CZsvrMgr::GetObj()->N3Object::GetMyID();
					unsigned int DataKey = N3DataTransferMgr::GetObj()->N3DataTransferMgr::Put(data);
					N3MessageMgr::GetObj()->N3MessageMgr::Post(ZsvrMgrID, N3MSG(CZsvrMgr,MSG_ZSVR_ACCEPT), session->m_Socket, DataKey);
				}
				else
				{
					closesocket(session->m_Socket);
				}

				FD_CLR(session->m_Socket, &m_Readfdset);

				iter = m_SessionMap.erase(iter);
			}
			else
			{
				++iter;
			}
		}
	} // while(1)
}


void CZsvrAcceptThread::PostThreadQuitMessage()
{
	m_MessageQueue.N3MessageQueue::Put(N3MSG(CZsvrAcceptThread,MSG_REQ_THREAD_QUIT), 0, 0);
}


void CZsvrAcceptThread::Receive(const unsigned int in_Msg, const unsigned int in_wParam, const unsigned int in_lParam)
{
	m_MessageQueue.N3MessageQueue::Put(in_Msg, in_wParam, in_lParam);
}
