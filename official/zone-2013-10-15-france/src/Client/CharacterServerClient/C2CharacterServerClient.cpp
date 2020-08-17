#include "CZsvrSchedulerIdentity.h"
#include "Client/C2ClientMgr.h"
#include "Client/CharacterServerClient/C2CharacterServerClient.h"
#include "Common/Packet.h"
#include "shared/NCriticalErrorLog.h"
#include "shared/NOutputTextMgr.h"
#include "shared/N3System/N3MessageMgr.h"


/// singleton instance
C2CharacterServerClient*& C2CharacterServerClient::m_cpSelf = VTOR<C2CharacterServerClient*>(DetourFindFunction(EXEPATH(), "C2CharacterServerClient::m_cpSelf"));


namespace {
class lcC2CharacterServerClientLivePing : public N3SchedulerTask<C2CharacterServerClient>
{
public:
	virtual bool operator()(C2CharacterServerClient* in_cpCharacterServerClient)
	{
		DWORD CurTime = timeGetTime();
		if( CurTime > in_cpCharacterServerClient->C2CharacterServerClient::GetLastPacketRecvTM() + 18000 )
		{
			in_cpCharacterServerClient->AddDisconnectReqCnt(__FILE__, __LINE__);
		}
		else
		if( CurTime > in_cpCharacterServerClient->C2CharacterServerClient::GetLastPacketSendTM() + 3000 || CurTime > in_cpCharacterServerClient->C2CharacterServerClient::GetLastPacketRecvTM() + 3000 )
		{
			PACKET_ZH_PING_LIVE packet;
			packet.PacketType = HEADER_ZH_PING_LIVE;
			in_cpCharacterServerClient->C2CharacterServerClient::Send(sizeof(packet), (char*)&packet);
		}

		m_Time += PERIODETM;

		return false; // loop
	}

public:
	lcC2CharacterServerClientLivePing() : N3SchedulerTask<C2CharacterServerClient>(1, timeGetTime() + PERIODETM)
	{
	}

	virtual ~lcC2CharacterServerClientLivePing()
	{
	}

private:
	enum { PERIODETM = 5000 };
};
}; // namespace


namespace {
class lcC2CharacterServerClientAuthTimeOut : public N3SchedulerTask<C2CharacterServerClient>
{
public:
	virtual bool operator()(C2CharacterServerClient* in_cpCharacterServerClient)
	{
		if( !in_cpCharacterServerClient->C2CharacterServerClient::isAuth() )
		{
			in_cpCharacterServerClient->AddDisconnectReqCnt(__FILE__, __LINE__);
			NOutputTextMgr::GetObj()->NOutputTextMgr::InsertFmt("[HSVR] auth time out");
		}

		return true;
	}

public:
	lcC2CharacterServerClientAuthTimeOut() : N3SchedulerTask<C2CharacterServerClient>(CZsvrSchedulerIdentity::GetObj()->CZsvrSchedulerIdentity::Get(), timeGetTime() + 5000)
	{
	}

	virtual ~lcC2CharacterServerClientAuthTimeOut()
	{
	}
};
}; // namespace


C2CharacterServerClient::C2CharacterServerClient(N3IPAddr in_ServerIPAddr, int in_ServerPortNum)
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


C2CharacterServerClient::~C2CharacterServerClient()
{
	N3MessageMgr::GetObj()->N3MessageMgr::Remove(this->N3Object::GetMyID(), this);
}


bool C2CharacterServerClient::Init(SOCKET in_hSocket)
{
	if( !this->C2Client::Init(in_hSocket, &m_PacketHandler) )
		return false;

	m_ProcessStep(lcProcessStep::enumStep_CONNECT);
	m_Scheduler.N3Scheduler<C2CharacterServerClient>::Init();
	m_bAuth = false;
	m_LastPacketSendTM = timeGetTime();
	m_PacketHandler.C2CharacterServerClientPacketHandler::SetLastPacketRecvTM(timeGetTime());

	m_Scheduler.N3Scheduler<C2CharacterServerClient>::Insert(N3Scheduler<C2CharacterServerClient>::TASKPTR(new(std::nothrow) lcC2CharacterServerClientLivePing()));
	m_Scheduler.N3Scheduler<C2CharacterServerClient>::Insert(N3Scheduler<C2CharacterServerClient>::TASKPTR(new(std::nothrow) lcC2CharacterServerClientAuthTimeOut()));

	PACKET_XX_CONNECT packet;
	packet.PacketType = HEADER_XX_CONNECT;
	m_asyncStream.CAsyncStream::GetRecvQueuePtr()->CPacketQueue::resetANDinsert(sizeof(packet), (char*)&packet);

	return true;
}


void C2CharacterServerClient::Send(const int in_nLen, const char* in_pBuf)
{
	if( m_ProcessStep() != lcProcessStep::enumStep_CONNECT )
		return;

	m_asyncStream.CAsyncStream::Send(in_nLen, in_pBuf);
	m_LastPacketSendTM = timeGetTime();
}


bool C2CharacterServerClient::CreateInstance(N3IPAddr in_ServerIPAddr, int in_ServerPortNum)
{
	if( m_cpSelf != NULL )
		return false;

	m_cpSelf = new(std::nothrow) C2CharacterServerClient(in_ServerIPAddr, in_ServerPortNum);
	if( m_cpSelf == NULL )
		return false;

	if( !m_cpSelf->C2CharacterServerClient::isOK() )
	{
		delete m_cpSelf;
		m_cpSelf = NULL;
		return false;
	}

	return true;
}


void C2CharacterServerClient::DestroyInstance()
{
	if( m_cpSelf != NULL )
	{
		delete m_cpSelf;
		m_cpSelf = NULL;
	}
}


C2CharacterServerClient* C2CharacterServerClient::GetObj() /// @custom
{
	return m_cpSelf;
}


bool C2CharacterServerClient::isOK() const
{
	return m_bOK;
}


void C2CharacterServerClient::MessageProcess()
{
	if( WaitForSingleObject(m_MessageQueue.N3MessageQueue::GetEventObj(), 0) == WAIT_OBJECT_0 )
	{
		N3MessageQueue::RETGET ret = m_MessageQueue.N3MessageQueue::Get();
		if( std::tr1::get<0>(ret) == true )
		{
			unsigned int Message = std::tr1::get<1>(ret);
			switch( Message )
			{
			case N3MSGID(C2StreamObject,MSG_DISCONNECT):
			{
				if( m_ProcessStep() == lcProcessStep::enumStep_CONNECT )
					this->AddDisconnectReqCnt(__FILE__, __LINE__);
			}
			break;
			};
		}
	}
}


void C2CharacterServerClient::Process()
{
	this->C2CharacterServerClient::MessageProcess();

	m_Scheduler.N3Scheduler<C2CharacterServerClient>::Process(this);

	switch( m_ProcessStep() )
	{
	case lcProcessStep::enumStep_DISCONNECT:
	break;
	case lcProcessStep::enumStep_CONNECT:
		if( this->GetDisconnectReqCnt() != 0 )
		{
			m_ProcessStep(lcProcessStep::enumStep_CLEAN_START);
		}
		else
		{
			m_PacketHandler.OnProcess();
		}
	break;
	default:
		this->C2CharacterServerClient::ProcessCleanUp();
	break;
	};
}


void C2CharacterServerClient::ProcessCleanUp()
{
	switch( m_ProcessStep() )
	{
	case lcProcessStep::enumStep_CLEAN_START:
	{
		m_Scheduler.N3Scheduler<C2CharacterServerClient>::Delete(CZsvrSchedulerIdentity::TASK_PING);
		m_bAuth = false;
		m_asyncStream.Close(true);
		m_ProcessStep(lcProcessStep::enumStep_CLEAN_NETWORK);
	}
	break;
	case lcProcessStep::enumStep_CLEAN_NETWORK:
	{
		if( m_asyncStream.C2StreamObject::GetIOCPoperationCnt() > 0 )
		{
			if( m_ProcessStep.m_dwRequestTM + 10000 >= timeGetTime() )
				return;
			NCriticalErrorLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__, "IOCP에 위임된 작업이 마무리 되지 않았다(%d)", m_asyncStream.C2StreamObject::GetIOCPoperationCnt());
		}

		m_ProcessStep(lcProcessStep::enumStep_CLEAN_WAIT);

		PACKET_XX_DISCONNECT packet;
		packet.PacketType = HEADER_XX_DISCONNECT;
		m_asyncStream.CAsyncStream::GetRecvQueuePtr()->CPacketQueue::resetANDinsert(sizeof(packet), (char*)&packet);

		m_PacketHandler.OnProcess();
	}
	break;
	case lcProcessStep::enumStep_CLEAN_WAIT:
	{
		if( timeGetTime() - m_ProcessStep.m_dwRequestTM > 10000 )
		{
			m_ProcessStep(lcProcessStep::enumStep_DISCONNECT);
			C2ClientMgr::GetObj()->C2ClientMgr::OnDisconnect(this->N3Object::GetMyID());
		}
	}
	break;
	};
}


bool C2CharacterServerClient::isAuth()
{
	return m_bAuth;
}


void C2CharacterServerClient::SetAuth(const bool bAuth)
{
	m_bAuth = bAuth;
}


DWORD C2CharacterServerClient::GetLastPacketRecvTM()
{
	return m_PacketHandler.C2CharacterServerClientPacketHandler::GetLastPacketRecvTM();
}


DWORD C2CharacterServerClient::GetLastPacketSendTM()
{
	return m_LastPacketSendTM;
}
