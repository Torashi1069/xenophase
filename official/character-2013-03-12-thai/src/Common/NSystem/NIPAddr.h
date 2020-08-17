#pragma once


class NIPAddr
{
public:
//	static bool IsPrivateIP(DWORD);
//	static DWORD GetHostIP(bool);

public:
	operator DWORD() const;
	void Set(const DWORD in_IPaddr);
	void Set(const std::string in_IPaddr);

public:
	NIPAddr();
	NIPAddr(const DWORD in_IPaddr);
	NIPAddr(const std::string in_IPaddr);
	virtual ~NIPAddr();

private:
	/* this+0 */ //const NIPAddr::`vftable';
	/* this+4 */ DWORD m_IPAddr;
};


const char* NIPAddapter(NIPAddr in_IPAddr);
