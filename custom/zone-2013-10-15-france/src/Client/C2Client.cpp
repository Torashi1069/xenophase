#include "Client/C2Client.h"
#include "shared/NCriticalErrorLog.h"


C2Client::C2Client(N3IPAddr in_ServerIPAddr, int in_ServerPortNum)
: N3Inter(),
  N3Object(),
  m_ServerIPAddr(in_ServerIPAddr),
  m_ServerPortNum(in_ServerPortNum),
  m_asyncStream(N3Object::GetMyID(), 10240000, 10240000),
  m_MessageQueue(),
  m_DisconnectReqCnt(0)
{
}


C2Client::~C2Client()
{
}


N3IPAddr C2Client::GetServerIPAddr()
{
	return m_ServerIPAddr;
}


int C2Client::GetServerPortNum()
{
	return m_ServerPortNum;
}


int C2Client::GetDisconnectReqCnt()
{
	return m_DisconnectReqCnt;
}


void C2Client::Process()
{
}


void C2Client::AddDisconnectReqCnt(const char* in_pSourceFileName, const int in_SourceLineNum)
{
	++m_DisconnectReqCnt;
	NCriticalErrorLog::GetObj()->NFileLog::WriteFmt(in_pSourceFileName, in_SourceLineNum, "m_DisconnectReqCnt(%d)", m_DisconnectReqCnt);
}


bool C2Client::Init(SOCKET in_hSocket, CPacketHandler* in_cpPacketHandler)
{
	m_asyncStream.Init(in_cpPacketHandler);

	if( !m_asyncStream.Open(in_hSocket) )
	{
		closesocket(in_hSocket);
		return false;
	}

	m_DisconnectReqCnt = 0;

	return true;
}


void C2Client::Receive(const unsigned int in_Msg, const unsigned int in_wParam, const unsigned int in_lParam)
{
	m_MessageQueue.N3MessageQueue::Put(in_Msg, in_wParam, in_lParam);
}
