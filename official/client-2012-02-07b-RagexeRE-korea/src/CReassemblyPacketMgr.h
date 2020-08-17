#pragma once


class CReassemblyPacketMgr
{
public:
	bool isOK() const;
	static bool CreateInstance();
	static void DestroyInstance();
//	static CReassemblyPacketMgr* GetObj();

private:
	bool Create();
	void Destroy();

private:
	CReassemblyPacketMgr();
	~CReassemblyPacketMgr();

private:
	/* this 0 */ bool m_bOK;
	/* static */ static CReassemblyPacketMgr*& m_cpSelf; //TODO
};
