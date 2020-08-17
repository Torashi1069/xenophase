#include "shared/NSystem/NIPAddr.h"


NIPAddr::NIPAddr()
{
}


NIPAddr::NIPAddr(const DWORD in_IPAddr)
{
	this->NIPAddr::Set(in_IPAddr);
}


NIPAddr::NIPAddr(const std::string in_IPaddr)
{
	this->NIPAddr::Set(in_IPaddr);
}


NIPAddr::~NIPAddr()
{
}


NIPAddr::operator DWORD() const
{
	return m_IPAddr;
}


void NIPAddr::Set(const DWORD in_IPAddr)
{
	m_IPAddr = in_IPAddr;
}


void NIPAddr::Set(const std::string in_IPAddr)
{
	m_IPAddr = inet_addr(in_IPAddr.c_str());
}


const char* NIPAddapter(NIPAddr in_IPAddr)
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
