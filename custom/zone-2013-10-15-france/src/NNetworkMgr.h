#pragma once
class NNetworkWorkThread;


class NNetworkMgr
{
public:
	bool isOK() const;
	unsigned int GenerateCompletionKey();
	HANDLE GetIOCPHandle();

public:
	bool Start();
	void Stop();

private:
	bool Create();
	void Destroy();

public:
	static bool CreateInstance();
	static void DestroyInstance();
	static NNetworkMgr* GetObj(); /// @custom

private:
	NNetworkMgr();
	virtual ~NNetworkMgr();

private:
	/* static  */ static NNetworkMgr*& m_cpSelf; //TODO
	/* this+ 0 */ //const NNetworkMgr::`vftable';
	/* this+ 4 */ bool m_bOK;
	/* this+ 8 */ HANDLE m_hIOCP;
	/* this+12 */ std::vector<NNetworkWorkThread*> m_ThreadPool;
};
