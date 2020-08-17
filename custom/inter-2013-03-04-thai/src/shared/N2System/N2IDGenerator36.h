#pragma once


class N2IDGenerator36
{
public:
	bool isOK() const;
	std::string Generate36(const DWORD in_dwID);
	int ReverseDecimal(const char* in_szValue);

public:
	static bool CreateInstance();
	static void DestroyInstance();
	static N2IDGenerator36* GetObj(); /// @custom

private:
	N2IDGenerator36();
	~N2IDGenerator36();
	N2IDGenerator36(N2IDGenerator36&); // = delete;
	N2IDGenerator36& operator=(N2IDGenerator36&); // = delete;

private:
	/* this+0 */ bool m_bOK;
	/* static */ static N2IDGenerator36*& m_cpSelf; //TODO
};
