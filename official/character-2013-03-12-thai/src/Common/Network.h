#pragma once


class CNetwork
{
public:
	bool InitializeNetwork();
	void CleanupNetwork();
	std::string GetTextIP(const DWORD in_IPaddr) const;
	void GetTextIP(DWORD dwIP, char* lpszIP);
	DWORD GetDWORDIP(const char* lpszIP) const;
	bool IsPrivateIP(DWORD dwIP);
	DWORD GetDWORDIP2(const char* lpszIP) const;
//	void GetTextIP2(DWORD dwIP, char* lpszIP);
	DWORD GetLocalIP(bool mode);

public:
	static bool CreateInstance();
	static void DestroyInstance();
	static CNetwork* GetObj();

private:
	CNetwork();
	~CNetwork();

private:
	/* this+  0 */ WSADATA m_wsaData;
	/* this+400 */ LONG m_RefCounter;
	/* static   */ static CNetwork* m_cpSelf;
};
