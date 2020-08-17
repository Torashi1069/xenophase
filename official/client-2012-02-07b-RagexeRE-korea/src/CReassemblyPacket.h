#pragma once


class CReassemblyPacket
{
public:
	void Seed(DWORD startVal, DWORD mulFactor, DWORD addFactor);
	int GetVal();

public:
	bool isOK() const;
	static bool CreateInstance();
	static void DestroyInstance();
	static CReassemblyPacket* GetObj();

private:
	CReassemblyPacket();
	~CReassemblyPacket();

private:
	/* this+ 0 */ bool m_bOK;
	/* this+ 4 */ DWORD m_currentVal;
	/* this+ 8 */ DWORD m_mulFactor;
	/* this+12 */ DWORD m_addFactor;
	/* static  */ static CReassemblyPacket*& m_cpSelf; //TODO
};
