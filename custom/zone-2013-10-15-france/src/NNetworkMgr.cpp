#include "NNetworkMgr.h"
#include "NNetworkWorkThread.h"
#include "shared/N3System/N3MessageMgr.h"


/// singleton instance
NNetworkMgr*& NNetworkMgr::m_cpSelf = VTOR<NNetworkMgr*>(DetourFindFunction(EXEPATH(), "NNetworkMgr::m_cpSelf"));


NNetworkMgr::NNetworkMgr()
: m_bOK(false), m_hIOCP(NULL), m_ThreadPool()
{
	if( this->NNetworkMgr::Create() )
		m_bOK = true;
}


NNetworkMgr::~NNetworkMgr()
{
	this->NNetworkMgr::Destroy();
}


NNetworkMgr* NNetworkMgr::GetObj() /// @custom
{
	return m_cpSelf;
}


bool NNetworkMgr::isOK() const
{
	return m_bOK;
}


HANDLE NNetworkMgr::GetIOCPHandle()
{
	return m_hIOCP;
}


namespace {
class CompletionKeyGenerator
{
public:
	int operator()() { return ++m_Key; }

public:
	CompletionKeyGenerator() { m_Key = 0; }
	virtual ~CompletionKeyGenerator() { }

private:
	/* this+0 */ //const CompletionKeyGenerator::`vftable';
	/* this+4 */ unsigned int m_Key;
};

CompletionKeyGenerator& InstanceCompletionKeyGenerator = VTOR<CompletionKeyGenerator>(DetourFindFunction(EXEPATH(), "?InstanceCompletionKeyGenerator@?A0xcac5a30e@@3VCompletionKeyGenerator@1@A"));
}; // namespace


unsigned int NNetworkMgr::GenerateCompletionKey()
{
	return InstanceCompletionKeyGenerator();
}


bool NNetworkMgr::Create()
{
	WSADATA wsaData = {};
	if( WSAStartup(MAKEWORD(2,2), &wsaData) != 0 )
		return false;

	m_hIOCP = CreateIoCompletionPort(INVALID_HANDLE_VALUE, NULL, 0, 0);
	if( m_hIOCP == NULL )
		return false;

	for( int Cnt = 0; Cnt < 32; ++Cnt )
	{
		char name[MAX_PATH] = {};
		_snprintf_s(name, countof(name), _TRUNCATE, "NetworkWorkThread%02d", Cnt);

		NNetworkWorkThread* cpWorkThread = new(std::nothrow) NNetworkWorkThread(name);
		if( cpWorkThread == NULL )
			return false;

		if( !cpWorkThread->NNetworkWorkThread::isOK() )
		{
			delete cpWorkThread;
			return false;
		}

		m_ThreadPool.push_back(cpWorkThread);
	}

	return true;
}


bool NNetworkMgr::Start()
{
	for( std::vector<NNetworkWorkThread*>::iterator iter = m_ThreadPool.begin(); iter != m_ThreadPool.end(); ++iter )
		if( !(*iter)->NNetworkWorkThread::Start() )
			return false;

	return true;
}


void NNetworkMgr::Stop()
{
	for( std::vector<NNetworkWorkThread*>::iterator iter = m_ThreadPool.begin(); iter != m_ThreadPool.end(); ++iter )
		N3MessageMgr::GetObj()->N3MessageMgr::Post((*iter)->N3Object::GetMyID(), NNetworkWorkThread::MSG_THREAD_QUIT, 0, 0);

	for( std::vector<NNetworkWorkThread*>::iterator iter = m_ThreadPool.begin(); iter != m_ThreadPool.end(); ++iter )
		PostQueuedCompletionStatus(m_hIOCP, 0, 0, NULL);
}


void NNetworkMgr::Destroy()
{
	if( m_hIOCP != NULL )
	{
		CloseHandle(m_hIOCP);
		m_hIOCP = NULL;
	}

	for( std::vector<NNetworkWorkThread*>::iterator iter = m_ThreadPool.begin(); iter != m_ThreadPool.end(); ++iter )
		(*iter)->NNetworkWorkThread::Stop();

	for( std::vector<NNetworkWorkThread*>::iterator iter = m_ThreadPool.begin(); iter != m_ThreadPool.end(); ++iter )
		delete *iter;

	WSACleanup();
}


bool NNetworkMgr::CreateInstance()
{
	if( m_cpSelf != NULL )
		return false;

	m_cpSelf = new(std::nothrow) NNetworkMgr();
	if( m_cpSelf == NULL )
		return false;

	if( !m_cpSelf->NNetworkMgr::isOK() )
	{
		delete m_cpSelf;
		m_cpSelf = NULL;
		return false;
	}

	return true;
}


void NNetworkMgr::DestroyInstance()
{
	if( m_cpSelf != NULL )
	{
		delete m_cpSelf;
		m_cpSelf = NULL;
	}
}
