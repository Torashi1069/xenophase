#include "CZsvrSchedulerIdentity.h"
#include "GVar.h"
#include "Client/C2ClientMgr.h"
#include "Client/C2ClientWorkThread.h"
#include "Client/CharacterServerClient/C2CharacterServerClient.h"
#include "Client/InterServerClient/C2InterServerClient.h"
#include "shared/NCriticalErrorLog.h"
#include "shared/NOutputTextMgr.h"
#include "shared/ServerInfo.h"
#include "shared/N3System/N3DataTransferMgr.h"
#include "shared/N3System/N3MessageMgr.h"


/// singleton instance
C2ClientMgr*& C2ClientMgr::m_cpSelf = VTOR<C2ClientMgr*>(DetourFindFunction(EXEPATH(), "C2ClientMgr::m_cpSelf"));


C2ClientMgr::C2ClientMgr()
: N3Inter(),
  N3Object(),
  m_MessageQueue(),
  m_Scheduler(),
  m_bOK(false)
{
	N3MessageMgr::GetObj()->N3MessageMgr::Insert(this->N3Object::GetMyID(), this);

	if( this->C2ClientMgr::Create() )
		m_bOK = true;
}


C2ClientMgr::~C2ClientMgr()
{
	this->C2ClientMgr::Destroy();

	N3MessageMgr::GetObj()->N3MessageMgr::Remove(this->N3Object::GetMyID(), this);
}


namespace {
class lcC2ClientConnect : public N3SchedulerTask<C2ClientMgr>
{
public:
	virtual bool operator()(C2ClientMgr* in_cpClientMgr)
	{
		const DWORD ServerIPaddr = m_cpClient->C2Client::GetServerIPAddr();
		const int ServerPortNum = m_cpClient->C2Client::GetServerPortNum();

		std::vector<unsigned char> data;
		data.insert(data.end(), (char*)&ServerIPaddr, (char*)&ServerIPaddr + sizeof(ServerIPaddr));
		data.insert(data.end(), (char*)&ServerPortNum, (char*)&ServerPortNum + sizeof(ServerPortNum));

		unsigned int dataKey = N3DataTransferMgr::GetObj()->N3DataTransferMgr::Put(data);
		N3MessageMgr::GetObj()->N3MessageMgr::Post(C2ClientWorkThread::GetObj()->N3Object::GetMyID(), N3MSGID(C2ClientWorkThread,MSG_REQUEST_CONNECT), m_cpClient->N3Object::GetMyID(), dataKey);

		return true;
	}

public:
	lcC2ClientConnect(C2Client* in_cpClient, const int in_DelayMS) : N3SchedulerTask<C2ClientMgr>(CZsvrSchedulerIdentity::GetObj()->CZsvrSchedulerIdentity::Get(), timeGetTime() + 10000), m_cpClient(in_cpClient)
	{		
	}

	virtual ~lcC2ClientConnect()
	{
	}

private:
	/* this+ 0 */ //N3SchedulerTask<C2ClientMgr> baseclass_0;
	/* this+12 */ C2Client* m_cpClient;
};
}; // namespace


bool C2ClientMgr::Create()
{
	if( !C2ClientWorkThread::CreateInstance() )
		return false;

	if( !C2ClientWorkThread::GetObj()->C2ClientWorkThread::Start() )
		return false;
///
	int ISvrSID = g_serverInfo.CServerInfo::GetDestinationSID(TARGET_TWO_SID);

	unsigned long ISvrIP = g_serverInfo.CServerInfo::GetServerPrivateIPAddr(ISvrSID);
	if( ISvrIP == INADDR_ANY ) ISvrIP = g_serverInfo.CServerInfo::GetServerIPAddr(ISvrSID);

	int ISvrPort = g_serverInfo.CServerInfo::GetServerPrivatePort(ISvrSID);
	if( ISvrPort == 0 ) ISvrPort = g_serverInfo.CServerInfo::GetServerPort(ISvrSID);

	if( !C2InterServerClient::CreateInstance(ISvrIP, ISvrPort) )
		return false;
	
	m_Scheduler.N3Scheduler<C2ClientMgr>::Insert(N3Scheduler<C2ClientMgr>::TASKPTR(new(std::nothrow) lcC2ClientConnect(C2InterServerClient::GetObj(), 10000)));
///
	int HSvrSID = g_serverInfo.CServerInfo::GetDestinationSID(TARGET_ONE_SID);

	unsigned long HSvrIP = g_serverInfo.CServerInfo::GetServerPrivateIPAddr(HSvrSID);
	if( HSvrIP == INADDR_ANY ) HSvrIP = g_serverInfo.CServerInfo::GetServerIPAddr(HSvrSID);

	int HSvrPort = g_serverInfo.CServerInfo::GetServerPrivatePort(HSvrSID);
	if( HSvrPort == 0 )
		HSvrPort = g_serverInfo.CServerInfo::GetServerPort(HSvrSID);

	CGVar::GetObj()->CGVar::SetHSID(HSvrSID);

	if( !C2CharacterServerClient::CreateInstance(HSvrIP, HSvrPort) )
		return false;

	m_Scheduler.N3Scheduler<C2ClientMgr>::Insert(N3Scheduler<C2ClientMgr>::TASKPTR(new(std::nothrow) lcC2ClientConnect(C2CharacterServerClient::GetObj(), 10000)));
///
	return true;
}


void C2ClientMgr::OnDisconnect(unsigned int in_hClient)
{
	if( in_hClient == C2InterServerClient::GetObj()->N3Object::GetMyID() )
	{
		N3IPAddr IPaddr = C2InterServerClient::GetObj()->C2Client::GetServerIPAddr();
		int PortNum = C2InterServerClient::GetObj()->C2Client::GetServerPortNum();

		NOutputTextMgr::GetObj()->NOutputTextMgr::InsertFmt("[ISVR] disconnected. [%s, %d]", N3IPAddapter(IPaddr), PortNum);
		NCriticalErrorLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__, "[ISVR] disconnected. [%s, %d]", N3IPAddapter(IPaddr), PortNum);

		m_Scheduler.N3Scheduler<C2ClientMgr>::Insert(N3Scheduler<C2ClientMgr>::TASKPTR(new(std::nothrow) lcC2ClientConnect(C2InterServerClient::GetObj(), 10000)));
	}
	else
	if( in_hClient == C2CharacterServerClient::GetObj()->N3Object::GetMyID() )
	{
		N3IPAddr IPaddr = C2CharacterServerClient::GetObj()->C2Client::GetServerIPAddr();
		int PortNum = C2CharacterServerClient::GetObj()->C2Client::GetServerPortNum();

		NOutputTextMgr::GetObj()->NOutputTextMgr::InsertFmt("[HSVR] disconnected. [%s, %d]", N3IPAddapter(IPaddr), PortNum);
		NCriticalErrorLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__, "[HSVR] disconnected. [%s, %d]", N3IPAddapter(IPaddr), PortNum);

		m_Scheduler.N3Scheduler<C2ClientMgr>::Insert(N3Scheduler<C2ClientMgr>::TASKPTR(new(std::nothrow) lcC2ClientConnect(C2CharacterServerClient::GetObj(), 10000)));
	}
}


void C2ClientMgr::Destroy()
{
	C2InterServerClient::DestroyInstance();
	C2CharacterServerClient::DestroyInstance();
	C2ClientWorkThread::GetObj()->C2ClientWorkThread::Stop();
	C2ClientWorkThread::DestroyInstance();
}


void C2ClientMgr::OnMSG_CONNECT_FAIL(unsigned int in_hClient, std::string in_msg)
{
	if( in_hClient == C2InterServerClient::GetObj()->N3Object::GetMyID() )
	{
		N3IPAddr IPaddr = C2InterServerClient::GetObj()->C2Client::GetServerIPAddr();
		int PortNum = C2InterServerClient::GetObj()->C2Client::GetServerPortNum();

		NOutputTextMgr::GetObj()->NOutputTextMgr::InsertFmt("[ISVR] connect fail : %s", in_msg.c_str());
		NOutputTextMgr::GetObj()->NOutputTextMgr::InsertFmt("[ISVR] %s:%d", N3IPAddapter(IPaddr), PortNum);
		NCriticalErrorLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__, "[ISVR] connect fail : %s", in_msg.c_str());
		NCriticalErrorLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__, "[ISVR] %s:%d", N3IPAddapter(IPaddr), PortNum);

		m_Scheduler.N3Scheduler<C2ClientMgr>::Insert(N3Scheduler<C2ClientMgr>::TASKPTR(new(std::nothrow) lcC2ClientConnect(C2InterServerClient::GetObj(), 10000)));
	}
	else
	if( in_hClient == C2CharacterServerClient::GetObj()->N3Object::GetMyID() )
	{
		N3IPAddr IPaddr = C2CharacterServerClient::GetObj()->C2Client::GetServerIPAddr();
		int PortNum = C2CharacterServerClient::GetObj()->C2Client::GetServerPortNum();

		NOutputTextMgr::GetObj()->NOutputTextMgr::InsertFmt("[HSVR] connect fail : %s", in_msg.c_str());
		NOutputTextMgr::GetObj()->NOutputTextMgr::InsertFmt("[HSVR] %s:%d", N3IPAddapter(IPaddr), PortNum);
		NCriticalErrorLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__, "[HSVR] connect fail : %s", in_msg.c_str());
		NCriticalErrorLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__, "[HSVR] %s:%d", N3IPAddapter(IPaddr), PortNum);

		m_Scheduler.N3Scheduler<C2ClientMgr>::Insert(N3Scheduler<C2ClientMgr>::TASKPTR(new(std::nothrow) lcC2ClientConnect(C2CharacterServerClient::GetObj(), 10000)));
	}
}


void C2ClientMgr::OnMSG_CONNECT_SUCCESS(unsigned int in_hClient, SOCKET in_hSocket) // 245-286
{
	if( in_hClient == C2InterServerClient::GetObj()->N3Object::GetMyID() )
	{
		if( C2InterServerClient::GetObj()->C2InterServerClient::Init(in_hSocket) )
		{
			NOutputTextMgr::GetObj()->NOutputTextMgr::InsertFmt("[ISVR] connect success");
		}
		else
		{
			m_Scheduler.N3Scheduler<C2ClientMgr>::Insert(N3Scheduler<C2ClientMgr>::TASKPTR(new(std::nothrow) lcC2ClientConnect(C2InterServerClient::GetObj(), 10000)));
		}
	}
	else
	if( in_hClient == C2CharacterServerClient::GetObj()->N3Object::GetMyID() )
	{
		if( C2CharacterServerClient::GetObj()->C2CharacterServerClient::Init(in_hSocket) )
		{
			NOutputTextMgr::GetObj()->NOutputTextMgr::InsertFmt("[HSVR] connect success");
		}
		else
		{
			m_Scheduler.N3Scheduler<C2ClientMgr>::Insert(N3Scheduler<C2ClientMgr>::TASKPTR(new(std::nothrow) lcC2ClientConnect(C2CharacterServerClient::GetObj(), 10000)));
		}
	}
}


void C2ClientMgr::MessageProcess()
{
	if( WaitForSingleObject(m_MessageQueue.N3MessageQueue::GetEventObj(), 0) == WAIT_OBJECT_0 )
	{
		N3MessageQueue::RETGET mRet = m_MessageQueue.N3MessageQueue::Get();
		if( std::tr1::get<0>(mRet) == true )
		{
			unsigned int Message = std::tr1::get<1>(mRet);
			switch( Message )
			{
			case N3MSGID(C2ClientMgr,MSG_CONNECT_FAIL):
			{
				unsigned int hClient = std::tr1::get<2>(mRet);
				unsigned int msgKey = std::tr1::get<3>(mRet);

				std::string msg = N3DataTransferMgr::GetObj()->N3DataTransferMgr::GetStr(msgKey);
				this->C2ClientMgr::OnMSG_CONNECT_FAIL(hClient, msg);
			}
			break;
			case N3MSGID(C2ClientMgr,MSG_CONNECT_SUCCESS):
			{
				unsigned int hClient = std::tr1::get<2>(mRet);
				SOCKET hSocket = std::tr1::get<3>(mRet);

				this->C2ClientMgr::OnMSG_CONNECT_SUCCESS(hClient, hSocket);
			}
			break;
			};
		}
	}
}


void C2ClientMgr::Process()
{
	this->C2ClientMgr::MessageProcess();
	m_Scheduler.N3Scheduler<C2ClientMgr>::Process(this);
	C2InterServerClient::GetObj()->Process();
	C2CharacterServerClient::GetObj()->Process();
}


void C2ClientMgr::Receive(const unsigned int in_Msg, const unsigned int in_wParam, const unsigned int in_lParam)
{
	m_MessageQueue.N3MessageQueue::Put(in_Msg, in_wParam, in_lParam);
}


bool C2ClientMgr::CreateInstance()
{
	if( m_cpSelf != NULL )
		return false;

	m_cpSelf = new(std::nothrow) C2ClientMgr();
	if( m_cpSelf == NULL )
		return false;

	if( !m_cpSelf->C2ClientMgr::isOK() )
	{
		delete m_cpSelf;
		m_cpSelf = NULL;
		return false;
	}

	return true;
}


void C2ClientMgr::DestroyInstance()
{
	if( m_cpSelf != NULL )
	{
		delete m_cpSelf;
		m_cpSelf = NULL;
	}
}


C2ClientMgr* C2ClientMgr::GetObj() /// @custom
{
	return m_cpSelf;
}


bool C2ClientMgr::isOK() const
{
	return m_bOK;
}
