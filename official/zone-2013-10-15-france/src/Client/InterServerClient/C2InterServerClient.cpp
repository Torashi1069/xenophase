#include "CharacterMgr.h"
#include "CZsvrSchedulerIdentity.h"
#include "GVar.h"
#include "Client/C2ClientMgr.h"
#include "Client/InterServerClient/C2InterServerClient.h"
#include "Common/Packet.h"
#include "shared/NCriticalErrorLog.h"
#include "shared/NOutputTextMgr.h"
#include "shared/N3System/N3MessageMgr.h"


/// singleton instance
C2InterServerClient*& C2InterServerClient::m_cpSelf = VTOR<C2InterServerClient*>(DetourFindFunction(EXEPATH(), "C2InterServerClient::m_cpSelf"));


C2InterServerClient::C2InterServerClient(N3IPAddr in_ServerIPAddr, int in_ServerPortNum)
: C2Client(in_ServerIPAddr, in_ServerPortNum),
  m_ProcessStep(),
  m_PacketHandler(),
  m_Scheduler(),
  m_bAuth(false),
  m_LastPacketSendTM(timeGetTime()),
  m_bOK(false)
{
	N3MessageMgr::GetObj()->N3MessageMgr::Insert(this->N3Object::GetMyID(), this);
	m_asyncStream.Init(&m_PacketHandler);
	m_asyncStream.CAsyncStream::SetRecvQueueSize(8192000);
	m_bOK = true;
}


C2InterServerClient::~C2InterServerClient()
{
	N3MessageMgr::GetObj()->N3MessageMgr::Remove(this->N3Object::GetMyID(), this);
}


namespace {
class lcC2InterServerClientLivePing : public N3SchedulerTask<C2InterServerClient>
{
public:
	virtual bool operator()(C2InterServerClient* in_cpInterServerClient)
	{
		DWORD CurTime = timeGetTime();
		if( CurTime > in_cpInterServerClient->C2InterServerClient::GetLastPacketRecvTM() + 18000 )
		{
			in_cpInterServerClient->AddDisconnectReqCnt(__FILE__, __LINE__);
		}
		else
		if( CurTime > in_cpInterServerClient->C2InterServerClient::GetLastPacketSendTM() + 3000 )
		{
			PACKET_ZI_PING_LIVE packet;
			packet.PacketType = HEADER_ZI_PING_LIVE;
			in_cpInterServerClient->C2InterServerClient::Send(sizeof(packet), (char*)&packet);
		}

		m_Time += PERIODETM;

		return false; // loop
	}

public:
	lcC2InterServerClientLivePing() : N3SchedulerTask<C2InterServerClient>(CZsvrSchedulerIdentity::TASK_PING, timeGetTime() + PERIODETM)
	{
	}

	virtual ~lcC2InterServerClientLivePing()
	{
	}

private:
	enum { PERIODETM = 3000 };
};
}; // namespace


namespace {
class lcC2InterServerClientState : public N3SchedulerTask<C2InterServerClient>
{
public:
	virtual bool operator()(C2InterServerClient* in_cpInterServerClient)
	{
		PACKET_ZI_STATEINFO packet = {};
		packet.PacketType = HEADER_ZI_STATEINFO;
		packet.UsedKBytesMemory = CGVar::GetObj()->CGVar::GetUsedMemoryBytes() / 1024;
		packet.NumTotalNPC = CCharacterMgr::GetObj()->CCharacterMgr::GetMonsterCount();
		in_cpInterServerClient->C2InterServerClient::Send(sizeof(packet), (char*)&packet);

		m_Time += PERIODETM;

		return false; // loop
	}

public:
	lcC2InterServerClientState() : N3SchedulerTask<C2InterServerClient>(CZsvrSchedulerIdentity::TASK_STATE, timeGetTime() + PERIODETM)
	{
	}

	virtual ~lcC2InterServerClientState()
	{
	}

private:
	enum { PERIODETM = 60000 };
};
}; // namespace


namespace {
class lcC2InterServerClientAuthTimeOut : public N3SchedulerTask<C2InterServerClient>
{
public:
	virtual bool operator()(C2InterServerClient* in_cpInterServerClient)
	{
		if( !in_cpInterServerClient->C2InterServerClient::isAuth() )
		{
			in_cpInterServerClient->AddDisconnectReqCnt(__FILE__, __LINE__);
			NOutputTextMgr::GetObj()->NOutputTextMgr::InsertFmt("[ISVR] auth time out");
		}

		return true;
	}

public:
	lcC2InterServerClientAuthTimeOut() : N3SchedulerTask<C2InterServerClient>(CZsvrSchedulerIdentity::GetObj()->CZsvrSchedulerIdentity::Get(), timeGetTime() + 5000)
	{
	}

	virtual ~lcC2InterServerClientAuthTimeOut()
	{
	}
};
}; // namespace


bool C2InterServerClient::Init(SOCKET in_hSocket)
{
	if( !this->C2Client::Init(in_hSocket, &m_PacketHandler) )
		false;

	m_ProcessStep(lcProcessStep::STEP_CONNECT);
	m_bAuth = false;
	m_Scheduler.N3Scheduler<C2InterServerClient>::Init();
	m_LastPacketSendTM = timeGetTime();
	m_PacketHandler.C2InterServerClientPacketHandler::SetLastPacketRecvTM(timeGetTime());

	m_Scheduler.N3Scheduler<C2InterServerClient>::Insert(N3Scheduler<C2InterServerClient>::TASKPTR(new(std::nothrow) lcC2InterServerClientLivePing()));
	m_Scheduler.N3Scheduler<C2InterServerClient>::Insert(N3Scheduler<C2InterServerClient>::TASKPTR(new(std::nothrow) lcC2InterServerClientState()));
	m_Scheduler.N3Scheduler<C2InterServerClient>::Insert(N3Scheduler<C2InterServerClient>::TASKPTR(new(std::nothrow) lcC2InterServerClientAuthTimeOut()));

	PACKET_XX_CONNECT packet;
	packet.PacketType = HEADER_XX_CONNECT;
	m_asyncStream.CAsyncStream::GetRecvQueuePtr()->CPacketQueue::resetANDinsert(sizeof(packet), (char*)&packet);

	return true;
}


void C2InterServerClient::Send(int len, const char* buf)
{
	if( m_ProcessStep() != lcProcessStep::STEP_CONNECT )
		return;

	m_asyncStream.CAsyncStream::Send(len, buf);
	m_LastPacketSendTM = timeGetTime();
}


void C2InterServerClient::ProcessCleanup()
{
	switch( m_ProcessStep() )
	{
	case lcProcessStep::STEP_CLEANUP_START:
	{
		m_Scheduler.N3Scheduler<C2InterServerClient>::Delete(CZsvrSchedulerIdentity::TASK_PING);
		m_Scheduler.N3Scheduler<C2InterServerClient>::Delete(CZsvrSchedulerIdentity::TASK_STATE);
		m_bAuth = false;
		m_asyncStream.Close(true);
		m_ProcessStep(lcProcessStep::STEP_CLEANUP_NETWORK);
	}
	break;
	case lcProcessStep::STEP_CLEANUP_NETWORK:
	{
		if( m_asyncStream.C2StreamObject::GetIOCPoperationCnt() > 0 )
		{
			if( m_ProcessStep.m_RequestTM + 10000 >= timeGetTime() )
				return;
			NCriticalErrorLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__, "IOCP에 위임된 작업이 마무리 되지 않았다(%d)", m_asyncStream.C2StreamObject::GetIOCPoperationCnt());
		}

		m_ProcessStep(lcProcessStep::STEP_CLEANUP_WAIT);

		PACKET_XX_DISCONNECT packet;
		packet.PacketType = HEADER_XX_DISCONNECT;
		m_asyncStream.CAsyncStream::GetRecvQueuePtr()->CPacketQueue::resetANDinsert(sizeof(packet), (char*)&packet);

		m_PacketHandler.OnProcess();
	}
	break;
	case lcProcessStep::STEP_CLEANUP_WAIT:
	{
		if( timeGetTime() - m_ProcessStep.m_RequestTM >= 10000 )
		{
			m_ProcessStep(lcProcessStep::STEP_DISCONNECT);
			C2ClientMgr::GetObj()->C2ClientMgr::OnDisconnect(this->N3Object::GetMyID());
		}
	}
	break;
	};
}


void C2InterServerClient::MessageProcess()
{
	if( WaitForSingleObject(m_MessageQueue.N3MessageQueue::GetEventObj(), 0) == WAIT_OBJECT_0 )
	{
		N3MessageQueue::RETGET mRet = m_MessageQueue.N3MessageQueue::Get();
		if( std::tr1::get<0>(mRet) == true )
		{
			unsigned int Message = std::tr1::get<1>(mRet);
			switch( Message )
			{
			case N3MSGID(C2StreamObject,MSG_DISCONNECT):
			{
				NCriticalErrorLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__, "[ISVR] receive disconnect process step(%d)", m_ProcessStep());
				if( m_ProcessStep() == lcProcessStep::STEP_CONNECT )
					this->AddDisconnectReqCnt(__FILE__, __LINE__);
			}
			break;
			};
		}
	}
}


void C2InterServerClient::Process()
{
	this->C2InterServerClient::MessageProcess();

	m_Scheduler.N3Scheduler<C2InterServerClient>::Process(this);

	switch( m_ProcessStep() )
	{
	case lcProcessStep::STEP_DISCONNECT:
	break;
	case lcProcessStep::STEP_CONNECT:
		if( this->GetDisconnectReqCnt() != 0 )
		{
			m_ProcessStep(lcProcessStep::STEP_CLEANUP_START);
		}
		else
		{
			m_PacketHandler.OnProcess();
		}
	break;
	default:
		this->C2InterServerClient::ProcessCleanup();
	break;
	};
}


bool C2InterServerClient::CreateInstance(N3IPAddr in_ServerIPAddr, int in_ServerPortNum)
{
	if( m_cpSelf != NULL )
		return false;

	m_cpSelf = new(std::nothrow) C2InterServerClient(in_ServerIPAddr, in_ServerPortNum);
	if( m_cpSelf == NULL )
		return false;

	if( !m_cpSelf->C2InterServerClient::isOK() )
	{
		delete m_cpSelf;
		m_cpSelf = NULL;
		return false;
	}

	return true;
}


void C2InterServerClient::DestroyInstance()
{
	if( m_cpSelf != NULL )
	{
		delete m_cpSelf;
		m_cpSelf = NULL;
	}
}


C2InterServerClient* C2InterServerClient::GetObj() /// @custom
{
	return m_cpSelf;
}


bool C2InterServerClient::isOK() const
{
	return m_bOK;
}


bool C2InterServerClient::isAuth()
{
	return m_bAuth;
}


void C2InterServerClient::SetAuth(bool bAuth)
{
	m_bAuth = bAuth;
}


DWORD C2InterServerClient::GetLastPacketRecvTM()
{
	return m_PacketHandler.C2InterServerClientPacketHandler::GetLastPacketRecvTM();
}


DWORD C2InterServerClient::GetLastPacketSendTM()
{
	return m_LastPacketSendTM;
}
