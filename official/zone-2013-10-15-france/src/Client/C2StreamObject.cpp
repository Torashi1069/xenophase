#include "Client/C2StreamObject.h"
#include "shared/NCriticalErrorLog.h"
#include "shared/N3System/N3MessageMgr.h"
#include "shared/N3System/N3Object.h"
#include "shared/N3System/N3SyncObject.h"


C2StreamObject::C2StreamObject(SOCKET in_hClient, int in_RecvQueueSize, int in_SendQueueSize)
: CAsyncStream(in_RecvQueueSize, in_SendQueueSize),
  m_IOCPoperationCnt(0),
  m_hClient(in_hClient)
{
	InitializeCriticalSection(&m_CS);
}


C2StreamObject::~C2StreamObject()
{
	DeleteCriticalSection(&m_CS);
}


bool C2StreamObject::Open(SOCKET in_hSocket)
{
	bool result = false;
	N3SyncObject sync(m_CS);

	InterlockedExchange(&m_IOCPoperationCnt, 0);

	if( this->CAsyncStream::Open(in_hSocket) )
	{
		InterlockedIncrement(&m_IOCPoperationCnt);
		result = true;
	}

	return result;
}


void C2StreamObject::Init(CPacketHandler* in_cpPacketHandler)
{
	this->CAsyncStream::Init(in_cpPacketHandler);
	InterlockedExchange(&m_IOCPoperationCnt, 0);
}


BOOL C2StreamObject::SendDataInQueue(int size)
{
	if( !this->CAsyncStream::SendDataInQueue(size) )
		return FALSE;

	InterlockedIncrement(&m_IOCPoperationCnt);
	return TRUE;
}


BOOL C2StreamObject::OnRecvCompletion(long len)
{
	if( !this->CAsyncStream::OnRecvCompletion(len) )
		return FALSE;

	InterlockedIncrement(&m_IOCPoperationCnt);
	return TRUE;
}


void C2StreamObject::OnComplete(BOOL result, DWORD transferSize, CAsyncOperation* op)
{
	InterlockedDecrement(&m_IOCPoperationCnt);
	this->CAsyncStream::OnComplete(result, transferSize, op);
}


BOOL C2StreamObject::Close(const bool in_bOnlySocketClose)
{
	NCriticalErrorLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__, " 동기화 객체 진입전 : C2StreamObject::Close() socket = %d", m_socket);

	N3SyncObject sync(m_CS);

	if( m_socket == INVALID_SOCKET )
	{
		NCriticalErrorLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__, "( INVALID_SOCKET == m_socket )");
		return FALSE;
	}

	linger linger;
	linger.l_onoff = 1;
	linger.l_linger = 0;
	setsockopt(m_socket, SOL_SOCKET, SO_LINGER, (char*)&linger, sizeof(linger));

	int ret = closesocket(m_socket);
	m_socket = INVALID_SOCKET;

	N3MessageMgr::GetObj()->N3MessageMgr::Post(m_hClient, N3MSGID(C2StreamObject,MSG_DISCONNECT), 0, 0);
	NCriticalErrorLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__, "N3MSGID( N3Object::SteamObject, MSG_DISCONNECT )");

	return ( ret != SOCKET_ERROR );
}


LONG C2StreamObject::GetIOCPoperationCnt()
{
	return m_IOCPoperationCnt;
}
