#include "shared/N3System/N3IPAddr.h"


N3IPAddr::N3IPAddr()
{
}


N3IPAddr::N3IPAddr(const DWORD in_IPAddr)
{
	this->N3IPAddr::Set(in_IPAddr);
}


N3IPAddr::N3IPAddr(const std::string in_IPaddr)
{
	this->N3IPAddr::Set(in_IPaddr);
}


N3IPAddr::~N3IPAddr()
{
}


N3IPAddr::operator DWORD() const
{
	return m_IPAddr;
}


void N3IPAddr::Set(const DWORD in_IPAddr)
{
	m_IPAddr = in_IPAddr;
}


void N3IPAddr::Set(const std::string in_IPAddr)
{
	m_IPAddr = inet_addr(in_IPAddr.c_str());
}


const char* N3IPAddapter(N3IPAddr in_IPAddr)
{
	//NOTE: should have just used __declspec(thread) thread-local storage
	struct threadBuffer { char m_buffer[16]; };
	static std::map<int,threadBuffer> s_threadBuffer; //NOTE: not thread-safe

	int threadId = (int)GetCurrentThread();
	threadBuffer& buf = s_threadBuffer[threadId]; //NOTE: not thread-safe

	in_addr addr;
	addr.s_addr = in_IPAddr;

	_snprintf_s(buf.m_buffer, countof(buf.m_buffer), _TRUNCATE, "%s", inet_ntoa(addr));
	return buf.m_buffer;
}
