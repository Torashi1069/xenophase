#pragma once


class CThreadAffinityMgr
{
public:
	bool isOK() const;
	unsigned long GetThreadAffinityMask();

public:
	static bool CreateInstance();
	static void DestroyInstance();
	static CThreadAffinityMgr* GetObj(); /// @custom

private:
	CThreadAffinityMgr();
	virtual ~CThreadAffinityMgr();
	CThreadAffinityMgr(const CThreadAffinityMgr&); // = delete;
	CThreadAffinityMgr& operator=(const CThreadAffinityMgr&); // = delete;

private:
	/* static */ static CThreadAffinityMgr*& m_cpSelf; //TODO
	/* this+0 */ //const CThreadAffinityMgr::`vftable';
	/* this+4 */ bool m_bOK;
	/* this+8 */ HANDLE m_hMutex;
};
