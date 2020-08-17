#pragma once


struct Addr
{
	/* this+0x0 */ unsigned long ip;
	/* this+0x4 */ int port;

	public: void Addr::GetIp(char* buffer) const
	{
		strcpy(buffer, inet_ntoa(*(struct in_addr*)&this->ip));
	}

	public: void Addr::SetIp(const char* buffer)
	{
		this->ip = inet_addr(buffer);
	}
};
