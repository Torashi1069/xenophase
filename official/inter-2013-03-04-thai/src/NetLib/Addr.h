#pragma once


struct Addr
{
	/* this+0 */ unsigned long ip;
	/* this+4 */ int port;

	void GetIp(char* buffer) const
	{
		in_addr addr;
		addr.s_addr = this->ip;
		strcpy(buffer, inet_ntoa(addr));
	}

	void SetIp(const char* buffer)
	{
		this->ip = inet_addr(buffer);
	}
};
