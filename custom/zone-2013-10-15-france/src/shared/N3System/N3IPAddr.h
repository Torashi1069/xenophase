#pragma once


class N3IPAddr
{
public:
	static bool IsPrivateIP(DWORD ); //TODO
	static DWORD GetHostIP(bool ); //TODO

public:
	operator DWORD() const;
	void Set(const DWORD in_IPAddr);
	void Set(const std::string in_IPAddr);

	N3IPAddr();
	N3IPAddr(const DWORD in_IPAddr);
	N3IPAddr(const std::string in_IPaddr);
	virtual ~N3IPAddr();

private:
	/* this+0 */ //const N3IPAddr::`vftable';
	/* this+4 */ DWORD m_IPAddr;
};


const char* N3IPAddapter(N3IPAddr in_IPAddr);
