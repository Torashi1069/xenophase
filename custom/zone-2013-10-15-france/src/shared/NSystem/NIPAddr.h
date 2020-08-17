#pragma once


class NIPAddr
{
public:
	static bool IsPrivateIP(DWORD ); //TODO
	static DWORD GetHostIP(bool ); //TODO

public:
	operator DWORD() const;
	void Set(const DWORD in_IPAddr);
	void Set(const std::string in_IPAddr);

public:
	NIPAddr();
	NIPAddr(const DWORD in_IPAddr);
	NIPAddr(const std::string in_IPaddr);
	virtual ~NIPAddr();

private:
	/* this+0 */ //const NIPAddr::`vftable';
	/* this+4 */ DWORD m_IPAddr;
};


const char* NIPAddapter(NIPAddr in_IPAddr);
