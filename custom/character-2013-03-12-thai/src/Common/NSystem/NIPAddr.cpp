#include "Common/NSystem/NIPAddr.h"


NIPAddr::NIPAddr()
{
}


NIPAddr::NIPAddr(const DWORD in_IPaddr)
{
	this->NIPAddr::Set(in_IPaddr);
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


void NIPAddr::Set(const DWORD in_IPaddr)
{
	m_IPAddr = in_IPaddr;
}


void NIPAddr::Set(const std::string in_IPaddr)
{
	m_IPAddr = inet_addr(in_IPaddr.c_str());
}


const char* NIPAddapter(NIPAddr in_IPAddr)
{
	//NOTE: should have just used __declspec(thread) thread-local storage
	struct threadBuffer { char m_buffer[16]; };
	static std::map<int,threadBuffer> s_threadBuffer;

	int threadId = (int)GetCurrentThread();

	in_addr addr;
	addr.s_addr = in_IPAddr;

	threadBuffer& buf = s_threadBuffer[threadId];
	_snprintf_s(buf.m_buffer, sizeof(buf.m_buffer), _TRUNCATE, "%s", inet_ntoa(addr));
	return buf.m_buffer;
}
