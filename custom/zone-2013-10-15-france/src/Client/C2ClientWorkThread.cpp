#include "Client/C2ClientMgr.h"
#include "Client/C2ClientWorkThread.h"
#include "shared/N3System/N3DataTransferMgr.h"
#include "shared/N3System/N3MessageMgr.h"


/// singleton instance
C2ClientWorkThread*& C2ClientWorkThread::m_cpSelf = VTOR<C2ClientWorkThread*>(DetourFindFunction(EXEPATH(), "C2ClientWorkThread::m_cpSelf"));


C2ClientWorkThread::C2ClientWorkThread()
: N3Thread("ClientWorkThread"),
  N3Inter(),
  N3Object(),
  m_MessageQueue(),
  m_bOK(false)
{
	N3MessageMgr::GetObj()->N3MessageMgr::Insert(this->N3Object::GetMyID(), this);
	m_bOK = true;
}


C2ClientWorkThread::~C2ClientWorkThread()
{
	N3MessageMgr::GetObj()->N3MessageMgr::Remove(this->N3Object::GetMyID(), this);
}


bool C2ClientWorkThread::Start()
{
	return this->N3Thread::Begin();
}


void C2ClientWorkThread::Stop()
{
	this->N3Thread::End();
}

	
bool C2ClientWorkThread::CreateInstance()
{
	if( m_cpSelf != NULL )
		return false;

	m_cpSelf = new(std::nothrow) C2ClientWorkThread();
	if( m_cpSelf == NULL )
		return false;
	
	if( !m_cpSelf->C2ClientWorkThread::isOK() )
	{
		delete m_cpSelf;
		m_cpSelf = NULL;
		return false;
	}

	return true;
}


void C2ClientWorkThread::DestroyInstance()
{
	if( m_cpSelf != NULL )
	{
		delete m_cpSelf;
		m_cpSelf = NULL;
	}
}


C2ClientWorkThread* C2ClientWorkThread::GetObj() /// @custom
{
	return m_cpSelf;
}


bool C2ClientWorkThread::isOK() const
{
	return m_bOK;
}


void C2ClientWorkThread::Receive(const unsigned int in_Msg, const unsigned int in_wParam, const unsigned int in_lParam)
{
	m_MessageQueue.N3MessageQueue::Put(in_Msg, in_wParam, in_lParam);
}


void C2ClientWorkThread::OnMSG_REQUEST_CONNECT(unsigned int in_hClient, N3IPAddr in_ServerIPaddr, int in_ServerPortNum) // 72-108
{
	SOCKET s = socket(AF_INET, SOCK_STREAM, 0);
	if( s == INVALID_SOCKET )
	{
		unsigned int dataKey = N3DataTransferMgr::GetObj()->N3DataTransferMgr::Put("create socket error");
		N3MessageMgr::GetObj()->N3MessageMgr::Post(C2ClientMgr::GetObj()->N3Object::GetMyID(), 0x20000, in_hClient, dataKey);
		return;
	}

	sockaddr_in sockaddr = {};
	sockaddr.sin_family = AF_INET;
	sockaddr.sin_addr.s_addr = in_ServerIPaddr;
	sockaddr.sin_port = htons(in_ServerPortNum);

	if( connect(s, (struct sockaddr*)&sockaddr, sizeof(sockaddr)) == SOCKET_ERROR )
	{
		unsigned int dataKey = N3DataTransferMgr::GetObj()->N3DataTransferMgr::Put("conect error");
		N3MessageMgr::GetObj()->N3MessageMgr::Post(C2ClientMgr::GetObj()->N3Object::GetMyID(), 0x20000, in_hClient, dataKey);
		return;
	}

	N3MessageMgr::GetObj()->N3MessageMgr::Post(C2ClientMgr::GetObj()->N3Object::GetMyID(), 0x20001, in_hClient, s);
}


unsigned int C2ClientWorkThread::ThreadFunction()
{
	while( 1 )
	{
		if( WaitForSingleObject(m_MessageQueue.N3MessageQueue::GetEventObj(), INFINITE) == WAIT_OBJECT_0 )
		{
			N3MessageQueue::RETGET mRet = m_MessageQueue.N3MessageQueue::Get();
			if( std::tr1::get<0>(mRet) == true )
			{
				unsigned int Message = std::tr1::get<1>(mRet);

				if( Message == 0x30000 )
				{
					return 0;
				}
				else
				if( Message == 0x30001 )
				{
					unsigned int hClient = std::tr1::get<2>(mRet);
					unsigned int dataKey = std::tr1::get<3>(mRet);

					std::vector<unsigned char> data = N3DataTransferMgr::GetObj()->N3DataTransferMgr::Get(dataKey);
					if( data.size() >= 8 )
					{
						unsigned long ServerIPaddr = *(unsigned long*)&data[0];
						int ServerPortNum = *(int*)&data[4];
						this->C2ClientWorkThread::OnMSG_REQUEST_CONNECT(hClient, ServerIPaddr, ServerPortNum);
					}
				}
			}
		}
	}; // while(1)
}


void C2ClientWorkThread::PostThreadQuitMessage()
{
	m_MessageQueue.N3MessageQueue::Put(0x30000, 0, 0);
}
