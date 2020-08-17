#pragma once


class CStaticNPCAIDGenerator
{
public:
	bool IsOk();
	void Free(const int in_AID);
	int Alloc();

public:
	static bool CreateInstance(const int in_MinimumAID, const int in_MaximumAID);
	static void DestroyInsance();
	static CStaticNPCAIDGenerator* GetObj(); /// @custom

private:
	CStaticNPCAIDGenerator(const int in_MinimumAID, const int in_MaximumAID);
	virtual ~CStaticNPCAIDGenerator();

private:
	/* static  */ static CStaticNPCAIDGenerator*& m_cpSelf; //TODO
	/* this+ 0 */ //const CStaticNPCAIDGenerator::`vftable';
	/* this+ 4 */ bool m_bOK;
	/* this+ 8 */ const unsigned long m_MinimumAID;
	/* this+12 */ const unsigned long m_MaximumAID;
	/* this+16 */ std::list<int> m_AIDPool;
};


class CStaticNPCAID
{
public:
	CStaticNPCAID(const int in_AID) : m_AID(in_AID) { }
	virtual ~CStaticNPCAID() { CStaticNPCAIDGenerator::GetObj()->CStaticNPCAIDGenerator::Free(m_AID); }

public:
	int Release() { m_AID = 0; return 0; } // guessed
	operator int() { return m_AID; }

private:
	/* this+0 */ //const CStaticNPCAID::`vftable';
	/* this+4 */ int m_AID;
};
